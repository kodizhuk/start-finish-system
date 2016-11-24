/*******************************************************************************
* File Name: AppDelay.h
* Version 2.70
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_Timer_v2_60_AppDelay_H)
#define CY_Timer_v2_60_AppDelay_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 AppDelay_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_70 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define AppDelay_Resolution                 24u
#define AppDelay_UsingFixedFunction         0u
#define AppDelay_UsingHWCaptureCounter      0u
#define AppDelay_SoftwareCaptureMode        0u
#define AppDelay_SoftwareTriggerMode        0u
#define AppDelay_UsingHWEnable              0u
#define AppDelay_EnableTriggerMode          0u
#define AppDelay_InterruptOnCaptureCount    0u
#define AppDelay_RunModeUsed                1u
#define AppDelay_ControlRegRemoved          0u

#if defined(AppDelay_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define AppDelay_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (AppDelay_UsingFixedFunction)
    #define AppDelay_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define AppDelay_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End AppDelay_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!AppDelay_UsingFixedFunction)

        uint32 TimerUdb;
        uint8 InterruptMaskValue;
        #if (AppDelay_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!AppDelay_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}AppDelay_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    AppDelay_Start(void) ;
void    AppDelay_Stop(void) ;

void    AppDelay_SetInterruptMode(uint8 interruptMode) ;
uint8   AppDelay_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define AppDelay_GetInterruptSource() AppDelay_ReadStatusRegister()

#if(!AppDelay_UDB_CONTROL_REG_REMOVED)
    uint8   AppDelay_ReadControlRegister(void) ;
    void    AppDelay_WriteControlRegister(uint8 control) ;
#endif /* (!AppDelay_UDB_CONTROL_REG_REMOVED) */

uint32  AppDelay_ReadPeriod(void) ;
void    AppDelay_WritePeriod(uint32 period) ;
uint32  AppDelay_ReadCounter(void) ;
void    AppDelay_WriteCounter(uint32 counter) ;
uint32  AppDelay_ReadCapture(void) ;
void    AppDelay_SoftwareCapture(void) ;

#if(!AppDelay_UsingFixedFunction) /* UDB Prototypes */
    #if (AppDelay_SoftwareCaptureMode)
        void    AppDelay_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!AppDelay_UsingFixedFunction) */

    #if (AppDelay_SoftwareTriggerMode)
        void    AppDelay_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (AppDelay_SoftwareTriggerMode) */

    #if (AppDelay_EnableTriggerMode)
        void    AppDelay_EnableTrigger(void) ;
        void    AppDelay_DisableTrigger(void) ;
    #endif /* (AppDelay_EnableTriggerMode) */


    #if(AppDelay_InterruptOnCaptureCount)
        void    AppDelay_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (AppDelay_InterruptOnCaptureCount) */

    #if (AppDelay_UsingHWCaptureCounter)
        void    AppDelay_SetCaptureCount(uint8 captureCount) ;
        uint8   AppDelay_ReadCaptureCount(void) ;
    #endif /* (AppDelay_UsingHWCaptureCounter) */

    void AppDelay_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void AppDelay_Init(void)          ;
void AppDelay_Enable(void)        ;
void AppDelay_SaveConfig(void)    ;
void AppDelay_RestoreConfig(void) ;
void AppDelay_Sleep(void)         ;
void AppDelay_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define AppDelay__B_TIMER__CM_NONE 0
#define AppDelay__B_TIMER__CM_RISINGEDGE 1
#define AppDelay__B_TIMER__CM_FALLINGEDGE 2
#define AppDelay__B_TIMER__CM_EITHEREDGE 3
#define AppDelay__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define AppDelay__B_TIMER__TM_NONE 0x00u
#define AppDelay__B_TIMER__TM_RISINGEDGE 0x04u
#define AppDelay__B_TIMER__TM_FALLINGEDGE 0x08u
#define AppDelay__B_TIMER__TM_EITHEREDGE 0x0Cu
#define AppDelay__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define AppDelay_INIT_PERIOD             131071u
#define AppDelay_INIT_CAPTURE_MODE       ((uint8)((uint8)0u << AppDelay_CTRL_CAP_MODE_SHIFT))
#define AppDelay_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << AppDelay_CTRL_TRIG_MODE_SHIFT))
#if (AppDelay_UsingFixedFunction)
    #define AppDelay_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << AppDelay_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << AppDelay_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define AppDelay_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << AppDelay_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << AppDelay_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << AppDelay_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (AppDelay_UsingFixedFunction) */
