//#include <debug.h>

//CY_ISR(DEBUG_INTERRUPT)
//{       
//
//    tmpMs = RTCgetRecentMs();
//    
//    if(tmpMs < 500)
//    {
//        if(tmpMs > minMs) minMs = tmpMs;           
//    }else
//    {
//        tmpMs = 1000 - tmpMs;
//        if(tmpMs > maxMs) maxMs = tmpMs;
//    }
//    
//    //INT_DEBUG_ClearPending();
//}
//
//void DebugStart(void)
//{
//    //INT_DEBUG_StartEx(DEBUG_INTERRUPT); 
//}
//
//void DebugPrintResult(void)
//{
//    LCD_Position(0,0);
//    LCD_PrintNumber(minMs);
//    LCD_PutChar('-');
//    LCD_PrintNumber(maxMs);
//}

//s        |            |            |            |
//t        |            |            |            |
//r        |            |            |            |
//         .
//f    |   .        |            |            |
//i    |   .        |            |            |
//n    |   .        |            |            |
//         .        
//         20ms
//
//
//s               |             |            |
//t               |             |            |
//r               |             |            |
//                .
//f    |          .  |            |            |
//i    |          .  |            |            |
//n    |          .  |            |            |
//                .        
//                950ms
/* [] END OF FILE */
