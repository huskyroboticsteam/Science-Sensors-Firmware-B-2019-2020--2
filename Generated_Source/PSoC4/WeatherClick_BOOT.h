/***************************************************************************//**
* \file WeatherClick_BOOT.h
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

#if !defined(CY_SCB_BOOT_WeatherClick_H)
#define CY_SCB_BOOT_WeatherClick_H

#include "WeatherClick_PVT.h"

#if (WeatherClick_SCB_MODE_I2C_INC)
    #include "WeatherClick_I2C.h"
#endif /* (WeatherClick_SCB_MODE_I2C_INC) */

#if (WeatherClick_SCB_MODE_EZI2C_INC)
    #include "WeatherClick_EZI2C.h"
#endif /* (WeatherClick_SCB_MODE_EZI2C_INC) */

#if (WeatherClick_SCB_MODE_SPI_INC || WeatherClick_SCB_MODE_UART_INC)
    #include "WeatherClick_SPI_UART.h"
#endif /* (WeatherClick_SCB_MODE_SPI_INC || WeatherClick_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define WeatherClick_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_WeatherClick) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (WeatherClick_SCB_MODE_I2C_INC)
    #define WeatherClick_I2C_BTLDR_COMM_ENABLED     (WeatherClick_BTLDR_COMM_ENABLED && \
                                                            (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             WeatherClick_I2C_SLAVE_CONST))
#else
     #define WeatherClick_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (WeatherClick_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (WeatherClick_SCB_MODE_EZI2C_INC)
    #define WeatherClick_EZI2C_BTLDR_COMM_ENABLED   (WeatherClick_BTLDR_COMM_ENABLED && \
                                                         WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define WeatherClick_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (WeatherClick_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (WeatherClick_SCB_MODE_SPI_INC)
    #define WeatherClick_SPI_BTLDR_COMM_ENABLED     (WeatherClick_BTLDR_COMM_ENABLED && \
                                                            (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             WeatherClick_SPI_SLAVE_CONST))
#else
        #define WeatherClick_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (WeatherClick_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (WeatherClick_SCB_MODE_UART_INC)
       #define WeatherClick_UART_BTLDR_COMM_ENABLED    (WeatherClick_BTLDR_COMM_ENABLED && \
                                                            (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (WeatherClick_UART_RX_DIRECTION && \
                                                              WeatherClick_UART_TX_DIRECTION)))
