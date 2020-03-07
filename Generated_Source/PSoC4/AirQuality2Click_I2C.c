/***************************************************************************//**
* \file AirQuality2Click_I2C.c
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

#include "AirQuality2Click_PVT.h"
#include "AirQuality2Click_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 AirQuality2Click_state;  /* Current state of I2C FSM */

#if(AirQuality2Click_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const AirQuality2Click_I2C_INIT_STRUCT AirQuality2Click_configI2C =
    {
        AirQuality2Click_I2C_MODE,
        AirQuality2Click_I2C_OVS_FACTOR_LOW,
        AirQuality2Click_I2C_OVS_FACTOR_HIGH,
        AirQuality2Click_I2C_MEDIAN_FILTER_ENABLE,
        AirQuality2Click_I2C_SLAVE_ADDRESS,
        AirQuality2Click_I2C_SLAVE_ADDRESS_MASK,
        AirQuality2Click_I2C_ACCEPT_ADDRESS,
        AirQuality2Click_I2C_WAKE_ENABLE,
        AirQuality2Click_I2C_BYTE_MODE_ENABLE,
        AirQuality2Click_I2C_DATA_RATE,
        AirQuality2Click_I2C_ACCEPT_GENERAL_CALL,
    };

    /*******************************************************************************
    * Function Name: AirQuality2Click_I2CInit
    ****************************************************************************//**
    *
    *
    *  Configures the AirQuality2Click for I2C operation.
    *
    *  This function is intended specifically to be used when the AirQuality2Click 
    *  configuration is set to “Unconfigured AirQuality2Click” in the customizer. 
    *  After initializing the AirQuality2Click in I2C mode using this function, 
    *  the component can be enabled using the AirQuality2Click_Start() or 
    * AirQuality2Click_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void AirQuality2Click_I2CInit(const AirQuality2Click_I2C_INIT_STRUCT *config)
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
            AirQuality2Click_SetPins(AirQuality2Click_SCB_MODE_I2C, AirQuality2Click_DUMMY_PARAM,
                                     AirQuality2Click_DUMMY_PARAM);

            /* Store internal configuration */
            AirQuality2Click_scbMode       = (uint8) AirQuality2Click_SCB_MODE_I2C;
            AirQuality2Click_scbEnableWake = (uint8) config->enableWake;
            AirQuality2Click_scbEnableIntr = (uint8) AirQuality2Click_SCB_IRQ_INTERNAL;

            AirQuality2Click_mode          = (uint8) config->mode;
            AirQuality2Click_acceptAddr    = (uint8) config->acceptAddr;

        #if (AirQuality2Click_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            AirQuality2Click_SET_I2C_CFG_SDA_FILT_TRIM(AirQuality2Click_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (AirQuality2Click_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((AirQuality2Click_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= AirQuality2Click_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (AirQuality2Click_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                AirQuality2Click_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = AirQuality2Click_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                AirQuality2Click_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = AirQuality2Click_DIGITAL_FILTER_ENABLE;
            }

        #if (!AirQuality2Click_CY_SCBIP_V0)
            locEnableWake = (AirQuality2Click_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!AirQuality2Click_CY_SCBIP_V0) */

            /* Configure I2C interface */
            AirQuality2Click_CTRL_REG     = AirQuality2Click_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            AirQuality2Click_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            AirQuality2Click_GET_CTRL_EC_AM_MODE (locEnableWake);

            AirQuality2Click_I2C_CTRL_REG = AirQuality2Click_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                    AirQuality2Click_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)                          |
                    AirQuality2Click_GET_I2C_CTRL_S_GENERAL_IGNORE((uint32)(0u == config->acceptGeneralAddr))    |
                    AirQuality2Click_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode);

            /* Configure RX direction */
            AirQuality2Click_RX_CTRL_REG      = AirQuality2Click_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                AirQuality2Click_I2C_RX_CTRL;
            AirQuality2Click_RX_FIFO_CTRL_REG = AirQuality2Click_CLEAR_REG;

            /* Set default address and mask */
            AirQuality2Click_RX_MATCH_REG    = ((AirQuality2Click_I2C_SLAVE) ?
                                                (AirQuality2Click_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 AirQuality2Click_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (AirQuality2Click_CLEAR_REG));


            /* Configure TX direction */
            AirQuality2Click_TX_CTRL_REG      = AirQuality2Click_I2C_TX_CTRL;
            AirQuality2Click_TX_FIFO_CTRL_REG = AirQuality2Click_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (AirQuality2Click_ISR_NUMBER);
            CyIntSetPriority(AirQuality2Click_ISR_NUMBER, AirQuality2Click_ISR_PRIORITY);
            (void) CyIntSetVector(AirQuality2Click_ISR_NUMBER, &AirQuality2Click_I2C_ISR);

            /* Configure interrupt sources */
        #if(!AirQuality2Click_CY_SCBIP_V1)
            AirQuality2Click_INTR_SPI_EC_MASK_REG = AirQuality2Click_NO_INTR_SOURCES;
        #endif /* (!AirQuality2Click_CY_SCBIP_V1) */

            AirQuality2Click_INTR_I2C_EC_MASK_REG = AirQuality2Click_NO_INTR_SOURCES;
            AirQuality2Click_INTR_RX_MASK_REG     = AirQuality2Click_NO_INTR_SOURCES;
            AirQuality2Click_INTR_TX_MASK_REG     = AirQuality2Click_NO_INTR_SOURCES;

            AirQuality2Click_INTR_SLAVE_MASK_REG  = ((AirQuality2Click_I2C_SLAVE) ?
                            (AirQuality2Click_GET_INTR_SLAVE_I2C_GENERAL(config->acceptGeneralAddr) |
                             AirQuality2Click_I2C_INTR_SLAVE_MASK) : (AirQuality2Click_CLEAR_REG));

            AirQuality2Click_INTR_MASTER_MASK_REG = AirQuality2Click_NO_INTR_SOURCES;

            /* Configure global variables */
            AirQuality2Click_state = AirQuality2Click_I2C_FSM_IDLE;

            /* Internal slave variables */
            AirQuality2Click_slStatus        = 0u;
            AirQuality2Click_slRdBufIndex    = 0u;
            AirQuality2Click_slWrBufIndex    = 0u;
            AirQuality2Click_slOverFlowCount = 0u;

            /* Internal master variables */
            AirQuality2Click_mstrStatus     = 0u;
            AirQuality2Click_mstrRdBufIndex = 0u;
            AirQuality2Click_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: AirQuality2Click_I2CInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the I2C operation.
    *
    *******************************************************************************/
    void AirQuality2Click_I2CInit(void)
    {
    #if(AirQuality2Click_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        AirQuality2Click_SET_I2C_CFG_SDA_FILT_TRIM(AirQuality2Click_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (AirQuality2Click_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        AirQuality2Click_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        AirQuality2Click_CTRL_REG     = AirQuality2Click_I2C_DEFAULT_CTRL;
        AirQuality2Click_I2C_CTRL_REG = AirQuality2Click_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        AirQuality2Click_RX_CTRL_REG      = AirQuality2Click_I2C_DEFAULT_RX_CTRL;
        AirQuality2Click_RX_FIFO_CTRL_REG = AirQuality2Click_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        AirQuality2Click_RX_MATCH_REG     = AirQuality2Click_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        AirQuality2Click_TX_CTRL_REG      = AirQuality2Click_I2C_DEFAULT_TX_CTRL;
        AirQuality2Click_TX_FIFO_CTRL_REG = AirQuality2Click_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (AirQuality2Click_ISR_NUMBER);
        CyIntSetPriority(AirQuality2Click_ISR_NUMBER, AirQuality2Click_ISR_PRIORITY);
    #if(!AirQuality2Click_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(AirQuality2Click_ISR_NUMBER, &AirQuality2Click_I2C_ISR);
    #endif /* (AirQuality2Click_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!AirQuality2Click_CY_SCBIP_V1)
        AirQuality2Click_INTR_SPI_EC_MASK_REG = AirQuality2Click_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!AirQuality2Click_CY_SCBIP_V1) */

        AirQuality2Click_INTR_I2C_EC_MASK_REG = AirQuality2Click_I2C_DEFAULT_INTR_I2C_EC_MASK;
        AirQuality2Click_INTR_SLAVE_MASK_REG  = AirQuality2Click_I2C_DEFAULT_INTR_SLAVE_MASK;
        AirQuality2Click_INTR_MASTER_MASK_REG = AirQuality2Click_I2C_DEFAULT_INTR_MASTER_MASK;
        AirQuality2Click_INTR_RX_MASK_REG     = AirQuality2Click_I2C_DEFAULT_INTR_RX_MASK;
        AirQuality2Click_INTR_TX_MASK_REG     = AirQuality2Click_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        AirQuality2Click_state = AirQuality2Click_I2C_FSM_IDLE;

    #if(AirQuality2Click_I2C_SLAVE)
        /* Internal slave variable */
        AirQuality2Click_slStatus        = 0u;
        AirQuality2Click_slRdBufIndex    = 0u;
        AirQuality2Click_slWrBufIndex    = 0u;
        AirQuality2Click_slOverFlowCount = 0u;
    #endif /* (AirQuality2Click_I2C_SLAVE) */

    #if(AirQuality2Click_I2C_MASTER)
    /* Internal master variable */
        AirQuality2Click_mstrStatus     = 0u;
        AirQuality2Click_mstrRdBufIndex = 0u;
        AirQuality2Click_mstrWrBufIndex = 0u;
    #endif /* (AirQuality2Click_I2C_MASTER) */
    }
