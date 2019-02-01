/**
 * Copyright (c) 2016-2018 Netflix, Inc.  All rights reserved.
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

#ifndef SRC_MSLERROR_H_
#define SRC_MSLERROR_H_

#include <MslConstants.h>
#include <util/StaticMslMutex.h>
#include <string>

namespace netflix {
namespace msl {

/**
 * <p>Message Security Layer error codes and descriptions.</p>
 *
 * <p>Errors are defined with an internal and a response error code. The
 * internal error code is specific to this implementation. The response error
 * codes are sent in error messages to inform the remote entity, who should use
 * it to decide on the correct error handling behavior.</p>
 *
 * @author Wesley Miaw <wmiaw@netflix.com>
 */
class MslError
{
public:
    static const MslError
    // 0 Message Security Layer
    MSL_PARSE_ERROR,
    MSL_ENCODE_ERROR,
    ENVELOPE_HASH_MISMATCH,
    INVALID_PUBLIC_KEY,
    INVALID_PRIVATE_KEY,
    PLAINTEXT_ILLEGAL_BLOCK_SIZE,
    PLAINTEXT_BAD_PADDING,
    CIPHERTEXT_ILLEGAL_BLOCK_SIZE,
    CIPHERTEXT_BAD_PADDING,
    ENCRYPT_NOT_SUPPORTED,
    DECRYPT_NOT_SUPPORTED,
    ENVELOPE_KEY_ID_MISMATCH,
    CIPHERTEXT_ENVELOPE_PARSE_ERROR,
    CIPHERTEXT_ENVELOPE_ENCODE_ERROR,
    SIGN_NOT_SUPPORTED,
    VERIFY_NOT_SUPPORTED,
    SIGNATURE_ERROR,
    HMAC_ERROR,
    ENCRYPT_ERROR,
    DECRYPT_ERROR,
    INSUFFICIENT_CIPHERTEXT,
    SESSION_KEY_CREATION_FAILURE,
    INVALID_SYMMETRIC_KEY,
    INVALID_ENCRYPTION_KEY,
    INVALID_HMAC_KEY,
    WRAP_NOT_SUPPORTED,
    UNWRAP_NOT_SUPPORTED,
    UNIDENTIFIED_JWK_TYPE,
    UNIDENTIFIED_JWK_USAGE,
    UNIDENTIFIED_JWK_ALGORITHM,
    WRAP_ERROR,
    UNWRAP_ERROR,
    INVALID_JWK,
    INVALID_JWK_KEYDATA,
    UNSUPPORTED_JWK_ALGORITHM,
    WRAP_KEY_CREATION_FAILURE,
    INVALID_WRAP_CIPHERTEXT,
    UNSUPPORTED_JWE_ALGORITHM,
    JWE_ENCODE_ERROR,
    JWE_PARSE_ERROR,
    INVALID_ALGORITHM_PARAMS,
    JWE_ALGORITHM_MISMATCH,
    KEY_IMPORT_ERROR,
    KEY_EXPORT_ERROR,
    DIGEST_ERROR,
    UNSUPPORTED_KEY,
    UNSUPPORTED_JWE_SERIALIZATION,
    INVALID_WRAPPING_KEY,
    UNIDENTIFIED_CIPHERTEXT_ENVELOPE,
    UNIDENTIFIED_SIGNATURE_ENVELOPE,
    UNSUPPORTED_CIPHERTEXT_ENVELOPE,
    UNSUPPORTED_SIGNATURE_ENVELOPE,
    UNIDENTIFIED_CIPHERSPEC,
    UNIDENTIFIED_ALGORITHM,
    SIGNATURE_ENVELOPE_PARSE_ERROR,
    SIGNATURE_ENVELOPE_ENCODE_ERROR,
    INVALID_SIGNATURE,
    DERIVEKEY_ERROR,
    UNIDENTIFIED_JWK_KEYOP,
    GENERATEKEY_ERROR,
    INVALID_IV,
    INVALID_CIPHERTEXT,
    DATA_TOO_LARGE,
    CRYPTO_ERROR,

