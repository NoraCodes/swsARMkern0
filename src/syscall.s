.global yeild
yeild:
	push {r7}
	mov r7, #0x0
	svc 0
	pop {r7}
	bx lr

.global fork
fork:
	push {r7}
	mov r7, #0x1
	svc 0
	pop {r7}
	bx lr

.global close
close:
	push {r7}
	mov r7, #0x2
	svc 0
	pop {r7}
	bx lr

.global halt
halt:
	push {r7}
	mov r7, #0x3
	svc 0
	pop {r7}
	bx lr
