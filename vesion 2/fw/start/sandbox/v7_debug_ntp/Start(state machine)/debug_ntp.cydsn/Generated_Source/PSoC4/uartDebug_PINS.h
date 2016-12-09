/***************************************************************************//**
* \file uartDebug_PINS.h
* \version 3.20
*
* \brief
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_uartDebug_H)
#define CY_SCB_PINS_uartDebug_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define uartDebug_REMOVE_RX_WAKE_SDA_MOSI_PIN  (1u)
#define uartDebug_REMOVE_RX_SDA_MOSI_PIN      (1u)
#define uartDebug_REMOVE_TX_SCL_MISO_PIN      (1u)
#define uartDebug_REMOVE_CTS_SCLK_PIN      (1u)
#define uartDebug_REMOVE_RTS_SS0_PIN      (1u)
#define uartDebug_REMOVE_SS1_PIN                 (1u)
#define uartDebug_REMOVE_SS2_PIN                 (1u)
#define uartDebug_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define uartDebug_REMOVE_I2C_PINS                (1u)
#define uartDebug_REMOVE_SPI_MASTER_PINS         (1u)
#define uartDebug_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define uartDebug_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define uartDebug_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define uartDebug_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define uartDebug_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define uartDebug_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define uartDebug_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define uartDebug_REMOVE_SPI_SLAVE_PINS          (1u)
#define uartDebug_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define uartDebug_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define uartDebug_REMOVE_UART_TX_PIN             (0u)
#define uartDebug_REMOVE_UART_RX_TX_PIN          (1u)
#define uartDebug_REMOVE_UART_RX_PIN             (0u)
#define uartDebug_REMOVE_UART_RX_WAKE_PIN        (1u)
#define uartDebug_REMOVE_UART_RTS_PIN            (1u)
#define uartDebug_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define uartDebug_RX_WAKE_SDA_MOSI_PIN (0u == uartDebug_REMOVE_RX_WAKE_SDA_MOSI_PIN)
#define uartDebug_RX_SDA_MOSI_PIN     (0u == uartDebug_REMOVE_RX_SDA_MOSI_PIN)
#define uartDebug_TX_SCL_MISO_PIN     (0u == uartDebug_REMOVE_TX_SCL_MISO_PIN)
#define uartDebug_CTS_SCLK_PIN     (0u == uartDebug_REMOVE_CTS_SCLK_PIN)
#define uartDebug_RTS_SS0_PIN     (0u == uartDebug_REMOVE_RTS_SS0_PIN)
#define uartDebug_SS1_PIN                (0u == uartDebug_REMOVE_SS1_PIN)
#define uartDebug_SS2_PIN                (0u == uartDebug_REMOVE_SS2_PIN)
#define uartDebug_SS3_PIN                (0u == uartDebug_REMOVE_SS3_PIN)

/* Mode defined pins */
#define uartDebug_I2C_PINS               (0u == uartDebug_REMOVE_I2C_PINS)
#define uartDebug_SPI_MASTER_PINS        (0u == uartDebug_REMOVE_SPI_MASTER_PINS)
#define uartDebug_SPI_MASTER_SCLK_PIN    (0u == uartDebug_REMOVE_SPI_MASTER_SCLK_PIN)
#define uartDebug_SPI_MASTER_MOSI_PIN    (0u == uartDebug_REMOVE_SPI_MASTER_MOSI_PIN)
#define uartDebug_SPI_MASTER_MISO_PIN    (0u == uartDebug_REMOVE_SPI_MASTER_MISO_PIN)
#define uartDebug_SPI_MASTER_SS0_PIN     (0u == uartDebug_REMOVE_SPI_MASTER_SS0_PIN)
#define uartDebug_SPI_MASTER_SS1_PIN     (0u == uartDebug_REMOVE_SPI_MASTER_SS1_PIN)
#define uartDebug_SPI_MASTER_SS2_PIN     (0u == uartDebug_REMOVE_SPI_MASTER_SS2_PIN)
#define uartDebug_SPI_MASTER_SS3_PIN     (0u == uartDebug_REMOVE_SPI_MASTER_SS3_PIN)
#define uartDebug_SPI_SLAVE_PINS         (0u == uartDebug_REMOVE_SPI_SLAVE_PINS)
#define uartDebug_SPI_SLAVE_MOSI_PIN     (0u == uartDebug_REMOVE_SPI_SLAVE_MOSI_PIN)
#define uartDebug_SPI_SLAVE_MISO_PIN     (0u == uartDebug_REMOVE_SPI_SLAVE_MISO_PIN)
#define uartDebug_UART_TX_PIN            (0u == uartDebug_REMOVE_UART_TX_PIN)
#define uartDebug_UART_RX_TX_PIN         (0u == uartDebug_REMOVE_UART_RX_TX_PIN)
#define uartDebug_UART_RX_PIN            (0u == uartDebug_REMOVE_UART_RX_PIN)
#define uartDebug_UART_RX_WAKE_PIN       (0u == uartDebug_REMOVE_UART_RX_WAKE_PIN)
#define uartDebug_UART_RTS_PIN           (0u == uartDebug_REMOVE_UART_RTS_PIN)
#define uartDebug_UART_CTS_PIN           (0u == uartDebug_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (uartDebug_RX_WAKE_SDA_MOSI_PIN)
    #include "uartDebug_uart_rx_wake_i2c_sda_spi_mosi.h"
#endif /* (uartDebug_RX_SDA_MOSI) */

#if (uartDebug_RX_SDA_MOSI_PIN)
    #include "uartDebug_uart_rx_i2c_sda_spi_mosi.h"
#endif /* (uartDebug_RX_SDA_MOSI) */

#if (uartDebug_TX_SCL_MISO_PIN)
    #include "uartDebug_uart_tx_i2c_scl_spi_miso.h"
#endif /* (uartDebug_TX_SCL_MISO) */

#if (uartDebug_CTS_SCLK_PIN)
    #include "uartDebug_uart_cts_spi_sclk.h"
#endif /* (uartDebug_CTS_SCLK) */

#if (uartDebug_RTS_SS0_PIN)
    #include "uartDebug_uart_rts_spi_ss0.h"
#endif /* (uartDebug_RTS_SS0_PIN) */

#if (uartDebug_SS1_PIN)
    #include "uartDebug_spi_ss1.h"
#endif /* (uartDebug_SS1_PIN) */

#if (uartDebug_SS2_PIN)
    #include "uartDebug_spi_ss2.h"
#endif /* (uartDebug_SS2_PIN) */

#if (uartDebug_SS3_PIN)
    #include "uartDebug_spi_ss3.h"
#endif /* (uartDebug_SS3_PIN) */

#if (uartDebug_I2C_PINS)
    #include "uartDebug_scl.h"
    #include "uartDebug_sda.h"
#endif /* (uartDebug_I2C_PINS) */

