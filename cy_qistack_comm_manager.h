/***************************************************************************//**
* \file cy_qistack_comm_manager.h
* \version 1.0
*
* Header file of Qi Communication Manager of the QiStack middleware.
*
********************************************************************************
* \copyright
* Copyright 2021-2022, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_QISTACK_COMM_MANAGER_H
#define CY_QISTACK_COMM_MANAGER_H

#include "cy_qistack_common.h"

/*******************************************************************************
*                              Type Definitions
*******************************************************************************/

/**
* \addtogroup group_qistack_comm_macros
* \{
*/

/** FSK maximum data size */
#define CY_QI_FSK_DATA_MAX_SIZE                     (10u)

/** FSK depth setting */
#define CY_QI_FSK_RESOLUTION_DEPTH_0                (2u)
#define CY_QI_FSK_RESOLUTION_DEPTH_1                (4u)
#define CY_QI_FSK_RESOLUTION_DEPTH_2                (7u)
#define CY_QI_FSK_RESOLUTION_DEPTH_3                (13u)

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
* \addtogroup group_qistack_comm_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_QiStack_Comm_Init
****************************************************************************//**
*
* This function initializes the Qi communication manager.
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* CY_QISTACK_STAT_SUCCESS if operation is successful
* CY_QISTACK_STAT_BAD_PARAM if the input parameters are not valid
*
*******************************************************************************/
cy_en_qi_status_t Cy_QiStack_Comm_Init(
       /* Pointer to the qistack context. */
       cy_stc_qi_context_t *qiCtx);

/*******************************************************************************
* Function Name: Cy_QiStack_Comm_Stop
****************************************************************************//**
*
* This function stops the Qi communication manager.
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* CY_QISTACK_STAT_SUCCESS if operation is successful
* CY_QISTACK_STAT_BAD_PARAM if the input parameters are not valid
*
*******************************************************************************/
cy_en_qi_status_t Cy_QiStack_Comm_Stop(
       /* Pointer to the qistack context. */
       cy_stc_qi_context_t *qiCtx);

/*******************************************************************************
* Function Name: Cy_QiStack_Comm_Start
******************************************************************************
*
* This function starts the Qi communication manager.
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* CY_QISTACK_STAT_SUCCESS if operation is successful
* CY_QISTACK_STAT_BAD_PARAM if the input parameters are not valid
*
*******************************************************************************/
cy_en_qi_status_t Cy_QiStack_Comm_Start(
       /* Pointer to the qistack context. */
       cy_stc_qi_context_t *qiCtx);

/*******************************************************************************
* Function Name: Cy_QiStack_Comm_Reset
****************************************************************************//**
*
* This function resets the Qi communication manager.
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* CY_QISTACK_STAT_SUCCESS if operation is successful
* CY_QISTACK_STAT_BAD_PARAM if the input parameters are not valid
*
*******************************************************************************/
cy_en_qi_status_t Cy_QiStack_Comm_Reset(
       /* Pointer to the qistack context. */
       cy_stc_qi_context_t *qiCtx);

/*******************************************************************************
* Function Name: Cy_QiStack_Comm_Task
******************************************************************************
*
* This function runs the Qi communication manager tasks.
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* CY_QISTACK_STAT_SUCCESS if operation is successful
* CY_QISTACK_STAT_BAD_PARAM if the input parameters are not valid
*
*******************************************************************************/
cy_en_qi_status_t Cy_QiStack_Comm_Task(
       /* Pointer to the qistack context. */
       cy_stc_qi_context_t *qiCtx);

/*******************************************************************************
* Function Name: Cy_QiStack_Comm_Ask_Config
******************************************************************************
*
* This function initiaizes ASK demodulation path for digtal ping phase.
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* CY_QISTACK_STAT_SUCCESS if operation is successful
* CY_QISTACK_STAT_BAD_PARAM if the input parameters are not valid
*
*******************************************************************************/
cy_en_qi_status_t Cy_QiStack_Comm_Ask_Config(
       /* Pointer to the qistack context. */
       cy_stc_qi_context_t *qiCtx);

/*******************************************************************************
* Function Name: Cy_QiStack_Ask_Mod_Update
******************************************************************************
*
* This function updates the ASK decode path as per sequence.
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* None.
*
*******************************************************************************/
void Cy_QiStack_Ask_Mod_Update(
       /* Pointer to the qistack context. */
       cy_stc_qi_context_t *qiCtx);

/**
 * @brief Function to check given Packet is Reserved on Not
 * 
 * @param header 
 * @return true 
 * @return false 
 */
bool Cy_QiStack_Is_Packet_Reserved(uint8_t header);

/**
 * @brief Reset Data Transport Layer
 * 
 * @param qiCtx 
 */
void Cy_QiStack_DTS_Reset(cy_stc_qi_context_t *qiCtx);


/** \} group_qistack_comm_functions */

#endif /* CY_QISTACK_COMM_MANAGER_H */

/* [] END OF FILE */
