#ifndef MY_ADS1115_H
#define MY_ADS1115_H

#include <Arduino.h>
#include <Wire.h>
#include "ADS1X15.h"

#define I2C_SDA_PIN 2
#define I2C_SCL_PIN 3
#define ADS1115_ADDR 0x48

using namespace ADS1X15;

void my_ads1115_setup( void );


#endif
