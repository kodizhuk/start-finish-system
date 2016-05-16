/*******************************************************************************
* File Name: xbee.h
* Version 2.50
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_xbee_H)
#define CY_UART_xbee_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define xbee_RX_ENABLED                     (1u)
#define xbee_TX_ENABLED                     (1u)
#define xbee_HD_ENABLED                     (0u)
#define xbee_RX_INTERRUPT_ENABLED           (0u)
#define xbee_TX_INTERRUPT_ENABLED           (0u)
#define xbee_INTERNAL_CLOCK_USED            (1u)
#define xbee_RXHW_ADDRESS_ENABLED           (0u)
#define xbee_OVER_SAMPLE_COUNT              (8u)
#define xbee_PARITY_TYPE                    (0u)
#define xbee_PARITY_TYPE_SW                 (0u)
#define xbee_BREAK_DETECT                   (0u)
#define xbee_BREAK_BITS_TX                  (13u)
#define xbee_BREAK_BITS_RX                  (13u)
#define xbee_TXCLKGEN_DP                    (1u)
#define xbee_USE23POLLING                   (1u)
#define xbee_FLOW_CONTROL                   (0u)
#define xbee_CLK_FREQ                       (0u)
#define xbee_TX_BUFFER_SIZE                 (4u)
#define xbee_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(xbee_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define xbee_CONTROL_REG_REMOVED            (0u)
#else
    #define xbee_CONTROL_REG_REMOVED            (1u)
#endif /* End xbee_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct xbee_backupStruct_
{
    uint8 enableState;

    #if(xbee_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End xbee_CONTROL_REG_REMOVED */

} xbee_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void xbee_Start(void) ;
void xbee_Stop(void) ;
uint8 xbee_ReadControlRegister(void) ;
void xbee_WriteControlRegister(uint8 control) ;

void xbee_Init(void) ;
void xbee_Enable(void) ;
void xbee_SaveConfig(void) ;
void xbee_RestoreConfig(void) ;
void xbee_Sleep(void) ;
void xbee_Wakeup(void) ;

/* Only if RX is enabled */
#if( (xbee_RX_ENABLED) || (xbee_HD_ENABLED) )

    #if (xbee_RX_INTERRUPT_ENABLED)
        #define xbee_EnableRxInt()  CyIntEnable (xbee_RX_VECT_NUM)
        #define xbee_DisableRxInt() CyIntDisable(xbee_RX_VECT_NUM)
        CY_ISR_PROTO(xbee_RXISR);
    #endif /* xbee_RX_INTERRUPT_ENABLED */

    void xbee_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void xbee_SetRxAddress1(uint8 address) ;
    void xbee_SetRxAddress2(uint8 address) ;

    void  xbee_SetRxInterruptMode(uint8 intSrc) ;
    uint8 xbee_ReadRxData(void) ;
    uint8 xbee_ReadRxStatus(void) ;
    uint8 xbee_GetChar(void) ;
    uint16 xbee_GetByte(void) ;
    uint8 xbee_GetRxBufferSize(void)
                                                            ;
    void xbee_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define xbee_GetRxInterruptSource   xbee_ReadRxStatus

#endif /* End (xbee_RX_ENABLED) || (xbee_HD_ENABLED) */

/* Only if TX is enabled */
#if(xbee_TX_ENABLED || xbee_HD_ENABLED)

    #if(xbee_TX_INTERRUPT_ENABLED)
        #define xbee_EnableTxInt()  CyIntEnable (xbee_TX_VECT_NUM)
        #define xbee_DisableTxInt() CyIntDisable(xbee_TX_VECT_NUM)
        #define xbee_SetPendingTxInt() CyIntSetPending(xbee_TX_VECT_NUM)
        #define xbee_ClearPendingTxInt() CyIntClearPending(xbee_TX_VECT_NUM)
        CY_ISR_PROTO(xbee_TXISR);
    #endif /* xbee_TX_INTERRUPT_ENABLED */

    void xbee_SetTxInterruptMode(uint8 intSrc) ;
    void xbee_WriteTxData(uint8 txDataByte) ;
    uint8 xbee_ReadTxStatus(void) ;
    void xbee_PutChar(uint8 txDataByte) ;
    void xbee_PutString(const char8 string[]) ;
    void xbee_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void xbee_PutCRLF(uint8 txDataByte) ;
    void xbee_ClearTxBuffer(void) ;
    void xbee_SetTxAddressMode(uint8 addressMode) ;
    void xbee_SendBreak(uint8 retMode) ;
    uint8 xbee_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define xbee_PutStringConst         xbee_PutString
    #define xbee_PutArrayConst          xbee_PutArray
    #define xbee_GetTxInterruptSource   xbee_ReadTxStatus

