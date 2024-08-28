//################################### IMU_ICM_20948 #####################################
#include "ICM_20948.h" 

#define SERIAL_PORT Serial  //Default Serial port for printing
#define CS_PIN 2     
#define WIRE_PORT Wire1   // Using 2nd (SCL1, SDA2) I2C bus of teensy 4.1
#define AD0_VAL 1

ICM_20948_I2C myICM;    // IMU Obj

//################################### Pressure_Sensor #####################################

#include<Wire.h>
#include <SparkFun_MicroPressure.h>

#define PCAADDR 0x70    // Default gateway address of I2C Multiplixer

SparkFun_MicroPressure mpr0;   // Pressure Sensor obj
SparkFun_MicroPressure mpr1;
SparkFun_MicroPressure mpr2;
SparkFun_MicroPressure mpr3;

float* p;
float pAvg;


//################################### SD_Card #####################################

#include <SD.h>
#include <SPI.h>

float accX, accY, accZ, gyroX, gyroY, gyroZ;
float s1, s2, s3, s4, s = 0;

const int chipSelect = BUILTIN_SDCARD;  // Teensy 4.1 SD card built-in CS pin

File file;
#define FILE_BASE_NAME "DATA"
char fileName[22] = FILE_BASE_NAME "00.csv";
float cTime;

// int avg_size = 10; 
// static int baseline_value_1;
// static int baseline_value_2;
// static int baseline_value_3;
// static int baseline_value_4;

// int current_value_1;
// int current_value_2;
// int current_value_3;
// int current_value_4;