#if (uartDebug_SPI_MASTER_PINS)
#if (uartDebug_SPI_MASTER_SCLK_PIN)
    #include "uartDebug_sclk_m.h"
#endif /* (uartDebug_SPI_MASTER_SCLK_PIN) */

#if (uartDebug_SPI_MASTER_MOSI_PIN)
    #include "uartDebug_mosi_m.h"
#endif /* (uartDebug_SPI_MASTER_MOSI_PIN) */

#if (uartDebug_SPI_MASTER_MISO_PIN)
    #include "uartDebug_miso_m.h"
#endif /*(uartDebug_SPI_MASTER_MISO_PIN) */
#endif /* (uartDebug_SPI_MASTER_PINS) */

#if (uartDebug_SPI_SLAVE_PINS)
    #include "uartDebug_sclk_s.h"
    #include "uartDebug_ss_s.h"

#if (uartDebug_SPI_SLAVE_MOSI_PIN)
    #include "uartDebug_mosi_s.h"
#endif /* (uartDebug_SPI_SLAVE_MOSI_PIN) */

#if (uartDebug_SPI_SLAVE_MISO_PIN)
    #include "uartDebug_miso_s.h"
#endif /*(uartDebug_SPI_SLAVE_MISO_PIN) */
#endif /* (uartDebug_SPI_SLAVE_PINS) */

#if (uartDebug_SPI_MASTER_SS0_PIN)
    #include "uartDebug_ss0_m.h"
#endif /* (uartDebug_SPI_MASTER_SS0_PIN) */

#if (uartDebug_SPI_MASTER_SS1_PIN)
    #include "uartDebug_ss1_m.h"
#endif /* (uartDebug_SPI_MASTER_SS1_PIN) */

#if (uartDebug_SPI_MASTER_SS2_PIN)
    #include "uartDebug_ss2_m.h"
#endif /* (uartDebug_SPI_MASTER_SS2_PIN) */

#if (uartDebug_SPI_MASTER_SS3_PIN)
    #include "uartDebug_ss3_m.h"
#endif /* (uartDebug_SPI_MASTER_SS3_PIN) */

#if (uartDebug_UART_TX_PIN)
    #include "uartDebug_tx.h"
#endif /* (uartDebug_UART_TX_PIN) */

#if (uartDebug_UART_RX_TX_PIN)
    #include "uartDebug_rx_tx.h"
#endif /* (uartDebug_UART_RX_TX_PIN) */

#if (uartDebug_UART_RX_PIN)
    #include "uartDebug_rx.h"
#endif /* (uartDebug_UART_RX_PIN) */

#if (uartDebug_UART_RX_WAKE_PIN)
    #include "uartDebug_rx_wake.h"
#endif /* (uartDebug_UART_RX_WAKE_PIN) */

#if (uartDebug_UART_RTS_PIN)
    #include "uartDebug_rts.h"
#endif /* (uartDebug_UART_RTS_PIN) */

#if (uartDebug_UART_CTS_PIN)
    #include "uartDebug_cts.h"
#endif /* (uartDebug_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (uartDebug_RX_SDA_MOSI_PIN)
    #define uartDebug_RX_SDA_MOSI_HSIOM_REG   (*(reg32 *) uartDebug_uart_rx_i2c_sda_spi_mosi__0__HSIOM)
    #define uartDebug_RX_SDA_MOSI_HSIOM_PTR   ( (reg32 *) uartDebug_uart_rx_i2c_sda_spi_mosi__0__HSIOM)
    
    #define uartDebug_RX_SDA_MOSI_HSIOM_MASK      (uartDebug_uart_rx_i2c_sda_spi_mosi__0__HSIOM_MASK)
    #define uartDebug_RX_SDA_MOSI_HSIOM_POS       (uartDebug_uart_rx_i2c_sda_spi_mosi__0__HSIOM_SHIFT)
    #define uartDebug_RX_SDA_MOSI_HSIOM_SEL_GPIO  (uartDebug_uart_rx_i2c_sda_spi_mosi__0__HSIOM_GPIO)
    #define uartDebug_RX_SDA_MOSI_HSIOM_SEL_I2C   (uartDebug_uart_rx_i2c_sda_spi_mosi__0__HSIOM_I2C)
    #define uartDebug_RX_SDA_MOSI_HSIOM_SEL_SPI   (uartDebug_uart_rx_i2c_sda_spi_mosi__0__HSIOM_SPI)
    #define uartDebug_RX_SDA_MOSI_HSIOM_SEL_UART  (uartDebug_uart_rx_i2c_sda_spi_mosi__0__HSIOM_UART)
    
#elif (uartDebug_RX_WAKE_SDA_MOSI_PIN)
    #define uartDebug_RX_WAKE_SDA_MOSI_HSIOM_REG   (*(reg32 *) uartDebug_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM)
    #define uartDebug_RX_WAKE_SDA_MOSI_HSIOM_PTR   ( (reg32 *) uartDebug_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM)
    
    #define uartDebug_RX_WAKE_SDA_MOSI_HSIOM_MASK      (uartDebug_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_MASK)
    #define uartDebug_RX_WAKE_SDA_MOSI_HSIOM_POS       (uartDebug_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_SHIFT)
    #define uartDebug_RX_WAKE_SDA_MOSI_HSIOM_SEL_GPIO  (uartDebug_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_GPIO)
    #define uartDebug_RX_WAKE_SDA_MOSI_HSIOM_SEL_I2C   (uartDebug_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_I2C)
    #define uartDebug_RX_WAKE_SDA_MOSI_HSIOM_SEL_SPI   (uartDebug_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_SPI)
    #define uartDebug_RX_WAKE_SDA_MOSI_HSIOM_SEL_UART  (uartDebug_uart_rx_wake_i2c_sda_spi_mosi__0__HSIOM_UART)    
   
    #define uartDebug_RX_WAKE_SDA_MOSI_INTCFG_REG (*(reg32 *) uartDebug_uart_rx_wake_i2c_sda_spi_mosi__0__INTCFG)
    #define uartDebug_RX_WAKE_SDA_MOSI_INTCFG_PTR ( (reg32 *) uartDebug_uart_rx_wake_i2c_sda_spi_mosi__0__INTCFG)
    #define uartDebug_RX_WAKE_SDA_MOSI_INTCFG_TYPE_POS  (uartDebug_uart_rx_wake_i2c_sda_spi_mosi__SHIFT)
    #define uartDebug_RX_WAKE_SDA_MOSI_INTCFG_TYPE_MASK ((uint32) uartDebug_INTCFG_TYPE_MASK << \
                                                                           uartDebug_RX_WAKE_SDA_MOSI_INTCFG_TYPE_POS)
#else
    /* None of pins uartDebug_RX_SDA_MOSI_PIN or uartDebug_RX_WAKE_SDA_MOSI_PIN present.*/
