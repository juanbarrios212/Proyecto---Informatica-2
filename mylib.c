#include "mylib.h"

void ADC_init(void) {
    ADMUX = (1 << REFS0); // Referencia AVcc
    ADCSRA = (1 << ADEN) | (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
}

uint16_t ADC_read(uint8_t channel) {
    ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1<<ADSC));
    return ADC;
}

entradas_t leer_entradas(void) {
    entradas_t in;
    in.L   = ADC_read(0);
    in.A   = PINB & (1<<PB0);
    in.SUB = PINB & (1<<PB1);
    in.BAJ = PINB & (1<<PB2);
    in.S1  = PINC & (1<<PC2);
    in.S2  = PINC & (1<<PC1);
    in.S3  = PINC & (1<<PC0);
    return in;
}

void motor_subir(void) {
    PORTD |= (1<<PD0);   
    PORTD &= ~(1<<PD1);   
    PORTD |= (1<<PD2);   
}

void motor_bajar(void) {
    PORTD &= ~(1<<PD0);  
    PORTD |= (1<<PD1);   
    PORTD |= (1<<PD2);   
}

void motor_stop(void) {
    PORTD |= (1<<PD0) | (1<<PD1);
    PORTD |= (1<<PD2);            
    _delay_ms(5);                
    PORTD &= ~(1<<PD2);           
}

estado_t f_inicio(void) {
    ADC_init();
    DDRA = 0x00;
    DDRB = 0x00; 
    DDRC = 0x00;
    DDRD = 0xFF;

    PORTB |= (1<<PB1)|(1<<PB2);

    return ESPERA;
}

estado_t f_control(entradas_t in, posicion_t *pos, entradas_t *last) {
    static estado_t estado_manual = ESPERA;
    static posicion_t pos_destino_manual = POS_BAJA;
    static posicion_t pos_destino_auto = POS_BAJA;
    estado_t estado = ESPERA;

    if (in.S1) *pos = POS_ALTA;
    else if (in.S2) *pos = POS_MEDIA;
    else if (in.S3) *pos = POS_BAJA;

    bool pulsoSUB = in.SUB && !last->SUB;
    bool pulsoBAJ = in.BAJ && !last->BAJ;

    if (in.A) {
        // MODO AUTOMATICO
        if (in.L <= 300) pos_destino_auto = POS_ALTA; 
        else if (in.L <= 700) pos_destino_auto = POS_MEDIA;
        else pos_destino_auto = POS_BAJA;                 
        if (*pos < pos_destino_auto) {
            motor_subir();
            estado = SUBIR;
            if ((pos_destino_auto == POS_MEDIA && in.S2) ||
                (pos_destino_auto == POS_ALTA && in.S1) ||
                (pos_destino_auto == POS_BAJA && in.S3)) {
                motor_stop();
                estado = ESPERA;
            }
        }
        else if (*pos > pos_destino_auto) {
            motor_bajar();
            estado = BAJAR;
            if ((pos_destino_auto == POS_MEDIA && in.S2) ||
                (pos_destino_auto == POS_ALTA && in.S1) ||
                (pos_destino_auto == POS_BAJA && in.S3)) {
                motor_stop();
                estado = ESPERA;
            }
        }
        else {
            motor_stop();
            estado = ESPERA;
        }

    } else {
        // MODO MANUAL
        if (estado_manual == ESPERA) {
            if (pulsoSUB) {
                if (*pos == POS_BAJA) pos_destino_manual = POS_MEDIA;
                else if (*pos == POS_MEDIA) pos_destino_manual = POS_ALTA;
                else pos_destino_manual = *pos;
                if (*pos != pos_destino_manual) estado_manual = SUBIR;
            } 
            else if (pulsoBAJ) {
                if (*pos == POS_ALTA) pos_destino_manual = POS_MEDIA;
                else if (*pos == POS_MEDIA) pos_destino_manual = POS_BAJA;
                else pos_destino_manual = *pos;
                if (*pos != pos_destino_manual) estado_manual = BAJAR;
            }
        }

        if (estado_manual == SUBIR) {
            motor_subir();
            if ((pos_destino_manual == POS_MEDIA && in.S2) ||
                (pos_destino_manual == POS_ALTA && in.S1)) {
                motor_stop();
                estado_manual = ESPERA;
                estado = ESPERA;
            } else estado = SUBIR;
        } 
        else if (estado_manual == BAJAR) {
            motor_bajar();
            if ((pos_destino_manual == POS_MEDIA && in.S2) ||
                (pos_destino_manual == POS_BAJA && in.S3)) {
                motor_stop();
                estado_manual = ESPERA;
                estado = ESPERA;
            } else estado = BAJAR;
        } 
        else {
            motor_stop();
            estado = ESPERA;
        }
    }
    *last = in;
    return estado;
}

