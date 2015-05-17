SWS ARMKern
------

###Directories

`src/` - source files.
	`bootstrap.s` - Assembly for setting up the environment for the kernel
	`context-switch.s` - Switch to user mode
	`serialio.c` - Serial I/O library
	`kernel.c` - Kernel main
	`tasks.c` - Tasking functions
	`memmgt.c` - Memory management
	`syscall.s` - Syscalls
	`include/` - Headers
		`hardware.h` - Hardware quirks
		`serialio.h` - Serial I/O library header
		`asm.h` - Use assembly functions in C
		`kernel.h` - kernel #defines
		`tasks.h` - Multitasking header
		`memmgt.h` - Memory management header
`isosrc/` - ISO image building files
`obj/` - *.o files
`elf/` - *.elf files, the final stage of compilation
