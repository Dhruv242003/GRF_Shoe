#include <Wire.h>
#include <SparkFun_MicroPressure.h>

SparkFun_MicroPressure mpr; // Initialize pressure sensor

void setup() {
  Serial.begin(115200);
  while (!Serial); // Wait for Serial to connect (for debugging)
  
  Wire.begin();
  Serial.println("\nMicro Pressure Sensor Test !!");

  // Initialize the sensor
  if (!mpr.begin()) {
    Serial.println("Cannot connect to MicroPressure sensor.");
    while (1); // Halt execution if sensor fails to initialize
  }

  Serial.println("Setup Done");
}

void loop() {
  // Read and print pressure in Torr
  Serial.print(mpr.readPressure(TORR), 3);
  Serial.println(" torr");

  delay(100);
}
