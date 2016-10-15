/*
 * IDT_cp1.c - support functions for set up idt entry and initialize idt 
 * Author:	    gyms
 * Version: 1
 *
 */
 #include "types.h"
 #include "x86_desc.h"
 #include "IDT_GATE_cp1.h"

// helper function decleration to set up each entry in the IDT table, see below for details
 static void 
 initialize_IDT_entry(int privilege_dpl, uint32_t handler_base_address,uint16_t segment,int size,int index);
 
/*  initialize_IDT_entry
 *	 DESCRIPTION: Set up the IDT entry based on the input value
 *   INPUTS: 
 *			 hanlder: the base adderss
 *			 segment: KERNAL_CS segmentment 
 *           size: determine the size of the entry
 *           privilege_dpl: determine the privilege_dpl
 *			 index : the index in the IDT table,
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
*/
void 
initialize_IDT_entry(int privilege_dpl, uint32_t handler_base_address,uint16_t segment,int size,int index){

  /*Set up all the reserved bits and present bits*/	
	// refer to x86_desc.h for idt strcture 
	idt[index].present = 1;
	idt[index].reserved0 = 0;
	idt[index].reserved1 = 1;
	idt[index].reserved2 = 1;
	idt[index].reserved3 = 0;
	idt[index].reserved4 = 0x00;
  // then set up the base address of handler for each entry 
	SET_IDT_ENTRY(idt[index], handler_base_address);
  // set up the remain flags 
	idt[index].size=size;
	idt[index].segment_selector=segment;
	idt[index].dpl=privilege_dpl;
}

/*  initialize_IDT
 *	 DESCRIPTION: set up  the IDT table
 *   INPUTS: none
 *   OUTPUTS: none
 *   RETURN VALUE: none
 *   SIDE EFFECTS: none
 */
void initialize_IDT(){
 
	/*Install the IDT entry for exception*/
	initialize_IDT_entry(0, (uint32_t)isr0,KERNEL_CS,1,0);
	initialize_IDT_entry(0, (uint32_t)isr1,KERNEL_CS,1,1);
	initialize_IDT_entry(0, (uint32_t)isr2,KERNEL_CS,1,2);
	initialize_IDT_entry(0, (uint32_t)isr3,KERNEL_CS,1,3);
	initialize_IDT_entry(0, (uint32_t)isr4,KERNEL_CS,1,4);
	initialize_IDT_entry(0, (uint32_t)isr5,KERNEL_CS,1,5);
	initialize_IDT_entry(0, (uint32_t)isr6,KERNEL_CS,1,6);
	initialize_IDT_entry(0, (uint32_t)isr7,KERNEL_CS,1,7);
	initialize_IDT_entry(0, (uint32_t)isr8,KERNEL_CS,1,8);
	initialize_IDT_entry(0, (uint32_t)isr9,KERNEL_CS,1,9);
	initialize_IDT_entry(0, (uint32_t)isr10,KERNEL_CS,1,10);
	initialize_IDT_entry(0, (uint32_t)isr11,KERNEL_CS,1,11);
	initialize_IDT_entry(0, (uint32_t)isr12,KERNEL_CS,1,12);
	initialize_IDT_entry(0, (uint32_t)isr13,KERNEL_CS,1,13);
	initialize_IDT_entry(0, (uint32_t)isr14,KERNEL_CS,1,14);
	initialize_IDT_entry(0, (uint32_t)isr15,KERNEL_CS,1,15);
	initialize_IDT_entry(0, (uint32_t)isr16,KERNEL_CS,1,16);
	initialize_IDT_entry(0, (uint32_t)isr17,KERNEL_CS,1,17);
	initialize_IDT_entry(0, (uint32_t)isr18,KERNEL_CS,1,18);
	initialize_IDT_entry(0, (uint32_t)isr19,KERNEL_CS,1,19);
	initialize_IDT_entry(0, (uint32_t)isr20,KERNEL_CS,1,20);
	initialize_IDT_entry(0, (uint32_t)isr21,KERNEL_CS,1,21);
	initialize_IDT_entry(0, (uint32_t)isr22,KERNEL_CS,1,22);
	initialize_IDT_entry(0, (uint32_t)isr23,KERNEL_CS,1,23);
	initialize_IDT_entry(0, (uint32_t)isr24,KERNEL_CS,1,24);
	initialize_IDT_entry(0, (uint32_t)isr25,KERNEL_CS,1,25);
	initialize_IDT_entry(0, (uint32_t)isr26,KERNEL_CS,1,26);
	initialize_IDT_entry(0, (uint32_t)isr27,KERNEL_CS,1,27);
	initialize_IDT_entry(0, (uint32_t)isr28,KERNEL_CS,1,28);
	initialize_IDT_entry(0, (uint32_t)isr29,KERNEL_CS,1,29);
	initialize_IDT_entry(0, (uint32_t)isr30,KERNEL_CS,1,30);
	initialize_IDT_entry(0, (uint32_t)isr31,KERNEL_CS,1,31);

	/*****Install the IDT entry for intterrupt*******/
	initialize_IDT_entry(0, (uint32_t)irq0,KERNEL_CS,1,32);
	initialize_IDT_entry(0, (uint32_t)irq1,KERNEL_CS,1,33);
	initialize_IDT_entry(0, (uint32_t)irq2,KERNEL_CS,1,34);
	initialize_IDT_entry(0, (uint32_t)irq3,KERNEL_CS,1,35);
	initialize_IDT_entry(0, (uint32_t)irq4,KERNEL_CS,1,36);
	initialize_IDT_entry(0, (uint32_t)irq5,KERNEL_CS,1,37);
	initialize_IDT_entry(0, (uint32_t)irq6,KERNEL_CS,1,38);
	initialize_IDT_entry(0, (uint32_t)irq7,KERNEL_CS,1,39);
	initialize_IDT_entry(0, (uint32_t)irq8,KERNEL_CS,1,40);
	initialize_IDT_entry(0, (uint32_t)irq9,KERNEL_CS,1,41);
	initialize_IDT_entry(0, (uint32_t)irq10,KERNEL_CS,1,42);
	initialize_IDT_entry(0, (uint32_t)irq11,KERNEL_CS,1,43);
	initialize_IDT_entry(0, (uint32_t)irq12,KERNEL_CS,1,44);
	initialize_IDT_entry(0, (uint32_t)irq13,KERNEL_CS,1,45);
	initialize_IDT_entry(0, (uint32_t)irq14,KERNEL_CS,1,46);
	initialize_IDT_entry(0, (uint32_t)irq15,KERNEL_CS,1,47);

	/*************system call*************************/
	initialize_IDT_entry(3, (uint32_t)system_call,KERNEL_CS,1,0x80);

	/*Load the IDTR register*/ 
	// it takes a 32 -bit address, so first we cast, refer to x86_desc.h
	lidt((uint32_t)(&idt_desc_ptr));
	
}








