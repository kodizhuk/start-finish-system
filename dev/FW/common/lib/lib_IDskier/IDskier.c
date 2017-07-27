#include "project.h"
#include "..\..\common\lib\lib_IDskier\IDskier.h"
#include "..\..\common\lib\lib_Display\Display.h"

#define NUM_STEP_SCROLL 5

uint8_t idNumSkier = 0;

uint8_t btnUpClick = 0;
uint8_t btnDownClick = 0;
uint8_t stepScroll = 1;
uint8_t scroll = 0;


/*button interrupt*/
CY_ISR(BUTT_UP_INTERRUPT)
{   
    BUTT_UP_INT_Disable();
    
    btnUpClick = 1;
    
    BUTT_UP_INT_ClearPending();
}

/*button interrupt*/
CY_ISR(BUTT_DOWN_INTERRUPT)
{   
    btnDownClick = 1;
    
    BUTT_DOWN_INT_ClearPending();
    BUTT_DOWN_INT_Disable();
}

/*******************************************************************************
* Function Name: ButtInit
********************************************************************************
*
* Summary:
*   inittilisation the button pin
*
*******************************************************************************/
void ButtInit(void)
{
    BUTT_UP_INT_ClearPending();
    BUTT_UP_INT_StartEx(BUTT_UP_INTERRUPT);
    BUTT_UP_INT_Enable();
    //BUTT_UP_INT_Disable();
    
    BUTT_DOWN_INT_ClearPending();
    BUTT_DOWN_INT_StartEx(BUTT_DOWN_INTERRUPT);
    BUTT_DOWN_INT_Enable();
    //BUTT_DOWN_INT_Disable();
}

/*******************************************************************************
* Function Name: ButtCheck
********************************************************************************
*
* Summary:
*   check button
*
*******************************************************************************/
void ButtCheck(void)
{
    if((btnUpClick == 1) || (BtnUp_Read() == 0))
    {
        idNumSkier+=stepScroll;
        btnUpClick = 0;  
    }
    if(BtnUp_Read() == 1)
    {
        BUTT_UP_INT_ClearPending();
        BUTT_UP_INT_Enable();
    }
    
    
    if((btnDownClick == 1) || (BtnDown_Read() == 0))
    {
        idNumSkier-=stepScroll;
        btnDownClick = 0;  
    }
    if(BtnDown_Read() == 1)
    {
        BUTT_DOWN_INT_ClearPending();
        BUTT_DOWN_INT_Enable();
    }
    
    if((BtnDown_Read() == 0) || BtnUp_Read() == 0)
        scroll++;
    else
        scroll = 0;
    
    if(scroll >= NUM_STEP_SCROLL)
        stepScroll = 5;
    else
        stepScroll = 1;
}


uint8_t ReadIdSkier(void)
{   
    return idNumSkier;
}