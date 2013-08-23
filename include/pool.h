//
//  pool.h
//  
//
//  Created by atsu on 13/08/20.
//
//

#ifndef POOL_H_
#define POOL_H_

#include <stdio.h>
#include <string.h>
#include "device_depend.h"


#define memory_available    1
#define memory_invalid      0
#define pool_size           256 // 256 * 4 = 1kByte
#define magic_value         0xDEADDEAD
//#define USE_MAGIC

typedef struct {
    int *first_pointer;
    int *next_pointer;
    int pool_size_all;
    int available;
}pool_all;

typedef struct {
    int **this_pointer;
    int my_size;
    int available;
#if defined(USE_MAGIC)
    int magic_num;
#endif
}pool_each;

extern int pl_buf[pool_size];
void pool_init(void);
void pool_free(int *pointr);
int *pool_alloc(int size);
int *pool_realloc(int *pointr, int size);



#endif
