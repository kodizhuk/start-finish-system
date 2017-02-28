/*******************************************************************************
* File Name: AppDelay.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the AppDelay
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

#if !defined(CY_TCPWM_AppDelay_H)
#define CY_TCPWM_AppDelay_H


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
} AppDelay_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  AppDelay_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define AppDelay_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define AppDelay_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define AppDelay_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define AppDelay_QUAD_ENCODING_MODES            (0lu)
#define AppDelay_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define AppDelay_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define AppDelay_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define AppDelay_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define AppDelay_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define AppDelay_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define AppDelay_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define AppDelay_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define AppDelay_TC_RUN_MODE                    (1lu)
#define AppDelay_TC_COUNTER_MODE                (1lu)
#define AppDelay_TC_COMP_CAP_MODE               (0lu)
#define AppDelay_TC_PRESCALER                   (0lu)

/* Signal modes */
#define AppDelay_TC_RELOAD_SIGNAL_MODE          (0lu)
#define AppDelay_TC_COUNT_SIGNAL_MODE           (3lu)
#define AppDelay_TC_START_SIGNAL_MODE           (0lu)
#define AppDelay_TC_STOP_SIGNAL_MODE            (0lu)
#define AppDelay_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define AppDelay_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define AppDelay_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define AppDelay_TC_START_SIGNAL_PRESENT        (0lu)
#define AppDelay_TC_STOP_SIGNAL_PRESENT         (0lu)
#define AppDelay_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define AppDelay_TC_INTERRUPT_MASK              (0lu)

/* PWM Mode */
/* Parameters */
#define AppDelay_PWM_KILL_EVENT                 (0lu)
#define AppDelay_PWM_STOP_EVENT                 (0lu)
#define AppDelay_PWM_MODE                       (4lu)
#define AppDelay_PWM_OUT_N_INVERT               (0lu)
#define AppDelay_PWM_OUT_INVERT                 (0lu)
#define AppDelay_PWM_ALIGN                      (0lu)
#define AppDelay_PWM_RUN_MODE                   (0lu)
#define AppDelay_PWM_DEAD_TIME_CYCLE            (0lu)
#define AppDelay_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define AppDelay_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define AppDelay_PWM_COUNT_SIGNAL_MODE          (3lu)
#define AppDelay_PWM_START_SIGNAL_MODE          (0lu)
#define AppDelay_PWM_STOP_SIGNAL_MODE           (0lu)
#define AppDelay_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define AppDelay_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define AppDelay_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define AppDelay_PWM_START_SIGNAL_PRESENT       (0lu)
#define AppDelay_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define AppDelay_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define AppDelay_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define AppDelay_TC_PERIOD_VALUE                (65000lu)
#define AppDelay_TC_COMPARE_VALUE               (65000lu)
#define AppDelay_TC_COMPARE_BUF_VALUE           (65535lu)
#define AppDelay_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define AppDelay_PWM_PERIOD_VALUE               (65535lu)
#define AppDelay_PWM_PERIOD_BUF_VALUE           (65535lu)
#define AppDelay_PWM_PERIOD_SWAP                (0lu)
#define AppDelay_PWM_COMPARE_VALUE              (65535lu)
#define AppDelay_PWM_COMPARE_BUF_VALUE          (65535lu)
#define AppDelay_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define AppDelay__LEFT 0
#define AppDelay__RIGHT 1
#define AppDelay__CENTER 2
#define AppDelay__ASYMMETRIC 3

#define AppDelay__X1 0
#define AppDelay__X2 1
#define AppDelay__X4 2

#define AppDelay__PWM 4
#define AppDelay__PWM_DT 5
#define AppDelay__PWM_PR 6

#define AppDelay__INVERSE 1
#define AppDelay__DIRECT 0

#define AppDelay__CAPTURE 2
#define AppDelay__COMPARE 0

#define AppDelay__TRIG_LEVEL 3
#define AppDelay__TRIG_RISING 0
#define AppDelay__TRIG_FALLING 1
#define AppDelay__TRIG_BOTH 2

