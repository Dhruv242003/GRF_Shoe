#include<Wire.h>
#include <SparkFun_MicroPressure.h>

#define PCAADDR 0x70

#define SENSOR 2

void pcaselect(uint8_t i) {
  if (i > 3) return;
 
  Wire.beginTransmission(PCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

SparkFun_MicroPressure mpr; // Use default values with reset and EOC pins unused

void setup() {

  while(!Serial);
  delay(1000);
  Wire.begin();
  Serial.begin(115200);

  Serial.println("\nMicro Pressure Sensor test !!");

  pcaselect(SENSOR);

  mpr.begin();

  if(!mpr.begin())
  {
    Serial.println("Cannot connect to MicroPressure sensor.");
    while(1);
  }
  Serial.println("Setup Done");
}

void loop() {
  pcaselect(SENSOR);
  
  // Serial.print(mpr.readPressure(),4);
  // Serial.println(" PSI");
  // Serial.print(mpr.readPressure(PA),1);
  // Serial.println(" Pa");
  // Serial.print(mpr.readPressure(KPA),4);
  // Serial.println(" kPa");
  Serial.print(mpr.readPressure(TORR),3);
  Serial.println(" torr");
  // Serial.print(mpr.readPressure(INHG),4);
  // Serial.println(" inHg");
  // Serial.print(mpr.readPressure(ATM),6);
  // Serial.println(" atm");
  // Serial.print(mpr.readPressure(BAR),6);
  // Serial.println(" bar");
  // Serial.println();
  delay(100);
}