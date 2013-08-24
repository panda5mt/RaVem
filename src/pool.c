#include <stdio.h>
#include "pool.h"


int pl_buf[pool_size];
pool_all poal;

void pool_init(void){    
    poal.first_pointer = &pl_buf[0];
    poal.pool_size_all = pool_size;
    
    poal.available = memory_available;
    poal.next_pointer = &pl_buf[(int)((sizeof(pool_all) + (sizeof(int) - 1)) / sizeof(int))];
    memcpy(poal.first_pointer, &poal, sizeof(pool_all)); //todo: change 'pl_buf' pointer

}

int *pool_alloc(int size){
    
    size = (size + (sizeof(int) - 1)) / sizeof(int); //round int type alignment
        
    int *pointr;
    pool_each poeh;
    
    poal.pool_size_all = poal.pool_size_all - ((sizeof(pool_each) + (sizeof(int) - 1)) / sizeof(int)) - size; // int alignment
    
    if(poal.pool_size_all <= 0){
        uart_print("malloc error!\r\n");
        return NULL;
    }
    
    poeh.my_size = size;
#if defined(USE_MAGIC)
    poeh.magic_num = magic_value;
#endif
    poeh.available  = memory_available;
    pointr = poal.next_pointer + (int)((sizeof(pool_each) + (sizeof(int) - 1)) / sizeof(int));

    poeh.this_pointer = &pointr;
    
    memcpy(poal.next_pointer, &poeh, sizeof(pool_each)); //todo: change 'pl_buf' pointer
    poal.next_pointer = pointr + size;

    return pointr;
}

void pool_free(int *pointr){
    if (pointr == NULL)return;
    pool_each poeh;
    
    pointr = pointr - (int)((sizeof(pool_each) + (sizeof(int) - 1)) / sizeof(int)); // align header
    memcpy(&poeh,pointr,sizeof(pool_each));
#if defined(USE_MAGIC)
    if (poeh.magic_num != magic_value){
        uart_print("pointer error\r\n");
        return;
    }
#endif
    poeh.available = memory_invalid;
    memcpy(pointr, &poeh, sizeof(pool_each));
    return;
    
}

int *pool_realloc(int *pointr, int size){

    int *new_pointr;
    
    if(pointr == NULL)return NULL;
    pool_each poeh;
    size = (size + (sizeof(int) - 1)) / sizeof(int); //round int type alignment
    
    pointr = pointr - (int)((sizeof(pool_each) + (sizeof(int) - 1)) / sizeof(int)); // align header
    
    memcpy(&poeh,pointr,sizeof(pool_each));
#if defined(USE_MAGIC)
    if (poeh.magic_num != magic_value){
			uart_print("pointer error\r\n");
			return NULL;
    }
#endif
    if (poeh.my_size >= size){
        
			poeh.my_size = size;
			memcpy(pointr, &poeh, sizeof(pool_each));
			pointr = pointr + (int)((sizeof(pool_each) + (sizeof(int) - 1)) / sizeof(int)); // align pointer
			return pointr;
        
    }
    poeh.available = memory_invalid;
    memcpy(pointr, &poeh, sizeof(pool_each));

    new_pointr = (int *)pool_alloc(sizeof(int) * size);
    pointr = pointr + (int)((sizeof(pool_each) + (sizeof(int) - 1)) / sizeof(int)); // align pointer

    memcpy(new_pointr, pointr, sizeof(int) * poeh.my_size);
    
    return new_pointr;
}
