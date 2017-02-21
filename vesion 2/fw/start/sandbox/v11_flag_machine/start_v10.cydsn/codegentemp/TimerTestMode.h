/*******************************************************************************
* File Name: TimerTestMode.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the TimerTestMode
*  component.
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

#if !defined(CY_TCPWM_TimerTestMode_H)
#define CY_TCPWM_TimerTestMode_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} TimerTestMode_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  TimerTestMode_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define TimerTestMode_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define TimerTestMode_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define TimerTestMode_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define TimerTestMode_QUAD_ENCODING_MODES            (0lu)
#define TimerTestMode_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define TimerTestMode_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define TimerTestMode_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define TimerTestMode_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define TimerTestMode_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define TimerTestMode_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define TimerTestMode_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define TimerTestMode_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define TimerTestMode_TC_RUN_MODE                    (0lu)
#define TimerTestMode_TC_COUNTER_MODE                (0lu)
#define TimerTestMode_TC_COMP_CAP_MODE               (0lu)
#define TimerTestMode_TC_PRESCALER                   (6lu)

/* Signal modes */
#define TimerTestMode_TC_RELOAD_SIGNAL_MODE          (0lu)
#define TimerTestMode_TC_COUNT_SIGNAL_MODE           (3lu)
#define TimerTestMode_TC_START_SIGNAL_MODE           (0lu)
#define TimerTestMode_TC_STOP_SIGNAL_MODE            (0lu)
#define TimerTestMode_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define TimerTestMode_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define TimerTestMode_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define TimerTestMode_TC_START_SIGNAL_PRESENT        (0lu)
#define TimerTestMode_TC_STOP_SIGNAL_PRESENT         (0lu)
#define TimerTestMode_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define TimerTestMode_TC_INTERRUPT_MASK              (2lu)

/* PWM Mode */
/* Parameters */
#define TimerTestMode_PWM_KILL_EVENT                 (0lu)
#define TimerTestMode_PWM_STOP_EVENT                 (0lu)
#define TimerTestMode_PWM_MODE                       (4lu)
#define TimerTestMode_PWM_OUT_N_INVERT               (0lu)
#define TimerTestMode_PWM_OUT_INVERT                 (0lu)
#define TimerTestMode_PWM_ALIGN                      (0lu)
#define TimerTestMode_PWM_RUN_MODE                   (0lu)
#define TimerTestMode_PWM_DEAD_TIME_CYCLE            (0lu)
#define TimerTestMode_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define TimerTestMode_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define TimerTestMode_PWM_COUNT_SIGNAL_MODE          (3lu)
#define TimerTestMode_PWM_START_SIGNAL_MODE          (0lu)
#define TimerTestMode_PWM_STOP_SIGNAL_MODE           (0lu)
#define TimerTestMode_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define TimerTestMode_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define TimerTestMode_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define TimerTestMode_PWM_START_SIGNAL_PRESENT       (0lu)
#define TimerTestMode_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define TimerTestMode_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define TimerTestMode_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define TimerTestMode_TC_PERIOD_VALUE                (65535lu)
#define TimerTestMode_TC_COMPARE_VALUE               (2500lu)
#define TimerTestMode_TC_COMPARE_BUF_VALUE           (65535lu)
#define TimerTestMode_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define TimerTestMode_PWM_PERIOD_VALUE               (65535lu)
#define TimerTestMode_PWM_PERIOD_BUF_VALUE           (65535lu)
#define TimerTestMode_PWM_PERIOD_SWAP                (0lu)
#define TimerTestMode_PWM_COMPARE_VALUE              (65535lu)
#define TimerTestMode_PWM_COMPARE_BUF_VALUE          (65535lu)
#define TimerTestMode_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define TimerTestMode__LEFT 0
#define TimerTestMode__RIGHT 1
#define TimerTestMode__CENTER 2
#define TimerTestMode__ASYMMETRIC 3

#define TimerTestMode__X1 0
#define TimerTestMode__X2 1
#define TimerTestMode__X4 2

