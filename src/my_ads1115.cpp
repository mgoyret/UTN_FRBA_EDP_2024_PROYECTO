
#include <my_ads1115.h>

//ADS1115_WE adc_in   =   ADS1115_WE(ADS1115_I2C_ADDR_VDD);
ADS1115_WE adc_out  =   ADS1115_WE(ADS1115_I2C_ADDR_GND);

volatile bool adc_in_conv_ready = false;
volatile bool adc_out_conv_ready = false;


void my_ads1115_setup()
{
    //Serial.print("############################ my_ads1115_setup()\r\n");
/*
    if (!adc_in.init())
        Serial.println("ADS1115 1 not connected!");
    else
    {
        adc_in.setVoltageRange_mV(ADS1115_RANGE_6144);
        adc_in.setCompareChannels(ADS1115_CH_I);
        adc_in.setAlertPinMode(ADS1115_ASSERT_AFTER_1);
        adc_in.setConvRate(ADS1115_128_SPS); //ADS1115_860_SPS
        adc_in.setAlertPinToConversionReady();
        attachInterrupt(digitalPinToInterrupt(ESP32_S2_MINI_PIN_INTERRUPT_ADC_IN), adc_in_conv_ready_handler, FALLING);
        adc_in.startSingleMeasurement();
    }
    if (!adc_out.init())
        Serial.println("ADS1115 2 not connected!");
    else
    {
        adc_out.setVoltageRange_mV(ADS1115_RANGE_6144);
        adc_out.setCompareChannels(ADS1115_CH_I); // luego va conmutando entre el canal 0 y 1 (tension, corriente)
        //adc_out.setAlertPinMode(ADS1115_ASSERT_AFTER_1);
        adc_out.setMeasureMode(ADS1115_CONTINUOUS); // TEST
    
        //adc_out.setConvRate(ADS1115_860_SPS);
        //adc_out.setAlertPinToConversionReady();
        //attachInterrupt(digitalPinToInterrupt(ESP32_S2_MINI_PIN_INTERRUPT_ADC_OUT), adc_out_conv_ready_handler, FALLING);
        //adc_out.startSingleMeasurement();
        //Serial.print("############################ ADC salida configurado \r\n");
    }
*/

  if(!adc_out.init()){
    Serial.println("ADS1115 not connected!");
  }

  adc_out.setVoltageRange_mV(ADS1115_RANGE_6144); //comment line/change parameter to change range
  adc_out.setCompareChannels(ADS1115_COMP_0_GND); //comment line/change parameter to change channel
  adc_out.setMeasureMode(ADS1115_CONTINUOUS); //comment line/change parameter to change mode
}

void adc_in_conv_ready_handler()
{
    adc_in_conv_ready = true;
}

void adc_out_conv_ready_handler()
{
    adc_out_conv_ready = true;
}
