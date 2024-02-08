#include "ch.h"
#include "hal.h"
#include <chprintf.h>
#include <serial.h>
#include "uart.h"
#include <string.h>

int main(void) {

    halInit();
    chSysInit();
    debug_stream_init();
    dbgprintf("Test\n\r");
    uartInit();
    uint8_t queryBytes[] ={0xFA,0xD3,0x0F} ;
	uint8_t password[] ={0xEF,0xFF,0xA0} ;
	uint8_t positionAnswer[] = {0xAF, 0xE4, 0xCD};
	uint8_t query[3];

    while (true) {
    	size_t readByteCount = uartRead(query, 3);
    	dbgprintf("%d %d %d bytecount = %d\r\n",query[0],query[1],query[2], readByteCount);
    	if(readByteCount!=3)
    		continue;
    	if(query[0]!=queryBytes[0] || query[1]!=queryBytes[1] || query[2]!=queryBytes[2])
    		continue;
    	msg_t res = uartWrite(password, 3);
    	dbgprintf("res: %d\r\n", res);
    	if(res!=3)
    		continue;
    	float positions[2]={0x0fffffff,-90.0};
    	while (true){
    		readByteCount = uartReadTimeout((uint8_t*)positions, 8, 800);
    		dbgprintf("readBytes:%d\r\n",readByteCount);
    		if (readByteCount!=8)
    			break;
    		dbgprintf("position:%f   %f\r\n",positions[0], positions[1]);
    		res = uartWrite(positionAnswer, 3);
    		dbgprintf("res %d\r\n", res);
    		if (res!=3)
    			break;

    	}
    	chThdSleepMilliseconds(200);
    }
}

