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