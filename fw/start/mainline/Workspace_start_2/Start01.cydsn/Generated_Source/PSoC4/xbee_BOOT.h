/*******************************************************************************
* File Name: xbee_BOOT.h
* Version 3.10
*
* Description:
*  This file provides constants and parameter values of the bootloader
*  communication APIs for the SCB Component.
*
* Note:
*
********************************************************************************
* Copyright 2014-2015, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_BOOT_xbee_H)
#define CY_SCB_BOOT_xbee_H

#include "xbee_PVT.h"

#if (xbee_SCB_MODE_I2C_INC)
    #include "xbee_I2C.h"
#endif /* (xbee_SCB_MODE_I2C_INC) */

#if (xbee_SCB_MODE_EZI2C_INC)
    #include "xbee_EZI2C.h"
#endif /* (xbee_SCB_MODE_EZI2C_INC) */

#if (xbee_SCB_MODE_SPI_INC || xbee_SCB_MODE_UART_INC)
    #include "xbee_SPI_UART.h"
#endif /* (xbee_SCB_MODE_SPI_INC || xbee_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define xbee_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_xbee) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (xbee_SCB_MODE_I2C_INC)
    #define xbee_I2C_BTLDR_COMM_ENABLED     (xbee_BTLDR_COMM_ENABLED && \
                                                            (xbee_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             xbee_I2C_SLAVE_CONST))
#else
     #define xbee_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (xbee_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (xbee_SCB_MODE_EZI2C_INC)
    #define xbee_EZI2C_BTLDR_COMM_ENABLED   (xbee_BTLDR_COMM_ENABLED && \
                                                         xbee_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define xbee_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (xbee_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (xbee_SCB_MODE_SPI_INC)
    #define xbee_SPI_BTLDR_COMM_ENABLED     (xbee_BTLDR_COMM_ENABLED && \
                                                            (xbee_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             xbee_SPI_SLAVE_CONST))
#else
        #define xbee_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (xbee_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (xbee_SCB_MODE_UART_INC)
       #define xbee_UART_BTLDR_COMM_ENABLED    (xbee_BTLDR_COMM_ENABLED && \
                                                            (xbee_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (xbee_UART_RX_DIRECTION && \
                                                              xbee_UART_TX_DIRECTION)))
#else
     #define xbee_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (xbee_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define xbee_BTLDR_COMM_MODE_ENABLED    (xbee_I2C_BTLDR_COMM_ENABLED   || \
                                                     xbee_SPI_BTLDR_COMM_ENABLED   || \
                                                     xbee_EZI2C_BTLDR_COMM_ENABLED || \
                                                     xbee_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (xbee_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void xbee_I2CCyBtldrCommStart(void);
    void xbee_I2CCyBtldrCommStop (void);
    void xbee_I2CCyBtldrCommReset(void);
    cystatus xbee_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus xbee_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (xbee_SCB_MODE_I2C_CONST_CFG)
        #define xbee_CyBtldrCommStart   xbee_I2CCyBtldrCommStart
        #define xbee_CyBtldrCommStop    xbee_I2CCyBtldrCommStop
        #define xbee_CyBtldrCommReset   xbee_I2CCyBtldrCommReset
        #define xbee_CyBtldrCommRead    xbee_I2CCyBtldrCommRead
        #define xbee_CyBtldrCommWrite   xbee_I2CCyBtldrCommWrite
    #endif /* (xbee_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (xbee_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (xbee_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void xbee_EzI2CCyBtldrCommStart(void);
    void xbee_EzI2CCyBtldrCommStop (void);
    void xbee_EzI2CCyBtldrCommReset(void);
    cystatus xbee_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus xbee_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (xbee_SCB_MODE_EZI2C_CONST_CFG)
        #define xbee_CyBtldrCommStart   xbee_EzI2CCyBtldrCommStart
        #define xbee_CyBtldrCommStop    xbee_EzI2CCyBtldrCommStop
        #define xbee_CyBtldrCommReset   xbee_EzI2CCyBtldrCommReset
        #define xbee_CyBtldrCommRead    xbee_EzI2CCyBtldrCommRead
        #define xbee_CyBtldrCommWrite   xbee_EzI2CCyBtldrCommWrite
    #endif /* (xbee_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (xbee_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (xbee_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void xbee_SpiCyBtldrCommStart(void);
    void xbee_SpiCyBtldrCommStop (void);
    void xbee_SpiCyBtldrCommReset(void);
    cystatus xbee_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus xbee_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (xbee_SCB_MODE_SPI_CONST_CFG)
        #define xbee_CyBtldrCommStart   xbee_SpiCyBtldrCommStart
        #define xbee_CyBtldrCommStop    xbee_SpiCyBtldrCommStop
        #define xbee_CyBtldrCommReset   xbee_SpiCyBtldrCommReset
        #define xbee_CyBtldrCommRead    xbee_SpiCyBtldrCommRead
        #define xbee_CyBtldrCommWrite   xbee_SpiCyBtldrCommWrite
    #endif /* (xbee_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (xbee_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (xbee_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void xbee_UartCyBtldrCommStart(void);
    void xbee_UartCyBtldrCommStop (void);
    void xbee_UartCyBtldrCommReset(void);
    cystatus xbee_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus xbee_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (xbee_SCB_MODE_UART_CONST_CFG)
        #define xbee_CyBtldrCommStart   xbee_UartCyBtldrCommStart
        #define xbee_CyBtldrCommStop    xbee_UartCyBtldrCommStop
        #define xbee_CyBtldrCommReset   xbee_UartCyBtldrCommReset
        #define xbee_CyBtldrCommRead    xbee_UartCyBtldrCommRead
        #define xbee_CyBtldrCommWrite   xbee_UartCyBtldrCommWrite
    #endif /* (xbee_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (xbee_UART_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (xbee_BTLDR_COMM_ENABLED)
    #if (xbee_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void xbee_CyBtldrCommStart(void);
        void xbee_CyBtldrCommStop (void);
        void xbee_CyBtldrCommReset(void);
        cystatus xbee_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus xbee_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (xbee_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_xbee)
        #define CyBtldrCommStart    xbee_CyBtldrCommStart
        #define CyBtldrCommStop     xbee_CyBtldrCommStop
        #define CyBtldrCommReset    xbee_CyBtldrCommReset
        #define CyBtldrCommWrite    xbee_CyBtldrCommWrite
        #define CyBtldrCommRead     xbee_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_xbee) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (xbee_BTLDR_COMM_ENABLED) */


/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define xbee_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define xbee_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define xbee_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define xbee_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef xbee_SPI_BYTE_TO_BYTE
    #define xbee_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef xbee_UART_BYTE_TO_BYTE
    #define xbee_UART_BYTE_TO_BYTE  (2081u)
#endif /* xbee_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_xbee_H) */


/* [] END OF FILE */
