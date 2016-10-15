/*
 * kb.h - support funciton for the keyboard 
 * Author:	    MacroSoft Yibo AND Hancheng
 * Version: 1
 *
 */

#ifndef KB__H
#define KB__H

#include "types.h"

#define KB_DATA_PORT 0x60
#define KB_IRQ_NUM	1
#define KB_ARRAY_NUM 55

/*Initialize the keyboard*/
extern void init_kb();

#endif /* KB__H */


