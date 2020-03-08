/***************************************************************************//**
* \file AirQuality2Click_PINS.h
* \version 4.0
*
* \brief
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
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

#if !defined(CY_SCB_PINS_AirQuality2Click_H)
#define CY_SCB_PINS_AirQuality2Click_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define AirQuality2Click_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define AirQuality2Click_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define AirQuality2Click_REMOVE_TX_SDA_MISO_PIN      (1u)
#define AirQuality2Click_REMOVE_CTS_SCLK_PIN      (1u)
#define AirQuality2Click_REMOVE_RTS_SS0_PIN      (1u)
#define AirQuality2Click_REMOVE_SS1_PIN                 (1u)
#define AirQuality2Click_REMOVE_SS2_PIN                 (1u)
#define AirQuality2Click_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define AirQuality2Click_REMOVE_I2C_PINS                (0u)
#define AirQuality2Click_REMOVE_SPI_MASTER_PINS         (1u)
#define AirQuality2Click_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define AirQuality2Click_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define AirQuality2Click_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define AirQuality2Click_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define AirQuality2Click_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define AirQuality2Click_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define AirQuality2Click_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define AirQuality2Click_REMOVE_SPI_SLAVE_PINS          (1u)
#define AirQuality2Click_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define AirQuality2Click_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define AirQuality2Click_REMOVE_UART_TX_PIN             (1u)
#define AirQuality2Click_REMOVE_UART_RX_TX_PIN          (1u)
#define AirQuality2Click_REMOVE_UART_RX_PIN             (1u)
#define AirQuality2Click_REMOVE_UART_RX_WAKE_PIN        (1u)
#define AirQuality2Click_REMOVE_UART_RTS_PIN            (1u)
#define AirQuality2Click_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define AirQuality2Click_RX_WAKE_SCL_MOSI_PIN (0u == AirQuality2Click_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define AirQuality2Click_RX_SCL_MOSI_PIN     (0u == AirQuality2Click_REMOVE_RX_SCL_MOSI_PIN)
#define AirQuality2Click_TX_SDA_MISO_PIN     (0u == AirQuality2Click_REMOVE_TX_SDA_MISO_PIN)
#define AirQuality2Click_CTS_SCLK_PIN     (0u == AirQuality2Click_REMOVE_CTS_SCLK_PIN)
#define AirQuality2Click_RTS_SS0_PIN     (0u == AirQuality2Click_REMOVE_RTS_SS0_PIN)
#define AirQuality2Click_SS1_PIN                (0u == AirQuality2Click_REMOVE_SS1_PIN)
#define AirQuality2Click_SS2_PIN                (0u == AirQuality2Click_REMOVE_SS2_PIN)
#define AirQuality2Click_SS3_PIN                (0u == AirQuality2Click_REMOVE_SS3_PIN)

/* Mode defined pins */
#define AirQuality2Click_I2C_PINS               (0u == AirQuality2Click_REMOVE_I2C_PINS)
#define AirQuality2Click_SPI_MASTER_PINS        (0u == AirQuality2Click_REMOVE_SPI_MASTER_PINS)
#define AirQuality2Click_SPI_MASTER_SCLK_PIN    (0u == AirQuality2Click_REMOVE_SPI_MASTER_SCLK_PIN)
#define AirQuality2Click_SPI_MASTER_MOSI_PIN    (0u == AirQuality2Click_REMOVE_SPI_MASTER_MOSI_PIN)
#define AirQuality2Click_SPI_MASTER_MISO_PIN    (0u == AirQuality2Click_REMOVE_SPI_MASTER_MISO_PIN)
#define AirQuality2Click_SPI_MASTER_SS0_PIN     (0u == AirQuality2Click_REMOVE_SPI_MASTER_SS0_PIN)
#define AirQuality2Click_SPI_MASTER_SS1_PIN     (0u == AirQuality2Click_REMOVE_SPI_MASTER_SS1_PIN)
#define AirQuality2Click_SPI_MASTER_SS2_PIN     (0u == AirQuality2Click_REMOVE_SPI_MASTER_SS2_PIN)
#define AirQuality2Click_SPI_MASTER_SS3_PIN     (0u == AirQuality2Click_REMOVE_SPI_MASTER_SS3_PIN)
#define AirQuality2Click_SPI_SLAVE_PINS         (0u == AirQuality2Click_REMOVE_SPI_SLAVE_PINS)
#define AirQuality2Click_SPI_SLAVE_MOSI_PIN     (0u == AirQuality2Click_REMOVE_SPI_SLAVE_MOSI_PIN)
#define AirQuality2Click_SPI_SLAVE_MISO_PIN     (0u == AirQuality2Click_REMOVE_SPI_SLAVE_MISO_PIN)
#define AirQuality2Click_UART_TX_PIN            (0u == AirQuality2Click_REMOVE_UART_TX_PIN)
#define AirQuality2Click_UART_RX_TX_PIN         (0u == AirQuality2Click_REMOVE_UART_RX_TX_PIN)
#define AirQuality2Click_UART_RX_PIN            (0u == AirQuality2Click_REMOVE_UART_RX_PIN)
#define AirQuality2Click_UART_RX_WAKE_PIN       (0u == AirQuality2Click_REMOVE_UART_RX_WAKE_PIN)
#define AirQuality2Click_UART_RTS_PIN           (0u == AirQuality2Click_REMOVE_UART_RTS_PIN)
#define AirQuality2Click_UART_CTS_PIN           (0u == AirQuality2Click_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (AirQuality2Click_RX_WAKE_SCL_MOSI_PIN)
    #include "AirQuality2Click_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (AirQuality2Click_RX_SCL_MOSI) */

#if (AirQuality2Click_RX_SCL_MOSI_PIN)
    #include "AirQuality2Click_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (AirQuality2Click_RX_SCL_MOSI) */

#if (AirQuality2Click_TX_SDA_MISO_PIN)
    #include "AirQuality2Click_uart_tx_i2c_sda_spi_miso.h"
#endif /* (AirQuality2Click_TX_SDA_MISO) */

#if (AirQuality2Click_CTS_SCLK_PIN)
    #include "AirQuality2Click_uart_cts_spi_sclk.h"
#endif /* (AirQuality2Click_CTS_SCLK) */

#if (AirQuality2Click_RTS_SS0_PIN)
    #include "AirQuality2Click_uart_rts_spi_ss0.h"
#endif /* (AirQuality2Click_RTS_SS0_PIN) */

#if (AirQuality2Click_SS1_PIN)
    #include "AirQuality2Click_spi_ss1.h"
#endif /* (AirQuality2Click_SS1_PIN) */

#if (AirQuality2Click_SS2_PIN)
    #include "AirQuality2Click_spi_ss2.h"
#endif /* (AirQuality2Click_SS2_PIN) */

#if (AirQuality2Click_SS3_PIN)
    #include "AirQuality2Click_spi_ss3.h"
#endif /* (AirQuality2Click_SS3_PIN) */

