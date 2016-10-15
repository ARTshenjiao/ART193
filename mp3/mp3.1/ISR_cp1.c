/*
 * isr.c - support functions for handling exception
 * Author:	    guo 
 * Version: 1
 *
 */

 #include "types.h"
 #include "lib.h"

 /*   
  *	  exception_handler
  *	  DESCRIPTION: handlering the exception
  *   INPUTS: irq_num: the number of irq to be installed
  *   OUTPUTS: none
  *   RETURN VALUE: none
  *   SIDE EFFECTS: none
  */

void exception_handler(stack_register reg){

	printf("NUMBER %d exception occured\n", reg.isr_number);

  	while(1);

}























