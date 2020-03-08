/***************************************************************************//**
* \file SpectroscopySensor_PINS.h
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

#if !defined(CY_SCB_PINS_SpectroscopySensor_H)
#define CY_SCB_PINS_SpectroscopySensor_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define SpectroscopySensor_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define SpectroscopySensor_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define SpectroscopySensor_REMOVE_TX_SDA_MISO_PIN      (1u)
#define SpectroscopySensor_REMOVE_CTS_SCLK_PIN      (1u)
#define SpectroscopySensor_REMOVE_RTS_SS0_PIN      (1u)
#define SpectroscopySensor_REMOVE_SS1_PIN                 (1u)
#define SpectroscopySensor_REMOVE_SS2_PIN                 (1u)
#define SpectroscopySensor_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define SpectroscopySensor_REMOVE_I2C_PINS                (0u)
#define SpectroscopySensor_REMOVE_SPI_MASTER_PINS         (1u)
#define SpectroscopySensor_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define SpectroscopySensor_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define SpectroscopySensor_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define SpectroscopySensor_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define SpectroscopySensor_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define SpectroscopySensor_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define SpectroscopySensor_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define SpectroscopySensor_REMOVE_SPI_SLAVE_PINS          (1u)
#define SpectroscopySensor_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define SpectroscopySensor_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define SpectroscopySensor_REMOVE_UART_TX_PIN             (1u)
#define SpectroscopySensor_REMOVE_UART_RX_TX_PIN          (1u)
#define SpectroscopySensor_REMOVE_UART_RX_PIN             (1u)
#define SpectroscopySensor_REMOVE_UART_RX_WAKE_PIN        (1u)
#define SpectroscopySensor_REMOVE_UART_RTS_PIN            (1u)
#define SpectroscopySensor_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN (0u == SpectroscopySensor_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define SpectroscopySensor_RX_SCL_MOSI_PIN     (0u == SpectroscopySensor_REMOVE_RX_SCL_MOSI_PIN)
#define SpectroscopySensor_TX_SDA_MISO_PIN     (0u == SpectroscopySensor_REMOVE_TX_SDA_MISO_PIN)
#define SpectroscopySensor_CTS_SCLK_PIN     (0u == SpectroscopySensor_REMOVE_CTS_SCLK_PIN)
#define SpectroscopySensor_RTS_SS0_PIN     (0u == SpectroscopySensor_REMOVE_RTS_SS0_PIN)
#define SpectroscopySensor_SS1_PIN                (0u == SpectroscopySensor_REMOVE_SS1_PIN)
#define SpectroscopySensor_SS2_PIN                (0u == SpectroscopySensor_REMOVE_SS2_PIN)
#define SpectroscopySensor_SS3_PIN                (0u == SpectroscopySensor_REMOVE_SS3_PIN)

/* Mode defined pins */
#define SpectroscopySensor_I2C_PINS               (0u == SpectroscopySensor_REMOVE_I2C_PINS)
#define SpectroscopySensor_SPI_MASTER_PINS        (0u == SpectroscopySensor_REMOVE_SPI_MASTER_PINS)
#define SpectroscopySensor_SPI_MASTER_SCLK_PIN    (0u == SpectroscopySensor_REMOVE_SPI_MASTER_SCLK_PIN)
#define SpectroscopySensor_SPI_MASTER_MOSI_PIN    (0u == SpectroscopySensor_REMOVE_SPI_MASTER_MOSI_PIN)
#define SpectroscopySensor_SPI_MASTER_MISO_PIN    (0u == SpectroscopySensor_REMOVE_SPI_MASTER_MISO_PIN)
#define SpectroscopySensor_SPI_MASTER_SS0_PIN     (0u == SpectroscopySensor_REMOVE_SPI_MASTER_SS0_PIN)
#define SpectroscopySensor_SPI_MASTER_SS1_PIN     (0u == SpectroscopySensor_REMOVE_SPI_MASTER_SS1_PIN)
#define SpectroscopySensor_SPI_MASTER_SS2_PIN     (0u == SpectroscopySensor_REMOVE_SPI_MASTER_SS2_PIN)
#define SpectroscopySensor_SPI_MASTER_SS3_PIN     (0u == SpectroscopySensor_REMOVE_SPI_MASTER_SS3_PIN)
#define SpectroscopySensor_SPI_SLAVE_PINS         (0u == SpectroscopySensor_REMOVE_SPI_SLAVE_PINS)
#define SpectroscopySensor_SPI_SLAVE_MOSI_PIN     (0u == SpectroscopySensor_REMOVE_SPI_SLAVE_MOSI_PIN)
#define SpectroscopySensor_SPI_SLAVE_MISO_PIN     (0u == SpectroscopySensor_REMOVE_SPI_SLAVE_MISO_PIN)
#define SpectroscopySensor_UART_TX_PIN            (0u == SpectroscopySensor_REMOVE_UART_TX_PIN)
#define SpectroscopySensor_UART_RX_TX_PIN         (0u == SpectroscopySensor_REMOVE_UART_RX_TX_PIN)
#define SpectroscopySensor_UART_RX_PIN            (0u == SpectroscopySensor_REMOVE_UART_RX_PIN)
#define SpectroscopySensor_UART_RX_WAKE_PIN       (0u == SpectroscopySensor_REMOVE_UART_RX_WAKE_PIN)
#define SpectroscopySensor_UART_RTS_PIN           (0u == SpectroscopySensor_REMOVE_UART_RTS_PIN)
#define SpectroscopySensor_UART_CTS_PIN           (0u == SpectroscopySensor_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN)
    #include "SpectroscopySensor_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (SpectroscopySensor_RX_SCL_MOSI) */

#if (SpectroscopySensor_RX_SCL_MOSI_PIN)
    #include "SpectroscopySensor_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (SpectroscopySensor_RX_SCL_MOSI) */

#if (SpectroscopySensor_TX_SDA_MISO_PIN)
    #include "SpectroscopySensor_uart_tx_i2c_sda_spi_miso.h"
#endif /* (SpectroscopySensor_TX_SDA_MISO) */

#if (SpectroscopySensor_CTS_SCLK_PIN)
    #include "SpectroscopySensor_uart_cts_spi_sclk.h"
#endif /* (SpectroscopySensor_CTS_SCLK) */

#if (SpectroscopySensor_RTS_SS0_PIN)
    #include "SpectroscopySensor_uart_rts_spi_ss0.h"
#endif /* (SpectroscopySensor_RTS_SS0_PIN) */

#if (SpectroscopySensor_SS1_PIN)
    #include "SpectroscopySensor_spi_ss1.h"
#endif /* (SpectroscopySensor_SS1_PIN) */

#if (SpectroscopySensor_SS2_PIN)
    #include "SpectroscopySensor_spi_ss2.h"
#endif /* (SpectroscopySensor_SS2_PIN) */

#if (SpectroscopySensor_SS3_PIN)
    #include "SpectroscopySensor_spi_ss3.h"
