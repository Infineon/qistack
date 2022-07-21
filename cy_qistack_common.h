/***************************************************************************//**
* \file cy_qistack_common.h
* \version 1.0
*
* Provides Common Header File of the QiStack middleware.
*
*
********************************************************************************
* \copyright
* Copyright 2021-2022, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_QISTACK_COMMON_H
#define CY_QISTACK_COMMON_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "cy_qistack_timer.h"
#include "cy_qistack_utils.h"
#include "cy_usbpd_defines.h"
#include "cy_usbpd_common.h"

/**
********************************************************************************
* \mainpage QiStack Middleware Library
*
* The QiStack middleware implements state machines defined in the **Wireless 
* Power Consortium Qi Specification**. 
* The middleware provides a set of Qi Policy Manager (QPM) APIs through which 
* the application can initialize, monitor and configure the middleware operation.
*
* The QiStack middleware operates on the top of the peripheral drivers included in
* the MTB PDL CAT2(mtb-pdl-cat2) Peripheral Driver Library
*
* <b>Features:</b>
* 1. Support Type-C port configuration and connection detection in the Sink Role
* 2. Support USBPD Communication with the following features:
*    * USB PD revision 3.0 compliance
*    * USB PD revision 2.0 compliance (backward compatibility)
*    * Power contract negotiation in Sink Role
*    * Ability to respond to SOP and SOP' messages to support designs with a
*    Captive USB-C cable.
* 3. Support configuration of the port roles and responses through the EZ-PD
* Configurator.
* 4. Support Device Policy Manager APIs to initialize, configure, monitor and
* control the port operation; as well as to send/receive USBPD messages
* associated with Alternate Mode discovery, Authentication, Firmware update
* etc.
*
********************************************************************************
* \section section_qistack_general_description General Description
********************************************************************************
*
* Include cy_qistack_common.h, cy_qistack_qpm.h, cy_qistack_config.h to
* get access to all functions and other declarations in this library. See the
* \ref section_qistack_quick_start to start using the QiStack.
*
* Refer to the \ref section_qistack_toolchain section for compatibility
* information.
*
********************************************************************************
* \section section_qistack_quick_start Quick Start Guide
********************************************************************************
*
* QiStack middleware can be used in various Development
* Environments such as ModusToolbox, MBED, etc. Refer to the
* \ref section_qistack_toolchain section.
*
* The below steps describe the simplest way of enabling the QiStack
* middleware in the application.
*
********************************************************************************
* \section section_qistack_configuration_considerations Configuration Considerations
********************************************************************************
*
* This section consists of instructions of how to configure, and use
* the QiStack Middleware in a design.
*
* Refer to the \ref section_qistack_miscellaneous for the existing
* restrictions.
*
********************************************************************************
* \section section_qistack_miscellaneous Limitations and Restrictions
********************************************************************************
*
********************************************************************************
* \section section_qistack_toolchain Supported Software and Tools
********************************************************************************
*
* This version of the QiStack Middleware was validated for the compatibility
* with the following software and tools:
*
* <table class="doxtable">
*   <tr>
*     <th>Software and Tools</th>
*     <th>Version</th>
*   </tr>
*   <tr>
*     <td>ModusToolbox Software Environment</td>
*     <td>2.3</td>
*   </tr>
*   <tr>
*     <td>mtb-pdl-cat2</td>
*     <td>1.1.0</td>
*   </tr>
*   <tr>
*     <td>GCC Compiler</td>
*     <td>9.3.1</td>
*   </tr>
*   <tr>
*     <td>IAR Compiler</td>
*     <td>8.42.2</td>
*   </tr>
*   <tr>
*     <td>Arm Compiler 6</td>
*     <td>6.13</td>
*   </tr>
* </table>
*
********************************************************************************
* \section section_qistack_changelog Changelog
********************************************************************************
*
* <table class="doxtable">
*   <tr>
*     <td>1.0</td>
*     <td>Initial Version</td>
*     <td></td>
*   </tr>
* </table>
*
********************************************************************************
* \section section_qistack_more_information More Information
********************************************************************************
*
* For more information, refer to the following documents:
*
* * <a href="https://www.cypress.com/products/modustoolbox-software-environment">
*      <b>ModusToolbox Software Environment, Quick Start Guide, Documentation,
*         and Videos</b>
*   </a>
*
* \note
* The links to the other software component's documentation (middleware and PDL)
* point to GitHub to the latest available version of the software.
* To get documentation of the specified version, download from GitHub and unzip
* the component archive. The documentation is available in
* the <i>docs</i> folder.
*
********************************************************************************
*
* \defgroup group_qistack_macros Macros
* \brief
* This section describes the QiStack Macros.
*
* \defgroup group_qistack_functions Functions
* \brief
* This section describes the QiStack Function Prototypes.
*
* \defgroup group_qistack_data_structures Data Structures
* \brief
* This section describes the data structures defined by the QiStack.
*
* \defgroup group_qistack_enums Enumerated Types
* \brief
* This section describes the enumeration types defined by the QiStack.
*
*/

/*******************************************************************************
*                              Type Definitions
*******************************************************************************/

/* Provide default values for feature selection macros where not already defined. */
#ifndef CY_QI_SYS_CLK_FREQ_KHZ
#define CY_QI_SYS_CLK_FREQ_KHZ                  (48000u)
#endif /* CY_QI_SYS_CLK_FREQ_KHZ */

#ifndef CY_QI_EPP_MODE_EN
#define CY_QI_EPP_MODE_EN                       (1u)
#endif /* CY_QI_EPP_MODE_EN */

#define CY_QI_AUTOMATION_DEBUG_EN               (1u)

/**
 * Status LED blink count.
 */
#define CY_QI_LED_BLINK_COUNT_POWER_ON          (10u)

/**
* \addtogroup group_qistack_macros
* \{
*/

/** Qi protocol IDLE/WAIT phase/state/sub-state */
#define CY_QI_ST_WAIT                               (0u)

/** FSK depth 0 with 48MHz PWM clock (Each cycle = 21nS). */
#define CY_QI_FSK_RESOLUTION_DEPTH_0                (2u)
/** FSK depth 1 with 48MHz PWM clock (Each cycle = 21nS). */
#define CY_QI_FSK_RESOLUTION_DEPTH_1                (4u)
/** FSK depth 2 with 48MHz PWM clock (Each cycle = 21nS). */
#define CY_QI_FSK_RESOLUTION_DEPTH_2                (7u)
/** FSK depth 3 with 48MHz PWM clock (Each cycle = 21nS). */
#define CY_QI_FSK_RESOLUTION_DEPTH_3                (13u)

/** FSK critical section counter buffer size */
#define CY_QI_FSK_EDGE_COUNTER_BUF                  (1000u)

/** ASK message header ID: 8-bit Power packet scaling factor  */
#define CY_QI_PWR_CAL_FACTOR_8_BIT                  (128u)
/** ASK message header ID: 24-bit Power packet scaling factor  */
#define CY_QI_PWR_CAL_FACTOR_24_BIT                 (32768u)

/** Minimum T_WINDOW for RPP sampling */
#define CY_QI_MIN_T_WINDOW                          (2u)

/** Minimum T_OFFSET for RPP sampling */
#define CY_QI_MIN_T_OFFSET                          (2u)

#define CY_QI_PCHO_TIMER_THRESHOLD_PER              (10u)

/** Maximum number of ASK paths */
#define CY_QI_MAX_NO_OF_ASK_SWITCH_OVER             (3u)

#define CY_QI_POTENTIAL_PWR                         (30u)
/** Samsung PPDE Power Number */
#define CY_QI_SAMSUNG_POWER                         (22u)    /* WCPT-391 */
/** Apple fast charge Power Number */
#define CY_QI_APPLE_POWER                           (22u)   /* WCPT-391 */

#define CY_QI_REPING_DELAY_DEF                      (12600u)

#define CY_QI_ASK_PKT_ERROR_RETRY_CNT               (1u)

/**
 * Number of fail / noise packets within CE window
 * allowing for additional timeout.
 */
#define CY_QI_ASK_NOISE_CNT_CEP_RETRY_THRESHOLD     (5u)

/**
 * Number of times to retry CEP timeout in event of noise.
 * This is done to avoid CEP timeout due to noisy phones.
 */
#define CY_QI_CEP_TIMEOUT_NOISE_RETRY_CNT           (2u)

#define CY_QI_PCH_MIN                               (5u)
#define CY_QI_PCH_MAX                               (100u)

/** ASK Message Definitions for Packet Fields */

#define CY_QI_CONFIG_ID_XID_MASK                    (0x80)

#define CY_QI_CONFIG_OPT_COUNT_MASK                 (0x07)

#define CY_QI_CONFIG_NEG_MASK                       (0x80)
#define CY_QI_CONFIG_AUTH_MASK                      (0x40)
#define CY_QI_CONFIG_POLARITY_MASK                  (0x40)
#define CY_QI_CONFIG_POLARITY_POS                   (6)
#define CY_QI_CONFIG_DEPTH_MASK                     (0x30)
#define CY_QI_CONFIG_DEPTH_POS                      (4)

#define CY_QI_SPEC_REQ_POLARITY_MASK                (0x04)
#define CY_QI_SPEC_REQ_POLARITY_POS                 (2)
#define CY_QI_SPEC_REQ_DEPTH_MASK                   (0x03)
#define CY_QI_SPEC_REQ_DEPTH_POS                    (0)

#define CY_QI_SPEC_REQ_GP_MASK                      (0x3F)
#define CY_QI_SPEC_REQ_RP_MASK                      (0x3F)

#define CY_QI_CONFIG_WINDOW_SIZE_MASK               (0xF8)
#define CY_QI_CONFIG_WINDOW_SIZE_POS                (3)
#define CY_QI_CONFIG_WINDOW_OFFSET_MASK             (0x07)

#define CY_QI_SPEC_REQ_RCVD_POWER_BPP               (0x04)
#define CY_QI_SPEC_REQ_RCVD_POWER_EPP               (0x31)

#define CY_QI_SPEC_REQ_REPING_DELAY_MASK            (0x3F)
#define CY_QI_SPEC_REQ_REPING_DELAY_UNIT            (200)

#define CY_QI_FOD_PARAMS_RSVD_MASK                  (0xF8)
#define CY_QI_FOD_PARAMS_TYPE_MASK                  (0x03)
#define CY_QI_FOD_PARAMS_TYPE_QF                    (0x00)
#define CY_QI_FOD_PARAMS_TYPE_RF                    (0x01)
#define CY_QI_FOD_PARAMS_RF_SCALE_HZ                (500)
#define CY_QI_FOD_PARAMS_RF_OFFSET                  (72)

/* Masks to detect reserved bits of PRx packets for qi 1.2.4*/
#define CY_QI_RESERVED_BITS_F_SRQ_GUARANTED_PWR     (0xC0)
#define CY_QI_RESERVED_BITS_F_SRQ_REF_PWR           (0xC0)
#define CY_QI_RESERVED_BITS_F_FSK_PARAMS            (0xF8)
#define CY_QI_RESERVED_BITS_F_FOD_STAT              (0xFC)

#define CY_QI_RPOWER24BIT_MODE_MASK                 (0x07)


/** ASK Message Definitions for Samsung PPDE Packet Fields */

#define CY_SAMSUNG_ACK_0_MASK                       (0xFF)

#define CY_SAMSUNG_REQUEST_PPTX_0_MASK              (0x00)
#define CY_SAMSUNG_REQUEST_PPTX_1_MASK              (0x0C)

#define CY_SAMSUNG_PP_SET_POW_TRANSFER_MASK         (0x05)
#define CY_SAMSUNG_PP_SET_PROP_POW_TRANSFER_MASK    (0x2C)

#define CY_SAMSUNG_PP_SET_1_MASK                    (0x06)

/** FSK Message Definitions for Packet Fields */

#define CY_QI_CAP_DUP_MASK                          (0x80)
#define CY_QI_CAP_DUP_POS                           (7)
#define CY_QI_CAP_AR_MASK                           (0x40)
#define CY_QI_CAP_AR_POS                            (6)
#define CY_QI_CAP_BUF_MASK                          (0x1C)
#define CY_QI_CAP_BUF_POS                           (2)

/** System clock frequency requirement for Qi stack in KHz. */
#define CY_QI_SYS_CLK_FREQ_REQ_KHZ                  (48000u)

#if (CY_QI_SYS_CLK_FREQ_REQ_KHZ != CY_QI_SYS_CLK_FREQ_KHZ)
#error "System Clock requirement failed"
#endif

/** FSK capability message size. */
#define CY_QI_FSK_CAP_MSG_SIZE                      (5u)

/** FSK data packet size maximum limit. */
#define CY_QI_FSK_DATA_SIZE                         (10u)

/** ASK data packet size maximum limit. */
#define CY_QI_ASK_DATA_SIZE                         (27u)

/** FSK ID Message Size */
#define CY_QI_FSK_ID_MSG_SIZE                       (5u)

/** MAX FSK ADT Message Size including header and Checksum*/
#define CY_QI_FSK_ADT_MAX_MSG_SIZE                  (9u)

