/*******************************************************************************
* File Name: uatr_SPI_UART.h
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

#if !defined(CY_SCB_SPI_UART_uatr_H)
#define CY_SCB_SPI_UART_uatr_H

#include "uatr.h"


/***************************************
*   SPI Initial Parameter Constants
****************************************/

#define uatr_SPI_MODE                   (0u)
#define uatr_SPI_SUB_MODE               (0u)
#define uatr_SPI_CLOCK_MODE             (0u)
#define uatr_SPI_OVS_FACTOR             (16u)
#define uatr_SPI_MEDIAN_FILTER_ENABLE   (0u)
#define uatr_SPI_LATE_MISO_SAMPLE_ENABLE (0u)
#define uatr_SPI_RX_DATA_BITS_NUM       (8u)
#define uatr_SPI_TX_DATA_BITS_NUM       (8u)
#define uatr_SPI_WAKE_ENABLE            (0u)
#define uatr_SPI_BITS_ORDER             (1u)
#define uatr_SPI_TRANSFER_SEPARATION    (1u)
#define uatr_SPI_NUMBER_OF_SS_LINES     (1u)
#define uatr_SPI_RX_BUFFER_SIZE         (8u)
#define uatr_SPI_TX_BUFFER_SIZE         (8u)

#define uatr_SPI_INTERRUPT_MODE         (0u)

#define uatr_SPI_INTR_RX_MASK           (0u)
#define uatr_SPI_INTR_TX_MASK           (0u)

#define uatr_SPI_RX_TRIGGER_LEVEL       (7u)
#define uatr_SPI_TX_TRIGGER_LEVEL       (0u)

#define uatr_SPI_BYTE_MODE_ENABLE       (0u)
#define uatr_SPI_FREE_RUN_SCLK_ENABLE   (0u)
#define uatr_SPI_SS0_POLARITY           (0u)
#define uatr_SPI_SS1_POLARITY           (0u)
#define uatr_SPI_SS2_POLARITY           (0u)
#define uatr_SPI_SS3_POLARITY           (0u)


/***************************************
*   UART Initial Parameter Constants
****************************************/

#define uatr_UART_SUB_MODE              (0u)
#define uatr_UART_DIRECTION             (3u)
#define uatr_UART_DATA_BITS_NUM         (8u)
#define uatr_UART_PARITY_TYPE           (2u)
#define uatr_UART_STOP_BITS_NUM         (2u)
#define uatr_UART_OVS_FACTOR            (12u)
#define uatr_UART_IRDA_LOW_POWER        (0u)
#define uatr_UART_MEDIAN_FILTER_ENABLE  (0u)
#define uatr_UART_RETRY_ON_NACK         (0u)
#define uatr_UART_IRDA_POLARITY         (0u)
#define uatr_UART_DROP_ON_FRAME_ERR     (0u)
#define uatr_UART_DROP_ON_PARITY_ERR    (0u)
#define uatr_UART_WAKE_ENABLE           (0u)
#define uatr_UART_RX_BUFFER_SIZE        (8u)
#define uatr_UART_TX_BUFFER_SIZE        (8u)
#define uatr_UART_MP_MODE_ENABLE        (0u)
#define uatr_UART_MP_ACCEPT_ADDRESS     (0u)
#define uatr_UART_MP_RX_ADDRESS         (2u)
#define uatr_UART_MP_RX_ADDRESS_MASK    (255u)

#define uatr_UART_INTERRUPT_MODE        (0u)

#define uatr_UART_INTR_RX_MASK          (0u)
#define uatr_UART_INTR_TX_MASK          (0u)

#define uatr_UART_RX_TRIGGER_LEVEL      (7u)
#define uatr_UART_TX_TRIGGER_LEVEL      (0u)

#define uatr_UART_BYTE_MODE_ENABLE      (0u)
#define uatr_UART_CTS_ENABLE            (0u)
#define uatr_UART_CTS_POLARITY          (0u)
#define uatr_UART_RTS_ENABLE            (0u)
#define uatr_UART_RTS_POLARITY          (0u)
#define uatr_UART_RTS_FIFO_LEVEL        (4u)

/* SPI mode enum */
#define uatr_SPI_SLAVE  (0u)
#define uatr_SPI_MASTER (1u)

/* UART direction enum */
#define uatr_UART_RX    (1u)
#define uatr_UART_TX    (2u)
#define uatr_UART_TX_RX (3u)


/***************************************
*   Conditional Compilation Parameters
****************************************/

