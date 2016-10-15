/*
 * IDT_GATE.S - entry fucntion for IDT table
 * Author:	    gyms 
 * Version: 1
 *
 */
////////////////.text section is the region of an executable where the actual executable instructions lie
/////////////// the data can't be modified in .text due to security reason, so we use .text not .data 

.text
//////////////////////// this part has all the exceptions, 32 total 
.global isr0	.global isr1	.global isr2	.global isr3
.global isr4	.global isr5	.global isr6	.global isr7
.global isr8	.global isr9	.global isr10	.global isr11
.global isr12	.global isr13	.global isr14	.global isr15
.global isr16	.global isr17	.global isr18	.global isr19
.global isr20	.global isr21	.global isr22	.global isr23
.global isr24	.global isr25	.global isr26	.global isr27
.global isr28	.global isr29	.global isr30	.global isr31
////////////////////////// this part is for all interrupt, 16 total 
.global irq0	.global irq1	.global irq2	.global irq3
.global irq4	.global irq5	.global irq6	.global irq7
.global irq8	.global irq9	.global irq10	.global irq11
.global irq12	.global irq13	.global irq14	.global irq15
//////////////////// system call 
.global system_call;

///////////////////exceptions ISR, push postive number for excpetions 

isr0:
	cli
	pushl $0
	pushl $0
	jmp exception_occur

isr1:
	cli
	pushl $0
	pushl $1
	jmp exception_occur
	
isr2:
	cli
	pushl $0
	pushl $2
	jmp exception_occur

isr3:
	cli
	pushl $0
	pushl $3
	jmp exception_occur

isr4:
	cli
	pushl $0
	pushl $4
	jmp exception_occur

isr5:
	cli
	pushl $0
	pushl $5
	jmp exception_occur

isr6:
	cli
	pushl $0
	pushl $6
	jmp exception_occur

isr7:
	cli
	pushl $0
	pushl $7
	jmp exception_occur

isr8:
	cli
	pushl $8
	jmp exception_occur

isr9:
	cli
	pushl $0
	pushl $9
	jmp exception_occur
	
isr10:
	cli
	pushl $10
	jmp exception_occur

isr11:
	cli
	pushl $11
	jmp exception_occur

isr12:
	cli
	pushl $12
	jmp exception_occur

isr13:
	cli
	pushl $13
	jmp exception_occur

isr14:
	cli
	pushl $14
	jmp exception_occur

isr15:
	cli
	pushl $0
	pushl $15
	jmp exception_occur

isr16:
	cli
	pushl $0
	pushl $16
	jmp exception_occur

isr17:
	cli
	pushl $0
	pushl $17
	jmp exception_occur

isr18:
	cli
	pushl $0
	pushl $18
	jmp exception_occur

isr19:
	cli
	pushl $0
	pushl $19
	jmp exception_occur

isr20:
	cli
	pushl $0
	pushl $20
	jmp exception_occur

isr21:
	cli
	pushl $0
	pushl $21
	jmp exception_occur

isr22:
	cli
	pushl $0
	pushl $22
	jmp exception_occur

isr23:
	cli
	pushl $0
	pushl $23
	jmp exception_occur

isr24:
	cli
	pushl $0
	pushl $24
	jmp exception_occur

isr25:
	cli
	pushl $0
	pushl $25
	jmp exception_occur

isr26:
	cli
	pushl $0
	pushl $26
	jmp exception_occur

isr27:
	cli
	pushl $0
	pushl $27
	jmp exception_occur

isr28:
	cli
	pushl $0
	pushl $28
	jmp exception_occur

isr29:
	cli
	pushl $0
	pushl $29
	jmp exception_occur

isr30:
	cli
	pushl $0
	pushl $30
	jmp exception_occur

isr31:
	cli
	pushl $0
	pushl $31
	jmp exception_occur

/////////////////////interrupt IRQ, push negative number for interrupt 
irq0:
	pushl $0   
	pushl $-1
	jmp interrupt_occur
irq1: 
	pushl $0 
	pushl $-2
	jmp interrupt_occur
irq2:
	pushl $0 
	pushl $-3
	jmp interrupt_occur
irq3:
	pushl $0 
	pushl $-4
	jmp interrupt_occur
irq4:
	pushl $0 
	pushl $-5
	jmp interrupt_occur
irq5:
	pushl $0 
	pushl $-6
	jmp interrupt_occur
irq6:
	pushl $0 
	pushl $-7
	jmp interrupt_occur
irq7:
	pushl $0 
	pushl $-8
	jmp interrupt_occur
irq8:
	pushl $0 
	pushl $-9
	jmp interrupt_occur
irq9:	
	pushl $0 
	pushl $-10
	jmp interrupt_occur
irq10:
	pushl $0 
	pushl $-11
	jmp interrupt_occur
irq11:
	pushl $0 
	pushl $-12
	jmp interrupt_occur
irq12:
	pushl $0 
	pushl $-13
	jmp interrupt_occur
irq13:
	pushl $0 
	pushl $-14
	jmp interrupt_occur
irq14:
	pushl $0 
	pushl $-15
	jmp interrupt_occur
irq15:
	pushl $0 
	pushl $-16
	jmp interrupt_occur

///////////////////////// system call 
system_call:
	pushl $0 
	pushl $0
	jmp interrupt_occur
	
# void exception_occur(void); 
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: push all GPR and segment registers 
exception_occur:

	pushal         #Push all general purpose registers

	pushw %ds      #Push  segament registers
	pushw %es
	pushw %fs
	pushw %gs

	movw $0x18,%cx             #0x18 corresponds to Kernel Data segment, refer x86_desc.h 
	movw %cx,%ds			   #Modify the segment registers
	movw %cx,%es	
	movw %cx,%fs	
	movw %cx,%gs	

	call exception_handler
					           #Restore all the segament regisers except the cs: code segment
	popw %gs
	popw %fs
	popw %es
	popw %ds

	popal

	addl $8, %esp				// popl the two parameters for the exception: pushl 0 and pushl #exception number 

	sti  						// enable interrupt 
	iret						// return from interrupt(exception) after done handler 


# void interrupt_occur(void);
# Interface: C-style
#    Inputs: none
#   Outputs: none
# Registers: 
interrupt_occur:
	pushal         #Push all the gereneral registers

	pushw %ds      #Push the segament registers
	pushw %es
	pushw %fs
	pushw %gs

	movw $0x18,%cx             #0x18 corresponds to Kernel Data segment
	movw %cx,%ds			   #Modify the segment registers
	movw %cx,%es	
	movw %cx,%fs	
	movw %cx,%gs	

	call interrupt_handler
					           #Restore all the segament regisers except the CS
	popw %gs
	popw %fs
	popw %es
	popw %ds

	popal

	addl $8, %esp			// popl the two parameters for the exception: pushl 0 and pushl #interrupt number 
	sti
	iret					// return from interrupt(exception) after done handler 
