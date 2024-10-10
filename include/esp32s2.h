#ifndef ESP32S2_H
#define ESP32S2_H

#include <Arduino.h>

#define PIN_RGB   15
#define ADC_PIN   1
#define ADC_VREF  1.0
#define ADC_M     4096.0 // 2^12
#define ADC_RES   12 // vincular con ADC_M
#define DIVISOR_R 0.2358 // 67.7k 219.4k. Solo si se usa el ADC interno del ESP32-S2

#define PIN_INTERRUPT (uint8_t)4

void esp32_adc_setup(void);


#endif