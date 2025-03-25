
#include "globals.h"
#define SERIAL 0  // 1 for serial monitor on and 0 for serial monitor off

int shoe = LEFT;  // LEFT for left shoe and RIGHT for right shoe
// int shoe = RIGHT; //
#include <Arduino.h>

#define WEIGHT 56

float predicted_value = 0;

unsigned long cTime, previousTime = 0, syncedTime;
const int samplingFrequency = 200;
unsigned long interval = 1000 / samplingFrequency;

#include "IMU.h"
#include "Pressure_Sensor.h"
#include "SD_Card.h"
#include "DL.h"

#define SYNC_PIN 20
int sync;

void setup() {
  if (SERIAL) {
    Serial.begin(9600);
  }

  pinMode(SYNC_PIN, INPUT);
  SD_Setup();
  create_new_file();
  IMU_setup();
  setup_pressure_sensor();
  DL_setup();
  delay(1000);
}

void loop() {
  // sync = digitalRead(SYNC_PIN);

  sync = 1;


  if (sync == 1) {
    syncedTime = millis();
    if (SERIAL) Serial.println("synced!!");

    while (1) {
      unsigned long currentTime = millis();
      if (currentTime - previousTime >= 1) {
        previousTime = currentTime;
        cTime = currentTime - previousTime;

        IMU_reading();
        // float p[5] = {0};  // Ensure p is declared before usage

        // WEIGHT OF THE SUBJECT IS ADDED IN getAllPressures function in the P array

        p = getAllPressures();
        printPressureReadings(p);


        standardize(p, scaled_features, 5);
        predicted_value = predictDL();  // Fixed function call

        if (SERIAL) {
          Serial.print("Predicted Value: ");
          Serial.println(predicted_value);
        }

        pAvg = (p[0] + p[1] + p[2] + p[3]) / 4;

        // Write data to SD card
        Write_SDcard();
      }
    }
  } else {
    if (SERIAL) Serial.println("vicon not synced!!");
  }
}