/* 
 * File:   L_ADC.c
 * Author: Anderson Daniel Eduardo Escobar Sandoval
 *
 * Created on 26 de marzo de 2023, 09:32 PM
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
#include <pic16f887.h>
#include "ADC.h"


/******************************Variables Globlales**************************/
uint8_t var;        //amacena los datos del potenciometro
uint8_t residuo;    //almacena el residuo de la division
uint8_t centena;    //almacena las centenas de la conversion del DAC
uint8_t decena;     //almacena las decenas de la conversion del DAC
uint8_t unidad;     //almacena las unidades de la conversion del DAC
uint8_t displ_var[3];   //almacena el valor a mostrar en cada display
uint8_t flags;      //bandera para hacer la multiplexacion

/***********************************tabla************************************/
uint8_t tabla[16] =    //valores a retornar de la tabla
{
    0b00111111,  //0
    0b00000110,  //1
    0b01011011,  //2
    0b01001111,  //3
    0b01100110,  //4
    0b01101101,  //5
    0b01111101,  //6
    0b00000111,  //7
    0b01111111,  //8
    0b01101111,  //9
    0b01110111,  //A
    0b01111100,  //B
    0b00111001,  //C
    0b01011110,  //D
    0b01111001,  //E
    0b01110001   //F
};

/******************************DEFINIR CONSTANTES***************************/

#define _trm0_value 200
#define _XTAL_FREQ 8000000


/******************************INTERRUPCIONES*******************************/
void __interrupt() isr(void)
{
    if(ADIF) //activa bandera de conversion
    { 
        if (ADCON0bits.CHS == 0b0000)   //si estamos en el canal principal
            PORTB = ADRESH;            
        else
            //PORTC = ADRESH;           //si cambio de canal
            var = ADRESH;   
        
        ADIF = 0;
         
    }
    
    
    if(T0IF)
    {   
        RE1 = !RE1; //se asigna su valor negado

 
        PORTD = 0;
        
        if(flags == 0){             //dipl centena
            PORTC = displ_var[2];   
            RD0 = 1;                //encendemos el puerto de la multiplexacion
            flags = 1;              //cambio de bandera
            
        }
        else if(flags == 1){             //dipl decena
            PORTC = displ_var[1];
            RD1 = 1;        
            flags = 2; 
        }
        else if(flags == 2){             //dipl unidad
            PORTC = displ_var[0];
            RD2 = 1;        
            flags = 0;
        }
        
        
        TMR0 = _trm0_value;   //reinicio tmr0
        T0IF = 0;   //apaga la bandera de interrupción
    }
    return;
}






/******************************CODIGO PRINCIPAL*****************************/

void main(void){

    setup();
    ADCON0bits.GO = 1;
    
   
   
    while(1)
    {   

        
        displ(var); //funcion que separa el valor del ADC
        
        displ_var[0]= tabla[unidad];        //retorna el valor de la variable en la posicion N
        displ_var[1]= tabla[decena];
        displ_var[2]= tabla[centena];
      
        
      //alternador
      if(ADCON0bits.GO == 0) //cuando terminala conversion
      {
            if(ADCON0bits.CHS == 0b0000)    //si estamos en el canal principal
                ADCON0bits.CHS = 0b0001;    //cambiamos
            else 
                ADCON0bits.CHS = 0b0000;   //vuelve al canal principal
        
        __delay_ms(10);
        ADCON0bits.GO = 1; //empieza la conversion
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
    
    //subrutina de reseteo
    TMR0 = _trm0_value;
    
    return;
    
}

    void displ(int valor){ 
    
    centena = (uint8_t) (valor/100);
    residuo = valor%100;
     
    decena = (uint8_t) residuo/10;
    residuo %= 10;
   
    unidad = residuo/1;
    
    return;
}
    