#define AppDelay__INTR_MASK_TC 1
#define AppDelay__INTR_MASK_CC_MATCH 2
#define AppDelay__INTR_MASK_NONE 0
#define AppDelay__INTR_MASK_TC_CC 3

#define AppDelay__UNCONFIG 8
#define AppDelay__TIMER 1
#define AppDelay__QUAD 3
#define AppDelay__PWM_SEL 7

#define AppDelay__COUNT_UP 0
#define AppDelay__COUNT_DOWN 1
#define AppDelay__COUNT_UPDOWN0 2
#define AppDelay__COUNT_UPDOWN1 3


/* Prescaler */
#define AppDelay_PRESCALE_DIVBY1                ((uint32)(0u << AppDelay_PRESCALER_SHIFT))
#define AppDelay_PRESCALE_DIVBY2                ((uint32)(1u << AppDelay_PRESCALER_SHIFT))
#define AppDelay_PRESCALE_DIVBY4                ((uint32)(2u << AppDelay_PRESCALER_SHIFT))
#define AppDelay_PRESCALE_DIVBY8                ((uint32)(3u << AppDelay_PRESCALER_SHIFT))
#define AppDelay_PRESCALE_DIVBY16               ((uint32)(4u << AppDelay_PRESCALER_SHIFT))
#define AppDelay_PRESCALE_DIVBY32               ((uint32)(5u << AppDelay_PRESCALER_SHIFT))
#define AppDelay_PRESCALE_DIVBY64               ((uint32)(6u << AppDelay_PRESCALER_SHIFT))
#define AppDelay_PRESCALE_DIVBY128              ((uint32)(7u << AppDelay_PRESCALER_SHIFT))

/* TCPWM set modes */
#define AppDelay_MODE_TIMER_COMPARE             ((uint32)(AppDelay__COMPARE         <<  \
                                                                  AppDelay_MODE_SHIFT))
#define AppDelay_MODE_TIMER_CAPTURE             ((uint32)(AppDelay__CAPTURE         <<  \
                                                                  AppDelay_MODE_SHIFT))
#define AppDelay_MODE_QUAD                      ((uint32)(AppDelay__QUAD            <<  \
                                                                  AppDelay_MODE_SHIFT))
#define AppDelay_MODE_PWM                       ((uint32)(AppDelay__PWM             <<  \
                                                                  AppDelay_MODE_SHIFT))
#define AppDelay_MODE_PWM_DT                    ((uint32)(AppDelay__PWM_DT          <<  \
                                                                  AppDelay_MODE_SHIFT))
#define AppDelay_MODE_PWM_PR                    ((uint32)(AppDelay__PWM_PR          <<  \
                                                                  AppDelay_MODE_SHIFT))

/* Quad Modes */
#define AppDelay_MODE_X1                        ((uint32)(AppDelay__X1              <<  \
                                                                  AppDelay_QUAD_MODE_SHIFT))
#define AppDelay_MODE_X2                        ((uint32)(AppDelay__X2              <<  \
                                                                  AppDelay_QUAD_MODE_SHIFT))
#define AppDelay_MODE_X4                        ((uint32)(AppDelay__X4              <<  \
                                                                  AppDelay_QUAD_MODE_SHIFT))

/* Counter modes */
#define AppDelay_COUNT_UP                       ((uint32)(AppDelay__COUNT_UP        <<  \
                                                                  AppDelay_UPDOWN_SHIFT))
#define AppDelay_COUNT_DOWN                     ((uint32)(AppDelay__COUNT_DOWN      <<  \
                                                                  AppDelay_UPDOWN_SHIFT))
#define AppDelay_COUNT_UPDOWN0                  ((uint32)(AppDelay__COUNT_UPDOWN0   <<  \
                                                                  AppDelay_UPDOWN_SHIFT))
