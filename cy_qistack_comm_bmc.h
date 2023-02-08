/***************************************************************************//**
* \file cy_qistack_comm_bmc.h
* \version 2.0
*
* Header file of Qi BMC decoder of the QiStack middleware.
*
********************************************************************************
* \copyright
* Copyright 2022-2023, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_QISTACK_COMM_BMC_H
#define CY_QISTACK_COMM_BMC_H

#include "cy_qistack_common.h"

/*******************************************************************************
*                              Type Definitions
*******************************************************************************/

/**
* \addtogroup group_qistack_comm_macros
* \{
*/

/** USBPD block to be used as BMC RX */
#define CY_QI_BMC_USBPD_RX_PORT                     (PDSS1)

/** Minimum number of preambles required to consider packet valid. */
#define CY_QI_BMC_RX_MIN_PREAMBLE_COUNT             (4u)

/**
 * Minimum number of bits in data to consider packet valid.
 * 4 preamble bits, header, one data, one checksum byte.
 * Each byte has a start bit, 8 data bits, 1 parity bit and 1 stop bit.
 * 4 + 3 * (1 + 8 + 1 + 1) = 37
 */
#define CY_QI_BMC_RX_PACKET_MIN_BIT_COUNT           (37u)

/**
 * Minimum number of bits in data to consider start of packet valid.
 * Since we are doing only post processing, we need to see if this
 * was noise or was real packet. If this is real packet, then there
 * needs to be preamble + at least one byte of data. So,
 * 4 preamble bits + start of packet + 8 bits + parity bit + stop bit.
 * 4 + 1 = 5
 */
#define CY_QI_BMC_RX_START_PACKET_MIN_BIT_COUNT     (15u)

/**
 * Minimum preamble bits count to be sent by PRx.
 */
#define CY_QI_BMC_RX_PREAMBLE_MIN_BIT_COUNT_PRX     (11u)

/**
 * Start of packet toggle timeout in us. 
 * Since the delay loop itself introduces additional delay than 1us,
 * effective loop count is 2.6us. To acheive ~300us delay, you need
 * to scale time. So a simpler scaled number is used here instead.
 * 125 loop count gives ~325us which is sufficiently higher than
 * one half cycle of data bit.
 */
#define CY_QI_BMC_RX_PACKET_START_TIMEOUT_US        (125u)

#if ((CY_QI_BMC_RX_BIT_SPI_OVER_SAMPLE != 8u) && (CY_QI_BMC_RX_BIT_SPI_OVER_SAMPLE != 16u))
#error "Unsupported SPI over sample rate. Only 8 or 16 supported."
#endif

/*
 * Assuming a preamble of 25 bits, (1 + 27 + 1) bytes at 11 bits per byte, there
 * will be about 44 bytes. Since we do not get to stop at the exact boundary, 
 * assuming 64 byte buffer is sufficent to hold all possible raw input.
 * Each byte is stored in 8X scale or 16X scale.
 */
#define CY_QI_BMC_RX_SPI_RAW_DATA_SIZE    (64u * (CY_QI_BMC_RX_BIT_SPI_OVER_SAMPLE))

#if (CY_QI_BMC_RX_BIT_SPI_OVER_SAMPLE > 8u)
/*
 * SPI FIFO trigger threshold for watermark interrupt. For the initial part,
 *  until start bit is detected, do faster collection to do early detection of
 *  noise.
 */
#define CY_QI_BMC_RX_SPI_FIFO_MIN_THRESHOLD         (2u)
#define CY_QI_BMC_RX_SPI_FIFO_THRESHOLD             (4u)
/** SPI FIFO size. */
#define CY_QI_BMC_RX_SPI_FIFO_SIZE                  (8u)
/* Minimum samples for zero detection */
#define CY_QI_BMC_RX_ZERO_MIN_COUNT                 (CY_QI_BMC_RX_BIT_SPI_OVER_SAMPLE - 5u)
#else
/** SPI FIFO trigger threshold for watermark interrupt. */
#define CY_QI_BMC_RX_SPI_FIFO_MIN_THRESHOLD         (2u)
#define CY_QI_BMC_RX_SPI_FIFO_THRESHOLD             (2u)
/** SPI FIFO size. */
#define CY_QI_BMC_RX_SPI_FIFO_SIZE                  (16u)
/* Minimum samples for zero detection */
#define CY_QI_BMC_RX_ZERO_MIN_COUNT                 (CY_QI_BMC_RX_BIT_SPI_OVER_SAMPLE - 2u)
#endif

/** Get bit from raw data. */
#define CY_QI_BMC_RX_RAW_DATA_GET_BIT(ptr,pos)      ((((ptr)[(pos) >> 3u] >> ((pos) & 0x7u))) & 0x01u

/** \} group_qistack_comm_macros */

/**
* \addtogroup group_qistack_comm_enums
* \{
*/

/** \} group_qistack_comm_enums */

/**
* \addtogroup group_qistack_comm_structures
* \{
*/

/** \} group_qistack_comm_structures */

/**
* \addtogroup group_qistack_comm_bmc_functions
* \{
*/
/*
 * Initialize and start the BMC RX state machine.
 */
void bmc_rx_init(cy_stc_qi_context_t *qiCtx,
           cy_cb_ask_pkt_evt_t cbk);

/*
 * Start scanning for packet. The function shall look for a toggle on the incoming
 * envolope detector. It uses internal filter on CC line to eliminate small noise.
 */
void bmc_rx_start_scan(cy_stc_qi_context_t *qiCtx);

/*
 * Abort and stop scanning for BMC packet. This can be used to disable receiver
 * to prevent wrong detection from happening based on stack operation.
 */
void bmc_rx_stop_scan(cy_stc_qi_context_t *qiCtx);

/*
 * Returns bmc packet status with packet data.
 */
bool bmc_rx_get_packet(cy_stc_qi_context_t *qiCtx, 
              cy_stc_qi_ask_pkt_t * pkt);

/*
 * Ideally the function need to be expanded to not decode from interrupt handler.
 * The task handler is expected to run from main task loop and provide decoded data
 * to Qi stack via a callback from here.
 */
void bmc_rx_task(cy_stc_qi_context_t *qiCtx);

/*
 * BMC Callback to Communication manager for handling events
 */
cy_en_qi_status_t Cy_Cb_BMC_Event(void *callbackContext,cy_en_qi_ask_pkt_evt_t pktEvt);

/** \} group_qistack_comm_bmc_functions */

#endif /* CY_QISTACK_COMM_BMC_H */

/* [] END OF FILE */
