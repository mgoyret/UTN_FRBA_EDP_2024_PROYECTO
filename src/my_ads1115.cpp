
#include <my_ads1115.h>

// using namespace puesto en el .h
ADS1115<TwoWire> ads(Wire); /* Use this for the 16-bit version */  

void my_ads1115_setup()
{
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  ads.begin(ADS1115_ADDR);
  ads.setGain(Gain::TWOTHIRDS_6144MV);
  ads.setDataRate(Rate::ADS1115_250SPS);
}
