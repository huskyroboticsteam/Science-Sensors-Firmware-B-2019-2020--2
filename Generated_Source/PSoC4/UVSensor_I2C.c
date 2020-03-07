/***************************************************************************//**
* \file UVSensor_I2C.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  I2C mode.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "UVSensor_PVT.h"
#include "UVSensor_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 UVSensor_state;  /* Current state of I2C FSM */

#if(UVSensor_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const UVSensor_I2C_INIT_STRUCT UVSensor_configI2C =
    {
        UVSensor_I2C_MODE,
        UVSensor_I2C_OVS_FACTOR_LOW,
        UVSensor_I2C_OVS_FACTOR_HIGH,
        UVSensor_I2C_MEDIAN_FILTER_ENABLE,
        UVSensor_I2C_SLAVE_ADDRESS,
        UVSensor_I2C_SLAVE_ADDRESS_MASK,
        UVSensor_I2C_ACCEPT_ADDRESS,
        UVSensor_I2C_WAKE_ENABLE,
        UVSensor_I2C_BYTE_MODE_ENABLE,
        UVSensor_I2C_DATA_RATE,
        UVSensor_I2C_ACCEPT_GENERAL_CALL,
    };

    /*******************************************************************************
    * Function Name: UVSensor_I2CInit
    ****************************************************************************//**
    *
    *
    *  Configures the UVSensor for I2C operation.
    *
    *  This function is intended specifically to be used when the UVSensor 
    *  configuration is set to “Unconfigured UVSensor” in the customizer. 
    *  After initializing the UVSensor in I2C mode using this function, 
    *  the component can be enabled using the UVSensor_Start() or 
    * UVSensor_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void UVSensor_I2CInit(const UVSensor_I2C_INIT_STRUCT *config)
    {
        uint32 medianFilter;
        uint32 locEnableWake;

        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            UVSensor_SetPins(UVSensor_SCB_MODE_I2C, UVSensor_DUMMY_PARAM,
                                     UVSensor_DUMMY_PARAM);

            /* Store internal configuration */
            UVSensor_scbMode       = (uint8) UVSensor_SCB_MODE_I2C;
            UVSensor_scbEnableWake = (uint8) config->enableWake;
            UVSensor_scbEnableIntr = (uint8) UVSensor_SCB_IRQ_INTERNAL;

            UVSensor_mode          = (uint8) config->mode;
            UVSensor_acceptAddr    = (uint8) config->acceptAddr;

        #if (UVSensor_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            UVSensor_SET_I2C_CFG_SDA_FILT_TRIM(UVSensor_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (UVSensor_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((UVSensor_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= UVSensor_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (UVSensor_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                UVSensor_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = UVSensor_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                UVSensor_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = UVSensor_DIGITAL_FILTER_ENABLE;
            }

        #if (!UVSensor_CY_SCBIP_V0)
            locEnableWake = (UVSensor_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!UVSensor_CY_SCBIP_V0) */

            /* Configure I2C interface */
            UVSensor_CTRL_REG     = UVSensor_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            UVSensor_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            UVSensor_GET_CTRL_EC_AM_MODE (locEnableWake);

            UVSensor_I2C_CTRL_REG = UVSensor_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                    UVSensor_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)                          |
                    UVSensor_GET_I2C_CTRL_S_GENERAL_IGNORE((uint32)(0u == config->acceptGeneralAddr))    |
                    UVSensor_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode);

            /* Configure RX direction */
            UVSensor_RX_CTRL_REG      = UVSensor_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                UVSensor_I2C_RX_CTRL;
            UVSensor_RX_FIFO_CTRL_REG = UVSensor_CLEAR_REG;

            /* Set default address and mask */
            UVSensor_RX_MATCH_REG    = ((UVSensor_I2C_SLAVE) ?
                                                (UVSensor_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 UVSensor_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (UVSensor_CLEAR_REG));


            /* Configure TX direction */
            UVSensor_TX_CTRL_REG      = UVSensor_I2C_TX_CTRL;
            UVSensor_TX_FIFO_CTRL_REG = UVSensor_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (UVSensor_ISR_NUMBER);
            CyIntSetPriority(UVSensor_ISR_NUMBER, UVSensor_ISR_PRIORITY);
            (void) CyIntSetVector(UVSensor_ISR_NUMBER, &UVSensor_I2C_ISR);

            /* Configure interrupt sources */
        #if(!UVSensor_CY_SCBIP_V1)
            UVSensor_INTR_SPI_EC_MASK_REG = UVSensor_NO_INTR_SOURCES;
        #endif /* (!UVSensor_CY_SCBIP_V1) */

            UVSensor_INTR_I2C_EC_MASK_REG = UVSensor_NO_INTR_SOURCES;
            UVSensor_INTR_RX_MASK_REG     = UVSensor_NO_INTR_SOURCES;
            UVSensor_INTR_TX_MASK_REG     = UVSensor_NO_INTR_SOURCES;

            UVSensor_INTR_SLAVE_MASK_REG  = ((UVSensor_I2C_SLAVE) ?
                            (UVSensor_GET_INTR_SLAVE_I2C_GENERAL(config->acceptGeneralAddr) |
                             UVSensor_I2C_INTR_SLAVE_MASK) : (UVSensor_CLEAR_REG));

            UVSensor_INTR_MASTER_MASK_REG = UVSensor_NO_INTR_SOURCES;

            /* Configure global variables */
            UVSensor_state = UVSensor_I2C_FSM_IDLE;

            /* Internal slave variables */
            UVSensor_slStatus        = 0u;
            UVSensor_slRdBufIndex    = 0u;
            UVSensor_slWrBufIndex    = 0u;
            UVSensor_slOverFlowCount = 0u;

            /* Internal master variables */
            UVSensor_mstrStatus     = 0u;
            UVSensor_mstrRdBufIndex = 0u;
            UVSensor_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: UVSensor_I2CInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the I2C operation.
    *
    *******************************************************************************/
    void UVSensor_I2CInit(void)
    {
    #if(UVSensor_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        UVSensor_SET_I2C_CFG_SDA_FILT_TRIM(UVSensor_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (UVSensor_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        UVSensor_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        UVSensor_CTRL_REG     = UVSensor_I2C_DEFAULT_CTRL;
        UVSensor_I2C_CTRL_REG = UVSensor_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        UVSensor_RX_CTRL_REG      = UVSensor_I2C_DEFAULT_RX_CTRL;
        UVSensor_RX_FIFO_CTRL_REG = UVSensor_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        UVSensor_RX_MATCH_REG     = UVSensor_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        UVSensor_TX_CTRL_REG      = UVSensor_I2C_DEFAULT_TX_CTRL;
        UVSensor_TX_FIFO_CTRL_REG = UVSensor_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (UVSensor_ISR_NUMBER);
        CyIntSetPriority(UVSensor_ISR_NUMBER, UVSensor_ISR_PRIORITY);
    #if(!UVSensor_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(UVSensor_ISR_NUMBER, &UVSensor_I2C_ISR);
    #endif /* (UVSensor_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!UVSensor_CY_SCBIP_V1)
        UVSensor_INTR_SPI_EC_MASK_REG = UVSensor_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!UVSensor_CY_SCBIP_V1) */

        UVSensor_INTR_I2C_EC_MASK_REG = UVSensor_I2C_DEFAULT_INTR_I2C_EC_MASK;
        UVSensor_INTR_SLAVE_MASK_REG  = UVSensor_I2C_DEFAULT_INTR_SLAVE_MASK;
        UVSensor_INTR_MASTER_MASK_REG = UVSensor_I2C_DEFAULT_INTR_MASTER_MASK;
        UVSensor_INTR_RX_MASK_REG     = UVSensor_I2C_DEFAULT_INTR_RX_MASK;
        UVSensor_INTR_TX_MASK_REG     = UVSensor_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        UVSensor_state = UVSensor_I2C_FSM_IDLE;

    #if(UVSensor_I2C_SLAVE)
        /* Internal slave variable */
        UVSensor_slStatus        = 0u;
        UVSensor_slRdBufIndex    = 0u;
        UVSensor_slWrBufIndex    = 0u;
        UVSensor_slOverFlowCount = 0u;
    #endif /* (UVSensor_I2C_SLAVE) */

    #if(UVSensor_I2C_MASTER)
    /* Internal master variable */
        UVSensor_mstrStatus     = 0u;
        UVSensor_mstrRdBufIndex = 0u;
        UVSensor_mstrWrBufIndex = 0u;
    #endif /* (UVSensor_I2C_MASTER) */
    }
