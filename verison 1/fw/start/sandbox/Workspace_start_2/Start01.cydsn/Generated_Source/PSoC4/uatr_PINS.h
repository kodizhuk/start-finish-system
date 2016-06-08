/*******************************************************************************
* File Name: uatr_PINS.h
* Version 3.10
*
* Description:
*  This file provides constants and parameter values for the pin components
*  buried into SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_PINS_uatr_H)
#define CY_SCB_PINS_uatr_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define uatr_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define uatr_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define uatr_REMOVE_TX_SDA_MISO_PIN      (1u)
#define uatr_REMOVE_SCLK_PIN      (1u)
#define uatr_REMOVE_SS0_PIN      (1u)
#define uatr_REMOVE_SS1_PIN                 (1u)
#define uatr_REMOVE_SS2_PIN                 (1u)
#define uatr_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define uatr_REMOVE_I2C_PINS                (1u)
#define uatr_REMOVE_SPI_MASTER_PINS         (1u)
#define uatr_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define uatr_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define uatr_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define uatr_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define uatr_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define uatr_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define uatr_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define uatr_REMOVE_SPI_SLAVE_PINS          (1u)
#define uatr_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define uatr_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define uatr_REMOVE_UART_TX_PIN             (0u)
#define uatr_REMOVE_UART_RX_TX_PIN          (1u)
#define uatr_REMOVE_UART_RX_PIN             (0u)
#define uatr_REMOVE_UART_RX_WAKE_PIN        (1u)
#define uatr_REMOVE_UART_RTS_PIN            (1u)
#define uatr_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define uatr_RX_WAKE_SCL_MOSI_PIN (0u == uatr_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define uatr_RX_SCL_MOSI_PIN     (0u == uatr_REMOVE_RX_SCL_MOSI_PIN)
#define uatr_TX_SDA_MISO_PIN     (0u == uatr_REMOVE_TX_SDA_MISO_PIN)
#define uatr_SCLK_PIN     (0u == uatr_REMOVE_SCLK_PIN)
#define uatr_SS0_PIN     (0u == uatr_REMOVE_SS0_PIN)
#define uatr_SS1_PIN                (0u == uatr_REMOVE_SS1_PIN)
#define uatr_SS2_PIN                (0u == uatr_REMOVE_SS2_PIN)
#define uatr_SS3_PIN                (0u == uatr_REMOVE_SS3_PIN)

/* Mode defined pins */
#define uatr_I2C_PINS               (0u == uatr_REMOVE_I2C_PINS)
#define uatr_SPI_MASTER_PINS        (0u == uatr_REMOVE_SPI_MASTER_PINS)
#define uatr_SPI_MASTER_SCLK_PIN    (0u == uatr_REMOVE_SPI_MASTER_SCLK_PIN)
#define uatr_SPI_MASTER_MOSI_PIN    (0u == uatr_REMOVE_SPI_MASTER_MOSI_PIN)
#define uatr_SPI_MASTER_MISO_PIN    (0u == uatr_REMOVE_SPI_MASTER_MISO_PIN)
#define uatr_SPI_MASTER_SS0_PIN     (0u == uatr_REMOVE_SPI_MASTER_SS0_PIN)
#define uatr_SPI_MASTER_SS1_PIN     (0u == uatr_REMOVE_SPI_MASTER_SS1_PIN)
#define uatr_SPI_MASTER_SS2_PIN     (0u == uatr_REMOVE_SPI_MASTER_SS2_PIN)
#define uatr_SPI_MASTER_SS3_PIN     (0u == uatr_REMOVE_SPI_MASTER_SS3_PIN)
#define uatr_SPI_SLAVE_PINS         (0u == uatr_REMOVE_SPI_SLAVE_PINS)
#define uatr_SPI_SLAVE_MOSI_PIN     (0u == uatr_REMOVE_SPI_SLAVE_MOSI_PIN)
#define uatr_SPI_SLAVE_MISO_PIN     (0u == uatr_REMOVE_SPI_SLAVE_MISO_PIN)
#define uatr_UART_TX_PIN            (0u == uatr_REMOVE_UART_TX_PIN)
#define uatr_UART_RX_TX_PIN         (0u == uatr_REMOVE_UART_RX_TX_PIN)
#define uatr_UART_RX_PIN            (0u == uatr_REMOVE_UART_RX_PIN)
#define uatr_UART_RX_WAKE_PIN       (0u == uatr_REMOVE_UART_RX_WAKE_PIN)
#define uatr_UART_RTS_PIN           (0u == uatr_REMOVE_UART_RTS_PIN)
#define uatr_UART_CTS_PIN           (0u == uatr_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (uatr_RX_WAKE_SCL_MOSI_PIN)
    #include "uatr_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (uatr_RX_SCL_MOSI) */

