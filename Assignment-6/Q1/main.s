	.file	"main.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"password is %s\n"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"password is stored at address 0x%lx\n"
	.text
	.p2align 4
	.globl	isPasswordOK
	.type	isPasswordOK, @function
isPasswordOK:
.LFB50:
	.cfi_startproc
	endbr64
	movabsq	$8319100072032694119, %rax
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	subq	$32, %rsp
	.cfi_def_cfa_offset 48
	leaq	23(%rsp), %rbp
	movq	%rax, 14(%rsp)
	xorl	%eax, %eax
	movq	%rbp, %rdi
	movb	$0, 22(%rsp)
	call	gets@PLT
	movq	%rbp, %rdx
	movl	$1, %edi
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rsi
	call	__printf_chk@PLT
	movq	%rbp, %rdx
	movl	$1, %edi
	xorl	%eax, %eax
	leaq	.LC1(%rip), %rsi
	call	__printf_chk@PLT
	leaq	14(%rsp), %rsi
	movq	%rbp, %rdi
	call	strcmp@PLT
	testl	%eax, %eax
	sete	%al
	addq	$32, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE50:
	.size	isPasswordOK, .-isPasswordOK
	.section	.rodata.str1.1
.LC2:
	.string	"Enter Password:"
.LC3:
	.string	"Access granted"
.LC4:
	.string	"Access denied"
	.section	.text.startup,"ax",@progbits
	.p2align 4
	.globl	main
	.type	main, @function
main:
.LFB51:
	.cfi_startproc
	endbr64
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	xorl	%eax, %eax
	call	isPasswordOK
	testb	%al, %al
	je	.L5
	leaq	.LC3(%rip), %rdi
	call	puts@PLT
	xorl	%eax, %eax
.L4:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L5:
	.cfi_restore_state
	leaq	.LC4(%rip), %rdi
	call	puts@PLT
	movl	$1, %eax
	jmp	.L4
	.cfi_endproc
.LFE51:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
