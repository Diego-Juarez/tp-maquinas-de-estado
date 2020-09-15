# Trabajo práctico - Máquinas de Estado
## Control de temperatura para una estación de soldado

### Memoria descriptiva

El archivo de configuración inicial establece los sig. parámetros:

- *Temp_unidad* [Cº / Fº]: unidad para los valores de temperatura a mostrar por pantalla. De éste parámetro depende el valor de la temperatura de operación predeterminada para el soldador (*Temp_op*), que será de 350ºC si la estación utiliza grados Celsius, o 750ºF si la estación utiliza grados Fahrenheit. El proceso de soldado puede comenzar cuando el soldador alcanza la temperatura de operación.

- *tiempo_reposo* [1 - 29]: Tiempo (en minutos ) que debe transcurrir, luego de haber colocado al soldador en el soporte, para que se active la función de reposo automático. Cuando el tiempo asignado en éste parámetro es superado en 1 minuto, el soldador comenzará a enfriarse hasta alcanzar el 50% de su temp. de operación, permaneciendo en el estado de "reposo" mientras no se retire el soldador del soporte nuevamente.

Una vez que se establecen los parámetros de configuración inicial, el soldador, que en principio se encuentra a temperatura ambiente, empezará a calentarse inmediatamente hasta alcanzar la temperatura de operación (*Temp_op*). 
Al alcanzar dicha temperatura se debe retirar el soldador del soporte y comenzar el proceso de soldado.
Terminado el proceso, se coloca el soldador en el soporte nuevamente. A partir de entonces, si se deja el soldador en el soporte por un tiempo que supere en 1 minuto el tiempo de activación del reposo automático (*tiempo_reposo*), el soldador empezará a enfriarse hasta alcanzar el 50% de su temperatura de operación (estado de "reposo").
El soldador permanecerá en éste valor inferior de temperatura mientras se mantenga en el soporte. En el momento en que se retire del mismo, el soldador comenzará a calentarse nuevamente hasta la temperatura de operación, lo cual permitirá comenzar un nuevo proceso de soldado.

### Diagrama

![Diagrama](https://github.com/Diego-Juarez/tp-maquinas-de-estado/blob/master/recursos/Imagen%20Diagrama%203%20(Info%202%20TP).png) 

### Código (abreviado)

- Archivo de cabecera __mylib.h__

~~~c
#ifndef MYLIB_H_INCLUDED
#define MYLIB_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// TIPOS DE DATOS DEFINIDOS PARA EL PROGRAMA

typedef struct {
    char unidad;        // Unidad de temperatura
    int  temperatura;   // Temperatura de operacion del soldador
    int  tiempo;        // tiempo para activacion de reposo automatico
    bool arranque;      // Permite detectar si la maquina acaba de encenderse
}params_t;

typedef enum {          // Enumeracion de estados de la FSM
    espera  = 0,
    calentar= 1,
    soldar  = 2,
    enfriar = 3,
    reposo  = 4
}estados_t;

// FUNCION AUXILIAR

params_t f_inicio(void);    // Lee el archivo de configuracion y carga las variables.

// FUNCIONES DE ESTADO

estados_t f_espera(params_t *);
estados_t f_calentar(params_t *);
estados_t f_soldar(params_t *);
estados_t f_enfriar(params_t *);
estados_t f_reposo(params_t *);
~~~

- Archivo __main.c__

~~~c
#include "../lib/mylib.h"

int main() {
    printf("\n*** FSM - Estacion de soldado ***\n");
    params_t config;
    config = f_inicio();
    f_display_chequeo(config);
    printf("\nConfiguracion inicial: Temp_unidad = º%c, Temp_op = %dº, tiempo_reposo = %d minutos\n", config.unidad, config.temperatura, config.tiempo);
    estados_t estado = espera; // Primer estado
    estados_t (*maquina[])(params_t*) = {f_espera, f_calentar, f_soldar, f_enfriar, f_reposo};
    while(1) estado = (*maquina[estado])(&config);
    return 0;
}
~~~
- Archivo __config.conf__

~~~bash
#Unidad de temperatura
Temp_unidad C
#Tiempo de activacion para reposo automatico
tiempo_reposo  15
~~~

