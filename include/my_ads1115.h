#ifndef MY_ADS1115_H
#define MY_ADS1115_H

#include <Arduino.h>
#include <Wire.h>
#include <ADS1115_WE.h>
#include <esp32s2.h>
#include <primitive.h>
#include <globals.h>

#define ADS1115_I2C_ADDR_1 0x48
#define ADS1115_I2C_ADDR_2 0x49
#define ADS1115_I2C_ADDR_3 0x4A
#define ADS1115_I2C_ADDR_4 0x4B

#define ADS1115_CHA0 ADS1115_COMP_0_GND
#define ADS1115_CHA1 ADS1115_COMP_1_GND
#define ADS1115_CHA2 ADS1115_COMP_2_GND
#define ADS1115_CHA3 ADS1115_COMP_3_GND

#define ADS1115_CH_I    ADS1115_COMP_0_GND
#define ADS1115_CH_V    ADS1115_COMP_1_GND

#define ADS1115_CH_I_NUM    0
#define ADS1115_CH_V_NUM    1

void my_ads1115_setup(void);
void adc_in_conv_ready_handler(void);
void adc_out_conv_ready_handler(void);
//float my_ads1115_filtered(ADS1115_MUX channel, int cnt_filter);
//float readChannel_V(ADS1115_MUX channel);

#endif