#if(uatr_SCB_MODE_UNCONFIG_CONST_CFG)

    /* Mode */
    #define uatr_SPI_SLAVE_CONST        (1u)
    #define uatr_SPI_MASTER_CONST       (1u)

    /* Direction */
    #define uatr_RX_DIRECTION           (1u)
    #define uatr_TX_DIRECTION           (1u)
    #define uatr_UART_RX_DIRECTION      (1u)
    #define uatr_UART_TX_DIRECTION      (1u)

    /* Only external RX and TX buffer for Uncofigured mode */
    #define uatr_INTERNAL_RX_SW_BUFFER   (0u)
    #define uatr_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define uatr_INTERNAL_RX_BUFFER_SIZE    (uatr_rxBufferSize + 1u)
    #define uatr_RX_BUFFER_SIZE             (uatr_rxBufferSize)
    #define uatr_TX_BUFFER_SIZE             (uatr_txBufferSize)

    /* Return true if buffer is provided */
    #define uatr_CHECK_RX_SW_BUFFER (NULL != uatr_rxBuffer)
    #define uatr_CHECK_TX_SW_BUFFER (NULL != uatr_txBuffer)

    /* Always provide global variables to support RX and TX buffers */
    #define uatr_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define uatr_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define uatr_SPI_WAKE_ENABLE_CONST  (1u)
    #define uatr_CHECK_SPI_WAKE_ENABLE  (0u != uatr_scbEnableWake)
    #define uatr_UART_WAKE_ENABLE_CONST (1u)

    /* SPI/UART: TX or RX FIFO size */
    #if (uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
        #define uatr_SPI_UART_FIFO_SIZE             (uatr_FIFO_SIZE)
        #define uatr_CHECK_UART_RTS_CONTROL_FLOW    (0u)
    #else
        #define uatr_SPI_UART_FIFO_SIZE (uatr_GET_FIFO_SIZE(uatr_CTRL_REG & \
                                                                                    uatr_CTRL_BYTE_MODE))

        #define uatr_CHECK_UART_RTS_CONTROL_FLOW \
                    ((uatr_SCB_MODE_UART_RUNTM_CFG) && \
                     (0u != uatr_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(uatr_UART_FLOW_CTRL_REG)))
    #endif /* (uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */

#else

    /* Internal RX and TX buffer: for SPI or UART */
    #if (uatr_SCB_MODE_SPI_CONST_CFG)

        /* SPI Direction */
        #define uatr_SPI_RX_DIRECTION (1u)
        #define uatr_SPI_TX_DIRECTION (1u)

        /* Get FIFO size */
        #if (uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
            #define uatr_SPI_UART_FIFO_SIZE    (uatr_FIFO_SIZE)
        #else
            #define uatr_SPI_UART_FIFO_SIZE \
                                           uatr_GET_FIFO_SIZE(uatr_SPI_BYTE_MODE_ENABLE)

        #endif /* (uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */

        /* SPI internal RX and TX buffers */
        #define uatr_INTERNAL_SPI_RX_SW_BUFFER  (uatr_SPI_RX_BUFFER_SIZE > \
                                                                uatr_SPI_UART_FIFO_SIZE)
        #define uatr_INTERNAL_SPI_TX_SW_BUFFER  (uatr_SPI_TX_BUFFER_SIZE > \
                                                                uatr_SPI_UART_FIFO_SIZE)

        /* Internal SPI RX and TX buffer */
        #define uatr_INTERNAL_RX_SW_BUFFER  (uatr_INTERNAL_SPI_RX_SW_BUFFER)
        #define uatr_INTERNAL_TX_SW_BUFFER  (uatr_INTERNAL_SPI_TX_SW_BUFFER)

        /* Internal SPI RX and TX buffer size */
        #define uatr_INTERNAL_RX_BUFFER_SIZE    (uatr_SPI_RX_BUFFER_SIZE + 1u)
        #define uatr_RX_BUFFER_SIZE             (uatr_SPI_RX_BUFFER_SIZE)
        #define uatr_TX_BUFFER_SIZE             (uatr_SPI_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define uatr_SPI_WAKE_ENABLE_CONST  (0u != uatr_SPI_WAKE_ENABLE)
        #define uatr_UART_WAKE_ENABLE_CONST (0u)

    #else

        /* UART Direction */
        #define uatr_UART_RX_DIRECTION (0u != (uatr_UART_DIRECTION & uatr_UART_RX))
        #define uatr_UART_TX_DIRECTION (0u != (uatr_UART_DIRECTION & uatr_UART_TX))

        /* Get FIFO size */
        #if (uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
            #define uatr_SPI_UART_FIFO_SIZE    (uatr_FIFO_SIZE)
        #else
            #define uatr_SPI_UART_FIFO_SIZE \
                                           uatr_GET_FIFO_SIZE(uatr_UART_BYTE_MODE_ENABLE)
        #endif /* (uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */

        /* UART internal RX and TX buffers */
        #define uatr_INTERNAL_UART_RX_SW_BUFFER  (uatr_UART_RX_BUFFER_SIZE > \
                                                                uatr_SPI_UART_FIFO_SIZE)
        #define uatr_INTERNAL_UART_TX_SW_BUFFER  (uatr_UART_TX_BUFFER_SIZE > \
                                                                    uatr_SPI_UART_FIFO_SIZE)

        /* Internal UART RX and TX buffer */
        #define uatr_INTERNAL_RX_SW_BUFFER  (uatr_INTERNAL_UART_RX_SW_BUFFER)
        #define uatr_INTERNAL_TX_SW_BUFFER  (uatr_INTERNAL_UART_TX_SW_BUFFER)

        /* Internal UART RX and TX buffer size */
        #define uatr_INTERNAL_RX_BUFFER_SIZE    (uatr_UART_RX_BUFFER_SIZE + 1u)
        #define uatr_RX_BUFFER_SIZE             (uatr_UART_RX_BUFFER_SIZE)
        #define uatr_TX_BUFFER_SIZE             (uatr_UART_TX_BUFFER_SIZE)

        /* Get wakeup enable option */
        #define uatr_SPI_WAKE_ENABLE_CONST  (0u)
        #define uatr_UART_WAKE_ENABLE_CONST (0u != uatr_UART_WAKE_ENABLE)

    #endif /* (uatr_SCB_MODE_SPI_CONST_CFG) */

    /* Mode */
    #define uatr_SPI_SLAVE_CONST    (uatr_SPI_MODE == uatr_SPI_SLAVE)
    #define uatr_SPI_MASTER_CONST   (uatr_SPI_MODE == uatr_SPI_MASTER)

    /* Direction */
    #define uatr_RX_DIRECTION ((uatr_SCB_MODE_SPI_CONST_CFG) ? \
                                            (uatr_SPI_RX_DIRECTION) : (uatr_UART_RX_DIRECTION))

    #define uatr_TX_DIRECTION ((uatr_SCB_MODE_SPI_CONST_CFG) ? \
                                            (uatr_SPI_TX_DIRECTION) : (uatr_UART_TX_DIRECTION))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define uatr_CHECK_RX_SW_BUFFER (uatr_INTERNAL_RX_SW_BUFFER)
    #define uatr_CHECK_TX_SW_BUFFER (uatr_INTERNAL_TX_SW_BUFFER)

    /* Provide global variables to support RX and TX buffers */
    #define uatr_INTERNAL_RX_SW_BUFFER_CONST    (uatr_INTERNAL_RX_SW_BUFFER)
    #define uatr_INTERNAL_TX_SW_BUFFER_CONST    (uatr_INTERNAL_TX_SW_BUFFER)

    /* SPI wakeup */
    #define uatr_CHECK_SPI_WAKE_ENABLE  (uatr_SPI_WAKE_ENABLE_CONST)

    /* UART flow control: not applicable for CY_SCBIP_V0 || CY_SCBIP_V1 */
    #define uatr_CHECK_UART_RTS_CONTROL_FLOW    (uatr_SCB_MODE_UART_CONST_CFG && \
                                                             uatr_UART_RTS_ENABLE)

#endif /* End (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*       Type Definitions
***************************************/

/* uatr_SPI_INIT_STRUCT */
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
} uatr_SPI_INIT_STRUCT;

/* uatr_UART_INIT_STRUCT */
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
} uatr_UART_INIT_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

/* SPI specific functions */
#if(uatr_SCB_MODE_UNCONFIG_CONST_CFG)
    void uatr_SpiInit(const uatr_SPI_INIT_STRUCT *config);
#endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(uatr_SCB_MODE_SPI_INC)
    #define uatr_SpiIsBusBusy() ((uint32) (0u != (uatr_SPI_STATUS_REG & \
                                                              uatr_SPI_STATUS_BUS_BUSY)))

    #if (uatr_SPI_MASTER_CONST)
        void uatr_SpiSetActiveSlaveSelect(uint32 slaveSelect);
    #endif /*(uatr_SPI_MASTER_CONST) */

    #if !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
        void uatr_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity);
    #endif /* !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */
#endif /* (uatr_SCB_MODE_SPI_INC) */

/* UART specific functions */
#if(uatr_SCB_MODE_UNCONFIG_CONST_CFG)
    void uatr_UartInit(const uatr_UART_INIT_STRUCT *config);
#endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */

#if(uatr_SCB_MODE_UART_INC)
    void uatr_UartSetRxAddress(uint32 address);
    void uatr_UartSetRxAddressMask(uint32 addressMask);

    /* UART RX direction APIs */
    #if(uatr_UART_RX_DIRECTION)
        uint32 uatr_UartGetChar(void);
        uint32 uatr_UartGetByte(void);

        #if !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void uatr_UartSetRtsPolarity(uint32 polarity);
            void uatr_UartSetRtsFifoLevel(uint32 level);
        #endif /* !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */
    #endif /* (uatr_UART_RX_DIRECTION) */

    /* UART TX direction APIs */
    #if(uatr_UART_TX_DIRECTION)
        #define uatr_UartPutChar(ch)    uatr_SpiUartWriteTxData((uint32)(ch))
        void uatr_UartPutString(const char8 string[]);
        void uatr_UartPutCRLF(uint32 txDataByte);

        #if !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1)
            /* UART APIs for Flow Control */
            void uatr_UartEnableCts(void);
            void uatr_UartDisableCts(void);
            void uatr_UartSetCtsPolarity(uint32 polarity);
        #endif /* !(uatr_CY_SCBIP_V0 || uatr_CY_SCBIP_V1) */
    #endif /* (uatr_UART_TX_DIRECTION) */
#endif /* (uatr_SCB_MODE_UART_INC) */

/* Common APIs RX direction */
#if(uatr_RX_DIRECTION)
    uint32 uatr_SpiUartReadRxData(void);
    uint32 uatr_SpiUartGetRxBufferSize(void);
    void   uatr_SpiUartClearRxBuffer(void);
#endif /* (uatr_RX_DIRECTION) */

/* Common APIs TX direction */
#if(uatr_TX_DIRECTION)
    void   uatr_SpiUartWriteTxData(uint32 txData);
    void   uatr_SpiUartPutArray(const uint8 wrBuf[], uint32 count);
    uint32 uatr_SpiUartGetTxBufferSize(void);
    void   uatr_SpiUartClearTxBuffer(void);
#endif /* (uatr_TX_DIRECTION) */

CY_ISR_PROTO(uatr_SPI_UART_ISR);

#if(uatr_UART_RX_WAKEUP_IRQ)
    CY_ISR_PROTO(uatr_UART_WAKEUP_ISR);
#endif /* (uatr_UART_RX_WAKEUP_IRQ) */


/***************************************
*     Buffer Access Macro Definitions
***************************************/

#if(uatr_SCB_MODE_UNCONFIG_CONST_CFG)
    /* RX direction */
    void   uatr_PutWordInRxBuffer  (uint32 idx, uint32 rxDataByte);
    uint32 uatr_GetWordFromRxBuffer(uint32 idx);

    /* TX direction */
    void   uatr_PutWordInTxBuffer  (uint32 idx, uint32 txDataByte);
    uint32 uatr_GetWordFromTxBuffer(uint32 idx);

#else
    /* RX direction */
    #if(uatr_INTERNAL_RX_SW_BUFFER_CONST)
        #define uatr_PutWordInRxBuffer(idx, rxDataByte) \
                do{                                                 \
                    uatr_rxBufferInternal[(idx)] = ((uint8) (rxDataByte)); \
                }while(0)

        #define uatr_GetWordFromRxBuffer(idx) uatr_rxBufferInternal[(idx)]

    #endif /* (uatr_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(uatr_INTERNAL_TX_SW_BUFFER_CONST)
        #define uatr_PutWordInTxBuffer(idx, txDataByte) \
                    do{                                             \
                        uatr_txBufferInternal[(idx)] = ((uint8) (txDataByte)); \
                    }while(0)

        #define uatr_GetWordFromTxBuffer(idx) uatr_txBufferInternal[(idx)]

    #endif /* (uatr_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (uatr_TX_SW_BUFFER_ENABLE) */


/***************************************
*         SPI API Constants
***************************************/

/* SPI sub mode enum */
#define uatr_SPI_MODE_MOTOROLA      (0x00u)
#define uatr_SPI_MODE_TI_COINCIDES  (0x01u)
#define uatr_SPI_MODE_TI_PRECEDES   (0x11u)
#define uatr_SPI_MODE_NATIONAL      (0x02u)
#define uatr_SPI_MODE_MASK          (0x03u)
#define uatr_SPI_MODE_TI_PRECEDES_MASK  (0x10u)
#define uatr_SPI_MODE_NS_MICROWIRE  (uatr_SPI_MODE_NATIONAL)