#endif /* End xbee_TX_ENABLED || xbee_HD_ENABLED */

#if(xbee_HD_ENABLED)
    void xbee_LoadRxConfig(void) ;
    void xbee_LoadTxConfig(void) ;
#endif /* End xbee_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_xbee) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    xbee_CyBtldrCommStart(void) CYSMALL ;
    void    xbee_CyBtldrCommStop(void) CYSMALL ;
    void    xbee_CyBtldrCommReset(void) CYSMALL ;
    cystatus xbee_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus xbee_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_xbee)
        #define CyBtldrCommStart    xbee_CyBtldrCommStart
        #define CyBtldrCommStop     xbee_CyBtldrCommStop
        #define CyBtldrCommReset    xbee_CyBtldrCommReset
        #define CyBtldrCommWrite    xbee_CyBtldrCommWrite
        #define CyBtldrCommRead     xbee_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_xbee) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define xbee_BYTE2BYTE_TIME_OUT (25u)
    #define xbee_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define xbee_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define xbee_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define xbee_SET_SPACE      (0x00u)
#define xbee_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (xbee_TX_ENABLED) || (xbee_HD_ENABLED) )
    #if(xbee_TX_INTERRUPT_ENABLED)
        #define xbee_TX_VECT_NUM            (uint8)xbee_TXInternalInterrupt__INTC_NUMBER
        #define xbee_TX_PRIOR_NUM           (uint8)xbee_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* xbee_TX_INTERRUPT_ENABLED */

    #define xbee_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define xbee_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define xbee_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(xbee_TX_ENABLED)
        #define xbee_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (xbee_HD_ENABLED) */
        #define xbee_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (xbee_TX_ENABLED) */

    #define xbee_TX_STS_COMPLETE            (uint8)(0x01u << xbee_TX_STS_COMPLETE_SHIFT)
    #define xbee_TX_STS_FIFO_EMPTY          (uint8)(0x01u << xbee_TX_STS_FIFO_EMPTY_SHIFT)
    #define xbee_TX_STS_FIFO_FULL           (uint8)(0x01u << xbee_TX_STS_FIFO_FULL_SHIFT)
    #define xbee_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << xbee_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (xbee_TX_ENABLED) || (xbee_HD_ENABLED)*/

#if( (xbee_RX_ENABLED) || (xbee_HD_ENABLED) )
    #if(xbee_RX_INTERRUPT_ENABLED)
        #define xbee_RX_VECT_NUM            (uint8)xbee_RXInternalInterrupt__INTC_NUMBER
        #define xbee_RX_PRIOR_NUM           (uint8)xbee_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* xbee_RX_INTERRUPT_ENABLED */
    #define xbee_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define xbee_RX_STS_BREAK_SHIFT             (0x01u)
    #define xbee_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define xbee_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define xbee_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define xbee_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define xbee_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define xbee_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define xbee_RX_STS_MRKSPC           (uint8)(0x01u << xbee_RX_STS_MRKSPC_SHIFT)
    #define xbee_RX_STS_BREAK            (uint8)(0x01u << xbee_RX_STS_BREAK_SHIFT)
    #define xbee_RX_STS_PAR_ERROR        (uint8)(0x01u << xbee_RX_STS_PAR_ERROR_SHIFT)
    #define xbee_RX_STS_STOP_ERROR       (uint8)(0x01u << xbee_RX_STS_STOP_ERROR_SHIFT)
    #define xbee_RX_STS_OVERRUN          (uint8)(0x01u << xbee_RX_STS_OVERRUN_SHIFT)
    #define xbee_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << xbee_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define xbee_RX_STS_ADDR_MATCH       (uint8)(0x01u << xbee_RX_STS_ADDR_MATCH_SHIFT)
    #define xbee_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << xbee_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define xbee_RX_HW_MASK                     (0x7Fu)
