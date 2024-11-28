#ifndef SM_H
#define SM_H

#include <primitive.h>
#include <globals.h>

/* los siguientes valores salen de hacer los cambios con SOC 60%, 90% y 90%
https://batteryuniversity.com/article/bu-409-charging-lithium-ion
https://secondlifestorage.com/index.php?threads/panasonic-cgr18650h-cell-specifications.2573/ */
#define CVCC_THRESHOLD  (float)4//.2//2.52 // SOC 60%
#define VO_HIGH         (float)3.99 // SOC 95%
#define VO_FULL         (float)3.78 // SOC 90%

//#define BAT_MIN_V           (float)2.5
#define DUTY_CARGA_APROX    (float)0.64 // 1 - tensionMaxBat/tensionNominalFuente = 1 - 4.2/12 = 0.65  ajustado a 0.64 para tener 1mA
#define DUTY_DISCHARGE      (float)0.348 // 1-duty y luego ajustado a dedo
#define DUTY_CHARGE_INIT    (float)0.64 // arrancar con un valor bien bajo pero que asegure carga, osea mayor a 0.5
#define DUTY_DISCHARGE_INIT (float)0.45 // arrancamos con corriente de descarga bajita y la vamos estabilizando

#define CHARGE_CONST_I      (float)0.500//0.980
#define CHARGE_CONST_V      (float)4.2
#define CHARGE_CUTOFF_I     (float)0.050
#define CHARGE_MAX_I        (float)1.925
#define DISCHARGE_I         (float)0.280
#define DISCHARGE_MAX_I     (float)1.560
#define DISCHARGE_CUTOFF_V  (float)3
#define NONIMAL_V           (float)3.7

// Definición de los estados
enum State {
    STATE_CONSTANT_CURRENT,
    STATE_CONSTANT_VOLTAGE,
    STATE_CHARGED,
    STATE_DISCHARGE,
    STATE_ERROR,
};

void state_machine();

#endif
