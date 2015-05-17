/*serialio.c
	Serial I/O library.
*/

#include "include/hardware.h"
#include "include/serialio.h"

//Check that we're in a sane place to do serial I/O - do we have a serial port?
#ifndef UART0
#error "No UART0! Serial I/O doesn't make any sense."
#endif

void kswrite(char* string)
{
	while(*string != '\0') { //Until we encounter the null char, pump it out the serial I/O
		UART0 = *string;
		string++;
	}
	return;
}
