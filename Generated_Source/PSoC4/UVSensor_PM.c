/***************************************************************************//**
* \file UVSensor_PM.c
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

#include "UVSensor.h"
#include "UVSensor_PVT.h"

#if(UVSensor_SCB_MODE_I2C_INC)
    #include "UVSensor_I2C_PVT.h"
#endif /* (UVSensor_SCB_MODE_I2C_INC) */

#if(UVSensor_SCB_MODE_EZI2C_INC)
    #include "UVSensor_EZI2C_PVT.h"
#endif /* (UVSensor_SCB_MODE_EZI2C_INC) */

#if(UVSensor_SCB_MODE_SPI_INC || UVSensor_SCB_MODE_UART_INC)
    #include "UVSensor_SPI_UART_PVT.h"
#endif /* (UVSensor_SCB_MODE_SPI_INC || UVSensor_SCB_MODE_UART_INC) */


/***************************************
*   Backup Structure declaration
***************************************/

#if(UVSensor_SCB_MODE_UNCONFIG_CONST_CFG || \
   (UVSensor_SCB_MODE_I2C_CONST_CFG   && (!UVSensor_I2C_WAKE_ENABLE_CONST))   || \
   (UVSensor_SCB_MODE_EZI2C_CONST_CFG && (!UVSensor_EZI2C_WAKE_ENABLE_CONST)) || \
   (UVSensor_SCB_MODE_SPI_CONST_CFG   && (!UVSensor_SPI_WAKE_ENABLE_CONST))   || \
   (UVSensor_SCB_MODE_UART_CONST_CFG  && (!UVSensor_UART_WAKE_ENABLE_CONST)))

    UVSensor_BACKUP_STRUCT UVSensor_backup =
    {
        0u, /* enableState */
    };
#endif


/*******************************************************************************
* Function Name: UVSensor_Sleep
****************************************************************************//**
*
*  Prepares the UVSensor component to enter Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has an influence on this 
*  function implementation:
*  - Checked: configures the component to be wakeup source from Deep Sleep.
*  - Unchecked: stores the current component state (enabled or disabled) and 
*    disables the component. See SCB_Stop() function for details about component 
*    disabling.
*
*  Call the UVSensor_Sleep() function before calling the 
*  CyPmSysDeepSleep() function. 
*  Refer to the PSoC Creator System Reference Guide for more information about 
*  power management functions and Low power section of this document for the 
*  selected mode.
*
*  This function should not be called before entering Sleep.
*
*******************************************************************************/
void UVSensor_Sleep(void)
{
#if(UVSensor_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UVSensor_SCB_WAKE_ENABLE_CHECK)
    {
        if(UVSensor_SCB_MODE_I2C_RUNTM_CFG)
        {
            UVSensor_I2CSaveConfig();
        }
        else if(UVSensor_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UVSensor_EzI2CSaveConfig();
        }
    #if(!UVSensor_CY_SCBIP_V1)
        else if(UVSensor_SCB_MODE_SPI_RUNTM_CFG)
        {
            UVSensor_SpiSaveConfig();
        }
        else if(UVSensor_SCB_MODE_UART_RUNTM_CFG)
        {
            UVSensor_UartSaveConfig();
        }
    #endif /* (!UVSensor_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        UVSensor_backup.enableState = (uint8) UVSensor_GET_CTRL_ENABLED;

        if(0u != UVSensor_backup.enableState)
        {
            UVSensor_Stop();
        }
    }

#else

    #if (UVSensor_SCB_MODE_I2C_CONST_CFG && UVSensor_I2C_WAKE_ENABLE_CONST)
        UVSensor_I2CSaveConfig();

    #elif (UVSensor_SCB_MODE_EZI2C_CONST_CFG && UVSensor_EZI2C_WAKE_ENABLE_CONST)
        UVSensor_EzI2CSaveConfig();

    #elif (UVSensor_SCB_MODE_SPI_CONST_CFG && UVSensor_SPI_WAKE_ENABLE_CONST)
        UVSensor_SpiSaveConfig();

    #elif (UVSensor_SCB_MODE_UART_CONST_CFG && UVSensor_UART_WAKE_ENABLE_CONST)
        UVSensor_UartSaveConfig();

    #else

        UVSensor_backup.enableState = (uint8) UVSensor_GET_CTRL_ENABLED;

        if(0u != UVSensor_backup.enableState)
        {
            UVSensor_Stop();
        }

    #endif /* defined (UVSensor_SCB_MODE_I2C_CONST_CFG) && (UVSensor_I2C_WAKE_ENABLE_CONST) */

#endif /* (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: UVSensor_Wakeup
****************************************************************************//**
*
*  Prepares the UVSensor component for Active mode operation after 
*  Deep Sleep.
*  The “Enable wakeup from Deep Sleep Mode” selection has influence on this 
*  function implementation:
*  - Checked: restores the component Active mode configuration.
*  - Unchecked: enables the component if it was enabled before enter Deep Sleep.
*
*  This function should not be called after exiting Sleep.
*
*  \sideeffect
*   Calling the UVSensor_Wakeup() function without first calling the 
*   UVSensor_Sleep() function may produce unexpected behavior.
*
*******************************************************************************/
void UVSensor_Wakeup(void)
{
#if(UVSensor_SCB_MODE_UNCONFIG_CONST_CFG)

    if(UVSensor_SCB_WAKE_ENABLE_CHECK)
    {
        if(UVSensor_SCB_MODE_I2C_RUNTM_CFG)
        {
            UVSensor_I2CRestoreConfig();
        }
        else if(UVSensor_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            UVSensor_EzI2CRestoreConfig();
        }
    #if(!UVSensor_CY_SCBIP_V1)
        else if(UVSensor_SCB_MODE_SPI_RUNTM_CFG)
        {
            UVSensor_SpiRestoreConfig();
        }
        else if(UVSensor_SCB_MODE_UART_RUNTM_CFG)
        {
            UVSensor_UartRestoreConfig();
        }
    #endif /* (!UVSensor_CY_SCBIP_V1) */
        else
        {
            /* Unknown mode */
        }
    }
    else
    {
        if(0u != UVSensor_backup.enableState)
        {
            UVSensor_Enable();
        }
    }

#else

    #if (UVSensor_SCB_MODE_I2C_CONST_CFG  && UVSensor_I2C_WAKE_ENABLE_CONST)
        UVSensor_I2CRestoreConfig();

    #elif (UVSensor_SCB_MODE_EZI2C_CONST_CFG && UVSensor_EZI2C_WAKE_ENABLE_CONST)
        UVSensor_EzI2CRestoreConfig();

    #elif (UVSensor_SCB_MODE_SPI_CONST_CFG && UVSensor_SPI_WAKE_ENABLE_CONST)
        UVSensor_SpiRestoreConfig();

    #elif (UVSensor_SCB_MODE_UART_CONST_CFG && UVSensor_UART_WAKE_ENABLE_CONST)
        UVSensor_UartRestoreConfig();

    #else

        if(0u != UVSensor_backup.enableState)
        {
            UVSensor_Enable();
        }

    #endif /* (UVSensor_I2C_WAKE_ENABLE_CONST) */

#endif /* (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG) */
}


/* [] END OF FILE */
