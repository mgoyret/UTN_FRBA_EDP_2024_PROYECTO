#include <main.h>

//////////////////////////////// Variables globales. Todas estas deben ser medidas y actualizadas en actualizar_mediciones()
float global_vo = 0, global_io = 0, global_vi = 0, global_ii = 0, global_duty = 0;
int flag_discharge = false, flag_reset = false;

void setup()
{
    my_esp32s2_mini_setup();
    my_ads1115_setup();
}

void loop()
{
    update_meassures();
    state_machine();
    //Serial.print("\n\nIN0: " + String(global_ii) + "\nIN1: " + String(global_vi) + "\nOUT0: " + String(global_io) + "\nOUT1: " + String(global_vo));
    //delay(1000);
}
