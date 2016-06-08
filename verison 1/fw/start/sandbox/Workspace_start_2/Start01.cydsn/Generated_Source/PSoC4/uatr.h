/*******************************************************************************
* File Name: uatr.h
* Version 3.10
*
* Description:
*  This file provides constants and parameter values for the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_uatr_H)
#define CY_SCB_uatr_H

#include <cydevice_trm.h>
#include <cyfitter.h>
#include <cytypes.h>
#include <CyLib.h>

/* SCB IP block v0 is available in PSoC 4100/PSoC 4200 */
#define uatr_CY_SCBIP_V0    (CYIPBLOCK_m0s8scb_VERSION == 0u)
/* SCB IP block v1 is available in PSoC 4000 */
#define uatr_CY_SCBIP_V1    (CYIPBLOCK_m0s8scb_VERSION == 1u)
/* SCB IP block v2 is available in all other devices */
#define uatr_CY_SCBIP_V2    (CYIPBLOCK_m0s8scb_VERSION >= 2u)

#define uatr_SCB_MODE                     (4u)

/* SCB modes enum */
#define uatr_SCB_MODE_I2C                 (0x01u)
#define uatr_SCB_MODE_SPI                 (0x02u)
#define uatr_SCB_MODE_UART                (0x04u)
#define uatr_SCB_MODE_EZI2C               (0x08u)
#define uatr_SCB_MODE_UNCONFIG            (0xFFu)

/* Condition compilation depends on operation mode: Unconfigured implies apply to all modes */
#define uatr_SCB_MODE_I2C_CONST_CFG       (uatr_SCB_MODE_I2C       == uatr_SCB_MODE)
#define uatr_SCB_MODE_SPI_CONST_CFG       (uatr_SCB_MODE_SPI       == uatr_SCB_MODE)
#define uatr_SCB_MODE_UART_CONST_CFG      (uatr_SCB_MODE_UART      == uatr_SCB_MODE)
#define uatr_SCB_MODE_EZI2C_CONST_CFG     (uatr_SCB_MODE_EZI2C     == uatr_SCB_MODE)
#define uatr_SCB_MODE_UNCONFIG_CONST_CFG  (uatr_SCB_MODE_UNCONFIG  == uatr_SCB_MODE)

/* Condition compilation for includes */
#define uatr_SCB_MODE_I2C_INC      (0u !=(uatr_SCB_MODE_I2C   & uatr_SCB_MODE))
#define uatr_SCB_MODE_EZI2C_INC    (0u !=(uatr_SCB_MODE_EZI2C & uatr_SCB_MODE))
#if (!uatr_CY_SCBIP_V1)
    #define uatr_SCB_MODE_SPI_INC  (0u !=(uatr_SCB_MODE_SPI   & uatr_SCB_MODE))
    #define uatr_SCB_MODE_UART_INC (0u !=(uatr_SCB_MODE_UART  & uatr_SCB_MODE))
#else
    #define uatr_SCB_MODE_SPI_INC  (0u)
    #define uatr_SCB_MODE_UART_INC (0u)
#endif /* (!uatr_CY_SCBIP_V1) */

/* Interrupts remove options */
#define uatr_REMOVE_SCB_IRQ             (1u)
#define uatr_SCB_IRQ_INTERNAL           (0u == uatr_REMOVE_SCB_IRQ)

#define uatr_REMOVE_UART_RX_WAKEUP_IRQ  (1u)
#define uatr_UART_RX_WAKEUP_IRQ         (0u == uatr_REMOVE_UART_RX_WAKEUP_IRQ)

/* SCB interrupt enum */
#define uatr_SCB_INTR_MODE_NONE     (0u)
#define uatr_SCB_INTR_MODE_INTERNAL (1u)
#define uatr_SCB_INTR_MODE_EXTERNAL (2u)

/* Internal clock remove option */
#define uatr_REMOVE_SCB_CLK     (0u)
#define uatr_SCB_CLK_INTERNAL   (0u == uatr_REMOVE_SCB_CLK)


/***************************************
*       Includes
****************************************/

#include "uatr_PINS.h"

#if (uatr_SCB_CLK_INTERNAL)
    #include "uatr_SCBCLK.h"
#endif /* (uatr_SCB_CLK_INTERNAL) */


/***************************************
*       Type Definitions
***************************************/

typedef struct
{
    uint8 enableState;
} uatr_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* Start and Stop APIs */
void uatr_Init(void);
void uatr_Enable(void);
void uatr_Start(void);
void uatr_Stop(void);

/* Sleep and Wakeup APis */
void uatr_Sleep(void);
void uatr_Wakeup(void);

#if (uatr_SCB_IRQ_INTERNAL)
    /* Custom interrupt handler */
    void uatr_SetCustomInterruptHandler(void (*func)(void));
#endif /* (uatr_SCB_IRQ_INTERNAL) */

/* Interface to internal interrupt component */
#if (uatr_SCB_IRQ_INTERNAL)
    #define uatr_EnableInt()        CyIntEnable      (uatr_ISR_NUMBER)
    #define uatr_DisableInt()       CyIntDisable     (uatr_ISR_NUMBER)
    #define uatr_ClearPendingInt()  CyIntClearPending(uatr_ISR_NUMBER)
#endif /* (uatr_SCB_IRQ_INTERNAL) */

#if (uatr_UART_RX_WAKEUP_IRQ)
    #define uatr_RxWakeEnableInt()        CyIntEnable      (uatr_RX_WAKE_ISR_NUMBER)
    #define uatr_RxWakeDisableInt()       CyIntDisable     (uatr_RX_WAKE_ISR_NUMBER)
    #define uatr_RxWakeClearPendingInt()  CyIntClearPending(uatr_RX_WAKE_ISR_NUMBER)
#endif /* (uatr_UART_RX_WAKEUP_IRQ) */

/* Get interrupt cause */
#define uatr_GetInterruptCause()    (uatr_INTR_CAUSE_REG)

/* APIs to service INTR_RX register */
#define uatr_SetRxInterruptMode(interruptMask)     uatr_WRITE_INTR_RX_MASK(interruptMask)
#define uatr_ClearRxInterruptSource(interruptMask) uatr_CLEAR_INTR_RX(interruptMask)
#define uatr_SetRxInterrupt(interruptMask)         uatr_SET_INTR_RX(interruptMask)
#define uatr_GetRxInterruptSource()                (uatr_INTR_RX_REG)
#define uatr_GetRxInterruptMode()                  (uatr_INTR_RX_MASK_REG)
#define uatr_GetRxInterruptSourceMasked()          (uatr_INTR_RX_MASKED_REG)
void uatr_SetRxFifoLevel(uint32 level);

/* APIs to service INTR_TX register */
#define uatr_SetTxInterruptMode(interruptMask)     uatr_WRITE_INTR_TX_MASK(interruptMask)
#define uatr_ClearTxInterruptSource(interruptMask) uatr_CLEAR_INTR_TX(interruptMask)
#define uatr_SetTxInterrupt(interruptMask)         uatr_SET_INTR_TX(interruptMask)
#define uatr_GetTxInterruptSource()                (uatr_INTR_TX_REG)
#define uatr_GetTxInterruptMode()                  (uatr_INTR_TX_MASK_REG)
#define uatr_GetTxInterruptSourceMasked()          (uatr_INTR_TX_MASKED_REG)
void uatr_SetTxFifoLevel(uint32 level);

/* APIs to service INTR_MASTER register */
#define uatr_SetMasterInterruptMode(interruptMask)    uatr_WRITE_INTR_MASTER_MASK(interruptMask)
#define uatr_ClearMasterInterruptSource(interruptMask) uatr_CLEAR_INTR_MASTER(interruptMask)
#define uatr_SetMasterInterrupt(interruptMask)         uatr_SET_INTR_MASTER(interruptMask)
#define uatr_GetMasterInterruptSource()                (uatr_INTR_MASTER_REG)
#define uatr_GetMasterInterruptMode()                  (uatr_INTR_MASTER_MASK_REG)
#define uatr_GetMasterInterruptSourceMasked()          (uatr_INTR_MASTER_MASKED_REG)

/* APIs to service INTR_SLAVE register */
#define uatr_SetSlaveInterruptMode(interruptMask)     uatr_WRITE_INTR_SLAVE_MASK(interruptMask)
#define uatr_ClearSlaveInterruptSource(interruptMask) uatr_CLEAR_INTR_SLAVE(interruptMask)
#define uatr_SetSlaveInterrupt(interruptMask)         uatr_SET_INTR_SLAVE(interruptMask)
#define uatr_GetSlaveInterruptSource()                (uatr_INTR_SLAVE_REG)
#define uatr_GetSlaveInterruptMode()                  (uatr_INTR_SLAVE_MASK_REG)
#define uatr_GetSlaveInterruptSourceMasked()          (uatr_INTR_SLAVE_MASKED_REG)


/***************************************
*     Vars with External Linkage
***************************************/

extern uint8 uatr_initVar;


/***************************************
*              Registers
***************************************/

#define uatr_CTRL_REG               (*(reg32 *) uatr_SCB__CTRL)
#define uatr_CTRL_PTR               ( (reg32 *) uatr_SCB__CTRL)

#define uatr_STATUS_REG             (*(reg32 *) uatr_SCB__STATUS)
#define uatr_STATUS_PTR             ( (reg32 *) uatr_SCB__STATUS)

#if (!uatr_CY_SCBIP_V1)
    #define uatr_SPI_CTRL_REG           (*(reg32 *) uatr_SCB__SPI_CTRL)
    #define uatr_SPI_CTRL_PTR           ( (reg32 *) uatr_SCB__SPI_CTRL)

    #define uatr_SPI_STATUS_REG         (*(reg32 *) uatr_SCB__SPI_STATUS)
    #define uatr_SPI_STATUS_PTR         ( (reg32 *) uatr_SCB__SPI_STATUS)

    #define uatr_UART_CTRL_REG          (*(reg32 *) uatr_SCB__UART_CTRL)
    #define uatr_UART_CTRL_PTR          ( (reg32 *) uatr_SCB__UART_CTRL)

    #define uatr_UART_TX_CTRL_REG       (*(reg32 *) uatr_SCB__UART_TX_CTRL)
    #define uatr_UART_TX_CTRL_PTR       ( (reg32 *) uatr_SCB__UART_TX_CTRL)

    #define uatr_UART_RX_CTRL_REG       (*(reg32 *) uatr_SCB__UART_RX_CTRL)
    #define uatr_UART_RX_CTRL_PTR       ( (reg32 *) uatr_SCB__UART_RX_CTRL)

    #define uatr_UART_RX_STATUS_REG     (*(reg32 *) uatr_SCB__UART_RX_STATUS)
    #define uatr_UART_RX_STATUS_PTR     ( (reg32 *) uatr_SCB__UART_RX_STATUS)
#endif /* (!uatr_CY_SCBIP_V1) */

#if !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
    #define uatr_UART_FLOW_CTRL_REG     (*(reg32 *) uatr_SCB__UART_FLOW_CTRL)
    #define uatr_UART_FLOW_CTRL_PTR     ( (reg32 *) uatr_SCB__UART_FLOW_CTRL)
#endif /* !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */

#define uatr_I2C_CTRL_REG           (*(reg32 *) uatr_SCB__I2C_CTRL)
#define uatr_I2C_CTRL_PTR           ( (reg32 *) uatr_SCB__I2C_CTRL)

#define uatr_I2C_STATUS_REG         (*(reg32 *) uatr_SCB__I2C_STATUS)
#define uatr_I2C_STATUS_PTR         ( (reg32 *) uatr_SCB__I2C_STATUS)

#define uatr_I2C_MASTER_CMD_REG     (*(reg32 *) uatr_SCB__I2C_M_CMD)
#define uatr_I2C_MASTER_CMD_PTR     ( (reg32 *) uatr_SCB__I2C_M_CMD)

#define uatr_I2C_SLAVE_CMD_REG      (*(reg32 *) uatr_SCB__I2C_S_CMD)
#define uatr_I2C_SLAVE_CMD_PTR      ( (reg32 *) uatr_SCB__I2C_S_CMD)

#define uatr_I2C_CFG_REG            (*(reg32 *) uatr_SCB__I2C_CFG)
#define uatr_I2C_CFG_PTR            ( (reg32 *) uatr_SCB__I2C_CFG)

#define uatr_TX_CTRL_REG            (*(reg32 *) uatr_SCB__TX_CTRL)
#define uatr_TX_CTRL_PTR            ( (reg32 *) uatr_SCB__TX_CTRL)

#define uatr_TX_FIFO_CTRL_REG       (*(reg32 *) uatr_SCB__TX_FIFO_CTRL)
#define uatr_TX_FIFO_CTRL_PTR       ( (reg32 *) uatr_SCB__TX_FIFO_CTRL)

#define uatr_TX_FIFO_STATUS_REG     (*(reg32 *) uatr_SCB__TX_FIFO_STATUS)
#define uatr_TX_FIFO_STATUS_PTR     ( (reg32 *) uatr_SCB__TX_FIFO_STATUS)

#define uatr_TX_FIFO_WR_REG         (*(reg32 *) uatr_SCB__TX_FIFO_WR)
#define uatr_TX_FIFO_WR_PTR         ( (reg32 *) uatr_SCB__TX_FIFO_WR)

#define uatr_RX_CTRL_REG            (*(reg32 *) uatr_SCB__RX_CTRL)
#define uatr_RX_CTRL_PTR            ( (reg32 *) uatr_SCB__RX_CTRL)

#define uatr_RX_FIFO_CTRL_REG       (*(reg32 *) uatr_SCB__RX_FIFO_CTRL)
#define uatr_RX_FIFO_CTRL_PTR       ( (reg32 *) uatr_SCB__RX_FIFO_CTRL)

