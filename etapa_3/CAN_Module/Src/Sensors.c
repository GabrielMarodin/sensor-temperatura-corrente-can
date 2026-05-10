/*
 * Sensors.c
 *
 *  Created on: 6 de mai. de 2026
 *      Author: potato
 */

#include "Sensors.h"
#include "CANSPI.h"

static uint8_t Current_Buffer[4];
static uint8_t Temp_Buffer[4];

static uCAN_MSG current_tx;
static uCAN_MSG temp_tx;

extern SPI_HandleTypeDef hspi2;

void Sensor_CAN_Init(uint32_t curr_id, uint32_t temp_id){
	// Iniciliza SPI
	CANSPI_Initialize();
	// Corrente
	current_tx.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
	current_tx.frame.id = curr_id;
	current_tx.frame.dlc = 4;
	// Temperatura
	temp_tx.frame.idType = dSTANDARD_CAN_MSG_ID_2_0B;
	temp_tx.frame.id = temp_id;
	temp_tx.frame.dlc = 4;
}

void Mount_Current_pkg(Current_pkg* curr_pkg){
	uint32_t temp_buffer;
	Current_pkg package = *curr_pkg;
	// Monta pacote no buffer
	temp_buffer = (\
			package.Peak_Current + \
			package.Peak_Dir<<11 +\
			package.Current_RMS<<12 +\
			package.Current_Dir<<24 +\
			package.Error_msg<<25);
	Current_Buffer[0] = temp_buffer&0xFF;
	Current_Buffer[1] = (temp_buffer>>8)&0xFF;
	Current_Buffer[2] = (temp_buffer>>16)&0xFF;
	Current_Buffer[3] = (temp_buffer>>24)&0xFF;
}

void Mount_Temp_pkg(Temp_pkg* temp_pkg){
	uint32_t temp_buffer;
	Temp_pkg package = *temp_pkg;
	// Monta pacote no buffer
	temp_buffer = (\
				package.Motor_Temp + \
				package.Charge_Temp<<10 +\
				package.Bat_Temp<<20 +\
				package.Error_msg<<30);

	Temp_Buffer[0] = temp_buffer&0xFF;
	Temp_Buffer[1] = (temp_buffer>>8)&0xFF;
	Temp_Buffer[2] = (temp_buffer>>16)&0xFF;
	Temp_Buffer[3] = (temp_buffer>>24)&0xFF;
}

void Current_Transmit(Current_pkg* curr_pkg){
	Mount_Current_pkg(curr_pkg);
	&(current_tx.frame.data0) = Current_Buffer;
}

void Temp_Transmit(Temp_pkg* temp_pkg){
	Mount_Temp_pkg(temp_pkg);
	&(temp_tx.frame.data0) = Temp_Buffer;
}
