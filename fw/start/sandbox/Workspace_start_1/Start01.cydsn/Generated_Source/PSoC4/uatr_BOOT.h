/*******************************************************************************
* File Name: uatr_BOOT.h
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

#if !defined(CY_SCB_BOOT_uatr_H)
#define CY_SCB_BOOT_uatr_H

#include "uatr_PVT.h"

#if (uatr_SCB_MODE_I2C_INC)
    #include "uatr_I2C.h"
#endif /* (uatr_SCB_MODE_I2C_INC) */

#if (uatr_SCB_MODE_EZI2C_INC)
    #include "uatr_EZI2C.h"
#endif /* (uatr_SCB_MODE_EZI2C_INC) */

#if (uatr_SCB_MODE_SPI_INC || uatr_SCB_MODE_UART_INC)
    #include "uatr_SPI_UART.h"
#endif /* (uatr_SCB_MODE_SPI_INC || uatr_SCB_MODE_UART_INC) */


/***************************************
*  Conditional Compilation Parameters
****************************************/

/* Bootloader communication interface enable */
#define uatr_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_uatr) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/* Enable I2C bootloader communication */
#if (uatr_SCB_MODE_I2C_INC)
    #define uatr_I2C_BTLDR_COMM_ENABLED     (uatr_BTLDR_COMM_ENABLED && \
                                                            (uatr_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             uatr_I2C_SLAVE_CONST))
#else
     #define uatr_I2C_BTLDR_COMM_ENABLED    (0u)
#endif /* (uatr_SCB_MODE_I2C_INC) */

/* EZI2C does not support bootloader communication. Provide empty APIs */
#if (uatr_SCB_MODE_EZI2C_INC)
    #define uatr_EZI2C_BTLDR_COMM_ENABLED   (uatr_BTLDR_COMM_ENABLED && \
                                                         uatr_SCB_MODE_UNCONFIG_CONST_CFG)
#else
    #define uatr_EZI2C_BTLDR_COMM_ENABLED   (0u)
#endif /* (uatr_EZI2C_BTLDR_COMM_ENABLED) */

/* Enable SPI bootloader communication */
#if (uatr_SCB_MODE_SPI_INC)
    #define uatr_SPI_BTLDR_COMM_ENABLED     (uatr_BTLDR_COMM_ENABLED && \
                                                            (uatr_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             uatr_SPI_SLAVE_CONST))
#else
        #define uatr_SPI_BTLDR_COMM_ENABLED (0u)
#endif /* (uatr_SPI_BTLDR_COMM_ENABLED) */

/* Enable UART bootloader communication */
#if (uatr_SCB_MODE_UART_INC)
       #define uatr_UART_BTLDR_COMM_ENABLED    (uatr_BTLDR_COMM_ENABLED && \
                                                            (uatr_SCB_MODE_UNCONFIG_CONST_CFG || \
                                                             (uatr_UART_RX_DIRECTION && \
                                                              uatr_UART_TX_DIRECTION)))
#else
     #define uatr_UART_BTLDR_COMM_ENABLED   (0u)
#endif /* (uatr_UART_BTLDR_COMM_ENABLED) */

/* Enable bootloader communication */
#define uatr_BTLDR_COMM_MODE_ENABLED    (uatr_I2C_BTLDR_COMM_ENABLED   || \
                                                     uatr_SPI_BTLDR_COMM_ENABLED   || \
                                                     uatr_EZI2C_BTLDR_COMM_ENABLED || \
                                                     uatr_UART_BTLDR_COMM_ENABLED)


/***************************************
*        Function Prototypes
***************************************/

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (uatr_I2C_BTLDR_COMM_ENABLED)
    /* I2C Bootloader physical layer functions */
    void uatr_I2CCyBtldrCommStart(void);
    void uatr_I2CCyBtldrCommStop (void);
    void uatr_I2CCyBtldrCommReset(void);
    cystatus uatr_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus uatr_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map I2C specific bootloader communication APIs to SCB specific APIs */
    #if (uatr_SCB_MODE_I2C_CONST_CFG)
        #define uatr_CyBtldrCommStart   uatr_I2CCyBtldrCommStart
        #define uatr_CyBtldrCommStop    uatr_I2CCyBtldrCommStop
        #define uatr_CyBtldrCommReset   uatr_I2CCyBtldrCommReset
        #define uatr_CyBtldrCommRead    uatr_I2CCyBtldrCommRead
        #define uatr_CyBtldrCommWrite   uatr_I2CCyBtldrCommWrite
    #endif /* (uatr_SCB_MODE_I2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (uatr_I2C_BTLDR_COMM_ENABLED) */


