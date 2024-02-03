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
#define  X_ENGINE 1
#define  Y_ENGINE 2
#define STOP_X() stop(X_ENGINE);
#define STOP_Y() stop(X_ENGINE);

#define SET_X(isUP,dutyCycle) set(X_ENGINE, isUP, dutyCycle);
#define SET_Y(isUP,dutyCycle) set(Y_ENGINE, isUP, dutyCycle);

#define INIT_X init(X_ENGINE);
#define INIT_Y init(Y_ENGINE);


void stop(uint8_t engine);//Остановка двигателя

void set(uint8_t engine,bool isUp, uint16_t dutyCycle);//dutyCycle делится на 10000

void init(uint8_t engine);


#endif /* ENGINE_INCLUDE_ENGINE_H_ */
