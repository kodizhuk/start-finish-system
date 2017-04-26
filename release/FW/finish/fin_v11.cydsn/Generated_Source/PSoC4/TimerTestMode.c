/*******************************************************************************
* File Name: TimerTestMode.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the TimerTestMode
*  component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "TimerTestMode.h"

uint8 TimerTestMode_initVar = 0u;


/*******************************************************************************
* Function Name: TimerTestMode_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default TimerTestMode configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (TimerTestMode__QUAD == TimerTestMode_CONFIG)
        TimerTestMode_CONTROL_REG = TimerTestMode_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        TimerTestMode_TRIG_CONTROL1_REG  = TimerTestMode_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        TimerTestMode_SetInterruptMode(TimerTestMode_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        TimerTestMode_SetCounterMode(TimerTestMode_COUNT_DOWN);
        TimerTestMode_WritePeriod(TimerTestMode_QUAD_PERIOD_INIT_VALUE);
        TimerTestMode_WriteCounter(TimerTestMode_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (TimerTestMode__QUAD == TimerTestMode_CONFIG) */

    #if (TimerTestMode__TIMER == TimerTestMode_CONFIG)
        TimerTestMode_CONTROL_REG = TimerTestMode_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        TimerTestMode_TRIG_CONTROL1_REG  = TimerTestMode_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        TimerTestMode_SetInterruptMode(TimerTestMode_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        TimerTestMode_WritePeriod(TimerTestMode_TC_PERIOD_VALUE );

        #if (TimerTestMode__COMPARE == TimerTestMode_TC_COMP_CAP_MODE)
            TimerTestMode_WriteCompare(TimerTestMode_TC_COMPARE_VALUE);

            #if (1u == TimerTestMode_TC_COMPARE_SWAP)
                TimerTestMode_SetCompareSwap(1u);
                TimerTestMode_WriteCompareBuf(TimerTestMode_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == TimerTestMode_TC_COMPARE_SWAP) */
        #endif  /* (TimerTestMode__COMPARE == TimerTestMode_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (TimerTestMode_CY_TCPWM_V2 && TimerTestMode_TIMER_UPDOWN_CNT_USED && !TimerTestMode_CY_TCPWM_4000)
            TimerTestMode_WriteCounter(1u);
        #elif(TimerTestMode__COUNT_DOWN == TimerTestMode_TC_COUNTER_MODE)
            TimerTestMode_WriteCounter(TimerTestMode_TC_PERIOD_VALUE);
        #else
            TimerTestMode_WriteCounter(0u);
        #endif /* (TimerTestMode_CY_TCPWM_V2 && TimerTestMode_TIMER_UPDOWN_CNT_USED && !TimerTestMode_CY_TCPWM_4000) */
    #endif  /* (TimerTestMode__TIMER == TimerTestMode_CONFIG) */

    #if (TimerTestMode__PWM_SEL == TimerTestMode_CONFIG)
        TimerTestMode_CONTROL_REG = TimerTestMode_CTRL_PWM_BASE_CONFIG;

        #if (TimerTestMode__PWM_PR == TimerTestMode_PWM_MODE)
            TimerTestMode_CONTROL_REG |= TimerTestMode_CTRL_PWM_RUN_MODE;
            TimerTestMode_WriteCounter(TimerTestMode_PWM_PR_INIT_VALUE);
        #else
            TimerTestMode_CONTROL_REG |= TimerTestMode_CTRL_PWM_ALIGN | TimerTestMode_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (TimerTestMode_CY_TCPWM_V2 && TimerTestMode_PWM_UPDOWN_CNT_USED && !TimerTestMode_CY_TCPWM_4000)
                TimerTestMode_WriteCounter(1u);
            #elif (TimerTestMode__RIGHT == TimerTestMode_PWM_ALIGN)
                TimerTestMode_WriteCounter(TimerTestMode_PWM_PERIOD_VALUE);
            #else 
                TimerTestMode_WriteCounter(0u);
            #endif  /* (TimerTestMode_CY_TCPWM_V2 && TimerTestMode_PWM_UPDOWN_CNT_USED && !TimerTestMode_CY_TCPWM_4000) */
        #endif  /* (TimerTestMode__PWM_PR == TimerTestMode_PWM_MODE) */

        #if (TimerTestMode__PWM_DT == TimerTestMode_PWM_MODE)
            TimerTestMode_CONTROL_REG |= TimerTestMode_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (TimerTestMode__PWM_DT == TimerTestMode_PWM_MODE) */

        #if (TimerTestMode__PWM == TimerTestMode_PWM_MODE)
            TimerTestMode_CONTROL_REG |= TimerTestMode_CTRL_PWM_PRESCALER;
        #endif  /* (TimerTestMode__PWM == TimerTestMode_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        TimerTestMode_TRIG_CONTROL1_REG  = TimerTestMode_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        TimerTestMode_SetInterruptMode(TimerTestMode_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (TimerTestMode__PWM_PR == TimerTestMode_PWM_MODE)
            TimerTestMode_TRIG_CONTROL2_REG =
                    (TimerTestMode_CC_MATCH_NO_CHANGE    |
                    TimerTestMode_OVERLOW_NO_CHANGE      |
                    TimerTestMode_UNDERFLOW_NO_CHANGE);
        #else
            #if (TimerTestMode__LEFT == TimerTestMode_PWM_ALIGN)
                TimerTestMode_TRIG_CONTROL2_REG = TimerTestMode_PWM_MODE_LEFT;
            #endif  /* ( TimerTestMode_PWM_LEFT == TimerTestMode_PWM_ALIGN) */

            #if (TimerTestMode__RIGHT == TimerTestMode_PWM_ALIGN)
                TimerTestMode_TRIG_CONTROL2_REG = TimerTestMode_PWM_MODE_RIGHT;
            #endif  /* ( TimerTestMode_PWM_RIGHT == TimerTestMode_PWM_ALIGN) */

            #if (TimerTestMode__CENTER == TimerTestMode_PWM_ALIGN)
                TimerTestMode_TRIG_CONTROL2_REG = TimerTestMode_PWM_MODE_CENTER;
            #endif  /* ( TimerTestMode_PWM_CENTER == TimerTestMode_PWM_ALIGN) */

            #if (TimerTestMode__ASYMMETRIC == TimerTestMode_PWM_ALIGN)
                TimerTestMode_TRIG_CONTROL2_REG = TimerTestMode_PWM_MODE_ASYM;
            #endif  /* (TimerTestMode__ASYMMETRIC == TimerTestMode_PWM_ALIGN) */
        #endif  /* (TimerTestMode__PWM_PR == TimerTestMode_PWM_MODE) */

        /* Set other values from customizer */
        TimerTestMode_WritePeriod(TimerTestMode_PWM_PERIOD_VALUE );
        TimerTestMode_WriteCompare(TimerTestMode_PWM_COMPARE_VALUE);

        #if (1u == TimerTestMode_PWM_COMPARE_SWAP)
            TimerTestMode_SetCompareSwap(1u);
            TimerTestMode_WriteCompareBuf(TimerTestMode_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == TimerTestMode_PWM_COMPARE_SWAP) */

        #if (1u == TimerTestMode_PWM_PERIOD_SWAP)
            TimerTestMode_SetPeriodSwap(1u);
            TimerTestMode_WritePeriodBuf(TimerTestMode_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == TimerTestMode_PWM_PERIOD_SWAP) */
    #endif  /* (TimerTestMode__PWM_SEL == TimerTestMode_CONFIG) */
    
}


