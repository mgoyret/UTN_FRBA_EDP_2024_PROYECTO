#include <primitive.h>

#define FILTRO_CNT 1

float get_io(void)
{
    float acs712_v = 0, acs712_i = 0;

    acs712_v = my_ads1115_filtered(ADS1115_CH_IO, FILTRO_CNT);
    acs712_i = (acs712_v - ACS712_V_I0) / ACS712_S; // Ecuación  para obtener la corriente
    // Serial.print("Corriente:\t"+String(acs712_i,3)+"A\n");
    // Serial.print("Tension:\t"+String(acs712_v,3)+"V\n\n");
    global_io = acs712_i;

    return acs712_i;
}

float get_vo(void)
{
    float voltage = 0;

    voltage = my_ads1115_filtered(ADS1115_CH_VO, FILTRO_CNT);
    // Serial.print("Tension:\t"+String(voltage,3)+"V\n\n");
    global_vo = voltage;

    return voltage;
}

float get_ii(void)
{
    float acs712_v = 0, acs712_i = 0;

    acs712_v = my_ads1115_filtered(ADS1115_CH_II, FILTRO_CNT);
    acs712_i = (acs712_v - ACS712_V_I0) / ACS712_S; // Ecuación  para obtener la corriente
    global_ii = acs712_i;

    return acs712_i;
}

float get_vi(void)
{
    float voltage = 0;

    voltage = my_ads1115_filtered(ADS1115_CH_VI, FILTRO_CNT);
    global_vi = voltage;

    return voltage;
}

float get_duty(void)
{
    float duty = global_duty;
    return duty;
}

void set_duty(float duty_val)
{
    /* enviar valor del duty al controlador */
    global_duty = duty_val;
}

void update_meassure(void)
{
    get_io();
    get_vo();
    get_ii();
    get_vi();
}

int security_error(void)
{
    int res = false;

    if (global_io > PEAK_IO ||
        global_vo > PEAK_VO ||
        global_ii > PEAK_II ||
        global_vi > PEAK_VI ||
        global_io < NULL_CURRENT ||
        global_vo < NULL_VOLTAGE_O ||
        global_ii < NULL_CURRENT ||
        global_vi < NULL_VOLTAGE_I)
        res = true;

    return res;
}

void reset(void) // COMPLETAR si se usa un boton, que sea interrupcion y este sea el handler
{
    flag_reset = true;
}