#if (AirQuality2Click_I2C_PINS)
    #include "AirQuality2Click_scl.h"
    #include "AirQuality2Click_sda.h"
#endif /* (AirQuality2Click_I2C_PINS) */

#if (AirQuality2Click_SPI_MASTER_PINS)
#if (AirQuality2Click_SPI_MASTER_SCLK_PIN)
    #include "AirQuality2Click_sclk_m.h"
#endif /* (AirQuality2Click_SPI_MASTER_SCLK_PIN) */

#if (AirQuality2Click_SPI_MASTER_MOSI_PIN)
    #include "AirQuality2Click_mosi_m.h"
#endif /* (AirQuality2Click_SPI_MASTER_MOSI_PIN) */

#if (AirQuality2Click_SPI_MASTER_MISO_PIN)
    #include "AirQuality2Click_miso_m.h"
#endif /*(AirQuality2Click_SPI_MASTER_MISO_PIN) */
#endif /* (AirQuality2Click_SPI_MASTER_PINS) */

#if (AirQuality2Click_SPI_SLAVE_PINS)
    #include "AirQuality2Click_sclk_s.h"
    #include "AirQuality2Click_ss_s.h"

#if (AirQuality2Click_SPI_SLAVE_MOSI_PIN)
    #include "AirQuality2Click_mosi_s.h"
#endif /* (AirQuality2Click_SPI_SLAVE_MOSI_PIN) */

#if (AirQuality2Click_SPI_SLAVE_MISO_PIN)
    #include "AirQuality2Click_miso_s.h"
#endif /*(AirQuality2Click_SPI_SLAVE_MISO_PIN) */
#endif /* (AirQuality2Click_SPI_SLAVE_PINS) */

#if (AirQuality2Click_SPI_MASTER_SS0_PIN)
    #include "AirQuality2Click_ss0_m.h"
#endif /* (AirQuality2Click_SPI_MASTER_SS0_PIN) */

#if (AirQuality2Click_SPI_MASTER_SS1_PIN)
    #include "AirQuality2Click_ss1_m.h"
#endif /* (AirQuality2Click_SPI_MASTER_SS1_PIN) */

#if (AirQuality2Click_SPI_MASTER_SS2_PIN)
    #include "AirQuality2Click_ss2_m.h"
#endif /* (AirQuality2Click_SPI_MASTER_SS2_PIN) */

#if (AirQuality2Click_SPI_MASTER_SS3_PIN)
    #include "AirQuality2Click_ss3_m.h"
#endif /* (AirQuality2Click_SPI_MASTER_SS3_PIN) */

#if (AirQuality2Click_UART_TX_PIN)
    #include "AirQuality2Click_tx.h"
#endif /* (AirQuality2Click_UART_TX_PIN) */

#if (AirQuality2Click_UART_RX_TX_PIN)
    #include "AirQuality2Click_rx_tx.h"
#endif /* (AirQuality2Click_UART_RX_TX_PIN) */

#if (AirQuality2Click_UART_RX_PIN)
    #include "AirQuality2Click_rx.h"
#endif /* (AirQuality2Click_UART_RX_PIN) */

#if (AirQuality2Click_UART_RX_WAKE_PIN)
    #include "AirQuality2Click_rx_wake.h"
#endif /* (AirQuality2Click_UART_RX_WAKE_PIN) */

#if (AirQuality2Click_UART_RTS_PIN)
    #include "AirQuality2Click_rts.h"
#endif /* (AirQuality2Click_UART_RTS_PIN) */

#if (AirQuality2Click_UART_CTS_PIN)
    #include "AirQuality2Click_cts.h"
#endif /* (AirQuality2Click_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (AirQuality2Click_RX_SCL_MOSI_PIN)
    #define AirQuality2Click_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) AirQuality2Click_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define AirQuality2Click_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) AirQuality2Click_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    
    #define AirQuality2Click_RX_SCL_MOSI_HSIOM_MASK      (AirQuality2Click_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define AirQuality2Click_RX_SCL_MOSI_HSIOM_POS       (AirQuality2Click_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define AirQuality2Click_RX_SCL_MOSI_HSIOM_SEL_GPIO  (AirQuality2Click_uart_rx_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define AirQuality2Click_RX_SCL_MOSI_HSIOM_SEL_I2C   (AirQuality2Click_uart_rx_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define AirQuality2Click_RX_SCL_MOSI_HSIOM_SEL_SPI   (AirQuality2Click_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define AirQuality2Click_RX_SCL_MOSI_HSIOM_SEL_UART  (AirQuality2Click_uart_rx_i2c_scl_spi_mosi__0__HSIOM_UART)
    
#elif (AirQuality2Click_RX_WAKE_SCL_MOSI_PIN)
    #define AirQuality2Click_RX_WAKE_SCL_MOSI_HSIOM_REG   (*(reg32 *) AirQuality2Click_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define AirQuality2Click_RX_WAKE_SCL_MOSI_HSIOM_PTR   ( (reg32 *) AirQuality2Click_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    
    #define AirQuality2Click_RX_WAKE_SCL_MOSI_HSIOM_MASK      (AirQuality2Click_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define AirQuality2Click_RX_WAKE_SCL_MOSI_HSIOM_POS       (AirQuality2Click_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define AirQuality2Click_RX_WAKE_SCL_MOSI_HSIOM_SEL_GPIO  (AirQuality2Click_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define AirQuality2Click_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C   (AirQuality2Click_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define AirQuality2Click_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI   (AirQuality2Click_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define AirQuality2Click_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART  (AirQuality2Click_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_UART)    
   
    #define AirQuality2Click_RX_WAKE_SCL_MOSI_INTCFG_REG (*(reg32 *) AirQuality2Click_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define AirQuality2Click_RX_WAKE_SCL_MOSI_INTCFG_PTR ( (reg32 *) AirQuality2Click_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define AirQuality2Click_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (AirQuality2Click_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define AirQuality2Click_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK ((uint32) AirQuality2Click_INTCFG_TYPE_MASK << \
                                                                           AirQuality2Click_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins AirQuality2Click_RX_SCL_MOSI_PIN or AirQuality2Click_RX_WAKE_SCL_MOSI_PIN present.*/
#endif /* (AirQuality2Click_RX_SCL_MOSI_PIN) */

#if (AirQuality2Click_TX_SDA_MISO_PIN)
    #define AirQuality2Click_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) AirQuality2Click_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define AirQuality2Click_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) AirQuality2Click_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    
    #define AirQuality2Click_TX_SDA_MISO_HSIOM_MASK      (AirQuality2Click_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define AirQuality2Click_TX_SDA_MISO_HSIOM_POS       (AirQuality2Click_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
    #define AirQuality2Click_TX_SDA_MISO_HSIOM_SEL_GPIO  (AirQuality2Click_uart_tx_i2c_sda_spi_miso__0__HSIOM_GPIO)
    #define AirQuality2Click_TX_SDA_MISO_HSIOM_SEL_I2C   (AirQuality2Click_uart_tx_i2c_sda_spi_miso__0__HSIOM_I2C)
    #define AirQuality2Click_TX_SDA_MISO_HSIOM_SEL_SPI   (AirQuality2Click_uart_tx_i2c_sda_spi_miso__0__HSIOM_SPI)
    #define AirQuality2Click_TX_SDA_MISO_HSIOM_SEL_UART  (AirQuality2Click_uart_tx_i2c_sda_spi_miso__0__HSIOM_UART)
