/*
 * gyroscope.h
 *
 *  Created on: 12 февр. 2024 г.
 *      Author: vparx
 */

#ifndef POSITIONSENSOR_INCLUDE_SENSORS_
#define POSITIONSENSOR_INCLUDE_SENSORS_

#include "ch.h"
#include "hal.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "serial.h"


void SensorInit(void);

msg_t SensorGetData(uint16_t (*data)[3], uint16_t tim_ms);

int8_t SensorCheckWhoAmI(void);

int8_t SensorConfigure(void);

i2cflags_t SensorGetErrors(void);
#endif /* GYROSCOPE_INCLUDE_POSITIONSENSOR_H_ */
