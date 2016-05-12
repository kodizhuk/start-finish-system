/*******************************************************************************
* File Name: xbee.c
* Version 2.50
*
* Description:
*  This file provides all API functionality of the UART component
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "xbee.h"
#if (xbee_INTERNAL_CLOCK_USED)
    #include "xbee_IntClock.h"
#endif /* End xbee_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 xbee_initVar = 0u;

#if (xbee_TX_INTERRUPT_ENABLED && xbee_TX_ENABLED)
    volatile uint8 xbee_txBuffer[xbee_TX_BUFFER_SIZE];
    volatile uint8 xbee_txBufferRead = 0u;
    uint8 xbee_txBufferWrite = 0u;
#endif /* (xbee_TX_INTERRUPT_ENABLED && xbee_TX_ENABLED) */

#if (xbee_RX_INTERRUPT_ENABLED && (xbee_RX_ENABLED || xbee_HD_ENABLED))
    uint8 xbee_errorStatus = 0u;
    volatile uint8 xbee_rxBuffer[xbee_RX_BUFFER_SIZE];
    volatile uint8 xbee_rxBufferRead  = 0u;
    volatile uint8 xbee_rxBufferWrite = 0u;
    volatile uint8 xbee_rxBufferLoopDetect = 0u;
    volatile uint8 xbee_rxBufferOverflow   = 0u;
    #if (xbee_RXHW_ADDRESS_ENABLED)
        volatile uint8 xbee_rxAddressMode = xbee_RX_ADDRESS_MODE;
        volatile uint8 xbee_rxAddressDetected = 0u;
    #endif /* (xbee_RXHW_ADDRESS_ENABLED) */
#endif /* (xbee_RX_INTERRUPT_ENABLED && (xbee_RX_ENABLED || xbee_HD_ENABLED)) */