/*******************************************************************************
* Function Name: TimerTestMode_Enable
********************************************************************************
*
* Summary:
*  Enables the TimerTestMode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    TimerTestMode_BLOCK_CONTROL_REG |= TimerTestMode_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (TimerTestMode__PWM_SEL == TimerTestMode_CONFIG)
        #if (0u == TimerTestMode_PWM_START_SIGNAL_PRESENT)
            TimerTestMode_TriggerCommand(TimerTestMode_MASK, TimerTestMode_CMD_START);
        #endif /* (0u == TimerTestMode_PWM_START_SIGNAL_PRESENT) */
    #endif /* (TimerTestMode__PWM_SEL == TimerTestMode_CONFIG) */

    #if (TimerTestMode__TIMER == TimerTestMode_CONFIG)
        #if (0u == TimerTestMode_TC_START_SIGNAL_PRESENT)
            TimerTestMode_TriggerCommand(TimerTestMode_MASK, TimerTestMode_CMD_START);
        #endif /* (0u == TimerTestMode_TC_START_SIGNAL_PRESENT) */
    #endif /* (TimerTestMode__TIMER == TimerTestMode_CONFIG) */
    
    #if (TimerTestMode__QUAD == TimerTestMode_CONFIG)
        #if (0u != TimerTestMode_QUAD_AUTO_START)
            TimerTestMode_TriggerCommand(TimerTestMode_MASK, TimerTestMode_CMD_RELOAD);
        #endif /* (0u != TimerTestMode_QUAD_AUTO_START) */
    #endif  /* (TimerTestMode__QUAD == TimerTestMode_CONFIG) */
}


