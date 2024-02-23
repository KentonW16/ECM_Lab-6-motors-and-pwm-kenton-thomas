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
    
    unsigned int PWMcycle = 199;
    initDCmotorsPWM(PWMcycle);
    
    struct DC_motor motorL, motorR; 		//declare two DC_motor structures 

    motorL.power=0; 						//zero power to start
    motorL.direction=1; 					//set default motor direction
    motorL.brakemode=1;						// brake mode (slow decay)
    motorL.posDutyHighByte=(unsigned char *)(&CCPR1H);  //store address of CCP1 duty high byte
    motorL.negDutyHighByte=(unsigned char *)(&CCPR2H);  //store address of CCP2 duty high byte
    motorL.PWMperiod=PWMcycle;              //store PWMperiod for motor (value of T2PR in this case)

    motorR.power=0; 						//zero power to start
    motorR.direction=1; 					//set default motor direction
    motorR.brakemode=1;						// brake mode (slow decay)
    motorR.posDutyHighByte=(unsigned char *)(&CCPR3H);  //store address of CCP1 duty high byte
    motorR.negDutyHighByte=(unsigned char *)(&CCPR4H);  //store address of CCP2 duty high byte
    motorR.PWMperiod=PWMcycle;              //store PWMperiod for motor (value of T2PR in this case)
    
    
    //wait for button press
    TRISFbits.TRISF2=1; //set TRIS value for pin (input)
    ANSELFbits.ANSELF2=0; //turn off analogue input on pin  
    while (PORTFbits.RF2);
    __delay_ms(500);
    
    
    // square turning left
    fullSpeedAhead(&motorL,&motorR);
    __delay_ms(100);
    stop(&motorL,&motorR);
    __delay_ms(200);
    turnLeft(&motorL,&motorR);
    __delay_ms(200);
    fullSpeedAhead(&motorL,&motorR);
    __delay_ms(100);
    stop(&motorL,&motorR);
    __delay_ms(200);
    turnLeft(&motorL,&motorR);
    __delay_ms(200);
    fullSpeedAhead(&motorL,&motorR);
    __delay_ms(100);
    stop(&motorL,&motorR);
    __delay_ms(200);
    turnLeft(&motorL,&motorR);
    __delay_ms(200);
    fullSpeedAhead(&motorL,&motorR);
    __delay_ms(100);
    stop(&motorL,&motorR);
    __delay_ms(200);
    turnLeft(&motorL,&motorR);
    __delay_ms(200);
    turnLeft(&motorL,&motorR);
    __delay_ms(200);
    
    // square turning right
    fullSpeedAhead(&motorL,&motorR);
    __delay_ms(100);
    stop(&motorL,&motorR);
    __delay_ms(200);
    turnRight(&motorL,&motorR);
    __delay_ms(200);
    fullSpeedAhead(&motorL,&motorR);
    __delay_ms(100);
    stop(&motorL,&motorR);
    __delay_ms(200);
    turnRight(&motorL,&motorR);
    __delay_ms(200);
    fullSpeedAhead(&motorL,&motorR);
    __delay_ms(100);
    stop(&motorL,&motorR);
    __delay_ms(200);
    turnRight(&motorL,&motorR);
    __delay_ms(200);
    fullSpeedAhead(&motorL,&motorR);
    __delay_ms(100);
    stop(&motorL,&motorR);
    __delay_ms(200);
    turnRight(&motorL,&motorR);
    __delay_ms(200);
    turnRight(&motorL,&motorR);
    __delay_ms(200);
    
    
    while(1){
		//to calibrate turning
        //turnRight(&motorL,&motorR);
        //__delay_ms(1000);
        
    }
    
}
