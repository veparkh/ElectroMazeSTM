/*
 * SensorThread.c
 *
 *  Created on: 16 февр. 2024 г.
 *      Author: vparx
 */

#include "Sensors.h"
#include "Fusion.h"

MUTEX_DECL(currentPositionMutex);
float currentPositionArray[2];


THD_WORKING_AREA(i2cWorkingArea, 1024);


static THD_FUNCTION(anglesHandler, arg) {

	chRegSetThreadName("I2C");
	sensorInit();
	float gyroCalibrationData[3];
	sensorConfigure();
	sensorCalibrate(gyroCalibrationData);
	chThdSetPriority(NORMALPRIO);
	dbgprintf("calibrationData: X :%.3f Y :%.3f Z :%.3f\r\n",gyroCalibrationData[0],gyroCalibrationData[1],gyroCalibrationData[2]);
	int16_t sensorData[3][3] = {0};

	 FusionVector gyroscope = {0};
	 FusionVector accelerometer = {0};
	FusionAhrs ahrs;
	FusionEuler euler;
	FusionAhrsInitialise(&ahrs);


	systime_t prev = chVTGetSystemTime();
	uint8_t counter = 0;
	systime_t timeBeforeCalulation = 0;
	systime_t timeAfterCalculation = 0;
	while (true) {
		timeBeforeCalulation = chVTGetSystemTime();
		counter++;

		int8_t ans = SensorGetData(sensorData, 1000);
		gyroscope.axis.x = (sensorData[1][0]-gyroCalibrationData[0])*0.00875;
		gyroscope.axis.y = (sensorData[1][1]-gyroCalibrationData[1])*0.00875;
		gyroscope.axis.z = (sensorData[1][2]-gyroCalibrationData[2])*0.00875;
		accelerometer.axis.x = sensorData[0][0]*0.001;
		accelerometer.axis.y = sensorData[0][1]*0.001;
		accelerometer.axis.z = sensorData[0][2]*0.001;

		FusionAhrsUpdateNoMagnetometer(&ahrs, gyroscope, accelerometer, 0.03);
		euler = FusionQuaternionToEuler(FusionAhrsGetQuaternion(&ahrs));
		if(euler.angle.roll>0){
			euler.angle.roll -= 180;
		}
		else{
			euler.angle.roll += 180;
		}

		/*dbgprintf("accel: %d  %d %d :\r\n",sensorData[0][0],sensorData[0][1],sensorData[0][2]);
		dbgprintf("gyro: %d  %d %d :\r\n",sensorData[1][0],sensorData[1][1],sensorData[1][2]);
		dbgprintf("data angles: roll: %.3f pitch: %.3f  :\r\n",euler.angle.roll,euler.angle.pitch);*/
		chMtxLock(&currentPositionMutex);
		currentPositionArray[0] = euler.angle.roll;
		currentPositionArray[1] = euler.angle.pitch;
		chMtxUnlock(&currentPositionMutex);
		timeAfterCalculation = chVTGetSystemTime();
		dbgprintf(" calcul time : %d\r\n",TIME_I2MS(timeAfterCalculation-timeBeforeCalulation));
		prev = chThdSleepUntilWindowed(prev, chTimeAddX(prev, TIME_MS2I(30)));

  }
}

void SensorThreadInit(void){

    chThdCreateStatic(i2cWorkingArea, sizeof(i2cWorkingArea), NORMALPRIO+2, anglesHandler, NULL);
}



