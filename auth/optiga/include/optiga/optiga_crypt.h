/**
* \copyright
* MIT License
*
* Copyright (c) 2020 Infineon Technologies AG
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE
*
* \endcopyright
*
* \author Infineon Technologies AG
*
* \file optiga_crypt.h
*
* \brief   This file implements the prototype declarations of OPTIGA Crypt module.
*
* \ingroup  grOptigaCrypt
*
* @{
*/

#ifndef _OPTIGA_CRYPT_H_
#define _OPTIGA_CRYPT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "optiga_cmd.h"

/** \brief union for OPTIGA crypt parameters */
typedef union optiga_crypt_params
{
    /// get random params
    optiga_get_random_params_t optiga_get_random_params;
    /// get key pair params
    optiga_gen_keypair_params_t optiga_gen_keypair_params;
    /// calc sign params
    optiga_calc_sign_params_t optiga_calc_sign_params;
    /// verify sign params
    optiga_verify_sign_params_t optiga_verify_sign_params;
    /// calc hash params
    optiga_calc_hash_params_t optiga_calc_hash_params;
}optiga_crypt_params_t;

/** \brief OPTIGA crypt instance structure */
struct optiga_crypt
{
    /// Details/references (pointers) to the Application Inputs
    optiga_crypt_params_t params;
    /// Command module instance
    optiga_cmd_t * my_cmd;
    /// Caller context
    void * caller_context;
    /// Callback handler
    callback_handler_t handler;
    ///To provide the busy/free status of the crypt instance
    uint16_t instance_state;
#ifdef OPTIGA_COMMS_SHIELDED_CONNECTION
    /// To provide the encryption and decryption need for command and response
    uint8_t protection_level;
    /// To provide the presentation layer protocol version to be used
    uint8_t protocol_version;
#endif //OPTIGA_COMMS_SHIELDED_CONNECTION

};

/** \brief OPTIGA crypt instance structure type*/
typedef struct optiga_crypt optiga_crypt_t;

#ifdef OPTIGA_COMMS_SHIELDED_CONNECTION
/**
 * \brief Sets/updates the OPTIGA Comms Shielded connection configuration in
 *        the respective (optiga_util) instance.
 *
 *\details
 * Sets/updates the OPTIGA Comms Shielded connection configuration in the respective (optiga_util) instance.
 * - The #OPTIGA_COMMS_PROTECTION_LEVEL configuration settings using this API, will be used in the next immediate usage of the instance.
 * - Once the API is invoked, this level gets reset to the default protection level #OPTIGA_COMMS_DEFAULT_PROTECTION_LEVEL
 *
 *\pre
 * - None
 *
 *\note
 * - None
 *
 * \param[in,out]  me                     Valid instance of #optiga_util_t
 * \param[in]      parameter_type         Parameter Type
 *                                        Possible Types are
 *                                        #OPTIGA_COMMS_PROTECTION_LEVEL
 *                                        #OPTIGA_COMMS_PROTOCOL_VERSION
 *
 * \param[in]      value                  Value part for the respective configuration
 *
 * <b>Example</b><br>
 *
 */
void optiga_crypt_set_comms_params(optiga_crypt_t * me,
                                   uint8_t parameter_type,
                                   uint8_t value);
#endif

/**
 * \brief Create an instance of #optiga_crypt_t.
 *
 * \details
 * Create an instance of #optiga_crypt_t.
 * - Stores the callers context and callback handler.
 * - Allocate memory for #optiga_crypt_t.
 *
 * \pre
 * - None
 *
 * \note
 * - This API is implemented in synchronous mode.
 * - For <b>protected I2C communication</b>,
 *      - Default protection level for this API is #OPTIGA_COMMS_DEFAULT_PROTECTION_LEVEL.
 *      - Default protocol version for this API is #OPTIGA_COMMS_PROTOCOL_VERSION_PRE_SHARED_SECRET.
 *
 * \param[in]   optiga_instance_id  Indicates the OPTIGA instance to be associated with #optiga_crypt_t. Should be defined as below:
 *                                  Use #OPTIGA_INSTANCE_ID_0.
 * \param[in]   handler             Pointer to callback function, must not be NULL.
 * \param[in]   caller_context      Pointer to upper layer context. Contains user context data.
 *
 * \retval      #optiga_crypt_t     On success function will return pointer of #optiga_crypt_t.
 * \retval      NULL                Input arguments are NULL.<br>
 *                                  Low layer function fails.<br>
 *                                  OPTIGA_CMD_MAX_REGISTRATIONS number of instances are already created.
 */