#define TimerTestMode__PWM 4
#define TimerTestMode__PWM_DT 5
#define TimerTestMode__PWM_PR 6

#define TimerTestMode__INVERSE 1
#define TimerTestMode__DIRECT 0

#define TimerTestMode__CAPTURE 2
#define TimerTestMode__COMPARE 0

#define TimerTestMode__TRIG_LEVEL 3
#define TimerTestMode__TRIG_RISING 0
#define TimerTestMode__TRIG_FALLING 1
#define TimerTestMode__TRIG_BOTH 2

#define TimerTestMode__INTR_MASK_TC 1
#define TimerTestMode__INTR_MASK_CC_MATCH 2
#define TimerTestMode__INTR_MASK_NONE 0
#define TimerTestMode__INTR_MASK_TC_CC 3

#define TimerTestMode__UNCONFIG 8
#define TimerTestMode__TIMER 1
#define TimerTestMode__QUAD 3
#define TimerTestMode__PWM_SEL 7

#define TimerTestMode__COUNT_UP 0
#define TimerTestMode__COUNT_DOWN 1
#define TimerTestMode__COUNT_UPDOWN0 2
#define TimerTestMode__COUNT_UPDOWN1 3


/* Prescaler */
#define TimerTestMode_PRESCALE_DIVBY1                ((uint32)(0u << TimerTestMode_PRESCALER_SHIFT))
#define TimerTestMode_PRESCALE_DIVBY2                ((uint32)(1u << TimerTestMode_PRESCALER_SHIFT))
#define TimerTestMode_PRESCALE_DIVBY4                ((uint32)(2u << TimerTestMode_PRESCALER_SHIFT))
#define TimerTestMode_PRESCALE_DIVBY8                ((uint32)(3u << TimerTestMode_PRESCALER_SHIFT))
#define TimerTestMode_PRESCALE_DIVBY16               ((uint32)(4u << TimerTestMode_PRESCALER_SHIFT))
#define TimerTestMode_PRESCALE_DIVBY32               ((uint32)(5u << TimerTestMode_PRESCALER_SHIFT))
#define TimerTestMode_PRESCALE_DIVBY64               ((uint32)(6u << TimerTestMode_PRESCALER_SHIFT))
#define TimerTestMode_PRESCALE_DIVBY128              ((uint32)(7u << TimerTestMode_PRESCALER_SHIFT))

/* TCPWM set modes */
#define TimerTestMode_MODE_TIMER_COMPARE             ((uint32)(TimerTestMode__COMPARE         <<  \
                                                                  TimerTestMode_MODE_SHIFT))
#define TimerTestMode_MODE_TIMER_CAPTURE             ((uint32)(TimerTestMode__CAPTURE         <<  \
                                                                  TimerTestMode_MODE_SHIFT))
#define TimerTestMode_MODE_QUAD                      ((uint32)(TimerTestMode__QUAD            <<  \
                                                                  TimerTestMode_MODE_SHIFT))
#define TimerTestMode_MODE_PWM                       ((uint32)(TimerTestMode__PWM             <<  \
                                                                  TimerTestMode_MODE_SHIFT))
#define TimerTestMode_MODE_PWM_DT                    ((uint32)(TimerTestMode__PWM_DT          <<  \
                                                                  TimerTestMode_MODE_SHIFT))
#define TimerTestMode_MODE_PWM_PR                    ((uint32)(TimerTestMode__PWM_PR          <<  \
                                                                  TimerTestMode_MODE_SHIFT))

/* Quad Modes */
#define TimerTestMode_MODE_X1                        ((uint32)(TimerTestMode__X1              <<  \
                                                                  TimerTestMode_QUAD_MODE_SHIFT))
#define TimerTestMode_MODE_X2                        ((uint32)(TimerTestMode__X2              <<  \
                                                                  TimerTestMode_QUAD_MODE_SHIFT))
#define TimerTestMode_MODE_X4                        ((uint32)(TimerTestMode__X4              <<  \
                                                                  TimerTestMode_QUAD_MODE_SHIFT))

