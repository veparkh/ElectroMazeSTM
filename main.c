#include "ch.h"
#include "hal.h"
#include <chprintf.h>
#include <serial.h>
#include "uart.h"
#include <string.h>
#include "gyroscope.h"

/*extern mutex_t positionMutex;
extern float positionArray[2];
THD_WORKING_AREA(uartWotkingArea, 800);*/
int main(void) {

    halInit();
    chSysInit();
    debug_stream_init();
    dbgprintf("Test\n\r");
    //float localPositionArray[2] = {0};
    //chThdCreateStatic(uartWotkingArea,2048, NORMALPRIO+1, uartWorker, NULL);
    gyroInit();
    uint16_t accelerometerValues[3] = {0};
    i2cstate_t  i2cstate = 0;
    msg_t res=0;
    while(true){
    	/*if(chMtxTryLock(&positionMutex)){
    		memcpy(localPositionArray,positionArray,8);
    		chMtxUnlock(&positionMutex);
        	dbgprintf("position %f   %f\r\n",positionArray[0], positionArray[1]);
    	}*/
    	res = gyroGetAccelerometerData((uint8_t*)accelerometerValues, 300);
    	i2cstate = getErrors();
    	dbgprintf("res: %d x:%d y:%d z:%d error: %d \r\n", res,accelerometerValues[0],accelerometerValues[1],accelerometerValues[2],i2cstate);


    	chThdSleepMilliseconds(1000);
    }
}

