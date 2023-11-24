/* Main.c 
 * Processor: PIC18F45K22
 * Compiler:  MPLAB XC8
 */

#include <xc.h>
#include <stdio.h>
#include "config.h"
#include "GLCD.h"
#define _XTAL_FREQ 8000000  

typedef enum{
    Curt=0,
    Llarg=1,
    Americano=2,
    Americano_XL=3
} state_t;

const char mes_menys[28] = {
    0x1C, 0x14, 0x77, 0x41, 0x77, 0x14, 0x1C,  //Contorno  +
    0x1C, 0x14, 0x14, 0x14, 0x14, 0x14, 0x1C,  //Contorno -
    0x08, 0x08, 0x08, 0x7F, 0x08, 0x08, 0x08,  // +
    0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08   // -
};

const char taza_arriba[17] = {
    0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 
    0x01, 0x01, 0x01, 0xFF, 0x40, 0x40, 0x40, 0xC0
};
const char taza_medio[17] = {
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
    0xFF,0xFF, 0xFF, 0xFF, 0x04, 0x04, 0x04, 0x07
};
const char taza_bajo[17] = {
    0x0, 0x1, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0
};

const char corto_arriba[13] = {
    0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0xFF, 0x24, 0x18
};
const char corto_abajo[13] = {
    0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x00
};

const char progress[7] = {0x1C, 0x3E, 0x7F, 0xFF, 0x7F, 0x3E, 0x1C};

const char nivel[6] = {0x81, 0xC1, 0xE1, 0xF1, 0xF9, 0xFD};

const char * s1 = "L5 Individual";
const char * s2 = "--------";
const char * s3 = "David Morais";
const char * s4 = "(";
const char * s5 = ")";
state_t nom = Curt; 
state_t nom_ant = Curt;
int cafe = 23, cafe_ant = 3; 
char taza = 'c', taza_ant = 'c';

void interrupt RSI_high() {
    if (TMR0IE && TMR0IF) {
        ++cafe;
        switch (nom) {
        case (Curt):
            TMR0 = 53036;        
            break;
        case (Llarg):
            TMR0 = 47536;
            break;
        case(Americano):
            TMR0 = 35536;
            break;
        default:
            TMR0 = 29536;
            break;
        }
        TMR0IF = 0;
    }
}

void writeTxt(byte page, byte y, char * s) {
   int i=0;
   while (*s!='\n' && *s!='\0') {
      putchGLCD(page, y+i, *(s++));
      i++;
   };
}

void print_symbol(byte p, byte y, char c)  {
   int fontPos;
   if (c == 'a') fontPos = 0;
   else if (c == 's') fontPos = 7*1;
   else if (c == '+' ) fontPos = 7*2;
   else fontPos = 7*3;
   int i;
   y = y*5-1;
   int aux;
   for (i = 0; i < 7; ++i) {
      aux = mes_menys[fontPos];
      writeByte (p, y, aux);
      ++y;
      ++fontPos;
   }
}

void print_cafe(byte p, byte y) {
    int aux = cafe/7;
    if (taza == 'c') {
        for (int i = 0; i < 9; ++i) {
            writeByte(p, y, nivel[aux]);
            ++y;
        }
    }
    else {
        if (aux < 7) {
            for (int i = 0; i < 11; ++i) {
                writeByte(p, y, 0xFF);
                ++y;
            }   
        }
        else {
            for (int i = 0; i < 11; ++i) {
                writeByte(p-1, y, nivel[aux-7]);
                ++y;
            }
        }
    }
}

