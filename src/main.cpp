#include <main.h>

//////////////////////////////// Variables globales
float SOC=0, Vout=0, Iout=0, duty=0;
// ACS712
uint16_t adc_read=0;
float acs712_i=0, acs712_v=0;


////////////////////////////////////////// PROGRAMA
void setup()
{
  Serial.begin(9600);
  Serial.println("Iicio del setup");
  my_ads1115_setup();
  esp32_adc_setup();

  //setup_para_adc_iterno();
}


void loop()
{
  //acs712_test();
  //delay(500);

  actualizar_mediciones();
  maquina_de_estados();

}
