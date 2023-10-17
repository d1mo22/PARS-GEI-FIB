#include "config.h"

int ORDRE[4];
int contador = 0;

//Aquest codi té un problema que dona ventatge al ordre en el que
//Estan posat els ifs, doncs si mentres estem tractant el 0
//arriben el 2 i despres el 1 en un espai de 10us guanyara el 1
//Perque esta primer el 1 als ifs

void interrupt RSI_high() {
    if (INT0IF && INT0IE) {
        ORDRE[contador++] = 0;
        INT0IF = 0;
    }
    if (INT1IF && INT1IE) {
        ORDRE[contador++] = 1;
        INT1IF = 0;
    }
    if (INT2IF && INT2IE) {
        ORDRE[contador++] = 2;
        INT2IF = 0;
    }
    if (INT3IF && INT3IE) {
        ORDRE[contador++] = 3;
        INT3IF = 0;
    }
}

void main() {
    config_pic();
    while (cont < 4);
    print(ORDRE); 
}