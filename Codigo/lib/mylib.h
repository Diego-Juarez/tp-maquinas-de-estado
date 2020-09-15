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

// FUNCIONES DE ESTADO

estados_t f_espera(params_t *);
estados_t f_calentar(params_t *);
estados_t f_soldar(params_t *);
estados_t f_enfriar(params_t *);
estados_t f_reposo(params_t *);

// FUNCIONES AUXILIARES

params_t f_inicio(void);    // Lee el archivo de configuracion y carga las variables.

char *getKey(char *key);    // Util para el "parseo" del arch. de configuracion

params_t parseConfig(char *nombreArchivo);  // "Parsea" el arch. de configuracion

int leerTemperatura1(params_t*);    // Lee la temperatura para los estados "espera" y "calentar"

int leerTemperatura2(params_t*);    // Lee la temperatura para el estado "enfriar"

int leerTiempo(params_t*);  // Lee el tiempo que se deja el soldador en el soporte (en minutos)

bool f_soporte(void);   // Chequea si el soldador se encuentra en el soporte

void f_display_chequeo(params_t); // Detecta y envia al display algunos posibles errores en la configuracion inicial


#endif // MYLIB_H_INCLUDED
