#include <SPI.h>
#include <mcp2515.h>
 
struct can_frame canMsg;
struct MCP2515 mcp2515(5); // CS pin is GPIO 5
 
#define CAN_ACK_ID 0x037  // CAN ID for acknowledgment
#define CAN_ID 0x036
void setup()
{
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
      unsigned char* data = canMsg.data; // Combine MSB and LSB
 
      // Send acknowledgment
      canMsg.can_id  = CAN_ACK_ID;  // Use ACK ID
      canMsg.can_dlc = 0;           // No data needed for ACK
      mcp2515.sendMessage(&canMsg);
    }
  }
}