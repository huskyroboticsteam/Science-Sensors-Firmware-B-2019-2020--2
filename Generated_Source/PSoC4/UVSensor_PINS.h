/***************************************************************************//**
* \file UVSensor_PINS.h
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

#if !defined(CY_SCB_PINS_UVSensor_H)
#define CY_SCB_PINS_UVSensor_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define UVSensor_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define UVSensor_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define UVSensor_REMOVE_TX_SDA_MISO_PIN      (1u)
#define UVSensor_REMOVE_CTS_SCLK_PIN      (1u)
#define UVSensor_REMOVE_RTS_SS0_PIN      (1u)
#define UVSensor_REMOVE_SS1_PIN                 (1u)
#define UVSensor_REMOVE_SS2_PIN                 (1u)
#define UVSensor_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define UVSensor_REMOVE_I2C_PINS                (0u)
#define UVSensor_REMOVE_SPI_MASTER_PINS         (1u)
#define UVSensor_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define UVSensor_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define UVSensor_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define UVSensor_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define UVSensor_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define UVSensor_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define UVSensor_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define UVSensor_REMOVE_SPI_SLAVE_PINS          (1u)
#define UVSensor_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define UVSensor_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define UVSensor_REMOVE_UART_TX_PIN             (1u)
#define UVSensor_REMOVE_UART_RX_TX_PIN          (1u)
#define UVSensor_REMOVE_UART_RX_PIN             (1u)
#define UVSensor_REMOVE_UART_RX_WAKE_PIN        (1u)
#define UVSensor_REMOVE_UART_RTS_PIN            (1u)
#define UVSensor_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define UVSensor_RX_WAKE_SCL_MOSI_PIN (0u == UVSensor_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define UVSensor_RX_SCL_MOSI_PIN     (0u == UVSensor_REMOVE_RX_SCL_MOSI_PIN)
#define UVSensor_TX_SDA_MISO_PIN     (0u == UVSensor_REMOVE_TX_SDA_MISO_PIN)
#define UVSensor_CTS_SCLK_PIN     (0u == UVSensor_REMOVE_CTS_SCLK_PIN)
#define UVSensor_RTS_SS0_PIN     (0u == UVSensor_REMOVE_RTS_SS0_PIN)
#define UVSensor_SS1_PIN                (0u == UVSensor_REMOVE_SS1_PIN)
#define UVSensor_SS2_PIN                (0u == UVSensor_REMOVE_SS2_PIN)
#define UVSensor_SS3_PIN                (0u == UVSensor_REMOVE_SS3_PIN)

/* Mode defined pins */
#define UVSensor_I2C_PINS               (0u == UVSensor_REMOVE_I2C_PINS)
#define UVSensor_SPI_MASTER_PINS        (0u == UVSensor_REMOVE_SPI_MASTER_PINS)
#define UVSensor_SPI_MASTER_SCLK_PIN    (0u == UVSensor_REMOVE_SPI_MASTER_SCLK_PIN)
#define UVSensor_SPI_MASTER_MOSI_PIN    (0u == UVSensor_REMOVE_SPI_MASTER_MOSI_PIN)
#define UVSensor_SPI_MASTER_MISO_PIN    (0u == UVSensor_REMOVE_SPI_MASTER_MISO_PIN)
#define UVSensor_SPI_MASTER_SS0_PIN     (0u == UVSensor_REMOVE_SPI_MASTER_SS0_PIN)
#define UVSensor_SPI_MASTER_SS1_PIN     (0u == UVSensor_REMOVE_SPI_MASTER_SS1_PIN)
#define UVSensor_SPI_MASTER_SS2_PIN     (0u == UVSensor_REMOVE_SPI_MASTER_SS2_PIN)
#define UVSensor_SPI_MASTER_SS3_PIN     (0u == UVSensor_REMOVE_SPI_MASTER_SS3_PIN)
#define UVSensor_SPI_SLAVE_PINS         (0u == UVSensor_REMOVE_SPI_SLAVE_PINS)
#define UVSensor_SPI_SLAVE_MOSI_PIN     (0u == UVSensor_REMOVE_SPI_SLAVE_MOSI_PIN)
#define UVSensor_SPI_SLAVE_MISO_PIN     (0u == UVSensor_REMOVE_SPI_SLAVE_MISO_PIN)
#define UVSensor_UART_TX_PIN            (0u == UVSensor_REMOVE_UART_TX_PIN)
#define UVSensor_UART_RX_TX_PIN         (0u == UVSensor_REMOVE_UART_RX_TX_PIN)
#define UVSensor_UART_RX_PIN            (0u == UVSensor_REMOVE_UART_RX_PIN)
#define UVSensor_UART_RX_WAKE_PIN       (0u == UVSensor_REMOVE_UART_RX_WAKE_PIN)
#define UVSensor_UART_RTS_PIN           (0u == UVSensor_REMOVE_UART_RTS_PIN)
#define UVSensor_UART_CTS_PIN           (0u == UVSensor_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (UVSensor_RX_WAKE_SCL_MOSI_PIN)
    #include "UVSensor_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (UVSensor_RX_SCL_MOSI) */

#if (UVSensor_RX_SCL_MOSI_PIN)
    #include "UVSensor_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (UVSensor_RX_SCL_MOSI) */

#if (UVSensor_TX_SDA_MISO_PIN)
    #include "UVSensor_uart_tx_i2c_sda_spi_miso.h"
#endif /* (UVSensor_TX_SDA_MISO) */

#if (UVSensor_CTS_SCLK_PIN)
    #include "UVSensor_uart_cts_spi_sclk.h"
#endif /* (UVSensor_CTS_SCLK) */

#if (UVSensor_RTS_SS0_PIN)
    #include "UVSensor_uart_rts_spi_ss0.h"
#endif /* (UVSensor_RTS_SS0_PIN) */

#if (UVSensor_SS1_PIN)
    #include "UVSensor_spi_ss1.h"
#endif /* (UVSensor_SS1_PIN) */

#if (UVSensor_SS2_PIN)
    #include "UVSensor_spi_ss2.h"
#endif /* (UVSensor_SS2_PIN) */

#if (UVSensor_SS3_PIN)
    #include "UVSensor_spi_ss3.h"
