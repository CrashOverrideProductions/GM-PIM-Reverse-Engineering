// |------------------------------- HEADER -----------------------------------------------------------------------------------------------------------------|
// APPLICATION:      POWERTRAIN INTERFACE MODULE - OBDII (ELM327) to GM-UART (ALDL)
// PURPOSE:          ALGORITHIMS
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

// |------------------------------- GENERATE ALDL CHECKSUM -------------------------------------------------------------------------------------------------|
int Calculate_ALDLChecksum(uint8_t BroadcastFrame[], int arraySize){
  int FrameSum = 0;
  int FrameLen = (arraySize - 2);
  int i = 0;

  while (i < 20){
      FrameSum = (FrameSum + BroadcastFrame[i]);
      i = i +1;
    }

  FrameSum = (FrameSum & 0xFF);
  
  if (FrameSum != 0){
      FrameSum = (0x100 - FrameSum);
  }
  
  return (FrameSum); 
  }

// REWRITE THIS BEFORE PUBLIC VIEW
int SetBit(int Value, Bit, boolean OnOff ){
  }
