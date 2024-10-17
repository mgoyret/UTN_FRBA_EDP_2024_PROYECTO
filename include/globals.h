#ifndef GLOBALS_H
#define GLOBALS_H

extern float global_vo, global_io, global_vi, global_ii, global_duty;
extern int flag_discharge, flag_reset;
extern ADS1115_WE adc_in, adc_out;
extern volatile bool adc_in_conv_ready, adc_out_conv_ready;

#endif