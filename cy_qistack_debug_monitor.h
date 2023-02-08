/***************************************************************************//**
* \file cy_qistack_debug_monitor.h
* \version 2.0
*
* Qi Debug/Monitor Command Manager header file.
*
********************************************************************************
* \copyright
* Copyright 2021-2023, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef CY_QISTACK_DEBUG_MONITOR_H
#define CY_QISTACK_DEBUG_MONITOR_H

#include "cy_qistack_common.h"

/*******************************************************************************
*                              Type Definitions
*******************************************************************************/

/**
* \addtogroup group_debug_monitor_macros
* \{
*/

/** \} group_debug_monitor_macros */


/**
* \addtogroup group_debug_monitor_enums
* \{
*/

/** \} group_debug_monitor_enums */

/**
* \addtogroup group_debug_monitor_structures
* \{
*/

#if (CCG_HPI_WLC_CMD_ENABLE != 0)

/**
 * @brief Structure to store device information.
 */
typedef struct  {

    /** Chip ID */
    uint16_t chip_id;

    /** Chip revision */
    uint16_t chip_rev;

    /** PMTC */
    uint16_t pmtc;

    /** Reserved */
    uint16_t reserved;

}cy_stc_qi_dm_chip_info_t;

 /**
 * @brief Structure to store Vin, Tx Capability and Auth details from device
 */
typedef struct {

    /** Adapter/VIN details */
    uint8_t get_vin_info;

    /** Negotiable load power info */
    uint8_t get_tx_info;

    /** Authentication status */
    uint8_t auth_status;

    /** Reserved */
    uint8_t reserved;

    /** Reserved */
    uint32_t reserved1;

}cy_stc_qi_dm_vin_tx_auth_t;

 /**
 * @brief Structure to store state details
 */
typedef struct {

    /** Qi Phase: Ping, Configuration, Negotiation, Power transfer phase*/
    uint8_t phase;

    /** Qi Tx State */
    uint8_t tx_state;

    /** Qi Tx Sub State */
    uint8_t sub_state;

    /** EPT Reason */
    uint8_t ept_reason;

    /** Tx operating mode */
    uint16_t tx_op_mode;

    /** Reserved */
    uint16_t reserved;

}cy_stc_qi_dm_state_t;

 /**
 * @brief Structure to store operating details
 */
typedef struct {

    /** Charge status */
    uint8_t charge_status;

    /** CEP value */
    int8_t cep_value;

    /** RPP value */
    uint8_t rpp_value;

    /** Reserved */
    uint8_t reserved;

    /** Input voltage */
    uint16_t in_volt;

    /** Input current */
    uint16_t in_cur;

    /** Bridge voltage */
    uint16_t br_volt;

    /** Operating frequency */
    uint16_t op_freq;

    /** Operating duty */
    uint16_t op_duty;

    /** Reserved */
    uint16_t reserved1;

    /** Tx power (Vbridge X Iin) */
    uint32_t tx_pwr;

    /** Tx power for FOD */
    uint32_t tx_pwr_fod;

    /** Rx power */
    uint32_t rx_pwr;

    /** Power loss */
    uint32_t pwr_loss;

}cy_stc_qi_dm_op_status_t;

 /**
 * @brief Structure to store VIN PD contract voltage and current details
 */
typedef struct  {

    /** Selected PDO details which resulted in the contract */
    uint32_t sel_pdo;

    /** Last RDO received that resulted in the contract */
    uint32_t last_rdo;

}cy_stc_qi_dm_vin_ext_t;

 /**
 * @brief Structure to store negotiated power profile details
 */
typedef struct {

    /** Reference power */
    uint8_t ref_pwr;

    /** Received power window size */
    uint8_t pwr_window_size;

    /** Received power window offset */
    uint8_t pwr_window_offset;

    /** Power control hold off */
    uint8_t pch;

    /** Received power reporting resolution */
    uint8_t rpp_header;

    /** FSK polarity and modulation depth */
    uint8_t fsk_config;

    /** Potential load power */
    uint8_t pot_power;

    /** Guaranteed lower power */
    uint8_t Gar_power;

    /** Re-ping delay */
    uint8_t reping_delay;

    /** Re-calibration support */
    uint8_t recalib_support;

    /** Reserved */
    uint8_t reserved;

    /** Reserved 2 */
    uint8_t reserved2;

    /** Reserved 3*/
    uint32_t reserved3;

}cy_stc_qi_dm_nego_pwr_t;

 /**
 * @brief Structure to packet debug info
 */