/** BMC RX baud rate. This is 2KHz as defined by Qi specification. */
#define CY_QI_BMC_RX_FREQ                           (2000u)

/**
 * This field indicates the over sample rate to be used. It can only take 8 or 16.
 */
#define CY_QI_BMC_RX_BIT_SPI_OVER_SAMPLE            (8u)
#if ((CY_QI_BMC_RX_BIT_SPI_OVER_SAMPLE != 8u) && (CY_QI_BMC_RX_BIT_SPI_OVER_SAMPLE != 16u))
#error "Unsupported SPI over sample rate. Only 8 or 16 supported."
#endif

/**
 * Assuming a preamble of 25 bits, (1 + 27 + 1) bytes at 11 bits per byte, there
 * will be about 44 bytes. Since we do not get to stop at the exact boundary, 
 * assuming 64 byte buffer is sufficient to hold all possible raw input.
 * Each byte is stored in 8X scale or 16X scale.
 */
#define CY_QI_BMC_RX_SPI_RAW_DATA_SIZE              (64u * (CY_QI_BMC_RX_BIT_SPI_OVER_SAMPLE))

#define CY_QI_MAX_NUM_ASK_SWITCH_OVER               (3u)

#define CY_QI_ASK_MOD_DEFAULT                       (CY_QI_ASK_PATH_VOLT_H)

#define CY_QI_EPP_5W_VAL                            (10u)
#define CY_QI_EPP_15W_VAL                           (30u)

#define CY_QI_VOLT_SAMPLE_RING_BUF_SIZE             (40u)
#define CY_QI_CUR_SAMPLE_RING_BUF_SIZE              (40u)

#define CY_QI_SUDDEN_LOAD_DROP_MAX_VAL_MA           (500u)
/* 
 * 75mA is minimum expected load with losses with practical PRx, 
 * consider 20% tolerance with this to set target load for load dump
 * generated by compliance tools.
 */
#define CY_QI_SUDDEN_LOAD_DROP_MIN_THRES_MA         (90u)

/** Q factor frequency starting edge to count */
#define CY_QI_Q_FREQ_ZCD_START_EDGE                 (5u)

/** Q factor frequency number of cycles to keep count data */
#define CY_QI_Q_FREQ_ZCD_CYCLE_NUM                  (10u)

/** Q factor ring buffer size */
#define CY_QI_Q_FACTOR_RING_BUF_MAX_SIZE            (20u)

#define CY_QI_NO_F_POWER_PARAMS                     (2u)   

#define CY_QI_LOAD_CALIB_MAX_RETRY_COUNT            (3u)

/* Macro to enable or disable Power Loss FOD */
#define CY_QI_DEASSERT_FOD                          (0u)

#define SIZE_UART_RING_BUF                          (512u)

/** PRx EPT retry count configuration */
#define CY_QI_PRX_EPT_RETRY_INFINITE                (255u)
#define CY_QI_PRX_EPT_RETRY_NUL                     (0u)
#define CY_QI_PRX_EPT_RETRY_CC                      (CY_QI_PRX_EPT_RETRY_INFINITE)
#define CY_QI_PRX_EPT_RETRY_IF                      (0u)
#define CY_QI_PRX_EPT_RETRY_OT                      (0u)
#define CY_QI_PRX_EPT_RETRY_OV                      (3u)
#define CY_QI_PRX_EPT_RETRY_OC                      (3u)
#define CY_QI_PRX_EPT_RETRY_BF                      (0u)
#define CY_QI_PRX_EPT_RETRY_NR                      (3u)
#define CY_QI_PRX_EPT_RETRY_AN                      (3u)
#define CY_QI_PRX_EPT_RETRY_RST                     (CY_QI_PRX_EPT_RETRY_INFINITE)
#define CY_QI_PRX_EPT_RETRY_REP                     (CY_QI_PRX_EPT_RETRY_INFINITE)
#define CY_QI_PRX_EPT_RETRY_NFC                     (3u)
#define CY_QI_PRX_EPT_RETRY_PTX_NFC                 (3u)

/** PRx EPT next ping delay configuration */
#define CY_QI_PRX_EPT_PING_DELAY_NUL                (60u)
#define CY_QI_PRX_EPT_PING_DELAY_CC                 (7700u)
#define CY_QI_PRX_EPT_PING_DELAY_IF                 (60u)
#define CY_QI_PRX_EPT_PING_DELAY_OT                 (0xFFFFu)
#define CY_QI_PRX_EPT_PING_DELAY_OV                 (2000u)
#define CY_QI_PRX_EPT_PING_DELAY_OC                 (2000u)
#define CY_QI_PRX_EPT_PING_DELAY_BF                 (0xFFFFu)
#define CY_QI_PRX_EPT_PING_DELAY_NR                 (60u)
#define CY_QI_PRX_EPT_PING_DELAY_AN                 (60u)
#define CY_QI_PRX_EPT_PING_DELAY_RST                (60u)
#define CY_QI_PRX_EPT_PING_DELAY_REP                (60u)
#define CY_QI_PRX_EPT_PING_DELAY_NFC                (60u)
#define CY_QI_PRX_EPT_PING_DELAY_PTX_NFC            (60u)


/** ADC, ADT and DSR Related Defines  */

#define CY_QI_ADC_END_AUTH_MASK                      0x00
#define CY_QI_ADC_START_AUTH_MASK                    0x02
#define CY_QI_ADC_RESET_AUTH_MASK                    0x05

#define CY_QI_ADT_EVEN_MASK                          0x06
#define CY_QI_ADT_ODD_MASK                           0x07
#define CY_QI_ADT_LENGTH_MASK                        0x07

#define CY_QI_DSR_NAK_MASK                           0x00
#define CY_QI_DSR_POLL_MASK                          0x33
#define CY_QI_DSR_ND_MASK                            0x55
#define CY_QI_DSR_ACK_MASK                           0xFF

/** Authentication configuration */
#define CY_QI_PTX_AUTH_EN_TEMP                      (1)
#define CY_QI_PTX_AUTH_DUP                          (0)
#define CY_QI_PTX_AUTH_BUFN                         (6)

#define COIL_VBRIDGE_MIN_VOLT                       (3000u)

/** \} group_qistack_macros */

/**
* \addtogroup group_qistack_enums
* \{
*/

/**
 * @brief Interface status codes
 *
 * Enumeration to hold status codes for all Qi interfaces. These values
 * are pre-defined for each interface and should not be modified. To make
 * interface usage easier, the enumeration starts at -2. This allows the
 * success status to have a value of zero. The response code should be
 * incremented by two before sending out on the individual interfaces.
 */
typedef enum cy_en_qi_status
{
    CY_QISTACK_STAT_NO_RESPONSE = -2,          /**< Special status code indicating no response. */
    CY_QISTACK_STAT_SUCCESS = 0,               /**< Success status. */
    CY_QISTACK_STAT_BAD_PARAM,                 /**< Bad input parameter. */
    CY_QISTACK_STAT_CMD_FAILURE,               /**< Command failure status */
    CY_QISTACK_STAT_FAILURE,                   /**< Generic failure status. */
} cy_en_qi_status_t;

/**
 * @typedef cy_en_qi_app_evt_t
 * @brief Enum of Qi events that are signalled to the application.
 */
typedef enum
{
    CY_QI_APP_EVT_INIT = 0,                     /**< 0x00: Qi init event. */
    CY_QI_APP_EVT_START,                        /**< 0x01: Qi start event. */
    CY_QI_APP_EVT_STOP,                         /**< 0x02: Qi stop event. */
    CY_QI_APP_EVT_RESET,                        /**< 0x03: Qi Reset event. */
    CY_QI_APP_EVT_PING_START,                   /**< 0x04: Qi Ping phase start event. */
    CY_QI_APP_EVT_OBJ_DET,                      /**< 0x05: Qi Object detected event */
    CY_QI_APP_EVT_Q_FACTOR_DATA_READY,          /**< 0x06: Qi QFactor data ready event */
    CY_QI_APP_EVT_RES_FREQ_DATA_READY,          /**< 0x07: Qi Resonce frequency data ready */
    CY_QI_APP_EVT_FREE_AIR_FOD,                 /**< 0x08: Qi Free air FOD event */
    CY_QI_APP_EVT_OBJ_REMOVED,                  /**< 0x09: Qi Object removed event */
    CY_QI_APP_EVT_PING_PRX_DET,                 /**< 0x0A: Qi Ping phase PRx detect event. */
    CY_QI_APP_EVT_RX_SS,                        /**< 0x0B: Qi received Signal strength event */
    CY_QI_APP_EVT_CFG_RCVD,                     /**< 0x0C: Qi Configuration received event. */
    CY_QI_APP_EVT_PROP,                         /**< 0x0D: Qi Proprietary packet event. */
    CY_QI_APP_EVT_RSVD,                         /**< 0x0E: Qi reserved packet event. */
    CY_QI_APP_EVT_NEG_EPT,                      /**< 0x0F: Qi negotiation ept event. */
    CY_QI_APP_EVT_NEG_DONE,                     /**< 0x10: Qi Negotiation done event. */
    CY_QI_APP_EVT_NEG_BPP_FAIL,                 /**< 0x11: Qi Negotiation BPP fail event. */
    CY_QI_APP_EVT_RXD_FOD_Q_FACTOR,             /**< 0x12: Qi Received QFactor from Rx event */
    CY_QI_APP_EVT_RXD_REF_FREQ,                 /**< 0x13: Qi Reference freq from Rx event */
    CY_QI_APP_EVT_CEP_RCVD,                     /**< 0x14: Qi Control Error Packet received event. */
    CY_QI_APP_EVT_SUDDEN_LOAD_REMOVAL,          /**< 0x15: Qi Sudden load removal event */
    CY_QI_APP_EVT_RPP_RCVD,                     /**< 0x16: Qi Received Power Packet event. */
    CY_QI_APP_EVT_RP0_RCVD,                     /**< 0x17: Qi Received Power0 Packet event. */
    CY_QI_APP_EVT_RP1_RCVD,                     /**< 0x18: Qi Received Power1 Packet event. */
    CY_QI_APP_EVT_RP2_RCVD,                     /**< 0x19: Qi Received Power2 Packet event. */
    CY_QI_APP_EVT_RP4_RCVD,                     /**< 0x1A: Qi Received Power4 Packet event. */
    CY_QI_APP_EVT_EPT_RCVD,                     /**< 0x1B: Qi End Power Transfer Received event. */
    CY_QI_APP_EVT_OBJ_FOD_SET,                  /**< 0x1C: Qi FO detected event */
    CY_QI_APP_EVT_OBJ_FOD_CLR,                  /**< 0x1D: Qi FO clear event */
    CY_QI_APP_EVT_LED_SET,                      /**< 0x1E: Qi LED set Event */
    CY_QI_APP_EVT_ASK_PATH_SWITCH_TIMEOUT,      /**< 0x1F: Qi ASK path switch timedout event */
    CY_QI_APP_EVT_ASK_PASS,                     /**< 0x20: Qi ASK Pass event */
    CY_QI_APP_EVT_ASK_NOISE,                    /**< 0x21: Qi ASK fail event */
    CY_QI_APP_EVT_ASK_FAIL,                     /**< 0x22: Qi ASK fail event */
    CY_QI_APP_EVT_FSK_ACK,                      /**< 0x23: Qi FSK ack event */
    CY_QI_APP_EVT_FSK_NAK,                      /**< 0x24: Qi FSK nack event */
    CY_QI_APP_EVT_FSK_ND,                       /**< 0x25: Qi FSK nd event */
    CY_QI_APP_EVT_FSK_NULL,                     /**< 0x26: Qi FSK null event */
    CY_QI_APP_EVT_FSK_ATN,                      /**< 0x27: Qi FSK atn event */
    CY_QI_APP_EVT_FSK_ID,                       /**< 0x28: Qi FSK id event */
    CY_QI_APP_EVT_FSK_CAP,                      /**< 0x29: Qi FSK cap event */
    CY_QI_APP_EVT_FSK_ADC,                      /**< 0x2A: Qi FSK adc event */
    CY_QI_APP_EVT_FSK_ADT,                      /**< 0x2B: Qi FSK adt event */
    CY_QI_APP_EVT_PWR_LOSS_PARAM_READY,         /**< 0x2C: Qi Power loss params ready event */
    CY_QI_APP_EVT_PWR_LOSS_THRES_READY,         /**< 0x2D: Qi Power loss threshold ready event */
    CY_QI_APP_EVT_PWR_LOSS_RETRY_INPROGRES,     /**< 0x2E: Qi Power loss retry in progress event */
    CY_QI_APP_EVT_POWER_LOSS_FOUND,             /**< 0x2F: Qi power loss value found event */
    CY_QI_APP_EVT_POWER_LOSS_TX_CALIB_READY,    /**< 0x30: Qi power loss tx calib ready event */
    CY_QI_APP_EVT_PTX_EPT_REASON,               /**< 0x31: Qi EPT reason event */
    CY_QI_APP_EVT_OBJ_DET_STARTED,              /**< 0x32: Qi Object detection started (not settled) event */
    CY_QI_APP_EVT_PWR_LOSS_PWR_CYCLE_COUNT,     /**< 0x33: Qi Power loss retry in progress event */
    CY_QI_APP_TOTAL_EVENTS                      /**< 0xNN: Total number of application events. */
} cy_en_qi_app_evt_t;

