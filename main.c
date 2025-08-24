/*
 * ECEA 5341 Lab1 - DC Motors Lab
 * Author: David Vuong
 */
#include "project.h"

void init_ADC()
{
    ADC_Start();
}

void init_LCD()
{
    LCD_Start();
    LCD_Position(0,0);
    LCD_PrintString("DC Motors Lab");
    CyDelay(1000);
}

void control_switch(uint8 val)
{
    LCD_IsReady();
    LCD_Position(0,0);
    LCD_ClearDisplay();
    LCD_PrintString(val == 1 ? "MOTOR ON" : "MOTOR OFF");
    P12_6_Write(val);
}

int main(void)
{
    uint16 adc_result = 0;

    CyGlobalIntEnable; /* Enable global interrupts. */
    init_ADC();
    init_LCD();
    
    for(;;)
    {
        // Spin DC Motor and sleep for 10 seconds
        control_switch(1);
        CyDelay(10000);

        // Stop DC Motor, then start measurement
        control_switch(0);
        ADC_StartConvert();
        ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);   // Blocking call until ADC conversion is complete
        adc_result = ADC_GetResult16();
        CyDelay(10000);
    }
}

