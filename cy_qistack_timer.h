/***************************************************************************//**
* \file cy_qistack_timer.h
* \version 2.0
*
* Provides Software Timer Header File of the QiStack middleware.
*
*
********************************************************************************
* \copyright
* Copyright 2022-2023, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_QISTACK_TIMER_H
#define CY_QISTACK_TIMER_H

#include "cy_pdutils_sw_timer.h"

/*******************************************************************************
*                              Type Definitions
*******************************************************************************/

/**
* \addtogroup group_qistack_timer_id_macros
* \{
*/

/** 
 * Qi timers offset in software timer stack.
 * This 256 ID boundary should not be used by any other system module.
 */
#define CY_QI_TIMER_ID_OFFSET   CY_PDUTILS_TIMER_WLC_START_ID

/**
 * Timer ID allocation
 * Ping timers <0 : 30>
 * Configuration and negotiation timers <31 : 60>
 * Power transfer timers <61 : 100>
 */

/** Ping timers */

#define CY_QI_TIMER_PING_START_ID                           ((CY_QI_TIMER_ID_OFFSET) + (0u))
#define CY_QI_TIMER_PING_END_ID                             ((CY_QI_TIMER_ID_OFFSET) + (30u))

/** Timer ID for Qi start delay. */
#define CY_QI_TIMER_DELAY_START_ID                          ((CY_QI_TIMER_ID_OFFSET) + (0u))

/** Timer ID for Analog ping interval. */
#define CY_QI_TIMER_ANA_PING_INTERVAL_ID                    ((CY_QI_TIMER_ID_OFFSET) + (1u))

/** Timer ID for Digital ping interval. */
#define CY_QI_TIMER_DIG_PING_INTERVAL_ID                    ((CY_QI_TIMER_ID_OFFSET) + (2u))

/** Timer ID for Digital ping timeout. */
#define CY_QI_TIMER_DIG_PING_TIME_ID                        ((CY_QI_TIMER_ID_OFFSET) + (3u))

/** Timer ID for Digital ping wake up timer. */
#define CY_QI_TIMER_DIG_PING_WAKE_TIME_ID                   ((CY_QI_TIMER_ID_OFFSET) + (4u))

/** Timer ID for Digital ping ASK path Config timer. */
#define CY_QI_TIMER_DIG_PING_ASK_PATH_TIME_ID               ((CY_QI_TIMER_ID_OFFSET) + (5u))

/** Configuration and negotiation timers */

#define CY_QI_TIMER_CFG_START_ID                            ((CY_QI_TIMER_ID_OFFSET) + (31u))
#define CY_QI_TIMER_CFG_END_ID                              ((CY_QI_TIMER_ID_OFFSET) + (60u))

/** Timer ID for FSK response time. */
#define CY_QI_TIMER_FSK_RESP_TIME_ID                        ((CY_QI_TIMER_ID_OFFSET) + (31u))

/** Timer ID for Configuration Tnext time */
#define CY_QI_T_NEXT_TIME_ID                                ((CY_QI_TIMER_ID_OFFSET) + (32u))

/** Timer ID for FOD EPT delay time */
#define CY_QI_FOD_EPT_TIME_ID                               ((CY_QI_TIMER_ID_OFFSET) + (33u))

/** Timer ID for Negotiation Tnegotiate time */
#define CY_QI_T_NEG_TIME_ID                                 ((CY_QI_TIMER_ID_OFFSET) + (34u))

/** Timer ID for Negotiation Tnegotiate time */
#define CY_HIPP_NEG_TIME_ID                                 ((CY_QI_TIMER_ID_OFFSET) + (35u))

/** Power Transfer timers */

#define CY_QI_TIMER_PWR_START_ID                            ((CY_QI_TIMER_ID_OFFSET) + (61u))
#define CY_QI_TIMER_PWR_END_ID                              ((CY_QI_TIMER_ID_OFFSET) + (90u))

