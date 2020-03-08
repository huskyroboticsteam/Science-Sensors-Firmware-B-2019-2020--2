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

#if !defined(CY_SCB_PVT_SpectroscopySensor_H)
#define CY_SCB_PVT_SpectroscopySensor_H

#include "SpectroscopySensor.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define SpectroscopySensor_SetI2CExtClkInterruptMode(interruptMask) SpectroscopySensor_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define SpectroscopySensor_ClearI2CExtClkInterruptSource(interruptMask) SpectroscopySensor_CLEAR_INTR_I2C_EC(interruptMask)
#define SpectroscopySensor_GetI2CExtClkInterruptSource()                (SpectroscopySensor_INTR_I2C_EC_REG)
#define SpectroscopySensor_GetI2CExtClkInterruptMode()                  (SpectroscopySensor_INTR_I2C_EC_MASK_REG)
#define SpectroscopySensor_GetI2CExtClkInterruptSourceMasked()          (SpectroscopySensor_INTR_I2C_EC_MASKED_REG)

#if (!SpectroscopySensor_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define SpectroscopySensor_SetSpiExtClkInterruptMode(interruptMask) \
                                                                SpectroscopySensor_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define SpectroscopySensor_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                SpectroscopySensor_CLEAR_INTR_SPI_EC(interruptMask)
    #define SpectroscopySensor_GetExtSpiClkInterruptSource()                 (SpectroscopySensor_INTR_SPI_EC_REG)
    #define SpectroscopySensor_GetExtSpiClkInterruptMode()                   (SpectroscopySensor_INTR_SPI_EC_MASK_REG)
    #define SpectroscopySensor_GetExtSpiClkInterruptSourceMasked()           (SpectroscopySensor_INTR_SPI_EC_MASKED_REG)
#endif /* (!SpectroscopySensor_CY_SCBIP_V1) */

#if(SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void SpectroscopySensor_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (SpectroscopySensor_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_SpectroscopySensor_CUSTOM_INTR_HANDLER)
    extern cyisraddress SpectroscopySensor_customIntrHandler;
#endif /* !defined (CY_REMOVE_SpectroscopySensor_CUSTOM_INTR_HANDLER) */
#endif /* (SpectroscopySensor_SCB_IRQ_INTERNAL) */

extern SpectroscopySensor_BACKUP_STRUCT SpectroscopySensor_backup;

#if(SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 SpectroscopySensor_scbMode;
    extern uint8 SpectroscopySensor_scbEnableWake;
    extern uint8 SpectroscopySensor_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 SpectroscopySensor_mode;
    extern uint8 SpectroscopySensor_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * SpectroscopySensor_rxBuffer;
    extern uint8   SpectroscopySensor_rxDataBits;
    extern uint32  SpectroscopySensor_rxBufferSize;

    extern volatile uint8 * SpectroscopySensor_txBuffer;
    extern uint8   SpectroscopySensor_txDataBits;
    extern uint32  SpectroscopySensor_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 SpectroscopySensor_numberOfAddr;
    extern uint8 SpectroscopySensor_subAddrSize;
#endif /* (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (SpectroscopySensor_SCB_MODE_I2C_CONST_CFG || \
        SpectroscopySensor_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 SpectroscopySensor_IntrTxMask;
#endif /* (! (SpectroscopySensor_SCB_MODE_I2C_CONST_CFG || \
              SpectroscopySensor_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define SpectroscopySensor_SCB_MODE_I2C_RUNTM_CFG     (SpectroscopySensor_SCB_MODE_I2C      == SpectroscopySensor_scbMode)
    #define SpectroscopySensor_SCB_MODE_SPI_RUNTM_CFG     (SpectroscopySensor_SCB_MODE_SPI      == SpectroscopySensor_scbMode)
    #define SpectroscopySensor_SCB_MODE_UART_RUNTM_CFG    (SpectroscopySensor_SCB_MODE_UART     == SpectroscopySensor_scbMode)
    #define SpectroscopySensor_SCB_MODE_EZI2C_RUNTM_CFG   (SpectroscopySensor_SCB_MODE_EZI2C    == SpectroscopySensor_scbMode)
    #define SpectroscopySensor_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (SpectroscopySensor_SCB_MODE_UNCONFIG == SpectroscopySensor_scbMode)

    /* Defines wakeup enable */
    #define SpectroscopySensor_SCB_WAKE_ENABLE_CHECK       (0u != SpectroscopySensor_scbEnableWake)
#endif /* (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!SpectroscopySensor_CY_SCBIP_V1)
    #define SpectroscopySensor_SCB_PINS_NUMBER    (7u)
#else
    #define SpectroscopySensor_SCB_PINS_NUMBER    (2u)
#endif /* (!SpectroscopySensor_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_SpectroscopySensor_H) */


/* [] END OF FILE */
