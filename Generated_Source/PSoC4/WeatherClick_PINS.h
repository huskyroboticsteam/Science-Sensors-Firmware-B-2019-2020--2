/***************************************************************************//**
* \file WeatherClick_PINS.h
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

#if !defined(CY_SCB_PINS_WeatherClick_H)
#define CY_SCB_PINS_WeatherClick_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define WeatherClick_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define WeatherClick_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define WeatherClick_REMOVE_TX_SDA_MISO_PIN      (1u)
#define WeatherClick_REMOVE_CTS_SCLK_PIN      (1u)
#define WeatherClick_REMOVE_RTS_SS0_PIN      (1u)
#define WeatherClick_REMOVE_SS1_PIN                 (1u)
#define WeatherClick_REMOVE_SS2_PIN                 (1u)
#define WeatherClick_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define WeatherClick_REMOVE_I2C_PINS                (0u)
#define WeatherClick_REMOVE_SPI_MASTER_PINS         (1u)
#define WeatherClick_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define WeatherClick_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define WeatherClick_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define WeatherClick_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define WeatherClick_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define WeatherClick_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define WeatherClick_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define WeatherClick_REMOVE_SPI_SLAVE_PINS          (1u)
#define WeatherClick_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define WeatherClick_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define WeatherClick_REMOVE_UART_TX_PIN             (1u)
#define WeatherClick_REMOVE_UART_RX_TX_PIN          (1u)
#define WeatherClick_REMOVE_UART_RX_PIN             (1u)
#define WeatherClick_REMOVE_UART_RX_WAKE_PIN        (1u)
#define WeatherClick_REMOVE_UART_RTS_PIN            (1u)
#define WeatherClick_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define WeatherClick_RX_WAKE_SCL_MOSI_PIN (0u == WeatherClick_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define WeatherClick_RX_SCL_MOSI_PIN     (0u == WeatherClick_REMOVE_RX_SCL_MOSI_PIN)
#define WeatherClick_TX_SDA_MISO_PIN     (0u == WeatherClick_REMOVE_TX_SDA_MISO_PIN)
#define WeatherClick_CTS_SCLK_PIN     (0u == WeatherClick_REMOVE_CTS_SCLK_PIN)
#define WeatherClick_RTS_SS0_PIN     (0u == WeatherClick_REMOVE_RTS_SS0_PIN)
#define WeatherClick_SS1_PIN                (0u == WeatherClick_REMOVE_SS1_PIN)
#define WeatherClick_SS2_PIN                (0u == WeatherClick_REMOVE_SS2_PIN)
#define WeatherClick_SS3_PIN                (0u == WeatherClick_REMOVE_SS3_PIN)

/* Mode defined pins */
#define WeatherClick_I2C_PINS               (0u == WeatherClick_REMOVE_I2C_PINS)
#define WeatherClick_SPI_MASTER_PINS        (0u == WeatherClick_REMOVE_SPI_MASTER_PINS)
#define WeatherClick_SPI_MASTER_SCLK_PIN    (0u == WeatherClick_REMOVE_SPI_MASTER_SCLK_PIN)
#define WeatherClick_SPI_MASTER_MOSI_PIN    (0u == WeatherClick_REMOVE_SPI_MASTER_MOSI_PIN)
#define WeatherClick_SPI_MASTER_MISO_PIN    (0u == WeatherClick_REMOVE_SPI_MASTER_MISO_PIN)
#define WeatherClick_SPI_MASTER_SS0_PIN     (0u == WeatherClick_REMOVE_SPI_MASTER_SS0_PIN)
#define WeatherClick_SPI_MASTER_SS1_PIN     (0u == WeatherClick_REMOVE_SPI_MASTER_SS1_PIN)
#define WeatherClick_SPI_MASTER_SS2_PIN     (0u == WeatherClick_REMOVE_SPI_MASTER_SS2_PIN)
#define WeatherClick_SPI_MASTER_SS3_PIN     (0u == WeatherClick_REMOVE_SPI_MASTER_SS3_PIN)
#define WeatherClick_SPI_SLAVE_PINS         (0u == WeatherClick_REMOVE_SPI_SLAVE_PINS)
#define WeatherClick_SPI_SLAVE_MOSI_PIN     (0u == WeatherClick_REMOVE_SPI_SLAVE_MOSI_PIN)
#define WeatherClick_SPI_SLAVE_MISO_PIN     (0u == WeatherClick_REMOVE_SPI_SLAVE_MISO_PIN)
#define WeatherClick_UART_TX_PIN            (0u == WeatherClick_REMOVE_UART_TX_PIN)
#define WeatherClick_UART_RX_TX_PIN         (0u == WeatherClick_REMOVE_UART_RX_TX_PIN)
#define WeatherClick_UART_RX_PIN            (0u == WeatherClick_REMOVE_UART_RX_PIN)
#define WeatherClick_UART_RX_WAKE_PIN       (0u == WeatherClick_REMOVE_UART_RX_WAKE_PIN)
#define WeatherClick_UART_RTS_PIN           (0u == WeatherClick_REMOVE_UART_RTS_PIN)
#define WeatherClick_UART_CTS_PIN           (0u == WeatherClick_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (WeatherClick_RX_WAKE_SCL_MOSI_PIN)
    #include "WeatherClick_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (WeatherClick_RX_SCL_MOSI) */

#if (WeatherClick_RX_SCL_MOSI_PIN)
    #include "WeatherClick_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (WeatherClick_RX_SCL_MOSI) */

#if (WeatherClick_TX_SDA_MISO_PIN)
    #include "WeatherClick_uart_tx_i2c_sda_spi_miso.h"
#endif /* (WeatherClick_TX_SDA_MISO) */

#if (WeatherClick_CTS_SCLK_PIN)
    #include "WeatherClick_uart_cts_spi_sclk.h"
#endif /* (WeatherClick_CTS_SCLK) */

#if (WeatherClick_RTS_SS0_PIN)
    #include "WeatherClick_uart_rts_spi_ss0.h"
#endif /* (WeatherClick_RTS_SS0_PIN) */

#if (WeatherClick_SS1_PIN)
    #include "WeatherClick_spi_ss1.h"
#endif /* (WeatherClick_SS1_PIN) */

#if (WeatherClick_SS2_PIN)
    #include "WeatherClick_spi_ss2.h"
#endif /* (WeatherClick_SS2_PIN) */

