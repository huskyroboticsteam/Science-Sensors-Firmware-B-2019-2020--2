/***************************************************************************//**
* \file SpectroscopySensor_I2C.c
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

#include "SpectroscopySensor_PVT.h"
#include "SpectroscopySensor_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 SpectroscopySensor_state;  /* Current state of I2C FSM */

#if(SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const SpectroscopySensor_I2C_INIT_STRUCT SpectroscopySensor_configI2C =
    {
        SpectroscopySensor_I2C_MODE,
        SpectroscopySensor_I2C_OVS_FACTOR_LOW,
        SpectroscopySensor_I2C_OVS_FACTOR_HIGH,
        SpectroscopySensor_I2C_MEDIAN_FILTER_ENABLE,
        SpectroscopySensor_I2C_SLAVE_ADDRESS,
        SpectroscopySensor_I2C_SLAVE_ADDRESS_MASK,
        SpectroscopySensor_I2C_ACCEPT_ADDRESS,
        SpectroscopySensor_I2C_WAKE_ENABLE,
        SpectroscopySensor_I2C_BYTE_MODE_ENABLE,
        SpectroscopySensor_I2C_DATA_RATE,
        SpectroscopySensor_I2C_ACCEPT_GENERAL_CALL,
    };

    /*******************************************************************************
    * Function Name: SpectroscopySensor_I2CInit
    ****************************************************************************//**
    *
    *
    *  Configures the SpectroscopySensor for I2C operation.
    *
    *  This function is intended specifically to be used when the SpectroscopySensor 
    *  configuration is set to “Unconfigured SpectroscopySensor” in the customizer. 
    *  After initializing the SpectroscopySensor in I2C mode using this function, 
    *  the component can be enabled using the SpectroscopySensor_Start() or 
    * SpectroscopySensor_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void SpectroscopySensor_I2CInit(const SpectroscopySensor_I2C_INIT_STRUCT *config)
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
            SpectroscopySensor_SetPins(SpectroscopySensor_SCB_MODE_I2C, SpectroscopySensor_DUMMY_PARAM,
                                     SpectroscopySensor_DUMMY_PARAM);

            /* Store internal configuration */
            SpectroscopySensor_scbMode       = (uint8) SpectroscopySensor_SCB_MODE_I2C;
            SpectroscopySensor_scbEnableWake = (uint8) config->enableWake;
            SpectroscopySensor_scbEnableIntr = (uint8) SpectroscopySensor_SCB_IRQ_INTERNAL;

            SpectroscopySensor_mode          = (uint8) config->mode;
            SpectroscopySensor_acceptAddr    = (uint8) config->acceptAddr;

        #if (SpectroscopySensor_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            SpectroscopySensor_SET_I2C_CFG_SDA_FILT_TRIM(SpectroscopySensor_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (SpectroscopySensor_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((SpectroscopySensor_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= SpectroscopySensor_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (SpectroscopySensor_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                SpectroscopySensor_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = SpectroscopySensor_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                SpectroscopySensor_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = SpectroscopySensor_DIGITAL_FILTER_ENABLE;
            }

        #if (!SpectroscopySensor_CY_SCBIP_V0)
            locEnableWake = (SpectroscopySensor_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!SpectroscopySensor_CY_SCBIP_V0) */

            /* Configure I2C interface */
            SpectroscopySensor_CTRL_REG     = SpectroscopySensor_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            SpectroscopySensor_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            SpectroscopySensor_GET_CTRL_EC_AM_MODE (locEnableWake);

            SpectroscopySensor_I2C_CTRL_REG = SpectroscopySensor_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                    SpectroscopySensor_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)                          |
                    SpectroscopySensor_GET_I2C_CTRL_S_GENERAL_IGNORE((uint32)(0u == config->acceptGeneralAddr))    |
                    SpectroscopySensor_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode);

            /* Configure RX direction */
            SpectroscopySensor_RX_CTRL_REG      = SpectroscopySensor_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                SpectroscopySensor_I2C_RX_CTRL;
            SpectroscopySensor_RX_FIFO_CTRL_REG = SpectroscopySensor_CLEAR_REG;

            /* Set default address and mask */
            SpectroscopySensor_RX_MATCH_REG    = ((SpectroscopySensor_I2C_SLAVE) ?
                                                (SpectroscopySensor_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 SpectroscopySensor_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (SpectroscopySensor_CLEAR_REG));


            /* Configure TX direction */
            SpectroscopySensor_TX_CTRL_REG      = SpectroscopySensor_I2C_TX_CTRL;
            SpectroscopySensor_TX_FIFO_CTRL_REG = SpectroscopySensor_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (SpectroscopySensor_ISR_NUMBER);
            CyIntSetPriority(SpectroscopySensor_ISR_NUMBER, SpectroscopySensor_ISR_PRIORITY);
            (void) CyIntSetVector(SpectroscopySensor_ISR_NUMBER, &SpectroscopySensor_I2C_ISR);

            /* Configure interrupt sources */
        #if(!SpectroscopySensor_CY_SCBIP_V1)
            SpectroscopySensor_INTR_SPI_EC_MASK_REG = SpectroscopySensor_NO_INTR_SOURCES;
        #endif /* (!SpectroscopySensor_CY_SCBIP_V1) */

            SpectroscopySensor_INTR_I2C_EC_MASK_REG = SpectroscopySensor_NO_INTR_SOURCES;
            SpectroscopySensor_INTR_RX_MASK_REG     = SpectroscopySensor_NO_INTR_SOURCES;
            SpectroscopySensor_INTR_TX_MASK_REG     = SpectroscopySensor_NO_INTR_SOURCES;

            SpectroscopySensor_INTR_SLAVE_MASK_REG  = ((SpectroscopySensor_I2C_SLAVE) ?
                            (SpectroscopySensor_GET_INTR_SLAVE_I2C_GENERAL(config->acceptGeneralAddr) |
                             SpectroscopySensor_I2C_INTR_SLAVE_MASK) : (SpectroscopySensor_CLEAR_REG));

            SpectroscopySensor_INTR_MASTER_MASK_REG = SpectroscopySensor_NO_INTR_SOURCES;

            /* Configure global variables */
            SpectroscopySensor_state = SpectroscopySensor_I2C_FSM_IDLE;

            /* Internal slave variables */
            SpectroscopySensor_slStatus        = 0u;
            SpectroscopySensor_slRdBufIndex    = 0u;
            SpectroscopySensor_slWrBufIndex    = 0u;
            SpectroscopySensor_slOverFlowCount = 0u;

            /* Internal master variables */
            SpectroscopySensor_mstrStatus     = 0u;
            SpectroscopySensor_mstrRdBufIndex = 0u;
            SpectroscopySensor_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: SpectroscopySensor_I2CInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the I2C operation.
    *
    *******************************************************************************/
    void SpectroscopySensor_I2CInit(void)
    {
    #if(SpectroscopySensor_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        SpectroscopySensor_SET_I2C_CFG_SDA_FILT_TRIM(SpectroscopySensor_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (SpectroscopySensor_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        SpectroscopySensor_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        SpectroscopySensor_CTRL_REG     = SpectroscopySensor_I2C_DEFAULT_CTRL;
        SpectroscopySensor_I2C_CTRL_REG = SpectroscopySensor_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        SpectroscopySensor_RX_CTRL_REG      = SpectroscopySensor_I2C_DEFAULT_RX_CTRL;
        SpectroscopySensor_RX_FIFO_CTRL_REG = SpectroscopySensor_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        SpectroscopySensor_RX_MATCH_REG     = SpectroscopySensor_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        SpectroscopySensor_TX_CTRL_REG      = SpectroscopySensor_I2C_DEFAULT_TX_CTRL;
        SpectroscopySensor_TX_FIFO_CTRL_REG = SpectroscopySensor_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (SpectroscopySensor_ISR_NUMBER);
        CyIntSetPriority(SpectroscopySensor_ISR_NUMBER, SpectroscopySensor_ISR_PRIORITY);
    #if(!SpectroscopySensor_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(SpectroscopySensor_ISR_NUMBER, &SpectroscopySensor_I2C_ISR);
    #endif /* (SpectroscopySensor_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!SpectroscopySensor_CY_SCBIP_V1)
        SpectroscopySensor_INTR_SPI_EC_MASK_REG = SpectroscopySensor_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!SpectroscopySensor_CY_SCBIP_V1) */

        SpectroscopySensor_INTR_I2C_EC_MASK_REG = SpectroscopySensor_I2C_DEFAULT_INTR_I2C_EC_MASK;
        SpectroscopySensor_INTR_SLAVE_MASK_REG  = SpectroscopySensor_I2C_DEFAULT_INTR_SLAVE_MASK;
        SpectroscopySensor_INTR_MASTER_MASK_REG = SpectroscopySensor_I2C_DEFAULT_INTR_MASTER_MASK;
        SpectroscopySensor_INTR_RX_MASK_REG     = SpectroscopySensor_I2C_DEFAULT_INTR_RX_MASK;
        SpectroscopySensor_INTR_TX_MASK_REG     = SpectroscopySensor_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        SpectroscopySensor_state = SpectroscopySensor_I2C_FSM_IDLE;

    #if(SpectroscopySensor_I2C_SLAVE)
        /* Internal slave variable */
        SpectroscopySensor_slStatus        = 0u;
        SpectroscopySensor_slRdBufIndex    = 0u;
        SpectroscopySensor_slWrBufIndex    = 0u;
        SpectroscopySensor_slOverFlowCount = 0u;
    #endif /* (SpectroscopySensor_I2C_SLAVE) */

    #if(SpectroscopySensor_I2C_MASTER)
    /* Internal master variable */
        SpectroscopySensor_mstrStatus     = 0u;
        SpectroscopySensor_mstrRdBufIndex = 0u;
        SpectroscopySensor_mstrWrBufIndex = 0u;
    #endif /* (SpectroscopySensor_I2C_MASTER) */
    }
