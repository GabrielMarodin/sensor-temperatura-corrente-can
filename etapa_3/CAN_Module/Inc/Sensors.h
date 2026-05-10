/*
 * Sensors.h
 *
 *  Created on: 5 de mai. de 2026
 *      Author: Emanuel Staub Araldi
 */

#ifndef INC_SENSORS_H_
#define INC_SENSORS_H_

#include "main.h"

extern uint8_t Current_Buffer[4]; // Buffer do pacote de corrente
extern uint8_t Temp_Buffer[4];    // Buffer do pacote de temperatura

typedef union Current_pkg {
	uint32_t Current_Bits;
	struct {
		uint32_t Peak_Current : 11; // Corrente de Pico
		uint32_t Peak_Dir     : 1;  // Sentido da Corrente de Pico
		uint32_t Current_RMS  : 12; // Corrente RMS
		uint32_t Current_Dir  : 1;  // Direção Principal da Corrente
		uint32_t Error_msg    : 7;  // Mensagens de Erro
	};
} Current_pkg;

typedef union Temp_pkg {
	uint32_t Temp_Bits;
	struct {
		uint32_t Motor_Temp  : 10; // Temperatura do Motor
		uint32_t Charge_Temp : 10; // Temperatura dos Controladores de Carga
		uint32_t Bat_Temp	 : 10; // Temperatura da Bateria
		uint32_t Error_msg   : 2;  // Mensagens de Erro
	};
} Temp_pkg;

/**
 * @brief Inicializa rede CAN
 *
 * @val curr_id ID do pacote de corrente
 * @val temp_id ID do pacote de temperatura
 */
void Sensor_CAN_Init(uint32_t curr_id, uint32_t temp_id);

/**
 * @brief Gera pacote do sensor de corrente para enviar pela rede CAN - armazena no buffer
 */
void Mount_Current_pkg(Current_pkg* curr_pkg);

/**
 * @brief Gera pacote dos sensores de temperatura para enviar pela rede CAN - armazena no buffer
 */
void Mount_Temp_pkg(Temp_pkg* temp_pkg);


/**
 * @brief Envia dados da corrente
 */
void Current_Transmit(Current_pkg* curr_pkg);

/**
 * @brief Envia dados da temperatura
 */
void Temp_Transmit(Temp_pkg temp_pkg);

#endif /* INC_SENSORS_H_ */