#endif /* (UVSensor_SS3_PIN) */

#if (UVSensor_I2C_PINS)
    #include "UVSensor_scl.h"
    #include "UVSensor_sda.h"
#endif /* (UVSensor_I2C_PINS) */

#if (UVSensor_SPI_MASTER_PINS)
#if (UVSensor_SPI_MASTER_SCLK_PIN)
    #include "UVSensor_sclk_m.h"
#endif /* (UVSensor_SPI_MASTER_SCLK_PIN) */

#if (UVSensor_SPI_MASTER_MOSI_PIN)
    #include "UVSensor_mosi_m.h"
#endif /* (UVSensor_SPI_MASTER_MOSI_PIN) */

#if (UVSensor_SPI_MASTER_MISO_PIN)
    #include "UVSensor_miso_m.h"
#endif /*(UVSensor_SPI_MASTER_MISO_PIN) */
#endif /* (UVSensor_SPI_MASTER_PINS) */

#if (UVSensor_SPI_SLAVE_PINS)
    #include "UVSensor_sclk_s.h"
    #include "UVSensor_ss_s.h"

#if (UVSensor_SPI_SLAVE_MOSI_PIN)
    #include "UVSensor_mosi_s.h"
#endif /* (UVSensor_SPI_SLAVE_MOSI_PIN) */

#if (UVSensor_SPI_SLAVE_MISO_PIN)
    #include "UVSensor_miso_s.h"
#endif /*(UVSensor_SPI_SLAVE_MISO_PIN) */
#endif /* (UVSensor_SPI_SLAVE_PINS) */

#if (UVSensor_SPI_MASTER_SS0_PIN)
    #include "UVSensor_ss0_m.h"
#endif /* (UVSensor_SPI_MASTER_SS0_PIN) */

#if (UVSensor_SPI_MASTER_SS1_PIN)
    #include "UVSensor_ss1_m.h"
#endif /* (UVSensor_SPI_MASTER_SS1_PIN) */

#if (UVSensor_SPI_MASTER_SS2_PIN)
    #include "UVSensor_ss2_m.h"
#endif /* (UVSensor_SPI_MASTER_SS2_PIN) */

#if (UVSensor_SPI_MASTER_SS3_PIN)
    #include "UVSensor_ss3_m.h"
#endif /* (UVSensor_SPI_MASTER_SS3_PIN) */

#if (UVSensor_UART_TX_PIN)
    #include "UVSensor_tx.h"
#endif /* (UVSensor_UART_TX_PIN) */

#if (UVSensor_UART_RX_TX_PIN)
    #include "UVSensor_rx_tx.h"
#endif /* (UVSensor_UART_RX_TX_PIN) */

#if (UVSensor_UART_RX_PIN)
    #include "UVSensor_rx.h"
#endif /* (UVSensor_UART_RX_PIN) */

#if (UVSensor_UART_RX_WAKE_PIN)
    #include "UVSensor_rx_wake.h"
#endif /* (UVSensor_UART_RX_WAKE_PIN) */

#if (UVSensor_UART_RTS_PIN)
    #include "UVSensor_rts.h"
#endif /* (UVSensor_UART_RTS_PIN) */

#if (UVSensor_UART_CTS_PIN)
    #include "UVSensor_cts.h"
#endif /* (UVSensor_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (UVSensor_RX_SCL_MOSI_PIN)
    #define UVSensor_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) UVSensor_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define UVSensor_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) UVSensor_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    
    #define UVSensor_RX_SCL_MOSI_HSIOM_MASK      (UVSensor_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define UVSensor_RX_SCL_MOSI_HSIOM_POS       (UVSensor_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define UVSensor_RX_SCL_MOSI_HSIOM_SEL_GPIO  (UVSensor_uart_rx_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define UVSensor_RX_SCL_MOSI_HSIOM_SEL_I2C   (UVSensor_uart_rx_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define UVSensor_RX_SCL_MOSI_HSIOM_SEL_SPI   (UVSensor_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define UVSensor_RX_SCL_MOSI_HSIOM_SEL_UART  (UVSensor_uart_rx_i2c_scl_spi_mosi__0__HSIOM_UART)
    
#elif (UVSensor_RX_WAKE_SCL_MOSI_PIN)
    #define UVSensor_RX_WAKE_SCL_MOSI_HSIOM_REG   (*(reg32 *) UVSensor_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define UVSensor_RX_WAKE_SCL_MOSI_HSIOM_PTR   ( (reg32 *) UVSensor_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    
    #define UVSensor_RX_WAKE_SCL_MOSI_HSIOM_MASK      (UVSensor_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define UVSensor_RX_WAKE_SCL_MOSI_HSIOM_POS       (UVSensor_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
    #define UVSensor_RX_WAKE_SCL_MOSI_HSIOM_SEL_GPIO  (UVSensor_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_GPIO)
    #define UVSensor_RX_WAKE_SCL_MOSI_HSIOM_SEL_I2C   (UVSensor_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_I2C)
    #define UVSensor_RX_WAKE_SCL_MOSI_HSIOM_SEL_SPI   (UVSensor_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SPI)
    #define UVSensor_RX_WAKE_SCL_MOSI_HSIOM_SEL_UART  (UVSensor_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_UART)    
   
    #define UVSensor_RX_WAKE_SCL_MOSI_INTCFG_REG (*(reg32 *) UVSensor_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define UVSensor_RX_WAKE_SCL_MOSI_INTCFG_PTR ( (reg32 *) UVSensor_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define UVSensor_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (UVSensor_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define UVSensor_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK ((uint32) UVSensor_INTCFG_TYPE_MASK << \
                                                                           UVSensor_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins UVSensor_RX_SCL_MOSI_PIN or UVSensor_RX_WAKE_SCL_MOSI_PIN present.*/
#endif /* (UVSensor_RX_SCL_MOSI_PIN) */