#endif /* (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: UVSensor_I2CStop
****************************************************************************//**
*
*  Resets the I2C FSM into the default state.
*
*******************************************************************************/
void UVSensor_I2CStop(void)
{
    /* Clear command registers because they keep assigned value after IP block was disabled */
    UVSensor_I2C_MASTER_CMD_REG = 0u;
    UVSensor_I2C_SLAVE_CMD_REG  = 0u;
    
    UVSensor_state = UVSensor_I2C_FSM_IDLE;
}


/*******************************************************************************
* Function Name: UVSensor_I2CFwBlockReset
****************************************************************************//**
*
* Resets the scb IP block and I2C into the known state.
*
*******************************************************************************/
void UVSensor_I2CFwBlockReset(void)
{
    /* Disable scb IP: stop respond to I2C traffic */
    UVSensor_CTRL_REG &= (uint32) ~UVSensor_CTRL_ENABLED;

    /* Clear command registers they are not cleared after scb IP is disabled */
    UVSensor_I2C_MASTER_CMD_REG = 0u;
    UVSensor_I2C_SLAVE_CMD_REG  = 0u;

    UVSensor_DISABLE_AUTO_DATA;

    UVSensor_SetTxInterruptMode(UVSensor_NO_INTR_SOURCES);
    UVSensor_SetRxInterruptMode(UVSensor_NO_INTR_SOURCES);
    
#if(UVSensor_CY_SCBIP_V0)
    /* Clear interrupt sources as they are not cleared after scb IP is disabled */
    UVSensor_ClearTxInterruptSource    (UVSensor_INTR_TX_ALL);
    UVSensor_ClearRxInterruptSource    (UVSensor_INTR_RX_ALL);
    UVSensor_ClearSlaveInterruptSource (UVSensor_INTR_SLAVE_ALL);
    UVSensor_ClearMasterInterruptSource(UVSensor_INTR_MASTER_ALL);
#endif /* (UVSensor_CY_SCBIP_V0) */

    UVSensor_state = UVSensor_I2C_FSM_IDLE;

    /* Enable scb IP: start respond to I2C traffic */
    UVSensor_CTRL_REG |= (uint32) UVSensor_CTRL_ENABLED;
}


