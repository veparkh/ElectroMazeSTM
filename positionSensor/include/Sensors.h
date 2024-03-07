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

void sensorInit(void);

void SensorThreadInit(void);

msg_t SensorGetData(int16_t (*data)[3], uint16_t tim_ms);

int8_t sensorCheckWhoAmI(void);

int8_t sensorConfigure(void);

void sensorCalibrate(float *calibrationData);

i2cflags_t SensorGetErrors(void);

//void anglesHandler(void *p);
#endif /* GYROSCOPE_INCLUDE_POSITIONSENSOR_H_ */
