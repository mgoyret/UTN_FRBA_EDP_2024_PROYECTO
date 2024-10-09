#include <primitivas.h>

extern float SOC;
extern float Iout;
extern float Vout;
extern float duty;

#define FILTRO_CNT 100
extern ADS1115<TwoWire> ads;


void esp32_adc_setup(void)
{
    Serial.begin(115200);
    while (!Serial);
    adcAttachPin(ADC_PIN);
    analogSetClockDiv(1);
    analogReadResolution((uint8_t)ADC_RES);
    analogSetAttenuation(ADC_0db); // con 11dB podemos leer hasta 3.55V pero no me funca
}

float get_i0(void)
{
    float corriente=0;

    float acs712_v=0, acs712_i=0;
    uint16_t adc_read=0;
    for(uint16_t i=0;i<FILTRO_CNT;i++)
    {
        adc_read = ads.readADCSingleEnded(0);
        acs712_v += ads.computeVolts(adc_read);//lectura del sensor
    }
    acs712_v /= FILTRO_CNT;
    acs712_i = (acs712_v-ACS712_V_I0)/ACS712_S; //Ecuación  para obtener la corriente
    //Serial.print("Corriente:\t"+String(acs712_i,3)+"A\n");
    //Serial.print("Tension:\t"+String(acs712_v,3)+"V\n\n");
    corriente = acs712_i;

    return corriente;
}

float get_vo(void)
{
    float tension=0;
    return tension;
}

float get_duty(void)
{
    float tension=0;
    return tension;
}

void set_duty(float duty_val)
{

}

void actualizar_mediciones(void)
{
    get_i0();
    get_vo();
    get_duty();
}
