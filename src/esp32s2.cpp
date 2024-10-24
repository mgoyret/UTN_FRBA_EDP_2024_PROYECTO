#include <esp32s2.h>

void esp32_adc_setup(void)
{
    Serial.begin(115200);
    while (!Serial)
        ;
    adcAttachPin(ESP32_S2_MINI_ADC_PIN);
    analogSetClockDiv(1);
    analogReadResolution((uint8_t)ESP32_S2_MINI_ADC_RES);
    analogSetAttenuation(ADC_0db); // con 11dB podemos leer hasta 3.55V pero no me funca
}

void my_esp32s2_mini_setup(void)
{
    Serial.begin(ESP32_S2_MINI_SERIAL_SPEED_BAUD);
    Wire.begin(ESP32_S2_MINI_I2C_SDA_PIN, ESP32_S2_MINI_I2C_SCL_PIN);
    Wire.setClock(ESP32_S2_MINI_I2C_SPEED_HZ);
    pinMode(ESP32_S2_MINI_PIN_INTERRUPT_4, INPUT_PULLUP); // para interrupcion
    pinMode(ESP32_S2_MINI_PIN_INTERRUPT_5, INPUT_PULLUP);
}

void setup_PWM()
{
  	ledcSetup(ESP32_S2_MINI_PWM_1_CHANNEL, ESP32_S2_MINI_PWM_FRECUENCY, ESP32_S2_MINI_PWM_RESOLUTION_BITS);//API's del esp32
  	ledcAttachPin(ESP32_S2_MINI_PWM_1_PIN, ESP32_S2_MINI_PWM_1_CHANNEL);
  	ledcSetup(ESP32_S2_MINI_PWM_2_CHANNEL, ESP32_S2_MINI_PWM_FRECUENCY, ESP32_S2_MINI_PWM_RESOLUTION_BITS);
  	ledcAttachPin(ESP32_S2_MINI_PWM_2_PIN, ESP32_S2_MINI_PWM_2_CHANNEL);
    ledcWrite(ESP32_S2_MINI_PWM_1_CHANNEL, 0);//setea el duty del PWM
    ledcWrite(ESP32_S2_MINI_PWM_2_CHANNEL, 0);//inicializo apagado
}