#if (WeatherClick_SS3_PIN)
    #include "WeatherClick_spi_ss3.h"
#endif /* (WeatherClick_SS3_PIN) */

#if (WeatherClick_I2C_PINS)
    #include "WeatherClick_scl.h"
    #include "WeatherClick_sda.h"
#endif /* (WeatherClick_I2C_PINS) */

#if (WeatherClick_SPI_MASTER_PINS)
#if (WeatherClick_SPI_MASTER_SCLK_PIN)
    #include "WeatherClick_sclk_m.h"
#endif /* (WeatherClick_SPI_MASTER_SCLK_PIN) */

#if (WeatherClick_SPI_MASTER_MOSI_PIN)
    #include "WeatherClick_mosi_m.h"
#endif /* (WeatherClick_SPI_MASTER_MOSI_PIN) */

#if (WeatherClick_SPI_MASTER_MISO_PIN)
    #include "WeatherClick_miso_m.h"
#endif /*(WeatherClick_SPI_MASTER_MISO_PIN) */
#endif /* (WeatherClick_SPI_MASTER_PINS) */

#if (WeatherClick_SPI_SLAVE_PINS)
    #include "WeatherClick_sclk_s.h"
    #include "WeatherClick_ss_s.h"

#if (WeatherClick_SPI_SLAVE_MOSI_PIN)
    #include "WeatherClick_mosi_s.h"
#endif /* (WeatherClick_SPI_SLAVE_MOSI_PIN) */

#if (WeatherClick_SPI_SLAVE_MISO_PIN)
    #include "WeatherClick_miso_s.h"
#endif /*(WeatherClick_SPI_SLAVE_MISO_PIN) */
#endif /* (WeatherClick_SPI_SLAVE_PINS) */

#if (WeatherClick_SPI_MASTER_SS0_PIN)
    #include "WeatherClick_ss0_m.h"
#endif /* (WeatherClick_SPI_MASTER_SS0_PIN) */

#if (WeatherClick_SPI_MASTER_SS1_PIN)
    #include "WeatherClick_ss1_m.h"
#endif /* (WeatherClick_SPI_MASTER_SS1_PIN) */

#if (WeatherClick_SPI_MASTER_SS2_PIN)
    #include "WeatherClick_ss2_m.h"
#endif /* (WeatherClick_SPI_MASTER_SS2_PIN) */

#if (WeatherClick_SPI_MASTER_SS3_PIN)
    #include "WeatherClick_ss3_m.h"
#endif /* (WeatherClick_SPI_MASTER_SS3_PIN) */

#if (WeatherClick_UART_TX_PIN)
    #include "WeatherClick_tx.h"
#endif /* (WeatherClick_UART_TX_PIN) */

#if (WeatherClick_UART_RX_TX_PIN)
    #include "WeatherClick_rx_tx.h"
#endif /* (WeatherClick_UART_RX_TX_PIN) */

#if (WeatherClick_UART_RX_PIN)
    #include "WeatherClick_rx.h"
#endif /* (WeatherClick_UART_RX_PIN) */

#if (WeatherClick_UART_RX_WAKE_PIN)
    #include "WeatherClick_rx_wake.h"
#endif /* (WeatherClick_UART_RX_WAKE_PIN) */

#if (WeatherClick_UART_RTS_PIN)
    #include "WeatherClick_rts.h"
#endif /* (WeatherClick_UART_RTS_PIN) */

#if (WeatherClick_UART_CTS_PIN)
    #include "WeatherClick_cts.h"
#endif /* (WeatherClick_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (WeatherClick_RX_SCL_MOSI_PIN)
    #define WeatherClick_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) WeatherClick_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define WeatherClick_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) WeatherClick_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    
    #define WeatherClick_RX_SCL_MOSI_HSIOM_MASK      (WeatherClick_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define WeatherClick_RX_SCL_MOSI_HSIOM_POS       (WeatherClick_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define WeatherClick_RX_SCL_MOSI_HSIOM_SEL_GPIO  (WeatherClick_uart_rx_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define WeatherClick_RX_SCL_MOSI_HSIOM_SEL_I2C   (WeatherClick_uart_rx_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define WeatherClick_RX_SCL_MOSI_HSIOM_SEL_SPI   (WeatherClick_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define WeatherClick_RX_SCL_MOSI_HSIOM_SEL_UART  (WeatherClick_uart_rx_i2c_scl_spi_mosi__0__HSIOM_UART)
    
#elif (WeatherClick_RX_WAKE_SCL_MOSI_PIN)
    #define WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_REG   (*(reg32 *) WeatherClick_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_PTR   ( (reg32 *) WeatherClick_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    
    #define WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_MASK      (WeatherClick_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_POS       (WeatherClick_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_SEL_GPIO  (WeatherClick_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C   (WeatherClick_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI   (WeatherClick_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART  (WeatherClick_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_UART)    
   
    #define WeatherClick_RX_WAKE_SCL_MOSI_INTCFG_REG (*(reg32 *) WeatherClick_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define WeatherClick_RX_WAKE_SCL_MOSI_INTCFG_PTR ( (reg32 *) WeatherClick_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define WeatherClick_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (WeatherClick_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define WeatherClick_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK ((uint32) WeatherClick_INTCFG_TYPE_MASK << \
                                                                           WeatherClick_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins WeatherClick_RX_SCL_MOSI_PIN or WeatherClick_RX_WAKE_SCL_MOSI_PIN present.*/
#endif /* (WeatherClick_RX_SCL_MOSI_PIN) */

#if (WeatherClick_TX_SDA_MISO_PIN)
    #define WeatherClick_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) WeatherClick_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define WeatherClick_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) WeatherClick_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    
    #define WeatherClick_TX_SDA_MISO_HSIOM_MASK      (WeatherClick_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define WeatherClick_TX_SDA_MISO_HSIOM_POS       (WeatherClick_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
    #define WeatherClick_TX_SDA_MISO_HSIOM_SEL_GPIO  (WeatherClick_uart_tx_i2c_sda_spi_miso__0__HSIOM_GPIO)
    #define WeatherClick_TX_SDA_MISO_HSIOM_SEL_I2C   (WeatherClick_uart_tx_i2c_sda_spi_miso__0__HSIOM_I2C)
    #define WeatherClick_TX_SDA_MISO_HSIOM_SEL_SPI   (WeatherClick_uart_tx_i2c_sda_spi_miso__0__HSIOM_SPI)
    #define WeatherClick_TX_SDA_MISO_HSIOM_SEL_UART  (WeatherClick_uart_tx_i2c_sda_spi_miso__0__HSIOM_UART)
