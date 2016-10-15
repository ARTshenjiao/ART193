/*
 * RTC_cp1.c - support funciton for RTC 
 * Author:	    guo 
 * Version: 1
 *
 */

#include "IRQ_cp1.h"
#include "lib.h"
#include "RTC_cp1.h"

//// local functions for rtc interrupt 
static void do_rtc(stack_register reg);

 /*   
  *	  do_rtc
  *	  DESCRIPTION: handlering the rtc function
  *   INPUTS: none
  *   OUTPUTS: none
  *   RETURN VALUE: none
  *   SIDE EFFECTS: none
  */
static void do_rtc(stack_register reg){
	/*test_interrupts();*/
	outb(RC,CMD_P);   /*Have to read something for the rtc to work*/
	inb(DATA_P);
}


 /*   
  *	  set_rtc
  *	  DESCRIPTION: initialize the RTC to 2Hz, r3-r0 : 15  rate 
  *   INPUTS: none
  *   OUTPUTS: none
  *   RETURN VALUE: none
  *   SIDE EFFECTS: none
  */
void set_rtc(){
	uint8_t rate_frequency = 15;	/// set the rate to 2 hz 
	uint8_t temp = 0;				// store the temp value from RTC register

	///// enable the periodic interrput, changing register B 
	cli();
	outb(RB, CMD_P);		// put RB value in CMD port 
	temp = inb(DATA_P);		// from data port getting temp value 
	outb(RB, CMD_P);		// put RB value in CMD port 
	outb(PIE_BIT|temp, DATA_P);  //// turn on the PIE bit 
	sti();

	/// set up frequnecy to 2 hz, by changing register A 
	cli();
	outb(RA, CMD_P);
	temp = inb(DATA_P);
	outb(RA, CMD_P);
	outb( (rate_frequency & 0x0f)|(temp & 0xf0), DATA_P );			// adjust frequency 
	sti();
	///////////////////////////////////		// set up the RTC handler 

	set_irq_handler(RTC_IRQ_NUMBER, do_rtc);

}