#define AppDelay_COUNT_UPDOWN1                  ((uint32)(AppDelay__COUNT_UPDOWN1   <<  \
                                                                  AppDelay_UPDOWN_SHIFT))

/* PWM output invert */
#define AppDelay_INVERT_LINE                    ((uint32)(AppDelay__INVERSE         <<  \
                                                                  AppDelay_INV_OUT_SHIFT))
#define AppDelay_INVERT_LINE_N                  ((uint32)(AppDelay__INVERSE         <<  \
                                                                  AppDelay_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define AppDelay_TRIG_RISING                    ((uint32)AppDelay__TRIG_RISING)
#define AppDelay_TRIG_FALLING                   ((uint32)AppDelay__TRIG_FALLING)
#define AppDelay_TRIG_BOTH                      ((uint32)AppDelay__TRIG_BOTH)
#define AppDelay_TRIG_LEVEL                     ((uint32)AppDelay__TRIG_LEVEL)

/* Interrupt mask */
#define AppDelay_INTR_MASK_TC                   ((uint32)AppDelay__INTR_MASK_TC)
#define AppDelay_INTR_MASK_CC_MATCH             ((uint32)AppDelay__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define AppDelay_CC_MATCH_SET                   (0x00u)
#define AppDelay_CC_MATCH_CLEAR                 (0x01u)
#define AppDelay_CC_MATCH_INVERT                (0x02u)
#define AppDelay_CC_MATCH_NO_CHANGE             (0x03u)
#define AppDelay_OVERLOW_SET                    (0x00u)
#define AppDelay_OVERLOW_CLEAR                  (0x04u)
#define AppDelay_OVERLOW_INVERT                 (0x08u)
#define AppDelay_OVERLOW_NO_CHANGE              (0x0Cu)
#define AppDelay_UNDERFLOW_SET                  (0x00u)
#define AppDelay_UNDERFLOW_CLEAR                (0x10u)
#define AppDelay_UNDERFLOW_INVERT               (0x20u)
#define AppDelay_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define AppDelay_PWM_MODE_LEFT                  (AppDelay_CC_MATCH_CLEAR        |   \
                                                         AppDelay_OVERLOW_SET           |   \
                                                         AppDelay_UNDERFLOW_NO_CHANGE)
#define AppDelay_PWM_MODE_RIGHT                 (AppDelay_CC_MATCH_SET          |   \
                                                         AppDelay_OVERLOW_NO_CHANGE     |   \
                                                         AppDelay_UNDERFLOW_CLEAR)
#define AppDelay_PWM_MODE_ASYM                  (AppDelay_CC_MATCH_INVERT       |   \
                                                         AppDelay_OVERLOW_SET           |   \
                                                         AppDelay_UNDERFLOW_CLEAR)

#if (AppDelay_CY_TCPWM_V2)
    #if(AppDelay_CY_TCPWM_4000)
        #define AppDelay_PWM_MODE_CENTER                (AppDelay_CC_MATCH_INVERT       |   \
                                                                 AppDelay_OVERLOW_NO_CHANGE     |   \
                                                                 AppDelay_UNDERFLOW_CLEAR)
    #else
        #define AppDelay_PWM_MODE_CENTER                (AppDelay_CC_MATCH_INVERT       |   \
                                                                 AppDelay_OVERLOW_SET           |   \
                                                                 AppDelay_UNDERFLOW_CLEAR)
    #endif /* (AppDelay_CY_TCPWM_4000) */
#else
    #define AppDelay_PWM_MODE_CENTER                (AppDelay_CC_MATCH_INVERT       |   \
                                                             AppDelay_OVERLOW_NO_CHANGE     |   \
                                                             AppDelay_UNDERFLOW_CLEAR)
#endif /* (AppDelay_CY_TCPWM_NEW) */

/* Command operations without condition */
#define AppDelay_CMD_CAPTURE                    (0u)
#define AppDelay_CMD_RELOAD                     (8u)
#define AppDelay_CMD_STOP                       (16u)
#define AppDelay_CMD_START                      (24u)