/* Counter modes */
#define TimerTestMode_COUNT_UP                       ((uint32)(TimerTestMode__COUNT_UP        <<  \
                                                                  TimerTestMode_UPDOWN_SHIFT))
#define TimerTestMode_COUNT_DOWN                     ((uint32)(TimerTestMode__COUNT_DOWN      <<  \
                                                                  TimerTestMode_UPDOWN_SHIFT))
#define TimerTestMode_COUNT_UPDOWN0                  ((uint32)(TimerTestMode__COUNT_UPDOWN0   <<  \
                                                                  TimerTestMode_UPDOWN_SHIFT))
#define TimerTestMode_COUNT_UPDOWN1                  ((uint32)(TimerTestMode__COUNT_UPDOWN1   <<  \
                                                                  TimerTestMode_UPDOWN_SHIFT))

/* PWM output invert */
#define TimerTestMode_INVERT_LINE                    ((uint32)(TimerTestMode__INVERSE         <<  \
                                                                  TimerTestMode_INV_OUT_SHIFT))
#define TimerTestMode_INVERT_LINE_N                  ((uint32)(TimerTestMode__INVERSE         <<  \
                                                                  TimerTestMode_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define TimerTestMode_TRIG_RISING                    ((uint32)TimerTestMode__TRIG_RISING)
#define TimerTestMode_TRIG_FALLING                   ((uint32)TimerTestMode__TRIG_FALLING)
#define TimerTestMode_TRIG_BOTH                      ((uint32)TimerTestMode__TRIG_BOTH)
#define TimerTestMode_TRIG_LEVEL                     ((uint32)TimerTestMode__TRIG_LEVEL)

/* Interrupt mask */
#define TimerTestMode_INTR_MASK_TC                   ((uint32)TimerTestMode__INTR_MASK_TC)
#define TimerTestMode_INTR_MASK_CC_MATCH             ((uint32)TimerTestMode__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define TimerTestMode_CC_MATCH_SET                   (0x00u)
#define TimerTestMode_CC_MATCH_CLEAR                 (0x01u)
#define TimerTestMode_CC_MATCH_INVERT                (0x02u)
#define TimerTestMode_CC_MATCH_NO_CHANGE             (0x03u)
#define TimerTestMode_OVERLOW_SET                    (0x00u)
#define TimerTestMode_OVERLOW_CLEAR                  (0x04u)
#define TimerTestMode_OVERLOW_INVERT                 (0x08u)
#define TimerTestMode_OVERLOW_NO_CHANGE              (0x0Cu)
#define TimerTestMode_UNDERFLOW_SET                  (0x00u)
#define TimerTestMode_UNDERFLOW_CLEAR                (0x10u)
#define TimerTestMode_UNDERFLOW_INVERT               (0x20u)
#define TimerTestMode_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define TimerTestMode_PWM_MODE_LEFT                  (TimerTestMode_CC_MATCH_CLEAR        |   \
                                                         TimerTestMode_OVERLOW_SET           |   \
                                                         TimerTestMode_UNDERFLOW_NO_CHANGE)
#define TimerTestMode_PWM_MODE_RIGHT                 (TimerTestMode_CC_MATCH_SET          |   \
                                                         TimerTestMode_OVERLOW_NO_CHANGE     |   \
                                                         TimerTestMode_UNDERFLOW_CLEAR)
#define TimerTestMode_PWM_MODE_ASYM                  (TimerTestMode_CC_MATCH_INVERT       |   \
                                                         TimerTestMode_OVERLOW_SET           |   \
                                                         TimerTestMode_UNDERFLOW_CLEAR)

#if (TimerTestMode_CY_TCPWM_V2)
    #if(TimerTestMode_CY_TCPWM_4000)
        #define TimerTestMode_PWM_MODE_CENTER                (TimerTestMode_CC_MATCH_INVERT       |   \
                                                                 TimerTestMode_OVERLOW_NO_CHANGE     |   \
                                                                 TimerTestMode_UNDERFLOW_CLEAR)
    #else
        #define TimerTestMode_PWM_MODE_CENTER                (TimerTestMode_CC_MATCH_INVERT       |   \
                                                                 TimerTestMode_OVERLOW_SET           |   \
                                                                 TimerTestMode_UNDERFLOW_CLEAR)
    #endif /* (TimerTestMode_CY_TCPWM_4000) */
