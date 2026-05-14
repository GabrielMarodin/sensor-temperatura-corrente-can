#include <SPI.h>
#include <mcp2515.h>
#include <HardwareSerial.h>
 
struct can_frame canMsg;
struct MCP2515 mcp2515(5); // CS pin is GPIO 5
 
#define CAN_ACK_ID 0x037  // CAN ID for acknowledgment
#define CAN_ID 0x036

void setup()
{
  Serial.begin(115200);

  SPI.begin();
 
  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();
}
 
 
void loop()
{
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK)
  {
    if (canMsg.can_id == CAN_ID)  // Check if the message is from the sender
    {
      int data = (canMsg.data[0] << 8) | canMsg.data[1]; // MSB + LSB

      Serial.print("Data received: ");
      Serial.print(data);

      // Send acknowledgment
      canMsg.can_id  = CAN_ACK_ID;  // Use ACK ID
      canMsg.can_dlc = 0;           // No data needed for ACK
      mcp2515.sendMessage(&canMsg);
      Serial.println("ACK sent");
    }
  }
}