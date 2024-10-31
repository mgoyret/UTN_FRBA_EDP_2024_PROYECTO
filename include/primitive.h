#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <stdio.h>
#include <Arduino.h>
#include <Wire.h>
#include <my_ads1115.h>
#include <main.h>
#include <globals.h>

////////////////////////////////////////// ACS712
//  ACS712 5A  uses 185 mV per A
//  ACS712 20A uses 100 mV per A
//  ACS712 30A uses  66 mV per A
/* CALIBRACION ACS712
La corriente la estoy midiendo real, y la tension real con tester, y la que mide el ADC
1. corriente en 0, y veo la tension (en teoria 2.5V)
El tester marca 2.501 pero el ADC 2.499
2. ahora pongo una corriente de 2A, y veo la tension
tester da 2.877, t ADC 2.875
Vsensor con corriente nula = 3.186
sensibilidad real del sensor = (2.875-2.499)/(2-0) = 188mV/A
La tension segun el ADC fue realizada con filtro promediador y esta linea:
adc_read_v = adc_read_v+ ((analogRead(ESP32_S2_MINI_ADC_PIN)*(ESP32_S2_MINI_ADC_VREF/ESP32_S2_MINI_ADC_M))/DIVISOR_R);*/
#define ACS712_V_I0 2.499
#define ACS712_S    0.188

#define ADS1115_CH_IO   ADS1115_CHA0
#define ADS1115_CH_VO   ADS1115_CHA1
#define ADS1115_CH_II   ADS1115_CHA0
#define ADS1115_CH_VI   ADS1115_CHA1

#define PEAK_VO (float)6.0
#define PEAK_IO (float)2.0
#define PEAK_VI (float)15.0
#define PEAK_II (float)2.0

#define NULL_CURRENT    (float)0.0001
#define NULL_VOLTAGE_O  (float)0.5 // el minimo de la bateria es 2.5, no deberia haber menos que eso
#define NULL_VOLTAGE_I  (float)0.5 // COMPLETAR para la bateria de 12V de entrada, habria que ver el valor adecuado

float get_io( void );
float get_vo( void );
float get_ii( void );
float get_vi( void );
float get_duty( void );
void set_duty( float duty_val );

void update_meassures( void );
void update_adc_in(void);
void update_adc_out(void);

int security_error( void );
void set_duty_off( void );
void reset( void );
void handler_reset( void );

#endif
