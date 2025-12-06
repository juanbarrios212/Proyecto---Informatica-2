#ifndef CONF_H
#define CONF_H 1
#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "avr_api.h"

typedef enum {
    INICIO = 0,
    ESPERA = 1,
    SUBIR  = 2,
    BAJAR  = 3
} estado_t;

#define UMBRAL_NOCHE  300
#define UMBRAL_DIA    700

//fines de carrera
#define SENS_PORT     avr_GPIO_C
#define S3_PIN        avr_GPIO_PIN_0
#define S2_PIN        avr_GPIO_PIN_1
#define S1_PIN        avr_GPIO_PIN_2 

#define LEER_S3       avr_GPIOC_IN_0
#define LEER_S2       avr_GPIOC_IN_1
#define LEER_S1       avr_GPIOC_IN_2

//botones (subir y bajar) y modo
#define CTRL_PORT     avr_GPIO_B
#define MODO_PIN      avr_GPIO_PIN_0
#define SUBIR_PIN     avr_GPIO_PIN_1
#define BAJAR_PIN     avr_GPIO_PIN_2

#define LEER_MODO_AUTO avr_GPIOB_IN_0
#define LEER_BTN_SUB   avr_GPIOB_IN_1
#define LEER_BTN_BAJ   avr_GPIOB_IN_2

//L298 para motor
#define MOTOR_PORT    avr_GPIO_D
#define IN1_PIN       avr_GPIO_PIN_0
#define IN2_PIN       avr_GPIO_PIN_1
#define ENA_PIN       avr_GPIO_PIN_2

#define MOTOR_IN1     avr_GPIOD_OUT_0
#define MOTOR_IN2     avr_GPIOD_OUT_1
#define MOTOR_ENA     avr_GPIOD_OUT_2

//LDR
#define CANAL_LUZ     avr_ADC_canal0 

extern int valor_luz;

//prototipos de funciones
void init_mcu(void);
void leer_sensores_luz(void);
void motor_stop(void);
void motor_subir(void);
void motor_bajar(void);

//prototipos de estados
estado_t e_inicio(void);
estado_t e_espera(void);
estado_t e_subir(void);
estado_t e_bajar(void);

#endif
