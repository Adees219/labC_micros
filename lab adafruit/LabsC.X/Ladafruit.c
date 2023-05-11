/*programacion de funciones*/
#include "LEEPROM.h"
#include <stdio.h>
#include <xc.h>
#include <stdint.h>
#include <pic16f887.h>
#include "Ladafruit.h"


/**************************************************setup******************************************/
void config_IO(void)
{
    /*IO*/
    ANSEL = 0;
    ANSELH = 0;
    
    TRISA = 0;
    TRISB = 0XFF;
    TRISC = 0XFF;
    TRISD = 0;
    TRISE = 0;
    
    /*limpieza*/
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    

    
    return;
}

void config_reloj(void){
     /*reloj*/
    OSCCONbits.IRCF2 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF0 = 1;   //8 MHZ
    OSCCONbits.SCS = 1;     //OSC interno
    return;
}
/*
void selec_just(void){
    ADCON1bits.ADFM = 0;    //just: izq
    return;
}

void selec_volti(void){
 ADCON1bits.VCFG1 = 0;      //VSS
 ADCON1bits.VCFG0 = 0;      //VDD
 return;
}*/

void config_timer0(void){
        /*TMR0*/
    OPTION_REGbits.T0CS = 0;        //temporizador
    //OPTION_REGbits.T0SE = 0;        //cambio de señal positivo
    OPTION_REGbits.PSA = 0;         //prescaler a temporizador
    
    OPTION_REGbits.PS2 = 1;
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS0 = 1; //216
    return;
}



void config_innable(void){
    /*INT ENABLE*/
    OPTION_REGbits.nRBPU = 0;
    WPUB = 0XFF; //pull-up 
    IOCB = 0xFF;
    
    GIE = 1;
    PEIE = 1;
    ADIE = 1;
    RBIE = 1;
            
    RBIF = 0;
    ADIF = 0;
    
    return;
}


//void selec_ch(){
    /*canal*/
  //  ADCON0bits.CHS = 0b0000; //AN0
   // return;
//}

/*
void selec_reloj(void){
    
    ADCON0bits.ADCS1 = 1;
    ADCON0bits.ADCS0 = 0;   
    return;
}
*/
void initUART(void){
    //paso 1
    SPBRG = 12; //SPBRGH:SPBRG  = [(8Mhz/9600)/64]-1 = 12 ? real 9615.38
    SPBRGH = 0; //%error = (9615.38-9600)/9600 * 100 = 0.16%
    BRGH = 0;   
    BRG16 = 0;
    
    //paso 2
    CREN = 1;
    SYNC = 0;   // TXSTAbits ? habilitar transmision & TXIF = 1
    SPEN = 1;   //RCSTAbits ? apagar bandera TX
    TXSTAbits.TXEN = 1; //permite transmitir
    
    //paso 3: habilitar los 9 bits
    RCSTAbits.RX9 = 0;
    
    //paso 4
    TXEN = 1;
    TXIF = 0;
    
    //C
    
    //paso 5: interrupciones
    PIE1bits.RCIE = 1;
    PIR1bits.RCIF = 0;

}