#endif /* (uartDebug_RX_SDA_MOSI_PIN) */

#if (uartDebug_TX_SCL_MISO_PIN)
    #define uartDebug_TX_SCL_MISO_HSIOM_REG   (*(reg32 *) uartDebug_uart_tx_i2c_scl_spi_miso__0__HSIOM)
    #define uartDebug_TX_SCL_MISO_HSIOM_PTR   ( (reg32 *) uartDebug_uart_tx_i2c_scl_spi_miso__0__HSIOM)
    
    #define uartDebug_TX_SCL_MISO_HSIOM_MASK      (uartDebug_uart_tx_i2c_scl_spi_miso__0__HSIOM_MASK)
    #define uartDebug_TX_SCL_MISO_HSIOM_POS       (uartDebug_uart_tx_i2c_scl_spi_miso__0__HSIOM_SHIFT)
    #define uartDebug_TX_SCL_MISO_HSIOM_SEL_GPIO  (uartDebug_uart_tx_i2c_scl_spi_miso__0__HSIOM_GPIO)
    #define uartDebug_TX_SCL_MISO_HSIOM_SEL_I2C   (uartDebug_uart_tx_i2c_scl_spi_miso__0__HSIOM_I2C)
    #define uartDebug_TX_SCL_MISO_HSIOM_SEL_SPI   (uartDebug_uart_tx_i2c_scl_spi_miso__0__HSIOM_SPI)
    #define uartDebug_TX_SCL_MISO_HSIOM_SEL_UART  (uartDebug_uart_tx_i2c_scl_spi_miso__0__HSIOM_UART)
#endif /* (uartDebug_TX_SCL_MISO_PIN) */

#if (uartDebug_CTS_SCLK_PIN)
    #define uartDebug_CTS_SCLK_HSIOM_REG   (*(reg32 *) uartDebug_uart_cts_spi_sclk__0__HSIOM)
    #define uartDebug_CTS_SCLK_HSIOM_PTR   ( (reg32 *) uartDebug_uart_cts_spi_sclk__0__HSIOM)
    
    #define uartDebug_CTS_SCLK_HSIOM_MASK      (uartDebug_uart_cts_spi_sclk__0__HSIOM_MASK)
    #define uartDebug_CTS_SCLK_HSIOM_POS       (uartDebug_uart_cts_spi_sclk__0__HSIOM_SHIFT)
    #define uartDebug_CTS_SCLK_HSIOM_SEL_GPIO  (uartDebug_uart_cts_spi_sclk__0__HSIOM_GPIO)
    #define uartDebug_CTS_SCLK_HSIOM_SEL_I2C   (uartDebug_uart_cts_spi_sclk__0__HSIOM_I2C)
    #define uartDebug_CTS_SCLK_HSIOM_SEL_SPI   (uartDebug_uart_cts_spi_sclk__0__HSIOM_SPI)
    #define uartDebug_CTS_SCLK_HSIOM_SEL_UART  (uartDebug_uart_cts_spi_sclk__0__HSIOM_UART)
#endif /* (uartDebug_CTS_SCLK_PIN) */

#if (uartDebug_RTS_SS0_PIN)
    #define uartDebug_RTS_SS0_HSIOM_REG   (*(reg32 *) uartDebug_uart_rts_spi_ss0__0__HSIOM)
    #define uartDebug_RTS_SS0_HSIOM_PTR   ( (reg32 *) uartDebug_uart_rts_spi_ss0__0__HSIOM)
    
    #define uartDebug_RTS_SS0_HSIOM_MASK      (uartDebug_uart_rts_spi_ss0__0__HSIOM_MASK)
    #define uartDebug_RTS_SS0_HSIOM_POS       (uartDebug_uart_rts_spi_ss0__0__HSIOM_SHIFT)
    #define uartDebug_RTS_SS0_HSIOM_SEL_GPIO  (uartDebug_uart_rts_spi_ss0__0__HSIOM_GPIO)
    #define uartDebug_RTS_SS0_HSIOM_SEL_I2C   (uartDebug_uart_rts_spi_ss0__0__HSIOM_I2C)
    #define uartDebug_RTS_SS0_HSIOM_SEL_SPI   (uartDebug_uart_rts_spi_ss0__0__HSIOM_SPI)
#if !(uartDebug_CY_SCBIP_V0 || uartDebug_CY_SCBIP_V1)
    #define uartDebug_RTS_SS0_HSIOM_SEL_UART  (uartDebug_uart_rts_spi_ss0__0__HSIOM_UART)
#endif /* !(uartDebug_CY_SCBIP_V0 || uartDebug_CY_SCBIP_V1) */
#endif /* (uartDebug_RTS_SS0_PIN) */

#if (uartDebug_SS1_PIN)
    #define uartDebug_SS1_HSIOM_REG  (*(reg32 *) uartDebug_spi_ss1__0__HSIOM)
    #define uartDebug_SS1_HSIOM_PTR  ( (reg32 *) uartDebug_spi_ss1__0__HSIOM)
    
    #define uartDebug_SS1_HSIOM_MASK     (uartDebug_spi_ss1__0__HSIOM_MASK)
    #define uartDebug_SS1_HSIOM_POS      (uartDebug_spi_ss1__0__HSIOM_SHIFT)
    #define uartDebug_SS1_HSIOM_SEL_GPIO (uartDebug_spi_ss1__0__HSIOM_GPIO)
    #define uartDebug_SS1_HSIOM_SEL_I2C  (uartDebug_spi_ss1__0__HSIOM_I2C)
    #define uartDebug_SS1_HSIOM_SEL_SPI  (uartDebug_spi_ss1__0__HSIOM_SPI)
#endif /* (uartDebug_SS1_PIN) */

#if (uartDebug_SS2_PIN)
    #define uartDebug_SS2_HSIOM_REG     (*(reg32 *) uartDebug_spi_ss2__0__HSIOM)
    #define uartDebug_SS2_HSIOM_PTR     ( (reg32 *) uartDebug_spi_ss2__0__HSIOM)
    
    #define uartDebug_SS2_HSIOM_MASK     (uartDebug_spi_ss2__0__HSIOM_MASK)
    #define uartDebug_SS2_HSIOM_POS      (uartDebug_spi_ss2__0__HSIOM_SHIFT)
    #define uartDebug_SS2_HSIOM_SEL_GPIO (uartDebug_spi_ss2__0__HSIOM_GPIO)
    #define uartDebug_SS2_HSIOM_SEL_I2C  (uartDebug_spi_ss2__0__HSIOM_I2C)
    #define uartDebug_SS2_HSIOM_SEL_SPI  (uartDebug_spi_ss2__0__HSIOM_SPI)
#endif /* (uartDebug_SS2_PIN) */

