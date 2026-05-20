/*
 * can_temp_task.c
 *
 *  Created on: 12 de mai. de 2026
 *      Author: Gabriel
 */
#include "Temperature_Sensor.h"
#include "can_temp_task.h"

void CANTempTask(void *argument)
{
    for(;;)
    {
        osThreadFlagsWait(CAN_TEMP_READY,osFlagsWaitAny,osWaitForever);
        //TODO Adicionar as funções CAN
        Send_Temperature_Package();
    }
}

