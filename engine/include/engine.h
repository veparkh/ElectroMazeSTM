/*
 * engine.h
 *
 *  Created on: X_ENGINE ����. Y_ENGINE0Y_ENGINE4 �.
 *      Author: vparx
 */
#ifndef ENGINE_INCLUDE_ENGINE_H_
#define ENGINE_INCLUDE_ENGINE_H_

#include "stdint.h"
#include "stdbool.h"
#include "hal.h"
#include "serial.h"

void stopEngines(void);//��������� ���������

void setEnginesSpeed(int32_t signalX,int32_t signalY);//dutyCycle ������� �� 10000

void initEngines(void);

void enginesTest(void);


#endif /* ENGINE_INCLUDE_ENGINE_H_ */
