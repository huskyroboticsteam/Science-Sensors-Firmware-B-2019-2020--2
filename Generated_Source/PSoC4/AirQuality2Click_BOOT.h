/***************************************************************************//**
* \file AirQuality2Click_BOOT.h
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

#if !defined(CY_SCB_BOOT_AirQuality2Click_H)
#define CY_SCB_BOOT_AirQuality2Click_H

#include "AirQuality2Click_PVT.h"

#if (AirQuality2Click_SCB_MODE_I2C_INC)
    #include "AirQuality2Click_I2C.h"
#endif /* (AirQuality2Click_SCB_MODE_I2C_INC) */

#if (AirQuality2Click_SCB_MODE_EZI2C_INC)
    #include "AirQuality2Click_EZI2C.h"
#endif /* (AirQuality2Click_SCB_MODE_EZI2C_INC) */

#if (AirQuality2Click_SCB_MODE_SPI_INC || AirQuality2Click_SCB_MODE_UART_INC)
    #include "AirQuality2Click_SPI_UART.h"
#endif /* (AirQuality2Click_SCB_MODE_SPI_INC || AirQuality2Click_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define AirQuality2Click_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_AirQuality2Click) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (AirQuality2Click_SCB_MODE_I2C_INC)
    #define AirQuality2Click_I2C_BTLDR_COMM_ENABLED     (AirQuality2Click_BTLDR_COMM_ENABLED && \
                                                            (AirQuality2Click_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             AirQuality2Click_I2C_SLAVE_CONST))
#else
     #define AirQuality2Click_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (AirQuality2Click_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (AirQuality2Click_SCB_MODE_EZI2C_INC)
    #define AirQuality2Click_EZI2C_BTLDR_COMM_ENABLED   (AirQuality2Click_BTLDR_COMM_ENABLED && \
                                                         AirQuality2Click_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define AirQuality2Click_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (AirQuality2Click_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (AirQuality2Click_SCB_MODE_SPI_INC)
    #define AirQuality2Click_SPI_BTLDR_COMM_ENABLED     (AirQuality2Click_BTLDR_COMM_ENABLED && \
                                                            (AirQuality2Click_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             AirQuality2Click_SPI_SLAVE_CONST))
#else
        #define AirQuality2Click_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (AirQuality2Click_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (AirQuality2Click_SCB_MODE_UART_INC)
       #define AirQuality2Click_UART_BTLDR_COMM_ENABLED    (AirQuality2Click_BTLDR_COMM_ENABLED && \
                                                            (AirQuality2Click_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (AirQuality2Click_UART_RX_DIRECTION && \
                                                              AirQuality2Click_UART_TX_DIRECTION)))
