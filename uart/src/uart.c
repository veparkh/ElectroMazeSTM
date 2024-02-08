/*
 * uart.c
 *
 *  Created on: 5 февр. 2024 г.
 *      Author: vparx
 */
#include "uart.h"

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
/*void uartSendPosition(float angl1, float angl2){
	uint8_t bytes[8];
	memcpy(bytes, &angl1,4);
	memcpy(&bytes[4], &angl2, 4);
	for (uint8_t i = 0;i<8;i++){
		dbgprintf("%c",bytes[0]);
	}
}*/
sdstate_t uartState(void){
	return sd->state;
}

