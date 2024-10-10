
#include <my_ads1115.h>

// using namespace puesto en el .h
//ADS1115<TwoWire> ads(Wire); /* Use this for the 16-bit version */  
ADS1115_WE adc = ADS1115_WE(I2C_ADS1115_ADDR);
volatile bool convReady = false;

void convReadyAlert()
{
   convReady = true;
}


void my_ads1115_setup()
{
  if(!adc.init())
    Serial.println("ADS1115 not connected!");

  adc.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc.setAlertPinMode(ADS1115_ASSERT_AFTER_1);
  adc.setConvRate(ADS1115_860_SPS);
  adc.setMeasureMode(ADS1115_SINGLE);
  adc.setAlertPinToConversionReady();
  attachInterrupt(digitalPinToInterrupt(PIN_INTERRUPT), convReadyAlert, FALLING);
}


float readChannel_V(ADS1115_MUX channel)
{
  float voltage = 0.0;

  adc.setCompareChannels(channel);
  adc.startSingleMeasurement();

  while(!convReady);
  if(convReady)
  {
    voltage = adc.getResult_V();
    convReady = false;
  }
  
  return voltage;
}


float my_ads1115_filtered(ADS1115_MUX channel, int cnt_filter)
{
  float volts_measure=0;
  for(uint16_t i=0;i<cnt_filter;i++)
    volts_measure += readChannel_V(channel);
  volts_measure /= cnt_filter;
  return volts_measure;
}

