#include <main.h>

//////////////////////////////// Variables globales. Todas estas deben ser medidas y actualizadas en actualizar_mediciones()
float global_vo=0, global_io=0, global_vi=0, global_ii=0, global_duty=0;
int flag_discharge = false, flag_reset=false;

unsigned long oldTime;

void setup()
{
  my_esp32s2_mini_setup();
  my_ads1115_setup();
}


void loop()
{

  oldTime = micros();
  update_meassure();
  Serial.print("\ntime: "+String(micros()-oldTime)+"\nio:"+String(global_io)+" vo:"+String(global_vo)+" ii:"+String(global_ii)+" vi:"+String(global_vi));
  //state_machine();

  delay(2000);
}