/* Status */
#define AppDelay_STATUS_DOWN                    (1u)
#define AppDelay_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   AppDelay_Init(void);
void   AppDelay_Enable(void);
void   AppDelay_Start(void);
void   AppDelay_Stop(void);

void   AppDelay_SetMode(uint32 mode);
void   AppDelay_SetCounterMode(uint32 counterMode);
void   AppDelay_SetPWMMode(uint32 modeMask);
void   AppDelay_SetQDMode(uint32 qdMode);

void   AppDelay_SetPrescaler(uint32 prescaler);
void   AppDelay_TriggerCommand(uint32 mask, uint32 command);
void   AppDelay_SetOneShot(uint32 oneShotEnable);
uint32 AppDelay_ReadStatus(void);

void   AppDelay_SetPWMSyncKill(uint32 syncKillEnable);
void   AppDelay_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   AppDelay_SetPWMDeadTime(uint32 deadTime);
void   AppDelay_SetPWMInvert(uint32 mask);

void   AppDelay_SetInterruptMode(uint32 interruptMask);
uint32 AppDelay_GetInterruptSourceMasked(void);
uint32 AppDelay_GetInterruptSource(void);
void   AppDelay_ClearInterrupt(uint32 interruptMask);
void   AppDelay_SetInterrupt(uint32 interruptMask);

void   AppDelay_WriteCounter(uint32 count);
uint32 AppDelay_ReadCounter(void);

uint32 AppDelay_ReadCapture(void);
uint32 AppDelay_ReadCaptureBuf(void);

void   AppDelay_WritePeriod(uint32 period);
uint32 AppDelay_ReadPeriod(void);
void   AppDelay_WritePeriodBuf(uint32 periodBuf);
uint32 AppDelay_ReadPeriodBuf(void);

void   AppDelay_WriteCompare(uint32 compare);
uint32 AppDelay_ReadCompare(void);
void   AppDelay_WriteCompareBuf(uint32 compareBuf);
uint32 AppDelay_ReadCompareBuf(void);

void   AppDelay_SetPeriodSwap(uint32 swapEnable);
void   AppDelay_SetCompareSwap(uint32 swapEnable);

void   AppDelay_SetCaptureMode(uint32 triggerMode);
void   AppDelay_SetReloadMode(uint32 triggerMode);
void   AppDelay_SetStartMode(uint32 triggerMode);
void   AppDelay_SetStopMode(uint32 triggerMode);
void   AppDelay_SetCountMode(uint32 triggerMode);

