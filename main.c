#include "ch.h"
#include "hal.h"
#include <chprintf.h>
#include <serial.h>


int main(void) {

    halInit();
    chSysInit();

    debug_stream_init();
    dbgprintf("Test\n\r");
    uint16_t i = 0;
    while (true) {
        chThdSleepMilliseconds(1000);
        dbgprintf("fine %d\n\r", i);
        palToggleLine(LINE_LED2);
        i++;
    }
}
