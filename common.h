/*
 * common.h
 *
 *  Created on: 29 февр. 2024 г.
 *      Author: vparx
 */

#ifndef COMMON_H_
#define COMMON_H_

#include "ch.h"
#include "hal.h"
#include "engine.h"
#include "uart.h"
#include "Sensors.h"
#include "maze.h"
#include "serial.h"

// List of all possible programs
#define MAIN_ROUTINE			0
#define ENGINES_TEST			1
#define UART_TEST				2
#define I2C_TEST				3
#define MAZE_TEST				4


// Selection of program to run
#define PROGRAM_ROUTINE MAZE_TEST

#endif /* COMMON_H_ */
