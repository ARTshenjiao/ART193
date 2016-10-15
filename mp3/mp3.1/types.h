/* types.h - Defines to use the familiar explicitly-sized types in this
 * OS (uint32_t, int8_t, etc.).  This is necessary because we don't want
 * to include <stdint.h> when building this OS
 * vim:ts=4 noexpandtab
 */

#ifndef _TYPES_H
#define _TYPES_H

#define NULL 0

#ifndef ASM

/* Types defined here just like in <stdint.h> */
typedef int int32_t;
typedef unsigned int uint32_t;

typedef short int16_t;
typedef unsigned short uint16_t;

typedef char int8_t;
typedef unsigned char uint8_t;

/////////////// define new data type for hanlding interrupts 
typedef struct stack_register{
	uint32_t isr_number, error;
	uint32_t eax, ebx, ecx, edx, edi, esi, ebp, esp;	// 8 general purpose register
	uint16_t ds, fs, es, gs;	// segment register on stack 
}stack_register;

///////////// define function pointer for intterrupt 
typedef void (*do_irq)(stack_register reg);


#endif /* ASM */

#endif /* _TYPES_H */
