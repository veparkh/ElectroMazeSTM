/*
 * SensorThread.c
 *
 *  Created on: 16 февр. 2024 г.
 *      Author: vparx
 */

#include "Sensors.h"
#include "Fusion.h"
 mutex_t currentPositionMutex;
float currentPositionArray[2];
THD_WORKING_AREA(i2cWorkingArea, 800);



static THD_FUNCTION(anglesHandler, arg) {

	SensorInit();
	msg_t res = SensorConfigure();
	i2cstate_t  i2cstate = 0;
	int16_t sensorData[3][3] = {0};

	 FusionVector gyroscope = {0};
	 FusionVector accelerometer = {0};
	FusionAhrs ahrs;
	FusionEuler euler;
	FusionAhrsInitialise(&ahrs);


	systime_t prev = chVTGetSystemTime();
	uint8_t counter = 0;

	while (true) {
		counter++;
		int8_t ans = SensorGetData(sensorData, 1000);
		gyroscope.axis.x = sensorData[1][0]*0.00875;
		gyroscope.axis.y = sensorData[1][1]*0.00875;
		gyroscope.axis.z = sensorData[1][2]*0.00875;
		accelerometer.axis.x = sensorData[0][0]*0.001;
		accelerometer.axis.y = sensorData[0][1]*0.001;
		accelerometer.axis.z = sensorData[0][2]*0.001;

		FusionAhrsUpdateNoMagnetometer(&ahrs, gyroscope, accelerometer, 0.01);
		euler = FusionQuaternionToEuler(FusionAhrsGetQuaternion(&ahrs));
		if(counter==10){
			counter =0;
			dbgprintf("Roll %0.1f, Pitch %0.1f\r\n", euler.angle.roll, euler.angle.pitch);
		}
		/*dbgprintf(" accel: %d  %d %d :\n\r",sensorData[0][0],sensorData[0][1],sensorData[0][2]);
		dbgprintf(" gyro: %d  %d %d :\n\r",sensorData[1][0],sensorData[1][1],sensorData[1][2]);
		dbgprintf(" magn: %d  %d %d :\n\r",sensorData[2][0],sensorData[2][1],sensorData[2][2]);*/
		/*chMtxLock(&currentPositionMutex);
		currentPositionArray[0] = -180.4365;
		currentPositionArray[1] = 35.45;
		chMtxUnlock(&currentPositionMutex);*/
		prev = chThdSleepUntilWindowed(prev, chTimeAddX(prev, TIME_MS2I(10)));

  }
}

void SensorThreadInit(void){

    chThdCreateStatic(i2cWorkingArea, 1024, NORMALPRIO+2, anglesHandler, NULL);
}



