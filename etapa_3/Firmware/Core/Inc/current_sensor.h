/*
 * Current_Sensor.h
 *
 *  Created on: 20 de mai. de 2026
 *      Author: potato
 */

#ifndef INC_CURRENT_SENSOR_H_
#define INC_CURRENT_SENSOR_H_

#define NBIT_MASK(N) ((1u<<N)-1)

#include "cmsis_os.h"

#include "main.h"
#include "ISR_flags.h"
#include "MCP2515_driver.h"

#define CURRENT_QUEUE_LENGTH 1
#define DMA_BUFF_LENGTH 128

extern uint16_t adc_buffer[DMA_BUFF_LENGTH];

extern osMessageQueueId_t current_queue;

typedef struct __attribute__((packed)) {
	uint32_t Peak_Current : 11; // Corrente de Pico
	uint32_t Peak_Dir     : 1;  // Sentido da Corrente de Pico
	uint32_t Current_RMS  : 12; // Corrente RMS
	uint32_t Current_Dir  : 1;  // Direção Principal da Corrente
	uint32_t Error_msg    : 7;  // Mensagens de Erro

} Current_pkg;

void CurrentTask(void *argument);

void CANCurrentTask(void *argument);

#endif /* INC_CURRENT_SENSOR_H_ */