/* SPI phase and polarity mode enum */
#define uatr_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define uatr_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define uatr_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define uatr_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define uatr_BITS_ORDER_LSB_FIRST   (0u)
#define uatr_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define uatr_SPI_TRANSFER_SEPARATED     (0u)
#define uatr_SPI_TRANSFER_CONTINUOUS    (1u)

/* SPI slave select constants */
#define uatr_SPI_SLAVE_SELECT0    (uatr_SCB__SS0_POSISTION)
#define uatr_SPI_SLAVE_SELECT1    (uatr_SCB__SS1_POSISTION)
#define uatr_SPI_SLAVE_SELECT2    (uatr_SCB__SS2_POSISTION)
#define uatr_SPI_SLAVE_SELECT3    (uatr_SCB__SS3_POSISTION)

/* SPI slave select polarity settings */
#define uatr_SPI_SS_ACTIVE_LOW  (0u)
#define uatr_SPI_SS_ACTIVE_HIGH (1u)


/***************************************
*         UART API Constants
***************************************/

/* UART sub-modes enum */
#define uatr_UART_MODE_STD          (0u)
#define uatr_UART_MODE_SMARTCARD    (1u)
#define uatr_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define uatr_UART_RX    (1u)
#define uatr_UART_TX    (2u)
#define uatr_UART_TX_RX (3u)

/* UART parity enum */
#define uatr_UART_PARITY_EVEN   (0u)
#define uatr_UART_PARITY_ODD    (1u)
#define uatr_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define uatr_UART_STOP_BITS_1   (2u)
#define uatr_UART_STOP_BITS_1_5 (3u)
#define uatr_UART_STOP_BITS_2   (4u)

/* UART IrDA low power OVS enum */
#define uatr_UART_IRDA_LP_OVS16     (16u)
#define uatr_UART_IRDA_LP_OVS32     (32u)
#define uatr_UART_IRDA_LP_OVS48     (48u)
#define uatr_UART_IRDA_LP_OVS96     (96u)
#define uatr_UART_IRDA_LP_OVS192    (192u)
#define uatr_UART_IRDA_LP_OVS768    (768u)
#define uatr_UART_IRDA_LP_OVS1536   (1536u)

/* Uart MP: mark (address) and space (data) bit definitions */
#define uatr_UART_MP_MARK       (0x100u)
#define uatr_UART_MP_SPACE      (0x000u)

/* UART CTS/RTS polarity settings */
#define uatr_UART_CTS_ACTIVE_LOW    (0u)
#define uatr_UART_CTS_ACTIVE_HIGH   (1u)
#define uatr_UART_RTS_ACTIVE_LOW    (0u)
#define uatr_UART_RTS_ACTIVE_HIGH   (1u)

/* Sources of RX errors */
#define uatr_INTR_RX_ERR        (uatr_INTR_RX_OVERFLOW    | \
                                             uatr_INTR_RX_UNDERFLOW   | \
                                             uatr_INTR_RX_FRAME_ERROR | \
                                             uatr_INTR_RX_PARITY_ERROR)

/* Shifted INTR_RX_ERR defines ONLY for uatr_UartGetByte() */
#define uatr_UART_RX_OVERFLOW       (uatr_INTR_RX_OVERFLOW << 8u)
#define uatr_UART_RX_UNDERFLOW      (uatr_INTR_RX_UNDERFLOW << 8u)
#define uatr_UART_RX_FRAME_ERROR    (uatr_INTR_RX_FRAME_ERROR << 8u)
#define uatr_UART_RX_PARITY_ERROR   (uatr_INTR_RX_PARITY_ERROR << 8u)
#define uatr_UART_RX_ERROR_MASK     (uatr_UART_RX_OVERFLOW    | \
                                                 uatr_UART_RX_UNDERFLOW   | \
                                                 uatr_UART_RX_FRAME_ERROR | \
                                                 uatr_UART_RX_PARITY_ERROR)


/***************************************
*     Vars with External Linkage
***************************************/

#if(uatr_SCB_MODE_UNCONFIG_CONST_CFG)
    extern const uatr_SPI_INIT_STRUCT  uatr_configSpi;
    extern const uatr_UART_INIT_STRUCT uatr_configUart;
#endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */


/***************************************
*    Specific SPI Macro Definitions
***************************************/

#define uatr_GET_SPI_INTR_SLAVE_MASK(sourceMask)  ((sourceMask) & uatr_INTR_SLAVE_SPI_BUS_ERROR)
#define uatr_GET_SPI_INTR_MASTER_MASK(sourceMask) ((sourceMask) & uatr_INTR_MASTER_SPI_DONE)
#define uatr_GET_SPI_INTR_RX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~uatr_INTR_SLAVE_SPI_BUS_ERROR)

