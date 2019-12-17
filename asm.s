	.section	.rodata
LC0:	.string "%d"
LC1:	.string "%f"
LC2:	.string " %c"
TRUE:	.string "TRUE"
FALSE:	.string "FALSE"
_TRUE:	.long 1
_FALSE:	.long 0
	.section	.rodata
_0:	.long	0
	.section	.rodata
_1:	.long	1
	.section	.rodata
_2:	.long	2
	.section	.rodata
_4:	.long	4
	.data
_Temp2:	.long	 0
	.data
_Temp7:	.long	 0
	.section	.rodata
STRING0:	.string	"\n Multiplicando x e y \n"
	.section	.rodata
STRING1:	.string	"\n Somando x e y: \n"
	.section	.rodata
_600:	.long	600
	.section	.rodata
STRING2:	.string	"\n Printando var bool \n"
	.section	.rodata
STRING3:	.string	"\n Divindo x e y  \n"
	.section	.rodata
_300:	.long	300
	.data
_Temp0:	.long	 0
	.data
_Temp5:	.long	 0
	.section	.rodata
STRING4:	.string	"\n Printando literal: \n"
	.section	.rodata
STRING5:	.string	"\n Mudei o valor de x \n"
	.section	.rodata
STRING6:	.string	"\n Printando x \n"
	.section	.rodata
_10:	.long	10
	.section	.rodata
STRING7:	.string	"\n Subtraindo x e  y \n"
	.section	.rodata
STRING8:	.string	"\n x agora eh y \n"
	.data
_Temp3:	.long	 0
	.data
_Temp8:	.long	 0
	.section	.rodata
STRING9:	.string	"\n Multiplicando valores literais \n"
	.section	.rodata
_100:	.long	100
	.section	.rodata
STRING10:	.string	"\n Subtraindo valores literais \n"
	.data
_Temp1:	.long	 0
	.data
_Temp6:	.long	 0
	.section	.rodata
STRING11:	.string	"\n Dividindo valores literais \n"
	.section	.rodata
_500:	.long	500
	.data
_Temp4:	.long	 0
	.section	.rodata
STRING12:	.string	"\n Somando valores literais \n"
	.section	.rodata
_200:	.long	200
	.section	.rodata
STRING13:	.string	"\n Printando literal bool: \n"
	.section	.rodata
_123:	.long	123

	.data
_x:	.long	1
	.section	.rodata

	.data
_y:	.long	10
	.section	.rodata

	.data
_z:	.long	0
	.section	.rodata

	.data
_b:	.long	1
	.section	.rodata

## TAC_BEGINFUN ##
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushq	%rbp
	movq	%rsp, %rbp
## TAC_PRINT_LITSTRING ##
	leaq	STRING4(%rip), %rdi
	call	printf@PLT
## TAC_PRINT_LITINT ##
	movl	_123(%rip), %esi
	leaq	LC0(%rip), %rdi
	call	printf@PLT
## TAC_PRINT_LITSTRING ##
	leaq	STRING6(%rip), %rdi
	call	printf@PLT
## TAC_PRINT_VAR ##
	movl	_x(%rip), %eax
	movl	%eax, %esi
	leaq	LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
## TAC_PRINT_LITSTRING ##
	leaq	STRING5(%rip), %rdi
	call	printf@PLT
## TAC_MOVE ##
	movl	_4(%rip), %eax
	movl	%eax, _x(%rip)
## TAC_PRINT_VAR ##
	movl	_x(%rip), %eax
	movl	%eax, %esi
	leaq	LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
## TAC_PRINT_LITSTRING ##
	leaq	STRING8(%rip), %rdi
	call	printf@PLT
## TAC_MOVE ##
	movl	_y(%rip), %eax
	movl	%eax, _x(%rip)
## TAC_PRINT_VAR ##
	movl	_x(%rip), %eax
	movl	%eax, %esi
	leaq	LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
## TAC_PRINT_LITSTRING ##
	leaq	STRING13(%rip), %rdi
	call	printf@PLT
## TAC_PRINT_LITBOOL ##
	leaq	TRUE(%rip), %rdi
	call	printf@PLT
## TAC_PRINT_LITSTRING ##
	leaq	STRING2(%rip), %rdi
	call	printf@PLT
## TAC_PRINT_VAR_BOOL
	movl	_b(%rip), %eax
	testl	%eax, %eax
	je	.LogicLabel0
	leaq	TRUE(%rip), %rdi
	call	printf@PLT
	jmp	.LogicLabel1
.LogicLabel0:
	leaq	FALSE(%rip), %rdi
	call	printf@PLT