#endif /* (AirQuality2Click_TX_SDA_MISO_PIN) */

#if (AirQuality2Click_CTS_SCLK_PIN)
    #define AirQuality2Click_CTS_SCLK_HSIOM_REG   (*(reg32 *) AirQuality2Click_uart_cts_spi_sclk__0__HSIOM)
    #define AirQuality2Click_CTS_SCLK_HSIOM_PTR   ( (reg32 *) AirQuality2Click_uart_cts_spi_sclk__0__HSIOM)
    
    #define AirQuality2Click_CTS_SCLK_HSIOM_MASK      (AirQuality2Click_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define AirQuality2Click_CTS_SCLK_HSIOM_POS       (AirQuality2Click_uart_cts_spi_sclk__0__HSIOM_SHIFT)
    #define AirQuality2Click_CTS_SCLK_HSIOM_SEL_GPIO  (AirQuality2Click_uart_cts_spi_sclk__0__HSIOM_GPIO)
    #define AirQuality2Click_CTS_SCLK_HSIOM_SEL_I2C   (AirQuality2Click_uart_cts_spi_sclk__0__HSIOM_I2C)
    #define AirQuality2Click_CTS_SCLK_HSIOM_SEL_SPI   (AirQuality2Click_uart_cts_spi_sclk__0__HSIOM_SPI)
    #define AirQuality2Click_CTS_SCLK_HSIOM_SEL_UART  (AirQuality2Click_uart_cts_spi_sclk__0__HSIOM_UART)
#endif /* (AirQuality2Click_CTS_SCLK_PIN) */

#if (AirQuality2Click_RTS_SS0_PIN)
    #define AirQuality2Click_RTS_SS0_HSIOM_REG   (*(reg32 *) AirQuality2Click_uart_rts_spi_ss0__0__HSIOM)
    #define AirQuality2Click_RTS_SS0_HSIOM_PTR   ( (reg32 *) AirQuality2Click_uart_rts_spi_ss0__0__HSIOM)
    
    #define AirQuality2Click_RTS_SS0_HSIOM_MASK      (AirQuality2Click_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define AirQuality2Click_RTS_SS0_HSIOM_POS       (AirQuality2Click_uart_rts_spi_ss0__0__HSIOM_SHIFT)
    #define AirQuality2Click_RTS_SS0_HSIOM_SEL_GPIO  (AirQuality2Click_uart_rts_spi_ss0__0__HSIOM_GPIO)
    #define AirQuality2Click_RTS_SS0_HSIOM_SEL_I2C   (AirQuality2Click_uart_rts_spi_ss0__0__HSIOM_I2C)
    #define AirQuality2Click_RTS_SS0_HSIOM_SEL_SPI   (AirQuality2Click_uart_rts_spi_ss0__0__HSIOM_SPI)
#if !(AirQuality2Click_CY_SCBIP_V0 || AirQuality2Click_CY_SCBIP_V1)
    #define AirQuality2Click_RTS_SS0_HSIOM_SEL_UART  (AirQuality2Click_uart_rts_spi_ss0__0__HSIOM_UART)
#endif /* !(AirQuality2Click_CY_SCBIP_V0 || AirQuality2Click_CY_SCBIP_V1) */
#endif /* (AirQuality2Click_RTS_SS0_PIN) */

#if (AirQuality2Click_SS1_PIN)
    #define AirQuality2Click_SS1_HSIOM_REG  (*(reg32 *) AirQuality2Click_spi_ss1__0__HSIOM)
    #define AirQuality2Click_SS1_HSIOM_PTR  ( (reg32 *) AirQuality2Click_spi_ss1__0__HSIOM)
    
    #define AirQuality2Click_SS1_HSIOM_MASK     (AirQuality2Click_spi_ss1__0__HSIOM_MASK)
    #define AirQuality2Click_SS1_HSIOM_POS      (AirQuality2Click_spi_ss1__0__HSIOM_SHIFT)
    #define AirQuality2Click_SS1_HSIOM_SEL_GPIO (AirQuality2Click_spi_ss1__0__HSIOM_GPIO)
    #define AirQuality2Click_SS1_HSIOM_SEL_I2C  (AirQuality2Click_spi_ss1__0__HSIOM_I2C)
    #define AirQuality2Click_SS1_HSIOM_SEL_SPI  (AirQuality2Click_spi_ss1__0__HSIOM_SPI)
#endif /* (AirQuality2Click_SS1_PIN) */

#if (AirQuality2Click_SS2_PIN)
    #define AirQuality2Click_SS2_HSIOM_REG     (*(reg32 *) AirQuality2Click_spi_ss2__0__HSIOM)
    #define AirQuality2Click_SS2_HSIOM_PTR     ( (reg32 *) AirQuality2Click_spi_ss2__0__HSIOM)
    
    #define AirQuality2Click_SS2_HSIOM_MASK     (AirQuality2Click_spi_ss2__0__HSIOM_MASK)
    #define AirQuality2Click_SS2_HSIOM_POS      (AirQuality2Click_spi_ss2__0__HSIOM_SHIFT)
    #define AirQuality2Click_SS2_HSIOM_SEL_GPIO (AirQuality2Click_spi_ss2__0__HSIOM_GPIO)
    #define AirQuality2Click_SS2_HSIOM_SEL_I2C  (AirQuality2Click_spi_ss2__0__HSIOM_I2C)
    #define AirQuality2Click_SS2_HSIOM_SEL_SPI  (AirQuality2Click_spi_ss2__0__HSIOM_SPI)
#endif /* (AirQuality2Click_SS2_PIN) */

#if (AirQuality2Click_SS3_PIN)
    #define AirQuality2Click_SS3_HSIOM_REG     (*(reg32 *) AirQuality2Click_spi_ss3__0__HSIOM)
    #define AirQuality2Click_SS3_HSIOM_PTR     ( (reg32 *) AirQuality2Click_spi_ss3__0__HSIOM)
    
    #define AirQuality2Click_SS3_HSIOM_MASK     (AirQuality2Click_spi_ss3__0__HSIOM_MASK)
    #define AirQuality2Click_SS3_HSIOM_POS      (AirQuality2Click_spi_ss3__0__HSIOM_SHIFT)
    #define AirQuality2Click_SS3_HSIOM_SEL_GPIO (AirQuality2Click_spi_ss3__0__HSIOM_GPIO)
    #define AirQuality2Click_SS3_HSIOM_SEL_I2C  (AirQuality2Click_spi_ss3__0__HSIOM_I2C)
    #define AirQuality2Click_SS3_HSIOM_SEL_SPI  (AirQuality2Click_spi_ss3__0__HSIOM_SPI)
