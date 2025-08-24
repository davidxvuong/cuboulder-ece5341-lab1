/*
 * ECEA 5341 Lab1 - DC Motors Lab
 * Author: David Vuong
 */
#include "project.h"
#include "math.h"
#include "float.h"

#define BACK_EMF_CONSTANT   0.3466f             // mV/RPM
#define LCD_CLEAR_LINE      "                "

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
    LCD_ClearDisplay();
    LCD_Position(0,0);
    LCD_PrintString("Speed (RPM)");
}

int main(void)
{
    uint16 adc_result = 0;
    int16 v_emf = 0;
    float v_emf_f = 0.0f;
    float speed = 0.0f;     // Units are RPM

    CyGlobalIntEnable; /* Enable global interrupts. */
    init_ADC();
    init_LCD();
    
    for(;;)
    {
        // Spin DC Motor and sleep for 1 second
        P12_6_Write(1);
        CyDelay(1000);

        // Stop DC Motor, then start voltage measurement
        P12_6_Write(0);
        ADC_StartConvert();
        ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);   // Blocking call until ADC conversion is complete
        adc_result = ADC_GetResult16();

        // Convert to mV
        v_emf = ADC_CountsTo_mVolts(adc_result);
        v_emf_f = (float)v_emf;

        // Compute speed
        speed = v_emf_f / BACK_EMF_CONSTANT;

        // Print to LCD
        LCD_IsReady();
        LCD_Position(1,0);
        LCD_PrintString(LCD_CLEAR_LINE);
        LCD_Position(1,0);
        LCD_PrintNumber((int16)speed);
    }
}

