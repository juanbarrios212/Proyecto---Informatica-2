#include "conf.h"

int valor_luz = 0;

int main(void)
{
    init_mcu();
    estado_t estado_actual = INICIO;
    estado_t (*tabla_estados[])(void) = {e_inicio, e_espera, e_subir, e_bajar};
   
    while(1)
    {
        estado_actual = (*tabla_estados[estado_actual])();
    }
    return 0;
}
