/*******************************************************************************
* File Name: xbee_PINS.h
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

#if !defined(CY_SCB_PINS_xbee_H)
#define CY_SCB_PINS_xbee_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"


/***************************************
*   Conditional Compilation Parameters
****************************************/

/* Unconfigured pins */
#define xbee_REMOVE_RX_WAKE_SCL_MOSI_PIN  (1u)
#define xbee_REMOVE_RX_SCL_MOSI_PIN      (1u)
#define xbee_REMOVE_TX_SDA_MISO_PIN      (1u)
#define xbee_REMOVE_SCLK_PIN      (1u)
#define xbee_REMOVE_SS0_PIN      (1u)
#define xbee_REMOVE_SS1_PIN                 (1u)
#define xbee_REMOVE_SS2_PIN                 (1u)
#define xbee_REMOVE_SS3_PIN                 (1u)

/* Mode defined pins */
#define xbee_REMOVE_I2C_PINS                (1u)
#define xbee_REMOVE_SPI_MASTER_PINS         (1u)
#define xbee_REMOVE_SPI_MASTER_SCLK_PIN     (1u)
#define xbee_REMOVE_SPI_MASTER_MOSI_PIN     (1u)
#define xbee_REMOVE_SPI_MASTER_MISO_PIN     (1u)
#define xbee_REMOVE_SPI_MASTER_SS0_PIN      (1u)
#define xbee_REMOVE_SPI_MASTER_SS1_PIN      (1u)
#define xbee_REMOVE_SPI_MASTER_SS2_PIN      (1u)
#define xbee_REMOVE_SPI_MASTER_SS3_PIN      (1u)
#define xbee_REMOVE_SPI_SLAVE_PINS          (1u)
#define xbee_REMOVE_SPI_SLAVE_MOSI_PIN      (1u)
#define xbee_REMOVE_SPI_SLAVE_MISO_PIN      (1u)
#define xbee_REMOVE_UART_TX_PIN             (0u)
#define xbee_REMOVE_UART_RX_TX_PIN          (1u)
#define xbee_REMOVE_UART_RX_PIN             (0u)
#define xbee_REMOVE_UART_RX_WAKE_PIN        (1u)
#define xbee_REMOVE_UART_RTS_PIN            (1u)
#define xbee_REMOVE_UART_CTS_PIN            (1u)

/* Unconfigured pins */
#define xbee_RX_WAKE_SCL_MOSI_PIN (0u == xbee_REMOVE_RX_WAKE_SCL_MOSI_PIN)
#define xbee_RX_SCL_MOSI_PIN     (0u == xbee_REMOVE_RX_SCL_MOSI_PIN)
#define xbee_TX_SDA_MISO_PIN     (0u == xbee_REMOVE_TX_SDA_MISO_PIN)
#define xbee_SCLK_PIN     (0u == xbee_REMOVE_SCLK_PIN)
#define xbee_SS0_PIN     (0u == xbee_REMOVE_SS0_PIN)
#define xbee_SS1_PIN                (0u == xbee_REMOVE_SS1_PIN)
#define xbee_SS2_PIN                (0u == xbee_REMOVE_SS2_PIN)
#define xbee_SS3_PIN                (0u == xbee_REMOVE_SS3_PIN)

/* Mode defined pins */
#define xbee_I2C_PINS               (0u == xbee_REMOVE_I2C_PINS)
#define xbee_SPI_MASTER_PINS        (0u == xbee_REMOVE_SPI_MASTER_PINS)
#define xbee_SPI_MASTER_SCLK_PIN    (0u == xbee_REMOVE_SPI_MASTER_SCLK_PIN)
#define xbee_SPI_MASTER_MOSI_PIN    (0u == xbee_REMOVE_SPI_MASTER_MOSI_PIN)
#define xbee_SPI_MASTER_MISO_PIN    (0u == xbee_REMOVE_SPI_MASTER_MISO_PIN)
#define xbee_SPI_MASTER_SS0_PIN     (0u == xbee_REMOVE_SPI_MASTER_SS0_PIN)
#define xbee_SPI_MASTER_SS1_PIN     (0u == xbee_REMOVE_SPI_MASTER_SS1_PIN)
#define xbee_SPI_MASTER_SS2_PIN     (0u == xbee_REMOVE_SPI_MASTER_SS2_PIN)
#define xbee_SPI_MASTER_SS3_PIN     (0u == xbee_REMOVE_SPI_MASTER_SS3_PIN)
#define xbee_SPI_SLAVE_PINS         (0u == xbee_REMOVE_SPI_SLAVE_PINS)
#define xbee_SPI_SLAVE_MOSI_PIN     (0u == xbee_REMOVE_SPI_SLAVE_MOSI_PIN)
#define xbee_SPI_SLAVE_MISO_PIN     (0u == xbee_REMOVE_SPI_SLAVE_MISO_PIN)
#define xbee_UART_TX_PIN            (0u == xbee_REMOVE_UART_TX_PIN)
#define xbee_UART_RX_TX_PIN         (0u == xbee_REMOVE_UART_RX_TX_PIN)
#define xbee_UART_RX_PIN            (0u == xbee_REMOVE_UART_RX_PIN)
#define xbee_UART_RX_WAKE_PIN       (0u == xbee_REMOVE_UART_RX_WAKE_PIN)
#define xbee_UART_RTS_PIN           (0u == xbee_REMOVE_UART_RTS_PIN)
#define xbee_UART_CTS_PIN           (0u == xbee_REMOVE_UART_CTS_PIN)


