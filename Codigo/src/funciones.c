#include "../lib/mylib.h"

char *getKey(char *key){        // Utilidad para "parseo" del arch. de configuracion
	char i=0;
	while (*(key+i)!=' '){
		i++;
	}
	*(key+i)=0;
	return key+i+1;
}


params_t parseConfig(char *nombreArchivo){      // Funcion para "parsear" el archivo de configuracion
    FILE *conf;
	char cadena[40],*key,*val;
    char variables[2][25]={"Temp_unidad", "tiempo_reposo"};
    params_t config;
    config.arranque = true;
    int i = 0;
    if((conf = fopen(nombreArchivo, "rt")) == NULL){
        config.unidad = '-';
        config.temperatura = -127;
        config.tiempo = -127;
        config.arranque = true;
        return config;
    }
    else{
        fgets(cadena,40, conf);
        do{
            key = cadena;
            if(*(key) != '#' && strlen(key) > 0){
                val = getKey(key);
                for(i=0; i<2; i++){
                    if(!strcmp(key, variables[i])){
                        switch(i){
                            case 0:
                                config.unidad = *val;
                                break;
                            case 1:
                                config.tiempo = atoi(val);
                                break;
                        }
                    }
                }
            }
            fgets(cadena, 40, conf);
        }while(!feof(conf));
    }
    return config;
}

int leerTemperatura1(params_t *sensor1){ // Funcion leerTemperatura1 - Para estado "espera" y estado "calentar"
    int temp = 0;
    do{
        printf("\nTemperatura que capta el sensor = ");
        scanf("%d", &temp);
    }while(temp > sensor1->temperatura);
    return temp;
}


int leerTemperatura2(params_t *sensor2){ // Funcion leerTemperatura2 - Para estado "enfriar"
    int temp = 0;
    do{
        printf("\nTemperatura que capta el sensor = ");
        scanf("%d", &temp);
        }while(temp < sensor2->temperatura/2);
    return temp;
}


int leerTiempo(params_t *clock){   // Funcion para leer el tiempo transcurrido en soporte
        int t = 0;
        do{
            printf("\nTiempo (en minutos) transcurrido en soporte = ");
            scanf("%d", &t);
        }while(t < 0 || t > clock->tiempo+1 );
        return t;
}



bool f_soporte(void){   // Funcion para chequear si el soldador se encuentra en el soporte
    int opcion = 0;
        do{
        printf("\n\n¿El soldador se encuentra en el soporte ahora?\tSI-1\tNO-2\n");
        scanf("%d", &opcion);
        }while(opcion != 1 && opcion != 2);
        if(opcion == 1){
            return true;
        }
        else{
            return false;
        }
}


void f_display_chequeo(params_t config){    // Funcion que detecta posibles errores en la configuracion y los envia al display

    if(config.unidad == '-' && config.temperatura == -127 && config.tiempo == -127){
        printf("\nConfiguracion inicial: Temp_unidad = º%c, Temp_op = %dº, tiempo_reposo = %d minutos\n", config.unidad, config.temperatura, config.tiempo);
        printf("\n\aError. No se encuentra el archivo de configuracion.\n");
        exit(-1);
    }

    if(config.unidad != 'f' && config.unidad != 'F' && config.unidad != 'c'&& config.unidad != 'C'){
        config.unidad = '*';
    }

    if(config.tiempo <= 0 || config.tiempo > 29){
        config.tiempo = -127;
    }

    if(config.unidad == '*' || config.temperatura == -127 || config.tiempo == -127){
        config.unidad = '*';
        config.temperatura = -127;
        config.tiempo = -127;
        printf("\nConfiguracion inicial: Temp_unidad = º%c, Temp_op = %dº, tiempo_reposo = %d minutos\n", config.unidad, config.temperatura, config.tiempo);
        printf("\n\aError. Configuracion inicial no valida.\n");
        exit(-1);
    }
}
