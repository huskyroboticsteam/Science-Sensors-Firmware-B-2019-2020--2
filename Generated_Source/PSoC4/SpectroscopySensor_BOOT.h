/***************************************************************************//**
* \file SpectroscopySensor_BOOT.h
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

#if !defined(CY_SCB_BOOT_SpectroscopySensor_H)
#define CY_SCB_BOOT_SpectroscopySensor_H

#include "SpectroscopySensor_PVT.h"

#if (SpectroscopySensor_SCB_MODE_I2C_INC)
    #include "SpectroscopySensor_I2C.h"
#endif /* (SpectroscopySensor_SCB_MODE_I2C_INC) */

#if (SpectroscopySensor_SCB_MODE_EZI2C_INC)
    #include "SpectroscopySensor_EZI2C.h"
#endif /* (SpectroscopySensor_SCB_MODE_EZI2C_INC) */

#if (SpectroscopySensor_SCB_MODE_SPI_INC || SpectroscopySensor_SCB_MODE_UART_INC)
    #include "SpectroscopySensor_SPI_UART.h"
#endif /* (SpectroscopySensor_SCB_MODE_SPI_INC || SpectroscopySensor_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define SpectroscopySensor_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SpectroscopySensor) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (SpectroscopySensor_SCB_MODE_I2C_INC)
    #define SpectroscopySensor_I2C_BTLDR_COMM_ENABLED     (SpectroscopySensor_BTLDR_COMM_ENABLED && \
                                                            (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             SpectroscopySensor_I2C_SLAVE_CONST))
#else
     #define SpectroscopySensor_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (SpectroscopySensor_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (SpectroscopySensor_SCB_MODE_EZI2C_INC)
    #define SpectroscopySensor_EZI2C_BTLDR_COMM_ENABLED   (SpectroscopySensor_BTLDR_COMM_ENABLED && \
                                                         SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define SpectroscopySensor_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (SpectroscopySensor_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (SpectroscopySensor_SCB_MODE_SPI_INC)
    #define SpectroscopySensor_SPI_BTLDR_COMM_ENABLED     (SpectroscopySensor_BTLDR_COMM_ENABLED && \
                                                            (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             SpectroscopySensor_SPI_SLAVE_CONST))
#else
        #define SpectroscopySensor_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (SpectroscopySensor_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (SpectroscopySensor_SCB_MODE_UART_INC)
       #define SpectroscopySensor_UART_BTLDR_COMM_ENABLED    (SpectroscopySensor_BTLDR_COMM_ENABLED && \
                                                            (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (SpectroscopySensor_UART_RX_DIRECTION && \
                                                              SpectroscopySensor_UART_TX_DIRECTION)))
