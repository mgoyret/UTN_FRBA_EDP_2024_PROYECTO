/*
#include <Arduino.h>
#include <Irms_Calc.h>
//#include <esp32-hal-adc.h>

//#define PIN_RGB 15
#define ACS_SENS_CORRECTION 2
//void myBlink(uint8_t pin);
double AmpsRMS = 0;
double read_mV = 0, read_raw=0, read_def=0, amps=0, volts=0, Vref=0;

ACS712_Irms acs712;
void setup() {
  //pinMode(PIN_RGB, OUTPUT);
  //digitalWrite(PIN_RGB, HIGH);
  //for (size_t i = 0; i < 10; i++)
  //{
  //  digitalWrite(PIN_RGB, !digitalRead(PIN_RGB));    
  //  delay(250);
  //}
 
  Serial.begin(9600);
//  acs712.ADCSamples = 4096.0; //2^12 samples
//  acs712.mVperAmp = scaleFactor::ACS712_5A;// +ACS_SENS_CORRECTION; // use 100 for 20A Module and 66 for 30A Module and 185 for 5A Module
//  acs712.maxADCVolt = 5.0; //5 Volts
//  acs712.ADCIn = A1;
//  acs712.Init();
adcAttachPin(A1);
}

void loop() {
  //digitalWrite(PIN_RGB, !digitalRead(PIN_RGB));
  //delay(1000);

//  double AmpsRMS = acs712.Process();
  read_def = analogRead(A1);
  read_raw = analogReadRaw(A1);
  read_mV = analogReadMilliVolts(A1);
  Vref = read_mV*4096/read_def;
  volts = read_def*Vref/4096.0;
  //amps = ((amps_mV/1000))
  Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
  Serial.println("read: " + String(read_def));
  Serial.println("read_raw: " + String(read_raw));
  Serial.println("read_mV: " + String(read_mV));
  Serial.println("Vref: " + String(Vref));
  Serial.println("VOLTS: " + String(volts));

  delay(1000);


}

// put function definitions here:
//void myBlink(uint8_t pin) {
//  digitalWrite(pin, !digitalRead(pin));
//}
*/