#endif /* (SpectroscopySensor_SS3_PIN) */

#if (SpectroscopySensor_I2C_PINS)
    #include "SpectroscopySensor_scl.h"
    #include "SpectroscopySensor_sda.h"
#endif /* (SpectroscopySensor_I2C_PINS) */

#if (SpectroscopySensor_SPI_MASTER_PINS)
#if (SpectroscopySensor_SPI_MASTER_SCLK_PIN)
    #include "SpectroscopySensor_sclk_m.h"
#endif /* (SpectroscopySensor_SPI_MASTER_SCLK_PIN) */

#if (SpectroscopySensor_SPI_MASTER_MOSI_PIN)
    #include "SpectroscopySensor_mosi_m.h"
#endif /* (SpectroscopySensor_SPI_MASTER_MOSI_PIN) */

#if (SpectroscopySensor_SPI_MASTER_MISO_PIN)
    #include "SpectroscopySensor_miso_m.h"
#endif /*(SpectroscopySensor_SPI_MASTER_MISO_PIN) */
#endif /* (SpectroscopySensor_SPI_MASTER_PINS) */

#if (SpectroscopySensor_SPI_SLAVE_PINS)
    #include "SpectroscopySensor_sclk_s.h"
    #include "SpectroscopySensor_ss_s.h"

#if (SpectroscopySensor_SPI_SLAVE_MOSI_PIN)
    #include "SpectroscopySensor_mosi_s.h"
#endif /* (SpectroscopySensor_SPI_SLAVE_MOSI_PIN) */

#if (SpectroscopySensor_SPI_SLAVE_MISO_PIN)
    #include "SpectroscopySensor_miso_s.h"
#endif /*(SpectroscopySensor_SPI_SLAVE_MISO_PIN) */
#endif /* (SpectroscopySensor_SPI_SLAVE_PINS) */

#if (SpectroscopySensor_SPI_MASTER_SS0_PIN)
    #include "SpectroscopySensor_ss0_m.h"
#endif /* (SpectroscopySensor_SPI_MASTER_SS0_PIN) */

#if (SpectroscopySensor_SPI_MASTER_SS1_PIN)
    #include "SpectroscopySensor_ss1_m.h"
#endif /* (SpectroscopySensor_SPI_MASTER_SS1_PIN) */

#if (SpectroscopySensor_SPI_MASTER_SS2_PIN)
    #include "SpectroscopySensor_ss2_m.h"
#endif /* (SpectroscopySensor_SPI_MASTER_SS2_PIN) */

#if (SpectroscopySensor_SPI_MASTER_SS3_PIN)
    #include "SpectroscopySensor_ss3_m.h"
#endif /* (SpectroscopySensor_SPI_MASTER_SS3_PIN) */

#if (SpectroscopySensor_UART_TX_PIN)
    #include "SpectroscopySensor_tx.h"
#endif /* (SpectroscopySensor_UART_TX_PIN) */

#if (SpectroscopySensor_UART_RX_TX_PIN)
    #include "SpectroscopySensor_rx_tx.h"
#endif /* (SpectroscopySensor_UART_RX_TX_PIN) */

#if (SpectroscopySensor_UART_RX_PIN)
    #include "SpectroscopySensor_rx.h"
#endif /* (SpectroscopySensor_UART_RX_PIN) */

#if (SpectroscopySensor_UART_RX_WAKE_PIN)
    #include "SpectroscopySensor_rx_wake.h"
#endif /* (SpectroscopySensor_UART_RX_WAKE_PIN) */

#if (SpectroscopySensor_UART_RTS_PIN)
    #include "SpectroscopySensor_rts.h"
#endif /* (SpectroscopySensor_UART_RTS_PIN) */

#if (SpectroscopySensor_UART_CTS_PIN)
    #include "SpectroscopySensor_cts.h"
#endif /* (SpectroscopySensor_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (SpectroscopySensor_RX_SCL_MOSI_PIN)
    #define SpectroscopySensor_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) SpectroscopySensor_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define SpectroscopySensor_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) SpectroscopySensor_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    
    #define SpectroscopySensor_RX_SCL_MOSI_HSIOM_MASK      (SpectroscopySensor_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define SpectroscopySensor_RX_SCL_MOSI_HSIOM_POS       (SpectroscopySensor_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define SpectroscopySensor_RX_SCL_MOSI_HSIOM_SEL_GPIO  (SpectroscopySensor_uart_rx_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define SpectroscopySensor_RX_SCL_MOSI_HSIOM_SEL_I2C   (SpectroscopySensor_uart_rx_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define SpectroscopySensor_RX_SCL_MOSI_HSIOM_SEL_SPI   (SpectroscopySensor_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define SpectroscopySensor_RX_SCL_MOSI_HSIOM_SEL_UART  (SpectroscopySensor_uart_rx_i2c_scl_spi_mosi__0__HSIOM_UART)
    
#elif (SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN)
    #define SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_REG   (*(reg32 *) SpectroscopySensor_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_PTR   ( (reg32 *) SpectroscopySensor_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    
    #define SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_MASK      (SpectroscopySensor_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_POS       (SpectroscopySensor_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_SEL_GPIO  (SpectroscopySensor_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C   (SpectroscopySensor_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI   (SpectroscopySensor_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART  (SpectroscopySensor_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_UART)    
   
    #define SpectroscopySensor_RX_WAKE_SCL_MOSI_INTCFG_REG (*(reg32 *) SpectroscopySensor_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define SpectroscopySensor_RX_WAKE_SCL_MOSI_INTCFG_PTR ( (reg32 *) SpectroscopySensor_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define SpectroscopySensor_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (SpectroscopySensor_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define SpectroscopySensor_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK ((uint32) SpectroscopySensor_INTCFG_TYPE_MASK << \
                                                                           SpectroscopySensor_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins SpectroscopySensor_RX_SCL_MOSI_PIN or SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN present.*/
#endif /* (SpectroscopySensor_RX_SCL_MOSI_PIN) */

#if (SpectroscopySensor_TX_SDA_MISO_PIN)
    #define SpectroscopySensor_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) SpectroscopySensor_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define SpectroscopySensor_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) SpectroscopySensor_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    
    #define SpectroscopySensor_TX_SDA_MISO_HSIOM_MASK      (SpectroscopySensor_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define SpectroscopySensor_TX_SDA_MISO_HSIOM_POS       (SpectroscopySensor_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
    #define SpectroscopySensor_TX_SDA_MISO_HSIOM_SEL_GPIO  (SpectroscopySensor_uart_tx_i2c_sda_spi_miso__0__HSIOM_GPIO)
    #define SpectroscopySensor_TX_SDA_MISO_HSIOM_SEL_I2C   (SpectroscopySensor_uart_tx_i2c_sda_spi_miso__0__HSIOM_I2C)
    #define SpectroscopySensor_TX_SDA_MISO_HSIOM_SEL_SPI   (SpectroscopySensor_uart_tx_i2c_sda_spi_miso__0__HSIOM_SPI)
    #define SpectroscopySensor_TX_SDA_MISO_HSIOM_SEL_UART  (SpectroscopySensor_uart_tx_i2c_sda_spi_miso__0__HSIOM_UART)
