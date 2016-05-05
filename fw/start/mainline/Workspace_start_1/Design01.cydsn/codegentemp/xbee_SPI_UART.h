/*******************************************************************************
* File Name: xbee_SPI_UART.h
* Version 3.10
*
* Description:
*  This file provides constants and parameter values for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_xbee_H)
#define CY_SCB_SPI_UART_xbee_H

#include "xbee.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define xbee_SPI_MODE                   (0u)
#define xbee_SPI_SUB_MODE               (0u)
#define xbee_SPI_CLOCK_MODE             (0u)
#define xbee_SPI_OVS_FACTOR             (16u)
#define xbee_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define xbee_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define xbee_SPI_RX_DATA_BITS_NUM       (8u)
#define xbee_SPI_TX_DATA_BITS_NUM       (8u)
#define xbee_SPI_WAKE_ENABLE            (0u)
#define xbee_SPI_BITS_ORDER             (1u)
#define xbee_SPI_TRANSFER_SEPARATION    (1u)
#define xbee_SPI_NUMBER_OF_SS_LINES     (1u)
#define xbee_SPI_RX_BUFFER_SIZE         (8u)
#define xbee_SPI_TX_BUFFER_SIZE         (8u)

#define xbee_SPI_INTERRUPT_MODE         (0u)

#define xbee_SPI_INTR_RX_MASK           (0u)
#define xbee_SPI_INTR_TX_MASK           (0u)

#define xbee_SPI_RX_TRIGGER_LEVEL       (7u)
#define xbee_SPI_TX_TRIGGER_LEVEL       (0u)

#define xbee_SPI_BYTE_MODE_ENABLE       (0u)
#define xbee_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define xbee_SPI_SS0_POLARITY           (0u)
#define xbee_SPI_SS1_POLARITY           (0u)
#define xbee_SPI_SS2_POLARITY           (0u)
#define xbee_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define xbee_UART_SUB_MODE              (0u)
#define xbee_UART_DIRECTION             (3u)
#define xbee_UART_DATA_BITS_NUM         (8u)
#define xbee_UART_PARITY_TYPE           (2u)
#define xbee_UART_STOP_BITS_NUM         (2u)
#define xbee_UART_OVS_FACTOR            (12u)
#define xbee_UART_IRDA_LOW_POWER        (0u)
#define xbee_UART_MEDIAN_FILTER_ENABLE  (0u)
#define xbee_UART_RETRY_ON_NACK         (0u)
#define xbee_UART_IRDA_POLARITY         (0u)
#define xbee_UART_DROP_ON_FRAME_ERR     (0u)
#define xbee_UART_DROP_ON_PARITY_ERR    (0u)
#define xbee_UART_WAKE_ENABLE           (0u)
#define xbee_UART_RX_BUFFER_SIZE        (8u)
#define xbee_UART_TX_BUFFER_SIZE        (8u)
#define xbee_UART_MP_MODE_ENABLE        (0u)
#define xbee_UART_MP_ACCEPT_ADDRESS     (0u)
#define xbee_UART_MP_RX_ADDRESS         (2u)
#define xbee_UART_MP_RX_ADDRESS_MASK    (255u)

#define xbee_UART_INTERRUPT_MODE        (0u)

#define xbee_UART_INTR_RX_MASK          (0u)
#define xbee_UART_INTR_TX_MASK          (0u)

#define xbee_UART_RX_TRIGGER_LEVEL      (7u)
#define xbee_UART_TX_TRIGGER_LEVEL      (0u)

#define xbee_UART_BYTE_MODE_ENABLE      (0u)
#define xbee_UART_CTS_ENABLE            (0u)
#define xbee_UART_CTS_POLARITY          (0u)
#define xbee_UART_RTS_ENABLE            (0u)
#define xbee_UART_RTS_POLARITY          (0u)
#define xbee_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define xbee_SPI_SLAVE  (0u)
#define xbee_SPI_MASTER (1u)

/* UART direction enum */
#define xbee_UART_RX    (1u)
#define xbee_UART_TX    (2u)
#define xbee_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(xbee_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define xbee_SPI_SLAVE_CONST        (1u)
    #define xbee_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define xbee_RX_DIRECTION           (1u)
    #define xbee_TX_DIRECTION           (1u)
    #define xbee_UART_RX_DIRECTION      (1u)
    #define xbee_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define xbee_INTERNAL_RX_SW_BUFFER   (0u)
    #define xbee_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define xbee_INTERNAL_RX_BUFFER_SIZE    (xbee_rxBufferSize + 1u)
    #define xbee_RX_BUFFER_SIZE             (xbee_rxBufferSize)
    #define xbee_TX_BUFFER_SIZE             (xbee_txBufferSize)

    /* Return true if buffer is provided */
    #define xbee_CHECK_RX_SW_BUFFER (NULL != xbee_rxBuffer)
    #define xbee_CHECK_TX_SW_BUFFER (NULL != xbee_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define xbee_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define xbee_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define xbee_SPI_WAKE_ENABLE_CONST  (1u)
    #define xbee_CHECK_SPI_WAKE_ENABLE  (0u != xbee_scbEnableWake)
    #define xbee_UART_WAKE_ENABLE_CONST (1u)

    /* SPI/UART: TX or RX FIFO size */
    #if (xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1)
        #define xbee_SPI_UART_FIFO_SIZE             (xbee_FIFO_SIZE)
        #define xbee_CHECK_UART_RTS_CONTROL_FLOW    (0u)
    #else
        #define xbee_SPI_UART_FIFO_SIZE (xbee_GET_FIFO_SIZE(xbee_CTRL_REG & \
                                                                                    xbee_CTRL_BYTE_MODE))

        #define xbee_CHECK_UART_RTS_CONTROL_FLOW \
                    ((xbee_SCB_MODE_UART_RUNTM_CFG) && \
                     (0u != xbee_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(xbee_UART_FLOW_CTRL_REG)))
    #endif /* (xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (xbee_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define xbee_SPI_RX_DIRECTION (1u)
        #define xbee_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #if (xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1)
            #define xbee_SPI_UART_FIFO_SIZE    (xbee_FIFO_SIZE)
        #else
            #define xbee_SPI_UART_FIFO_SIZE \
                                           xbee_GET_FIFO_SIZE(xbee_SPI_BYTE_MODE_ENABLE)

        #endif /* (xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1) */

        /* SPI internal RX and TX buffers */
        #define xbee_INTERNAL_SPI_RX_SW_BUFFER  (xbee_SPI_RX_BUFFER_SIZE > \
                                                                xbee_SPI_UART_FIFO_SIZE)
        #define xbee_INTERNAL_SPI_TX_SW_BUFFER  (xbee_SPI_TX_BUFFER_SIZE > \
                                                                xbee_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define xbee_INTERNAL_RX_SW_BUFFER  (xbee_INTERNAL_SPI_RX_SW_BUFFER)
        #define xbee_INTERNAL_TX_SW_BUFFER  (xbee_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define xbee_INTERNAL_RX_BUFFER_SIZE    (xbee_SPI_RX_BUFFER_SIZE + 1u)
        #define xbee_RX_BUFFER_SIZE             (xbee_SPI_RX_BUFFER_SIZE)
        #define xbee_TX_BUFFER_SIZE             (xbee_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define xbee_SPI_WAKE_ENABLE_CONST  (0u != xbee_SPI_WAKE_ENABLE)
        #define xbee_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define xbee_UART_RX_DIRECTION (0u != (xbee_UART_DIRECTION & xbee_UART_RX))
        #define xbee_UART_TX_DIRECTION (0u != (xbee_UART_DIRECTION & xbee_UART_TX))

        /* Get FIFO size */
        #if (xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1)
            #define xbee_SPI_UART_FIFO_SIZE    (xbee_FIFO_SIZE)
        #else
            #define xbee_SPI_UART_FIFO_SIZE \
                                           xbee_GET_FIFO_SIZE(xbee_UART_BYTE_MODE_ENABLE)
        #endif /* (xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1) */

        /* UART internal RX and TX buffers */
        #define xbee_INTERNAL_UART_RX_SW_BUFFER  (xbee_UART_RX_BUFFER_SIZE > \
                                                                xbee_SPI_UART_FIFO_SIZE)
        #define xbee_INTERNAL_UART_TX_SW_BUFFER  (xbee_UART_TX_BUFFER_SIZE > \
                                                                    xbee_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define xbee_INTERNAL_RX_SW_BUFFER  (xbee_INTERNAL_UART_RX_SW_BUFFER)
        #define xbee_INTERNAL_TX_SW_BUFFER  (xbee_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define xbee_INTERNAL_RX_BUFFER_SIZE    (xbee_UART_RX_BUFFER_SIZE + 1u)
        #define xbee_RX_BUFFER_SIZE             (xbee_UART_RX_BUFFER_SIZE)
        #define xbee_TX_BUFFER_SIZE             (xbee_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define xbee_SPI_WAKE_ENABLE_CONST  (0u)
        #define xbee_UART_WAKE_ENABLE_CONST (0u != xbee_UART_WAKE_ENABLE)

    #endif /* (xbee_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define xbee_SPI_SLAVE_CONST    (xbee_SPI_MODE == xbee_SPI_SLAVE)
    #define xbee_SPI_MASTER_CONST   (xbee_SPI_MODE == xbee_SPI_MASTER)

    /* Direction */
    #define xbee_RX_DIRECTION ((xbee_SCB_MODE_SPI_CONST_CFG) ? \
                                            (xbee_SPI_RX_DIRECTION) : (xbee_UART_RX_DIRECTION))

    #define xbee_TX_DIRECTION ((xbee_SCB_MODE_SPI_CONST_CFG) ? \
                                            (xbee_SPI_TX_DIRECTION) : (xbee_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define xbee_CHECK_RX_SW_BUFFER (xbee_INTERNAL_RX_SW_BUFFER)
    #define xbee_CHECK_TX_SW_BUFFER (xbee_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define xbee_INTERNAL_RX_SW_BUFFER_CONST    (xbee_INTERNAL_RX_SW_BUFFER)
    #define xbee_INTERNAL_TX_SW_BUFFER_CONST    (xbee_INTERNAL_TX_SW_BUFFER)

    /* SPI wakeup */
    #define xbee_CHECK_SPI_WAKE_ENABLE  (xbee_SPI_WAKE_ENABLE_CONST)

    /* UART flow control: not applicable for CY_SCBIP_V0 || CY_SCBIP_V1 */
    #define xbee_CHECK_UART_RTS_CONTROL_FLOW    (xbee_SCB_MODE_UART_CONST_CFG && \
                                                             xbee_UART_RTS_ENABLE)

