/*
 * Temperature_Sensor.h
 *
 *  Created on: 20 de mai. de 2026
 *      Author: potato
 */

#ifndef INC_TEMPERATURE_SENSOR_H_
#define INC_TEMPERATURE_SENSOR_H_

#include "main.h"

#define BIT_MASK ((1u<<10)-1)

typedef union Temp_pkg {
	uint32_t Temp_Bits;
	struct {
		uint32_t Motor_Temp  : 10; // Temperatura do Motor
		uint32_t Charge_Temp : 10; // Temperatura dos Controladores de Carga
		uint32_t Bat_Temp	 : 10; // Temperatura da Bateria
		uint32_t Error_msg   : 2;  // Mensagens de Erro
	};
} Temp_pkg;

void Mount_Temperature_Package(float* temperatures, uint8_t* faults);

void Send_Temperature_Package();

#endif /* INC_TEMPERATURE_SENSOR_H_ */
