#include <Wire.h>
#include <SparkFun_MicroPressure.h>
#include <TeensyThreads.h>

#define PCAADDR 0x70

Threads::Mutex i2cMutex;

void pcaselect(uint8_t i) {
  if (i > 3) return;

  Wire.beginTransmission(PCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();
}

float mprValue0 = 0;
float mprValue1 = 0;
float mprValue2 = 0;
float mprValue3 = 0;

SparkFun_MicroPressure mpr0;
SparkFun_MicroPressure mpr1;
SparkFun_MicroPressure mpr2;
SparkFun_MicroPressure mpr3;

void thread0() {
  while (1) {
    i2cMutex.lock();
    pcaselect(0);
    mprValue0 = mpr0.readPressure(ATM);
    i2cMutex.unlock();
  }
}

void thread1() {
  while (1) {
    i2cMutex.lock();
    pcaselect(1);
    mprValue1 = mpr1.readPressure(ATM);
    i2cMutex.unlock();
  }
}

void thread2() {
  while (1) {
    i2cMutex.lock();
    pcaselect(2);
    mprValue2 = mpr2.readPressure(ATM);
    i2cMutex.unlock();
  }
}

void thread3() {
  while (1) {
    i2cMutex.lock();
    pcaselect(3);
    mprValue3 = mpr3.readPressure(ATM);
    i2cMutex.unlock();
  }
}

void setup() {
  while (!Serial);
  delay(1000);

  Wire.begin();
  Serial.begin(115200);

  Serial.println("\nMicro Pressure Sensor test !!");

  pcaselect(0);
  mpr0.begin();

  pcaselect(1);
  mpr1.begin();

  pcaselect(2);
  mpr2.begin();

  pcaselect(3);
  mpr3.begin();

  threads.addThread(thread0);
  threads.addThread(thread1);
  threads.addThread(thread2);
  threads.addThread(thread3);

  Serial.println("Setup Done");
}

void loop() {
  Serial.print(mprValue0, 4);
  Serial.print("   ");
  Serial.print(mprValue1, 4);
  Serial.print("   ");
  Serial.print(mprValue2, 4);
  Serial.print("   ");
  Serial.println(mprValue3, 4);
  delay(100);
}
