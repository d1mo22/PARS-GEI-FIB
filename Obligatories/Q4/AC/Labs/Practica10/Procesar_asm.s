.text
	.align 4
	.globl procesar
	.type	procesar, @function

cero: .byte 0,0,0,0,0,0,0,0,0,0,0,0
procesar:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	pushl	%ebx
	pushl	%esi
	pushl	%edi

# Aqui has de introducir el codigo 
 movl 8(%ebp), %eax         #%eax = @mata
 movl 12(%ebp), %ebx        #%ebx = @matb
 movl 16(%ebp), %ecx        #%ecx = @matc
 movl 20(%ebp), %edi        #%edi = n

 imul %edi, %edi            #%edi = n^2
 movl $0, %esi 
 jmp end_while

while:
 movb (%eax, %esi), %dl
 subb (%ebx, %esi), %dl    #%edx = mata[i*n+j] - matb[i*n+j]
 movb %dl, (%ecx, %esi)
 cmpb $0, %dl
 jle else

if:
 movb $255, (%ecx, %esi)
 jmp end_if

else:
 movb $0, (%ecx, %esi)

end_if:
 incl %esi

end_while:
 cmpl %esi, %edi
 jg while
# El final de la rutina ya esta programado

	popl	%edi
	popl	%esi
	popl	%ebx
	movl %ebp,%esp
	popl %ebp
	ret