#endif /* (SpectroscopySensor_TX_SDA_MISO_PIN) */

#if (SpectroscopySensor_CTS_SCLK_PIN)
    #define SpectroscopySensor_CTS_SCLK_HSIOM_REG   (*(reg32 *) SpectroscopySensor_uart_cts_spi_sclk__0__HSIOM)
    #define SpectroscopySensor_CTS_SCLK_HSIOM_PTR   ( (reg32 *) SpectroscopySensor_uart_cts_spi_sclk__0__HSIOM)
    
    #define SpectroscopySensor_CTS_SCLK_HSIOM_MASK      (SpectroscopySensor_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define SpectroscopySensor_CTS_SCLK_HSIOM_POS       (SpectroscopySensor_uart_cts_spi_sclk__0__HSIOM_SHIFT)
    #define SpectroscopySensor_CTS_SCLK_HSIOM_SEL_GPIO  (SpectroscopySensor_uart_cts_spi_sclk__0__HSIOM_GPIO)
    #define SpectroscopySensor_CTS_SCLK_HSIOM_SEL_I2C   (SpectroscopySensor_uart_cts_spi_sclk__0__HSIOM_I2C)
    #define SpectroscopySensor_CTS_SCLK_HSIOM_SEL_SPI   (SpectroscopySensor_uart_cts_spi_sclk__0__HSIOM_SPI)
    #define SpectroscopySensor_CTS_SCLK_HSIOM_SEL_UART  (SpectroscopySensor_uart_cts_spi_sclk__0__HSIOM_UART)
#endif /* (SpectroscopySensor_CTS_SCLK_PIN) */

#if (SpectroscopySensor_RTS_SS0_PIN)
    #define SpectroscopySensor_RTS_SS0_HSIOM_REG   (*(reg32 *) SpectroscopySensor_uart_rts_spi_ss0__0__HSIOM)
    #define SpectroscopySensor_RTS_SS0_HSIOM_PTR   ( (reg32 *) SpectroscopySensor_uart_rts_spi_ss0__0__HSIOM)
    
    #define SpectroscopySensor_RTS_SS0_HSIOM_MASK      (SpectroscopySensor_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define SpectroscopySensor_RTS_SS0_HSIOM_POS       (SpectroscopySensor_uart_rts_spi_ss0__0__HSIOM_SHIFT)
    #define SpectroscopySensor_RTS_SS0_HSIOM_SEL_GPIO  (SpectroscopySensor_uart_rts_spi_ss0__0__HSIOM_GPIO)
    #define SpectroscopySensor_RTS_SS0_HSIOM_SEL_I2C   (SpectroscopySensor_uart_rts_spi_ss0__0__HSIOM_I2C)
    #define SpectroscopySensor_RTS_SS0_HSIOM_SEL_SPI   (SpectroscopySensor_uart_rts_spi_ss0__0__HSIOM_SPI)
#if !(SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1)
    #define SpectroscopySensor_RTS_SS0_HSIOM_SEL_UART  (SpectroscopySensor_uart_rts_spi_ss0__0__HSIOM_UART)
#endif /* !(SpectroscopySensor_CY_SCBIP_V0 || SpectroscopySensor_CY_SCBIP_V1) */
#endif /* (SpectroscopySensor_RTS_SS0_PIN) */

#if (SpectroscopySensor_SS1_PIN)
    #define SpectroscopySensor_SS1_HSIOM_REG  (*(reg32 *) SpectroscopySensor_spi_ss1__0__HSIOM)
    #define SpectroscopySensor_SS1_HSIOM_PTR  ( (reg32 *) SpectroscopySensor_spi_ss1__0__HSIOM)
    
    #define SpectroscopySensor_SS1_HSIOM_MASK     (SpectroscopySensor_spi_ss1__0__HSIOM_MASK)
    #define SpectroscopySensor_SS1_HSIOM_POS      (SpectroscopySensor_spi_ss1__0__HSIOM_SHIFT)
    #define SpectroscopySensor_SS1_HSIOM_SEL_GPIO (SpectroscopySensor_spi_ss1__0__HSIOM_GPIO)
    #define SpectroscopySensor_SS1_HSIOM_SEL_I2C  (SpectroscopySensor_spi_ss1__0__HSIOM_I2C)
    #define SpectroscopySensor_SS1_HSIOM_SEL_SPI  (SpectroscopySensor_spi_ss1__0__HSIOM_SPI)
#endif /* (SpectroscopySensor_SS1_PIN) */

#if (SpectroscopySensor_SS2_PIN)
    #define SpectroscopySensor_SS2_HSIOM_REG     (*(reg32 *) SpectroscopySensor_spi_ss2__0__HSIOM)
    #define SpectroscopySensor_SS2_HSIOM_PTR     ( (reg32 *) SpectroscopySensor_spi_ss2__0__HSIOM)
    
    #define SpectroscopySensor_SS2_HSIOM_MASK     (SpectroscopySensor_spi_ss2__0__HSIOM_MASK)
    #define SpectroscopySensor_SS2_HSIOM_POS      (SpectroscopySensor_spi_ss2__0__HSIOM_SHIFT)
    #define SpectroscopySensor_SS2_HSIOM_SEL_GPIO (SpectroscopySensor_spi_ss2__0__HSIOM_GPIO)
    #define SpectroscopySensor_SS2_HSIOM_SEL_I2C  (SpectroscopySensor_spi_ss2__0__HSIOM_I2C)
    #define SpectroscopySensor_SS2_HSIOM_SEL_SPI  (SpectroscopySensor_spi_ss2__0__HSIOM_SPI)
#endif /* (SpectroscopySensor_SS2_PIN) */

#if (SpectroscopySensor_SS3_PIN)
    #define SpectroscopySensor_SS3_HSIOM_REG     (*(reg32 *) SpectroscopySensor_spi_ss3__0__HSIOM)
    #define SpectroscopySensor_SS3_HSIOM_PTR     ( (reg32 *) SpectroscopySensor_spi_ss3__0__HSIOM)
    
    #define SpectroscopySensor_SS3_HSIOM_MASK     (SpectroscopySensor_spi_ss3__0__HSIOM_MASK)
    #define SpectroscopySensor_SS3_HSIOM_POS      (SpectroscopySensor_spi_ss3__0__HSIOM_SHIFT)
    #define SpectroscopySensor_SS3_HSIOM_SEL_GPIO (SpectroscopySensor_spi_ss3__0__HSIOM_GPIO)
    #define SpectroscopySensor_SS3_HSIOM_SEL_I2C  (SpectroscopySensor_spi_ss3__0__HSIOM_I2C)
    #define SpectroscopySensor_SS3_HSIOM_SEL_SPI  (SpectroscopySensor_spi_ss3__0__HSIOM_SPI)
#endif /* (SpectroscopySensor_SS3_PIN) */

