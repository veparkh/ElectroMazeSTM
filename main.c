#include "ch.h"
#include "hal.h"
#include <chprintf.h>
#include "serial.h"
#include "uart.h"
#include <string.h>
#include <Sensors.h>

static uint8_t changeEndian(uint16_t bytes){
	return bytes<<8|bytes>>8;
}

/*extern mutex_t positionMutex;
extern float positionArray[2];
THD_WORKING_AREA(uartWotkingArea, 800);*/
int main(void) {

    halInit();
    chSysInit();
    debug_stream_init();

    dbgprintf("Test\n\r");
    uint16_t val = 0b1010101011111111;
    dbgprintf("%d      %d\r\n",*((uint8_t*)&val), *((uint8_t*)&val+1));
    //float localPositionArray[2] = {0};
    //chThdCreateStatic(uartWotkingArea,2048, NORMALPRIO+1, uartWorker, NULL);
    SensorInit();
    uint16_t accelerometerValues[3] = {0};
    i2cstate_t  i2cstate = 0;
    msg_t res=0;
    res = SensorConfigure();
    uint16_t sensorData[3][3] = {0};
    dbgprintf("conf:%d",res);
    while(true){
    	/*if(chMtxTryLock(&positionMutex)){
    		memcpy(localPositionArray,positionArray,8);
    		chMtxUnlock(&positionMutex);
        	dbgprintf("position %f   %f\r\n",positionArray[0], positionArray[1]);
    	}*/
    	int8_t ans = SensorGetData(sensorData, 1000);
    	dbgprintf(" accel: %d  %d %d :\n\r",sensorData[0][0],sensorData[0][1],sensorData[0][2]);
    	dbgprintf(" gyro: %d  %d %d :\n\r",sensorData[1][0],sensorData[1][1],sensorData[1][2]);
    	dbgprintf(" magn: %d  %d %d :\n\r",sensorData[2][0],sensorData[2][1],sensorData[2][2]);
    	dbgprintf("ans : %d\r\n",ans);


    	//i2cstate = SensorGetErrors();
    	//dbgprintf("res: %d x:%d y:%d z:%d error: %d \r\n", res,accelerometerValues[0],accelerometerValues[1],accelerometerValues[2],i2cstate);
    	chThdSleepMilliseconds(1000);
    }
}

