#ifndef SM_H
#define SM_H

#include <primitive.h>

/* los siguientes valores salen de hacer los cambios con SOC 60%, 90% y 90%
https://batteryuniversity.com/article/bu-409-charging-lithium-ion */
#define VO_LOW  (float)2.52 // SOC 60%
#define VO_HIGH  (float)3.99 // SOC 95%
#define VO_FULL  (float)3.78 // SOC 90%

#define BAT_MIN_V        (float)2.5
#define DUTY_CARGA_APROX    (float)0.64 // 1 - tensionMaxBat/tensionNominalFuente = 1 - 4.2/12 = 0.65  ajustado a 0.64 para tener 1mA
#define DUTY_DISCHARGE       (float)0.348 // 1-duty y luego ajustado a dedo
#define DUTY_INIT        (float)0.55 // arrancar con un valor bien bajo pero que asegure carga, osea mayor a 0.5

#define NULL_CURRENT      (float)0.00001

#define FALSE   0
#define TRUE    1

// Definición de los estados
enum State {
    STATE_CONSTANT_CURRENT,
    STATE_CONSTANT_VOLTAGE,
    STATE_CHARGED,
    STATE_DISCHARGE,
    STATE_ERROR
};

void state_machine();

#endif