#if (UVSensor_TX_SDA_MISO_PIN)
    #define UVSensor_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) UVSensor_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define UVSensor_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) UVSensor_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    
    #define UVSensor_TX_SDA_MISO_HSIOM_MASK      (UVSensor_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define UVSensor_TX_SDA_MISO_HSIOM_POS       (UVSensor_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
    #define UVSensor_TX_SDA_MISO_HSIOM_SEL_GPIO  (UVSensor_uart_tx_i2c_sda_spi_miso__0__HSIOM_GPIO)
    #define UVSensor_TX_SDA_MISO_HSIOM_SEL_I2C   (UVSensor_uart_tx_i2c_sda_spi_miso__0__HSIOM_I2C)
    #define UVSensor_TX_SDA_MISO_HSIOM_SEL_SPI   (UVSensor_uart_tx_i2c_sda_spi_miso__0__HSIOM_SPI)
    #define UVSensor_TX_SDA_MISO_HSIOM_SEL_UART  (UVSensor_uart_tx_i2c_sda_spi_miso__0__HSIOM_UART)
#endif /* (UVSensor_TX_SDA_MISO_PIN) */

#if (UVSensor_CTS_SCLK_PIN)
    #define UVSensor_CTS_SCLK_HSIOM_REG   (*(reg32 *) UVSensor_uart_cts_spi_sclk__0__HSIOM)
    #define UVSensor_CTS_SCLK_HSIOM_PTR   ( (reg32 *) UVSensor_uart_cts_spi_sclk__0__HSIOM)
    
    #define UVSensor_CTS_SCLK_HSIOM_MASK      (UVSensor_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define UVSensor_CTS_SCLK_HSIOM_POS       (UVSensor_uart_cts_spi_sclk__0__HSIOM_SHIFT)
    #define UVSensor_CTS_SCLK_HSIOM_SEL_GPIO  (UVSensor_uart_cts_spi_sclk__0__HSIOM_GPIO)
    #define UVSensor_CTS_SCLK_HSIOM_SEL_I2C   (UVSensor_uart_cts_spi_sclk__0__HSIOM_I2C)
    #define UVSensor_CTS_SCLK_HSIOM_SEL_SPI   (UVSensor_uart_cts_spi_sclk__0__HSIOM_SPI)
    #define UVSensor_CTS_SCLK_HSIOM_SEL_UART  (UVSensor_uart_cts_spi_sclk__0__HSIOM_UART)
#endif /* (UVSensor_CTS_SCLK_PIN) */

#if (UVSensor_RTS_SS0_PIN)
    #define UVSensor_RTS_SS0_HSIOM_REG   (*(reg32 *) UVSensor_uart_rts_spi_ss0__0__HSIOM)
    #define UVSensor_RTS_SS0_HSIOM_PTR   ( (reg32 *) UVSensor_uart_rts_spi_ss0__0__HSIOM)
    
    #define UVSensor_RTS_SS0_HSIOM_MASK      (UVSensor_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define UVSensor_RTS_SS0_HSIOM_POS       (UVSensor_uart_rts_spi_ss0__0__HSIOM_SHIFT)
    #define UVSensor_RTS_SS0_HSIOM_SEL_GPIO  (UVSensor_uart_rts_spi_ss0__0__HSIOM_GPIO)
    #define UVSensor_RTS_SS0_HSIOM_SEL_I2C   (UVSensor_uart_rts_spi_ss0__0__HSIOM_I2C)
    #define UVSensor_RTS_SS0_HSIOM_SEL_SPI   (UVSensor_uart_rts_spi_ss0__0__HSIOM_SPI)
#if !(UVSensor_CY_SCBIP_V0 || UVSensor_CY_SCBIP_V1)
    #define UVSensor_RTS_SS0_HSIOM_SEL_UART  (UVSensor_uart_rts_spi_ss0__0__HSIOM_UART)
#endif /* !(UVSensor_CY_SCBIP_V0 || UVSensor_CY_SCBIP_V1) */
#endif /* (UVSensor_RTS_SS0_PIN) */

#if (UVSensor_SS1_PIN)
    #define UVSensor_SS1_HSIOM_REG  (*(reg32 *) UVSensor_spi_ss1__0__HSIOM)
    #define UVSensor_SS1_HSIOM_PTR  ( (reg32 *) UVSensor_spi_ss1__0__HSIOM)
    
    #define UVSensor_SS1_HSIOM_MASK     (UVSensor_spi_ss1__0__HSIOM_MASK)
    #define UVSensor_SS1_HSIOM_POS      (UVSensor_spi_ss1__0__HSIOM_SHIFT)
    #define UVSensor_SS1_HSIOM_SEL_GPIO (UVSensor_spi_ss1__0__HSIOM_GPIO)
    #define UVSensor_SS1_HSIOM_SEL_I2C  (UVSensor_spi_ss1__0__HSIOM_I2C)
    #define UVSensor_SS1_HSIOM_SEL_SPI  (UVSensor_spi_ss1__0__HSIOM_SPI)
#endif /* (UVSensor_SS1_PIN) */

#if (UVSensor_SS2_PIN)
    #define UVSensor_SS2_HSIOM_REG     (*(reg32 *) UVSensor_spi_ss2__0__HSIOM)
    #define UVSensor_SS2_HSIOM_PTR     ( (reg32 *) UVSensor_spi_ss2__0__HSIOM)
    
    #define UVSensor_SS2_HSIOM_MASK     (UVSensor_spi_ss2__0__HSIOM_MASK)
    #define UVSensor_SS2_HSIOM_POS      (UVSensor_spi_ss2__0__HSIOM_SHIFT)
    #define UVSensor_SS2_HSIOM_SEL_GPIO (UVSensor_spi_ss2__0__HSIOM_GPIO)
    #define UVSensor_SS2_HSIOM_SEL_I2C  (UVSensor_spi_ss2__0__HSIOM_I2C)
    #define UVSensor_SS2_HSIOM_SEL_SPI  (UVSensor_spi_ss2__0__HSIOM_SPI)
#endif /* (UVSensor_SS2_PIN) */

#if (UVSensor_SS3_PIN)
    #define UVSensor_SS3_HSIOM_REG     (*(reg32 *) UVSensor_spi_ss3__0__HSIOM)
    #define UVSensor_SS3_HSIOM_PTR     ( (reg32 *) UVSensor_spi_ss3__0__HSIOM)
    
    #define UVSensor_SS3_HSIOM_MASK     (UVSensor_spi_ss3__0__HSIOM_MASK)
    #define UVSensor_SS3_HSIOM_POS      (UVSensor_spi_ss3__0__HSIOM_SHIFT)
    #define UVSensor_SS3_HSIOM_SEL_GPIO (UVSensor_spi_ss3__0__HSIOM_GPIO)
    #define UVSensor_SS3_HSIOM_SEL_I2C  (UVSensor_spi_ss3__0__HSIOM_I2C)
    #define UVSensor_SS3_HSIOM_SEL_SPI  (UVSensor_spi_ss3__0__HSIOM_SPI)
