#include "conf.h"

int main(void){
    init_mcu();
    estado_t est = INICIO;

    estado_t (*fsm[])(void) = {
        e_inicio,
        e_manual_stop,
        e_manual_subiendo,
        e_manual_bajando,
        e_auto_stop,
        e_auto_subiendo,
        e_auto_bajando
    };

    while(1){
        est = fsm[est]();
    }
}