#endif /* (AirQuality2Click_SS3_PIN) */

#if (AirQuality2Click_I2C_PINS)
    #define AirQuality2Click_SCL_HSIOM_REG  (*(reg32 *) AirQuality2Click_scl__0__HSIOM)
    #define AirQuality2Click_SCL_HSIOM_PTR  ( (reg32 *) AirQuality2Click_scl__0__HSIOM)
    
    #define AirQuality2Click_SCL_HSIOM_MASK     (AirQuality2Click_scl__0__HSIOM_MASK)
    #define AirQuality2Click_SCL_HSIOM_POS      (AirQuality2Click_scl__0__HSIOM_SHIFT)
    #define AirQuality2Click_SCL_HSIOM_SEL_GPIO (AirQuality2Click_sda__0__HSIOM_GPIO)
    #define AirQuality2Click_SCL_HSIOM_SEL_I2C  (AirQuality2Click_sda__0__HSIOM_I2C)
    
    #define AirQuality2Click_SDA_HSIOM_REG  (*(reg32 *) AirQuality2Click_sda__0__HSIOM)
    #define AirQuality2Click_SDA_HSIOM_PTR  ( (reg32 *) AirQuality2Click_sda__0__HSIOM)
    
    #define AirQuality2Click_SDA_HSIOM_MASK     (AirQuality2Click_sda__0__HSIOM_MASK)
    #define AirQuality2Click_SDA_HSIOM_POS      (AirQuality2Click_sda__0__HSIOM_SHIFT)
    #define AirQuality2Click_SDA_HSIOM_SEL_GPIO (AirQuality2Click_sda__0__HSIOM_GPIO)
    #define AirQuality2Click_SDA_HSIOM_SEL_I2C  (AirQuality2Click_sda__0__HSIOM_I2C)
#endif /* (AirQuality2Click_I2C_PINS) */

#if (AirQuality2Click_SPI_SLAVE_PINS)
    #define AirQuality2Click_SCLK_S_HSIOM_REG   (*(reg32 *) AirQuality2Click_sclk_s__0__HSIOM)
    #define AirQuality2Click_SCLK_S_HSIOM_PTR   ( (reg32 *) AirQuality2Click_sclk_s__0__HSIOM)
    
    #define AirQuality2Click_SCLK_S_HSIOM_MASK      (AirQuality2Click_sclk_s__0__HSIOM_MASK)
    #define AirQuality2Click_SCLK_S_HSIOM_POS       (AirQuality2Click_sclk_s__0__HSIOM_SHIFT)
    #define AirQuality2Click_SCLK_S_HSIOM_SEL_GPIO  (AirQuality2Click_sclk_s__0__HSIOM_GPIO)
    #define AirQuality2Click_SCLK_S_HSIOM_SEL_SPI   (AirQuality2Click_sclk_s__0__HSIOM_SPI)
    
    #define AirQuality2Click_SS0_S_HSIOM_REG    (*(reg32 *) AirQuality2Click_ss0_s__0__HSIOM)
    #define AirQuality2Click_SS0_S_HSIOM_PTR    ( (reg32 *) AirQuality2Click_ss0_s__0__HSIOM)
    
    #define AirQuality2Click_SS0_S_HSIOM_MASK       (AirQuality2Click_ss0_s__0__HSIOM_MASK)
    #define AirQuality2Click_SS0_S_HSIOM_POS        (AirQuality2Click_ss0_s__0__HSIOM_SHIFT)
    #define AirQuality2Click_SS0_S_HSIOM_SEL_GPIO   (AirQuality2Click_ss0_s__0__HSIOM_GPIO)  
    #define AirQuality2Click_SS0_S_HSIOM_SEL_SPI    (AirQuality2Click_ss0_s__0__HSIOM_SPI)
#endif /* (AirQuality2Click_SPI_SLAVE_PINS) */

#if (AirQuality2Click_SPI_SLAVE_MOSI_PIN)
    #define AirQuality2Click_MOSI_S_HSIOM_REG   (*(reg32 *) AirQuality2Click_mosi_s__0__HSIOM)
    #define AirQuality2Click_MOSI_S_HSIOM_PTR   ( (reg32 *) AirQuality2Click_mosi_s__0__HSIOM)
    
    #define AirQuality2Click_MOSI_S_HSIOM_MASK      (AirQuality2Click_mosi_s__0__HSIOM_MASK)
    #define AirQuality2Click_MOSI_S_HSIOM_POS       (AirQuality2Click_mosi_s__0__HSIOM_SHIFT)
    #define AirQuality2Click_MOSI_S_HSIOM_SEL_GPIO  (AirQuality2Click_mosi_s__0__HSIOM_GPIO)
    #define AirQuality2Click_MOSI_S_HSIOM_SEL_SPI   (AirQuality2Click_mosi_s__0__HSIOM_SPI)
#endif /* (AirQuality2Click_SPI_SLAVE_MOSI_PIN) */

#if (AirQuality2Click_SPI_SLAVE_MISO_PIN)
    #define AirQuality2Click_MISO_S_HSIOM_REG   (*(reg32 *) AirQuality2Click_miso_s__0__HSIOM)
    #define AirQuality2Click_MISO_S_HSIOM_PTR   ( (reg32 *) AirQuality2Click_miso_s__0__HSIOM)
    
    #define AirQuality2Click_MISO_S_HSIOM_MASK      (AirQuality2Click_miso_s__0__HSIOM_MASK)
    #define AirQuality2Click_MISO_S_HSIOM_POS       (AirQuality2Click_miso_s__0__HSIOM_SHIFT)
    #define AirQuality2Click_MISO_S_HSIOM_SEL_GPIO  (AirQuality2Click_miso_s__0__HSIOM_GPIO)
    #define AirQuality2Click_MISO_S_HSIOM_SEL_SPI   (AirQuality2Click_miso_s__0__HSIOM_SPI)
#endif /* (AirQuality2Click_SPI_SLAVE_MISO_PIN) */

#if (AirQuality2Click_SPI_MASTER_MISO_PIN)
    #define AirQuality2Click_MISO_M_HSIOM_REG   (*(reg32 *) AirQuality2Click_miso_m__0__HSIOM)
    #define AirQuality2Click_MISO_M_HSIOM_PTR   ( (reg32 *) AirQuality2Click_miso_m__0__HSIOM)
    
    #define AirQuality2Click_MISO_M_HSIOM_MASK      (AirQuality2Click_miso_m__0__HSIOM_MASK)
    #define AirQuality2Click_MISO_M_HSIOM_POS       (AirQuality2Click_miso_m__0__HSIOM_SHIFT)
    #define AirQuality2Click_MISO_M_HSIOM_SEL_GPIO  (AirQuality2Click_miso_m__0__HSIOM_GPIO)
    #define AirQuality2Click_MISO_M_HSIOM_SEL_SPI   (AirQuality2Click_miso_m__0__HSIOM_SPI)
