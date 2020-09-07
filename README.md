# Trabajo práctico - Máquinas de Estado
## Control de temperatura para una estación de soldado

### Memoria descriptiva

El archivo de configuración inicial establecería los sig. parámetros:

- *Temp_unidad* [Cº / Fº]: unidad para los valores de temperatura a mostrar por pantalla.
- *Temp_op* [350 Cº (si los valores de temp. están dados en Cº) / 750 Fº (si los valores de temp. están dados en Fº)]: Temperatura de operación predeterminada del soldador. El proceso de soldado puede comenzar cuando la punta del soldador alcanza ese valor de temperatura.

- *tiempo_reposo* [0 - 29]: Tiempo (en minutos ) que debe transcurrir, luego de haber colocado al soldador en el soporte, para que se active la función de reposo automático. Al alcanzar el modo de reposo, el soldador habrá reducido su temperatura a un 50% de la temp. de operación.

Establecidos los parámetros de configuración inicial, el soldador, que en principio se encuentra a temperatura ambiente, empezará a calentarse inmediatamente hasta alcanzar la temperatura de operación (*Temp_op*). 
Al alcanzar dicha temperatura se debe retirar el soldador del soporte y comenzar el proceso de soldado.
Terminado el proceso, se coloca el soldador en el soporte nuevamente. El soldador se encontrará, en ésta oportunidad, a su temperatura de operación; luego, si se deja el soldador en el soporte por un tiempo que supere el tiempo de activación del reposo automático (*tiempo_reposo*), el soldador empezará a enfriarse hasta alcanzar el 50% de su temperatura de operación (modo de reposo).
El soldador permanecerá en éste valor inferior de temperatura mientras se mantenga en el soporte. En el momento en que se retire del mismo, el soldador comenzará a calentarse nuevamente hasta la temperatura de operación, lo cual permitirá comenzar un nuevo proceso de soldado.

### Diagrama

![Diagrama](https://github.com/Diego-Juarez/tp-maquinas-de-estado/blob/master/recursos/Imagen%20diagrama(Info%202%20TP).png)

## Mecánica de la máquina de estado

### Código

- Archivo de cabecera __mylib.h__

~~~c
#ifndef MYLIB_H_INCLUDED
#define MYLIB_H_INCLUDED
#include <stdio.h>

typedef enum {
    espera  = 0,
    calentar= 1,
    soldar  = 2,
    enfriar = 3,
    reposo  = 4
}estados_t;

typedef struct {
    char unidad;         // Unidad de temperatura
    int  temperatura;    // temperatura del soldador
    int  tiempo;         // tiempo para activacion de reposo automatico
}params_t;

params_t f_inicio(void); // lee el archivo de configuracion y carga las variables.

estados_t f_espera(params_t);
estados_t f_calentar(params_t);
estados_t f_soldar(params_t);
estados_t f_enfriar(params_t);
estados_t f_reposo(params_t);

#endif // MYLIB_H_INCLUDED
~~~

- Archivo __main.c__

~~~c
#include "mylib.h"

int main() {
    params_t config;
    config = f_inicio();
    printf("\nFSM - Estacion de soldado\n\n");
    printf("Configuracion inicial: Temp_unidad = %c, Temp_op = %d, tiempo_reposo = %d\n", config.unidad, config.temperatura, config.tiempo);
    estados_t estado = espera; // primer estado
    estados_t (*maquina[])(params_t) = {f_espera, f_calentar, f_soldar, f_enfriar, f_reposo};
    while(1) estado = (*maquina[estado])(config);
    return 0;
} 
~~~
- Archivo __config.conf__

~~~bash
# Unidad de temperatura (C para ºC; F para ºF)
Temp_unidad C
# Temperatura de operacion (por defecto, en ºC)
Temp_op 350
# Tiempo de activacion para reposo automatico
tiempo_reposo 15
~~~

