#include <xc.h>
#include <time.h> 
#include <stdlib.h>
#include "config.h"


#define _XTAL_FREQ 8000000

char chars[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67};
char previous_input = 0x0;
char input;
char caracters[4] = {'\0', '\0', '\0', '\0'};

void display_char(unsigned char displays, char num) {
   if (num == '\0') PORTA = 0x00;
   else {
      int numero = num - '0';
      PORTA = 0x00;
      PORTD = chars[numero];
      PORTA = displays;
   }
}

void dreta(int x) {
    caracters[0] = '0' + x%10;
    caracters[1] = '0' + x/10;
}

void esquerra(int y) {
    caracters[3] = '0' + y/10;
    caracters[2] = '0' + y%10;
}

void configure_pic() {
   // Output (seleccio display).
   ANSELA = 0x0;
   TRISA = 0x0; 
   
   // Output (display segments).
   TRISD = 0x00;
   ANSELD = 0x00;
   
   // Input (botons).
   TRISC = 0xF0;
   ANSELC = 0x0;
}


void main(void) {
   configure_pic();
   int ON = 1;
   int x, y, z;
   int contador = 0;
   
   while (1) {
      input = PORTC;
      srand(contador);
      
      //RC7
      if (previous_input == 0x00) {
         //delay
         if (input == 0x80) {
            x = rand()%100;
            dreta(x);
         }
      }
         
      //RC6
      if(previous_input == 0x40) {
         //delay
         if (input == 0x00) {
            z = x*y;
            //Modifiquem la variable per si hem
            //de muiltiplicar mes d'un cop
            x = z%100;
            y = z/100;
            dreta(x);
            esquerra(y);
         }
      }
         
      //RC5
      if (previous_input == 0x00) {
         //delay
         if (input == 0x20) {
            y = rand()%100;
            esquerra(y);
         }
      }
         
      //RC4
      if (previous_input == 0x10) {
         //delay
         if (input == 0x00) {
            ON = !ON;
         }
      }
         
      //Si ON es 1 el display esta ences
      if (ON == 1) {
            PORTA = 0x00;
            display_char(0x01, caracters[0]);
            display_char(0x02, caracters[1]);
            display_char(0x04, caracters[2]);
            display_char(0x08, caracters[3]);
         }
      else PORTA = 0x00;
         
      previous_input = input;
      ++contador;    
   }
}