/* Main.c 
 * Processor: PIC18F45K22
 * Compiler:  MPLAB XC8
 */

#include <xc.h>
#include <stdio.h>
#include <math.h>
#include "config.h"
#include "GLCD.h"
#define _XTAL_FREQ 8000000  

const char * s1 = "Frequencia: 500Hz";
const char * s2 = "Periode: 2ms";
const char * s3 = "Duty: 50";
int dc = 500;


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

int aproximacio(double n) {
    double x = 299.5617;    //f(2.58)
    double y = 17.744;      //f'(2.58)
    double z = 2.5568/2;    //f''(2.58)/2
    double t = 6.2424/6;    //f'''(2.58)/6
    //Taylor
    return (int)round((x+y*(n-2.58)+z*(n-2.58)*(n-2.58)+t*(n-2.58)*(n-2.58)*(n-2.58))-273.15);
}

int funcio(double n) {
    return (int)round(((4050)/(log(-((4700-((4700*5)/n))/0.0059257)))-273.15));
}

double conversor(int n) {
    return (n*5.0)/1023.0;
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

void config_ADC() {
    ADCON0 = 0x18;
    ADCON1 = 0x00;
    ADCON2 = 0xA1; //Right justified
}

void config_PIC() {
    ANSELB=0x00;
    ANSELA=0x00;
    ANSELD=0x00;
    ANSELE=0x02;

    TRISB=0x00;
    TRISA=0x03;
    TRISD=0x00;
    TRISE=0x02;

    PORTB=0x00;
    PORTD=0x00;
    PORTE=0x00;
    PORTA=0x00;

    IPEN = 1;
    GIEH = 1;
    GIEL = 1;
}

void start() {
    writeTxt(0, 0, s1);	
    writeTxt(2, 0, s2);	
    writeTxt(4, 0, s3);	
}

void main(void) {
    config_PIC();
        
    GLCDinit();             //Inicialitzem la pantalla
    clearGLCD(0,7,0,127);   //Esborrem pantalla
    setStartLine(0); 
    start();                //Definim linia d'inici
    config_PWM();
    config_ADC();
    
   int dc_ant = dc;
   int adc = 265;
   char buff[128];
    
    while (1) { 
        dc_ant = dc;
        ADCON0bits.GODONE = 1;
       
        writeNum(6, 5, adc);
        //Esperem que el conversor acabi
        while (ADCON0bits.GODONE);
        
        adc = conversor(ADRES);
        dc = adc*20;
        
        if (PORTAbits.RA0) {
            if (dc < 1000) ++dc;
        }
        if (PORTAbits.RA1) {
            if (dc > 0) --dc;
        }

        Escriu_DC(dc);
        
        if (dc_ant != dc) {
            sprintf(buff, "Duty: %d ", dc/10);
            writeTxt(4, 0, buff);     
        }
     }        
}
