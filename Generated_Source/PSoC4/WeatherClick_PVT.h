/***************************************************************************//**
* \file .h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PVT_WeatherClick_H)
#define CY_SCB_PVT_WeatherClick_H

#include "WeatherClick.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define WeatherClick_SetI2CExtClkInterruptMode(interruptMask) WeatherClick_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define WeatherClick_ClearI2CExtClkInterruptSource(interruptMask) WeatherClick_CLEAR_INTR_I2C_EC(interruptMask)
#define WeatherClick_GetI2CExtClkInterruptSource()                (WeatherClick_INTR_I2C_EC_REG)
#define WeatherClick_GetI2CExtClkInterruptMode()                  (WeatherClick_INTR_I2C_EC_MASK_REG)
#define WeatherClick_GetI2CExtClkInterruptSourceMasked()          (WeatherClick_INTR_I2C_EC_MASKED_REG)

#if (!WeatherClick_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define WeatherClick_SetSpiExtClkInterruptMode(interruptMask) \
                                                                WeatherClick_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define WeatherClick_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                WeatherClick_CLEAR_INTR_SPI_EC(interruptMask)
    #define WeatherClick_GetExtSpiClkInterruptSource()                 (WeatherClick_INTR_SPI_EC_REG)
    #define WeatherClick_GetExtSpiClkInterruptMode()                   (WeatherClick_INTR_SPI_EC_MASK_REG)
    #define WeatherClick_GetExtSpiClkInterruptSourceMasked()           (WeatherClick_INTR_SPI_EC_MASKED_REG)
#endif /* (!WeatherClick_CY_SCBIP_V1) */

#if(WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void WeatherClick_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (WeatherClick_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_WeatherClick_CUSTOM_INTR_HANDLER)
    extern cyisraddress WeatherClick_customIntrHandler;
#endif /* !defined (CY_REMOVE_WeatherClick_CUSTOM_INTR_HANDLER) */
#endif /* (WeatherClick_SCB_IRQ_INTERNAL) */

extern WeatherClick_BACKUP_STRUCT WeatherClick_backup;

#if(WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 WeatherClick_scbMode;
    extern uint8 WeatherClick_scbEnableWake;
    extern uint8 WeatherClick_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 WeatherClick_mode;
    extern uint8 WeatherClick_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * WeatherClick_rxBuffer;
    extern uint8   WeatherClick_rxDataBits;
    extern uint32  WeatherClick_rxBufferSize;

    extern volatile uint8 * WeatherClick_txBuffer;
    extern uint8   WeatherClick_txDataBits;
    extern uint32  WeatherClick_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 WeatherClick_numberOfAddr;
    extern uint8 WeatherClick_subAddrSize;
#endif /* (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (WeatherClick_SCB_MODE_I2C_CONST_CFG || \
        WeatherClick_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 WeatherClick_IntrTxMask;
#endif /* (! (WeatherClick_SCB_MODE_I2C_CONST_CFG || \
              WeatherClick_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define WeatherClick_SCB_MODE_I2C_RUNTM_CFG     (WeatherClick_SCB_MODE_I2C      == WeatherClick_scbMode)
    #define WeatherClick_SCB_MODE_SPI_RUNTM_CFG     (WeatherClick_SCB_MODE_SPI      == WeatherClick_scbMode)
    #define WeatherClick_SCB_MODE_UART_RUNTM_CFG    (WeatherClick_SCB_MODE_UART     == WeatherClick_scbMode)
    #define WeatherClick_SCB_MODE_EZI2C_RUNTM_CFG   (WeatherClick_SCB_MODE_EZI2C    == WeatherClick_scbMode)
    #define WeatherClick_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (WeatherClick_SCB_MODE_UNCONFIG == WeatherClick_scbMode)

    /* Defines wakeup enable */
    #define WeatherClick_SCB_WAKE_ENABLE_CHECK       (0u != WeatherClick_scbEnableWake)
#endif /* (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!WeatherClick_CY_SCBIP_V1)
    #define WeatherClick_SCB_PINS_NUMBER    (7u)
#else
    #define WeatherClick_SCB_PINS_NUMBER    (2u)
#endif /* (!WeatherClick_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_WeatherClick_H) */


/* [] END OF FILE */