#endif /* (WeatherClick_TX_SDA_MISO_PIN) */

#if (WeatherClick_CTS_SCLK_PIN)
    #define WeatherClick_CTS_SCLK_HSIOM_REG   (*(reg32 *) WeatherClick_uart_cts_spi_sclk__0__HSIOM)
    #define WeatherClick_CTS_SCLK_HSIOM_PTR   ( (reg32 *) WeatherClick_uart_cts_spi_sclk__0__HSIOM)
    
    #define WeatherClick_CTS_SCLK_HSIOM_MASK      (WeatherClick_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define WeatherClick_CTS_SCLK_HSIOM_POS       (WeatherClick_uart_cts_spi_sclk__0__HSIOM_SHIFT)
    #define WeatherClick_CTS_SCLK_HSIOM_SEL_GPIO  (WeatherClick_uart_cts_spi_sclk__0__HSIOM_GPIO)
    #define WeatherClick_CTS_SCLK_HSIOM_SEL_I2C   (WeatherClick_uart_cts_spi_sclk__0__HSIOM_I2C)
    #define WeatherClick_CTS_SCLK_HSIOM_SEL_SPI   (WeatherClick_uart_cts_spi_sclk__0__HSIOM_SPI)
    #define WeatherClick_CTS_SCLK_HSIOM_SEL_UART  (WeatherClick_uart_cts_spi_sclk__0__HSIOM_UART)
#endif /* (WeatherClick_CTS_SCLK_PIN) */

#if (WeatherClick_RTS_SS0_PIN)
    #define WeatherClick_RTS_SS0_HSIOM_REG   (*(reg32 *) WeatherClick_uart_rts_spi_ss0__0__HSIOM)
    #define WeatherClick_RTS_SS0_HSIOM_PTR   ( (reg32 *) WeatherClick_uart_rts_spi_ss0__0__HSIOM)
    
    #define WeatherClick_RTS_SS0_HSIOM_MASK      (WeatherClick_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define WeatherClick_RTS_SS0_HSIOM_POS       (WeatherClick_uart_rts_spi_ss0__0__HSIOM_SHIFT)
    #define WeatherClick_RTS_SS0_HSIOM_SEL_GPIO  (WeatherClick_uart_rts_spi_ss0__0__HSIOM_GPIO)
    #define WeatherClick_RTS_SS0_HSIOM_SEL_I2C   (WeatherClick_uart_rts_spi_ss0__0__HSIOM_I2C)
    #define WeatherClick_RTS_SS0_HSIOM_SEL_SPI   (WeatherClick_uart_rts_spi_ss0__0__HSIOM_SPI)
#if !(WeatherClick_CY_SCBIP_V0 || WeatherClick_CY_SCBIP_V1)
    #define WeatherClick_RTS_SS0_HSIOM_SEL_UART  (WeatherClick_uart_rts_spi_ss0__0__HSIOM_UART)
#endif /* !(WeatherClick_CY_SCBIP_V0 || WeatherClick_CY_SCBIP_V1) */
#endif /* (WeatherClick_RTS_SS0_PIN) */

#if (WeatherClick_SS1_PIN)
    #define WeatherClick_SS1_HSIOM_REG  (*(reg32 *) WeatherClick_spi_ss1__0__HSIOM)
    #define WeatherClick_SS1_HSIOM_PTR  ( (reg32 *) WeatherClick_spi_ss1__0__HSIOM)
    
    #define WeatherClick_SS1_HSIOM_MASK     (WeatherClick_spi_ss1__0__HSIOM_MASK)
    #define WeatherClick_SS1_HSIOM_POS      (WeatherClick_spi_ss1__0__HSIOM_SHIFT)
    #define WeatherClick_SS1_HSIOM_SEL_GPIO (WeatherClick_spi_ss1__0__HSIOM_GPIO)
    #define WeatherClick_SS1_HSIOM_SEL_I2C  (WeatherClick_spi_ss1__0__HSIOM_I2C)
    #define WeatherClick_SS1_HSIOM_SEL_SPI  (WeatherClick_spi_ss1__0__HSIOM_SPI)
#endif /* (WeatherClick_SS1_PIN) */

#if (WeatherClick_SS2_PIN)
    #define WeatherClick_SS2_HSIOM_REG     (*(reg32 *) WeatherClick_spi_ss2__0__HSIOM)
    #define WeatherClick_SS2_HSIOM_PTR     ( (reg32 *) WeatherClick_spi_ss2__0__HSIOM)
    
    #define WeatherClick_SS2_HSIOM_MASK     (WeatherClick_spi_ss2__0__HSIOM_MASK)
    #define WeatherClick_SS2_HSIOM_POS      (WeatherClick_spi_ss2__0__HSIOM_SHIFT)
    #define WeatherClick_SS2_HSIOM_SEL_GPIO (WeatherClick_spi_ss2__0__HSIOM_GPIO)
    #define WeatherClick_SS2_HSIOM_SEL_I2C  (WeatherClick_spi_ss2__0__HSIOM_I2C)
    #define WeatherClick_SS2_HSIOM_SEL_SPI  (WeatherClick_spi_ss2__0__HSIOM_SPI)
#endif /* (WeatherClick_SS2_PIN) */

#if (WeatherClick_SS3_PIN)
    #define WeatherClick_SS3_HSIOM_REG     (*(reg32 *) WeatherClick_spi_ss3__0__HSIOM)
    #define WeatherClick_SS3_HSIOM_PTR     ( (reg32 *) WeatherClick_spi_ss3__0__HSIOM)
    
    #define WeatherClick_SS3_HSIOM_MASK     (WeatherClick_spi_ss3__0__HSIOM_MASK)
    #define WeatherClick_SS3_HSIOM_POS      (WeatherClick_spi_ss3__0__HSIOM_SHIFT)
    #define WeatherClick_SS3_HSIOM_SEL_GPIO (WeatherClick_spi_ss3__0__HSIOM_GPIO)
    #define WeatherClick_SS3_HSIOM_SEL_I2C  (WeatherClick_spi_ss3__0__HSIOM_I2C)
    #define WeatherClick_SS3_HSIOM_SEL_SPI  (WeatherClick_spi_ss3__0__HSIOM_SPI)
