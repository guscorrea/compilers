.LC0:
.string	"%i"
	.text
.globl	i
.align	8
.type	i,	@object
.size	i,	8
i:
	.quad	0
.globl	j
.align	8
.type	j,	@object
.size	j,	8
j:
	.quad	1

## TAC_BEGIN_FUNC ##
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushq	%rbp
	movq	%rsp, %rbp
## TAC_PRINT ##
movl	$21,	%esi
leaq	.LC0(%rip),	%rdi
movl	$0,	%eax
call	printf@PLT
## TAC_END_FUNC ##
	movl	$0, %eax
	popq	%rbp
	ret
.LFE0:
	.size	main, .-main
