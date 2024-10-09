#ifndef MDE_H
#define MDE_H

#include <primitivas.h>

#define SOC_BAJA  (float)0.6
#define SOC_ALTA  (float)0.95
#define SOC_FULL  (float)0.9

#define FALSE   0
#define TRUE    1

// Definición de los estados
enum Estado {
    ESTADO_CORRIENTE_CTE,
    ESTADO_TENSION_CTE,
    ESTADO_CARGADO,
    ESTADO_DESCARGA
};

void maquina_de_estados();

#endif
