//Allows us to go into a loop of NOPing.

.global halt
halt:
	nop
	ldr r0, =halt
	movs pc, r0