#if defined(CYDEV_BOOTLOADER_IO_COMP) && (uatr_EZI2C_BTLDR_COMM_ENABLED)
    /* Bootloader physical layer functions */
    void uatr_EzI2CCyBtldrCommStart(void);
    void uatr_EzI2CCyBtldrCommStop (void);
    void uatr_EzI2CCyBtldrCommReset(void);
    cystatus uatr_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus uatr_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map EZI2C specific bootloader communication APIs to SCB specific APIs */
    #if (uatr_SCB_MODE_EZI2C_CONST_CFG)
        #define uatr_CyBtldrCommStart   uatr_EzI2CCyBtldrCommStart
        #define uatr_CyBtldrCommStop    uatr_EzI2CCyBtldrCommStop
        #define uatr_CyBtldrCommReset   uatr_EzI2CCyBtldrCommReset
        #define uatr_CyBtldrCommRead    uatr_EzI2CCyBtldrCommRead
        #define uatr_CyBtldrCommWrite   uatr_EzI2CCyBtldrCommWrite
    #endif /* (uatr_SCB_MODE_EZI2C_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (uatr_EZI2C_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (uatr_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void uatr_SpiCyBtldrCommStart(void);
    void uatr_SpiCyBtldrCommStop (void);
    void uatr_SpiCyBtldrCommReset(void);
    cystatus uatr_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus uatr_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map SPI specific bootloader communication APIs to SCB specific APIs */
    #if (uatr_SCB_MODE_SPI_CONST_CFG)
        #define uatr_CyBtldrCommStart   uatr_SpiCyBtldrCommStart
        #define uatr_CyBtldrCommStop    uatr_SpiCyBtldrCommStop
        #define uatr_CyBtldrCommReset   uatr_SpiCyBtldrCommReset
        #define uatr_CyBtldrCommRead    uatr_SpiCyBtldrCommRead
        #define uatr_CyBtldrCommWrite   uatr_SpiCyBtldrCommWrite
    #endif /* (uatr_SCB_MODE_SPI_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (uatr_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (uatr_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void uatr_UartCyBtldrCommStart(void);
    void uatr_UartCyBtldrCommStop (void);
    void uatr_UartCyBtldrCommReset(void);
    cystatus uatr_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus uatr_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Map UART specific bootloader communication APIs to SCB specific APIs */
    #if (uatr_SCB_MODE_UART_CONST_CFG)
        #define uatr_CyBtldrCommStart   uatr_UartCyBtldrCommStart
        #define uatr_CyBtldrCommStop    uatr_UartCyBtldrCommStop
        #define uatr_CyBtldrCommReset   uatr_UartCyBtldrCommReset
        #define uatr_CyBtldrCommRead    uatr_UartCyBtldrCommRead
        #define uatr_CyBtldrCommWrite   uatr_UartCyBtldrCommWrite
    #endif /* (uatr_SCB_MODE_UART_CONST_CFG) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (uatr_UART_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (uatr_BTLDR_COMM_ENABLED)
    #if (uatr_SCB_MODE_UNCONFIG_CONST_CFG)
        /* Bootloader physical layer functions */
        void uatr_CyBtldrCommStart(void);
        void uatr_CyBtldrCommStop (void);
        void uatr_CyBtldrCommReset(void);
        cystatus uatr_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
        cystatus uatr_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    #endif /* (uatr_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Map SCB specific bootloader communication APIs to common APIs */
    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_uatr)
        #define CyBtldrCommStart    uatr_CyBtldrCommStart
        #define CyBtldrCommStop     uatr_CyBtldrCommStop
        #define CyBtldrCommReset    uatr_CyBtldrCommReset
        #define CyBtldrCommWrite    uatr_CyBtldrCommWrite
        #define CyBtldrCommRead     uatr_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_uatr) */

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (uatr_BTLDR_COMM_ENABLED) */


/***************************************
*           API Constants
***************************************/

/* Timeout unit in milliseconds */
#define uatr_WAIT_1_MS  (1u)

/* Return number of bytes to copy into bootloader buffer */
#define uatr_BYTES_TO_COPY(actBufSize, bufSize) \
                            ( ((uint32)(actBufSize) < (uint32)(bufSize)) ? \
                                ((uint32) (actBufSize)) : ((uint32) (bufSize)) )

/* Size of Read/Write buffers for I2C bootloader  */
#define uatr_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
#define uatr_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)

/* Byte to byte time interval: calculated basing on current component
* data rate configuration, can be defined in project if required.
*/
#ifndef uatr_SPI_BYTE_TO_BYTE
    #define uatr_SPI_BYTE_TO_BYTE   (160u)
#endif

/* Byte to byte time interval: calculated basing on current component
* baud rate configuration, can be defined in the project if required.
*/
#ifndef uatr_UART_BYTE_TO_BYTE
    #define uatr_UART_BYTE_TO_BYTE  (2081u)
#endif /* uatr_UART_BYTE_TO_BYTE */

#endif /* (CY_SCB_BOOT_uatr_H) */


/* [] END OF FILE */
