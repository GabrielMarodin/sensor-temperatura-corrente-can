#include <SPI.h>
#include <mcp2515.h>
#include <HardwareSerial.h>
 
struct can_frame canMsg;
struct MCP2515 mcp2515(5); // CS pin is GPIO 5

#define CAN_ID_1 0x010
#define CAN_ID_2 0x011

void setup()
{
  Serial.begin(9600);

  SPI.begin();
 
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}
 
 
void loop()
{
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK)
  {
    if (canMsg.can_id == CAN_ID_1)  // Check if the message is from the sender
    {
      unsigned char data[4];

      for (int i = 0; i<4; i++){
        data[i] = canMsg.data[i];
      }
      

      Serial.println("Data received: ");
      for (int i = 0; i<4; i++){
        Serial.println(data[i]);
        Serial.println((uint8_t)data[i]);
      }
    }
    if (canMsg.can_id == CAN_ID_2)  // Check if the message is from the sender
    {
      unsigned char data[4];

      for (int i = 0; i<4; i++){
        data[i] = canMsg.data[i];
      }
      

      Serial.println("Data received: ");
      for (int i = 0; i<4; i++){
        Serial.println(data[i]);
        Serial.println((uint8_t)data[i]);
      }
    }
  }
}