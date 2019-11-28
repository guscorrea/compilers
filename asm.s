
## TAC_BEGIN_FUNC ##
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushq	%rbp
	movq	%rsp, %rbp
## TAC_END_FUNC ##
	popq	%rbp
	ret
.LFE0:
	.size	main, .-main

## TAC_BEGIN_FUNC ##
	.globl	func
	.type	func, @function
func:
.LFB1:
	pushq	%rbp
	movq	%rsp, %rbp
## TAC_END_FUNC ##
	popq	%rbp
	ret
.LFE1:
	.size	func, .-func

## TAC_BEGIN_FUNC ##
	.globl	foo
	.type	foo, @function
foo:
.LFB2:
	pushq	%rbp
	movq	%rsp, %rbp
## TAC_END_FUNC ##
	popq	%rbp
	ret
.LFE2:
	.size	foo, .-foo
