	.file	"a2.c"
	.comm	readyqueue,4,4
	.globl	HEXTABLE
	.section	.rodata
.LC0:
	.string	"0123456789BCDEF"
	.data
	.align 4
	.type	HEXTABLE, @object
	.size	HEXTABLE, 4
HEXTABLE:
	.long	.LC0
	.section	.rodata
	.align 4
.LC1:
	.string	"\n\nAUTHOR:CONNOR WOOL | ID# 11253438\n"
	.text
	.globl	printCredits
	.type	printCredits, @function
printCredits:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	subl	$12, %esp
	pushl	$.LC1
	call	myprintf
	addl	$16, %esp
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	printCredits, .-printCredits
	.globl	rprintbase
	.type	rprintbase, @function
rprintbase:
.LFB3:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$20, %esp
	.cfi_offset 3, -12
	cmpl	$0, 8(%ebp)
	je	.L5
	movl	HEXTABLE, %ecx
	movl	12(%ebp), %ebx
	movl	8(%ebp), %eax
	movl	$0, %edx
	divl	%ebx
	movl	%edx, %eax
	addl	%ecx, %eax
	movzbl	(%eax), %eax
	movb	%al, -9(%ebp)
	movl	12(%ebp), %ecx
	movl	8(%ebp), %eax
	movl	$0, %edx
	divl	%ecx
	subl	$8, %esp
	pushl	12(%ebp)
	pushl	%eax
	call	rprintbase
	addl	$16, %esp
	movsbl	-9(%ebp), %eax
	subl	$12, %esp
	pushl	%eax
	call	putchar
	addl	$16, %esp
	jmp	.L2
.L5:
	nop
.L2:
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	rprintbase, .-rprintbase
	.globl	printx
	.type	printx, @function
printx:
.LFB4:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	cmpl	$0, 8(%ebp)
	jne	.L7
	subl	$12, %esp
	pushl	$48
	call	putchar
	addl	$16, %esp
	jmp	.L6
.L7:
	subl	$8, %esp
	pushl	$16
	pushl	8(%ebp)
	call	rprintbase
	addl	$16, %esp
.L6:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE4:
	.size	printx, .-printx
	.globl	printo
	.type	printo, @function
printo:
.LFB5:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	cmpl	$0, 8(%ebp)
	jne	.L10
	subl	$12, %esp
	pushl	$48
	call	putchar
	addl	$16, %esp
	jmp	.L9
.L10:
	subl	$8, %esp
	pushl	$8
	pushl	8(%ebp)
	call	rprintbase
	addl	$16, %esp
.L9:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE5:
	.size	printo, .-printo
	.globl	printd
	.type	printd, @function
printd:
.LFB6:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	cmpl	$0, 8(%ebp)
	jne	.L13
	subl	$12, %esp
	pushl	$48
	call	putchar
	addl	$16, %esp
	jmp	.L12
.L13:
	cmpl	$0, 8(%ebp)
	jns	.L15
	subl	$12, %esp
	pushl	$45
	call	putchar
	addl	$16, %esp
	movl	8(%ebp), %eax
	negl	%eax
	subl	$8, %esp
	pushl	$10
	pushl	%eax
	call	rprintbase
	addl	$16, %esp
	jmp	.L12
.L15:
	movl	8(%ebp), %eax
	subl	$8, %esp
	pushl	$10
	pushl	%eax
	call	rprintbase
	addl	$16, %esp
.L12:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE6:
	.size	printd, .-printd
	.globl	printu
	.type	printu, @function
printu:
.LFB7:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	cmpl	$0, 8(%ebp)
	jne	.L17
	subl	$12, %esp
	pushl	$48
	call	putchar
	addl	$16, %esp
	jmp	.L16
.L17:
	subl	$8, %esp
	pushl	$10
	pushl	8(%ebp)
	call	rprintbase
	addl	$16, %esp
.L16:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE7:
	.size	printu, .-printu
	.globl	prints
	.type	prints, @function
