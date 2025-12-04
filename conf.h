#ifndef CONF_H
#define CONF_H

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "avr_api.h"

typedef enum {
    INICIO = 0,
    MANUAL_STOP,
    MANUAL_SUBIENDO,
    MANUAL_BAJANDO,
    AUTO_STOP,
    AUTO_SUBIENDO,
    AUTO_BAJANDO
} estado_t;

typedef struct {
    uint8_t up;
    uint8_t down;
} accion_t;

// prototipos
void init_mcu(void);
accion_t driver_leer(void);
void driver_ejecutar(accion_t ac);

// estados
estado_t e_inicio(void);
estado_t e_manual_stop(void);
estado_t e_manual_subiendo(void);
estado_t e_manual_bajando(void);
estado_t e_auto_stop(void);
estado_t e_auto_subiendo(void);
estado_t e_auto_bajando(void);

// pines
#define PIN_LDR   0     // ADC0, PA0
#define PIN_MODO avr_GPIOB_IN_0
#define PIN_SUB avr_GPIOB_IN_1
#define PIN_BAJ avr_GPIOB_IN_2

#define PIN_S1 avr_GPIOC_IN_2  
#define PIN_S2 avr_GPIOC_IN_1  
#define PIN_S3avr_GPIOC_IN_0  

#define MOTOR_PORT avr_GPIO_D
#define MOTOR_UP avr_GPIOD_OUT_0
#define MOTOR_DOWN avr_GPIOD_OUT_1
#define MOTOR_EN avr_GPIOD_OUT_2

#endif

