/*
 * ISR_Flags.h
 *
 *  Created on: 11 de mai. de 2026
 *      Author: Gabriel
 */

#ifndef INC_TASK_FLAGS_H_
#define INC_TASK_FLAGS_H_

#define ADC_HALF_READY   (1U << 0)
#define ADC_FULL_READY   (1U << 1)

#define RTD_READ_FLAG    (1U << 2)
#define CAN_TEMP_READY   (1U << 3)
#define CAN_CURR_READY   (1U << 4)

#endif /* INC_TASK_FLAGS_H_ */