void   AppDelay_SaveConfig(void);
void   AppDelay_RestoreConfig(void);
void   AppDelay_Sleep(void);
void   AppDelay_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define AppDelay_BLOCK_CONTROL_REG              (*(reg32 *) AppDelay_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define AppDelay_BLOCK_CONTROL_PTR              ( (reg32 *) AppDelay_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define AppDelay_COMMAND_REG                    (*(reg32 *) AppDelay_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define AppDelay_COMMAND_PTR                    ( (reg32 *) AppDelay_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define AppDelay_INTRRUPT_CAUSE_REG             (*(reg32 *) AppDelay_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define AppDelay_INTRRUPT_CAUSE_PTR             ( (reg32 *) AppDelay_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define AppDelay_CONTROL_REG                    (*(reg32 *) AppDelay_cy_m0s8_tcpwm_1__CTRL )
#define AppDelay_CONTROL_PTR                    ( (reg32 *) AppDelay_cy_m0s8_tcpwm_1__CTRL )
#define AppDelay_STATUS_REG                     (*(reg32 *) AppDelay_cy_m0s8_tcpwm_1__STATUS )
#define AppDelay_STATUS_PTR                     ( (reg32 *) AppDelay_cy_m0s8_tcpwm_1__STATUS )
#define AppDelay_COUNTER_REG                    (*(reg32 *) AppDelay_cy_m0s8_tcpwm_1__COUNTER )
#define AppDelay_COUNTER_PTR                    ( (reg32 *) AppDelay_cy_m0s8_tcpwm_1__COUNTER )
#define AppDelay_COMP_CAP_REG                   (*(reg32 *) AppDelay_cy_m0s8_tcpwm_1__CC )
#define AppDelay_COMP_CAP_PTR                   ( (reg32 *) AppDelay_cy_m0s8_tcpwm_1__CC )
#define AppDelay_COMP_CAP_BUF_REG               (*(reg32 *) AppDelay_cy_m0s8_tcpwm_1__CC_BUFF )
#define AppDelay_COMP_CAP_BUF_PTR               ( (reg32 *) AppDelay_cy_m0s8_tcpwm_1__CC_BUFF )
#define AppDelay_PERIOD_REG                     (*(reg32 *) AppDelay_cy_m0s8_tcpwm_1__PERIOD )
#define AppDelay_PERIOD_PTR                     ( (reg32 *) AppDelay_cy_m0s8_tcpwm_1__PERIOD )
#define AppDelay_PERIOD_BUF_REG                 (*(reg32 *) AppDelay_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define AppDelay_PERIOD_BUF_PTR                 ( (reg32 *) AppDelay_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define AppDelay_TRIG_CONTROL0_REG              (*(reg32 *) AppDelay_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define AppDelay_TRIG_CONTROL0_PTR              ( (reg32 *) AppDelay_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define AppDelay_TRIG_CONTROL1_REG              (*(reg32 *) AppDelay_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define AppDelay_TRIG_CONTROL1_PTR              ( (reg32 *) AppDelay_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define AppDelay_TRIG_CONTROL2_REG              (*(reg32 *) AppDelay_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define AppDelay_TRIG_CONTROL2_PTR              ( (reg32 *) AppDelay_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define AppDelay_INTERRUPT_REQ_REG              (*(reg32 *) AppDelay_cy_m0s8_tcpwm_1__INTR )
#define AppDelay_INTERRUPT_REQ_PTR              ( (reg32 *) AppDelay_cy_m0s8_tcpwm_1__INTR )
#define AppDelay_INTERRUPT_SET_REG              (*(reg32 *) AppDelay_cy_m0s8_tcpwm_1__INTR_SET )
#define AppDelay_INTERRUPT_SET_PTR              ( (reg32 *) AppDelay_cy_m0s8_tcpwm_1__INTR_SET )
#define AppDelay_INTERRUPT_MASK_REG             (*(reg32 *) AppDelay_cy_m0s8_tcpwm_1__INTR_MASK )
#define AppDelay_INTERRUPT_MASK_PTR             ( (reg32 *) AppDelay_cy_m0s8_tcpwm_1__INTR_MASK )
#define AppDelay_INTERRUPT_MASKED_REG           (*(reg32 *) AppDelay_cy_m0s8_tcpwm_1__INTR_MASKED )
#define AppDelay_INTERRUPT_MASKED_PTR           ( (reg32 *) AppDelay_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define AppDelay_MASK                           ((uint32)AppDelay_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define AppDelay_RELOAD_CC_SHIFT                (0u)
#define AppDelay_RELOAD_PERIOD_SHIFT            (1u)
#define AppDelay_PWM_SYNC_KILL_SHIFT            (2u)
#define AppDelay_PWM_STOP_KILL_SHIFT            (3u)
#define AppDelay_PRESCALER_SHIFT                (8u)
#define AppDelay_UPDOWN_SHIFT                   (16u)
#define AppDelay_ONESHOT_SHIFT                  (18u)
#define AppDelay_QUAD_MODE_SHIFT                (20u)
#define AppDelay_INV_OUT_SHIFT                  (20u)
#define AppDelay_INV_COMPL_OUT_SHIFT            (21u)
#define AppDelay_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define AppDelay_RELOAD_CC_MASK                 ((uint32)(AppDelay_1BIT_MASK        <<  \
                                                                            AppDelay_RELOAD_CC_SHIFT))
#define AppDelay_RELOAD_PERIOD_MASK             ((uint32)(AppDelay_1BIT_MASK        <<  \
                                                                            AppDelay_RELOAD_PERIOD_SHIFT))
#define AppDelay_PWM_SYNC_KILL_MASK             ((uint32)(AppDelay_1BIT_MASK        <<  \
                                                                            AppDelay_PWM_SYNC_KILL_SHIFT))
