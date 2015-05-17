/*hardware.h
	Contains definitions for hardware quirks.
	Define, in the Makefile, HWCLASS= one of:
		versatilepb
*/

#ifndef _HARDWARE_H
#define _HARDWARE_H

#if HWCLASS == versatilepb
//VersatilePB virtual board

//Hardware devices
	#define UART0 *((volatile unsigned int*)0x101f1000)


#endif /*HWCLASS == versatilepb*/


#endif