#if (uartDebug_SS3_PIN)
    #define uartDebug_SS3_HSIOM_REG     (*(reg32 *) uartDebug_spi_ss3__0__HSIOM)
    #define uartDebug_SS3_HSIOM_PTR     ( (reg32 *) uartDebug_spi_ss3__0__HSIOM)
    
    #define uartDebug_SS3_HSIOM_MASK     (uartDebug_spi_ss3__0__HSIOM_MASK)
    #define uartDebug_SS3_HSIOM_POS      (uartDebug_spi_ss3__0__HSIOM_SHIFT)
    #define uartDebug_SS3_HSIOM_SEL_GPIO (uartDebug_spi_ss3__0__HSIOM_GPIO)
    #define uartDebug_SS3_HSIOM_SEL_I2C  (uartDebug_spi_ss3__0__HSIOM_I2C)
    #define uartDebug_SS3_HSIOM_SEL_SPI  (uartDebug_spi_ss3__0__HSIOM_SPI)
#endif /* (uartDebug_SS3_PIN) */

#if (uartDebug_I2C_PINS)
    #define uartDebug_SCL_HSIOM_REG  (*(reg32 *) uartDebug_scl__0__HSIOM)
    #define uartDebug_SCL_HSIOM_PTR  ( (reg32 *) uartDebug_scl__0__HSIOM)
    
    #define uartDebug_SCL_HSIOM_MASK     (uartDebug_scl__0__HSIOM_MASK)
    #define uartDebug_SCL_HSIOM_POS      (uartDebug_scl__0__HSIOM_SHIFT)
    #define uartDebug_SCL_HSIOM_SEL_GPIO (uartDebug_sda__0__HSIOM_GPIO)
    #define uartDebug_SCL_HSIOM_SEL_I2C  (uartDebug_sda__0__HSIOM_I2C)
    
    #define uartDebug_SDA_HSIOM_REG  (*(reg32 *) uartDebug_sda__0__HSIOM)
    #define uartDebug_SDA_HSIOM_PTR  ( (reg32 *) uartDebug_sda__0__HSIOM)
    
    #define uartDebug_SDA_HSIOM_MASK     (uartDebug_sda__0__HSIOM_MASK)
    #define uartDebug_SDA_HSIOM_POS      (uartDebug_sda__0__HSIOM_SHIFT)
    #define uartDebug_SDA_HSIOM_SEL_GPIO (uartDebug_sda__0__HSIOM_GPIO)
    #define uartDebug_SDA_HSIOM_SEL_I2C  (uartDebug_sda__0__HSIOM_I2C)
#endif /* (uartDebug_I2C_PINS) */

#if (uartDebug_SPI_SLAVE_PINS)
    #define uartDebug_SCLK_S_HSIOM_REG   (*(reg32 *) uartDebug_sclk_s__0__HSIOM)
    #define uartDebug_SCLK_S_HSIOM_PTR   ( (reg32 *) uartDebug_sclk_s__0__HSIOM)
    
    #define uartDebug_SCLK_S_HSIOM_MASK      (uartDebug_sclk_s__0__HSIOM_MASK)
    #define uartDebug_SCLK_S_HSIOM_POS       (uartDebug_sclk_s__0__HSIOM_SHIFT)
    #define uartDebug_SCLK_S_HSIOM_SEL_GPIO  (uartDebug_sclk_s__0__HSIOM_GPIO)
    #define uartDebug_SCLK_S_HSIOM_SEL_SPI   (uartDebug_sclk_s__0__HSIOM_SPI)
    
    #define uartDebug_SS0_S_HSIOM_REG    (*(reg32 *) uartDebug_ss0_s__0__HSIOM)
    #define uartDebug_SS0_S_HSIOM_PTR    ( (reg32 *) uartDebug_ss0_s__0__HSIOM)
    
    #define uartDebug_SS0_S_HSIOM_MASK       (uartDebug_ss0_s__0__HSIOM_MASK)
    #define uartDebug_SS0_S_HSIOM_POS        (uartDebug_ss0_s__0__HSIOM_SHIFT)
    #define uartDebug_SS0_S_HSIOM_SEL_GPIO   (uartDebug_ss0_s__0__HSIOM_GPIO)  
    #define uartDebug_SS0_S_HSIOM_SEL_SPI    (uartDebug_ss0_s__0__HSIOM_SPI)
#endif /* (uartDebug_SPI_SLAVE_PINS) */

#if (uartDebug_SPI_SLAVE_MOSI_PIN)
    #define uartDebug_MOSI_S_HSIOM_REG   (*(reg32 *) uartDebug_mosi_s__0__HSIOM)
    #define uartDebug_MOSI_S_HSIOM_PTR   ( (reg32 *) uartDebug_mosi_s__0__HSIOM)
    
    #define uartDebug_MOSI_S_HSIOM_MASK      (uartDebug_mosi_s__0__HSIOM_MASK)
    #define uartDebug_MOSI_S_HSIOM_POS       (uartDebug_mosi_s__0__HSIOM_SHIFT)
    #define uartDebug_MOSI_S_HSIOM_SEL_GPIO  (uartDebug_mosi_s__0__HSIOM_GPIO)
    #define uartDebug_MOSI_S_HSIOM_SEL_SPI   (uartDebug_mosi_s__0__HSIOM_SPI)
#endif /* (uartDebug_SPI_SLAVE_MOSI_PIN) */

#if (uartDebug_SPI_SLAVE_MISO_PIN)
    #define uartDebug_MISO_S_HSIOM_REG   (*(reg32 *) uartDebug_miso_s__0__HSIOM)
    #define uartDebug_MISO_S_HSIOM_PTR   ( (reg32 *) uartDebug_miso_s__0__HSIOM)
    
    #define uartDebug_MISO_S_HSIOM_MASK      (uartDebug_miso_s__0__HSIOM_MASK)
    #define uartDebug_MISO_S_HSIOM_POS       (uartDebug_miso_s__0__HSIOM_SHIFT)
    #define uartDebug_MISO_S_HSIOM_SEL_GPIO  (uartDebug_miso_s__0__HSIOM_GPIO)
    #define uartDebug_MISO_S_HSIOM_SEL_SPI   (uartDebug_miso_s__0__HSIOM_SPI)
#endif /* (uartDebug_SPI_SLAVE_MISO_PIN) */

#if (uartDebug_SPI_MASTER_MISO_PIN)
    #define uartDebug_MISO_M_HSIOM_REG   (*(reg32 *) uartDebug_miso_m__0__HSIOM)
    #define uartDebug_MISO_M_HSIOM_PTR   ( (reg32 *) uartDebug_miso_m__0__HSIOM)
    
    #define uartDebug_MISO_M_HSIOM_MASK      (uartDebug_miso_m__0__HSIOM_MASK)
    #define uartDebug_MISO_M_HSIOM_POS       (uartDebug_miso_m__0__HSIOM_SHIFT)
    #define uartDebug_MISO_M_HSIOM_SEL_GPIO  (uartDebug_miso_m__0__HSIOM_GPIO)
    #define uartDebug_MISO_M_HSIOM_SEL_SPI   (uartDebug_miso_m__0__HSIOM_SPI)
