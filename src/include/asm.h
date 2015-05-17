/*asm.h
	For calling assembly functions from C.
*/
#ifndef _ASM_H
#define _ASM_H

unsigned int* activate(unsigned int*);

//Syscalls, in order/
void yeild(void); 	//Yeild
int fork(void);		//Fork
void close(void);
void halt(void);	//Halt the kernel

#endif
