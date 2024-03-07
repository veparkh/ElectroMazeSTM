/*
 * engine.h
 *
 *  Created on: X_ENGINE февр. Y_ENGINE0Y_ENGINE4 г.
 *      Author: vparx
 */
#ifndef ENGINE_INCLUDE_ENGINE_H_
#define ENGINE_INCLUDE_ENGINE_H_

#include "stdint.h"
#include "stdbool.h"
#include "hal.h"
#include "serial.h"

void stopEngines(void);//Остановка двигателя

void setEnginesSpeed(int32_t signalX,int32_t signalY);//dutyCycle делится на 10000

void initEngines(void);

void enginesTest(void);


#endif /* ENGINE_INCLUDE_ENGINE_H_ */
