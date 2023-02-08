/***************************************************************************//**
* \file cy_qistack_object_manager.h
* \version 2.0
*
* Header file of Qi Object (FO and/or PRx) Manager of the QiStack middleware.
*
********************************************************************************
* \copyright
* Copyright 2022-2023, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_QISTACK_OBJECT_MANAGER_H
#define CY_QISTACK_OBJECT_MANAGER_H

#include "cy_qistack_common.h"

/*******************************************************************************
*                              Type Definitions
*******************************************************************************/

/**
* \addtogroup group_qistack_object_macros
* \{
*/

/** USBPD block to be used for Q factor measurement */
#define CY_QI_Q_FACTOR_USBPD_PORT                       (PDSS1)

/* Frequency counter offset, keep signed */
#define CY_QI_Q_FREQ_ZCD_COUNTER_OFFSET                 (0)

/* Maximum Q Factor deviation */
#define CY_QI_Q_FACTOR_DEVIATION_MAX                    (4u)

/* Maximum Q peaks deviation */
#define CY_QI_Q_PEAKS_DEVIATION_MAX                     (3u)

/* Q calibration macros, keep signed */
#define CY_QI_Q_REF_MIN                                 (25)
#define CY_QI_Q_REF_MAX                                 (200)
#define CY_QI_Q_BPP_THRES_PER                           (30) /* 'x' percentage of free air Q */   

#define CY_QI_VALID_Q_FAC_RING_BUF_DATA_COUNT           (1u)

/* Resonant Frequency helper macro */
#define CY_QI_RES_FREQ_SCALED_FREQ(x)                   (((x) * (get_wireless_fod_config(qiCtx->ptrCfg, qiCtx->coilNum)->resFreqScaleFactor)) / 1000)

/* % of threshold where possible Q Fod suspected */
#define CY_QI_Q_FO_SUSPECT_THR                          (8u)

/* Value used for percentage calculations  */
#define PERCENTAGE_CONVERSION_VAL                       (100u)

/** \} group_qistack_object_macros */

/**
* \addtogroup group_qistack_object_enums
* \{
*/

/** \} group_qistack_object_enums */

/**
* \addtogroup group_qistack_object_structures
* \{
*/

/** \} group_qistack_object_structures */

/**
* \addtogroup group_qistack_object_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_QiStack_Object_Init
****************************************************************************//**
*
* This function initializes the Qi object manager.
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* CY_QISTACK_STAT_SUCCESS if operation is successful
* CY_QISTACK_STAT_BAD_PARAM if the input parameters are not valid
*
*******************************************************************************/
cy_en_qi_status_t Cy_QiStack_Object_Init(
       /* Pointer to the qistack context. */
       cy_stc_qi_context_t *qiCtx);

/*******************************************************************************
* Function Name: Cy_QiStack_Object_Reset
****************************************************************************//**
*
* This function resets the Qi object manager.
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* CY_QISTACK_STAT_SUCCESS if operation is successful
* CY_QISTACK_STAT_BAD_PARAM if the input parameters are not valid
*
*******************************************************************************/
cy_en_qi_status_t Cy_QiStack_Object_Reset(
       /* Pointer to the qistack context. */
       cy_stc_qi_context_t *qiCtx);

/*******************************************************************************
* Function Name: Cy_QiStack_Object_Task
****************************************************************************//**
*
* This function runs the Qi object manager tasks.
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* CY_QISTACK_STAT_SUCCESS if operation is successful
* CY_QISTACK_STAT_BAD_PARAM if the input parameters are not valid
*
*******************************************************************************/
cy_en_qi_status_t Cy_QiStack_Object_Task(
       /* Pointer to the qistack context. */
       cy_stc_qi_context_t *qiCtx);

/*******************************************************************************
* Function Name: Cy_QiStack_Object_Q_Factor_Measure
****************************************************************************//**
*
* This function starts the Q factor measurement for object.
* Q factor measure also initiates analog pings and stays in critical section
* until Q factor measurement is completed.
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* CY_QISTACK_STAT_SUCCESS if operation is successful
* CY_QISTACK_STAT_BAD_PARAM if the input parameters are not valid
*
*******************************************************************************/
cy_en_qi_status_t Cy_QiStack_Object_Q_Factor_Measure(
       /* Pointer to the qistack context. */
       cy_stc_qi_context_t *qiCtx);

/*******************************************************************************
* Function Name: Cy_QiStack_Object_Check_Q_Factor_Status
****************************************************************************//**
*
* This function analyzes measured Q against reference Q.
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \param fodSupportData
* QiStack Reference Q to compare against. If no reference, pass 0.
*
* \return
* CY_QI_FOD_STAT_ERROR if analysis error
* CY_QI_FOD_STAT_FO if analysis success and FO present
* CY_QI_FOD_STAT_NO_FO if analysis success and no FO present
*******************************************************************************/
cy_en_qi_fod_stat_t Cy_QiStack_Object_Check_Q_Factor_Status(
       cy_stc_qi_context_t *qiCtx, 
       uint32_t fodSupportData);

/*******************************************************************************
* Function Name: Cy_QiStack_Object_Check_Res_Freq_Status
****************************************************************************//**
*
* This function analyzes measured Resonance Frequency against reference frequency.
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \param fodSupportData
* QiStack Reference frequency (in Hz) to compare against. If no reference, pass 0.
*
* \return
* CY_QI_FOD_STAT_ERROR if analysis error
* CY_QI_FOD_STAT_FO if analysis success and FO present
* CY_QI_FOD_STAT_NO_FO if analysis success and no FO present
*******************************************************************************/
cy_en_qi_fod_stat_t Cy_QiStack_Object_Check_Res_Freq_Status(
       cy_stc_qi_context_t *qiCtx, 
       uint32_t fodSupportData);

/*******************************************************************************
* Function Name: Cy_QiStack_Validate_Calib_Data
****************************************************************************//**
*
* This function validates the calibration data
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \param
*
* \return
* None.
*******************************************************************************/
void Cy_QiStack_Validate_Calib_Data(cy_stc_qi_context_t *qiCtx);

/** \} group_qistack_object_functions */

#endif /* CY_QISTACK_OBJECT_MANAGER_H */

/* [] END OF FILE */