#else
     #define WeatherClick_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (WeatherClick_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define WeatherClick_BTLDR_COMM_MODE_ENABLED    (WeatherClick_I2C_BTLDR_COMM_ENABLED   || \
                                                     WeatherClick_SPI_BTLDR_COMM_ENABLED   || \
                                                     WeatherClick_EZI2C_BTLDR_COMM_ENABLED || \
                                                     WeatherClick_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (WeatherClick_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void WeatherClick_I2CCyBtldrCommStart(void);
    void WeatherClick_I2CCyBtldrCommStop (void);
    void WeatherClick_I2CCyBtldrCommReset(void);
    cystatus WeatherClick_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus WeatherClick_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (WeatherClick_SCB_MODE_I2C_CONST_CFG)
        #define WeatherClick_CyBtldrCommStart   WeatherClick_I2CCyBtldrCommStart
        #define WeatherClick_CyBtldrCommStop    WeatherClick_I2CCyBtldrCommStop
        #define WeatherClick_CyBtldrCommReset   WeatherClick_I2CCyBtldrCommReset
        #define WeatherClick_CyBtldrCommRead    WeatherClick_I2CCyBtldrCommRead
        #define WeatherClick_CyBtldrCommWrite   WeatherClick_I2CCyBtldrCommWrite
    #endif /* (WeatherClick_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (WeatherClick_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (WeatherClick_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void WeatherClick_EzI2CCyBtldrCommStart(void);
    void WeatherClick_EzI2CCyBtldrCommStop (void);
    void WeatherClick_EzI2CCyBtldrCommReset(void);
    cystatus WeatherClick_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus WeatherClick_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (WeatherClick_SCB_MODE_EZI2C_CONST_CFG)
        #define WeatherClick_CyBtldrCommStart   WeatherClick_EzI2CCyBtldrCommStart
        #define WeatherClick_CyBtldrCommStop    WeatherClick_EzI2CCyBtldrCommStop
        #define WeatherClick_CyBtldrCommReset   WeatherClick_EzI2CCyBtldrCommReset
        #define WeatherClick_CyBtldrCommRead    WeatherClick_EzI2CCyBtldrCommRead
        #define WeatherClick_CyBtldrCommWrite   WeatherClick_EzI2CCyBtldrCommWrite
    #endif /* (WeatherClick_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (WeatherClick_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (WeatherClick_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void WeatherClick_SpiCyBtldrCommStart(void);
    void WeatherClick_SpiCyBtldrCommStop (void);
    void WeatherClick_SpiCyBtldrCommReset(void);
    cystatus WeatherClick_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus WeatherClick_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (WeatherClick_SCB_MODE_SPI_CONST_CFG)
        #define WeatherClick_CyBtldrCommStart   WeatherClick_SpiCyBtldrCommStart
        #define WeatherClick_CyBtldrCommStop    WeatherClick_SpiCyBtldrCommStop
        #define WeatherClick_CyBtldrCommReset   WeatherClick_SpiCyBtldrCommReset
        #define WeatherClick_CyBtldrCommRead    WeatherClick_SpiCyBtldrCommRead
        #define WeatherClick_CyBtldrCommWrite   WeatherClick_SpiCyBtldrCommWrite
    #endif /* (WeatherClick_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (WeatherClick_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (WeatherClick_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void WeatherClick_UartCyBtldrCommStart(void);
    void WeatherClick_UartCyBtldrCommStop (void);
    void WeatherClick_UartCyBtldrCommReset(void);
    cystatus WeatherClick_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus WeatherClick_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (WeatherClick_SCB_MODE_UART_CONST_CFG)
        #define WeatherClick_CyBtldrCommStart   WeatherClick_UartCyBtldrCommStart
        #define WeatherClick_CyBtldrCommStop    WeatherClick_UartCyBtldrCommStop
        #define WeatherClick_CyBtldrCommReset   WeatherClick_UartCyBtldrCommReset
        #define WeatherClick_CyBtldrCommRead    WeatherClick_UartCyBtldrCommRead
        #define WeatherClick_CyBtldrCommWrite   WeatherClick_UartCyBtldrCommWrite
    #endif /* (WeatherClick_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (WeatherClick_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (WeatherClick_BTLDR_COMM_ENABLED)
    #if (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void WeatherClick_CyBtldrCommStart(void);
        void WeatherClick_CyBtldrCommStop (void);
        void WeatherClick_CyBtldrCommReset(void);
        cystatus WeatherClick_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus WeatherClick_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (WeatherClick_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_WeatherClick)
        #define CyBtldrCommStart    WeatherClick_CyBtldrCommStart
        #define CyBtldrCommStop     WeatherClick_CyBtldrCommStop
        #define CyBtldrCommReset    WeatherClick_CyBtldrCommReset
        #define CyBtldrCommWrite    WeatherClick_CyBtldrCommWrite
        #define CyBtldrCommRead     WeatherClick_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_WeatherClick) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (WeatherClick_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define WeatherClick_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define WeatherClick_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define WeatherClick_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define WeatherClick_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef WeatherClick_SPI_BYTE_TO_BYTE
    #define WeatherClick_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef WeatherClick_UART_BYTE_TO_BYTE
    #define WeatherClick_UART_BYTE_TO_BYTE  (2500u)
#endif /* WeatherClick_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_WeatherClick_H) */


/* [] END OF FILE */
