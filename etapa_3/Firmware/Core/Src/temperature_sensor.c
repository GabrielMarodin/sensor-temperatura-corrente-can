/*
 * Temperature_Sensor.c
 *
 *  Created on: 20 de mai. de 2026
 *      Author: potato
 */

#include "temperature_sensor.h"
#include "main.h"

Temp_pkg Mount_Temperature_Package(tempData_t data[3]){
	Temp_pkg pkg;

	pkg.Batt_Temp = (uint32_t)(data[2].Temperature*10) & BIT_MASK;
	pkg.Motor_Temp = (uint32_t)(data[0].Temperature*10) & BIT_MASK;
	pkg.Charge_Temp = (uint32_t)(data[1].Temperature*10) & BIT_MASK;

	pkg.Error_msg = 0;

	if (data[0].Fault){
		pkg.Error_msg |= 0b01;
	}
	if (data[1].Fault){
		pkg.Error_msg |= 0b10;
	}
	if (data[2].Fault){
		pkg.Error_msg |= 0b100;
	}

	return pkg;
}

void Send_Temperature_Package(Temp_pkg pkg, MCP2515_t *dev){
	uint8_t data_L[4];

	data_L[0] = (uint8_t)(pkg.Motor_Temp & 0xFF);
    data_L[1] = (uint8_t)((pkg.Motor_Temp >> 8) & 0x03);
    data_L[1] |= (uint8_t)((pkg.Charge_Temp << 2) & 0xFC);
    data_L[2] = (uint8_t)((pkg.Charge_Temp >> 6) & 0x07); 
	data_L[2] |= (uint8_t)((pkg.Batt_Temp << 3) & 0xF8);
    data_L[3] = (uint8_t)((pkg.Batt_Temp >> 5) & 0x1F);
	data_L[3] |= (uint8_t)((pkg.Error_msg << 5) & 0xE0);
 
	MCP2515_TX(dev, 0x10, 4, data_L, 0);
}

void RTD_Init(void)
{
	for(uint8_t i = 0; i < 3; i++){
	  begin(&devices[i], MAX31865_3WIRE);
	}
}

void RTDTask(void *argument)
{

	tempData_t data[3];

    for(;;)
    {
        osThreadFlagsWait(RTD_READ_FLAG, osFlagsWaitAny, osWaitForever);

        for(uint8_t i = 0; i < 3; i++)
        {

            data[i].Temperature = temperature(&devices[i], RNOMINAL, PREF);

            data[i].Fault = readFault(&devices[i], MAX31865_FAULT_AUTO);

            if(data[i].Fault)
            {
                clearFault(&devices[i]);
            }

        }
        osMessageQueuePut(temp_queue, data, 0, 0);
   }
}

void CANTempTask(void *argument)
{
	tempData_t data[3];
	Temp_pkg pkg;

    for(;;)
    {

  	  if (osMessageQueueGet(temp_queue, data, 0, osWaitForever) == osOK)
  	  {
  		pkg = Mount_Temperature_Package(data);
  		Send_Temperature_Package(pkg);
  	  }

    }
}
