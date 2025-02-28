void SD_Setup();
void create_new_file();
void Write_SDcard();

void SD_Setup() {
  // Check if the SD card is present
  if (!SD.begin(chipSelect)) {

    if (SERIAL) Serial.println("SD card initialization failed!");
    return;
  }
  if (SERIAL) Serial.println("SD card is present.");
}

void create_new_file() {

  const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
  while (SD.exists(fileName)) {
    if (fileName[BASE_NAME_SIZE + 1] != '9') {
      fileName[BASE_NAME_SIZE + 1]++;
    } else if (fileName[BASE_NAME_SIZE] != '9') {
      fileName[BASE_NAME_SIZE + 1] = '0';
      fileName[BASE_NAME_SIZE]++;
    } else {
      if (SERIAL) Serial.println("Can't create file name");

      // Blink Portenta LED Red ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    }
  }
  file = SD.open(fileName, FILE_WRITE);

  file.print("currTime");
  file.print(",");
  file.print("s1");
  file.print(",");
  file.print("s2");
  file.print(",");
  file.print("s3");
  file.print(",");
  file.print("s4");
  file.print(",");
  file.print("s");
  file.print(",");
  file.print("AccX");
  file.print(",");
  file.print("AccY");
  file.print(",");
  file.print("AccZ");
  file.print(",");
  file.print("GyroX");
  file.print(",");
  file.print("GyroY");
  file.print(",");
  file.print("GyroZ");  //file.print(",");
  file.print(",");
  file.print("GRF");

  //  file.print("s_ax");                           file.print(",");
  //  file.print("s_ay");                           file.print(",");
  //  file.print("s_az");                           file.print(",");
  //  file.print("s_gx");                           file.print(",");
  //  file.print("s_gy");                           file.print(",");
  //  file.print("s_gz");

  file.println();
  file.close();  // Closing File in setup

  if (SERIAL) Serial.println("s1, s2, s3, s4, s, AccX, AccY, AccZ, GyroX, GyroY, GyroZ, GRF");  // Legend for Serial Plot
  delay(2000);
}


void Write_SDcard() {
  file = SD.open(fileName, FILE_WRITE);
  if (file) {
    // if (SERIAL) Serial.println("Inside SD write");
    file.print((millis()-syncedTime-interval));
    file.print(",");

    file.print((p[0]));
    file.print(",");
    file.print((p[1]));
    file.print(",");
    file.print((p[2]));
    file.print(",");
    file.print((p[3]));
    file.print(",");
    file.print((pAvg));
    file.print(",");
    
    file.print((accX));
    file.print(",");
    file.print((accY));
    file.print(",");
    file.print((accZ));
    file.print(",");
    file.print((gyroX));
    file.print(",");
    file.print((gyroY));
    file.print(",");
    file.print((gyroZ));  //file.print(",");
    file.print(",");
    file.print((predicted_value));
    //    file.print((s_ax));                   file.print(",");
    //    file.print((s_ay));                   file.print(",");
    //    file.print((s_az));                   file.print(",");
    //    file.print((s_gx));                   file.print(",");
    //    file.print((s_gy));                   file.print(",");
    //    file.print((s_gz));

    file.println();  //End of Row move to next row
    file.close();
  } else {
    if (SERIAL) Serial.println("can't write in sd card");
  }
}
