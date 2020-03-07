/***************************************************************************//**
* \file WeatherClick_I2C.c
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

#include "WeatherClick_PVT.h"
#include "WeatherClick_I2C_PVT.h"


/***************************************
*      I2C Private Vars
***************************************/

volatile uint8 WeatherClick_state;  /* Current state of I2C FSM */

#if(WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    /* Constant configuration of I2C */
    const WeatherClick_I2C_INIT_STRUCT WeatherClick_configI2C =
    {
        WeatherClick_I2C_MODE,
        WeatherClick_I2C_OVS_FACTOR_LOW,
        WeatherClick_I2C_OVS_FACTOR_HIGH,
        WeatherClick_I2C_MEDIAN_FILTER_ENABLE,
        WeatherClick_I2C_SLAVE_ADDRESS,
        WeatherClick_I2C_SLAVE_ADDRESS_MASK,
        WeatherClick_I2C_ACCEPT_ADDRESS,
        WeatherClick_I2C_WAKE_ENABLE,
        WeatherClick_I2C_BYTE_MODE_ENABLE,
        WeatherClick_I2C_DATA_RATE,
        WeatherClick_I2C_ACCEPT_GENERAL_CALL,
    };

    /*******************************************************************************
    * Function Name: WeatherClick_I2CInit
    ****************************************************************************//**
    *
    *
    *  Configures the WeatherClick for I2C operation.
    *
    *  This function is intended specifically to be used when the WeatherClick 
    *  configuration is set to “Unconfigured WeatherClick” in the customizer. 
    *  After initializing the WeatherClick in I2C mode using this function, 
    *  the component can be enabled using the WeatherClick_Start() or 
    * WeatherClick_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void WeatherClick_I2CInit(const WeatherClick_I2C_INIT_STRUCT *config)
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
            WeatherClick_SetPins(WeatherClick_SCB_MODE_I2C, WeatherClick_DUMMY_PARAM,
                                     WeatherClick_DUMMY_PARAM);

            /* Store internal configuration */
            WeatherClick_scbMode       = (uint8) WeatherClick_SCB_MODE_I2C;
            WeatherClick_scbEnableWake = (uint8) config->enableWake;
            WeatherClick_scbEnableIntr = (uint8) WeatherClick_SCB_IRQ_INTERNAL;

            WeatherClick_mode          = (uint8) config->mode;
            WeatherClick_acceptAddr    = (uint8) config->acceptAddr;

        #if (WeatherClick_CY_SCBIP_V0)
            /* Adjust SDA filter settings. Ticket ID#150521 */
            WeatherClick_SET_I2C_CFG_SDA_FILT_TRIM(WeatherClick_EC_AM_I2C_CFG_SDA_FILT_TRIM);
        #endif /* (WeatherClick_CY_SCBIP_V0) */

            /* Adjust AF and DF filter settings. Ticket ID#176179 */
            if (((WeatherClick_I2C_MODE_SLAVE != config->mode) &&
                 (config->dataRate <= WeatherClick_I2C_DATA_RATE_FS_MODE_MAX)) ||
                 (WeatherClick_I2C_MODE_SLAVE == config->mode))
            {
                /* AF = 1, DF = 0 */
                WeatherClick_I2C_CFG_ANALOG_FITER_ENABLE;
                medianFilter = WeatherClick_DIGITAL_FILTER_DISABLE;
            }
            else
            {
                /* AF = 0, DF = 1 */
                WeatherClick_I2C_CFG_ANALOG_FITER_DISABLE;
                medianFilter = WeatherClick_DIGITAL_FILTER_ENABLE;
            }

        #if (!WeatherClick_CY_SCBIP_V0)
            locEnableWake = (WeatherClick_I2C_MULTI_MASTER_SLAVE) ? (0u) : (config->enableWake);
        #else
            locEnableWake = config->enableWake;
        #endif /* (!WeatherClick_CY_SCBIP_V0) */

            /* Configure I2C interface */
            WeatherClick_CTRL_REG     = WeatherClick_GET_CTRL_BYTE_MODE  (config->enableByteMode) |
                                            WeatherClick_GET_CTRL_ADDR_ACCEPT(config->acceptAddr)     |
                                            WeatherClick_GET_CTRL_EC_AM_MODE (locEnableWake);

            WeatherClick_I2C_CTRL_REG = WeatherClick_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                    WeatherClick_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)                          |
                    WeatherClick_GET_I2C_CTRL_S_GENERAL_IGNORE((uint32)(0u == config->acceptGeneralAddr))    |
                    WeatherClick_GET_I2C_CTRL_SL_MSTR_MODE  (config->mode);

            /* Configure RX direction */
            WeatherClick_RX_CTRL_REG      = WeatherClick_GET_RX_CTRL_MEDIAN(medianFilter) |
                                                WeatherClick_I2C_RX_CTRL;
            WeatherClick_RX_FIFO_CTRL_REG = WeatherClick_CLEAR_REG;

            /* Set default address and mask */
            WeatherClick_RX_MATCH_REG    = ((WeatherClick_I2C_SLAVE) ?
                                                (WeatherClick_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                                 WeatherClick_GET_RX_MATCH_MASK(config->slaveAddrMask)) :
                                                (WeatherClick_CLEAR_REG));


            /* Configure TX direction */
            WeatherClick_TX_CTRL_REG      = WeatherClick_I2C_TX_CTRL;
            WeatherClick_TX_FIFO_CTRL_REG = WeatherClick_CLEAR_REG;

            /* Configure interrupt with I2C handler but do not enable it */
            CyIntDisable    (WeatherClick_ISR_NUMBER);
            CyIntSetPriority(WeatherClick_ISR_NUMBER, WeatherClick_ISR_PRIORITY);
            (void) CyIntSetVector(WeatherClick_ISR_NUMBER, &WeatherClick_I2C_ISR);

            /* Configure interrupt sources */
        #if(!WeatherClick_CY_SCBIP_V1)
            WeatherClick_INTR_SPI_EC_MASK_REG = WeatherClick_NO_INTR_SOURCES;
        #endif /* (!WeatherClick_CY_SCBIP_V1) */

            WeatherClick_INTR_I2C_EC_MASK_REG = WeatherClick_NO_INTR_SOURCES;
            WeatherClick_INTR_RX_MASK_REG     = WeatherClick_NO_INTR_SOURCES;
            WeatherClick_INTR_TX_MASK_REG     = WeatherClick_NO_INTR_SOURCES;

            WeatherClick_INTR_SLAVE_MASK_REG  = ((WeatherClick_I2C_SLAVE) ?
                            (WeatherClick_GET_INTR_SLAVE_I2C_GENERAL(config->acceptGeneralAddr) |
                             WeatherClick_I2C_INTR_SLAVE_MASK) : (WeatherClick_CLEAR_REG));

            WeatherClick_INTR_MASTER_MASK_REG = WeatherClick_NO_INTR_SOURCES;

            /* Configure global variables */
            WeatherClick_state = WeatherClick_I2C_FSM_IDLE;

            /* Internal slave variables */
            WeatherClick_slStatus        = 0u;
            WeatherClick_slRdBufIndex    = 0u;
            WeatherClick_slWrBufIndex    = 0u;
            WeatherClick_slOverFlowCount = 0u;

            /* Internal master variables */
            WeatherClick_mstrStatus     = 0u;
            WeatherClick_mstrRdBufIndex = 0u;
            WeatherClick_mstrWrBufIndex = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: WeatherClick_I2CInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the I2C operation.
    *
    *******************************************************************************/
    void WeatherClick_I2CInit(void)
    {
    #if(WeatherClick_CY_SCBIP_V0)
        /* Adjust SDA filter settings. Ticket ID#150521 */
        WeatherClick_SET_I2C_CFG_SDA_FILT_TRIM(WeatherClick_EC_AM_I2C_CFG_SDA_FILT_TRIM);
    #endif /* (WeatherClick_CY_SCBIP_V0) */

        /* Adjust AF and DF filter settings. Ticket ID#176179 */
        WeatherClick_I2C_CFG_ANALOG_FITER_ENABLE_ADJ;

        /* Configure I2C interface */
        WeatherClick_CTRL_REG     = WeatherClick_I2C_DEFAULT_CTRL;
        WeatherClick_I2C_CTRL_REG = WeatherClick_I2C_DEFAULT_I2C_CTRL;

        /* Configure RX direction */
        WeatherClick_RX_CTRL_REG      = WeatherClick_I2C_DEFAULT_RX_CTRL;
        WeatherClick_RX_FIFO_CTRL_REG = WeatherClick_I2C_DEFAULT_RX_FIFO_CTRL;

        /* Set default address and mask */
        WeatherClick_RX_MATCH_REG     = WeatherClick_I2C_DEFAULT_RX_MATCH;

        /* Configure TX direction */
        WeatherClick_TX_CTRL_REG      = WeatherClick_I2C_DEFAULT_TX_CTRL;
        WeatherClick_TX_FIFO_CTRL_REG = WeatherClick_I2C_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with I2C handler but do not enable it */
        CyIntDisable    (WeatherClick_ISR_NUMBER);
        CyIntSetPriority(WeatherClick_ISR_NUMBER, WeatherClick_ISR_PRIORITY);
    #if(!WeatherClick_I2C_EXTERN_INTR_HANDLER)
        (void) CyIntSetVector(WeatherClick_ISR_NUMBER, &WeatherClick_I2C_ISR);
    #endif /* (WeatherClick_I2C_EXTERN_INTR_HANDLER) */

        /* Configure interrupt sources */
    #if(!WeatherClick_CY_SCBIP_V1)
        WeatherClick_INTR_SPI_EC_MASK_REG = WeatherClick_I2C_DEFAULT_INTR_SPI_EC_MASK;
    #endif /* (!WeatherClick_CY_SCBIP_V1) */

        WeatherClick_INTR_I2C_EC_MASK_REG = WeatherClick_I2C_DEFAULT_INTR_I2C_EC_MASK;
        WeatherClick_INTR_SLAVE_MASK_REG  = WeatherClick_I2C_DEFAULT_INTR_SLAVE_MASK;
        WeatherClick_INTR_MASTER_MASK_REG = WeatherClick_I2C_DEFAULT_INTR_MASTER_MASK;
        WeatherClick_INTR_RX_MASK_REG     = WeatherClick_I2C_DEFAULT_INTR_RX_MASK;
        WeatherClick_INTR_TX_MASK_REG     = WeatherClick_I2C_DEFAULT_INTR_TX_MASK;

        /* Configure global variables */
        WeatherClick_state = WeatherClick_I2C_FSM_IDLE;

    #if(WeatherClick_I2C_SLAVE)
        /* Internal slave variable */
        WeatherClick_slStatus        = 0u;
        WeatherClick_slRdBufIndex    = 0u;
        WeatherClick_slWrBufIndex    = 0u;
        WeatherClick_slOverFlowCount = 0u;
    #endif /* (WeatherClick_I2C_SLAVE) */

    #if(WeatherClick_I2C_MASTER)
    /* Internal master variable */
        WeatherClick_mstrStatus     = 0u;
        WeatherClick_mstrRdBufIndex = 0u;
        WeatherClick_mstrWrBufIndex = 0u;
    #endif /* (WeatherClick_I2C_MASTER) */
    }
