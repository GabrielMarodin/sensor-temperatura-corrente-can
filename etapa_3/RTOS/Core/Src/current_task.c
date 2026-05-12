/*
 * current_task.c
 *
 *  Created on: 11 de mai. de 2026
 *      Author: Gabriel
 */


#include "current_task.h"


static void IIRFilter(uint16_t *buffer,uint32_t length)
{
    for(uint32_t i = 0; i < length; i++)
    {
    	//TODO
    }
}

void CurrentTask(void *argument)
{
    uint32_t flags;

    for(;;)
    {
        flags = osThreadFlagsWait(ADC_HALF_READY | ADC_FULL_READY, osFlagsWaitAny, osWaitForever);

        if(flags & ADC_HALF_READY)
        {
        	IIRFilter(&adc_buffer[0], DMA_BUFF_LENGTH/2);
        }

        if(flags & ADC_FULL_READY)
        {
        	IIRFilter(&adc_buffer[DMA_BUFF_LENGTH/2], DMA_BUFF_LENGTH/2);
        }

        osThreadFlagsSet(canCurrentTaskHandle,CAN_CURR_READY);
    }
}