/***************************************
*             Includes
****************************************/

#if (xbee_RX_WAKE_SCL_MOSI_PIN)
    #include "xbee_uart_rx_wake_i2c_scl_spi_mosi.h"
#endif /* (xbee_RX_SCL_MOSI) */

#if (xbee_RX_SCL_MOSI_PIN)
    #include "xbee_uart_rx_i2c_scl_spi_mosi.h"
#endif /* (xbee_RX_SCL_MOSI) */

#if (xbee_TX_SDA_MISO_PIN)
    #include "xbee_uart_tx_i2c_sda_spi_miso.h"
#endif /* (xbee_TX_SDA_MISO) */

#if (xbee_SCLK_PIN)
    #include "xbee_spi_sclk.h"
#endif /* (xbee_SCLK) */

#if (xbee_SS0_PIN)
    #include "xbee_spi_ss0.h"
#endif /* (xbee_SS0_PIN) */

#if (xbee_SS1_PIN)
    #include "xbee_spi_ss1.h"
#endif /* (xbee_SS1_PIN) */

#if (xbee_SS2_PIN)
    #include "xbee_spi_ss2.h"
#endif /* (xbee_SS2_PIN) */

#if (xbee_SS3_PIN)
    #include "xbee_spi_ss3.h"
#endif /* (xbee_SS3_PIN) */

#if (xbee_I2C_PINS)
    #include "xbee_scl.h"
    #include "xbee_sda.h"
#endif /* (xbee_I2C_PINS) */

#if (xbee_SPI_MASTER_PINS)
#if (xbee_SPI_MASTER_SCLK_PIN)
    #include "xbee_sclk_m.h"
#endif /* (xbee_SPI_MASTER_SCLK_PIN) */

#if (xbee_SPI_MASTER_MOSI_PIN)
    #include "xbee_mosi_m.h"
#endif /* (xbee_SPI_MASTER_MOSI_PIN) */

#if (xbee_SPI_MASTER_MISO_PIN)
    #include "xbee_miso_m.h"
#endif /*(xbee_SPI_MASTER_MISO_PIN) */
#endif /* (xbee_SPI_MASTER_PINS) */

#if (xbee_SPI_SLAVE_PINS)
    #include "xbee_sclk_s.h"
    #include "xbee_ss_s.h"

#if (xbee_SPI_SLAVE_MOSI_PIN)
    #include "xbee_mosi_s.h"
#endif /* (xbee_SPI_SLAVE_MOSI_PIN) */

#if (xbee_SPI_SLAVE_MISO_PIN)
    #include "xbee_miso_s.h"
#endif /*(xbee_SPI_SLAVE_MISO_PIN) */
#endif /* (xbee_SPI_SLAVE_PINS) */

#if (xbee_SPI_MASTER_SS0_PIN)
    #include "xbee_ss0_m.h"
#endif /* (xbee_SPI_MASTER_SS0_PIN) */

#if (xbee_SPI_MASTER_SS1_PIN)
    #include "xbee_ss1_m.h"
#endif /* (xbee_SPI_MASTER_SS1_PIN) */

#if (xbee_SPI_MASTER_SS2_PIN)
    #include "xbee_ss2_m.h"
#endif /* (xbee_SPI_MASTER_SS2_PIN) */

#if (xbee_SPI_MASTER_SS3_PIN)
    #include "xbee_ss3_m.h"
#endif /* (xbee_SPI_MASTER_SS3_PIN) */

#if (xbee_UART_TX_PIN)
    #include "xbee_tx.h"