LIBRARY_EXPORTS optiga_crypt_t * optiga_crypt_create(uint8_t optiga_instance_id,
                                                     callback_handler_t handler,
                                                     void * caller_context);

/**
 * \brief Destroys an instance of #optiga_crypt_t.
 *
 * \details
 * Destroys the #optiga_crypt_t instance.
 * - De-allocate the memory of the #optiga_crypt_t instance.
 *
 * \pre
 * - An instance of optiga_crypt using #optiga_crypt_create must be available.<br>
 *
 * \note
 *  - User must take care to nullify the instance pointer.
 *  - Invoke this API only after all the asynchronous process is completed otherwise the behavior of software stack is not defined.
 *
 * \param[in] me                                      Valid instance of #optiga_crypt_t.
 *
 * \retval    #OPTIGA_LIB_SUCCESS                    Successful invocation.
 * \retval    #OPTIGA_CRYPT_ERROR_INVALID_INPUT       Wrong Input arguments provided.
 * \retval    #OPTIGA_CRYPT_ERROR_INSTANCE_IN_USE     The previous operation with the same instance is not complete.
 *
 */
LIBRARY_EXPORTS optiga_lib_status_t optiga_crypt_destroy(optiga_crypt_t * me);

#ifdef OPTIGA_CRYPT_RANDOM_ENABLED
/**
 * \brief Generates a random number.
 *
 * \details
 * Generates the requested random stream of data for the user provided length.
 * - Invokes #optiga_cmd_get_random API, based on the input arguments to retrieve random data .
 *
 * \pre
 * - The application on OPTIGA must be opened using #optiga_util_open_application before using this API.
 *
 * \note
 * - For <b>protected I2C communication</b>, Refer #OPTIGA_CRYPT_SET_COMMS_PROTECTION_LEVEL
 * - Error codes from lower layers is returned as it is.<br>
 * - The maximum value of the <b>random_data_length</b> parameter is size of buffer <b>random_data</b>.
 *   In case the value is greater than buffer size, memory corruption can occur.<br>
 *
 * \param[in]      me                                       Valid instance of #optiga_crypt_t created using #optiga_crypt_create.
 * \param[in]      rng_type                                 Type of random data generator.
 *                                                          - The input must be from #optiga_rng_type.
 *                                                          - Argument check for rng_type is not done since OPTIGA will provide an error for invalid rng_type.
 * \param[in,out]  random_data                              Pointer to the buffer into which random data is stored, must not be NULL.
 * \param[in]      random_data_length                       Length of random data to be generated.
 *                                                          - Range should be 8 - 256 bytes.
 *                                                          - Length validation is not done, since OPTIGA will provide an error for invalid random_data_length.
 *
 * \retval         #OPTIGA_CRYPT_SUCCESS                    Successful invocation.
 * \retval         #OPTIGA_CRYPT_ERROR_INVALID_INPUT        Wrong Input arguments provided.
 * \retval         #OPTIGA_CRYPT_ERROR_INSTANCE_IN_USE      The previous operation with the same instance is not complete.
 * \retval         #OPTIGA_DEVICE_ERROR                     Command execution failure in OPTIGA and the LSB indicates the error code.
 *                                                          (Refer Solution Reference Manual)
 *
 * <b>Example</b><br>
 * example_optiga_crypt_random.c
 *
 */
LIBRARY_EXPORTS optiga_lib_status_t optiga_crypt_random(optiga_crypt_t * me,
                                                        optiga_rng_type_t rng_type,
                                                        uint8_t * random_data,
                                                        uint16_t random_data_length);
#endif //OPTIGA_CRYPT_RANDOM_ENABLED