#endif /* (AirQuality2Click_SPI_MASTER_MISO_PIN) */

#if (AirQuality2Click_SPI_MASTER_MOSI_PIN)
    #define AirQuality2Click_MOSI_M_HSIOM_REG   (*(reg32 *) AirQuality2Click_mosi_m__0__HSIOM)
    #define AirQuality2Click_MOSI_M_HSIOM_PTR   ( (reg32 *) AirQuality2Click_mosi_m__0__HSIOM)
    
    #define AirQuality2Click_MOSI_M_HSIOM_MASK      (AirQuality2Click_mosi_m__0__HSIOM_MASK)
    #define AirQuality2Click_MOSI_M_HSIOM_POS       (AirQuality2Click_mosi_m__0__HSIOM_SHIFT)
    #define AirQuality2Click_MOSI_M_HSIOM_SEL_GPIO  (AirQuality2Click_mosi_m__0__HSIOM_GPIO)
    #define AirQuality2Click_MOSI_M_HSIOM_SEL_SPI   (AirQuality2Click_mosi_m__0__HSIOM_SPI)
#endif /* (AirQuality2Click_SPI_MASTER_MOSI_PIN) */

#if (AirQuality2Click_SPI_MASTER_SCLK_PIN)
    #define AirQuality2Click_SCLK_M_HSIOM_REG   (*(reg32 *) AirQuality2Click_sclk_m__0__HSIOM)
    #define AirQuality2Click_SCLK_M_HSIOM_PTR   ( (reg32 *) AirQuality2Click_sclk_m__0__HSIOM)
    
    #define AirQuality2Click_SCLK_M_HSIOM_MASK      (AirQuality2Click_sclk_m__0__HSIOM_MASK)
    #define AirQuality2Click_SCLK_M_HSIOM_POS       (AirQuality2Click_sclk_m__0__HSIOM_SHIFT)
    #define AirQuality2Click_SCLK_M_HSIOM_SEL_GPIO  (AirQuality2Click_sclk_m__0__HSIOM_GPIO)
    #define AirQuality2Click_SCLK_M_HSIOM_SEL_SPI   (AirQuality2Click_sclk_m__0__HSIOM_SPI)
#endif /* (AirQuality2Click_SPI_MASTER_SCLK_PIN) */

#if (AirQuality2Click_SPI_MASTER_SS0_PIN)
    #define AirQuality2Click_SS0_M_HSIOM_REG    (*(reg32 *) AirQuality2Click_ss0_m__0__HSIOM)
    #define AirQuality2Click_SS0_M_HSIOM_PTR    ( (reg32 *) AirQuality2Click_ss0_m__0__HSIOM)
    
    #define AirQuality2Click_SS0_M_HSIOM_MASK       (AirQuality2Click_ss0_m__0__HSIOM_MASK)
    #define AirQuality2Click_SS0_M_HSIOM_POS        (AirQuality2Click_ss0_m__0__HSIOM_SHIFT)
    #define AirQuality2Click_SS0_M_HSIOM_SEL_GPIO   (AirQuality2Click_ss0_m__0__HSIOM_GPIO)
    #define AirQuality2Click_SS0_M_HSIOM_SEL_SPI    (AirQuality2Click_ss0_m__0__HSIOM_SPI)
#endif /* (AirQuality2Click_SPI_MASTER_SS0_PIN) */

#if (AirQuality2Click_SPI_MASTER_SS1_PIN)
    #define AirQuality2Click_SS1_M_HSIOM_REG    (*(reg32 *) AirQuality2Click_ss1_m__0__HSIOM)
    #define AirQuality2Click_SS1_M_HSIOM_PTR    ( (reg32 *) AirQuality2Click_ss1_m__0__HSIOM)
    
    #define AirQuality2Click_SS1_M_HSIOM_MASK       (AirQuality2Click_ss1_m__0__HSIOM_MASK)
    #define AirQuality2Click_SS1_M_HSIOM_POS        (AirQuality2Click_ss1_m__0__HSIOM_SHIFT)
    #define AirQuality2Click_SS1_M_HSIOM_SEL_GPIO   (AirQuality2Click_ss1_m__0__HSIOM_GPIO)
    #define AirQuality2Click_SS1_M_HSIOM_SEL_SPI    (AirQuality2Click_ss1_m__0__HSIOM_SPI)
#endif /* (AirQuality2Click_SPI_MASTER_SS1_PIN) */

#if (AirQuality2Click_SPI_MASTER_SS2_PIN)
    #define AirQuality2Click_SS2_M_HSIOM_REG    (*(reg32 *) AirQuality2Click_ss2_m__0__HSIOM)
    #define AirQuality2Click_SS2_M_HSIOM_PTR    ( (reg32 *) AirQuality2Click_ss2_m__0__HSIOM)
    
    #define AirQuality2Click_SS2_M_HSIOM_MASK       (AirQuality2Click_ss2_m__0__HSIOM_MASK)
    #define AirQuality2Click_SS2_M_HSIOM_POS        (AirQuality2Click_ss2_m__0__HSIOM_SHIFT)
    #define AirQuality2Click_SS2_M_HSIOM_SEL_GPIO   (AirQuality2Click_ss2_m__0__HSIOM_GPIO)
    #define AirQuality2Click_SS2_M_HSIOM_SEL_SPI    (AirQuality2Click_ss2_m__0__HSIOM_SPI)
#endif /* (AirQuality2Click_SPI_MASTER_SS2_PIN) */

#if (AirQuality2Click_SPI_MASTER_SS3_PIN)
    #define AirQuality2Click_SS3_M_HSIOM_REG    (*(reg32 *) AirQuality2Click_ss3_m__0__HSIOM)
    #define AirQuality2Click_SS3_M_HSIOM_PTR    ( (reg32 *) AirQuality2Click_ss3_m__0__HSIOM)
    
    #define AirQuality2Click_SS3_M_HSIOM_MASK      (AirQuality2Click_ss3_m__0__HSIOM_MASK)
    #define AirQuality2Click_SS3_M_HSIOM_POS       (AirQuality2Click_ss3_m__0__HSIOM_SHIFT)
    #define AirQuality2Click_SS3_M_HSIOM_SEL_GPIO  (AirQuality2Click_ss3_m__0__HSIOM_GPIO)
    #define AirQuality2Click_SS3_M_HSIOM_SEL_SPI   (AirQuality2Click_ss3_m__0__HSIOM_SPI)
#endif /* (AirQuality2Click_SPI_MASTER_SS3_PIN) */

