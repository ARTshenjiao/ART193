/*
 * paging_cp1.c - this file is for paging initialization
 * Author:	    guo
 * Version: 1
 *
 */


#include "paging.h"

/// local functions 
static void set_pd();	static void set_pt();
static void set_registers();		static void translation();


/*
 *	set_pd
 *	DESCRIPTION: set the page directory array 
 *	INPUT: None
 * 	OUTPUT: None
 */
static void set_pd()
{
	int index = 0;		// index to pd
	for(index = 0; index < DIRECTORY_SIZE; index++){
		//// set bits into the entry to specific value 
		pd[index].R_W = 1;		// read write mode 
		pd[index].PCD = 1;		// cache disabled 

		pd[index].P = 0;
		pd[index].U_S = 0;
		pd[index].PWT = 0;
		pd[index].A = 0;
		pd[index].zero = 0;
		pd[index].PS = 0;
		pd[index].G = 0;
		pd[index].avail = 0;
		pd[index].pt_base_address = 0;	/*set bits in pde to proper value*/
	}
}


/*
 *	set_pt
 *	DESCRIPTION: set pte in pte table to initialized value
 *	INPUT: None
 * 	OUTPUT: None
 */
static void set_pt()
{
	int index = 0;
	for(index = 0; index < TABLE_SIZE; index++){
		pt[index].R_W = 1;
		pt[i].PCD = 1;
		pt[i].page_base_address = index;	/*set bits in pde to proper value*/

		pt[index].P = 0;
		pt[index].U_S = 0;
		pt[index].PWT = 0;
		pt[index].A = 0;
		pt[index].D = 0;
		pt[index].PAT = 0;
		pt[index].G = 0;
		pt[index].avail = 0;	
	}

}

/*
 *	translation
 *  DESCRIPTION: translation the memeory location in different sizes with different entry
 *	INPUT: NONE
 *	OUTPUT: NONE
 */
static void translation()
{

	/*translation the first PDE with a 4kb space*/
	pd[USER_MODE].PS = 0;		/*4KB page*/
	pd[USER_MODE].U_S = 1;		/*user level*/
	pd[USER_MODE].P = 1;		/*present*/
	pd[USER_MODE].R_W = 1;		/*read only*/
	
	pd[USER_MODE].pt_base_address = ((uint32_t)pt >> 12);	/*fill the address by disregarind the rightmost 12 bit of pt*/


	/*translation the second PDE to kernel(4MB)*/
	pd[KERNEL_MODE].PS = 1;		/*4MB page*/
	pd[KERNEL_MODE].U_S = 0;		/*supervisor, high priviledge*/ 
	pd[KERNEL_MODE].P = 1;		/*present*/
	pd[KERNEL_MODE].R_W = 1;		/*read only*/

	pd[KERNEL_MODE].pt_base_address = ((KERNEL_ADDRESS >> 22) << 10);/*fill the address, since they are 20 bits */ 

	/*translation the PTE to video memory(4KB)*/
	//// 
	pt[VIDEO_MEMORY].P = 1;	/*present*/
	pt[VIDEO_MEMORY].R_W = 1;	/*read & write*/
	pt[VIDEO_MEMORY].U_S = 1;	/*user level*/
	pt[VIDEO_MEMORY].page_base_addr = VIDEO_MEMORY;/*fill the address*/


}


/*  
 *	set_registerss
 *  DESCRIPTION: set CR0, CR3, CR4 to proper value to USER_MODE paging
 *	INPUT:NONE
 *	OUTPUT:NONE
 *	
 */
static void set_registerss()
{
	uint32_t cr3 = (uint32_t) pd;
	uint32_t cr0=0,cr4=0;
	asm volatile("movl %0, %%cr3"
				  :
				  :"r"(cr3)
				  : "memory" );		/*CR3 contains the base address of pde table*/ 


	asm volatile("movl %%cr4, %0"
				  :"=a"(cr4));		/*CR4 Contains flags that enable several architectural extensions*/
	cr4=cr4|CR4_VAL;
	asm volatile("movl %0, %%cr4"
				 :
				 :"r"(CR4_VAL)
				 :"memory");

	asm volatile("movl %%cr0, %0"
				 :"=a"(cr0));	/*CR0 Contains system control flags*/ 
	cr0=cr0|CR0_VAL;
	asm volatile("movl %0, %%cr0"
				 :
				 :"r"(CR0_VAL)
				 : "memory" );

}

/*  
 *  set_paging: this function is from page.h 
 *	 used as initialization 
 *	DESCRIPTION: USER_MODE paging and distribute memory location for different uses
 *  INPUT: None
 *  OUTPUT: None
 */
void set_paging()
{
	set_pd();
	set_pt();
	translation();
	set_registers();
}