#ifdef OPTIGA_CRYPT_HASH_ENABLED
/**
 *
 * \brief Updates a hashing for input data and returns digest.
 *
 * \details
 * Updates hashing for the given data and returns digest.<br>
 *
 * \pre
 * - The application on OPTIGA must be opened using #optiga_util_open_application.<br>
 *
 * \note
 * - For <b>protected I2C communication</b>, Refer #OPTIGA_CRYPT_SET_COMMS_PROTECTION_LEVEL.
 * - Error codes from lower layer will be returned as it is.<br>
 *
 *<br>
 * \param[in]      me                                        Valid instance of #optiga_crypt_t created using #optiga_crypt_create.
 * \param[in]      hash_algorithm                            Hash algorithm of #optiga_hash_type_t.
 * \param[in]      source_of_data_to_hash                    Data from host / Data in OPTIGA. Must be one of the below
 *                                                           - #OPTIGA_CRYPT_HOST_DATA or Non-Zero value ,if source of data is from Host.
 *                                                           - #OPTIGA_CRYPT_OID_DATA, if the source of data is from OPTIGA.
 * \param[in]      data_to_hash                              Data for hashing either in #hash_data_from_host_t or in #hash_data_in_optiga_t
 * \param[inout]   hash_output                               Pointer to the valid buffer to store hash output.
 *
 * \retval         #OPTIGA_CRYPT_SUCCESS                     Successful invocation.
 * \retval         #OPTIGA_CRYPT_ERROR_INVALID_INPUT         Wrong Input arguments provided.
 * \retval         #OPTIGA_CRYPT_ERROR_INSTANCE_IN_USE       The previous operation with the same instance is not complete.
 * \retval         #OPTIGA_DEVICE_ERROR                      Command execution failure in OPTIGA and the LSB indicates the error code.
 *                                                           (Refer Solution Reference Manual)
 *
 * <b>Example</b><br>
 * example_optiga_crypt_hash.c
 *
 */
LIBRARY_EXPORTS optiga_lib_status_t optiga_crypt_hash(optiga_crypt_t * me,
                                                      optiga_hash_type_t hash_algorithm,
                                                      uint8_t source_of_data_to_hash,
                                                      const void * data_to_hash, 
                                                      uint8_t * hash_output);
                                      
 /**
 *
 * \brief Initializes a hash context.
 *
 * \details
 * Sets up a hash context and exports it.
 * - Invokes #optiga_cmd_calc_hash API, based on the input arguments.<br>
 * - Initializes a new hash context.<br>
 * - Exports the hash context to caller.<br>
 * - The callback registered with instance (#optiga_crypt_create) gets invoked, when the operation is asynchronously completed.<br>
 *
 * \pre
 * - The application on OPTIGA must be opened using #optiga_util_open_application before using this API.<br>
 *
 * \note
 * - For <b>protected I2C communication</b>, Refer #OPTIGA_CRYPT_SET_COMMS_PROTECTION_LEVEL.
 * - Error codes from lower layer will be returned as it is.<br>
 * - User must save the output hash context for further usage because OPTIGA does not store it internally.<br>
 *
 *<br>
 * \param[in]      me                                        Valid instance of #optiga_crypt_t created using #optiga_crypt_create.
 * \param[inout]   hash_ctx                                  Pointer to #optiga_hash_context_t to store the hash context from OPTIGA.
 *                                                           - The minimum size of the <b>context_buffer</b> must be #OPTIGA_HASH_CONTEXT_LENGTH_SHA_256 bytes in #optiga_hash_context_t for hash algo #OPTIGA_HASH_TYPE_SHA_256.
 *                                                           - The input <b>hash_algo</b> in  <b>hash_ctx</b> must be from #optiga_hash_type.
 *
 * \retval         #OPTIGA_CRYPT_SUCCESS                     Successful invocation.
 * \retval         #OPTIGA_CRYPT_ERROR_INVALID_INPUT         Wrong Input arguments provided.
 * \retval         #OPTIGA_CRYPT_ERROR_INSTANCE_IN_USE       The previous operation with the same instance is not complete.
 * \retval         #OPTIGA_DEVICE_ERROR                      Command execution failure in OPTIGA and the LSB indicates the error code.
 *                                                           (Refer Solution Reference Manual)
 *
 * <b>Example</b><br>
 * example_optiga_crypt_hash.c
 *
 */
