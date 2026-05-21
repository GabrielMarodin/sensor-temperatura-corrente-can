/*
 * Current_Sensor.c
 *
 *  Created on: 20 de mai. de 2026
 *      Author: potato
 */

#include <math.h>
#include "Current_Sensor.h"

static Current_pkg pkg;
static uint32_t peak = 0;

void Mount_Current_Package(uint16_t* buffer, uint32_t lenght){
	int32_t milli_amps = 0;
	uint32_t sentido = 0;
	uint32_t acc = 0;

		for(uint32_t i = 0; i<lenght; i++){
			milli_amps = 125*(((buffer[i]*3300)>>10)-(3300>>1));
			acc += (uint32_t)(milli_amps*milli_amps);
			if (milli_amps > peak){
				peak = milli_amps;
				pkg.Peak_Dir = 1;
			} else if ((-milli_amps) > peak){
				peak = -milli_amps;
				pkg.Peak_Dir = 0;
			}
			if (milli_amps >= 0){
				sentido++;
			} else{
				sentido--;
			}
		}
		if (sentido >= 0){
			pkg.Current_Dir = 1;
		} else{
			pkg.Current_Dir = 0;
		}

		pkg.Error_msg = 0;
		pkg.Peak_Current = (peak/100) & NBIT_MASK(11);
		pkg.Current_RMS = (uint32_t)(sqrt((float)(acc/lenght))/100) & NBIT_MASK(12);
}

void Send_Current_Package(){
	// TODO
	return;
}
