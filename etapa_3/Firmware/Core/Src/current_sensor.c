/*
 * Current_Sensor.c
 *
 *  Created on: 20 de mai. de 2026
 *      Author: potato
 */

#include "current_sensor.h"
#include <math.h>

static uint32_t peak = 0;
/**
 * @brief: Extrai valores do ADC e monta pacote
 *
 * Realiza todos os calculos menos o filtro
 *
 * @param: buffer Buffer do ADC
 * @param: lenght Tamanho do buffer
 */
void Mount_Current_Package(uint32_t *buffer, Current_pkg *pkg, uint32_t length){
	int32_t milli_amps = 0;
	int32_t sentido = 0;
	uint64_t acc = 0;

	for(uint32_t i = 0; i<length; i++){

		milli_amps = 125*(((buffer[i]*3300)>>10)-(3300>>1));

		acc += (uint64_t)(milli_amps*milli_amps);

		if (milli_amps > peak){

			peak = milli_amps;
			pkg->Peak_Dir = 1;

		} else if ((-milli_amps) > peak){

			peak = -milli_amps;
			pkg->Peak_Dir = 0;

		}
		if (milli_amps >= 0){
			sentido++;
		} else{
			sentido--;
		}
	}

	if (sentido >= 0){
		pkg->Current_Dir = 1;
	} else{
		pkg->Current_Dir = 0;
	}

	pkg->Error_msg = 0;
	pkg->Peak_Current = (peak/100) & NBIT_MASK(11);
	pkg->Current_RMS = (uint32_t)(sqrt((float)(acc/length))/100) & NBIT_MASK(12);
}

/**
 * @brief: Envia pacote por SPI
 */
void Send_Current_Package(Current_pkg pkg, MCP2515_t *dev){
    MCP2515_TX(dev, 0x11, sizeof(Current_pkg), (uint8_t *)&pkg, 1);
}

static void IIRFilter(uint16_t *raw, uint32_t *filtered, uint32_t length)
{
    for(uint32_t i = 0; i < length; i++)
    {
    	//TODO: implementar filtro
    	filtered[i] = raw[i];
    }

}


void CurrentTask(void *argument)
{
    uint32_t flags;
    uint32_t filter_data[DMA_BUFF_LENGTH];

    for(;;)
    {
        flags = osThreadFlagsWait(ADC_HALF_READY | ADC_FULL_READY, osFlagsWaitAny, osWaitForever);

        if(flags & ADC_HALF_READY)
        {
        	IIRFilter(&adc_buffer[0], &filter_data[0], DMA_BUFF_LENGTH/2);
        }

        if(flags & ADC_FULL_READY)
        {
        	IIRFilter(&adc_buffer[DMA_BUFF_LENGTH/2], &filter_data[DMA_BUFF_LENGTH/2], DMA_BUFF_LENGTH/2);

            osMessageQueuePut(current_queue, filter_data, 0, 0);

        }

    }
}

void CANCurrentTask(void *argument)
{
	Current_pkg pkg;
	uint32_t filter_data[DMA_BUFF_LENGTH];

    for(;;)
    {

		if (osMessageQueueGet(current_queue, filter_data, 0, osWaitForever) == osOK)
		{
			Mount_Current_Package(filter_data, &pkg, DMA_BUFF_LENGTH);
			Send_Current_Package(pkg, &hcan);
		}

      }
}