.LogicLabel1:
## TAC_PRINT_LITSTRING ##
	leaq	STRING1(%rip), %rdi
	call	printf@PLT
## TAC_ADD ##
	movl	_x(%rip), %edx
	movl	_y(%rip), %eax
	addl	%edx, %eax
	movl	%eax, _Temp0(%rip)
## TAC_MOVE ##
	movl	_Temp0(%rip), %eax
	movl	%eax, _z(%rip)
## TAC_PRINT_VAR ##
	movl	_z(%rip), %eax
	movl	%eax, %esi
	leaq	LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
## TAC_PRINT_LITSTRING ##
	leaq	STRING12(%rip), %rdi
	call	printf@PLT
## TAC_ADD ##
	movl	_200(%rip), %edx
	movl	_300(%rip), %eax
	addl	%edx, %eax
	movl	%eax, _Temp1(%rip)
## TAC_ADD ##
	movl	_Temp1(%rip), %edx
	movl	_100(%rip), %eax
	addl	%edx, %eax
	movl	%eax, _Temp2(%rip)
## TAC_MOVE ##
	movl	_Temp2(%rip), %eax
	movl	%eax, _z(%rip)
## TAC_PRINT_VAR ##
	movl	_z(%rip), %eax
	movl	%eax, %esi
	leaq	LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
## TAC_PRINT_LITSTRING ##
	leaq	STRING10(%rip), %rdi
	call	printf@PLT
## TAC_SUB
	movl	_500(%rip), %edx
	movl	_300(%rip), %eax
	subl	%eax, %edx
	movl	%edx, _Temp3(%rip)
## TAC_MOVE ##
	movl	_Temp3(%rip), %eax
	movl	%eax, _z(%rip)
## TAC_PRINT_VAR ##
	movl	_z(%rip), %eax
	movl	%eax, %esi
	leaq	LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
## TAC_PRINT_LITSTRING ##
	leaq	STRING7(%rip), %rdi
	call	printf@PLT
## TAC_SUB
	movl	_x(%rip), %edx
	movl	_y(%rip), %eax
	subl	%eax, %edx
	movl	%edx, _Temp4(%rip)
## TAC_MOVE ##
	movl	_Temp4(%rip), %eax
	movl	%eax, _z(%rip)
## TAC_PRINT_VAR ##
	movl	_z(%rip), %eax
	movl	%eax, %esi
	leaq	LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
## TAC_PRINT_LITSTRING ##
	leaq	STRING9(%rip), %rdi
	call	printf@PLT
## TAC_MUL
	movl	_10(%rip), %edx
	movl	_2(%rip), %eax
	imull	%edx, %eax
	movl	%eax, _Temp5(%rip)
## TAC_MOVE ##
	movl	_Temp5(%rip), %eax
	movl	%eax, _z(%rip)
## TAC_PRINT_VAR ##
	movl	_z(%rip), %eax
	movl	%eax, %esi
	leaq	LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
## TAC_PRINT_LITSTRING ##
	leaq	STRING0(%rip), %rdi
	call	printf@PLT
## TAC_MUL
	movl	_x(%rip), %edx
	movl	_y(%rip), %eax
	imull	%edx, %eax
	movl	%eax, _Temp6(%rip)
## TAC_MOVE ##
	movl	_Temp6(%rip), %eax
	movl	%eax, _z(%rip)
## TAC_PRINT_VAR ##
	movl	_z(%rip), %eax
	movl	%eax, %esi
	leaq	LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
## TAC_PRINT_LITSTRING ##
	leaq	STRING11(%rip), %rdi
	call	printf@PLT
## TAC_DIV
	movl	_600(%rip), %eax
	movl	_300(%rip), %ecx
	cltd
	idivl	%ecx
	movl	%eax, _Temp7(%rip)
## TAC_MOVE ##
	movl	_Temp7(%rip), %eax
	movl	%eax, _z(%rip)
## TAC_PRINT_VAR ##
	movl	_z(%rip), %eax
	movl	%eax, %esi
	leaq	LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
## TAC_PRINT_LITSTRING ##
	leaq	STRING3(%rip), %rdi
	call	printf@PLT
## TAC_DIV
	movl	_x(%rip), %eax
	movl	_y(%rip), %ecx
	cltd
	idivl	%ecx
	movl	%eax, _Temp8(%rip)
## TAC_MOVE ##
	movl	_Temp8(%rip), %eax
	movl	%eax, _z(%rip)
## TAC_PRINT_VAR ##
	movl	_z(%rip), %eax
	movl	%eax, %esi
	leaq	LC0(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT
## TAC_ENDFUN
	popq	%rbp
	ret
.LFE0:
	.size	main, .-main