#endif /* (UVSensor_SS3_PIN) */

#if (UVSensor_I2C_PINS)
    #define UVSensor_SCL_HSIOM_REG  (*(reg32 *) UVSensor_scl__0__HSIOM)
    #define UVSensor_SCL_HSIOM_PTR  ( (reg32 *) UVSensor_scl__0__HSIOM)
    
    #define UVSensor_SCL_HSIOM_MASK     (UVSensor_scl__0__HSIOM_MASK)
    #define UVSensor_SCL_HSIOM_POS      (UVSensor_scl__0__HSIOM_SHIFT)
    #define UVSensor_SCL_HSIOM_SEL_GPIO (UVSensor_sda__0__HSIOM_GPIO)
    #define UVSensor_SCL_HSIOM_SEL_I2C  (UVSensor_sda__0__HSIOM_I2C)
    
    #define UVSensor_SDA_HSIOM_REG  (*(reg32 *) UVSensor_sda__0__HSIOM)
    #define UVSensor_SDA_HSIOM_PTR  ( (reg32 *) UVSensor_sda__0__HSIOM)
    
    #define UVSensor_SDA_HSIOM_MASK     (UVSensor_sda__0__HSIOM_MASK)
    #define UVSensor_SDA_HSIOM_POS      (UVSensor_sda__0__HSIOM_SHIFT)
    #define UVSensor_SDA_HSIOM_SEL_GPIO (UVSensor_sda__0__HSIOM_GPIO)
    #define UVSensor_SDA_HSIOM_SEL_I2C  (UVSensor_sda__0__HSIOM_I2C)
#endif /* (UVSensor_I2C_PINS) */

#if (UVSensor_SPI_SLAVE_PINS)
    #define UVSensor_SCLK_S_HSIOM_REG   (*(reg32 *) UVSensor_sclk_s__0__HSIOM)
    #define UVSensor_SCLK_S_HSIOM_PTR   ( (reg32 *) UVSensor_sclk_s__0__HSIOM)
    
    #define UVSensor_SCLK_S_HSIOM_MASK      (UVSensor_sclk_s__0__HSIOM_MASK)
    #define UVSensor_SCLK_S_HSIOM_POS       (UVSensor_sclk_s__0__HSIOM_SHIFT)
    #define UVSensor_SCLK_S_HSIOM_SEL_GPIO  (UVSensor_sclk_s__0__HSIOM_GPIO)
    #define UVSensor_SCLK_S_HSIOM_SEL_SPI   (UVSensor_sclk_s__0__HSIOM_SPI)
    
    #define UVSensor_SS0_S_HSIOM_REG    (*(reg32 *) UVSensor_ss0_s__0__HSIOM)
    #define UVSensor_SS0_S_HSIOM_PTR    ( (reg32 *) UVSensor_ss0_s__0__HSIOM)
    
    #define UVSensor_SS0_S_HSIOM_MASK       (UVSensor_ss0_s__0__HSIOM_MASK)
    #define UVSensor_SS0_S_HSIOM_POS        (UVSensor_ss0_s__0__HSIOM_SHIFT)
    #define UVSensor_SS0_S_HSIOM_SEL_GPIO   (UVSensor_ss0_s__0__HSIOM_GPIO)  
    #define UVSensor_SS0_S_HSIOM_SEL_SPI    (UVSensor_ss0_s__0__HSIOM_SPI)
#endif /* (UVSensor_SPI_SLAVE_PINS) */

#if (UVSensor_SPI_SLAVE_MOSI_PIN)
    #define UVSensor_MOSI_S_HSIOM_REG   (*(reg32 *) UVSensor_mosi_s__0__HSIOM)
    #define UVSensor_MOSI_S_HSIOM_PTR   ( (reg32 *) UVSensor_mosi_s__0__HSIOM)
    
    #define UVSensor_MOSI_S_HSIOM_MASK      (UVSensor_mosi_s__0__HSIOM_MASK)
    #define UVSensor_MOSI_S_HSIOM_POS       (UVSensor_mosi_s__0__HSIOM_SHIFT)
    #define UVSensor_MOSI_S_HSIOM_SEL_GPIO  (UVSensor_mosi_s__0__HSIOM_GPIO)
    #define UVSensor_MOSI_S_HSIOM_SEL_SPI   (UVSensor_mosi_s__0__HSIOM_SPI)
#endif /* (UVSensor_SPI_SLAVE_MOSI_PIN) */

#if (UVSensor_SPI_SLAVE_MISO_PIN)
    #define UVSensor_MISO_S_HSIOM_REG   (*(reg32 *) UVSensor_miso_s__0__HSIOM)
    #define UVSensor_MISO_S_HSIOM_PTR   ( (reg32 *) UVSensor_miso_s__0__HSIOM)
    
    #define UVSensor_MISO_S_HSIOM_MASK      (UVSensor_miso_s__0__HSIOM_MASK)
    #define UVSensor_MISO_S_HSIOM_POS       (UVSensor_miso_s__0__HSIOM_SHIFT)
    #define UVSensor_MISO_S_HSIOM_SEL_GPIO  (UVSensor_miso_s__0__HSIOM_GPIO)
    #define UVSensor_MISO_S_HSIOM_SEL_SPI   (UVSensor_miso_s__0__HSIOM_SPI)
#endif /* (UVSensor_SPI_SLAVE_MISO_PIN) */

#if (UVSensor_SPI_MASTER_MISO_PIN)
    #define UVSensor_MISO_M_HSIOM_REG   (*(reg32 *) UVSensor_miso_m__0__HSIOM)
    #define UVSensor_MISO_M_HSIOM_PTR   ( (reg32 *) UVSensor_miso_m__0__HSIOM)
    
    #define UVSensor_MISO_M_HSIOM_MASK      (UVSensor_miso_m__0__HSIOM_MASK)
    #define UVSensor_MISO_M_HSIOM_POS       (UVSensor_miso_m__0__HSIOM_SHIFT)
    #define UVSensor_MISO_M_HSIOM_SEL_GPIO  (UVSensor_miso_m__0__HSIOM_GPIO)
    #define UVSensor_MISO_M_HSIOM_SEL_SPI   (UVSensor_miso_m__0__HSIOM_SPI)