#else
    #define TimerTestMode_PWM_MODE_CENTER                (TimerTestMode_CC_MATCH_INVERT       |   \
                                                             TimerTestMode_OVERLOW_NO_CHANGE     |   \
                                                             TimerTestMode_UNDERFLOW_CLEAR)
#endif /* (TimerTestMode_CY_TCPWM_NEW) */

/* Command operations without condition */
#define TimerTestMode_CMD_CAPTURE                    (0u)
#define TimerTestMode_CMD_RELOAD                     (8u)
#define TimerTestMode_CMD_STOP                       (16u)
#define TimerTestMode_CMD_START                      (24u)

/* Status */
#define TimerTestMode_STATUS_DOWN                    (1u)
#define TimerTestMode_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   TimerTestMode_Init(void);
void   TimerTestMode_Enable(void);
void   TimerTestMode_Start(void);
void   TimerTestMode_Stop(void);

void   TimerTestMode_SetMode(uint32 mode);
void   TimerTestMode_SetCounterMode(uint32 counterMode);
void   TimerTestMode_SetPWMMode(uint32 modeMask);
void   TimerTestMode_SetQDMode(uint32 qdMode);

void   TimerTestMode_SetPrescaler(uint32 prescaler);
void   TimerTestMode_TriggerCommand(uint32 mask, uint32 command);
void   TimerTestMode_SetOneShot(uint32 oneShotEnable);
uint32 TimerTestMode_ReadStatus(void);

void   TimerTestMode_SetPWMSyncKill(uint32 syncKillEnable);
void   TimerTestMode_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   TimerTestMode_SetPWMDeadTime(uint32 deadTime);
void   TimerTestMode_SetPWMInvert(uint32 mask);

void   TimerTestMode_SetInterruptMode(uint32 interruptMask);
uint32 TimerTestMode_GetInterruptSourceMasked(void);
uint32 TimerTestMode_GetInterruptSource(void);
void   TimerTestMode_ClearInterrupt(uint32 interruptMask);
void   TimerTestMode_SetInterrupt(uint32 interruptMask);

void   TimerTestMode_WriteCounter(uint32 count);
uint32 TimerTestMode_ReadCounter(void);

uint32 TimerTestMode_ReadCapture(void);
uint32 TimerTestMode_ReadCaptureBuf(void);

void   TimerTestMode_WritePeriod(uint32 period);
uint32 TimerTestMode_ReadPeriod(void);
void   TimerTestMode_WritePeriodBuf(uint32 periodBuf);
uint32 TimerTestMode_ReadPeriodBuf(void);

void   TimerTestMode_WriteCompare(uint32 compare);
uint32 TimerTestMode_ReadCompare(void);
void   TimerTestMode_WriteCompareBuf(uint32 compareBuf);
uint32 TimerTestMode_ReadCompareBuf(void);

void   TimerTestMode_SetPeriodSwap(uint32 swapEnable);
void   TimerTestMode_SetCompareSwap(uint32 swapEnable);

void   TimerTestMode_SetCaptureMode(uint32 triggerMode);
void   TimerTestMode_SetReloadMode(uint32 triggerMode);
void   TimerTestMode_SetStartMode(uint32 triggerMode);
void   TimerTestMode_SetStopMode(uint32 triggerMode);
void   TimerTestMode_SetCountMode(uint32 triggerMode);

