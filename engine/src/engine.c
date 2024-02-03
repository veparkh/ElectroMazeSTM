/*
 * engine.c
 *
 *  Created on: 1 февр. 2024 г.
 *      Author: vparx
 */
#include "engine.h"

void pwmcb_fun(PWMDriver *pwmp)
{
    (void)pwmp; // Это не обязательно, просто чтобы не было ворнингов о неиспользуемой переменной
    dbgprintf("callback");
}
static void pwmc1cb(PWMDriver *pwmp) {
  (void)pwmp;
  dbgprintf("callback");
}
static PWMDriver *pwmDriver = &PWMD3;

static PWMConfig pvmConfig = {
		  .frequency = 1080000,
		  .period = 10000,
		  .callback = pwmcb_fun,
		  .channels = {{PWM_OUTPUT_ACTIVE_HIGH, pwmc1cb}, {PWM_OUTPUT_ACTIVE_HIGH, NULL}},
		  .cr2 = 0,
		  .dier = 0
		};
void stop(uint8_t engine){
	switch (engine){
	case X_ENGINE:
		pwmStop(pwmDriver);
		break;
	case Y_ENGINE:
		break;
	default:
		break;
	}
}//остановка двигателя

void set(uint8_t engine,bool isUp, uint16_t dutyCycle){
	switch (engine){
	case X_ENGINE:
		if (isUp){
			pwmEnableChannel(pwmDriver, 0, PWM_PERCENTAGE_TO_WIDTH(pwmDriver,0));
			pwmEnableChannel(pwmDriver, 1, PWM_PERCENTAGE_TO_WIDTH(pwmDriver,dutyCycle));
		}
		else{
			pwmEnableChannel(pwmDriver, 1, PWM_PERCENTAGE_TO_WIDTH(pwmDriver,0));
			pwmEnableChannel(pwmDriver, 0, PWM_PERCENTAGE_TO_WIDTH(pwmDriver,dutyCycle));
		}


		break;
	case Y_ENGINE:
		break;
	default:
		break;
	}
}


void init (uint8_t engine){

	switch (engine){
	case X_ENGINE:
		pwmEnablePeriodicNotification(pwmDriver);
		pwmEnableChannelNotification(pwmDriver, 0);
		palSetLineMode( PAL_LINE( GPIOB, 4 ),  PAL_MODE_ALTERNATE(2));
		palSetLineMode( PAL_LINE( GPIOB, 5 ),  PAL_MODE_ALTERNATE(2));
		pwmStart(pwmDriver, &pvmConfig);
		break;
	case Y_ENGINE:
		break;
	default:
		break;
	}
}// инициализация двигателя