#endif /* (WeatherClick_SS3_PIN) */

#if (WeatherClick_I2C_PINS)
    #define WeatherClick_SCL_HSIOM_REG  (*(reg32 *) WeatherClick_scl__0__HSIOM)
    #define WeatherClick_SCL_HSIOM_PTR  ( (reg32 *) WeatherClick_scl__0__HSIOM)
    
    #define WeatherClick_SCL_HSIOM_MASK     (WeatherClick_scl__0__HSIOM_MASK)
    #define WeatherClick_SCL_HSIOM_POS      (WeatherClick_scl__0__HSIOM_SHIFT)
    #define WeatherClick_SCL_HSIOM_SEL_GPIO (WeatherClick_sda__0__HSIOM_GPIO)
    #define WeatherClick_SCL_HSIOM_SEL_I2C  (WeatherClick_sda__0__HSIOM_I2C)
    
    #define WeatherClick_SDA_HSIOM_REG  (*(reg32 *) WeatherClick_sda__0__HSIOM)
    #define WeatherClick_SDA_HSIOM_PTR  ( (reg32 *) WeatherClick_sda__0__HSIOM)
    
    #define WeatherClick_SDA_HSIOM_MASK     (WeatherClick_sda__0__HSIOM_MASK)
    #define WeatherClick_SDA_HSIOM_POS      (WeatherClick_sda__0__HSIOM_SHIFT)
    #define WeatherClick_SDA_HSIOM_SEL_GPIO (WeatherClick_sda__0__HSIOM_GPIO)
    #define WeatherClick_SDA_HSIOM_SEL_I2C  (WeatherClick_sda__0__HSIOM_I2C)
#endif /* (WeatherClick_I2C_PINS) */

#if (WeatherClick_SPI_SLAVE_PINS)
    #define WeatherClick_SCLK_S_HSIOM_REG   (*(reg32 *) WeatherClick_sclk_s__0__HSIOM)
    #define WeatherClick_SCLK_S_HSIOM_PTR   ( (reg32 *) WeatherClick_sclk_s__0__HSIOM)
    
    #define WeatherClick_SCLK_S_HSIOM_MASK      (WeatherClick_sclk_s__0__HSIOM_MASK)
    #define WeatherClick_SCLK_S_HSIOM_POS       (WeatherClick_sclk_s__0__HSIOM_SHIFT)
    #define WeatherClick_SCLK_S_HSIOM_SEL_GPIO  (WeatherClick_sclk_s__0__HSIOM_GPIO)
    #define WeatherClick_SCLK_S_HSIOM_SEL_SPI   (WeatherClick_sclk_s__0__HSIOM_SPI)
    
    #define WeatherClick_SS0_S_HSIOM_REG    (*(reg32 *) WeatherClick_ss0_s__0__HSIOM)
    #define WeatherClick_SS0_S_HSIOM_PTR    ( (reg32 *) WeatherClick_ss0_s__0__HSIOM)
    
    #define WeatherClick_SS0_S_HSIOM_MASK       (WeatherClick_ss0_s__0__HSIOM_MASK)
    #define WeatherClick_SS0_S_HSIOM_POS        (WeatherClick_ss0_s__0__HSIOM_SHIFT)
    #define WeatherClick_SS0_S_HSIOM_SEL_GPIO   (WeatherClick_ss0_s__0__HSIOM_GPIO)  
    #define WeatherClick_SS0_S_HSIOM_SEL_SPI    (WeatherClick_ss0_s__0__HSIOM_SPI)
#endif /* (WeatherClick_SPI_SLAVE_PINS) */

#if (WeatherClick_SPI_SLAVE_MOSI_PIN)
    #define WeatherClick_MOSI_S_HSIOM_REG   (*(reg32 *) WeatherClick_mosi_s__0__HSIOM)
    #define WeatherClick_MOSI_S_HSIOM_PTR   ( (reg32 *) WeatherClick_mosi_s__0__HSIOM)
    
    #define WeatherClick_MOSI_S_HSIOM_MASK      (WeatherClick_mosi_s__0__HSIOM_MASK)
    #define WeatherClick_MOSI_S_HSIOM_POS       (WeatherClick_mosi_s__0__HSIOM_SHIFT)
    #define WeatherClick_MOSI_S_HSIOM_SEL_GPIO  (WeatherClick_mosi_s__0__HSIOM_GPIO)
    #define WeatherClick_MOSI_S_HSIOM_SEL_SPI   (WeatherClick_mosi_s__0__HSIOM_SPI)
#endif /* (WeatherClick_SPI_SLAVE_MOSI_PIN) */

#if (WeatherClick_SPI_SLAVE_MISO_PIN)
    #define WeatherClick_MISO_S_HSIOM_REG   (*(reg32 *) WeatherClick_miso_s__0__HSIOM)
    #define WeatherClick_MISO_S_HSIOM_PTR   ( (reg32 *) WeatherClick_miso_s__0__HSIOM)
    
    #define WeatherClick_MISO_S_HSIOM_MASK      (WeatherClick_miso_s__0__HSIOM_MASK)
    #define WeatherClick_MISO_S_HSIOM_POS       (WeatherClick_miso_s__0__HSIOM_SHIFT)
    #define WeatherClick_MISO_S_HSIOM_SEL_GPIO  (WeatherClick_miso_s__0__HSIOM_GPIO)
    #define WeatherClick_MISO_S_HSIOM_SEL_SPI   (WeatherClick_miso_s__0__HSIOM_SPI)
#endif /* (WeatherClick_SPI_SLAVE_MISO_PIN) */

#if (WeatherClick_SPI_MASTER_MISO_PIN)
    #define WeatherClick_MISO_M_HSIOM_REG   (*(reg32 *) WeatherClick_miso_m__0__HSIOM)
    #define WeatherClick_MISO_M_HSIOM_PTR   ( (reg32 *) WeatherClick_miso_m__0__HSIOM)
    
    #define WeatherClick_MISO_M_HSIOM_MASK      (WeatherClick_miso_m__0__HSIOM_MASK)
    #define WeatherClick_MISO_M_HSIOM_POS       (WeatherClick_miso_m__0__HSIOM_SHIFT)
    #define WeatherClick_MISO_M_HSIOM_SEL_GPIO  (WeatherClick_miso_m__0__HSIOM_GPIO)
    #define WeatherClick_MISO_M_HSIOM_SEL_SPI   (WeatherClick_miso_m__0__HSIOM_SPI)