void   TimerTestMode_SaveConfig(void);
void   TimerTestMode_RestoreConfig(void);
void   TimerTestMode_Sleep(void);
void   TimerTestMode_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define TimerTestMode_BLOCK_CONTROL_REG              (*(reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define TimerTestMode_BLOCK_CONTROL_PTR              ( (reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define TimerTestMode_COMMAND_REG                    (*(reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define TimerTestMode_COMMAND_PTR                    ( (reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define TimerTestMode_INTRRUPT_CAUSE_REG             (*(reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define TimerTestMode_INTRRUPT_CAUSE_PTR             ( (reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define TimerTestMode_CONTROL_REG                    (*(reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__CTRL )
#define TimerTestMode_CONTROL_PTR                    ( (reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__CTRL )
#define TimerTestMode_STATUS_REG                     (*(reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__STATUS )
#define TimerTestMode_STATUS_PTR                     ( (reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__STATUS )
#define TimerTestMode_COUNTER_REG                    (*(reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__COUNTER )
#define TimerTestMode_COUNTER_PTR                    ( (reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__COUNTER )
#define TimerTestMode_COMP_CAP_REG                   (*(reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__CC )
#define TimerTestMode_COMP_CAP_PTR                   ( (reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__CC )
#define TimerTestMode_COMP_CAP_BUF_REG               (*(reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__CC_BUFF )
#define TimerTestMode_COMP_CAP_BUF_PTR               ( (reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__CC_BUFF )
#define TimerTestMode_PERIOD_REG                     (*(reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__PERIOD )
#define TimerTestMode_PERIOD_PTR                     ( (reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__PERIOD )
#define TimerTestMode_PERIOD_BUF_REG                 (*(reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define TimerTestMode_PERIOD_BUF_PTR                 ( (reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define TimerTestMode_TRIG_CONTROL0_REG              (*(reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define TimerTestMode_TRIG_CONTROL0_PTR              ( (reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define TimerTestMode_TRIG_CONTROL1_REG              (*(reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define TimerTestMode_TRIG_CONTROL1_PTR              ( (reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define TimerTestMode_TRIG_CONTROL2_REG              (*(reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define TimerTestMode_TRIG_CONTROL2_PTR              ( (reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define TimerTestMode_INTERRUPT_REQ_REG              (*(reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__INTR )
#define TimerTestMode_INTERRUPT_REQ_PTR              ( (reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__INTR )
#define TimerTestMode_INTERRUPT_SET_REG              (*(reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__INTR_SET )
#define TimerTestMode_INTERRUPT_SET_PTR              ( (reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__INTR_SET )
#define TimerTestMode_INTERRUPT_MASK_REG             (*(reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__INTR_MASK )
#define TimerTestMode_INTERRUPT_MASK_PTR             ( (reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__INTR_MASK )
#define TimerTestMode_INTERRUPT_MASKED_REG           (*(reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__INTR_MASKED )
#define TimerTestMode_INTERRUPT_MASKED_PTR           ( (reg32 *) TimerTestMode_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define TimerTestMode_MASK                           ((uint32)TimerTestMode_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define TimerTestMode_RELOAD_CC_SHIFT                (0u)
#define TimerTestMode_RELOAD_PERIOD_SHIFT            (1u)
#define TimerTestMode_PWM_SYNC_KILL_SHIFT            (2u)
#define TimerTestMode_PWM_STOP_KILL_SHIFT            (3u)
#define TimerTestMode_PRESCALER_SHIFT                (8u)
#define TimerTestMode_UPDOWN_SHIFT                   (16u)
#define TimerTestMode_ONESHOT_SHIFT                  (18u)
#define TimerTestMode_QUAD_MODE_SHIFT                (20u)
#define TimerTestMode_INV_OUT_SHIFT                  (20u)
#define TimerTestMode_INV_COMPL_OUT_SHIFT            (21u)
#define TimerTestMode_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define TimerTestMode_RELOAD_CC_MASK                 ((uint32)(TimerTestMode_1BIT_MASK        <<  \
                                                                            TimerTestMode_RELOAD_CC_SHIFT))
#define TimerTestMode_RELOAD_PERIOD_MASK             ((uint32)(TimerTestMode_1BIT_MASK        <<  \
                                                                            TimerTestMode_RELOAD_PERIOD_SHIFT))
#define TimerTestMode_PWM_SYNC_KILL_MASK             ((uint32)(TimerTestMode_1BIT_MASK        <<  \
                                                                            TimerTestMode_PWM_SYNC_KILL_SHIFT))
#define TimerTestMode_PWM_STOP_KILL_MASK             ((uint32)(TimerTestMode_1BIT_MASK        <<  \
                                                                            TimerTestMode_PWM_STOP_KILL_SHIFT))
#define TimerTestMode_PRESCALER_MASK                 ((uint32)(TimerTestMode_8BIT_MASK        <<  \
                                                                            TimerTestMode_PRESCALER_SHIFT))
#define TimerTestMode_UPDOWN_MASK                    ((uint32)(TimerTestMode_2BIT_MASK        <<  \
                                                                            TimerTestMode_UPDOWN_SHIFT))
#define TimerTestMode_ONESHOT_MASK                   ((uint32)(TimerTestMode_1BIT_MASK        <<  \
                                                                            TimerTestMode_ONESHOT_SHIFT))