/** Timer ID for Rx active timeout without ASK packet. */
#define CY_QI_TIMER_RX_ACTIVE_TIME_ID                       ((CY_QI_TIMER_ID_OFFSET) + (61u))

/** Timer ID for PID loop time. */
#define CY_QI_TIMER_PID_LOOP_TIME_ID                        ((CY_QI_TIMER_ID_OFFSET) + (62u))

/** Timer ID for Power Control Hold off time. */
#define CY_QI_TIMER_PCH_TIME_ID                             ((CY_QI_TIMER_ID_OFFSET) + (63u))

/** Timer ID for Sampling task */
#define CY_QI_TIMER_SAMPLING_TASK_ID                        ((CY_QI_TIMER_ID_OFFSET) + (64u))

/** Timer ID for CEP packet timeout as per spec */
#define CY_QI_TIMER_T_TIMER_TIME_ID                         ((CY_QI_TIMER_ID_OFFSET) + (65u))

/** Timer ID for RPP packet timeout */
#define CY_QI_TIMER_T_POWER_TIME_ID                         ((CY_QI_TIMER_ID_OFFSET) + (66u))

/** Timer ID for CEP packet timeout for ASK path switch */
#define CY_QI_TIMER_PKT_TIMEOUT_TIME_ID                     ((CY_QI_TIMER_ID_OFFSET) + (67u))

/** Timer ID for receiving an ASK packet and passing it to ASK Event handler */
#define CY_QI_ASK_PKT_RECEPTION_TIME_ID                     ((CY_QI_TIMER_ID_OFFSET) + (68u))

/** Timer ID for staggered Duty Frequency Control During PID  */
#define CY_QI_STAGGER_Df_TIME_ID                           ((CY_QI_TIMER_ID_OFFSET) + (69u))

#define CY_QI_SAMSUNG_FSK_ACK_RETRY_TIME_ID                ((CY_QI_TIMER_ID_OFFSET) + (70u))

/** Solution layer timers */

#define CY_SOLN_TIMER_ID_OFFSET     CY_PDUTILS_TIMER_USER_START_ID

/** Timer ID for LED task. Keep outside Qi timer IDs */
#define CY_SOLN_TIMER_0_TIME_ID                             (CY_SOLN_TIMER_ID_OFFSET)

/** Timer ID 1 */
#define CY_SOLN_TIMER_1_TIME_ID                             ((CY_SOLN_TIMER_ID_OFFSET) + (1u))

/** Timer ID 2 */
#define CY_SOLN_TIMER_2_TIME_ID                             ((CY_SOLN_TIMER_ID_OFFSET) + (2u))

/** Timer ID 3 */
#define CY_SOLN_TIMER_3_TIME_ID                             ((CY_SOLN_TIMER_ID_OFFSET) + (3u))

/** Timer ID 4 */
#define CY_SOLN_TIMER_4_TIME_ID                             ((CY_SOLN_TIMER_ID_OFFSET) + (4u))

/** Timer ID 5 */
#define CY_SOLN_TIMER_5_TIME_ID                             ((CY_SOLN_TIMER_ID_OFFSET) + (5u))

/** Timer ID for Authentication Optiga Stack. */
#define CY_QI_TIMER_PKT_AUTH_TIMEOUT_TIME_ID                 ((CY_SOLN_TIMER_ID_OFFSET) + (6u))

/** Timer ID for Authentication Optiga Stack. */
#define CY_QI_TIMER_AUTH_STACK_TASK                           ((CY_SOLN_TIMER_ID_OFFSET) + (7u))

/** Timer ID for Authentication Optiga Stack. */
#define CY_QI_TIMER_AUTH_STACK_LONG_TIMER                     ((CY_SOLN_TIMER_ID_OFFSET) + (8u))

/** Timer ID 9 */
#define CY_SOLN_TIMER_9_TIME_ID                              ((CY_SOLN_TIMER_ID_OFFSET) + (9u))