/**
 * @typedef cy_en_qi_ask_pkt_evt_t
 * @brief Enum of ASK BMC decoder events.
 */
typedef enum
{
    CY_QI_ASK_EVT_PKT_NONE = 0x00,                 /**< 0x00: ASK Packet no event. */
    CY_QI_ASK_EVT_DET_START = 0x01,                /**< 0x01: ASK Packet detection started. */
    CY_QI_ASK_EVT_START_BIT = 0x02,                /**< 0x02: ASK Packet start bit detected. */
    CY_QI_ASK_EVT_PKT_END = 0x04,                  /**< 0x04: ASK Packet end detected. */
    CY_QI_ASK_EVT_BIT_ERR = 0x08,                  /**< 0x08: ASK bit error. */
    CY_QI_ASK_EVT_PKT_ERR = 0x10,                  /**< 0x10: ASK packet error. */
    CY_QI_ASK_EVT_PKT_READY = 0x20,                /**< 0x20: ASK packet Ready. */
    CY_QI_ASK_EVT_DET_END = 0x40,                  /**< 0x40: ASK Packet detection ended. */
    CY_QI_ASK_EVT_MAX                              /**< 0xNN: Total number of ASK BMC events. */
} cy_en_qi_ask_pkt_evt_t;

/**
 * @typedef cy_en_qi_ask_pkt_t
 * @brief Enum of ASK packets.
 */
typedef enum {
    
    CY_QI_ASK_SIGNAL_STRENGTH = 0x01,                   /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_END_POWER_TRANSFER = 0x02,                /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_CONTROL_ERROR = 0x03,                     /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_RECEIVED_POWER_RP8 = 0x04,                /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_CHARGE_STATUS = 0x05,                     /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_CONFIG_PCH = 0x06,                        /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_GENERAL_REQUEST = 0x07,                   /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_RENEGOTIATE = 0x09,                       /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_DATA_STREAM_RESP = 0x15,                  /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_SPECIFIC_REQUEST = 0x20,                  /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_FOD_STATUS = 0x22,                        /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_DATA_AUX_DATA_CTRL = 0x25,                /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_RECEIVED_POWER_RP = 0x31,                 /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_CONFIGURATION = 0x51,                     /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_WPID_MSB = 0x54,                          /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_WPID_LSB = 0x55,                          /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_IDENTIFICATION = 0x71,                    /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_EXTENDED_IDENTIFICATION = 0x81,           /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_DATA_AUX_DATA_EVEN_1 = 0x16,              /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_DATA_AUX_DATA_ODD_1 = 0x17,               /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_DATA_AUX_DATA_EVEN_2 = 0x26,              /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_DATA_AUX_DATA_ODD_2 = 0x27,               /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_DATA_AUX_DATA_EVEN_3 = 0x36,              /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_DATA_AUX_DATA_ODD_3 = 0x37,               /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_DATA_AUX_DATA_EVEN_4 = 0x46,              /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_DATA_AUX_DATA_ODD_4 = 0x47,               /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_DATA_AUX_DATA_EVEN_5 = 0x56,              /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_DATA_AUX_DATA_ODD_5 = 0x57,               /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_DATA_AUX_DATA_EVEN_6 = 0x66,              /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_DATA_AUX_DATA_ODD_6 = 0x67,               /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_DATA_AUX_DATA_EVEN_7 = 0x76,              /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_DATA_AUX_DATA_ODD_7 = 0x77,               /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_CONFIG_PROP_1 = 0x18,                     /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_CONFIG_PROP_2 = 0x19,                     /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_CONFIG_PROP_3 = 0x28,                     /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_CONFIG_PROP_4 = 0x29,                     /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_CONFIG_PROP_5 = 0x38,                     /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_CONFIG_PROP_6 = 0x48,                     /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_CONFIG_PROP_7 = 0x58,                     /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_CONFIG_PROP_8 = 0x68,                     /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_CONFIG_PROP_9 = 0x78,                     /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_CONFIG_PROP_10 = 0x84,                    /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_CONFIG_PROP_11 = 0xA4,                    /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_CONFIG_PROP_12 = 0xC4,                    /**< 0xNN: ASK Packet Type. */
    CY_QI_ASK_CONFIG_PROP_13 = 0xE2                     /**< 0xNN: ASK Packet Type. */
} cy_en_qi_ask_pkt_t;

/**
 * @typedef cy_en_qi_prx_ept_reason_t
 * @brief Enum of Qi receiver End Power Transfer reasons.
 */
typedef enum
{
    CY_QI_PRX_EPT_UNKNOWN = 0,                      /**< 0x00: PRx EPT with reason Unknown */
    CY_QI_PRX_EPT_CHARGE_COMPLETE,                  /**< 0x01: PRx EPT with reason Charge Complete */
    CY_QI_PRX_EPT_INTERNAL_FAULT,                   /**< 0x02: PRx EPT with reason Internal Fault */
    CY_QI_PRX_EPT_OVER_TEMPERATURE,                 /**< 0x03: PRx EPT with reason OTP */
    CY_QI_PRX_EPT_OVER_VOLTAGE,                     /**< 0x04: PRx EPT with reason OVP */
    CY_QI_PRX_EPT_OVER_CURRENT,                     /**< 0x05: PRx EPT with reason OCP */
    CY_QI_PRX_EPT_BATT_FAILURE,                     /**< 0x06: PRx EPT with reason Battery failure */
    CY_QI_PRX_EPT_RSVD1,                            /**< 0x07: Reserved */
    CY_QI_PRX_EPT_NO_RESPONSE,                      /**< 0x08: PRx EPT with reason No response */
    CY_QI_PRX_EPT_RSVD2,                            /**< 0x09: Reserved */
    CY_QI_PRX_EPT_NEGOTIATION_FAIL,                 /**< 0x0A: PRx EPT with reason Negotiation fail */
    CY_QI_PRX_EPT_RESTART_POWER,                    /**< 0x0B: PRx EPT with reason Restart Power */
    CY_QI_PRX_EPT_REPING,                           /**< 0x0C: PRx EPT with reason Reping */
    CY_QI_PRX_EPT_NFC,                              /**< 0x0D: PRx EPT with reason NFC */
    CY_QI_PRX_EPT_PTX_NFC,                          /**< 0x0E: PRx EPT with reason PTx NFC */
    CY_QI_PRX_EPT_MAX                               /**< 0xNN: Total number of PRx EPT reasons */
} cy_en_qi_prx_ept_reason_t;

/**
 * @typedef cy_en_qi_srq_t
 * @brief Enum of Specific Request Types.
 */
typedef enum
{
    CY_QI_SRQ_END_NEGOTIATION = 0,                  /**< 0x00: SRQ: End negotiation */
    CY_QI_SRQ_GUARANTEED_POWER,                     /**< 0x01: SRQ: Guaranteed load power */
    CY_QI_SRQ_RCVD_POWER_REPORTING,                 /**< 0x02: SRQ: Received Power reporting */
    CY_QI_SRQ_FSK_PARAMS,                           /**< 0x03: SRQ: FSK configuration */
    CY_QI_SRQ_REFERENCE_POWER,                      /**< 0x04: SRQ: Reference/Max Power */
    CY_QI_SRQ_REPING_DELAY,                         /**< 0x05: SRQ: Reping Delay */
    CY_QI_SRQ_RECALIB,                              /**< 0x06: SRQ: Recalibration support */
    CY_QI_SRQ_MAX                                   /**< 0xNN: Total number of PRx EPT reasons */
} cy_en_qi_srq_t;

/**
 * @typedef cy_en_qi_grq_t
 * @brief Enum of General Request Types.
 */
typedef enum
{
    CY_QI_GRQ_NULL = 0,                             /**< GRQ: NULL */
    CY_QI_GRQ_PTX_ID = 0x30,                        /**< GRQ: PTx ID */
    CY_QI_GRQ_PTX_CAP = 0x31,                       /**< GRQ: PTx Capability */
    CY_QI_GRQ_PTX_XCAP = 0x32,                      /**< GRQ: PTx Extended ID */
    CY_QI_GRQ_ADC = 0x25,                           /**< GRQ: Auxiliary Data Control */
    CY_QI_GRQ_AUX_DATA_EVEN_1 = 0x16,               /**< GRQ: Auxiliary Data. */
    CY_QI_GRQ_AUX_DATA_ODD_1 = 0x17,                /**< GRQ: Auxiliary Data. */
    CY_QI_GRQ_AUX_DATA_EVEN_2 = 0x26,               /**< GRQ: Auxiliary Data. */
    CY_QI_GRQ_AUX_DATA_ODD_2 = 0x27,                /**< GRQ: Auxiliary Data. */
    CY_QI_GRQ_AUX_DATA_EVEN_3 = 0x36,               /**< GRQ: Auxiliary Data. */
    CY_QI_GRQ_AUX_DATA_ODD_3 = 0x37,                /**< GRQ: Auxiliary Data. */
    CY_QI_GRQ_AUX_DATA_EVEN_4 = 0x46,               /**< GRQ: Auxiliary Data. */
    CY_QI_GRQ_AUX_DATA_ODD_4 = 0x47,                /**< GRQ: Auxiliary Data. */
    CY_QI_GRQ_AUX_DATA_EVEN_5 = 0x56,               /**< GRQ: Auxiliary Data. */
    CY_QI_GRQ_AUX_DATA_ODD_5 = 0x57,                /**< GRQ: Auxiliary Data. */
    CY_QI_GRQ_AUX_DATA_EVEN_6 = 0x66,               /**< GRQ: Auxiliary Data. */
    CY_QI_GRQ_AUX_DATA_ODD_6 = 0x67,                /**< GRQ: Auxiliary Data. */
    CY_QI_GRQ_AUX_DATA_EVEN_7 = 0x76,               /**< GRQ: Auxiliary Data. */
    CY_QI_GRQ_AUX_DATA_ODD_7 = 0x77,                /**< GRQ: Auxiliary Data. */
    CY_QI_GRQ_PROP_DATA_ODD_1 = 0x1E,               /**< GRQ: Proprietary Data. */
    CY_QI_GRQ_PROP_DATA_EVEN_1 = 0x1F,              /**< GRQ: Proprietary Data. */
    CY_QI_GRQ_PROP_DATA_EVEN_2 = 0x2E,              /**< GRQ: Proprietary Data. */
    CY_QI_GRQ_PROP_DATA_ODD_2 = 0x2F,               /**< GRQ: Proprietary Data. */
    CY_QI_GRQ_PROP_DATA_3 = 0x3F,                   /**< GRQ: Proprietary Data. */
    CY_QI_GRQ_PROP_DATA_4 = 0x4F,                   /**< GRQ: Proprietary Data. */
    CY_QI_GRQ_PROP_DATA_5 = 0x5F,                   /**< GRQ: Proprietary Data. */
    CY_QI_GRQ_PROP_DATA_6 = 0x6F,                   /**< GRQ: Proprietary Data. */
    CY_QI_GRQ_PROP_DATA_7 = 0x7F,                   /**< GRQ: Proprietary Data. */
    CY_QI_GRQ_PROP_DATA_8 = 0x8F,                   /**< GRQ: Proprietary Data. */
    CY_QI_GRQ_MAX                                   /**< 0xNN: Total number of GRQ */
} cy_en_qi_grq_t;

/**
 * @typedef cy_en_qi_rp_mode_t
 * @brief Enum of Received Power(RP) Modes.
 */
typedef enum
{
    CY_QI_RP_MODE_RP0 = 0x00,               /**< RP Mode: RP0: Normal Value with response */
    CY_QI_RP_MODE_RP1 = 0x01,               /**< RP Mode: RP1: First (light load) data */
    CY_QI_RP_MODE_RP2 = 0x02,               /**< RP Mode: PR2: Additional (connected load) data */
    CY_QI_RP_MODE_RP4 = 0x04,               /**< RP Mode: RP4: Normal value no response */
    CY_QI_RP_MODE_MAX                       /**< 0xNN: Total number of RP Modes */
} cy_en_qi_rp_mode_t;

/**
 * @typedef cy_en_qi_ask_path_t
 * @brief Enum of ASK demodulation paths.
 */
typedef enum
{
    CY_QI_ASK_PATH_VOLT_H = 0,            /**< 0x00: Voltage high gain path. */
    CY_QI_ASK_PATH_VOLT_L,                /**< 0x01: Voltage low gain path. */
    CY_QI_ASK_PATH_CUR_H,                 /**< 0x02: Current high gain path. */
    CY_QI_ASK_PATH_CUR_L,                 /**< 0x03: Current low gain path. */
    CY_QI_ASK_PATH_MAX                    /**< 0xNN: Total number of ASK paths. */
} cy_en_qi_ask_path_t;

/**
 * @typedef cy_en_qi_cc_up_level_t
 * @brief Enum of USBPD CC line comparator levels
 */