/*******************************************************************************
* Function Name: xbee_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  xbee_Start() sets the initVar variable, calls the
*  xbee_Init() function, and then calls the
*  xbee_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The xbee_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time xbee_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the xbee_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void xbee_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(xbee_initVar == 0u)
    {
        xbee_Init();
        xbee_initVar = 1u;
    }

    xbee_Enable();
}


/*******************************************************************************
* Function Name: xbee_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call xbee_Init() because
*  the xbee_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void xbee_Init(void) 
{
    #if(xbee_RX_ENABLED || xbee_HD_ENABLED)

        #if (xbee_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(xbee_RX_VECT_NUM, &xbee_RXISR);
            CyIntSetPriority(xbee_RX_VECT_NUM, xbee_RX_PRIOR_NUM);
            xbee_errorStatus = 0u;
        #endif /* (xbee_RX_INTERRUPT_ENABLED) */

        #if (xbee_RXHW_ADDRESS_ENABLED)
            xbee_SetRxAddressMode(xbee_RX_ADDRESS_MODE);
            xbee_SetRxAddress1(xbee_RX_HW_ADDRESS1);
            xbee_SetRxAddress2(xbee_RX_HW_ADDRESS2);
        #endif /* End xbee_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        xbee_RXBITCTR_PERIOD_REG = xbee_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        xbee_RXSTATUS_MASK_REG  = xbee_INIT_RX_INTERRUPTS_MASK;
    #endif /* End xbee_RX_ENABLED || xbee_HD_ENABLED*/

    #if(xbee_TX_ENABLED)
        #if (xbee_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(xbee_TX_VECT_NUM, &xbee_TXISR);
            CyIntSetPriority(xbee_TX_VECT_NUM, xbee_TX_PRIOR_NUM);
        #endif /* (xbee_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (xbee_TXCLKGEN_DP)
            xbee_TXBITCLKGEN_CTR_REG = xbee_BIT_CENTER;
            xbee_TXBITCLKTX_COMPLETE_REG = ((xbee_NUMBER_OF_DATA_BITS +
                        xbee_NUMBER_OF_START_BIT) * xbee_OVER_SAMPLE_COUNT) - 1u;
        #else
            xbee_TXBITCTR_PERIOD_REG = ((xbee_NUMBER_OF_DATA_BITS +
                        xbee_NUMBER_OF_START_BIT) * xbee_OVER_SAMPLE_8) - 1u;
        #endif /* End xbee_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (xbee_TX_INTERRUPT_ENABLED)
            xbee_TXSTATUS_MASK_REG = xbee_TX_STS_FIFO_EMPTY;
        #else
            xbee_TXSTATUS_MASK_REG = xbee_INIT_TX_INTERRUPTS_MASK;
        #endif /*End xbee_TX_INTERRUPT_ENABLED*/

    #endif /* End xbee_TX_ENABLED */

    #if(xbee_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        xbee_WriteControlRegister( \
            (xbee_ReadControlRegister() & (uint8)~xbee_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(xbee_PARITY_TYPE << xbee_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End xbee_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: xbee_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call xbee_Enable() because the xbee_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  xbee_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void xbee_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (xbee_RX_ENABLED || xbee_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        xbee_RXBITCTR_CONTROL_REG |= xbee_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        xbee_RXSTATUS_ACTL_REG  |= xbee_INT_ENABLE;

        #if (xbee_RX_INTERRUPT_ENABLED)
            xbee_EnableRxInt();

            #if (xbee_RXHW_ADDRESS_ENABLED)
                xbee_rxAddressDetected = 0u;
            #endif /* (xbee_RXHW_ADDRESS_ENABLED) */
        #endif /* (xbee_RX_INTERRUPT_ENABLED) */
    #endif /* (xbee_RX_ENABLED || xbee_HD_ENABLED) */

    #if(xbee_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!xbee_TXCLKGEN_DP)
            xbee_TXBITCTR_CONTROL_REG |= xbee_CNTR_ENABLE;
        #endif /* End xbee_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        xbee_TXSTATUS_ACTL_REG |= xbee_INT_ENABLE;
        #if (xbee_TX_INTERRUPT_ENABLED)
            xbee_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            xbee_EnableTxInt();
        #endif /* (xbee_TX_INTERRUPT_ENABLED) */
     #endif /* (xbee_TX_INTERRUPT_ENABLED) */

    #if (xbee_INTERNAL_CLOCK_USED)
        xbee_IntClock_Start();  /* Enable the clock */
    #endif /* (xbee_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: xbee_Stop
********************************************************************************
*
* Summary:
*  Disables the UART operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void xbee_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (xbee_RX_ENABLED || xbee_HD_ENABLED)
        xbee_RXBITCTR_CONTROL_REG &= (uint8) ~xbee_CNTR_ENABLE;
    #endif /* (xbee_RX_ENABLED || xbee_HD_ENABLED) */

    #if (xbee_TX_ENABLED)
        #if(!xbee_TXCLKGEN_DP)
            xbee_TXBITCTR_CONTROL_REG &= (uint8) ~xbee_CNTR_ENABLE;
        #endif /* (!xbee_TXCLKGEN_DP) */
    #endif /* (xbee_TX_ENABLED) */

    #if (xbee_INTERNAL_CLOCK_USED)
        xbee_IntClock_Stop();   /* Disable the clock */
    #endif /* (xbee_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (xbee_RX_ENABLED || xbee_HD_ENABLED)
        xbee_RXSTATUS_ACTL_REG  &= (uint8) ~xbee_INT_ENABLE;

        #if (xbee_RX_INTERRUPT_ENABLED)
            xbee_DisableRxInt();
        #endif /* (xbee_RX_INTERRUPT_ENABLED) */
    #endif /* (xbee_RX_ENABLED || xbee_HD_ENABLED) */

    #if (xbee_TX_ENABLED)
        xbee_TXSTATUS_ACTL_REG &= (uint8) ~xbee_INT_ENABLE;

        #if (xbee_TX_INTERRUPT_ENABLED)
            xbee_DisableTxInt();
        #endif /* (xbee_TX_INTERRUPT_ENABLED) */
    #endif /* (xbee_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: xbee_ReadControlRegister
********************************************************************************
*
* Summary:
*  Returns the current value of the control register.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the control register.
*
*******************************************************************************/
uint8 xbee_ReadControlRegister(void) 
{
    #if (xbee_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(xbee_CONTROL_REG);
    #endif /* (xbee_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: xbee_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  xbee_WriteControlRegister(uint8 control) 
{
    #if (xbee_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       xbee_CONTROL_REG = control;
    #endif /* (xbee_CONTROL_REG_REMOVED) */
}


#if(xbee_RX_ENABLED || xbee_HD_ENABLED)
    /*******************************************************************************
    * Function Name: xbee_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      xbee_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      xbee_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      xbee_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      xbee_RX_STS_BREAK            Interrupt on break.
    *      xbee_RX_STS_OVERRUN          Interrupt on overrun error.
    *      xbee_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      xbee_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void xbee_SetRxInterruptMode(uint8 intSrc) 
    {
        xbee_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: xbee_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns the next byte of received data. This function returns data without
    *  checking the status. You must check the status separately.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  xbee_rxBuffer - RAM buffer pointer for save received data.
    *  xbee_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  xbee_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  xbee_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 xbee_ReadRxData(void) 
    {
        uint8 rxData;

    #if (xbee_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        xbee_DisableRxInt();

        locRxBufferRead  = xbee_rxBufferRead;
        locRxBufferWrite = xbee_rxBufferWrite;

        if( (xbee_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = xbee_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= xbee_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            xbee_rxBufferRead = locRxBufferRead;

            if(xbee_rxBufferLoopDetect != 0u)
            {
                xbee_rxBufferLoopDetect = 0u;
                #if ((xbee_RX_INTERRUPT_ENABLED) && (xbee_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( xbee_HD_ENABLED )
                        if((xbee_CONTROL_REG & xbee_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            xbee_RXSTATUS_MASK_REG  |= xbee_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        xbee_RXSTATUS_MASK_REG  |= xbee_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end xbee_HD_ENABLED */
                #endif /* ((xbee_RX_INTERRUPT_ENABLED) && (xbee_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = xbee_RXDATA_REG;
        }

        xbee_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = xbee_RXDATA_REG;

    #endif /* (xbee_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: xbee_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the receiver status register and the software
    *  buffer overflow status.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Side Effect:
    *  All status register bits are clear-on-read except
    *  xbee_RX_STS_FIFO_NOTEMPTY.
    *  xbee_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  xbee_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   xbee_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   xbee_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 xbee_ReadRxStatus(void) 
    {
        uint8 status;

        status = xbee_RXSTATUS_REG & xbee_RX_HW_MASK;

    #if (xbee_RX_INTERRUPT_ENABLED)
        if(xbee_rxBufferOverflow != 0u)
        {
            status |= xbee_RX_STS_SOFT_BUFF_OVER;
            xbee_rxBufferOverflow = 0u;
        }
    #endif /* (xbee_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: xbee_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. xbee_GetChar() is
    *  designed for ASCII characters and returns a uint8 where 1 to 255 are values
    *  for valid characters and 0 indicates an error occurred or no data is present.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  xbee_rxBuffer - RAM buffer pointer for save received data.
    *  xbee_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  xbee_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  xbee_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 xbee_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (xbee_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        xbee_DisableRxInt();

        locRxBufferRead  = xbee_rxBufferRead;
        locRxBufferWrite = xbee_rxBufferWrite;

        if( (xbee_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = xbee_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= xbee_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            xbee_rxBufferRead = locRxBufferRead;

            if(xbee_rxBufferLoopDetect != 0u)
            {
                xbee_rxBufferLoopDetect = 0u;
                #if( (xbee_RX_INTERRUPT_ENABLED) && (xbee_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( xbee_HD_ENABLED )
                        if((xbee_CONTROL_REG & xbee_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            xbee_RXSTATUS_MASK_REG |= xbee_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        xbee_RXSTATUS_MASK_REG |= xbee_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end xbee_HD_ENABLED */
                #endif /* xbee_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = xbee_RXSTATUS_REG;
            if((rxStatus & xbee_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = xbee_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (xbee_RX_STS_BREAK | xbee_RX_STS_PAR_ERROR |
                                xbee_RX_STS_STOP_ERROR | xbee_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        xbee_EnableRxInt();

    #else

        rxStatus =xbee_RXSTATUS_REG;
        if((rxStatus & xbee_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = xbee_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (xbee_RX_STS_BREAK | xbee_RX_STS_PAR_ERROR |
                            xbee_RX_STS_STOP_ERROR | xbee_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (xbee_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: xbee_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, returns received character and error
    *  condition.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains status and LSB contains UART RX data. If the MSB is nonzero,
    *  an error has occurred.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 xbee_GetByte(void) 
    {
        
    #if (xbee_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        xbee_DisableRxInt();
        locErrorStatus = (uint16)xbee_errorStatus;
        xbee_errorStatus = 0u;
        xbee_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | xbee_ReadRxData() );
    #else
        return ( ((uint16)xbee_ReadRxStatus() << 8u) | xbee_ReadRxData() );
    #endif /* xbee_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: xbee_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received bytes available in the RX buffer.
    *  * RX software buffer is disabled (RX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty RX FIFO or 1 for not empty RX FIFO.
    *  * RX software buffer is enabled: returns the number of bytes available in 
    *    the RX software buffer. Bytes available in the RX FIFO do not take to 
    *    account.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Number of bytes in the RX buffer. 
    *    Return value type depends on RX Buffer Size parameter.
    *
    * Global Variables:
    *  xbee_rxBufferWrite - used to calculate left bytes.
    *  xbee_rxBufferRead - used to calculate left bytes.
    *  xbee_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 xbee_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (xbee_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        xbee_DisableRxInt();

        if(xbee_rxBufferRead == xbee_rxBufferWrite)
        {
            if(xbee_rxBufferLoopDetect != 0u)
            {
                size = xbee_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(xbee_rxBufferRead < xbee_rxBufferWrite)
        {
            size = (xbee_rxBufferWrite - xbee_rxBufferRead);
        }
        else
        {
            size = (xbee_RX_BUFFER_SIZE - xbee_rxBufferRead) + xbee_rxBufferWrite;
        }

        xbee_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((xbee_RXSTATUS_REG & xbee_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (xbee_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: xbee_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receiver memory buffer and hardware RX FIFO of all received data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  xbee_rxBufferWrite - cleared to zero.
    *  xbee_rxBufferRead - cleared to zero.
    *  xbee_rxBufferLoopDetect - cleared to zero.
    *  xbee_rxBufferOverflow - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM or FIFO buffer will be lost.
    *
    *******************************************************************************/
    void xbee_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        xbee_RXDATA_AUX_CTL_REG |= (uint8)  xbee_RX_FIFO_CLR;
        xbee_RXDATA_AUX_CTL_REG &= (uint8) ~xbee_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (xbee_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        xbee_DisableRxInt();

        xbee_rxBufferRead = 0u;
        xbee_rxBufferWrite = 0u;
        xbee_rxBufferLoopDetect = 0u;
        xbee_rxBufferOverflow = 0u;

        xbee_EnableRxInt();

    #endif /* (xbee_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: xbee_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  xbee__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  xbee__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  xbee__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  xbee__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  xbee__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  xbee_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  xbee_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void xbee_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(xbee_RXHW_ADDRESS_ENABLED)
            #if(xbee_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* xbee_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = xbee_CONTROL_REG & (uint8)~xbee_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << xbee_CTRL_RXADDR_MODE0_SHIFT);
                xbee_CONTROL_REG = tmpCtrl;

                #if(xbee_RX_INTERRUPT_ENABLED && \
                   (xbee_RXBUFFERSIZE > xbee_FIFO_LENGTH) )
                    xbee_rxAddressMode = addressMode;
                    xbee_rxAddressDetected = 0u;
                #endif /* End xbee_RXBUFFERSIZE > xbee_FIFO_LENGTH*/
            #endif /* End xbee_CONTROL_REG_REMOVED */
        #else /* xbee_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End xbee_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: xbee_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Sets the first of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #1 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void xbee_SetRxAddress1(uint8 address) 
    {
        xbee_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: xbee_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Sets the second of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #2 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void xbee_SetRxAddress2(uint8 address) 
    {
        xbee_RXADDRESS2_REG = address;
    }

#endif  /* xbee_RX_ENABLED || xbee_HD_ENABLED*/


#if( (xbee_TX_ENABLED) || (xbee_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: xbee_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   xbee_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   xbee_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   xbee_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   xbee_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void xbee_SetTxInterruptMode(uint8 intSrc) 
    {
        xbee_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: xbee_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data into the transmit buffer to be sent when the bus is
    *  available without checking the TX status register. You must check status
    *  separately.
    *
    * Parameters:
    *  txDataByte: data byte
    *
    * Return:
    * None.
    *
    * Global Variables:
    *  xbee_txBuffer - RAM buffer pointer for save data for transmission
    *  xbee_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  xbee_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  xbee_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void xbee_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(xbee_initVar != 0u)
        {
        #if (xbee_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            xbee_DisableTxInt();

            if( (xbee_txBufferRead == xbee_txBufferWrite) &&
                ((xbee_TXSTATUS_REG & xbee_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                xbee_TXDATA_REG = txDataByte;
            }
            else
            {
                if(xbee_txBufferWrite >= xbee_TX_BUFFER_SIZE)
                {
                    xbee_txBufferWrite = 0u;
                }

                xbee_txBuffer[xbee_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                xbee_txBufferWrite++;
            }

            xbee_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            xbee_TXDATA_REG = txDataByte;

        #endif /*(xbee_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: xbee_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Reads the status register for the TX portion of the UART.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the TX status register, which is cleared on read.
    *  It is up to the user to handle all bits in this return value accordingly,
    *  even if the bit was not enabled as an interrupt source the event happened
    *  and must be handled accordingly.
    *
    *******************************************************************************/
    uint8 xbee_ReadTxStatus(void) 
    {
        return(xbee_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: xbee_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Puts a byte of data into the transmit buffer to be sent when the bus is
    *  available. This is a blocking API that waits until the TX buffer has room to
    *  hold the data.
    *
    * Parameters:
    *  txDataByte: Byte containing the data to transmit
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  xbee_txBuffer - RAM buffer pointer for save data for transmission
    *  xbee_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  xbee_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  xbee_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void xbee_PutChar(uint8 txDataByte) 
    {
    #if (xbee_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((xbee_TX_BUFFER_SIZE > xbee_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            xbee_DisableTxInt();
        #endif /* (xbee_TX_BUFFER_SIZE > xbee_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = xbee_txBufferWrite;
            locTxBufferRead  = xbee_txBufferRead;

        #if ((xbee_TX_BUFFER_SIZE > xbee_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            xbee_EnableTxInt();
        #endif /* (xbee_TX_BUFFER_SIZE > xbee_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(xbee_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((xbee_TXSTATUS_REG & xbee_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            xbee_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= xbee_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            xbee_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((xbee_TX_BUFFER_SIZE > xbee_MAX_BYTE_VALUE) && (CY_PSOC3))
            xbee_DisableTxInt();
        #endif /* (xbee_TX_BUFFER_SIZE > xbee_MAX_BYTE_VALUE) && (CY_PSOC3) */

            xbee_txBufferWrite = locTxBufferWrite;

        #if ((xbee_TX_BUFFER_SIZE > xbee_MAX_BYTE_VALUE) && (CY_PSOC3))
            xbee_EnableTxInt();
        #endif /* (xbee_TX_BUFFER_SIZE > xbee_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (xbee_TXSTATUS_REG & xbee_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                xbee_SetPendingTxInt();
            }
        }

    #else

        while((xbee_TXSTATUS_REG & xbee_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        xbee_TXDATA_REG = txDataByte;

    #endif /* xbee_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: xbee_PutString
    ********************************************************************************
    *
    * Summary:
    *  Sends a NULL terminated string to the TX buffer for transmission.
    *
    * Parameters:
    *  string[]: Pointer to the null terminated string array residing in RAM or ROM
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  xbee_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void xbee_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(xbee_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                xbee_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: xbee_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Places N bytes of data from a memory array into the TX buffer for
    *  transmission.
    *
    * Parameters:
    *  string[]: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of bytes to be transmitted. The type depends on TX Buffer
    *             Size parameter.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  xbee_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void xbee_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(xbee_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                xbee_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: xbee_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Writes a byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) to the transmit buffer.
    *
    * Parameters:
    *  txDataByte: Data byte to transmit before the carriage return and line feed.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  xbee_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void xbee_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(xbee_initVar != 0u)
        {
            xbee_PutChar(txDataByte);
            xbee_PutChar(0x0Du);
            xbee_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: xbee_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of bytes in the TX buffer which are waiting to be 
    *  transmitted.
    *  * TX software buffer is disabled (TX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty TX FIFO, 1 for not full TX FIFO or 4 for full TX FIFO.
    *  * TX software buffer is enabled: returns the number of bytes in the TX 
    *    software buffer which are waiting to be transmitted. Bytes available in the
    *    TX FIFO do not count.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Number of bytes used in the TX buffer. Return value type depends on the TX 
    *  Buffer Size parameter.
    *
    * Global Variables:
    *  xbee_txBufferWrite - used to calculate left space.
    *  xbee_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 xbee_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (xbee_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        xbee_DisableTxInt();

        if(xbee_txBufferRead == xbee_txBufferWrite)
        {
            size = 0u;
        }
        else if(xbee_txBufferRead < xbee_txBufferWrite)
        {
            size = (xbee_txBufferWrite - xbee_txBufferRead);
        }
        else
        {
            size = (xbee_TX_BUFFER_SIZE - xbee_txBufferRead) +
                    xbee_txBufferWrite;
        }

        xbee_EnableTxInt();

    #else

        size = xbee_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & xbee_TX_STS_FIFO_FULL) != 0u)
        {
            size = xbee_FIFO_LENGTH;
        }
        else if((size & xbee_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (xbee_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: xbee_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears all data from the TX buffer and hardware TX FIFO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  xbee_txBufferWrite - cleared to zero.
    *  xbee_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Data waiting in the transmit buffer is not sent; a byte that is currently
    *  transmitting finishes transmitting.
    *
    *******************************************************************************/
    void xbee_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        xbee_TXDATA_AUX_CTL_REG |= (uint8)  xbee_TX_FIFO_CLR;
        xbee_TXDATA_AUX_CTL_REG &= (uint8) ~xbee_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (xbee_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        xbee_DisableTxInt();

        xbee_txBufferRead = 0u;
        xbee_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        xbee_EnableTxInt();

    #endif /* (xbee_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: xbee_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   xbee_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   xbee_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   xbee_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   xbee_SEND_WAIT_REINIT - Performs both options: 
    *      xbee_SEND_BREAK and xbee_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  xbee_initVar - checked to identify that the component has been
    *     initialized.
    *  txPeriod - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  There are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Function will block CPU until transmission
    *     complete.
    *  2) User may want to use blocking time if UART configured to the low speed
    *     operation
    *     Example for this case:
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to initialize and use the interrupt to
    *     complete break operation.
    *     Example for this case:
    *     Initialize TX interrupt with "TX - On TX Complete" parameter
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     When interrupt appear with xbee_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The xbee_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void xbee_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(xbee_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(xbee_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == xbee_SEND_BREAK) ||
                (retMode == xbee_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                xbee_WriteControlRegister(xbee_ReadControlRegister() |
                                                      xbee_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                xbee_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = xbee_TXSTATUS_REG;
                }
                while((tmpStat & xbee_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == xbee_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == xbee_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = xbee_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & xbee_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == xbee_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == xbee_REINIT) ||
                (retMode == xbee_SEND_WAIT_REINIT) )
            {
                xbee_WriteControlRegister(xbee_ReadControlRegister() &
                                              (uint8)~xbee_CTRL_HD_SEND_BREAK);
            }

        #else /* xbee_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == xbee_SEND_BREAK) ||
                (retMode == xbee_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (xbee_PARITY_TYPE != xbee__B_UART__NONE_REVB) || \
                                    (xbee_PARITY_TYPE_SW != 0u) )
                    xbee_WriteControlRegister(xbee_ReadControlRegister() |
                                                          xbee_CTRL_HD_SEND_BREAK);
                #endif /* End xbee_PARITY_TYPE != xbee__B_UART__NONE_REVB  */

                #if(xbee_TXCLKGEN_DP)
                    txPeriod = xbee_TXBITCLKTX_COMPLETE_REG;
                    xbee_TXBITCLKTX_COMPLETE_REG = xbee_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = xbee_TXBITCTR_PERIOD_REG;
                    xbee_TXBITCTR_PERIOD_REG = xbee_TXBITCTR_BREAKBITS8X;
                #endif /* End xbee_TXCLKGEN_DP */

                /* Send zeros */
                xbee_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = xbee_TXSTATUS_REG;
                }
                while((tmpStat & xbee_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == xbee_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == xbee_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = xbee_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & xbee_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == xbee_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == xbee_REINIT) ||
                (retMode == xbee_SEND_WAIT_REINIT) )
            {

            #if(xbee_TXCLKGEN_DP)
                xbee_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                xbee_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End xbee_TXCLKGEN_DP */

            #if( (xbee_PARITY_TYPE != xbee__B_UART__NONE_REVB) || \
                 (xbee_PARITY_TYPE_SW != 0u) )
                xbee_WriteControlRegister(xbee_ReadControlRegister() &
                                                      (uint8) ~xbee_CTRL_HD_SEND_BREAK);
            #endif /* End xbee_PARITY_TYPE != NONE */
            }
        #endif    /* End xbee_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: xbee_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       xbee_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       xbee_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears xbee_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void xbee_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( xbee_CONTROL_REG_REMOVED == 0u )
            xbee_WriteControlRegister(xbee_ReadControlRegister() |
                                                  xbee_CTRL_MARK);
        #endif /* End xbee_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( xbee_CONTROL_REG_REMOVED == 0u )
            xbee_WriteControlRegister(xbee_ReadControlRegister() &
                                                  (uint8) ~xbee_CTRL_MARK);
        #endif /* End xbee_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* Endxbee_TX_ENABLED */

#if(xbee_HD_ENABLED)


    /*******************************************************************************
    * Function Name: xbee_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the receiver configuration in half duplex mode. After calling this
    *  function, the UART is ready to receive data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the transmitter
    *  configuration.
    *
    *******************************************************************************/
    void xbee_LoadRxConfig(void) 
    {
        xbee_WriteControlRegister(xbee_ReadControlRegister() &
                                                (uint8)~xbee_CTRL_HD_SEND);
        xbee_RXBITCTR_PERIOD_REG = xbee_HD_RXBITCTR_INIT;

    #if (xbee_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        xbee_SetRxInterruptMode(xbee_INIT_RX_INTERRUPTS_MASK);
    #endif /* (xbee_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: xbee_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the transmitter configuration in half duplex mode. After calling this
    *  function, the UART is ready to transmit data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the receiver configuration.
    *
    *******************************************************************************/
    void xbee_LoadTxConfig(void) 
    {
    #if (xbee_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        xbee_SetRxInterruptMode(0u);
    #endif /* (xbee_RX_INTERRUPT_ENABLED) */

        xbee_WriteControlRegister(xbee_ReadControlRegister() | xbee_CTRL_HD_SEND);
        xbee_RXBITCTR_PERIOD_REG = xbee_HD_TXBITCTR_INIT;
    }

#endif  /* xbee_HD_ENABLED */


/* [] END OF FILE */