/** Timer ID 10 */
#define CY_SOLN_TIMER_10_TIME_ID                             ((CY_SOLN_TIMER_ID_OFFSET) + (10u))

/** Timer ID 11 */
#define CY_SOLN_TIMER_11_TIME_ID                             ((CY_SOLN_TIMER_ID_OFFSET) + (11u))

/** Timer ID 12 */
#define CY_SOLN_TIMER_12_TIME_ID                             ((CY_SOLN_TIMER_ID_OFFSET) + (12u))

/** Timer ID 13 */
#define CY_SOLN_TIMER_13_TIME_ID                             ((CY_SOLN_TIMER_ID_OFFSET) + (13u))

/** \} group_qistack_timer_id_macros */

/**
* \addtogroup group_qistack_timer_value_macros
* \{
*/

/** Qi start delay timeout for power up in mS. */
#define CY_QI_TIMER_DELAY_START_TIME                        (2000u)

/** Qi start delay timeout for reset in mS. */
#define CY_QI_TIMER_DELAY_RESET_TIME                        (10u)

/** Digital ping interval in mS, for obj detection */
#define CY_QI_TIMER_DIG_PING_W_OBJ_INTERVAL                 (1000u)

/** Digital ping try timeout in mS. */
#define CY_QI_TIMER_DIG_PING_TIME                           (70u)

/** Digital ping extend timeout in mS. */
#define CY_QI_TIMER_DIG_PING_EXT_TIME                       (20u)

/** Digital ping wake up time in mS. */
#define CY_QI_TIMER_DIG_PING_WAKE_TIME                      (20u)

/** Digital ping ASK path Config time in mS. */
#define CY_QI_TIMER_DIG_PING_ASK_PATH_TIME                  (5u)

/** PRx active timeout without ASK packet in mS. */
#define CY_QI_TIMER_RX_ACTIVE_TIME                          (2000u) 

/** Power Control Hold off time in mS. */
#define CY_QI_TIMER_PCH_TIME                                (5u)

/** FSK min response time in mS. */
#define CY_QI_TIMER_FSK_RESP_TIME                           (3u)

/** FSK max response time in mS. */
#define CY_QI_TIMER_FSK_RESP_MAX_TIME                       (10u)

/** Sampling task time in mS. */
#define CY_QI_TIMER_SAMPLE_TASK_TIME                        (4u)

/** Sampling task delayed time in mS. */
#define CY_QI_TIMER_SAMPLE_TASK_DELAYED_TIME                (10u)

/** Configuration Tnext time in mS */
#define CY_QI_T_NEXT_TIME                                   (22u)

/** Maximum time between start of ASK packet to processing the packet */
#define CY_QI_ASK_PKT_RECEPTION_TIME                        (300u)

/** 
 * Packet timeout for ASK path switch in mS. This number ensures that
 * we switch ASK decode mode if no packet was received within this timeout.
 * Since there is a possibility of a wrong switch, we need to ensure that
 * we come back to original mode within CEP packet timeout and be able to
 * receive a packet. To allow for this, we use 1800ms / 4 = 450ms.
 */
#define CY_QI_TIMER_PKT_TIMEOUT_TIME                        (450u)

/** FOD EPT delay time in mS */
#define CY_QI_FOD_EPT_TIME                                  (2u)

/** Negotiation Tnegotiate time in mS */
#define CY_QI_T_NEG_TIME                                    (500u)  

/** HiPP negotiation time in mS */
#define CY_HIPP_NEG_TIME                                    (4000u)

/** Timer for staggered Duty Frequency Control During PID in mS*/
#define CY_QI_STAGGER_Df_TIME                              (3u)

/** Timer for Retrying the FSK ACK Transaction if Samsung ASK Not received */
#define CY_QI_SAMSUNG_FSK_ACK_RETRY_TIME                    (200u)

/** \} group_qistack_timer_value_macros */

#endif /* CY_QISTACK_TIMER_H */

/* [] END OF FILE */
