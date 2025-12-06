#include "conf.h"

void init_mcu(void)
{
   //pines de los fin de carrera
    GpioInitStructure_AVR sensores;
    sensores.port = SENS_PORT;
    sensores.modo = avr_GPIO_mode_Input;
    sensores.pines = S3_PIN | S2_PIN | S1_PIN;
    init_gpio(sensores);

   //pines de control
    GpioInitStructure_AVR controles;
    controles.port = CTRL_PORT;
    controles.modo = avr_GPIO_mode_Input;
    controles.pines = MODO_PIN | SUBIR_PIN | BAJAR_PIN;
    init_gpio(controles);

   //pines del motor
    GpioInitStructure_AVR motor;
    motor.port = MOTOR_PORT;
    motor.modo = avr_GPIO_mode_Output;
    motor.pines = IN1_PIN | IN2_PIN | ENA_PIN;
    init_gpio(motor);
    
    motor_stop();

   //ADC
    AdcInitStructure_AVR adc_conf;
    adc_conf.mode = avr_ADC_MODE_Single_Conversion;
    adc_conf.prescaler = avr_ADC_Prescaler_128;
    adc_conf.channel = CANAL_LUZ;
    adc_conf.resolution = avr_ADC_RES_10Bit;
    adc_conf.reference = avr_ADC_REF_AVcc;
    adc_conf.avr_adc_handler = 0;  
    
    init_adc(adc_conf);
}

//ldr
void leer_sensores_luz(void)
{
    valor_luz = leer_ADC(CANAL_LUZ);
}

// motor
void motor_stop(void)
{
    MOTOR_ENA = 0; 
    MOTOR_IN1 = 0;
    MOTOR_IN2 = 0;
}

void motor_subir(void)
{
    MOTOR_IN1 = 1;
    MOTOR_IN2 = 0;
    MOTOR_ENA = 1;
}

void motor_bajar(void)
{
    MOTOR_IN1 = 0;
    MOTOR_IN2 = 1;
    MOTOR_ENA = 1; 
}
