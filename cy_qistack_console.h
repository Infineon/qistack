/***************************************************************************//**
* \file cy_qistack_console.h
* \version 1.0
*
* Header file of Qi Debug logger.
*
********************************************************************************
* \copyright
* Copyright 2021-2022, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef QISTACK_DEVELOP_CY_QISTACK_CONSOLE_H_
#define QISTACK_DEVELOP_CY_QISTACK_CONSOLE_H_

#include "cy_usbpd_config_table.h"
#include "cy_qistack_common.h"
#include <stdarg.h>


/**
* \addtogroup group_qistack_console_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_Console_RingBuf_Init
******************************************************************************
*
* This function initiaizes ring buffer used for UART Console
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* None
*
*******************************************************************************/
void Cy_Console_RingBuf_Init(cy_stc_qi_context_t *qiCtx);

/** \} group_qistack_console_functions */

#endif /* QISTACK_DEVELOP_CY_QISTACK_CONSOLE_H_ */

/* [] END OF FILE */
