/*
 * maze.c
 *
 *  Created on: 29 февр. 2024 г.
 *      Author: vparx
 */
#include "ch.h"
#include "hal.h"
#include <chprintf.h>
#include "engine.h"
#include "serial.h"
#include "uart.h"
#include <string.h>
#include "Sensors.h"
#include "maze.h"
extern mutex_t targetPositionMutex;
extern float targetPositionArray[2];

extern mutex_t currentPositionMutex;
extern float currentPositionArray[2];

#define KP 80
#define KI 3
#define TIME_MS 15
#define WIEGHT_COEFF 60

void mazeRoutine(void){

	float errX = 0;
	float errY  = 0;
	int32_t signalX = 0;
	int32_t signalY = 0;
	dbgprintf("Test\n\r");

	//initEngines();
	SensorThreadInit();
	//uartThreadInit();

	float localTargetPositionArray[2] = {0};
	float localCurrentPositionArray[2] = {0};
	float errSumX = 0;
	float errSumY = 0;
	systime_t prev = chVTGetSystemTime();
	int i = 0;
	chThdSleepSeconds(20);
	while(true){
		i++;
		chMtxLock(&targetPositionMutex);
		memcpy(localTargetPositionArray,targetPositionArray,8);
		chMtxUnlock(&targetPositionMutex);
		chMtxLock(&currentPositionMutex);
		memcpy(localCurrentPositionArray,currentPositionArray,8);
		chMtxUnlock(&currentPositionMutex);
		errX =  localTargetPositionArray[0] - localCurrentPositionArray[0];
		errY =  localTargetPositionArray[1] - localCurrentPositionArray[1];
		if(i ==80){
			dbgprintf("errX:%.3f   errY:%.3f\r\n",errX,errY);
			dbgprintf("sumErrX:%.3f   smmErrY:%.3f\r\n",errSumX,errSumY);
			dbgprintf("current roll:%.3f   pitch:%.3f\r\n",localCurrentPositionArray[0],localCurrentPositionArray[1]);
			dbgprintf("target roll:%.3f   pitch:%.3f\r\n",localTargetPositionArray[0],localTargetPositionArray[1]);
			dbgprintf("SignalX:%d   SignalY:%d\r\n",signalX,signalY);
			i = 0;
		}
		errSumX +=errX;
		errSumY +=errY;
		signalX = KP*errX+KI*errSumX*TIME_MS/1000;
		signalY = KP*errY+KI*errSumY*TIME_MS/1000;
		signalX *=-WIEGHT_COEFF;
		signalY *=-WIEGHT_COEFF;
		if (errSumX>500||errSumX<-500)
			errSumX = 0;
		if (errSumY>500||errSumY<-500)
			errSumY = 0;
		if(signalX>10000)
			signalX = 10000;
		else if(signalX<-10000)
			signalX = -10000;
		if(signalY>10000)
			signalY = 10000;
		else if(signalY<-10000)
			signalY = -10000;
		if(signalX<2000 && signalX>-2000)
			signalX=0;
		if(signalY<2000 && signalY>-2000)
			signalY=0;
		setEnginesSpeed(signalY,signalX);
		prev = chThdSleepUntilWindowed(prev, chTimeAddX(prev, TIME_MS2I(TIME_MS)));
		//bgprintf("maze alibe\r\n");
	}
}
