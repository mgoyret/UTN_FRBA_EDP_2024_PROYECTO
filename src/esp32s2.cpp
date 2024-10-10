#include <esp32s2.h>

void esp32_adc_setup( void )
{
    Serial.begin(115200);
    while (!Serial);
    adcAttachPin(ESP32_S2_MINI_ADC_PIN);
    analogSetClockDiv(1);
    analogReadResolution((uint8_t)ESP32_S2_MINI_ADC_RES);
    analogSetAttenuation(ADC_0db); // con 11dB podemos leer hasta 3.55V pero no me funca
}

void my_esp32s2_mini_setup( void )
{
  Serial.begin(ESP32_S2_MINI_SERIAL_SPEED_BAUD);
  Wire.begin(ESP32_S2_MINI_I2C_SDA_PIN, ESP32_S2_MINI_I2C_SCL_PIN);
  Wire.setClock(ESP32_S2_MINI_I2C_SPEED_HZ);
  pinMode(ESP32_S2_MINI_PIN_INTERRUPT, INPUT_PULLUP);
}