#define AppDelay_PWM_STOP_KILL_MASK             ((uint32)(AppDelay_1BIT_MASK        <<  \
                                                                            AppDelay_PWM_STOP_KILL_SHIFT))
#define AppDelay_PRESCALER_MASK                 ((uint32)(AppDelay_8BIT_MASK        <<  \
                                                                            AppDelay_PRESCALER_SHIFT))
#define AppDelay_UPDOWN_MASK                    ((uint32)(AppDelay_2BIT_MASK        <<  \
                                                                            AppDelay_UPDOWN_SHIFT))
#define AppDelay_ONESHOT_MASK                   ((uint32)(AppDelay_1BIT_MASK        <<  \
                                                                            AppDelay_ONESHOT_SHIFT))
#define AppDelay_QUAD_MODE_MASK                 ((uint32)(AppDelay_3BIT_MASK        <<  \
                                                                            AppDelay_QUAD_MODE_SHIFT))
#define AppDelay_INV_OUT_MASK                   ((uint32)(AppDelay_2BIT_MASK        <<  \
                                                                            AppDelay_INV_OUT_SHIFT))
#define AppDelay_MODE_MASK                      ((uint32)(AppDelay_3BIT_MASK        <<  \
                                                                            AppDelay_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define AppDelay_CAPTURE_SHIFT                  (0u)
#define AppDelay_COUNT_SHIFT                    (2u)
#define AppDelay_RELOAD_SHIFT                   (4u)
#define AppDelay_STOP_SHIFT                     (6u)
#define AppDelay_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define AppDelay_CAPTURE_MASK                   ((uint32)(AppDelay_2BIT_MASK        <<  \
                                                                  AppDelay_CAPTURE_SHIFT))
#define AppDelay_COUNT_MASK                     ((uint32)(AppDelay_2BIT_MASK        <<  \
                                                                  AppDelay_COUNT_SHIFT))
#define AppDelay_RELOAD_MASK                    ((uint32)(AppDelay_2BIT_MASK        <<  \
                                                                  AppDelay_RELOAD_SHIFT))
#define AppDelay_STOP_MASK                      ((uint32)(AppDelay_2BIT_MASK        <<  \
                                                                  AppDelay_STOP_SHIFT))
#define AppDelay_START_MASK                     ((uint32)(AppDelay_2BIT_MASK        <<  \
                                                                  AppDelay_START_SHIFT))

/* MASK */
#define AppDelay_1BIT_MASK                      ((uint32)0x01u)
#define AppDelay_2BIT_MASK                      ((uint32)0x03u)
#define AppDelay_3BIT_MASK                      ((uint32)0x07u)
#define AppDelay_6BIT_MASK                      ((uint32)0x3Fu)
#define AppDelay_8BIT_MASK                      ((uint32)0xFFu)
#define AppDelay_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define AppDelay_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define AppDelay_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(AppDelay_QUAD_ENCODING_MODES     << AppDelay_QUAD_MODE_SHIFT))       |\
         ((uint32)(AppDelay_CONFIG                  << AppDelay_MODE_SHIFT)))

#define AppDelay_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(AppDelay_PWM_STOP_EVENT          << AppDelay_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(AppDelay_PWM_OUT_INVERT          << AppDelay_INV_OUT_SHIFT))         |\
         ((uint32)(AppDelay_PWM_OUT_N_INVERT        << AppDelay_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(AppDelay_PWM_MODE                << AppDelay_MODE_SHIFT)))

