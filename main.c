#include "ch.h"
#include "hal.h"
#include <chprintf.h>
#include <serial.h>
#include "uart.h"
#include <string.h>

extern mutex_t positionMutex;
extern float positionArray[2];
THD_WORKING_AREA(uartWotkingArea, 800);
int main(void) {

    halInit();
    chSysInit();
    debug_stream_init();
    dbgprintf("Test\n\r");
    float localPositionArray[2] = {0};
    chThdCreateStatic(uartWotkingArea,2048, NORMALPRIO+1, uartWorker, NULL);
    while(true){
    	if(chMtxTryLock(&positionMutex)){
    		memcpy(localPositionArray,positionArray,8);
    		chMtxUnlock(&positionMutex);
        	dbgprintf("position %f   %f\r\n",positionArray[0], positionArray[1]);
    	}
    	dbgprintf("alive\r\n");
    	chThdSleepMilliseconds(1000);
    }
}