#define AppDelay_INIT_CAPTURE_COUNT      (10u)
#define AppDelay_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << AppDelay_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (AppDelay_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define AppDelay_STATUS         (*(reg8 *) AppDelay_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define AppDelay_STATUS_MASK    (*(reg8 *) AppDelay_TimerHW__SR0 )
    #define AppDelay_CONTROL        (*(reg8 *) AppDelay_TimerHW__CFG0)
    #define AppDelay_CONTROL2       (*(reg8 *) AppDelay_TimerHW__CFG1)
    #define AppDelay_CONTROL2_PTR   ( (reg8 *) AppDelay_TimerHW__CFG1)
    #define AppDelay_RT1            (*(reg8 *) AppDelay_TimerHW__RT1)
    #define AppDelay_RT1_PTR        ( (reg8 *) AppDelay_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define AppDelay_CONTROL3       (*(reg8 *) AppDelay_TimerHW__CFG2)
        #define AppDelay_CONTROL3_PTR   ( (reg8 *) AppDelay_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define AppDelay_GLOBAL_ENABLE  (*(reg8 *) AppDelay_TimerHW__PM_ACT_CFG)
    #define AppDelay_GLOBAL_STBY_ENABLE  (*(reg8 *) AppDelay_TimerHW__PM_STBY_CFG)

    #define AppDelay_CAPTURE_LSB         (* (reg16 *) AppDelay_TimerHW__CAP0 )
    #define AppDelay_CAPTURE_LSB_PTR       ((reg16 *) AppDelay_TimerHW__CAP0 )
    #define AppDelay_PERIOD_LSB          (* (reg16 *) AppDelay_TimerHW__PER0 )
    #define AppDelay_PERIOD_LSB_PTR        ((reg16 *) AppDelay_TimerHW__PER0 )
    #define AppDelay_COUNTER_LSB         (* (reg16 *) AppDelay_TimerHW__CNT_CMP0 )
    #define AppDelay_COUNTER_LSB_PTR       ((reg16 *) AppDelay_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define AppDelay_BLOCK_EN_MASK                     AppDelay_TimerHW__PM_ACT_MSK
    #define AppDelay_BLOCK_STBY_EN_MASK                AppDelay_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define AppDelay_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define AppDelay_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define AppDelay_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define AppDelay_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define AppDelay_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define AppDelay_CTRL_ENABLE                        ((uint8)((uint8)0x01u << AppDelay_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define AppDelay_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define AppDelay_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << AppDelay_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define AppDelay_CTRL_MODE_SHIFT                 0x01u
        #define AppDelay_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << AppDelay_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define AppDelay_CTRL_RCOD_SHIFT        0x02u
        #define AppDelay_CTRL_ENBL_SHIFT        0x00u
        #define AppDelay_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define AppDelay_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << AppDelay_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define AppDelay_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << AppDelay_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define AppDelay_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << AppDelay_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define AppDelay_CTRL_RCOD       ((uint8)((uint8)0x03u << AppDelay_CTRL_RCOD_SHIFT))
        #define AppDelay_CTRL_ENBL       ((uint8)((uint8)0x80u << AppDelay_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define AppDelay_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define AppDelay_RT1_MASK                        ((uint8)((uint8)0x03u << AppDelay_RT1_SHIFT))
    #define AppDelay_SYNC                            ((uint8)((uint8)0x03u << AppDelay_RT1_SHIFT))
    #define AppDelay_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define AppDelay_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << AppDelay_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define AppDelay_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << AppDelay_SYNCDSI_SHIFT))

    #define AppDelay_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << AppDelay_CTRL_MODE_SHIFT))
    #define AppDelay_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << AppDelay_CTRL_MODE_SHIFT))
    #define AppDelay_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << AppDelay_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define AppDelay_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define AppDelay_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define AppDelay_STATUS_TC_INT_MASK_SHIFT        (AppDelay_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define AppDelay_STATUS_CAPTURE_INT_MASK_SHIFT   (AppDelay_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define AppDelay_STATUS_TC                       ((uint8)((uint8)0x01u << AppDelay_STATUS_TC_SHIFT))
    #define AppDelay_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << AppDelay_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define AppDelay_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << AppDelay_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define AppDelay_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << AppDelay_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define AppDelay_STATUS              (* (reg8 *) AppDelay_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define AppDelay_STATUS_MASK         (* (reg8 *) AppDelay_TimerUDB_rstSts_stsreg__MASK_REG)
    #define AppDelay_STATUS_AUX_CTRL     (* (reg8 *) AppDelay_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define AppDelay_CONTROL             (* (reg8 *) AppDelay_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(AppDelay_Resolution <= 8u) /* 8-bit Timer */
        #define AppDelay_CAPTURE_LSB         (* (reg8 *) AppDelay_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define AppDelay_CAPTURE_LSB_PTR       ((reg8 *) AppDelay_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define AppDelay_PERIOD_LSB          (* (reg8 *) AppDelay_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define AppDelay_PERIOD_LSB_PTR        ((reg8 *) AppDelay_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define AppDelay_COUNTER_LSB         (* (reg8 *) AppDelay_TimerUDB_sT24_timerdp_u0__A0_REG )
        #define AppDelay_COUNTER_LSB_PTR       ((reg8 *) AppDelay_TimerUDB_sT24_timerdp_u0__A0_REG )
    #elif(AppDelay_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define AppDelay_CAPTURE_LSB         (* (reg16 *) AppDelay_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define AppDelay_CAPTURE_LSB_PTR       ((reg16 *) AppDelay_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define AppDelay_PERIOD_LSB          (* (reg16 *) AppDelay_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define AppDelay_PERIOD_LSB_PTR        ((reg16 *) AppDelay_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define AppDelay_COUNTER_LSB         (* (reg16 *) AppDelay_TimerUDB_sT24_timerdp_u0__A0_REG )
            #define AppDelay_COUNTER_LSB_PTR       ((reg16 *) AppDelay_TimerUDB_sT24_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define AppDelay_CAPTURE_LSB         (* (reg16 *) AppDelay_TimerUDB_sT24_timerdp_u0__16BIT_F0_REG )
            #define AppDelay_CAPTURE_LSB_PTR       ((reg16 *) AppDelay_TimerUDB_sT24_timerdp_u0__16BIT_F0_REG )
            #define AppDelay_PERIOD_LSB          (* (reg16 *) AppDelay_TimerUDB_sT24_timerdp_u0__16BIT_D0_REG )
            #define AppDelay_PERIOD_LSB_PTR        ((reg16 *) AppDelay_TimerUDB_sT24_timerdp_u0__16BIT_D0_REG )
            #define AppDelay_COUNTER_LSB         (* (reg16 *) AppDelay_TimerUDB_sT24_timerdp_u0__16BIT_A0_REG )
            #define AppDelay_COUNTER_LSB_PTR       ((reg16 *) AppDelay_TimerUDB_sT24_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(AppDelay_Resolution <= 24u)/* 24-bit Timer */
        #define AppDelay_CAPTURE_LSB         (* (reg32 *) AppDelay_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define AppDelay_CAPTURE_LSB_PTR       ((reg32 *) AppDelay_TimerUDB_sT24_timerdp_u0__F0_REG )
        #define AppDelay_PERIOD_LSB          (* (reg32 *) AppDelay_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define AppDelay_PERIOD_LSB_PTR        ((reg32 *) AppDelay_TimerUDB_sT24_timerdp_u0__D0_REG )
        #define AppDelay_COUNTER_LSB         (* (reg32 *) AppDelay_TimerUDB_sT24_timerdp_u0__A0_REG )
        #define AppDelay_COUNTER_LSB_PTR       ((reg32 *) AppDelay_TimerUDB_sT24_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define AppDelay_CAPTURE_LSB         (* (reg32 *) AppDelay_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define AppDelay_CAPTURE_LSB_PTR       ((reg32 *) AppDelay_TimerUDB_sT24_timerdp_u0__F0_REG )
            #define AppDelay_PERIOD_LSB          (* (reg32 *) AppDelay_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define AppDelay_PERIOD_LSB_PTR        ((reg32 *) AppDelay_TimerUDB_sT24_timerdp_u0__D0_REG )
            #define AppDelay_COUNTER_LSB         (* (reg32 *) AppDelay_TimerUDB_sT24_timerdp_u0__A0_REG )
            #define AppDelay_COUNTER_LSB_PTR       ((reg32 *) AppDelay_TimerUDB_sT24_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define AppDelay_CAPTURE_LSB         (* (reg32 *) AppDelay_TimerUDB_sT24_timerdp_u0__32BIT_F0_REG )
            #define AppDelay_CAPTURE_LSB_PTR       ((reg32 *) AppDelay_TimerUDB_sT24_timerdp_u0__32BIT_F0_REG )
            #define AppDelay_PERIOD_LSB          (* (reg32 *) AppDelay_TimerUDB_sT24_timerdp_u0__32BIT_D0_REG )
            #define AppDelay_PERIOD_LSB_PTR        ((reg32 *) AppDelay_TimerUDB_sT24_timerdp_u0__32BIT_D0_REG )
            #define AppDelay_COUNTER_LSB         (* (reg32 *) AppDelay_TimerUDB_sT24_timerdp_u0__32BIT_A0_REG )
            #define AppDelay_COUNTER_LSB_PTR       ((reg32 *) AppDelay_TimerUDB_sT24_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define AppDelay_COUNTER_LSB_PTR_8BIT       ((reg8 *) AppDelay_TimerUDB_sT24_timerdp_u0__A0_REG )
    
    #if (AppDelay_UsingHWCaptureCounter)
        #define AppDelay_CAP_COUNT              (*(reg8 *) AppDelay_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define AppDelay_CAP_COUNT_PTR          ( (reg8 *) AppDelay_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define AppDelay_CAPTURE_COUNT_CTRL     (*(reg8 *) AppDelay_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define AppDelay_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) AppDelay_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (AppDelay_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define AppDelay_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define AppDelay_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define AppDelay_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define AppDelay_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define AppDelay_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define AppDelay_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << AppDelay_CTRL_INTCNT_SHIFT))
    #define AppDelay_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << AppDelay_CTRL_TRIG_MODE_SHIFT))
    #define AppDelay_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << AppDelay_CTRL_TRIG_EN_SHIFT))
    #define AppDelay_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << AppDelay_CTRL_CAP_MODE_SHIFT))
    #define AppDelay_CTRL_ENABLE                    ((uint8)((uint8)0x01u << AppDelay_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define AppDelay_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define AppDelay_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define AppDelay_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define AppDelay_STATUS_TC_INT_MASK_SHIFT       AppDelay_STATUS_TC_SHIFT
    #define AppDelay_STATUS_CAPTURE_INT_MASK_SHIFT  AppDelay_STATUS_CAPTURE_SHIFT
    #define AppDelay_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define AppDelay_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define AppDelay_STATUS_FIFOFULL_INT_MASK_SHIFT AppDelay_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define AppDelay_STATUS_TC                      ((uint8)((uint8)0x01u << AppDelay_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define AppDelay_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << AppDelay_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define AppDelay_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << AppDelay_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define AppDelay_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << AppDelay_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define AppDelay_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << AppDelay_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define AppDelay_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << AppDelay_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define AppDelay_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << AppDelay_STATUS_FIFOFULL_SHIFT))

    #define AppDelay_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define AppDelay_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define AppDelay_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define AppDelay_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define AppDelay_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define AppDelay_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_Timer_v2_30_AppDelay_H */


/* [] END OF FILE */
