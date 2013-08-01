/*
 * eXVM.h
 *
 *  Created on: 2013/07/18
 *      Author: lynxeyed
 */

#ifndef EXVM_H_
#define EXVM_H_

#include "type.h"
#include "device_depend.h"

// constant_pool
//#define Constant Type				Value		length (in bytes)
#define CONSTANT_Class				7					// 3
#define	CONSTANT_Fieldref			9					// 5
#define	CONSTANT_Methodref		10				// 5
#define	CONSTANT_InterfaceMethodref	11	// 5
#define	CONSTANT_String				8					// 3
#define	CONSTANT_Integer			3					// 5
#define	CONSTANT_Float				4					// 5
#define	CONSTANT_Long					5					// 9
#define	CONSTANT_Double				6					// 9
#define	CONSTANT_NameAndType		12			// 5
#define	CONSTANT_Utf8						1				// 4 or more (see 'length')
#define	CONSTANT_MethodHandle		15			// 5
#define	CONSTANT_MethodType			16			// 3
#define	CONSTANT_InvokeDynamic	18			// 3

//stack type
#define Stack_Nothing 			0
#define Stack_IntType				1
#define Stack_DoubleType		2
#define Stack_ConstantPool	3
#define Stack_Field					4


// instruction code			mnemonic code		number of arguments
#define JAVA_nop								0x00					// 0
#define JAVA_iconst_0						0x03					// 0
#define JAVA_iconst_1						0x04					// 0
#define JAVA_iconst_2						0x05					// 0
#define JAVA_iconst_3						0x06					// 0
#define JAVA_iconst_4						0x07					// 0
#define JAVA_iconst_5						0x08					// 0
#define JAVA_bipush							0x10					// 1
#define JAVA_sipush							0x11					// 2
#define JAVA_ldc								0x12					// 1
#define JAVA_ldc_w							0x13					// 1

#define JAVA_iload_0						0x1A					// 0
#define JAVA_iload_1						0x1B					// 0
#define JAVA_iload_2						0x1C					// 0
#define JAVA_iload_3						0x1D					// 0

#define JAVA_istore_0						0x3B					// 0
#define JAVA_istore_1						0x3C					// 0
#define JAVA_istore_2						0x3D					// 0
#define JAVA_istore_3						0x3E					// 0

#define JAVA_iadd								0x60					// 0

#define JAVA_return							0xb1					// 0
#define JAVA_getstatic					0xb2					// 2
#define JAVA_getfield						0xb4					// 2
#define JAVA_putfield						0xb5					// 2
#define JAVA_invokevirtual			0xb6					// 2
//#define JAVA_invokespecial			0x00					// 0


extern const char exvm[];

typedef struct {
  int		tab;
	int		index;
	int		index2;
	int		bc_num;		//pointer of bytecode
	void*	stack_pt;	// stack pointer (int,long,float,double,string)
} const_pool_t;


typedef struct {
	int bc_offset;				// offset of bytecode (this class starts here = exvm[bc_offset]) 
	int code_offset;			// offset of code (Now we translate here from bc_offset = exvm[bc_offset+code_offset] )
	int code_length;			// length of code
	int *local_reg;				// local registers(malloc here)
	int *op_stack;				// operand stack(malloc here) numerics or CP num
	int *op_stack_type;		// type of each stack,0:nothing 1:int,byte 2:long,float,double 3:See CP 
	int stack_num;				// number of stacks
	int local_num;				// number of local registers
	char *field_mem_reg;	// Field (getfield and putfield)
} class_st;

const_pool_t getConstantPoolInfo(int constant_num);
const_pool_t seekConstClassNumString(int const_num);
const_pool_t seekClassIndex(int const_num);
const_pool_t seekNameAndType_name(int const_num);
const_pool_t seekNameAndType_desc(int const_num);
class_st seekCodeArrtibute(char* method_name,int strlen);
//
int getIntegerFromOperandStack(class_st cl);
char* getStringFromOperandStack(class_st cl);
//
class_st setStackFromConstantPool(class_st cl, int cp_num);
class_st setIntegerToStack(class_st cl, int num);
//
class_st getField(class_st cl);
class_st putField(class_st cl);
//
void invokevirtual_callFunction(class_st cl, char* func_name);
class_st decodeVM(class_st cl);



#endif /* EXVM_H_ */