LIBRARY_EXPORTS optiga_lib_status_t optiga_crypt_hash_start(optiga_crypt_t * me,
                                                            optiga_hash_context_t * hash_ctx);


 /**
 * \brief Updates a hash context with the input data.
 *
 * \details
 * Updates hashing for the given data and hash context then export the updated hash context.<br>
 * - Invokes #optiga_cmd_calc_hash API, based on the input arguments.<br>
 * - Update the input hash context.<br>
 * - Exports the hash context to caller.<br>
 * - The callback registered with instance (#optiga_crypt_create) gets invoked, when the operation is asynchronously completed.<br>
 *
 * \pre
 * - The application on OPTIGA must be opened using #optiga_util_open_application before using this API.
 * - #optiga_hash_context_t from #optiga_crypt_hash_start or #optiga_crypt_hash_update must be available.
 *
 * \note<br>
 * - For <b>protected I2C communication</b>, Refer #OPTIGA_CRYPT_SET_COMMS_PROTECTION_LEVEL
 * - Error codes from lower layer will be returned as it is.<br>
 * - User must save the output hash context for further usage as OPTIGA does not store it internally.
 *
 * \param[in]   me                                      Valid instance of #optiga_crypt_t created using #optiga_crypt_create.
 * \param[in]   hash_ctx                                Pointer to #optiga_hash_context_t containing hash context from OPTIGA, must not be NULL
 *                                                      - The minimum size of the <b>context_buffer</b> must be #OPTIGA_HASH_CONTEXT_LENGTH_SHA_256 bytes in #optiga_hash_context_t for hash algo #OPTIGA_HASH_TYPE_SHA_256.
 * \param[in]   source_of_data_to_hash                  Data from host / Data in optiga. Must be one of the below
 *                                                      - #OPTIGA_CRYPT_HOST_DATA or Non-Zero value ,if source of data is from Host.
 *                                                      - #OPTIGA_CRYPT_OID_DATA, if the source of data is from OPITGA.
 * \param[in]   data_to_hash                            Data for hashing either in #hash_data_from_host or in #hash_data_in_optiga
 *
 * \retval      #OPTIGA_CRYPT_SUCCESS                   Successful invocation.
 * \retval      #OPTIGA_CRYPT_ERROR_INVALID_INPUT       Wrong Input arguments provided.
 * \retval      #OPTIGA_CRYPT_ERROR_INSTANCE_IN_USE     The previous operation with the same instance is not complete.
 * \retval      #OPTIGA_DEVICE_ERROR                    Command execution failure in OPTIGA and the LSB indicates the error code.
 *                                                      (Refer Solution Reference Manual)
 *
 * <b>Example</b><br>
 * example_optiga_crypt_hash.c
 *
 */
LIBRARY_EXPORTS optiga_lib_status_t optiga_crypt_hash_update(optiga_crypt_t * me,
                                                             optiga_hash_context_t * hash_ctx,
                                                             uint8_t source_of_data_to_hash,
                                                             const void * data_to_hash);

 /**
 *
 * \brief Finalizes and exports the hash output.
 *
 * \details
 * Finalizes the hash context and returns hash as output.
 * - Invokes #optiga_cmd_calc_hash API, based on the input arguments.<br>
 * - Finalize the hash from the input hash context
 * - Exports the finalized hash.
 * - The callback registered with instance (#optiga_crypt_create) gets invoked, when the operation is asynchronously completed.
 *
 * \pre
 * - The application on OPTIGA must be opened using #optiga_util_open_application before using this API.
 * - #optiga_hash_context_t from #optiga_crypt_hash_start or #optiga_crypt_hash_update must be available.
 *
 * \note
 * - For <b>protected I2C communication</b>, Refer #OPTIGA_CRYPT_SET_COMMS_PROTECTION_LEVEL
 * - Error codes from lower layer will be returned as it is.
 * - hash context is not updated by this API. This can be used later to fulfill intermediate hash use-cases.
 * - User must save the output hash context for further usage as OPTIGA does not store it internally.
 *
 * \param[in]      me                                      Valid instance of #optiga_crypt_t created using #optiga_crypt_create.
 * \param[in]      hash_ctx                                Pointer to #optiga_hash_context_t containing hash context from OPTIGA, must not be NULL.
 *                                                         - The minimum size of the <b>context_buffer</b> must be #OPTIGA_HASH_CONTEXT_LENGTH_SHA_256 bytes in #optiga_hash_context_t for hash algo #OPTIGA_HASH_TYPE_SHA_256.
 * \param[inout]   hash_output                             Output Hash.
 *
 * \retval         #OPTIGA_CRYPT_SUCCESS                   Successful invocation.
 * \retval         #OPTIGA_CRYPT_ERROR_INVALID_INPUT       Wrong Input arguments provided.
 * \retval         #OPTIGA_CRYPT_ERROR_INSTANCE_IN_USE     The previous operation with the same instance is not complete.
 * \retval         #OPTIGA_DEVICE_ERROR                    Command execution failure in OPTIGA and the LSB indicates the error code.
 *                                                         (Refer Solution Reference Manual)
 *
 * <b>Example</b><br>
 * example_optiga_crypt_hash.c
 *
 */
