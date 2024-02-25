// CONFIG1L
#pragma config FEXTOSC = HS     // External Oscillator mode Selection bits (HS (crystal oscillator) above 8 MHz; PFM set to high power)
#pragma config RSTOSC = EXTOSC_4PLL// Power-up default value for COSC bits (EXTOSC with 4x PLL, with EXTOSC operating per FEXTOSC bits)

// CONFIG3L
#pragma config WDTCPS = WDTCPS_31// WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE = OFF        // WDT operating mode (WDT enabled regardless of sleep)

#include <xc.h>
#include "dc_motor.h"




#define _XTAL_FREQ 64000000 //note intrinsic _delay function is 62.5ns at 64,000,000Hz  

void main(void){
    int PWMcycle=99; // 0.0001s*16MHz/16 -1 = 99
    initDCmotorsPWM(PWMcycle);
       
    struct DC_motor motorL, motorR; 		//declare two DC_motor structures 

    motorL.power=0; 						//zero power to start
    motorL.direction=1; 					//set default motor direction
    motorL.brakemode=1;						// brake mode (slow decay)
    motorL.posDutyHighByte=(unsigned char *)(&CCPR1H);  //store address of CCP1 duty high byte
    motorL.negDutyHighByte=(unsigned char *)(&CCPR2H);  //store address of CCP2 duty high byte
    motorL.PWMperiod=PWMcycle;

    motorR.power=0; 						//zero power to start
    motorR.direction=1; 					//set default motor direction
    motorR.brakemode=1;						// brake mode (slow decay)
    motorR.posDutyHighByte=(unsigned char *)(&CCPR3H);  //store address of CCP3 duty high byte
    motorR.negDutyHighByte=(unsigned char *)(&CCPR4H);  //store address of CCP4 duty high byte
    motorR.PWMperiod=PWMcycle;

    // setup pin for input (connected to button)
    TRISFbits.TRISF2=1; //set TRIS value for pin (input) BUTTON 1
    ANSELFbits.ANSELF2=0; //turn off analogue input on pin 
    
    //Turn light on and off to debug
    LATHbits.LATH3=0;   //set initial output state
    TRISHbits.TRISH3=0; //set TRIS value for pin (output)
    
    while (PORTFbits.RF2); //Wait for button press to execute movement
    __delay_ms(300);
    
    fullSpeedAhead(&motorL, &motorR);
    __delay_ms(200);
    stop(&motorL, &motorR);
    __delay_ms(100);
    turnLeft(&motorL, &motorR);
    __delay_ms(800);
    fullSpeedAhead(&motorL, &motorR);
    __delay_ms(200);
    stop(&motorL, &motorR);
    __delay_ms(100);
    turnRight(&motorL, &motorR);
    __delay_ms(800);
    fullSpeedAhead(&motorL, &motorR);
    __delay_ms(200);
    stop(&motorL, &motorR);
    __delay_ms(100);
}
