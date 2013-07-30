#ifndef __DEVICE_DEPEND_H__
#define __DEVICE_DEPEND_H__

#include "LPC8xx.h"
//#include "lpc8xx_clkconfig.h"
#include "lpc8xx_gpio.h"
#include "lpc8xx_mrt.h"
#include "lpc8xx_uart.h"

// functions
void hardware_init(void);
void uart_init(int baud_rate);
void uart_print(char *str);





#endif
