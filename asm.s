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
_5:	.long	5
	.data
_Temp2:	.long	 0
	.data
_Temp7:	.long	 0
	.section	.rodata
STRING0:	.string	"\n Entrou if: X menor igual a 1 \n"
	.section	.rodata
STRING1:	.string	"\n Nao pode entrar aqui \n"
	.data
_Temp0:	.long	 0
	.section	.rodata
STRING2:	.string	"\n Entrou if: teste do NOT \n"
	.data
_Temp5:	.long	 0
	.section	.rodata
STRING3:	.string	"\n Entrou no if do OR \n"
	.section	.rodata
_10:	.long	10
	.section	.rodata
STRING4:	.string	"\n Entrou no else do AND \n"
	.data
_Temp3:	.long	 0
	.data
_Temp8:	.long	 0
	.section	.rodata
STRING5:	.string	"\n Entrou if: y eh diferente de 2 \n"
	.section	.rodata
STRING6:	.string	"\n Entrou if: Y tem valor maior igual a 5 \n"
	.section	.rodata
STRING7:	.string	"\n Entrou if: B tem valor TRUE \n"
	.data
_Temp1:	.long	 0
	.data
_Temp6:	.long	 0
	.section	.rodata
STRING8:	.string	"\n Funciona \n"
	.section	.rodata
STRING9:	.string	"\n Entrou no else do b equals false \n"
	.data
_Temp4:	.long	 0
	.data
_Temp9:	.long	 0
	.section	.rodata
STRING10:	.string	"\n Loop! \n"

	.data
_x:	.long	0
	.section	.rodata

	.data
_y:	.long	10
	.section	.rodata

	.data
_b:	.long	1
	.section	.rodata

	.data
_f:	.long	0
	.section	.rodata

## TAC_BEGINFUN ##
	.globl	main
	.type	main, @function
main:
.LFB0:
	pushq	%rbp
	movq	%rsp, %rbp
## TAC_EQ ##
	movl	_b(%rip), %edx
	movl	_TRUE(%rip), %eax
	cmpl	%eax, %edx
	sete	%al
	movzbl	%al, %eax
	movl	%eax, _Temp0(%rip)
## TAC_IFZ
	movl	_Temp0(%rip), %eax
	testl	%eax, %eax
	je	.Label0
## TAC_PRINT_LITSTRING ##
	leaq	STRING7(%rip), %rdi
	call	printf@PLT
## TAC_LABEL
.Label0:
## TAC_DIF ##
	movl	_y(%rip), %edx
	movl	_2(%rip), %eax
	cmpl	%eax, %edx
	setne	%al
	movzbl	%al, %eax
	movl	%eax, _Temp1(%rip)
## TAC_IFZ
	movl	_Temp1(%rip), %eax
	testl	%eax, %eax
	je	.Label1
## TAC_PRINT_LITSTRING ##
	leaq	STRING5(%rip), %rdi
	call	printf@PLT
## TAC_LABEL
.Label1:
## TAC_LE
	movl	_x(%rip), %edx
	movl	_1(%rip), %eax
	cmpl	%eax, %edx
	setle	%al
	movzbl	%al, %eax
	movl	%eax, _Temp2(%rip)
## TAC_IFZ
	movl	_Temp2(%rip), %eax
	testl	%eax, %eax
	je	.Label2
## TAC_PRINT_LITSTRING ##
	leaq	STRING0(%rip), %rdi
	call	printf@PLT
## TAC_LABEL
.Label2:
## TAC_GE
	movl	_y(%rip), %edx
	movl	_5(%rip), %eax
	cmpl	%eax, %edx
	setge	%al
	movzbl	%al, %eax
	movl	%eax, _Temp3(%rip)
## TAC_IFZ
	movl	_Temp3(%rip), %eax
	testl	%eax, %eax
	je	.Label3
## TAC_PRINT_LITSTRING ##
	leaq	STRING6(%rip), %rdi
	call	printf@PLT
