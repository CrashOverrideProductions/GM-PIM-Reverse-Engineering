// |------------------------------- HEADER -----------------------------------------------------------------------------------------------------------------|
// APPLICATION:      POWERTRAIN INTERFACE MODULE - SPEEDO GENERATOR
// PURPOSE:          GENERATE SQUARE WAVE PULSE TO DRIVE SPEEDOMETER
// AUTHOR:           JUSTIN BLAND
// DATE:             14/09/2020
// AUDIT DATE:
// STATUS:           IN DEVELOPMENT
//
// LICENCE:          CREATIVE COMMONS (CC BY-NC-SA 4.0)
//
// DESIGNED MCU:     TEST - ATmega328P | PRODUCTION - ATTINY202
//
// REVISIONS:
//                   14/09/2020  FILE CREATION

// |------------------------------- HELPFUL INFO ------------------------------------------------------------------------------------------------------------|
    // ATTINY202 PINS (ALL)
        // 1 - VDD | 1.8V - 5.5V
        // 2 - PA6 | UART TXD
        // 3 - PA7 | UART RXD
        // 4 - PA2 |
        // 5 - PA1 |
        // 6 - PA0 | RESET
        // 7 - PA3 |
        // 8 - GND
    
    // ATmega328P PINS (ONLY USEFUL)
        //  2 - PD0 | UART RXD
        //  3 - PD1 | UART TXD
        // 12 - PD6
    
    // delayMicroseconds
        // Data Type = INT
        // has a minimum delay value of     3 uS
        // has a maximum delay value of 16383 uS
    
    // delay
        // Data Type = INT
        // has a minimum delay value of     1 mS
        // has a minimum delay value of 32767 mS
    
    // Conversion Algorithims (Long Form | Simplified)
        // mS | (1000/((KPH * PPK) / 3600))/2           |        1800000 / (KPH * PPK)
        // uS | (1000/((KPH * PPK) / 3600)*1000)/2      |     1800000000 / (KPH * PPK)



// |------------------------------- DEFINITIONS -------------------------------------------------------------------------------------------------------------|

// Variables
const double PPK = 6301;   // Standard V8 Ute 235/45/R17
const int UartTimeout = 5; //mS
int KPH = 0;

// Pin Definitions
#define OutputPin 6 // 6 for ATmega328 | 2 for ATTINY202 



// |------------------------------- SETUP -------------------------------------------------------------------------------------------------------------------|
void setup()
{
  // Set Output Pin
  pinMode(OutputPin, OUTPUT);

  // Open UART to get Speed
  Serial.begin(115200);
  Serial.setTimeout(UartTimeout);
}

// |------------------------------- LOOP --------------------------------------------------------------------------------------------------------------------|
void loop()
{
  // Check for Updated Speed Value
  if (Serial.available())
  {
    KPH = Serial.parseInt();
  }

  // Generate Pulse if speed not 0 KPH (0 will cause an arithmatic failure)
  if (KPH != 0)
  {
    GeneratePulse(KPH);
  }
}

// |------------------------------- GENERATE PULSE ----------------------------------------------------------------------------------------------------------|
void GeneratePulse(int Speed)
{
  if (Speed < 20) // Less that 20 KPH needs Milliseconds as Pulse Duration is longer than MAX Microseconds
  {
    double SpeedoPulse = CalcPulseMS(Speed);
    digitalWrite(OutputPin, HIGH);
    delay(SpeedoPulse);
    digitalWrite(OutputPin, LOW);
    delay(SpeedoPulse);
  }
  else
  {
    double SpeedoPulse = CalcPulseUS(Speed); // Greater than 20 KPH needs Microseconds for greater pulse resolution
    digitalWrite(OutputPin, HIGH);
    delayMicroseconds(SpeedoPulse);
    digitalWrite(OutputPin, LOW);
    delayMicroseconds(SpeedoPulse);
  }
}

// |------------------------------- CALCULATE PULSE ---------------------------------------------------------------------------------------------------------|
int CalcPulseMS(int Speed)
{
  return (1000 / ((Speed * PPK) / 3600)) / 2;
}

int CalcPulseUS(int Speed)
{
  return (1000 / ((Speed * PPK) / 3600) * 1000) / 2;
}

