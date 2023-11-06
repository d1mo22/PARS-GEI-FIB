
/* 
 * GLCD (Graphic Liquid Crystal Display)
 */
 
#include <xc.h>
#include "GLCD.h"
#include "ascii.h"

// D'us intern
void GLCDBusyWait(byte CS);
byte readByteReal(byte, byte, byte);

#define CS1 PORTBbits.RB0
#define CS2 PORTBbits.RB1
#define RS PORTBbits.RB2
#define RW PORTBbits.RB3
#define E PORTBbits.RB4
#define RST PORTBbits.RB5
#define D0 PORTDbits.RD0
#define D1 PORTDbits.RD1
#define D2 PORTDbits.RD2
#define D3 PORTDbits.RD3
#define D4 PORTDbits.RD4
#define D5 PORTDbits.RD5
#define D6 PORTDbits.RD6
#define D7 PORTDbits.RD7

//Codis d'ordres
#define SET_Y_ADDRESS 0x40  //columna
#define SET_START_LINE 0xC0
#define SET_X_ADDRESS 0xB8  //fila
#define SET_ON_OFF 0x3E

// Activacio dels senyals de control del GLCD
#define _CS1 0x1
#define _CS2 0x2
#define _RST 0x20
#define _E 0x10
#define _RW 0x08
#define _RS 0x04

void GLCDBusyWait(byte CS)
{
   byte valor;
   TRISD=0xFF;
   TRISB=0;
   //Seleccionem controlador
   if(CS==_CS1)CS1=0;
   if(CS==_CS2)CS2=0;

   RW=1;
   RS=0;
   Nop();
   E=1;
   Nop();
   valor=PORTD;
   E=0;
   while(valor&0x80)
   {
      E=1;	
      Nop();
      valor=PORTD;
      E=0;
   }

   CS1=1;
   CS2=1;
}


// Send command  to GLCD
//
void sendGLCDCommand(byte val, byte CS) 
{
   GLCDBusyWait(CS);

   TRISB=0;
   //Seleccionem controlador
   if(CS==_CS1)CS1=0;
   if(CS==_CS2)CS2=0;

   RW=0;
   RS=0;
   Nop();
   E=1;
   Nop();
   PORTD = val;
   TRISD = 0x00;
   Nop();
   E=0;

   CS1=1;
   CS2=1;
}

// Selecciona linea de inici (z= 0 a 63)
// 
void setStartLine(byte z) 
{
   sendGLCDCommand(SET_START_LINE|z, _CS1);
   sendGLCDCommand(SET_START_LINE|z, _CS2);
}

// Set Page Address  X -row- (x= 0 a 7)
//
void setXAddress(byte page) 
{
   sendGLCDCommand(SET_X_ADDRESS|page, _CS1);
   sendGLCDCommand(SET_X_ADDRESS|page, _CS2);
}

// Set Y address Y -column- (y= 0 a 127)
//
void setYAddress(byte y) 
{
   if (y < 64) // Part esquerra
   {
      sendGLCDCommand(SET_Y_ADDRESS|y, _CS1); 
      sendGLCDCommand(SET_Y_ADDRESS|0, _CS2);
   } else { // Part dreta
      sendGLCDCommand(SET_Y_ADDRESS|63, _CS1);     
      sendGLCDCommand(SET_Y_ADDRESS|(y-64), _CS2);
   }
}

//Posiciona el cursor
// x [0:7] y [0:127]
void setAddress(byte page, byte y)
{
   setXAddress(page);
   setYAddress(y);
}

// Init GLCD
//
void GLCDinit() 
{
   RST=1;
   sendGLCDCommand(SET_ON_OFF|1, _CS1);
   sendGLCDCommand(SET_ON_OFF|1, _CS2);
   setStartLine(0);
}

// Write data on GLCD at position (p,y)(Page p= 0 a 7) (y= 0 a 127)  
//
void writeByte(byte p, byte y, byte data) 
{
   byte chip = y > 63 ? _CS2 : _CS1;
   setXAddress(p);
   setYAddress(y);

   GLCDBusyWait(chip);

   TRISB=0;
   //Seleccionem controlador
   if(chip==_CS1)CS1=0;
   if(chip==_CS2)CS2=0;

   RW=0;
   RS=1;
   Nop();
   E=1;
   Nop();
   PORTD = data;
   TRISD = 0x00;
   Nop();
   E=0;

   CS1=1;
   CS2=1;
}

byte readByteReal(byte p, byte y, byte first) 
{
   byte data;
   byte chip = y > 63 ? _CS2 : _CS1;
   if(first) 
   {
      setXAddress(p);
      setYAddress(y);
   }

   GLCDBusyWait(chip);

   TRISD = 0xFF;

   TRISB=0;
   //Seleccionem controlador
   if(chip==_CS1)CS1=0;
   if(chip==_CS2)CS2=0;

   RW=1;
   RS=1;
   Nop();
   E=1;
   Nop();
   data = PORTD;
   E=0;

   CS1=1;
   CS2=1;

   return (data);
}

// Read the GLCD RAM at position (x,y) (Page p= 0 a 7) (y= 0 a 127)
//
// Two acces are required to read data
// 1st is a dummy access. 2nd is RAM value
byte readByte(byte p, byte y)
{
   byte aux;
   readByteReal(p, y, 1);
   aux=readByteReal(p, y, 1);
   return(aux);
}

//  Clear all pixels in ri to re pages and ci to ce columns 
// ri,re [0:7] ci,ce [0:127]
void clearGLCD(byte ri, byte re, byte ci, byte ce) 
{
   int i,j;

   for (i = ri; i <= re; i++) 
      for (j=ci;j<=ce;j++)
	 writeByte(i,j,0);
}

// Encen el pixel a la posicio (x,y), (x [0:63]) (y [0:127])
void SetDot(byte x, byte y) 
{
   int page = x/8;
   int aux = 0x01 << (x%8);
   int read = readByte (page, y);
   writeByte (page, y, aux | read);
}
// Apaga el pixel a la posicio (x,y), (x [0:63]) (y [0:127])
void ClearDot(byte x, byte y) 
{
   int page = x/8;
   int aux = ~(0x01 << (x%8));
   int read = readByte (page, y);
   writeByte (page, y, aux & read);
}

// Escriu el caracter c en la posicio (p,y) (pagina p= 0 a 7) (character column y= 0 a 24)
// Els caracters estan definits en la taula font5x7[], al fitxer ascii.h
void putchGLCD(byte p, byte y, char c) 
{
   int fontPos = (c-' ')*5;
   int i;
   y = y*5;
   int aux;
   for (i = 0; i < 5; ++i)
   {
      aux = font5x7[fontPos];
      writeByte (p, y, aux);
      ++y;
      ++fontPos;
   }
}

// Escriu el nombre enter i en la posicio (p,y) (page p= 0 a 7) (character column y= 0 a 24)
// Cal fer la conversió de INT to ASCII 
// Els caracters estan definits en la taula font5x7[], al fitxer ascii.h
void writeNum (byte p, byte y, int i) {
   //int page = 0;
   //int y = 0;
   int aux;
   char arr[32];
   if (i <0) 
   {
      putchGLCD (p, y, '-');
      ++y;
      i*= -1;
   }
   int j = 0;
   if (i == 0) {arr[0] = '0';++j;}
   while (i > 0)
   {
      arr[j] = i%10+'0';
      ++j;
      i/=10;
   }
   while (j > 0)
   {
      j--;
      i = arr[j];
      putchGLCD (p, y, i);
      ++y;
      if (y > 127) ++p, y = 0;
   }
}
