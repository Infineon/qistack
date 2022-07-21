/***************************************************************************//**
* \file cy_qistack_power_manager.h
* \version 1.0
*
* Header file of Qi Power Manager of the QiStack middleware.
*
********************************************************************************
* \copyright
* Copyright 2021-2022, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_QISTACK_POWER_MANAGER_H
#define CY_QISTACK_POWER_MANAGER_H

#include "cy_qistack_common.h"

/*******************************************************************************
*                              Type Definitions
*******************************************************************************/

/**
* \addtogroup group_qistack_power_macros
* \{
*/

/** Coil current number of samples for average. */
#define QI_COIL_CUR_AVG_SAMPLES           (5)

/** Coil Kp value for low load at 10x scale. Write 10 if intended value is 1. */
#define QI_COIL_KP_LOW_LOAD               (200)

/** Coil Kp value for high CEP at 10x scale. Write 10 if intended value is 1. */
#define QI_COIL_KP_CEP_H                  (100)

/** Coil Kp value for low CEP at 10x scale. Write 10 if intended value is 1. */
#define QI_COIL_KP_CEP_L                  (0)

/** PID thresholds */
#define QI_PID_CONTROL_ERROR_DIV          (128)
#define QI_PID_REG_VOLT_UNIT_MV           (20)
#define QI_PID_REG_CUR_UNIT_MA            (50)
#define QI_PID_REG_CUR_MIN_VAL_MA         (50)
#define QI_PID_REG_CUR_HYS_MA             (50)
#define QI_PID_CEP_H_U                    (30u)
#define QI_PID_CEP_L_U                    (10u)
#define QI_PID_CEP_REPEAT_CNT             (10u)
#define QI_PID_CEP_STABLE_THRESHOLD_VAL   (10)
#define QI_PID_REG_VOLT_CHNG_MAX_MV       (1000u)

/** PID loop configuration */
#define QI_TIMER_PID_LOOP_MS              (2u)
#define QI_TIMER_PID_LOOP_CYCLES          (2u)
#define QI_TIMER_PID_CEP_H_LOOP_MS        (2u)
#define QI_TIMER_PID_CEP_H_LOOP_CYCLES    (1u)

/* 
 * HB and FB switch levels. FB switch level has 
 * to be atleast more than double of HB level,
 * with some hysteresis.
 */
#define QI_COIL_REG_HB_SS_THRES             (150)
#define QI_COIL_REG_HB_ENTER_VOLT_MV        (3300)
#define QI_COIL_REG_HB_TARGET_VOLT_MV       ((QI_COIL_REG_HB_ENTER_VOLT_MV) * (2))
#define QI_COIL_REG_HB_HYS_MV               (1000)
#define QI_COIL_REG_HB_EXIT_VOLT_MV         (((QI_COIL_REG_HB_ENTER_VOLT_MV) * (2)) + ((QI_COIL_REG_HB_HYS_MV) * (2))) 
#define QI_COIL_REG_FB_TARGET_VOLT_MV       (QI_COIL_REG_HB_ENTER_VOLT_MV + QI_COIL_REG_HB_HYS_MV)

/**
 * Additional RPx load supported on top of negotiated 
 * power in percentage. v1.3.x and higher.
 */
#define CY_QI_POWER_ADDITIONAL_PER          (40u)

/**
 * Additional RPx load supported on top of negotiated 
 * power in percentage. preious to v1.3.x.
 */
#define CY_QI_OLD_POWER_ADDITIONAL_PER      (60u)

/** \} group_qistack_power_macros */

/**
* \addtogroup group_qistack_power_enums
* \{
*/

/** \} group_qistack_power_enums */

/**
* \addtogroup group_qistack_power_structures
* \{
*/

/** \} group_qistack_power_structures */

/**
* \addtogroup group_qistack_power_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_QiStack_Power_Init
****************************************************************************//**
*
* This function initializes the Qi power manager.
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* CY_QISTACK_STAT_SUCCESS if operation is successful
* CY_QISTACK_STAT_BAD_PARAM if the input parameters are not valid
*
*******************************************************************************/
cy_en_qi_status_t Cy_QiStack_Power_Init(
       /* Pointer to the qistack context. */
       cy_stc_qi_context_t *qiCtx);

/*******************************************************************************
* Function Name: Cy_QiStack_Power_Reset
****************************************************************************//**
*
* This function resets the Qi power manager.
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* CY_QISTACK_STAT_SUCCESS if operation is successful
* CY_QISTACK_STAT_BAD_PARAM if the input parameters are not valid
*
*******************************************************************************/
cy_en_qi_status_t Cy_QiStack_Power_Reset(
       /* Pointer to the qistack context. */
       cy_stc_qi_context_t *qiCtx);

/*******************************************************************************
* Function Name: Cy_QiStack_Power_Task
****************************************************************************//**
*
* This function runs the Qi power manager tasks.
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* CY_QISTACK_STAT_SUCCESS if operation is successful
* CY_QISTACK_STAT_BAD_PARAM if the input parameters are not valid
*
*******************************************************************************/
cy_en_qi_status_t Cy_QiStack_Power_Task(
       /* Pointer to the qistack context. */
       cy_stc_qi_context_t *qiCtx);

/*******************************************************************************
* Function Name: Cy_QiStack_PID_Trigger
****************************************************************************//**
*
* This function trigger PID algorithm for control loop correction
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \param cep
* Control Error value for PID algorithm.
*
* \return
* CY_QISTACK_STAT_SUCCESS if operation is successful
* CY_QISTACK_STAT_BAD_PARAM if the input parameters are not valid
*
*******************************************************************************/
cy_en_qi_status_t Cy_QiStack_PID_Trigger(
       cy_stc_qi_context_t *qiCtx,
       int8_t controlError);

/*******************************************************************************
* Function Name: Cy_QiStack_Get_Present_Volt_Cur
****************************************************************************//**
*
* This function gets the latest Voltage and Current from Ring buf
*
* \param qiCtx
* QiStack Library Context pointer.
*
*
* \return
* CY_QISTACK_STAT_SUCCESS if operation is successful
* CY_QISTACK_STAT_BAD_PARAM if the input parameters are not valid
*
*******************************************************************************/
cy_en_qi_status_t Cy_QiStack_Get_Present_Volt_Cur(cy_stc_qi_context_t *qiCtx);

/*******************************************************************************
* Function Name: Cy_QiStack_ValidSampling_Time_Duration
****************************************************************************//**
*
* This function gets the sampling time window
*
* \param qiCtx
* QiStack Library Context pointer.
*
*
* \return
* None
*
*******************************************************************************/
void Cy_QiStack_ValidSampling_Time_Duration(cy_stc_qi_context_t *qiCtx, uint16_t time);

/** \} group_qistack_power_functions */

#endif /* CY_QISTACK_POWER_MANAGER_H */

/* [] END OF FILE */
