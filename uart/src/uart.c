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
	sdStart(sd, &sc);
    palSetPadMode( GPIOD, 0, PAL_MODE_ALTERNATE(8) );
    palSetPadMode( GPIOD, 1, PAL_MODE_ALTERNATE(8) );
}
msg_t uartPut(uint8_t byte){
	return sdPut(sd,byte);
}
msg_t uartWrite(uint8_t *bytes, size_t byteCount){
	return sdWrite(sd,bytes, byteCount );
}

size_t uartRead(uint8_t *bytes, size_t byteCount){
	return sdRead(sd,bytes,byteCount) ;
}

