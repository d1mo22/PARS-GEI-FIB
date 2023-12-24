/* Main.c 
 * Processor: PIC18F45K22
 * Compiler:  MPLAB XC8
 */

#include <xc.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "config.h"
#include "GLCD.h"
#include "splash.h"
#define _XTAL_FREQ 8000000  

const char * s1 = "L7 Projecte";
const char * s2 = "David Morais";
const char * s3 = "Raul Box";
const char* endl = "\r\n";
char c = 'x';
int dc = 500;


void interrupt RSI_high() {
    if (TMR2IE && TMR2IF) {
      TRISE&=0xFE;
      TMR2IF = 0;
    }
}

void pinta_CI() {
   int k = 0;
    for (int i = 0; i < 8; ++i) {
        for(int j = 0; j < 128; ++j) {
            int aux = bitmap[k];
            writeByte(i, j, aux);
            ++k;
	    }  
    }
}

void write_term(char* s) {
    for (int i = 0; i < strlen(s); ++i) {
        while(!TXSTA1bits.TRMT);
        TXREG1 = s[i];
    }
}

unsigned char llegir_term(void) {
    while(!RC1IF);
    return RCREG1;
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
   ANSELE=0x00;

   TRISB=0x00;
   TRISA=0x03;
   TRISD=0x00;
   TRISC=0xFF;
   TRISEbits.RE1 = 1;

   PORTB=0x00;
   PORTD=0x00;
   PORTE=0x00;
   PORTA=0x00;

    IPEN = 1;
    GIEH = 1;
    GIEL = 1;
}

void pintar_noms(void) {
   writeTxt(0,1,s1);
   writeTxt(3,7, s2);
   writeTxt(5, 9, s3);
   write_term(s1);
   write_term(endl);
   write_term(s2);
   write_term(endl);
   write_term(s3);
   write_term(endl);
}

void start(void) {
    pinta_CI();
    __delay_ms(2000);
    clearGLCD(0,7,0,127);
    pintar_noms();
    __delay_ms(2000);
    clearGLCD(0,7,0,127);
}

void config_SC(void) {
    SPBRG1 = 16;
    SPBRGH1 = 0;
    BAUDCON1bits.BRG16 = 1;

    TXSTA1bits.BRGH = 1;
    TXSTA1bits.SYNC = 0;
    TXSTA1bits.TXEN = 1;

    RCSTA1bits.SPEN = 1;
    RCSTAbits.CREN = 1;
    PIR1bits.RC1IF = 0;
    RC1IE = 1;
    RCIE = 1;
}

void main(void) {
    config_PIC();
        
    GLCDinit();             //Inicialitzem la pantalla
    clearGLCD(0,7,0,127);   //Esborrem pantalla
    setStartLine(0);        //Definim linia d'inici
    config_SC();              
    start(); 
    config_PWM();
    config_ADC();
    
   //int dc_ant = dc;
   //int adc = 265;
   //char buff[128];
   /*
        dc_ant = dc;
        ADCON0bits.GODONE = 1;
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
   */
    while (1) { 
    }        
}
