#ifndef MY_ADS1115_H
#define MY_ADS1115_H

#include <Arduino.h>
#include <Wire.h>
#include<ADS1115_WE.h> 
#include <esp32s2.h>

#define ADS1115_I2C_ADDR 0x48

#define ADS1115_ADDR 0x48

#define ADS1115_CHA0 ADS1115_COMP_0_GND
#define ADS1115_CHA1 ADS1115_COMP_1_GND
#define ADS1115_CHA2 ADS1115_COMP_2_GND
#define ADS1115_CHA3 ADS1115_COMP_3_GND


void my_ads1115_setup( void );
float my_ads1115_filtered(ADS1115_MUX channel, int cnt_filter);
float readChannel_V(ADS1115_MUX channel);



#endif