#if (SpectroscopySensor_I2C_PINS)
    #define SpectroscopySensor_SCL_HSIOM_REG  (*(reg32 *) SpectroscopySensor_scl__0__HSIOM)
    #define SpectroscopySensor_SCL_HSIOM_PTR  ( (reg32 *) SpectroscopySensor_scl__0__HSIOM)
    
    #define SpectroscopySensor_SCL_HSIOM_MASK     (SpectroscopySensor_scl__0__HSIOM_MASK)
    #define SpectroscopySensor_SCL_HSIOM_POS      (SpectroscopySensor_scl__0__HSIOM_SHIFT)
    #define SpectroscopySensor_SCL_HSIOM_SEL_GPIO (SpectroscopySensor_sda__0__HSIOM_GPIO)
    #define SpectroscopySensor_SCL_HSIOM_SEL_I2C  (SpectroscopySensor_sda__0__HSIOM_I2C)
    
    #define SpectroscopySensor_SDA_HSIOM_REG  (*(reg32 *) SpectroscopySensor_sda__0__HSIOM)
    #define SpectroscopySensor_SDA_HSIOM_PTR  ( (reg32 *) SpectroscopySensor_sda__0__HSIOM)
    
    #define SpectroscopySensor_SDA_HSIOM_MASK     (SpectroscopySensor_sda__0__HSIOM_MASK)
    #define SpectroscopySensor_SDA_HSIOM_POS      (SpectroscopySensor_sda__0__HSIOM_SHIFT)
    #define SpectroscopySensor_SDA_HSIOM_SEL_GPIO (SpectroscopySensor_sda__0__HSIOM_GPIO)
    #define SpectroscopySensor_SDA_HSIOM_SEL_I2C  (SpectroscopySensor_sda__0__HSIOM_I2C)
#endif /* (SpectroscopySensor_I2C_PINS) */

#if (SpectroscopySensor_SPI_SLAVE_PINS)
    #define SpectroscopySensor_SCLK_S_HSIOM_REG   (*(reg32 *) SpectroscopySensor_sclk_s__0__HSIOM)
    #define SpectroscopySensor_SCLK_S_HSIOM_PTR   ( (reg32 *) SpectroscopySensor_sclk_s__0__HSIOM)
    
    #define SpectroscopySensor_SCLK_S_HSIOM_MASK      (SpectroscopySensor_sclk_s__0__HSIOM_MASK)
    #define SpectroscopySensor_SCLK_S_HSIOM_POS       (SpectroscopySensor_sclk_s__0__HSIOM_SHIFT)
    #define SpectroscopySensor_SCLK_S_HSIOM_SEL_GPIO  (SpectroscopySensor_sclk_s__0__HSIOM_GPIO)
    #define SpectroscopySensor_SCLK_S_HSIOM_SEL_SPI   (SpectroscopySensor_sclk_s__0__HSIOM_SPI)
    
    #define SpectroscopySensor_SS0_S_HSIOM_REG    (*(reg32 *) SpectroscopySensor_ss0_s__0__HSIOM)
    #define SpectroscopySensor_SS0_S_HSIOM_PTR    ( (reg32 *) SpectroscopySensor_ss0_s__0__HSIOM)
    
    #define SpectroscopySensor_SS0_S_HSIOM_MASK       (SpectroscopySensor_ss0_s__0__HSIOM_MASK)
    #define SpectroscopySensor_SS0_S_HSIOM_POS        (SpectroscopySensor_ss0_s__0__HSIOM_SHIFT)
    #define SpectroscopySensor_SS0_S_HSIOM_SEL_GPIO   (SpectroscopySensor_ss0_s__0__HSIOM_GPIO)  
    #define SpectroscopySensor_SS0_S_HSIOM_SEL_SPI    (SpectroscopySensor_ss0_s__0__HSIOM_SPI)
#endif /* (SpectroscopySensor_SPI_SLAVE_PINS) */

#if (SpectroscopySensor_SPI_SLAVE_MOSI_PIN)
    #define SpectroscopySensor_MOSI_S_HSIOM_REG   (*(reg32 *) SpectroscopySensor_mosi_s__0__HSIOM)
    #define SpectroscopySensor_MOSI_S_HSIOM_PTR   ( (reg32 *) SpectroscopySensor_mosi_s__0__HSIOM)
    
    #define SpectroscopySensor_MOSI_S_HSIOM_MASK      (SpectroscopySensor_mosi_s__0__HSIOM_MASK)
    #define SpectroscopySensor_MOSI_S_HSIOM_POS       (SpectroscopySensor_mosi_s__0__HSIOM_SHIFT)
    #define SpectroscopySensor_MOSI_S_HSIOM_SEL_GPIO  (SpectroscopySensor_mosi_s__0__HSIOM_GPIO)
    #define SpectroscopySensor_MOSI_S_HSIOM_SEL_SPI   (SpectroscopySensor_mosi_s__0__HSIOM_SPI)
#endif /* (SpectroscopySensor_SPI_SLAVE_MOSI_PIN) */

#if (SpectroscopySensor_SPI_SLAVE_MISO_PIN)
    #define SpectroscopySensor_MISO_S_HSIOM_REG   (*(reg32 *) SpectroscopySensor_miso_s__0__HSIOM)
    #define SpectroscopySensor_MISO_S_HSIOM_PTR   ( (reg32 *) SpectroscopySensor_miso_s__0__HSIOM)
    
    #define SpectroscopySensor_MISO_S_HSIOM_MASK      (SpectroscopySensor_miso_s__0__HSIOM_MASK)
    #define SpectroscopySensor_MISO_S_HSIOM_POS       (SpectroscopySensor_miso_s__0__HSIOM_SHIFT)
    #define SpectroscopySensor_MISO_S_HSIOM_SEL_GPIO  (SpectroscopySensor_miso_s__0__HSIOM_GPIO)
    #define SpectroscopySensor_MISO_S_HSIOM_SEL_SPI   (SpectroscopySensor_miso_s__0__HSIOM_SPI)
#endif /* (SpectroscopySensor_SPI_SLAVE_MISO_PIN) */

#if (SpectroscopySensor_SPI_MASTER_MISO_PIN)
    #define SpectroscopySensor_MISO_M_HSIOM_REG   (*(reg32 *) SpectroscopySensor_miso_m__0__HSIOM)
    #define SpectroscopySensor_MISO_M_HSIOM_PTR   ( (reg32 *) SpectroscopySensor_miso_m__0__HSIOM)
    
    #define SpectroscopySensor_MISO_M_HSIOM_MASK      (SpectroscopySensor_miso_m__0__HSIOM_MASK)
    #define SpectroscopySensor_MISO_M_HSIOM_POS       (SpectroscopySensor_miso_m__0__HSIOM_SHIFT)
    #define SpectroscopySensor_MISO_M_HSIOM_SEL_GPIO  (SpectroscopySensor_miso_m__0__HSIOM_GPIO)
    #define SpectroscopySensor_MISO_M_HSIOM_SEL_SPI   (SpectroscopySensor_miso_m__0__HSIOM_SPI)