#define uatr_RX_FIFO_STATUS_REG     (*(reg32 *) uatr_SCB__RX_FIFO_STATUS)
#define uatr_RX_FIFO_STATUS_PTR     ( (reg32 *) uatr_SCB__RX_FIFO_STATUS)

#define uatr_RX_MATCH_REG           (*(reg32 *) uatr_SCB__RX_MATCH)
#define uatr_RX_MATCH_PTR           ( (reg32 *) uatr_SCB__RX_MATCH)

#define uatr_RX_FIFO_RD_REG         (*(reg32 *) uatr_SCB__RX_FIFO_RD)
#define uatr_RX_FIFO_RD_PTR         ( (reg32 *) uatr_SCB__RX_FIFO_RD)

#define uatr_RX_FIFO_RD_SILENT_REG  (*(reg32 *) uatr_SCB__RX_FIFO_RD_SILENT)
#define uatr_RX_FIFO_RD_SILENT_PTR  ( (reg32 *) uatr_SCB__RX_FIFO_RD_SILENT)

#define uatr_EZBUF_DATA00_REG       (*(reg32 *) uatr_SCB__EZ_DATA00)
#define uatr_EZBUF_DATA00_PTR       ( (reg32 *) uatr_SCB__EZ_DATA00)

#define uatr_INTR_CAUSE_REG         (*(reg32 *) uatr_SCB__INTR_CAUSE)
#define uatr_INTR_CAUSE_PTR         ( (reg32 *) uatr_SCB__INTR_CAUSE)

#define uatr_INTR_I2C_EC_REG        (*(reg32 *) uatr_SCB__INTR_I2C_EC)
#define uatr_INTR_I2C_EC_PTR        ( (reg32 *) uatr_SCB__INTR_I2C_EC)

#define uatr_INTR_I2C_EC_MASK_REG   (*(reg32 *) uatr_SCB__INTR_I2C_EC_MASK)
#define uatr_INTR_I2C_EC_MASK_PTR   ( (reg32 *) uatr_SCB__INTR_I2C_EC_MASK)

#define uatr_INTR_I2C_EC_MASKED_REG (*(reg32 *) uatr_SCB__INTR_I2C_EC_MASKED)
#define uatr_INTR_I2C_EC_MASKED_PTR ( (reg32 *) uatr_SCB__INTR_I2C_EC_MASKED)

#if (!uatr_CY_SCBIP_V1)
    #define uatr_INTR_SPI_EC_REG        (*(reg32 *) uatr_SCB__INTR_SPI_EC)
    #define uatr_INTR_SPI_EC_PTR        ( (reg32 *) uatr_SCB__INTR_SPI_EC)

    #define uatr_INTR_SPI_EC_MASK_REG   (*(reg32 *) uatr_SCB__INTR_SPI_EC_MASK)
    #define uatr_INTR_SPI_EC_MASK_PTR   ( (reg32 *) uatr_SCB__INTR_SPI_EC_MASK)

    #define uatr_INTR_SPI_EC_MASKED_REG (*(reg32 *) uatr_SCB__INTR_SPI_EC_MASKED)
    #define uatr_INTR_SPI_EC_MASKED_PTR ( (reg32 *) uatr_SCB__INTR_SPI_EC_MASKED)
#endif /* (!uatr_CY_SCBIP_V1) */

#define uatr_INTR_MASTER_REG        (*(reg32 *) uatr_SCB__INTR_M)
#define uatr_INTR_MASTER_PTR        ( (reg32 *) uatr_SCB__INTR_M)

#define uatr_INTR_MASTER_SET_REG    (*(reg32 *) uatr_SCB__INTR_M_SET)
#define uatr_INTR_MASTER_SET_PTR    ( (reg32 *) uatr_SCB__INTR_M_SET)

#define uatr_INTR_MASTER_MASK_REG   (*(reg32 *) uatr_SCB__INTR_M_MASK)
#define uatr_INTR_MASTER_MASK_PTR   ( (reg32 *) uatr_SCB__INTR_M_MASK)

#define uatr_INTR_MASTER_MASKED_REG (*(reg32 *) uatr_SCB__INTR_M_MASKED)
#define uatr_INTR_MASTER_MASKED_PTR ( (reg32 *) uatr_SCB__INTR_M_MASKED)

#define uatr_INTR_SLAVE_REG         (*(reg32 *) uatr_SCB__INTR_S)
#define uatr_INTR_SLAVE_PTR         ( (reg32 *) uatr_SCB__INTR_S)

#define uatr_INTR_SLAVE_SET_REG     (*(reg32 *) uatr_SCB__INTR_S_SET)
#define uatr_INTR_SLAVE_SET_PTR     ( (reg32 *) uatr_SCB__INTR_S_SET)

#define uatr_INTR_SLAVE_MASK_REG    (*(reg32 *) uatr_SCB__INTR_S_MASK)
#define uatr_INTR_SLAVE_MASK_PTR    ( (reg32 *) uatr_SCB__INTR_S_MASK)

#define uatr_INTR_SLAVE_MASKED_REG  (*(reg32 *) uatr_SCB__INTR_S_MASKED)
#define uatr_INTR_SLAVE_MASKED_PTR  ( (reg32 *) uatr_SCB__INTR_S_MASKED)

#define uatr_INTR_TX_REG            (*(reg32 *) uatr_SCB__INTR_TX)
#define uatr_INTR_TX_PTR            ( (reg32 *) uatr_SCB__INTR_TX)

#define uatr_INTR_TX_SET_REG        (*(reg32 *) uatr_SCB__INTR_TX_SET)
#define uatr_INTR_TX_SET_PTR        ( (reg32 *) uatr_SCB__INTR_TX_SET)

#define uatr_INTR_TX_MASK_REG       (*(reg32 *) uatr_SCB__INTR_TX_MASK)
#define uatr_INTR_TX_MASK_PTR       ( (reg32 *) uatr_SCB__INTR_TX_MASK)

#define uatr_INTR_TX_MASKED_REG     (*(reg32 *) uatr_SCB__INTR_TX_MASKED)
#define uatr_INTR_TX_MASKED_PTR     ( (reg32 *) uatr_SCB__INTR_TX_MASKED)

#define uatr_INTR_RX_REG            (*(reg32 *) uatr_SCB__INTR_RX)
#define uatr_INTR_RX_PTR            ( (reg32 *) uatr_SCB__INTR_RX)

#define uatr_INTR_RX_SET_REG        (*(reg32 *) uatr_SCB__INTR_RX_SET)
#define uatr_INTR_RX_SET_PTR        ( (reg32 *) uatr_SCB__INTR_RX_SET)

#define uatr_INTR_RX_MASK_REG       (*(reg32 *) uatr_SCB__INTR_RX_MASK)
#define uatr_INTR_RX_MASK_PTR       ( (reg32 *) uatr_SCB__INTR_RX_MASK)

#define uatr_INTR_RX_MASKED_REG     (*(reg32 *) uatr_SCB__INTR_RX_MASKED)
#define uatr_INTR_RX_MASKED_PTR     ( (reg32 *) uatr_SCB__INTR_RX_MASKED)

#if (uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
    #define uatr_FF_DATA_NR_LOG2_PLUS1_MASK (0x0Fu) /* FF_DATA_NR_LOG2_PLUS1 = 4, MASK = 2^4 - 1 = 15 */
    #define uatr_FF_DATA_NR_LOG2_MASK       (0x07u) /* FF_DATA_NR_LOG2 = 3, MASK = 2^3 - 1 = 7 */
#else
    #define uatr_FF_DATA_NR_LOG2_PLUS1_MASK (0x1Fu) /* FF_DATA_NR_LOG2_PLUS1 = 5, MASK = 2^5 - 1 = 31 */
    #define uatr_FF_DATA_NR_LOG2_MASK       (0x0Fu) /* FF_DATA_NR_LOG2 = 4, MASK = 2^4 - 1 = 15 */
#endif /* (uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */


/***************************************
*        Registers Constants
***************************************/

#if (uatr_SCB_IRQ_INTERNAL)
    #define uatr_ISR_NUMBER     ((uint8) uatr_SCB_IRQ__INTC_NUMBER)
    #define uatr_ISR_PRIORITY   ((uint8) uatr_SCB_IRQ__INTC_PRIOR_NUM)
#endif /* (uatr_SCB_IRQ_INTERNAL) */

#if (uatr_UART_RX_WAKEUP_IRQ)
    #define uatr_RX_WAKE_ISR_NUMBER     ((uint8) uatr_RX_WAKEUP_IRQ__INTC_NUMBER)
    #define uatr_RX_WAKE_ISR_PRIORITY   ((uint8) uatr_RX_WAKEUP_IRQ__INTC_PRIOR_NUM)
#endif /* (uatr_UART_RX_WAKEUP_IRQ) */

/* uatr_CTRL_REG */
#define uatr_CTRL_OVS_POS           (0u)  /* [3:0]   Oversampling factor                 */
#define uatr_CTRL_EC_AM_MODE_POS    (8u)  /* [8]     Externally clocked address match    */
#define uatr_CTRL_EC_OP_MODE_POS    (9u)  /* [9]     Externally clocked operation mode   */
#define uatr_CTRL_EZBUF_MODE_POS    (10u) /* [10]    EZ buffer is enabled                */
#if !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
    #define uatr_CTRL_BYTE_MODE_POS (11u) /* [11]    Determines the number of bits per FIFO data element */
#endif /* !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */
#define uatr_CTRL_ADDR_ACCEPT_POS   (16u) /* [16]    Put matched address in RX FIFO       */
#define uatr_CTRL_BLOCK_POS         (17u) /* [17]    Ext and Int logic to resolve collide */
#define uatr_CTRL_MODE_POS          (24u) /* [25:24] Operation mode                       */
#define uatr_CTRL_ENABLED_POS       (31u) /* [31]    Enable SCB block                     */
#define uatr_CTRL_OVS_MASK          ((uint32) 0x0Fu)
#define uatr_CTRL_EC_AM_MODE        ((uint32) 0x01u << uatr_CTRL_EC_AM_MODE_POS)
#define uatr_CTRL_EC_OP_MODE        ((uint32) 0x01u << uatr_CTRL_EC_OP_MODE_POS)
#define uatr_CTRL_EZBUF_MODE        ((uint32) 0x01u << uatr_CTRL_EZBUF_MODE_POS)
#if !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
    #define uatr_CTRL_BYTE_MODE ((uint32) 0x01u << uatr_CTRL_BYTE_MODE_POS)
#endif /* !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */
#define uatr_CTRL_ADDR_ACCEPT       ((uint32) 0x01u << uatr_CTRL_ADDR_ACCEPT_POS)
#define uatr_CTRL_BLOCK             ((uint32) 0x01u << uatr_CTRL_BLOCK_POS)
#define uatr_CTRL_MODE_MASK         ((uint32) 0x03u << uatr_CTRL_MODE_POS)
#define uatr_CTRL_MODE_I2C          ((uint32) 0x00u)
#define uatr_CTRL_MODE_SPI          ((uint32) 0x01u << uatr_CTRL_MODE_POS)
#define uatr_CTRL_MODE_UART         ((uint32) 0x02u << uatr_CTRL_MODE_POS)
#define uatr_CTRL_ENABLED           ((uint32) 0x01u << uatr_CTRL_ENABLED_POS)

/* uatr_STATUS_REG */
#define uatr_STATUS_EC_BUSY_POS     (0u)  /* [0] Bus busy. Externally clocked logic access to EZ memory */
#define uatr_STATUS_EC_BUSY         ((uint32) 0x0Fu)

/* uatr_SPI_CTRL_REG  */
#define uatr_SPI_CTRL_CONTINUOUS_POS        (0u)  /* [0]     Continuous or Separated SPI data transfers */
#define uatr_SPI_CTRL_SELECT_PRECEDE_POS    (1u)  /* [1]     Precedes or coincides start of data frame  */
#define uatr_SPI_CTRL_CPHA_POS              (2u)  /* [2]     SCLK phase                                 */
#define uatr_SPI_CTRL_CPOL_POS              (3u)  /* [3]     SCLK polarity                              */
#define uatr_SPI_CTRL_LATE_MISO_SAMPLE_POS  (4u)  /* [4]     Late MISO sample enabled                   */
#if !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
    #define uatr_SPI_CTRL_SCLK_CONTINUOUS_POS   (5u)  /* [5]     Enable continuous SCLK generation */
    #define uatr_SPI_CTRL_SSEL0_POLARITY_POS    (8u)  /* [8]     SS0 polarity                      */
    #define uatr_SPI_CTRL_SSEL1_POLARITY_POS    (9u)  /* [9]     SS1 polarity                      */
    #define uatr_SPI_CTRL_SSEL2_POLARITY_POS    (10u) /* [10]    SS2 polarity                      */
    #define uatr_SPI_CTRL_SSEL3_POLARITY_POS    (11u) /* [11]    SS3 polarity                      */
#endif /* !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */
#define uatr_SPI_CTRL_LOOPBACK_POS          (16u) /* [16]    Local loop-back control enabled            */
#define uatr_SPI_CTRL_MODE_POS              (24u) /* [25:24] Submode of SPI operation                   */
#define uatr_SPI_CTRL_SLAVE_SELECT_POS      (26u) /* [27:26] Selects SPI SS signal                      */
#define uatr_SPI_CTRL_MASTER_MODE_POS       (31u) /* [31]    Master mode enabled                        */
#define uatr_SPI_CTRL_CONTINUOUS            ((uint32) 0x01u)
#define uatr_SPI_CTRL_SELECT_PRECEDE        ((uint32) 0x01u << uatr_SPI_CTRL_SELECT_PRECEDE_POS)
#define uatr_SPI_CTRL_SCLK_MODE_MASK        ((uint32) 0x03u << uatr_SPI_CTRL_CPHA_POS)
#define uatr_SPI_CTRL_CPHA                  ((uint32) 0x01u << uatr_SPI_CTRL_CPHA_POS)
#define uatr_SPI_CTRL_CPOL                  ((uint32) 0x01u << uatr_SPI_CTRL_CPOL_POS)
#define uatr_SPI_CTRL_LATE_MISO_SAMPLE      ((uint32) 0x01u << \
                                                                    uatr_SPI_CTRL_LATE_MISO_SAMPLE_POS)