#endif /* (WeatherClick_SPI_MASTER_MISO_PIN) */

#if (WeatherClick_SPI_MASTER_MOSI_PIN)
    #define WeatherClick_MOSI_M_HSIOM_REG   (*(reg32 *) WeatherClick_mosi_m__0__HSIOM)
    #define WeatherClick_MOSI_M_HSIOM_PTR   ( (reg32 *) WeatherClick_mosi_m__0__HSIOM)
    
    #define WeatherClick_MOSI_M_HSIOM_MASK      (WeatherClick_mosi_m__0__HSIOM_MASK)
    #define WeatherClick_MOSI_M_HSIOM_POS       (WeatherClick_mosi_m__0__HSIOM_SHIFT)
    #define WeatherClick_MOSI_M_HSIOM_SEL_GPIO  (WeatherClick_mosi_m__0__HSIOM_GPIO)
    #define WeatherClick_MOSI_M_HSIOM_SEL_SPI   (WeatherClick_mosi_m__0__HSIOM_SPI)
#endif /* (WeatherClick_SPI_MASTER_MOSI_PIN) */

#if (WeatherClick_SPI_MASTER_SCLK_PIN)
    #define WeatherClick_SCLK_M_HSIOM_REG   (*(reg32 *) WeatherClick_sclk_m__0__HSIOM)
    #define WeatherClick_SCLK_M_HSIOM_PTR   ( (reg32 *) WeatherClick_sclk_m__0__HSIOM)
    
    #define WeatherClick_SCLK_M_HSIOM_MASK      (WeatherClick_sclk_m__0__HSIOM_MASK)
    #define WeatherClick_SCLK_M_HSIOM_POS       (WeatherClick_sclk_m__0__HSIOM_SHIFT)
    #define WeatherClick_SCLK_M_HSIOM_SEL_GPIO  (WeatherClick_sclk_m__0__HSIOM_GPIO)
    #define WeatherClick_SCLK_M_HSIOM_SEL_SPI   (WeatherClick_sclk_m__0__HSIOM_SPI)
#endif /* (WeatherClick_SPI_MASTER_SCLK_PIN) */

#if (WeatherClick_SPI_MASTER_SS0_PIN)
    #define WeatherClick_SS0_M_HSIOM_REG    (*(reg32 *) WeatherClick_ss0_m__0__HSIOM)
    #define WeatherClick_SS0_M_HSIOM_PTR    ( (reg32 *) WeatherClick_ss0_m__0__HSIOM)
    
    #define WeatherClick_SS0_M_HSIOM_MASK       (WeatherClick_ss0_m__0__HSIOM_MASK)
    #define WeatherClick_SS0_M_HSIOM_POS        (WeatherClick_ss0_m__0__HSIOM_SHIFT)
    #define WeatherClick_SS0_M_HSIOM_SEL_GPIO   (WeatherClick_ss0_m__0__HSIOM_GPIO)
    #define WeatherClick_SS0_M_HSIOM_SEL_SPI    (WeatherClick_ss0_m__0__HSIOM_SPI)
#endif /* (WeatherClick_SPI_MASTER_SS0_PIN) */

#if (WeatherClick_SPI_MASTER_SS1_PIN)
    #define WeatherClick_SS1_M_HSIOM_REG    (*(reg32 *) WeatherClick_ss1_m__0__HSIOM)
    #define WeatherClick_SS1_M_HSIOM_PTR    ( (reg32 *) WeatherClick_ss1_m__0__HSIOM)
    
    #define WeatherClick_SS1_M_HSIOM_MASK       (WeatherClick_ss1_m__0__HSIOM_MASK)
    #define WeatherClick_SS1_M_HSIOM_POS        (WeatherClick_ss1_m__0__HSIOM_SHIFT)
    #define WeatherClick_SS1_M_HSIOM_SEL_GPIO   (WeatherClick_ss1_m__0__HSIOM_GPIO)
    #define WeatherClick_SS1_M_HSIOM_SEL_SPI    (WeatherClick_ss1_m__0__HSIOM_SPI)
#endif /* (WeatherClick_SPI_MASTER_SS1_PIN) */

#if (WeatherClick_SPI_MASTER_SS2_PIN)
    #define WeatherClick_SS2_M_HSIOM_REG    (*(reg32 *) WeatherClick_ss2_m__0__HSIOM)
    #define WeatherClick_SS2_M_HSIOM_PTR    ( (reg32 *) WeatherClick_ss2_m__0__HSIOM)
    
    #define WeatherClick_SS2_M_HSIOM_MASK       (WeatherClick_ss2_m__0__HSIOM_MASK)
    #define WeatherClick_SS2_M_HSIOM_POS        (WeatherClick_ss2_m__0__HSIOM_SHIFT)
    #define WeatherClick_SS2_M_HSIOM_SEL_GPIO   (WeatherClick_ss2_m__0__HSIOM_GPIO)
    #define WeatherClick_SS2_M_HSIOM_SEL_SPI    (WeatherClick_ss2_m__0__HSIOM_SPI)
#endif /* (WeatherClick_SPI_MASTER_SS2_PIN) */

#if (WeatherClick_SPI_MASTER_SS3_PIN)
    #define WeatherClick_SS3_M_HSIOM_REG    (*(reg32 *) WeatherClick_ss3_m__0__HSIOM)
    #define WeatherClick_SS3_M_HSIOM_PTR    ( (reg32 *) WeatherClick_ss3_m__0__HSIOM)
    
    #define WeatherClick_SS3_M_HSIOM_MASK      (WeatherClick_ss3_m__0__HSIOM_MASK)
    #define WeatherClick_SS3_M_HSIOM_POS       (WeatherClick_ss3_m__0__HSIOM_SHIFT)
    #define WeatherClick_SS3_M_HSIOM_SEL_GPIO  (WeatherClick_ss3_m__0__HSIOM_GPIO)
    #define WeatherClick_SS3_M_HSIOM_SEL_SPI   (WeatherClick_ss3_m__0__HSIOM_SPI)
#endif /* (WeatherClick_SPI_MASTER_SS3_PIN) */