    // 1 Master Token
    MASTERTOKEN_UNTRUSTED,
    MASTERTOKEN_KEY_CREATION_ERROR,
    MASTERTOKEN_EXPIRES_BEFORE_RENEWAL,
    MASTERTOKEN_SESSIONDATA_MISSING,
    MASTERTOKEN_SEQUENCE_NUMBER_OUT_OF_RANGE,
    MASTERTOKEN_SERIAL_NUMBER_OUT_OF_RANGE,
    MASTERTOKEN_TOKENDATA_INVALID,
    MASTERTOKEN_SIGNATURE_INVALID,
    MASTERTOKEN_SESSIONDATA_INVALID,
    MASTERTOKEN_SEQUENCE_NUMBER_OUT_OF_SYNC,
    MASTERTOKEN_TOKENDATA_MISSING,
    MASTERTOKEN_TOKENDATA_PARSE_ERROR,
    MASTERTOKEN_SESSIONDATA_PARSE_ERROR,
    MASTERTOKEN_IDENTITY_REVOKED,
    MASTERTOKEN_REJECTED_BY_APP,
    MASTERTOKEN_ISSUERDATA_ENCODE_ERROR,

    // 2 User ID Token
    USERIDTOKEN_MASTERTOKEN_MISMATCH,
    USERIDTOKEN_NOT_DECRYPTED,
    USERIDTOKEN_MASTERTOKEN_NULL,
    USERIDTOKEN_EXPIRES_BEFORE_RENEWAL,
    USERIDTOKEN_USERDATA_MISSING,
    USERIDTOKEN_MASTERTOKEN_NOT_FOUND,
    USERIDTOKEN_MASTERTOKEN_SERIAL_NUMBER_OUT_OF_RANGE,
    USERIDTOKEN_SERIAL_NUMBER_OUT_OF_RANGE,
    USERIDTOKEN_TOKENDATA_INVALID,
    USERIDTOKEN_SIGNATURE_INVALID,
    USERIDTOKEN_USERDATA_INVALID,
    USERIDTOKEN_IDENTITY_INVALID,
    RESERVED_2012,
    USERIDTOKEN_USERAUTH_DATA_MISMATCH,
    USERIDTOKEN_TOKENDATA_MISSING,
    USERIDTOKEN_TOKENDATA_PARSE_ERROR,
    USERIDTOKEN_USERDATA_PARSE_ERROR,
    USERIDTOKEN_REVOKED,
    USERIDTOKEN_REJECTED_BY_APP,

    // 3 Service Token
    SERVICETOKEN_MASTERTOKEN_MISMATCH,
    SERVICETOKEN_USERIDTOKEN_MISMATCH,
    SERVICETOKEN_SERVICEDATA_INVALID,
    SERVICETOKEN_MASTERTOKEN_NOT_FOUND,
    SERVICETOKEN_USERIDTOKEN_NOT_FOUND,
    SERVICETOKEN_MASTERTOKEN_SERIAL_NUMBER_OUT_OF_RANGE,
    SERVICETOKEN_USERIDTOKEN_SERIAL_NUMBER_OUT_OF_RANGE,
    SERVICETOKEN_TOKENDATA_INVALID,
    SERVICETOKEN_SIGNATURE_INVALID,
    SERVICETOKEN_TOKENDATA_MISSING,

    // 4 Entity Authentication
    UNIDENTIFIED_ENTITYAUTH_SCHEME,
    ENTITYAUTH_FACTORY_NOT_FOUND,
    X509CERT_PARSE_ERROR,
    X509CERT_ENCODE_ERROR,
    X509CERT_VERIFICATION_FAILED,
    ENTITY_NOT_FOUND,
    INCORRECT_ENTITYAUTH_DATA,
    RSA_PUBLICKEY_NOT_FOUND,
    UNSUPPORTED_ENTITYAUTH_DATA,
    ENTITY_REVOKED,
    ENTITY_REJECTED_BY_APP,
    X509CERT_EXPIRED,
    X509CERT_NOT_YET_VALID,
    X509CERT_INVALID,
    RSA_PRIVATEKEY_NOT_FOUND,
    ENTITYAUTH_MASTERTOKEN_NOT_DECRYPTED,
    ENTITYAUTH_SIGNATURE_INVALID,
    ENTITYAUTH_CIPHERTEXT_INVALID,
    ENTITYAUTH_VERIFICATION_FAILED,
    ENTITYAUTH_MASTERTOKEN_INVALID,
    ECC_PUBLICKEY_NOT_FOUND,
    ECC_PRIVATEKEY_NOT_FOUND,