#endif /* End (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/* xbee_SPI_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 submode;
    uint32 sclkMode;
    uint32 oversample;
    uint32 enableMedianFilter;
    uint32 enableLateSampling;
    uint32 enableWake;
    uint32 rxDataBits;
    uint32 txDataBits;
    uint32 bitOrder;
    uint32 transferSeperation;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableFreeRunSclk;
    uint8 polaritySs;
} xbee_SPI_INIT_STRUCT;

/* xbee_UART_INIT_STRUCT */
typedef struct
{
    uint32 mode;
    uint32 direction;
    uint32 dataBits;
    uint32 parity;
    uint32 stopBits;
    uint32 oversample;
    uint32 enableIrdaLowPower;
    uint32 enableMedianFilter;
    uint32 enableRetryNack;
    uint32 enableInvertedRx;
    uint32 dropOnParityErr;
    uint32 dropOnFrameErr;
    uint32 enableWake;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableMultiproc;
    uint32 multiprocAcceptAddr;
    uint32 multiprocAddr;
    uint32 multiprocAddrMask;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
    uint8 enableByteMode;
    uint8 enableCts;
    uint8 ctsPolarity;
    uint8 rtsRxFifoLevel;
    uint8 rtsPolarity;
} xbee_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(xbee_SCB_MODE_UNCONFIG_CONST_CFG)
    void xbee_SpiInit(const xbee_SPI_INIT_STRUCT *config);
#endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(xbee_SCB_MODE_SPI_INC)
    #define xbee_SpiIsBusBusy() ((uint32) (0u != (xbee_SPI_STATUS_REG & \
                                                              xbee_SPI_STATUS_BUS_BUSY)))

    #if (xbee_SPI_MASTER_CONST)
        void xbee_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(xbee_SPI_MASTER_CONST) */

    #if !(xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1)
        void xbee_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1) */
#endif /* (xbee_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(xbee_SCB_MODE_UNCONFIG_CONST_CFG)
    void xbee_UartInit(const xbee_UART_INIT_STRUCT *config);
#endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(xbee_SCB_MODE_UART_INC)
    void xbee_UartSetRxAddress(uint32 address);
    void xbee_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(xbee_UART_RX_DIRECTION)
        uint32 xbee_UartGetChar(void);
        uint32 xbee_UartGetByte(void);

        #if !(xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void xbee_UartSetRtsPolarity(uint32 polarity);
            void xbee_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1) */
    #endif /* (xbee_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(xbee_UART_TX_DIRECTION)
        #define xbee_UartPutChar(ch)    xbee_SpiUartWriteTxData((uint32)(ch))
        void xbee_UartPutString(const char8 string[]);
        void xbee_UartPutCRLF(uint32 txDataByte);

        #if !(xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void xbee_UartEnableCts(void);
            void xbee_UartDisableCts(void);
            void xbee_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(xbee_CY_SCBIP_V0 || xbee_CY_SCBIP_V1) */
    #endif /* (xbee_UART_TX_DIRECTION) */
