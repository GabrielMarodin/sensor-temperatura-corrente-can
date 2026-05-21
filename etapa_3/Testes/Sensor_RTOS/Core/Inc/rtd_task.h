/*
 * rtd_task.h
 *
 *  Created on: 11 de mai. de 2026
 *      Author: Gabriel
 */

#ifndef INC_RTD_TASK_H_
#define INC_RTD_TASK_H_

#include "task_flags.h"
#include "global_data.h"
#include "MAX31865.h"
#include "main.h"
#include "task_handles.h"

#define PREF 430.0f
#define RNOMINAL 100.0f

extern SPI_HandleTypeDef hspi1;

void RTD_Init(void);

void RTDTask(void *argument);

#endif /* INC_RTD_TASK_H_ */