    // 5 User Authentication
    UNIDENTIFIED_USERAUTH_SCHEME,
    USERAUTH_FACTORY_NOT_FOUND,
    EMAILPASSWORD_BLANK,
    EMAILPASSWORD_INCORRECT,
    UNSUPPORTED_USERAUTH_DATA,
    USERAUTH_USERIDTOKEN_INVALID,
    UNIDENTIFIED_USERAUTH_MECHANISM,
    UNSUPPORTED_USERAUTH_MECHANISM,
    USERAUTH_MASTERTOKEN_MISSING,
    USERAUTH_USERIDTOKEN_NOT_DECRYPTED,
    USERAUTH_MASTERTOKEN_INVALID,
    USERAUTH_MASTERTOKEN_NOT_DECRYPTED,
    USERAUTH_USERIDTOKEN_MISSING,
    USERAUTH_ENTITY_MISMATCH,
    USERAUTH_ENTITY_INCORRECT_DATA,
    USER_REJECTED_BY_APP,
    USERIDTOKEN_IDENTITY_NOT_ASSOCIATED_WITH_ENTITY,
    USERAUTH_ENTITYUSER_INCORRECT_DATA,
    USERAUTH_VERIFICATION_FAILED,
    USERAUTH_USERIDTOKEN_REVOKE_CHECK_ERROR,

    // 6 Message
    UNSUPPORTED_COMPRESSION,
    COMPRESSION_ERROR,
    UNCOMPRESSION_ERROR,
    MESSAGE_ENTITY_NOT_FOUND,
    PAYLOAD_MESSAGE_ID_MISMATCH,
    PAYLOAD_SEQUENCE_NUMBER_MISMATCH,
    PAYLOAD_VERIFICATION_FAILED,
    MESSAGE_DATA_MISSING,
    MESSAGE_FORMAT_ERROR,
    MESSAGE_VERIFICATION_FAILED,
    HEADER_DATA_MISSING,
    PAYLOAD_DATA_MISSING,
    PAYLOAD_DATA_CORRUPT,
    UNIDENTIFIED_COMPRESSION,
    MESSAGE_EXPIRED,
    MESSAGE_ID_OUT_OF_RANGE,
    INTERNAL_CODE_NEGATIVE,
    UNEXPECTED_RESPONSE_MESSAGE_ID,
    RESPONSE_REQUIRES_ENCRYPTION,
    PAYLOAD_SEQUENCE_NUMBER_OUT_OF_RANGE,
    PAYLOAD_MESSAGE_ID_OUT_OF_RANGE,
    MESSAGE_REPLAYED,
    INCOMPLETE_NONREPLAYABLE_MESSAGE,
    HEADER_SIGNATURE_INVALID,
    HEADER_DATA_INVALID,
    PAYLOAD_INVALID,
    PAYLOAD_SIGNATURE_INVALID,
    RESPONSE_REQUIRES_MASTERTOKEN,
    RESPONSE_REQUIRES_USERIDTOKEN,
    REQUEST_REQUIRES_USERAUTHDATA,
    UNEXPECTED_MESSAGE_SENDER,
    NONREPLAYABLE_MESSAGE_REQUIRES_MASTERTOKEN,
    NONREPLAYABLE_ID_OUT_OF_RANGE,
    MESSAGE_SERVICETOKEN_MISMATCH,
    MESSAGE_PEER_SERVICETOKEN_MISMATCH,
    RESPONSE_REQUIRES_INTEGRITY_PROTECTION,
    HANDSHAKE_DATA_MISSING,
    MESSAGE_RECIPIENT_MISMATCH,
    MESSAGE_ENTITYDATABASED_VERIFICATION_FAILED,
    MESSAGE_MASTERTOKENBASED_VERIFICATION_FAILED,
    MESSAGE_REPLAYED_UNRECOVERABLE,
    UNEXPECTED_LOCAL_MESSAGE_SENDER,
    UNENCRYPTED_MESSAGE_WITH_USERAUTHDATA,
    MESSAGE_SENDER_MISMATCH,
    MESSAGE_EXPIRED_NOT_RENEWABLE,
    MESSAGE_EXPIRED_NO_KEYREQUEST_DATA,

