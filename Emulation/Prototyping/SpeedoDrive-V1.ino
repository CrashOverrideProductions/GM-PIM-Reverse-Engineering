// |------------------------------- HEADER -----------------------------------------------------------------------------------------------------------------|
// APPLICATION:      POWERTRAIN INTERFACE MODULE - SPEEDO GENERATOR
// PURPOSE:          PROOF OF CONCEPT
// AUTHOR:           JUSTIN BLAND
// DATE:             13/09/2020
// AUDIT DATE:
// STATUS:           IN DEVELOPMENT
//
// LICENCE:          CREATIVE COMMONS (CC BY-NC-SA 4.0)
//
// REVISIONS:
//
// REVIEW HISTORY:   13/09/2020  FILE CREATION

// |------------------------------- DEFINITIONS -------------------------------------------------------------------------------------------------------------|
#define SpeedoDrive 6
#define PPK 6301

double KPH = 0;

// |------------------------------- SETUP  ------------------------------------------------------------------------------------------------------------------|
void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  Serial.begin(115200);
  Serial.println("Begin Test");
  Serial.setTimeout(5);
}

// |------------------------------- LOOP  -------------------------------------------------------------------------------------------------------------------|
void loop() {
  if (Serial.available())
  {
    KPH = Serial.parseInt();  
  }
  if (KPH != 0)
  {
  GeneratePulse(KPH);
  }
}

// |------------------------------- GENERATE PULSE  ---------------------------------------------------------------------------------------------------------|
void GeneratePulse(double InteruptSpeed)
{
  if (InteruptSpeed <  20)
  {
    double SpeedoPulse = CalcPulseMS(InteruptSpeed);
    int i = 0;

    while (i < 10)
    {
      digitalWrite(SpeedoDrive, HIGH);
      delay(SpeedoPulse);
      digitalWrite(SpeedoDrive, LOW);
      delay(SpeedoPulse);
      i++;
    }
  }
  else
  {
    double SpeedoPulse = CalcPulseUS(InteruptSpeed);
    int i = 0;

    while (i < 10)
    {
      digitalWrite(SpeedoDrive, HIGH);
      delayMicroseconds(SpeedoPulse);
      digitalWrite(SpeedoDrive, LOW);
      delayMicroseconds(SpeedoPulse);
      i++;
    }
  }
}


// |------------------------------- ALGORITHIMS  -----------------------------------------------------------------------------------------------------------|
double CalcPulseMS (double InputSpeed)
{
  double result;

  result = (1000/((InputSpeed * PPK) / 3600))/2;
  return result;
}

double CalcPulseUS (double InputSpeed)
{
  double result;

  //result = 7200 / (InputSpeed * PPK);
  result = (1000/((InputSpeed * PPK) / 3600)*1000)/2;

  return result;
  
}