#endif /* (uartDebug_SPI_MASTER_MISO_PIN) */

#if (uartDebug_SPI_MASTER_MOSI_PIN)
    #define uartDebug_MOSI_M_HSIOM_REG   (*(reg32 *) uartDebug_mosi_m__0__HSIOM)
    #define uartDebug_MOSI_M_HSIOM_PTR   ( (reg32 *) uartDebug_mosi_m__0__HSIOM)
    
    #define uartDebug_MOSI_M_HSIOM_MASK      (uartDebug_mosi_m__0__HSIOM_MASK)
    #define uartDebug_MOSI_M_HSIOM_POS       (uartDebug_mosi_m__0__HSIOM_SHIFT)
    #define uartDebug_MOSI_M_HSIOM_SEL_GPIO  (uartDebug_mosi_m__0__HSIOM_GPIO)
    #define uartDebug_MOSI_M_HSIOM_SEL_SPI   (uartDebug_mosi_m__0__HSIOM_SPI)
#endif /* (uartDebug_SPI_MASTER_MOSI_PIN) */

#if (uartDebug_SPI_MASTER_SCLK_PIN)
    #define uartDebug_SCLK_M_HSIOM_REG   (*(reg32 *) uartDebug_sclk_m__0__HSIOM)
    #define uartDebug_SCLK_M_HSIOM_PTR   ( (reg32 *) uartDebug_sclk_m__0__HSIOM)
    
    #define uartDebug_SCLK_M_HSIOM_MASK      (uartDebug_sclk_m__0__HSIOM_MASK)
    #define uartDebug_SCLK_M_HSIOM_POS       (uartDebug_sclk_m__0__HSIOM_SHIFT)
    #define uartDebug_SCLK_M_HSIOM_SEL_GPIO  (uartDebug_sclk_m__0__HSIOM_GPIO)
    #define uartDebug_SCLK_M_HSIOM_SEL_SPI   (uartDebug_sclk_m__0__HSIOM_SPI)
#endif /* (uartDebug_SPI_MASTER_SCLK_PIN) */

#if (uartDebug_SPI_MASTER_SS0_PIN)
    #define uartDebug_SS0_M_HSIOM_REG    (*(reg32 *) uartDebug_ss0_m__0__HSIOM)
    #define uartDebug_SS0_M_HSIOM_PTR    ( (reg32 *) uartDebug_ss0_m__0__HSIOM)
    
    #define uartDebug_SS0_M_HSIOM_MASK       (uartDebug_ss0_m__0__HSIOM_MASK)
    #define uartDebug_SS0_M_HSIOM_POS        (uartDebug_ss0_m__0__HSIOM_SHIFT)
    #define uartDebug_SS0_M_HSIOM_SEL_GPIO   (uartDebug_ss0_m__0__HSIOM_GPIO)
    #define uartDebug_SS0_M_HSIOM_SEL_SPI    (uartDebug_ss0_m__0__HSIOM_SPI)
#endif /* (uartDebug_SPI_MASTER_SS0_PIN) */

#if (uartDebug_SPI_MASTER_SS1_PIN)
    #define uartDebug_SS1_M_HSIOM_REG    (*(reg32 *) uartDebug_ss1_m__0__HSIOM)
    #define uartDebug_SS1_M_HSIOM_PTR    ( (reg32 *) uartDebug_ss1_m__0__HSIOM)
    
    #define uartDebug_SS1_M_HSIOM_MASK       (uartDebug_ss1_m__0__HSIOM_MASK)
    #define uartDebug_SS1_M_HSIOM_POS        (uartDebug_ss1_m__0__HSIOM_SHIFT)
    #define uartDebug_SS1_M_HSIOM_SEL_GPIO   (uartDebug_ss1_m__0__HSIOM_GPIO)
    #define uartDebug_SS1_M_HSIOM_SEL_SPI    (uartDebug_ss1_m__0__HSIOM_SPI)
#endif /* (uartDebug_SPI_MASTER_SS1_PIN) */

#if (uartDebug_SPI_MASTER_SS2_PIN)
    #define uartDebug_SS2_M_HSIOM_REG    (*(reg32 *) uartDebug_ss2_m__0__HSIOM)
    #define uartDebug_SS2_M_HSIOM_PTR    ( (reg32 *) uartDebug_ss2_m__0__HSIOM)
    
    #define uartDebug_SS2_M_HSIOM_MASK       (uartDebug_ss2_m__0__HSIOM_MASK)
    #define uartDebug_SS2_M_HSIOM_POS        (uartDebug_ss2_m__0__HSIOM_SHIFT)
    #define uartDebug_SS2_M_HSIOM_SEL_GPIO   (uartDebug_ss2_m__0__HSIOM_GPIO)
    #define uartDebug_SS2_M_HSIOM_SEL_SPI    (uartDebug_ss2_m__0__HSIOM_SPI)
#endif /* (uartDebug_SPI_MASTER_SS2_PIN) */

#if (uartDebug_SPI_MASTER_SS3_PIN)
    #define uartDebug_SS3_M_HSIOM_REG    (*(reg32 *) uartDebug_ss3_m__0__HSIOM)
    #define uartDebug_SS3_M_HSIOM_PTR    ( (reg32 *) uartDebug_ss3_m__0__HSIOM)
    
    #define uartDebug_SS3_M_HSIOM_MASK      (uartDebug_ss3_m__0__HSIOM_MASK)
    #define uartDebug_SS3_M_HSIOM_POS       (uartDebug_ss3_m__0__HSIOM_SHIFT)
    #define uartDebug_SS3_M_HSIOM_SEL_GPIO  (uartDebug_ss3_m__0__HSIOM_GPIO)
    #define uartDebug_SS3_M_HSIOM_SEL_SPI   (uartDebug_ss3_m__0__HSIOM_SPI)
#endif /* (uartDebug_SPI_MASTER_SS3_PIN) */

#if (uartDebug_UART_RX_PIN)
    #define uartDebug_RX_HSIOM_REG   (*(reg32 *) uartDebug_rx__0__HSIOM)
    #define uartDebug_RX_HSIOM_PTR   ( (reg32 *) uartDebug_rx__0__HSIOM)
    
    #define uartDebug_RX_HSIOM_MASK      (uartDebug_rx__0__HSIOM_MASK)
    #define uartDebug_RX_HSIOM_POS       (uartDebug_rx__0__HSIOM_SHIFT)
    #define uartDebug_RX_HSIOM_SEL_GPIO  (uartDebug_rx__0__HSIOM_GPIO)
    #define uartDebug_RX_HSIOM_SEL_UART  (uartDebug_rx__0__HSIOM_UART)
