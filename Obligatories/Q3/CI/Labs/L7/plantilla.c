#include <xc.h>
#include <string.h>
#include "config.h"
#include "GLCD.h"
#include "splash.h"
#define _XTAL_FREQ 8000000  

typedef enum{
   Tipus = 0,
   Dosis = 1,
   Temperatura = 2,
   Servint = 3
} state_t;

// Coordenades dels dibuixos (en Bytes)
const int yBarraTipus = 5;
const int yBarraDosis = 6;
const int yBarraTemp = 7;
const char * s1 = "L7 Projecte";
const char * s2 = "David Morais";
const char * s3 = "Raul Box";
const char* endl = "\r\n";

// Utilitzem els valors arbitraris 0 i 94 perquè són els
// bits que ocupa el diagrama de la barra a la GLCD
int tipus = 0, tipus_ant = 0; // 0 <= tipus <= 94
int dosis = 0, dosis_ant = 0; // 0 <= dosis <= 94
int temp = 0, temp_ant = 0;// 0 <= temp <= 94
int t = 0, contador = 0;

state_t estat = Tipus;

void writeTxt(byte page, byte y, char * s) {
   int i=0;
   while (*s!='\n' && *s!='\0') {
      putchGLCD(page, y+i, *(s++));
      i++;
   }
}


//Timer configurat a 1s
void interrupt low_priority RSI_low() {
    if (TMR0IE && TMR0IF) {
        if (contador < t) {
            ++contador;
            TMR0 = 15625;
            TMROIF = 0;
        }
        else {
            contador = 0;
            TMR0ON = 0;
        }
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
// IMPRIMEIX UNA BARRA DE PROGRÉS BUIDA
void imprimir_barra(int y) {
   writeByte(y, 30, 0x7C);
   writeByte(y, 126, 0x7C);
   for (int i = 31; i < 126; ++i)
      writeByte(y, i, 0x10);
}

void actualitzar_barra(int y, int prev, int actual) {
   if (actual > prev)
      writeByte(y, 30 + actual, 0x38);
   else if (actual < prev)
      writeByte(y, 30 + prev, 0x10);
}

void imprimir_inici() {
   writeTxt(yBarraTipus, 0, "Tipus:");
   imprimir_barra(yBarraTipus);
   writeTxt(yBarraDosis, 0, "Dosis:");
   imprimir_barra(yBarraDosis);
   writeTxt(yBarraTemp, 0, "Temp.:");
   imprimir_barra(yBarraTemp);
}

void config_PIC() {
   ANSELA = 0x00;
   ANSELB = 0x00;
   ANSELC = 0x00;
   ANSELD = 0x00;
   ANSELE=0x00;
   
   TRISD = 0x00;
   TRISC = 0xFF;
   TRISB = 0x00;
   TRISEbits.RE1 = 1;
    
   PORTD = 0x00;
   PORTB = 0x00;
   
   GIEH = 1;
   IPEN = 0;
}
//Falla algo
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

void config_TMR() {
    T0CONbits.T08BIT = 0;
    T0CONbits.T0CS = 0;
    T0CONbits.PSA = 0;
    T0CONbits.T0PS2 = 1;
    T0CONbits.T0PS1 = 1;
    T0CONbits.T0PS = 1;
    TMR0 = 15625;
    INTCONbits.TMR0IF = 0;
    INTCONbits.T0IE = 1;
    T0CONbits.TMR0ON = 0;

}

void main(void) {
   config_PIC();
   config_SC();
   GLCDinit();		   //Inicialitzem la pantalla
   clearGLCD(0,7,0,127);   //Esborrem pantalla
   setStartLine(0);        //Definim linia d'inici
   
   start();
   imprimir_inici();
   
   int RC4_prev = 0;
   
   while (1) {
      RC4_prev = PORTCbits.RC4;
      
      switch(estat) {
      case (Tipus):
      	 if (PORTCbits.RC2) {
	    __delay_ms(20); // estratègia antirrebots
	    if (PORTCbits.RC2) {
	       if (tipus < 95) {
		  tipus_ant = tipus;
		  ++tipus;
		  actualitzar_barra(yBarraTipus, tipus_ant, tipus);
	       }
	    }
	 }
	 else if (PORTCbits.RC3) {
	    __delay_ms(20); // estratègia antirrebots
	    if (PORTCbits.RC3) {
	       if (tipus > 0) {
		  tipus_ant = tipus;
		  --tipus;
		  actualitzar_barra(yBarraTipus, tipus_ant, tipus);
	       }
	    }
	 }
	 else if (PORTCbits.RC4 && !RC4_prev) {
	    __delay_ms(20); // estratègia antirrebots
	    if (PORTCbits.RC4) estat = Dosis;
	 }
	 break;
	 
      case (Dosis):
      	 if (PORTCbits.RC2) {
	    __delay_ms(20); // estratègia antirrebots
	    if (PORTCbits.RC2) {
	       if (tipus < 95) {
		  tipus_ant = dosis;
		  ++dosis;
		  actualitzar_barra(yBarraDosis, dosis_ant, dosis);
	       }
	    }
	 }
	 else if (PORTCbits.RC3) {
	    __delay_ms(20); // estratègia antirrebots
	    if (PORTCbits.RC3) {
	       if (tipus > 0) {
		  dosis_ant= dosis;
		  --dosis;
		  actualitzar_barra(yBarraDosis, dosis_ant, dosis);
	       }
	    }
	 }
	 else if (PORTCbits.RC4 && !RC4_prev) {
	    __delay_ms(20); // estratègia antirrebots
	    if (PORTCbits.RC4 == 1) estat = Temperatura;
	 }
	 break;
	 
      case (Temperatura):
      	 if (PORTCbits.RC2) {
	    __delay_ms(20); // estratègia antirrebots
	    if (PORTCbits.RC2) {
	       if (tipus < 95) {
		  temp_ant= temp;
		  ++temp;
		  actualitzar_barra(yBarraTemp, temp_ant, temp);
	       }
	    }
	 }
	 else if (PORTCbits.RC3) {
	    __delay_ms(20); // estratègia antirrebots
	    if (PORTCbits.RC3) {
	       if (tipus > 0) {
		  temp_ant= temp;
		  --temp;
		  actualitzar_barra(yBarraTemp, temp_ant, temp);
	       }
	    }
	 }
	 else if (PORTCbits.RC4 && !RC4_prev) {
	    __delay_ms(20); // estratègia antirrebots
	    if (PORTCbits.RC4) estat = Servint;
	 }
	 break;
	 
      default:
	 // CODI DEL MOLINILLO, BOMBA, ETC.ç
     //Molinet
     if (dosis >= 47) t = 15;
     else t = 5;
     TMR0ON = 1;
     POTRAbits.RA0 = 1;
     writeTxt(0,0,"Molint el cafe");
	 writeTxt(0,0,"Servint. Ficarem dibuix");
	 writeTxt(1,8,"tassa");
	 estat = Tipus;
	 break;
	 
      }
   }
}
