/*
 * ISR_cp1.h - support functions for handle isr 
 * Author:	    guo
 * Version: 1
 *
 */

#ifndef ISR__H
#define ISR__H

#include "types.h"

/*handlering the exception*/
extern void exception_handler(stack_register reg);

#endif /* ISR__H */
