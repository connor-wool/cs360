	.global get_esp, get_ebp
get_esp:
	movl %esp, %eax
	ret
get_ebp:
	movl %ebp, %eax
	ret