typedef enum
{
    CY_QI_CC_UP_CMP_LVL_0P2 = 0,            /**< 0x00: 0.2V. */
    CY_QI_CC_UP_CMP_LVL_0P4 = 1,            /**< 0x01: 0.4V. */
    CY_QI_CC_UP_CMP_LVL_0P3 = 2,            /**< 0x02: 0.3V. */
    CY_QI_CC_UP_CMP_LVL_0P65 = 3,           /**< 0x03: 0.65V. */
    CY_QI_CC_UP_CMP_LVL_0P8 = 4,            /**< 0x04: 0.8V. */
    CY_QI_CC_UP_CMP_LVL_1P235 = 5,          /**< 0x05: 1.235V. */
    CY_QI_CC_UP_CMP_LVL_1P575 = 6,          /**< 0x06: 1.575V. */
    CY_QI_CC_UP_CMP_LVL_2P6 = 7,            /**< 0x07: 2.6V. */
    CY_QI_CC_UP_CMP_LVL_MAX                 /**< 0xNN: Total number of levels. */
} cy_en_qi_cc_up_level_t;

/**
 * @typedef cy_cb_ask_pkt_evt_t
 * @brief ASK packet event callback function.
 *
 * This callback function is invoked on ASK packet decode events and
 * should be treated as interrupt.
 */
typedef cy_en_qi_status_t (*cy_cb_ask_pkt_evt_t)(
        void * callbackContext,       /**< Context. */
        cy_en_qi_ask_pkt_evt_t pktEvt    /**< ASK packet decode event */
        );

/**
 * @typedef cy_en_qi_led_state_t
 * @brief Enum of ASK demodulation paths.
 */
typedef enum 
{
    CY_QI_LED_STATE_INIT = 0,                  /**< 0x00: Initial state. Both LED off. */
    CY_QI_LED_STATE_POWER_ON,                  /**< 0x01: Blink RED and BLUE */
    CY_QI_LED_STATE_CHARGING_PROGRESS,         /**< 0x02: Solid BLUE */ 
    CY_QI_LED_STATE_END_CHARGE_PROGRESS,       /**< 0x03: BLUE off */
    CY_QI_LED_STATE_FOD,                       /**< 0x04: Solid RED */
    CY_QI_LED_STATE_NO_FOD,                    /**< 0x05: Turn off RED */
    CY_QI_LED_STATE_VALID_RX_NO_COMM,          /**< 0x06: Blink BLUE */
    CY_QI_LED_STATE_RX_EPT_REQ_FAILURE,        /**< 0x07: Blink RED */
    CY_QI_LED_STATE_RX_EPT_REQ_SUCCESS,        /**< 0x08: Turn off RED and BLUE */    
    CY_QI_LED_STATE_FAULT,                     /**< 0x09: Solid RED */
    CY_QI_LED_STATE_FAULT_RECOVER,             /**< 0x0A: Turn off RED */
    CY_QI_LED_STATE_MAX                        /**< 0xNN: Total number of LED states */
} cy_en_qi_led_state_t;

/**
 * @typedef cy_en_qi_fod_stat_t
 * @brief Enum of FOD status
 */
typedef enum 
{
    CY_QI_FOD_STAT_ERROR = 0,
    CY_QI_FOD_STAT_NO_FO,
    CY_QI_FOD_STAT_FO
} cy_en_qi_fod_stat_t;

/**
 * @typedef cy_en_qi_object_status_t
 * @brief Enum of Object status
 */
typedef enum 
{
    CY_QI_OBJECT_ERROR = 0,
    CY_QI_OBJECT_NOT_PRESENT,
    CY_QI_OBJECT_PRESENT
} cy_en_qi_object_status_t;

/**
 * @brief Enum of Power Loss States
 * 
 */
typedef enum 
{
    CY_QI_PWR_LOSS_RCVD_NONE = 0,
    CY_QI_PWR_LOSS_RCVD_UNKNOWN,
    CY_QI_PWR_LOSS_LIGHT_LOAD,
    CY_QI_PWR_LOSS_CNCTD_LOAD,
    CY_QI_PWR_LOSS_RCVD_LOAD,
} cy_en_qi_pwr_loss_state_t;

/**
 * @typedef cy_en_qi_ver_t
 * @brief Enum of Qi specification versions (byte) list. 
 * Major Version: Upper nibble
 * Minor Version: Lower nibble
 */
typedef enum {
    CY_QI_VER_1P0 = 0x10,                   /**< Qi Spec version */
    CY_QI_VER_1P1 = 0x11,                   /**< Qi Spec version */
    CY_QI_VER_1P2 = 0x12,                   /**< Qi Spec version */
    CY_QI_VER_1P3 = 0x13,                   /**< Qi Spec version */
    CY_QI_VER_MAX                           /**< 0xNN: Total versions. */
} cy_en_qi_ver_t;



/**
 * @typedef cy_en_qi_mc_t
 * @brief Enum of Qi compliant device manufacturer code.
 * @see todo
 */
typedef enum {
    CY_QI_MC_NONE = 0x00,                   /**< Qi Manufacturere Code for:  */
    CY_QI_MC_IPHONE_1 = 0x5A,                   /**< Qi Manufacturere Code for: Apple Iphone   */
    CY_QI_MC_IPHONE_2 = 0xA5,                   /**< Qi Manufacturere Code for: Apple Iphone  */
    CY_QI_MC_MAX                           /**< 0xNN: Total versions. */
} cy_en_qi_mc_t;

/**
 * @typedef cy_en_qi_proto_t
 * @brief Enum of Qi Power Transmitter Protocols.
 */
typedef enum {
    CY_QI_PROTO_BPP = 0,                    /**< 0x00: Qi Baseline Protocol. */
    CY_QI_PROTO_EPP,                        /**< 0x01: Qi Extended Protocol. */
    CY_QI_PROTO_PPP,                        /**< 0x02: Proprietary Protocol. */
    CY_QI_PROTO_MAX                         /**< 0xNN: Total phases. */
} cy_en_qi_proto_t;

/**
 * @typedef cy_en_qi_phase_t
 * @brief Enum of Qi Power Transmitter Phases.
 */
typedef enum {
    CY_QI_PHASE_IDLE = 0,                   /**< 0x00: Idle Phase. */
    CY_QI_PHASE_PING,                       /**< 0x01: Ping Phase. */
    CY_QI_PHASE_CFG,                        /**< 0x02: Configuration Phase. */
    CY_QI_PHASE_NEG,                        /**< 0x03: Negotiation Phase. */
    CY_QI_PHASE_PWR,                        /**< 0x04: Power transfer Phase. */
    CY_QI_PHASE_MAX                         /**< 0xNN: Total phases. */
} cy_en_qi_phase_t;

/**
 * @typedef cy_en_qi_st_t
 * @brief Enum of Qi Power Transmitter States.
 */
typedef enum 
{
    CY_QI_ST_IDLE = 0xFE,                  /**<   -2: Idle state */
    CY_QI_ST_F = 0xFF,                     /**<   -1: Ping State Fault */
    CY_QI_ST_0 = 0,                      /**< 0x00: Ping State 0 */
    CY_QI_ST_1 = 1,                      /**< 0x01: Ping State 1 */
    CY_QI_ST_2 = 2,                      /**< 0x02: Configuration State  2 */
    CY_QI_ST_3 = 3,                      /**< 0x03: Configuration State  3 */
    CY_QI_ST_4 = 4,                      /**< 0x04: Configuration State  4 */
    CY_QI_ST_5 = 5,                      /**< 0x05: Configuration State  5 */
    CY_QI_ST_6 = 6,                      /**< 0x06: Configuration State  6 */
    CY_QI_ST_7 = 7,                      /**< 0x07: Negotiation State  7 (EPP only) */
    CY_QI_ST_8 = 8,                      /**< 0x08: Negotiation State  8 (EPP only) */
    CY_QI_ST_9 = 9,                      /**< 0x09: Negotiation State  9 (EPP only) */
    CY_QI_ST_10 = 10,                    /**< 0x0A: Negotiation State  10 (EPP only) */
    CY_QI_ST_11 = 11,                    /**< 0x0B: Power Transfer State  11 */
    CY_QI_ST_12 = 12,                    /**< 0x0C: Power Transfer State  12 */
    CY_QI_ST_13 = 13,                    /**< 0x0D: Power Transfer State  13 (EPP only) */
    CY_QI_ST_14 = 14,                    /**< 0x0E: Power Transfer State  14 (EPP only) */
    CY_QI_ST_15 = 15,                    /**< 0x0F: Power Transfer State  15 (EPP only) */
    CY_QI_ST_MAX                         /**< 0xNN: Qi Ping States Max. */
} cy_en_qi_st_t;

/**
 * @typedef cy_en_qi_st_0_ping_t
 * @brief Enum of Qi State 0 sub states.
 */
typedef enum 
{
    CY_QI_ST_0_PING_WAIT = 0,                   /**< 0x00: Qi State 0 ping Wait state. */
    CY_QI_ST_0_PING_ENTRY,                      /**< 0x01: Qi State 0 ping Analog ping. */
    CY_QI_ST_0_PING_ANA_PING,                   /**< 0x02: Qi State 0 ping Analog ping. */
    CY_QI_ST_0_PING_NFC,                        /**< 0x03: Qi State 0 ping NFC. */
    CY_QI_ST_0_PING_FOD,                        /**< 0x04: Qi State 0 ping FOD. */
    CY_QI_ST_0_PING_DIG_PING,                   /**< 0x05: Qi State 0 ping Digital Ping. */
    CY_QI_ST_0_PING_NO_PWR,                     /**< 0x06: Qi State 0 ping No power wait. */
    CY_QI_ST_0_PING_EXIT,                       /**< 0x07: Qi State 0 ping Exit state. */
    CY_QI_ST_0_PING_MAX                         /**< 0xNN: Qi State 0 ping States Max. */
} cy_en_qi_st_0_ping_t;

/**
 * @typedef cy_en_analog_ping_t
 * @brief Enum of Qi State 0 Analog Ping sub tasks
 */
typedef enum 
{
    CY_QI_ANALOG_PING_INIT = 0,                /**< 0x00: Qi ping Analog ping initialization. */
    CY_QI_ANALOG_PING_MEASURE,                 /**< 0x01: Qi ping Analog ping measure parameters. */
    CY_QI_ANALOG_PING_ANALYZE,                 /**< 0x02: Qi ping Analog ping analyze parameters. */
    CY_QI_ANALOG_PING_MAX                      /**< 0xNN: Qi ping States Max. */
} cy_en_analog_ping_t;

/**
 * @typedef cy_en_qi_st_1_ping_t
 * @brief Enum of Qi State 1 sub states.
 */
typedef enum 
{
    CY_QI_ST_1_PING_WAIT = 0,                   /**< 0x00: Qi State 1 ping Wait state. */
    CY_QI_ST_1_PING_SIG,                        /**< 0x01: Qi State 1 ping SS received. */
    CY_QI_ST_1_PING_EPT,                        /**< 0x02: Qi State 1 ping EPT received. */
    CY_QI_ST_1_PING_PING_EXIT,                  /**< 0x02: Qi State 1 ping Ping Exit state. */
    CY_QI_ST_1_PING_CFG_EXIT,                   /**< 0x03: Qi State 1 ping Config Exit. */
    CY_QI_ST_1_PING_MAX                         /**< 0xNN: Qi ping States Max. */
} cy_en_qi_st_1_ping_t;

/**
 * @typedef cy_en_qi_st_f_ping_t
 * @brief Enum of Qi State F sub states.
 */
typedef enum 
{
    CY_QI_ST_F_PING_WAIT = 0,                   /**< 0x00: Qi State Fault ping Wait state. */
    CY_QI_ST_F_PING_PWR_STOP,                   /**< 0x01: Qi State Fault ping Stop power. */
    CY_QI_ST_F_PING_RESET,                      /**< 0x02: Qi State Fault ping Reset. */
    CY_QI_ST_F_PING_EXIT,                       /**< 0x03: Qi State Fault ping Exit state. */
    CY_QI_ST_F_PING_MAX                         /**< 0xNN: Qi State Fault ping States Max. */
} cy_en_qi_st_f_ping_t;

/**
 * @typedef cy_en_qi_st_2_cfg_t
 * @brief Enum of Qi State 2 sub states.
 */
typedef enum 
{
    CY_QI_ST_2_CFG_WAIT = 0,                    /**< 0x00: Qi State 2 cfg Wait state. */
    CY_QI_ST_2_CFG_ENTRY,                       /**< 0x01: Qi State 2 cfg Entry. */
    CY_QI_ST_2_CFG_ID,                          /**< 0x02: Qi State 2 cfg ID. */
    CY_QI_ST_2_CFG_PING_EXIT,                   /**< 0x03: Qi State 2 cfg Exit state. */
    CY_QI_ST_2_CFG_MAX                          /**< 0xNN: Qi State 2 cfg States Max. */
} cy_en_qi_st_2_cfg_t;

/**
 * @typedef cy_en_qi_st_3_cfg_t
 * @brief Enum of Qi State 3 sub states.
 */