typedef struct {

    /** Total CE packet number */
    uint32_t ce_count;

    /** Total RP packet number */
    uint32_t rp_count;

    /** Total EPT packet number */
    uint32_t ept_count;

    /** ASK fail count */
    uint32_t ask_fail_count;

    /** ASK noise count */
    uint32_t ask_noise_count;

    /** ASK path switch count */
    uint32_t ask_path_sw_count;

    /** CE retry count */
    uint32_t ce_to_retry_count;

    /** Reserved */
    uint32_t reserved;

}cy_stc_qi_dm_pkt_counter_t;

 /**
 * @brief Structure to store complete monitor info
 */
typedef struct __attribute__((__packed__)) {
    cy_stc_qi_dm_chip_info_t c_info;
    cy_stc_qi_dm_vin_tx_auth_t misc_info;
    cy_stc_qi_dm_state_t state;

    cy_stc_qi_dm_vin_ext_t vin_ext_info;
    cy_stc_qi_dm_nego_pwr_t neg_pwr_info;

    cy_stc_qi_dm_op_status_t op_status;
    cy_stc_qi_dm_pkt_counter_t packet_debug;
} cy_stc_qi_monitor_info_t;

 /**
 * @brief Structure to store PLOSS FO details
 */

/*
 * Extract PLOSS FO details.
 * Byte 0: PFOD_EN.
 * Byte 1 - Byte 3: Reserved
 * FOD manual
 * Byte 4 - Byte 7: PFOD_COEF_A_BPP.
 * Byte 8 - Byte 11: PFOD_COEF_B_BPP.
 * Byte 12 - Byte 15: PFOD_COEF_C_BPP.
 * Byte 16 - Byte 17: FOD_THD_BPP.
 * Byte 18 - Byte 19: Reserved
 *
 * FOD manual calibration coefficients for 5W EPP
 * Byte 20 - Byte 23: PFOD_COEF_A_EPP.
 * Byte 24 - Byte 27: PFOD_COEF_B_EPP.
 * Byte 28 - Byte 31: PFOD_COEF_C_EPP.
 * Byte 32 - Byte 33: FOD_THD_EPP.
 * Byte 34 - Byte 35: Reserved
 *
 * FOD manual calibration coefficients for 15W EPP
 * Byte 36 - Byte 39: PFOD_COEF_A_EPP.
 * Byte 40 - Byte 43: PFOD_COEF_B_EPP.
 * Byte 44 - Byte 47: PFOD_COEF_C_EPP.
 * Byte 48 - Byte 49: FOD_THD_EPP.
 * Byte 50 - Byte 51: Reserved
 */
typedef struct __attribute__((__packed__)){

    /** FOD power loss feature enable */
    uint8_t pfod_en;

    /** Reserved 1 */
    uint8_t rsvd1;

    /** Reserved 2 */
    uint8_t rsvd2;

    /** Reserved 3 */
    uint8_t rsvd3;

    /** Calibration coefficients for BPP */

    /* COEF_A_BPP */
    float bppFODCoeffA;

    /* COEF_B_BPP */
    float bppFODCoeffB;

    /* COEF_C_BPP */
    float bppFODCoeffC;

    /* FOD_THD_BPP */
    int16_t bppFODThr;

    /* Reserved */
    int16_t bppRsvd;

    /** Calibration coefficients for EPP 5W */

    /** COEF_A_EPP */
    float epp5wFODCoeffA;

    /** COEF_B_EPP */
    float epp5wFODCoeffB;

    /** COEF_C_EPP */
    float epp5wFODCoeffC;

    /** FOD_THD_EPP */
    int16_t epp5wFODThr;

    /** Reserved */
    int16_t epp5wRsvd;

    /** Calibration coefficients for EPP 15W */

    /** COEF_A_EPP */
    float epp15wFODCoeffA;

    /** COEF_B_EPP */
    float epp15wFODCoeffB;

    /** COEF_C_EPP */
    float epp15wFODCoeffC;

    /** FOD_THD_EPP */
    int16_t epp15wFODThr;

    /** Reserved */
    int16_t epp15wRsvd;

    /** Calibration coefficients for HiPP */

     /** COEF_A_HiPP */
     float hippFODCoeffA;

     /** COEF_B_HiPP */
     float hippFODCoeffB;

     /** COEF_C_HiPP */
     float hippFODCoeffC;

     /** FOD_THD_HiPP */
     int16_t hippFODThr;

     /** Reserved */
     int16_t hippRsvd;
}cy_stc_qi_dm_fo_cfg_data_t;