#if (WeatherClick_UART_RX_PIN)
    #define WeatherClick_RX_HSIOM_REG   (*(reg32 *) WeatherClick_rx__0__HSIOM)
    #define WeatherClick_RX_HSIOM_PTR   ( (reg32 *) WeatherClick_rx__0__HSIOM)
    
    #define WeatherClick_RX_HSIOM_MASK      (WeatherClick_rx__0__HSIOM_MASK)
    #define WeatherClick_RX_HSIOM_POS       (WeatherClick_rx__0__HSIOM_SHIFT)
    #define WeatherClick_RX_HSIOM_SEL_GPIO  (WeatherClick_rx__0__HSIOM_GPIO)
    #define WeatherClick_RX_HSIOM_SEL_UART  (WeatherClick_rx__0__HSIOM_UART)
#endif /* (WeatherClick_UART_RX_PIN) */

#if (WeatherClick_UART_RX_WAKE_PIN)
    #define WeatherClick_RX_WAKE_HSIOM_REG   (*(reg32 *) WeatherClick_rx_wake__0__HSIOM)
    #define WeatherClick_RX_WAKE_HSIOM_PTR   ( (reg32 *) WeatherClick_rx_wake__0__HSIOM)
    
    #define WeatherClick_RX_WAKE_HSIOM_MASK      (WeatherClick_rx_wake__0__HSIOM_MASK)
    #define WeatherClick_RX_WAKE_HSIOM_POS       (WeatherClick_rx_wake__0__HSIOM_SHIFT)
    #define WeatherClick_RX_WAKE_HSIOM_SEL_GPIO  (WeatherClick_rx_wake__0__HSIOM_GPIO)
    #define WeatherClick_RX_WAKE_HSIOM_SEL_UART  (WeatherClick_rx_wake__0__HSIOM_UART)
#endif /* (WeatherClick_UART_WAKE_RX_PIN) */

#if (WeatherClick_UART_CTS_PIN)
    #define WeatherClick_CTS_HSIOM_REG   (*(reg32 *) WeatherClick_cts__0__HSIOM)
    #define WeatherClick_CTS_HSIOM_PTR   ( (reg32 *) WeatherClick_cts__0__HSIOM)
    
    #define WeatherClick_CTS_HSIOM_MASK      (WeatherClick_cts__0__HSIOM_MASK)
    #define WeatherClick_CTS_HSIOM_POS       (WeatherClick_cts__0__HSIOM_SHIFT)
    #define WeatherClick_CTS_HSIOM_SEL_GPIO  (WeatherClick_cts__0__HSIOM_GPIO)
    #define WeatherClick_CTS_HSIOM_SEL_UART  (WeatherClick_cts__0__HSIOM_UART)
#endif /* (WeatherClick_UART_CTS_PIN) */

#if (WeatherClick_UART_TX_PIN)
    #define WeatherClick_TX_HSIOM_REG   (*(reg32 *) WeatherClick_tx__0__HSIOM)
    #define WeatherClick_TX_HSIOM_PTR   ( (reg32 *) WeatherClick_tx__0__HSIOM)
    
    #define WeatherClick_TX_HSIOM_MASK      (WeatherClick_tx__0__HSIOM_MASK)
    #define WeatherClick_TX_HSIOM_POS       (WeatherClick_tx__0__HSIOM_SHIFT)
    #define WeatherClick_TX_HSIOM_SEL_GPIO  (WeatherClick_tx__0__HSIOM_GPIO)
    #define WeatherClick_TX_HSIOM_SEL_UART  (WeatherClick_tx__0__HSIOM_UART)
#endif /* (WeatherClick_UART_TX_PIN) */

#if (WeatherClick_UART_RX_TX_PIN)
    #define WeatherClick_RX_TX_HSIOM_REG   (*(reg32 *) WeatherClick_rx_tx__0__HSIOM)
    #define WeatherClick_RX_TX_HSIOM_PTR   ( (reg32 *) WeatherClick_rx_tx__0__HSIOM)
    
    #define WeatherClick_RX_TX_HSIOM_MASK      (WeatherClick_rx_tx__0__HSIOM_MASK)
    #define WeatherClick_RX_TX_HSIOM_POS       (WeatherClick_rx_tx__0__HSIOM_SHIFT)
    #define WeatherClick_RX_TX_HSIOM_SEL_GPIO  (WeatherClick_rx_tx__0__HSIOM_GPIO)
    #define WeatherClick_RX_TX_HSIOM_SEL_UART  (WeatherClick_rx_tx__0__HSIOM_UART)
#endif /* (WeatherClick_UART_RX_TX_PIN) */

#if (WeatherClick_UART_RTS_PIN)
    #define WeatherClick_RTS_HSIOM_REG      (*(reg32 *) WeatherClick_rts__0__HSIOM)
    #define WeatherClick_RTS_HSIOM_PTR      ( (reg32 *) WeatherClick_rts__0__HSIOM)
    
    #define WeatherClick_RTS_HSIOM_MASK     (WeatherClick_rts__0__HSIOM_MASK)
    #define WeatherClick_RTS_HSIOM_POS      (WeatherClick_rts__0__HSIOM_SHIFT)    
    #define WeatherClick_RTS_HSIOM_SEL_GPIO (WeatherClick_rts__0__HSIOM_GPIO)
    #define WeatherClick_RTS_HSIOM_SEL_UART (WeatherClick_rts__0__HSIOM_UART)    
