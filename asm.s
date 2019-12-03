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
	.globl	y
	.data
	.align	8
	.type	y,	@object
	.size	y,	8
	y:
	.quad	2
	.section	.rodata

## TAC_BEGIN_FUNC ##
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushq	%rbp
	movq	%rsp, %rbp
## TAC_MOVE ##
	movl	$2, y(%rip)
## TAC_PRINT DATATYPE INT ## ##
	movl	y(%rip), %eax
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
