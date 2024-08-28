#include <SD.h>
#include <SPI.h>

const int chipSelect = BUILTIN_SDCARD;  // Teensy 4.1 SD card built-in CS pin

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  while (!Serial) {
    // Wait for the serial monitor to connect
  }
  Serial.println("Initializing SD card...");

  // Check if the SD card is present
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card is present.");

  // Create a text file on the SD card
  File file = SD.open("example.txt", FILE_WRITE);
  if (file) {
    Serial.println("Creating file: example.txt");
    file.println("This is a test file on the SD card.");
    file.close();
    Serial.println("File created successfully.");
  } else {
    Serial.println("Failed to create file.");
  }
}

void loop() {
  // Do nothing here
}
