/****************************************************************************
 *   $Id:: blinky.c 3634 2012-10-31 00:09:55Z usb00423                      $
 *   Project: NXP LPC8xx Blinky example
 *
 *   Description:
 *     This file contains LED blink code example which include timer,
 *     GPIO initialization, and clock monitoring.
 *
 ****************************************************************************
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * products. This software is supplied "AS IS" without any warranties.
 * NXP Semiconductors assumes no responsibility or liability for the
 * use of the software, conveys no license or title under any patent,
 * copyright, or mask work right to the product. NXP Semiconductors
 * reserves the right to make changes in the software without
 * notification. NXP Semiconductors also make no representation or
 * warranty that such application will be suitable for the specified
 * use without further testing or modification.

 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors'
 * relevant copyright in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers. This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.

****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "eXVM.h"


///* Main Program */
int main (void) {
	
	hardware_init();	
	uart_init(9600);

	
	uart_print("LPC81x JVM Start\r\n");
	uart_print("please wait...\r\n\r\n");

	
//	char *strn;
		
	// Initialize Operand Stack and local Register
	
	class_st *p;
	p = (class_st *)malloc(sizeof(class_st));
	*p = seekCodeArrtibute("main",4);	//main_attribute
	p->local_reg = (int *)malloc(sizeof(int) * p->local_num);
	p->op_stack_type = (int *)malloc(sizeof(int) * p->stack_num);
	p->op_stack = (int *)malloc(sizeof(int) * p->stack_num);	
	p->op_stack_type[0] = 0;
	
	
	decodeVM(*p);
	
	// end
	free(p->local_reg);
	free(p->op_stack_type);
	free(p->op_stack);
	free(p);
	
	
	
	uart_print("\r\n\r\nJVM Fin\r\n");
	while(1);
	
	
}

