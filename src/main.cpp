#include <Arduino.h>
#include <Wire.h>
#include "ADS1X15.h"


//////////////////////////////  ESP32-S2
#define PIN_RGB   15
#define ADC_PIN   1
#define ADC_VREF  1.0
#define ADC_M     4096.0 // 2^12
#define ADC_RES   12 // vincular con ADC_M
#define DIVISOR_R 0.2358 // 67.7k 219.4k. Solo si se usa el ADC interno del ESP32-S2

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
adc_read_v = adc_read_v+ ((analogRead(ADC_PIN)*(ADC_VREF/ADC_M))/DIVISOR_R);*/
#define ACS712_V_I0 2.499
#define ACS712_S    0.188
uint16_t adc_read=0;
float acs712_i=0, acs712_v=0;

////////////////////////////////////////// ADS1115
#define I2C_SDA_PIN 2
#define I2C_SCL_PIN 3
#define ADS1115_ADDR 0x48

using namespace ADS1X15;
ADS1115<TwoWire> ads(Wire); /* Use this for the 16-bit version */  

//////////////////////////////////////////
#define FILTRO_CNT 100

////////////////////////////////////////// PROGRAMA
void setup()
{
  Serial.begin(9600);
  Serial.println("Iicio del setup");
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  ads.begin(ADS1115_ADDR);
  ads.setGain(Gain::TWOTHIRDS_6144MV);
  ads.setDataRate(Rate::ADS1115_250SPS);

  /* ADC interno ESP32-S2
  Serial.begin(115200);
  while (!Serial);
  adcAttachPin(ADC_PIN);
  analogSetClockDiv(1);
  analogReadResolution((uint8_t)ADC_RES);
  analogSetAttenuation(ADC_0db); // con 11dB podemos leer hasta 3.55V pero no me funca */
}


void loop()
{
  acs712_v=0;
  for(uint16_t i=0;i<FILTRO_CNT;i++)
  {
      adc_read = ads.readADCSingleEnded(0);
      acs712_v += ads.computeVolts(adc_read);//lectura del sensor
  }
  acs712_v /= FILTRO_CNT;
  acs712_i = (acs712_v-ACS712_V_I0)/ACS712_S; //Ecuación  para obtener la corriente
  
  Serial.print("Corriente:\t"+String(acs712_i,3)+"A\n");
  Serial.print("Tension:\t"+String(acs712_v,3)+"V\n\n");

  delay(500);
}