#if !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
    #define uatr_SPI_CTRL_SCLK_CONTINUOUS  ((uint32) 0x01u << uatr_SPI_CTRL_SCLK_CONTINUOUS_POS)
    #define uatr_SPI_CTRL_SSEL0_POLARITY   ((uint32) 0x01u << uatr_SPI_CTRL_SSEL0_POLARITY_POS)
    #define uatr_SPI_CTRL_SSEL1_POLARITY   ((uint32) 0x01u << uatr_SPI_CTRL_SSEL1_POLARITY_POS)
    #define uatr_SPI_CTRL_SSEL2_POLARITY   ((uint32) 0x01u << uatr_SPI_CTRL_SSEL2_POLARITY_POS)
    #define uatr_SPI_CTRL_SSEL3_POLARITY   ((uint32) 0x01u << uatr_SPI_CTRL_SSEL3_POLARITY_POS)
    #define uatr_SPI_CTRL_SSEL_POLARITY_MASK ((uint32)0x0Fu << uatr_SPI_CTRL_SSEL0_POLARITY_POS)
#endif /* !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */

#define uatr_SPI_CTRL_LOOPBACK              ((uint32) 0x01u << uatr_SPI_CTRL_LOOPBACK_POS)
#define uatr_SPI_CTRL_MODE_MASK             ((uint32) 0x03u << uatr_SPI_CTRL_MODE_POS)
#define uatr_SPI_CTRL_MODE_MOTOROLA         ((uint32) 0x00u)
#define uatr_SPI_CTRL_MODE_TI               ((uint32) 0x01u << uatr_CTRL_MODE_POS)
#define uatr_SPI_CTRL_MODE_NS               ((uint32) 0x02u << uatr_CTRL_MODE_POS)
#define uatr_SPI_CTRL_SLAVE_SELECT_MASK     ((uint32) 0x03u << uatr_SPI_CTRL_SLAVE_SELECT_POS)
#define uatr_SPI_CTRL_SLAVE_SELECT0         ((uint32) 0x00u)
#define uatr_SPI_CTRL_SLAVE_SELECT1         ((uint32) 0x01u << uatr_SPI_CTRL_SLAVE_SELECT_POS)
#define uatr_SPI_CTRL_SLAVE_SELECT2         ((uint32) 0x02u << uatr_SPI_CTRL_SLAVE_SELECT_POS)
#define uatr_SPI_CTRL_SLAVE_SELECT3         ((uint32) 0x03u << uatr_SPI_CTRL_SLAVE_SELECT_POS)
#define uatr_SPI_CTRL_MASTER                ((uint32) 0x01u << uatr_SPI_CTRL_MASTER_MODE_POS)
#define uatr_SPI_CTRL_SLAVE                 ((uint32) 0x00u)

/* uatr_SPI_STATUS_REG  */
#define uatr_SPI_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy - slave selected */
#define uatr_SPI_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EzAddress                 */
#define uatr_SPI_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define uatr_SPI_STATUS_EZBUF_ADDR_MASK ((uint32) 0xFFu << uatr_I2C_STATUS_EZBUF_ADDR_POS)

/* uatr_UART_CTRL */
#define uatr_UART_CTRL_LOOPBACK_POS         (16u) /* [16] Loop-back    */
#define uatr_UART_CTRL_MODE_POS             (24u) /* [24] UART subMode */
#define uatr_UART_CTRL_LOOPBACK             ((uint32) 0x01u << uatr_UART_CTRL_LOOPBACK_POS)
#define uatr_UART_CTRL_MODE_UART_STD        ((uint32) 0x00u)
#define uatr_UART_CTRL_MODE_UART_SMARTCARD  ((uint32) 0x01u << uatr_UART_CTRL_MODE_POS)
#define uatr_UART_CTRL_MODE_UART_IRDA       ((uint32) 0x02u << uatr_UART_CTRL_MODE_POS)
#define uatr_UART_CTRL_MODE_MASK            ((uint32) 0x03u << uatr_UART_CTRL_MODE_POS)

/* uatr_UART_TX_CTRL */
#define uatr_UART_TX_CTRL_STOP_BITS_POS         (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 period */
#define uatr_UART_TX_CTRL_PARITY_POS            (4u)  /* [4]   Parity bit                              */
#define uatr_UART_TX_CTRL_PARITY_ENABLED_POS    (5u)  /* [5]   Parity enable                           */
#define uatr_UART_TX_CTRL_RETRY_ON_NACK_POS     (8u)  /* [8]   Smart Card: re-send frame on NACK       */
#define uatr_UART_TX_CTRL_ONE_STOP_BIT          ((uint32) 0x01u)
#define uatr_UART_TX_CTRL_ONE_HALF_STOP_BITS    ((uint32) 0x02u)
#define uatr_UART_TX_CTRL_TWO_STOP_BITS         ((uint32) 0x03u)
#define uatr_UART_TX_CTRL_STOP_BITS_MASK        ((uint32) 0x07u)
#define uatr_UART_TX_CTRL_PARITY                ((uint32) 0x01u << \
                                                                    uatr_UART_TX_CTRL_PARITY_POS)
#define uatr_UART_TX_CTRL_PARITY_ENABLED        ((uint32) 0x01u << \
                                                                    uatr_UART_TX_CTRL_PARITY_ENABLED_POS)
#define uatr_UART_TX_CTRL_RETRY_ON_NACK         ((uint32) 0x01u << \
                                                                    uatr_UART_TX_CTRL_RETRY_ON_NACK_POS)

/* uatr_UART_RX_CTRL */
#define uatr_UART_RX_CTRL_STOP_BITS_POS             (0u)  /* [2:0] Stop bits: (Stop bits + 1) * 0.5 period*/
#define uatr_UART_RX_CTRL_PARITY_POS                (4u)  /* [4]   Parity bit                             */
#define uatr_UART_RX_CTRL_PARITY_ENABLED_POS        (5u)  /* [5]   Parity enable                          */
#define uatr_UART_RX_CTRL_POLARITY_POS              (6u)  /* [6]   IrDA: inverts polarity of RX signal    */
#define uatr_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS    (8u)  /* [8]   Drop and lost RX FIFO on parity error  */
#define uatr_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS     (9u)  /* [9]   Drop and lost RX FIFO on frame error   */
#define uatr_UART_RX_CTRL_MP_MODE_POS               (10u) /* [10]  Multi-processor mode                   */
#define uatr_UART_RX_CTRL_LIN_MODE_POS              (12u) /* [12]  Lin mode: applicable for UART Standard */
#define uatr_UART_RX_CTRL_SKIP_START_POS            (13u) /* [13]  Skip start not: only for UART Standard */
#define uatr_UART_RX_CTRL_BREAK_WIDTH_POS           (16u) /* [19:16]  Break width: (Break width + 1)      */
#define uatr_UART_TX_CTRL_ONE_STOP_BIT              ((uint32) 0x01u)
#define uatr_UART_TX_CTRL_ONE_HALF_STOP_BITS        ((uint32) 0x02u)
#define uatr_UART_TX_CTRL_TWO_STOP_BITS             ((uint32) 0x03u)
#define uatr_UART_RX_CTRL_STOP_BITS_MASK            ((uint32) 0x07u)
#define uatr_UART_RX_CTRL_PARITY                    ((uint32) 0x01u << \
                                                                    uatr_UART_RX_CTRL_PARITY_POS)
#define uatr_UART_RX_CTRL_PARITY_ENABLED            ((uint32) 0x01u << \
                                                                    uatr_UART_RX_CTRL_PARITY_ENABLED_POS)
#define uatr_UART_RX_CTRL_POLARITY                  ((uint32) 0x01u << \
                                                                    uatr_UART_RX_CTRL_POLARITY_POS)
#define uatr_UART_RX_CTRL_DROP_ON_PARITY_ERR        ((uint32) 0x01u << \
                                                                   uatr_UART_RX_CTRL_DROP_ON_PARITY_ERR_POS)
#define uatr_UART_RX_CTRL_DROP_ON_FRAME_ERR         ((uint32) 0x01u << \
                                                                    uatr_UART_RX_CTRL_DROP_ON_FRAME_ERR_POS)
#define uatr_UART_RX_CTRL_MP_MODE                   ((uint32) 0x01u << \
                                                                    uatr_UART_RX_CTRL_MP_MODE_POS)
#define uatr_UART_RX_CTRL_LIN_MODE                  ((uint32) 0x01u << \
                                                                    uatr_UART_RX_CTRL_LIN_MODE_POS)
#define uatr_UART_RX_CTRL_SKIP_START                ((uint32) 0x01u << \
                                                                    uatr_UART_RX_CTRL_SKIP_START_POS)
#define uatr_UART_RX_CTRL_BREAK_WIDTH_MASK          ((uint32) 0x0Fu << \
                                                                    uatr_UART_RX_CTRL_BREAK_WIDTH_POS)
/* uatr_UART_RX_STATUS_REG */
#define uatr_UART_RX_STATUS_BR_COUNTER_POS     (0u)  /* [11:0] Baud Rate counter */
#define uatr_UART_RX_STATUS_BR_COUNTER_MASK    ((uint32) 0xFFFu)

#if !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
    /* uatr_UART_FLOW_CTRL_REG */
    #define uatr_UART_FLOW_CTRL_TRIGGER_LEVEL_POS    (0u)  /* [7:0] RTS RX FIFO trigger level         */
    #define uatr_UART_FLOW_CTRL_RTS_POLARITY_POS     (16u) /* [16]  Polarity of the RTS output signal */
    #define uatr_UART_FLOW_CTRL_CTS_POLARITY_POS     (24u) /* [24]  Polarity of the CTS input signal  */
    #define uatr_UART_FLOW_CTRL_CTS_ENABLED_POS      (25u) /* [25]  Enable CTS signal                 */
    #define uatr_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK   ((uint32) uatr_FF_DATA_NR_LOG2_MASK)
    #define uatr_UART_FLOW_CTRL_RTS_POLARITY         ((uint32) 0x01u << \
                                                                       uatr_UART_FLOW_CTRL_RTS_POLARITY_POS)
    #define uatr_UART_FLOW_CTRL_CTS_POLARITY         ((uint32) 0x01u << \
                                                                       uatr_UART_FLOW_CTRL_CTS_POLARITY_POS)
    #define uatr_UART_FLOW_CTRL_CTS_ENABLE           ((uint32) 0x01u << \
                                                                       uatr_UART_FLOW_CTRL_CTS_ENABLED_POS)
#endif /* !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */

/* uatr_I2C_CTRL */
#define uatr_I2C_CTRL_HIGH_PHASE_OVS_POS           (0u)   /* [3:0] Oversampling factor high: master only */
#define uatr_I2C_CTRL_LOW_PHASE_OVS_POS            (4u)   /* [7:4] Oversampling factor low:  master only */
#define uatr_I2C_CTRL_M_READY_DATA_ACK_POS         (8u)   /* [8]   Master ACKs data while RX FIFO != FULL*/
#define uatr_I2C_CTRL_M_NOT_READY_DATA_NACK_POS    (9u)   /* [9]   Master NACKs data if RX FIFO ==  FULL */
#define uatr_I2C_CTRL_S_GENERAL_IGNORE_POS         (11u)  /* [11]  Slave ignores General call            */
#define uatr_I2C_CTRL_S_READY_ADDR_ACK_POS         (12u)  /* [12]  Slave ACKs Address if RX FIFO != FULL */
#define uatr_I2C_CTRL_S_READY_DATA_ACK_POS         (13u)  /* [13]  Slave ACKs data while RX FIFO == FULL */
#define uatr_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS    (14u)  /* [14]  Slave NACKs address if RX FIFO == FULL*/
#define uatr_I2C_CTRL_S_NOT_READY_DATA_NACK_POS    (15u)  /* [15]  Slave NACKs data if RX FIFO is  FULL  */
#define uatr_I2C_CTRL_LOOPBACK_POS                 (16u)  /* [16]  Loop-back                             */
#define uatr_I2C_CTRL_SLAVE_MODE_POS               (30u)  /* [30]  Slave mode enabled                    */
#define uatr_I2C_CTRL_MASTER_MODE_POS              (31u)  /* [31]  Master mode enabled                   */
#define uatr_I2C_CTRL_HIGH_PHASE_OVS_MASK  ((uint32) 0x0Fu)
#define uatr_I2C_CTRL_LOW_PHASE_OVS_MASK   ((uint32) 0x0Fu << \
                                                                uatr_I2C_CTRL_LOW_PHASE_OVS_POS)
#define uatr_I2C_CTRL_M_READY_DATA_ACK      ((uint32) 0x01u << \
                                                                uatr_I2C_CTRL_M_READY_DATA_ACK_POS)
#define uatr_I2C_CTRL_M_NOT_READY_DATA_NACK ((uint32) 0x01u << \
                                                                uatr_I2C_CTRL_M_NOT_READY_DATA_NACK_POS)
#define uatr_I2C_CTRL_S_GENERAL_IGNORE      ((uint32) 0x01u << \
                                                                uatr_I2C_CTRL_S_GENERAL_IGNORE_POS)
#define uatr_I2C_CTRL_S_READY_ADDR_ACK      ((uint32) 0x01u << \
                                                                uatr_I2C_CTRL_S_READY_ADDR_ACK_POS)
#define uatr_I2C_CTRL_S_READY_DATA_ACK      ((uint32) 0x01u << \
                                                                uatr_I2C_CTRL_S_READY_DATA_ACK_POS)
#define uatr_I2C_CTRL_S_NOT_READY_ADDR_NACK ((uint32) 0x01u << \
                                                                uatr_I2C_CTRL_S_NOT_READY_ADDR_NACK_POS)
