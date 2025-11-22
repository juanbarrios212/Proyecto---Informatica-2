# Proyecto-Informatica-2

# Persiana Automática con Control Lumínico y Manual
---
## Memoria Descriptiva
---
El presente proyecto consiste en el diseño y control de una persiana motorizada que puede ubicarse en tres posiciones predefinidas: alta, media y baja. Para determinar la ubicación de la persiana en todo momento, se dispondrán sensores de posición en cada uno de estos niveles.
El sistema contará con una llave selectora que permitirá elegir entre dos modos de funcionamiento: automático y manual.
- Modo Automático:
En este modo, la posición de la persiana se ajustará de manera autónoma en función de la intensidad lumínica exterior, medida por un sensor fotoeléctrico.
    - Alta intensidad de luz (mañana o mediodía) → la persiana se ubicará en la posición alta.
    - Intensidad de luz intermedia (tarde) → la persiana se ubicará en la posición media.
    - Ausencia o baja intensidad de luz (noche) → la persiana descenderá hasta la posición baja.
- Modo Manual:
En este modo, el usuario podrá controlar la persiana mediante dos pulsadores: SUBIR y BAJAR. Cada pulsación ejecutará un desplazamiento de una sola posición, evitando movimientos continuos:
    - Si la persiana está en posición baja y se presiona SUBIR, se moverá a la posición media.
    - Si está en posición media y se presiona SUBIR, pasará a la posición alta.
    - Si está en posición alta y se presiona BAJAR, se moverá a la posición media.
    - Si está en posición media y se presiona BAJAR, pasará a la posición baja.
De esta manera el sistema se adapta tanto a las condiciones de iluminación del entorno como a las necesidades específicas del usuario.

<p align="center">
<img width="755" height="455" alt="image" src="https://github.com/user-attachments/assets/e0841a08-b6ef-4422-9173-0b157ed62b0b" />

- L: Sensor Fotoelectrico.
- S1: Sensor Fin de carrera en la posicion superior.
- S2: Sensor Fin de carrera en la posicion media.
- S3: Sensor Fin de carrera en la posicion baja.
- A: Modo Automatico (A=1 activado ; A=0 desactivado, modo manual).
- Sub: Pulsador para subir en Manual.
- Baj: ulsador para bajar en Manual.

La placa LPC845-BRK (con el microcontrolador NXP LPC845M301) dispone de un Conversor Analógico-Digital (ADC) de 10 bits, lo que significa que convierte la señal analógica en un valor digital comprendido entre 0 y 1023, donde:
* 0 – 300	Noche / muy poca luz.
* 301 – 700	Luz intermedia / tarde.
* 701 – 1023	Mucha luz / día.
    
## Simulación en Proteus
---
<p align="center">
<img width="819" height="576" alt="image" src="https://github.com/user-attachments/assets/1983e8c2-3293-45c2-89db-3d587ac4aced" />
