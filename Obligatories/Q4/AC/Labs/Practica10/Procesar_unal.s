.text
	.align 4
	.globl procesar
	.type	procesar, @function
zero: .byte 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
procesar:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl	%ebx
	pushl	%esi
	pushl	%edi

# Aqui has de introducir el codigo

 movl $0, %edx				#%edx = i = 0
 movl 8(%ebp), %eax			#%eax = @mata
 movl 12(%ebp), %ebx		#%ebx = @matb
 movl 16(%ebp), %ecx		#%ecx = @matc
 movl 20(%ebp), %esi
 imull %esi, %esi			#%esi = n^2

for:
 cmpl %esi, %edx
 jge end_for

 movdqu (%eax, %edx), %xmm0
 movdqu (%ebx, %edx), %xmm1
 psubb %xmm1, %xmm0
 movdqu %xmm0, (%ecx, %edx)

 movdqu zero, %xmm2
 pcmpgtb %xmm2, %xmm0
 movdqu %xmm0, (%ecx, %edx)

 addl $16, %edx
 jmp for

end_for:
# El final de la rutina ya esta programado

	emms	# Instruccion necesaria si os equivocais y usais MMX
	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret
