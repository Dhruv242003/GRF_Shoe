void IMU_setup();
void IMU_reading();
void printPaddedInt16b(int16_t val);
void printRawAGMT(ICM_20948_AGMT_t agmt);
void printFormattedFloat(float val, uint8_t leading, uint8_t decimals);
void printScaledAGMT(ICM_20948_SPI *sensor);
void printScaledAGMT(ICM_20948_I2C *sensor);



void IMU_setup() {

  WIRE_PORT.begin();
  WIRE_PORT.setClock(400000);

  //myICM.enableDebugging(); // Uncomment this line to enable helpful debug messages on Serial

  bool initialized = false;
  while (!initialized) {


    myICM.begin(WIRE_PORT, AD0_VAL);
    if (SERIAL) {
      SERIAL_PORT.print(F("Initialization of the sensor returned: "));
      SERIAL_PORT.println(myICM.statusString());
    }

    if (myICM.status != ICM_20948_Stat_Ok) {
      if (SERIAL) SERIAL_PORT.println("Trying again...");
      delay(500);
    } else {
      initialized = true;
    }
  }
}





// void IMU_reading() {
//   if (myICM.dataReady()) {
//     myICM.getAGMT();          // The values are only updated when you call 'getAGMT'
//                               //    printRawAGMT( myICM.agmt );     // Uncomment this to see the raw values, taken directly from the agmt structure
//     printScaledAGMT(&myICM);  // This function takes into account the scale settings from when the measurement was made to calculate the values with units
//     delay(30);
//   } else {
//     SERIAL_PORT.println("Waiting for data");
//     delay(500);
//   }
// }


void IMU_reading() {
  if (myICM.dataReady()) {
    myICM.getAGMT();  // The values are only updated when you call 'getAGMT'
    gyroX = myICM.gyrX();
    gyroY = myICM.gyrY();
    gyroZ = myICM.gyrZ();
    accX = myICM.accX();
    accY = myICM.accY();
    accZ = myICM.accZ();
  }

  //X_norm = (X - X_min) / (X_max - X_min)

  //  float accX_n = (accX + 16000)/32000;
  //  float accY_n = (accY + 16000)/32000;
  //  float accZ_n = (accZ + 16000)/32000;
  //  float gyroX_n = (gyroX + 2000)/4000;
  //  float gyroY_n = (gyroY + 2000)/4000;
  //  float gyroZ_n = (gyroZ + 2000)/4000;
}



void printPaddedInt16b(int16_t val) {
  if (val > 0) {
    SERIAL_PORT.print(" ");
    if (val < 10000) {
      SERIAL_PORT.print("0");
    }
    if (val < 1000) {
      SERIAL_PORT.print("0");
    }
    if (val < 100) {
      SERIAL_PORT.print("0");
    }
    if (val < 10) {
      SERIAL_PORT.print("0");
    }
  } else {
    SERIAL_PORT.print("-");
    if (abs(val) < 10000) {
      SERIAL_PORT.print("0");
    }
    if (abs(val) < 1000) {
      SERIAL_PORT.print("0");
    }
    if (abs(val) < 100) {
      SERIAL_PORT.print("0");
    }
    if (abs(val) < 10) {
      SERIAL_PORT.print("0");
    }
  }
  SERIAL_PORT.print(abs(val));
}

void printRawAGMT(ICM_20948_AGMT_t agmt) {
  SERIAL_PORT.print("RAW. Acc [ ");
  printPaddedInt16b(agmt.acc.axes.x);
  SERIAL_PORT.print(", ");
  printPaddedInt16b(agmt.acc.axes.y);
  SERIAL_PORT.print(", ");
  printPaddedInt16b(agmt.acc.axes.z);
  SERIAL_PORT.print(" ], Gyr [ ");
  printPaddedInt16b(agmt.gyr.axes.x);
  SERIAL_PORT.print(", ");
  printPaddedInt16b(agmt.gyr.axes.y);
  SERIAL_PORT.print(", ");
  printPaddedInt16b(agmt.gyr.axes.z);
  SERIAL_PORT.print(" ], Mag [ ");
  printPaddedInt16b(agmt.mag.axes.x);
  SERIAL_PORT.print(", ");
  printPaddedInt16b(agmt.mag.axes.y);
  SERIAL_PORT.print(", ");
  printPaddedInt16b(agmt.mag.axes.z);
  SERIAL_PORT.print(" ], Tmp [ ");
  printPaddedInt16b(agmt.tmp.val);
  SERIAL_PORT.print(" ]");
  SERIAL_PORT.println();
}

void printFormattedFloat(float val, uint8_t leading, uint8_t decimals) {
  float aval = abs(val);
  if (val < 0) {
    SERIAL_PORT.print("-");
  } else {
    SERIAL_PORT.print(" ");
  }
  for (uint8_t indi = 0; indi < leading; indi++) {
    uint32_t tenpow = 0;
    if (indi < (leading - 1)) {
      tenpow = 1;
    }
    for (uint8_t c = 0; c < (leading - 1 - indi); c++) {
      tenpow *= 10;
    }
    if (aval < tenpow) {
      SERIAL_PORT.print("0");
    } else {
      break;
    }
  }
  if (val < 0) {
    SERIAL_PORT.print(-val, decimals);
  } else {
    SERIAL_PORT.print(val, decimals);
  }
}

#ifdef USE_SPI
void printScaledAGMT(ICM_20948_SPI *sensor) {
#else
void printScaledAGMT(ICM_20948_I2C *sensor) {
#endif
  SERIAL_PORT.print("Scaled. Acc (mg) [ ");
  printFormattedFloat(sensor->accX(), 5, 2);
  SERIAL_PORT.print(", ");
  printFormattedFloat(sensor->accY(), 5, 2);
  SERIAL_PORT.print(", ");
  printFormattedFloat(sensor->accZ(), 5, 2);
  SERIAL_PORT.print(" ], Gyr (DPS) [ ");
  printFormattedFloat(sensor->gyrX(), 5, 2);
  SERIAL_PORT.print(", ");
  printFormattedFloat(sensor->gyrY(), 5, 2);
  SERIAL_PORT.print(", ");
  printFormattedFloat(sensor->gyrZ(), 5, 2);
  SERIAL_PORT.print(" ], Mag (uT) [ ");
  printFormattedFloat(sensor->magX(), 5, 2);
  SERIAL_PORT.print(", ");
  printFormattedFloat(sensor->magY(), 5, 2);
  SERIAL_PORT.print(", ");
  printFormattedFloat(sensor->magZ(), 5, 2);
  SERIAL_PORT.print(" ], Tmp (C) [ ");
  printFormattedFloat(sensor->temp(), 5, 2);
  SERIAL_PORT.print(" ]");
  SERIAL_PORT.println();
}
