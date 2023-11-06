const char * s1 = "David Morais";
const char * s2 = "Raul Box";
const char * s3 = "L4A GLCD";
const char * s4 = "--------";

void writeTxt(byte page, byte y, char * s) {
   int i=0;
   while (*s!='\n' && *s!='\0') 
   {
      putchGLCD(page, y+i, *(s++));
      i++;
   };
}

int espais(int x) {
    if (x > 99 || x < -9) return 2;
	else if (x > 9 || x < 0) return 1;
	else return 0;
}

void clean(int x, int y) {
    if (x > 99 && y < 0) clearGLCD(0,0,90,95);
    if (x > 9 && y < 0 || x > 99 && y = 0) clearGLCD(0,0,85,90);
    if (x < 100 && y > -10) clearGLCD(0, 0, 80, 85);
    if (x < 10 && 0 <= y && y < 10) clearGLCD(0, 0, 75, 80);
    //No funciona x >= 100 e y 10 o -10
}


void print(int x, int y, int space_x, int space_y) {
    space_x = espais(x);
    space_y = espais(y);
        
    clean(x,y);
    writeTxt(0, 10, "(");
	writeNum(0, 11, x);
	writeTxt(0, 12 + space_x, ",");
	writeNum(0, 13 + space_x, y);
	writeTxt(0, 14 + space_y + space_x, ")");
}

void main(void) {
    ANSELA=0x00; 
    ANSELB=0x00;                  
    ANSELC=0x00;                  
    ANSELD=0x00;                  
    
    TRISD=0x00;		   
    TRISB=0x00;
    TRISA=0x0F;
        
    PORTD=0x00;
    PORTB=0x00;  
    
    GLCDinit();		   //Inicialitzem la pantalla
    clearGLCD(0,7,0,127);   //Esborrem pantalla
    setStartLine(0);        //Definim linia d'inici

    writeTxt(2, 9, s3);	//Nom de la practica
    writeTxt(3, 9, s4);	//Linia de separacio
    writeTxt(4, 9, s2);	//Nom Raul
    writeTxt(5, 7, s1);	//Nom David
    __delay_ms(2000);
    clearGLCD(0,7,0,127); //Esborrem la pantalla
    
    SetDot(-31,0);

    int estatAnteriorPujada = 0, estatAnteriorBaixada = 0;
    int estatActualPujada = 0, estatActualBaixada = 0;

    int space_x = 0, space_y = 0;
    int xValue = 0, xAnterior = 0;
    int yValue = 0, yAnterior = 0;
    int contador = 0, salt = 0;

    while (1) { 
        xAnterior = xValue;
        yAnterior = yValue;
        estatActualBaixada = PORTAbits.RA3;
        estatActualPujada = PORTAbits.RA2;
        
        if (estatAnteriorPujada == 0) {
            __delay_ms(10);
            if (estatActualPujada == 1) {
                salt = 1;
            }
        }

        if (estatAnteriorBaixada == 1) {
            __delay_ms(10);
            if (estatActualBaixada == 0) {
                salt = -1;
            }
        }

        if (PORTAbits.RA0) {
            if (xValue < 127) ++xValue;
            __delay_ms(20);
        }
        if (PORTAbits.RA1) {
            if (xValue > 0) --xValue;
            __delay_ms(20);
        }
        if (salt == 1) {
            ++yValue;
            ++contador;
            __delay_ms(50);
            if (contador == 10 && yValue != 0) salt = -1;
            else if (contador == 0 && yValue == 0) salt = 0;
        }
        else if (salt == -1) {
            --yValue;
            --contador;
            __delay_ms(50);
            if (contador == -10 && yValue != 0) salt = 1;
            else if (contador == 0 && yValue == 0) salt = 0;
        }

        print(xValue, yValue, space_x, space_y);
        
        ClearDot(-(yAnterior + 31), xAnterior);
        SetDot(-(yValue + 31), xValue);

        estatAnteriorBaixada = estatActualBaixada;
        estatAnteriorPujada = estatActualPujada;
    }
}