typedef enum 
{
    CY_QI_ST_3_CFG_WAIT = 0,                     /**< 0x00: Qi State 3 cfg Wait state. */
    CY_QI_ST_3_CFG_ENTRY,                        /**< 0x01: Qi State 3 cfg Entry. */
    CY_QI_ST_3_CFG_XID,                          /**< 0x02: Qi State 3 cfg Extended ID. */
    CY_QI_ST_3_CFG_PING_EXIT,                    /**< 0x03: Qi State 3 cfg Exit state. */
    CY_QI_ST_3_CFG_MAX                           /**< 0xNN: Qi State 3 cfg States Max. */
} cy_en_qi_st_3_cfg_t;

/**
 * @typedef cy_en_qi_st_4_cfg_t
 * @brief Enum of Qi State 4 sub states.
 */
typedef enum 
{
    CY_QI_ST_4_CFG_WAIT = 0,                     /**< 0x00: Qi State 4 cfg Wait state. */
    CY_QI_ST_4_CFG_ENTRY,                        /**< 0x01: Qi State 4 cfg Entry. */
    CY_QI_ST_4_CFG_CFG,                          /**< 0x02: Qi State 4 cfg Configuration. */
    CY_QI_ST_4_CFG_PCH,                          /**< 0x03: Qi State 4 cfg Power Control Hold-off. */
    CY_QI_ST_4_CFG_PROP,                         /**< 0x04: Qi State 4 cfg Proprietary. */
    CY_QI_ST_4_CFG_RSVD,                         /**< 0x05: Qi State 4 cfg Reserved. */
    CY_QI_ST_4_CFG_PING_EXIT,                    /**< 0x06: Qi State 4 cfg Ping Exit state. */
    CY_QI_ST_4_CFG_BPP_EXIT,                     /**< 0x07: Qi State 4 cfg BPP Exit state. */
    CY_QI_ST_4_CFG_EPP_EXIT,                     /**< 0x08: Qi State 4 cfg EPP Exit state. */
    CY_QI_ST_4_CFG_MAX                           /**< 0xNN: Qi State 4 cfg States Max. */
} cy_en_qi_st_4_cfg_t;

/**
 * @typedef cy_en_qi_st_5_cfg_t
 * @brief Enum of Qi State 5 sub states.
 */
typedef enum 
{
    CY_QI_ST_5_CFG_WAIT = 0,                     /**< 0x00: Qi State 5 cfg Wait state. */
    CY_QI_ST_5_CFG_BPP,                          /**< 0x01: Qi State 5 cfg BPP mode. */
    CY_QI_ST_5_CFG_PING_EXIT,                    /**< 0x02: Qi State 5 cfg Exit Ping. */
    CY_QI_ST_5_CFG_PWR_EXIT,                     /**< 0x03: Qi State 5 cfg Exit Power Transfer. */
    CY_QI_ST_5_CFG_MAX                           /**< 0xNN: Qi State 5 cfg States Max. */
} cy_en_qi_st_5_cfg_t;

/**
 * @typedef cy_en_qi_st_6_cfg_t
 * @brief Enum of Qi State 6 sub states.
 */
typedef enum 
{
    CY_QI_ST_6_CFG_WAIT = 0,                     /**< 0x00: Qi State 6 cfg Wait state. */
    CY_QI_ST_6_CFG_EPP,                          /**< 0x01: Qi State 6 cfg EPP Mode. */
    CY_QI_ST_6_CFG_PING_EXIT,                    /**< 0x02: Qi State 6 cfg Exit Ping. */
    CY_QI_ST_6_CFG_NEG_EXIT,                     /**< 0x03: Qi State 6 cfg Exit Negotiation. */
    CY_QI_ST_6_CFG_PWR_EXIT,                     /**< 0x04: Qi State 6 cfg Exit Power Transfer. */
    CY_QI_ST_6_CFG_MAX                           /**< 0xNN: Qi State 6 cfg States Max. */
} cy_en_qi_st_6_cfg_t;

/**
 * @typedef cy_en_qi_st_7_neg_t
 * @brief Enum of Qi State 7 sub states.
 */
typedef enum 
{
    CY_QI_ST_7_NEG_WAIT = 0,                     /**< 0x00: Qi State 7 Neg Wait state. */
    CY_QI_ST_7_NEG_ENTRY,                        /**< 0x01: Qi State 7 Neg entry. */
    CY_QI_ST_7_NEG_SRQ,                          /**< 0x02: Qi State 7 Neg Specific Request. */
    CY_QI_ST_7_NEG_GRQ,                          /**< 0x03: Qi State 7 Neg General Request. */
    CY_QI_ST_7_NEG_FOD,                          /**< 0x04: Qi State 7 Neg FOD Status. */
    CY_QI_ST_7_NEG_WPID,                         /**< 0x05: Qi State 7 Neg WPID. */
    CY_QI_ST_7_NEG_PROP,                         /**< 0x06: Qi State 7 Neg Proprietary. */
    CY_QI_ST_7_NEG_RSVD,                         /**< 0x07: Qi State 7 Neg Reserved. */
    CY_QI_ST_7_NEG_EPT,                          /**< 0x08: Qi State 7 Neg EPT. */
    CY_QI_ST_7_NEG_AUTH,                         /**< 0x09: Qi State 7 Neg Authentication */
    CY_QI_ST_7_NEG_PING_EXIT,                    /**< 0x0A: Qi State 7 Neg Wait Exit Ping. */
    CY_QI_ST_7_NEG_BPP_PWR_EXIT,                 /**< 0x0B: Qi State 7 Neg Exit BPP Power Transfer. */
    CY_QI_ST_7_NEG_EPP_PWR_EXIT,                 /**< 0x0C: Qi State 7 Neg Exit EPP Power Transfer. */
    CY_QI_ST_7_NEG_MAX                           /**< 0xNN: Qi State 7 Neg States Max. */
} cy_en_qi_st_7_neg_t;

/**
 * @typedef cy_en_qi_st_11_pwr_t
 * @brief Enum of Qi State 11 sub states.
 */
typedef enum 
{
    CY_QI_ST_11_PWR_BPP_WAIT = 0,                 /**< 0x00: Qi State 11 Power Trasnfer Wait state. */
    CY_QI_ST_11_PWR_EPP_WAIT,                     /**< 0x01: Qi State 11 Power Trasnfer Wait state. */
    CY_QI_ST_11_PWR_BPP_ENTRY,                    /**< 0x02: Qi State 11 Power Trasnfer entry. */
    CY_QI_ST_11_PWR_EPP_ENTRY,                    /**< 0x03: Qi State 11 Power Trasnfer entry. */
    CY_QI_ST_11_PWR_RENEG,                        /**< 0x04: Qi State 11 Power Trasnfer Renegotiate. */
    CY_QI_ST_11_PWR_CEP,                          /**< 0x05: Qi State 11 Power Trasnfer CEP. */
    CY_QI_ST_11_PWR_RP8,                          /**< 0x06: Qi State 11 Power Trasnfer RPP 8 bit. */
    CY_QI_ST_11_PWR_RP,                           /**< 0x07: Qi State 11 Power Trasnfer RPP 24 bit. */
    CY_QI_ST_11_PWR_CHS,                          /**< 0x08: Qi State 11 Power Trasnfer CHS. */
    CY_QI_ST_11_PWR_PROP,                         /**< 0x09: Qi State 11 Power Trasnfer Propriatary. */
    CY_QI_ST_11_PWR_RSVD,                         /**< 0x0A: Qi State 11 Power Trasnfer Reserved. */
    CY_QI_ST_11_PWR_EPT,                          /**< 0x0B: Qi State 11 Power Trasnfer EPT. */
    CY_QI_ST_11_PWR_AUX_CTL,                      /**< 0x0C: Qi State 11 Power Trasnfer Authentication */
    CY_QI_ST_11_PWR_AUX_DATA,                     /**< 0x0D: Qi State 11 Power Trasnfer Authentication */
    CY_QI_ST_11_PWR_DSR,                          /**< 0x0E: Qi State 11 Power Trasnfer Authentication */                            
    CY_QI_ST_11_PWR_PING_EXIT,                    /**< 0x0F: Qi State 11 Power Trasnfer Exit Ping. */ 
    CY_QI_ST_11_PWR_NEG_EXIT,                     /**< 0x10: Qi State 11 Power Trasnfer Exit Negotiation. */ 
    CY_QI_ST_11_PWR_MAX                           /**< 0x11: Qi State 11 Power Trasnfer States Max. */
} cy_en_qi_st_11_pwr_t;

/**
 * @typedef cy_en_qi_st_12_pwr_t
 * @brief Enum of Qi State 12 Sub states
 */
typedef enum
{
    CY_QI_ST_13_PWR_ADC = 0, 
    CY_QI_ST_13_PWR_ADT
}cy_en_qi_st_13_pwr_t;

/**
 * @brief 
 * 
 */
typedef enum
{
    CY_QI_ST_13_PWR_ADT_EVEN_ENTRY = 1,
    CY_QI_ST_13_PWR_ADT_ODD_ENTRY
}cy_en_qi_st_13_data_transport_t;

/**
 * @typedef cy_en_qi_st_15_pwr_t
 * @brief Enum of Qi State 15 Sub states
 */
typedef enum
{
    CY_QI_ST_15_PWR_DSR = 0,
    CY_QI_ST_15_PWR_DSR_EXIT
}cy_en_qi_st_15_pwr_t;

/**
 * @brief 
 * 
 */
typedef enum
{
    CY_QI_ST_15_PWR_DSR_ADC_START,
    CY_QI_ST_15_PWR_DSR_ADC_WAIT,
    CY_QI_ST_15_PWR_DSR_DATA_READY_EVEN,
    CY_QI_ST_15_PWR_DSR_DATA_READY_ODD,
    CY_QI_ST_15_PWR_DSR_ADC_EXIT
}cy_en_qi_st_15_data_transport_t;

/**
 * @typedef cy_en_qi_ptx_ept_reason_t
 * @brief Enum of End of Power transfer cause
 */
typedef enum {
    CY_QI_PTX_EPT_CAUSE_INVALID_PKT = 0,                 /**< 00: Invalid packet */
    CY_QI_PTX_EPT_CAUSE_DELAYED_1ST_PKT,                 /**< 01: Invalid 1st packet */
    CY_QI_PTX_EPT_CAUSE_T_NEXT_TIMEOUT,                  /**< 02: Tnext timeout */
    CY_QI_PTX_EPT_CAUSE_RX_CONFIG_COUNT_MISMATCH,        /**< 03: Configuration packet sequence mismatch */
    CY_QI_PTX_EPT_CAUSE_T_NEGO_TIMEOUT,                  /**< 04: Tnegotiate timeout */
    CY_QI_PTX_EPT_CAUSE_T_TIMER_TIMEOUT,                 /**< 05: Ttimer timeout */
    CY_QI_PTX_EPT_CAUSE_T_POWER_TIMEOUT,                 /**< 06: Tpower timeout */
    CY_QI_PTX_EPT_CAUSE_FOD_NACK,                        /**< 07: FOD Nacked */
    CY_QI_PTX_EPT_CAUSE_ASK_PKT_TIMEOUT,                 /**< 08: ASK Packet timeout */
    CY_QI_PTX_EPT_CAUSE_ASK_ERR_BEFORE_PWRTRANS,         /**< 09: ASK packet error before power transfer */
    CY_QI_PTX_EPT_CAUSE_PLOSS_FOD_EXCE_THRES,            /**< 10: Power Loss exceed threshold */
    CY_QI_PTX_EPT_CAUSE_PLOSS_FOD_EXCE_MAX_THRES,        /**< 11: Power Loss exceed max threshold */
    CY_QI_PTX_EPT_CAUSE_PLOSS_FOD_PWRCYCLE,              /**< 12: Power Loss FOD power cycle count reached */
    CY_QI_PTX_EPT_CAUSE_PLOSS_RESERVED1,                 /**< 13: RESERVED */
    CY_QI_PTX_EPT_CAUSE_PLOSS_RESERVED2,                 /**< 14: RESERVED */
    CY_QI_PTX_EPT_CAUSE_PLOSS_RESERVED3,                 /**< 15: RESERVED */
    CY_QI_PTX_EPT_CAUSE_PLOSS_RESERVED4,                 /**< 16: RESERVED */
    CY_QI_PTX_EPT_CAUSE_PLOSS_RESERVED5,                 /**< 17: RESERVED */
    CY_QI_PTX_EPT_CAUSE_PLOSS_RESERVED6,                 /**< 18: RESERVED */
    CY_QI_PTX_EPT_CAUSE_FAULT_VBRG_OVP,                  /**< 19: FAULT: VBRG_OVP */
    CY_QI_PTX_EPT_CAUSE_FAULT_VBRG_OCP,                  /**< 20: FAULT: VBRG_OCP */
    CY_QI_PTX_EPT_CAUSE_FAULT_VBRG_SCP,                  /**< 21: FAULT: VBRG_SCP */
    CY_QI_PTX_EPT_CAUSE_FAULT_OTP,                       /**< 22: FAULT: VBRG_OTP */
    CY_QI_PTX_EPT_CAUSE_FAULT_VIN_OVP,                   /**< 23: FAULT: VIN_OVP */
    CY_QI_PTX_EPT_CAUSE_FAULT_VIN_UVP,                   /**< 24: FAULT: VIN_UVP */
    CY_QI_PTX_EPT_CAUSE_FAULT_VREG_INRUSH,               /**< 25: FAULT: VREG_INRUSH */
    CY_QI_PTX_EPT_CAUSE_FAULT_VDDD_BOD,                  /**< 26: FAULT: VDDD_BOD */
    CY_QI_PTX_EPT_CAUSE_FAULT_BB_ILIM,                   /**< 27: FAULT: BB_ILIM */
    CY_QI_PTX_EPT_CAUSE_FAULT_CC_OVP,                    /**< 28: FAULT: CC_OVP */

    CY_QI_PTX_EPT_CAUSE_PCH_OUT_F_RANGE = 41,            /**< 41: PCH out of range */
    CY_QI_PTX_EPT_CAUSE_NEG_FAILED_VER_EXCEED,           /**< 42: Unsuccessful negotiation, oper.version is above 1.3.x */
    CY_QI_PTX_EPT_CAUSE_INVALID_RP0_ENTRY,               /**< 43: Invalid RP0 entry */
    CY_QI_PTX_EPT_CAUSE_INVALID_RP1_ENTRY,               /**< 44: Invalid RP1 entry  */
    CY_QI_PTX_EPT_CAUSE_INVALID_RP2_ENTRY,               /**< 45: Invalid RP2 entry  */
    CY_QI_PTX_EPT_CAUSE_INVALID_RP4_ENTRY,               /**< 46: Invalid RP4 entry  */
    CY_QI_PTX_EPT_CAUSE_SRQ_FAILED_VER_EXCEED,           /**< 47: Failed SRQ, operating version exceed  */

    CY_QI_PTX_EPT_CAUSE_INVALID_PKT1 = 101,              /**< 101: Invalid packet1 */
    CY_QI_PTX_EPT_CAUSE_INVALID_PKT2,                    /**< 102: Invalid packet2 */
    CY_QI_PTX_EPT_CAUSE_INVALID_PKT3,                    /**< 103: Invalid packet3 */
    CY_QI_PTX_EPT_CAUSE_INVALID_PKT4,                    /**< 104: Invalid packet4 */
    CY_QI_PTX_EPT_CAUSE_INVALID_PKT5,                    /**< 105: Invalid packet5 */
    CY_QI_PTX_EPT_CAUSE_INVALID_PKT6,                    /**< 106: Invalid packet6 */
    CY_QI_PTX_EPT_CAUSE_INVALID_PKT7,                    /**< 107: Invalid packet7 */

    CY_QI_PTX_EPT_CAUSE_PRX_EPT = 121,                   /**< 121: Due to PRx EPT */

    CY_QI_PTX_EPT_CAUSE_MAX = 0xFF
} cy_en_qi_ptx_ept_reason_t;

