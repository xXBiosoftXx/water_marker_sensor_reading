#define power_sensor 39
#include "water_marker_reader.hpp"
#include "driver/adc.h"
unsigned long last_reading = 0;
const unsigned long reading_period = 60000; // every 1 min will be read value from sensor
unsigned long last_power_up = 0;
const unsigned long time_power_up = 50; //sent VDC to sensor when power status true
bool power_status = false;
water_marker sensor;

void setup() {
  Serial.begin(115200);
  pinMode(power_sensor, OUTPUT);
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_0); // Read data at GPIO36
}

void loop() {
  if ((millis() - last_reading) >= reading_period) {
    last_reading = millis();
    last_power_up = millis();
    power_status = true;
    digitalWrite(power_sensor,power_status);
    Serial.println("Power on");
    delayMicroseconds(100);
    for(int i = 0; i < 5; i++){
      sensor.value[i] = adc1_get_raw(ADC1_CHANNEL_0);
    }
  }

  if(power_status){
    if((millis() - last_power_up) >= time_power_up){
      power_status = false;
      digitalWrite(power_sensor,power_status);
      Serial.println("Power off");
      sensor.calculate(sensor.value);
      sensor.show_data();
    }
  }
}
