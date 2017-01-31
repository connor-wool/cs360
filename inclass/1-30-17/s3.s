# int mysum(int x, int y)

	.gloal mysum, printf

mysum:
	pushl %ebp
	movl %esp, %ebp
	movl 8(%ebp), %eax
	addl 12(%ebp), %eax
	movl %ebp, %esp
	pop %ebp
	ret
