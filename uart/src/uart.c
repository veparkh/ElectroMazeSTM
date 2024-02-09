/*
 * uart.c
 *
 *  Created on: 5 февр. 2024 г.
 *      Author: vparx
 */
#include "uart.h"

MUTEX_DECL(positionMutex);

float positionArray[2]={0};
static SerialDriver *sd = &SD4;

SerialConfig sc = {
		.speed = 115200,.cr1 = 0,
	    .cr2 = 0,
	    .cr3 = 0
};

void uartInit(void){
    palSetPadMode( GPIOD, 0, PAL_MODE_ALTERNATE(8) );
    palSetPadMode( GPIOD, 1, PAL_MODE_ALTERNATE(8) );
	//sdObjectInit(sd);
	sdStart(sd, &sc);


}
msg_t uartPut(uint8_t byte){
	return sdPut(sd,byte);
}
msg_t uartWrite(uint8_t *bytes, size_t byteCount){
	return sdWrite(sd,bytes, byteCount );
}
size_t uartReadTimeout(uint8_t *bytes, size_t byteCount,time_msecs_t msec ){
	return sdReadTimeout(sd,bytes,byteCount,chTimeMS2I(msec));
}

size_t uartRead(uint8_t *bytes, size_t byteCount){
	return sdRead(sd,bytes,byteCount) ;
}

sdstate_t uartState(void){
	return sd->state;
}

THD_FUNCTION(uartWorker, arq){
	(void)arq;
    uartInit();
    uint8_t queryBytes[] ={0xFA,0xD3,0x0F} ;
	uint8_t password[] ={0xEF,0xFF,0xA0} ;
	uint8_t positionAnswer[] = {0xAF, 0xE4, 0xCD};
	uint8_t query[100];
	dbgprintf("hello\r\n");
    while (true) {
    	chMtxLock(&positionMutex);
    	memset((uint8_t*)positionArray,0,8);
    	chMtxUnlock(&positionMutex);
    	size_t readByteCount = uartReadTimeout(query, 100, 0);
		dbgprintf(" clear bytecount = %d\r\n",readByteCount);
    	readByteCount = uartRead(query, 3);
    	dbgprintf("%d %d %d bytecount = %d\r\n",query[0],query[1],query[2], readByteCount);
    	if(query[0]!=queryBytes[0] || query[1]!=queryBytes[1] || query[2]!=queryBytes[2]){
    		continue;
    	}

    	msg_t res = uartWrite(password, 3);
    	dbgprintf("res: %d\r\n", res);
    	if(res!=3)
    		continue;
    	float positions[2]={0x0fffffff,-90.0};
    	while (true){
    		readByteCount = uartReadTimeout((uint8_t*)positions, 8, 2000);
    		dbgprintf("readBytes:%d\r\n",readByteCount);
    		if (readByteCount!=8)
    			break;
    		res = uartWrite(positionAnswer, 3);
    		dbgprintf("res %d\r\n", res);
    		if (res!=3)
    			break;
    		if (positions[0]==positionArray[0] && positions[0]==positionArray[0]){
    			dbgprintf("same\r\n");
    			chThdSleepMilliseconds(10);
    			continue;
    		}
    		if(chMtxTryLock(&positionMutex)){
    			memcpy((uint8_t*)positionArray, (uint8_t*)positions, 8);
    			chMtxUnlock(&positionMutex);
    			chThdSleepMilliseconds(10);
    		}
    		dbgprintf("position:%f   %f\r\n",positions[0], positions[1]);


    	}
    }

}

