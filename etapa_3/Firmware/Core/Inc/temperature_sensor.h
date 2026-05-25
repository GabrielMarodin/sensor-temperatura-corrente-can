/*
 * Temperature_Sensor.h
 *
 *  Created on: 20 de mai. de 2026
 *      Author: potato
 */

#ifndef INC_TEMPERATURE_SENSOR_H_
#define INC_TEMPERATURE_SENSOR_H_

#include "cmsis_os.h"
#include "main.h"
#include "ISR_flags.h"
#include "MAX31865.h"
#include "MCP2515_driver.h"

#define PREF 430.0f
#define RNOMINAL 100.0f
#define TEMP_QUEUE_LENGTH 1

#define BIT_MASK ((1u<<10)-1)

extern SPI_HandleTypeDef hspi1;

extern osMessageQueueId_t temp_queue;

static MAX31865_HandleTypeDef devices[] = {
		{CS1_GPIO_Port, CS1_Pin},
		{CS2_GPIO_Port, CS2_Pin},
		{CS3_GPIO_Port, CS3_Pin}
};

typedef struct tempData {
	float Temperature; //valor da equacão de Callendar-Van Dusen
	uint8_t Fault; // código de erro do módulo
} tempData_t;

typedef struct __attribute__((packed)) {
	uint32_t Motor_Temp  : 10; // Temperatura do Motor
	uint32_t Charge_Temp : 9; // Temperatura dos Controladores de Carga
	uint32_t Batt_Temp	 : 10; // Temperatura da Bateria
	uint32_t Error_msg   : 3;  // Mensagens de Erro

} Temp_pkg;

void RTD_Init(void);

void RTDTask(void *argument);

void CANTempTask(void *argument);

#endif /* INC_TEMPERATURE_SENSOR_H_ */
