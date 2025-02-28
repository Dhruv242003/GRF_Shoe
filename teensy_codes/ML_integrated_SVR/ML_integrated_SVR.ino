
#include "globals.h"
#define SERIAL 1  // 1 for serial monitor on and 0 for serial monitor off 

int shoe = LEFT;   // LEFT for left shoe and RIGHT for right shoe


unsigned long cTime;
unsigned long previousTime = 0;
const int samplingFrequency = 200;
unsigned long interval = 1000 / samplingFrequency;
unsigned long syncedTime;


#include "IMU.h"
#include "Pressure_Sensor.h"
#include "SD_Card.h"
#include "svr_model.h"
#include "scaling_params.h"
#include "svr.h"

#define SYNC_PIN 20
int sync;

#define DISABLE_SENSOR -1


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
  // // Serial.print("  "); Serial.print(accX, 3); Serial.print("  "); Serial.print(accY, 3); Serial.print("  "); Serial.print(accZ, 3); Serial.print("  "); Serial.print(gyroX, 3); Serial.print("  "); Serial.print(gyroY, 3); Serial.print("  "); Serial.print(gyroZ, 3);  Serial.print("  ");
  Serial.print("  ");
}


void setup() {

  if (SERIAL) {
    SERIAL_PORT.begin(115200);
  }

  pinMode(SYNC_PIN, INPUT);

  SD_Setup();
  create_new_file();
  IMU_setup();
  setup_pressure_sensor();
  delay(1000);
}

void loop() {
  // sync = digitalRead(SYNC_PIN);
  
  sync = 1;
  // sync = Serial.parseInt();

  if(sync==1){
    syncedTime = millis();
    if(SERIAL) Serial.println("synced!!");

    while(1)
    {


      unsigned long currentTime = millis();
      /////// DATA READING STARTS ////////

      if (currentTime - previousTime >= interval) {
        previousTime = currentTime;
        cTime = currentTime - previousTime;

        IMU_reading();
        
        // Read pressure sensor values
        p = getAllPressures();
        printPressureReadings(p); 

        // Standardize sensor values BEFORE passing to svr_predict
        standardize(p, scaled_features, num_features);

        // Use scaled features in SVR prediction
        predicted_value = svr_predict(scaled_features);

        if (SERIAL) {
          Serial.print("Predicted Value: ");
          Serial.println(predicted_value);
        }

        // Write data to SD card
        // Write_SDcard();
        // serial_plot();
      }
    }
  }
  else{
    if(SERIAL) Serial.println("vicon not synced!!");
  }

  
}