#define TimerTestMode_QUAD_MODE_MASK                 ((uint32)(TimerTestMode_3BIT_MASK        <<  \
                                                                            TimerTestMode_QUAD_MODE_SHIFT))
#define TimerTestMode_INV_OUT_MASK                   ((uint32)(TimerTestMode_2BIT_MASK        <<  \
                                                                            TimerTestMode_INV_OUT_SHIFT))
#define TimerTestMode_MODE_MASK                      ((uint32)(TimerTestMode_3BIT_MASK        <<  \
                                                                            TimerTestMode_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define TimerTestMode_CAPTURE_SHIFT                  (0u)
#define TimerTestMode_COUNT_SHIFT                    (2u)
#define TimerTestMode_RELOAD_SHIFT                   (4u)
#define TimerTestMode_STOP_SHIFT                     (6u)
#define TimerTestMode_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define TimerTestMode_CAPTURE_MASK                   ((uint32)(TimerTestMode_2BIT_MASK        <<  \
                                                                  TimerTestMode_CAPTURE_SHIFT))
#define TimerTestMode_COUNT_MASK                     ((uint32)(TimerTestMode_2BIT_MASK        <<  \
                                                                  TimerTestMode_COUNT_SHIFT))
#define TimerTestMode_RELOAD_MASK                    ((uint32)(TimerTestMode_2BIT_MASK        <<  \
                                                                  TimerTestMode_RELOAD_SHIFT))
#define TimerTestMode_STOP_MASK                      ((uint32)(TimerTestMode_2BIT_MASK        <<  \
                                                                  TimerTestMode_STOP_SHIFT))
#define TimerTestMode_START_MASK                     ((uint32)(TimerTestMode_2BIT_MASK        <<  \
                                                                  TimerTestMode_START_SHIFT))

/* MASK */
#define TimerTestMode_1BIT_MASK                      ((uint32)0x01u)
#define TimerTestMode_2BIT_MASK                      ((uint32)0x03u)
#define TimerTestMode_3BIT_MASK                      ((uint32)0x07u)
#define TimerTestMode_6BIT_MASK                      ((uint32)0x3Fu)
#define TimerTestMode_8BIT_MASK                      ((uint32)0xFFu)
#define TimerTestMode_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define TimerTestMode_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define TimerTestMode_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(TimerTestMode_QUAD_ENCODING_MODES     << TimerTestMode_QUAD_MODE_SHIFT))       |\
         ((uint32)(TimerTestMode_CONFIG                  << TimerTestMode_MODE_SHIFT)))

#define TimerTestMode_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(TimerTestMode_PWM_STOP_EVENT          << TimerTestMode_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(TimerTestMode_PWM_OUT_INVERT          << TimerTestMode_INV_OUT_SHIFT))         |\
         ((uint32)(TimerTestMode_PWM_OUT_N_INVERT        << TimerTestMode_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(TimerTestMode_PWM_MODE                << TimerTestMode_MODE_SHIFT)))

#define TimerTestMode_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(TimerTestMode_PWM_RUN_MODE         << TimerTestMode_ONESHOT_SHIFT))
            