#define uatr_GET_SPI_INTR_TX_MASK(sourceMask) \
                                             ((sourceMask) & (uint32) ~uatr_INTR_MASTER_SPI_DONE)


/***************************************
*    Specific UART Macro Definitions
***************************************/

#define uatr_UART_GET_CTRL_OVS_IRDA_LP(oversample) \
        ((uatr_UART_IRDA_LP_OVS16   == (oversample)) ? uatr_CTRL_OVS_IRDA_LP_OVS16 : \
         ((uatr_UART_IRDA_LP_OVS32   == (oversample)) ? uatr_CTRL_OVS_IRDA_LP_OVS32 : \
          ((uatr_UART_IRDA_LP_OVS48   == (oversample)) ? uatr_CTRL_OVS_IRDA_LP_OVS48 : \
           ((uatr_UART_IRDA_LP_OVS96   == (oversample)) ? uatr_CTRL_OVS_IRDA_LP_OVS96 : \
            ((uatr_UART_IRDA_LP_OVS192  == (oversample)) ? uatr_CTRL_OVS_IRDA_LP_OVS192 : \
             ((uatr_UART_IRDA_LP_OVS768  == (oversample)) ? uatr_CTRL_OVS_IRDA_LP_OVS768 : \
              ((uatr_UART_IRDA_LP_OVS1536 == (oversample)) ? uatr_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                          uatr_CTRL_OVS_IRDA_LP_OVS16)))))))

#define uatr_GET_UART_RX_CTRL_ENABLED(direction) ((0u != (uatr_UART_RX & (direction))) ? \
                                                                     (uatr_RX_CTRL_ENABLED) : (0u))

#define uatr_GET_UART_TX_CTRL_ENABLED(direction) ((0u != (uatr_UART_TX & (direction))) ? \
                                                                     (uatr_TX_CTRL_ENABLED) : (0u))


/***************************************
*        SPI Register Settings
***************************************/

#define uatr_CTRL_SPI      (uatr_CTRL_MODE_SPI)
#define uatr_SPI_RX_CTRL   (uatr_RX_CTRL_ENABLED)
#define uatr_SPI_TX_CTRL   (uatr_TX_CTRL_ENABLED)


/***************************************
*       SPI Init Register Settings
***************************************/

#define uatr_SPI_SS_POLARITY \
             (((uint32) uatr_SPI_SS0_POLARITY << uatr_SPI_SLAVE_SELECT0) | \
              ((uint32) uatr_SPI_SS1_POLARITY << uatr_SPI_SLAVE_SELECT1) | \
              ((uint32) uatr_SPI_SS2_POLARITY << uatr_SPI_SLAVE_SELECT2) | \
              ((uint32) uatr_SPI_SS3_POLARITY << uatr_SPI_SLAVE_SELECT3))