#endif /* (xbee_SCB_MODE_UART_INC) */

/* Common APIs RX direction */
#if(xbee_RX_DIRECTION)
    uint32 xbee_SpiUartReadRxData(void);
    uint32 xbee_SpiUartGetRxBufferSize(void);
    void   xbee_SpiUartClearRxBuffer(void);
#endif /* (xbee_RX_DIRECTION) */

/* Common APIs TX direction */
#if(xbee_TX_DIRECTION)
    void   xbee_SpiUartWriteTxData(uint32 txData);
    void   xbee_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    uint32 xbee_SpiUartGetTxBufferSize(void);
    void   xbee_SpiUartClearTxBuffer(void);
#endif /* (xbee_TX_DIRECTION) */

CY_ISR_PROTO(xbee_SPI_UART_ISR);

#if(xbee_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(xbee_UART_WAKEUP_ISR);
#endif /* (xbee_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(xbee_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   xbee_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 xbee_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   xbee_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 xbee_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(xbee_INTERNAL_RX_SW_BUFFER_CONST)
        #define xbee_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    xbee_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define xbee_GetWordFromRxBuffer(idx) xbee_rxBufferInternal[(idx)]

    #endif /* (xbee_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(xbee_INTERNAL_TX_SW_BUFFER_CONST)
        #define xbee_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        xbee_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define xbee_GetWordFromTxBuffer(idx) xbee_txBufferInternal[(idx)]

    #endif /* (xbee_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (xbee_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define xbee_SPI_MODE_MOTOROLA      (0x00u)