#if (AirQuality2Click_UART_RX_PIN)
    #define AirQuality2Click_RX_HSIOM_REG   (*(reg32 *) AirQuality2Click_rx__0__HSIOM)
    #define AirQuality2Click_RX_HSIOM_PTR   ( (reg32 *) AirQuality2Click_rx__0__HSIOM)
    
    #define AirQuality2Click_RX_HSIOM_MASK      (AirQuality2Click_rx__0__HSIOM_MASK)
    #define AirQuality2Click_RX_HSIOM_POS       (AirQuality2Click_rx__0__HSIOM_SHIFT)
    #define AirQuality2Click_RX_HSIOM_SEL_GPIO  (AirQuality2Click_rx__0__HSIOM_GPIO)
    #define AirQuality2Click_RX_HSIOM_SEL_UART  (AirQuality2Click_rx__0__HSIOM_UART)
#endif /* (AirQuality2Click_UART_RX_PIN) */

#if (AirQuality2Click_UART_RX_WAKE_PIN)
    #define AirQuality2Click_RX_WAKE_HSIOM_REG   (*(reg32 *) AirQuality2Click_rx_wake__0__HSIOM)
    #define AirQuality2Click_RX_WAKE_HSIOM_PTR   ( (reg32 *) AirQuality2Click_rx_wake__0__HSIOM)
    
    #define AirQuality2Click_RX_WAKE_HSIOM_MASK      (AirQuality2Click_rx_wake__0__HSIOM_MASK)
    #define AirQuality2Click_RX_WAKE_HSIOM_POS       (AirQuality2Click_rx_wake__0__HSIOM_SHIFT)
    #define AirQuality2Click_RX_WAKE_HSIOM_SEL_GPIO  (AirQuality2Click_rx_wake__0__HSIOM_GPIO)
    #define AirQuality2Click_RX_WAKE_HSIOM_SEL_UART  (AirQuality2Click_rx_wake__0__HSIOM_UART)
#endif /* (AirQuality2Click_UART_WAKE_RX_PIN) */

#if (AirQuality2Click_UART_CTS_PIN)
    #define AirQuality2Click_CTS_HSIOM_REG   (*(reg32 *) AirQuality2Click_cts__0__HSIOM)
    #define AirQuality2Click_CTS_HSIOM_PTR   ( (reg32 *) AirQuality2Click_cts__0__HSIOM)
    
    #define AirQuality2Click_CTS_HSIOM_MASK      (AirQuality2Click_cts__0__HSIOM_MASK)
    #define AirQuality2Click_CTS_HSIOM_POS       (AirQuality2Click_cts__0__HSIOM_SHIFT)
    #define AirQuality2Click_CTS_HSIOM_SEL_GPIO  (AirQuality2Click_cts__0__HSIOM_GPIO)
    #define AirQuality2Click_CTS_HSIOM_SEL_UART  (AirQuality2Click_cts__0__HSIOM_UART)
#endif /* (AirQuality2Click_UART_CTS_PIN) */

#if (AirQuality2Click_UART_TX_PIN)
    #define AirQuality2Click_TX_HSIOM_REG   (*(reg32 *) AirQuality2Click_tx__0__HSIOM)
    #define AirQuality2Click_TX_HSIOM_PTR   ( (reg32 *) AirQuality2Click_tx__0__HSIOM)
    
    #define AirQuality2Click_TX_HSIOM_MASK      (AirQuality2Click_tx__0__HSIOM_MASK)
    #define AirQuality2Click_TX_HSIOM_POS       (AirQuality2Click_tx__0__HSIOM_SHIFT)
    #define AirQuality2Click_TX_HSIOM_SEL_GPIO  (AirQuality2Click_tx__0__HSIOM_GPIO)
    #define AirQuality2Click_TX_HSIOM_SEL_UART  (AirQuality2Click_tx__0__HSIOM_UART)
#endif /* (AirQuality2Click_UART_TX_PIN) */

#if (AirQuality2Click_UART_RX_TX_PIN)
    #define AirQuality2Click_RX_TX_HSIOM_REG   (*(reg32 *) AirQuality2Click_rx_tx__0__HSIOM)
    #define AirQuality2Click_RX_TX_HSIOM_PTR   ( (reg32 *) AirQuality2Click_rx_tx__0__HSIOM)
    
    #define AirQuality2Click_RX_TX_HSIOM_MASK      (AirQuality2Click_rx_tx__0__HSIOM_MASK)
    #define AirQuality2Click_RX_TX_HSIOM_POS       (AirQuality2Click_rx_tx__0__HSIOM_SHIFT)
    #define AirQuality2Click_RX_TX_HSIOM_SEL_GPIO  (AirQuality2Click_rx_tx__0__HSIOM_GPIO)
    #define AirQuality2Click_RX_TX_HSIOM_SEL_UART  (AirQuality2Click_rx_tx__0__HSIOM_UART)
#endif /* (AirQuality2Click_UART_RX_TX_PIN) */

#if (AirQuality2Click_UART_RTS_PIN)
    #define AirQuality2Click_RTS_HSIOM_REG      (*(reg32 *) AirQuality2Click_rts__0__HSIOM)
    #define AirQuality2Click_RTS_HSIOM_PTR      ( (reg32 *) AirQuality2Click_rts__0__HSIOM)
    
    #define AirQuality2Click_RTS_HSIOM_MASK     (AirQuality2Click_rts__0__HSIOM_MASK)
    #define AirQuality2Click_RTS_HSIOM_POS      (AirQuality2Click_rts__0__HSIOM_SHIFT)    
    #define AirQuality2Click_RTS_HSIOM_SEL_GPIO (AirQuality2Click_rts__0__HSIOM_GPIO)
    #define AirQuality2Click_RTS_HSIOM_SEL_UART (AirQuality2Click_rts__0__HSIOM_UART)    
