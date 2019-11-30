
## TAC_BEGIN_FUNC ##
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushq	%rbp
	movq	%rsp, %rbp
## TAC_MOVE ##
	movl	c(%rip), %eax
	movl	%eax, b(%rip)
## TAC_MOVE ##
	movl	$2, c(%rip)
## TAC_END_FUNC ##
	movl	$0, %eax
	popq	%rbp
	ret
.LFE0:
	.size	main, .-main