prints:
.LFB8:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	jmp	.L20
.L21:
	movl	8(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, 8(%ebp)
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	subl	$12, %esp
	pushl	%eax
	call	putchar
	addl	$16, %esp
.L20:
	movl	8(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	.L21
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE8:
	.size	prints, .-prints
	.globl	myprintf
	.type	myprintf, @function
myprintf:
.LFB9:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, -16(%ebp)
	leal	12(%ebp), %eax
	movl	%eax, -12(%ebp)
	jmp	.L23
.L31:
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$37, %al
	jne	.L24
	addl	$1, -16(%ebp)
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$117, %al
	jne	.L25
	movl	-12(%ebp), %eax
	leal	4(%eax), %edx
	movl	%edx, -12(%ebp)
	movl	(%eax), %eax
	subl	$12, %esp
	pushl	%eax
	call	printu
	addl	$16, %esp
	jmp	.L26
.L25:
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$100, %al
	jne	.L27
	movl	-12(%ebp), %eax
	leal	4(%eax), %edx
	movl	%edx, -12(%ebp)
	movl	(%eax), %eax
	subl	$12, %esp
	pushl	%eax
	call	printd
	addl	$16, %esp
	jmp	.L26
.L27:
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$99, %al
	jne	.L28
	movl	-12(%ebp), %eax
	leal	4(%eax), %edx
	movl	%edx, -12(%ebp)
	movl	(%eax), %eax
	subl	$12, %esp
	pushl	%eax
	call	putchar
	addl	$16, %esp
	jmp	.L26
.L28:
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$115, %al
	jne	.L29
	movl	-12(%ebp), %eax
	leal	4(%eax), %edx
	movl	%edx, -12(%ebp)
	movl	(%eax), %eax
	subl	$12, %esp
	pushl	%eax
	call	prints
	addl	$16, %esp
	jmp	.L26
.L29:
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$111, %al
	jne	.L30
	movl	-12(%ebp), %eax
	leal	4(%eax), %edx
	movl	%edx, -12(%ebp)
	movl	(%eax), %eax
	subl	$12, %esp
	pushl	%eax
	call	printo
	addl	$16, %esp
	jmp	.L26
.L30:
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	cmpb	$120, %al
	jne	.L26
	movl	-12(%ebp), %eax
	leal	4(%eax), %edx
	movl	%edx, -12(%ebp)
	movl	(%eax), %eax
	subl	$12, %esp
	pushl	%eax
	call	printx
	addl	$16, %esp
.L26:
	addl	$1, -16(%ebp)
	jmp	.L23
.L24:
	movl	-16(%ebp), %eax
	leal	1(%eax), %edx
	movl	%edx, -16(%ebp)
	movzbl	(%eax), %eax
	movsbl	%al, %eax
	subl	$12, %esp
	pushl	%eax
	call	putchar
	addl	$16, %esp
.L23:
	movl	-16(%ebp), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	.L31
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE9:
	.size	myprintf, .-myprintf
	.section	.rodata
.LC2:
	.string	"node%d"
	.text
	.globl	makenode
	.type	makenode, @function
makenode:
.LFB10:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	subl	$12, %esp
	pushl	$72
	call	malloc
	addl	$16, %esp
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	movl	$0, (%eax)
	call	rand
	movl	%eax, %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	movl	-12(%ebp), %eax
	movl	%edx, 68(%eax)
	movl	-12(%ebp), %eax
	addl	$4, %eax
	subl	$4, %esp
	pushl	8(%ebp)
	pushl	$.LC2
	pushl	%eax
	call	sprintf
	addl	$16, %esp
	movl	-12(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE10:
	.size	makenode, .-makenode
	.globl	enqueue
	.type	enqueue, @function
enqueue:
.LFB11:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	jne	.L35
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, (%eax)
	jmp	.L42
.L35:
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	12(%ebp), %eax
	movl	68(%eax), %edx
	movl	-8(%ebp), %eax
	movl	68(%eax), %eax
	cmpl	%eax, %edx
	jle	.L38
	movl	8(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, (%eax)
	movl	12(%ebp), %eax
	movl	-8(%ebp), %edx
	movl	%edx, (%eax)
	jmp	.L42
.L40:
	movl	-8(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	-8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -8(%ebp)
.L38:
	cmpl	$0, -8(%ebp)
	je	.L39
	movl	12(%ebp), %eax
	movl	68(%eax), %edx
	movl	-8(%ebp), %eax
	movl	68(%eax), %eax
	cmpl	%eax, %edx
	jle	.L40
.L39:
	movl	-4(%ebp), %eax
	movl	12(%ebp), %edx
	movl	%edx, (%eax)
	cmpl	$0, -8(%ebp)
	je	.L41
	movl	12(%ebp), %eax
	movl	-8(%ebp), %edx
	movl	%edx, (%eax)
	jmp	.L42
.L41:
	movl	12(%ebp), %eax
	movl	$0, (%eax)
.L42:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE11:
	.size	enqueue, .-enqueue
	.globl	dequeue
	.type	dequeue, @function
dequeue:
.LFB12:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -4(%ebp)
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	je	.L44
	movl	-4(%ebp), %eax
	movl	(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
.L44:
	movl	-4(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE12:
	.size	dequeue, .-dequeue
	.section	.rodata
.LC3:
	.string	"\n(PQ) Start queue print\n"
.LC4:
	.string	"(PQ)  Start  address [%x]\n"
.LC5:
	.string	"(PQ) Current address [%x] --\t"
.LC6:
	.string	"[name: %s\tpri:%d] nxt(%x)->\n"
.LC7:
	.string	"(PQ) Finish queue print\n\n"
	.text
	.globl	printqueue
	.type	printqueue, @function
printqueue:
.LFB13:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	8(%ebp), %eax
	movl	%eax, -12(%ebp)
	subl	$12, %esp
	pushl	$.LC3
	call	myprintf
	addl	$16, %esp
	subl	$8, %esp
	pushl	-12(%ebp)
	pushl	$.LC4
	call	myprintf
	addl	$16, %esp
	jmp	.L47
.L48:
	subl	$8, %esp
	pushl	-12(%ebp)
	pushl	$.LC5
	call	myprintf
	addl	$16, %esp
	movl	-12(%ebp), %eax
	movl	(%eax), %edx
	movl	-12(%ebp), %eax
	movl	68(%eax), %eax
	movl	-12(%ebp), %ecx
	addl	$4, %ecx
	pushl	%edx
	pushl	%eax
	pushl	%ecx
	pushl	$.LC6
	call	myprintf
	addl	$16, %esp
	movl	-12(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, -12(%ebp)
.L47:
	cmpl	$0, -12(%ebp)
	jne	.L48
	subl	$12, %esp
	pushl	$.LC7
	call	myprintf
	addl	$16, %esp
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE13:
	.size	printqueue, .-printqueue
	.section	.rodata
	.align 4
.LC8:
	.string	"\n\n--------BEGIN SECTION 1--------\n"
.LC9:
	.string	"--------ARGC--------\n"
.LC10:
	.string	"argc: %d\n"
.LC11:
	.string	"--------ARGV--------\n"
.LC12:
	.string	"argv%d: %s\n"
.LC13:
	.string	"--------ENV--------\n"
.LC14:
	.string	"env%d: %s\n"
	.align 4
.LC15:
	.string	"\n\n--------SECTION 1 COMPLETE--------\n"
	.align 4
.LC16:
	.string	"--------BEGIN NODE QUEUE SECTION--------\n"
	.align 4
.LC17:
	.string	"----Max priority value set to %d----\n"
	.align 4
.LC18:
	.string	"Press any key to generate next node!\n"
.LC19:
	.string	"Press ^C to exit.\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB14:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ebx
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x78,0x6
	.cfi_escape 0x10,0x3,0x2,0x75,0x7c
	subl	$16, %esp
	movl	%ecx, %ebx
	call	printCredits
	subl	$12, %esp
	pushl	$.LC8
	call	myprintf
	addl	$16, %esp
	subl	$12, %esp
	pushl	$.LC9
	call	myprintf
	addl	$16, %esp
	subl	$8, %esp
	pushl	(%ebx)
	pushl	$.LC10
	call	myprintf
	addl	$16, %esp
	subl	$12, %esp
	pushl	$.LC11
	call	myprintf
	addl	$16, %esp
	movl	$0, -16(%ebp)
	jmp	.L50
.L51:
	movl	-16(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	4(%ebx), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	subl	$4, %esp
	pushl	%eax
	pushl	-16(%ebp)
	pushl	$.LC12
	call	myprintf
	addl	$16, %esp
	addl	$1, -16(%ebp)
.L50:
	movl	-16(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	4(%ebx), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	jne	.L51
	subl	$12, %esp
	pushl	$.LC13
	call	myprintf
	addl	$16, %esp
	movl	$0, -16(%ebp)
	jmp	.L52
.L53:
	movl	-16(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebx), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	subl	$4, %esp
	pushl	%eax
	pushl	-16(%ebp)
	pushl	$.LC14
	call	myprintf
	addl	$16, %esp
	addl	$1, -16(%ebp)
.L52:
	movl	-16(%ebp), %eax
	leal	0(,%eax,4), %edx
	movl	8(%ebx), %eax
	addl	%edx, %eax
	movl	(%eax), %eax
	testl	%eax, %eax
	jne	.L53
	subl	$12, %esp
	pushl	$.LC15
	call	myprintf
	addl	$16, %esp
	subl	$12, %esp
	pushl	$.LC16
	call	myprintf
	addl	$16, %esp
	subl	$8, %esp
	pushl	$10
	pushl	$.LC17
	call	myprintf
	addl	$16, %esp
	movl	$0, -12(%ebp)
.L54:
	subl	$12, %esp
	pushl	-12(%ebp)
	call	makenode
	addl	$16, %esp
	subl	$8, %esp
	pushl	%eax
	pushl	$readyqueue
	call	enqueue
	addl	$16, %esp
	movl	readyqueue, %eax
	subl	$12, %esp
	pushl	%eax
	call	printqueue
	addl	$16, %esp
	addl	$1, -12(%ebp)
	subl	$12, %esp
	pushl	$.LC18
	call	myprintf
	addl	$16, %esp
	subl	$12, %esp
	pushl	$.LC19
	call	myprintf
	addl	$16, %esp
	call	getchar
	movb	%al, -17(%ebp)
	jmp	.L54
	.cfi_endproc
.LFE14:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
