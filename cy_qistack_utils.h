/***************************************************************************//**
* \file cy_qistack_utils.h
* \version 1.0
*
* Provides Utilities Header File of the QiStack middleware.
*
*
********************************************************************************
* \copyright
* Copyright 2021-2022, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_QISTACK_UTILS_H
#define CY_QISTACK_UTILS_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/*******************************************************************************
*                              Type Definitions
*******************************************************************************/

/**
* \addtogroup group_qistack_utils_macros
* \{
*/

/** Get higher nibble of a byte. */
#define GET_HIGHER_NIBBLE(x)                (((x) & (0xF0u)) >> (4u))

/** Get lower nibble of a byte. */
#define GET_LOWER_NIBBLE(x)                 ((x) & (0x0Fu))

/** Get higher byte of a half word. */
#define GET_HIGHER_BYTE(x)                  (((x) & (0xFF00u)) >> (8u))

/** Get lower byte of a half word. */
#define GET_LOWER_BYTE(x)                   ((x) & (0xFFu))

/**<  Get the maximum from among two numbers. */
#define GET_MAX(a,b)                        (((a) > (b)) ? (a) : (b))

/**<  Get the minimum from among two numbers. */
#define GET_MIN(a,b)                        (((a) > (b)) ? (b) : (a))

/**< Divider with ceil consideration */
#define DIV(nume, denom)                    (((nume) + ((denom) >> 1)) / (denom))

/**< Unsigned difference */
#define CY_QI_GET_DIFF_U(a,b)               (((a) > (b)) ? ((a) - (b)) : ((b) - (a)))

/**< Make 16 bit from two 8 bit data */
#define MAKE_WORD(hi,lo)                    (((uint16_t)(hi) << 8) | ((uint16_t)(lo)))

/**
 * @brief Combine four bytes to create one 32-bit DWORD.
 */
#define MAKE_DWORD(b3,b2,b1,b0)                         \
    (((uint32_t)(b3) << 24) | ((uint32_t)(b2) << 16) |  \
     ((uint32_t)(b1) << 8) | ((uint32_t)(b0)))

/* Maximum value of 32 bit */
#define CY_QI_VAL_INVALID                 (0xFFFFFFFFu)

/** \} group_qistack_utils_macros */


/**
* \addtogroup group_qistack_util_enums
* \{
*/

/**
 * @brief Enum for Console Prints
 * 
 */
typedef enum 
{
    CY_QI_UART_VERBO_LVL_CRITICAL = 0,  /**< Critical messages like fatal errors, system errors, faults, and high priority events. */
    CY_QI_UART_VERBO_LVL_MESSAGE,       /**< Vital messages like Qi events, PD events etc. without any values or data */
    CY_QI_UART_VERBO_LVL_DATA,          /**< Additional required data for vital messages */
    CY_QI_UART_VERBO_LVL_AUTOMATION,    /**< Automation debug logs */
    CY_QI_UART_VERBO_LVL_DEBUG_LV1,     /**< Debug level 1 messages to be printed for validation */
    CY_QI_UART_VERBO_LVL_DEBUG_LV2,     /**< Temporary Debug level 2 messages to be printed while debugging */
    CY_QI_UART_VERBO_LVL_CUSTOMER_LV1,  /**< Customer level 1 to be enabled by user */
    CY_QI_UART_VERBO_LVL_CUSTOMER_LV2   /**< Customer level 2 to be enabled by user */
} cy_en_qi_uart_verbosity_level_t;

/**
 * @brief Structure to QISTACK Ring buf
 */
typedef struct cy_stc_ring_buf
{
    /** Pointer to Ring buffer */
    uint8_t *ptrBuf;

    /** Size of the buffer */
    uint16_t bufSize;
    
    /** Size of a Single data */
    uint8_t eachDataSize;

    /** Ring buffer head */
    uint16_t head;

    /** Ring buffer tail */
    uint16_t tail;

    /** Ring buffer data count */
    uint16_t count;
} cy_stc_ring_buf_t;

/** \} group_qistack_util_enums */

/**
* \addtogroup group_qistack_utils_functions
* \{
*/

/*******************************************************************************
* Function Name: cy_get_odd_parity
********************************************************************************
*
* This function returns Get odd parity of a byte
*
* \param data
* data for calculating parity byte
*
* \return
* Parity bit
*
*******************************************************************************/
bool cy_get_odd_parity(uint8_t data);

/*******************************************************************************
* Function Name: cy_calc_checksum
********************************************************************************
*
* This function calculates the checksum for buffer
*
* \param buff
* pointer to the data buffer for checksum calcualtion
*
* \param size
* size of the data
*
* \param checksum
* Pointer to hold the checksum value
*
* \return
* The difference value
*
*******************************************************************************/
bool cy_calc_checksum(uint8_t * buff, uint8_t size, uint8_t * checksum);

/*******************************************************************************
* Function Name: cy_apply_threshold
********************************************************************************
*
* This function adds a Percentage to given value
*
* \param val
* value considered for the threshold calculation
*
* \param percentage
* Percentage of threshold
*
* \return
* calculated threshold value
*
*******************************************************************************/
int32_t cy_apply_threshold(int32_t val, int8_t percentage);

/*******************************************************************************
* Function Name: cy_value_in_range
********************************************************************************
*
* This function returns the range check, both positive and negative
*
* \param val
* Value to be checked
*
* \param ref
* reference value
*
* \param per
* percentage value
*
* \return
* TRUE - If it is within the range
* FALSE - If it is not in the range
*
*******************************************************************************/
bool cy_value_in_range(uint32_t val, uint32_t ref, uint8_t per);

