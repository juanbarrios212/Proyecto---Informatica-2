#include "conf.h"

//posición actual
static int posicion_actual(void){
    if (PIN_S1) return 1;
    if (PIN_S2) return 2;
    return 3;
}

//leer luz
static int nivel_luz(void){
    uint16_t adc = leer_adc();

    if (adc < 300) return 3;
    if (adc < 700) return 2;
    return 1;
}

estado_t e_inicio(void){
    accion_t ac = {0,0};
    driver_ejecutar(ac);
    return MANUAL_STOP;
}

estado_t e_manual_stop(void){
    accion_t ac = {0,0};
    driver_ejecutar(ac);

    if (PIN_MODO) return AUTO_STOP;

    int pos = posicion_actual();

    if (driver_leer().up && pos > 1) return MANUAL_SUBIENDO;
    if (driver_leer().down && pos < 3) return MANUAL_BAJANDO;

    return MANUAL_STOP;
}

estado_t e_manual_subiendo(void){
    accion_t ac = {1,0};
    driver_ejecutar(ac);

    if (PIN_S1) return MANUAL_STOP;
    return MANUAL_SUBIENDO;
}

estado_t e_manual_bajando(void){
    accion_t ac = {0,1};
    driver_ejecutar(ac);

    if (PIN_S3) return MANUAL_STOP;
    return MANUAL_BAJANDO;
}

estado_t e_auto_stop(void){
    accion_t ac = {0,0};
    driver_ejecutar(ac);

    if (!PIN_MODO) return MANUAL_STOP;

    int deseada = nivel_luz();
    int actual = posicion_actual();

    if (deseada < actual) return AUTO_BAJANDO;
    if (deseada > actual) return AUTO_SUBIENDO;
    return AUTO_STOP;
}

estado_t e_auto_subiendo(void){
    accion_t ac = {1,0};
    driver_ejecutar(ac);

    if (PIN_S1 || !PIN_MODO) return AUTO_STOP;
    return AUTO_SUBIENDO;
}

estado_t e_auto_bajando(void){
    accion_t ac = {0,1};
    driver_ejecutar(ac);

    if (PIN_S3 || !PIN_MODO) return AUTO_STOP;
    return AUTO_BAJANDO;
}
