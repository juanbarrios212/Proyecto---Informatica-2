#include "mylib.h"

int main(void) {
    // Inicialización del sistema
    entradas_t in, last = {0};
    posicion_t pos = POS_BAJA;       
    estado_t estado = f_inicio();    

    while(1) {
        in = leer_entradas();             
        estado = f_control(in, &pos, &last); 
        last = in;                        
        _delay_ms(50);                    
    }

    return 0;
}

