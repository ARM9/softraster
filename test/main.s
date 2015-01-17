	.file	"b.c"
	.intel_syntax noprefix
	.text
	.globl	f
	.def	f;	.scl	2;	.type	32;	.endef
	.seh_proc	f
f:
	.seh_endprologue
/APP
 # 6 "b.c" 1
	mov rcx, 'a'; jmp putchar;

 # 0 "" 2
/NO_APP
	ret
	.seh_endproc
	.def	__main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
.LC0:
	.ascii "\12%d\12%d\0"
	.text
	.globl	main
	.def	main;	.scl	2;	.type	32;	.endef
	.seh_proc	main
main:
	sub	rsp, 40
	.seh_stackalloc	40
	.seh_endprologue
	call	__main
	call	f
	mov	r8d, 2
	mov	edx, 1
	lea	rcx, .LC0[rip]
	call	printf
	mov	eax, 0
	add	rsp, 40
	ret
	.seh_endproc
	.ident	"GCC: (x86_64-win32-seh-rev2, Built by MinGW-W64 project) 4.9.0"
	.def	printf;	.scl	2;	.type	32;	.endef