/*******************************************************************************
* Function Name: TimerTestMode_Start
********************************************************************************
*
* Summary:
*  Initializes the TimerTestMode with default customizer
*  values when called the first time and enables the TimerTestMode.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  TimerTestMode_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time TimerTestMode_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the TimerTestMode_Start() routine.
*
*******************************************************************************/
void TimerTestMode_Start(void)
{
    if (0u == TimerTestMode_initVar)
    {
        TimerTestMode_Init();
        TimerTestMode_initVar = 1u;
    }

    TimerTestMode_Enable();
}


/*******************************************************************************
* Function Name: TimerTestMode_Stop
********************************************************************************
*
* Summary:
*  Disables the TimerTestMode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimerTestMode_BLOCK_CONTROL_REG &= (uint32)~TimerTestMode_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimerTestMode_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the TimerTestMode. This function is used when
*  configured as a generic TimerTestMode and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the TimerTestMode to operate in
*   Values:
*   - TimerTestMode_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - TimerTestMode_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - TimerTestMode_MODE_QUAD - Quadrature decoder
*         - TimerTestMode_MODE_PWM - PWM
*         - TimerTestMode_MODE_PWM_DT - PWM with dead time
*         - TimerTestMode_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimerTestMode_CONTROL_REG &= (uint32)~TimerTestMode_MODE_MASK;
    TimerTestMode_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimerTestMode_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - TimerTestMode_MODE_X1 - Counts on phi 1 rising
*         - TimerTestMode_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - TimerTestMode_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimerTestMode_CONTROL_REG &= (uint32)~TimerTestMode_QUAD_MODE_MASK;
    TimerTestMode_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimerTestMode_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - TimerTestMode_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - TimerTestMode_PRESCALE_DIVBY2    - Divide by 2
*         - TimerTestMode_PRESCALE_DIVBY4    - Divide by 4
*         - TimerTestMode_PRESCALE_DIVBY8    - Divide by 8
*         - TimerTestMode_PRESCALE_DIVBY16   - Divide by 16
*         - TimerTestMode_PRESCALE_DIVBY32   - Divide by 32
*         - TimerTestMode_PRESCALE_DIVBY64   - Divide by 64
*         - TimerTestMode_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimerTestMode_CONTROL_REG &= (uint32)~TimerTestMode_PRESCALER_MASK;
    TimerTestMode_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimerTestMode_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the TimerTestMode runs
*  continuously or stops when terminal count is reached.  By default the
*  TimerTestMode operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimerTestMode_CONTROL_REG &= (uint32)~TimerTestMode_ONESHOT_MASK;
    TimerTestMode_CONTROL_REG |= ((uint32)((oneShotEnable & TimerTestMode_1BIT_MASK) <<
                                                               TimerTestMode_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimerTestMode_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_SetPWMMode(uint32 modeMask)
{
    TimerTestMode_TRIG_CONTROL2_REG = (modeMask & TimerTestMode_6BIT_MASK);
}



/*******************************************************************************
* Function Name: TimerTestMode_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimerTestMode_CONTROL_REG &= (uint32)~TimerTestMode_PWM_SYNC_KILL_MASK;
    TimerTestMode_CONTROL_REG |= ((uint32)((syncKillEnable & TimerTestMode_1BIT_MASK)  <<
                                               TimerTestMode_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimerTestMode_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimerTestMode_CONTROL_REG &= (uint32)~TimerTestMode_PWM_STOP_KILL_MASK;
    TimerTestMode_CONTROL_REG |= ((uint32)((stopOnKillEnable & TimerTestMode_1BIT_MASK)  <<
                                                         TimerTestMode_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimerTestMode_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimerTestMode_CONTROL_REG &= (uint32)~TimerTestMode_PRESCALER_MASK;
    TimerTestMode_CONTROL_REG |= ((uint32)((deadTime & TimerTestMode_8BIT_MASK) <<
                                                          TimerTestMode_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimerTestMode_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - TimerTestMode_INVERT_LINE   - Inverts the line output
*         - TimerTestMode_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimerTestMode_CONTROL_REG &= (uint32)~TimerTestMode_INV_OUT_MASK;
    TimerTestMode_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: TimerTestMode_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_WriteCounter(uint32 count)
{
    TimerTestMode_COUNTER_REG = (count & TimerTestMode_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TimerTestMode_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 TimerTestMode_ReadCounter(void)
{
    return (TimerTestMode_COUNTER_REG & TimerTestMode_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TimerTestMode_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - TimerTestMode_COUNT_UP       - Counts up
*     - TimerTestMode_COUNT_DOWN     - Counts down
*     - TimerTestMode_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - TimerTestMode_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimerTestMode_CONTROL_REG &= (uint32)~TimerTestMode_UPDOWN_MASK;
    TimerTestMode_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimerTestMode_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_WritePeriod(uint32 period)
{
    TimerTestMode_PERIOD_REG = (period & TimerTestMode_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TimerTestMode_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 TimerTestMode_ReadPeriod(void)
{
    return (TimerTestMode_PERIOD_REG & TimerTestMode_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TimerTestMode_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimerTestMode_CONTROL_REG &= (uint32)~TimerTestMode_RELOAD_CC_MASK;
    TimerTestMode_CONTROL_REG |= (swapEnable & TimerTestMode_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimerTestMode_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_WritePeriodBuf(uint32 periodBuf)
{
    TimerTestMode_PERIOD_BUF_REG = (periodBuf & TimerTestMode_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TimerTestMode_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 TimerTestMode_ReadPeriodBuf(void)
{
    return (TimerTestMode_PERIOD_BUF_REG & TimerTestMode_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TimerTestMode_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimerTestMode_CONTROL_REG &= (uint32)~TimerTestMode_RELOAD_PERIOD_MASK;
    TimerTestMode_CONTROL_REG |= ((uint32)((swapEnable & TimerTestMode_1BIT_MASK) <<
                                                            TimerTestMode_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimerTestMode_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void TimerTestMode_WriteCompare(uint32 compare)
{
    #if (TimerTestMode_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (TimerTestMode_CY_TCPWM_4000) */

    #if (TimerTestMode_CY_TCPWM_4000)
        currentMode = ((TimerTestMode_CONTROL_REG & TimerTestMode_UPDOWN_MASK) >> TimerTestMode_UPDOWN_SHIFT);

        if (((uint32)TimerTestMode__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)TimerTestMode__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (TimerTestMode_CY_TCPWM_4000) */
    
    TimerTestMode_COMP_CAP_REG = (compare & TimerTestMode_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TimerTestMode_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 TimerTestMode_ReadCompare(void)
{
    #if (TimerTestMode_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (TimerTestMode_CY_TCPWM_4000) */

    #if (TimerTestMode_CY_TCPWM_4000)
        currentMode = ((TimerTestMode_CONTROL_REG & TimerTestMode_UPDOWN_MASK) >> TimerTestMode_UPDOWN_SHIFT);
        
        regVal = TimerTestMode_COMP_CAP_REG;
        
        if (((uint32)TimerTestMode__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)TimerTestMode__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & TimerTestMode_16BIT_MASK);
    #else
        return (TimerTestMode_COMP_CAP_REG & TimerTestMode_16BIT_MASK);
    #endif /* (TimerTestMode_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: TimerTestMode_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void TimerTestMode_WriteCompareBuf(uint32 compareBuf)
{
    #if (TimerTestMode_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (TimerTestMode_CY_TCPWM_4000) */

    #if (TimerTestMode_CY_TCPWM_4000)
        currentMode = ((TimerTestMode_CONTROL_REG & TimerTestMode_UPDOWN_MASK) >> TimerTestMode_UPDOWN_SHIFT);

        if (((uint32)TimerTestMode__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)TimerTestMode__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (TimerTestMode_CY_TCPWM_4000) */
    
    TimerTestMode_COMP_CAP_BUF_REG = (compareBuf & TimerTestMode_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TimerTestMode_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 TimerTestMode_ReadCompareBuf(void)
{
    #if (TimerTestMode_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (TimerTestMode_CY_TCPWM_4000) */

    #if (TimerTestMode_CY_TCPWM_4000)
        currentMode = ((TimerTestMode_CONTROL_REG & TimerTestMode_UPDOWN_MASK) >> TimerTestMode_UPDOWN_SHIFT);

        regVal = TimerTestMode_COMP_CAP_BUF_REG;
        
        if (((uint32)TimerTestMode__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)TimerTestMode__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & TimerTestMode_16BIT_MASK);
    #else
        return (TimerTestMode_COMP_CAP_BUF_REG & TimerTestMode_16BIT_MASK);
    #endif /* (TimerTestMode_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: TimerTestMode_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 TimerTestMode_ReadCapture(void)
{
    return (TimerTestMode_COMP_CAP_REG & TimerTestMode_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TimerTestMode_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 TimerTestMode_ReadCaptureBuf(void)
{
    return (TimerTestMode_COMP_CAP_BUF_REG & TimerTestMode_16BIT_MASK);
}


/*******************************************************************************
* Function Name: TimerTestMode_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TimerTestMode_TRIG_LEVEL     - Level
*     - TimerTestMode_TRIG_RISING    - Rising edge
*     - TimerTestMode_TRIG_FALLING   - Falling edge
*     - TimerTestMode_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimerTestMode_TRIG_CONTROL1_REG &= (uint32)~TimerTestMode_CAPTURE_MASK;
    TimerTestMode_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimerTestMode_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TimerTestMode_TRIG_LEVEL     - Level
*     - TimerTestMode_TRIG_RISING    - Rising edge
*     - TimerTestMode_TRIG_FALLING   - Falling edge
*     - TimerTestMode_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimerTestMode_TRIG_CONTROL1_REG &= (uint32)~TimerTestMode_RELOAD_MASK;
    TimerTestMode_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TimerTestMode_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimerTestMode_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TimerTestMode_TRIG_LEVEL     - Level
*     - TimerTestMode_TRIG_RISING    - Rising edge
*     - TimerTestMode_TRIG_FALLING   - Falling edge
*     - TimerTestMode_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimerTestMode_TRIG_CONTROL1_REG &= (uint32)~TimerTestMode_START_MASK;
    TimerTestMode_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TimerTestMode_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimerTestMode_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TimerTestMode_TRIG_LEVEL     - Level
*     - TimerTestMode_TRIG_RISING    - Rising edge
*     - TimerTestMode_TRIG_FALLING   - Falling edge
*     - TimerTestMode_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimerTestMode_TRIG_CONTROL1_REG &= (uint32)~TimerTestMode_STOP_MASK;
    TimerTestMode_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TimerTestMode_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimerTestMode_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - TimerTestMode_TRIG_LEVEL     - Level
*     - TimerTestMode_TRIG_RISING    - Rising edge
*     - TimerTestMode_TRIG_FALLING   - Falling edge
*     - TimerTestMode_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimerTestMode_TRIG_CONTROL1_REG &= (uint32)~TimerTestMode_COUNT_MASK;
    TimerTestMode_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << TimerTestMode_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimerTestMode_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - TimerTestMode_CMD_CAPTURE    - Trigger Capture/Switch command
*     - TimerTestMode_CMD_RELOAD     - Trigger Reload/Index command
*     - TimerTestMode_CMD_STOP       - Trigger Stop/Kill command
*     - TimerTestMode_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    TimerTestMode_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: TimerTestMode_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the TimerTestMode.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - TimerTestMode_STATUS_DOWN    - Set if counting down
*     - TimerTestMode_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 TimerTestMode_ReadStatus(void)
{
    return ((TimerTestMode_STATUS_REG >> TimerTestMode_RUNNING_STATUS_SHIFT) |
            (TimerTestMode_STATUS_REG & TimerTestMode_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: TimerTestMode_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - TimerTestMode_INTR_MASK_TC       - Terminal count mask
*     - TimerTestMode_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_SetInterruptMode(uint32 interruptMask)
{
    TimerTestMode_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: TimerTestMode_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - TimerTestMode_INTR_MASK_TC       - Terminal count mask
*     - TimerTestMode_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 TimerTestMode_GetInterruptSourceMasked(void)
{
    return (TimerTestMode_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: TimerTestMode_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - TimerTestMode_INTR_MASK_TC       - Terminal count mask
*     - TimerTestMode_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 TimerTestMode_GetInterruptSource(void)
{
    return (TimerTestMode_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: TimerTestMode_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - TimerTestMode_INTR_MASK_TC       - Terminal count mask
*     - TimerTestMode_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_ClearInterrupt(uint32 interruptMask)
{
    TimerTestMode_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: TimerTestMode_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - TimerTestMode_INTR_MASK_TC       - Terminal count mask
*     - TimerTestMode_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void TimerTestMode_SetInterrupt(uint32 interruptMask)
{
    TimerTestMode_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
