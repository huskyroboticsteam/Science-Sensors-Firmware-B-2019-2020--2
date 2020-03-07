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

#if !defined(CY_SCB_PVT_UVSensor_H)
#define CY_SCB_PVT_UVSensor_H

#include "UVSensor.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define UVSensor_SetI2CExtClkInterruptMode(interruptMask) UVSensor_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define UVSensor_ClearI2CExtClkInterruptSource(interruptMask) UVSensor_CLEAR_INTR_I2C_EC(interruptMask)
#define UVSensor_GetI2CExtClkInterruptSource()                (UVSensor_INTR_I2C_EC_REG)
#define UVSensor_GetI2CExtClkInterruptMode()                  (UVSensor_INTR_I2C_EC_MASK_REG)
#define UVSensor_GetI2CExtClkInterruptSourceMasked()          (UVSensor_INTR_I2C_EC_MASKED_REG)

#if (!UVSensor_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define UVSensor_SetSpiExtClkInterruptMode(interruptMask) \
                                                                UVSensor_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define UVSensor_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                UVSensor_CLEAR_INTR_SPI_EC(interruptMask)
    #define UVSensor_GetExtSpiClkInterruptSource()                 (UVSensor_INTR_SPI_EC_REG)
    #define UVSensor_GetExtSpiClkInterruptMode()                   (UVSensor_INTR_SPI_EC_MASK_REG)
    #define UVSensor_GetExtSpiClkInterruptSourceMasked()           (UVSensor_INTR_SPI_EC_MASKED_REG)
#endif /* (!UVSensor_CY_SCBIP_V1) */

#if(UVSensor_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void UVSensor_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (UVSensor_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_UVSensor_CUSTOM_INTR_HANDLER)
    extern cyisraddress UVSensor_customIntrHandler;
#endif /* !defined (CY_REMOVE_UVSensor_CUSTOM_INTR_HANDLER) */
#endif /* (UVSensor_SCB_IRQ_INTERNAL) */

extern UVSensor_BACKUP_STRUCT UVSensor_backup;

#if(UVSensor_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 UVSensor_scbMode;
    extern uint8 UVSensor_scbEnableWake;
    extern uint8 UVSensor_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 UVSensor_mode;
    extern uint8 UVSensor_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * UVSensor_rxBuffer;
    extern uint8   UVSensor_rxDataBits;
    extern uint32  UVSensor_rxBufferSize;

    extern volatile uint8 * UVSensor_txBuffer;
    extern uint8   UVSensor_txDataBits;
    extern uint32  UVSensor_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 UVSensor_numberOfAddr;
    extern uint8 UVSensor_subAddrSize;
#endif /* (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (UVSensor_SCB_MODE_I2C_CONST_CFG || \
        UVSensor_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 UVSensor_IntrTxMask;
#endif /* (! (UVSensor_SCB_MODE_I2C_CONST_CFG || \
              UVSensor_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(UVSensor_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define UVSensor_SCB_MODE_I2C_RUNTM_CFG     (UVSensor_SCB_MODE_I2C      == UVSensor_scbMode)
    #define UVSensor_SCB_MODE_SPI_RUNTM_CFG     (UVSensor_SCB_MODE_SPI      == UVSensor_scbMode)
    #define UVSensor_SCB_MODE_UART_RUNTM_CFG    (UVSensor_SCB_MODE_UART     == UVSensor_scbMode)
    #define UVSensor_SCB_MODE_EZI2C_RUNTM_CFG   (UVSensor_SCB_MODE_EZI2C    == UVSensor_scbMode)
    #define UVSensor_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (UVSensor_SCB_MODE_UNCONFIG == UVSensor_scbMode)

    /* Defines wakeup enable */
    #define UVSensor_SCB_WAKE_ENABLE_CHECK       (0u != UVSensor_scbEnableWake)
#endif /* (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!UVSensor_CY_SCBIP_V1)
    #define UVSensor_SCB_PINS_NUMBER    (7u)
#else
    #define UVSensor_SCB_PINS_NUMBER    (2u)
#endif /* (!UVSensor_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_UVSensor_H) */


/* [] END OF FILE */