LIBRARY_EXPORTS optiga_lib_status_t optiga_crypt_hash_finalize(optiga_crypt_t * me,
                                                               optiga_hash_context_t * hash_ctx,
                                                               uint8_t * hash_output);

#endif //OPTIGA_CRYPT_HASH_ENABLED


#ifdef OPTIGA_CRYPT_ECC_GENERATE_KEYPAIR_ENABLED

/**
 * \brief Generates a key pair based on ECC curves.
 *
 * \details
 * Generates an ECC key-pair based on the input curve.
 * - Invokes #optiga_cmd_gen_keypair API, based on the input arguments.<br>
 * - Generate an ECC key pair using OPTIGA.
 * - Private key is exported only if explicitly requested otherwise it is stored in the input private key OID.
 * - Public key is always exported.
 * - The callback registered with instance (#optiga_crypt_create) gets invoked, when the operation is asynchronously completed.
 *
 * \pre
 * - The application on OPTIGA must be opened using #optiga_util_open_application before using this API.
 *
 * \note
 * - For <b>protected I2C communication</b>, Refer #OPTIGA_CRYPT_SET_COMMS_PROTECTION_LEVEL
 * - Error codes from lower layers is returned as it is.
 *
 * \param[in]       me                                      Valid instance of #optiga_crypt_t created using #optiga_crypt_create.
 * \param[in]       curve_id                                ECC curve id as #optiga_ecc_curve.
 * \param[in]       key_usage                               Key usage defined in #optiga_key_usage_t.
 *                                                          - Values from #optiga_key_usage can be logically ORed and passed.<br>
 *                                                          - It is ignored if export_private_key is TRUE (1).
 * \param[in]       export_private_key                      TRUE (1) or Non-Zero value - Exports private key to the host.<br>
 *                                                          FALSE (0) - Exports only public key to the host and writes private key to OPTIGA. The input key_usage is ignored.
 * \param[in]       private_key                             Buffer to store private key or private key OID of OPTIGA, must not be NULL.
 *                                                          - If export_private_key is TRUE, assign pointer to a buffer to store private key.
 *                                                          - The size of the buffer must be sufficient enough to accommodate the key type and additional DER encoding formats.
 *                                                          - If export_private_key is FALSE, assign pointer to variable of type #optiga_key_id_t.
 * \param[in,out]   public_key                              Buffer to store public key, must not be NULL.
 * \param[in]       public_key_length                       Initially set as length of buffer to store public_key, later updated as actual length of public_key.
 *
 * \retval          #OPTIGA_CRYPT_SUCCESS                   Successful invocation.
 * \retval          #OPTIGA_CRYPT_ERROR_INVALID_INPUT       Wrong Input arguments provided.
 * \retval          #OPTIGA_CRYPT_ERROR_INSTANCE_IN_USE     The previous operation with the same instance is not complete.
 * \retval          #OPTIGA_DEVICE_ERROR                    Command execution failure in OPTIGA and the LSB indicates the error code.
 *                                                          (Refer Solution Reference Manual)
 *
 * <b>Example</b><br>
 * example_optiga_crypt_ecc_generate_keypair.c
 *
 */
LIBRARY_EXPORTS optiga_lib_status_t optiga_crypt_ecc_generate_keypair(optiga_crypt_t * me,
                                                                      optiga_ecc_curve_t curve_id,
                                                                      uint8_t key_usage,
                                                                      bool_t export_private_key,
                                                                      void * private_key,
                                                                      uint8_t * public_key,
                                                                      uint16_t * public_key_length);
#endif //OPTIGA_CRYPT_ECC_GENERATE_KEYPAIR_ENABLED