#if(uatr_SCB_MODE_SPI_CONST_CFG)

    /* SPI Configuration */
    #define uatr_SPI_DEFAULT_CTRL \
                    (uatr_GET_CTRL_OVS(uatr_SPI_OVS_FACTOR) | \
                     uatr_GET_CTRL_BYTE_MODE (uatr_SPI_BYTE_MODE_ENABLE) | \
                     uatr_GET_CTRL_EC_AM_MODE(uatr_SPI_WAKE_ENABLE)      | \
                     uatr_CTRL_SPI)

    #define uatr_SPI_DEFAULT_SPI_CTRL \
                    (uatr_GET_SPI_CTRL_CONTINUOUS    (uatr_SPI_TRANSFER_SEPARATION)       | \
                     uatr_GET_SPI_CTRL_SELECT_PRECEDE(uatr_SPI_SUB_MODE &                   \
                                                                  uatr_SPI_MODE_TI_PRECEDES_MASK)     | \
                     uatr_GET_SPI_CTRL_SCLK_MODE     (uatr_SPI_CLOCK_MODE)                | \
                     uatr_GET_SPI_CTRL_LATE_MISO_SAMPLE(uatr_SPI_LATE_MISO_SAMPLE_ENABLE) | \
                     uatr_GET_SPI_CTRL_SCLK_CONTINUOUS(uatr_SPI_FREE_RUN_SCLK_ENABLE)     | \
                     uatr_GET_SPI_CTRL_SSEL_POLARITY (uatr_SPI_SS_POLARITY)               | \
                     uatr_GET_SPI_CTRL_SUB_MODE      (uatr_SPI_SUB_MODE)                  | \
                     uatr_GET_SPI_CTRL_MASTER_MODE   (uatr_SPI_MODE))

    /* RX direction */
    #define uatr_SPI_DEFAULT_RX_CTRL \
                    (uatr_GET_RX_CTRL_DATA_WIDTH(uatr_SPI_RX_DATA_BITS_NUM)     | \
                     uatr_GET_RX_CTRL_BIT_ORDER (uatr_SPI_BITS_ORDER)           | \
                     uatr_GET_RX_CTRL_MEDIAN    (uatr_SPI_MEDIAN_FILTER_ENABLE) | \
                     uatr_SPI_RX_CTRL)

    #define uatr_SPI_DEFAULT_RX_FIFO_CTRL \
                    uatr_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(uatr_SPI_RX_TRIGGER_LEVEL)

    /* TX direction */
    #define uatr_SPI_DEFAULT_TX_CTRL \
                    (uatr_GET_TX_CTRL_DATA_WIDTH(uatr_SPI_TX_DATA_BITS_NUM) | \
                     uatr_GET_TX_CTRL_BIT_ORDER (uatr_SPI_BITS_ORDER)       | \
                     uatr_SPI_TX_CTRL)

    #define uatr_SPI_DEFAULT_TX_FIFO_CTRL \
                    uatr_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(uatr_SPI_TX_TRIGGER_LEVEL)

    /* Interrupt sources */
    #define uatr_SPI_DEFAULT_INTR_SPI_EC_MASK   (uatr_NO_INTR_SOURCES)

    #define uatr_SPI_DEFAULT_INTR_I2C_EC_MASK   (uatr_NO_INTR_SOURCES)
    #define uatr_SPI_DEFAULT_INTR_SLAVE_MASK \
                    (uatr_SPI_INTR_RX_MASK & uatr_INTR_SLAVE_SPI_BUS_ERROR)

    #define uatr_SPI_DEFAULT_INTR_MASTER_MASK \
                    (uatr_SPI_INTR_TX_MASK & uatr_INTR_MASTER_SPI_DONE)

    #define uatr_SPI_DEFAULT_INTR_RX_MASK \
                    (uatr_SPI_INTR_RX_MASK & (uint32) ~uatr_INTR_SLAVE_SPI_BUS_ERROR)

    #define uatr_SPI_DEFAULT_INTR_TX_MASK \
                    (uatr_SPI_INTR_TX_MASK & (uint32) ~uatr_INTR_MASTER_SPI_DONE)

#endif /* (uatr_SCB_MODE_SPI_CONST_CFG) */


/***************************************
*        UART Register Settings
***************************************/

#define uatr_CTRL_UART      (uatr_CTRL_MODE_UART)
#define uatr_UART_RX_CTRL   (uatr_RX_CTRL_LSB_FIRST) /* LSB for UART goes first */
#define uatr_UART_TX_CTRL   (uatr_TX_CTRL_LSB_FIRST) /* LSB for UART goes first */


/***************************************
*      UART Init Register Settings
***************************************/

