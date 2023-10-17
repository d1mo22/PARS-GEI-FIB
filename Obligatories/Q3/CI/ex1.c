#include "config.h"

void interrupt_low RSI_low() {
    if (INT2IF && INT2IE) {
        PORTD = 0x00;
        INT2IF = 0;
    }
}

void interrput RSI_high() {
    if (INT1IE && INT1IF) {
        PORTD = 0x01;
        INT1IF = 0;
    }
}

void config_pic() {
    //PORTD
    ANSELD = 0x00;
    TRISD = 0x00; //0xFC
    PORTD = 0x00;

    //PORTB
    ANSELB = 0x00;
    TRISB = 0x06;

    //Enable INTERUPT
    IPEN = 1;

    //Definir PRIO
    INT1IP = 1;
    INT2IP = 0;

    //Enable
    INT1IE = 1;
    INT2IE = 1;

    //Inicialitzar flags
    INT1IF = 0;
    INT2IF = 0;

    //Activar INTERUPT
    GIEL = 1;
    GIEH = 1;
}

void main(void) {
    config_pic();
    while(1);
}