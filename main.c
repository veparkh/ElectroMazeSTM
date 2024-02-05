#include "ch.h"
#include "hal.h"
#include <chprintf.h>
#include <serial.h>
#include "uart.h"

int main(void) {

    halInit();
    chSysInit();

    debug_stream_init();
    dbgprintf("Test\n\r");
    uint16_t i = 0;
    //uartInit();
    while (true) {
    	//msg_t res = uartPut(0b10100101);
    	//dbgprintf("%d\n\r",res);
    	chThdSleepMilliseconds(3000);

    }
}

