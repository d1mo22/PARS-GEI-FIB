/* Main.c 
 * Processor: PIC18F45K22
 * Compiler:  MPLAB XC8
 */

#include <xc.h>
#include <stdio.h>
#include "config.h"
#include "GLCD.h"
#define _XTAL_FREQ 8000000  

const char * s1 = "Frequencia: 500Hz";
const char * s2 = "Periode: 2ms";
const char * s3 = "Duty: 25%";
const char * s4 = "Amplada del pols: 0.5ms";
const char * s5 = ")";
int dc = 250;

void interrupt RSI_high() {
    if (TMR2IE && TMR2IF) {
      TRISE&=0xFE;
      TMR2IF = 0;
    }
}

void writeTxt(byte page, byte y, char * s) {
   int i=0;
   while (*s!='\n' && *s!='\0') {
      putchGLCD(page, y+i, *(s++));
      i++;
   };
}

void Escriu_DC(int dc) {
    int baix = dc%4;
    int alt = dc/4;
    CCPR3L=alt;
    CCP3CON &=0xCF;
    CCP3CON += baix << 4;
}

void config_PWM() {
    TRISE|=0x01;
    CCPTMRS0&=0xE7;
    PR2 = 249;
    CCP3CON|=0x0C;
    Escriu_DC(dc);
    TMR2IF = 0;
    TMR2IE = 1;
    TMR2IP = 1;
    T2CON = 0x06;
    TRISE &=0xFE;
}

void config_PIC() {
   ANSELB=0x00;
   ANSELD=0x00;
   ANSELE=0x00;

   TRISB=0x00;
   TRISD=0x00;

   PORTB=0x00;
   PORTD=0x00;
   PORTE=0x00;

    IPEN = 1;
    GIEH = 1;
    GIEL = 1;
}

void start() {
    writeTxt(0, 0, s1);	
    writeTxt(2, 0, s2);	
    writeTxt(4, 0, s3);	
    writeTxt(6, 0, s4);	
}

void main(void) {
    config_PIC();
        
    GLCDinit();             //Inicialitzem la pantalla
    clearGLCD(0,7,0,127);   //Esborrem pantalla
    setStartLine(0);        //Definim linia d'inici
    start();    
    config_PWM();
    
  
    
    while (1) { 

    }        
}
