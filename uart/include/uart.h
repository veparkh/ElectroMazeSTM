/*
 * uart.h
 *
 *  Created on: 5 февр. 2024 г.
 *      Author: vparx
 */

#ifndef UART_SRC_UART_H_
#define UART_SRC_UART_H_

#include "ch.h"
#include "hal.h"
#include <stdint.h>
#include <stddef.h>
#include <string.h>

void uartInit(void);


msg_t uartPut(uint8_t byte);

msg_t uartWrite(uint8_t *bytes, size_t byteCount);
size_t  uartReadTimeout(uint8_t *bytes, size_t byteCount, time_msecs_t msec);
size_t uartRead(uint8_t *bytes, size_t byteCount);

//void uartSendPosition(float angl1, float angl2);

sdstate_t uartState(void);
#endif /* UART_SRC_UART_H_ */