    // 7 Key Exchange
    UNIDENTIFIED_KEYX_SCHEME,
    KEYX_FACTORY_NOT_FOUND,
    KEYX_REQUEST_NOT_FOUND,
    UNIDENTIFIED_KEYX_KEY_ID,
    UNSUPPORTED_KEYX_KEY_ID,
    UNIDENTIFIED_KEYX_MECHANISM,
    UNSUPPORTED_KEYX_MECHANISM,
    KEYX_RESPONSE_REQUEST_MISMATCH,
    KEYX_PRIVATE_KEY_MISSING,
    UNKNOWN_KEYX_PARAMETERS_ID,
    KEYX_MASTER_TOKEN_MISSING,
    KEYX_INVALID_PUBLIC_KEY,
    KEYX_PUBLIC_KEY_MISSING,
    KEYX_WRAPPING_KEY_MISSING,
    KEYX_WRAPPING_KEY_ID_MISSING,
    KEYX_INVALID_WRAPPING_KEY,
    KEYX_INCORRECT_DATA,
    KEYX_INCORRECT_MECHANISM,
    KEYX_DERIVATION_KEY_MISSING,
    KEYX_INVALID_ENCRYPTION_KEY,
    KEYX_INVALID_HMAC_KEY,
    KEYX_INVALID_WRAPDATA,
    UNSUPPORTED_KEYX_SCHEME,
    KEYX_IDENTITY_NOT_FOUND,

    // 9 Internal Errors
    INTERNAL_EXCEPTION,
    MSL_COMMS_FAILURE,
    NONE,

    // No Error
    OK;

    virtual ~MslError() {}

    /**
     * @return the internal error code.
     */
    inline int32_t getInternalCode() const { return internalCode_; }

    /**
     * @return the response error code.
     */
    inline MslConstants::ResponseCode getResponseCode() const { return responseCode_; }

    /**
     * @return the error message.
     */
    inline std::string getMessage() const { return msg_; }

    /**
     * @param rhs the reference object with which to compare.
     * @return true if the internal code and response code are equal.
     */
    inline bool operator==(const MslError& rhs) const {
        return (internalCode_ == rhs.internalCode_) &&
               (responseCode_ == rhs.responseCode_);
    }

    /**
     * @param rhs the reference object with which to compare.
     * @return true if the internal code and response code are not equal.
     */
    inline bool operator!=(const MslError& rhs) const { return !(*this == rhs); }

    // operator<< for easier use with output
    friend std::ostream & operator<<(std::ostream& os, const MslError& me);

    MslError(const MslError& other);
    MslError& operator=(const MslError& other);

    /**
     * Construct a MSL error with the specified internal and response error
     * codes and message.
     *
     * @param internalCode internal error code.
     * @param responseCode response error code.
     * @param msg developer-consumable error message.
     */
    MslError(int internalCode, const MslConstants::ResponseCode& responseCode, const std::string& msg);

protected:    
    MslError(); // not implemented

    static const int BASE = 100000;
    /** Mutex that protects internal error code set. */
    static util::StaticMslMutex& internalCodesLock();
    /** Internal error code set. */
    static std::set<int>& internalCodes();

    /** Internal error code. */
    int internalCode_;
    /** Response error code. */
    MslConstants::ResponseCode responseCode_;
    /** Error message. */
    std::string msg_;

    friend class MslErrorTest_DuplicateConstruction_Test;  // For testing only
};

std::ostream & operator<<(std::ostream& os, const MslError& me);

}} //namespace netflix::msl

#endif /* SRC_MSLERROR_H_ */
