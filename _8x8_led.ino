#include <SPI.h>
const int slaveSelect = 10;
const int decodeMode = 9;
const int intensity = 10;
const int scanLimit = 11;
const int shutDown = 12;
const int dispTest = 15;
byte i;
const byte character[8] =                     //output 'B'
  { 0x00, 0x7f,
    0x49, 0x49,
    0x49, 0x36,
    0x00, 0x00  };
const byte chord_C[8] =                       //chord: C
    {
      B00001000, B00000000,
      B00100000, B01000000,
      B00000000, B00000000,
      B00000000, B00000000
    };
const byte chord_G[8] =                       //chord: G 
    {
      B00000000, B01000000,
      B10000100, B00000000,
      B00000000, B00000000,
      B00000000, B00000000
    };
const byte chord_Am7[8] =                       //chord: Am7 
    {
      B00000000, B00001000,
      B00110000, B00000000,
      B00000000, B00000000,
      B00000000, B00000000
    };
const byte chord_Em[8] =                       //chord: Em 
    {
      B00000000, B01100000,
      B00000000, B00000000,
      B00000000, B00000000,
      B00000000, B00000000
    };
void setup() {
  // put your setup code here, to run once:
  SPI.begin();
  pinMode(slaveSelect, OUTPUT);
  digitalWrite(slaveSelect, HIGH);
  sendCommand(shutDown, 1);
  sendCommand(dispTest, 0);
  sendCommand(intensity, 1);
  sendCommand(scanLimit, 7);
  sendCommand(decodeMode, 0);
  for (i=0;i<8;i++)           //起始為0
    sendCommand(i+1, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (i=0;i<8;i++)
    sendCommand(i+1, chord_Am7[i]);
  delay(2000);
  for (i=0;i<8;i++)
      sendCommand(i+1, chord_C[i]);
  delay(2000);
  for (i=0;i<8;i++)
      sendCommand(i+1, chord_Em[i]);
  delay(2000);
  for (i=0;i<8;i++)
      sendCommand(i+1, chord_G[i]);
  delay(2000);
}
void sendCommand(byte command, byte value)
{
  digitalWrite(slaveSelect, LOW);
  SPI.transfer(command);
  SPI.transfer(value);
  digitalWrite(slaveSelect, HIGH);
}
