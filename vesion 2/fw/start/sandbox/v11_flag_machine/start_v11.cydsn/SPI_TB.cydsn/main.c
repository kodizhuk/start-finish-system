/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    SwSPI_Master_1_ChipSelect();
    SwSPI_Master_1_SendByte(0x11);
    SwSPI_Master_1_ChipDeselect();
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