#if(uatr_SCB_MODE_UART_CONST_CFG)

    /* UART configuration */
    #if(uatr_UART_MODE_IRDA == uatr_UART_SUB_MODE)

        #define uatr_DEFAULT_CTRL_OVS   ((0u != uatr_UART_IRDA_LOW_POWER) ?              \
                                (uatr_UART_GET_CTRL_OVS_IRDA_LP(uatr_UART_OVS_FACTOR)) : \
                                (uatr_CTRL_OVS_IRDA_OVS16))

    #else

        #define uatr_DEFAULT_CTRL_OVS   uatr_GET_CTRL_OVS(uatr_UART_OVS_FACTOR)

    #endif /* (uatr_UART_MODE_IRDA == uatr_UART_SUB_MODE) */

    #define uatr_UART_DEFAULT_CTRL \
                                (uatr_GET_CTRL_BYTE_MODE  (uatr_UART_BYTE_MODE_ENABLE)  | \
                                 uatr_GET_CTRL_ADDR_ACCEPT(uatr_UART_MP_ACCEPT_ADDRESS) | \
                                 uatr_DEFAULT_CTRL_OVS                                              | \
                                 uatr_CTRL_UART)

    #define uatr_UART_DEFAULT_UART_CTRL \
                                    (uatr_GET_UART_CTRL_MODE(uatr_UART_SUB_MODE))

    /* RX direction */
    #define uatr_UART_DEFAULT_RX_CTRL_PARITY \
                                ((uatr_UART_PARITY_NONE != uatr_UART_PARITY_TYPE) ?      \
                                  (uatr_GET_UART_RX_CTRL_PARITY(uatr_UART_PARITY_TYPE) | \
                                   uatr_UART_RX_CTRL_PARITY_ENABLED) : (0u))

    #define uatr_UART_DEFAULT_UART_RX_CTRL \
                    (uatr_GET_UART_RX_CTRL_MODE(uatr_UART_STOP_BITS_NUM)                    | \
                     uatr_GET_UART_RX_CTRL_POLARITY(uatr_UART_IRDA_POLARITY)                | \
                     uatr_GET_UART_RX_CTRL_MP_MODE(uatr_UART_MP_MODE_ENABLE)                | \
                     uatr_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(uatr_UART_DROP_ON_PARITY_ERR) | \
                     uatr_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(uatr_UART_DROP_ON_FRAME_ERR)   | \
                     uatr_UART_DEFAULT_RX_CTRL_PARITY)

    #define uatr_UART_DEFAULT_RX_CTRL \
                                (uatr_GET_RX_CTRL_DATA_WIDTH(uatr_UART_DATA_BITS_NUM)        | \
                                 uatr_GET_RX_CTRL_MEDIAN    (uatr_UART_MEDIAN_FILTER_ENABLE) | \
                                 uatr_GET_UART_RX_CTRL_ENABLED(uatr_UART_DIRECTION))

    #define uatr_UART_DEFAULT_RX_FIFO_CTRL \
                                uatr_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(uatr_UART_RX_TRIGGER_LEVEL)

    #define uatr_UART_DEFAULT_RX_MATCH_REG  ((0u != uatr_UART_MP_MODE_ENABLE) ?          \
                                (uatr_GET_RX_MATCH_ADDR(uatr_UART_MP_RX_ADDRESS) | \
                                 uatr_GET_RX_MATCH_MASK(uatr_UART_MP_RX_ADDRESS_MASK)) : (0u))

    /* TX direction */
    #define uatr_UART_DEFAULT_TX_CTRL_PARITY (uatr_UART_DEFAULT_RX_CTRL_PARITY)

    #define uatr_UART_DEFAULT_UART_TX_CTRL \
                                (uatr_GET_UART_TX_CTRL_MODE(uatr_UART_STOP_BITS_NUM)       | \
                                 uatr_GET_UART_TX_CTRL_RETRY_NACK(uatr_UART_RETRY_ON_NACK) | \
                                 uatr_UART_DEFAULT_TX_CTRL_PARITY)

    #define uatr_UART_DEFAULT_TX_CTRL \
                                (uatr_GET_TX_CTRL_DATA_WIDTH(uatr_UART_DATA_BITS_NUM) | \
                                 uatr_GET_UART_TX_CTRL_ENABLED(uatr_UART_DIRECTION))

    #define uatr_UART_DEFAULT_TX_FIFO_CTRL \
                                uatr_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(uatr_UART_TX_TRIGGER_LEVEL)

    #define uatr_UART_DEFAULT_FLOW_CTRL \
                        (uatr_GET_UART_FLOW_CTRL_TRIGGER_LEVEL(uatr_UART_RTS_FIFO_LEVEL) | \
                         uatr_GET_UART_FLOW_CTRL_RTS_POLARITY (uatr_UART_RTS_POLARITY)   | \
                         uatr_GET_UART_FLOW_CTRL_CTS_POLARITY (uatr_UART_CTS_POLARITY)   | \
                         uatr_GET_UART_FLOW_CTRL_CTS_ENABLE   (uatr_UART_CTS_ENABLE))

    /* Interrupt sources */
    #define uatr_UART_DEFAULT_INTR_I2C_EC_MASK  (uatr_NO_INTR_SOURCES)
    #define uatr_UART_DEFAULT_INTR_SPI_EC_MASK  (uatr_NO_INTR_SOURCES)
    #define uatr_UART_DEFAULT_INTR_SLAVE_MASK   (uatr_NO_INTR_SOURCES)
    #define uatr_UART_DEFAULT_INTR_MASTER_MASK  (uatr_NO_INTR_SOURCES)
    #define uatr_UART_DEFAULT_INTR_RX_MASK      (uatr_UART_INTR_RX_MASK)
    #define uatr_UART_DEFAULT_INTR_TX_MASK      (uatr_UART_INTR_TX_MASK)

#endif /* (uatr_SCB_MODE_UART_CONST_CFG) */


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

#define uatr_SPIM_ACTIVE_SS0    (uatr_SPI_SLAVE_SELECT0)
#define uatr_SPIM_ACTIVE_SS1    (uatr_SPI_SLAVE_SELECT1)
#define uatr_SPIM_ACTIVE_SS2    (uatr_SPI_SLAVE_SELECT2)
#define uatr_SPIM_ACTIVE_SS3    (uatr_SPI_SLAVE_SELECT3)

#endif /* CY_SCB_SPI_UART_uatr_H */


/* [] END OF FILE */