#endif /* (SpectroscopySensor_SPI_MASTER_MISO_PIN) */

#if (SpectroscopySensor_SPI_MASTER_MOSI_PIN)
    #define SpectroscopySensor_MOSI_M_HSIOM_REG   (*(reg32 *) SpectroscopySensor_mosi_m__0__HSIOM)
    #define SpectroscopySensor_MOSI_M_HSIOM_PTR   ( (reg32 *) SpectroscopySensor_mosi_m__0__HSIOM)
    
    #define SpectroscopySensor_MOSI_M_HSIOM_MASK      (SpectroscopySensor_mosi_m__0__HSIOM_MASK)
    #define SpectroscopySensor_MOSI_M_HSIOM_POS       (SpectroscopySensor_mosi_m__0__HSIOM_SHIFT)
    #define SpectroscopySensor_MOSI_M_HSIOM_SEL_GPIO  (SpectroscopySensor_mosi_m__0__HSIOM_GPIO)
    #define SpectroscopySensor_MOSI_M_HSIOM_SEL_SPI   (SpectroscopySensor_mosi_m__0__HSIOM_SPI)
#endif /* (SpectroscopySensor_SPI_MASTER_MOSI_PIN) */

#if (SpectroscopySensor_SPI_MASTER_SCLK_PIN)
    #define SpectroscopySensor_SCLK_M_HSIOM_REG   (*(reg32 *) SpectroscopySensor_sclk_m__0__HSIOM)
    #define SpectroscopySensor_SCLK_M_HSIOM_PTR   ( (reg32 *) SpectroscopySensor_sclk_m__0__HSIOM)
    
    #define SpectroscopySensor_SCLK_M_HSIOM_MASK      (SpectroscopySensor_sclk_m__0__HSIOM_MASK)
    #define SpectroscopySensor_SCLK_M_HSIOM_POS       (SpectroscopySensor_sclk_m__0__HSIOM_SHIFT)
    #define SpectroscopySensor_SCLK_M_HSIOM_SEL_GPIO  (SpectroscopySensor_sclk_m__0__HSIOM_GPIO)
    #define SpectroscopySensor_SCLK_M_HSIOM_SEL_SPI   (SpectroscopySensor_sclk_m__0__HSIOM_SPI)
#endif /* (SpectroscopySensor_SPI_MASTER_SCLK_PIN) */

#if (SpectroscopySensor_SPI_MASTER_SS0_PIN)
    #define SpectroscopySensor_SS0_M_HSIOM_REG    (*(reg32 *) SpectroscopySensor_ss0_m__0__HSIOM)
    #define SpectroscopySensor_SS0_M_HSIOM_PTR    ( (reg32 *) SpectroscopySensor_ss0_m__0__HSIOM)
    
    #define SpectroscopySensor_SS0_M_HSIOM_MASK       (SpectroscopySensor_ss0_m__0__HSIOM_MASK)
    #define SpectroscopySensor_SS0_M_HSIOM_POS        (SpectroscopySensor_ss0_m__0__HSIOM_SHIFT)
    #define SpectroscopySensor_SS0_M_HSIOM_SEL_GPIO   (SpectroscopySensor_ss0_m__0__HSIOM_GPIO)
    #define SpectroscopySensor_SS0_M_HSIOM_SEL_SPI    (SpectroscopySensor_ss0_m__0__HSIOM_SPI)
#endif /* (SpectroscopySensor_SPI_MASTER_SS0_PIN) */

#if (SpectroscopySensor_SPI_MASTER_SS1_PIN)
    #define SpectroscopySensor_SS1_M_HSIOM_REG    (*(reg32 *) SpectroscopySensor_ss1_m__0__HSIOM)
    #define SpectroscopySensor_SS1_M_HSIOM_PTR    ( (reg32 *) SpectroscopySensor_ss1_m__0__HSIOM)
    
    #define SpectroscopySensor_SS1_M_HSIOM_MASK       (SpectroscopySensor_ss1_m__0__HSIOM_MASK)
    #define SpectroscopySensor_SS1_M_HSIOM_POS        (SpectroscopySensor_ss1_m__0__HSIOM_SHIFT)
    #define SpectroscopySensor_SS1_M_HSIOM_SEL_GPIO   (SpectroscopySensor_ss1_m__0__HSIOM_GPIO)
    #define SpectroscopySensor_SS1_M_HSIOM_SEL_SPI    (SpectroscopySensor_ss1_m__0__HSIOM_SPI)
#endif /* (SpectroscopySensor_SPI_MASTER_SS1_PIN) */

#if (SpectroscopySensor_SPI_MASTER_SS2_PIN)
    #define SpectroscopySensor_SS2_M_HSIOM_REG    (*(reg32 *) SpectroscopySensor_ss2_m__0__HSIOM)
    #define SpectroscopySensor_SS2_M_HSIOM_PTR    ( (reg32 *) SpectroscopySensor_ss2_m__0__HSIOM)
    
    #define SpectroscopySensor_SS2_M_HSIOM_MASK       (SpectroscopySensor_ss2_m__0__HSIOM_MASK)
    #define SpectroscopySensor_SS2_M_HSIOM_POS        (SpectroscopySensor_ss2_m__0__HSIOM_SHIFT)
    #define SpectroscopySensor_SS2_M_HSIOM_SEL_GPIO   (SpectroscopySensor_ss2_m__0__HSIOM_GPIO)
    #define SpectroscopySensor_SS2_M_HSIOM_SEL_SPI    (SpectroscopySensor_ss2_m__0__HSIOM_SPI)
#endif /* (SpectroscopySensor_SPI_MASTER_SS2_PIN) */

#if (SpectroscopySensor_SPI_MASTER_SS3_PIN)
    #define SpectroscopySensor_SS3_M_HSIOM_REG    (*(reg32 *) SpectroscopySensor_ss3_m__0__HSIOM)
    #define SpectroscopySensor_SS3_M_HSIOM_PTR    ( (reg32 *) SpectroscopySensor_ss3_m__0__HSIOM)
    
    #define SpectroscopySensor_SS3_M_HSIOM_MASK      (SpectroscopySensor_ss3_m__0__HSIOM_MASK)
    #define SpectroscopySensor_SS3_M_HSIOM_POS       (SpectroscopySensor_ss3_m__0__HSIOM_SHIFT)
    #define SpectroscopySensor_SS3_M_HSIOM_SEL_GPIO  (SpectroscopySensor_ss3_m__0__HSIOM_GPIO)
    #define SpectroscopySensor_SS3_M_HSIOM_SEL_SPI   (SpectroscopySensor_ss3_m__0__HSIOM_SPI)
#endif /* (SpectroscopySensor_SPI_MASTER_SS3_PIN) */

