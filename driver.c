#include "conf.h"

static uint16_t leer_adc(void) {
    AdcInitStructure_AVR adc;
    adc.channel = PIN_LDR;
    adc.clock = avr_ADC_Clock_Prescaler128;
    adc.mode = avr_ADC_mode_SingleConversion;
    init_adc(adc);
    return read_adc_blocking();
}

accion_t driver_leer(void){
    accion_t in = {0,0};

    in.up   = PIN_SUB;
    in.down = PIN_BAJ;

    return in;
}

void driver_ejecutar(accion_t ac){
    MOTOR_UP   = ac.up;
    MOTOR_DOWN = ac.down;

    if (ac.up || ac.down) MOTOR_EN = 1;
    else MOTOR_EN = 0;
}