#define xbee_SPI_MODE_TI_COINCIDES  (0x01u)
#define xbee_SPI_MODE_TI_PRECEDES   (0x11u)
#define xbee_SPI_MODE_NATIONAL      (0x02u)
#define xbee_SPI_MODE_MASK          (0x03u)
#define xbee_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define xbee_SPI_MODE_NS_MICROWIRE  (xbee_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define xbee_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define xbee_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define xbee_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define xbee_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define xbee_BITS_ORDER_LSB_FIRST   (0u)
#define xbee_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define xbee_SPI_TRANSFER_SEPARATED     (0u)
#define xbee_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define xbee_SPI_SLAVE_SELECT0    (xbee_SCB__SS0_POSISTION)
#define xbee_SPI_SLAVE_SELECT1    (xbee_SCB__SS1_POSISTION)
#define xbee_SPI_SLAVE_SELECT2    (xbee_SCB__SS2_POSISTION)
#define xbee_SPI_SLAVE_SELECT3    (xbee_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define xbee_SPI_SS_ACTIVE_LOW  (0u)
#define xbee_SPI_SS_ACTIVE_HIGH (1u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define xbee_UART_MODE_STD          (0u)
#define xbee_UART_MODE_SMARTCARD    (1u)
#define xbee_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define xbee_UART_RX    (1u)
#define xbee_UART_TX    (2u)
#define xbee_UART_TX_RX (3u)

/* UART parity enum */
#define xbee_UART_PARITY_EVEN   (0u)
#define xbee_UART_PARITY_ODD    (1u)
#define xbee_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define xbee_UART_STOP_BITS_1   (2u)
#define xbee_UART_STOP_BITS_1_5 (3u)
#define xbee_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define xbee_UART_IRDA_LP_OVS16     (16u)
#define xbee_UART_IRDA_LP_OVS32     (32u)
#define xbee_UART_IRDA_LP_OVS48     (48u)
#define xbee_UART_IRDA_LP_OVS96     (96u)
#define xbee_UART_IRDA_LP_OVS192    (192u)
#define xbee_UART_IRDA_LP_OVS768    (768u)
#define xbee_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define xbee_UART_MP_MARK       (0x100u)
#define xbee_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define xbee_UART_CTS_ACTIVE_LOW    (0u)
#define xbee_UART_CTS_ACTIVE_HIGH   (1u)
#define xbee_UART_RTS_ACTIVE_LOW    (0u)
#define xbee_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define xbee_INTR_RX_ERR        (xbee_INTR_RX_OVERFLOW    | \
                                             xbee_INTR_RX_UNDERFLOW   | \
                                             xbee_INTR_RX_FRAME_ERROR | \
                                             xbee_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for xbee_UartGetByte() */
#define xbee_UART_RX_OVERFLOW       (xbee_INTR_RX_OVERFLOW << 8u)
#define xbee_UART_RX_UNDERFLOW      (xbee_INTR_RX_UNDERFLOW << 8u)
#define xbee_UART_RX_FRAME_ERROR    (xbee_INTR_RX_FRAME_ERROR << 8u)
#define xbee_UART_RX_PARITY_ERROR   (xbee_INTR_RX_PARITY_ERROR << 8u)
#define xbee_UART_RX_ERROR_MASK     (xbee_UART_RX_OVERFLOW    | \
                                                 xbee_UART_RX_UNDERFLOW   | \
                                                 xbee_UART_RX_FRAME_ERROR | \
                                                 xbee_UART_RX_PARITY_ERROR)


/***************************************
*     Vars with External Linkage
***************************************/

#if(xbee_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const xbee_SPI_INIT_STRUCT  xbee_configSpi;
    extern const xbee_UART_INIT_STRUCT xbee_configUart;
#endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define xbee_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & xbee_INTR_SLAVE_SPI_BUS_ERROR)
#define xbee_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & xbee_INTR_MASTER_SPI_DONE)
#define xbee_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~xbee_INTR_SLAVE_SPI_BUS_ERROR)

