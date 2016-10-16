/* i8259.c - Functions to interact with the 8259 interrupt controller
 * vim:ts=4 noexpandtab
 */

// reference for initializing and masking:
// http://wiki.osdev.org/PIC#Masking

#include "i8259.h"
#include "lib.h"

/* Interrupt masks to determine which interrupts
 * are enabled and disabled */
uint8_t master_mask; /* IRQs 0-7 */
uint8_t slave_mask; /* IRQs 8-15 */

/* Initialize the 8259 PIC */
void
i8259_init(void)
{
	// mask all bits
	master_mask = 0xFF;
    slave_mask = 0xFF;
    set_masks();

    // Initialize master PIC.
    outb(ICW1, MASTER_8259_PORT);  			// write ICW1 to command port
    outb(ICW2_MASTER, MASTER_8259_PORT+1);	// write three bytes to data port
    outb(ICW3_MASTER, MASTER_8259_PORT+1);
    outb(ICW4, MASTER_8259_PORT+1);

    // Initialize slave PIC.
    outb(ICW1, SLAVE_8259_PORT); 
    outb(ICW2_SLAVE, SLAVE_8259_PORT+1);
    outb(ICW3_SLAVE, SLAVE_8259_PORT+1);
    outb(ICW4, SLAVE_8259_PORT+1);
}

/* Enable (unmask) the specified IRQ */
void
enable_irq(uint32_t irq_num)
{
	if (irq_num < 8)	// a master PIC interrupt
		master_mask &= ~(1 << irq_num);
	else				// a slave PIC interrupt
		slave_mask &= ~(1 << (irq_num-8));
	set_masks();
}

/* Disable (mask) the specified IRQ */
void
disable_irq(uint32_t irq_num)
{
	if (irq_num < 8)	// a master PIC interrupt
		master_mask |= (1 << irq_num);
	else				// a slave PIC interrupt
		slave_mask |= (1 << (irq_num-8));
	set_masks();
}

/* Send end-of-interrupt signal for the specified IRQ */
void
send_eoi(uint32_t irq_num)
{
	if (irq_num < 8)	// master PIC interrupt; issue only to master PIC
		outb(EOI|irq_num, MASTER_8259_PORT);
	else				// slave PIC interrupt; issue the command to both PIC chips
	{
		outb(EOI|(irq_num-8), SLAVE_8259_PORT);
		outb(EOI|2, MASTER_8259_PORT);		// slave is connected to the #2 port on master
	}
}

/* Set masks according to master_mask and slave_mask */
void 
set_masks()
{
	outb(master_mask, MASTER_8259_PORT+1);	// write to data ports
    outb(slave_mask, SLAVE_8259_PORT+1);
}