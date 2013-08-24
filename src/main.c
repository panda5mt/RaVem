
#include <stdio.h>
#include <string.h>

#include "ravem.h"

// Main Program 
int main (void) {
    
	hardware_init();    
	uart_init(9600);
	pool_init();
	
	uart_print("LPC81x JVM Start\r\n");
	uart_print("please wait...\r\n\r\n");

	int32_t thread_count = 0,lp,method_all_end;
	// Initialize Operand Stack and local Register  
	class_st *p;

	p = (class_st *)pool_alloc(sizeof(class_st) * 1);
	if(p == NULL)uart_print("error!");
	p[0] = seekCodeArrtibute(p[0], "main", 4);  //main_attribute
	p[0].field_mem_reg = NULL;
	p[0].field_num = 0;
	p[0].local_reg = (int *)pool_alloc(sizeof(int) * p[0].local_num);
	p[0].op_stack_type = (int *)pool_alloc(sizeof(int) * p[0].stack_num);
	p[0].op_stack = (int *)pool_alloc(sizeof(int) * p[0].stack_num);    
	p[0].op_stack_type[0] = 0;
	p[0].threadCommand = Thread_Active;
	p[0].myThreadNum   = 0;
    
    
	while(1){
		for(lp = 0 ; lp < thread_count + 1 ;lp++){
				if((p[lp].threadCommand == Thread_Active)||
				(p[lp].threadCommand == Thread_inSleep)){
					
					p[lp] = decodeVM(p[lp]);
			}
		}           
		switch(p[0].threadCommand){
		case Thread_getInitMethodWithStack:
			thread_count++;
	
			p = (class_st *)pool_realloc((int *)p,sizeof(class_st)*(1 + thread_count));
			if(p == NULL)uart_print("error!");  
			p[thread_count] = seekCodeArrtibute(p[thread_count], "<init>", 6);  // init
			p[thread_count].field_mem_reg = NULL;
			p[thread_count].field_num = 0;
			p[thread_count].local_reg = (int *)pool_alloc(sizeof(int) * p[thread_count].local_num);
			p[thread_count].op_stack_type = (int *)pool_alloc(sizeof(int) * p[thread_count].stack_num);
			p[thread_count].op_stack = (int *)pool_alloc(sizeof(int) * p[thread_count].stack_num);  
			p[thread_count].op_stack_type[0] = 0;           
			p[thread_count].threadCommand = Thread_init;
			
			// copy stack -> local variable
			for(lp = p[0].threadArg+1; lp != 0 ; lp--){
					p[thread_count].local_reg[lp] = getIntegerFromOperandStack(p[0]);
			}
									
			while(p[thread_count].threadCommand != Thread_returned){
					p[thread_count] = decodeVM(p[thread_count]);
			}
			
			p[thread_count].threadCommand = Thread_initIsDone;
			p[0].threadCommand = Thread_Active;

			break;
						
		case Thread_getStartMethod:
			for(lp = 0 ; lp <= thread_count + 1 ; lp++){
					if(p[lp].threadCommand == Thread_initIsDone)break;
			}
			
			if(p[lp].threadCommand != Thread_initIsDone){
				thread_count++;
				p = (class_st *)pool_realloc((int *)p,sizeof(class_st)*(1+thread_count));
				if(p == NULL)uart_print("error!");  
				lp = thread_count;
				
				p[lp] = seekCodeArrtibute(p[lp], "run", 3); // run method(start() calls this method)
								
				p[lp].local_reg = (int *)pool_alloc(sizeof(int) * p[lp].local_num);
				if(p[lp].local_reg == NULL)uart_print("error!");
				p[lp].op_stack_type = (int *)pool_alloc(sizeof(int) * p[lp].stack_num);
				if(p[lp].op_stack_type == NULL)uart_print("error!");
				p[lp].op_stack = (int *)pool_alloc( sizeof(int) * p[lp].stack_num);
				if(p[lp].op_stack == NULL)uart_print("error!");             
				p[lp].op_stack_type[0] = 0;
				p[lp].threadCommand = Thread_Active;
				p[lp].myThreadNum = lp;
				p[0].threadCommand = Thread_Active;
				break;
			}
								
			p[lp] = seekCodeArrtibute(p[lp], "run", 3); // run method(start() calls this method)
			if(p[lp].local_reg == NULL)uart_print("pointr error!\r\n");     
			p[lp].local_reg = (int *)pool_realloc(p[lp].local_reg, sizeof(int) * p[lp].local_num);
			if(p[lp].local_reg == NULL)uart_print("pointr error!\r\n");
			p[lp].op_stack_type = (int *)pool_realloc(p[lp].op_stack_type,sizeof(int) * p[lp].stack_num);
			if(p[lp].op_stack_type == NULL)uart_print("pointr error!\r\n");
			p[lp].op_stack = (int *)pool_realloc(p[lp].op_stack, sizeof(int) * p[lp].stack_num);
			if(p[lp].op_stack == NULL)uart_print("pointr error!\r\n");          
			p[lp].op_stack_type[0] = 0;
			p[lp].threadCommand = Thread_Active;
			p[lp].myThreadNum = lp;
			p[0].threadCommand = Thread_Active;

			break;              
		}
		method_all_end = 0;
		for(lp = 0 ; lp < thread_count + 1 ; lp++){
				if(p[lp].threadCommand != Thread_returned) method_all_end = method_all_end + 1;
		}
		if(method_all_end == 0) break;
	}	

	// end
	for(lp = 0; lp < thread_count + 1; lp++){   
		pool_free(p[lp].local_reg);
		pool_free(p[lp].op_stack_type);
		pool_free(p[lp].op_stack);
	}
	pool_free((int *)&p);

	p = NULL;

	uart_print("\r\n\r\nJVM Fin\r\n");
	while(1);
    
}
