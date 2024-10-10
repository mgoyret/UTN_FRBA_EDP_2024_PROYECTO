#include <main.h>

//////////////////////////////// Variables globales. Todas estas deben ser medidas y actualizadas en actualizar_mediciones()
float global_vo=0, global_io=0, global_vi=0, global_ii=0, global_duty=0;


unsigned long oldTime,currTime;




void setup()
{
  Serial.begin(9600);
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  Wire.setClock(400000);
  pinMode(PIN_INTERRUPT, INPUT_PULLUP);
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

