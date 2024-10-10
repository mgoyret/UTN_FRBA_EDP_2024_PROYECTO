#include <esp32s2.h>

void esp32_adc_setup(void)
{
    Serial.begin(115200);
    while (!Serial);
    adcAttachPin(ADC_PIN);
    analogSetClockDiv(1);
    analogReadResolution((uint8_t)ADC_RES);
    analogSetAttenuation(ADC_0db); // con 11dB podemos leer hasta 3.55V pero no me funca
}
