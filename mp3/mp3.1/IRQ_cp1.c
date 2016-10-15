/*
 * IRQ.c - support functions for handling interrupt
 * Author:	    guo 
 * Version: 1
 *
 */
 #include "IRQ_cp1.h"
 #include "i8259.h"			// used to initialize PIC 
 #include "types.h"
 #include "lib.h"

/// initialize the jump table for irq hanlder, in types.h, NULL == 0 
static do_irq irq_handler[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

/*   
 *	 set_irq_handler
 *	 DESCRIPTION: set up  the handler and enable the irq
 *   INPUTS: irq_number: the number of irq to be installed and func_p: the handler function
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void set_irq_handler(uint32_t irq_number,do_irq func_p){
	cli();									// mask interrupt 
	irq_handler[irq_number] = func_p;	/*Install the handler and enable the irq*/
	enable_irq(irq_number);
	sti();									// unmask 

}


/*   
 *	 unset_irq_handler
 *	 DESCRIPTION: Uninstall the handler and disable the irq
 *   INPUTS: irq_num: the number of irq to be installed
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */

void unset_irq_handler(uint32_t irq_number){
	cli();
	irq_handler[irq_number]= 0;			    /*Uninstall the handler and disable the irq*/
	disable_irq(irq_number);
	sti();
}

/*   
 *	interrupt_handler
 *	 DESCRIPTION: The interrupt handling fuction(called for each interrupt, as an interface)
 *   INPUTS:  register on the stack
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void interrupt_handler(stack_register reg){
	// create a hanlder function pointer to deal with this interrupt 
	void (*handler)(stack_register reg);
	//// given the isr number in the register, convert to the corresponding irq number 
	uint32_t irq_index = -1 * reg.isr_number;
	irq_index -= 1;
	/////// we find the function 
	handler = irq_handler[irq_index];
	////// when deal with current interrupt, we mask the interrupt from that line and send EOI 
	disable_irq(irq_index);		// refer to i8589.h 
	send_eoi(irq_index);
	/////// then execute if function well define 
	if(handler != 0){
		handler(reg);
	}
	//// after dealing, we enable irq again
	enable_irq(irq_index);
}













