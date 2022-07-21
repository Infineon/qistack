/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#ifndef _STACK_AUTH_H_
#define _STACK_AUTH_H_
#include "cy_qistack_common.h"
#include "cy_qistack_pm.h"

typedef enum
{
    INVALID = 0x0,
    GET_DIGEST = 0x09,
    GET_CERTIFICATE = 0x0A,
    CHALLENGE = 0x0B

} qi_authentication_request;

#define AUTH_MESS_TYPE_MASK                     0x0F
#define SUPPORTED_QI_AUTH_PROTOCOL_VERSION      (1u)
#define QI_TIMER_AUTH_I2C_WRITE_TIMEOUT         (2u)
#define QI_TIMER_AUTH_I2C_READ_TIMEOUT          (2u)
#define QI_TIMER_AUTH_OPTIGA_LONG_EXPIRY_TIMER  (65000u)

#define WPC_CERTIFICATE_CHAIN_LENGTH            (700)
#define WPC_CERTIFICATE_CHAIN_DIGEST_LENGTH     (34)
#define WPC_CHALLENGE_AUTH_LENGTH               (67)
#define AUTH_ERROR_DATA_LENGTH                  (3)
#define DIGEST_ERROR_DATA_LENGTH                (2)

#define INVALID_AUTHENTICATION_REQUEST          (1u)
#define UNSUPPORTED_AUTH_PROTOCOL               (2u)
#define UNSPECIFIED_AUTHENTICATION_ERROR        (4u)
#define CERT_STORE_SLOT_0                       (1u)
#define PTx_ADT_BUFFER_SIZE         (0x01) // The acctual buffer size = 16 * 2^n. here, we are specifying n =1
#define AUTHENTICATION_ENABLE       (0x01) // we are enabling Authentication enable.
#define PTx_ADT_BUFFER_SIZE_ALLOC   (32) // 16 * 2^PTx_ADT_BUFFER_SIZE

#define GET_AUTHICATION_QUERY_TIMEOUT       (50)
#define GET_DIGEST_LENGTH                   (2)
#define GET_CERTIFICATE_REQUEST_LENGTH      (4)
#define ADT_PTx_MAX_DATA_STREAM_MAX         (7)
#define AUTHENTICATION_PROTO_VERSION        (0x01)
#define AUTHENTICATION_PROTO_MASK           (0x10)
#define QI_PROTO_CERT_DIGEST_SLOT_0_MASK    (0x01)
#define QI_PROTO_CERT_STORE_SLOT_MASK       (0x03)
#define SIZEOF_CHALLENGE_NOUNCE             (18)

typedef struct __attribute__((__packed__))
{
    cy_stc_qi_context_t* qiCtx;
    void* callbackTimerContext;
} wicg_qi_authentication_context_param;

wicg_qi_authentication_context_param* wicg_qi_auth_params_get(void);
void Cy_QiStack_Authentication_Task_cbk(cy_timer_id_t id, void* ctx);
void Cy_QiStack_Authentication_Task(cy_stc_qi_context_t* qiCtx);
void Cy_QiStack_Authentication_Init(cy_stc_qi_context_t* qiCtx);
uint16_t populate_cert_chain_data();

/**
 * @brief
 *
 * @param qiCtx
 * @param error_code
 * @param error_data
 */
void Cy_QiStack_Transmit_Auth_Error(cy_stc_qi_context_t* qiCtx, uint8_t error_code, uint8_t error_data);
#endif // _STACK_AUTH_H_

/* [] END OF FILE */