#endif /* (uartDebug_UART_RX_PIN) */

#if (uartDebug_UART_RX_WAKE_PIN)
    #define uartDebug_RX_WAKE_HSIOM_REG   (*(reg32 *) uartDebug_rx_wake__0__HSIOM)
    #define uartDebug_RX_WAKE_HSIOM_PTR   ( (reg32 *) uartDebug_rx_wake__0__HSIOM)
    
    #define uartDebug_RX_WAKE_HSIOM_MASK      (uartDebug_rx_wake__0__HSIOM_MASK)
    #define uartDebug_RX_WAKE_HSIOM_POS       (uartDebug_rx_wake__0__HSIOM_SHIFT)
    #define uartDebug_RX_WAKE_HSIOM_SEL_GPIO  (uartDebug_rx_wake__0__HSIOM_GPIO)
    #define uartDebug_RX_WAKE_HSIOM_SEL_UART  (uartDebug_rx_wake__0__HSIOM_UART)
#endif /* (uartDebug_UART_WAKE_RX_PIN) */

#if (uartDebug_UART_CTS_PIN)
    #define uartDebug_CTS_HSIOM_REG   (*(reg32 *) uartDebug_cts__0__HSIOM)
    #define uartDebug_CTS_HSIOM_PTR   ( (reg32 *) uartDebug_cts__0__HSIOM)
    
    #define uartDebug_CTS_HSIOM_MASK      (uartDebug_cts__0__HSIOM_MASK)
    #define uartDebug_CTS_HSIOM_POS       (uartDebug_cts__0__HSIOM_SHIFT)
    #define uartDebug_CTS_HSIOM_SEL_GPIO  (uartDebug_cts__0__HSIOM_GPIO)
    #define uartDebug_CTS_HSIOM_SEL_UART  (uartDebug_cts__0__HSIOM_UART)
#endif /* (uartDebug_UART_CTS_PIN) */

#if (uartDebug_UART_TX_PIN)
    #define uartDebug_TX_HSIOM_REG   (*(reg32 *) uartDebug_tx__0__HSIOM)
    #define uartDebug_TX_HSIOM_PTR   ( (reg32 *) uartDebug_tx__0__HSIOM)
    
    #define uartDebug_TX_HSIOM_MASK      (uartDebug_tx__0__HSIOM_MASK)
    #define uartDebug_TX_HSIOM_POS       (uartDebug_tx__0__HSIOM_SHIFT)
    #define uartDebug_TX_HSIOM_SEL_GPIO  (uartDebug_tx__0__HSIOM_GPIO)
    #define uartDebug_TX_HSIOM_SEL_UART  (uartDebug_tx__0__HSIOM_UART)
#endif /* (uartDebug_UART_TX_PIN) */

#if (uartDebug_UART_RX_TX_PIN)
    #define uartDebug_RX_TX_HSIOM_REG   (*(reg32 *) uartDebug_rx_tx__0__HSIOM)
    #define uartDebug_RX_TX_HSIOM_PTR   ( (reg32 *) uartDebug_rx_tx__0__HSIOM)
    
    #define uartDebug_RX_TX_HSIOM_MASK      (uartDebug_rx_tx__0__HSIOM_MASK)
    #define uartDebug_RX_TX_HSIOM_POS       (uartDebug_rx_tx__0__HSIOM_SHIFT)
    #define uartDebug_RX_TX_HSIOM_SEL_GPIO  (uartDebug_rx_tx__0__HSIOM_GPIO)
    #define uartDebug_RX_TX_HSIOM_SEL_UART  (uartDebug_rx_tx__0__HSIOM_UART)
#endif /* (uartDebug_UART_RX_TX_PIN) */

#if (uartDebug_UART_RTS_PIN)
    #define uartDebug_RTS_HSIOM_REG      (*(reg32 *) uartDebug_rts__0__HSIOM)
    #define uartDebug_RTS_HSIOM_PTR      ( (reg32 *) uartDebug_rts__0__HSIOM)
    
    #define uartDebug_RTS_HSIOM_MASK     (uartDebug_rts__0__HSIOM_MASK)
    #define uartDebug_RTS_HSIOM_POS      (uartDebug_rts__0__HSIOM_SHIFT)    
    #define uartDebug_RTS_HSIOM_SEL_GPIO (uartDebug_rts__0__HSIOM_GPIO)
    #define uartDebug_RTS_HSIOM_SEL_UART (uartDebug_rts__0__HSIOM_UART)    
#endif /* (uartDebug_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* HSIOM switch values. */ 
#define uartDebug_HSIOM_DEF_SEL      (0x00u)
#define uartDebug_HSIOM_GPIO_SEL     (0x00u)
/* The HSIOM values provided below are valid only for uartDebug_CY_SCBIP_V0 
* and uartDebug_CY_SCBIP_V1. It is not recommended to use them for 
* uartDebug_CY_SCBIP_V2. Use pin name specific HSIOM constants provided 
* above instead for any SCB IP block version.
*/
#define uartDebug_HSIOM_UART_SEL     (0x09u)
#define uartDebug_HSIOM_I2C_SEL      (0x0Eu)
#define uartDebug_HSIOM_SPI_SEL      (0x0Fu)

/* Pins settings index. */
#define uartDebug_RX_WAKE_SDA_MOSI_PIN_INDEX   (0u)
#define uartDebug_RX_SDA_MOSI_PIN_INDEX       (0u)
#define uartDebug_TX_SCL_MISO_PIN_INDEX       (1u)
#define uartDebug_CTS_SCLK_PIN_INDEX       (2u)
#define uartDebug_RTS_SS0_PIN_INDEX       (3u)
#define uartDebug_SS1_PIN_INDEX                  (4u)
#define uartDebug_SS2_PIN_INDEX                  (5u)
#define uartDebug_SS3_PIN_INDEX                  (6u)

/* Pins settings mask. */
#define uartDebug_RX_WAKE_SDA_MOSI_PIN_MASK ((uint32) 0x01u << uartDebug_RX_WAKE_SDA_MOSI_PIN_INDEX)
#define uartDebug_RX_SDA_MOSI_PIN_MASK     ((uint32) 0x01u << uartDebug_RX_SDA_MOSI_PIN_INDEX)
#define uartDebug_TX_SCL_MISO_PIN_MASK     ((uint32) 0x01u << uartDebug_TX_SCL_MISO_PIN_INDEX)
#define uartDebug_CTS_SCLK_PIN_MASK     ((uint32) 0x01u << uartDebug_CTS_SCLK_PIN_INDEX)
#define uartDebug_RTS_SS0_PIN_MASK     ((uint32) 0x01u << uartDebug_RTS_SS0_PIN_INDEX)
#define uartDebug_SS1_PIN_MASK                ((uint32) 0x01u << uartDebug_SS1_PIN_INDEX)
#define uartDebug_SS2_PIN_MASK                ((uint32) 0x01u << uartDebug_SS2_PIN_INDEX)
#define uartDebug_SS3_PIN_MASK                ((uint32) 0x01u << uartDebug_SS3_PIN_INDEX)

