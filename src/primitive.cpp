#include <primitive.h>

float get_io(void)
{
    float acs712_v = 0;
    adc_out.setCompareChannels(ADS1115_CH_I);
    acs712_v = adc_out.getResult_V();
    global_io = -(acs712_v - ACS712_V_I0) / ACS712_S; // Ecuación  para obtener la corriente
    return global_io;
}

float get_vo(void)
{
    adc_out.setCompareChannels(ADS1115_CH_V);
    global_vo = adc_out.getResult_V();
    global_vo = global_vo/PUENTE_R;
    return global_vo;
}
/*
float get_ii(void)
{
    float acs712_v = adc_in.getResult_V();
    global_ii = (acs712_v - ACS712_V_I0) / ACS712_S; // Ecuación  para obtener la corriente
    return global_ii;
}

float get_vi(void)
{
    global_vi = adc_in.getResult_V();
    return global_vi;
}
*/
float get_duty(void)
{
    return (float)global_duty;
}

void set_duty(float duty_val)
{
    //Serial.print("############################ set_duty()\r\n");
    uint32_t duty_uint32 = 0;
    duty_uint32 = (uint32_t)((int)(duty_val*ESP32_S2_MINI_PWM_MAX_VAL));

    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL1, duty_uint32);//duty_uint32
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL1);
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL2, duty_uint32);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL2);
    //GPIO.func_out_sel_cfg[ESP32_S2_MINI_PWM_2_PIN].inv_sel = 1;//invierte la señal

    global_duty = duty_val;
}
/*
void update_adc_in(void)
{
    static unsigned long old_time_in;
    static uint8_t state_channel_in=0;

    if (adc_in_conv_ready)
    {
        adc_in_conv_ready = false;
        switch (state_channel_in)
        {
        case ADS1115_CH_I_NUM:
            old_time_in = micros();
            get_ii();
            adc_in.setCompareChannels(ADS1115_CH_V);
            state_channel_in=ADS1115_CH_V_NUM;
            break;
        case ADS1115_CH_V_NUM:
            Serial.print("\ntime in: "+String(micros() - old_time_in));
            get_vi();
            adc_in.setCompareChannels(ADS1115_CH_I);
            state_channel_in=ADS1115_CH_I_NUM;
            break;
        default:
            break;
        }
        adc_in.startSingleMeasurement();
    }
}
*/
void update_adc_out(void)
{
    get_vo();
    get_io();
}

void update_meassures(void)
{
    //update_adc_in();
    update_adc_out();
}

void set_duty_off( void )
{
	GPIO.func_out_sel_cfg[ESP32_S2_MINI_PWM_2_PIN].inv_sel = 0;
	set_duty(0);
}

int security_error(void)
{
    int err = false;

/*
    if (global_io > PEAK_IO || global_vo > PEAK_VO
                            || global_ii > PEAK_II
                            || global_vi > PEAK_VI
                            || global_io < NULL_CURRENT
                            || global_vo < NULL_VOLTAGE_O
                            || global_ii < NULL_CURRENT
                            || global_vi < NULL_VOLTAGE_I)
        err=true;
*/
//    if (global_io > PEAK_IO || global_vo > PEAK_VO
//                            || global_io < NULL_CURRENT
//                            || global_vo < NULL_VOLTAGE_O)
//        err=true;

    return err;
}

void reset(void)
{
	GPIO.func_out_sel_cfg[ESP32_S2_MINI_PWM_2_PIN].inv_sel = 1; // niega la señal PWM de este canal
	flag_reset = false;
}

void handler_reset(void) // COMPLETAR si se usa un boton, que sea interrupcion y este sea el handler
{
    flag_reset = true;
}