#define AppDelay_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(AppDelay_PWM_RUN_MODE         << AppDelay_ONESHOT_SHIFT))
            
#define AppDelay_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(AppDelay_PWM_ALIGN            << AppDelay_UPDOWN_SHIFT))

#define AppDelay_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(AppDelay_PWM_KILL_EVENT      << AppDelay_PWM_SYNC_KILL_SHIFT))

#define AppDelay_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(AppDelay_PWM_DEAD_TIME_CYCLE  << AppDelay_PRESCALER_SHIFT))

#define AppDelay_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(AppDelay_PWM_PRESCALER        << AppDelay_PRESCALER_SHIFT))

#define AppDelay_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(AppDelay_TC_PRESCALER            << AppDelay_PRESCALER_SHIFT))       |\
         ((uint32)(AppDelay_TC_COUNTER_MODE         << AppDelay_UPDOWN_SHIFT))          |\
         ((uint32)(AppDelay_TC_RUN_MODE             << AppDelay_ONESHOT_SHIFT))         |\
         ((uint32)(AppDelay_TC_COMP_CAP_MODE        << AppDelay_MODE_SHIFT)))
        
#define AppDelay_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(AppDelay_QUAD_PHIA_SIGNAL_MODE   << AppDelay_COUNT_SHIFT))           |\
         ((uint32)(AppDelay_QUAD_INDEX_SIGNAL_MODE  << AppDelay_RELOAD_SHIFT))          |\
         ((uint32)(AppDelay_QUAD_STOP_SIGNAL_MODE   << AppDelay_STOP_SHIFT))            |\
         ((uint32)(AppDelay_QUAD_PHIB_SIGNAL_MODE   << AppDelay_START_SHIFT)))

#define AppDelay_PWM_SIGNALS_MODES                                                              \
        (((uint32)(AppDelay_PWM_SWITCH_SIGNAL_MODE  << AppDelay_CAPTURE_SHIFT))         |\
         ((uint32)(AppDelay_PWM_COUNT_SIGNAL_MODE   << AppDelay_COUNT_SHIFT))           |\
         ((uint32)(AppDelay_PWM_RELOAD_SIGNAL_MODE  << AppDelay_RELOAD_SHIFT))          |\
         ((uint32)(AppDelay_PWM_STOP_SIGNAL_MODE    << AppDelay_STOP_SHIFT))            |\
         ((uint32)(AppDelay_PWM_START_SIGNAL_MODE   << AppDelay_START_SHIFT)))

#define AppDelay_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(AppDelay_TC_CAPTURE_SIGNAL_MODE  << AppDelay_CAPTURE_SHIFT))         |\
         ((uint32)(AppDelay_TC_COUNT_SIGNAL_MODE    << AppDelay_COUNT_SHIFT))           |\
         ((uint32)(AppDelay_TC_RELOAD_SIGNAL_MODE   << AppDelay_RELOAD_SHIFT))          |\
         ((uint32)(AppDelay_TC_STOP_SIGNAL_MODE     << AppDelay_STOP_SHIFT))            |\
         ((uint32)(AppDelay_TC_START_SIGNAL_MODE    << AppDelay_START_SHIFT)))
        
#define AppDelay_TIMER_UPDOWN_CNT_USED                                                          \
                ((AppDelay__COUNT_UPDOWN0 == AppDelay_TC_COUNTER_MODE)                  ||\
                 (AppDelay__COUNT_UPDOWN1 == AppDelay_TC_COUNTER_MODE))

#define AppDelay_PWM_UPDOWN_CNT_USED                                                            \
                ((AppDelay__CENTER == AppDelay_PWM_ALIGN)                               ||\
                 (AppDelay__ASYMMETRIC == AppDelay_PWM_ALIGN))               
        
#define AppDelay_PWM_PR_INIT_VALUE              (1u)
#define AppDelay_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_AppDelay_H */

/* [] END OF FILE */
