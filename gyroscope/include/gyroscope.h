/*
 * gyroscope.h
 *
 *  Created on: 12 февр. 2024 г.
 *      Author: vparx
 */

#ifndef GYROSCOPE_INCLUDE_GYROSCOPE_H_
#define GYROSCOPE_INCLUDE_GYROSCOPE_H_

#include "ch.h"
#include "hal.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "serial.h"


void gyroInit(void);

msg_t gyroGetAccelerometerData(uint8_t *bytes, uint16_t tim_ms);


i2cflags_t getErrors(void);
#endif /* GYROSCOPE_INCLUDE_GYROSCOPE_H_ */
