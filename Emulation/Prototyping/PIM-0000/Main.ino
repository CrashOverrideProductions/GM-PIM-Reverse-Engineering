// |------------------------------- HEADER -----------------------------------------------------------------------------------------------------------------|
// APPLICATION:      POWERTRAIN INTERFACE MODULE - OBDII (STN2120) to GM-UART (ALDL)
// PURPOSE:          MAIN
// AUTHOR:           JUSTIN BLAND
// DATE:             06/07/2020
// AUDIT DATE:
// STATUS:           IN DEVELOPMENT
//
// LICENCE:          CREATIVE COMMONS (CC BY-NC-SA 4.0)
//
// REVISIONS:
//
// REVIEW HISTORY:   06/07/2020  FILE CREATION
//

// |------------------------------- DEFINITIONS -------------------------------------------------------------------------------------------------------------|
// INCLUDES
#include <math.h>

// DEBUG SERIAL PORT
#define DebugSerial Serial

// GM-UART SERIAL
#define ALDLSerial Serial2

// OBDII SERIAL PORT
#define OBDIISerial Serial1

// LED PINS
#define FaultLED 23
#define OKLED 22

// OBDII DEFINITIONS
#define OBDIIProtocol 12

// INPUT PIN DEFINITIONS
#define DebugEnable 35   // High = Disabled |  Low = Enabled
#define FrameSize 34     // High = VY / VZ  |  Low = VT / VX
#define TransPin 39      // High = Auto     |  Low = Manual
#define EnginePin 36     // High = V6       |  Low = V8

// MULTITHREAD DEFINITIONS
TaskHandle_t Task0;
TaskHandle_t Task1;


// |------------------------------- ARRAYS ------------------------------------------------------------------------------------------------------------------|
//      VT / VX Frame          0     1     2     3     4     5     6     7     8     9     10    11    12    13    14    15    16
uint8_t BaseFrameShort[17] = {0x41, 0x63, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00};
uint8_t SendFrameShort[17] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

//      VY / VZ Frame         0     1     2     3     4     5     6     7     8     9     10    11    12    13    14    15    16    17    18    19    20    21
uint8_t BaseFrameLong[22] = {0x41, 0x68, 0x12, 0x00, 0x76, 0x34, 0x78, 0x41, 0xAF, 0x22, 0x40, 0x96, 0x23, 0x12, 0x25, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t SendFrameLong[22] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

//                         0     1     2     3     4     5     6     7     8     9     10    11    12    13    14    15    16    17    18    19
byte SupportedPIDS[20] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

// 40 Request         0     1     2     3     4     5
byte BcmRequest[6] = {0x40, 0x58, 0xFF, 0xFF, 0xFF, 0x6B};

//                    0     1     2     3     4     5
byte ALDLFrame[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

//                        0     1     2     3
byte OBDIIResponse[4] = {0x00, 0x00, 0x00, 0x00};

// |------------------------------- GLOBAL VARIABLES --------------------------------------------------------------------------------------------------------|
bool DeviceStart = true;
bool EngineRun = false;


unsigned long timeout;
int OBD2Protocol = 0; // 0 =


// |------------------------------- PROGRAM SETUP ----------------------------------------------------------------------------------------------------------|
void setup() {
  // START DEBUG PORT (Onboard USB or Pins 01 TX | 03 RX )
  if (DebugEnable == LOW) {
    DebugSerial.begin(115200, SERIAL_8N1, 3, 1);
  }

  // START GM-UART PORT (8192 Baud Pins 17 TX | RX 16)
  ALDLSerial.begin(8192, SERIAL_8N1, 16, 17);

  // OBDII Port - 38400 Baud Pins 2 RX / 4 TX
  OBDIISerial.begin(38400, SERIAL_8N1, 2, 4);

  // STARTUP ROUTINE
  try {
    DeviceStartup();
  }
  catch (...) {
    DeviceStart = false;
    //FaultLight(true, "Startup Failure");

  }

  // START COMMUNICATIONS
  if (DeviceStart = true) {
    try {
      if (ValidKey) {
        // Call Normal OBDII Opperation
        // Call Normal ALDL Opperation

      }

    }
    catch (...) {
      FaultLight(true, "Communications Failure");
    }
  }
  else {
    FaultLight(true, "Startup Failure");
    PrintDebugMessage("Restarting in 5 Seconds");
    delay(5000);
    ESP.restart();
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