#endif /* End (xbee_RX_ENABLED) || (xbee_HD_ENABLED) */

/* Control Register definitions */
#define xbee_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define xbee_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define xbee_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define xbee_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define xbee_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define xbee_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define xbee_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define xbee_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define xbee_CTRL_HD_SEND               (uint8)(0x01u << xbee_CTRL_HD_SEND_SHIFT)
#define xbee_CTRL_HD_SEND_BREAK         (uint8)(0x01u << xbee_CTRL_HD_SEND_BREAK_SHIFT)
#define xbee_CTRL_MARK                  (uint8)(0x01u << xbee_CTRL_MARK_SHIFT)
#define xbee_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << xbee_CTRL_PARITY_TYPE0_SHIFT)
#define xbee_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << xbee_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define xbee_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define xbee_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define xbee_SEND_BREAK                         (0x00u)
#define xbee_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define xbee_REINIT                             (0x02u)
#define xbee_SEND_WAIT_REINIT                   (0x03u)

#define xbee_OVER_SAMPLE_8                      (8u)
#define xbee_OVER_SAMPLE_16                     (16u)

#define xbee_BIT_CENTER                         (xbee_OVER_SAMPLE_COUNT - 2u)

#define xbee_FIFO_LENGTH                        (4u)
#define xbee_NUMBER_OF_START_BIT                (1u)
#define xbee_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define xbee_TXBITCTR_BREAKBITS8X   ((xbee_BREAK_BITS_TX * xbee_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define xbee_TXBITCTR_BREAKBITS ((xbee_BREAK_BITS_TX * xbee_OVER_SAMPLE_COUNT) - 1u)

#define xbee_HALF_BIT_COUNT   \
                            (((xbee_OVER_SAMPLE_COUNT / 2u) + (xbee_USE23POLLING * 1u)) - 2u)
#if (xbee_OVER_SAMPLE_COUNT == xbee_OVER_SAMPLE_8)
    #define xbee_HD_TXBITCTR_INIT   (((xbee_BREAK_BITS_TX + \
                            xbee_NUMBER_OF_START_BIT) * xbee_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define xbee_RXBITCTR_INIT  ((((xbee_BREAK_BITS_RX + xbee_NUMBER_OF_START_BIT) \
                            * xbee_OVER_SAMPLE_COUNT) + xbee_HALF_BIT_COUNT) - 1u)

#else /* xbee_OVER_SAMPLE_COUNT == xbee_OVER_SAMPLE_16 */
    #define xbee_HD_TXBITCTR_INIT   ((8u * xbee_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define xbee_RXBITCTR_INIT      (((7u * xbee_OVER_SAMPLE_COUNT) - 1u) + \
                                                      xbee_HALF_BIT_COUNT)
#endif /* End xbee_OVER_SAMPLE_COUNT */

#define xbee_HD_RXBITCTR_INIT                   xbee_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 xbee_initVar;
#if (xbee_TX_INTERRUPT_ENABLED && xbee_TX_ENABLED)
    extern volatile uint8 xbee_txBuffer[xbee_TX_BUFFER_SIZE];
    extern volatile uint8 xbee_txBufferRead;
    extern uint8 xbee_txBufferWrite;
#endif /* (xbee_TX_INTERRUPT_ENABLED && xbee_TX_ENABLED) */
#if (xbee_RX_INTERRUPT_ENABLED && (xbee_RX_ENABLED || xbee_HD_ENABLED))
    extern uint8 xbee_errorStatus;
    extern volatile uint8 xbee_rxBuffer[xbee_RX_BUFFER_SIZE];
    extern volatile uint8 xbee_rxBufferRead;
    extern volatile uint8 xbee_rxBufferWrite;
    extern volatile uint8 xbee_rxBufferLoopDetect;
    extern volatile uint8 xbee_rxBufferOverflow;
    #if (xbee_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 xbee_rxAddressMode;
        extern volatile uint8 xbee_rxAddressDetected;
    #endif /* (xbee_RXHW_ADDRESS_ENABLED) */
#endif /* (xbee_RX_INTERRUPT_ENABLED && (xbee_RX_ENABLED || xbee_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define xbee__B_UART__AM_SW_BYTE_BYTE 1
#define xbee__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define xbee__B_UART__AM_HW_BYTE_BY_BYTE 3
#define xbee__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define xbee__B_UART__AM_NONE 0

