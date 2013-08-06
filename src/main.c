
#include <stdio.h>
#include <string.h>

#include "ravem.h"


///* Main Program */
int main (void) {
	
	hardware_init();	
	uart_init(9600);

	
	uart_print("LPC81x JVM Start\r\n");
	uart_print("please wait...\r\n\r\n");

	char s[64];
	int thread_count = 0,lp;
	// Initialize Operand Stack and local Register
	class_st *p = NULL,*q = NULL;
	p = (class_st *)malloc(sizeof(class_st)*1);
	p[0] = seekCodeArrtibute("main",4);	//main_attribute
	p[0].field_mem_reg = NULL;
	p[0].local_reg = (int *)malloc(sizeof(int) * p[0].local_num);
	p[0].op_stack_type = (int *)malloc(sizeof(int) * p[0].stack_num);
	p[0].op_stack = (int *)malloc(sizeof(int) * p[0].stack_num);	
	p[0].op_stack_type[0] = 0;
	p[0].threadCommand = Thread_Active;
	p[0].myThreadNum   = 0;
	
	while(1){
		for(lp = 0 ; lp < thread_count + 1 ;lp++){
			if(p[lp].threadCommand != Thread_returned)
			{
				p[lp] = decodeVM(p[lp]);
			}
			
			if(p[0].threadCommand == Thread_getStartMethod){  //only main method can start method
				thread_count++;
				p[0].threadCommand = Thread_Active;
				p = (class_st *)realloc(p,sizeof(class_st)*(1+thread_count));
				if(p == NULL)uart_print("error!");
				//p = q;
				p[thread_count] = seekCodeArrtibute("run",3);	//main_attribute
				p[thread_count].field_mem_reg = NULL;
				p[thread_count].local_reg = (int *)malloc(sizeof(int) * p[thread_count].local_num);
				p[thread_count].op_stack_type = (int *)malloc(sizeof(int) * p[thread_count].stack_num);
				p[thread_count].op_stack = (int *)malloc(sizeof(int) * p[thread_count].stack_num);	
				p[thread_count].op_stack_type[0] = 0;
				p[thread_count].threadCommand = Thread_Active;
				p[thread_count].myThreadNum   = thread_count;
				//sprintf(s,"threadNo=%d,stack=%d,local=%d\r\n",thread_count,p[thread_count].stack_num,p[thread_count].local_num);
				//uart_print(s);
			}
		}	
		//if(p[0].threadCommand == Thread_returned)break;
			
		}
	
	// end
	
  free(p[0].local_reg);
	free(p[0].op_stack_type);
  free(p[0].op_stack);
  free(p);
	p = NULL;
	
	
	uart_print("\r\n\r\nJVM Fin\r\n");
	while(1);
	
	
}

