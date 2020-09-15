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
