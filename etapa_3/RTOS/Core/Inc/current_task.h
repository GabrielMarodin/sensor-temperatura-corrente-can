/*
 * current_task.h
 *
 *  Created on: 11 de mai. de 2026
 *      Author: Gabriel
 */

#ifndef INC_CURRENT_TASK_H_
#define INC_CURRENT_TASK_H_

#include "global_data.h"
#include "ISR_Flags.h"
#include "main.h"

#define DMA_BUFF_LENGTH 128

extern uint16_t adc_buffer[DMA_BUFF_LENGTH];

void CurrentTask(void *argument);

#endif /* INC_CURRENT_TASK_H_ */