typedef struct {

    /** ASK demod voltage high gain */
    uint8_t vGainH;

    /** ASK demod voltage low gain */
    uint8_t vGainL;

    /** ASK demod current low gain */
    uint8_t cGainL;

    /** Reserved */
    uint8_t Rsvd;
}cy_stc_qi_dm_ask_gain_t;

typedef struct {

    /** Q free air FOD enable/disable. */
    uint8_t qFODEn;

    /** Q Free AIR FOD threshold percentage*/
    uint8_t qFreeAirFODThrPer;

    /** Scale factor for high reported Q calibration, percentage */
    uint8_t qSFactorRxFriendly;

    /** Scale factor for low reported Q calibration, percentage */
    uint8_t qSFactorRxNonFriendly;

}cy_stc_qi_dm_q_fo_cfg_t;

typedef struct {

    /** Power level threshold for VBRG saturation (Upper Limit) */
    uint8_t qVbrgSaturationThr;

    /** Reserved */
    uint8_t Rsvd;

    /** Scale factor for high reported Q calibration, percentage */
    uint16_t qOcpThr;

}cy_stc_qi_dm_maxpwr_cap_t;

#endif /* CCG_HPI_WLC_CMD_ENABLE */

/** \} group_debug_monitor_structures */

/**
* \addtogroup group_debug_monitor_functions
* \{
*/
#if (CCG_HPI_WLC_CMD_ENABLE != 0)
/*******************************************************************************
* Function Name: Cy_QiStack_Misc_Info
******************************************************************************
*
* This function populates the Vin, Tx Capability and Auth from Qi stack.
*
* \param qiCtx
* QiStack Library Context pointer.
* \param buffer
* buffer to extract data from QiStack
* \return
* none
*
*******************************************************************************/
void Cy_QiStack_Misc_Info(cy_stc_qi_context_t *qiCtx, uint8_t *buffer);

/*******************************************************************************
* Function Name: Cy_QiStack_Get_State_Info
******************************************************************************
*
* This function populates the Qi state details from stack.
*
* \param qiCtx
* QiStack Library Context pointer.
* \param buffer
* buffer to extract data from QiStack
* \return
* none
*
*******************************************************************************/
void Cy_QiStack_Get_State_Info(cy_stc_qi_context_t *qiCtx, uint8_t *buffer);

/*******************************************************************************
* Function Name: Cy_QiStack_Get_Nego_Pwr_Info
******************************************************************************
*
* This function populates the negotiated power profile details from stack.
*
* \param qiCtx
* QiStack Library Context pointer.
* \param buffer
* buffer to extract data from QiStack
* \return
* none
*
*******************************************************************************/
void Cy_QiStack_Get_Nego_Pwr_Info(cy_stc_qi_context_t *qiCtx, uint8_t *buffer);

/*******************************************************************************
* Function Name: Cy_QiStack_Get_Operating_Info
******************************************************************************
*
* This function populates the operating details from stack.
*
* \param qiCtx
* QiStack Library Context pointer.
* \param buffer
* buffer to extract data from QiStack
* \return
* none
*
*******************************************************************************/
void Cy_QiStack_Get_Operating_Info(cy_stc_qi_context_t *qiCtx, uint8_t *buffer);

/*******************************************************************************
* Function Name: Cy_QiStack_Get_Operating_Info
******************************************************************************
*
* This function populates the packet debug details from stack.
*
* \param qiCtx
* QiStack Library Context pointer.
* \param buffer
* buffer to extract data from QiStack
* \return
* none
*
*******************************************************************************/
void Cy_QiStack_Get_Packet_Info(cy_stc_qi_context_t *qiCtx, uint8_t *buffer);