#endif /* (AirQuality2Click_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define AirQuality2Click_HSIOM_DEF_SEL      (0x00u)
#define AirQuality2Click_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for AirQuality2Click_CY_SCBIP_V0 
* and AirQuality2Click_CY_SCBIP_V1. It is not recommended to use them for 
* AirQuality2Click_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define AirQuality2Click_HSIOM_UART_SEL     (0x09u)
#define AirQuality2Click_HSIOM_I2C_SEL      (0x0Eu)
#define AirQuality2Click_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define AirQuality2Click_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define AirQuality2Click_RX_SCL_MOSI_PIN_INDEX       (0u)
#define AirQuality2Click_TX_SDA_MISO_PIN_INDEX       (1u)
#define AirQuality2Click_CTS_SCLK_PIN_INDEX       (2u)
#define AirQuality2Click_RTS_SS0_PIN_INDEX       (3u)
#define AirQuality2Click_SS1_PIN_INDEX                  (4u)
#define AirQuality2Click_SS2_PIN_INDEX                  (5u)
#define AirQuality2Click_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define AirQuality2Click_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << AirQuality2Click_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define AirQuality2Click_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << AirQuality2Click_RX_SCL_MOSI_PIN_INDEX)
#define AirQuality2Click_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << AirQuality2Click_TX_SDA_MISO_PIN_INDEX)
#define AirQuality2Click_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << AirQuality2Click_CTS_SCLK_PIN_INDEX)
#define AirQuality2Click_RTS_SS0_PIN_MASK     ((uint32) 0x01u << AirQuality2Click_RTS_SS0_PIN_INDEX)
#define AirQuality2Click_SS1_PIN_MASK                ((uint32) 0x01u << AirQuality2Click_SS1_PIN_INDEX)
#define AirQuality2Click_SS2_PIN_MASK                ((uint32) 0x01u << AirQuality2Click_SS2_PIN_INDEX)
#define AirQuality2Click_SS3_PIN_MASK                ((uint32) 0x01u << AirQuality2Click_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define AirQuality2Click_INTCFG_TYPE_MASK           (0x03u)
#define AirQuality2Click_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define AirQuality2Click_PIN_DM_ALG_HIZ  (0u)
#define AirQuality2Click_PIN_DM_DIG_HIZ  (1u)
#define AirQuality2Click_PIN_DM_OD_LO    (4u)
#define AirQuality2Click_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define AirQuality2Click_DM_MASK    (0x7u)
#define AirQuality2Click_DM_SIZE    (3u)
#define AirQuality2Click_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) AirQuality2Click_DM_MASK << (AirQuality2Click_DM_SIZE * (pos)))) >> \
                                                              (AirQuality2Click_DM_SIZE * (pos)) )