void print_taza(byte p, byte y)  {
   int fontPos = 0;
   int i;
   y = y*5-3;
   int aux;
    if (taza == 'l') {
        y -= 1;
        for (i = 0; i < 17; ++i) {
            aux = taza_arriba[fontPos];
            writeByte (p-1, y, aux);
            ++y;
            ++fontPos;
        }
        fontPos = 0;
        y -= 17;
        for (i = 0; i < 17; ++i) {
            aux = taza_medio[fontPos];
            writeByte (p, y, aux);
            ++y;
            ++fontPos;
        }
        fontPos = 0;
        y -= 17;
        for (i = 0; i < 17; ++i) {
            aux = taza_bajo[fontPos];
            writeByte (p+1, y, aux);
            ++y;
            ++fontPos;
        }
        print_cafe(p, y-16);
    }
    else {
        for (i = 0; i < 13; ++i) {
            aux = corto_arriba[fontPos];
            writeByte (p, y, aux);
            ++y;
            ++fontPos;
        }
        fontPos = 0;
        y -= 13;
        for (i = 0; i < 13; ++i) {
            aux = corto_abajo[fontPos];
            writeByte (p+1, y, aux);
            ++y;
            ++fontPos;
        }
        print_cafe(p, y-12);
    }
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

    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS2 = 0;
    T0CONbits.T0PS1 = 0;
    T0CONbits.T0PS0 = 1;
    T0CONbits.TMR0ON = 0;

    TMR0IF = 0;
    TMR0IP = 1;
    TMR0IE = 1;

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

void print_progress(byte p, byte y) {
   int fontPos = 0;
   int i;
   y = y*5+1;
   int aux;
   for (i = 0; i < cafe; ++i) {
        aux = progress[fontPos];
        writeByte (p, y, aux);
        ++y;
        if (fontPos < 3 || i > 78) ++fontPos;
    } 
}

void clear_progress(byte p, byte y) {
    int fontPos = 0; 
    if (cafe_ant > 79) fontPos = 82 - cafe_ant;
    int i;
    y = y*5+1+cafe_ant;
    int aux;
    for (i = cafe_ant; i >= cafe; --i) {
        if (fontPos > 0) {
            writeTxt(7,20, s5);
            y -= fontPos;
            fontPos = 0;
        }
        else {
	 clearGLCD(p, p, y, y);
	 if (i < 80) SetDot(63, 21+i);
	}
        --y;
    }
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

void actualitzar_nom(int ready) {
    if (cafe/7 < 3) nom = Curt;
    else if (cafe/7 < 6) nom = Llarg;
    else if (cafe/7 < 9) nom = Americano;
    else nom = Americano_XL;
    if (nom != nom_ant || ready) {
        clearGLCD(1,1,30, 95);
        if (cafe/7 < 3) writeTxt(1, 11, "Curt");
        else if (cafe/7 < 6) writeTxt(1, 10, "Llarg");
        else if (cafe/7 < 9) writeTxt(1, 8, "Americano");
        else writeTxt(1, 7, "Americano XL");
    }
    nom_ant = nom;
}

void main(void) {
    config_PIC();
    
    GLCDinit();             //Inicialitzem la pantalla
    clearGLCD(0,7,0,127);   //Esborrem pantalla
    setStartLine(0);        //Definim linia d'inici

    start();

    print_barra();
    print_symbol(1,20,'+');
    print_symbol(1,4,'-');
    print_taza(4, 12);
    writeTxt(1,11,"Curt");
    
    int ready = 0;
    int cafe_prev;
    

    while (1) { 
        taza_ant = taza;
        cafe_ant = cafe;
        if (ready) {
            if (cafe_ant < cafe) print_progress(7,4);
            if (cafe > 80) {
                TMR0ON = 0;
                clearGLCD(1,1,30, 95);
                writeTxt(1,10,"Llest");
                __delay_ms(1000);
                cafe_ant = cafe;
                cafe = cafe_prev;
                clearGLCD(1,1,30, 95);
                actualitzar_nom(ready);
                print_taza(4, 12);
                clear_progress(7,4);
                ready = 0;
            }
        }
        else {
            if (PORTAbits.RA2) {
                cafe_prev = cafe;
                ready = 1;
                cafe = 3;
                clearGLCD(1,1,30, 95);
                writeTxt(1,8,"Esperi...");
                switch (nom) {
                case (Curt):
                    TMR0 = 53036;        
                    break;
                case (Llarg):
                    TMR0 = 47536;
                    break;
                case(Americano):
                    TMR0 = 35536;
                    break;
                default:
                    TMR0 = 29536;
                    break;
                }
                clear_progress(7,4);
                TMR0ON = 1;
            }
            if (PORTAbits.RA0 && !PORTAbits.RA1) {
                print_symbol(1,20,'a');
                if (cafe < 83) ++cafe;
                __delay_ms(100);
            }
            else print_symbol(1,20,'+');
                    
            if (PORTAbits.RA1 && !PORTAbits.RA0) {
                print_symbol(1,4,'s');
                if (cafe > 3) --cafe;
                __delay_ms(100);
            }
            else print_symbol(1,4,'-');
	    
            if (!ready) {
                if (cafe > 41) taza = 'l';
                else taza = 'c';

                if (taza_ant != taza) {
                    clearGLCD(3 ,4, 50, 86);
                    print_taza(4, 12);
                }

                if (cafe_ant < cafe) {
                    print_progress(7,4);
                }
                else if (cafe_ant > cafe) {
                    clear_progress(7,4);
                }
            
                if (cafe_ant/7 != cafe/7) print_taza(4,12);
                actualitzar_nom(ready);
            }
        }
        
    }
}