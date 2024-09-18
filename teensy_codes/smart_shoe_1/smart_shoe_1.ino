#define SERIAL 0

#include "globals.h"
#include "IMU.h"
#include "Pressure_Sensor.h"
#include "SD_Card.h"

void serial_plot() {
  Serial.print(p[0]);
  Serial.print("  ");
  Serial.print(p[1]);
  Serial.print("  ");
  Serial.print(p[2]);
  Serial.print("  ");
  Serial.print(p[3]);
  Serial.print("  ");
  Serial.println(pAvg);
  //Serial.print("  "); Serial.print(accX, 3); Serial.print("  "); Serial.print(accY, 3); Serial.print("  "); Serial.print(accZ, 3); Serial.print("  "); Serial.print(gyroX, 3); Serial.print("  "); Serial.print(gyroY, 3); Serial.print("  "); Serial.print(gyroZ, 3);  Serial.print("  ");
  Serial.print("  ");
}


void setup() {
  if (SERIAL) {
    SERIAL_PORT.begin(115200);
  }

  SD_Setup();
  create_new_file();
  IMU_setup();
  setup_pressure_sensor();
  delay(5000);
}

void loop() {
  float startTime = millis();
  while (((millis() - startTime) / 1000) <= 30) {
    cTime = (millis() - startTime);

    IMU_reading();
    p = getAllPressures();
    printPressureReadings(p);
    pAvg = (p[0] + p[1] + p[2] + p[3]) / 4;

    Write_SDcard();
    
    // serial_plot();
  }
}



