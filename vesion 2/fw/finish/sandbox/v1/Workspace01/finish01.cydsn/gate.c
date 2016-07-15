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
#include "gate.h"

/*******************************************************************************
* Function Name: IsGateOpen
********************************************************************************
*
* * verification or gate closed
*
* Return:
*  true(gate closed) or false(gate not closed))
*******************************************************************************/
bool IsGateOpen(void)
{
    if(!GatePin_Read())
    {
        return true;
    }
    else{
        return false;
    }
}
/* [] END OF FILE */
