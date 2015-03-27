
	.intel_syntax noprefix
    .section .rodata

    .equ v0, rax
    .equ a0, rcx
    .equ a1, rdx
    .equ a2, r8
    .equ a3, r9
    .equ t0, r10
    .equ t1, r11
    .equ s0, rbx
    .equ s1, rbp
    .equ s2, rdi
    .equ s3, rsi
    .equ s4, r12
    .equ s5, r13
    .equ s6, r14
    .equ s7, r15

    .text
    .global lzssDecompress
// void lzssDecompress(char *dest, void *src);
lzssDecompress:
    .equ dest,      rcx
    .equ src,       rdx
    .equ src_end,    r8

    push rbp
    mov rbp, rsp

    push rbx
    push rdi
    // rcx, rdx, r8, r9, r10, r11, rbx, rdi
    mov src_end, [src]
    shr src_end, 8
    add src_end, src

_loop:
    movb r9b, [src]
    mov r10, 0x80
    _loop_block:
        cmp dest, src_end
        je _loop_end
        cmp r10, 0
        je _loop
        mov rax, r10
        shr r10, 1
        test r9, r10
        jne _decode
        mov r11b, [src]
        inc src
        mov [dest], r11b
        inc dest
        jmp _loop_block

        _decode:
            mov r11b, [src]
            inc src
            mov bl, [src]
            inc src

            mov rax, r11
            shl rax, 8
            add rbx, rax
            shr r11, 4
            add r11, 3 # number of bytes to copy
            mov rax, 0xFFF
            and rbx, rax
            inc rbx
            // rsb rbx, dest // r6 = dest - r6 - 1
            mov rax, dest
            sub rax, rbx
            mov rbx, rax
            _lz_copy:
                mov al, [rbx]
                inc rbx
                mov [dest], al
                inc dest
                dec r11
                jne _lz_copy
                jmp _loop_block
_loop_end:

    pop rdi
    pop rbx

    pop rbp
    ret

// vim:ft=masm
