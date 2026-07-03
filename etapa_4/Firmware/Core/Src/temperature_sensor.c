/*
 * Temperature_Sensor.c
 *
 *  Created on: 20 de mai. de 2026
 *      Author: potato
 */

#include "temperature_sensor.h"
#include <string.h>
#include "MCP2515.h"

static uCAN_MSG txMsg =
{
    .frame =
    {
        .idType = dSTANDARD_CAN_MSG_ID_2_0B,
        .id     = CAN_ID_SENSOR_TEMPERATURA,
        .dlc    = sizeof(Temp_pkg)
    }
};

static MAX31865_HandleTypeDef devices[] = {
		{CS1_GPIO_Port, CS1_Pin},
		{CS2_GPIO_Port, CS2_Pin},
		{CS3_GPIO_Port, CS3_Pin}
};

void Mount_Temperature_Package(tempData_t data[3], Temp_pkg *pkg){

	pkg->Batt_Temp = (uint32_t)(data[2].Temperature*10) & BIT_MASK;
	pkg->Motor_Temp = (uint32_t)(data[0].Temperature*10) & BIT_MASK;
	pkg->Charge_Temp = (uint32_t)(data[1].Temperature*10) & BIT_MASK;

	pkg->Error_msg = 0;

	if (data[0].Fault){
		pkg->Error_msg |= 0b01;
	}
	if (data[1].Fault){
		pkg->Error_msg |= 0b10;
	}
	if (data[2].Fault){
		pkg->Error_msg |= 0b100;
	}
}

void Send_Temperature_Package(Temp_pkg *pkg){

//	Temp_pkg rxPkg;
//
//	uCAN_MSG rxMsg;

	memcpy(&txMsg.frame.data0, pkg, sizeof(Temp_pkg));

	CANSPI_Transmit(&txMsg);

//	if (CANSPI_Receive(&rxMsg))
//	{
//	    memcpy(&rxPkg,
//	           &rxMsg.frame.data0,
//	           sizeof(Temp_pkg));
//	}

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
  		Mount_Temperature_Package(data, &pkg);
  		Send_Temperature_Package(&pkg);
  	  }

    }
}
