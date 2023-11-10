// A proposal for main.c ..... just to inspire you
#include <xc.h>
#include "config.h"
#include "GLCD.h"
....
#define _XTAL_FREQ 8000000 // Needed for __delay_ms function

typedef enum{
    Ready=0,
    Running,
    Stopped
}state_t;

// Global Variables 
unsigned int decimes=0;
....
void tic(void) {
 ++decimes; 
}

void interrupt RSI_high(){
// RSI High Priority for handling Timer0
... if (timer0_flag) {
        tic();
    }
}
// Falling edge detection and debouncing
??? inputDetector(·) {
....
}

// Initialize PORTs, timer0 and basic PIC resources
void configPIC() {
....
}
void main(void) {
    configPIC();
    // MAIN LOOP
    while (1) {
        if ( inputDetector(·) ) { // check falling edge
            switch(estatCrono) {
            // depending on the current state, handle the transition
            }
        }
    updateGLCD(·);// show things on the GLCD smartly!
    }
}