/**
 * @typedef cy_en_qi_st_samsung_ppde_t
 * @brief Samsung PPDE State 
 */
typedef enum
{
    CY_QI_ST_11_SAMSUNG_PPDE_ENTRY = 0,
    CY_QI_ST_11_SAMSUNG_PPDE_WAIT,
    CY_QI_ST_11_SAMSUNG_PPDE
}cy_en_qi_st_samsung_ppde_t;

/**
 * @typedef cy_en_qi_ploss_reasons_t
 * @brief Enum of Power Loss FO detection reasons
 */
typedef enum {
    CY_QI_PLOSS_REASON_NONE = 0,    
    CY_QI_PLOSS_DISABLED = CY_QI_PLOSS_REASON_NONE,
    CY_QI_PLOSS_REASON_EXCEED_THRES_MAX,         /**< 0x01: Invalid packet */
    CY_QI_PLOSS_REASON_EXCEED_THRES,             /**< 0x02: Invalid packet */
    CY_QI_PLOSS_REASON_MAX_PWRCYCLE_CNT,         /**< 0x03: Invalid packet */
} cy_en_qi_ploss_reasons_t;


/* Forward declarations of structures. */
struct cy_stc_qi_context;

/**
 * @brief Struct to hold the application interface. The application is expected to
 * fill the structure with pointers to functions that use the on-board circuitry to
 * accomplish specific tasks. All the functions in this
 * structure must be non-blocking and take minimum execution time.
 *
 * @warning The application must check the callback pointer passed by the
 * stack is not NULL.
 */
typedef struct
{
    void (*app_event_handler) (
            struct cy_stc_qi_context *qiCtx, /**< Qi context. */
            cy_en_qi_app_evt_t evt
            );      /**< App event handler callback. */

    void (*hardware_init) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /**< Initialize Hardware Modules as required. */

    void (*ask_bmc_init) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /**< Initialize Hardware Modules as required. */

    void (*cc_up_cmp_enable) (
            struct cy_stc_qi_context *qiCtx,        /**< Qi context. */
            cy_en_qi_cc_up_level_t level,       /**< Comparator level */
            void * cbk      /**< Callback */
            );      /**< Enable USBPD CC line up comparator as required. */

    void (*ask_cc_up_cmp_enable) (
            struct cy_stc_qi_context *qiCtx,        /**< Qi context. */
            cy_en_qi_cc_up_level_t level,       /**< Comparator level */
            void * cbk      /**< Callback */
            );      /**< Enable USBPD CC line up comparator as required for ASK. */

    void (*cc_up_cmp_disable) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /**< Disable USBPD CC line up comparator. */

    void (*cc_dn_cmp_enable) (
            struct cy_stc_qi_context *qiCtx,        /**< Qi context. */
            cy_en_qi_cc_up_level_t level,       /**< Comparator level */
            void * cbk      /**< Callback */
            );      /**< Enable USBPD CC line down comparator as required. */

    void (*cc_dn_cmp_disable) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /**< Disable USBPD CC line down comparator. */

    void (*pds_scp_cmp_enable) (
            struct cy_stc_qi_context *qiCtx,        /**< Qi context. */
            void * cbk      /**< Callback */
            );      /**< Enable PDS SCP comparator as required. */

    void (*pds_scp_cmp_disable) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /**< Disable PDS SCP comparator. */

    void (*set_ask_path) (
            struct cy_stc_qi_context *qiCtx,        /**< Qi context. */
            cy_en_qi_ask_path_t askPath        /**< ASK path for demodulation */ 
            );      /**< Set requested ASK path for ASK demodulation. */

    void (*fsk_oper_init) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /**< Initialize Hardware Modules as required. */

    void (*inv_fb_enable) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /**< Enable Inverter full bridge. */

    void (*inv_fb_disable) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /**< Disable Inverter full bridge. */

    void (*inv_send_analog_ping) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /**< Send inverter analog ping. */

    void (*inv_start_digital_ping) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /**< Start inverter digital ping. */

    void (*inv_stop_digital_ping) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /**< Stop inverter digital ping. */

    void (*coil_src_enable) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /**< Enable coil voltage source. */

    void (*coil_src_disable) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /**< Disable coil voltage source. */

    bool (*coil_src_enable_status) (
            struct cy_stc_qi_context *qiCtx       /**< Qi context. */
            );      /**< Returns coil voltage enable status. */

    void (*coil_src_set_voltage) (
            struct cy_stc_qi_context *qiCtx,       /**< Qi context. */
            uint16_t volt_mV,        /**< Target voltage in mV units. */
            bool multiSlope        /**< Multi-slope VBTR */
            );      /**< Set coil voltage in mV units. */

    bool (*coil_src_ready_status) (
            struct cy_stc_qi_context *qiCtx       /**< Qi context. */
            );      /**< Returns coil voltage enable/set ready status. */

    uint16_t (*coil_src_get_voltage) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /**< Get coil voltage. */

    uint16_t (*coil_src_get_current) (
            struct cy_stc_qi_context *qiCtx,        /**< Qi context. */
            uint8_t avgSamples     /**< Number of samples to average */
            );      /**< Get coil current. */
    uint16_t (*coil_src_get_max_supported_volt) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /**< Get maximum supported coil source volt */
    void (*led_set_pin_value)(
            uint8_t pin,                           /**< Pin number */
            bool value                             /**< Value to be set */
            );      /**< Set LED Pin and Value */
    void (*Console_WriteString)(
            char_t const string[]                  /**< String value */
            );      /**< String value to write */
    void (*auth_init_pwm)(void);         /**< Init Auth PWM */
    void (*debug_gpio_SetValue)(
            struct cy_stc_qi_context *qiCtx,       /**< Qi context. */
            bool setorclear
            );  /**< Set Debug Pin with Value */
} cy_stc_qi_app_cbk_t;

/**
 * @brief Structure to hold the Qi configuration state parameters.
 */
typedef struct {
    /** Qi protocol type status */
    cy_en_qi_proto_t proto;

    /** Qi operating version. This is minimum of PTx and PRx versions */
    cy_en_qi_ver_t verOp;

    /** Qi PTx version */
    cy_en_qi_ver_t verPTx;

    /** Qi PRx version */
    cy_en_qi_ver_t verPRx;

    /** Qi manufacturer code */
    cy_en_qi_mc_t qiMc;

    /** Qi Authentication enable status */
    bool authOp;

    /** Optional configuration count */
    uint16_t optCfgCnt;

} cy_stc_qi_cfg_params_t;

/**
 * @brief Structure to hold the Qi power transfer elements.
 */
typedef struct {
    /** PRx RPP sample offset time */
    uint8_t tOffset;

    /** PRx RPP sample window time */
    uint8_t tWindow;

    /** PRx Power Control Hold-off time */
    uint16_t pch;

    /** FSK polarity */
    uint8_t polarity;

    /** FSK depth */
    uint8_t depth;

    /** Receiver Power Resolution */
    uint8_t rxPowerResolution;

    /** Negotiated reference load power */
    uint8_t referencePower;

    /** Negotiated guaranteed load power */
    uint8_t guaranteedPower;

    /** Potential load power */
    uint8_t potentialPower;

    /** Re-ping delay */
    uint16_t rePingDelay;

} cy_stc_qi_pwr_params_t;

/**
 * @brief Structure to hold the Qi LED state.
 */
typedef struct {
    /** Flag to run LED or not */
    bool runLEDtask;

    /** Red LED status */
    bool redLEDstatus;
          
    /** Blue LED status */
    bool blueLEDstatus;
          
    /** LED Blink count */
    uint8_t ledBlinkCount;

    /** LED timer timeout value */
    uint16_t ledTimeout;
    
    /** Present LED state */
    cy_en_qi_led_state_t requestedLEDstate;

    /** Present LED state */
    cy_en_qi_led_state_t presentLEDstatus;

    /** Previous LED state */
    cy_en_qi_led_state_t previousLEDstatus;
} cy_stc_qi_led_state_t;

/**
 * @brief Structure to hold the Qi EPT status
 */
typedef struct {

    /** EPT: Unknown ping retry count. 0x00 - No retry, 0xFF - Infinite retry */
    uint8_t eptRetryNul;

    /** EPT: Charge complete ping retry count. 0x00 - No retry, 0xFF - Infinite retry */
    uint8_t eptRetryCc;

    /** EPT: Internal Fault ping retry count. 0x00 - No retry, 0xFF - Infinite retry */
    uint8_t eptRetryIf;

    /** EPT: OTP ping retry count. 0x00 - No retry, 0xFF - Infinite retry */
    uint8_t eptRetryOt;

    /** EPT: OVP ping retry count. 0x00 - No retry, 0xFF - Infinite retry */
    uint8_t eptRetryOv;

    /** EPT: OCP ping retry count. 0x00 - No retry, 0xFF - Infinite retry */
    uint8_t eptRetryOc;

    /** EPT: Battery Full ping retry count. 0x00 - No retry, 0xFF - Infinite retry */
    uint8_t eptRetryBf;

    /** EPT: No response ping retry count. 0x00 - No retry, 0xFF - Infinite retry */
    uint8_t eptRetryNr;

    /** EPT: Negotiation fail ping retry count. 0x00 - No retry, 0xFF - Infinite retry */
    uint8_t eptRetryAn;

    /** EPT: Reset ping retry count. 0x00 - No retry, 0xFF - Infinite retry */
    uint8_t eptRetryRst;

    /** EPT: Reping ping retry count. 0x00 - No retry, 0xFF - Infinite retry */
    uint8_t eptRetryRep;

    /** EPT: NFC ping retry count. 0x00 - No retry, 0xFF - Infinite retry */
    uint8_t eptRetryNfc;

    /** EPT: PTx NFC ping retry count. 0x00 - No retry, 0xFF - Infinite retry */
    uint8_t eptRetryPtxNfc;

} cy_stc_qi_ept_t;

/**
 * @brief Structure to hold the Qi Policy Configuration and Status.
 */