/* Pin interrupt constants. */
#define uartDebug_INTCFG_TYPE_MASK           (0x03u)
#define uartDebug_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants. */
#define uartDebug_PIN_DM_ALG_HIZ  (0u)
#define uartDebug_PIN_DM_DIG_HIZ  (1u)
#define uartDebug_PIN_DM_OD_LO    (4u)
#define uartDebug_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define uartDebug_DM_MASK    (0x7u)
#define uartDebug_DM_SIZE    (3u)
#define uartDebug_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) uartDebug_DM_MASK << (uartDebug_DM_SIZE * (pos)))) >> \
                                                              (uartDebug_DM_SIZE * (pos)) )

#if (uartDebug_TX_SCL_MISO_PIN)
    #define uartDebug_CHECK_TX_SCL_MISO_PIN_USED \
                (uartDebug_PIN_DM_ALG_HIZ != \
                    uartDebug_GET_P4_PIN_DM(uartDebug_uart_tx_i2c_scl_spi_miso_PC, \
                                                   uartDebug_uart_tx_i2c_scl_spi_miso_SHIFT))
#endif /* (uartDebug_TX_SCL_MISO_PIN) */

#if (uartDebug_RTS_SS0_PIN)
    #define uartDebug_CHECK_RTS_SS0_PIN_USED \
                (uartDebug_PIN_DM_ALG_HIZ != \
                    uartDebug_GET_P4_PIN_DM(uartDebug_uart_rts_spi_ss0_PC, \
                                                   uartDebug_uart_rts_spi_ss0_SHIFT))
#endif /* (uartDebug_RTS_SS0_PIN) */

/* Set bits-mask in register */
#define uartDebug_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define uartDebug_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define uartDebug_SET_HSIOM_SEL(reg, mask, pos, sel) uartDebug_SET_REGISTER_BITS(reg, mask, pos, sel)
#define uartDebug_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        uartDebug_SET_REGISTER_BITS(reg, mask, pos, intType)
#define uartDebug_SET_INP_DIS(reg, mask, val) uartDebug_SET_REGISTER_BIT(reg, mask, val)

/* uartDebug_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  uartDebug_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (uartDebug_CY_SCBIP_V0)
#if (uartDebug_I2C_PINS)
    #define uartDebug_SET_I2C_SCL_DR(val) uartDebug_scl_Write(val)

    #define uartDebug_SET_I2C_SCL_HSIOM_SEL(sel) \
                          uartDebug_SET_HSIOM_SEL(uartDebug_SCL_HSIOM_REG,  \
                                                         uartDebug_SCL_HSIOM_MASK, \
                                                         uartDebug_SCL_HSIOM_POS,  \
                                                         (sel))
    #define uartDebug_WAIT_SCL_SET_HIGH  (0u == uartDebug_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (uartDebug_RX_WAKE_SDA_MOSI_PIN)
    #define uartDebug_SET_I2C_SCL_DR(val) \
                            uartDebug_uart_rx_wake_i2c_sda_spi_mosi_Write(val)

    #define uartDebug_SET_I2C_SCL_HSIOM_SEL(sel) \
                    uartDebug_SET_HSIOM_SEL(uartDebug_RX_WAKE_SDA_MOSI_HSIOM_REG,  \
                                                   uartDebug_RX_WAKE_SDA_MOSI_HSIOM_MASK, \
                                                   uartDebug_RX_WAKE_SDA_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define uartDebug_WAIT_SCL_SET_HIGH  (0u == uartDebug_uart_rx_wake_i2c_sda_spi_mosi_Read())

#elif (uartDebug_RX_SDA_MOSI_PIN)
    #define uartDebug_SET_I2C_SCL_DR(val) \
                            uartDebug_uart_rx_i2c_sda_spi_mosi_Write(val)


    #define uartDebug_SET_I2C_SCL_HSIOM_SEL(sel) \
                            uartDebug_SET_HSIOM_SEL(uartDebug_RX_SDA_MOSI_HSIOM_REG,  \
                                                           uartDebug_RX_SDA_MOSI_HSIOM_MASK, \
                                                           uartDebug_RX_SDA_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define uartDebug_WAIT_SCL_SET_HIGH  (0u == uartDebug_uart_rx_i2c_sda_spi_mosi_Read())

#else
    #define uartDebug_SET_I2C_SCL_DR(val)        do{ /* Does nothing */ }while(0)
    #define uartDebug_SET_I2C_SCL_HSIOM_SEL(sel) do{ /* Does nothing */ }while(0)

    #define uartDebug_WAIT_SCL_SET_HIGH  (0u)
#endif /* (uartDebug_I2C_PINS) */

/* SCB I2C: sda signal */
#if (uartDebug_I2C_PINS)
    #define uartDebug_WAIT_SDA_SET_HIGH  (0u == uartDebug_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (uartDebug_TX_SCL_MISO_PIN)
    #define uartDebug_WAIT_SDA_SET_HIGH  (0u == uartDebug_uart_tx_i2c_scl_spi_miso_Read())
#else
    #define uartDebug_WAIT_SDA_SET_HIGH  (0u)
#endif /* (uartDebug_MOSI_SCL_RX_PIN) */
#endif /* (uartDebug_CY_SCBIP_V0) */

/* Clear UART wakeup source */
#if (uartDebug_RX_SDA_MOSI_PIN)
    #define uartDebug_CLEAR_UART_RX_WAKE_INTR        do{ /* Does nothing */ }while(0)
    
#elif (uartDebug_RX_WAKE_SDA_MOSI_PIN)
    #define uartDebug_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) uartDebug_uart_rx_wake_i2c_sda_spi_mosi_ClearInterrupt(); \
            }while(0)

#elif(uartDebug_UART_RX_WAKE_PIN)
    #define uartDebug_CLEAR_UART_RX_WAKE_INTR \
            do{                                      \
                (void) uartDebug_rx_wake_ClearInterrupt(); \
            }while(0)
