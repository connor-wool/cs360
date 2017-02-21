	.file	"mysh2.c"
	.comm	path_tokens,256,32
	.globl	sleepy
	.section	.rodata
.LC0:
	.string	" (-.-) Zzz..."
	.data
	.align 4
	.type	sleepy, @object
	.size	sleepy, 4
sleepy:
	.long	.LC0
	.globl	work_msg
	.section	.rodata
.LC1:
	.string	"\341\225\246(\303\262_\303\263\313\207)\341\225\244"
	.data
	.align 4
	.type	work_msg, @object
	.size	work_msg, 4
work_msg:
	.long	.LC1
	.globl	i_die
	.section	.rodata
.LC2:
	.string	"\\(X_X)/"
	.data
	.align 4
	.type	i_die, @object
	.size	i_die, 4
i_die:
	.long	.LC2
	.text
	.globl	nprintc
	.type	nprintc, @function
nprintc:
.LFB2:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$40, %esp
	movl	8(%ebp), %eax
	movb	%al, -28(%ebp)
	movl	$0, -12(%ebp)
	jmp	.L2
.L3:
	movsbl	-28(%ebp), %eax
	subl	$12, %esp
	pushl	%eax
	call	putchar
	addl	$16, %esp
	addl	$1, -12(%ebp)
.L2:
	movl	-12(%ebp), %eax
	cmpl	12(%ebp), %eax
	jl	.L3
	cmpl	$0, 16(%ebp)
	je	.L5
	subl	$12, %esp
	pushl	$10
	call	putchar
	addl	$16, %esp
.L5:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE2:
	.size	nprintc, .-nprintc
	.globl	makestring
	.type	makestring, @function