typedef struct {
    /** Active or Idle Status */
    uint16_t activeMask;

    /** Qi policy Run or Stop Control */
    bool run;

    /**< Qi protocol version */
    cy_en_qi_proto_t proto;

    /**< Qi protocol operating phase */
    cy_en_qi_phase_t phase;

    /**< Qi protocol state */
    uint8_t state;

    /**< Qi protocol substate under each state */
    uint8_t subState;

    /**< Stages/tasks under each substate */
    uint8_t subTask;

    /**< Qi protocol previous state for backtracing */
    uint8_t prevState;

    /**< Qi protocol previous substate for backtracing */
    uint8_t prevSubState;

    /** Wait for object removal */
    bool waitForObjectRemove;

    /** cause of PTx EPT */
    cy_en_qi_ptx_ept_reason_t ptxEptReason;
    
    /** cause of PRx EPT */
    cy_en_qi_prx_ept_reason_t prxEptReason;

    /** EPT status */
    cy_stc_qi_ept_t eptStat;

    /** Receiver Signal Strength */
    uint8_t rxSignalStr;

    /** Run Analog ping */
    bool anaPingPending;

    /** Run Digital ping */
    bool digPingPending;

    /** Digital ping wake up pending */
    bool digPingWakePending;

    /** Digital ping interval timeout */
    bool digIntervalTimeout;

    /** Digital Tping timeout */
    bool digtPingTimeout;

    /** Analog ping timeout */
    volatile bool anaPingTimeout;

    /** PTx allowed maximum/potential power */
    uint8_t maxPower;

    /** PTx allowed guaranteed/negotiable power */
    uint8_t guaranteedPower;

    /** Object is detected, count the number Comm retries */
    uint8_t objCommRetryCount;

    /** FOD_STATUS/Qf receive status */
    bool fodStatusQf;

    /** FOD_STATUS/Rf receive status */
    bool fodStatusRf;

    /** Inverter PWM period */
    uint32_t invPwmPeriod;

    /** Inverter PWM module */
    TCPWM_Type * invPwm;

    /** Inverter PWM index */
    uint32_t invPwmIndex;

    /** Inverter PWM enable mask */
    uint32_t invPwmMask;

    /** Delayed start interval */
    uint16_t delayStartInterval;

    /** Time taken to process an ASK packet */
    uint16_t timeToProcessAskPkt;

    /** Re-negotiation status */
    bool renegotiationStat;

    /** Configuration parameters */
    cy_stc_qi_cfg_params_t cfgParams;

    /** Power parameters */
    cy_stc_qi_pwr_params_t pwrParams;

    /** Power parameters temporary (active only during negotiation) */
    cy_stc_qi_pwr_params_t pwrParamsTemp;

    /** Authentication status */
    bool authStat;

    /** Received Authentication Events */
    uint8_t authRxEvent;

    /**Transmitted Authentication Events */
    uint8_t authTxEvent;

    /** Size of Authenticaion Event Data that needs to be Sent to Receiver */
    uint16_t authTxEventSize;

    /** Authentication Common Buffer */
    uint8_t authRxBuffer[128];

    /** Authentication Common Buffer */
    uint8_t authTxBuffer[1024];

    /** LED status */
    cy_stc_qi_led_state_t stLed;
   
    /** UART queue */
    cy_stc_ring_buf_t qiStUartRingBuf;

    uint8_t  uartRingDataBuf[SIZE_UART_RING_BUF];
    
} cy_stc_qi_status_t;

/**
 * @brief Structure to hold the Object Q factor data
 */
typedef struct {
    /** FSK edge counter module */
    TCPWM_Type * freeCounter;

    /** FSK edge counter index */
    uint32_t freeCounterIndex;

    /** FSK edge counter enable mask */
    uint32_t freeCounterMask;

    void (*cc_up_cmp_int_handler) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /** CC Up comparator interrupt handler */

    void (*cc_dn_cmp_int_handler) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /** CC Down comparator interrupt handler */

    void (*pds_scp_cmp_int_handler) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /** PDS SCP comparator interrupt handler */

    /** Q frequency */
    uint32_t qFrequency;

    /** Q factor */
    uint32_t qFactor;
    /** Q factor */
    uint32_t qFactorMPA1;

    /** Received Q factor */
    uint32_t rxdQfactor;

    /** Received reference frequency */
    uint32_t rxdRefFreq;

    /** Q high amplitude cycles count */
    uint32_t qHighPeakCount;
    
    /** Queue for storing sampled Q factor */
    cy_stc_ring_buf_t qFactorQueue;

    /** Array for Q factor queue buffer */
    uint8_t qFactorQueueDataBuf[CY_QI_Q_FACTOR_RING_BUF_MAX_SIZE];

    /** Queue for storing sampled Q peaks */
    cy_stc_ring_buf_t qPeaksQueue;

    /** Array for Q peaks queue buffer */
    uint8_t qPeaksQueueDataBuf[CY_QI_Q_FACTOR_RING_BUF_MAX_SIZE];
    
    /** Status of whether Q Factor FO detected or not */
    bool qFoDetected;

    /** Status of whether Resonant Frequency FO detected or not */
    bool fresFoDetected;

} cy_stc_qi_object_q_factor_t;


/**
 * @brief Structure to hold the Power Loss FO data
 */
typedef struct {
      
    bool isLightLoadDataReady;   /** Flag for Light load Data Ready */
    bool is2pointCalibReady;     /** Flag for running 2 point calibration */
    bool isCalibLossesReady;     /** Flag for calculating calibration losses */
    bool isFirstRppProcessed;    /** Flag to identify the first rpp packet in case of BPP Devices. */
    bool ptxCalibNotFull;        /** Flag to adjust thresholod to take of extrapolation math error */
    bool ptxCalibCorrectionSkip; /** Flag to skip loss correction approach because two points has severe errors.*/
    bool qFoSuspected;           /** Flag to skip loss correction if the q factor indicates no FO but is at a value which is doubtful */
    
    /** Flag for Light load Data Ready */
    uint8_t  calibRetryCnt;
    
    /** Flag for Light load Data Ready */
    cy_en_qi_pwr_loss_state_t state;
    
    /** Flag vBusVolt */
    uint32_t vBusVolt;    
    /** Flag vBusVolt */
    uint32_t vBusCur;
    /** Flag vBusVolt */
    uint32_t rxPwrMw;
    /** Flag vBusVolt */
    uint32_t txPwrMw;
    
    /** First RPP data for handling B2B issues in BPP devices. */
    uint32_t bppRxFirstRpp;
    /** Flag for Light load Data Ready */
    uint32_t bppTxFirstRpp;
    /** BPP B2B issues handler.... */
    int32_t bppOffset;             
    
    /**
     * 2- Point calibration data. 
     */
    float prxL;    /** RPP at light load calibration */
    float prxC;    /** RPP at light load calibration */    
    float ptxL;    /** Transmitted Power at light load calibration */
    float ptxC;    /** Transmitted Power at light load calibration */      

    /** Coefficients for linear curve - y = ax + b */
    float coeffA;
    /** Coefficients for linear curve - y = ax + b */
    float coeffB;
    
    /** Coefficients for linear curve - y = ax + b */
    float manualCalibCoeffA;
    /** Coefficients for linear curve - y = ax + b */
    float manualCalibCoeffB;
    /** Coefficients for linear curve - y = ax + b */
    float manualCalibCoeffC;
    
    /** Coefficients for linear curve - y = ax + b */
    float deltaLossCoeffA;
    /** Coefficients for linear curve - y = ax + b */
    float deltaLossCoeffB;
    
    /** Threshold */
    uint32_t threshold; 
    /** Threshold */
    uint32_t thresholdMax;
    /** Threshold */
    uint8_t assertCountMax;
    /** Threshold */
    uint8_t discontinePowerCountMax;

     /* Keeps track of FO */
    uint8_t fodCount;
    uint8_t powerCycleCount;

    uint32_t calcPwrLoss;

    uint32_t txPwrCalibMw;

    uint32_t prevFOPowLossVal;
    /** Power Loss FOD set reason */
    cy_en_qi_ploss_reasons_t pwrlossFodReason;
}cy_stc_qi_object_power_loss_t;
/**
 * @brief Structure to hold the Qi Object layer Configuration and Status.
 */
typedef struct {
    /** Object Status */
    bool object;

    /** Object Settle (not moving) status */
    bool objectStatic;

    /** Free air FOD Status */
    bool freeAirFod;

    /** FOD Status */
    bool fod;

    /** FOD EPT request */
    bool fodEptPending;

    /** Q factor data */
    cy_stc_qi_object_q_factor_t qFactor;
    
    /** Power Loss Structure */
    cy_stc_qi_object_power_loss_t powerLoss;

} cy_stc_qi_object_status_t;

/**
 * @brief Structure to hold the Qi ASK packet signature.
 */
typedef struct
{
    /** Header byte in the packet. */
    uint8_t header;

    /** Message bytes in the packet. */
    uint8_t msg[CY_QI_ASK_DATA_SIZE];

    /** Checksum for the packet. */
    uint8_t checksum;

} cy_stc_qi_ask_pkt_t;

/**
 * @brief Structure to hold the Qi Communication layer ASK Configuration.
 */
typedef struct {
    void (*cc_up_cmp_int_handler) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /** CC Up comparator interrupt handler */

    /** Event notified by BMC Module */
    cy_en_qi_ask_pkt_evt_t askPktEvent;

    /** Current ASK pkt */
    cy_stc_qi_ask_pkt_t askPkt;

    /** ASK active demodulation path */
    cy_en_qi_ask_path_t askPath;

    /** ASK path Sequence */
    cy_en_qi_ask_path_t askPathSeq[CY_QI_MAX_NUM_ASK_SWITCH_OVER];

    /** Present askPathSeq */
    cy_en_qi_ask_path_t presentAskPathSeq;

    /** ASK immediate packet error count */
    uint8_t askPktErrCnt;

    /** ASK noise or fail packet count within a CEP window. */
    uint8_t noiseFailCEPktErrCnt;

    /** CEP packet timeout delayed once due to ASK noise. */
    uint8_t askCEPTimeoutRetryCnt;

    /** ASK path change status */
    bool askPathChanged;

    /** ASK path configuration during digital ping phase status */
    bool askPathPingPhasePending;

    /** ASK Start Pending status */
    bool askStartPending;

    /** ASK path during digital ping phase */
    cy_en_qi_ask_path_t askPathPingPhase;

    /** Tnext timeout status */
    bool tNextTimeout;

    /** Tnegotiate timeout status */
    bool tNegTimeout;

    /** Ttimer timeout status */
    bool tTimerTimeout;

    /** Tpower timeout status */
    bool tPowerTimeout;

    /** Packet timeout for ASK path switch status */
    bool tPktAskSwitchTimeout;

    /** Packet timeout for ASK path switch status */
    bool tPktTimeout;

} cy_stc_qi_comm_ask_status_t;

/**
 * @brief Structure to hold the Qi Communication layer ASK Configuration.
 */
typedef struct {

    /** FSK parameters update required */
    bool updateParams;

    /** FSK completed event */
    bool pktDone;

    /** FSK capability message */
    uint8_t fskCap[CY_QI_FSK_CAP_MSG_SIZE];

    /* Infineon PTMC */
    uint8_t fskID[CY_QI_FSK_ID_MSG_SIZE];

} cy_stc_qi_comm_fsk_status_t;

/**
 * @brief Structure to hold the FSK status.
 */
typedef struct {

    /** FSK edge counter module */
    TCPWM_Type * edgeCounter;

    /** FSK edge counter index */
    uint32_t edgeCounterIndex;

    /** FSK edge counter enable mask */
    uint32_t edgeCounterMask;

    /** FSK Edge Counter IRQ Type */
    IRQn_Type edgeCounterIRQType;

    void (*edge_int_handler) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /** FSK edge interrupt handler */

    /** Operating frequency PWM clock cycles */
    uint32_t periodOpPwmCnt;

    /** Modulated frequency PWM clock cycles */
    uint32_t periodModPwmCnt;

    /** Operating frequency timer window */
    uint32_t periodOpPwmTimer;

    /** modulated frequency timer window */
    uint32_t periodModPwmTimer;

    /** Critical section timer limit for FSK edge */
    uint32_t periodPwmTimerLim;

    /** Is frame or pattern */
    bool frame;

    /** FSK data in bytes */
    uint8_t data[CY_QI_FSK_DATA_SIZE];

    /** FSK data length */
    uint8_t dataLen;

    /** FSK current data index */
    uint8_t dataIndex;

    /** FSK current bit index */
    uint8_t bitIndex;

    /** FSK edge requires frequency change */
    bool changeFreq;

    /** Required freq change is modulated or operating */
    bool isFreqMod;

    /** FSK at half bit edge */
    bool halfBit;

    /** Half bit operations completed status */
    bool halfBitDone;

} cy_stc_qi_comm_fsk_oper_t;

/**
 * @brief Structure to hold the ASK BMC decoder status.
 */