#define xbee_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~xbee_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define xbee_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((xbee_UART_IRDA_LP_OVS16   == (oversample)) ? xbee_CTRL_OVS_IRDA_LP_OVS16 : \
         ((xbee_UART_IRDA_LP_OVS32   == (oversample)) ? xbee_CTRL_OVS_IRDA_LP_OVS32 : \
          ((xbee_UART_IRDA_LP_OVS48   == (oversample)) ? xbee_CTRL_OVS_IRDA_LP_OVS48 : \
           ((xbee_UART_IRDA_LP_OVS96   == (oversample)) ? xbee_CTRL_OVS_IRDA_LP_OVS96 : \
            ((xbee_UART_IRDA_LP_OVS192  == (oversample)) ? xbee_CTRL_OVS_IRDA_LP_OVS192 : \
             ((xbee_UART_IRDA_LP_OVS768  == (oversample)) ? xbee_CTRL_OVS_IRDA_LP_OVS768 : \
              ((xbee_UART_IRDA_LP_OVS1536 == (oversample)) ? xbee_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          xbee_CTRL_OVS_IRDA_LP_OVS16)))))))

#define xbee_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (xbee_UART_RX & (direction))) ? \
                                                                     (xbee_RX_CTRL_ENABLED) : (0u))

#define xbee_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (xbee_UART_TX & (direction))) ? \
                                                                     (xbee_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define xbee_CTRL_SPI      (xbee_CTRL_MODE_SPI)
#define xbee_SPI_RX_CTRL   (xbee_RX_CTRL_ENABLED)
#define xbee_SPI_TX_CTRL   (xbee_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define xbee_SPI_SS_POLARITY \
             (((uint32) xbee_SPI_SS0_POLARITY << xbee_SPI_SLAVE_SELECT0) | \
              ((uint32) xbee_SPI_SS1_POLARITY << xbee_SPI_SLAVE_SELECT1) | \
              ((uint32) xbee_SPI_SS2_POLARITY << xbee_SPI_SLAVE_SELECT2) | \
              ((uint32) xbee_SPI_SS3_POLARITY << xbee_SPI_SLAVE_SELECT3))

#if(xbee_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define xbee_SPI_DEFAULT_CTRL \
                    (xbee_GET_CTRL_OVS(xbee_SPI_OVS_FACTOR) | \
                     xbee_GET_CTRL_BYTE_MODE (xbee_SPI_BYTE_MODE_ENABLE) | \
                     xbee_GET_CTRL_EC_AM_MODE(xbee_SPI_WAKE_ENABLE)      | \
                     xbee_CTRL_SPI)

    #define xbee_SPI_DEFAULT_SPI_CTRL \
                    (xbee_GET_SPI_CTRL_CONTINUOUS    (xbee_SPI_TRANSFER_SEPARATION)       | \
                     xbee_GET_SPI_CTRL_SELECT_PRECEDE(xbee_SPI_SUB_MODE &                   \
                                                                  xbee_SPI_MODE_TI_PRECEDES_MASK)     | \
                     xbee_GET_SPI_CTRL_SCLK_MODE     (xbee_SPI_CLOCK_MODE)                | \
                     xbee_GET_SPI_CTRL_LATE_MISO_SAMPLE(xbee_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     xbee_GET_SPI_CTRL_SCLK_CONTINUOUS(xbee_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     xbee_GET_SPI_CTRL_SSEL_POLARITY (xbee_SPI_SS_POLARITY)               | \
                     xbee_GET_SPI_CTRL_SUB_MODE      (xbee_SPI_SUB_MODE)                  | \
                     xbee_GET_SPI_CTRL_MASTER_MODE   (xbee_SPI_MODE))

    /* RX direction */
    #define xbee_SPI_DEFAULT_RX_CTRL \
                    (xbee_GET_RX_CTRL_DATA_WIDTH(xbee_SPI_RX_DATA_BITS_NUM)     | \
                     xbee_GET_RX_CTRL_BIT_ORDER (xbee_SPI_BITS_ORDER)           | \
                     xbee_GET_RX_CTRL_MEDIAN    (xbee_SPI_MEDIAN_FILTER_ENABLE) | \
                     xbee_SPI_RX_CTRL)

    #define xbee_SPI_DEFAULT_RX_FIFO_CTRL \
                    xbee_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(xbee_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define xbee_SPI_DEFAULT_TX_CTRL \
                    (xbee_GET_TX_CTRL_DATA_WIDTH(xbee_SPI_TX_DATA_BITS_NUM) | \
                     xbee_GET_TX_CTRL_BIT_ORDER (xbee_SPI_BITS_ORDER)       | \
                     xbee_SPI_TX_CTRL)

    #define xbee_SPI_DEFAULT_TX_FIFO_CTRL \
                    xbee_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(xbee_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define xbee_SPI_DEFAULT_INTR_SPI_EC_MASK   (xbee_NO_INTR_SOURCES)

    #define xbee_SPI_DEFAULT_INTR_I2C_EC_MASK   (xbee_NO_INTR_SOURCES)
    #define xbee_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (xbee_SPI_INTR_RX_MASK & xbee_INTR_SLAVE_SPI_BUS_ERROR)

    #define xbee_SPI_DEFAULT_INTR_MASTER_MASK \
                    (xbee_SPI_INTR_TX_MASK & xbee_INTR_MASTER_SPI_DONE)

    #define xbee_SPI_DEFAULT_INTR_RX_MASK \
                    (xbee_SPI_INTR_RX_MASK & (uint32) ~xbee_INTR_SLAVE_SPI_BUS_ERROR)

    #define xbee_SPI_DEFAULT_INTR_TX_MASK \
                    (xbee_SPI_INTR_TX_MASK & (uint32) ~xbee_INTR_MASTER_SPI_DONE)

#endif /* (xbee_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define xbee_CTRL_UART      (xbee_CTRL_MODE_UART)
#define xbee_UART_RX_CTRL   (xbee_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define xbee_UART_TX_CTRL   (xbee_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(xbee_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(xbee_UART_MODE_IRDA == xbee_UART_SUB_MODE)

        #define xbee_DEFAULT_CTRL_OVS   ((0u != xbee_UART_IRDA_LOW_POWER) ?              \
                                (xbee_UART_GET_CTRL_OVS_IRDA_LP(xbee_UART_OVS_FACTOR)) : \
                                (xbee_CTRL_OVS_IRDA_OVS16))

    #else

        #define xbee_DEFAULT_CTRL_OVS   xbee_GET_CTRL_OVS(xbee_UART_OVS_FACTOR)

    #endif /* (xbee_UART_MODE_IRDA == xbee_UART_SUB_MODE) */

    #define xbee_UART_DEFAULT_CTRL \
                                (xbee_GET_CTRL_BYTE_MODE  (xbee_UART_BYTE_MODE_ENABLE)  | \
                                 xbee_GET_CTRL_ADDR_ACCEPT(xbee_UART_MP_ACCEPT_ADDRESS) | \
                                 xbee_DEFAULT_CTRL_OVS                                              | \
                                 xbee_CTRL_UART)

    #define xbee_UART_DEFAULT_UART_CTRL \
                                    (xbee_GET_UART_CTRL_MODE(xbee_UART_SUB_MODE))

    /* RX direction */
    #define xbee_UART_DEFAULT_RX_CTRL_PARITY \
                                ((xbee_UART_PARITY_NONE != xbee_UART_PARITY_TYPE) ?      \
                                  (xbee_GET_UART_RX_CTRL_PARITY(xbee_UART_PARITY_TYPE) | \
                                   xbee_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define xbee_UART_DEFAULT_UART_RX_CTRL \
                    (xbee_GET_UART_RX_CTRL_MODE(xbee_UART_STOP_BITS_NUM)                    | \
                     xbee_GET_UART_RX_CTRL_POLARITY(xbee_UART_IRDA_POLARITY)                | \
                     xbee_GET_UART_RX_CTRL_MP_MODE(xbee_UART_MP_MODE_ENABLE)                | \
                     xbee_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(xbee_UART_DROP_ON_PARITY_ERR) | \
                     xbee_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(xbee_UART_DROP_ON_FRAME_ERR)   | \
                     xbee_UART_DEFAULT_RX_CTRL_PARITY)

    #define xbee_UART_DEFAULT_RX_CTRL \
                                (xbee_GET_RX_CTRL_DATA_WIDTH(xbee_UART_DATA_BITS_NUM)        | \
                                 xbee_GET_RX_CTRL_MEDIAN    (xbee_UART_MEDIAN_FILTER_ENABLE) | \
                                 xbee_GET_UART_RX_CTRL_ENABLED(xbee_UART_DIRECTION))

    #define xbee_UART_DEFAULT_RX_FIFO_CTRL \
                                xbee_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(xbee_UART_RX_TRIGGER_LEVEL)

    #define xbee_UART_DEFAULT_RX_MATCH_REG  ((0u != xbee_UART_MP_MODE_ENABLE) ?          \
                                (xbee_GET_RX_MATCH_ADDR(xbee_UART_MP_RX_ADDRESS) | \
                                 xbee_GET_RX_MATCH_MASK(xbee_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define xbee_UART_DEFAULT_TX_CTRL_PARITY (xbee_UART_DEFAULT_RX_CTRL_PARITY)

    #define xbee_UART_DEFAULT_UART_TX_CTRL \
                                (xbee_GET_UART_TX_CTRL_MODE(xbee_UART_STOP_BITS_NUM)       | \
                                 xbee_GET_UART_TX_CTRL_RETRY_NACK(xbee_UART_RETRY_ON_NACK) | \
                                 xbee_UART_DEFAULT_TX_CTRL_PARITY)

    #define xbee_UART_DEFAULT_TX_CTRL \
                                (xbee_GET_TX_CTRL_DATA_WIDTH(xbee_UART_DATA_BITS_NUM) | \
                                 xbee_GET_UART_TX_CTRL_ENABLED(xbee_UART_DIRECTION))

    #define xbee_UART_DEFAULT_TX_FIFO_CTRL \
                                xbee_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(xbee_UART_TX_TRIGGER_LEVEL)

    #define xbee_UART_DEFAULT_FLOW_CTRL \
                        (xbee_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(xbee_UART_RTS_FIFO_LEVEL) | \
                         xbee_GET_UART_FLOW_CTRL_RTS_POLARITY (xbee_UART_RTS_POLARITY)   | \
                         xbee_GET_UART_FLOW_CTRL_CTS_POLARITY (xbee_UART_CTS_POLARITY)   | \
                         xbee_GET_UART_FLOW_CTRL_CTS_ENABLE   (xbee_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define xbee_UART_DEFAULT_INTR_I2C_EC_MASK  (xbee_NO_INTR_SOURCES)
    #define xbee_UART_DEFAULT_INTR_SPI_EC_MASK  (xbee_NO_INTR_SOURCES)
    #define xbee_UART_DEFAULT_INTR_SLAVE_MASK   (xbee_NO_INTR_SOURCES)
    #define xbee_UART_DEFAULT_INTR_MASTER_MASK  (xbee_NO_INTR_SOURCES)
    #define xbee_UART_DEFAULT_INTR_RX_MASK      (xbee_UART_INTR_RX_MASK)
    #define xbee_UART_DEFAULT_INTR_TX_MASK      (xbee_UART_INTR_TX_MASK)

#endif /* (xbee_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define xbee_SPIM_ACTIVE_SS0    (xbee_SPI_SLAVE_SELECT0)
#define xbee_SPIM_ACTIVE_SS1    (xbee_SPI_SLAVE_SELECT1)
#define xbee_SPIM_ACTIVE_SS2    (xbee_SPI_SLAVE_SELECT2)
#define xbee_SPIM_ACTIVE_SS3    (xbee_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_xbee_H */


/* [] END OF FILE */
