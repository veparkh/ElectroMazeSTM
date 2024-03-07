#include "common.h"

static inline void testRoutines(void) {

    halInit();
    chSysInit();
    debug_stream_init();
#if(PROGRAM_ROUTINE == ENGINES_TEST)
	enginesTest();
#elif(PROGRAM_ROUTINE == UART_TEST)
	uartInit();
#elif(PROGRAM_ROUTINE == I2C_TEST)
	SensorThreadInit();
#elif(PROGRAM_ROUTINE == MAZE_TEST)
	mazeRoutine();
#endif
}



int main(void) {
#if(PROGRAM_ROUTINE != MAIN_ROUTINE)
	testRoutines();
#endif
	while(1){
		chThdSleepSeconds(40);
		//dbgprintf("alive\r\n");
	}
}


