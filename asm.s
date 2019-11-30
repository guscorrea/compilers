
## TAC_BEGIN_FUNC ##
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushq	%rbp
	movq	%rsp, %rbp
## TAC_READ ##
	movl	b(%rip), %eax
	movl	%eax, %edi
	movl	$0, %eax
	call	read@PLT
	movl	$0, %eax
## TAC_END_FUNC ##
	popq	%rbp
	ret
.LFE0:
	.size	main, .-main