#endif /* (UVSensor_SPI_MASTER_MISO_PIN) */

#if (UVSensor_SPI_MASTER_MOSI_PIN)
    #define UVSensor_MOSI_M_HSIOM_REG   (*(reg32 *) UVSensor_mosi_m__0__HSIOM)
    #define UVSensor_MOSI_M_HSIOM_PTR   ( (reg32 *) UVSensor_mosi_m__0__HSIOM)
    
    #define UVSensor_MOSI_M_HSIOM_MASK      (UVSensor_mosi_m__0__HSIOM_MASK)
    #define UVSensor_MOSI_M_HSIOM_POS       (UVSensor_mosi_m__0__HSIOM_SHIFT)
    #define UVSensor_MOSI_M_HSIOM_SEL_GPIO  (UVSensor_mosi_m__0__HSIOM_GPIO)
    #define UVSensor_MOSI_M_HSIOM_SEL_SPI   (UVSensor_mosi_m__0__HSIOM_SPI)
#endif /* (UVSensor_SPI_MASTER_MOSI_PIN) */

#if (UVSensor_SPI_MASTER_SCLK_PIN)
    #define UVSensor_SCLK_M_HSIOM_REG   (*(reg32 *) UVSensor_sclk_m__0__HSIOM)
    #define UVSensor_SCLK_M_HSIOM_PTR   ( (reg32 *) UVSensor_sclk_m__0__HSIOM)
    
    #define UVSensor_SCLK_M_HSIOM_MASK      (UVSensor_sclk_m__0__HSIOM_MASK)
    #define UVSensor_SCLK_M_HSIOM_POS       (UVSensor_sclk_m__0__HSIOM_SHIFT)
    #define UVSensor_SCLK_M_HSIOM_SEL_GPIO  (UVSensor_sclk_m__0__HSIOM_GPIO)
    #define UVSensor_SCLK_M_HSIOM_SEL_SPI   (UVSensor_sclk_m__0__HSIOM_SPI)
#endif /* (UVSensor_SPI_MASTER_SCLK_PIN) */

#if (UVSensor_SPI_MASTER_SS0_PIN)
    #define UVSensor_SS0_M_HSIOM_REG    (*(reg32 *) UVSensor_ss0_m__0__HSIOM)
    #define UVSensor_SS0_M_HSIOM_PTR    ( (reg32 *) UVSensor_ss0_m__0__HSIOM)
    
    #define UVSensor_SS0_M_HSIOM_MASK       (UVSensor_ss0_m__0__HSIOM_MASK)
    #define UVSensor_SS0_M_HSIOM_POS        (UVSensor_ss0_m__0__HSIOM_SHIFT)
    #define UVSensor_SS0_M_HSIOM_SEL_GPIO   (UVSensor_ss0_m__0__HSIOM_GPIO)
    #define UVSensor_SS0_M_HSIOM_SEL_SPI    (UVSensor_ss0_m__0__HSIOM_SPI)
#endif /* (UVSensor_SPI_MASTER_SS0_PIN) */

#if (UVSensor_SPI_MASTER_SS1_PIN)
    #define UVSensor_SS1_M_HSIOM_REG    (*(reg32 *) UVSensor_ss1_m__0__HSIOM)
    #define UVSensor_SS1_M_HSIOM_PTR    ( (reg32 *) UVSensor_ss1_m__0__HSIOM)
    
    #define UVSensor_SS1_M_HSIOM_MASK       (UVSensor_ss1_m__0__HSIOM_MASK)
    #define UVSensor_SS1_M_HSIOM_POS        (UVSensor_ss1_m__0__HSIOM_SHIFT)
    #define UVSensor_SS1_M_HSIOM_SEL_GPIO   (UVSensor_ss1_m__0__HSIOM_GPIO)
    #define UVSensor_SS1_M_HSIOM_SEL_SPI    (UVSensor_ss1_m__0__HSIOM_SPI)
#endif /* (UVSensor_SPI_MASTER_SS1_PIN) */

#if (UVSensor_SPI_MASTER_SS2_PIN)
    #define UVSensor_SS2_M_HSIOM_REG    (*(reg32 *) UVSensor_ss2_m__0__HSIOM)
    #define UVSensor_SS2_M_HSIOM_PTR    ( (reg32 *) UVSensor_ss2_m__0__HSIOM)
    
    #define UVSensor_SS2_M_HSIOM_MASK       (UVSensor_ss2_m__0__HSIOM_MASK)
    #define UVSensor_SS2_M_HSIOM_POS        (UVSensor_ss2_m__0__HSIOM_SHIFT)
    #define UVSensor_SS2_M_HSIOM_SEL_GPIO   (UVSensor_ss2_m__0__HSIOM_GPIO)
    #define UVSensor_SS2_M_HSIOM_SEL_SPI    (UVSensor_ss2_m__0__HSIOM_SPI)
#endif /* (UVSensor_SPI_MASTER_SS2_PIN) */

#if (UVSensor_SPI_MASTER_SS3_PIN)
    #define UVSensor_SS3_M_HSIOM_REG    (*(reg32 *) UVSensor_ss3_m__0__HSIOM)
    #define UVSensor_SS3_M_HSIOM_PTR    ( (reg32 *) UVSensor_ss3_m__0__HSIOM)
    
    #define UVSensor_SS3_M_HSIOM_MASK      (UVSensor_ss3_m__0__HSIOM_MASK)
    #define UVSensor_SS3_M_HSIOM_POS       (UVSensor_ss3_m__0__HSIOM_SHIFT)
    #define UVSensor_SS3_M_HSIOM_SEL_GPIO  (UVSensor_ss3_m__0__HSIOM_GPIO)
    #define UVSensor_SS3_M_HSIOM_SEL_SPI   (UVSensor_ss3_m__0__HSIOM_SPI)
