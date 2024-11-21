#include <esp32s2.h>


void setup_pwm(void) // basada en funcion de espressif
{
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .duty_resolution  = LEDC_TIMER_10_BIT,
        .timer_num        = LEDC_TIMER,
        .freq_hz          = LEDC_FREQUENCY,  // Set output frequency at 4 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .gpio_num       = ESP32_S2_MINI_PWM_1_PIN,
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL1,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = LEDC_TIMER,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_channel);

    ledc_channel_config_t ledc_channe2 = {
        .gpio_num       = ESP32_S2_MINI_PWM_2_PIN,
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL2,
        .intr_type      = LEDC_INTR_DISABLE,
        .timer_sel      = LEDC_TIMER,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ledc_channel_config(&ledc_channe2);
    GPIO.func_out_sel_cfg[ESP32_S2_MINI_PWM_2_PIN].inv_sel = 1;//invierte la señal

    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL1, 0); // inicializo dutys en cero
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL1);
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL2, 0);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL2);
}

void my_esp32s2_mini_setup(void)
{
    Serial.begin(ESP32_S2_MINI_SERIAL_SPEED_BAUD);

    Wire.begin();
    //Wire.begin(ESP32_S2_MINI_I2C_SDA_PIN, ESP32_S2_MINI_I2C_SCL_PIN);
    //Wire.setClock(ESP32_S2_MINI_I2C_SPEED_HZ);

    //pinMode(ESP32_S2_MINI_PIN_INTERRUPT_ADC_IN, INPUT);
    pinMode(ESP32_S2_MINI_PIN_INTERRUPT_ADC_OUT, INPUT);

    pinMode(ESP32_S2_MINI_SHUTDOWN_DRIVER, OUTPUT);
    digitalWrite(ESP32_S2_MINI_SHUTDOWN_DRIVER, LOW);

    setup_pwm();
}