#define uatr_I2C_CTRL_S_NOT_READY_DATA_NACK ((uint32) 0x01u << \
                                                                uatr_I2C_CTRL_S_NOT_READY_DATA_NACK_POS)
#define uatr_I2C_CTRL_LOOPBACK              ((uint32) 0x01u << \
                                                                uatr_I2C_CTRL_LOOPBACK_POS)
#define uatr_I2C_CTRL_SLAVE_MODE            ((uint32) 0x01u << \
                                                                uatr_I2C_CTRL_SLAVE_MODE_POS)
#define uatr_I2C_CTRL_MASTER_MODE           ((uint32) 0x01u << \
                                                                uatr_I2C_CTRL_MASTER_MODE_POS)
#define uatr_I2C_CTRL_SLAVE_MASTER_MODE_MASK    ((uint32) 0x03u << \
                                                                uatr_I2C_CTRL_SLAVE_MODE_POS)

/* uatr_I2C_STATUS_REG  */
#define uatr_I2C_STATUS_BUS_BUSY_POS    (0u)  /* [0]    Bus busy: internally clocked */
#define uatr_I2C_STATUS_S_READ_POS      (4u)  /* [4]    Slave is read by master      */
#define uatr_I2C_STATUS_M_READ_POS      (5u)  /* [5]    Master reads Slave           */
#define uatr_I2C_STATUS_EZBUF_ADDR_POS  (8u)  /* [15:8] EZAddress                    */
#define uatr_I2C_STATUS_BUS_BUSY        ((uint32) 0x01u)
#define uatr_I2C_STATUS_S_READ          ((uint32) 0x01u << uatr_I2C_STATUS_S_READ_POS)
#define uatr_I2C_STATUS_M_READ          ((uint32) 0x01u << uatr_I2C_STATUS_M_READ_POS)
#define uatr_I2C_STATUS_EZBUF_ADDR_MASK ((uint32) 0xFFu << uatr_I2C_STATUS_EZBUF_ADDR_POS)

/* uatr_I2C_MASTER_CMD_REG */
#define uatr_I2C_MASTER_CMD_M_START_POS             (0u)  /* [0] Master generate Start                */
#define uatr_I2C_MASTER_CMD_M_START_ON_IDLE_POS     (1u)  /* [1] Master generate Start if bus is free */
#define uatr_I2C_MASTER_CMD_M_ACK_POS               (2u)  /* [2] Master generate ACK                  */
#define uatr_I2C_MASTER_CMD_M_NACK_POS              (3u)  /* [3] Master generate NACK                 */
#define uatr_I2C_MASTER_CMD_M_STOP_POS              (4u)  /* [4] Master generate Stop                 */
#define uatr_I2C_MASTER_CMD_M_START         ((uint32) 0x01u)
#define uatr_I2C_MASTER_CMD_M_START_ON_IDLE ((uint32) 0x01u << \
                                                                   uatr_I2C_MASTER_CMD_M_START_ON_IDLE_POS)
#define uatr_I2C_MASTER_CMD_M_ACK           ((uint32) 0x01u << \
                                                                   uatr_I2C_MASTER_CMD_M_ACK_POS)
#define uatr_I2C_MASTER_CMD_M_NACK          ((uint32) 0x01u << \
                                                                    uatr_I2C_MASTER_CMD_M_NACK_POS)
#define uatr_I2C_MASTER_CMD_M_STOP          ((uint32) 0x01u << \
                                                                    uatr_I2C_MASTER_CMD_M_STOP_POS)

/* uatr_I2C_SLAVE_CMD_REG  */
#define uatr_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define uatr_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define uatr_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define uatr_I2C_SLAVE_CMD_S_NACK       ((uint32) 0x01u << uatr_I2C_SLAVE_CMD_S_NACK_POS)

#define uatr_I2C_SLAVE_CMD_S_ACK_POS    (0u)  /* [0] Slave generate ACK  */
#define uatr_I2C_SLAVE_CMD_S_NACK_POS   (1u)  /* [1] Slave generate NACK */
#define uatr_I2C_SLAVE_CMD_S_ACK        ((uint32) 0x01u)
#define uatr_I2C_SLAVE_CMD_S_NACK       ((uint32) 0x01u << uatr_I2C_SLAVE_CMD_S_NACK_POS)

/* uatr_I2C_CFG_REG */
#if (uatr_CY_SCBIP_V0)
#define uatr_I2C_CFG_SDA_FILT_HYS_POS           (0u)  /* [1:0]   Trim bits for the I2C SDA filter         */
#define uatr_I2C_CFG_SDA_FILT_TRIM_POS          (2u)  /* [3:2]   Trim bits for the I2C SDA filter         */
#define uatr_I2C_CFG_SCL_FILT_HYS_POS           (4u)  /* [5:4]   Trim bits for the I2C SCL filter         */
#define uatr_I2C_CFG_SCL_FILT_TRIM_POS          (6u)  /* [7:6]   Trim bits for the I2C SCL filter         */
#define uatr_I2C_CFG_SDA_FILT_OUT_HYS_POS       (8u)  /* [9:8]   Trim bits for I2C SDA filter output path */
#define uatr_I2C_CFG_SDA_FILT_OUT_TRIM_POS      (10u) /* [11:10] Trim bits for I2C SDA filter output path */
#define uatr_I2C_CFG_SDA_FILT_HS_POS            (16u) /* [16]    '0': 50 ns filter, '1': 10 ns filter     */
#define uatr_I2C_CFG_SDA_FILT_ENABLED_POS       (17u) /* [17]    I2C SDA filter enabled                   */
#define uatr_I2C_CFG_SCL_FILT_HS_POS            (24u) /* [24]    '0': 50 ns filter, '1': 10 ns filter     */
#define uatr_I2C_CFG_SCL_FILT_ENABLED_POS       (25u) /* [25]    I2C SCL filter enabled                   */
#define uatr_I2C_CFG_SDA_FILT_OUT_HS_POS        (26u) /* [26]    '0': 50 ns filter, '1': 10 ns filter     */
#define uatr_I2C_CFG_SDA_FILT_OUT_ENABLED_POS   (27u) /* [27]    I2C SDA output delay filter enabled      */
#define uatr_I2C_CFG_SDA_FILT_HYS_MASK          ((uint32) 0x03u)
#define uatr_I2C_CFG_SDA_FILT_TRIM_MASK         ((uint32) 0x03u << \
                                                                uatr_I2C_CFG_SDA_FILT_TRIM_POS)
#define uatr_I2C_CFG_SCL_FILT_HYS_MASK          ((uint32) 0x03u << \
                                                                uatr_I2C_CFG_SCL_FILT_HYS_POS)
#define uatr_I2C_CFG_SCL_FILT_TRIM_MASK         ((uint32) 0x03u << \
                                                                uatr_I2C_CFG_SCL_FILT_TRIM_POS)
#define uatr_I2C_CFG_SDA_FILT_OUT_HYS_MASK      ((uint32) 0x03u << \
                                                                uatr_I2C_CFG_SDA_FILT_OUT_HYS_POS)
#define uatr_I2C_CFG_SDA_FILT_OUT_TRIM_MASK     ((uint32) 0x03u << \
                                                                uatr_I2C_CFG_SDA_FILT_OUT_TRIM_POS)
#define uatr_I2C_CFG_SDA_FILT_HS                ((uint32) 0x01u << \
                                                                uatr_I2C_CFG_SDA_FILT_HS_POS)
#define uatr_I2C_CFG_SDA_FILT_ENABLED           ((uint32) 0x01u << \
                                                                uatr_I2C_CFG_SDA_FILT_ENABLED_POS)
#define uatr_I2C_CFG_SCL_FILT_HS                ((uint32) 0x01u << \
                                                                uatr_I2C_CFG_SCL_FILT_HS_POS)
#define uatr_I2C_CFG_SCL_FILT_ENABLED           ((uint32) 0x01u << \
                                                                uatr_I2C_CFG_SCL_FILT_ENABLED_POS)
#define uatr_I2C_CFG_SDA_FILT_OUT_HS            ((uint32) 0x01u << \
                                                                uatr_I2C_CFG_SDA_FILT_OUT_HS_POS)
#define uatr_I2C_CFG_SDA_FILT_OUT_ENABLED       ((uint32) 0x01u << \
                                                                uatr_I2C_CFG_SDA_FILT_OUT_ENABLED_POS)
#else
#define uatr_I2C_CFG_SDA_IN_FILT_TRIM_POS   (0u)  /* [1:0] Trim bits for "i2c_sda_in" 50 ns filter */
#define uatr_I2C_CFG_SDA_IN_FILT_SEL_POS    (4u)  /* [4]   "i2c_sda_in" filter delay: 0 ns and 50 ns */
#define uatr_I2C_CFG_SCL_IN_FILT_TRIM_POS   (8u)  /* [9:8] Trim bits for "i2c_scl_in" 50 ns filter */
#define uatr_I2C_CFG_SCL_IN_FILT_SEL_POS    (12u) /* [12]  "i2c_scl_in" filter delay: 0 ns and 50 ns */
#define uatr_I2C_CFG_SDA_OUT_FILT0_TRIM_POS (16u) /* [17:16] Trim bits for "i2c_sda_out" 50 ns filter 0 */
#define uatr_I2C_CFG_SDA_OUT_FILT1_TRIM_POS (18u) /* [19:18] Trim bits for "i2c_sda_out" 50 ns filter 1 */
#define uatr_I2C_CFG_SDA_OUT_FILT2_TRIM_POS (20u) /* [21:20] Trim bits for "i2c_sda_out" 50 ns filter 2 */
#define uatr_I2C_CFG_SDA_OUT_FILT_SEL_POS   (28u) /* [29:28] Cumulative "i2c_sda_out" filter delay: */

#define uatr_I2C_CFG_SDA_IN_FILT_TRIM_MASK  ((uint32) 0x03u)
#define uatr_I2C_CFG_SDA_IN_FILT_SEL        ((uint32) 0x01u << uatr_I2C_CFG_SDA_IN_FILT_SEL_POS)
#define uatr_I2C_CFG_SCL_IN_FILT_TRIM_MASK  ((uint32) 0x03u << \
                                                            uatr_I2C_CFG_SCL_IN_FILT_TRIM_POS)
#define uatr_I2C_CFG_SCL_IN_FILT_SEL        ((uint32) 0x01u << uatr_I2C_CFG_SCL_IN_FILT_SEL_POS)
#define uatr_I2C_CFG_SDA_OUT_FILT0_TRIM_MASK ((uint32) 0x03u << \
                                                            uatr_I2C_CFG_SDA_OUT_FILT0_TRIM_POS)
#define uatr_I2C_CFG_SDA_OUT_FILT1_TRIM_MASK ((uint32) 0x03u << \
                                                            uatr_I2C_CFG_SDA_OUT_FILT1_TRIM_POS)
#define uatr_I2C_CFG_SDA_OUT_FILT2_TRIM_MASK ((uint32) 0x03u << \
                                                            uatr_I2C_CFG_SDA_OUT_FILT2_TRIM_POS)
#define uatr_I2C_CFG_SDA_OUT_FILT_SEL_MASK   ((uint32) 0x03u << \
                                                            uatr_I2C_CFG_SDA_OUT_FILT_SEL_POS)
#endif /* (uatr_CY_SCBIP_V0) */


/* uatr_TX_CTRL_REG */
#define uatr_TX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Data frame width: (Data width - 1) */
#define uatr_TX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define uatr_TX_CTRL_ENABLED_POS        (31u) /* [31]  Transmitter enabled               */
#define uatr_TX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define uatr_TX_CTRL_MSB_FIRST          ((uint32) 0x01u << uatr_TX_CTRL_MSB_FIRST_POS)
#define uatr_TX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define uatr_TX_CTRL_ENABLED            ((uint32) 0x01u << uatr_TX_CTRL_ENABLED_POS)

/* uatr_TX_CTRL_FIFO_REG */
#define uatr_TX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)  /* [2:0] Trigger level                              */
#define uatr_TX_FIFO_CTRL_CLEAR_POS             (16u) /* [16]  Clear TX FIFO: cleared after set           */
#define uatr_TX_FIFO_CTRL_FREEZE_POS            (17u) /* [17]  Freeze TX FIFO: HW do not inc read pointer */
#define uatr_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) uatr_FF_DATA_NR_LOG2_MASK)
#define uatr_TX_FIFO_CTRL_CLEAR                 ((uint32) 0x01u << uatr_TX_FIFO_CTRL_CLEAR_POS)
#define uatr_TX_FIFO_CTRL_FREEZE                ((uint32) 0x01u << uatr_TX_FIFO_CTRL_FREEZE_POS)

/* uatr_TX_FIFO_STATUS_REG */
#define uatr_TX_FIFO_STATUS_USED_POS    (0u)  /* [3:0]   Amount of entries in TX FIFO */
#define uatr_TX_FIFO_SR_VALID_POS       (15u) /* [15]    Shifter status of TX FIFO    */
#define uatr_TX_FIFO_STATUS_RD_PTR_POS  (16u) /* [18:16] TX FIFO read pointer         */
#define uatr_TX_FIFO_STATUS_WR_PTR_POS  (24u) /* [26:24] TX FIFO write pointer        */
#define uatr_TX_FIFO_STATUS_USED_MASK   ((uint32) uatr_FF_DATA_NR_LOG2_PLUS1_MASK)
#define uatr_TX_FIFO_SR_VALID           ((uint32) 0x01u << uatr_TX_FIFO_SR_VALID_POS)
#define uatr_TX_FIFO_STATUS_RD_PTR_MASK ((uint32) uatr_FF_DATA_NR_LOG2_MASK << \
                                                                    uatr_TX_FIFO_STATUS_RD_PTR_POS)
