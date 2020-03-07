/***************************************************************************//**
* \file SpectroscopySensor_PM.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Power Management support for
*  the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SpectroscopySensor.h"
#include "SpectroscopySensor_PVT.h"

#if(SpectroscopySensor_SCB_MODE_I2C_INC)
    #include "SpectroscopySensor_I2C_PVT.h"
#endif /* (SpectroscopySensor_SCB_MODE_I2C_INC) */

#if(SpectroscopySensor_SCB_MODE_EZI2C_INC)
    #include "SpectroscopySensor_EZI2C_PVT.h"
#endif /* (SpectroscopySensor_SCB_MODE_EZI2C_INC) */

#if(SpectroscopySensor_SCB_MODE_SPI_INC || SpectroscopySensor_SCB_MODE_UART_INC)
    #include "SpectroscopySensor_SPI_UART_PVT.h"
#endif /* (SpectroscopySensor_SCB_MODE_SPI_INC || SpectroscopySensor_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG || \
   (SpectroscopySensor_SCB_MODE_I2C_CONST_CFG   && (!SpectroscopySensor_I2C_WAKE_ENABLE_CONST))   || \
   (SpectroscopySensor_SCB_MODE_EZI2C_CONST_CFG && (!SpectroscopySensor_EZI2C_WAKE_ENABLE_CONST)) || \
   (SpectroscopySensor_SCB_MODE_SPI_CONST_CFG   && (!SpectroscopySensor_SPI_WAKE_ENABLE_CONST))   || \
   (SpectroscopySensor_SCB_MODE_UART_CONST_CFG  && (!SpectroscopySensor_UART_WAKE_ENABLE_CONST)))

    SpectroscopySensor_BACKUP_STRUCT SpectroscopySensor_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: SpectroscopySensor_Sleep
****************************************************************************//**
*
*  Prepares the SpectroscopySensor component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the SpectroscopySensor_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void SpectroscopySensor_Sleep(void)
{
#if(SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG)

    if(SpectroscopySensor_SCB_WAKE_ENABLE_CHECK)
    {
        if(SpectroscopySensor_SCB_MODE_I2C_RUNTM_CFG)
        {
            SpectroscopySensor_I2CSaveConfig();
        }
        else if(SpectroscopySensor_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            SpectroscopySensor_EzI2CSaveConfig();
        }
    #if(!SpectroscopySensor_CY_SCBIP_V1)
        else if(SpectroscopySensor_SCB_MODE_SPI_RUNTM_CFG)
        {
            SpectroscopySensor_SpiSaveConfig();
        }
        else if(SpectroscopySensor_SCB_MODE_UART_RUNTM_CFG)
        {
            SpectroscopySensor_UartSaveConfig();
        }
    #endif /* (!SpectroscopySensor_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        SpectroscopySensor_backup.enableState = (uint8) SpectroscopySensor_GET_CTRL_ENABLED;

        if(0u != SpectroscopySensor_backup.enableState)
        {
            SpectroscopySensor_Stop();
        }
    }

#else

    #if (SpectroscopySensor_SCB_MODE_I2C_CONST_CFG && SpectroscopySensor_I2C_WAKE_ENABLE_CONST)
        SpectroscopySensor_I2CSaveConfig();

    #elif (SpectroscopySensor_SCB_MODE_EZI2C_CONST_CFG && SpectroscopySensor_EZI2C_WAKE_ENABLE_CONST)
        SpectroscopySensor_EzI2CSaveConfig();

    #elif (SpectroscopySensor_SCB_MODE_SPI_CONST_CFG && SpectroscopySensor_SPI_WAKE_ENABLE_CONST)
        SpectroscopySensor_SpiSaveConfig();

    #elif (SpectroscopySensor_SCB_MODE_UART_CONST_CFG && SpectroscopySensor_UART_WAKE_ENABLE_CONST)
        SpectroscopySensor_UartSaveConfig();

    #else

        SpectroscopySensor_backup.enableState = (uint8) SpectroscopySensor_GET_CTRL_ENABLED;

        if(0u != SpectroscopySensor_backup.enableState)
        {
            SpectroscopySensor_Stop();
        }

    #endif /* defined (SpectroscopySensor_SCB_MODE_I2C_CONST_CFG) && (SpectroscopySensor_I2C_WAKE_ENABLE_CONST) */

#endif /* (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: SpectroscopySensor_Wakeup
****************************************************************************//**
*
*  Prepares the SpectroscopySensor component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the SpectroscopySensor_Wakeup() function without first calling the 
*   SpectroscopySensor_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void SpectroscopySensor_Wakeup(void)
{
#if(SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG)

    if(SpectroscopySensor_SCB_WAKE_ENABLE_CHECK)
    {
        if(SpectroscopySensor_SCB_MODE_I2C_RUNTM_CFG)
        {
            SpectroscopySensor_I2CRestoreConfig();
        }
        else if(SpectroscopySensor_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            SpectroscopySensor_EzI2CRestoreConfig();
        }
    #if(!SpectroscopySensor_CY_SCBIP_V1)
        else if(SpectroscopySensor_SCB_MODE_SPI_RUNTM_CFG)
        {
            SpectroscopySensor_SpiRestoreConfig();
        }
        else if(SpectroscopySensor_SCB_MODE_UART_RUNTM_CFG)
        {
            SpectroscopySensor_UartRestoreConfig();
        }
    #endif /* (!SpectroscopySensor_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != SpectroscopySensor_backup.enableState)
        {
            SpectroscopySensor_Enable();
        }
    }

#else

    #if (SpectroscopySensor_SCB_MODE_I2C_CONST_CFG  && SpectroscopySensor_I2C_WAKE_ENABLE_CONST)
        SpectroscopySensor_I2CRestoreConfig();

    #elif (SpectroscopySensor_SCB_MODE_EZI2C_CONST_CFG && SpectroscopySensor_EZI2C_WAKE_ENABLE_CONST)
        SpectroscopySensor_EzI2CRestoreConfig();

    #elif (SpectroscopySensor_SCB_MODE_SPI_CONST_CFG && SpectroscopySensor_SPI_WAKE_ENABLE_CONST)
        SpectroscopySensor_SpiRestoreConfig();

    #elif (SpectroscopySensor_SCB_MODE_UART_CONST_CFG && SpectroscopySensor_UART_WAKE_ENABLE_CONST)
        SpectroscopySensor_UartRestoreConfig();

    #else

        if(0u != SpectroscopySensor_backup.enableState)
        {
            SpectroscopySensor_Enable();
        }

    #endif /* (SpectroscopySensor_I2C_WAKE_ENABLE_CONST) */

#endif /* (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
