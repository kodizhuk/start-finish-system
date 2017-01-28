/***************************************************************************//**
* \file DEBUG_UART_BOOT.c
* \version 3.20
*
* \brief
*  This file provides the source code of the bootloader communication APIs
*  for the SCB Component Unconfigured mode.
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

#include "DEBUG_UART_BOOT.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (DEBUG_UART_BTLDR_COMM_ENABLED) && \
                                (DEBUG_UART_SCB_MODE_UNCONFIG_CONST_CFG)

/*******************************************************************************
* Function Name: DEBUG_UART_CyBtldrCommStart
****************************************************************************//**
*
*  Starts DEBUG_UART component. After this function call the component is 
*  ready for communication.
*
*******************************************************************************/
void DEBUG_UART_CyBtldrCommStart(void)
{
    if (DEBUG_UART_SCB_MODE_I2C_RUNTM_CFG)
    {
        DEBUG_UART_I2CCyBtldrCommStart();
    }
    else if (DEBUG_UART_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        DEBUG_UART_EzI2CCyBtldrCommStart();
    }
#if (!DEBUG_UART_CY_SCBIP_V1)
    else if (DEBUG_UART_SCB_MODE_SPI_RUNTM_CFG)
    {
        DEBUG_UART_SpiCyBtldrCommStart();
    }
    else if (DEBUG_UART_SCB_MODE_UART_RUNTM_CFG)
    {
        DEBUG_UART_UartCyBtldrCommStart();
    }
#endif /* (!DEBUG_UART_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: DEBUG_UART_CyBtldrCommStop
****************************************************************************//**
*
*  Stops DEBUG_UART component.
*
*******************************************************************************/
void DEBUG_UART_CyBtldrCommStop(void)
{
    if (DEBUG_UART_SCB_MODE_I2C_RUNTM_CFG)
    {
        DEBUG_UART_I2CCyBtldrCommStop();
    }
    else if (DEBUG_UART_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        DEBUG_UART_EzI2CCyBtldrCommStop();
    }
#if (!DEBUG_UART_CY_SCBIP_V1)
    else if (DEBUG_UART_SCB_MODE_SPI_RUNTM_CFG)
    {
        DEBUG_UART_SpiCyBtldrCommStop();
    }
    else if (DEBUG_UART_SCB_MODE_UART_RUNTM_CFG)
    {
        DEBUG_UART_UartCyBtldrCommStop();
    }
#endif /* (!DEBUG_UART_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: DEBUG_UART_CyBtldrCommReset
****************************************************************************//**
*
*  Clears DEBUG_UART component buffers.
*
*******************************************************************************/
void DEBUG_UART_CyBtldrCommReset(void)
{
    if(DEBUG_UART_SCB_MODE_I2C_RUNTM_CFG)
    {
        DEBUG_UART_I2CCyBtldrCommReset();
    }
    else if(DEBUG_UART_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        DEBUG_UART_EzI2CCyBtldrCommReset();
    }
#if (!DEBUG_UART_CY_SCBIP_V1)
    else if(DEBUG_UART_SCB_MODE_SPI_RUNTM_CFG)
    {
        DEBUG_UART_SpiCyBtldrCommReset();
    }
    else if(DEBUG_UART_SCB_MODE_UART_RUNTM_CFG)
    {
        DEBUG_UART_UartCyBtldrCommReset();
    }
#endif /* (!DEBUG_UART_CY_SCBIP_V1) */
    else
    {
        /* Unknown mode: do nothing */
    }
}


/*******************************************************************************
* Function Name: DEBUG_UART_CyBtldrCommRead
****************************************************************************//**
*
*  Allows the caller to read data from the bootloader host (the host writes the 
*  data). The function handles polling to allow a block of data to be completely
*  received from the host device.
*
*  \param pData: Pointer to storage for the block of data to be read from the
*   bootloader host.
*  \param size: Number of bytes to be read.
*  \param count: Pointer to the variable to write the number of bytes actually
*   read.
*  \param timeOut: Number of units in 10 ms to wait before returning because of a
*   timeout.
*
* \return
*  \return
*  cystatus: Returns CYRET_SUCCESS if no problem was encountered or returns the
*  value that best describes the problem. For more information refer to 
*  the “Return Codes” section of the System Reference Guide.
*
*******************************************************************************/
cystatus DEBUG_UART_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(DEBUG_UART_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = DEBUG_UART_I2CCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(DEBUG_UART_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = DEBUG_UART_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
    }
#if (!DEBUG_UART_CY_SCBIP_V1)
    else if(DEBUG_UART_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = DEBUG_UART_SpiCyBtldrCommRead(pData, size, count, timeOut);
    }
    else if(DEBUG_UART_SCB_MODE_UART_RUNTM_CFG)
    {
        status = DEBUG_UART_UartCyBtldrCommRead(pData, size, count, timeOut);
    }
#endif /* (!DEBUG_UART_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}


/*******************************************************************************
* Function Name: DEBUG_UART_CyBtldrCommWrite
****************************************************************************//**
*
*  Allows the caller to write data to the bootloader host (the host reads the 
*  data). The function does not use timeout and returns after data has been copied
*  into the slave read buffer. This data available to be read by the bootloader
*  host until following host data write.
*
*  \param pData: Pointer to the block of data to be written to the bootloader host.
*  \param size: Number of bytes to be written.
*  \param count: Pointer to the variable to write the number of bytes actually
*   written.
*  \param timeOut: Number of units in 10 ms to wait before returning because of a
*   timeout.
*
*  \return
*  cystatus: Returns CYRET_SUCCESS if no problem was encountered or returns the
*  value that best describes the problem. For more information refer to 
*  the “Return Codes” section of the System Reference Guide.
*
*******************************************************************************/
cystatus DEBUG_UART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    if(DEBUG_UART_SCB_MODE_I2C_RUNTM_CFG)
    {
        status = DEBUG_UART_I2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(DEBUG_UART_SCB_MODE_EZI2C_RUNTM_CFG)
    {
        status = DEBUG_UART_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
    }
#if (!DEBUG_UART_CY_SCBIP_V1)
    else if(DEBUG_UART_SCB_MODE_SPI_RUNTM_CFG)
    {
        status = DEBUG_UART_SpiCyBtldrCommWrite(pData, size, count, timeOut);
    }
    else if(DEBUG_UART_SCB_MODE_UART_RUNTM_CFG)
    {
        status = DEBUG_UART_UartCyBtldrCommWrite(pData, size, count, timeOut);
    }
#endif /* (!DEBUG_UART_CY_SCBIP_V1) */
    else
    {
        status = CYRET_INVALID_STATE; /* Unknown mode: return invalid status */
    }

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (DEBUG_UART_BTLDR_COMM_MODE_ENABLED) */


/* [] END OF FILE */
