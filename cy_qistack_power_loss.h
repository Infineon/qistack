/***************************************************************************//**
* \file cy_qistack_power_loss.h
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

#ifndef CY_QISTACK_POWER_LOSS_H
#define CY_QISTACK_POWER_LOSS_H

#include "cy_qistack_common.h"

/*******************************************************************************
*                              Type Definitions
*******************************************************************************/

/**
* \addtogroup group_power_loss_macros
* \{
*/

/** \} group_power_loss_macros */

#define CY_QI_FO_DETECT_EPP_5W                                  (10u)
#define CY_QI_FO_DETECT_EPP_15W                                 (30u)

#define CY_QI_FO_DETECT_DELTA_PRx_CALIB_MIN                     (1000)
#define CY_QI_FO_COEFF_MULTIPLIER                               (10000u)
#define CY_QI_FO_LOW_POWER_THRESHOLD_CHECK                      (600)
#define CY_QI_FO_ADD_SYS_EFFICIENCY_LOSS                        (100)
#define CY_QI_MIN_PLOSS_OFFSET                                  (1)

#define CY_QI_FO_DETECT_DELTA_POWER_LOSS_THRESHOLD              (0.085) /* Data obtained by OnePlus charge cycles in OFF conditions */
#define CY_QI_FO_DETECT_DELTA_POWER_THRESHOLD_OFFSET_EPP        (200u)
#define CY_QI_MAX_OFFSET_VALUE_CONSIDERED_FOR_CORRECTION        (210u)  /* This value is obtained from the excel sheet sample of 5 boards. */

#define CY_QI_BPP_OFFSET_DETECTION_RETRIAL_COUNT                (3u)

#define CY_QI_CONFIG_BPP_Q_FACTOR_FO_SUSPECT                    (30u) /* This value determine whether to perform PLOSS threshold correction */

#define CY_QI_SAMSUNG_FAST_CHARGE_PHONES_Q_FACTOR               (45u) /* This value is obtained from 8 Inter OP Samsung Phone data */
#define CY_QI_SAMSUNG_FAST_CHARGE_PHONES_Q_FACTOR_FO_SUSPECT    (10)  /* This PERCENTAGE of FO suspect deviation for samsung phone */

#define CY_QI_HIPP_FO_DETECT_MAX_THRESHOLD_ADJUSTMENT           (500u) /* The additional offset for HIPP FO detection at max threshold */

/**
* \addtogroup group_power_loss_enums
* \{
*/

/** \} group_power_loss_enums */

/**
* \addtogroup group_power_loss_structures
* \{
*/

/** \} group_power_loss_structures */

/**
* \addtogroup group_power_loss_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_QiStack_Power_Loss_Fo_Status
******************************************************************************
*
* This function return whether Power Loss FO detected or not
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* TRUE  - FO detected
* FALSE - No FO detected
*
*******************************************************************************/
cy_en_qi_ploss_reasons_t Cy_QiStack_Power_Loss_Fo_Status(cy_stc_qi_context_t *qiCtx);

/*******************************************************************************
* Function Name: Cy_QiStack_PowerLoss_Reset_Params
******************************************************************************
*
* This function resets the power loss parameters
*
* \param qiCtx
* QiStack Library Context pointer.
*
* \return
* none
*
*******************************************************************************/
void Cy_QiStack_PowerLoss_Reset_Params(cy_stc_qi_context_t *qiCtx);
/** \} group_power_loss_functions */

#endif /* CY_QISTACK_OBJECT_MANAGER_H */

/* [] END OF FILE */
