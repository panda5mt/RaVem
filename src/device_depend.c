#include <stdio.h>
#include <string.h>
#include "device_depend.h"



void hardware_init(void){
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
