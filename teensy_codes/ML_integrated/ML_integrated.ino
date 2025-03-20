
#include "globals.h"
#define SERIAL 0  // 1 for serial monitor on and 0 for serial monitor off

int shoe = LEFT;  // LEFT for left shoe and RIGHT for right shoe
// int shoe = RIGHT; //
#include <Arduino.h>

#define WEIGHT 82

// Define Linear regression model parameters
float coefficients[] = { -51.24390447, -26.97226867, 58.29750692, -78.83222018, -15.7695863 };
float intercept = -333.4212807405909;

// Standardization parameters
float mean[] = { 800.93105253, 769.04597102, 755.89004629, 761.82081103, 68.2129201 };
float std_dev[] = { 14.93579566, 3.36180796, 2.34004597, 5.35692161, 4.91855033 };

const int num_features = sizeof(coefficients) / sizeof(coefficients[0]);
float scaled_features[5];
float predicted_value = 0;

// Standardization function
void standardize(float input[], float output[], int size) {
  for (int i = 0; i < size; i++) {
    output[i] = (input[i] - mean[i]) / std_dev[i];
  }
}


// Prediction function
float predict(float scaled_input[], int size) {
  float result = intercept;
  for (int i = 0; i < size; i++) {
    result += scaled_input[i] * coefficients[i];
  }
  return result;
}

unsigned long cTime, previousTime = 0, syncedTime;
const int samplingFrequency = 200;
unsigned long interval = 1000 / samplingFrequency;

#include "IMU.h"
#include "Pressure_Sensor.h"
#include "SD_Card.h"

#define SYNC_PIN 20
int sync;

void setup() {
  if (SERIAL) {
    Serial.begin(115200);
  }

  pinMode(SYNC_PIN, INPUT);
  SD_Setup();
  create_new_file();
  IMU_setup();
  setup_pressure_sensor();
  delay(1000);
}

void loop() {
  sync = digitalRead(SYNC_PIN);

  // sync = 1;

  if (sync == 1) {
    syncedTime = millis();
    if (SERIAL) Serial.println("synced!!");

    while (1) {
      unsigned long currentTime = millis();
      if (currentTime - previousTime >= interval) {
        previousTime = currentTime;
        cTime = currentTime - previousTime;

        IMU_reading();
        // float p[5] = {0};  // Ensure p is declared before usage

        // WEIGHT OF THE SUBJECT IS ADDED IN getAllPressures function in the P array

        p = getAllPressures();
        printPressureReadings(p);


        standardize(p, scaled_features, num_features);
        predicted_value = predict(scaled_features, num_features);  // Fixed function call

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