#ifndef ESP32_S2_MINI_H
#define ESP32_S2_MINI_H

#include <Arduino.h>
#include <Wire.h>

#define ESP32_S2_MINI_ADC_PIN   1
#define ESP32_S2_MINI_ADC_VREF  1.0
#define ESP32_S2_MINI_ADC_M     4096.0 // 2^12
#define ESP32_S2_MINI_ADC_RES   12 // vincular con ESP32_S2_MINI_ADC_M
#define DIVISOR_R 0.2358 // 67.7k 219.4k. Solo si se usa el ADC interno del ESP32-S2

#define ESP32_S2_MINI_PIN_INTERRUPT_4   (uint8_t)4
#define ESP32_S2_MINI_PIN_INTERRUPT_5   (uint8_t)5
#define ESP32_S2_MINI_I2C_SDA_PIN 2
#define ESP32_S2_MINI_I2C_SCL_PIN 3

#define ESP32_S2_MINI_I2C_SPEED_HZ      400000
#define ESP32_S2_MINI_SERIAL_SPEED_BAUD 9600

// FRAN
#define ESP32_S2_MINI_PWM_1_CHANNEL         (uint8_t)0
#define ESP32_S2_MINI_PWM_1_PIN             5   // COMPLETAR gpio pin a definir
#define ESP32_S2_MINI_PWM_2_CHANNEL         (uint8_t)1
#define ESP32_S2_MINI_PWM_2_PIN             6   // COMPLETAR gpio pin a definir
#define ESP32_S2_MINI_PWM_FRECUENCY         10000
#define ESP32_S2_MINI_PWM_RESOLUTION_BITS   12//es la maxima a 10khz con 80Mhz de clock(la api la selecciona), nos da pasos de 0,00025, habria que reajustar la SM
#define ESP32_S2_MINI_PWM_MAX_VAL           4095//; rango: 0--> apagado | 1--> 0,00025 | 4095 --> prendido

void my_esp32s2_mini_setup( void );
void esp32_adc_setup( void );


#endif