/*******************************************************************************
* Function Name: Cy_QiStack_Get_FO_Config_Data
******************************************************************************
*
* This function populates the FO config parameters stored in stack
*
* \param qiCtx
* QiStack Library Context pointer.
* \param buffer
* buffer to extract data from QiStack
* \return
* none
*
*******************************************************************************/
void Cy_QiStack_Get_FO_Config_Data(cy_stc_qi_context_t *qiCtx, uint8_t *buffer);

/*******************************************************************************
* Function Name: Cy_QiStack_Set_FO_Config_Data
******************************************************************************
*
* This function updates the FO config parameters stored in stack
*
* \param qiCtx
* QiStack Library Context pointer.
* \param buffer
* buffer to extract data from QiStack
* \return
* none
*
*******************************************************************************/
void Cy_QiStack_Set_FO_Config_Data(cy_stc_qi_context_t *qiCtx, uint8_t *buffer);

/*******************************************************************************
* Function Name: Cy_QiStack_Get_ASK_Demod_Gain
******************************************************************************
*
* This function updates the FO config parameters stored in stack
*
* \param qiCtx
* QiStack Library Context pointer.
* \param buffer
* buffer to extract data from QiStack
* \return
* none
*
*******************************************************************************/
void Cy_QiStack_Get_ASK_Demod_Gain(cy_stc_qi_context_t *qiCtx, uint8_t *buffer);

/*******************************************************************************
* Function Name: Cy_QiStack_Set_ASK_Demod_Gain
******************************************************************************
*
* This function updates the FO config parameters stored in stack
*
* \param qiCtx
* QiStack Library Context pointer.
* \param buffer
* buffer to extract data from QiStack
* \return
* none
*
*******************************************************************************/
void Cy_QiStack_Set_ASK_Demod_Gain(cy_stc_qi_context_t *qiCtx, uint8_t *buffer);

/*******************************************************************************
* Function Name: Cy_QiStack_Get_Q_FO_Cfg
******************************************************************************
*
* This function reads the  Q FO config stored in stack
*
* \param qiCtx
* QiStack Library Context pointer.
* \param buffer
* buffer to extract data from QiStack
* \return
* none
*
*******************************************************************************/
void Cy_QiStack_Get_Q_FO_Cfg(cy_stc_qi_context_t *qiCtx, uint8_t *buffer);

/*******************************************************************************
* Function Name: Cy_QiStack_Set_Q_FO_Cfg
******************************************************************************
*
* This function updates the Q FO config stored in stack
*
* \param qiCtx
* QiStack Library Context pointer.
* \param buffer
* buffer to extract data from QiStack
* \return
* none
*
*******************************************************************************/
void Cy_QiStack_Set_Q_FO_Cfg(cy_stc_qi_context_t *qiCtx, uint8_t *buffer);

/*******************************************************************************
* Function Name: Cy_QiStack_Get_Max_Pwr_Cap
******************************************************************************
*
* This function reads  Max Power Cap details.
*
* \param qiCtx
* QiStack Library Context pointer.
* \param buffer
* buffer to extract data from QiStack
* \return
* none
*
*******************************************************************************/
void Cy_QiStack_Get_Max_Pwr_Cap(cy_stc_qi_context_t *qiCtx, uint8_t *buffer);

/*******************************************************************************
* Function Name: Cy_QiStack_Set_Max_Pwr_Cap
******************************************************************************
*
* This function updates the Max Power Cap details.
*
* \param qiCtx
* QiStack Library Context pointer.
* \param buffer
* buffer to extract data from QiStack
* \return
* none
*
*******************************************************************************/
void Cy_QiStack_Set_Max_Pwr_Cap(cy_stc_qi_context_t *qiCtx, uint8_t *buffer);

#endif /* CCG_HPI_WLC_CMD_ENABLE */
/** \} group_debug_monitor_functions */

#endif /* CY_QISTACK_DEBUG_MONITOR_H */

/* [] END OF FILE */