#endif /* (UVSensor_SPI_MASTER_SS3_PIN) */

#if (UVSensor_UART_RX_PIN)
    #define UVSensor_RX_HSIOM_REG   (*(reg32 *) UVSensor_rx__0__HSIOM)
    #define UVSensor_RX_HSIOM_PTR   ( (reg32 *) UVSensor_rx__0__HSIOM)
    
    #define UVSensor_RX_HSIOM_MASK      (UVSensor_rx__0__HSIOM_MASK)
    #define UVSensor_RX_HSIOM_POS       (UVSensor_rx__0__HSIOM_SHIFT)
    #define UVSensor_RX_HSIOM_SEL_GPIO  (UVSensor_rx__0__HSIOM_GPIO)
    #define UVSensor_RX_HSIOM_SEL_UART  (UVSensor_rx__0__HSIOM_UART)
#endif /* (UVSensor_UART_RX_PIN) */

#if (UVSensor_UART_RX_WAKE_PIN)
    #define UVSensor_RX_WAKE_HSIOM_REG   (*(reg32 *) UVSensor_rx_wake__0__HSIOM)
    #define UVSensor_RX_WAKE_HSIOM_PTR   ( (reg32 *) UVSensor_rx_wake__0__HSIOM)
    
    #define UVSensor_RX_WAKE_HSIOM_MASK      (UVSensor_rx_wake__0__HSIOM_MASK)
    #define UVSensor_RX_WAKE_HSIOM_POS       (UVSensor_rx_wake__0__HSIOM_SHIFT)
    #define UVSensor_RX_WAKE_HSIOM_SEL_GPIO  (UVSensor_rx_wake__0__HSIOM_GPIO)
    #define UVSensor_RX_WAKE_HSIOM_SEL_UART  (UVSensor_rx_wake__0__HSIOM_UART)
#endif /* (UVSensor_UART_WAKE_RX_PIN) */

#if (UVSensor_UART_CTS_PIN)
    #define UVSensor_CTS_HSIOM_REG   (*(reg32 *) UVSensor_cts__0__HSIOM)
    #define UVSensor_CTS_HSIOM_PTR   ( (reg32 *) UVSensor_cts__0__HSIOM)
    
    #define UVSensor_CTS_HSIOM_MASK      (UVSensor_cts__0__HSIOM_MASK)
    #define UVSensor_CTS_HSIOM_POS       (UVSensor_cts__0__HSIOM_SHIFT)
    #define UVSensor_CTS_HSIOM_SEL_GPIO  (UVSensor_cts__0__HSIOM_GPIO)
    #define UVSensor_CTS_HSIOM_SEL_UART  (UVSensor_cts__0__HSIOM_UART)
#endif /* (UVSensor_UART_CTS_PIN) */

#if (UVSensor_UART_TX_PIN)
    #define UVSensor_TX_HSIOM_REG   (*(reg32 *) UVSensor_tx__0__HSIOM)
    #define UVSensor_TX_HSIOM_PTR   ( (reg32 *) UVSensor_tx__0__HSIOM)
    
    #define UVSensor_TX_HSIOM_MASK      (UVSensor_tx__0__HSIOM_MASK)
    #define UVSensor_TX_HSIOM_POS       (UVSensor_tx__0__HSIOM_SHIFT)
    #define UVSensor_TX_HSIOM_SEL_GPIO  (UVSensor_tx__0__HSIOM_GPIO)
    #define UVSensor_TX_HSIOM_SEL_UART  (UVSensor_tx__0__HSIOM_UART)
#endif /* (UVSensor_UART_TX_PIN) */

#if (UVSensor_UART_RX_TX_PIN)
    #define UVSensor_RX_TX_HSIOM_REG   (*(reg32 *) UVSensor_rx_tx__0__HSIOM)
    #define UVSensor_RX_TX_HSIOM_PTR   ( (reg32 *) UVSensor_rx_tx__0__HSIOM)
    
    #define UVSensor_RX_TX_HSIOM_MASK      (UVSensor_rx_tx__0__HSIOM_MASK)
    #define UVSensor_RX_TX_HSIOM_POS       (UVSensor_rx_tx__0__HSIOM_SHIFT)
    #define UVSensor_RX_TX_HSIOM_SEL_GPIO  (UVSensor_rx_tx__0__HSIOM_GPIO)
    #define UVSensor_RX_TX_HSIOM_SEL_UART  (UVSensor_rx_tx__0__HSIOM_UART)
#endif /* (UVSensor_UART_RX_TX_PIN) */

#if (UVSensor_UART_RTS_PIN)
    #define UVSensor_RTS_HSIOM_REG      (*(reg32 *) UVSensor_rts__0__HSIOM)
    #define UVSensor_RTS_HSIOM_PTR      ( (reg32 *) UVSensor_rts__0__HSIOM)
    
    #define UVSensor_RTS_HSIOM_MASK     (UVSensor_rts__0__HSIOM_MASK)
    #define UVSensor_RTS_HSIOM_POS      (UVSensor_rts__0__HSIOM_SHIFT)    
    #define UVSensor_RTS_HSIOM_SEL_GPIO (UVSensor_rts__0__HSIOM_GPIO)
    #define UVSensor_RTS_HSIOM_SEL_UART (UVSensor_rts__0__HSIOM_UART)    