#define xbee__B_UART__NONE_REVB 0
#define xbee__B_UART__EVEN_REVB 1
#define xbee__B_UART__ODD_REVB 2
#define xbee__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define xbee_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define xbee_NUMBER_OF_STOP_BITS    (1u)

#if (xbee_RXHW_ADDRESS_ENABLED)
    #define xbee_RX_ADDRESS_MODE    (0u)
    #define xbee_RX_HW_ADDRESS1     (0u)
    #define xbee_RX_HW_ADDRESS2     (0u)
#endif /* (xbee_RXHW_ADDRESS_ENABLED) */

#define xbee_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((1 << xbee_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << xbee_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << xbee_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << xbee_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << xbee_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << xbee_RX_STS_BREAK_SHIFT) \
                                        | (0 << xbee_RX_STS_OVERRUN_SHIFT))

#define xbee_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << xbee_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << xbee_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << xbee_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << xbee_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef xbee_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define xbee_CONTROL_REG \
                            (* (reg8 *) xbee_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define xbee_CONTROL_PTR \
                            (  (reg8 *) xbee_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End xbee_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(xbee_TX_ENABLED)
    #define xbee_TXDATA_REG          (* (reg8 *) xbee_BUART_sTX_TxShifter_u0__F0_REG)
    #define xbee_TXDATA_PTR          (  (reg8 *) xbee_BUART_sTX_TxShifter_u0__F0_REG)
    #define xbee_TXDATA_AUX_CTL_REG  (* (reg8 *) xbee_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define xbee_TXDATA_AUX_CTL_PTR  (  (reg8 *) xbee_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define xbee_TXSTATUS_REG        (* (reg8 *) xbee_BUART_sTX_TxSts__STATUS_REG)
    #define xbee_TXSTATUS_PTR        (  (reg8 *) xbee_BUART_sTX_TxSts__STATUS_REG)
    #define xbee_TXSTATUS_MASK_REG   (* (reg8 *) xbee_BUART_sTX_TxSts__MASK_REG)
    #define xbee_TXSTATUS_MASK_PTR   (  (reg8 *) xbee_BUART_sTX_TxSts__MASK_REG)
    #define xbee_TXSTATUS_ACTL_REG   (* (reg8 *) xbee_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define xbee_TXSTATUS_ACTL_PTR   (  (reg8 *) xbee_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(xbee_TXCLKGEN_DP)
        #define xbee_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) xbee_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define xbee_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) xbee_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define xbee_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) xbee_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define xbee_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) xbee_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define xbee_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) xbee_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define xbee_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) xbee_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define xbee_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) xbee_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define xbee_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) xbee_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define xbee_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) xbee_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define xbee_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) xbee_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* xbee_TXCLKGEN_DP */

#endif /* End xbee_TX_ENABLED */

#if(xbee_HD_ENABLED)

    #define xbee_TXDATA_REG             (* (reg8 *) xbee_BUART_sRX_RxShifter_u0__F1_REG )
    #define xbee_TXDATA_PTR             (  (reg8 *) xbee_BUART_sRX_RxShifter_u0__F1_REG )
    #define xbee_TXDATA_AUX_CTL_REG     (* (reg8 *) xbee_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define xbee_TXDATA_AUX_CTL_PTR     (  (reg8 *) xbee_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define xbee_TXSTATUS_REG           (* (reg8 *) xbee_BUART_sRX_RxSts__STATUS_REG )
    #define xbee_TXSTATUS_PTR           (  (reg8 *) xbee_BUART_sRX_RxSts__STATUS_REG )
    #define xbee_TXSTATUS_MASK_REG      (* (reg8 *) xbee_BUART_sRX_RxSts__MASK_REG )
    #define xbee_TXSTATUS_MASK_PTR      (  (reg8 *) xbee_BUART_sRX_RxSts__MASK_REG )
    #define xbee_TXSTATUS_ACTL_REG      (* (reg8 *) xbee_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define xbee_TXSTATUS_ACTL_PTR      (  (reg8 *) xbee_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End xbee_HD_ENABLED */

#if( (xbee_RX_ENABLED) || (xbee_HD_ENABLED) )
    #define xbee_RXDATA_REG             (* (reg8 *) xbee_BUART_sRX_RxShifter_u0__F0_REG )
    #define xbee_RXDATA_PTR             (  (reg8 *) xbee_BUART_sRX_RxShifter_u0__F0_REG )
    #define xbee_RXADDRESS1_REG         (* (reg8 *) xbee_BUART_sRX_RxShifter_u0__D0_REG )
    #define xbee_RXADDRESS1_PTR         (  (reg8 *) xbee_BUART_sRX_RxShifter_u0__D0_REG )
    #define xbee_RXADDRESS2_REG         (* (reg8 *) xbee_BUART_sRX_RxShifter_u0__D1_REG )
    #define xbee_RXADDRESS2_PTR         (  (reg8 *) xbee_BUART_sRX_RxShifter_u0__D1_REG )
    #define xbee_RXDATA_AUX_CTL_REG     (* (reg8 *) xbee_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define xbee_RXBITCTR_PERIOD_REG    (* (reg8 *) xbee_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define xbee_RXBITCTR_PERIOD_PTR    (  (reg8 *) xbee_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define xbee_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) xbee_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define xbee_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) xbee_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define xbee_RXBITCTR_COUNTER_REG   (* (reg8 *) xbee_BUART_sRX_RxBitCounter__COUNT_REG )
    #define xbee_RXBITCTR_COUNTER_PTR   (  (reg8 *) xbee_BUART_sRX_RxBitCounter__COUNT_REG )

    #define xbee_RXSTATUS_REG           (* (reg8 *) xbee_BUART_sRX_RxSts__STATUS_REG )
    #define xbee_RXSTATUS_PTR           (  (reg8 *) xbee_BUART_sRX_RxSts__STATUS_REG )
    #define xbee_RXSTATUS_MASK_REG      (* (reg8 *) xbee_BUART_sRX_RxSts__MASK_REG )
    #define xbee_RXSTATUS_MASK_PTR      (  (reg8 *) xbee_BUART_sRX_RxSts__MASK_REG )
    #define xbee_RXSTATUS_ACTL_REG      (* (reg8 *) xbee_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define xbee_RXSTATUS_ACTL_PTR      (  (reg8 *) xbee_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (xbee_RX_ENABLED) || (xbee_HD_ENABLED) */

#if(xbee_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define xbee_INTCLOCK_CLKEN_REG     (* (reg8 *) xbee_IntClock__PM_ACT_CFG)
    #define xbee_INTCLOCK_CLKEN_PTR     (  (reg8 *) xbee_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define xbee_INTCLOCK_CLKEN_MASK    xbee_IntClock__PM_ACT_MSK
#endif /* End xbee_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(xbee_TX_ENABLED)
    #define xbee_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End xbee_TX_ENABLED */

#if(xbee_HD_ENABLED)
    #define xbee_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End xbee_HD_ENABLED */

#if( (xbee_RX_ENABLED) || (xbee_HD_ENABLED) )
    #define xbee_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (xbee_RX_ENABLED) || (xbee_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define xbee_WAIT_1_MS      xbee_BL_CHK_DELAY_MS   

#define xbee_TXBUFFERSIZE   xbee_TX_BUFFER_SIZE
#define xbee_RXBUFFERSIZE   xbee_RX_BUFFER_SIZE

#if (xbee_RXHW_ADDRESS_ENABLED)
    #define xbee_RXADDRESSMODE  xbee_RX_ADDRESS_MODE
    #define xbee_RXHWADDRESS1   xbee_RX_HW_ADDRESS1
    #define xbee_RXHWADDRESS2   xbee_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define xbee_RXAddressMode  xbee_RXADDRESSMODE
#endif /* (xbee_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define xbee_initvar                    xbee_initVar

#define xbee_RX_Enabled                 xbee_RX_ENABLED
#define xbee_TX_Enabled                 xbee_TX_ENABLED
#define xbee_HD_Enabled                 xbee_HD_ENABLED
#define xbee_RX_IntInterruptEnabled     xbee_RX_INTERRUPT_ENABLED
#define xbee_TX_IntInterruptEnabled     xbee_TX_INTERRUPT_ENABLED
#define xbee_InternalClockUsed          xbee_INTERNAL_CLOCK_USED
#define xbee_RXHW_Address_Enabled       xbee_RXHW_ADDRESS_ENABLED
#define xbee_OverSampleCount            xbee_OVER_SAMPLE_COUNT
#define xbee_ParityType                 xbee_PARITY_TYPE

#if( xbee_TX_ENABLED && (xbee_TXBUFFERSIZE > xbee_FIFO_LENGTH))
    #define xbee_TXBUFFER               xbee_txBuffer
    #define xbee_TXBUFFERREAD           xbee_txBufferRead
    #define xbee_TXBUFFERWRITE          xbee_txBufferWrite
#endif /* End xbee_TX_ENABLED */
#if( ( xbee_RX_ENABLED || xbee_HD_ENABLED ) && \
     (xbee_RXBUFFERSIZE > xbee_FIFO_LENGTH) )
    #define xbee_RXBUFFER               xbee_rxBuffer
    #define xbee_RXBUFFERREAD           xbee_rxBufferRead
    #define xbee_RXBUFFERWRITE          xbee_rxBufferWrite
    #define xbee_RXBUFFERLOOPDETECT     xbee_rxBufferLoopDetect
    #define xbee_RXBUFFER_OVERFLOW      xbee_rxBufferOverflow
#endif /* End xbee_RX_ENABLED */

#ifdef xbee_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define xbee_CONTROL                xbee_CONTROL_REG
#endif /* End xbee_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(xbee_TX_ENABLED)
    #define xbee_TXDATA                 xbee_TXDATA_REG
    #define xbee_TXSTATUS               xbee_TXSTATUS_REG
    #define xbee_TXSTATUS_MASK          xbee_TXSTATUS_MASK_REG
    #define xbee_TXSTATUS_ACTL          xbee_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(xbee_TXCLKGEN_DP)
        #define xbee_TXBITCLKGEN_CTR        xbee_TXBITCLKGEN_CTR_REG
        #define xbee_TXBITCLKTX_COMPLETE    xbee_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define xbee_TXBITCTR_PERIOD        xbee_TXBITCTR_PERIOD_REG
        #define xbee_TXBITCTR_CONTROL       xbee_TXBITCTR_CONTROL_REG
        #define xbee_TXBITCTR_COUNTER       xbee_TXBITCTR_COUNTER_REG
    #endif /* xbee_TXCLKGEN_DP */
#endif /* End xbee_TX_ENABLED */

#if(xbee_HD_ENABLED)
    #define xbee_TXDATA                 xbee_TXDATA_REG
    #define xbee_TXSTATUS               xbee_TXSTATUS_REG
    #define xbee_TXSTATUS_MASK          xbee_TXSTATUS_MASK_REG
    #define xbee_TXSTATUS_ACTL          xbee_TXSTATUS_ACTL_REG
#endif /* End xbee_HD_ENABLED */

#if( (xbee_RX_ENABLED) || (xbee_HD_ENABLED) )
    #define xbee_RXDATA                 xbee_RXDATA_REG
    #define xbee_RXADDRESS1             xbee_RXADDRESS1_REG
    #define xbee_RXADDRESS2             xbee_RXADDRESS2_REG
    #define xbee_RXBITCTR_PERIOD        xbee_RXBITCTR_PERIOD_REG
    #define xbee_RXBITCTR_CONTROL       xbee_RXBITCTR_CONTROL_REG
    #define xbee_RXBITCTR_COUNTER       xbee_RXBITCTR_COUNTER_REG
    #define xbee_RXSTATUS               xbee_RXSTATUS_REG
    #define xbee_RXSTATUS_MASK          xbee_RXSTATUS_MASK_REG
    #define xbee_RXSTATUS_ACTL          xbee_RXSTATUS_ACTL_REG
#endif /* End  (xbee_RX_ENABLED) || (xbee_HD_ENABLED) */

#if(xbee_INTERNAL_CLOCK_USED)
    #define xbee_INTCLOCK_CLKEN         xbee_INTCLOCK_CLKEN_REG
#endif /* End xbee_INTERNAL_CLOCK_USED */

#define xbee_WAIT_FOR_COMLETE_REINIT    xbee_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_xbee_H */


/* [] END OF FILE */
