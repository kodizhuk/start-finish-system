/***************************************************************************//**
* \file uartDebug_BOOT.h
* \version 3.20
*
* \brief
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2014-2016, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_uartDebug_H)
#define CY_SCB_BOOT_uartDebug_H

#include "uartDebug_PVT.h"

#if (uartDebug_SCB_MODE_I2C_INC)
    #include "uartDebug_I2C.h"
#endif /* (uartDebug_SCB_MODE_I2C_INC) */

#if (uartDebug_SCB_MODE_EZI2C_INC)
    #include "uartDebug_EZI2C.h"
#endif /* (uartDebug_SCB_MODE_EZI2C_INC) */

#if (uartDebug_SCB_MODE_SPI_INC || uartDebug_SCB_MODE_UART_INC)
    #include "uartDebug_SPI_UART.h"
#endif /* (uartDebug_SCB_MODE_SPI_INC || uartDebug_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define uartDebug_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_uartDebug) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (uartDebug_SCB_MODE_I2C_INC)
    #define uartDebug_I2C_BTLDR_COMM_ENABLED     (uartDebug_BTLDR_COMM_ENABLED && \
                                                            (uartDebug_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             uartDebug_I2C_SLAVE_CONST))
#else
     #define uartDebug_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (uartDebug_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (uartDebug_SCB_MODE_EZI2C_INC)
    #define uartDebug_EZI2C_BTLDR_COMM_ENABLED   (uartDebug_BTLDR_COMM_ENABLED && \
                                                         uartDebug_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define uartDebug_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (uartDebug_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (uartDebug_SCB_MODE_SPI_INC)
    #define uartDebug_SPI_BTLDR_COMM_ENABLED     (uartDebug_BTLDR_COMM_ENABLED && \
                                                            (uartDebug_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             uartDebug_SPI_SLAVE_CONST))
#else
        #define uartDebug_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (uartDebug_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (uartDebug_SCB_MODE_UART_INC)
       #define uartDebug_UART_BTLDR_COMM_ENABLED    (uartDebug_BTLDR_COMM_ENABLED && \
                                                            (uartDebug_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (uartDebug_UART_RX_DIRECTION && \
                                                              uartDebug_UART_TX_DIRECTION)))
#else
     #define uartDebug_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (uartDebug_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define uartDebug_BTLDR_COMM_MODE_ENABLED    (uartDebug_I2C_BTLDR_COMM_ENABLED   || \
                                                     uartDebug_SPI_BTLDR_COMM_ENABLED   || \
                                                     uartDebug_EZI2C_BTLDR_COMM_ENABLED || \
                                                     uartDebug_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (uartDebug_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void uartDebug_I2CCyBtldrCommStart(void);
    void uartDebug_I2CCyBtldrCommStop (void);
    void uartDebug_I2CCyBtldrCommReset(void);
    cystatus uartDebug_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus uartDebug_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (uartDebug_SCB_MODE_I2C_CONST_CFG)
        #define uartDebug_CyBtldrCommStart   uartDebug_I2CCyBtldrCommStart
        #define uartDebug_CyBtldrCommStop    uartDebug_I2CCyBtldrCommStop
        #define uartDebug_CyBtldrCommReset   uartDebug_I2CCyBtldrCommReset
        #define uartDebug_CyBtldrCommRead    uartDebug_I2CCyBtldrCommRead
        #define uartDebug_CyBtldrCommWrite   uartDebug_I2CCyBtldrCommWrite
    #endif /* (uartDebug_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (uartDebug_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (uartDebug_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void uartDebug_EzI2CCyBtldrCommStart(void);
    void uartDebug_EzI2CCyBtldrCommStop (void);
    void uartDebug_EzI2CCyBtldrCommReset(void);
    cystatus uartDebug_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus uartDebug_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (uartDebug_SCB_MODE_EZI2C_CONST_CFG)
        #define uartDebug_CyBtldrCommStart   uartDebug_EzI2CCyBtldrCommStart
        #define uartDebug_CyBtldrCommStop    uartDebug_EzI2CCyBtldrCommStop
        #define uartDebug_CyBtldrCommReset   uartDebug_EzI2CCyBtldrCommReset
        #define uartDebug_CyBtldrCommRead    uartDebug_EzI2CCyBtldrCommRead
        #define uartDebug_CyBtldrCommWrite   uartDebug_EzI2CCyBtldrCommWrite
    #endif /* (uartDebug_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (uartDebug_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (uartDebug_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void uartDebug_SpiCyBtldrCommStart(void);
    void uartDebug_SpiCyBtldrCommStop (void);
    void uartDebug_SpiCyBtldrCommReset(void);
    cystatus uartDebug_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus uartDebug_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (uartDebug_SCB_MODE_SPI_CONST_CFG)
        #define uartDebug_CyBtldrCommStart   uartDebug_SpiCyBtldrCommStart
        #define uartDebug_CyBtldrCommStop    uartDebug_SpiCyBtldrCommStop
        #define uartDebug_CyBtldrCommReset   uartDebug_SpiCyBtldrCommReset
        #define uartDebug_CyBtldrCommRead    uartDebug_SpiCyBtldrCommRead
        #define uartDebug_CyBtldrCommWrite   uartDebug_SpiCyBtldrCommWrite
    #endif /* (uartDebug_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (uartDebug_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (uartDebug_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void uartDebug_UartCyBtldrCommStart(void);
    void uartDebug_UartCyBtldrCommStop (void);
    void uartDebug_UartCyBtldrCommReset(void);
    cystatus uartDebug_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus uartDebug_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (uartDebug_SCB_MODE_UART_CONST_CFG)
        #define uartDebug_CyBtldrCommStart   uartDebug_UartCyBtldrCommStart
        #define uartDebug_CyBtldrCommStop    uartDebug_UartCyBtldrCommStop
        #define uartDebug_CyBtldrCommReset   uartDebug_UartCyBtldrCommReset
        #define uartDebug_CyBtldrCommRead    uartDebug_UartCyBtldrCommRead
        #define uartDebug_CyBtldrCommWrite   uartDebug_UartCyBtldrCommWrite
    #endif /* (uartDebug_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (uartDebug_UART_BTLDR_COMM_ENABLED) */

/**
* \addtogroup group_bootloader
* @{
*/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (uartDebug_BTLDR_COMM_ENABLED)
    #if (uartDebug_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void uartDebug_CyBtldrCommStart(void);
        void uartDebug_CyBtldrCommStop (void);
        void uartDebug_CyBtldrCommReset(void);
        cystatus uartDebug_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus uartDebug_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (uartDebug_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_uartDebug)
        #define CyBtldrCommStart    uartDebug_CyBtldrCommStart
        #define CyBtldrCommStop     uartDebug_CyBtldrCommStop
        #define CyBtldrCommReset    uartDebug_CyBtldrCommReset
        #define CyBtldrCommWrite    uartDebug_CyBtldrCommWrite
        #define CyBtldrCommRead     uartDebug_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_uartDebug) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (uartDebug_BTLDR_COMM_ENABLED) */

/** @} group_bootloader */

/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define uartDebug_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define uartDebug_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define uartDebug_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define uartDebug_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef uartDebug_SPI_BYTE_TO_BYTE
    #define uartDebug_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef uartDebug_UART_BYTE_TO_BYTE
    #define uartDebug_UART_BYTE_TO_BYTE  (2086u)
#endif /* uartDebug_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_uartDebug_H) */


/* [] END OF FILE */
