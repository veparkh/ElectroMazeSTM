#include "ch.h"
#include "hal.h"
#include <chprintf.h>
#include "engine.h"
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
  
    dbgprintf("Test\n\r");
    INIT_X;
    for (uint16_t i=0;i<10000;i+=50){
    	chThdSleepMilliseconds(200);
    	SET_X(false,i);
    }
    for (uint16_t i=1000;i<2000;i+=10){
    	chThdSleepMilliseconds(200);
    	SET_X(true,i);
    }

    int i = 0;
    chThdSleepMilliseconds(10000);
    SET_X(true,2000);
    while (true) {
        chThdSleepMilliseconds(1000);
        dbgprintf("fine %d\n\r", i);
        palToggleLine(LINE_LED2);
        i++;
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