#if (AirQuality2Click_TX_SDA_MISO_PIN)
    #define AirQuality2Click_CHECK_TX_SDA_MISO_PIN_USED \
                (AirQuality2Click_PIN_DM_ALG_HIZ != \
                    AirQuality2Click_GET_P4_PIN_DM(AirQuality2Click_uart_tx_i2c_sda_spi_miso_PC, \
                                                   AirQuality2Click_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (AirQuality2Click_TX_SDA_MISO_PIN) */

#if (AirQuality2Click_RTS_SS0_PIN)
    #define AirQuality2Click_CHECK_RTS_SS0_PIN_USED \
                (AirQuality2Click_PIN_DM_ALG_HIZ != \
                    AirQuality2Click_GET_P4_PIN_DM(AirQuality2Click_uart_rts_spi_ss0_PC, \
                                                   AirQuality2Click_uart_rts_spi_ss0_SHIFT))
#endif /* (AirQuality2Click_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define AirQuality2Click_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define AirQuality2Click_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define AirQuality2Click_SET_HSIOM_SEL(reg, mask, pos, sel) AirQuality2Click_SET_REGISTER_BITS(reg, mask, pos, sel)
#define AirQuality2Click_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        AirQuality2Click_SET_REGISTER_BITS(reg, mask, pos, intType)
#define AirQuality2Click_SET_INP_DIS(reg, mask, val) AirQuality2Click_SET_REGISTER_BIT(reg, mask, val)

/* AirQuality2Click_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  AirQuality2Click_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (AirQuality2Click_CY_SCBIP_V0)
#if (AirQuality2Click_I2C_PINS)
    #define AirQuality2Click_SET_I2C_SCL_DR(val) AirQuality2Click_scl_Write(val)

    #define AirQuality2Click_SET_I2C_SCL_HSIOM_SEL(sel) \
                          AirQuality2Click_SET_HSIOM_SEL(AirQuality2Click_SCL_HSIOM_REG,  \
                                                         AirQuality2Click_SCL_HSIOM_MASK, \
                                                         AirQuality2Click_SCL_HSIOM_POS,  \
                                                         (sel))
    #define AirQuality2Click_WAIT_SCL_SET_HIGH  (0u == AirQuality2Click_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (AirQuality2Click_RX_WAKE_SCL_MOSI_PIN)
    #define AirQuality2Click_SET_I2C_SCL_DR(val) \
                            AirQuality2Click_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define AirQuality2Click_SET_I2C_SCL_HSIOM_SEL(sel) \
                    AirQuality2Click_SET_HSIOM_SEL(AirQuality2Click_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   AirQuality2Click_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   AirQuality2Click_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define AirQuality2Click_WAIT_SCL_SET_HIGH  (0u == AirQuality2Click_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (AirQuality2Click_RX_SCL_MOSI_PIN)
    #define AirQuality2Click_SET_I2C_SCL_DR(val) \
                            AirQuality2Click_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define AirQuality2Click_SET_I2C_SCL_HSIOM_SEL(sel) \
                            AirQuality2Click_SET_HSIOM_SEL(AirQuality2Click_RX_SCL_MOSI_HSIOM_REG,  \
                                                           AirQuality2Click_RX_SCL_MOSI_HSIOM_MASK, \
                                                           AirQuality2Click_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define AirQuality2Click_WAIT_SCL_SET_HIGH  (0u == AirQuality2Click_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define AirQuality2Click_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define AirQuality2Click_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define AirQuality2Click_WAIT_SCL_SET_HIGH  (0u)
#endif /* (AirQuality2Click_I2C_PINS) */

/* SCB I2C: sda signal */
#if (AirQuality2Click_I2C_PINS)
    #define AirQuality2Click_WAIT_SDA_SET_HIGH  (0u == AirQuality2Click_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (AirQuality2Click_TX_SDA_MISO_PIN)
    #define AirQuality2Click_WAIT_SDA_SET_HIGH  (0u == AirQuality2Click_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define AirQuality2Click_WAIT_SDA_SET_HIGH  (0u)
#endif /* (AirQuality2Click_MOSI_SCL_RX_PIN) */
#endif /* (AirQuality2Click_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (AirQuality2Click_RX_SCL_MOSI_PIN)
    #define AirQuality2Click_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (AirQuality2Click_RX_WAKE_SCL_MOSI_PIN)
    #define AirQuality2Click_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) AirQuality2Click_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(AirQuality2Click_UART_RX_WAKE_PIN)
    #define AirQuality2Click_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) AirQuality2Click_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (AirQuality2Click_RX_SCL_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define AirQuality2Click_REMOVE_MOSI_SCL_RX_WAKE_PIN    AirQuality2Click_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define AirQuality2Click_REMOVE_MOSI_SCL_RX_PIN         AirQuality2Click_REMOVE_RX_SCL_MOSI_PIN
#define AirQuality2Click_REMOVE_MISO_SDA_TX_PIN         AirQuality2Click_REMOVE_TX_SDA_MISO_PIN
#ifndef AirQuality2Click_REMOVE_SCLK_PIN
#define AirQuality2Click_REMOVE_SCLK_PIN                AirQuality2Click_REMOVE_CTS_SCLK_PIN
#endif /* AirQuality2Click_REMOVE_SCLK_PIN */
#ifndef AirQuality2Click_REMOVE_SS0_PIN
#define AirQuality2Click_REMOVE_SS0_PIN                 AirQuality2Click_REMOVE_RTS_SS0_PIN
#endif /* AirQuality2Click_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define AirQuality2Click_MOSI_SCL_RX_WAKE_PIN   AirQuality2Click_RX_WAKE_SCL_MOSI_PIN
#define AirQuality2Click_MOSI_SCL_RX_PIN        AirQuality2Click_RX_SCL_MOSI_PIN
#define AirQuality2Click_MISO_SDA_TX_PIN        AirQuality2Click_TX_SDA_MISO_PIN
#ifndef AirQuality2Click_SCLK_PIN
#define AirQuality2Click_SCLK_PIN               AirQuality2Click_CTS_SCLK_PIN
#endif /* AirQuality2Click_SCLK_PIN */
#ifndef AirQuality2Click_SS0_PIN
#define AirQuality2Click_SS0_PIN                AirQuality2Click_RTS_SS0_PIN
#endif /* AirQuality2Click_SS0_PIN */

#if (AirQuality2Click_MOSI_SCL_RX_WAKE_PIN)
    #define AirQuality2Click_MOSI_SCL_RX_WAKE_HSIOM_REG     AirQuality2Click_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define AirQuality2Click_MOSI_SCL_RX_WAKE_HSIOM_PTR     AirQuality2Click_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define AirQuality2Click_MOSI_SCL_RX_WAKE_HSIOM_MASK    AirQuality2Click_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define AirQuality2Click_MOSI_SCL_RX_WAKE_HSIOM_POS     AirQuality2Click_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define AirQuality2Click_MOSI_SCL_RX_WAKE_INTCFG_REG    AirQuality2Click_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define AirQuality2Click_MOSI_SCL_RX_WAKE_INTCFG_PTR    AirQuality2Click_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define AirQuality2Click_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   AirQuality2Click_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define AirQuality2Click_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  AirQuality2Click_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (AirQuality2Click_RX_WAKE_SCL_MOSI_PIN) */

#if (AirQuality2Click_MOSI_SCL_RX_PIN)
    #define AirQuality2Click_MOSI_SCL_RX_HSIOM_REG      AirQuality2Click_RX_SCL_MOSI_HSIOM_REG
    #define AirQuality2Click_MOSI_SCL_RX_HSIOM_PTR      AirQuality2Click_RX_SCL_MOSI_HSIOM_PTR
    #define AirQuality2Click_MOSI_SCL_RX_HSIOM_MASK     AirQuality2Click_RX_SCL_MOSI_HSIOM_MASK
    #define AirQuality2Click_MOSI_SCL_RX_HSIOM_POS      AirQuality2Click_RX_SCL_MOSI_HSIOM_POS
#endif /* (AirQuality2Click_MOSI_SCL_RX_PIN) */

#if (AirQuality2Click_MISO_SDA_TX_PIN)
    #define AirQuality2Click_MISO_SDA_TX_HSIOM_REG      AirQuality2Click_TX_SDA_MISO_HSIOM_REG
    #define AirQuality2Click_MISO_SDA_TX_HSIOM_PTR      AirQuality2Click_TX_SDA_MISO_HSIOM_REG
    #define AirQuality2Click_MISO_SDA_TX_HSIOM_MASK     AirQuality2Click_TX_SDA_MISO_HSIOM_REG
    #define AirQuality2Click_MISO_SDA_TX_HSIOM_POS      AirQuality2Click_TX_SDA_MISO_HSIOM_REG
#endif /* (AirQuality2Click_MISO_SDA_TX_PIN_PIN) */

#if (AirQuality2Click_SCLK_PIN)
    #ifndef AirQuality2Click_SCLK_HSIOM_REG
    #define AirQuality2Click_SCLK_HSIOM_REG     AirQuality2Click_CTS_SCLK_HSIOM_REG
    #define AirQuality2Click_SCLK_HSIOM_PTR     AirQuality2Click_CTS_SCLK_HSIOM_PTR
    #define AirQuality2Click_SCLK_HSIOM_MASK    AirQuality2Click_CTS_SCLK_HSIOM_MASK
    #define AirQuality2Click_SCLK_HSIOM_POS     AirQuality2Click_CTS_SCLK_HSIOM_POS
    #endif /* AirQuality2Click_SCLK_HSIOM_REG */
#endif /* (AirQuality2Click_SCLK_PIN) */

#if (AirQuality2Click_SS0_PIN)
    #ifndef AirQuality2Click_SS0_HSIOM_REG
    #define AirQuality2Click_SS0_HSIOM_REG      AirQuality2Click_RTS_SS0_HSIOM_REG
    #define AirQuality2Click_SS0_HSIOM_PTR      AirQuality2Click_RTS_SS0_HSIOM_PTR
    #define AirQuality2Click_SS0_HSIOM_MASK     AirQuality2Click_RTS_SS0_HSIOM_MASK
    #define AirQuality2Click_SS0_HSIOM_POS      AirQuality2Click_RTS_SS0_HSIOM_POS
    #endif /* AirQuality2Click_SS0_HSIOM_REG */
#endif /* (AirQuality2Click_SS0_PIN) */

#define AirQuality2Click_MOSI_SCL_RX_WAKE_PIN_INDEX AirQuality2Click_RX_WAKE_SCL_MOSI_PIN_INDEX
#define AirQuality2Click_MOSI_SCL_RX_PIN_INDEX      AirQuality2Click_RX_SCL_MOSI_PIN_INDEX
#define AirQuality2Click_MISO_SDA_TX_PIN_INDEX      AirQuality2Click_TX_SDA_MISO_PIN_INDEX
#ifndef AirQuality2Click_SCLK_PIN_INDEX
#define AirQuality2Click_SCLK_PIN_INDEX             AirQuality2Click_CTS_SCLK_PIN_INDEX
#endif /* AirQuality2Click_SCLK_PIN_INDEX */
#ifndef AirQuality2Click_SS0_PIN_INDEX
#define AirQuality2Click_SS0_PIN_INDEX              AirQuality2Click_RTS_SS0_PIN_INDEX
#endif /* AirQuality2Click_SS0_PIN_INDEX */

#define AirQuality2Click_MOSI_SCL_RX_WAKE_PIN_MASK AirQuality2Click_RX_WAKE_SCL_MOSI_PIN_MASK
#define AirQuality2Click_MOSI_SCL_RX_PIN_MASK      AirQuality2Click_RX_SCL_MOSI_PIN_MASK
#define AirQuality2Click_MISO_SDA_TX_PIN_MASK      AirQuality2Click_TX_SDA_MISO_PIN_MASK
#ifndef AirQuality2Click_SCLK_PIN_MASK
#define AirQuality2Click_SCLK_PIN_MASK             AirQuality2Click_CTS_SCLK_PIN_MASK
#endif /* AirQuality2Click_SCLK_PIN_MASK */
#ifndef AirQuality2Click_SS0_PIN_MASK
#define AirQuality2Click_SS0_PIN_MASK              AirQuality2Click_RTS_SS0_PIN_MASK
#endif /* AirQuality2Click_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_AirQuality2Click_H) */


/* [] END OF FILE */
