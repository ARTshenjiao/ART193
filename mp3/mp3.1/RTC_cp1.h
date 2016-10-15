/*
 * RTC_cp1.h - support funciton for RTC 
 * Author:	    guo 
 * Version: 1
 *
 */

#ifndef RTC_H
#define RTC_H

#include "types.h"

#define RA 0x0A				// stand for register A,B,C 
#define RB 0x0B
#define RC 0x0C

#define CMD_P 0x70			// stand for RTC CMD PORT 
#define DATA_P 0x71 

#define PIE_BIT       0x40
#define RTC_IRQ_NUMBER  	8 

/////////////////////////  set up the RTC to 2HZ, correponding to 15 in R3-R0 
extern void set_rtc();
#endif /* RTC_H */