#define uatr_TX_FIFO_STATUS_WR_PTR_MASK ((uint32) uatr_FF_DATA_NR_LOG2_MASK << \
                                                                    uatr_TX_FIFO_STATUS_WR_PTR_POS)

/* uatr_TX_FIFO_WR_REG */
#define uatr_TX_FIFO_WR_POS    (0u)  /* [15:0] Data written into TX FIFO */
#define uatr_TX_FIFO_WR_MASK   ((uint32) 0xFFu)

/* uatr_RX_CTRL_REG */
#define uatr_RX_CTRL_DATA_WIDTH_POS     (0u)  /* [3:0] Data frame width: (Data width - 1) */
#define uatr_RX_CTRL_MSB_FIRST_POS      (8u)  /* [8]   MSB first shifter-out             */
#define uatr_RX_CTRL_MEDIAN_POS         (9u)  /* [9]   Median filter                     */
#define uatr_RX_CTRL_ENABLED_POS        (31u) /* [31]  Receiver enabled                  */
#define uatr_RX_CTRL_DATA_WIDTH_MASK    ((uint32) 0x0Fu)
#define uatr_RX_CTRL_MSB_FIRST          ((uint32) 0x01u << uatr_RX_CTRL_MSB_FIRST_POS)
#define uatr_RX_CTRL_LSB_FIRST          ((uint32) 0x00u)
#define uatr_RX_CTRL_MEDIAN             ((uint32) 0x01u << uatr_RX_CTRL_MEDIAN_POS)
#define uatr_RX_CTRL_ENABLED            ((uint32) 0x01u << uatr_RX_CTRL_ENABLED_POS)


/* uatr_RX_FIFO_CTRL_REG */
#define uatr_RX_FIFO_CTRL_TRIGGER_LEVEL_POS     (0u)   /* [2:0] Trigger level                            */
#define uatr_RX_FIFO_CTRL_CLEAR_POS             (16u)  /* [16]  Clear RX FIFO: clear after set           */
#define uatr_RX_FIFO_CTRL_FREEZE_POS            (17u)  /* [17]  Freeze RX FIFO: HW writes has not effect */
#define uatr_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) uatr_FF_DATA_NR_LOG2_MASK)
#define uatr_RX_FIFO_CTRL_CLEAR                 ((uint32) 0x01u << uatr_RX_FIFO_CTRL_CLEAR_POS)
#define uatr_RX_FIFO_CTRL_FREEZE                ((uint32) 0x01u << uatr_RX_FIFO_CTRL_FREEZE_POS)

/* uatr_RX_FIFO_STATUS_REG */
#define uatr_RX_FIFO_STATUS_USED_POS    (0u)   /* [3:0]   Amount of entries in RX FIFO */
#define uatr_RX_FIFO_SR_VALID_POS       (15u)  /* [15]    Shifter status of RX FIFO    */
#define uatr_RX_FIFO_STATUS_RD_PTR_POS  (16u)  /* [18:16] RX FIFO read pointer         */
#define uatr_RX_FIFO_STATUS_WR_PTR_POS  (24u)  /* [26:24] RX FIFO write pointer        */
#define uatr_RX_FIFO_STATUS_USED_MASK   ((uint32) uatr_FF_DATA_NR_LOG2_PLUS1_MASK)
#define uatr_RX_FIFO_SR_VALID           ((uint32) 0x01u << uatr_RX_FIFO_SR_VALID_POS)
#define uatr_RX_FIFO_STATUS_RD_PTR_MASK ((uint32) uatr_FF_DATA_NR_LOG2_MASK << \
                                                                    uatr_RX_FIFO_STATUS_RD_PTR_POS)
#define uatr_RX_FIFO_STATUS_WR_PTR_MASK ((uint32) uatr_FF_DATA_NR_LOG2_MASK << \
                                                                    uatr_RX_FIFO_STATUS_WR_PTR_POS)

/* uatr_RX_MATCH_REG */
#define uatr_RX_MATCH_ADDR_POS     (0u)  /* [7:0]   Slave address                        */
#define uatr_RX_MATCH_MASK_POS     (16u) /* [23:16] Slave address mask: 0 - doesn't care */
#define uatr_RX_MATCH_ADDR_MASK    ((uint32) 0xFFu)
#define uatr_RX_MATCH_MASK_MASK    ((uint32) 0xFFu << uatr_RX_MATCH_MASK_POS)

/* uatr_RX_FIFO_WR_REG */
#define uatr_RX_FIFO_RD_POS    (0u)  /* [15:0] Data read from RX FIFO */
#define uatr_RX_FIFO_RD_MASK   ((uint32) 0xFFu)

/* uatr_RX_FIFO_RD_SILENT_REG */
#define uatr_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define uatr_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* uatr_RX_FIFO_RD_SILENT_REG */
#define uatr_RX_FIFO_RD_SILENT_POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define uatr_RX_FIFO_RD_SILENT_MASK    ((uint32) 0xFFu)

/* uatr_EZBUF_DATA_REG */
#define uatr_EZBUF_DATA_POS   (0u)  /* [7:0] Data from EZ Memory */
#define uatr_EZBUF_DATA_MASK  ((uint32) 0xFFu)

/*  uatr_INTR_CAUSE_REG */
#define uatr_INTR_CAUSE_MASTER_POS  (0u)  /* [0] Master interrupt active                 */
#define uatr_INTR_CAUSE_SLAVE_POS   (1u)  /* [1] Slave interrupt active                  */
#define uatr_INTR_CAUSE_TX_POS      (2u)  /* [2] Transmitter interrupt active            */
#define uatr_INTR_CAUSE_RX_POS      (3u)  /* [3] Receiver interrupt active               */
#define uatr_INTR_CAUSE_I2C_EC_POS  (4u)  /* [4] Externally clock I2C interrupt active   */
#define uatr_INTR_CAUSE_SPI_EC_POS  (5u)  /* [5] Externally clocked SPI interrupt active */
#define uatr_INTR_CAUSE_MASTER      ((uint32) 0x01u)
#define uatr_INTR_CAUSE_SLAVE       ((uint32) 0x01u << uatr_INTR_CAUSE_SLAVE_POS)
#define uatr_INTR_CAUSE_TX          ((uint32) 0x01u << uatr_INTR_CAUSE_TX_POS)
#define uatr_INTR_CAUSE_RX          ((uint32) 0x01u << uatr_INTR_CAUSE_RX_POS)
#define uatr_INTR_CAUSE_I2C_EC      ((uint32) 0x01u << uatr_INTR_CAUSE_I2C_EC_POS)
#define uatr_INTR_CAUSE_SPI_EC      ((uint32) 0x01u << uatr_INTR_CAUSE_SPI_EC_POS)

/* uatr_INTR_SPI_EC_REG, uatr_INTR_SPI_EC_MASK_REG, uatr_INTR_SPI_EC_MASKED_REG */
#define uatr_INTR_SPI_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define uatr_INTR_SPI_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define uatr_INTR_SPI_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define uatr_INTR_SPI_EC_WAKE_UP              ((uint32) 0x01u)
#define uatr_INTR_SPI_EC_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    uatr_INTR_SPI_EC_EZBUF_STOP_POS)
#define uatr_INTR_SPI_EC_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                    uatr_INTR_SPI_EC_EZBUF_WRITE_STOP_POS)

/* uatr_INTR_I2C_EC, uatr_INTR_I2C_EC_MASK, uatr_INTR_I2C_EC_MASKED */
#define uatr_INTR_I2C_EC_WAKE_UP_POS          (0u)  /* [0] Address match: triggers wakeup of chip */
#define uatr_INTR_I2C_EC_EZBUF_STOP_POS       (1u)  /* [1] Externally clocked Stop detected       */
#define uatr_INTR_I2C_EC_EZBUF_WRITE_STOP_POS (2u)  /* [2] Externally clocked Write Stop detected */
#define uatr_INTR_I2C_EC_WAKE_UP              ((uint32) 0x01u)
#define uatr_INTR_I2C_EC_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    uatr_INTR_I2C_EC_EZBUF_STOP_POS)
#define uatr_INTR_I2C_EC_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                    uatr_INTR_I2C_EC_EZBUF_WRITE_STOP_POS)

/* uatr_INTR_MASTER, uatr_INTR_MASTER_SET,
   uatr_INTR_MASTER_MASK, uatr_INTR_MASTER_MASKED */
#define uatr_INTR_MASTER_I2C_ARB_LOST_POS   (0u)  /* [0] Master lost arbitration                          */
#define uatr_INTR_MASTER_I2C_NACK_POS       (1u)  /* [1] Master receives NACK: address or write to slave  */
#define uatr_INTR_MASTER_I2C_ACK_POS        (2u)  /* [2] Master receives NACK: address or write to slave  */
#define uatr_INTR_MASTER_I2C_STOP_POS       (4u)  /* [4] Master detects the Stop: only self generated Stop*/
#define uatr_INTR_MASTER_I2C_BUS_ERROR_POS  (8u)  /* [8] Master detects bus error: misplaced Start or Stop*/
#define uatr_INTR_MASTER_SPI_DONE_POS       (9u)  /* [9] Master complete transfer: Only for SPI           */
#define uatr_INTR_MASTER_I2C_ARB_LOST       ((uint32) 0x01u)
#define uatr_INTR_MASTER_I2C_NACK           ((uint32) 0x01u << uatr_INTR_MASTER_I2C_NACK_POS)
#define uatr_INTR_MASTER_I2C_ACK            ((uint32) 0x01u << uatr_INTR_MASTER_I2C_ACK_POS)
#define uatr_INTR_MASTER_I2C_STOP           ((uint32) 0x01u << uatr_INTR_MASTER_I2C_STOP_POS)
#define uatr_INTR_MASTER_I2C_BUS_ERROR      ((uint32) 0x01u << \
                                                                    uatr_INTR_MASTER_I2C_BUS_ERROR_POS)
#define uatr_INTR_MASTER_SPI_DONE           ((uint32) 0x01u << uatr_INTR_MASTER_SPI_DONE_POS)

/*
* uatr_INTR_SLAVE, uatr_INTR_SLAVE_SET,
* uatr_INTR_SLAVE_MASK, uatr_INTR_SLAVE_MASKED
*/
#define uatr_INTR_SLAVE_I2C_ARB_LOST_POS         (0u)  /* [0]  Slave lost arbitration                   */
#define uatr_INTR_SLAVE_I2C_NACK_POS             (1u)  /* [1]  Slave receives NACK: master reads data   */
#define uatr_INTR_SLAVE_I2C_ACK_POS              (2u)  /* [2]  Slave receives ACK: master reads data    */
#define uatr_INTR_SLAVE_I2C_WRITE_STOP_POS       (3u)  /* [3]  Slave detects end of write transaction   */
#define uatr_INTR_SLAVE_I2C_STOP_POS             (4u)  /* [4]  Slave detects end of transaction intended */
#define uatr_INTR_SLAVE_I2C_START_POS            (5u)  /* [5]  Slave detects Start                      */
#define uatr_INTR_SLAVE_I2C_ADDR_MATCH_POS       (6u)  /* [6]  Slave address matches                    */
#define uatr_INTR_SLAVE_I2C_GENERAL_POS          (7u)  /* [7]  General call received                    */
#define uatr_INTR_SLAVE_I2C_BUS_ERROR_POS        (8u)  /* [8]  Slave detects bus error                  */
#define uatr_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS (9u)  /* [9]  Slave write complete: Only for SPI       */
#define uatr_INTR_SLAVE_SPI_EZBUF_STOP_POS       (10u) /* [10] Slave end of transaction: Only for SPI   */
#define uatr_INTR_SLAVE_SPI_BUS_ERROR_POS        (11u) /* [11] Slave detects bus error: Only for SPI    */
#define uatr_INTR_SLAVE_I2C_ARB_LOST             ((uint32) 0x01u)
#define uatr_INTR_SLAVE_I2C_NACK                 ((uint32) 0x01u << \
                                                                    uatr_INTR_SLAVE_I2C_NACK_POS)
#define uatr_INTR_SLAVE_I2C_ACK                  ((uint32) 0x01u << \
                                                                    uatr_INTR_SLAVE_I2C_ACK_POS)
#define uatr_INTR_SLAVE_I2C_WRITE_STOP           ((uint32) 0x01u << \
                                                                    uatr_INTR_SLAVE_I2C_WRITE_STOP_POS)
#define uatr_INTR_SLAVE_I2C_STOP                 ((uint32) 0x01u << \
                                                                    uatr_INTR_SLAVE_I2C_STOP_POS)
#define uatr_INTR_SLAVE_I2C_START                ((uint32) 0x01u << \
                                                                    uatr_INTR_SLAVE_I2C_START_POS)
#define uatr_INTR_SLAVE_I2C_ADDR_MATCH           ((uint32) 0x01u << \
                                                                    uatr_INTR_SLAVE_I2C_ADDR_MATCH_POS)
#define uatr_INTR_SLAVE_I2C_GENERAL              ((uint32) 0x01u << \
                                                                    uatr_INTR_SLAVE_I2C_GENERAL_POS)
#define uatr_INTR_SLAVE_I2C_BUS_ERROR            ((uint32) 0x01u << \
                                                                    uatr_INTR_SLAVE_I2C_BUS_ERROR_POS)
#define uatr_INTR_SLAVE_SPI_EZBUF_WRITE_STOP     ((uint32) 0x01u << \
                                                                   uatr_INTR_SLAVE_SPI_EZBUF_WRITE_STOP_POS)
#define uatr_INTR_SLAVE_SPI_EZBUF_STOP           ((uint32) 0x01u << \
                                                                    uatr_INTR_SLAVE_SPI_EZBUF_STOP_POS)
#define uatr_INTR_SLAVE_SPI_BUS_ERROR           ((uint32) 0x01u << \
                                                                    uatr_INTR_SLAVE_SPI_BUS_ERROR_POS)