#endif /* (AirQuality2Click_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: AirQuality2Click_I2CStop
****************************************************************************//**
*
*  Resets the I2C FSM into the default state.
*
*******************************************************************************/
void AirQuality2Click_I2CStop(void)
{
    /* Clear command registers because they keep assigned value after IP block was disabled */
    AirQuality2Click_I2C_MASTER_CMD_REG = 0u;
    AirQuality2Click_I2C_SLAVE_CMD_REG  = 0u;
    
    AirQuality2Click_state = AirQuality2Click_I2C_FSM_IDLE;
}


/*******************************************************************************
* Function Name: AirQuality2Click_I2CFwBlockReset
****************************************************************************//**
*
* Resets the scb IP block and I2C into the known state.
*
*******************************************************************************/
void AirQuality2Click_I2CFwBlockReset(void)
{
    /* Disable scb IP: stop respond to I2C traffic */
    AirQuality2Click_CTRL_REG &= (uint32) ~AirQuality2Click_CTRL_ENABLED;

    /* Clear command registers they are not cleared after scb IP is disabled */
    AirQuality2Click_I2C_MASTER_CMD_REG = 0u;
    AirQuality2Click_I2C_SLAVE_CMD_REG  = 0u;

    AirQuality2Click_DISABLE_AUTO_DATA;

    AirQuality2Click_SetTxInterruptMode(AirQuality2Click_NO_INTR_SOURCES);
    AirQuality2Click_SetRxInterruptMode(AirQuality2Click_NO_INTR_SOURCES);
    
#if(AirQuality2Click_CY_SCBIP_V0)
    /* Clear interrupt sources as they are not cleared after scb IP is disabled */
    AirQuality2Click_ClearTxInterruptSource    (AirQuality2Click_INTR_TX_ALL);
    AirQuality2Click_ClearRxInterruptSource    (AirQuality2Click_INTR_RX_ALL);
    AirQuality2Click_ClearSlaveInterruptSource (AirQuality2Click_INTR_SLAVE_ALL);
    AirQuality2Click_ClearMasterInterruptSource(AirQuality2Click_INTR_MASTER_ALL);
#endif /* (AirQuality2Click_CY_SCBIP_V0) */

    AirQuality2Click_state = AirQuality2Click_I2C_FSM_IDLE;

    /* Enable scb IP: start respond to I2C traffic */
    AirQuality2Click_CTRL_REG |= (uint32) AirQuality2Click_CTRL_ENABLED;
}


