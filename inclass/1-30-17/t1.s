	.file	"t1.c"
	.text
	.globl	A
	.type	A, @function
A:
.LFB0:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	$4, -20(%ebp)
	movl	$5, -16(%ebp)
	movl	$6, -12(%ebp)
	subl	$8, %esp
	pushl	-16(%ebp)
	pushl	-20(%ebp)
	call	B
	addl	$16, %esp
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE0:
	.size	A, .-A
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