/*
* uatr_INTR_TX, uatr_INTR_TX_SET,
* uatr_INTR_TX_MASK, uatr_INTR_TX_MASKED
*/
#define uatr_INTR_TX_TRIGGER_POS        (0u)  /* [0]  Trigger on TX FIFO entires                       */
#define uatr_INTR_TX_NOT_FULL_POS       (1u)  /* [1]  TX FIFO is not full                              */
#define uatr_INTR_TX_EMPTY_POS          (4u)  /* [4]  TX FIFO is empty                                 */
#define uatr_INTR_TX_OVERFLOW_POS       (5u)  /* [5]  Attempt to write to a full TX FIFO               */
#define uatr_INTR_TX_UNDERFLOW_POS      (6u)  /* [6]  Attempt to read from an empty TX FIFO            */
#define uatr_INTR_TX_BLOCKED_POS        (7u)  /* [7]  No access to the EZ memory                       */
#define uatr_INTR_TX_UART_NACK_POS      (8u)  /* [8]  UART transmitter received a NACK: SmartCard mode */
#define uatr_INTR_TX_UART_DONE_POS      (9u)  /* [9]  UART transmitter done even                       */
#define uatr_INTR_TX_UART_ARB_LOST_POS  (10u) /* [10] UART lost arbitration: LIN or SmartCard          */
#define uatr_INTR_TX_TRIGGER            ((uint32) 0x01u)
#define uatr_INTR_TX_FIFO_LEVEL         (uatr_INTR_TX_TRIGGER)
#define uatr_INTR_TX_NOT_FULL           ((uint32) 0x01u << uatr_INTR_TX_NOT_FULL_POS)
#define uatr_INTR_TX_EMPTY              ((uint32) 0x01u << uatr_INTR_TX_EMPTY_POS)
#define uatr_INTR_TX_OVERFLOW           ((uint32) 0x01u << uatr_INTR_TX_OVERFLOW_POS)
#define uatr_INTR_TX_UNDERFLOW          ((uint32) 0x01u << uatr_INTR_TX_UNDERFLOW_POS)
#define uatr_INTR_TX_BLOCKED            ((uint32) 0x01u << uatr_INTR_TX_BLOCKED_POS)
#define uatr_INTR_TX_UART_NACK          ((uint32) 0x01u << uatr_INTR_TX_UART_NACK_POS)
#define uatr_INTR_TX_UART_DONE          ((uint32) 0x01u << uatr_INTR_TX_UART_DONE_POS)
#define uatr_INTR_TX_UART_ARB_LOST      ((uint32) 0x01u << uatr_INTR_TX_UART_ARB_LOST_POS)

/*
* uatr_INTR_RX, uatr_INTR_RX_SET,
* uatr_INTR_RX_MASK, uatr_INTR_RX_MASKED
*/
#define uatr_INTR_RX_TRIGGER_POS        (0u)   /* [0]  Trigger on RX FIFO entires            */
#define uatr_INTR_RX_NOT_EMPTY_POS      (2u)   /* [2]  RX FIFO is not empty                  */
#define uatr_INTR_RX_FULL_POS           (3u)   /* [3]  RX FIFO is full                       */
#define uatr_INTR_RX_OVERFLOW_POS       (5u)   /* [5]  Attempt to write to a full RX FIFO    */
#define uatr_INTR_RX_UNDERFLOW_POS      (6u)   /* [6]  Attempt to read from an empty RX FIFO */
#define uatr_INTR_RX_BLOCKED_POS        (7u)   /* [7]  No access to the EZ memory            */
#define uatr_INTR_RX_FRAME_ERROR_POS    (8u)   /* [8]  Frame error in received data frame    */
#define uatr_INTR_RX_PARITY_ERROR_POS   (9u)   /* [9]  Parity error in received data frame   */
#define uatr_INTR_RX_BAUD_DETECT_POS    (10u)  /* [10] LIN baud rate detection is completed   */
#define uatr_INTR_RX_BREAK_DETECT_POS   (11u)  /* [11] Break detection is successful         */
#define uatr_INTR_RX_TRIGGER            ((uint32) 0x01u)
#define uatr_INTR_RX_FIFO_LEVEL         (uatr_INTR_RX_TRIGGER)
#define uatr_INTR_RX_NOT_EMPTY          ((uint32) 0x01u << uatr_INTR_RX_NOT_EMPTY_POS)
#define uatr_INTR_RX_FULL               ((uint32) 0x01u << uatr_INTR_RX_FULL_POS)
#define uatr_INTR_RX_OVERFLOW           ((uint32) 0x01u << uatr_INTR_RX_OVERFLOW_POS)
#define uatr_INTR_RX_UNDERFLOW          ((uint32) 0x01u << uatr_INTR_RX_UNDERFLOW_POS)
#define uatr_INTR_RX_BLOCKED            ((uint32) 0x01u << uatr_INTR_RX_BLOCKED_POS)
#define uatr_INTR_RX_FRAME_ERROR        ((uint32) 0x01u << uatr_INTR_RX_FRAME_ERROR_POS)
#define uatr_INTR_RX_PARITY_ERROR       ((uint32) 0x01u << uatr_INTR_RX_PARITY_ERROR_POS)
#define uatr_INTR_RX_BAUD_DETECT        ((uint32) 0x01u << uatr_INTR_RX_BAUD_DETECT_POS)
#define uatr_INTR_RX_BREAK_DETECT       ((uint32) 0x01u << uatr_INTR_RX_BREAK_DETECT_POS)

/* Define all interrupt sources */
#define uatr_INTR_I2C_EC_ALL    (uatr_INTR_I2C_EC_WAKE_UP    | \
                                             uatr_INTR_I2C_EC_EZBUF_STOP | \
                                             uatr_INTR_I2C_EC_EZBUF_WRITE_STOP)

#define uatr_INTR_SPI_EC_ALL    (uatr_INTR_SPI_EC_WAKE_UP    | \
                                             uatr_INTR_SPI_EC_EZBUF_STOP | \
                                             uatr_INTR_SPI_EC_EZBUF_WRITE_STOP)

#define uatr_INTR_MASTER_ALL    (uatr_INTR_MASTER_I2C_ARB_LOST  | \
                                             uatr_INTR_MASTER_I2C_NACK      | \
                                             uatr_INTR_MASTER_I2C_ACK       | \
                                             uatr_INTR_MASTER_I2C_STOP      | \
                                             uatr_INTR_MASTER_I2C_BUS_ERROR | \
                                             uatr_INTR_MASTER_SPI_DONE)

#define uatr_INTR_SLAVE_ALL     (uatr_INTR_SLAVE_I2C_ARB_LOST      | \
                                             uatr_INTR_SLAVE_I2C_NACK          | \
                                             uatr_INTR_SLAVE_I2C_ACK           | \
                                             uatr_INTR_SLAVE_I2C_WRITE_STOP    | \
                                             uatr_INTR_SLAVE_I2C_STOP          | \
                                             uatr_INTR_SLAVE_I2C_START         | \
                                             uatr_INTR_SLAVE_I2C_ADDR_MATCH    | \
                                             uatr_INTR_SLAVE_I2C_GENERAL       | \
                                             uatr_INTR_SLAVE_I2C_BUS_ERROR     | \
                                             uatr_INTR_SLAVE_SPI_EZBUF_WRITE_STOP | \
                                             uatr_INTR_SLAVE_SPI_EZBUF_STOP       | \
                                             uatr_INTR_SLAVE_SPI_BUS_ERROR)

#define uatr_INTR_TX_ALL        (uatr_INTR_TX_TRIGGER   | \
                                             uatr_INTR_TX_NOT_FULL  | \
                                             uatr_INTR_TX_EMPTY     | \
                                             uatr_INTR_TX_OVERFLOW  | \
                                             uatr_INTR_TX_UNDERFLOW | \
                                             uatr_INTR_TX_BLOCKED   | \
                                             uatr_INTR_TX_UART_NACK | \
                                             uatr_INTR_TX_UART_DONE | \
                                             uatr_INTR_TX_UART_ARB_LOST)

#define uatr_INTR_RX_ALL        (uatr_INTR_RX_TRIGGER      | \
                                             uatr_INTR_RX_NOT_EMPTY    | \
                                             uatr_INTR_RX_FULL         | \
                                             uatr_INTR_RX_OVERFLOW     | \
                                             uatr_INTR_RX_UNDERFLOW    | \
                                             uatr_INTR_RX_BLOCKED      | \
                                             uatr_INTR_RX_FRAME_ERROR  | \
                                             uatr_INTR_RX_PARITY_ERROR | \
                                             uatr_INTR_RX_BAUD_DETECT  | \
                                             uatr_INTR_RX_BREAK_DETECT)

/* General usage HW definitions */
#define uatr_ONE_BYTE_WIDTH (8u)   /* Number of bits in one byte           */
#define uatr_FIFO_SIZE      (8u)   /* Size of TX or RX FIFO: defined by HW */
#define uatr_EZBUFFER_SIZE  (32u)  /* EZ Buffer size: defined by HW        */

/* I2C and EZI2C slave address defines */
#define uatr_I2C_SLAVE_ADDR_POS    (0x01u)    /* 7-bit address shift */
#define uatr_I2C_SLAVE_ADDR_MASK   (0xFEu)    /* 8-bit address mask */

/* OVS constants for IrDA Low Power operation */
#define uatr_CTRL_OVS_IRDA_LP_OVS16     (0x00u)
#define uatr_CTRL_OVS_IRDA_LP_OVS32     (0x01u)
#define uatr_CTRL_OVS_IRDA_LP_OVS48     (0x02u)
#define uatr_CTRL_OVS_IRDA_LP_OVS96     (0x03u)
#define uatr_CTRL_OVS_IRDA_LP_OVS192    (0x04u)
#define uatr_CTRL_OVS_IRDA_LP_OVS768    (0x05u)
#define uatr_CTRL_OVS_IRDA_LP_OVS1536   (0x06u)

/* OVS constant for IrDA */
#define uatr_CTRL_OVS_IRDA_OVS16        (uatr_UART_IRDA_LP_OVS16)


/***************************************
*    Common Macro Definitions
***************************************/

/* Re-enables the SCB IP. A clear enable bit has a different effect
* on the scb IP depending on the version:
*  CY_SCBIP_V0: resets state, status, TX and RX FIFOs.
*  CY_SCBIP_V1 or later: resets state, status, TX and RX FIFOs and interrupt sources.
*/
#define uatr_SCB_SW_RESET \
                        do{           \
                            uatr_CTRL_REG &= ((uint32) ~uatr_CTRL_ENABLED); \
                            uatr_CTRL_REG |= ((uint32)  uatr_CTRL_ENABLED); \
                        }while(0)

/* TX FIFO macro */
#define uatr_CLEAR_TX_FIFO \
                            do{        \
                                uatr_TX_FIFO_CTRL_REG |= ((uint32)  uatr_TX_FIFO_CTRL_CLEAR); \
                                uatr_TX_FIFO_CTRL_REG &= ((uint32) ~uatr_TX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define uatr_GET_TX_FIFO_ENTRIES    (uatr_TX_FIFO_STATUS_REG & \
                                                 uatr_TX_FIFO_STATUS_USED_MASK)

#define uatr_GET_TX_FIFO_SR_VALID   ((0u != (uatr_TX_FIFO_STATUS_REG & \
                                                         uatr_TX_FIFO_SR_VALID)) ? (1u) : (0u))

/* RX FIFO macro */
#define uatr_CLEAR_RX_FIFO \
                            do{        \
                                uatr_RX_FIFO_CTRL_REG |= ((uint32)  uatr_RX_FIFO_CTRL_CLEAR); \
                                uatr_RX_FIFO_CTRL_REG &= ((uint32) ~uatr_RX_FIFO_CTRL_CLEAR); \
                            }while(0)

#define uatr_GET_RX_FIFO_ENTRIES    (uatr_RX_FIFO_STATUS_REG & \
                                                    uatr_RX_FIFO_STATUS_USED_MASK)

#define uatr_GET_RX_FIFO_SR_VALID   ((0u != (uatr_RX_FIFO_STATUS_REG & \
                                                         uatr_RX_FIFO_SR_VALID)) ? (1u) : (0u))

