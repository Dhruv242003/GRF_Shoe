void setup_pressure_sensor();
void pcaselect(uint8_t i);
float* getAllPressures();


void pcaselect(uint8_t i) {
  if (i > 3) return;

  Wire.beginTransmission(PCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}


void setup_pressure_sensor() {

  delay(1000);
  Wire.begin();

  pcaselect(0);  // Heel
  mpr0.begin();
  if (!mpr0.begin()) {
    if (SERIAL) Serial.println("Pressure sensor 0 is not ready.");
    while (1)
      ;
  }

  pcaselect(1);  // Meta 45
  mpr1.begin();
  if (!mpr1.begin()) {
    if (SERIAL) Serial.println("Pressure sensor 1 is not ready.");
    while (1)
      ;
  }

  pcaselect(2);  // Toe
  mpr2.begin();
  if (!mpr2.begin()) {
    if (SERIAL) Serial.println("Pressure sensor 2 is not ready.");
    while (1)
      ;
  }

  pcaselect(3);  // Meta 12
  mpr3.begin();
  if (!mpr3.begin()) {
    if (SERIAL) Serial.println("Pressure sensor 3 is not ready.");
    while (1)
      ;
  }
}


float* getAllPressures() {
  // Serial.println("getAllPressures");

  static float pressures[5];  // Static array to store pressure values from 4 sensors
  pressures[4] = WEIGHT;

  if (shoe == RIGHT) {
    pcaselect(0);
    pressures[0] = right_heel + mpr0.readPressure(TORR);

    pcaselect(1);
    pressures[1] = right_meta45 + mpr1.readPressure(TORR);

    pcaselect(2);
    pressures[2] = right_toe + mpr2.readPressure(TORR);

    pcaselect(3);
    pressures[3] = right_meta12 + mpr3.readPressure(TORR);
  } else if (shoe == LEFT) {
    pcaselect(3);
    pressures[0] = left_heel + mpr3.readPressure(TORR);

    pcaselect(2);
    pressures[1] = left_meta45 + mpr2.readPressure(TORR);

    pcaselect(1);
    pressures[2] = left_toe + mpr1.readPressure(TORR);

    pcaselect(0);
    pressures[3] = left_meta12 + mpr0.readPressure(TORR);
  }

  return pressures;  // Return the array with the pressure values
}


void printPressureReadings(float* pressureArray) {
  if (SERIAL) {


    Serial.println("Pressure Sensor Readings:");
    Serial.println("=========================");

    // Print each pressure value with proper formatting
    for (int i = 0; i < 4; i++) {
      Serial.print("Sensor ");
      Serial.print(i);
      Serial.print(": ");
      Serial.print(pressureArray[i], 2);  // Print the value with 2 decimal places
      Serial.println(" Torr");            // Assuming the pressure is in Pascals (Pa)
    }

    Serial.println("=========================");
  }
}