#endif /* (xbee_UART_TX_PIN) */

#if (xbee_UART_RX_TX_PIN)
    #include "xbee_rx_tx.h"
#endif /* (xbee_UART_RX_TX_PIN) */

#if (xbee_UART_RX_PIN)
    #include "xbee_rx.h"
#endif /* (xbee_UART_RX_PIN) */

#if (xbee_UART_RX_WAKE_PIN)
    #include "xbee_rx_wake.h"
#endif /* (xbee_UART_RX_WAKE_PIN) */

#if (xbee_UART_RTS_PIN)
    #include "xbee_rts.h"
#endif /* (xbee_UART_RTS_PIN) */

#if (xbee_UART_CTS_PIN)
    #include "xbee_cts.h"
#endif /* (xbee_UART_CTS_PIN) */


/***************************************
*              Registers
***************************************/

#if (xbee_RX_WAKE_SCL_MOSI_PIN)
    #define xbee_RX_WAKE_SCL_MOSI_HSIOM_REG \
                            (*(reg32 *) xbee_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define xbee_RX_WAKE_SCL_MOSI_HSIOM_PTR \
                            ( (reg32 *) xbee_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM)
    #define xbee_RX_WAKE_SCL_MOSI_HSIOM_MASK \
                            (xbee_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define xbee_RX_WAKE_SCL_MOSI_HSIOM_POS \
                            (xbee_uart_rx_wake_i2c_scl_spi_mosi__0__HSIOM_SHIFT)

    #define xbee_RX_WAKE_SCL_MOSI_INTCFG_REG \
                            (*(reg32 *) xbee_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define xbee_RX_WAKE_SCL_MOSI_INTCFG_PTR \
                            ( (reg32 *) xbee_uart_rx_wake_i2c_scl_spi_mosi__0__INTCFG)
    #define xbee_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS  (xbee_uart_rx_wake_i2c_scl_spi_mosi__SHIFT)
    #define xbee_RX_WAKE_SCL_MOSI_INTCFG_TYPE_MASK \
                            ((uint32) xbee_INTCFG_TYPE_MASK << \
                                      xbee_RX_WAKE_SCL_MOSI_INTCFG_TYPE_POS)
#endif /* (xbee_RX_WAKE_SCL_MOSI_PIN) */

#if (xbee_RX_SCL_MOSI_PIN)
    #define xbee_RX_SCL_MOSI_HSIOM_REG   (*(reg32 *) xbee_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define xbee_RX_SCL_MOSI_HSIOM_PTR   ( (reg32 *) xbee_uart_rx_i2c_scl_spi_mosi__0__HSIOM)
    #define xbee_RX_SCL_MOSI_HSIOM_MASK  (xbee_uart_rx_i2c_scl_spi_mosi__0__HSIOM_MASK)
    #define xbee_RX_SCL_MOSI_HSIOM_POS   (xbee_uart_rx_i2c_scl_spi_mosi__0__HSIOM_SHIFT)
#endif /* (xbee_RX_SCL_MOSI_PIN) */

#if (xbee_TX_SDA_MISO_PIN)
    #define xbee_TX_SDA_MISO_HSIOM_REG   (*(reg32 *) xbee_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define xbee_TX_SDA_MISO_HSIOM_PTR   ( (reg32 *) xbee_uart_tx_i2c_sda_spi_miso__0__HSIOM)
    #define xbee_TX_SDA_MISO_HSIOM_MASK  (xbee_uart_tx_i2c_sda_spi_miso__0__HSIOM_MASK)
    #define xbee_TX_SDA_MISO_HSIOM_POS   (xbee_uart_tx_i2c_sda_spi_miso__0__HSIOM_SHIFT)
#endif /* (xbee_TX_SDA_MISO_PIN) */

#if (xbee_SCLK_PIN)
    #define xbee_SCLK_HSIOM_REG   (*(reg32 *) xbee_spi_sclk__0__HSIOM)
    #define xbee_SCLK_HSIOM_PTR   ( (reg32 *) xbee_spi_sclk__0__HSIOM)
    #define xbee_SCLK_HSIOM_MASK  (xbee_spi_sclk__0__HSIOM_MASK)
    #define xbee_SCLK_HSIOM_POS   (xbee_spi_sclk__0__HSIOM_SHIFT)
#endif /* (xbee_SCLK_PIN) */

#if (xbee_SS0_PIN)
    #define xbee_SS0_HSIOM_REG   (*(reg32 *) xbee_spi_ss0__0__HSIOM)
    #define xbee_SS0_HSIOM_PTR   ( (reg32 *) xbee_spi_ss0__0__HSIOM)
    #define xbee_SS0_HSIOM_MASK  (xbee_spi_ss0__0__HSIOM_MASK)
    #define xbee_SS0_HSIOM_POS   (xbee_spi_ss0__0__HSIOM_SHIFT)
#endif /* (xbee_SS0_PIN) */

#if (xbee_SS1_PIN)
    #define xbee_SS1_HSIOM_REG      (*(reg32 *) xbee_spi_ss1__0__HSIOM)
    #define xbee_SS1_HSIOM_PTR      ( (reg32 *) xbee_spi_ss1__0__HSIOM)
    #define xbee_SS1_HSIOM_MASK     (xbee_spi_ss1__0__HSIOM_MASK)
    #define xbee_SS1_HSIOM_POS      (xbee_spi_ss1__0__HSIOM_SHIFT)
#endif /* (xbee_SS1_PIN) */

#if (xbee_SS2_PIN)
    #define xbee_SS2_HSIOM_REG     (*(reg32 *) xbee_spi_ss2__0__HSIOM)
    #define xbee_SS2_HSIOM_PTR     ( (reg32 *) xbee_spi_ss2__0__HSIOM)
    #define xbee_SS2_HSIOM_MASK    (xbee_spi_ss2__0__HSIOM_MASK)
    #define xbee_SS2_HSIOM_POS     (xbee_spi_ss2__0__HSIOM_SHIFT)
#endif /* (xbee_SS2_PIN) */

#if (xbee_SS3_PIN)
    #define xbee_SS3_HSIOM_REG     (*(reg32 *) xbee_spi_ss3__0__HSIOM)
    #define xbee_SS3_HSIOM_PTR     ( (reg32 *) xbee_spi_ss3__0__HSIOM)
    #define xbee_SS3_HSIOM_MASK    (xbee_spi_ss3__0__HSIOM_MASK)
    #define xbee_SS3_HSIOM_POS     (xbee_spi_ss3__0__HSIOM_SHIFT)
#endif /* (xbee_SS3_PIN) */

#if (xbee_I2C_PINS)
    #define xbee_SCL_HSIOM_REG     (*(reg32 *) xbee_scl__0__HSIOM)
    #define xbee_SCL_HSIOM_PTR     ( (reg32 *) xbee_scl__0__HSIOM)
    #define xbee_SCL_HSIOM_MASK    (xbee_scl__0__HSIOM_MASK)
    #define xbee_SCL_HSIOM_POS     (xbee_scl__0__HSIOM_SHIFT)

    #define xbee_SDA_HSIOM_REG     (*(reg32 *) xbee_sda__0__HSIOM)
    #define xbee_SDA_HSIOM_PTR     ( (reg32 *) xbee_sda__0__HSIOM)
    #define xbee_SDA_HSIOM_MASK    (xbee_sda__0__HSIOM_MASK)
    #define xbee_SDA_HSIOM_POS     (xbee_sda__0__HSIOM_SHIFT)
#endif /* (xbee_I2C_PINS) */

#if (xbee_SPI_MASTER_SCLK_PIN)
    #define xbee_SCLK_M_HSIOM_REG   (*(reg32 *) xbee_sclk_m__0__HSIOM)
    #define xbee_SCLK_M_HSIOM_PTR   ( (reg32 *) xbee_sclk_m__0__HSIOM)
    #define xbee_SCLK_M_HSIOM_MASK  (xbee_sclk_m__0__HSIOM_MASK)
    #define xbee_SCLK_M_HSIOM_POS   (xbee_sclk_m__0__HSIOM_SHIFT)
#endif /* (xbee_SPI_MASTER_SCLK_PIN) */

#if (xbee_SPI_MASTER_SS0_PIN)
    #define xbee_SS0_M_HSIOM_REG    (*(reg32 *) xbee_ss0_m__0__HSIOM)
    #define xbee_SS0_M_HSIOM_PTR    ( (reg32 *) xbee_ss0_m__0__HSIOM)
    #define xbee_SS0_M_HSIOM_MASK   (xbee_ss0_m__0__HSIOM_MASK)
    #define xbee_SS0_M_HSIOM_POS    (xbee_ss0_m__0__HSIOM_SHIFT)
#endif /* (xbee_SPI_MASTER_SS0_PIN) */

#if (xbee_SPI_MASTER_SS1_PIN)
    #define xbee_SS1_M_HSIOM_REG    (*(reg32 *) xbee_ss1_m__0__HSIOM)
    #define xbee_SS1_M_HSIOM_PTR    ( (reg32 *) xbee_ss1_m__0__HSIOM)
    #define xbee_SS1_M_HSIOM_MASK   (xbee_ss1_m__0__HSIOM_MASK)
    #define xbee_SS1_M_HSIOM_POS    (xbee_ss1_m__0__HSIOM_SHIFT)
#endif /* (xbee_SPI_MASTER_SS1_PIN) */

#if (xbee_SPI_MASTER_SS2_PIN)
    #define xbee_SS2_M_HSIOM_REG    (*(reg32 *) xbee_ss2_m__0__HSIOM)
    #define xbee_SS2_M_HSIOM_PTR    ( (reg32 *) xbee_ss2_m__0__HSIOM)
    #define xbee_SS2_M_HSIOM_MASK   (xbee_ss2_m__0__HSIOM_MASK)
    #define xbee_SS2_M_HSIOM_POS    (xbee_ss2_m__0__HSIOM_SHIFT)
#endif /* (xbee_SPI_MASTER_SS2_PIN) */

#if (xbee_SPI_MASTER_SS3_PIN)
    #define xbee_SS3_M_HSIOM_REG    (*(reg32 *) xbee_ss3_m__0__HSIOM)
    #define xbee_SS3_M_HSIOM_PTR    ( (reg32 *) xbee_ss3_m__0__HSIOM)
    #define xbee_SS3_M_HSIOM_MASK   (xbee_ss3_m__0__HSIOM_MASK)
    #define xbee_SS3_M_HSIOM_POS    (xbee_ss3_m__0__HSIOM_SHIFT)
#endif /* (xbee_SPI_MASTER_SS3_PIN) */

#if (xbee_UART_TX_PIN)
    #define xbee_TX_HSIOM_REG   (*(reg32 *) xbee_tx__0__HSIOM)
    #define xbee_TX_HSIOM_PTR   ( (reg32 *) xbee_tx_0__HSIOM)
    #define xbee_TX_HSIOM_MASK  (xbee_tx__0__HSIOM_MASK)
    #define xbee_TX_HSIOM_POS   (xbee_tx__0__HSIOM_SHIFT)
#endif /* (xbee_UART_TX_PIN) */

#if (xbee_UART_RTS_PIN)
    #define xbee_RTS_HSIOM_REG  (*(reg32 *) xbee_rts__0__HSIOM)
    #define xbee_RTS_HSIOM_PTR  ( (reg32 *) xbee_rts__0__HSIOM)
    #define xbee_RTS_HSIOM_MASK (xbee_rts__0__HSIOM_MASK)
    #define xbee_RTS_HSIOM_POS  (xbee_rts__0__HSIOM_SHIFT)
#endif /* (xbee_UART_RTS_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constants */
#define xbee_HSIOM_DEF_SEL      (0x00u)
#define xbee_HSIOM_GPIO_SEL     (0x00u)
#define xbee_HSIOM_UART_SEL     (0x09u)
#define xbee_HSIOM_I2C_SEL      (0x0Eu)
#define xbee_HSIOM_SPI_SEL      (0x0Fu)

#define xbee_RX_WAKE_SCL_MOSI_PIN_INDEX   (0u)
#define xbee_RX_SCL_MOSI_PIN_INDEX       (0u)
#define xbee_TX_SDA_MISO_PIN_INDEX       (1u)
#define xbee_SCLK_PIN_INDEX       (2u)
#define xbee_SS0_PIN_INDEX       (3u)
#define xbee_SS1_PIN_INDEX                  (4u)
#define xbee_SS2_PIN_INDEX                  (5u)
#define xbee_SS3_PIN_INDEX                  (6u)

#define xbee_RX_WAKE_SCL_MOSI_PIN_MASK ((uint32) 0x01u << xbee_RX_WAKE_SCL_MOSI_PIN_INDEX)
#define xbee_RX_SCL_MOSI_PIN_MASK     ((uint32) 0x01u << xbee_RX_SCL_MOSI_PIN_INDEX)
#define xbee_TX_SDA_MISO_PIN_MASK     ((uint32) 0x01u << xbee_TX_SDA_MISO_PIN_INDEX)
#define xbee_SCLK_PIN_MASK     ((uint32) 0x01u << xbee_SCLK_PIN_INDEX)
#define xbee_SS0_PIN_MASK     ((uint32) 0x01u << xbee_SS0_PIN_INDEX)
#define xbee_SS1_PIN_MASK                ((uint32) 0x01u << xbee_SS1_PIN_INDEX)
#define xbee_SS2_PIN_MASK                ((uint32) 0x01u << xbee_SS2_PIN_INDEX)
#define xbee_SS3_PIN_MASK                ((uint32) 0x01u << xbee_SS3_PIN_INDEX)

/* Pin interrupt constants */
#define xbee_INTCFG_TYPE_MASK           (0x03u)
#define xbee_INTCFG_TYPE_FALLING_EDGE   (0x02u)

/* Pin Drive Mode constants */
#define xbee_PIN_DM_ALG_HIZ  (0u)
#define xbee_PIN_DM_DIG_HIZ  (1u)
#define xbee_PIN_DM_OD_LO    (4u)
#define xbee_PIN_DM_STRONG   (6u)


/***************************************
*          Macro Definitions
***************************************/

/* Return drive mode of the pin */
#define xbee_DM_MASK    (0x7u)
#define xbee_DM_SIZE    (3)
#define xbee_GET_P4_PIN_DM(reg, pos) \
    ( ((reg) & (uint32) ((uint32) xbee_DM_MASK << (xbee_DM_SIZE * (pos)))) >> \
                                                              (xbee_DM_SIZE * (pos)) )

#if (xbee_TX_SDA_MISO_PIN)
    #define xbee_CHECK_TX_SDA_MISO_PIN_USED \
                (xbee_PIN_DM_ALG_HIZ != \
                    xbee_GET_P4_PIN_DM(xbee_uart_tx_i2c_sda_spi_miso_PC, \
                                                   xbee_uart_tx_i2c_sda_spi_miso_SHIFT))
#endif /* (xbee_TX_SDA_MISO_PIN) */

#if (xbee_SS0_PIN)
    #define xbee_CHECK_SS0_PIN_USED \
                (xbee_PIN_DM_ALG_HIZ != \
                    xbee_GET_P4_PIN_DM(xbee_spi_ss0_PC, \
                                                   xbee_spi_ss0_SHIFT))
#endif /* (xbee_SS0_PIN) */

/* Set bits-mask in register */
#define xbee_SET_REGISTER_BITS(reg, mask, pos, mode) \
                    do                                           \
                    {                                            \
                        (reg) = (((reg) & ((uint32) ~(uint32) (mask))) | ((uint32) ((uint32) (mode) << (pos)))); \
                    }while(0)

/* Set bit in the register */
#define xbee_SET_REGISTER_BIT(reg, mask, val) \
                    ((val) ? ((reg) |= (mask)) : ((reg) &= ((uint32) ~((uint32) (mask)))))

#define xbee_SET_HSIOM_SEL(reg, mask, pos, sel) xbee_SET_REGISTER_BITS(reg, mask, pos, sel)
#define xbee_SET_INCFG_TYPE(reg, mask, pos, intType) \
                                                        xbee_SET_REGISTER_BITS(reg, mask, pos, intType)
#define xbee_SET_INP_DIS(reg, mask, val) xbee_SET_REGISTER_BIT(reg, mask, val)

/* xbee_SET_I2C_SCL_DR(val) - Sets I2C SCL DR register.
*  xbee_SET_I2C_SCL_HSIOM_SEL(sel) - Sets I2C SCL HSIOM settings.
*/
/* SCB I2C: scl signal */
#if (xbee_CY_SCBIP_V0)
#if (xbee_I2C_PINS)
    #define xbee_SET_I2C_SCL_DR(val) xbee_scl_Write(val)

    #define xbee_SET_I2C_SCL_HSIOM_SEL(sel) \
                          xbee_SET_HSIOM_SEL(xbee_SCL_HSIOM_REG,  \
                                                         xbee_SCL_HSIOM_MASK, \
                                                         xbee_SCL_HSIOM_POS,  \
                                                         (sel))
    #define xbee_WAIT_SCL_SET_HIGH  (0u == xbee_scl_Read())

/* Unconfigured SCB: scl signal */
#elif (xbee_RX_WAKE_SCL_MOSI_PIN)
    #define xbee_SET_I2C_SCL_DR(val) \
                            xbee_uart_rx_wake_i2c_scl_spi_mosi_Write(val)

    #define xbee_SET_I2C_SCL_HSIOM_SEL(sel) \
                    xbee_SET_HSIOM_SEL(xbee_RX_WAKE_SCL_MOSI_HSIOM_REG,  \
                                                   xbee_RX_WAKE_SCL_MOSI_HSIOM_MASK, \
                                                   xbee_RX_WAKE_SCL_MOSI_HSIOM_POS,  \
                                                   (sel))

    #define xbee_WAIT_SCL_SET_HIGH  (0u == xbee_uart_rx_wake_i2c_scl_spi_mosi_Read())

#elif (xbee_RX_SCL_MOSI_PIN)
    #define xbee_SET_I2C_SCL_DR(val) \
                            xbee_uart_rx_i2c_scl_spi_mosi_Write(val)


    #define xbee_SET_I2C_SCL_HSIOM_SEL(sel) \
                            xbee_SET_HSIOM_SEL(xbee_RX_SCL_MOSI_HSIOM_REG,  \
                                                           xbee_RX_SCL_MOSI_HSIOM_MASK, \
                                                           xbee_RX_SCL_MOSI_HSIOM_POS,  \
                                                           (sel))

    #define xbee_WAIT_SCL_SET_HIGH  (0u == xbee_uart_rx_i2c_scl_spi_mosi_Read())

#else
    #define xbee_SET_I2C_SCL_DR(val) \
                                                    do{ /* Does nothing */ }while(0)
    #define xbee_SET_I2C_SCL_HSIOM_SEL(sel) \
                                                    do{ /* Does nothing */ }while(0)

    #define xbee_WAIT_SCL_SET_HIGH  (0u)
#endif /* (xbee_I2C_PINS) */

/* SCB I2C: sda signal */
#if (xbee_I2C_PINS)
    #define xbee_WAIT_SDA_SET_HIGH  (0u == xbee_sda_Read())
/* Unconfigured SCB: sda signal */
#elif (xbee_TX_SDA_MISO_PIN)
    #define xbee_WAIT_SDA_SET_HIGH  (0u == xbee_uart_tx_i2c_sda_spi_miso_Read())
#else
    #define xbee_WAIT_SDA_SET_HIGH  (0u)
#endif /* (xbee_MOSI_SCL_RX_PIN) */
#endif /* (xbee_CY_SCBIP_V0) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Unconfigured pins */
#define xbee_REMOVE_MOSI_SCL_RX_WAKE_PIN    xbee_REMOVE_RX_WAKE_SCL_MOSI_PIN
#define xbee_REMOVE_MOSI_SCL_RX_PIN         xbee_REMOVE_RX_SCL_MOSI_PIN
#define xbee_REMOVE_MISO_SDA_TX_PIN         xbee_REMOVE_TX_SDA_MISO_PIN
#ifndef xbee_REMOVE_SCLK_PIN
#define xbee_REMOVE_SCLK_PIN                xbee_REMOVE_SCLK_PIN
#endif /* xbee_REMOVE_SCLK_PIN */
#ifndef xbee_REMOVE_SS0_PIN
#define xbee_REMOVE_SS0_PIN                 xbee_REMOVE_SS0_PIN
#endif /* xbee_REMOVE_SS0_PIN */

/* Unconfigured pins */
#define xbee_MOSI_SCL_RX_WAKE_PIN   xbee_RX_WAKE_SCL_MOSI_PIN
#define xbee_MOSI_SCL_RX_PIN        xbee_RX_SCL_MOSI_PIN
#define xbee_MISO_SDA_TX_PIN        xbee_TX_SDA_MISO_PIN
#ifndef xbee_SCLK_PIN
#define xbee_SCLK_PIN               xbee_SCLK_PIN
#endif /* xbee_SCLK_PIN */
#ifndef xbee_SS0_PIN
#define xbee_SS0_PIN                xbee_SS0_PIN
#endif /* xbee_SS0_PIN */

#if (xbee_MOSI_SCL_RX_WAKE_PIN)
    #define xbee_MOSI_SCL_RX_WAKE_HSIOM_REG     xbee_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define xbee_MOSI_SCL_RX_WAKE_HSIOM_PTR     xbee_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define xbee_MOSI_SCL_RX_WAKE_HSIOM_MASK    xbee_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define xbee_MOSI_SCL_RX_WAKE_HSIOM_POS     xbee_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define xbee_MOSI_SCL_RX_WAKE_INTCFG_REG    xbee_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define xbee_MOSI_SCL_RX_WAKE_INTCFG_PTR    xbee_RX_WAKE_SCL_MOSI_HSIOM_REG

    #define xbee_MOSI_SCL_RX_WAKE_INTCFG_TYPE_POS   xbee_RX_WAKE_SCL_MOSI_HSIOM_REG
    #define xbee_MOSI_SCL_RX_WAKE_INTCFG_TYPE_MASK  xbee_RX_WAKE_SCL_MOSI_HSIOM_REG
#endif /* (xbee_RX_WAKE_SCL_MOSI_PIN) */

#if (xbee_MOSI_SCL_RX_PIN)
    #define xbee_MOSI_SCL_RX_HSIOM_REG      xbee_RX_SCL_MOSI_HSIOM_REG
    #define xbee_MOSI_SCL_RX_HSIOM_PTR      xbee_RX_SCL_MOSI_HSIOM_PTR
    #define xbee_MOSI_SCL_RX_HSIOM_MASK     xbee_RX_SCL_MOSI_HSIOM_MASK
    #define xbee_MOSI_SCL_RX_HSIOM_POS      xbee_RX_SCL_MOSI_HSIOM_POS
#endif /* (xbee_MOSI_SCL_RX_PIN) */

#if (xbee_MISO_SDA_TX_PIN)
    #define xbee_MISO_SDA_TX_HSIOM_REG      xbee_TX_SDA_MISO_HSIOM_REG
    #define xbee_MISO_SDA_TX_HSIOM_PTR      xbee_TX_SDA_MISO_HSIOM_REG
    #define xbee_MISO_SDA_TX_HSIOM_MASK     xbee_TX_SDA_MISO_HSIOM_REG
    #define xbee_MISO_SDA_TX_HSIOM_POS      xbee_TX_SDA_MISO_HSIOM_REG
#endif /* (xbee_MISO_SDA_TX_PIN_PIN) */

#if (xbee_SCLK_PIN)
    #ifndef xbee_SCLK_HSIOM_REG
    #define xbee_SCLK_HSIOM_REG     xbee_SCLK_HSIOM_REG
    #define xbee_SCLK_HSIOM_PTR     xbee_SCLK_HSIOM_PTR
    #define xbee_SCLK_HSIOM_MASK    xbee_SCLK_HSIOM_MASK
    #define xbee_SCLK_HSIOM_POS     xbee_SCLK_HSIOM_POS
    #endif /* xbee_SCLK_HSIOM_REG */
#endif /* (xbee_SCLK_PIN) */

#if (xbee_SS0_PIN)
    #ifndef xbee_SS0_HSIOM_REG
    #define xbee_SS0_HSIOM_REG      xbee_SS0_HSIOM_REG
    #define xbee_SS0_HSIOM_PTR      xbee_SS0_HSIOM_PTR
    #define xbee_SS0_HSIOM_MASK     xbee_SS0_HSIOM_MASK
    #define xbee_SS0_HSIOM_POS      xbee_SS0_HSIOM_POS
    #endif /* xbee_SS0_HSIOM_REG */
#endif /* (xbee_SS0_PIN) */

#define xbee_MOSI_SCL_RX_WAKE_PIN_INDEX xbee_RX_WAKE_SCL_MOSI_PIN_INDEX
#define xbee_MOSI_SCL_RX_PIN_INDEX      xbee_RX_SCL_MOSI_PIN_INDEX
#define xbee_MISO_SDA_TX_PIN_INDEX      xbee_TX_SDA_MISO_PIN_INDEX
#ifndef xbee_SCLK_PIN_INDEX
#define xbee_SCLK_PIN_INDEX             xbee_SCLK_PIN_INDEX
#endif /* xbee_SCLK_PIN_INDEX */
#ifndef xbee_SS0_PIN_INDEX
#define xbee_SS0_PIN_INDEX              xbee_SS0_PIN_INDEX
#endif /* xbee_SS0_PIN_INDEX */

#define xbee_MOSI_SCL_RX_WAKE_PIN_MASK xbee_RX_WAKE_SCL_MOSI_PIN_MASK
#define xbee_MOSI_SCL_RX_PIN_MASK      xbee_RX_SCL_MOSI_PIN_MASK
#define xbee_MISO_SDA_TX_PIN_MASK      xbee_TX_SDA_MISO_PIN_MASK
#ifndef xbee_SCLK_PIN_MASK
#define xbee_SCLK_PIN_MASK             xbee_SCLK_PIN_MASK
#endif /* xbee_SCLK_PIN_MASK */
#ifndef xbee_SS0_PIN_MASK
#define xbee_SS0_PIN_MASK              xbee_SS0_PIN_MASK
#endif /* xbee_SS0_PIN_MASK */

#endif /* (CY_SCB_PINS_xbee_H) */


/* [] END OF FILE */