#endif /* (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: SpectroscopySensor_I2CStop
****************************************************************************//**
*
*  Resets the I2C FSM into the default state.
*
*******************************************************************************/
void SpectroscopySensor_I2CStop(void)
{
    /* Clear command registers because they keep assigned value after IP block was disabled */
    SpectroscopySensor_I2C_MASTER_CMD_REG = 0u;
    SpectroscopySensor_I2C_SLAVE_CMD_REG  = 0u;
    
    SpectroscopySensor_state = SpectroscopySensor_I2C_FSM_IDLE;
}


/*******************************************************************************
* Function Name: SpectroscopySensor_I2CFwBlockReset
****************************************************************************//**
*
* Resets the scb IP block and I2C into the known state.
*
*******************************************************************************/
void SpectroscopySensor_I2CFwBlockReset(void)
{
    /* Disable scb IP: stop respond to I2C traffic */
    SpectroscopySensor_CTRL_REG &= (uint32) ~SpectroscopySensor_CTRL_ENABLED;

    /* Clear command registers they are not cleared after scb IP is disabled */
    SpectroscopySensor_I2C_MASTER_CMD_REG = 0u;
    SpectroscopySensor_I2C_SLAVE_CMD_REG  = 0u;

    SpectroscopySensor_DISABLE_AUTO_DATA;

    SpectroscopySensor_SetTxInterruptMode(SpectroscopySensor_NO_INTR_SOURCES);
    SpectroscopySensor_SetRxInterruptMode(SpectroscopySensor_NO_INTR_SOURCES);
    
#if(SpectroscopySensor_CY_SCBIP_V0)
    /* Clear interrupt sources as they are not cleared after scb IP is disabled */
    SpectroscopySensor_ClearTxInterruptSource    (SpectroscopySensor_INTR_TX_ALL);
    SpectroscopySensor_ClearRxInterruptSource    (SpectroscopySensor_INTR_RX_ALL);
    SpectroscopySensor_ClearSlaveInterruptSource (SpectroscopySensor_INTR_SLAVE_ALL);
    SpectroscopySensor_ClearMasterInterruptSource(SpectroscopySensor_INTR_MASTER_ALL);
#endif /* (SpectroscopySensor_CY_SCBIP_V0) */

    SpectroscopySensor_state = SpectroscopySensor_I2C_FSM_IDLE;

    /* Enable scb IP: start respond to I2C traffic */
    SpectroscopySensor_CTRL_REG |= (uint32) SpectroscopySensor_CTRL_ENABLED;
}


