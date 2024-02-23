#include "ch.h"
#include "hal.h"
#include <chprintf.h>
#include "serial.h"
#include "uart.h"
#include <string.h>
#include <Sensors.h>


extern mutex_t targetPositionMutex;
extern float targetPositionArray[2];


extern mutex_t currentPositionMutex;
extern float currentPositionArray[2];

int main(void) {

    halInit();
    chSysInit();
    debug_stream_init();

    SensorThreadInit();
    uartInit();

    while(true){
    	chThdSleepMilliseconds(1000);
    }
    float localPositionArray[2] = {0};
    while(true){
    	if(chMtxTryLock(&targetPositionMutex)){
    		memcpy(localPositionArray,targetPositionArray,8);
    		chMtxUnlock(&targetPositionMutex);
        	dbgprintf("position %f   %f\r\n",targetPositionArray[0], targetPositionArray[1]);
    	}
    	chThdSleepMilliseconds(1000);
    }
}

