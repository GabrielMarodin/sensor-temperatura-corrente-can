/*
 * Temperature_Sensor.c
 *
 *  Created on: 20 de mai. de 2026
 *      Author: potato
 */

#include "Temperature_Sensor.h"
#include "main.h"

static Temp_pkg pkg;

void Mount_Temperature_Package(float* temperatures, uint8_t* faults){
	pkg.Bat_Temp = (uint32_t)(temperatures[2]*10) & BIT_MASK;
	pkg.Motor_Temp = (uint32_t)(temperatures[0]*10) & BIT_MASK;
	pkg.Charge_Temp = (uint32_t)(temperatures[1]*10) & BIT_MASK;

	pkg.Error_msg = 0;

	if (faults[0] != 0){
		pkg.Error_msg = 0b01;
	} else if (faults[1] != 0){
		pkg.Error_msg = 0b10;
	} else if (faults[2] != 0){
		pkg.Error_msg = 0b11;
	}

	return;
}

void Send_Temperature_Package(){
	//TODO
	return;
}
