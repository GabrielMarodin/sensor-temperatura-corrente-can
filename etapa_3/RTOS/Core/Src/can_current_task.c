/*
 * can_current_task.c
 *
 *  Created on: 12 de mai. de 2026
 *      Author: Gabriel
 */
#include "can_current_task.h"

void CANCurrentTask(void *argument)
{
    for(;;)
    {
        osThreadFlagsWait(CAN_CURR_READY,osFlagsWaitAny,osWaitForever);
        //TODO Adicionar as funções CAN
    }
}

