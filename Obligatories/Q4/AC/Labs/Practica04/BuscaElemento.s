 .text
	.align 4
	.globl BuscarElemento
	.type BuscarElemento,@function
BuscarElemento:
        # Aqui viene vuestro codigo
		pushl %ebp
		movl %esp, %ebp

		movl 16(%ebp), %eax
		movl (%eax), %eax
		imull $12, %eax, %eax
		movl 32(%ebp), %ecx
		movl 4(%ecx, %eax), %edx
		cmpl %edx, 24(%ebp)
		jne else

		movl 16(%ebp), %eax
		movl (%eax), %eax
		movl %ebp, %esp
		popl %ebp
		ret
else:
		movl 12(%ebp), %ecx
		movl (%ecx), %ecx		
		movl 16(%ebp), %eax		
		movl (%eax), %eax		
		cmpl %ecx, %eax
		jge else2

		movl 16(%ebp), %eax
		movl %ecx, (%eax)
		movl 8(%ebp), %eax
		movl (%eax), %ecx
		incl %ecx
		movl %ecx, (%eax)
		jmp end_if
else2:
		movl 8(%ebp), %edx		
		movl (%edx), %edx		
		movl 16(%ebp), %eax	
		movl %edx, (%eax)
		movl 12(%ebp), %eax
		movl (%eax), %ecx
		decl %ecx
		movl %ecx, (%eax)
end_if: 
	movl $-1, %eax
	movl %ebp,%esp
	popl %ebp
	ret