#if (uatr_RX_SCL_MOSI_PIN)
    #include "uatr_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (uatr_RX_SCL_MOSI) */

#if (uatr_TX_SDA_MISO_PIN)
    #include "uatr_uart_tx_i2c_sda_spi_miso.h"
#endif /* (uatr_TX_SDA_MISO) */

#if (uatr_SCLK_PIN)
    #include "uatr_spi_sclk.h"
#endif /* (uatr_SCLK) */

#if (uatr_SS0_PIN)
    #include "uatr_spi_ss0.h"
#endif /* (uatr_SS0_PIN) */

#if (uatr_SS1_PIN)
    #include "uatr_spi_ss1.h"
#endif /* (uatr_SS1_PIN) */

#if (uatr_SS2_PIN)
    #include "uatr_spi_ss2.h"
#endif /* (uatr_SS2_PIN) */

#if (uatr_SS3_PIN)
    #include "uatr_spi_ss3.h"
#endif /* (uatr_SS3_PIN) */

#if (uatr_I2C_PINS)
    #include "uatr_scl.h"
    #include "uatr_sda.h"
#endif /* (uatr_I2C_PINS) */

#if (uatr_SPI_MASTER_PINS)
#if (uatr_SPI_MASTER_SCLK_PIN)
    #include "uatr_sclk_m.h"
#endif /* (uatr_SPI_MASTER_SCLK_PIN) */

#if (uatr_SPI_MASTER_MOSI_PIN)
    #include "uatr_mosi_m.h"
#endif /* (uatr_SPI_MASTER_MOSI_PIN) */

#if (uatr_SPI_MASTER_MISO_PIN)
    #include "uatr_miso_m.h"
#endif /*(uatr_SPI_MASTER_MISO_PIN) */
#endif /* (uatr_SPI_MASTER_PINS) */

#if (uatr_SPI_SLAVE_PINS)
    #include "uatr_sclk_s.h"
    #include "uatr_ss_s.h"

#if (uatr_SPI_SLAVE_MOSI_PIN)
    #include "uatr_mosi_s.h"
#endif /* (uatr_SPI_SLAVE_MOSI_PIN) */

#if (uatr_SPI_SLAVE_MISO_PIN)
    #include "uatr_miso_s.h"
#endif /*(uatr_SPI_SLAVE_MISO_PIN) */
#endif /* (uatr_SPI_SLAVE_PINS) */

#if (uatr_SPI_MASTER_SS0_PIN)
    #include "uatr_ss0_m.h"
#endif /* (uatr_SPI_MASTER_SS0_PIN) */

#if (uatr_SPI_MASTER_SS1_PIN)
    #include "uatr_ss1_m.h"
#endif /* (uatr_SPI_MASTER_SS1_PIN) */

#if (uatr_SPI_MASTER_SS2_PIN)
    #include "uatr_ss2_m.h"
#endif /* (uatr_SPI_MASTER_SS2_PIN) */

#if (uatr_SPI_MASTER_SS3_PIN)
    #include "uatr_ss3_m.h"
#endif /* (uatr_SPI_MASTER_SS3_PIN) */

#if (uatr_UART_TX_PIN)
    #include "uatr_tx.h"
#endif /* (uatr_UART_TX_PIN) */

#if (uatr_UART_RX_TX_PIN)
    #include "uatr_rx_tx.h"
#endif /* (uatr_UART_RX_TX_PIN) */

#if (uatr_UART_RX_PIN)
    #include "uatr_rx.h"
#endif /* (uatr_UART_RX_PIN) */

#if (uatr_UART_RX_WAKE_PIN)
    #include "uatr_rx_wake.h"
#endif /* (uatr_UART_RX_WAKE_PIN) */

#if (uatr_UART_RTS_PIN)
    #include "uatr_rts.h"
#endif /* (uatr_UART_RTS_PIN) */

#if (uatr_UART_CTS_PIN)
    #include "uatr_cts.h"
