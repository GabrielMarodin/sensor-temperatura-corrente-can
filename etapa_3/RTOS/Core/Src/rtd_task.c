/*
 * rtd_task.c
 *
 *  Created on: 11 de mai. de 2026
 *      Author: Gabriel
 */

#include "rtd_task.h"

static MAX31865_HandleTypeDef devices[] = {
		{CS1_GPIO_Port, CS1_Pin},
		{CS2_GPIO_Port, CS2_Pin},
		{CS3_GPIO_Port, CS3_Pin}
};

void RTD_Init(void)
{
	for(uint8_t i = 0; i < 3; i++){
	  begin(&devices[i], MAX31865_3WIRE);
	}
}

void RTDTask(void *argument)
{
    uint16_t rtd;
    uint8_t fault;

    for(;;)
    {
        osThreadFlagsWait(RTD_READ_FLAG, osFlagsWaitAny, osWaitForever);

        for(uint8_t i = 0; i < 3; i++)
        {
            rtd = readRTD(&devices[i]);

            temperatures[i] = temperature(&devices[i], RNOMINAL, PREF);

            fault = readFault(&devices[i], MAX31865_FAULT_AUTO);

//            if(fault)
//            {
//                clearFault(&devices[i]);
//            }
        }
    }
}