#if (SpectroscopySensor_UART_RX_PIN)
    #define SpectroscopySensor_RX_HSIOM_REG   (*(reg32 *) SpectroscopySensor_rx__0__HSIOM)
    #define SpectroscopySensor_RX_HSIOM_PTR   ( (reg32 *) SpectroscopySensor_rx__0__HSIOM)
    
    #define SpectroscopySensor_RX_HSIOM_MASK      (SpectroscopySensor_rx__0__HSIOM_MASK)
    #define SpectroscopySensor_RX_HSIOM_POS       (SpectroscopySensor_rx__0__HSIOM_SHIFT)
    #define SpectroscopySensor_RX_HSIOM_SEL_GPIO  (SpectroscopySensor_rx__0__HSIOM_GPIO)
    #define SpectroscopySensor_RX_HSIOM_SEL_UART  (SpectroscopySensor_rx__0__HSIOM_UART)
#endif /* (SpectroscopySensor_UART_RX_PIN) */

#if (SpectroscopySensor_UART_RX_WAKE_PIN)
    #define SpectroscopySensor_RX_WAKE_HSIOM_REG   (*(reg32 *) SpectroscopySensor_rx_wake__0__HSIOM)
    #define SpectroscopySensor_RX_WAKE_HSIOM_PTR   ( (reg32 *) SpectroscopySensor_rx_wake__0__HSIOM)
    
    #define SpectroscopySensor_RX_WAKE_HSIOM_MASK      (SpectroscopySensor_rx_wake__0__HSIOM_MASK)
    #define SpectroscopySensor_RX_WAKE_HSIOM_POS       (SpectroscopySensor_rx_wake__0__HSIOM_SHIFT)
    #define SpectroscopySensor_RX_WAKE_HSIOM_SEL_GPIO  (SpectroscopySensor_rx_wake__0__HSIOM_GPIO)
    #define SpectroscopySensor_RX_WAKE_HSIOM_SEL_UART  (SpectroscopySensor_rx_wake__0__HSIOM_UART)
#endif /* (SpectroscopySensor_UART_WAKE_RX_PIN) */

#if (SpectroscopySensor_UART_CTS_PIN)
    #define SpectroscopySensor_CTS_HSIOM_REG   (*(reg32 *) SpectroscopySensor_cts__0__HSIOM)
    #define SpectroscopySensor_CTS_HSIOM_PTR   ( (reg32 *) SpectroscopySensor_cts__0__HSIOM)
    
    #define SpectroscopySensor_CTS_HSIOM_MASK      (SpectroscopySensor_cts__0__HSIOM_MASK)
    #define SpectroscopySensor_CTS_HSIOM_POS       (SpectroscopySensor_cts__0__HSIOM_SHIFT)
    #define SpectroscopySensor_CTS_HSIOM_SEL_GPIO  (SpectroscopySensor_cts__0__HSIOM_GPIO)
    #define SpectroscopySensor_CTS_HSIOM_SEL_UART  (SpectroscopySensor_cts__0__HSIOM_UART)
#endif /* (SpectroscopySensor_UART_CTS_PIN) */

#if (SpectroscopySensor_UART_TX_PIN)
    #define SpectroscopySensor_TX_HSIOM_REG   (*(reg32 *) SpectroscopySensor_tx__0__HSIOM)
    #define SpectroscopySensor_TX_HSIOM_PTR   ( (reg32 *) SpectroscopySensor_tx__0__HSIOM)
    
    #define SpectroscopySensor_TX_HSIOM_MASK      (SpectroscopySensor_tx__0__HSIOM_MASK)
    #define SpectroscopySensor_TX_HSIOM_POS       (SpectroscopySensor_tx__0__HSIOM_SHIFT)
    #define SpectroscopySensor_TX_HSIOM_SEL_GPIO  (SpectroscopySensor_tx__0__HSIOM_GPIO)
    #define SpectroscopySensor_TX_HSIOM_SEL_UART  (SpectroscopySensor_tx__0__HSIOM_UART)
#endif /* (SpectroscopySensor_UART_TX_PIN) */

#if (SpectroscopySensor_UART_RX_TX_PIN)
    #define SpectroscopySensor_RX_TX_HSIOM_REG   (*(reg32 *) SpectroscopySensor_rx_tx__0__HSIOM)
    #define SpectroscopySensor_RX_TX_HSIOM_PTR   ( (reg32 *) SpectroscopySensor_rx_tx__0__HSIOM)
    
    #define SpectroscopySensor_RX_TX_HSIOM_MASK      (SpectroscopySensor_rx_tx__0__HSIOM_MASK)
    #define SpectroscopySensor_RX_TX_HSIOM_POS       (SpectroscopySensor_rx_tx__0__HSIOM_SHIFT)
    #define SpectroscopySensor_RX_TX_HSIOM_SEL_GPIO  (SpectroscopySensor_rx_tx__0__HSIOM_GPIO)
    #define SpectroscopySensor_RX_TX_HSIOM_SEL_UART  (SpectroscopySensor_rx_tx__0__HSIOM_UART)
#endif /* (SpectroscopySensor_UART_RX_TX_PIN) */

#if (SpectroscopySensor_UART_RTS_PIN)
    #define SpectroscopySensor_RTS_HSIOM_REG      (*(reg32 *) SpectroscopySensor_rts__0__HSIOM)
    #define SpectroscopySensor_RTS_HSIOM_PTR      ( (reg32 *) SpectroscopySensor_rts__0__HSIOM)
    
    #define SpectroscopySensor_RTS_HSIOM_MASK     (SpectroscopySensor_rts__0__HSIOM_MASK)
    #define SpectroscopySensor_RTS_HSIOM_POS      (SpectroscopySensor_rts__0__HSIOM_SHIFT)    
    #define SpectroscopySensor_RTS_HSIOM_SEL_GPIO (SpectroscopySensor_rts__0__HSIOM_GPIO)
    #define SpectroscopySensor_RTS_HSIOM_SEL_UART (SpectroscopySensor_rts__0__HSIOM_UART)    
