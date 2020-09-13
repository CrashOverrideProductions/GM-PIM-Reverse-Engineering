// |------------------------------- HEADER -----------------------------------------------------------------------------------------------------------------|
// APPLICATION:      POWERTRAIN INTERFACE MODULE - OBDII (ELM327) to GM-UART (ALDL)
// PURPOSE:          DEBUG FUNCTIONS
// AUTHOR:           JUSTIN BLAND
// DATE:             13/06/2020
// AUDIT DATE:
// STATUS:           IN DEVELOPMENT
//
// LICENCE:          CREATIVE COMMONS (CC BY-NC-SA 4.0)
//
// REVISIONS:
//
// REVIEW HISTORY:   06/07/2020  FILE CREATION

// |------------------------------- DEVICE STARTUP ---------------------------------------------------------------------------------------------------------|
void DeviceStartup() {
  if (DebugEnable == LOW) {
    esp_chip_info_t chip_info;
    esp_chip_info(&chip_info);

    //StartupLogo();
    Serial.println("CRASH-OVERRIDE PRODUCTIONS");
    Serial.println("POWERTRAIN INTERFACE MODULE - Version 0.0.0.1");
    Serial.println();

    Serial.println("CPU:            Espressif Systems, ESP32");

    Serial.print("  SPEED:   ");
    Serial.print(ESP.getCpuFreqMHz());
    Serial.println("MHz");

    Serial.print("  CORES:   ");
    Serial.printf("%d cores Wifi %s%s\n", chip_info.cores, (chip_info.features & CHIP_FEATURE_BT) ? "/BT" : "", (chip_info.features & CHIP_FEATURE_BLE) ? "/BLE" : "");

    Serial.print("  MEMORY:  ");
    Serial.print(ESP.getHeapSize() / 1024);
    Serial.println("KB");

    Serial.print("  FLASH:   ");
    double flash = ESP.getFlashChipSize();
    Serial.print((flash / 1024) / 1024);
    Serial.println("MB");

    Serial.println("");
  }
  // SET FRAME SIZE
  if (FrameSize == HIGH) {
    //BaseFrameShort[14] = SetBit(BaseFrameShort[14], 16, true);
  }
  else {
    //BaseFrameShort[14] = SetBit(BaseFrameShort[14], 16, false);
  }


  // SET TRANSMISSION TYPE
  if (TransPin == HIGH) {
    BaseFrameShort[14] = SetBit(BaseFrameShort[14], 16, true);
  }
  else {
    BaseFrameShort[14] = SetBit(BaseFrameShort[14], 16, false);
  }

  // SET ENGINE TYPE
  if (EnginePin == HIGH) {
    // BaseFrameShort[14] = SetBit(BaseFrameShort[14], 16, true);
  }
  else {
    // BaseFrameShort[14] = SetBit(BaseFrameShort[14], 16, false);
  }
}

//#define FrameSize 34     // High = VY / VZ  |  Low = VT / VX
//#define TransPin 39     // High = Auto     |  Low = Manual
//#define EnginePin 36    // High = V6       |  Low = V8

// |------------------------------- MULTITHREADING ---------------------------------------------------------------------------------------------------------|
void StartMultithreading() {
  xTaskCreatePinnedToCore(
    OBDIIStartup,   /* Task function. */
    "OBDIIStartup",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task1,      /* Task handle to keep track of created task */
    1);          /* pin task to core 1 */
  delay(50);

  xTaskCreatePinnedToCore(
    GenerateSend41Frame,   /* Task function. */
    "GenerateSend41Frame",     /* name of task. */
    10000,       /* Stack size of task */
    NULL,        /* parameter of the task */
    1,           /* priority of the task */
    &Task0,      /* Task handle to keep track of created task */
    0);          /* pin task to core 0 */
  delay(50);
}

void PrintDebugMessage(String Message) {
  if (DebugEnable == LOW) {
    DebugSerial.println(Message);
  }
}

void FaultLight(boolean Status, String Message){
  if (Status == true){
    digitalWrite(FaultLED, HIGH);
    PrintDebugMessage(Message);
    }
    else{
      digitalWrite(FaultLED, LOW);
      }
  
  }
