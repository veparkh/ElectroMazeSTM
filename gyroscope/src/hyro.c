#include "ch.h"
#include "hal.h"
#include <chprintf.h>

static const SerialConfig sd_st_cfg = {
  .speed = 115200,
  .cr1 = 0, .cr2 = 0, .cr3 = 0
};

static SerialDriver         *debug_serial = &SD3;
static BaseSequentialStream *debug_stream = NULL;

void debug_stream_init( void )
{
    sdStart( debug_serial, &sd_st_cfg );
    palSetPadMode( GPIOD, 8, PAL_MODE_ALTERNATE(7) );
    palSetPadMode( GPIOD, 9, PAL_MODE_ALTERNATE(7) );

    debug_stream = (BaseSequentialStream *)debug_serial;
}

void dbgprintf( const char* format, ... )
{
    if ( !debug_stream )
        return;

    va_list ap;
    va_start(ap, format);
    chvprintf(debug_stream, format, ap);
    va_end(ap);
}

static const I2CConfig i2c1_conf = {
    .timingr = STM32_TIMINGR_PRESC(14U)  |
    STM32_TIMINGR_SCLDEL(3U)  | STM32_TIMINGR_SDADEL(2U) |
    STM32_TIMINGR_SCLH(14U)   | STM32_TIMINGR_SCLL(17U),
    .cr1 = 0,
    .cr2 = 0
};

static I2CDriver* i2c1 =  &I2CD1;

int main(void) {

    halInit();
    chSysInit();

    i2cStart(i2c1, &i2c1_conf);
    // Переведем ноги B8 и B9 в режим i2c1
    palSetLineMode(PAL_LINE(GPIOB, 8), PAL_MODE_ALTERNATE(4));
    palSetLineMode(PAL_LINE(GPIOB, 9), PAL_MODE_ALTERNATE(4));

    uint8_t txbuf[1] = {0x0F};
    uint8_t rxbuf[1] = {0};

    debug_stream_init();
    dbgprintf("Test\n\r");
    uint16_t i = 0;
    while (true) {
        chThdSleepMilliseconds(1000);
        msg_t msg = i2cMasterTransmitTimeout(i2c1, 0b1101000, txbuf, 1, rxbuf, 1, 1000);
        dbgprintf("%d\n\r", rxbuf[0]);
        palToggleLine(LINE_LED2);
        i++;
    }
}
