 .text
	.align 4
	.globl Buscar
	.type Buscar,@function
Buscar:
	 # Aqui viene vuestro codigo

	pushl %ebp
	movl %esp, %ebp
	subl $-16, %esp
	movl $-1, -4(%ebp)
	movl $0, -16(%ebp)
	movl $0, -8(%ebp)
	movl 24(%ebp), %ecx
	decl %ecx
	movl %ecx, -12(%ebp)
while:
	cmpl %ecx, -16(%ebp)
	jg end_while

	pushl 8(%ebp)
	pushl 20(%ebp)
	pushl 16(%ebp)
	pushl 12(%ebp)
	leal -8(%ebp), %eax
	pushl %eax
	leal -12(%ebp), %ecx
	pushl %ecx
	leal -16(%ebp), %eax
	pushl %eax
	call BuscarElemento

	addl $28, %esp
	movl %eax, -4(%ebp)
	cmpl $0, %eax
	jl end_while

	jmp while
end_while:
	movl -4(%ebp), %eax
	movl %ebp, %esp
	popl %ebp
	ret



       