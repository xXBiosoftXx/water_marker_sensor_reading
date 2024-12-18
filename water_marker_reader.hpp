class water_marker {
private:
  float tempD = 1.00 + 0.018 * (temp - 24.00);
  float voltage;
  float resistance;
public:
  int value[5];
  int temp = 24;
  float moisture = 0;
  int val_sum = 0;
  int val_avg = val_sum/5;
  void calculate(int *raw_val) {
    for(int i = 0; i < 5; i++){
      val_sum += raw_val[i];
    }
    voltage = (val_avg * 3.3) / 4095;
    resistance = (3.3 * voltage) / (3.3 - voltage);
    float resistancek = resistance / 1000;
    if (resistance > 550) {
      if (resistance > 8000.0) {
        moisture = (-2.246 - 5.239 * resistancek * (1 + .018 * (temp - 24.00)) - .06756 * resistancek * resistancek * (tempD * tempD));
      } else if (resistance > 1000.0) {
        moisture = (-3.213 * resistancek - 4.093) / (1 - 0.009733 * resistancek - 0.01205 * (temp));
      } else {
        moisture = (resistancek * 23.156 - 12.736) * tempD;
      }
    } else {
      moisture = 0;
    }
  }
  void show_data(void) {
    Serial.print("Read data : ");
    Serial.println(val_avg);
    Serial.print("voltage :");
    Serial.print(voltage);
    Serial.println(" V");
    Serial.print("resistance :");
    Serial.print(resistance);
    Serial.println(" Ohm");
    Serial.print("moisture : ");
    Serial.print(moisture);
    Serial.println(" kPa");
  }
};