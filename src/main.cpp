#include <main.h>

//////////////////////////////// Variables globales. Todas estas deben ser medidas y actualizadas en actualizar_mediciones()
float global_vo = 0, global_io = 0, global_vi = 0, global_ii = 0, global_duty = 0;
int flag_discharge = false, flag_reset = false;
uint32_t duty_uint32=0;

void setup()
{
    my_esp32s2_mini_setup();
    my_ads1115_setup();
    set_duty(DUTY_CHARGE_INIT);
}

void loop()
{
    update_meassures();
    state_machine();
    Serial.print("Io: " + String(global_io*1000) + "mA\tVo: " + String(global_vo)+"\n");

    delay(10);
}