/*******************************************************************************
* Function Name: cy_get_counter_diff
********************************************************************************
*
* This function returns the difference between two counter value by considering
* the 16-bit rollover
*
* \param counter_start
* counter start value
*
* \param counter_end
* counter end value
*
* \return
* The difference value
*
*******************************************************************************/
uint32_t cy_get_counter_diff (uint32_t counter_start, uint32_t counter_end);

/*******************************************************************************
* Function Name: Cy_RingBuf_Init
********************************************************************************
*
* This function initializes the ring buffer
*
* \param ptrRingBuf
* Pointer to ring buffer structure
*
* \param buf
* Pointer to Buffer which can store the data
*
* \param size
* Size of the Buffer
*
* \return
* None
*
*******************************************************************************/
void Cy_RingBuf_Init(cy_stc_ring_buf_t* ptrRingBuf, uint8_t* buf, uint8_t dataSize, uint16_t bufSize);

/*******************************************************************************
* Function Name: Cy_RingBuf_Flush
********************************************************************************
*
* This function flushes out the passed ring buffer
*
* \param ptrRingBuf
* Pointer to ring buffer structure
*
* \return
* None
*
*******************************************************************************/
void Cy_RingBuf_Flush(cy_stc_ring_buf_t* ptrRingBuf);

/*******************************************************************************
* Function Name: Cy_RingBuf_IsEmpty
********************************************************************************
*
* This function returs the status whether the ring buffer is empty or not
*
* \param ptrRingBuf
* Pointer to ring buffer structure
*
* \return
* true if ring buffer is empty
* false if ring buffer is having atleast a data
*
*******************************************************************************/
bool Cy_RingBuf_IsEmpty(cy_stc_ring_buf_t* ptrRingBuf);

/*******************************************************************************
* Function Name: Cy_RingBuf_IsFull
********************************************************************************
*
* This function returs the status whether the ring buffer is full or not
*
* \param ptrRingBuf
* Pointer to ring buffer structure
*
* \return
* true if ring buffer is full
* false if ring buffer is not full
*
*******************************************************************************/
bool Cy_RingBuf_IsFull(cy_stc_ring_buf_t* ptrRingBuf);

/*******************************************************************************
* Function Name: Cy_RingBuf_DataCount
********************************************************************************
*
* This function returs the status whether the ring buffer is full or not
*
* \param ptrRingBuf
* Pointer to ring buffer structure
*
* \return
* No of data available in the ring buffer
*
*******************************************************************************/
uint8_t Cy_RingBuf_DataCount(cy_stc_ring_buf_t* ptrRingBuf);

/*******************************************************************************
* Function Name: Cy_RingBuf_DataCount
********************************************************************************
*
* This function flushes out the data from ring buffer for the no of count
*
* \param ptrRingBuf
* Pointer to ring buffer structure
*
* \param flushCount
* No of flush count
*
* \return
* None
*
*******************************************************************************/
void Cy_RingBuf_FlushLastIn(cy_stc_ring_buf_t* ptrRingBuf, uint8_t flushCount);

/*******************************************************************************
* Function Name: Cy_RingBuf_Get
********************************************************************************
*
* This function returns the First In data from ring buffer
*
* \param ptrRingBuf
* Pointer to ring buffer structure
*
* \return
* true if the data is retrieved successfully 
* false if there is a failure in retrieving
*
*******************************************************************************/
bool Cy_RingBuf_Get(cy_stc_ring_buf_t* ptrRingBuf, uint8_t *destBuf);

/*******************************************************************************
* Function Name: Cy_RingBuf_GetLatest
********************************************************************************
*
* This function returns the Last In data from ring buffer, however without 
* clearing it from the ring buffer
*
* \param ptrRingBuf
* Pointer to ring buffer structure
*
* \return
* Returns the value read from ring buffer and also if the read was successful
* or not.
*
*******************************************************************************/
bool Cy_RingBuf_GetLatest(cy_stc_ring_buf_t* ptrRingBuf, uint8_t *destBuf, uint8_t index);

/*******************************************************************************
* Function Name: Cy_RingBuf_Put
********************************************************************************
*
* This function add the passed data into the ring buffer
*
* \param ptrRingBuf
* Pointer to ring buffer structure
*
* \param data
* Data to keep in the ring buffer
*
* \return
* None
*
*******************************************************************************/
void Cy_RingBuf_Put(cy_stc_ring_buf_t* ptrRingBuf, uint8_t *data);


/*******************************************************************************
* Function Name: Cy_RingBuf_Put_Ex
********************************************************************************
*
* This function add the passed data into the ring buffer without overwriting old 
* data
*
* \param ptrRingBuf
* Pointer to ring buffer structure
*
* \param data
* Data to keep in the ring buffer
*
* \return
* None
*
*******************************************************************************/
void Cy_RingBuf_Put_Ex(cy_stc_ring_buf_t* ptrRingBuf, uint8_t *data);

/*******************************************************************************
* Function Name: Cy_RingBuf_GetMin
********************************************************************************
*
* This function returns the min value present in the ring buffer
*
* \param ptrRingBuf
* Pointer to ring buffer structure
*
* \return
* Returns the least value from ring buffer
*
*******************************************************************************/
uint8_t Cy_RingBuf_GetMin_Uint8(cy_stc_ring_buf_t* ptrRingBuf);

/*******************************************************************************
* Function Name: Cy_RingBuf_GetMax
********************************************************************************
*
* This function returns the max value present in the ring buffer
*
* \param ptrRingBuf
* Pointer to ring buffer structure
*
* \return
* Returns the maximum value from ring buffer
*
*******************************************************************************/
uint8_t Cy_RingBuf_GetMax_Uint8(cy_stc_ring_buf_t* ptrRingBuf);

/** \} group_qistack_utils_functions */

#endif /* CY_QISTACK_UTILS_H */

/* [] END OF FILE */
