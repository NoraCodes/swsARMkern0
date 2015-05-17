/*kernel.c
	The main kernel program.

*/

#include "include/hardware.h"
#include "include/serialio.h"
#include "include/asm.h"
#include "include/kernel.h"
#include "include/tasks.h"
#include "include/memmgt.h"
#include <stddef.h>

//User mode program 3
void third(void) {
	kswrite("\tIn user mode for task 2; yeilding.\n");
	yeild();
	kswrite("\tIn user mode again for task 2; closing. \n");
	close();
}

//User mode program 2
void second(void) {
	kswrite("\tIn user mode for task 1; spawning task 2.\n");
	if(!fork()){third();}
	kswrite("\tTask 1 is yeilding.\n");
	yeild();
	kswrite("\tTask 1 is yeilding again.\n");
	yeild();
	kswrite("\tTask 1 is closing.\n");
	close();
}

//User mode program
void first(void) {
	kswrite("\tInit was run, spawning task 1.\n");
	if(!fork()){second();}
	kswrite("\tInit is yeilding.\n");
	yeild();
	kswrite("\tInit got control back, yeilding again.\n");
	yeild();
	kswrite("\tInit has control for a third time, closing.\n");
	close();
}

int main(void) {
	kswrite("Starting SWS ARM NewKern\n");
	/* Set up the user mode stacks*/
	unsigned int stacks[TASK_LIMIT][STACK_SIZE];
	unsigned int *tasks[TASK_LIMIT];
	size_t task_count = 0;
	size_t current_task = 0;
	kswrite("Kernel has allocated stack space.\n");

	/* Make a stack for the first task at &first */
	tasks[0] = init_task(stacks[0], &first);
	task_count++;
	
	/* Scheduling */
	kswrite("Going for scheduling.\n");
	while(1) {
		//Whatever we're doing, do it.
		tasks[current_task] = activate(tasks[current_task]);
		//We've been called by a syscall. We check r7 (which is the 7th thing in the stack 
		//after 2 other entries because the handler pushes them) to see which call it was,
		//and then figure out if we can service that call.
		switch(tasks[current_task][2+7]){
			case 0x0: //Yeild
				kswrite("User yeilded to the kernel.\n");
				break;

			case 0x1: //Fork
				kswrite("User wants to make a new process.\n");
				if(task_count == TASK_LIMIT){
					//Too bad, we're full. Error.
					tasks[current_task][2+0] = -1;
					kswrite("Failed to create a new process - out of task space.\n");
				} else {			
					/* Compute how much of the stack is used */
					size_t used = stacks[current_task] + STACK_SIZE - tasks[current_task];
					/* New stack is END - used */
					tasks[task_count] = stacks[task_count] + STACK_SIZE - used;
					/* Copy only the used part of the stack */
					memcpy(tasks[task_count], tasks[current_task], used*sizeof(*tasks[current_task]));
					/* Set return values in each process */
					tasks[current_task][2+0] = task_count;
					tasks[task_count][2+0] = 0;
					/* There is now one more task */
					task_count++;
				}
				break;
			case 0x2: //Close
				kswrite("User process says it's done.\n");
				if(task_count == 1){
					//Init is done, so we'll halt
					kswrite("All our processes are done, going to halt.\n");
					while(1);
				} else {			
					//Is this most recently created task?
					if(current_task == task_count - 1){
						//If so, this is trivial. One fewer tasks are being run.
						kswrite("User asked to terminate the latest process.\n");
						task_count--;
						break;
					} else {
						//If not, we have to copy all the other processes down
						kswrite("User asked to terminate a non-latest process.\n");
						unsigned int i = 0;
						for (i = current_task; i<task_count; i++){
							kswrite(" Moving a task down.\n");
							//How much is used by the process we're processing?
							size_t used = stacks[i] + STACK_SIZE - tasks[i];
							//Copy only the used part of the stack, down one
							memcpy(tasks[i - 1], tasks[i], used*sizeof(*tasks[i]));
						}
						//We've now freed the space, so reduce the number of tasks.
						task_count--;
					}
				}
				break;
			case 0x3: //Halt
				kswrite("Halting CPU.\n");
				while(1);
				break;
		}
		current_task++;
		if(current_task >= task_count){
			kswrite("Wrapping task number.\n");
			current_task = 0;
		}
	}


	kswrite("Halting.\n");
	while(1);
	return 0;
}
