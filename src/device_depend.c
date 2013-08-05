#include <stdio.h>
#include <string.h>
#include "device_depend.h"


volatile static unsigned long msTicks;                            /* counts 1ms timeTicks */

void hardware_init(void){
	
	
	SystemCoreClockUpdate();
	
	/* Enable SWM clock */
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<7);

	/* Pin Assign 8 bit Configuration */
	/* U0_TXD */
	/* U0_RXD */
	LPC_SWM->PINASSIGN0 = 0xffff0004UL; 

	/* Pin Assign 1 bit Configuration */
	/* SWCLK */
	/* SWDIO */
	/* RESET */
	LPC_SWM->PINENABLE0 = 0xffffffb3UL; 
	
	setup_systick();
}

void uart_print(char *str){
	UARTSend(LPC_USART0,(uint8_t*)str,strlen(str));
	return;
}

void uart_init(int baud_rate){
	UARTInit(LPC_USART0, baud_rate);
}

int uart_read(void){

	while(!(LPC_USART0->STAT & RXRDY)); 
	return (int) ( LPC_USART0->RXDATA );
	
}

int time_millis(void){
	return msTicks;
}


/*----------------------------------------------------------------------------
  SysTick_Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler(void) {
  msTicks++;                        /* increment counter necessary in Delay() */
}

void setup_systick (void) {

	 SysTick->CTRL |= (0x1<<0);

	// Setup SysTick Timer for 1 msec interrupts
	// Configure System tick timer in 10msec period
	if (SysTick_Config(SystemCoreClock / 1000)) { /* Setup SysTick Timer for 1 msec interrupts  */
		while (1);                                  /* Capture error */
	}

}