#endif /* (UVSensor_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define UVSensor_HSIOM_DEF_SEL      (0x00u)
#define UVSensor_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for UVSensor_CY_SCBIP_V0 
* and UVSensor_CY_SCBIP_V1. It is not recommended to use them for 
* UVSensor_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define UVSensor_HSIOM_UART_SEL     (0x09u)
#define UVSensor_HSIOM_I2C_SEL      (0x0Eu)
#define UVSensor_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define UVSensor_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define UVSensor_RX_SCL_MOSI_PIN_INDEX       (0u)
#define UVSensor_TX_SDA_MISO_PIN_INDEX       (1u)
#define UVSensor_CTS_SCLK_PIN_INDEX       (2u)
#define UVSensor_RTS_SS0_PIN_INDEX       (3u)
#define UVSensor_SS1_PIN_INDEX                  (4u)
#define UVSensor_SS2_PIN_INDEX                  (5u)
#define UVSensor_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define UVSensor_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << UVSensor_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define UVSensor_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << UVSensor_RX_SCL_MOSI_PIN_INDEX)
#define UVSensor_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << UVSensor_TX_SDA_MISO_PIN_INDEX)
#define UVSensor_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << UVSensor_CTS_SCLK_PIN_INDEX)
#define UVSensor_RTS_SS0_PIN_MASK     ((uint32) 0x01u << UVSensor_RTS_SS0_PIN_INDEX)
#define UVSensor_SS1_PIN_MASK                ((uint32) 0x01u << UVSensor_SS1_PIN_INDEX)
#define UVSensor_SS2_PIN_MASK                ((uint32) 0x01u << UVSensor_SS2_PIN_INDEX)
#define UVSensor_SS3_PIN_MASK                ((uint32) 0x01u << UVSensor_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define UVSensor_INTCFG_TYPE_MASK           (0x03u)
#define UVSensor_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define UVSensor_PIN_DM_ALG_HIZ  (0u)
#define UVSensor_PIN_DM_DIG_HIZ  (1u)
#define UVSensor_PIN_DM_OD_LO    (4u)
#define UVSensor_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define UVSensor_DM_MASK    (0x7u)
#define UVSensor_DM_SIZE    (3u)
#define UVSensor_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) UVSensor_DM_MASK << (UVSensor_DM_SIZE * (pos)))) >> \
                                                              (UVSensor_DM_SIZE * (pos)) )