#if(UVSensor_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: UVSensor_I2CSaveConfig
    ****************************************************************************//**
    *
    *  Enables UVSensor_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void UVSensor_I2CSaveConfig(void)
    {
    #if (!UVSensor_CY_SCBIP_V0)
        #if (UVSensor_I2C_MULTI_MASTER_SLAVE_CONST && UVSensor_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (UVSensor_CTRL_REG & UVSensor_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                UVSensor_Stop();
                UVSensor_CTRL_REG |= UVSensor_CTRL_EC_AM_MODE;
                UVSensor_Enable();
            }
        #endif /* (UVSensor_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (UVSensor_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            UVSensor_SCBCLK_Stop();
        #endif /* (UVSensor_SCB_CLK_INTERNAL) */
    #endif /* (!UVSensor_CY_SCBIP_V0) */

        UVSensor_SetI2CExtClkInterruptMode(UVSensor_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: UVSensor_I2CRestoreConfig
    ****************************************************************************//**
    *
    *  Disables UVSensor_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void UVSensor_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        UVSensor_SetI2CExtClkInterruptMode(UVSensor_NO_INTR_SOURCES);

    #if (!UVSensor_CY_SCBIP_V0)
        #if (UVSensor_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            UVSensor_SCBCLK_Start();
        #endif /* (UVSensor_SCB_CLK_INTERNAL) */
    #endif /* (!UVSensor_CY_SCBIP_V0) */
    }
#endif /* (UVSensor_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
