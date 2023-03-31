/* 
 * File:   ADC.h
 * Author: USUARIO FINAL
 *
 * Created on 26 de marzo de 2023, 09:30 PM
 */

#ifndef ADC_H
#define	ADC_H



/******************************PROTOTIPOS***********************************/
void setup(void);

    void config_IO(void);
    void config_reloj(void);
    void config_timer0(void);
    void config_innable(void);

    void selec_ch(void);
    void selec_volti(void);
    void selec_reloj(void);
    void selec_just(void);

void displ(int puerto);    



#endif	/* ADC_H */

