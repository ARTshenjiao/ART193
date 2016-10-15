/*
 * IRQ_cp1.h - header file for  support fucntions for interrupt handling
 * Author:	    guo 
 * Version: 1
 *
 */

#ifndef IRQ_H
#define IRQ_H

#include "types.h"

/*handlering the interrupt*/
extern void interrupt_handler(stack_register reg);
/// initiailze irq handler 
extern void set_irq_handler(uint32_t irq_number, do_irq func_p);
//// delete the irq handler 
extern void unset_irq_handler(uint32_t irq_number);

#endif /* IRQ_H */


