/***************************************************************************//**
* \file UVSensor_BOOT.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_UVSensor_H)
#define CY_SCB_BOOT_UVSensor_H

#include "UVSensor_PVT.h"

#if (UVSensor_SCB_MODE_I2C_INC)
    #include "UVSensor_I2C.h"
#endif /* (UVSensor_SCB_MODE_I2C_INC) */

#if (UVSensor_SCB_MODE_EZI2C_INC)
    #include "UVSensor_EZI2C.h"
#endif /* (UVSensor_SCB_MODE_EZI2C_INC) */

#if (UVSensor_SCB_MODE_SPI_INC || UVSensor_SCB_MODE_UART_INC)
    #include "UVSensor_SPI_UART.h"
#endif /* (UVSensor_SCB_MODE_SPI_INC || UVSensor_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define UVSensor_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UVSensor) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (UVSensor_SCB_MODE_I2C_INC)
    #define UVSensor_I2C_BTLDR_COMM_ENABLED     (UVSensor_BTLDR_COMM_ENABLED && \
                                                            (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             UVSensor_I2C_SLAVE_CONST))
#else
     #define UVSensor_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (UVSensor_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (UVSensor_SCB_MODE_EZI2C_INC)
    #define UVSensor_EZI2C_BTLDR_COMM_ENABLED   (UVSensor_BTLDR_COMM_ENABLED && \
                                                         UVSensor_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define UVSensor_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (UVSensor_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (UVSensor_SCB_MODE_SPI_INC)
    #define UVSensor_SPI_BTLDR_COMM_ENABLED     (UVSensor_BTLDR_COMM_ENABLED && \
                                                            (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             UVSensor_SPI_SLAVE_CONST))
#else
        #define UVSensor_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (UVSensor_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (UVSensor_SCB_MODE_UART_INC)
       #define UVSensor_UART_BTLDR_COMM_ENABLED    (UVSensor_BTLDR_COMM_ENABLED && \
                                                            (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (UVSensor_UART_RX_DIRECTION && \
                                                              UVSensor_UART_TX_DIRECTION)))
#else
     #define UVSensor_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (UVSensor_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define UVSensor_BTLDR_COMM_MODE_ENABLED    (UVSensor_I2C_BTLDR_COMM_ENABLED   || \
                                                     UVSensor_SPI_BTLDR_COMM_ENABLED   || \
                                                     UVSensor_EZI2C_BTLDR_COMM_ENABLED || \
                                                     UVSensor_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UVSensor_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void UVSensor_I2CCyBtldrCommStart(void);
    void UVSensor_I2CCyBtldrCommStop (void);
    void UVSensor_I2CCyBtldrCommReset(void);
    cystatus UVSensor_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UVSensor_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (UVSensor_SCB_MODE_I2C_CONST_CFG)
        #define UVSensor_CyBtldrCommStart   UVSensor_I2CCyBtldrCommStart
        #define UVSensor_CyBtldrCommStop    UVSensor_I2CCyBtldrCommStop
        #define UVSensor_CyBtldrCommReset   UVSensor_I2CCyBtldrCommReset
        #define UVSensor_CyBtldrCommRead    UVSensor_I2CCyBtldrCommRead
        #define UVSensor_CyBtldrCommWrite   UVSensor_I2CCyBtldrCommWrite
    #endif /* (UVSensor_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UVSensor_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UVSensor_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void UVSensor_EzI2CCyBtldrCommStart(void);
    void UVSensor_EzI2CCyBtldrCommStop (void);
    void UVSensor_EzI2CCyBtldrCommReset(void);
    cystatus UVSensor_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UVSensor_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (UVSensor_SCB_MODE_EZI2C_CONST_CFG)
        #define UVSensor_CyBtldrCommStart   UVSensor_EzI2CCyBtldrCommStart
        #define UVSensor_CyBtldrCommStop    UVSensor_EzI2CCyBtldrCommStop
        #define UVSensor_CyBtldrCommReset   UVSensor_EzI2CCyBtldrCommReset
        #define UVSensor_CyBtldrCommRead    UVSensor_EzI2CCyBtldrCommRead
        #define UVSensor_CyBtldrCommWrite   UVSensor_EzI2CCyBtldrCommWrite
    #endif /* (UVSensor_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UVSensor_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UVSensor_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void UVSensor_SpiCyBtldrCommStart(void);
    void UVSensor_SpiCyBtldrCommStop (void);
    void UVSensor_SpiCyBtldrCommReset(void);
    cystatus UVSensor_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UVSensor_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (UVSensor_SCB_MODE_SPI_CONST_CFG)
        #define UVSensor_CyBtldrCommStart   UVSensor_SpiCyBtldrCommStart
        #define UVSensor_CyBtldrCommStop    UVSensor_SpiCyBtldrCommStop
        #define UVSensor_CyBtldrCommReset   UVSensor_SpiCyBtldrCommReset
        #define UVSensor_CyBtldrCommRead    UVSensor_SpiCyBtldrCommRead
        #define UVSensor_CyBtldrCommWrite   UVSensor_SpiCyBtldrCommWrite
    #endif /* (UVSensor_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UVSensor_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UVSensor_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void UVSensor_UartCyBtldrCommStart(void);
    void UVSensor_UartCyBtldrCommStop (void);
    void UVSensor_UartCyBtldrCommReset(void);
    cystatus UVSensor_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus UVSensor_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (UVSensor_SCB_MODE_UART_CONST_CFG)
        #define UVSensor_CyBtldrCommStart   UVSensor_UartCyBtldrCommStart
        #define UVSensor_CyBtldrCommStop    UVSensor_UartCyBtldrCommStop
        #define UVSensor_CyBtldrCommReset   UVSensor_UartCyBtldrCommReset
        #define UVSensor_CyBtldrCommRead    UVSensor_UartCyBtldrCommRead
        #define UVSensor_CyBtldrCommWrite   UVSensor_UartCyBtldrCommWrite
    #endif /* (UVSensor_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UVSensor_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (UVSensor_BTLDR_COMM_ENABLED)
    #if (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void UVSensor_CyBtldrCommStart(void);
        void UVSensor_CyBtldrCommStop (void);
        void UVSensor_CyBtldrCommReset(void);
        cystatus UVSensor_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus UVSensor_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (UVSensor_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UVSensor)
        #define CyBtldrCommStart    UVSensor_CyBtldrCommStart
        #define CyBtldrCommStop     UVSensor_CyBtldrCommStop
        #define CyBtldrCommReset    UVSensor_CyBtldrCommReset
        #define CyBtldrCommWrite    UVSensor_CyBtldrCommWrite
        #define CyBtldrCommRead     UVSensor_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_UVSensor) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (UVSensor_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define UVSensor_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define UVSensor_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define UVSensor_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define UVSensor_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef UVSensor_SPI_BYTE_TO_BYTE
    #define UVSensor_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef UVSensor_UART_BYTE_TO_BYTE
    #define UVSensor_UART_BYTE_TO_BYTE  (2500u)
#endif /* UVSensor_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_UVSensor_H) */


/* [] END OF FILE */
