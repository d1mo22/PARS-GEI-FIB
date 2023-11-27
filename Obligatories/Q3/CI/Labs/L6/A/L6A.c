/* Main.c 
 * Processor: PIC18F45K22
 * Compiler:  MPLAB XC8
 */

#include <xc.h>
#include <stdio.h>
#include "config.h"
#include "GLCD.h"
#define _XTAL_FREQ 8000000  

const char * s1 = "L5 Individual";
const char * s2 = "--------";
const char * s3 = "David Morais";
const char * s4 = "(";
const char * s5 = ")";
int dc = 250;



void interrupt RSI_high() {
    if (TMR2IE && TMR2IF) {

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
    TMR2IE = 1
    TMR2IP = 1;
    TMR2CON = 0x06;
    TRISE &=0xFE;
}

void config_PIC() {
    ANSELA=0x00; 
    ANSELB=0x00;                  
    ANSELC=0x00;                  
    ANSELD=0x00;                  
    
    TRISD=0x00;   
    TRISB=0x00;
    TRISA=0x0F;
        
    PORTD=0x00;
    PORTB=0x00; 

    IPEN = 1;
    GIEH = 1;
    GIEL = 1;
}

void start() {
    writeTxt(2, 6, s1);	//Nom de la practica
    writeTxt(3, 9, s2);	//Linia de separacio
    writeTxt(4, 7, s3);	//Nom David
    __delay_ms(2000);
    clearGLCD(0,7,0,127); //Esborrem la pantalla
}

void print_barra() {
    clearGLCD(7,7,0,127);
    writeTxt(7, 4, s4);
    writeTxt(7,20, s5);
    for (int i = 0; i <= 76; ++i) {
      SetDot(55,24+i);
      SetDot(63, 24+i);
    }
    print_progress(7, 4);
}

void main(void) {
    config_PIC();
    
    GLCDinit();             //Inicialitzem la pantalla
    clearGLCD(0,7,0,127);   //Esborrem pantalla
    setStartLine(0);        //Definim linia d'inici

    start();
    
    while (1) { 
        taza_ant = taza;
	cafe_ant = cafe;

     }        
}