typedef struct
{
    /** SCB index to be used for BMC decoder */
    CySCB_Type * scb;

    void (*scb_int_handler) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /** SCB interrupt handler */

    void (*cmp_int_handler) (
            struct cy_stc_qi_context *qiCtx        /**< Qi context. */
            );      /** Comparator interrupt handler */

    /** Flag to indicate BMC decoder start bit detection status */
    bool startBitDet;

    /** Flag to indicate BMC decoder about DEMOD line active state */
    bool isActiveHigh;

    /** Internal flag to indicate block is initialized. */
    bool isStarted;

    /** Internal flag to indicate the PD block is scanning for RX message. */
    bool isScanning;

    /** Internal flag indicating block is actively receiving data. */
    bool isActive;

    /** Internal flag indicating BMC receive was aborted. */
    bool isAborted;

    /** Internal flag to indicate block has received a valid Qi packet. */
    bool isRcvDone;

    /** Internal flag to indicate packet decoding is completed */
    bool isDataReady;

    /** Internal state machine variable indicating the raw data count. */
    uint16_t rawDataCount;

    /** Internal state machine variable indicating raw data bit count. */
    uint16_t rawBitCount;

    /** Internal state machine variable to hold raw BMC data. */
    uint8_t rawData[CY_QI_BMC_RX_SPI_RAW_DATA_SIZE];

    /** Internal state machine variable to hold the decoded RX packet. */
    cy_stc_qi_ask_pkt_t pkt;

    /** ASK packet decode event callback */
    cy_en_qi_status_t (*cy_cb_ask_pkt_evt)(
        void * callbackContext,       /**< Context. */
        cy_en_qi_ask_pkt_evt_t pktEvt    /**< ASK packet decode event */
        );

} cy_stc_qi_comm_ask_bmc_t;

/**
 * @brief Structure to hold the Qi Communication layer Configuration and Status.
 */
typedef struct 
{
    /** ASK Status */
    bool askActive;

    /** FSK Status */
    bool fskActive;

    /** ASK Configuration */
    cy_stc_qi_comm_ask_status_t askCfg;

    /** FSK Configuration */
    cy_stc_qi_comm_fsk_status_t fskCfg;

    /** ASK BMC decoder status: internal */
    cy_stc_qi_comm_ask_bmc_t askBmc;

    /** FSK operatoin status: internal */
    cy_stc_qi_comm_fsk_oper_t fskOper;

} cy_stc_qi_comm_status_t;

typedef struct
{
    uint8_t n;          /**< Store Count for Received ADT*/

    uint8_t m;          /**< Store Count for Transmitted ADT*/

    cy_en_qi_st_13_data_transport_t dtsRxState;   /**< State variable for DTS State in Receiver Mode*/

    cy_en_qi_st_15_data_transport_t dtsTxState;   /**< State variable for DTS State in Tx Mode*/

    uint16_t dtsADCTotalLength;     /**< Total Length of Transfer for ADC Packet */ 

    uint16_t dtsADTTotalLength;     /**< Total Length of Transfer for each ADT Packet */

    uint8_t dtsADTEvenLength;     /**< Length of ADT Even packet */

    uint8_t dtsADTOddLength;      /**< Length of ADT Odd packet */

    uint8_t dtsADTBuffer[7];       /**< Copy of EVEN/ODD ADT Packet till successful transit */

} cy_stc_qi_data_stream_t;

/**
 * @brief Structure to hold the Qi Coil Power parameters.
 */
typedef struct __attribute__((__packed__))
{
    int16_t kp;         /**< Proportional gain, milli scale */

    int16_t ki;         /**< Integral gain, milli scale */

    int16_t kd;         /**< Deviation gain, milli scale */

    int16_t mi;         /**< Integral term limit, NA */

    int16_t mpid;       /**< PID output limit, NA */

    int16_t svmv;       /**< Scale factor, milli scale */
}cy_stc_qi_coil_t;

/**
 * @brief Structure to hold the Qi Power PID parameters.
 * This structure defines the Control parameters needed for manipulating the Coil Voltage
 */
typedef struct __attribute__((__packed__))
{
    /** PID loop run pending status */
    bool pidPending;

    /** Current control error */
    int8_t cep;

    /** Current control error unsigned */
    uint8_t cepUnsigned;

    /** Previous control error */
    int8_t cepPrev;

    /** Repeated CEP count */
    uint16_t cepRepeatCount;

    /** PID very low CEP condition status */
    bool cepLow;

    /** PID very high CEP condition status */
    bool cepHigh;

    /** Stable CEP status */
    bool cepStable;

    /** PID loop saturation indicator */
    bool pidSaturated;


    /** PID Calculated error in milli units */
    int16_t error;

    /** PID measured current */
    int16_t coilCurA;

    /** PID previous loop current */
    int16_t coilCurI;

    /** PID loop time interval in mS */
    int16_t loopTime;

    /** PID loop count */
    uint8_t loopCount;

    /** PID low load condition status */
    bool lowLoad;

    /** PID proportional only condition status */
    bool pidKpOnly;

    /** PID single loop condition status */
    bool pidSingleLoop;

    /** PID inverter half bridge condition status */
    bool halfBridge;

    /** PID correction skip condition status */
    bool pidAdjSkip;

    /** PID Calculated Previous integral component */
    int32_t termIntegral;

}cy_stc_qi_pid_t;

/**
 * @brief Structure to hold the Sampling task parameters.
 */
typedef struct 
{

    /** Voltage */
    uint32_t volt;

    /** Current */
    uint32_t current;

    /** Timestamp */
    uint16_t timeStamp;

    uint8_t wasAskActive;
} cy_stc_qi_sampling_parameters_t;

/**
 * @brief Structure to hold the Voltage and Current Sampling parameters.
 */
typedef struct {
    /** Timer interval value for Sampling task */
    uint16_t taskInterval;

    /** Samples which are considered during this time */
    uint16_t validSampleStartTime;
    uint16_t validSampleEndTime;

    /** Flag for actating sampling task */
    bool startSampling;
    
    /** Sampling task ring buffer */
    cy_stc_ring_buf_t ringBuf;

    uint8_t  ringDataBuf[CY_QI_VOLT_SAMPLE_RING_BUF_SIZE * sizeof(cy_stc_qi_sampling_parameters_t)];

} cy_stc_qi_sampling_t;
/**
 * @brief Structure to hold the Qi Power layer Configuration and Status.
 */
typedef struct 
{
    /** Coil Voltage Requested in mV */
    uint16_t coilVoltReq;

    /** Coil Voltage in mV */
    uint16_t coilVolt;

    /** Measured (during PID or RPP) Coil Current in mA */
    uint16_t coilCur;

    /** Coil configuration parameters */
    cy_stc_qi_coil_t coil;

    /** PID configuration parameters */
    cy_stc_qi_pid_t pid;

    /** Sampling task parameters */
    cy_stc_qi_sampling_t sampling;    

} cy_stc_qi_power_status_t;


/**
 * @brief 
 * 
 */
typedef struct
{
    /** State variable for Samsung PPDE states */
    cy_en_qi_st_samsung_ppde_t state;

    /** Samsung Mode Request Processeed status */
    bool samsungPPDEReqProcessed;

    /** Samsung Mode Active/Inactive status */
    bool samsungPPDEActive;

    /** Rx Request for Samsung PPDE mode */
    bool reqSamsungPPDE;

    /** Rx Request for Samsung feature Enable */
    bool samsungRxPPDEFeatureEnable;

}cy_stc_qi_samsung_ppde_t;

/**
 * @brief Structure to QISTACK Middleware context information.
 */
typedef struct cy_stc_qi_context
{
    /** Coil Index */
    uint8_t coilNum;

    /** Pointer to the application callback structure. */
    cy_stc_qi_app_cbk_t *ptrAppCbk;

    /** Pointer to the Configuration structure. */
    const void *ptrCfg;

    /** Qi Policy Configuration and Status structure. */
    cy_stc_qi_status_t qiStat;

    /** Object layer status structure. */
    cy_stc_qi_object_status_t qiObjectStat;

    /** Communication layer status structure. */
    cy_stc_qi_comm_status_t qiCommStat;

    /** Transport Data Stream layer status structure. */
    cy_stc_qi_data_stream_t qiDataStreamStat;

    /** Power layer status structure. */
    cy_stc_qi_power_status_t qiPowerStat;
    
    /** Samsung PPDE Status Structure */
    cy_stc_qi_samsung_ppde_t qiSamsungStat;

    /** Pointer to the USBPD0 PDL context information. */
    cy_stc_usbpd_context_t *ptrUsbPd0Context;

    /** Pointer to the USBPD1 PDL context information. */
    cy_stc_usbpd_context_t *ptrUsbPd1Context;

    /** Stack Timer Context */
    cy_stc_sw_timer_t *ptrTimerContext;
} cy_stc_qi_context_t;

/** \} group_qistack_enums */

/**
* \addtogroup group_qistack_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_QiStack_PTx_EPT
****************************************************************************//**
*
* This function re-starts the Qi stack policy with new policy information.
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \param waitForObjectRemove
* Power transfer restart or wait for object removal.
*
* \return
* CY_QISTACK_STAT_SUCCESS if operation is successful
* CY_QISTACK_STAT_BAD_PARAM if the context pointer is invalid
* CY_QISTACK_STAT_FAILURE if the operation fails.
*
*******************************************************************************/
cy_en_qi_status_t Cy_QiStack_PTx_EPT(
       cy_stc_qi_context_t *qiCtx,
       bool waitForObjectRemove);

/*******************************************************************************
* Function Name: Cy_QiStack_LED_State_Set
****************************************************************************//**
*
* This function sets requested LED state for Qi policy.
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \param ledState
* LED state.
*
* \return
* None
*
*******************************************************************************/
void Cy_QiStack_LED_State_Set(
       cy_stc_qi_context_t *qiCtx,
       cy_en_qi_led_state_t ledState);

/*******************************************************************************
* Function Name: Cy_QiStack_Fo_Status_Set
****************************************************************************//**
*
* This function sets FOD status.
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \param status
* QiStack FOD status.
*
* \return
* None.
*******************************************************************************/
void Cy_QiStack_Fo_Status_Set(cy_stc_qi_context_t *qiCtx, bool status);

/*******************************************************************************
* Function Name: Cy_Console_Printf
********************************************************************************
*
* This function converts the passed parameters into string and loads this
* UART string into ring buffer
*
* \param verbosity
* Verbosity level
*
* \param message
* Message to be printed on console
*
* \return
* Returns if the passing parameters are within max length
*
*******************************************************************************/
bool Cy_Console_Printf(cy_stc_qi_context_t *qiCtx, cy_en_qi_uart_verbosity_level_t verbosity,
        char *message,
        ...);

/*******************************************************************************
* Function Name: Cy_QiStack_Fsk_Ack
******************************************************************************
*
* This function sends FSK ACK
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* None.
*
*******************************************************************************/
void Cy_QiStack_Fsk_Ack(cy_stc_qi_context_t *qiCtx);

/*******************************************************************************
* Function Name: Cy_QiStack_Fsk_Nack
******************************************************************************
*
* This function sends FSK NACK
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* None.
*
*******************************************************************************/
void Cy_QiStack_Fsk_Nack(cy_stc_qi_context_t *qiCtx);

/*******************************************************************************
* Function Name: Cy_QiStack_Fsk_Nd
******************************************************************************
*
* This function sends FSK Not defined/recognized data
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* None.
*
*******************************************************************************/
void Cy_QiStack_Fsk_Nd(cy_stc_qi_context_t *qiCtx);

/*******************************************************************************
* Function Name: Cy_QiStack_Fsk_Null
******************************************************************************
*
* This function sends FSK Null (no data)
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* None.
*
*******************************************************************************/
void Cy_QiStack_Fsk_Null(cy_stc_qi_context_t *qiCtx);

/*******************************************************************************
* Function Name: Cy_QiStack_Fsk_Id
******************************************************************************
*
* This function sends FSK PTx ID
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* None.
*
*******************************************************************************/
void Cy_QiStack_Fsk_Id(cy_stc_qi_context_t *qiCtx);


/**
 * @brief Helper function to send Attention
 * 
 * @param qiCtx 
 */
void Cy_QiStack_Fsk_Atn(cy_stc_qi_context_t *qiCtx);

/*******************************************************************************
* Function Name: Cy_QiStack_Fsk_Cap
******************************************************************************
*
* This function sends FSK PTx Capability
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* None.
*
*******************************************************************************/
void Cy_QiStack_Fsk_Cap(cy_stc_qi_context_t *qiCtx);



/**
 * @brief 
 * 
 */
void Cy_QiStack_Fsk_ADC(cy_stc_qi_context_t *qiCtx, uint8_t request, uint16_t param);


/**
 * @brief 
 * 
 * @param qiCtx 
 * @param data 
 * @param type 
 * @param size 
 */
void Cy_QiStack_Fsk_ADT(cy_stc_qi_context_t *qiCtx, uint8_t *data, uint8_t type, uint8_t size);


/**
 * @brief Used for Sending Samsung FSK ACK Sequence
 * 
 * @param qiCtx 
 */
void Cy_QiStack_Fsk_SamsungAck(cy_stc_qi_context_t *qiCtx);

/** \} group_qistack_functions */

#endif /* CY_QISTACK_COMMON_H */

/* [] END OF FILE */
