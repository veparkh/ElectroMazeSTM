/*
 * engine.c
 *
 *  Created on: 1 февр. 2024 г.
 *      Author: vparx
 */
#include "engine.h"

static PWMDriver *pwmDriver = &PWMD3;

static PWMConfig pvmConfig = {
		  .frequency = 1080000,
		  .period = 10000,
		  .callback = NULL,
		  .channels = {{PWM_OUTPUT_ACTIVE_HIGH, NULL}, {PWM_OUTPUT_ACTIVE_HIGH, NULL},{PWM_OUTPUT_ACTIVE_HIGH, NULL},{PWM_OUTPUT_ACTIVE_HIGH, NULL}},
		  .cr2 = 0,
		  .dier = 0
		};
void stopEngines(void){
	pwmStop(pwmDriver);
}//остановка двигателя

void setEnginesSpeed(int32_t signalX,int32_t signalY){

	if(signalX>0){
		pwmEnableChannel(pwmDriver, 0, PWM_PERCENTAGE_TO_WIDTH(pwmDriver,0));
		pwmEnableChannel(pwmDriver, 1, PWM_PERCENTAGE_TO_WIDTH(pwmDriver,signalX));
	}
	else{
		pwmEnableChannel(pwmDriver, 1, PWM_PERCENTAGE_TO_WIDTH(pwmDriver,0));
		pwmEnableChannel(pwmDriver, 0, PWM_PERCENTAGE_TO_WIDTH(pwmDriver,-signalX));
	}
	if(signalY>0)
	{
		pwmEnableChannel(pwmDriver, 2, PWM_PERCENTAGE_TO_WIDTH(pwmDriver,0));
		pwmEnableChannel(pwmDriver, 3, PWM_PERCENTAGE_TO_WIDTH(pwmDriver,signalY));
	}
	else{
		pwmEnableChannel(pwmDriver, 3, PWM_PERCENTAGE_TO_WIDTH(pwmDriver,0));
		pwmEnableChannel(pwmDriver, 2, PWM_PERCENTAGE_TO_WIDTH(pwmDriver,-signalY));
	}
}


void initEngines(){
		// 1 двигатель
		palSetLineMode( PAL_LINE( GPIOB, 4 ),  PAL_MODE_ALTERNATE(2));
		palSetLineMode( PAL_LINE( GPIOB, 5 ),  PAL_MODE_ALTERNATE(2));
		// 2 двигатель
		palSetLineMode( PAL_LINE( GPIOB, 0 ),  PAL_MODE_ALTERNATE(2));
		palSetLineMode( PAL_LINE( GPIOB, 1 ),  PAL_MODE_ALTERNATE(2));
		pwmStart(pwmDriver, &pvmConfig);

}

void enginesTest(void){
	initEngines();
	while(1){

		for(int32_t i = -10000;i<10000;i+=400){
			setEnginesSpeed(i,-i);
			chThdSleepMilliseconds(200);
		}
	}

}