#endif /* (uatr_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (uatr_RX_WAKE_SCL_MOSI_PIN)
    #define uatr_RX_WAKE_SCL_MOSI_HSIOM_REG \
                            (*(reg32 *) uatr_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define uatr_RX_WAKE_SCL_MOSI_HSIOM_PTR \
                            ( (reg32 *) uatr_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define uatr_RX_WAKE_SCL_MOSI_HSIOM_MASK \
                            (uatr_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define uatr_RX_WAKE_SCL_MOSI_HSIOM_POS \
                            (uatr_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)

    #define uatr_RX_WAKE_SCL_MOSI_INTCFG_REG \
                            (*(reg32 *) uatr_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define uatr_RX_WAKE_SCL_MOSI_INTCFG_PTR \
                            ( (reg32 *) uatr_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define uatr_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (uatr_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define uatr_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK \
                            ((uint32) uatr_INTCFG_TYPE_MASK << \
                                      uatr_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#endif /* (uatr_RX_WAKE_SCL_MOSI_PIN) */

#if (uatr_RX_SCL_MOSI_PIN)
    #define uatr_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) uatr_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define uatr_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) uatr_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define uatr_RX_SCL_MOSI_HSIOM_MASK  (uatr_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define uatr_RX_SCL_MOSI_HSIOM_POS   (uatr_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
#endif /* (uatr_RX_SCL_MOSI_PIN) */

#if (uatr_TX_SDA_MISO_PIN)
    #define uatr_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) uatr_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define uatr_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) uatr_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define uatr_TX_SDA_MISO_HSIOM_MASK  (uatr_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define uatr_TX_SDA_MISO_HSIOM_POS   (uatr_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
#endif /* (uatr_TX_SDA_MISO_PIN) */

#if (uatr_SCLK_PIN)
    #define uatr_SCLK_HSIOM_REG   (*(reg32 *) uatr_spi_sclk__0__HSIOM)
    #define uatr_SCLK_HSIOM_PTR   ( (reg32 *) uatr_spi_sclk__0__HSIOM)
    #define uatr_SCLK_HSIOM_MASK  (uatr_spi_sclk__0__HSIOM_MASK)
    #define uatr_SCLK_HSIOM_POS   (uatr_spi_sclk__0__HSIOM_SHIFT)
#endif /* (uatr_SCLK_PIN) */

#if (uatr_SS0_PIN)
    #define uatr_SS0_HSIOM_REG   (*(reg32 *) uatr_spi_ss0__0__HSIOM)
    #define uatr_SS0_HSIOM_PTR   ( (reg32 *) uatr_spi_ss0__0__HSIOM)
    #define uatr_SS0_HSIOM_MASK  (uatr_spi_ss0__0__HSIOM_MASK)
    #define uatr_SS0_HSIOM_POS   (uatr_spi_ss0__0__HSIOM_SHIFT)
#endif /* (uatr_SS0_PIN) */

#if (uatr_SS1_PIN)
    #define uatr_SS1_HSIOM_REG      (*(reg32 *) uatr_spi_ss1__0__HSIOM)
    #define uatr_SS1_HSIOM_PTR      ( (reg32 *) uatr_spi_ss1__0__HSIOM)
    #define uatr_SS1_HSIOM_MASK     (uatr_spi_ss1__0__HSIOM_MASK)
    #define uatr_SS1_HSIOM_POS      (uatr_spi_ss1__0__HSIOM_SHIFT)
#endif /* (uatr_SS1_PIN) */

#if (uatr_SS2_PIN)
    #define uatr_SS2_HSIOM_REG     (*(reg32 *) uatr_spi_ss2__0__HSIOM)
    #define uatr_SS2_HSIOM_PTR     ( (reg32 *) uatr_spi_ss2__0__HSIOM)
    #define uatr_SS2_HSIOM_MASK    (uatr_spi_ss2__0__HSIOM_MASK)
    #define uatr_SS2_HSIOM_POS     (uatr_spi_ss2__0__HSIOM_SHIFT)
#endif /* (uatr_SS2_PIN) */

#if (uatr_SS3_PIN)
    #define uatr_SS3_HSIOM_REG     (*(reg32 *) uatr_spi_ss3__0__HSIOM)
    #define uatr_SS3_HSIOM_PTR     ( (reg32 *) uatr_spi_ss3__0__HSIOM)
    #define uatr_SS3_HSIOM_MASK    (uatr_spi_ss3__0__HSIOM_MASK)
    #define uatr_SS3_HSIOM_POS     (uatr_spi_ss3__0__HSIOM_SHIFT)
#endif /* (uatr_SS3_PIN) */

#if (uatr_I2C_PINS)
    #define uatr_SCL_HSIOM_REG     (*(reg32 *) uatr_scl__0__HSIOM)
    #define uatr_SCL_HSIOM_PTR     ( (reg32 *) uatr_scl__0__HSIOM)
    #define uatr_SCL_HSIOM_MASK    (uatr_scl__0__HSIOM_MASK)
    #define uatr_SCL_HSIOM_POS     (uatr_scl__0__HSIOM_SHIFT)

    #define uatr_SDA_HSIOM_REG     (*(reg32 *) uatr_sda__0__HSIOM)
    #define uatr_SDA_HSIOM_PTR     ( (reg32 *) uatr_sda__0__HSIOM)
    #define uatr_SDA_HSIOM_MASK    (uatr_sda__0__HSIOM_MASK)
    #define uatr_SDA_HSIOM_POS     (uatr_sda__0__HSIOM_SHIFT)
#endif /* (uatr_I2C_PINS) */

#if (uatr_SPI_MASTER_SCLK_PIN)
    #define uatr_SCLK_M_HSIOM_REG   (*(reg32 *) uatr_sclk_m__0__HSIOM)
    #define uatr_SCLK_M_HSIOM_PTR   ( (reg32 *) uatr_sclk_m__0__HSIOM)
    #define uatr_SCLK_M_HSIOM_MASK  (uatr_sclk_m__0__HSIOM_MASK)
    #define uatr_SCLK_M_HSIOM_POS   (uatr_sclk_m__0__HSIOM_SHIFT)
#endif /* (uatr_SPI_MASTER_SCLK_PIN) */

#if (uatr_SPI_MASTER_SS0_PIN)
    #define uatr_SS0_M_HSIOM_REG    (*(reg32 *) uatr_ss0_m__0__HSIOM)
    #define uatr_SS0_M_HSIOM_PTR    ( (reg32 *) uatr_ss0_m__0__HSIOM)
    #define uatr_SS0_M_HSIOM_MASK   (uatr_ss0_m__0__HSIOM_MASK)
    #define uatr_SS0_M_HSIOM_POS    (uatr_ss0_m__0__HSIOM_SHIFT)
#endif /* (uatr_SPI_MASTER_SS0_PIN) */

#if (uatr_SPI_MASTER_SS1_PIN)
    #define uatr_SS1_M_HSIOM_REG    (*(reg32 *) uatr_ss1_m__0__HSIOM)
    #define uatr_SS1_M_HSIOM_PTR    ( (reg32 *) uatr_ss1_m__0__HSIOM)
    #define uatr_SS1_M_HSIOM_MASK   (uatr_ss1_m__0__HSIOM_MASK)
    #define uatr_SS1_M_HSIOM_POS    (uatr_ss1_m__0__HSIOM_SHIFT)
#endif /* (uatr_SPI_MASTER_SS1_PIN) */

#if (uatr_SPI_MASTER_SS2_PIN)
    #define uatr_SS2_M_HSIOM_REG    (*(reg32 *) uatr_ss2_m__0__HSIOM)
    #define uatr_SS2_M_HSIOM_PTR    ( (reg32 *) uatr_ss2_m__0__HSIOM)
    #define uatr_SS2_M_HSIOM_MASK   (uatr_ss2_m__0__HSIOM_MASK)
    #define uatr_SS2_M_HSIOM_POS    (uatr_ss2_m__0__HSIOM_SHIFT)
#endif /* (uatr_SPI_MASTER_SS2_PIN) */

#if (uatr_SPI_MASTER_SS3_PIN)
    #define uatr_SS3_M_HSIOM_REG    (*(reg32 *) uatr_ss3_m__0__HSIOM)
    #define uatr_SS3_M_HSIOM_PTR    ( (reg32 *) uatr_ss3_m__0__HSIOM)
    #define uatr_SS3_M_HSIOM_MASK   (uatr_ss3_m__0__HSIOM_MASK)
    #define uatr_SS3_M_HSIOM_POS    (uatr_ss3_m__0__HSIOM_SHIFT)
#endif /* (uatr_SPI_MASTER_SS3_PIN) */

#if (uatr_UART_TX_PIN)
    #define uatr_TX_HSIOM_REG   (*(reg32 *) uatr_tx__0__HSIOM)
    #define uatr_TX_HSIOM_PTR   ( (reg32 *) uatr_tx_0__HSIOM)
    #define uatr_TX_HSIOM_MASK  (uatr_tx__0__HSIOM_MASK)
    #define uatr_TX_HSIOM_POS   (uatr_tx__0__HSIOM_SHIFT)
#endif /* (uatr_UART_TX_PIN) */

#if (uatr_UART_RTS_PIN)
    #define uatr_RTS_HSIOM_REG  (*(reg32 *) uatr_rts__0__HSIOM)
    #define uatr_RTS_HSIOM_PTR  ( (reg32 *) uatr_rts__0__HSIOM)
    #define uatr_RTS_HSIOM_MASK (uatr_rts__0__HSIOM_MASK)
    #define uatr_RTS_HSIOM_POS  (uatr_rts__0__HSIOM_SHIFT)
#endif /* (uatr_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constants */
#define uatr_HSIOM_DEF_SEL      (0x00u)
#define uatr_HSIOM_GPIO_SEL     (0x00u)
#define uatr_HSIOM_UART_SEL     (0x09u)
#define uatr_HSIOM_I2C_SEL      (0x0Eu)
#define uatr_HSIOM_SPI_SEL      (0x0Fu)

#define uatr_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define uatr_RX_SCL_MOSI_PIN_INDEX       (0u)
#define uatr_TX_SDA_MISO_PIN_INDEX       (1u)
#define uatr_SCLK_PIN_INDEX       (2u)
#define uatr_SS0_PIN_INDEX       (3u)
#define uatr_SS1_PIN_INDEX                  (4u)
#define uatr_SS2_PIN_INDEX                  (5u)
#define uatr_SS3_PIN_INDEX                  (6u)

#define uatr_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << uatr_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define uatr_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << uatr_RX_SCL_MOSI_PIN_INDEX)
#define uatr_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << uatr_TX_SDA_MISO_PIN_INDEX)
#define uatr_SCLK_PIN_MASK     ((uint32) 0x01u << uatr_SCLK_PIN_INDEX)
#define uatr_SS0_PIN_MASK     ((uint32) 0x01u << uatr_SS0_PIN_INDEX)
#define uatr_SS1_PIN_MASK                ((uint32) 0x01u << uatr_SS1_PIN_INDEX)
#define uatr_SS2_PIN_MASK                ((uint32) 0x01u << uatr_SS2_PIN_INDEX)
#define uatr_SS3_PIN_MASK                ((uint32) 0x01u << uatr_SS3_PIN_INDEX)

/* Pin interrupt constants */
#define uatr_INTCFG_TYPE_MASK           (0x03u)
#define uatr_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants */
#define uatr_PIN_DM_ALG_HIZ  (0u)
#define uatr_PIN_DM_DIG_HIZ  (1u)
#define uatr_PIN_DM_OD_LO    (4u)
#define uatr_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define uatr_DM_MASK    (0x7u)
#define uatr_DM_SIZE    (3)
#define uatr_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) uatr_DM_MASK << (uatr_DM_SIZE * (pos)))) >> \
                                                              (uatr_DM_SIZE * (pos)) )

#if (uatr_TX_SDA_MISO_PIN)
    #define uatr_CHECK_TX_SDA_MISO_PIN_USED \
                (uatr_PIN_DM_ALG_HIZ != \
                    uatr_GET_P4_PIN_DM(uatr_uart_tx_i2c_sda_spi_miso_PC, \
                                                   uatr_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (uatr_TX_SDA_MISO_PIN) */

#if (uatr_SS0_PIN)
    #define uatr_CHECK_SS0_PIN_USED \
                (uatr_PIN_DM_ALG_HIZ != \
                    uatr_GET_P4_PIN_DM(uatr_spi_ss0_PC, \
                                                   uatr_spi_ss0_SHIFT))
#endif /* (uatr_SS0_PIN) */

/* Set bits-mask in register */
#define uatr_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define uatr_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define uatr_SET_HSIOM_SEL(reg, mask, pos, sel) uatr_SET_REGISTER_BITS(reg, mask, pos, sel)
#define uatr_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        uatr_SET_REGISTER_BITS(reg, mask, pos, intType)
#define uatr_SET_INP_DIS(reg, mask, val) uatr_SET_REGISTER_BIT(reg, mask, val)

/* uatr_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  uatr_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (uatr_CY_SCBIP_V0)
#if (uatr_I2C_PINS)
    #define uatr_SET_I2C_SCL_DR(val) uatr_scl_Write(val)

    #define uatr_SET_I2C_SCL_HSIOM_SEL(sel) \
                          uatr_SET_HSIOM_SEL(uatr_SCL_HSIOM_REG,  \
                                                         uatr_SCL_HSIOM_MASK, \
                                                         uatr_SCL_HSIOM_POS,  \
                                                         (sel))
    #define uatr_WAIT_SCL_SET_HIGH  (0u == uatr_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (uatr_RX_WAKE_SCL_MOSI_PIN)
    #define uatr_SET_I2C_SCL_DR(val) \
                            uatr_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define uatr_SET_I2C_SCL_HSIOM_SEL(sel) \
                    uatr_SET_HSIOM_SEL(uatr_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   uatr_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   uatr_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define uatr_WAIT_SCL_SET_HIGH  (0u == uatr_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (uatr_RX_SCL_MOSI_PIN)
    #define uatr_SET_I2C_SCL_DR(val) \
                            uatr_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define uatr_SET_I2C_SCL_HSIOM_SEL(sel) \
                            uatr_SET_HSIOM_SEL(uatr_RX_SCL_MOSI_HSIOM_REG,  \
                                                           uatr_RX_SCL_MOSI_HSIOM_MASK, \
                                                           uatr_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define uatr_WAIT_SCL_SET_HIGH  (0u == uatr_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define uatr_SET_I2C_SCL_DR(val) \
                                                    do{ /* Does nothing */ }while(0)
    #define uatr_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                    do{ /* Does nothing */ }while(0)

    #define uatr_WAIT_SCL_SET_HIGH  (0u)
#endif /* (uatr_I2C_PINS) */

/* SCB I2C: sda signal */
#if (uatr_I2C_PINS)
    #define uatr_WAIT_SDA_SET_HIGH  (0u == uatr_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (uatr_TX_SDA_MISO_PIN)
    #define uatr_WAIT_SDA_SET_HIGH  (0u == uatr_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define uatr_WAIT_SDA_SET_HIGH  (0u)
#endif /* (uatr_MOSI_SCL_RX_PIN) */
#endif /* (uatr_CY_SCBIP_V0) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define uatr_REMOVE_MOSI_SCL_RX_WAKE_PIN    uatr_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define uatr_REMOVE_MOSI_SCL_RX_PIN         uatr_REMOVE_RX_SCL_MOSI_PIN
#define uatr_REMOVE_MISO_SDA_TX_PIN         uatr_REMOVE_TX_SDA_MISO_PIN
#ifndef uatr_REMOVE_SCLK_PIN
#define uatr_REMOVE_SCLK_PIN                uatr_REMOVE_SCLK_PIN
#endif /* uatr_REMOVE_SCLK_PIN */
#ifndef uatr_REMOVE_SS0_PIN
#define uatr_REMOVE_SS0_PIN                 uatr_REMOVE_SS0_PIN
#endif /* uatr_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define uatr_MOSI_SCL_RX_WAKE_PIN   uatr_RX_WAKE_SCL_MOSI_PIN
#define uatr_MOSI_SCL_RX_PIN        uatr_RX_SCL_MOSI_PIN
#define uatr_MISO_SDA_TX_PIN        uatr_TX_SDA_MISO_PIN
#ifndef uatr_SCLK_PIN
#define uatr_SCLK_PIN               uatr_SCLK_PIN
#endif /* uatr_SCLK_PIN */
#ifndef uatr_SS0_PIN
#define uatr_SS0_PIN                uatr_SS0_PIN
#endif /* uatr_SS0_PIN */

#if (uatr_MOSI_SCL_RX_WAKE_PIN)
    #define uatr_MOSI_SCL_RX_WAKE_HSIOM_REG     uatr_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define uatr_MOSI_SCL_RX_WAKE_HSIOM_PTR     uatr_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define uatr_MOSI_SCL_RX_WAKE_HSIOM_MASK    uatr_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define uatr_MOSI_SCL_RX_WAKE_HSIOM_POS     uatr_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define uatr_MOSI_SCL_RX_WAKE_INTCFG_REG    uatr_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define uatr_MOSI_SCL_RX_WAKE_INTCFG_PTR    uatr_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define uatr_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   uatr_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define uatr_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  uatr_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (uatr_RX_WAKE_SCL_MOSI_PIN) */

#if (uatr_MOSI_SCL_RX_PIN)
    #define uatr_MOSI_SCL_RX_HSIOM_REG      uatr_RX_SCL_MOSI_HSIOM_REG
    #define uatr_MOSI_SCL_RX_HSIOM_PTR      uatr_RX_SCL_MOSI_HSIOM_PTR
    #define uatr_MOSI_SCL_RX_HSIOM_MASK     uatr_RX_SCL_MOSI_HSIOM_MASK
    #define uatr_MOSI_SCL_RX_HSIOM_POS      uatr_RX_SCL_MOSI_HSIOM_POS
#endif /* (uatr_MOSI_SCL_RX_PIN) */

#if (uatr_MISO_SDA_TX_PIN)
    #define uatr_MISO_SDA_TX_HSIOM_REG      uatr_TX_SDA_MISO_HSIOM_REG
    #define uatr_MISO_SDA_TX_HSIOM_PTR      uatr_TX_SDA_MISO_HSIOM_REG
    #define uatr_MISO_SDA_TX_HSIOM_MASK     uatr_TX_SDA_MISO_HSIOM_REG
    #define uatr_MISO_SDA_TX_HSIOM_POS      uatr_TX_SDA_MISO_HSIOM_REG
#endif /* (uatr_MISO_SDA_TX_PIN_PIN) */

#if (uatr_SCLK_PIN)
    #ifndef uatr_SCLK_HSIOM_REG
    #define uatr_SCLK_HSIOM_REG     uatr_SCLK_HSIOM_REG
    #define uatr_SCLK_HSIOM_PTR     uatr_SCLK_HSIOM_PTR
    #define uatr_SCLK_HSIOM_MASK    uatr_SCLK_HSIOM_MASK
    #define uatr_SCLK_HSIOM_POS     uatr_SCLK_HSIOM_POS
    #endif /* uatr_SCLK_HSIOM_REG */
#endif /* (uatr_SCLK_PIN) */

#if (uatr_SS0_PIN)
    #ifndef uatr_SS0_HSIOM_REG
    #define uatr_SS0_HSIOM_REG      uatr_SS0_HSIOM_REG
    #define uatr_SS0_HSIOM_PTR      uatr_SS0_HSIOM_PTR
    #define uatr_SS0_HSIOM_MASK     uatr_SS0_HSIOM_MASK
    #define uatr_SS0_HSIOM_POS      uatr_SS0_HSIOM_POS
    #endif /* uatr_SS0_HSIOM_REG */
#endif /* (uatr_SS0_PIN) */

#define uatr_MOSI_SCL_RX_WAKE_PIN_INDEX uatr_RX_WAKE_SCL_MOSI_PIN_INDEX
#define uatr_MOSI_SCL_RX_PIN_INDEX      uatr_RX_SCL_MOSI_PIN_INDEX
#define uatr_MISO_SDA_TX_PIN_INDEX      uatr_TX_SDA_MISO_PIN_INDEX
#ifndef uatr_SCLK_PIN_INDEX
#define uatr_SCLK_PIN_INDEX             uatr_SCLK_PIN_INDEX
#endif /* uatr_SCLK_PIN_INDEX */
#ifndef uatr_SS0_PIN_INDEX
#define uatr_SS0_PIN_INDEX              uatr_SS0_PIN_INDEX
#endif /* uatr_SS0_PIN_INDEX */

#define uatr_MOSI_SCL_RX_WAKE_PIN_MASK uatr_RX_WAKE_SCL_MOSI_PIN_MASK
#define uatr_MOSI_SCL_RX_PIN_MASK      uatr_RX_SCL_MOSI_PIN_MASK
#define uatr_MISO_SDA_TX_PIN_MASK      uatr_TX_SDA_MISO_PIN_MASK
#ifndef uatr_SCLK_PIN_MASK
#define uatr_SCLK_PIN_MASK             uatr_SCLK_PIN_MASK
#endif /* uatr_SCLK_PIN_MASK */
#ifndef uatr_SS0_PIN_MASK
#define uatr_SS0_PIN_MASK              uatr_SS0_PIN_MASK
#endif /* uatr_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_uatr_H) */


/* [] END OF FILE */
