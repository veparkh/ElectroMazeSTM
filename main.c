#include "ch.h"
#include "hal.h"
#include <chprintf.h>
#include <serial.h>
#include "engine.h"


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
    }
}
