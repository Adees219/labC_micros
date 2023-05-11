/* 
 * File:   adafruit.c
 * Author: USUARIO FINAL
 *
 * Created on 3 de mayo de 2023, 01:37 PM
 */


// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

/*******************************LIBRERIAS***********************************/
#include <stdio.h>
#include <xc.h>
#include <stdint.h>
#include <stdlib.h>
#include <pic16f887.h>
#include "Ladafruit.h"

/******************************DEFINIR CONSTANTES***************************/
#define _XTAL_FREQ 8000000


/******************************Variables Globlales**************************/
char recept;
uint8_t transmit;
char data[4];
char puerto;
/******************************PROTOTIPOS***********************************/
void setup(void);
void initUART(void);

void cadena(char txt[]);
void valor_PORT (uint8_t numero, char puerto);
void TXT(void);
/******************************INTERRUPCIONES*******************************/

void __interrupt() isr(void)
{
  if(PIR1bits.RCIF){
      TXT();
  
    }
  if(INTCONbits.RBIF){
      
        if(RB0 == 0){
            while(RB0 == 0);
            PORTA++;
        }
        if(RB1 == 0){
            while(RB1 == 0);
            PORTA--;
        }
        if(RB2 == 0){
            while(RB2 == 0);
            transmit  = PORTA;
            valor_PORT(transmit, 'A');
        }
        if(RB3 == 0){
            while(RB3 == 0);
            transmit  = PORTD;
            valor_PORT(transmit, 'D');
        }
        if(RB4 == 0){
            while(RB4 == 0);
            TXREG = 'Q';
        }
        RBIF = 0;
        
  }
  
  return;
}

/******************************CODIGO PRINCIPAL*****************************/

void main(void){
    setup();
    TXREG = '\0';

    while(1){
        
        while(!PIR1bits.RCIF);
        __delay_ms(500); 
        
  
    }
       
    return;
}
/*******************************Funciones***********************************/
void setup(void)
{  // ADCON0bits.ADON = 1; //activamos el ADC 
    

    config_IO();
    config_reloj();   
    config_timer0();
    config_innable();
    initUART();
    
    return;
}

void cadena(char txt[]){
    int i;  //variable iteracion
    
    for(i = 0; txt[i] != '\0'; i++){
        
        while(!PIR1bits.TXIF); // Esperamos a que el registro de transmisión esté vacío
        
        TXREG = txt[i]; // envia caracter por caracter a la terminal
    }
    return;
}

void valor_PORT (uint8_t numero, char puerto){
    char oracion[15];
    
    sprintf(data, "%d\r", numero); //pasa a caracter el valor que leyo
    sprintf(oracion, "valor puerto %c: ", puerto);
    cadena(oracion);
    cadena(data);
    return;
}

void TXT(void){
    while(!PIR1bits.RCIF); 
    recept = RCREG; 
    if(recept == '+'){
        PORTD++;
    }
    else if(recept == '-'){
        PORTD--;
    }
    else if(recept == '1'){
        RE0=1;
    }
    else if(recept == '0'){
        RE0=0;
    }
}





