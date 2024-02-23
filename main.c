// CONFIG1L
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31// WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "rc_servo.h"
#include "ADC.h"
#include "LCD.h"


#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void){
    Timer0_init();
    Interrupts_init();
	//don't forget TRIS for your output!
    TRISAbits.TRISA1=0; //Set pin A1 for output

    //Similar to main of Lab 4, to display current LDR voltage on LCD for easy calibration
    LCD_Init(); 
    ADC_init();
	
	LCD_setline(1); //Set Line 1
    
    unsigned int val=0;  
    signed int angle=0;
    char buf[40]; //set buf as array
    
    while (1) {
        val = ADC_getval(); // get ADC value
        ADC2String(buf, val); // get string of ADC value
        LCD_sendstring(buf); // send string to LCD
        
        if (val>150) {angle=90;} //Set threshold by testing manually for ambient light
        else {angle=-90;}
        angle2PWM(angle);
    }
}