makestring:
.LFB3:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	subl	$12, %esp
	pushl	8(%ebp)
	call	strlen
	addl	$16, %esp
	movl	%eax, -16(%ebp)
	movl	-16(%ebp), %eax
	addl	$1, %eax
	subl	$12, %esp
	pushl	%eax
	call	malloc
	addl	$16, %esp
	movl	%eax, -12(%ebp)
	subl	$8, %esp
	pushl	8(%ebp)
	pushl	-12(%ebp)
	call	strcpy
	addl	$16, %esp
	movl	-12(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE3:
	.size	makestring, .-makestring
	.section	.rodata
.LC3:
	.string	"--> Tokenize path string"
.LC4:
	.string	"PATH"
.LC5:
	.string	":"
	.text
	.globl	tok_paths
	.type	tok_paths, @function
tok_paths:
.LFB4:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%ebx
	subl	$276, %esp
	.cfi_offset 3, -12
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	subl	$12, %esp
	pushl	$.LC3
	call	puts
	addl	$16, %esp
	movl	$0, -272(%ebp)
	subl	$12, %esp
	pushl	$.LC4
	call	getenv
	addl	$16, %esp
	subl	$8, %esp
	pushl	%eax
	leal	-268(%ebp), %eax
	pushl	%eax
	call	strcpy
	addl	$16, %esp
	subl	$8, %esp
	pushl	$.LC5
	leal	-268(%ebp), %eax
	pushl	%eax
	call	strtok
	addl	$16, %esp
	movl	%eax, -276(%ebp)
	jmp	.L9
.L10:
	movl	-272(%ebp), %ebx
	leal	1(%ebx), %eax
	movl	%eax, -272(%ebp)
	subl	$12, %esp
	pushl	-276(%ebp)
	call	makestring
	addl	$16, %esp
	movl	%eax, path_tokens(,%ebx,4)
	subl	$8, %esp
	pushl	$.LC5
	pushl	$0
	call	strtok
	addl	$16, %esp
	movl	%eax, -276(%ebp)
.L9:
	cmpl	$0, -276(%ebp)
	jne	.L10
	movl	-272(%ebp), %eax
	movl	$0, path_tokens(,%eax,4)
	nop
	movl	-12(%ebp), %edx
	xorl	%gs:20, %edx
	je	.L11
	call	__stack_chk_fail
.L11:
	movl	-4(%ebp), %ebx
	leave
	.cfi_restore 5
	.cfi_restore 3
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE4:
	.size	tok_paths, .-tok_paths
	.section	.rodata
.LC6:
	.string	"\t\tCONNOR'S COOL SHELL V.2"
.LC7:
	.string	"--> Running init process..."
.LC8:
	.string	"--> Init process finished."
	.text
	.globl	init
	.type	init, @function
init:
.LFB5:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	subl	$4, %esp
	pushl	$1
	pushl	$50
	pushl	$61
	call	nprintc
	addl	$16, %esp
	subl	$12, %esp
	pushl	$.LC6
	call	puts
	addl	$16, %esp
	subl	$4, %esp
	pushl	$1
	pushl	$50
	pushl	$61
	call	nprintc
	addl	$16, %esp
	subl	$12, %esp
	pushl	$.LC7
	call	puts
	addl	$16, %esp
	call	tok_paths
	subl	$12, %esp
	pushl	$.LC8
	call	puts
	addl	$16, %esp
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE5:
	.size	init, .-init
	.section	.rodata
.LC9:
	.string	"%s:%s$ "
	.text
	.globl	get_input
	.type	get_input, @function
get_input:
.LFB6:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$792, %esp
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	subl	$8, %esp
	pushl	$256
	leal	-780(%ebp), %eax
	pushl	%eax
	call	getcwd
	addl	$16, %esp
	subl	$8, %esp
	pushl	$256
	leal	-524(%ebp), %eax
	pushl	%eax
	call	gethostname
	addl	$16, %esp
	subl	$4, %esp
	leal	-780(%ebp), %eax
	pushl	%eax
	leal	-524(%ebp), %eax
	pushl	%eax
	pushl	$.LC9
	call	printf
	addl	$16, %esp
	movl	stdin, %eax
	subl	$4, %esp
	pushl	%eax
	pushl	$256
	leal	-268(%ebp), %eax
	pushl	%eax
	call	fgets
	addl	$16, %esp
	subl	$12, %esp
	leal	-268(%ebp), %eax
	pushl	%eax
	call	strlen
	addl	$16, %esp
	subl	$1, %eax
	movb	$0, -268(%ebp,%eax)
	subl	$12, %esp
	leal	-268(%ebp), %eax
	pushl	%eax
	call	makestring
	addl	$16, %esp
	movl	-12(%ebp), %edx
	xorl	%gs:20, %edx
	je	.L15
	call	__stack_chk_fail
.L15:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE6:
	.size	get_input, .-get_input
	.section	.rodata
.LC10:
	.string	" "
	.text
	.globl	process_string
	.type	process_string, @function
process_string:
.LFB7:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	subl	$12, %esp
	pushl	$260
	call	malloc
	addl	$16, %esp
	movl	%eax, -16(%ebp)
	subl	$12, %esp
	pushl	8(%ebp)
	call	makestring
	addl	$16, %esp
	movl	%eax, -12(%ebp)
	movl	$0, -24(%ebp)
	movl	-16(%ebp), %eax
	movl	$0, (%eax)
	subl	$8, %esp
	pushl	$.LC10
	pushl	-12(%ebp)
	call	strtok
	addl	$16, %esp
	movl	%eax, -20(%ebp)
	jmp	.L17
.L18:
	subl	$12, %esp
	pushl	-20(%ebp)
	call	makestring
	addl	$16, %esp
	movl	%eax, %ecx
	movl	-16(%ebp), %eax
	movl	-24(%ebp), %edx
	movl	%ecx, 4(%eax,%edx,4)
	subl	$8, %esp
	pushl	$.LC10
	pushl	$0
	call	strtok
	addl	$16, %esp
	movl	%eax, -20(%ebp)
	addl	$1, -24(%ebp)
	movl	-16(%ebp), %eax
	movl	-24(%ebp), %edx
	movl	%edx, (%eax)
.L17:
	cmpl	$0, -20(%ebp)
	jne	.L18
	movl	-16(%ebp), %eax
	movl	-24(%ebp), %edx
	movl	$0, 4(%eax,%edx,4)
	movl	-16(%ebp), %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE7:
	.size	process_string, .-process_string
	.section	.rodata
.LC11:
	.string	"cd"
.LC12:
	.string	"HOME"
	.text
	.globl	check_cd
	.type	check_cd, @function
check_cd:
.LFB8:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	subl	$8, %esp
	pushl	$.LC11
	pushl	%eax
	call	strcmp
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L21
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	$1, %eax
	jle	.L22
	movl	8(%ebp), %eax
	movl	8(%eax), %eax
	subl	$12, %esp
	pushl	%eax
	call	chdir
	addl	$16, %esp
	jmp	.L23
.L22:
	subl	$12, %esp
	pushl	$.LC12
	call	getenv
	addl	$16, %esp
	subl	$12, %esp
	pushl	%eax
	call	chdir
	addl	$16, %esp
.L23:
	movl	$1, %eax
	jmp	.L24
.L21:
	movl	$0, %eax
.L24:
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE8:
	.size	check_cd, .-check_cd
	.section	.rodata
.LC13:
	.string	"exit"
	.text
	.globl	check_exit
	.type	check_exit, @function
check_exit:
.LFB9:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$8, %esp
	movl	8(%ebp), %eax
	movl	4(%eax), %eax
	subl	$8, %esp
	pushl	$.LC13
	pushl	%eax
	call	strcmp
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L26
	subl	$12, %esp
	pushl	$0
	call	exit
.L26:
	movl	$0, %eax
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE9:
	.size	check_exit, .-check_exit
	.section	.rodata
.LC14:
	.string	"<"
.LC15:
	.string	">"
.LC16:
	.string	">>"
.LC17:
	.string	"r"
.LC18:
	.string	"w"
.LC19:
	.string	"a"
	.text
	.globl	redirect_io
	.type	redirect_io, @function
redirect_io:
.LFB10:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	subl	$24, %esp
	movl	$0, -20(%ebp)
	movl	$0, -16(%ebp)
	movl	$0, -12(%ebp)
	jmp	.L29
.L33:
	movl	8(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	4(%eax,%edx,4), %eax
	subl	$8, %esp
	pushl	$.LC14
	pushl	%eax
	call	strcmp
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L30
	movl	-12(%ebp), %eax
	movl	%eax, -20(%ebp)
.L30:
	movl	8(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	4(%eax,%edx,4), %eax
	subl	$8, %esp
	pushl	$.LC15
	pushl	%eax
	call	strcmp
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L31
	movl	-12(%ebp), %eax
	movl	%eax, -16(%ebp)
.L31:
	movl	8(%ebp), %eax
	movl	-12(%ebp), %edx
	movl	4(%eax,%edx,4), %eax
	subl	$8, %esp
	pushl	$.LC16
	pushl	%eax
	call	strcmp
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L32
	movl	-12(%ebp), %eax
	movl	%eax, -16(%ebp)
.L32:
	addl	$1, -12(%ebp)
.L29:
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	cmpl	-12(%ebp), %eax
	jg	.L33
	cmpl	$0, -20(%ebp)
	jle	.L34
	subl	$12, %esp
	pushl	$0
	call	close
	addl	$16, %esp
	movl	-20(%ebp), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	4(%eax,%edx,4), %eax
	subl	$8, %esp
	pushl	$.LC17
	pushl	%eax
	call	fopen
	addl	$16, %esp
.L34:
	cmpl	$0, -16(%ebp)
	jle	.L35
	subl	$12, %esp
	pushl	$1
	call	close
	addl	$16, %esp
	movl	8(%ebp), %eax
	movl	-16(%ebp), %edx
	movl	4(%eax,%edx,4), %eax
	subl	$8, %esp
	pushl	$.LC15
	pushl	%eax
	call	strcmp
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L36
	movl	-16(%ebp), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	4(%eax,%edx,4), %eax
	subl	$8, %esp
	pushl	$.LC18
	pushl	%eax
	call	fopen
	addl	$16, %esp
	jmp	.L35
.L36:
	movl	-16(%ebp), %eax
	leal	1(%eax), %edx
	movl	8(%ebp), %eax
	movl	4(%eax,%edx,4), %eax
	subl	$8, %esp
	pushl	$.LC19
	pushl	%eax
	call	fopen
	addl	$16, %esp
.L35:
	nop
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE10:
	.size	redirect_io, .-redirect_io
	.section	.rodata
.LC20:
	.string	"no command `%s` found\n"
	.text
	.globl	handle_fork
	.type	handle_fork, @function
handle_fork:
.LFB11:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	pushl	%edi
	subl	$292, %esp
	.cfi_offset 7, -12
	movl	8(%ebp), %eax
	movl	%eax, -284(%ebp)
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	call	fork
	movl	%eax, -272(%ebp)
	cmpl	$0, -272(%ebp)
	je	.L38
	leal	-280(%ebp), %eax
	subl	$12, %esp
	pushl	%eax
	call	wait
	addl	$16, %esp
	movl	-12(%ebp), %edi
	xorl	%gs:20, %edi
	je	.L44
	jmp	.L45
.L38:
	subl	$12, %esp
	pushl	-284(%ebp)
	call	redirect_io
	addl	$16, %esp
	movb	$0, -268(%ebp)
	movl	path_tokens, %eax
	subl	$8, %esp
	pushl	%eax
	leal	-268(%ebp), %eax
	pushl	%eax
	call	strcat
	addl	$16, %esp
	subl	$12, %esp
	leal	-268(%ebp), %eax
	pushl	%eax
	call	strlen
	addl	$16, %esp
	subl	$1, %eax
	movzbl	-268(%ebp,%eax), %eax
	cmpb	$47, %al
	je	.L39
	leal	-268(%ebp), %eax
	movl	$-1, %ecx
	movl	%eax, %edx
	movl	$0, %eax
	movl	%edx, %edi
	repnz scasb
	movl	%ecx, %eax
	notl	%eax
	leal	-1(%eax), %edx
	leal	-268(%ebp), %eax
	addl	%edx, %eax
	movw	$47, (%eax)
.L39:
	movl	-284(%ebp), %eax
	movl	4(%eax), %eax
	subl	$8, %esp
	pushl	%eax
	leal	-268(%ebp), %eax
	pushl	%eax
	call	strcat
	addl	$16, %esp
	movl	$0, -276(%ebp)
	jmp	.L40
.L43:
	addl	$1, -276(%ebp)
	subl	$4, %esp
	pushl	$256
	pushl	$0
	leal	-268(%ebp), %eax
	pushl	%eax
	call	memset
	addl	$16, %esp
	movl	-276(%ebp), %eax
	movl	path_tokens(,%eax,4), %eax
	subl	$8, %esp
	pushl	%eax
	leal	-268(%ebp), %eax
	pushl	%eax
	call	strcat
	addl	$16, %esp
	subl	$12, %esp
	leal	-268(%ebp), %eax
	pushl	%eax
	call	strlen
	addl	$16, %esp
	subl	$1, %eax
	movzbl	-268(%ebp,%eax), %eax
	cmpb	$47, %al
	je	.L41
	leal	-268(%ebp), %eax
	movl	$-1, %ecx
	movl	%eax, %edx
	movl	$0, %eax
	movl	%edx, %edi
	repnz scasb
	movl	%ecx, %eax
	notl	%eax
	leal	-1(%eax), %edx
	leal	-268(%ebp), %eax
	addl	%edx, %eax
	movw	$47, (%eax)
.L41:
	movl	-284(%ebp), %eax
	movl	4(%eax), %eax
	subl	$8, %esp
	pushl	%eax
	leal	-268(%ebp), %eax
	pushl	%eax
	call	strcat
	addl	$16, %esp
.L40:
	movl	-284(%ebp), %eax
	addl	$4, %eax
	subl	$4, %esp
	pushl	$0
	pushl	%eax
	leal	-268(%ebp), %eax
	pushl	%eax
	call	execve
	addl	$16, %esp
	testl	%eax, %eax
	je	.L42
	movl	-276(%ebp), %eax
	movl	path_tokens(,%eax,4), %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	.L43
.L42:
	movl	-284(%ebp), %eax
	movl	4(%eax), %edx
	movl	stderr, %eax
	subl	$4, %esp
	pushl	%edx
	pushl	$.LC20
	pushl	%eax
	call	fprintf
	addl	$16, %esp
	subl	$12, %esp
	pushl	$0
	call	exit
.L45:
	call	__stack_chk_fail
.L44:
	movl	-4(%ebp), %edi
	leave
	.cfi_restore 5
	.cfi_restore 7
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE11:
	.size	handle_fork, .-handle_fork
	.globl	main
	.type	main, @function
main:
.LFB12:
	.cfi_startproc
	leal	4(%esp), %ecx
	.cfi_def_cfa 1, 0
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	.cfi_escape 0x10,0x5,0x2,0x75,0
	movl	%esp, %ebp
	pushl	%ecx
	.cfi_escape 0xf,0x3,0x75,0x7c,0x6
	subl	$20, %esp
	call	init
.L51:
	call	get_input
	movl	%eax, -16(%ebp)
	subl	$12, %esp
	pushl	-16(%ebp)
	call	process_string
	addl	$16, %esp
	movl	%eax, -12(%ebp)
	subl	$12, %esp
	pushl	-12(%ebp)
	call	check_cd
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L54
	subl	$12, %esp
	pushl	-12(%ebp)
	call	check_exit
	addl	$16, %esp
	testl	%eax, %eax
	jne	.L55
	subl	$12, %esp
	pushl	-12(%ebp)
	call	handle_fork
	addl	$16, %esp
	jmp	.L51
.L54:
	nop
	jmp	.L51
.L55:
	nop
	movl	$0, %eax
	movl	-4(%ebp), %ecx
	.cfi_def_cfa 1, 0
	leave
	.cfi_restore 5
	leal	-4(%ecx), %esp
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
.LFE12:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.4) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
