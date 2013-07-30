
#include <stdio.h>
#include <string.h>

#include "eXVM.h"


///* Main Program */
int main (void) {
	
	hardware_init();	
	uart_init(9600);

	
	uart_print("LPC81x JVM Start\r\n");
	uart_print("please wait...\r\n\r\n");

	
		
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

