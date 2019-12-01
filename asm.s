.LC0:
	.string	"%i"
	.text
	.globl	x
	.data
	.align	8
	.type	x,	@object
	.size	x,	8
	x:
	.quad	10
	.section	.rodata

## TAC_BEGIN_FUNC ##
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushq	%rbp
	movq	%rsp, %rbp
## TAC_GE ##
	movl	x(%rip), %eax
	cmpl	$2, %eax
	jle	.Label0
## TAC_MOVE ##
	movl	$3, x(%rip)
## TAC_LABEL ##
.Label0:
## TAC_PRINT DATATYPE INT ## ##
	movl	x(%rip), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
## TAC_END_FUNC ##
	movl	$0, %eax
	popq	%rbp
	ret
.LFE0:
	.size	main, .-main
