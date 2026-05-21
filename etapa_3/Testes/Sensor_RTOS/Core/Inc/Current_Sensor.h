/*
 * Current_Sensor.h
 *
 *  Created on: 20 de mai. de 2026
 *      Author: potato
 */

#ifndef INC_CURRENT_SENSOR_H_
#define INC_CURRENT_SENSOR_H_

#define NBIT_MASK(N) ((1u<<N)-1)

#include "main.h"

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

/**
 * @brief: Extrai valores do ADC e monta pacote
 *
 * Realiza todos os calculos menos o filtro
 *
 * @param: buffer Buffer do ADC
 * @param: lenght Tamanho do buffer
 */
void Mount_Current_Package(uint16_t* buffer, uint32_t lenght);

/**
 * @brief: Envia pacote por SPI
 */
void Send_Current_Package();

#endif /* INC_CURRENT_SENSOR_H_ */