#else
     #define AirQuality2Click_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (AirQuality2Click_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define AirQuality2Click_BTLDR_COMM_MODE_ENABLED    (AirQuality2Click_I2C_BTLDR_COMM_ENABLED   || \
                                                     AirQuality2Click_SPI_BTLDR_COMM_ENABLED   || \
                                                     AirQuality2Click_EZI2C_BTLDR_COMM_ENABLED || \
                                                     AirQuality2Click_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (AirQuality2Click_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void AirQuality2Click_I2CCyBtldrCommStart(void);
    void AirQuality2Click_I2CCyBtldrCommStop (void);
    void AirQuality2Click_I2CCyBtldrCommReset(void);
    cystatus AirQuality2Click_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus AirQuality2Click_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (AirQuality2Click_SCB_MODE_I2C_CONST_CFG)
        #define AirQuality2Click_CyBtldrCommStart   AirQuality2Click_I2CCyBtldrCommStart
        #define AirQuality2Click_CyBtldrCommStop    AirQuality2Click_I2CCyBtldrCommStop
        #define AirQuality2Click_CyBtldrCommReset   AirQuality2Click_I2CCyBtldrCommReset
        #define AirQuality2Click_CyBtldrCommRead    AirQuality2Click_I2CCyBtldrCommRead
        #define AirQuality2Click_CyBtldrCommWrite   AirQuality2Click_I2CCyBtldrCommWrite
    #endif /* (AirQuality2Click_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (AirQuality2Click_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (AirQuality2Click_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void AirQuality2Click_EzI2CCyBtldrCommStart(void);
    void AirQuality2Click_EzI2CCyBtldrCommStop (void);
    void AirQuality2Click_EzI2CCyBtldrCommReset(void);
    cystatus AirQuality2Click_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus AirQuality2Click_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (AirQuality2Click_SCB_MODE_EZI2C_CONST_CFG)
        #define AirQuality2Click_CyBtldrCommStart   AirQuality2Click_EzI2CCyBtldrCommStart
        #define AirQuality2Click_CyBtldrCommStop    AirQuality2Click_EzI2CCyBtldrCommStop
        #define AirQuality2Click_CyBtldrCommReset   AirQuality2Click_EzI2CCyBtldrCommReset
        #define AirQuality2Click_CyBtldrCommRead    AirQuality2Click_EzI2CCyBtldrCommRead
        #define AirQuality2Click_CyBtldrCommWrite   AirQuality2Click_EzI2CCyBtldrCommWrite
    #endif /* (AirQuality2Click_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (AirQuality2Click_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (AirQuality2Click_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void AirQuality2Click_SpiCyBtldrCommStart(void);
    void AirQuality2Click_SpiCyBtldrCommStop (void);
    void AirQuality2Click_SpiCyBtldrCommReset(void);
    cystatus AirQuality2Click_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus AirQuality2Click_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (AirQuality2Click_SCB_MODE_SPI_CONST_CFG)
        #define AirQuality2Click_CyBtldrCommStart   AirQuality2Click_SpiCyBtldrCommStart
        #define AirQuality2Click_CyBtldrCommStop    AirQuality2Click_SpiCyBtldrCommStop
        #define AirQuality2Click_CyBtldrCommReset   AirQuality2Click_SpiCyBtldrCommReset
        #define AirQuality2Click_CyBtldrCommRead    AirQuality2Click_SpiCyBtldrCommRead
        #define AirQuality2Click_CyBtldrCommWrite   AirQuality2Click_SpiCyBtldrCommWrite
    #endif /* (AirQuality2Click_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (AirQuality2Click_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (AirQuality2Click_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void AirQuality2Click_UartCyBtldrCommStart(void);
    void AirQuality2Click_UartCyBtldrCommStop (void);
    void AirQuality2Click_UartCyBtldrCommReset(void);
    cystatus AirQuality2Click_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus AirQuality2Click_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (AirQuality2Click_SCB_MODE_UART_CONST_CFG)
        #define AirQuality2Click_CyBtldrCommStart   AirQuality2Click_UartCyBtldrCommStart
        #define AirQuality2Click_CyBtldrCommStop    AirQuality2Click_UartCyBtldrCommStop
        #define AirQuality2Click_CyBtldrCommReset   AirQuality2Click_UartCyBtldrCommReset
        #define AirQuality2Click_CyBtldrCommRead    AirQuality2Click_UartCyBtldrCommRead
        #define AirQuality2Click_CyBtldrCommWrite   AirQuality2Click_UartCyBtldrCommWrite
    #endif /* (AirQuality2Click_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (AirQuality2Click_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (AirQuality2Click_BTLDR_COMM_ENABLED)
    #if (AirQuality2Click_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void AirQuality2Click_CyBtldrCommStart(void);
        void AirQuality2Click_CyBtldrCommStop (void);
        void AirQuality2Click_CyBtldrCommReset(void);
        cystatus AirQuality2Click_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus AirQuality2Click_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (AirQuality2Click_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_AirQuality2Click)
        #define CyBtldrCommStart    AirQuality2Click_CyBtldrCommStart
        #define CyBtldrCommStop     AirQuality2Click_CyBtldrCommStop
        #define CyBtldrCommReset    AirQuality2Click_CyBtldrCommReset
        #define CyBtldrCommWrite    AirQuality2Click_CyBtldrCommWrite
        #define CyBtldrCommRead     AirQuality2Click_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_AirQuality2Click) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (AirQuality2Click_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define AirQuality2Click_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define AirQuality2Click_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define AirQuality2Click_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define AirQuality2Click_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef AirQuality2Click_SPI_BYTE_TO_BYTE
    #define AirQuality2Click_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef AirQuality2Click_UART_BYTE_TO_BYTE
    #define AirQuality2Click_UART_BYTE_TO_BYTE  (2500u)
#endif /* AirQuality2Click_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_AirQuality2Click_H) */


/* [] END OF FILE */
