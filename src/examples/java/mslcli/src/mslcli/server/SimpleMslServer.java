/**
 * Copyright (c) 2014 Netflix, Inc.  All rights reserved.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package mslcli.server;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.security.Security;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.Future;

import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;

import org.bouncycastle.jce.provider.BouncyCastleProvider;

import com.netflix.msl.MslConstants;
import com.netflix.msl.MslCryptoException;
import com.netflix.msl.crypto.ICryptoContext;
import com.netflix.msl.crypto.JcaAlgorithm;
import com.netflix.msl.crypto.SymmetricCryptoContext;
import com.netflix.msl.entityauth.PresharedKeyStore;
import com.netflix.msl.entityauth.RsaStore;
import com.netflix.msl.msg.ConsoleFilterStreamFactory;
import com.netflix.msl.msg.ErrorHeader;
import com.netflix.msl.msg.MessageContext;
import com.netflix.msl.msg.MessageInputStream;
import com.netflix.msl.msg.MslControl;
import com.netflix.msl.msg.MslControl.MslChannel;
import com.netflix.msl.tokens.MslUser;
import com.netflix.msl.userauth.EmailPasswordStore;
import com.netflix.msl.util.MslContext;
import com.netflix.msl.util.MslStore;

import static mslcli.common.Constants.*;
import mslcli.common.util.SharedUtil;
import mslcli.server.msg.ServerReceiveMessageContext;
import mslcli.server.msg.ServerRespondMessageContext;
import mslcli.server.util.ServerMslContext;

/**
 * <p>An example Java MSL server that listens for requests from the example MSL client.
 * </p> 
 * 
 * <p>This class is thread-safe.</p>
 * 
 * @author Vadim Spector <vspector@netflix.com>
 */

public class SimpleMslServer {
    private static final long serialVersionUID = -4593207843035538485L;
    
    /** Line separator. */
    private static final String NEWLINE = System.lineSeparator();
    
    /** Service token key set ID. */
    private static final String ST_KEYSET_ID = "serviceTokenKeySetId";

    /** Service token encryption key. */
    private static final byte[] ST_ENCRYPTION_KEY = SharedUtil.hexStringToByteArray("000102030405060708090A0B0C0D0E0F");

    /** Service token HMAC key. */
    private static final byte[] ST_HMAC_KEY = SharedUtil.hexStringToByteArray("000102030405060708090A0B0C0D0E0F101112131415161718191A1B1C1D1E1F");
    
    // Add BouncyCastle provider.
    static {
        Security.addProvider(new BouncyCastleProvider());
    }
    
    /**
     * <p>Create a new server instance and initialize its static, immutable state.
     * </p>
     */
    public SimpleMslServer() {
        // Create the MSL control.
        //
        // Since this is an example process all requests on the calling thread.
        this.mslCtrl = new MslControl(0);
        mslCtrl.setFilterFactory(new ConsoleFilterStreamFactory());

        /* Initialize memory-backed MSL store.
         * This class is implemented in MSL core
         */
        final MslStore mslStore = SharedUtil.getServerMslStore();

        // Create the pre-shared key store.
        final PresharedKeyStore presharedKeyStore = SharedUtil.getPresharedKeyStore();

        // Create the RSA key store.
        final RsaStore rsaStore = SharedUtil.getRsaStore();

       // Create the email/password store.
        final EmailPasswordStore emailPasswordStore = SharedUtil.getEmailPasswordStore();
        
        // Set up the MSL context.
        this.mslCtx = new ServerMslContext(SERVER_ID, presharedKeyStore, rsaStore, emailPasswordStore, mslStore);
        
        // Use one crypto context for all service tokens.
        final SecretKey encryptionKey = new SecretKeySpec(ST_ENCRYPTION_KEY, JcaAlgorithm.AES);
        final SecretKey hmacKey = new SecretKeySpec(ST_HMAC_KEY, JcaAlgorithm.HMAC_SHA256);
        final ICryptoContext stCryptoContext = new SymmetricCryptoContext(this.mslCtx, ST_KEYSET_ID, encryptionKey, hmacKey, null);
        cryptoContexts.put("", stCryptoContext);
    }
    
    public void processRequest(final InputStream in, final OutputStream out) throws IOException {
        //  Set up the receive MSL message context.
        final MessageContext rcvMsgCtx = new ServerReceiveMessageContext(cryptoContexts);

        // Receive a request.
        final MessageInputStream requestInputStream;
        final Future<MessageInputStream> requestFuture = mslCtrl.receive(mslCtx, rcvMsgCtx, in, out, TIMEOUT_MS);
        try {
            requestInputStream = requestFuture.get();
            if (requestInputStream == null) {
                System.err.println("NULL Input Stream ?");
                return;
            }
        } catch (final ExecutionException e) {
            throw new IOException("ExecutionException", e);
        } catch (final InterruptedException e) {
            throw new IOException("InterruptedException", e);
        }

        // We should not receive error headers but check just in case.
        final ErrorHeader error = requestInputStream.getErrorHeader();
        if (error != null) {
            throw new IOException("Unexpectedly received error message: [" + error.getErrorCode() + "][" + error.getInternalCode() + "][" + error.getErrorMessage() + "]");
        }

        // Process request.
        final String clientId;
        try {
            clientId = requestInputStream.getIdentity();
        } catch (MslCryptoException e) {
            throw new IOException("Error Extracting Identity from Request", e);
        }
        final MslUser user = requestInputStream.getUser();
        final byte[] request = SharedUtil.readIntoArray(requestInputStream);

        //  Set up the respond MSL message context. Echo back the initial request.
        final MessageContext responseMsgCtx = new ServerRespondMessageContext(clientId, true, new String(request, MslConstants.DEFAULT_CHARSET));

        // Send response. We don't need the MslChannel because we are not
        // opening a persistent channel.
        final Future<MslChannel> channelFuture = mslCtrl.respond(mslCtx, responseMsgCtx, in, out, requestInputStream, TIMEOUT_MS);
        try {
            channelFuture.get();
        } catch (final ExecutionException e) {
            throw new IOException("ExecutionException", e);
        } catch (final InterruptedException e) {
            System.err.println("MslControl.receive() interrupted.");
            return;
        }
    }
    
    /** MSL context. */
    private final MslContext mslCtx;

    /** MSL control. */
    private final MslControl mslCtrl;

    /** Service token crypto contexts. */
    private final Map<String,ICryptoContext> cryptoContexts = new HashMap<String,ICryptoContext>();
}