#endif /* (SpectroscopySensor_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define SpectroscopySensor_HSIOM_DEF_SEL      (0x00u)
#define SpectroscopySensor_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for SpectroscopySensor_CY_SCBIP_V0 
* and SpectroscopySensor_CY_SCBIP_V1. It is not recommended to use them for 
* SpectroscopySensor_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define SpectroscopySensor_HSIOM_UART_SEL     (0x09u)
#define SpectroscopySensor_HSIOM_I2C_SEL      (0x0Eu)
#define SpectroscopySensor_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define SpectroscopySensor_RX_SCL_MOSI_PIN_INDEX       (0u)
#define SpectroscopySensor_TX_SDA_MISO_PIN_INDEX       (1u)
#define SpectroscopySensor_CTS_SCLK_PIN_INDEX       (2u)
#define SpectroscopySensor_RTS_SS0_PIN_INDEX       (3u)
#define SpectroscopySensor_SS1_PIN_INDEX                  (4u)
#define SpectroscopySensor_SS2_PIN_INDEX                  (5u)
#define SpectroscopySensor_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define SpectroscopySensor_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << SpectroscopySensor_RX_SCL_MOSI_PIN_INDEX)
#define SpectroscopySensor_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << SpectroscopySensor_TX_SDA_MISO_PIN_INDEX)
#define SpectroscopySensor_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << SpectroscopySensor_CTS_SCLK_PIN_INDEX)
#define SpectroscopySensor_RTS_SS0_PIN_MASK     ((uint32) 0x01u << SpectroscopySensor_RTS_SS0_PIN_INDEX)
#define SpectroscopySensor_SS1_PIN_MASK                ((uint32) 0x01u << SpectroscopySensor_SS1_PIN_INDEX)
#define SpectroscopySensor_SS2_PIN_MASK                ((uint32) 0x01u << SpectroscopySensor_SS2_PIN_INDEX)
#define SpectroscopySensor_SS3_PIN_MASK                ((uint32) 0x01u << SpectroscopySensor_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define SpectroscopySensor_INTCFG_TYPE_MASK           (0x03u)
#define SpectroscopySensor_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define SpectroscopySensor_PIN_DM_ALG_HIZ  (0u)
#define SpectroscopySensor_PIN_DM_DIG_HIZ  (1u)
#define SpectroscopySensor_PIN_DM_OD_LO    (4u)
#define SpectroscopySensor_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define SpectroscopySensor_DM_MASK    (0x7u)
#define SpectroscopySensor_DM_SIZE    (3u)
#define SpectroscopySensor_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) SpectroscopySensor_DM_MASK << (SpectroscopySensor_DM_SIZE * (pos)))) >> \
                                                              (SpectroscopySensor_DM_SIZE * (pos)) )