#else
     #define SpectroscopySensor_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (SpectroscopySensor_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define SpectroscopySensor_BTLDR_COMM_MODE_ENABLED    (SpectroscopySensor_I2C_BTLDR_COMM_ENABLED   || \
                                                     SpectroscopySensor_SPI_BTLDR_COMM_ENABLED   || \
                                                     SpectroscopySensor_EZI2C_BTLDR_COMM_ENABLED || \
                                                     SpectroscopySensor_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SpectroscopySensor_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void SpectroscopySensor_I2CCyBtldrCommStart(void);
    void SpectroscopySensor_I2CCyBtldrCommStop (void);
    void SpectroscopySensor_I2CCyBtldrCommReset(void);
    cystatus SpectroscopySensor_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SpectroscopySensor_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (SpectroscopySensor_SCB_MODE_I2C_CONST_CFG)
        #define SpectroscopySensor_CyBtldrCommStart   SpectroscopySensor_I2CCyBtldrCommStart
        #define SpectroscopySensor_CyBtldrCommStop    SpectroscopySensor_I2CCyBtldrCommStop
        #define SpectroscopySensor_CyBtldrCommReset   SpectroscopySensor_I2CCyBtldrCommReset
        #define SpectroscopySensor_CyBtldrCommRead    SpectroscopySensor_I2CCyBtldrCommRead
        #define SpectroscopySensor_CyBtldrCommWrite   SpectroscopySensor_I2CCyBtldrCommWrite
    #endif /* (SpectroscopySensor_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SpectroscopySensor_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SpectroscopySensor_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void SpectroscopySensor_EzI2CCyBtldrCommStart(void);
    void SpectroscopySensor_EzI2CCyBtldrCommStop (void);
    void SpectroscopySensor_EzI2CCyBtldrCommReset(void);
    cystatus SpectroscopySensor_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SpectroscopySensor_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (SpectroscopySensor_SCB_MODE_EZI2C_CONST_CFG)
        #define SpectroscopySensor_CyBtldrCommStart   SpectroscopySensor_EzI2CCyBtldrCommStart
        #define SpectroscopySensor_CyBtldrCommStop    SpectroscopySensor_EzI2CCyBtldrCommStop
        #define SpectroscopySensor_CyBtldrCommReset   SpectroscopySensor_EzI2CCyBtldrCommReset
        #define SpectroscopySensor_CyBtldrCommRead    SpectroscopySensor_EzI2CCyBtldrCommRead
        #define SpectroscopySensor_CyBtldrCommWrite   SpectroscopySensor_EzI2CCyBtldrCommWrite
    #endif /* (SpectroscopySensor_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SpectroscopySensor_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SpectroscopySensor_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void SpectroscopySensor_SpiCyBtldrCommStart(void);
    void SpectroscopySensor_SpiCyBtldrCommStop (void);
    void SpectroscopySensor_SpiCyBtldrCommReset(void);
    cystatus SpectroscopySensor_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SpectroscopySensor_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (SpectroscopySensor_SCB_MODE_SPI_CONST_CFG)
        #define SpectroscopySensor_CyBtldrCommStart   SpectroscopySensor_SpiCyBtldrCommStart
        #define SpectroscopySensor_CyBtldrCommStop    SpectroscopySensor_SpiCyBtldrCommStop
        #define SpectroscopySensor_CyBtldrCommReset   SpectroscopySensor_SpiCyBtldrCommReset
        #define SpectroscopySensor_CyBtldrCommRead    SpectroscopySensor_SpiCyBtldrCommRead
        #define SpectroscopySensor_CyBtldrCommWrite   SpectroscopySensor_SpiCyBtldrCommWrite
    #endif /* (SpectroscopySensor_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SpectroscopySensor_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SpectroscopySensor_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void SpectroscopySensor_UartCyBtldrCommStart(void);
    void SpectroscopySensor_UartCyBtldrCommStop (void);
    void SpectroscopySensor_UartCyBtldrCommReset(void);
    cystatus SpectroscopySensor_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus SpectroscopySensor_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (SpectroscopySensor_SCB_MODE_UART_CONST_CFG)
        #define SpectroscopySensor_CyBtldrCommStart   SpectroscopySensor_UartCyBtldrCommStart
        #define SpectroscopySensor_CyBtldrCommStop    SpectroscopySensor_UartCyBtldrCommStop
        #define SpectroscopySensor_CyBtldrCommReset   SpectroscopySensor_UartCyBtldrCommReset
        #define SpectroscopySensor_CyBtldrCommRead    SpectroscopySensor_UartCyBtldrCommRead
        #define SpectroscopySensor_CyBtldrCommWrite   SpectroscopySensor_UartCyBtldrCommWrite
    #endif /* (SpectroscopySensor_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SpectroscopySensor_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (SpectroscopySensor_BTLDR_COMM_ENABLED)
    #if (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void SpectroscopySensor_CyBtldrCommStart(void);
        void SpectroscopySensor_CyBtldrCommStop (void);
        void SpectroscopySensor_CyBtldrCommReset(void);
        cystatus SpectroscopySensor_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus SpectroscopySensor_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (SpectroscopySensor_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SpectroscopySensor)
        #define CyBtldrCommStart    SpectroscopySensor_CyBtldrCommStart
        #define CyBtldrCommStop     SpectroscopySensor_CyBtldrCommStop
        #define CyBtldrCommReset    SpectroscopySensor_CyBtldrCommReset
        #define CyBtldrCommWrite    SpectroscopySensor_CyBtldrCommWrite
        #define CyBtldrCommRead     SpectroscopySensor_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_SpectroscopySensor) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (SpectroscopySensor_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define SpectroscopySensor_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define SpectroscopySensor_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define SpectroscopySensor_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define SpectroscopySensor_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef SpectroscopySensor_SPI_BYTE_TO_BYTE
    #define SpectroscopySensor_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef SpectroscopySensor_UART_BYTE_TO_BYTE
    #define SpectroscopySensor_UART_BYTE_TO_BYTE  (2500u)
#endif /* SpectroscopySensor_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_SpectroscopySensor_H) */


/* [] END OF FILE */
