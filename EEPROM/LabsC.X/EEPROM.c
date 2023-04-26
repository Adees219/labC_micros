/* 
 * File:   EEPROM.c
 * Author: Anderson Daniel Eduardo Escobar Sandoval
 *
 * Created on 23 de abril de 2023, 07:24 PM
 */

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
#include <pic16f887.h>
#include "LEEPROM.h"


/******************************PROTOTIPOS***********************************/
uint8_t Lec_EEPROM(uint8_t address);
void wrt_EEPROM(uint8_t adress ,uint8_t dato);

/******************************Variables Globlales**************************/

uint8_t address = 0;
uint8_t dato = 0;
char mimir;

/***********************************tabla************************************/


/******************************DEFINIR CONSTANTES***************************/


#define _XTAL_FREQ 8000000


/******************************INTERRUPCIONES*******************************/
void __interrupt() isr(void){
     
    if(ADIF){ //activa bandera de conversion
       PORTC = ADRESH; //El puerto C recibe el resultado de la conversion del ADC    
       ADIF = 0; //apagamos la bandera  
    }
    
    if(RBIF){                 //si se presiona un boton
        
        if(RB0 == 0){          //sleep
           mimir = 1; 
           RE0 = 1;           //señal que indica que se ha establecido el modo sleep
        }
        else if(RB1 == 0){   //wake up
            mimir = 0;
            RE0 = 0;         //señal que indica que se ha salido del modo sleep
        }
        else if(RB2 == 0){   //escribir
          
            mimir = 0;      //sale del estado sleep
            RE0 = 0;
            
            dato = PORTC;               //la variable obtiene el valor del adc
            wrt_EEPROM(address, dato); //lo manda a la funcion de escritura
            
        }
        else if(RB3 == 0){//lectura
            PORTD = 0;                   //limpia el puerto
            dato = Lec_EEPROM(address); //llama a la funcion de lectura
            PORTD = dato;               //muestra el dato almacenado
        }
        
        RBIF = 0;
    }
    
}


/******************************CODIGO PRINCIPAL*****************************/

void main(void){

    setup();
    ADCON0bits.GO = 1;

    while(1)
    {   

      if(ADCON0bits.GO == 0)    //cuando terminala conversion
      {  
        __delay_ms(10);
        ADCON0bits.GO = 1;      //empieza la conversion
      }
      
      if(mimir == 1){        //verifica la variable para determinar el estado del pic
        SLEEP();            //Pone al pic en modo reposo
      }
   
    }
    
}




/*******************************Funciones***********************************/
void setup(void)
{   ADCON0bits.ADON = 1; //activamos el ADC 
    

    config_IO();
    config_reloj();   
    config_timer0();
    config_innable();
    
    selec_ch();
    __delay_ms(10); //delay
    
    selec_volti();
    selec_reloj();
    selec_just();      
    
    
    return;
    
}

  
uint8_t Lec_EEPROM(uint8_t address){
    while(WR || RD); //verificar para ver si hay un proceso (lectura/escritura) en progreso
    
    EEADR = address; 
    EECON1bits.EEPGD = 0;   //se lee la eeprom
    EECON1bits.RD = 1;      //se obtiene el dato
    return EEDAT;           //se retorna el valor
        
}  

void wrt_EEPROM(uint8_t address , uint8_t data){
    uint8_t gieStatus; //variable para almacenar las interrupciones
    
    while(WR); //revisar si hay un proceso de escritura en progreso
    
    EEADR = address;    //direccion A guardar de la eeprom
    EEDAT = data;       //dato a escribir
    EECON1bits.EEPGD = 0;   //acceso a la memoria de datos
    EECON1bits.WREN = 1;    //habilitacion de escritura en la eeprom
    gieStatus = GIE;        
    INTCONbits.GIE = 0; //deshabilitando interrupciones
    EECON2 = 0X55;      //secuencia de escritura
    EECON2 = 0XAA;
    EECON1bits.WR = 1;  //inicio de escritura
    EECON1bits.WREN = 0; //dehabilitar escritura
    
    INTCONbits.GIE = gieStatus; //habilitar interrupciones
}


