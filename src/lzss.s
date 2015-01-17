
	.intel_syntax noprefix
    .section .rodata
.LC0:
.asciz "%p\n%p"

    .text
    .global lzssDecompress
// void lzssDecompress(char *dest, void *src);
lzssDecompress:
    .equ v0, rax
    .equ a0, rcx
    .equ a1, rdx
    .equ a2, r8
    .equ a3, r9
    .equ pc, rip
    // rcx, rdx, r8, r9
    mov v0, rax
    //mov a0, .LC0
    lea ecx, .LC0[eip]
    lea a0, .LC0[rip]
    ret

// vim:ft=asm