#endif /* (WeatherClick_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define WeatherClick_HSIOM_DEF_SEL      (0x00u)
#define WeatherClick_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for WeatherClick_CY_SCBIP_V0 
* and WeatherClick_CY_SCBIP_V1. It is not recommended to use them for 
* WeatherClick_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define WeatherClick_HSIOM_UART_SEL     (0x09u)
#define WeatherClick_HSIOM_I2C_SEL      (0x0Eu)
#define WeatherClick_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define WeatherClick_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define WeatherClick_RX_SCL_MOSI_PIN_INDEX       (0u)
#define WeatherClick_TX_SDA_MISO_PIN_INDEX       (1u)
#define WeatherClick_CTS_SCLK_PIN_INDEX       (2u)
#define WeatherClick_RTS_SS0_PIN_INDEX       (3u)
#define WeatherClick_SS1_PIN_INDEX                  (4u)
#define WeatherClick_SS2_PIN_INDEX                  (5u)
#define WeatherClick_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define WeatherClick_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << WeatherClick_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define WeatherClick_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << WeatherClick_RX_SCL_MOSI_PIN_INDEX)
#define WeatherClick_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << WeatherClick_TX_SDA_MISO_PIN_INDEX)
#define WeatherClick_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << WeatherClick_CTS_SCLK_PIN_INDEX)
#define WeatherClick_RTS_SS0_PIN_MASK     ((uint32) 0x01u << WeatherClick_RTS_SS0_PIN_INDEX)
#define WeatherClick_SS1_PIN_MASK                ((uint32) 0x01u << WeatherClick_SS1_PIN_INDEX)
#define WeatherClick_SS2_PIN_MASK                ((uint32) 0x01u << WeatherClick_SS2_PIN_INDEX)
#define WeatherClick_SS3_PIN_MASK                ((uint32) 0x01u << WeatherClick_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define WeatherClick_INTCFG_TYPE_MASK           (0x03u)
#define WeatherClick_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define WeatherClick_PIN_DM_ALG_HIZ  (0u)
#define WeatherClick_PIN_DM_DIG_HIZ  (1u)
#define WeatherClick_PIN_DM_OD_LO    (4u)
#define WeatherClick_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define WeatherClick_DM_MASK    (0x7u)
#define WeatherClick_DM_SIZE    (3u)
#define WeatherClick_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) WeatherClick_DM_MASK << (WeatherClick_DM_SIZE * (pos)))) >> \
                                                              (WeatherClick_DM_SIZE * (pos)) )

