
#include <stdio.h>
#include <string.h>

#include "ravem.h"


///* Main Program */
int main (void) {
	
	hardware_init();	
	uart_init(9600);

	
	uart_print("LPC81x JVM Start\r\n");
	uart_print("please wait...\r\n\r\n");

	int32_t thread_count = 0,lp,method_all_end;

	// Initialize Operand Stack and local Register	
	class_st *p;

	p = (class_st *)malloc(sizeof(class_st) * 1);	
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
		method_all_end = 0;
		for(lp = 0;lp < thread_count + 1;lp++){
			if(p[0].threadCommand == Thread_returned) method_all_end = method_all_end + 1;
			if(method_all_end == thread_count + 1) break;
		}
	}
	
	// end
	for(lp = 0; lp < thread_count + 1; lp++){	
		free(p[lp].local_reg);
		free(p[lp].op_stack_type);
		free(p[lp].op_stack);
	}
  free(p);
	
	p = NULL;
	
	
	uart_print("\r\n\r\nJVM Fin\r\n");
	while(1);
	
	
}

