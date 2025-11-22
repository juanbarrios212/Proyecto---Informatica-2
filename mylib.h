#ifndef MY_LIB
#define MY_LIB

#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum { ESPERA=0, SUBIR, BAJAR } estado_t;
typedef enum { POS_BAJA=0, POS_MEDIA, POS_ALTA } posicion_t;
typedef struct {
    uint16_t L;  
    bool A;      
    bool SUB;    
    bool BAJ;   
    bool S1;     
    bool S2;    
    bool S3;     
} entradas_t;

void ADC_init(void);
uint16_t ADC_read(uint8_t channel);
entradas_t leer_entradas(void);

estado_t f_inicio(void);
estado_t f_control(entradas_t in, posicion_t *pos, entradas_t *last);

void motor_subir(void);
void motor_bajar(void);
void motor_stop(void);

#endif

