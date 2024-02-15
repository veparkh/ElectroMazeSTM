/*
 * gyroscope.c
 *
 *  Created on: 12 февр. 2024 г.
 *      Author: vparx
 */


#include <Sensors.h>

static I2CDriver *i2c1 = &I2CD1;

typedef struct Sensor{
	uint8_t whoAmIAddress;
	uint8_t whoAmIAnswer;
	uint8_t address;
	uint8_t dataStartAddress;
	uint8_t dataBytesCount;
}  Sensor;

Sensor accelerometer = {0x0F,0b110010,0x18,0x28|0x80,6};
Sensor gyroscope = {0x0F,0b11010011,0x68,0x28|0x80,6};
Sensor magnetometer = {0x0F,0b00111101,0x1C,0x28|0x80,6};

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


void SensorInit(void){
	i2cStart(i2c1, &i2c1_conf);
    palSetLineMode(PAL_LINE(GPIOB, 8), PAL_MODE_ALTERNATE(4)|PAL_STM32_OTYPE_OPENDRAIN );
    palSetLineMode(PAL_LINE(GPIOB, 9), PAL_MODE_ALTERNATE(4)|PAL_STM32_OTYPE_OPENDRAIN );
}
msg_t SensorGetData(uint16_t (*data)[3], uint16_t tim_ms){
	msg_t msg = 0;
	uint8_t tx[1]={accelerometer.dataStartAddress};


	msg = i2cMasterTransmitTimeout(i2c1, accelerometer.address, tx, 1, (uint8_t*)data, accelerometer.dataBytesCount, chTimeMS2I(tim_ms));
	if(msg!=MSG_OK)
		return -1;

	uint8_t d[6];
	tx[0] = gyroscope.dataStartAddress;
	msg = i2cMasterTransmitTimeout(i2c1, gyroscope.address, tx, 1, /*(uint8_t*)&data[1][0]*/d, gyroscope.dataBytesCount, chTimeMS2I(tim_ms));
	memcpy((uint8_t*)&data[1][0],d,6);
	dbgprintf("%d\t%d\t%d\t%d\t%d\t%d\r\n", *(d + 0), *(d + 1), *(d + 2), *(d + 3), *(d + 4), *(d + 5));
	//dbgprintf("%d\t%d\t%d\t%d\t%d\t%d\r\n", *((uint8_t*)&data[1][0] + 0), *((uint8_t*)&data[0][0] + 1), *((uint8_t*)&data[1][0] + 2), *((uint8_t*)&data[1][0] + 3), *((uint8_t*)&data[1][0] + 4), *((uint8_t*)data[1][0] + 5));
	if(msg!=MSG_OK)
		return -2;
	tx[0] = magnetometer.dataStartAddress;
	msg = i2cMasterTransmitTimeout(i2c1, magnetometer.address, tx, 1, (uint8_t*)&data[2][0], magnetometer.dataBytesCount, chTimeMS2I(tim_ms));
	if(msg!=MSG_OK)
		return -3;
	return 0;

}

int8_t SensorCheckWhoAmI(void){
	uint8_t rx[1]={0};
	uint8_t tx[] = {accelerometer.whoAmIAddress};
	int8_t err = i2cMasterTransmitTimeout(i2c1,accelerometer.address,tx,1,rx,1,1000);
	if(err!=MSG_OK||rx[0]!=accelerometer.whoAmIAnswer)
		return -1;
	err = i2cMasterTransmitTimeout(i2c1,gyroscope.address,tx,1,rx,1,1000);
	if(err!=MSG_OK||rx[0]!=gyroscope.whoAmIAnswer)
		return -2;
	err = i2cMasterTransmitTimeout(i2c1,magnetometer.address,tx,1,rx,1,1000);
	if(err!=MSG_OK||rx[0]!=magnetometer.whoAmIAnswer)
		return -3;
	return 0;


}
int8_t SensorConfigure(void){

	msg_t res;
	//Акселерометр
	uint8_t acceltx[] = {0x20,0b00110111};//нормальный режим питания, 400 Герц CR1
	res = i2cMasterTransmitTimeout(i2c1,accelerometer.address,acceltx,2,NULL,0,1000);
	if (res!=0)
		return -1;
	//Гироскоп
	uint8_t gyrotx[] = {0x20,0b10011111};//нормальный режим питания, 400 Герц CR1
	res = i2cMasterTransmitTimeout(i2c1,gyroscope.address,gyrotx,2,NULL, 0, 1000);
	if (res!=0)
		return -1;
	//Магнитометр
	uint8_t magntx[] = {0x20,0b00100010};//Включения X и Y, 500 Герц CR1
	uint8_t magntx2[] = {0x22,0b00000000};// Включение работы CR3
	uint8_t magntx3[] = {0x23,0b00000100};// Включение Z CR4
	res = i2cMasterTransmitTimeout(i2c1, magnetometer.address, magntx, 2, NULL, 0, 1000);
	if (res!=0)
		return -1;
	res = i2cMasterTransmitTimeout(i2c1,magnetometer.address,magntx2,2,NULL,0,1000);
	if (res!=0)
		return -1;
	res = i2cMasterTransmitTimeout(i2c1,magnetometer.address,magntx3,2,NULL,0,1000);
	if (res!=0)
		return -1;
	return 0;
}


i2cflags_t SensorGetErrors(void){
	return i2cGetErrors(i2c1);
}



