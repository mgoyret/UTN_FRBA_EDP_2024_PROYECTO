#ifndef ESP32_S2_MINI_H
#define ESP32_S2_MINI_H

#include <Arduino.h>
#include <Wire.h>
#include <pins.h>

// PARA LEDC
#include <stdio.h>
#include "driver/ledc.h"
#include "esp_err.h"


#define ESP32_S2_MINI_ADC_VREF  1.0
#define ESP32_S2_MINI_ADC_M     4096.0 // 2^12
#define ESP32_S2_MINI_ADC_RES   12 // vincular con ESP32_S2_MINI_ADC_M
#define DIVISOR_R 0.2358 // 67.7k 219.4k. Solo si se usa el ADC interno del ESP32-S2


#define ESP32_S2_MINI_I2C_SPEED_HZ      300000
#define ESP32_S2_MINI_SERIAL_SPEED_BAUD 9600

// pines PWM definidos en pins.h
#define ESP32_S2_MINI_PWM_FRECUENCY         5000
#define ESP32_S2_MINI_DUTY_RESOLUTION       10
#define ESP32_S2_MINI_PWM_MAX_VAL           1023 // duty 0 a 8191, steps de 0.00012

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL1            LEDC_CHANNEL_0
#define LEDC_CHANNEL2            LEDC_CHANNEL_1
#define LEDC_DUTY_RES           LEDC_TIMER_10_BIT // Set duty resolution to 10 bits
#define LEDC_DUTY               (512) // Set duty to 50%. (2 ** 10) * 50% = 512
#define LEDC_FREQUENCY          (50000) // Frequency in Hertz. Set frequency at 50 kHz

void my_esp32s2_mini_setup( void );
void setup_pwm( void );


#endif