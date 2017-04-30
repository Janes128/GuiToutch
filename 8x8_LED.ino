#include <SPI.h>
const int slaveSelect = 10;
const int decodeMode = 9;
const int intensity = 10;
const int scanLimit = 11;
const int shutDown = 12;
const int dispTest = 15;
byte i;
const byte character[8] =
  { 0x00, 0x7f,
    0x49, 0x49,
    0x49, 0x36,
    0x00, 0x00  };
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
  for (i=0;i<8;i++)
    sendCommand(i+1, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (i=0;i<8;i++)
    sendCommand(i+1, character[i]);
}
void sendCommand(byte command, byte value)
{
  digitalWrite(slaveSelect, LOW);
  SPI.transfer(command);
  SPI.transfer(value);
  digitalWrite(slaveSelect, HIGH);
}