#endif /* (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: WeatherClick_I2CStop
****************************************************************************//**
*
*  Resets the I2C FSM into the default state.
*
*******************************************************************************/
void WeatherClick_I2CStop(void)
{
    /* Clear command registers because they keep assigned value after IP block was disabled */
    WeatherClick_I2C_MASTER_CMD_REG = 0u;
    WeatherClick_I2C_SLAVE_CMD_REG  = 0u;
    
    WeatherClick_state = WeatherClick_I2C_FSM_IDLE;
}


/*******************************************************************************
* Function Name: WeatherClick_I2CFwBlockReset
****************************************************************************//**
*
* Resets the scb IP block and I2C into the known state.
*
*******************************************************************************/
void WeatherClick_I2CFwBlockReset(void)
{
    /* Disable scb IP: stop respond to I2C traffic */
    WeatherClick_CTRL_REG &= (uint32) ~WeatherClick_CTRL_ENABLED;

    /* Clear command registers they are not cleared after scb IP is disabled */
    WeatherClick_I2C_MASTER_CMD_REG = 0u;
    WeatherClick_I2C_SLAVE_CMD_REG  = 0u;

    WeatherClick_DISABLE_AUTO_DATA;

    WeatherClick_SetTxInterruptMode(WeatherClick_NO_INTR_SOURCES);
    WeatherClick_SetRxInterruptMode(WeatherClick_NO_INTR_SOURCES);
    
#if(WeatherClick_CY_SCBIP_V0)
    /* Clear interrupt sources as they are not cleared after scb IP is disabled */
    WeatherClick_ClearTxInterruptSource    (WeatherClick_INTR_TX_ALL);
    WeatherClick_ClearRxInterruptSource    (WeatherClick_INTR_RX_ALL);
    WeatherClick_ClearSlaveInterruptSource (WeatherClick_INTR_SLAVE_ALL);
    WeatherClick_ClearMasterInterruptSource(WeatherClick_INTR_MASTER_ALL);
#endif /* (WeatherClick_CY_SCBIP_V0) */

    WeatherClick_state = WeatherClick_I2C_FSM_IDLE;

    /* Enable scb IP: start respond to I2C traffic */
    WeatherClick_CTRL_REG |= (uint32) WeatherClick_CTRL_ENABLED;
}


