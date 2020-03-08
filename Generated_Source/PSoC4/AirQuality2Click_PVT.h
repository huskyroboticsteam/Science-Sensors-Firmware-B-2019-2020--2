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

#if !defined(CY_SCB_PVT_AirQuality2Click_H)
#define CY_SCB_PVT_AirQuality2Click_H

#include "AirQuality2Click.h"


/***************************************
*     Private Function Prototypes
***************************************/

/* APIs to service INTR_I2C_EC register */
#define AirQuality2Click_SetI2CExtClkInterruptMode(interruptMask) AirQuality2Click_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define AirQuality2Click_ClearI2CExtClkInterruptSource(interruptMask) AirQuality2Click_CLEAR_INTR_I2C_EC(interruptMask)
#define AirQuality2Click_GetI2CExtClkInterruptSource()                (AirQuality2Click_INTR_I2C_EC_REG)
#define AirQuality2Click_GetI2CExtClkInterruptMode()                  (AirQuality2Click_INTR_I2C_EC_MASK_REG)
#define AirQuality2Click_GetI2CExtClkInterruptSourceMasked()          (AirQuality2Click_INTR_I2C_EC_MASKED_REG)

#if (!AirQuality2Click_CY_SCBIP_V1)
    /* APIs to service INTR_SPI_EC register */
    #define AirQuality2Click_SetSpiExtClkInterruptMode(interruptMask) \
                                                                AirQuality2Click_WRITE_INTR_SPI_EC_MASK(interruptMask)
    #define AirQuality2Click_ClearSpiExtClkInterruptSource(interruptMask) \
                                                                AirQuality2Click_CLEAR_INTR_SPI_EC(interruptMask)
    #define AirQuality2Click_GetExtSpiClkInterruptSource()                 (AirQuality2Click_INTR_SPI_EC_REG)
    #define AirQuality2Click_GetExtSpiClkInterruptMode()                   (AirQuality2Click_INTR_SPI_EC_MASK_REG)
    #define AirQuality2Click_GetExtSpiClkInterruptSourceMasked()           (AirQuality2Click_INTR_SPI_EC_MASKED_REG)
#endif /* (!AirQuality2Click_CY_SCBIP_V1) */

#if(AirQuality2Click_SCB_MODE_UNCONFIG_CONST_CFG)
    extern void AirQuality2Click_SetPins(uint32 mode, uint32 subMode, uint32 uartEnableMask);
#endif /* (AirQuality2Click_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*     Vars with External Linkage
***************************************/

#if (AirQuality2Click_SCB_IRQ_INTERNAL)
#if !defined (CY_REMOVE_AirQuality2Click_CUSTOM_INTR_HANDLER)
    extern cyisraddress AirQuality2Click_customIntrHandler;
#endif /* !defined (CY_REMOVE_AirQuality2Click_CUSTOM_INTR_HANDLER) */
#endif /* (AirQuality2Click_SCB_IRQ_INTERNAL) */

extern AirQuality2Click_BACKUP_STRUCT AirQuality2Click_backup;

#if(AirQuality2Click_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Common configuration variables */
    extern uint8 AirQuality2Click_scbMode;
    extern uint8 AirQuality2Click_scbEnableWake;
    extern uint8 AirQuality2Click_scbEnableIntr;

    /* I2C configuration variables */
    extern uint8 AirQuality2Click_mode;
    extern uint8 AirQuality2Click_acceptAddr;

    /* SPI/UART configuration variables */
    extern volatile uint8 * AirQuality2Click_rxBuffer;
    extern uint8   AirQuality2Click_rxDataBits;
    extern uint32  AirQuality2Click_rxBufferSize;

    extern volatile uint8 * AirQuality2Click_txBuffer;
    extern uint8   AirQuality2Click_txDataBits;
    extern uint32  AirQuality2Click_txBufferSize;

    /* EZI2C configuration variables */
    extern uint8 AirQuality2Click_numberOfAddr;
    extern uint8 AirQuality2Click_subAddrSize;
#endif /* (AirQuality2Click_SCB_MODE_UNCONFIG_CONST_CFG) */

#if (! (AirQuality2Click_SCB_MODE_I2C_CONST_CFG || \
        AirQuality2Click_SCB_MODE_EZI2C_CONST_CFG))
    extern uint16 AirQuality2Click_IntrTxMask;
#endif /* (! (AirQuality2Click_SCB_MODE_I2C_CONST_CFG || \
              AirQuality2Click_SCB_MODE_EZI2C_CONST_CFG)) */


/***************************************
*        Conditional Macro
****************************************/

#if(AirQuality2Click_SCB_MODE_UNCONFIG_CONST_CFG)
    /* Defines run time operation mode */
    #define AirQuality2Click_SCB_MODE_I2C_RUNTM_CFG     (AirQuality2Click_SCB_MODE_I2C      == AirQuality2Click_scbMode)
    #define AirQuality2Click_SCB_MODE_SPI_RUNTM_CFG     (AirQuality2Click_SCB_MODE_SPI      == AirQuality2Click_scbMode)
    #define AirQuality2Click_SCB_MODE_UART_RUNTM_CFG    (AirQuality2Click_SCB_MODE_UART     == AirQuality2Click_scbMode)
    #define AirQuality2Click_SCB_MODE_EZI2C_RUNTM_CFG   (AirQuality2Click_SCB_MODE_EZI2C    == AirQuality2Click_scbMode)
    #define AirQuality2Click_SCB_MODE_UNCONFIG_RUNTM_CFG \
                                                        (AirQuality2Click_SCB_MODE_UNCONFIG == AirQuality2Click_scbMode)

    /* Defines wakeup enable */
    #define AirQuality2Click_SCB_WAKE_ENABLE_CHECK       (0u != AirQuality2Click_scbEnableWake)
#endif /* (AirQuality2Click_SCB_MODE_UNCONFIG_CONST_CFG) */

/* Defines maximum number of SCB pins */
#if (!AirQuality2Click_CY_SCBIP_V1)
    #define AirQuality2Click_SCB_PINS_NUMBER    (7u)
#else
    #define AirQuality2Click_SCB_PINS_NUMBER    (2u)
#endif /* (!AirQuality2Click_CY_SCBIP_V1) */

#endif /* (CY_SCB_PVT_AirQuality2Click_H) */


/* [] END OF FILE */