#if (WeatherClick_TX_SDA_MISO_PIN)
    #define WeatherClick_CHECK_TX_SDA_MISO_PIN_USED \
                (WeatherClick_PIN_DM_ALG_HIZ != \
                    WeatherClick_GET_P4_PIN_DM(WeatherClick_uart_tx_i2c_sda_spi_miso_PC, \
                                                   WeatherClick_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (WeatherClick_TX_SDA_MISO_PIN) */

#if (WeatherClick_RTS_SS0_PIN)
    #define WeatherClick_CHECK_RTS_SS0_PIN_USED \
                (WeatherClick_PIN_DM_ALG_HIZ != \
                    WeatherClick_GET_P4_PIN_DM(WeatherClick_uart_rts_spi_ss0_PC, \
                                                   WeatherClick_uart_rts_spi_ss0_SHIFT))
#endif /* (WeatherClick_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define WeatherClick_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define WeatherClick_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define WeatherClick_SET_HSIOM_SEL(reg, mask, pos, sel) WeatherClick_SET_REGISTER_BITS(reg, mask, pos, sel)
#define WeatherClick_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        WeatherClick_SET_REGISTER_BITS(reg, mask, pos, intType)
#define WeatherClick_SET_INP_DIS(reg, mask, val) WeatherClick_SET_REGISTER_BIT(reg, mask, val)

/* WeatherClick_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  WeatherClick_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (WeatherClick_CY_SCBIP_V0)
#if (WeatherClick_I2C_PINS)
    #define WeatherClick_SET_I2C_SCL_DR(val) WeatherClick_scl_Write(val)

    #define WeatherClick_SET_I2C_SCL_HSIOM_SEL(sel) \
                          WeatherClick_SET_HSIOM_SEL(WeatherClick_SCL_HSIOM_REG,  \
                                                         WeatherClick_SCL_HSIOM_MASK, \
                                                         WeatherClick_SCL_HSIOM_POS,  \
                                                         (sel))
    #define WeatherClick_WAIT_SCL_SET_HIGH  (0u == WeatherClick_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (WeatherClick_RX_WAKE_SCL_MOSI_PIN)
    #define WeatherClick_SET_I2C_SCL_DR(val) \
                            WeatherClick_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define WeatherClick_SET_I2C_SCL_HSIOM_SEL(sel) \
                    WeatherClick_SET_HSIOM_SEL(WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define WeatherClick_WAIT_SCL_SET_HIGH  (0u == WeatherClick_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (WeatherClick_RX_SCL_MOSI_PIN)
    #define WeatherClick_SET_I2C_SCL_DR(val) \
                            WeatherClick_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define WeatherClick_SET_I2C_SCL_HSIOM_SEL(sel) \
                            WeatherClick_SET_HSIOM_SEL(WeatherClick_RX_SCL_MOSI_HSIOM_REG,  \
                                                           WeatherClick_RX_SCL_MOSI_HSIOM_MASK, \
                                                           WeatherClick_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define WeatherClick_WAIT_SCL_SET_HIGH  (0u == WeatherClick_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define WeatherClick_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define WeatherClick_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define WeatherClick_WAIT_SCL_SET_HIGH  (0u)
#endif /* (WeatherClick_I2C_PINS) */

/* SCB I2C: sda signal */
#if (WeatherClick_I2C_PINS)
    #define WeatherClick_WAIT_SDA_SET_HIGH  (0u == WeatherClick_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (WeatherClick_TX_SDA_MISO_PIN)
    #define WeatherClick_WAIT_SDA_SET_HIGH  (0u == WeatherClick_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define WeatherClick_WAIT_SDA_SET_HIGH  (0u)
#endif /* (WeatherClick_MOSI_SCL_RX_PIN) */
#endif /* (WeatherClick_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (WeatherClick_RX_SCL_MOSI_PIN)
    #define WeatherClick_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (WeatherClick_RX_WAKE_SCL_MOSI_PIN)
    #define WeatherClick_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) WeatherClick_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(WeatherClick_UART_RX_WAKE_PIN)
    #define WeatherClick_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) WeatherClick_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (WeatherClick_RX_SCL_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define WeatherClick_REMOVE_MOSI_SCL_RX_WAKE_PIN    WeatherClick_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define WeatherClick_REMOVE_MOSI_SCL_RX_PIN         WeatherClick_REMOVE_RX_SCL_MOSI_PIN
#define WeatherClick_REMOVE_MISO_SDA_TX_PIN         WeatherClick_REMOVE_TX_SDA_MISO_PIN
#ifndef WeatherClick_REMOVE_SCLK_PIN
#define WeatherClick_REMOVE_SCLK_PIN                WeatherClick_REMOVE_CTS_SCLK_PIN
#endif /* WeatherClick_REMOVE_SCLK_PIN */
#ifndef WeatherClick_REMOVE_SS0_PIN
#define WeatherClick_REMOVE_SS0_PIN                 WeatherClick_REMOVE_RTS_SS0_PIN
#endif /* WeatherClick_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define WeatherClick_MOSI_SCL_RX_WAKE_PIN   WeatherClick_RX_WAKE_SCL_MOSI_PIN
#define WeatherClick_MOSI_SCL_RX_PIN        WeatherClick_RX_SCL_MOSI_PIN
#define WeatherClick_MISO_SDA_TX_PIN        WeatherClick_TX_SDA_MISO_PIN
#ifndef WeatherClick_SCLK_PIN
#define WeatherClick_SCLK_PIN               WeatherClick_CTS_SCLK_PIN
#endif /* WeatherClick_SCLK_PIN */
#ifndef WeatherClick_SS0_PIN
#define WeatherClick_SS0_PIN                WeatherClick_RTS_SS0_PIN
#endif /* WeatherClick_SS0_PIN */

#if (WeatherClick_MOSI_SCL_RX_WAKE_PIN)
    #define WeatherClick_MOSI_SCL_RX_WAKE_HSIOM_REG     WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define WeatherClick_MOSI_SCL_RX_WAKE_HSIOM_PTR     WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define WeatherClick_MOSI_SCL_RX_WAKE_HSIOM_MASK    WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define WeatherClick_MOSI_SCL_RX_WAKE_HSIOM_POS     WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define WeatherClick_MOSI_SCL_RX_WAKE_INTCFG_REG    WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define WeatherClick_MOSI_SCL_RX_WAKE_INTCFG_PTR    WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define WeatherClick_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define WeatherClick_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  WeatherClick_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (WeatherClick_RX_WAKE_SCL_MOSI_PIN) */

#if (WeatherClick_MOSI_SCL_RX_PIN)
    #define WeatherClick_MOSI_SCL_RX_HSIOM_REG      WeatherClick_RX_SCL_MOSI_HSIOM_REG
    #define WeatherClick_MOSI_SCL_RX_HSIOM_PTR      WeatherClick_RX_SCL_MOSI_HSIOM_PTR
    #define WeatherClick_MOSI_SCL_RX_HSIOM_MASK     WeatherClick_RX_SCL_MOSI_HSIOM_MASK
    #define WeatherClick_MOSI_SCL_RX_HSIOM_POS      WeatherClick_RX_SCL_MOSI_HSIOM_POS
#endif /* (WeatherClick_MOSI_SCL_RX_PIN) */

#if (WeatherClick_MISO_SDA_TX_PIN)
    #define WeatherClick_MISO_SDA_TX_HSIOM_REG      WeatherClick_TX_SDA_MISO_HSIOM_REG
    #define WeatherClick_MISO_SDA_TX_HSIOM_PTR      WeatherClick_TX_SDA_MISO_HSIOM_REG
    #define WeatherClick_MISO_SDA_TX_HSIOM_MASK     WeatherClick_TX_SDA_MISO_HSIOM_REG
    #define WeatherClick_MISO_SDA_TX_HSIOM_POS      WeatherClick_TX_SDA_MISO_HSIOM_REG
#endif /* (WeatherClick_MISO_SDA_TX_PIN_PIN) */

#if (WeatherClick_SCLK_PIN)
    #ifndef WeatherClick_SCLK_HSIOM_REG
    #define WeatherClick_SCLK_HSIOM_REG     WeatherClick_CTS_SCLK_HSIOM_REG
    #define WeatherClick_SCLK_HSIOM_PTR     WeatherClick_CTS_SCLK_HSIOM_PTR
    #define WeatherClick_SCLK_HSIOM_MASK    WeatherClick_CTS_SCLK_HSIOM_MASK
    #define WeatherClick_SCLK_HSIOM_POS     WeatherClick_CTS_SCLK_HSIOM_POS
    #endif /* WeatherClick_SCLK_HSIOM_REG */
#endif /* (WeatherClick_SCLK_PIN) */

#if (WeatherClick_SS0_PIN)
    #ifndef WeatherClick_SS0_HSIOM_REG
    #define WeatherClick_SS0_HSIOM_REG      WeatherClick_RTS_SS0_HSIOM_REG
    #define WeatherClick_SS0_HSIOM_PTR      WeatherClick_RTS_SS0_HSIOM_PTR
    #define WeatherClick_SS0_HSIOM_MASK     WeatherClick_RTS_SS0_HSIOM_MASK
    #define WeatherClick_SS0_HSIOM_POS      WeatherClick_RTS_SS0_HSIOM_POS
    #endif /* WeatherClick_SS0_HSIOM_REG */
#endif /* (WeatherClick_SS0_PIN) */

#define WeatherClick_MOSI_SCL_RX_WAKE_PIN_INDEX WeatherClick_RX_WAKE_SCL_MOSI_PIN_INDEX
#define WeatherClick_MOSI_SCL_RX_PIN_INDEX      WeatherClick_RX_SCL_MOSI_PIN_INDEX
#define WeatherClick_MISO_SDA_TX_PIN_INDEX      WeatherClick_TX_SDA_MISO_PIN_INDEX
#ifndef WeatherClick_SCLK_PIN_INDEX
#define WeatherClick_SCLK_PIN_INDEX             WeatherClick_CTS_SCLK_PIN_INDEX
#endif /* WeatherClick_SCLK_PIN_INDEX */
#ifndef WeatherClick_SS0_PIN_INDEX
#define WeatherClick_SS0_PIN_INDEX              WeatherClick_RTS_SS0_PIN_INDEX
#endif /* WeatherClick_SS0_PIN_INDEX */

#define WeatherClick_MOSI_SCL_RX_WAKE_PIN_MASK WeatherClick_RX_WAKE_SCL_MOSI_PIN_MASK
#define WeatherClick_MOSI_SCL_RX_PIN_MASK      WeatherClick_RX_SCL_MOSI_PIN_MASK
#define WeatherClick_MISO_SDA_TX_PIN_MASK      WeatherClick_TX_SDA_MISO_PIN_MASK
#ifndef WeatherClick_SCLK_PIN_MASK
#define WeatherClick_SCLK_PIN_MASK             WeatherClick_CTS_SCLK_PIN_MASK
#endif /* WeatherClick_SCLK_PIN_MASK */
#ifndef WeatherClick_SS0_PIN_MASK
#define WeatherClick_SS0_PIN_MASK              WeatherClick_RTS_SS0_PIN_MASK
#endif /* WeatherClick_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_WeatherClick_H) */


/* [] END OF FILE */
