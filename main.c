/*
 * ECEA 5341 Lab1 - DC Motors Lab
 * Author: David Vuong
 */
#include "project.h"

void Init_ADC()
{
}

void Init_LCD()
{
    LCD_Start();
    LCD_Position(0,0);
    LCD_PrintString("DC Motors Lab");
    CyDelay(1000);
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    Init_LCD();
    
    for(;;)
    {
        LCD_IsReady();
        LCD_Position(1,0);
        LCD_PrintString("GPIO ON");
        P12_6_Write(1);
        CyDelay(5000);
        
        LCD_IsReady();
        LCD_Position(1,0);
        LCD_PrintString("GPIO OFF");
        P12_6_Write(0);
        CyDelay(5000);
    }
}

