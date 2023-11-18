// A proposal for main.c ..... just to inspire you
#include <xc.h>
#include <stdio.h>
#include <string.h>

#include "config.h"
#include "GLCD.h"

#define _XTAL_FREQ 8000000 // Needed for __delay_ms function

typedef enum{
    Ready=0,
    Running=1,
    Stopped=2
} state_t;

// Global Variables 
unsigned int decimes = 0;
unsigned int s = 1;
unsigned int decimes_anterior = 0;
const char * s1 = "David Morais";
const char * s2 = "Raul Box";
const char * s3 = "L4B GLCD";
const char * s4 = "--------";
char buff[128];
int press = 0;
state_t estatCrono = Ready;

void writeTxt(byte page, byte y, char * s) {
   int i=0;
   while (*s!='\n' && *s!='\0') {
      putchGLCD(page, y+i, *(s++));
      i++;
   };
}

void tic(void) {
    decimes_anterior = decimes;
    if (decimes > 0) --decimes;
    else {
        --s;
        decimes = 9;
    }
}

// RSI High Priority for handling Timer0
void interrupt RSI_high(){
    if (TMR0IE && TMR0IF) {
        tic();
        TMR0 = 62411;
        TMR0IF = 0;  
    }
}
// Falling edge detection and debouncing
int inputDetector() {
    int detect = 0;
    if (press) {
        __delay_ms(10);
        if (!PORTCbits.RC0) {
            detect = 1;
        }
    }
    press = PORTCbits.RC0;
    return detect;
}

// Initialize PORTs, timer0 and basic PIC resources
void configPIC() {
    ANSELA=0x00; 
    ANSELB=0x00;                  
    ANSELC=0x00;                  
    ANSELD=0x00;                  
    
    TRISD=0x00;		   
    TRISB=0x00;
    TRISC=0x01;
        
    PORTD=0x00;
    PORTB=0x00; 
    PORTC=0x00;
    
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS2 = 0;
    T0CONbits.T0PS1 = 1;
    T0CONbits.T0PS0 = 1;
    TMR0 = 62411;
    T0CONbits.TMR0ON = 0;

    TMR0IF = 0;
    TMR0IP = 1;
    TMR0IE = 1;

    IPEN = 1;
    GIEH = 1;
    GIEL = 1;
}

void start() {
    writeTxt(2, 9, s3);	//Nom de la practica
    writeTxt(3, 9, s4);	//Linia de separacio
    writeTxt(4, 9, s2);	//Nom Raul
    writeTxt(5, 7, s1);	//Nom David
    __delay_ms(2000);
    clearGLCD(0,7,0,127); //Esborrem la pantalla
}

void updateGLCD(state_t estatCrono) {
    const char *estat = "Ready";
    if (estatCrono == Running) estat = "Running...";
    else if (estatCrono == Stopped) estat = "Stopped";
    writeTxt(0, 0, estat);

    if (decimes != decimes_anterior) {
        sprintf(buff,"%d%d.%d", s/10, s%10, decimes);
        writeTxt(3, 10, buff); 
    }
}

void main(void) {
    configPIC();

    GLCDinit();		   //Inicialitzem la pantalla
    clearGLCD(0,7,0,127);   //Esborrem pantalla
    setStartLine(0);        //Definim linia d'inici
    start();

    
    writeTxt(0, 0, "Ready");
    sprintf(buff,"%d%d.%d", s/10, s%10, decimes);
    writeTxt(3, 10, buff); 
    // MAIN LOOP
    while (1) {
        if (inputDetector()) { // check falling edge
            switch(estatCrono) {
                case(Ready):
                    clearGLCD(0,0,0,127); 
                    TMR0ON = 1;
                    estatCrono = Running;
                    break;
                case(Running): 
                    clearGLCD(0,0,0,127);
                    TMR0ON = 0;
                    estatCrono = Stopped;
                    break;
                default: 
                    clearGLCD(0,0,0,127);
                    s = 10;
                    decimes = 0;
                    estatCrono = Ready;
                    break;
            }
        }  
        if (decimes == 0 && s == 0) {
            estatCrono = Stopped;
            TMR0ON = 0;
        }
        updateGLCD(estatCrono);
    }
}