/* Write interrupt source: set sourceMask bits in uatr_INTR_X_MASK_REG */
#define uatr_WRITE_INTR_I2C_EC_MASK(sourceMask) \
                                                do{         \
                                                    uatr_INTR_I2C_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#if (!uatr_CY_SCBIP_V1)
    #define uatr_WRITE_INTR_SPI_EC_MASK(sourceMask) \
                                                do{         \
                                                    uatr_INTR_SPI_EC_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!uatr_CY_SCBIP_V1) */

#define uatr_WRITE_INTR_MASTER_MASK(sourceMask) \
                                                do{         \
                                                    uatr_INTR_MASTER_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define uatr_WRITE_INTR_SLAVE_MASK(sourceMask)  \
                                                do{         \
                                                    uatr_INTR_SLAVE_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define uatr_WRITE_INTR_TX_MASK(sourceMask)     \
                                                do{         \
                                                    uatr_INTR_TX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

#define uatr_WRITE_INTR_RX_MASK(sourceMask)     \
                                                do{         \
                                                    uatr_INTR_RX_MASK_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Enable interrupt source: set sourceMask bits in uatr_INTR_X_MASK_REG */
#define uatr_ENABLE_INTR_I2C_EC(sourceMask) \
                                                do{     \
                                                    uatr_INTR_I2C_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)
#if (!uatr_CY_SCBIP_V1)
    #define uatr_ENABLE_INTR_SPI_EC(sourceMask) \
                                                do{     \
                                                    uatr_INTR_SPI_EC_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!uatr_CY_SCBIP_V1) */

#define uatr_ENABLE_INTR_MASTER(sourceMask) \
                                                do{     \
                                                    uatr_INTR_MASTER_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define uatr_ENABLE_INTR_SLAVE(sourceMask)  \
                                                do{     \
                                                    uatr_INTR_SLAVE_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define uatr_ENABLE_INTR_TX(sourceMask)     \
                                                do{     \
                                                    uatr_INTR_TX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

#define uatr_ENABLE_INTR_RX(sourceMask)     \
                                                do{     \
                                                    uatr_INTR_RX_MASK_REG |= (uint32) (sourceMask); \
                                                }while(0)

/* Disable interrupt source: clear sourceMask bits in uatr_INTR_X_MASK_REG */
#define uatr_DISABLE_INTR_I2C_EC(sourceMask) \
                                do{                      \
                                    uatr_INTR_I2C_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#if (!uatr_CY_SCBIP_V1)
    #define uatr_DISABLE_INTR_SPI_EC(sourceMask) \
                                do{                      \
                                    uatr_INTR_SPI_EC_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)
#endif /* (!uatr_CY_SCBIP_V1) */

#define uatr_DISABLE_INTR_MASTER(sourceMask) \
                                do{                      \
                                uatr_INTR_MASTER_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define uatr_DISABLE_INTR_SLAVE(sourceMask) \
                                do{                     \
                                    uatr_INTR_SLAVE_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

#define uatr_DISABLE_INTR_TX(sourceMask)    \
                                do{                     \
                                    uatr_INTR_TX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                 }while(0)

#define uatr_DISABLE_INTR_RX(sourceMask)    \
                                do{                     \
                                    uatr_INTR_RX_MASK_REG &= ((uint32) ~((uint32) (sourceMask))); \
                                }while(0)

/* Set interrupt sources: write sourceMask bits in uatr_INTR_X_SET_REG */
#define uatr_SET_INTR_MASTER(sourceMask)    \
                                                do{     \
                                                    uatr_INTR_MASTER_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define uatr_SET_INTR_SLAVE(sourceMask) \
                                                do{ \
                                                    uatr_INTR_SLAVE_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define uatr_SET_INTR_TX(sourceMask)    \
                                                do{ \
                                                    uatr_INTR_TX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

#define uatr_SET_INTR_RX(sourceMask)    \
                                                do{ \
                                                    uatr_INTR_RX_SET_REG = (uint32) (sourceMask); \
                                                }while(0)

/* Clear interrupt sources: write sourceMask bits in uatr_INTR_X_REG */
#define uatr_CLEAR_INTR_I2C_EC(sourceMask)  \
                                                do{     \
                                                    uatr_INTR_I2C_EC_REG = (uint32) (sourceMask); \
                                                }while(0)

#if (!uatr_CY_SCBIP_V1)
    #define uatr_CLEAR_INTR_SPI_EC(sourceMask)  \
                                                do{     \
                                                    uatr_INTR_SPI_EC_REG = (uint32) (sourceMask); \
                                                }while(0)
#endif /* (!uatr_CY_SCBIP_V1) */

#define uatr_CLEAR_INTR_MASTER(sourceMask)  \
                                                do{     \
                                                    uatr_INTR_MASTER_REG = (uint32) (sourceMask); \
                                                }while(0)

#define uatr_CLEAR_INTR_SLAVE(sourceMask)   \
                                                do{     \
                                                    uatr_INTR_SLAVE_REG  = (uint32) (sourceMask); \
                                                }while(0)

#define uatr_CLEAR_INTR_TX(sourceMask)      \
                                                do{     \
                                                    uatr_INTR_TX_REG     = (uint32) (sourceMask); \
                                                }while(0)

#define uatr_CLEAR_INTR_RX(sourceMask)      \
                                                do{     \
                                                    uatr_INTR_RX_REG     = (uint32) (sourceMask); \
                                                }while(0)

/* Return true if sourceMask is set in uatr_INTR_CAUSE_REG */
#define uatr_CHECK_CAUSE_INTR(sourceMask)    (0u != (uatr_INTR_CAUSE_REG & (sourceMask)))

/* Return true if sourceMask is set in INTR_X_MASKED_REG */
#define uatr_CHECK_INTR_I2C_EC(sourceMask)  (0u != (uatr_INTR_I2C_EC_REG & (sourceMask)))
#if (!uatr_CY_SCBIP_V1)
    #define uatr_CHECK_INTR_SPI_EC(sourceMask)  (0u != (uatr_INTR_SPI_EC_REG & (sourceMask)))
#endif /* (!uatr_CY_SCBIP_V1) */
#define uatr_CHECK_INTR_MASTER(sourceMask)  (0u != (uatr_INTR_MASTER_REG & (sourceMask)))
#define uatr_CHECK_INTR_SLAVE(sourceMask)   (0u != (uatr_INTR_SLAVE_REG  & (sourceMask)))
#define uatr_CHECK_INTR_TX(sourceMask)      (0u != (uatr_INTR_TX_REG     & (sourceMask)))
#define uatr_CHECK_INTR_RX(sourceMask)      (0u != (uatr_INTR_RX_REG     & (sourceMask)))

/* Return true if sourceMask is set in uatr_INTR_X_MASKED_REG */
#define uatr_CHECK_INTR_I2C_EC_MASKED(sourceMask)   (0u != (uatr_INTR_I2C_EC_MASKED_REG & \
                                                                       (sourceMask)))
#if (!uatr_CY_SCBIP_V1)
    #define uatr_CHECK_INTR_SPI_EC_MASKED(sourceMask)   (0u != (uatr_INTR_SPI_EC_MASKED_REG & \
                                                                       (sourceMask)))
#endif /* (!uatr_CY_SCBIP_V1) */
#define uatr_CHECK_INTR_MASTER_MASKED(sourceMask)   (0u != (uatr_INTR_MASTER_MASKED_REG & \
                                                                       (sourceMask)))
#define uatr_CHECK_INTR_SLAVE_MASKED(sourceMask)    (0u != (uatr_INTR_SLAVE_MASKED_REG  & \
                                                                       (sourceMask)))
#define uatr_CHECK_INTR_TX_MASKED(sourceMask)       (0u != (uatr_INTR_TX_MASKED_REG     & \
                                                                       (sourceMask)))
#define uatr_CHECK_INTR_RX_MASKED(sourceMask)       (0u != (uatr_INTR_RX_MASKED_REG     & \
                                                                       (sourceMask)))

/* Return true if sourceMask is set in uatr_CTRL_REG: generally is used to check enable bit */
#define uatr_GET_CTRL_ENABLED    (0u != (uatr_CTRL_REG & uatr_CTRL_ENABLED))

#define uatr_CHECK_SLAVE_AUTO_ADDR_NACK     (0u != (uatr_I2C_CTRL_REG & \
                                                                uatr_I2C_CTRL_S_NOT_READY_DATA_NACK))


/***************************************
*      I2C Macro Definitions
***************************************/

/* Enable auto ACK/NACK */
#define uatr_ENABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                      \
                                uatr_I2C_CTRL_REG |= uatr_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define uatr_ENABLE_SLAVE_AUTO_DATA_ACK \
                            do{                     \
                                uatr_I2C_CTRL_REG |= uatr_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define uatr_ENABLE_SLAVE_AUTO_DATA_NACK \
                            do{                      \
                                uatr_I2C_CTRL_REG |= uatr_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define uatr_ENABLE_MASTER_AUTO_DATA_ACK \
                            do{                      \
                                uatr_I2C_CTRL_REG |= uatr_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define uatr_ENABLE_MASTER_AUTO_DATA_NACK \
                            do{                       \
                                uatr_I2C_CTRL_REG |= uatr_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Disable auto ACK/NACK */
#define uatr_DISABLE_SLAVE_AUTO_ADDR_NACK \
                            do{                       \
                                uatr_I2C_CTRL_REG &= ~uatr_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define uatr_DISABLE_SLAVE_AUTO_DATA_ACK \
                            do{                      \
                                uatr_I2C_CTRL_REG &= ~uatr_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define uatr_DISABLE_SLAVE_AUTO_DATA_NACK \
                            do{                       \
                                uatr_I2C_CTRL_REG &= ~uatr_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define uatr_DISABLE_MASTER_AUTO_DATA_ACK \
                            do{                       \
                                uatr_I2C_CTRL_REG &= ~uatr_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define uatr_DISABLE_MASTER_AUTO_DATA_NACK \
                            do{                        \
                                uatr_I2C_CTRL_REG &= ~uatr_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Enable Slave autoACK/NACK Data */
#define uatr_ENABLE_SLAVE_AUTO_DATA \
                            do{                 \
                                uatr_I2C_CTRL_REG |= (uatr_I2C_CTRL_S_READY_DATA_ACK |      \
                                                                  uatr_I2C_CTRL_S_NOT_READY_DATA_NACK); \
                            }while(0)

/* Disable Slave autoACK/NACK Data */
#define uatr_DISABLE_SLAVE_AUTO_DATA \
                            do{                  \
                                uatr_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(uatr_I2C_CTRL_S_READY_DATA_ACK |       \
                                                                    uatr_I2C_CTRL_S_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Disable Master autoACK/NACK Data */
#define uatr_DISABLE_MASTER_AUTO_DATA \
                            do{                   \
                                uatr_I2C_CTRL_REG &= ((uint32) \
                                                                  ~(uatr_I2C_CTRL_M_READY_DATA_ACK |       \
                                                                    uatr_I2C_CTRL_M_NOT_READY_DATA_NACK)); \
                            }while(0)

/* Master commands */
#define uatr_I2C_MASTER_GENERATE_START \
                            do{                    \
                                uatr_I2C_MASTER_CMD_REG = uatr_I2C_MASTER_CMD_M_START_ON_IDLE; \
                            }while(0)

#define uatr_I2C_MASTER_CLEAR_START \
                            do{                 \
                                uatr_I2C_MASTER_CMD_REG =  ((uint32) 0u); \
                            }while(0)

#define uatr_I2C_MASTER_GENERATE_RESTART uatr_I2CReStartGeneration()

#define uatr_I2C_MASTER_GENERATE_STOP \
                            do{                   \
                                uatr_I2C_MASTER_CMD_REG =                                            \
                                    (uatr_I2C_MASTER_CMD_M_STOP |                                    \
                                        (uatr_CHECK_I2C_STATUS(uatr_I2C_STATUS_M_READ) ? \
                                            (uatr_I2C_MASTER_CMD_M_NACK) : (0u)));                   \
                            }while(0)

#define uatr_I2C_MASTER_GENERATE_ACK \
                            do{                  \
                                uatr_I2C_MASTER_CMD_REG = uatr_I2C_MASTER_CMD_M_ACK; \
                            }while(0)

#define uatr_I2C_MASTER_GENERATE_NACK \
                            do{                   \
                                uatr_I2C_MASTER_CMD_REG = uatr_I2C_MASTER_CMD_M_NACK; \
                            }while(0)

/* Slave commands */
#define uatr_I2C_SLAVE_GENERATE_ACK \
                            do{                 \
                                uatr_I2C_SLAVE_CMD_REG = uatr_I2C_SLAVE_CMD_S_ACK; \
                            }while(0)

#if (uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
    /* Slave NACK generation for EC_AM logic on address phase. Ticket ID #183902 */
    void uatr_I2CSlaveNackGeneration(void);
    #define uatr_I2C_SLAVE_GENERATE_NACK uatr_I2CSlaveNackGeneration()

#else
    #define uatr_I2C_SLAVE_GENERATE_NACK \
                            do{                      \
                                uatr_I2C_SLAVE_CMD_REG = uatr_I2C_SLAVE_CMD_S_NACK; \
                            }while(0)
#endif /* (uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */

#define uatr_I2C_SLAVE_CLEAR_NACK \
                            do{               \
                                uatr_I2C_SLAVE_CMD_REG = 0u; \
                            }while(0)

/* Return 8-bit address. The input address should be 7-bits */
#define uatr_GET_I2C_8BIT_ADDRESS(addr) (((uint32) ((uint32) (addr) << \
                                                                    uatr_I2C_SLAVE_ADDR_POS)) & \
                                                                        uatr_I2C_SLAVE_ADDR_MASK)

#define uatr_GET_I2C_7BIT_ADDRESS(addr) ((uint32) (addr) >> uatr_I2C_SLAVE_ADDR_POS)

/* Adjust SDA filter Trim settings */
#define uatr_DEFAULT_I2C_CFG_SDA_FILT_TRIM  (0x02u)
#define uatr_EC_AM_I2C_CFG_SDA_FILT_TRIM    (0x03u)

#if (uatr_CY_SCBIP_V0)
    #define uatr_SET_I2C_CFG_SDA_FILT_TRIM(sdaTrim) \
        do{                                                 \
            uatr_I2C_CFG_REG =                  \
                            ((uatr_I2C_CFG_REG & (uint32) ~uatr_I2C_CFG_SDA_FILT_TRIM_MASK) | \
                             ((uint32) ((uint32) (sdaTrim) <<uatr_I2C_CFG_SDA_FILT_TRIM_POS)));           \
        }while(0)
#endif /* (uatr_CY_SCBIP_V0) */

/* Enable/Disable analog and digital filter */
#define uatr_DIGITAL_FILTER_DISABLE    (0u)
#define uatr_DIGITAL_FILTER_ENABLE     (1u)
#define uatr_I2C_DATA_RATE_FS_MODE_MAX (400u)
#if (uatr_CY_SCBIP_V0)
    /* uatr_I2C_CFG_SDA_FILT_OUT_ENABLED is disabled by default */
    #define uatr_I2C_CFG_FILT_MASK  (uatr_I2C_CFG_SDA_FILT_ENABLED | \
                                                 uatr_I2C_CFG_SCL_FILT_ENABLED)
#else
    /* uatr_I2C_CFG_SDA_OUT_FILT_SEL_MASK is disabled by default */
    #define uatr_I2C_CFG_FILT_MASK  (uatr_I2C_CFG_SDA_IN_FILT_SEL | \
                                                 uatr_I2C_CFG_SCL_IN_FILT_SEL)
#endif /* (uatr_CY_SCBIP_V0) */

#define uatr_I2C_CFG_ANALOG_FITER_DISABLE \
        do{                                           \
            uatr_I2C_CFG_REG &= (uint32) ~uatr_I2C_CFG_FILT_MASK; \
        }while(0)

#define uatr_I2C_CFG_ANALOG_FITER_ENABLE \
        do{                                          \
            uatr_I2C_CFG_REG |= (uint32)  uatr_I2C_CFG_FILT_MASK; \
        }while(0)

/* Return slave select number from SPI_CTRL register */
#define uatr_GET_SPI_CTRL_SS(activeSelect) (((uint32) ((uint32) (activeSelect) << \
                                                                    uatr_SPI_CTRL_SLAVE_SELECT_POS)) & \
                                                                        uatr_SPI_CTRL_SLAVE_SELECT_MASK)

/* Return true if bit is set in uatr_I2C_STATUS_REG */
#define uatr_CHECK_I2C_STATUS(sourceMask)   (0u != (uatr_I2C_STATUS_REG & (sourceMask)))

/* Return true if bit is set in uatr_SPI_STATUS_REG */
#define uatr_CHECK_SPI_STATUS(sourceMask)   (0u != (uatr_SPI_STATUS_REG & (sourceMask)))

/* Return FIFO size depends on uatr_CTRL_BYTE_MODE bit */
#define uatr_GET_FIFO_SIZE(condition) ((0u != (condition)) ? \
                                                    (2u * uatr_FIFO_SIZE) : (uatr_FIFO_SIZE))


/***************************************
*       Get Macros Definitions
***************************************/

/* uatr_CTRL */
#define uatr_GET_CTRL_OVS(oversample)       (((uint32) (oversample) - 1u) & uatr_CTRL_OVS_MASK)

#define uatr_GET_CTRL_EC_OP_MODE(opMode)        ((0u != (opMode)) ? \
                                                                (uatr_CTRL_EC_OP_MODE)  : (0u))

#define uatr_GET_CTRL_EC_AM_MODE(amMode)        ((0u != (amMode)) ? \
                                                                (uatr_CTRL_EC_AM_MODE)  : (0u))

