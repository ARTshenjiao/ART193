 
/*
 * paging_cp1.h - this header file is for paging initialization
 * Author:	    guo
 * Version: 1
 *
 */
#ifndef PAGING_H
#define PAGING_H

#include "types.h"

#define DIRECTORY_SIZE 1024
#define TABLE_SIZE 1024
#define FOUR_KB 0x1000			// different page size 
#define FOUR_MB 0x400000
//// kernal start address
#define KERNEL_ADDRESS 0x400000 

#define VIDEO_MEMORY 0xB8

///////// set up control registers 
#define CR3_VALUE 0x00000000	// use to hold the base address of the page directory register 
#define CR0_VALUE 0x80000001	// CR0: SET the high bit to 1：enable paging, SET low bit to 1: in protected mode 
#define CR4_VALUE 0x00000010	// SET up the bit in CR4 to enable page size extension 
///////// for translation modes 
#define USER_MODE 0
#define KERNEL_MODE 1 




#ifndef ASM

/*refer to INTEL manual p90*/
typedef struct page_directory_entry
{
	union{
		uint32_t page_value;				// used to directly load values 
		struct{
			uint8_t P : 1;
			uint8_t R_W : 1;
			uint8_t U_S : 1;
			uint8_t PWT : 1;
			uint8_t PCD : 1;
			uint8_t A : 1;
			uint8_t zero : 1;
			uint8_t PS : 1;
			uint8_t G : 1;
			uint8_t avail : 3;
			uint32_t pt_base_address : 20;
		}__attribute__((packed));
	};
}page_directory_entry;

typedef struct page_table_entry
{
	union
	{
		uint32_t page_value;		// used to directly load values 
		struct 
		{
			uint8_t P : 1;
			uint8_t R_W : 1;
			uint8_t U_S : 1;
			uint8_t PWT : 1;
			uint8_t PCD : 1;
			uint8_t A : 1;
			uint8_t D : 1;
			uint8_t PAT : 1;
			uint8_t G : 1;
			uint8_t avail : 3;
			uint32_t page_base_address : 20;
		} __attribute__((packed));
	};
}page_table_entry; 

page_directory_entry pd[DIRECTORY_SIZE] __attribute__((aligned(4096)));			// 4 kb align 
page_table_entry pt[TABLE_SIZE] __attribute__((aligned(4096)));


#endif /*ASM*/

extern void set_paging();

#endif /* PAGING_H */

