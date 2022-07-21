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
* \file optiga_cmd.h
*
* \brief   This file defines APIs, types and data structures used in the Command (cmd) module implementation.
*
* \ingroup  grOptigaCmd
*
* @{
*/

#ifndef _OPTIGA_CMD_H_
#define _OPTIGA_CMD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "optiga_lib_common.h"

/** \brief OPTIGA command instance structure type*/
typedef struct optiga_cmd optiga_cmd_t;

/** \brief OPTIGA comms instance structure type*/
typedef struct optiga_context optiga_context_t;

/**
 * \brief Creates an instance of #optiga_cmd_t.
 *
 * \details
 * Creates an instance of #optiga_cmd_t.
 * - Stores the callers context and callback handler.<br>
 * - Allocate memory for #optiga_cmd_t.<br>
 * - Assigns OPTIGA structure based on the optiga instance.<br>
 *
 * \pre
 * - None
 *
 * \note
 * - None
 *
 * \param[in] optiga_instance_id  Indicates the OPTIGA configuration to associate with instance.
 * \param[in] handler             Pointer to callback function, must not be NULL.
 * \param[in] caller_context      Pointer to upper layer context.
 *
 * \retval    #optiga_cmd_t *     On successful instance creation.
 * \retval    NULL                Memory allocation failure.
 *                                Already, OPTIGA_CMD_MAX_REGISTRATIONS number of instances is created.
 */
optiga_cmd_t * optiga_cmd_create(uint8_t optiga_instance_id,
                                 callback_handler_t handler,
                                 void * caller_context);

/**
 * \brief Destroys the instance of #optiga_cmd_t.
 *
 * \details
 * Destroys the instance of #optiga_cmd_t.
 * - Releases any OPTIGA cmd module lock utilized by the instance.<br>
 * - Releases any OPTIGA session acquired by the instance.<br>
 * - De-allocate the memory of the #optiga_cmd_t instance.<br>
 *
 * \pre
 * - None
 *
 * \note
 * - None
 *
 * \param[in] me                      Valid instance of #optiga_cmd_t created using #optiga_cmd_create.
 *
 * \retval    #OPTIGA_LIB_SUCCESS     Successful destruction of instance.
 */
optiga_lib_status_t optiga_cmd_destroy(optiga_cmd_t * me);


/**
 * \brief Releases the OPTIGA cmd lock.
 *
 * \details
 * Releases the OPTIGA cmd lock.
 * - Release the OPTIGA lock acquired by the instance.<br>
 * - If OPTIGA cmd lock request register in not empty, invoke the next registered caller handler with corresponding context.<br>
 *
 * \pre
 * - None
 *
 * \note
 * - None
 *
 * \param[in] me                      Valid instance of #optiga_cmd_t created using #optiga_cmd_create.
 *
 * \retval    #OPTIGA_CMD_SUCCESS     Successful release of the access layer lock.
 */
optiga_lib_status_t optiga_cmd_release_lock(const optiga_cmd_t * me);


/**
 * \brief Opens the OPTIGA Application
 *
 * \details
 * Opens the OPTIGA Application by issuing the OpenApplication command.
 * - Acquires the OPTIGA lock for #optiga_util_open_application.<br>
 * - Invokes #optiga_comms_open API to initialize OPTIGA and to establish the communication channel.<br>
 * - Forms the OpenApplication commands based on inputs.<br>
 * - Issues the OpenApplication command using #optiga_comms_transceive.<br>
 * - Releases the OPTIGA lock on successful completion of asynchronous operation.<br>
 *
 * \pre
 * - None
 *
 * \note
 * - This function must be mandatorily invoked before starting any interactions with OPTIGA after the reset.
 * - Error codes from lower layers will be returned as it is.<br>
 *
 * \param[in] me                                          Valid instance of #optiga_cmd_t created using #optiga_cmd_create.
 * \param[in] cmd_param                                   Param of Command APDU.
 *                                                        - Must be valid argument, otherwise OPTIGA returns an error.<br>
 * \param[in] params                                      Secure connection related information, must not be NULL.
 *
 * \retval    #OPTIGA_CMD_SUCCESS                         Successful invocation.
 * \retval    #OPTIGA_CMD_ERROR                           Error occurred before invoking OpenApplication command.
 *                                                        Error in the asynchronous state machine.
 * \retval    #OPTIGA_CMD_ERROR_MEMORY_INSUFFICIENT       APDU length formed is greater than <b>OPTIGA_MAX_COMMS_BUFFER_SIZE</b>.
 */
optiga_lib_status_t optiga_cmd_open_application(optiga_cmd_t * me,
                                                uint8_t cmd_param,
                                                void * params);

/**
 * \brief Closes the OPTIGA Application
 *
 * \details
 * Closes the OPTIGA Application by issuing the CloseApplication command.
 * - Acquires the OPTIGA lock for #optiga_util_close_application.<br>
 * - Forms the CloseApplication commands based on inputs.<br>
 * - Issues the CloseApplication command through #optiga_comms_transceive.<br>
 * - Releases the OPTIGA lock on successful completion of asynchronous operation.<br>
 *
 * \pre
 * - Application on OPTIGA must be opened using #optiga_cmd_open_application before using this API.<br>
 *
 * \note
 * - This function must be mandatorily invoked before issuing a reset to OPTIGA, in case the context needs to be saved.
 * - Error codes from lower layers will be returned as it is.<br>
 *
 * \param[in] me                                          Valid instance of #optiga_cmd_t created using #optiga_cmd_create.
 * \param[in] cmd_param                                   Param of Command APDU.
 *                                                        - Must be valid argument, otherwise OPTIGA returns an error.<br>
 * \param[in] params                                      Secure connection related information, must not be NULL.
 *
 * \retval    #OPTIGA_CMD_SUCCESS                         Successful invocation.
 * \retval    #OPTIGA_CMD_ERROR                           Error occurred before invoking CloseApplication command.
 *                                                        Error in the asynchronous state machine.
 * \retval    #OPTIGA_CMD_ERROR_MEMORY_INSUFFICIENT       APDU length formed is greater than <b>OPTIGA_MAX_COMMS_BUFFER_SIZE</b>.
 */
optiga_lib_status_t optiga_cmd_close_application(optiga_cmd_t * me,
                                                 uint8_t cmd_param,
                                                 void * params);

/**
 * \brief Reads data or metadata of the specified data object
 *
 * \details
 * Reads data or metadata of the specified data object, by issuing the GetDataObject command, based on input parameters.
 * - Acquires the OPTIGA lock for #optiga_util_read_data/#optiga_util_read_metadata.<br>
 * - Forms the ReadData/ReadMetaData commands based on inputs.<br>
 * - Issues the ReadData/ReadMetaData command through #optiga_comms_transceive.<br>
 * - In case the data to be read by the user is greater than the <b>OPTIGA_MAX_COMMS_BUFFER_SIZE</b>,
 *   the data is retrieved by internal chaining (by calling GetDataObject command multiple times).
 * - Releases the OPTIGA lock on successful completion of asynchronous operation.<br>
 *
 * \pre
 * - Application on OPTIGA must be opened using #optiga_cmd_open_application before using this API.<br>
 *
 * \note
 * - Error codes from lower layers will be returned as it is.<br>
 *
 *\param[in]  me                                          Valid instance of #optiga_cmd_t created using #optiga_cmd_create.
 *\param[in]  cmd_param                                   Param of Get Data Command APDU.
 *                                                        - Must be valid argument, otherwise OPTIGA returns an error.<br>
 *\param[in]  params                                      InData of Get Data Command APDU, must not be NULL.
 *
 * \retval    #OPTIGA_CMD_SUCCESS                         Successful invocation.
 * \retval    #OPTIGA_CMD_ERROR                           Error occurred before invoking GetDataObject command.
 *                                                        Error in the asynchronous state machine.
 * \retval    #OPTIGA_CMD_ERROR_MEMORY_INSUFFICIENT       Error due to insufficient buffer size.
 *                                                        - APDU length formed is greater than <b>OPTIGA_MAX_COMMS_BUFFER_SIZE</b>.
 *                                                        - Data received from OPTIGA is greater than the buffer size provided by user.
 */
optiga_lib_status_t optiga_cmd_get_data_object(optiga_cmd_t * me,
                                               uint8_t cmd_param,
                                               optiga_get_data_object_params_t * params);

/**
 * \brief Writes data or metadata to the specified data object
 *
 * \details
 * Writes data or metadata to the specified data object, by issuing the SetDataObject command, based on input parameters.
 * - Acquires the OPTIGA lock for #optiga_util_write_data/#optiga_util_write_metadata.<br>
 * - Forms the SetData/SetMetaData commands based on inputs.<br>
 * - Issues the SetData/SetMetaData command through #optiga_comms_transceive.<br>
 * - In case the data to be written by the user is greater than the <b>OPTIGA_MAX_COMMS_BUFFER_SIZE</b>,
 *   the data is written to the OPTIGA by internal chaining (by calling SetDataObject command multiple times).<br>
 * - Releases the OPTIGA lock on successful completion of asynchronous operation.<br>
 *
 * \pre
 * - Application on OPTIGA must be opened using #optiga_cmd_open_application before using this API.<br>
 *
 * \note
 * - In case of failure, it is possible that partial data is written into the data object.<br>
 *   In such a case, the user should decide if the data has to be re-written.
 * - Error codes from lower layers will be returned as it is.<br>
 *
 *\param[in]  me                                          Valid instance of #optiga_cmd_t created using #optiga_cmd_create.
 *\param[in]  cmd_param                                   Param of Set Data Command APDU.
 *                                                        - Must be valid argument, otherwise OPTIGA returns an error.<br>
 *\param[in]  params                                      InData of Set Data Command APDU, must not be NULL.
 *
 * \retval    #OPTIGA_CMD_SUCCESS                         Successful invocation.
 * \retval    #OPTIGA_CMD_ERROR                           Error occurred before invoking SetDataObject command.
 *                                                        Error in the asynchronous state machine.
 * \retval    #OPTIGA_CMD_ERROR_MEMORY_INSUFFICIENT       APDU length formed is greater than <b>OPTIGA_MAX_COMMS_BUFFER_SIZE</b>.
 */
optiga_lib_status_t optiga_cmd_set_data_object(optiga_cmd_t * me,
                                               uint8_t cmd_param,
                                               optiga_set_data_object_params_t * params);

#ifdef OPTIGA_CRYPT_RANDOM_ENABLED
/**
 * \brief Generates random data.
 *
 * \details
 * Generates random data, by issuing the GetRandom command to OPTIGA.
 * - Acquires the OPTIGA session/lock for #optiga_crypt_random.<br>
 * - Forms the GetRandom command based on inputs.<br>
 * - Issues the GetRandom command through #optiga_comms_transceive.<br>
 * - Releases the OPTIGA lock on successful completion of asynchronous operation.<br>
 *
 * \pre
 * - Application on OPTIGA must be opened using #optiga_cmd_open_application before using this API.<br>
 *
 * \note
 * - Error codes from lower layers will be returned as it is.<br>
 *
 *\param[in] me                                           Valid instance of #optiga_cmd_t created using #optiga_cmd_create.
 *\param[in] cmd_param                                    Param of Get Random Command APDU.
 *                                                        - Must be valid argument, otherwise OPTIGA returns an error.<br>
 *\param[in] params                                       InData of Get Random Command APDU, must not be NULL.
 *
 * \retval   #OPTIGA_CMD_SUCCESS                          Successful invocation.
 * \retval   #OPTIGA_CMD_ERROR                            Error occurred before invoking GetRandom command.
 *                                                        Error in the asynchronous state machine.
 * \retval   #OPTIGA_CMD_ERROR_MEMORY_INSUFFICIENT        APDU length formed is greater than <b>OPTIGA_MAX_COMMS_BUFFER_SIZE</b>.
 */
optiga_lib_status_t optiga_cmd_get_random(optiga_cmd_t * me,
                                          uint8_t cmd_param,
                                          optiga_get_random_params_t * params);
#endif //OPTIGA_CRYPT_RANDOM_ENABLED

#ifdef OPTIGA_CRYPT_HASH_ENABLED
/**
 * \brief Generates hash on external data or data in OID.
 *
 * \details
 * Generates hash on external data or data in OID by issuing Calc Hash command to OPTIGA.
 * - Acquires the OPTIGA lock for #optiga_crypt_hash_start/#optiga_crypt_hash_update/#optiga_crypt_hash_finalize.<br>
 * - Forms the CalcHash command based on inputs.<br>
 * - Issues the CalcHash command through #optiga_comms_transceive.<br>
 * - Releases the OPTIGA lock on successful completion of asynchronous operation.<br>
 *
 * \pre
 * - Application on OPTIGA must be opened using #optiga_cmd_open_application before using this API.
 *
 * \note
 * - Error codes from lower layers will be returned as it is.
 *
 *\param[in] me                                           Valid instance of #optiga_cmd_t created using #optiga_cmd_create.
 *\param[in] cmd_param                                    Param of CalcHash Command APDU.
 *                                                        - Must be valid argument, otherwise OPTIGA returns an error.<br>
 *\param[in] params                                       InData of CalcHash Command APDU, must not be NULL.
 *
 * \retval   #OPTIGA_CMD_SUCCESS                          Successful invocation.
 * \retval   #OPTIGA_CMD_ERROR                            Error occurred before invoking CalcHash command.<br>
 *                                                        Error in the asynchronous state machine.
 * \retval   #OPTIGA_CMD_ERROR_MEMORY_INSUFFICIENT        Error due to insufficient buffer size.
 *                                                        - APDU length formed is greater than <b>OPTIGA_MAX_COMMS_BUFFER_SIZE</b>.
 *                                                        - Data received from OPTIGA is greater than the buffer size provided by user.
 */
optiga_lib_status_t optiga_cmd_calc_hash(optiga_cmd_t * me,
                                         uint8_t cmd_param,
                                         optiga_calc_hash_params_t * params);
#endif //OPTIGA_CRYPT_HASH_ENABLED

#ifdef OPTIGA_CRYPT_ECDSA_SIGN_ENABLED
/**
 * \brief Calculate signature on digest.
 *
 * \details
 * Calculate signature on digest by issuing Calc Sign command to OPTIGA.
 * - Acquires the OPTIGA session/lock for #optiga_crypt_ecdsa_sign.<br>
 * - Forms the Generate KeyPair command based on inputs.<br>
 * - Issues the Generate KeyPair command through #optiga_comms_transceive.
 * - Releases the OPTIGA lock on successful completion of asynchronous operation.<br>
 *
 * \pre
 * - Application on OPTIGA must be opened using #optiga_cmd_open_application before using this API.
 *
 * \note
 * - Error codes from lower layers will be returned as it is.<br>
 *
 *\param[in]  me                                      Valid instance of #optiga_cmd_t created using #optiga_cmd_create.
 *\param[in]  cmd_param                               Param of Calc Sign Command APDU.
 *                                                    - Must be valid argument, otherwise OPTIGA returns an error.<br>
 *\param[in]  params                                  InData of Calc Sign Command APDU, must not be NULL.
 *
 * \retval    #OPTIGA_CMD_SUCCESS                     Successful invocation.
 * \retval    #OPTIGA_CMD_ERROR                       Error occurred before invoking Calc Sign command.<br>
 *                                                    Error in the asynchronous state machine.
 * \retval    #OPTIGA_CMD_ERROR_INVALID_INPUT         Instance invoked for session oid, without acquiring the session (from #optiga_cmd_gen_keypair).
 * \retval    #OPTIGA_CMD_ERROR_MEMORY_INSUFFICIENT   Error due to insufficient buffer size.
 *                                                    - APDU length formed is greater than <b>OPTIGA_MAX_COMMS_BUFFER_SIZE</b>.
 *                                                    - Length of the buffer to copy the signature is less than actual length of signature.
 */
optiga_lib_status_t optiga_cmd_calc_sign(optiga_cmd_t * me,
                                         uint8_t cmd_param,
                                         optiga_calc_sign_params_t * params);
#endif //OPTIGA_CRYPT_ECDSA_SIGN_ENABLED 

#ifdef OPTIGA_CRYPT_ECDSA_VERIFY_ENABLED
/**
 * \brief Verifies the signature over the given digest.
 *
 * \details
 * Verifies the signature over the given digest by issuing VerifySign command.
 * - Acquires the OPTIGA lock for #optiga_crypt_ecdsa_verify.<br>
 * - Forms the VerifySign command based on inputs and invokes the optiga_comms_transceive to send the same to OPTIGA.
 * - Releases the OPTIGA lock on successful completion of asynchronous operation.<br>
 *
 * \pre
 * - Application on OPTIGA must be opened using #optiga_cmd_open_application before using this API.<br>
 *
 * \note
 * - Error codes from lower layers will be returned as it is.<br>
 *
 *\param[in]  me                                          Valid instance of #optiga_cmd_t created using #optiga_cmd_create.
 *\param[in]  cmd_param                                   Param of VerifySign Command APDU.
 *                                                        - Must be valid argument, otherwise OPTIGA returns an error.<br>
 *\param[in]  params                                      Parameters for InData of VerifySign Command APDU, must not be NULL.
 *
 * \retval    #OPTIGA_CMD_SUCCESS                         Successful invocation.
 * \retval    #OPTIGA_CMD_ERROR                           Error occurred before invoking VerifySign command.<br>
 *                                                        Error in the asynchronous state machine.
 * \retval   #OPTIGA_CMD_ERROR_MEMORY_INSUFFICIENT        APDU length formed is greater than <b>OPTIGA_MAX_COMMS_BUFFER_SIZE</b>.
 */
optiga_lib_status_t optiga_cmd_verify_sign(optiga_cmd_t * me,
                                           uint8_t cmd_param,
                                           optiga_verify_sign_params_t * params);
#endif //OPTIGA_CRYPT_ECDSA_VERIFY_ENABLED

#ifdef OPTIGA_CRYPT_ECC_GENERATE_KEYPAIR_ENABLED
/**
 * \brief Generates ECC key-pair.
 *
 * \details
 * Generate ECC key-pair by issuing Generate KeyPair command to OPTIGA.
 * - Acquires the OPTIGA session/lock for #optiga_crypt_ecc_generate_keypair.<br>
 * - Forms the Generate KeyPair command based on inputs.
 * - Issues the Generate KeyPair command through #optiga_comms_transceive.
 * - Releases the OPTIGA lock on successful completion of asynchronous operation.<br>
 *
 * \pre
 * - Application on OPTIGA must be opened using #optiga_cmd_open_application before using this API.
 *
 * \note
 * - Error codes from lower layers will be returned as it is.
 *
 *\param[in]  me                                      Valid instance of #optiga_cmd_t created using #optiga_cmd_create.
 *\param[in]  cmd_param                               Param of Generate KeyPair Command APDU.
 *                                                    - Must be valid argument, otherwise OPTIGA returns an error.
 *\param[in]  params                                  InData of Generate KeyPair Command APDU, must not be NULL.
 *
 * \retval    #OPTIGA_LIB_SUCCESS                     Successful invocation.
 * \retval    #OPTIGA_CMD_ERROR                       Error occurred before invoking Generate KeyPair command.<br>
 *                                                    Error in the asynchronous state machine.
 * \retval    #OPTIGA_CMD_ERROR_MEMORY_INSUFFICIENT   Error due to insufficient buffer size.
 *                                                    - APDU length formed is greater than <b>OPTIGA_MAX_COMMS_BUFFER_SIZE</b>.
 *                                                    - Length of the buffer to copy the key is less than actual length of key.
 */
optiga_lib_status_t optiga_cmd_gen_keypair(optiga_cmd_t * me,
                                           uint8_t cmd_param,
                                           optiga_gen_keypair_params_t * params);
#endif //(OPTIGA_CRYPT_ECC_GENERATE_KEYPAIR_ENABLED)

/**
 * \brief Writes protected object fragments to OPTIGA.
 *
 * \details
 * Writes manifest or data fragement(s) to the specified data object, by issuing the SetObjectProtected command, in a securely.
 * - Acquires the strict sequence for #optiga_util_protected_update_start.<br>
 * - Forms the SetObjectProtected commands based on inputs.<br>
 * - Issues the SetObjectProtected command through #optiga_comms_transceive.<br>
 * - Releases the strict sequence in case of an error or after #optiga_util_protected_update_final is successfully completed.
 *
 * \pre
 * - Application on OPTIGA must be opened using #optiga_cmd_open_application before using this API.<br>
 *
 * \note
 * - Error codes from lower layers will be returned as it is.<br>
 *
 *\param[in]  me                                          Valid instance of #optiga_cmd_t created using #optiga_cmd_create.
 *\param[in]  cmd_param                                   Param of Set Object Protected APDU.
 *                                                        - Must be valid argument, otherwise OPTIGA returns an error.<br>
 *\param[in]  params                                      InData of Set Object Protected APDU, must not be NULL.
 *
 * \retval    #OPTIGA_CMD_SUCCESS                         Successful invocation.
 * \retval    #OPTIGA_CMD_ERROR                           Error occurred before invoking SetObjectProtected command.
 *                                                        Error in the asynchronous state machine.
 * \retval    #OPTIGA_CMD_ERROR_MEMORY_INSUFFICIENT       APDU length formed is greater than <b>OPTIGA_MAX_COMMS_BUFFER_SIZE</b>.
 * \retval    #OPTIGA_CMD_ERROR_INVALID_INPUT             Continue and final APDU command invoked without strict lock acquired for the instance.
 */
optiga_lib_status_t optiga_cmd_set_object_protected(optiga_cmd_t * me,
                                                    uint8_t cmd_param,
                                                    optiga_set_object_protected_params_t * params);
                                                    



#ifdef __cplusplus
}
#endif

#endif /*_OPTIGA_CMD_H_ */

/**
* @}
*/