#if (UVSensor_TX_SDA_MISO_PIN)
    #define UVSensor_CHECK_TX_SDA_MISO_PIN_USED \
                (UVSensor_PIN_DM_ALG_HIZ != \
                    UVSensor_GET_P4_PIN_DM(UVSensor_uart_tx_i2c_sda_spi_miso_PC, \
                                                   UVSensor_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (UVSensor_TX_SDA_MISO_PIN) */

#if (UVSensor_RTS_SS0_PIN)
    #define UVSensor_CHECK_RTS_SS0_PIN_USED \
                (UVSensor_PIN_DM_ALG_HIZ != \
                    UVSensor_GET_P4_PIN_DM(UVSensor_uart_rts_spi_ss0_PC, \
                                                   UVSensor_uart_rts_spi_ss0_SHIFT))
#endif /* (UVSensor_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define UVSensor_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define UVSensor_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define UVSensor_SET_HSIOM_SEL(reg, mask, pos, sel) UVSensor_SET_REGISTER_BITS(reg, mask, pos, sel)
#define UVSensor_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        UVSensor_SET_REGISTER_BITS(reg, mask, pos, intType)
#define UVSensor_SET_INP_DIS(reg, mask, val) UVSensor_SET_REGISTER_BIT(reg, mask, val)

/* UVSensor_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  UVSensor_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (UVSensor_CY_SCBIP_V0)
#if (UVSensor_I2C_PINS)
    #define UVSensor_SET_I2C_SCL_DR(val) UVSensor_scl_Write(val)

    #define UVSensor_SET_I2C_SCL_HSIOM_SEL(sel) \
                          UVSensor_SET_HSIOM_SEL(UVSensor_SCL_HSIOM_REG,  \
                                                         UVSensor_SCL_HSIOM_MASK, \
                                                         UVSensor_SCL_HSIOM_POS,  \
                                                         (sel))
    #define UVSensor_WAIT_SCL_SET_HIGH  (0u == UVSensor_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (UVSensor_RX_WAKE_SCL_MOSI_PIN)
    #define UVSensor_SET_I2C_SCL_DR(val) \
                            UVSensor_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define UVSensor_SET_I2C_SCL_HSIOM_SEL(sel) \
                    UVSensor_SET_HSIOM_SEL(UVSensor_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   UVSensor_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   UVSensor_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define UVSensor_WAIT_SCL_SET_HIGH  (0u == UVSensor_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (UVSensor_RX_SCL_MOSI_PIN)
    #define UVSensor_SET_I2C_SCL_DR(val) \
                            UVSensor_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define UVSensor_SET_I2C_SCL_HSIOM_SEL(sel) \
                            UVSensor_SET_HSIOM_SEL(UVSensor_RX_SCL_MOSI_HSIOM_REG,  \
                                                           UVSensor_RX_SCL_MOSI_HSIOM_MASK, \
                                                           UVSensor_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define UVSensor_WAIT_SCL_SET_HIGH  (0u == UVSensor_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define UVSensor_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define UVSensor_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define UVSensor_WAIT_SCL_SET_HIGH  (0u)
#endif /* (UVSensor_I2C_PINS) */

/* SCB I2C: sda signal */
#if (UVSensor_I2C_PINS)
    #define UVSensor_WAIT_SDA_SET_HIGH  (0u == UVSensor_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (UVSensor_TX_SDA_MISO_PIN)
    #define UVSensor_WAIT_SDA_SET_HIGH  (0u == UVSensor_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define UVSensor_WAIT_SDA_SET_HIGH  (0u)
#endif /* (UVSensor_MOSI_SCL_RX_PIN) */
#endif /* (UVSensor_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (UVSensor_RX_SCL_MOSI_PIN)
    #define UVSensor_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (UVSensor_RX_WAKE_SCL_MOSI_PIN)
    #define UVSensor_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) UVSensor_uart_rx_wake_i2c_scl_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(UVSensor_UART_RX_WAKE_PIN)
    #define UVSensor_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) UVSensor_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (UVSensor_RX_SCL_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define UVSensor_REMOVE_MOSI_SCL_RX_WAKE_PIN    UVSensor_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define UVSensor_REMOVE_MOSI_SCL_RX_PIN         UVSensor_REMOVE_RX_SCL_MOSI_PIN
#define UVSensor_REMOVE_MISO_SDA_TX_PIN         UVSensor_REMOVE_TX_SDA_MISO_PIN
#ifndef UVSensor_REMOVE_SCLK_PIN
#define UVSensor_REMOVE_SCLK_PIN                UVSensor_REMOVE_CTS_SCLK_PIN
#endif /* UVSensor_REMOVE_SCLK_PIN */
#ifndef UVSensor_REMOVE_SS0_PIN
#define UVSensor_REMOVE_SS0_PIN                 UVSensor_REMOVE_RTS_SS0_PIN
#endif /* UVSensor_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define UVSensor_MOSI_SCL_RX_WAKE_PIN   UVSensor_RX_WAKE_SCL_MOSI_PIN
#define UVSensor_MOSI_SCL_RX_PIN        UVSensor_RX_SCL_MOSI_PIN
#define UVSensor_MISO_SDA_TX_PIN        UVSensor_TX_SDA_MISO_PIN
#ifndef UVSensor_SCLK_PIN
#define UVSensor_SCLK_PIN               UVSensor_CTS_SCLK_PIN
#endif /* UVSensor_SCLK_PIN */
#ifndef UVSensor_SS0_PIN
#define UVSensor_SS0_PIN                UVSensor_RTS_SS0_PIN
#endif /* UVSensor_SS0_PIN */

#if (UVSensor_MOSI_SCL_RX_WAKE_PIN)
    #define UVSensor_MOSI_SCL_RX_WAKE_HSIOM_REG     UVSensor_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UVSensor_MOSI_SCL_RX_WAKE_HSIOM_PTR     UVSensor_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UVSensor_MOSI_SCL_RX_WAKE_HSIOM_MASK    UVSensor_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UVSensor_MOSI_SCL_RX_WAKE_HSIOM_POS     UVSensor_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define UVSensor_MOSI_SCL_RX_WAKE_INTCFG_REG    UVSensor_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UVSensor_MOSI_SCL_RX_WAKE_INTCFG_PTR    UVSensor_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define UVSensor_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   UVSensor_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define UVSensor_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  UVSensor_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (UVSensor_RX_WAKE_SCL_MOSI_PIN) */

#if (UVSensor_MOSI_SCL_RX_PIN)
    #define UVSensor_MOSI_SCL_RX_HSIOM_REG      UVSensor_RX_SCL_MOSI_HSIOM_REG
    #define UVSensor_MOSI_SCL_RX_HSIOM_PTR      UVSensor_RX_SCL_MOSI_HSIOM_PTR
    #define UVSensor_MOSI_SCL_RX_HSIOM_MASK     UVSensor_RX_SCL_MOSI_HSIOM_MASK
    #define UVSensor_MOSI_SCL_RX_HSIOM_POS      UVSensor_RX_SCL_MOSI_HSIOM_POS
#endif /* (UVSensor_MOSI_SCL_RX_PIN) */

#if (UVSensor_MISO_SDA_TX_PIN)
    #define UVSensor_MISO_SDA_TX_HSIOM_REG      UVSensor_TX_SDA_MISO_HSIOM_REG
    #define UVSensor_MISO_SDA_TX_HSIOM_PTR      UVSensor_TX_SDA_MISO_HSIOM_REG
    #define UVSensor_MISO_SDA_TX_HSIOM_MASK     UVSensor_TX_SDA_MISO_HSIOM_REG
    #define UVSensor_MISO_SDA_TX_HSIOM_POS      UVSensor_TX_SDA_MISO_HSIOM_REG
#endif /* (UVSensor_MISO_SDA_TX_PIN_PIN) */

#if (UVSensor_SCLK_PIN)
    #ifndef UVSensor_SCLK_HSIOM_REG
    #define UVSensor_SCLK_HSIOM_REG     UVSensor_CTS_SCLK_HSIOM_REG
    #define UVSensor_SCLK_HSIOM_PTR     UVSensor_CTS_SCLK_HSIOM_PTR
    #define UVSensor_SCLK_HSIOM_MASK    UVSensor_CTS_SCLK_HSIOM_MASK
    #define UVSensor_SCLK_HSIOM_POS     UVSensor_CTS_SCLK_HSIOM_POS
    #endif /* UVSensor_SCLK_HSIOM_REG */
#endif /* (UVSensor_SCLK_PIN) */

#if (UVSensor_SS0_PIN)
    #ifndef UVSensor_SS0_HSIOM_REG
    #define UVSensor_SS0_HSIOM_REG      UVSensor_RTS_SS0_HSIOM_REG
    #define UVSensor_SS0_HSIOM_PTR      UVSensor_RTS_SS0_HSIOM_PTR
    #define UVSensor_SS0_HSIOM_MASK     UVSensor_RTS_SS0_HSIOM_MASK
    #define UVSensor_SS0_HSIOM_POS      UVSensor_RTS_SS0_HSIOM_POS
    #endif /* UVSensor_SS0_HSIOM_REG */
#endif /* (UVSensor_SS0_PIN) */

#define UVSensor_MOSI_SCL_RX_WAKE_PIN_INDEX UVSensor_RX_WAKE_SCL_MOSI_PIN_INDEX
#define UVSensor_MOSI_SCL_RX_PIN_INDEX      UVSensor_RX_SCL_MOSI_PIN_INDEX
#define UVSensor_MISO_SDA_TX_PIN_INDEX      UVSensor_TX_SDA_MISO_PIN_INDEX
#ifndef UVSensor_SCLK_PIN_INDEX
#define UVSensor_SCLK_PIN_INDEX             UVSensor_CTS_SCLK_PIN_INDEX
#endif /* UVSensor_SCLK_PIN_INDEX */
#ifndef UVSensor_SS0_PIN_INDEX
#define UVSensor_SS0_PIN_INDEX              UVSensor_RTS_SS0_PIN_INDEX
#endif /* UVSensor_SS0_PIN_INDEX */

#define UVSensor_MOSI_SCL_RX_WAKE_PIN_MASK UVSensor_RX_WAKE_SCL_MOSI_PIN_MASK
#define UVSensor_MOSI_SCL_RX_PIN_MASK      UVSensor_RX_SCL_MOSI_PIN_MASK
#define UVSensor_MISO_SDA_TX_PIN_MASK      UVSensor_TX_SDA_MISO_PIN_MASK
#ifndef UVSensor_SCLK_PIN_MASK
#define UVSensor_SCLK_PIN_MASK             UVSensor_CTS_SCLK_PIN_MASK
#endif /* UVSensor_SCLK_PIN_MASK */
#ifndef UVSensor_SS0_PIN_MASK
#define UVSensor_SS0_PIN_MASK              UVSensor_RTS_SS0_PIN_MASK
#endif /* UVSensor_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_UVSensor_H) */


/* [] END OF FILE */