#if(AirQuality2Click_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: AirQuality2Click_I2CSaveConfig
    ****************************************************************************//**
    *
    *  Enables AirQuality2Click_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void AirQuality2Click_I2CSaveConfig(void)
    {
    #if (!AirQuality2Click_CY_SCBIP_V0)
        #if (AirQuality2Click_I2C_MULTI_MASTER_SLAVE_CONST && AirQuality2Click_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (AirQuality2Click_CTRL_REG & AirQuality2Click_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                AirQuality2Click_Stop();
                AirQuality2Click_CTRL_REG |= AirQuality2Click_CTRL_EC_AM_MODE;
                AirQuality2Click_Enable();
            }
        #endif /* (AirQuality2Click_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (AirQuality2Click_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            AirQuality2Click_SCBCLK_Stop();
        #endif /* (AirQuality2Click_SCB_CLK_INTERNAL) */
    #endif /* (!AirQuality2Click_CY_SCBIP_V0) */

        AirQuality2Click_SetI2CExtClkInterruptMode(AirQuality2Click_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: AirQuality2Click_I2CRestoreConfig
    ****************************************************************************//**
    *
    *  Disables AirQuality2Click_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void AirQuality2Click_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        AirQuality2Click_SetI2CExtClkInterruptMode(AirQuality2Click_NO_INTR_SOURCES);

    #if (!AirQuality2Click_CY_SCBIP_V0)
        #if (AirQuality2Click_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            AirQuality2Click_SCBCLK_Start();
        #endif /* (AirQuality2Click_SCB_CLK_INTERNAL) */
    #endif /* (!AirQuality2Click_CY_SCBIP_V0) */
    }
#endif /* (AirQuality2Click_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