#define uatr_GET_CTRL_BLOCK(block)              ((0u != (block))  ? \
                                                                (uatr_CTRL_BLOCK)       : (0u))

#define uatr_GET_CTRL_ADDR_ACCEPT(acceptAddr)   ((0u != (acceptAddr)) ? \
                                                                (uatr_CTRL_ADDR_ACCEPT) : (0u))

#if (uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
    #define uatr_GET_CTRL_BYTE_MODE(mode)   (0u)
#else
    #define uatr_GET_CTRL_BYTE_MODE(mode)   ((0u != (mode)) ? \
                                                            (uatr_CTRL_BYTE_MODE) : (0u))
#endif /* (uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */

/* uatr_I2C_CTRL */
#define uatr_GET_I2C_CTRL_HIGH_PHASE_OVS(oversampleHigh) (((uint32) (oversampleHigh) - 1u) & \
                                                                        uatr_I2C_CTRL_HIGH_PHASE_OVS_MASK)

#define uatr_GET_I2C_CTRL_LOW_PHASE_OVS(oversampleLow)  ((((uint32) (oversampleLow) - 1u) << \
                                                                    uatr_I2C_CTRL_LOW_PHASE_OVS_POS) &  \
                                                                    uatr_I2C_CTRL_LOW_PHASE_OVS_MASK)

#define uatr_GET_I2C_CTRL_S_NOT_READY_ADDR_NACK(wakeNack) ((0u != (wakeNack)) ? \
                                                            (uatr_I2C_CTRL_S_NOT_READY_ADDR_NACK) : (0u))

#define uatr_GET_I2C_CTRL_S_GENERAL_IGNORE(genCall) ((0u != (genCall)) ? \
                                                                    (uatr_I2C_CTRL_S_GENERAL_IGNORE) : (0u))

#define uatr_GET_I2C_CTRL_SL_MSTR_MODE(mode)    ((uint32)(mode) << uatr_I2C_CTRL_SLAVE_MODE_POS)

/* uatr_SPI_CTRL */
#define uatr_GET_SPI_CTRL_CONTINUOUS(separate)  ((0u != (separate)) ? \
                                                                (uatr_SPI_CTRL_CONTINUOUS) : (0u))

#define uatr_GET_SPI_CTRL_SELECT_PRECEDE(mode)  ((0u != (mode)) ? \
                                                                      (uatr_SPI_CTRL_SELECT_PRECEDE) : (0u))

#define uatr_GET_SPI_CTRL_SCLK_MODE(mode)       (((uint32) (mode) << \
                                                                        uatr_SPI_CTRL_CPHA_POS) & \
                                                                        uatr_SPI_CTRL_SCLK_MODE_MASK)

#define uatr_GET_SPI_CTRL_LATE_MISO_SAMPLE(lateMiso) ((0u != (lateMiso)) ? \
                                                                    (uatr_SPI_CTRL_LATE_MISO_SAMPLE) : (0u))

#if (uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
    #define uatr_GET_SPI_CTRL_SCLK_CONTINUOUS(sclkType) (0u)
    #define uatr_GET_SPI_CTRL_SSEL_POLARITY(polarity)   (0u)
#else
    #define uatr_GET_SPI_CTRL_SCLK_CONTINUOUS(sclkType) ((0u != (sclkType)) ? \
                                                                    (uatr_SPI_CTRL_SCLK_CONTINUOUS) : (0u))

    #define uatr_GET_SPI_CTRL_SSEL_POLARITY(polarity)   (((uint32) (polarity) << \
                                                                     uatr_SPI_CTRL_SSEL0_POLARITY_POS) & \
                                                                     uatr_SPI_CTRL_SSEL_POLARITY_MASK)
#endif /* ((uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */

#define uatr_GET_SPI_CTRL_SUB_MODE(mode)        (((uint32) (mode) << uatr_SPI_CTRL_MODE_POS) & \
                                                                                 uatr_SPI_CTRL_MODE_MASK)

#define uatr_GET_SPI_CTRL_SLAVE_SELECT(select)  (((uint32) (select) << \
                                                                      uatr_SPI_CTRL_SLAVE_SELECT_POS) & \
                                                                      uatr_SPI_CTRL_SLAVE_SELECT_MASK)

#define uatr_GET_SPI_CTRL_MASTER_MODE(mode)     ((0u != (mode)) ? \
                                                                (uatr_SPI_CTRL_MASTER) : (0u))

/* uatr_UART_CTRL */
#define uatr_GET_UART_CTRL_MODE(mode)           (((uint32) (mode) << \
                                                                            uatr_UART_CTRL_MODE_POS) & \
                                                                            uatr_UART_CTRL_MODE_MASK)

/* uatr_UART_RX_CTRL */
#define uatr_GET_UART_RX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                        uatr_UART_RX_CTRL_STOP_BITS_MASK)

#define uatr_GET_UART_RX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                                    (uatr_UART_RX_CTRL_PARITY) : (0u))

#define uatr_GET_UART_RX_CTRL_POLARITY(polarity)    ((0u != (polarity)) ? \
                                                                    (uatr_UART_RX_CTRL_POLARITY) : (0u))

#define uatr_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (uatr_UART_RX_CTRL_DROP_ON_PARITY_ERR) : (0u))

#define uatr_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (uatr_UART_RX_CTRL_DROP_ON_FRAME_ERR) : (0u))

#define uatr_GET_UART_RX_CTRL_MP_MODE(mpMode)   ((0u != (mpMode)) ? \
                                                        (uatr_UART_RX_CTRL_MP_MODE) : (0u))

/* uatr_UART_TX_CTRL */
#define uatr_GET_UART_TX_CTRL_MODE(stopBits)    (((uint32) (stopBits) - 1u) & \
                                                                uatr_UART_RX_CTRL_STOP_BITS_MASK)

#define uatr_GET_UART_TX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                               (uatr_UART_TX_CTRL_PARITY) : (0u))

#define uatr_GET_UART_TX_CTRL_RETRY_NACK(nack)  ((0u != (nack)) ? \
                                                               (uatr_UART_TX_CTRL_RETRY_ON_NACK) : (0u))

/* uatr_UART_FLOW_CTRL */
#if !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
    #define uatr_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(level)   ( (uint32) (level) & \
                                                                 uatr_UART_FLOW_CTRL_TRIGGER_LEVEL_MASK)

    #define uatr_GET_UART_FLOW_CTRL_RTS_POLARITY(polarity) ((0u != (polarity)) ? \
                                                                (uatr_UART_FLOW_CTRL_RTS_POLARITY) : (0u))

    #define uatr_GET_UART_FLOW_CTRL_CTS_POLARITY(polarity) ((0u != (polarity)) ? \
                                                                (uatr_UART_FLOW_CTRL_CTS_POLARITY) : (0u))

    #define uatr_GET_UART_FLOW_CTRL_CTS_ENABLE(ctsEn)      ((0u != (ctsEn)) ? \
                                                                (uatr_UART_FLOW_CTRL_CTS_ENABLE) : (0u))
#endif /* !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */

/* uatr_RX_CTRL */
#define uatr_GET_RX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                uatr_RX_CTRL_DATA_WIDTH_MASK)

#define uatr_GET_RX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (uatr_RX_CTRL_MSB_FIRST) : (0u))

#define uatr_GET_RX_CTRL_MEDIAN(filterEn)       ((0u != (filterEn)) ? \
                                                                (uatr_RX_CTRL_MEDIAN) : (0u))

/* uatr_RX_MATCH */
#define uatr_GET_RX_MATCH_ADDR(addr)    ((uint32) (addr) & uatr_RX_MATCH_ADDR_MASK)
#define uatr_GET_RX_MATCH_MASK(mask)    (((uint32) (mask) << \
                                                            uatr_RX_MATCH_MASK_POS) & \
                                                            uatr_RX_MATCH_MASK_MASK)

/* uatr_RX_FIFO_CTRL */
#define uatr_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    uatr_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* uatr_TX_CTRL */
#define uatr_GET_TX_CTRL_DATA_WIDTH(dataWidth)  (((uint32) (dataWidth) - 1u) & \
                                                                uatr_RX_CTRL_DATA_WIDTH_MASK)

#define uatr_GET_TX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (uatr_TX_CTRL_MSB_FIRST) : (0u))

/* uatr_TX_FIFO_CTRL */
#define uatr_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level) & \
                                                                    uatr_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK)

/* uatr_INTR_SLAVE_I2C_GENERAL */
#define uatr_GET_INTR_SLAVE_I2C_GENERAL(genCall)  ((0u != (genCall)) ? \
                                                                (uatr_INTR_SLAVE_I2C_GENERAL) : (0u))

/* Return true if master mode is enabled uatr_SPI_CTRL_REG */
#define uatr_CHECK_SPI_MASTER   (0u != (uatr_SPI_CTRL_REG & uatr_SPI_CTRL_MASTER))

/* Return inactive state of SPI SCLK line depends on CPOL */
#define uatr_GET_SPI_SCLK_INACTIVE \
            ((0u == (uatr_SPI_CTRL_REG & uatr_SPI_CTRL_CPOL)) ? (0u) : (1u))

/* Get output pin inactive state */
#if (uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
#define uatr_GET_SPI_SS0_INACTIVE       (1u)
#define uatr_GET_SPI_SS1_INACTIVE       (1u)
#define uatr_GET_SPI_SS2_INACTIVE       (1u)
#define uatr_GET_SPI_SS3_INACTIVE       (1u)
#define uatr_GET_UART_RTS_INACTIVE      (1u)

#else
#define uatr_GET_SPI_SS0_INACTIVE  \
        ((0u != (uatr_SPI_CTRL_REG & uatr_SPI_CTRL_SSEL0_POLARITY)) ? (0u) : (1u))

#define uatr_GET_SPI_SS1_INACTIVE  \
        ((0u != (uatr_SPI_CTRL_REG & uatr_SPI_CTRL_SSEL1_POLARITY)) ? (0u) : (1u))

#define uatr_GET_SPI_SS2_INACTIVE  \
        ((0u != (uatr_SPI_CTRL_REG & uatr_SPI_CTRL_SSEL2_POLARITY)) ? (0u) : (1u))

#define uatr_GET_SPI_SS3_INACTIVE  \
        ((0u != (uatr_SPI_CTRL_REG & uatr_SPI_CTRL_SSEL3_POLARITY)) ? (0u) : (1u))

#define uatr_GET_UART_RTS_INACTIVE \
        ((0u == (uatr_UART_FLOW_CTRL_REG & uatr_UART_FLOW_CTRL_RTS_POLARITY)) ? (0u) : (1u))

#endif /*(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */

/* Clear register constants for configuration and interrupt mask */
#define uatr_CLEAR_REG          ((uint32) (0u))
#define uatr_NO_INTR_SOURCES    ((uint32) (0u))
#define uatr_DUMMY_PARAM        ((uint32) (0u))
#define uatr_SUBMODE_SPI_SLAVE  ((uint32) (0u))

/* Return in case of I2C read error */
#define uatr_I2C_INVALID_BYTE   ((uint32) 0xFFFFFFFFu)
#define uatr_CHECK_VALID_BYTE   ((uint32) 0x80000000u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define uatr_CHECK_INTR_EC_I2C(sourceMask)  uatr_CHECK_INTR_I2C_EC(sourceMask)
#if (!uatr_CY_SCBIP_V1)
    #define uatr_CHECK_INTR_EC_SPI(sourceMask)  uatr_CHECK_INTR_SPI_EC(sourceMask)
#endif /* (!uatr_CY_SCBIP_V1) */

#define uatr_CY_SCBIP_V1_I2C_ONLY   (uatr_CY_SCBIP_V1)

#endif /* (CY_SCB_uatr_H) */


/* [] END OF FILE */
