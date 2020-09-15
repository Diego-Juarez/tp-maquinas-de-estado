#include "../lib/mylib.h"

params_t f_inicio(void){    // Funcion para configuracion inicial
    params_t config;
    config = parseConfig("config.conf");

    switch(config.unidad){  // Este bloque corrige la unidad de temp. y, basado en la correcion, asigna la temp que corresponde
        case 'c':
            config.unidad = 'C';
            config.temperatura = 350;
            break;
        case 'C':
            config.temperatura = 350;
            break;
        case 'f':
            config.unidad = 'f';
            config.unidad = 'F';
            config.temperatura = 750;
            break;
        case 'F':
            config.temperatura = 750;
            break;
    }
    return config;
}


estados_t f_espera(params_t *config){    // Funcion "espera"
    estados_t estado = espera;
    if(config->arranque){
        printf("\n\nEl soldador se encuentra a temperatura ambiente. Empezara a calentarse inmediatamente");
        config->arranque = false;
        estado = calentar;
    }else{
        printf("\nESTADO: En espera.\n");
        int t = 0;
        t = leerTiempo(config);
            if(t <= config->tiempo){
            estado = espera;
            }
            if(t > config->tiempo){
                estado = enfriar;
            }
    }
    return estado;
}


estados_t f_calentar(params_t *config){  // Funcion "calentar"
    estados_t estado = calentar;
    int temp = 0;
    printf("\n\nESTADO: Calentando soldador...\n");
    temp = leerTemperatura1(config);
    if(temp == config->temperatura){
        estado = soldar;
    }
    else{
    estado = calentar;
    }
    return estado;
}

estados_t f_soldar(params_t *config){    // Funcion "soldar"
    estados_t estado = soldar;
    printf("\n\nESTADO: Listo para soldar. El soldador se encuentra a la temperatura de operacion = %dº", config->temperatura);
    bool soporte = f_soporte();
    switch(soporte){
        case false:
            estado = soldar;
            break;
        case true:
            estado = espera;
            break;
    }
    return estado;
}

estados_t f_enfriar(params_t *config){   // Funcion "enfriar"
    estados_t estado = enfriar;
    int temp = 0;
    printf("\n\nESTADO: Enfriando soldador...\n");
    temp = leerTemperatura2(config);
    printf("\nEnfriando soldador...\tTemperatura actual = %dº", temp);
    if(temp == (config->temperatura/2)){
        estado = reposo;
    }
    else{
        estado = enfriar;
    }
    return estado;
}


estados_t f_reposo(params_t *config){    // Funcion "reposo"
    estados_t estado = reposo;
    printf("\n\nESTADO: Reposo. El soldador se encuentra al 50 por ciento de su temperatura de operacion.\tTemperatura = %dº", config->temperatura/2);
    bool soporte = f_soporte();
    switch(soporte){
        case false:
            estado = calentar;
            break;
        case true:
            estado = reposo;
            break;
    }
    return estado;
}
