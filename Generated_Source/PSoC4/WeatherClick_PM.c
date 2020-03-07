/***************************************************************************//**
* \file WeatherClick_PM.c
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

#include "WeatherClick.h"
#include "WeatherClick_PVT.h"

#if(WeatherClick_SCB_MODE_I2C_INC)
    #include "WeatherClick_I2C_PVT.h"
#endif /* (WeatherClick_SCB_MODE_I2C_INC) */

#if(WeatherClick_SCB_MODE_EZI2C_INC)
    #include "WeatherClick_EZI2C_PVT.h"
#endif /* (WeatherClick_SCB_MODE_EZI2C_INC) */

#if(WeatherClick_SCB_MODE_SPI_INC || WeatherClick_SCB_MODE_UART_INC)
    #include "WeatherClick_SPI_UART_PVT.h"
#endif /* (WeatherClick_SCB_MODE_SPI_INC || WeatherClick_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG || \
   (WeatherClick_SCB_MODE_I2C_CONST_CFG   && (!WeatherClick_I2C_WAKE_ENABLE_CONST))   || \
   (WeatherClick_SCB_MODE_EZI2C_CONST_CFG && (!WeatherClick_EZI2C_WAKE_ENABLE_CONST)) || \
   (WeatherClick_SCB_MODE_SPI_CONST_CFG   && (!WeatherClick_SPI_WAKE_ENABLE_CONST))   || \
   (WeatherClick_SCB_MODE_UART_CONST_CFG  && (!WeatherClick_UART_WAKE_ENABLE_CONST)))

    WeatherClick_BACKUP_STRUCT WeatherClick_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: WeatherClick_Sleep
****************************************************************************//**
*
*  Prepares the WeatherClick component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the WeatherClick_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void WeatherClick_Sleep(void)
{
#if(WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG)

    if(WeatherClick_SCB_WAKE_ENABLE_CHECK)
    {
        if(WeatherClick_SCB_MODE_I2C_RUNTM_CFG)
        {
            WeatherClick_I2CSaveConfig();
        }
        else if(WeatherClick_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            WeatherClick_EzI2CSaveConfig();
        }
    #if(!WeatherClick_CY_SCBIP_V1)
        else if(WeatherClick_SCB_MODE_SPI_RUNTM_CFG)
        {
            WeatherClick_SpiSaveConfig();
        }
        else if(WeatherClick_SCB_MODE_UART_RUNTM_CFG)
        {
            WeatherClick_UartSaveConfig();
        }
    #endif /* (!WeatherClick_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        WeatherClick_backup.enableState = (uint8) WeatherClick_GET_CTRL_ENABLED;

        if(0u != WeatherClick_backup.enableState)
        {
            WeatherClick_Stop();
        }
    }

#else

    #if (WeatherClick_SCB_MODE_I2C_CONST_CFG && WeatherClick_I2C_WAKE_ENABLE_CONST)
        WeatherClick_I2CSaveConfig();

    #elif (WeatherClick_SCB_MODE_EZI2C_CONST_CFG && WeatherClick_EZI2C_WAKE_ENABLE_CONST)
        WeatherClick_EzI2CSaveConfig();

    #elif (WeatherClick_SCB_MODE_SPI_CONST_CFG && WeatherClick_SPI_WAKE_ENABLE_CONST)
        WeatherClick_SpiSaveConfig();

    #elif (WeatherClick_SCB_MODE_UART_CONST_CFG && WeatherClick_UART_WAKE_ENABLE_CONST)
        WeatherClick_UartSaveConfig();

    #else

        WeatherClick_backup.enableState = (uint8) WeatherClick_GET_CTRL_ENABLED;

        if(0u != WeatherClick_backup.enableState)
        {
            WeatherClick_Stop();
        }

    #endif /* defined (WeatherClick_SCB_MODE_I2C_CONST_CFG) && (WeatherClick_I2C_WAKE_ENABLE_CONST) */

#endif /* (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: WeatherClick_Wakeup
****************************************************************************//**
*
*  Prepares the WeatherClick component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the WeatherClick_Wakeup() function without first calling the 
*   WeatherClick_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void WeatherClick_Wakeup(void)
{
#if(WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG)

    if(WeatherClick_SCB_WAKE_ENABLE_CHECK)
    {
        if(WeatherClick_SCB_MODE_I2C_RUNTM_CFG)
        {
            WeatherClick_I2CRestoreConfig();
        }
        else if(WeatherClick_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            WeatherClick_EzI2CRestoreConfig();
        }
    #if(!WeatherClick_CY_SCBIP_V1)
        else if(WeatherClick_SCB_MODE_SPI_RUNTM_CFG)
        {
            WeatherClick_SpiRestoreConfig();
        }
        else if(WeatherClick_SCB_MODE_UART_RUNTM_CFG)
        {
            WeatherClick_UartRestoreConfig();
        }
    #endif /* (!WeatherClick_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != WeatherClick_backup.enableState)
        {
            WeatherClick_Enable();
        }
    }

#else

    #if (WeatherClick_SCB_MODE_I2C_CONST_CFG  && WeatherClick_I2C_WAKE_ENABLE_CONST)
        WeatherClick_I2CRestoreConfig();

    #elif (WeatherClick_SCB_MODE_EZI2C_CONST_CFG && WeatherClick_EZI2C_WAKE_ENABLE_CONST)
        WeatherClick_EzI2CRestoreConfig();

    #elif (WeatherClick_SCB_MODE_SPI_CONST_CFG && WeatherClick_SPI_WAKE_ENABLE_CONST)
        WeatherClick_SpiRestoreConfig();

    #elif (WeatherClick_SCB_MODE_UART_CONST_CFG && WeatherClick_UART_WAKE_ENABLE_CONST)
        WeatherClick_UartRestoreConfig();

    #else

        if(0u != WeatherClick_backup.enableState)
        {
            WeatherClick_Enable();
        }

    #endif /* (WeatherClick_I2C_WAKE_ENABLE_CONST) */

#endif /* (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