#if(WeatherClick_I2C_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: WeatherClick_I2CSaveConfig
    ****************************************************************************//**
    *
    *  Enables WeatherClick_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void WeatherClick_I2CSaveConfig(void)
    {
    #if (!WeatherClick_CY_SCBIP_V0)
        #if (WeatherClick_I2C_MULTI_MASTER_SLAVE_CONST && WeatherClick_I2C_WAKE_ENABLE_CONST)
            /* Enable externally clocked address match if it was not enabled before.
            * This applicable only for Multi-Master-Slave. Ticket ID#192742 */
            if (0u == (WeatherClick_CTRL_REG & WeatherClick_CTRL_EC_AM_MODE))
            {
                /* Enable external address match logic */
                WeatherClick_Stop();
                WeatherClick_CTRL_REG |= WeatherClick_CTRL_EC_AM_MODE;
                WeatherClick_Enable();
            }
        #endif /* (WeatherClick_I2C_MULTI_MASTER_SLAVE_CONST) */

        #if (WeatherClick_SCB_CLK_INTERNAL)
            /* Disable clock to internal address match logic. Ticket ID#187931 */
            WeatherClick_SCBCLK_Stop();
        #endif /* (WeatherClick_SCB_CLK_INTERNAL) */
    #endif /* (!WeatherClick_CY_SCBIP_V0) */

        WeatherClick_SetI2CExtClkInterruptMode(WeatherClick_INTR_I2C_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: WeatherClick_I2CRestoreConfig
    ****************************************************************************//**
    *
    *  Disables WeatherClick_INTR_I2C_EC_WAKE_UP interrupt source. This interrupt
    *  triggers on address match and wakes up device.
    *
    *******************************************************************************/
    void WeatherClick_I2CRestoreConfig(void)
    {
        /* Disable wakeup interrupt on address match */
        WeatherClick_SetI2CExtClkInterruptMode(WeatherClick_NO_INTR_SOURCES);

    #if (!WeatherClick_CY_SCBIP_V0)
        #if (WeatherClick_SCB_CLK_INTERNAL)
            /* Enable clock to internal address match logic. Ticket ID#187931 */
            WeatherClick_SCBCLK_Start();
        #endif /* (WeatherClick_SCB_CLK_INTERNAL) */
    #endif /* (!WeatherClick_CY_SCBIP_V0) */
    }
#endif /* (WeatherClick_I2C_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
