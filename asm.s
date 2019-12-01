.LC0:
.string	"%i"
.text
.globl	x
.align	8
.type	x,	@object
.size	x,	8
x:
	.quad	1

## TAC_BEGIN_FUNC ##
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushq	%rbp
	movq	%rsp, %rbp
## TAC_MOVE ##
	movl	$4, x(%rip)
## TAC_PRINT DATATYPE INT ## ##
	movl	x(%rip),	%eax
	movl	%eax,	%esi
	leaq	.LC0(%rip),	%rdi
	movl	$0,	%eax
	call	printf@PLT
## TAC_END_FUNC ##
	movl	$0, %eax
	popq	%rbp
	ret
.LFE0:
	.size	main, .-main
