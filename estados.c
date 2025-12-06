#include "conf.h"

static int destino_manual = 0; 

//ESTADO INICIO
estado_t e_inicio(void)
{
    motor_stop();
    return ESPERA;
}

//ESTADO ESPERA
estado_t e_espera(void)
{
    motor_stop();
    leer_sensores_luz();

    int A = LEER_MODO_AUTO; 
    int S1 = LEER_S1;
    int S2 = LEER_S2;
    int S3 = LEER_S3;
    int L = valor_luz;
    int Pulsador_Subir = LEER_BTN_SUB;
    int Pulsador_Bajar = LEER_BTN_BAJ;

   //funcionamiento en modo automatico
    if (A == 1)
    {
        if (L > UMBRAL_DIA && S2 == 1) return SUBIR;
        if (L > UMBRAL_DIA && S3 == 1) return SUBIR;
        if (L > UMBRAL_NOCHE && L <= UMBRAL_DIA && S3 == 1) return SUBIR;
        if (L <= UMBRAL_NOCHE && S2 == 1) return BAJAR;
        if (L <= UMBRAL_NOCHE && S1 == 1) return BAJAR;
        if (L > UMBRAL_NOCHE && L <= UMBRAL_DIA && S1 == 1) return BAJAR;
    }
    
   //funionamiento en modo manual
    else 
    {
        if (Pulsador_Subir == 1)
        {
            if (S3 == 1) { destino_manual = 2; return SUBIR; }
            if (S2 == 1) { destino_manual = 1; return SUBIR; }
        }
        if (Pulsador_Bajar == 1)
        {
            if (S1 == 1) { destino_manual = 2; return BAJAR; }
            if (S2 == 1) { destino_manual = 3; return BAJAR; }
        }
    }

    return ESPERA;
}

//ESTADO SUBIR
estado_t e_subir(void)
{
    motor_subir();
    leer_sensores_luz();
    
    int A = LEER_MODO_AUTO;
    int S1 = LEER_S1;
    int S2 = LEER_S2;
    int S3 = LEER_S3;
    int L = valor_luz;

    if (S1 == 1 && A == 0) return ESPERA; 

   //parada en modo automatico
    if (A == 1)
    {
        if (L > UMBRAL_DIA && S1 == 1) return ESPERA;
        if (L > UMBRAL_NOCHE && L <= UMBRAL_DIA && S2 == 1) return ESPERA;
        if (L <= UMBRAL_NOCHE) return ESPERA; 
    }

   //parada en modo manual
    if (A == 0)
    {
        if (destino_manual == 2 && S2 == 1) return ESPERA;
        if (destino_manual == 1 && S1 == 1) return ESPERA;
    }

    return SUBIR;
}

//ESTADO BAJAR
estado_t e_bajar(void)
{
    motor_bajar();
    leer_sensores_luz();
    
    int A = LEER_MODO_AUTO;
    int S1 = LEER_S1;
    int S2 = LEER_S2;
    int S3 = LEER_S3;
    int L = valor_luz;

    if (S3 == 1 && A == 0) return ESPERA;

   // parada en modo automatico
    if (A == 1)
    {
        if (L <= UMBRAL_NOCHE && S3 == 1) return ESPERA;
        if (L > UMBRAL_NOCHE && L <= UMBRAL_DIA && S2 == 1) return ESPERA;
        if (L > UMBRAL_DIA) return ESPERA;
    }

   //parada en modo manual
    if (A == 0)
    {
        if (destino_manual == 2 && S2 == 1) return ESPERA;
        if (destino_manual == 3 && S3 == 1) return ESPERA;
    }

    return BAJAR;
}
