/*
 * KB_cp1.c - support funciton for the keyboard 
 * Author:	    guo 
 * Version: 1
 *
 */
#include "IRQ_cp1.h"
#include "types.h"
#include "lib.h"
#include "KB_cp1.h"

/* 
* US Keyboard Layout. Adapted from 0Sdev.net 
* This is part of the scancode table used for check point 1
*/
/////////////// USB keyboard layout, reference from osdev.net 
/////////////////// we use part of scancode table for cp1 

static uint8_t kbdus[KARRAY_SIZE] = {
	0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
  '9', '0', '-', '=', '\b', /* Backspace */
  '\t',         /* Tab */
  'q', 'w', 'e', 'r',   /* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0,          /* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
 '\'', '`',   0,        /* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',            /* 49 */
  'm', ',', '.', '/',   0              /* Right shift */
};

//////////////// local function 
static void keyboard_handler(stack_register reg);

/*   
 *	 kb_handler
 *	 DESCRIPTION: handlering the keyboard
 *   INPUTS: reg the register on the stack
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */

static void keyboard_handler(stack_register reg){

	///////////// reference to osdev.net 
	uint8_t input_key;
	cli();								/*Start the critical section*/
	input_key = inb(KDATA_P);			/* Read from the keyboard's data buffer */
	if(input_key < KARRAY_SIZE){
		putc(kbdus[input_key]);			//////// display that key 
	}
	sti();

}

/*   
 *	 set_kb
 *	 DESCRIPTION: initialize the keyboard and install the handler
 *   INPUTS: none
 *   OUTPUTS: none
 *   SIDE EFFECTS: none
 */

void set_kb(){
	set_irq_handler(KB_IRQ_NUMBER,keyboard_handler);
}