#ifdef OPTIGA_CRYPT_ECDSA_SIGN_ENABLED
 /**
 * \brief Generates a signature for the given digest.
 *
 * \details
 * Generates a signature for the given digest using private key stored in OPTIGA.
 * - Invokes #optiga_cmd_calc_sign API, based on the input arguments.<br>
 * - Generates signature for the input digest.
 * - Exports the generated signature.
 * - The callback registered with instance (#optiga_crypt_create) gets invoked, when the operation is asynchronously completed.
 *
 * \pre
 * - The application on OPTIGA must be opened using #optiga_util_open_application before using this API.<br>
 * - If the private_key type is #OPTIGA_KEY_ID_SESSION_BASED then session must be already available in the instance. (For .e.g Using #optiga_crypt_ecc_generate_keypair )
 * \note
 * - For <b>protected I2C communication</b>, Refer #OPTIGA_CRYPT_SET_COMMS_PROTECTION_LEVEL
 * - Error codes from lower layers is returned as it is.
 *
 * \param[in]      me                                       Valid instance of #optiga_crypt_t created using #optiga_crypt_create.
 * \param[in]      digest                                   Digest on which signature is generated.
 * \param[in]      digest_length                            Length of the input digest.
 * \param[in]      private_key                              Private key OID to generate signature.
 * \param[in,out]  signature                                Pointer to store generated signature, must not be NULL.
 *                                                          - The size of the buffer must be sufficient enough to accommodate the additional
 *                                                          DER encoding formatting for R and S components of signature.
 * \param[in,out]  signature_length                         Length of signature. Initial value set as length of buffer, later updated as the actual length of generated signature.
 *
 * \retval         #OPTIGA_CRYPT_SUCCESS                    Successful invocation.
 * \retval         #OPTIGA_CRYPT_ERROR_INVALID_INPUT        Wrong Input arguments provided.<br>
                                                            Session is not available in instance and the private_key type is #OPTIGA_KEY_ID_SESSION_BASED
 * \retval         #OPTIGA_CRYPT_ERROR_INSTANCE_IN_USE      The previous operation with the same instance is not complete.
 * \retval         #OPTIGA_DEVICE_ERROR                     Command execution failure in OPTIGA and the LSB indicates the error code.
 *                                                          (Refer Solution Reference Manual)
 *
 * <b>Example</b><br>
 * example_optiga_crypt_ecdsa_sign.c
 *
 */
LIBRARY_EXPORTS optiga_lib_status_t optiga_crypt_ecdsa_sign(optiga_crypt_t * me,
                                                            const uint8_t * digest,
                                                            uint8_t digest_length,
                                                            optiga_key_id_t private_key,
                                                            uint8_t * signature,
                                                            uint16_t * signature_length);
#endif //OPTIGA_CRYPT_ECDSA_SIGN_ENABLED

#ifdef OPTIGA_CRYPT_ECDSA_VERIFY_ENABLED
/**
 * \brief Verifies the signature over the given digest.
 *
 * \details
 * Verifies the signature over a given digest provided with the input data.
 * - Invokes #optiga_cmd_verify_sign API, based on the input arguments.<br>
 * - Verifies the signature over the given provided with the input data using public key.
 * - It invokes the callback handler of the instance, when it is asynchronously completed.
 * - The callback registered with instance (#optiga_crypt_create) gets invoked, when the operation is asynchronously completed.
 *
 * \pre
 * - The application on OPTIGA must be opened using #optiga_util_open_application.<br>
 *
 * \note
 * - For <b>protected I2C communication</b>, Refer #OPTIGA_CRYPT_SET_COMMS_PROTECTION_LEVEL.
 * - Error codes from lower layers is returned as it is to the application.<br>
 *
 * \param[in]   me                                        Valid instance of #optiga_crypt_t created using #optiga_crypt_create.
 * \param[in]   digest                                    Pointer to a given digest buffer, must not be NULL.
 * \param[in]   digest_length                             Length of digest.
 * \param[in]   signature                                 Pointer to a given signature buffer, must not be NULL.
 * \param[in]   signature_length                          Length of signature.
 * \param[in]   public_key_source_type                    Public key from host / public key of certificate OID from OPTIGA. Value must be one of the below
 *                                                        - #OPTIGA_CRYPT_OID_DATA, if the public key is to used from the certificate data object from OPTIGA.
 *                                                        - #OPTIGA_CRYPT_HOST_DATA  or Non-Zero value , if the public key is provided by host.
 * \param[in]   public_key                                Public key from host / OID of certificate object. Value must be one of the below
 *                                                        - For certificate OID, pointer OID value must be passed.
 *                                                        - For Public key from host, pointer to #public_key_from_host_t instance.
 *
 * \retval      #OPTIGA_CRYPT_SUCCESS                     Successful invocation
 * \retval      #OPTIGA_CRYPT_ERROR_INVALID_INPUT         Wrong Input arguments provided
 * \retval      #OPTIGA_CRYPT_ERROR_INSTANCE_IN_USE       The previous operation with the same instance is not complete
 * \retval      #OPTIGA_DEVICE_ERROR                      Command execution failure in OPTIGA and the LSB indicates the error code.
 *                                                        (Refer Solution Reference Manual)
 *
 * <b>Example</b><br>
 * example_optiga_crypt_ecdsa_verify.c
 *
 */