#else
#endif /* (uartDebug_RX_SDA_MOSI_PIN) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define uartDebug_REMOVE_MOSI_SCL_RX_WAKE_PIN    uartDebug_REMOVE_RX_WAKE_SDA_MOSI_PIN
#define uartDebug_REMOVE_MOSI_SCL_RX_PIN         uartDebug_REMOVE_RX_SDA_MOSI_PIN
#define uartDebug_REMOVE_MISO_SDA_TX_PIN         uartDebug_REMOVE_TX_SCL_MISO_PIN
#ifndef uartDebug_REMOVE_SCLK_PIN
#define uartDebug_REMOVE_SCLK_PIN                uartDebug_REMOVE_CTS_SCLK_PIN
#endif /* uartDebug_REMOVE_SCLK_PIN */
#ifndef uartDebug_REMOVE_SS0_PIN
#define uartDebug_REMOVE_SS0_PIN                 uartDebug_REMOVE_RTS_SS0_PIN
#endif /* uartDebug_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define uartDebug_MOSI_SCL_RX_WAKE_PIN   uartDebug_RX_WAKE_SDA_MOSI_PIN
#define uartDebug_MOSI_SCL_RX_PIN        uartDebug_RX_SDA_MOSI_PIN
#define uartDebug_MISO_SDA_TX_PIN        uartDebug_TX_SCL_MISO_PIN
#ifndef uartDebug_SCLK_PIN
#define uartDebug_SCLK_PIN               uartDebug_CTS_SCLK_PIN
#endif /* uartDebug_SCLK_PIN */
#ifndef uartDebug_SS0_PIN
#define uartDebug_SS0_PIN                uartDebug_RTS_SS0_PIN
#endif /* uartDebug_SS0_PIN */

#if (uartDebug_MOSI_SCL_RX_WAKE_PIN)
    #define uartDebug_MOSI_SCL_RX_WAKE_HSIOM_REG     uartDebug_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define uartDebug_MOSI_SCL_RX_WAKE_HSIOM_PTR     uartDebug_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define uartDebug_MOSI_SCL_RX_WAKE_HSIOM_MASK    uartDebug_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define uartDebug_MOSI_SCL_RX_WAKE_HSIOM_POS     uartDebug_RX_WAKE_SDA_MOSI_HSIOM_REG

    #define uartDebug_MOSI_SCL_RX_WAKE_INTCFG_REG    uartDebug_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define uartDebug_MOSI_SCL_RX_WAKE_INTCFG_PTR    uartDebug_RX_WAKE_SDA_MOSI_HSIOM_REG

    #define uartDebug_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   uartDebug_RX_WAKE_SDA_MOSI_HSIOM_REG
    #define uartDebug_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  uartDebug_RX_WAKE_SDA_MOSI_HSIOM_REG
#endif /* (uartDebug_RX_WAKE_SDA_MOSI_PIN) */

#if (uartDebug_MOSI_SCL_RX_PIN)
    #define uartDebug_MOSI_SCL_RX_HSIOM_REG      uartDebug_RX_SDA_MOSI_HSIOM_REG
    #define uartDebug_MOSI_SCL_RX_HSIOM_PTR      uartDebug_RX_SDA_MOSI_HSIOM_PTR
    #define uartDebug_MOSI_SCL_RX_HSIOM_MASK     uartDebug_RX_SDA_MOSI_HSIOM_MASK
    #define uartDebug_MOSI_SCL_RX_HSIOM_POS      uartDebug_RX_SDA_MOSI_HSIOM_POS
#endif /* (uartDebug_MOSI_SCL_RX_PIN) */

#if (uartDebug_MISO_SDA_TX_PIN)
    #define uartDebug_MISO_SDA_TX_HSIOM_REG      uartDebug_TX_SCL_MISO_HSIOM_REG
    #define uartDebug_MISO_SDA_TX_HSIOM_PTR      uartDebug_TX_SCL_MISO_HSIOM_REG
    #define uartDebug_MISO_SDA_TX_HSIOM_MASK     uartDebug_TX_SCL_MISO_HSIOM_REG
    #define uartDebug_MISO_SDA_TX_HSIOM_POS      uartDebug_TX_SCL_MISO_HSIOM_REG
#endif /* (uartDebug_MISO_SDA_TX_PIN_PIN) */

#if (uartDebug_SCLK_PIN)
    #ifndef uartDebug_SCLK_HSIOM_REG
    #define uartDebug_SCLK_HSIOM_REG     uartDebug_CTS_SCLK_HSIOM_REG
    #define uartDebug_SCLK_HSIOM_PTR     uartDebug_CTS_SCLK_HSIOM_PTR
    #define uartDebug_SCLK_HSIOM_MASK    uartDebug_CTS_SCLK_HSIOM_MASK
    #define uartDebug_SCLK_HSIOM_POS     uartDebug_CTS_SCLK_HSIOM_POS
    #endif /* uartDebug_SCLK_HSIOM_REG */
#endif /* (uartDebug_SCLK_PIN) */

#if (uartDebug_SS0_PIN)
    #ifndef uartDebug_SS0_HSIOM_REG
    #define uartDebug_SS0_HSIOM_REG      uartDebug_RTS_SS0_HSIOM_REG
    #define uartDebug_SS0_HSIOM_PTR      uartDebug_RTS_SS0_HSIOM_PTR
    #define uartDebug_SS0_HSIOM_MASK     uartDebug_RTS_SS0_HSIOM_MASK
    #define uartDebug_SS0_HSIOM_POS      uartDebug_RTS_SS0_HSIOM_POS
    #endif /* uartDebug_SS0_HSIOM_REG */
#endif /* (uartDebug_SS0_PIN) */

#define uartDebug_MOSI_SCL_RX_WAKE_PIN_INDEX uartDebug_RX_WAKE_SDA_MOSI_PIN_INDEX
#define uartDebug_MOSI_SCL_RX_PIN_INDEX      uartDebug_RX_SDA_MOSI_PIN_INDEX
#define uartDebug_MISO_SDA_TX_PIN_INDEX      uartDebug_TX_SCL_MISO_PIN_INDEX
#ifndef uartDebug_SCLK_PIN_INDEX
#define uartDebug_SCLK_PIN_INDEX             uartDebug_CTS_SCLK_PIN_INDEX
#endif /* uartDebug_SCLK_PIN_INDEX */
#ifndef uartDebug_SS0_PIN_INDEX
#define uartDebug_SS0_PIN_INDEX              uartDebug_RTS_SS0_PIN_INDEX
#endif /* uartDebug_SS0_PIN_INDEX */

#define uartDebug_MOSI_SCL_RX_WAKE_PIN_MASK uartDebug_RX_WAKE_SDA_MOSI_PIN_MASK
#define uartDebug_MOSI_SCL_RX_PIN_MASK      uartDebug_RX_SDA_MOSI_PIN_MASK
#define uartDebug_MISO_SDA_TX_PIN_MASK      uartDebug_TX_SCL_MISO_PIN_MASK
#ifndef uartDebug_SCLK_PIN_MASK
#define uartDebug_SCLK_PIN_MASK             uartDebug_CTS_SCLK_PIN_MASK
#endif /* uartDebug_SCLK_PIN_MASK */
#ifndef uartDebug_SS0_PIN_MASK
#define uartDebug_SS0_PIN_MASK              uartDebug_RTS_SS0_PIN_MASK
#endif /* uartDebug_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_uartDebug_H) */


/* [] END OF FILE */