## TAC_LABEL
.Label3:
## TAC_EQ ##
	movl	_b(%rip), %edx
	movl	_FALSE(%rip), %eax
	cmpl	%eax, %edx
	sete	%al
	movzbl	%al, %eax
	movl	%eax, _Temp4(%rip)
## TAC_IFZ
	movl	_Temp4(%rip), %eax
	testl	%eax, %eax
	je	.Label4
## TAC_PRINT_LITSTRING ##
	leaq	STRING1(%rip), %rdi
	call	printf@PLT
## TAC_JUMP
	jmp	.Label5
## TAC_LABEL
.Label4:
## TAC_PRINT_LITSTRING ##
	leaq	STRING9(%rip), %rdi
	call	printf@PLT
## TAC_LABEL
.Label5:
## TAC_NOT ##
	movl	_f(%rip), %eax
	testl	%eax, %eax
	sete	%al
	movzbl	%al, %eax
	movl	%eax, _Temp5(%rip)
## TAC_IFZ
	movl	_Temp5(%rip), %eax
	testl	%eax, %eax
	je	.Label6
## TAC_PRINT_LITSTRING ##
	leaq	STRING2(%rip), %rdi
	call	printf@PLT
## TAC_LABEL
.Label6:
## TAC_AND
	movl	_f(%rip), %eax
	testl	%eax, %eax
	je	.LogicOP0
	movl	_b(%rip), %eax
	testl	%eax, %eax
	je	.LogicOP0
	movl	$1, %eax
	jmp	.LogicOP1
.LogicOP0:
	movl	$0, %eax
.LogicOP1:
	movl	%eax, _Temp6(%rip)
## TAC_IFZ
	movl	_Temp6(%rip), %eax
	testl	%eax, %eax
	je	.Label7
## TAC_PRINT_LITSTRING ##
	leaq	STRING1(%rip), %rdi
	call	printf@PLT
## TAC_JUMP
	jmp	.Label8
## TAC_LABEL
.Label7:
## TAC_PRINT_LITSTRING ##
	leaq	STRING4(%rip), %rdi
	call	printf@PLT
## TAC_LABEL
.Label8:
## TAC_OR ##
	movl	_f(%rip), %eax
	testl	%eax, %eax
	jne	.LogicOP2
	movl	_b(%rip), %eax
	testl	%eax, %eax
	je	.LogicOP3
.LogicOP2:
	movl	$1, %eax
	jmp	.LogicOP4
.LogicOP3:
	movl	$0, %eax
.LogicOP4:
	movl	%eax, _Temp7(%rip)
## TAC_IFZ
	movl	_Temp7(%rip), %eax
	testl	%eax, %eax
	je	.Label9
## TAC_PRINT_LITSTRING ##
	leaq	STRING3(%rip), %rdi
	call	printf@PLT
## TAC_JUMP
	jmp	.Label10
## TAC_LABEL
.Label9:
## TAC_PRINT_LITSTRING ##
	leaq	STRING1(%rip), %rdi
	call	printf@PLT
## TAC_LABEL
.Label10:
## TAC_LABEL
.Label11:
## TAC_LE
	movl	_x(%rip), %edx
	movl	_5(%rip), %eax
	cmpl	%eax, %edx
	setle	%al
	movzbl	%al, %eax
	movl	%eax, _Temp8(%rip)
## TAC_IFZ
	movl	_Temp8(%rip), %eax
	testl	%eax, %eax
	je	.Label12
## TAC_PRINT_LITSTRING ##
	leaq	STRING10(%rip), %rdi
	call	printf@PLT
## TAC_ADD ##
	movl	_x(%rip), %edx
	movl	_1(%rip), %eax
	addl	%edx, %eax
	movl	%eax, _Temp9(%rip)
## TAC_MOVE ##
	movl	_Temp9(%rip), %eax
	movl	%eax, _x(%rip)
## TAC_JUMP
	jmp	.Label11
## TAC_LABEL
.Label12:
## TAC_PRINT_LITSTRING ##
	leaq	STRING8(%rip), %rdi
	call	printf@PLT
## TAC_ENDFUN
	popq	%rbp
	ret
.LFE0:
	.size	main, .-main