LIBRARY_EXPORTS optiga_lib_status_t optiga_crypt_ecdsa_verify(optiga_crypt_t * me,
                                                              const uint8_t * digest,
                                                              uint8_t digest_length,
                                                              const uint8_t * signature,
                                                              uint16_t signature_length,
                                                              uint8_t public_key_source_type,
                                                              const void * public_key);
#endif //OPTIGA_CRYPT_ECDSA_VERIFY_ENABLED

/**
 * \brief Enables the protected I2C communication with OPTIGA for CRYPT instances
 *
 * \details
 * Enables the protected I2C communication with OPTIGA
 * - Sets the protection mode for the supplied instance.<br>
 * - Call this function before calling the service layer API which requires protection.
 * - The callback registered with instance (#optiga_crypt_create) gets invoked, when the operation is asynchronously completed.
 *
 * \pre
 * - #OPTIGA_COMMS_SHIELDED_CONNECTION macro must be defined.<br>
 * - #OPTIGA_CRYPT_SET_COMMS_PROTOCOL_VERSION function must be called once to set the required protocol version
 *   - Currently only the Pre-shared Secret based version is supported.
 * - The host and OPTIGA must be paired and Pre-Shared secret is available.<br>
 *
 * \note
 * - The protection mode for the instance is reset to #OPTIGA_COMMS_NO_PROTECTION once the service layer API returns synchronously.
 *
 * \param[in]      p_instance           Valid pointer to an instance
 * \param[in]      protection_level     Required protection mode
 *                                      - #OPTIGA_COMMS_NO_PROTECTION : Command and response is unprotected
 *                                      - #OPTIGA_COMMS_COMMAND_PROTECTION : Command is protected and response is unprotected
 *                                      - #OPTIGA_COMMS_RESPONSE_PROTECTION : Command is unprotected and response is protected
 *                                      - #OPTIGA_COMMS_FULL_PROTECTION : Both command and response is protected
 *                                      - To re-establish secure channel, bitwise-OR protection_level with #OPTIGA_COMMS_RE_ESTABLISH
 */
#ifdef OPTIGA_COMMS_SHIELDED_CONNECTION
#define OPTIGA_CRYPT_SET_COMMS_PROTECTION_LEVEL(p_instance, protection_level) \
{ \
    optiga_crypt_set_comms_params(p_instance, \
                                  OPTIGA_COMMS_PROTECTION_LEVEL, \
                                  protection_level);\
}
#else
#define OPTIGA_CRYPT_SET_COMMS_PROTECTION_LEVEL(p_instance, protection_level) {}
#endif

/**
 * \brief Select the protocol version required for the I2C protected communication for CRYPT instances
 *
 * \details
 * Select the protocol version required for the I2C protected communication
 * - Select the protocol version for the supplied instance.<br>
 *
 * \pre
 * - #OPTIGA_COMMS_SHIELDED_CONNECTION macro must be defined.<br>
 *
 * \note
 * - None
 *
 * \param[in]      p_instance    Valid pointer to an instance
 * \param[in]      version       Required protocol version
 *                               - #OPTIGA_COMMS_PROTOCOL_VERSION_PRE_SHARED_SECRET : Pre-shared Secret based protocol version
 */
#ifdef OPTIGA_COMMS_SHIELDED_CONNECTION
#define OPTIGA_CRYPT_SET_COMMS_PROTOCOL_VERSION(p_instance, version) \
{ \
    optiga_crypt_set_comms_params(p_instance, \
                                  OPTIGA_COMMS_PROTOCOL_VERSION, \
                                  version);\
}
#else
#define OPTIGA_CRYPT_SET_COMMS_PROTOCOL_VERSION(p_instance, version) {}
#endif

#ifdef __cplusplus
}
#endif

#endif /*_OPTIGA_CRYPT_H_*/

/**
* @}
*/