#if (SpectroscopySensor_TX_SDA_MISO_PIN)
    #define SpectroscopySensor_CHECK_TX_SDA_MISO_PIN_USED \
                (SpectroscopySensor_PIN_DM_ALG_HIZ != \
                    SpectroscopySensor_GET_P4_PIN_DM(SpectroscopySensor_uart_tx_i2c_sda_spi_miso_PC, \
                                                   SpectroscopySensor_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (SpectroscopySensor_TX_SDA_MISO_PIN) */

#if (SpectroscopySensor_RTS_SS0_PIN)
    #define SpectroscopySensor_CHECK_RTS_SS0_PIN_USED \
                (SpectroscopySensor_PIN_DM_ALG_HIZ != \
                    SpectroscopySensor_GET_P4_PIN_DM(SpectroscopySensor_uart_rts_spi_ss0_PC, \
                                                   SpectroscopySensor_uart_rts_spi_ss0_SHIFT))
#endif /* (SpectroscopySensor_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define SpectroscopySensor_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define SpectroscopySensor_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define SpectroscopySensor_SET_HSIOM_SEL(reg, mask, pos, sel) SpectroscopySensor_SET_REGISTER_BITS(reg, mask, pos, sel)
#define SpectroscopySensor_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        SpectroscopySensor_SET_REGISTER_BITS(reg, mask, pos, intType)
#define SpectroscopySensor_SET_INP_DIS(reg, mask, val) SpectroscopySensor_SET_REGISTER_BIT(reg, mask, val)

/* SpectroscopySensor_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  SpectroscopySensor_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (SpectroscopySensor_CY_SCBIP_V0)
#if (SpectroscopySensor_I2C_PINS)
    #define SpectroscopySensor_SET_I2C_SCL_DR(val) SpectroscopySensor_scl_Write(val)

    #define SpectroscopySensor_SET_I2C_SCL_HSIOM_SEL(sel) \
                          SpectroscopySensor_SET_HSIOM_SEL(SpectroscopySensor_SCL_HSIOM_REG,  \
                                                         SpectroscopySensor_SCL_HSIOM_MASK, \
                                                         SpectroscopySensor_SCL_HSIOM_POS,  \
                                                         (sel))
    #define SpectroscopySensor_WAIT_SCL_SET_HIGH  (0u == SpectroscopySensor_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN)
    #define SpectroscopySensor_SET_I2C_SCL_DR(val) \
                            SpectroscopySensor_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define SpectroscopySensor_SET_I2C_SCL_HSIOM_SEL(sel) \
                    SpectroscopySensor_SET_HSIOM_SEL(SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define SpectroscopySensor_WAIT_SCL_SET_HIGH  (0u == SpectroscopySensor_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (SpectroscopySensor_RX_SCL_MOSI_PIN)
    #define SpectroscopySensor_SET_I2C_SCL_DR(val) \
                            SpectroscopySensor_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define SpectroscopySensor_SET_I2C_SCL_HSIOM_SEL(sel) \
                            SpectroscopySensor_SET_HSIOM_SEL(SpectroscopySensor_RX_SCL_MOSI_HSIOM_REG,  \
                                                           SpectroscopySensor_RX_SCL_MOSI_HSIOM_MASK, \
                                                           SpectroscopySensor_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define SpectroscopySensor_WAIT_SCL_SET_HIGH  (0u == SpectroscopySensor_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define SpectroscopySensor_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define SpectroscopySensor_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define SpectroscopySensor_WAIT_SCL_SET_HIGH  (0u)
#endif /* (SpectroscopySensor_I2C_PINS) */

/* SCB I2C: sda signal */
#if (SpectroscopySensor_I2C_PINS)
    #define SpectroscopySensor_WAIT_SDA_SET_HIGH  (0u == SpectroscopySensor_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (SpectroscopySensor_TX_SDA_MISO_PIN)
    #define SpectroscopySensor_WAIT_SDA_SET_HIGH  (0u == SpectroscopySensor_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define SpectroscopySensor_WAIT_SDA_SET_HIGH  (0u)
#endif /* (SpectroscopySensor_MOSI_SCL_RX_PIN) */
#endif /* (SpectroscopySensor_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (SpectroscopySensor_RX_SCL_MOSI_PIN)
    #define SpectroscopySensor_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN)
    #define SpectroscopySensor_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) SpectroscopySensor_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(SpectroscopySensor_UART_RX_WAKE_PIN)
    #define SpectroscopySensor_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) SpectroscopySensor_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (SpectroscopySensor_RX_SCL_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define SpectroscopySensor_REMOVE_MOSI_SCL_RX_WAKE_PIN    SpectroscopySensor_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define SpectroscopySensor_REMOVE_MOSI_SCL_RX_PIN         SpectroscopySensor_REMOVE_RX_SCL_MOSI_PIN
#define SpectroscopySensor_REMOVE_MISO_SDA_TX_PIN         SpectroscopySensor_REMOVE_TX_SDA_MISO_PIN
#ifndef SpectroscopySensor_REMOVE_SCLK_PIN
#define SpectroscopySensor_REMOVE_SCLK_PIN                SpectroscopySensor_REMOVE_CTS_SCLK_PIN
#endif /* SpectroscopySensor_REMOVE_SCLK_PIN */
#ifndef SpectroscopySensor_REMOVE_SS0_PIN
#define SpectroscopySensor_REMOVE_SS0_PIN                 SpectroscopySensor_REMOVE_RTS_SS0_PIN
#endif /* SpectroscopySensor_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define SpectroscopySensor_MOSI_SCL_RX_WAKE_PIN   SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN
#define SpectroscopySensor_MOSI_SCL_RX_PIN        SpectroscopySensor_RX_SCL_MOSI_PIN
#define SpectroscopySensor_MISO_SDA_TX_PIN        SpectroscopySensor_TX_SDA_MISO_PIN
#ifndef SpectroscopySensor_SCLK_PIN
#define SpectroscopySensor_SCLK_PIN               SpectroscopySensor_CTS_SCLK_PIN
#endif /* SpectroscopySensor_SCLK_PIN */
#ifndef SpectroscopySensor_SS0_PIN
#define SpectroscopySensor_SS0_PIN                SpectroscopySensor_RTS_SS0_PIN
#endif /* SpectroscopySensor_SS0_PIN */

#if (SpectroscopySensor_MOSI_SCL_RX_WAKE_PIN)
    #define SpectroscopySensor_MOSI_SCL_RX_WAKE_HSIOM_REG     SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SpectroscopySensor_MOSI_SCL_RX_WAKE_HSIOM_PTR     SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SpectroscopySensor_MOSI_SCL_RX_WAKE_HSIOM_MASK    SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SpectroscopySensor_MOSI_SCL_RX_WAKE_HSIOM_POS     SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define SpectroscopySensor_MOSI_SCL_RX_WAKE_INTCFG_REG    SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SpectroscopySensor_MOSI_SCL_RX_WAKE_INTCFG_PTR    SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define SpectroscopySensor_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define SpectroscopySensor_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  SpectroscopySensor_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN) */

#if (SpectroscopySensor_MOSI_SCL_RX_PIN)
    #define SpectroscopySensor_MOSI_SCL_RX_HSIOM_REG      SpectroscopySensor_RX_SCL_MOSI_HSIOM_REG
    #define SpectroscopySensor_MOSI_SCL_RX_HSIOM_PTR      SpectroscopySensor_RX_SCL_MOSI_HSIOM_PTR
    #define SpectroscopySensor_MOSI_SCL_RX_HSIOM_MASK     SpectroscopySensor_RX_SCL_MOSI_HSIOM_MASK
    #define SpectroscopySensor_MOSI_SCL_RX_HSIOM_POS      SpectroscopySensor_RX_SCL_MOSI_HSIOM_POS
#endif /* (SpectroscopySensor_MOSI_SCL_RX_PIN) */

#if (SpectroscopySensor_MISO_SDA_TX_PIN)
    #define SpectroscopySensor_MISO_SDA_TX_HSIOM_REG      SpectroscopySensor_TX_SDA_MISO_HSIOM_REG
    #define SpectroscopySensor_MISO_SDA_TX_HSIOM_PTR      SpectroscopySensor_TX_SDA_MISO_HSIOM_REG
    #define SpectroscopySensor_MISO_SDA_TX_HSIOM_MASK     SpectroscopySensor_TX_SDA_MISO_HSIOM_REG
    #define SpectroscopySensor_MISO_SDA_TX_HSIOM_POS      SpectroscopySensor_TX_SDA_MISO_HSIOM_REG
#endif /* (SpectroscopySensor_MISO_SDA_TX_PIN_PIN) */

#if (SpectroscopySensor_SCLK_PIN)
    #ifndef SpectroscopySensor_SCLK_HSIOM_REG
    #define SpectroscopySensor_SCLK_HSIOM_REG     SpectroscopySensor_CTS_SCLK_HSIOM_REG
    #define SpectroscopySensor_SCLK_HSIOM_PTR     SpectroscopySensor_CTS_SCLK_HSIOM_PTR
    #define SpectroscopySensor_SCLK_HSIOM_MASK    SpectroscopySensor_CTS_SCLK_HSIOM_MASK
    #define SpectroscopySensor_SCLK_HSIOM_POS     SpectroscopySensor_CTS_SCLK_HSIOM_POS
    #endif /* SpectroscopySensor_SCLK_HSIOM_REG */
#endif /* (SpectroscopySensor_SCLK_PIN) */

#if (SpectroscopySensor_SS0_PIN)
    #ifndef SpectroscopySensor_SS0_HSIOM_REG
    #define SpectroscopySensor_SS0_HSIOM_REG      SpectroscopySensor_RTS_SS0_HSIOM_REG
    #define SpectroscopySensor_SS0_HSIOM_PTR      SpectroscopySensor_RTS_SS0_HSIOM_PTR
    #define SpectroscopySensor_SS0_HSIOM_MASK     SpectroscopySensor_RTS_SS0_HSIOM_MASK
    #define SpectroscopySensor_SS0_HSIOM_POS      SpectroscopySensor_RTS_SS0_HSIOM_POS
    #endif /* SpectroscopySensor_SS0_HSIOM_REG */
#endif /* (SpectroscopySensor_SS0_PIN) */

#define SpectroscopySensor_MOSI_SCL_RX_WAKE_PIN_INDEX SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN_INDEX
#define SpectroscopySensor_MOSI_SCL_RX_PIN_INDEX      SpectroscopySensor_RX_SCL_MOSI_PIN_INDEX
#define SpectroscopySensor_MISO_SDA_TX_PIN_INDEX      SpectroscopySensor_TX_SDA_MISO_PIN_INDEX
#ifndef SpectroscopySensor_SCLK_PIN_INDEX
#define SpectroscopySensor_SCLK_PIN_INDEX             SpectroscopySensor_CTS_SCLK_PIN_INDEX
#endif /* SpectroscopySensor_SCLK_PIN_INDEX */
#ifndef SpectroscopySensor_SS0_PIN_INDEX
#define SpectroscopySensor_SS0_PIN_INDEX              SpectroscopySensor_RTS_SS0_PIN_INDEX
#endif /* SpectroscopySensor_SS0_PIN_INDEX */

#define SpectroscopySensor_MOSI_SCL_RX_WAKE_PIN_MASK SpectroscopySensor_RX_WAKE_SCL_MOSI_PIN_MASK
#define SpectroscopySensor_MOSI_SCL_RX_PIN_MASK      SpectroscopySensor_RX_SCL_MOSI_PIN_MASK
#define SpectroscopySensor_MISO_SDA_TX_PIN_MASK      SpectroscopySensor_TX_SDA_MISO_PIN_MASK
#ifndef SpectroscopySensor_SCLK_PIN_MASK
#define SpectroscopySensor_SCLK_PIN_MASK             SpectroscopySensor_CTS_SCLK_PIN_MASK
#endif /* SpectroscopySensor_SCLK_PIN_MASK */
#ifndef SpectroscopySensor_SS0_PIN_MASK
#define SpectroscopySensor_SS0_PIN_MASK              SpectroscopySensor_RTS_SS0_PIN_MASK
#endif /* SpectroscopySensor_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_SpectroscopySensor_H) */


/* [] END OF FILE */
