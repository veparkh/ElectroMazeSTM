/*
 * gyroscope.c
 *
 *  Created on: 12 февр. 2024 г.
 *      Author: vparx
 */


#include "gyroscope.h"

static I2CDriver *i2c1 = &I2CD1;

static const I2CConfig i2c1_conf = {
 .timingr = STM32_TIMINGR_PRESC(14U)  |
 STM32_TIMINGR_SCLDEL(3U)  | STM32_TIMINGR_SDADEL(2U) |
 STM32_TIMINGR_SCLH(14U)   | STM32_TIMINGR_SCLL(17U),
 .cr1 = 0,
 .cr2 = 0
};

//TODO() откалибровать компас
const float compassCalibrationBias[3] = { 567.893, -825.35, 1061.436 };

const float compassCalibrationMatrix[3][3] = { { 1.909, 0.082, 0.004 },
                                               { 0.049, 1.942, -0.235 },
                                               { -0.003, 0.008, 1.944 } };


void gyroInit(void){
	i2cStart(i2c1, &i2c1_conf);
    palSetLineMode(PAL_LINE(GPIOB, 8), PAL_MODE_ALTERNATE(4)|PAL_STM32_OTYPE_OPENDRAIN );
    palSetLineMode(PAL_LINE(GPIOB, 9), PAL_MODE_ALTERNATE(4)|PAL_STM32_OTYPE_OPENDRAIN );
}
msg_t gyroGetAccelerometerData(uint8_t *bytes, uint16_t tim_ms){
	/*//uint8_t sub[] = {0b10101000};
	uint8_t who_am_i[]={0b0001111};
	//return i2cMasterTransmitTimeout(i2c1,0b0011000,sub,1 ,bytes,6,chTimeMS2I(tim_ms));
	msg_t msg =  i2cMasterTransmitTimeout(i2c1,0b1101000,who_am_i,1 ,bytes,1,chTimeMS2I(tim_ms));
	dbgprintf("answer :%u\r\n", bytes[0]);
	return msg;*/
    uint8_t txbuf[1] = {0x0F};
    uint8_t rxbuf[1] = {0};
    uint16_t i = 0;
    while (true) {
        chThdSleepMilliseconds(1000);
        msg_t msg = i2cMasterTransmitTimeout(i2c1, 0b0011000, txbuf, 1, rxbuf, 1, 1000);
        dbgprintf(" msg %d  val%d\n\r",msg, rxbuf[0]);
        palToggleLine(LINE_LED2);
        i++;
    }
}

i2cflags_t getErrors(void){
	return i2cGetErrors(i2c1);
}