#define TimerTestMode_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(TimerTestMode_PWM_ALIGN            << TimerTestMode_UPDOWN_SHIFT))

#define TimerTestMode_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(TimerTestMode_PWM_KILL_EVENT      << TimerTestMode_PWM_SYNC_KILL_SHIFT))

#define TimerTestMode_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(TimerTestMode_PWM_DEAD_TIME_CYCLE  << TimerTestMode_PRESCALER_SHIFT))

#define TimerTestMode_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(TimerTestMode_PWM_PRESCALER        << TimerTestMode_PRESCALER_SHIFT))

#define TimerTestMode_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(TimerTestMode_TC_PRESCALER            << TimerTestMode_PRESCALER_SHIFT))       |\
         ((uint32)(TimerTestMode_TC_COUNTER_MODE         << TimerTestMode_UPDOWN_SHIFT))          |\
         ((uint32)(TimerTestMode_TC_RUN_MODE             << TimerTestMode_ONESHOT_SHIFT))         |\
         ((uint32)(TimerTestMode_TC_COMP_CAP_MODE        << TimerTestMode_MODE_SHIFT)))
        
#define TimerTestMode_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(TimerTestMode_QUAD_PHIA_SIGNAL_MODE   << TimerTestMode_COUNT_SHIFT))           |\
         ((uint32)(TimerTestMode_QUAD_INDEX_SIGNAL_MODE  << TimerTestMode_RELOAD_SHIFT))          |\
         ((uint32)(TimerTestMode_QUAD_STOP_SIGNAL_MODE   << TimerTestMode_STOP_SHIFT))            |\
         ((uint32)(TimerTestMode_QUAD_PHIB_SIGNAL_MODE   << TimerTestMode_START_SHIFT)))

#define TimerTestMode_PWM_SIGNALS_MODES                                                              \
        (((uint32)(TimerTestMode_PWM_SWITCH_SIGNAL_MODE  << TimerTestMode_CAPTURE_SHIFT))         |\
         ((uint32)(TimerTestMode_PWM_COUNT_SIGNAL_MODE   << TimerTestMode_COUNT_SHIFT))           |\
         ((uint32)(TimerTestMode_PWM_RELOAD_SIGNAL_MODE  << TimerTestMode_RELOAD_SHIFT))          |\
         ((uint32)(TimerTestMode_PWM_STOP_SIGNAL_MODE    << TimerTestMode_STOP_SHIFT))            |\
         ((uint32)(TimerTestMode_PWM_START_SIGNAL_MODE   << TimerTestMode_START_SHIFT)))

#define TimerTestMode_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(TimerTestMode_TC_CAPTURE_SIGNAL_MODE  << TimerTestMode_CAPTURE_SHIFT))         |\
         ((uint32)(TimerTestMode_TC_COUNT_SIGNAL_MODE    << TimerTestMode_COUNT_SHIFT))           |\
         ((uint32)(TimerTestMode_TC_RELOAD_SIGNAL_MODE   << TimerTestMode_RELOAD_SHIFT))          |\
         ((uint32)(TimerTestMode_TC_STOP_SIGNAL_MODE     << TimerTestMode_STOP_SHIFT))            |\
         ((uint32)(TimerTestMode_TC_START_SIGNAL_MODE    << TimerTestMode_START_SHIFT)))
        
#define TimerTestMode_TIMER_UPDOWN_CNT_USED                                                          \
                ((TimerTestMode__COUNT_UPDOWN0 == TimerTestMode_TC_COUNTER_MODE)                  ||\
                 (TimerTestMode__COUNT_UPDOWN1 == TimerTestMode_TC_COUNTER_MODE))

#define TimerTestMode_PWM_UPDOWN_CNT_USED                                                            \
                ((TimerTestMode__CENTER == TimerTestMode_PWM_ALIGN)                               ||\
                 (TimerTestMode__ASYMMETRIC == TimerTestMode_PWM_ALIGN))               
        
#define TimerTestMode_PWM_PR_INIT_VALUE              (1u)
#define TimerTestMode_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_TimerTestMode_H */

/* [] END OF FILE */