#if(SpectroscopySensor_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: SpectroscopySensor_I2CSaveConfig
    ****************************************************************************//**
    *
    *  Enables SpectroscopySensor_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void SpectroscopySensor_I2CSaveConfig(void)
    {
    #if (!SpectroscopySensor_CY_SCBIP_V0)
        #if (SpectroscopySensor_I2C_MULTI_MASTER_SLAVE_CONST && SpectroscopySensor_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (SpectroscopySensor_CTRL_REG & SpectroscopySensor_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                SpectroscopySensor_Stop();
                SpectroscopySensor_CTRL_REG |= SpectroscopySensor_CTRL_EC_AM_MODE;
                SpectroscopySensor_Enable();
            }
        #endif /* (SpectroscopySensor_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (SpectroscopySensor_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            SpectroscopySensor_SCBCLK_Stop();
        #endif /* (SpectroscopySensor_SCB_CLK_INTERNAL) */
    #endif /* (!SpectroscopySensor_CY_SCBIP_V0) */

        SpectroscopySensor_SetI2CExtClkInterruptMode(SpectroscopySensor_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: SpectroscopySensor_I2CRestoreConfig
    ****************************************************************************//**
    *
    *  Disables SpectroscopySensor_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void SpectroscopySensor_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        SpectroscopySensor_SetI2CExtClkInterruptMode(SpectroscopySensor_NO_INTR_SOURCES);

    #if (!SpectroscopySensor_CY_SCBIP_V0)
        #if (SpectroscopySensor_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            SpectroscopySensor_SCBCLK_Start();
        #endif /* (SpectroscopySensor_SCB_CLK_INTERNAL) */
    #endif /* (!SpectroscopySensor_CY_SCBIP_V0) */
    }
#endif /* (SpectroscopySensor_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
