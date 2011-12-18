	.file	"main.c"
	.section	.rodata
	.align 8
.LC0:
	.string	"Quelle taille de tableau souhaitez-vous utiliser?"
.LC1:
	.string	"Premier tableau"
.LC2:
	.string	"Second tableau"
	.text
.globl main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$1432, %rsp
	movl	$.LC0, %edx
	movl	$15, %esi
	movl	$0, %edi
	.cfi_offset 3, -24
	call	ask_val
	movb	%al, -17(%rbp)
	movl	$0, %edi
	call	time
	movl	%eax, %edi
	call	srand
	movsbl	-17(%rbp),%edx
	leaq	-480(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	init_array
	movsbl	-17(%rbp),%edx
	leaq	-944(%rbp), %rax
	movl	%edx, %esi
	movq	%rax, %rdi
	call	init_array
	movsbl	-17(%rbp),%edx
	movsbl	-17(%rbp),%ebx
	leaq	-480(%rbp), %rax
	movl	$.LC1, %ecx
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	show_array
	movsbl	-17(%rbp),%edx
	movsbl	-17(%rbp),%ebx
	leaq	-944(%rbp), %rax
	movl	$.LC2, %ecx
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	show_array
	movsbl	-17(%rbp),%esi
	leaq	-1408(%rbp), %rdx
	leaq	-944(%rbp), %rbx
	leaq	-480(%rbp), %rax
	leaq	-1440(%rbp), %rcx
	movl	%esi, %r8d
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	menu
	movl	$0, %eax
	addq	$1432, %rsp
	popq	%rbx
	leave
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
.LC3:
	.string	"Menu"
	.align 8
.LC4:
	.string	"1. Ajouter une valeur \303\240 la premi\303\250re matrice"
	.align 8
.LC5:
	.string	"2. Additionner les deux premi\303\250res matrices"
	.align 8
.LC6:
	.string	"3. Soustraire une valeur \303\240 la premi\303\250re matrice"
	.align 8
.LC7:
	.string	"4. Soustraire les deux premi\303\250res matrices"
	.align 8
.LC8:
	.string	"5. Multiplier la premi\303\250re matrice par une valeur"
	.align 8
.LC9:
	.string	"6. Mutliplier les deux premi\303\250res matrices"
.LC10:
	.string	"7. Quitter"
.LC11:
	.string	"Votre choix: "
.LC12:
	.string	"%hd"
	.text
.globl menu
	.type	menu, @function
menu:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movq	%rcx, -64(%rbp)
	movl	%r8d, %eax
	movb	%al, -68(%rbp)
.L12:
	movl	$.LC3, %edi
	.cfi_offset 3, -24
	call	puts
	movl	$.LC4, %edi
	call	puts
	movl	$.LC5, %edi
	call	puts
	movl	$.LC6, %edi
	call	puts
	movl	$.LC7, %edi
	call	puts
	movl	$.LC8, %edi
	call	puts
	movl	$.LC9, %edi
	call	puts
	movl	$.LC10, %edi
	call	puts
	movl	$.LC11, %eax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movl	$.LC12, %eax
	leaq	-18(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf
	movzwl	-18(%rbp), %eax
	cwtl
	cmpl	$6, %eax
	ja	.L4
	mov	%eax, %eax
	movq	.L11(,%rax,8), %rax
	jmp	*%rax
	.section	.rodata
	.align 8
	.align 4
.L11:
	.quad	.L4
	.quad	.L5
	.quad	.L6
	.quad	.L7
	.quad	.L8
	.quad	.L9
	.quad	.L10
	.text
.L5:
	movsbl	-68(%rbp),%edx
	movq	-56(%rbp), %rcx
	movq	-40(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	add_to_array
	jmp	.L4
.L6:
	movsbl	-68(%rbp),%ecx
	movq	-56(%rbp), %rdx
	movq	-48(%rbp), %rbx
	movq	-40(%rbp), %rax
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	add_arrays
	jmp	.L4
.L7:
	movsbl	-68(%rbp),%edx
	movq	-56(%rbp), %rcx
	movq	-40(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	soustract_to_array
	jmp	.L4
.L8:
	movsbl	-68(%rbp),%ecx
	movq	-56(%rbp), %rdx
	movq	-48(%rbp), %rbx
	movq	-40(%rbp), %rax
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	soustract_arrays
	jmp	.L4
.L9:
	movsbl	-68(%rbp),%edx
	movq	-56(%rbp), %rcx
	movq	-40(%rbp), %rax
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	mult_to_array
	jmp	.L4
.L10:
	movsbl	-68(%rbp),%ecx
	movq	-64(%rbp), %rdx
	movq	-48(%rbp), %rbx
	movq	-40(%rbp), %rax
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	cross_arrays
.L4:
	movzwl	-18(%rbp), %eax
	cmpw	$7, %ax
	jne	.L12
	addq	$72, %rsp
	popq	%rbx
	leave
	ret
	.cfi_endproc
.LFE1:
	.size	menu, .-menu
.globl r_rand
	.type	r_rand, @function
r_rand:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	call	rand
	movl	-8(%rbp), %edx
	addl	$1, %edx
	movl	%edx, %ecx
	movl	%eax, %edx
	sarl	$31, %edx
	idivl	%ecx
	movl	%edx, %eax
	addl	-4(%rbp), %eax
	leave
	ret
	.cfi_endproc
.LFE2:
	.size	r_rand, .-r_rand
	.section	.rodata
.LC13:
	.string	"%s [%hd, %hd] "
	.text
.globl ask_val
	.type	ask_val, @function
ask_val:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	movl	%edi, %ecx
	movl	%esi, %eax
	movq	%rdx, -48(%rbp)
	movw	%cx, -36(%rbp)
	movw	%ax, -40(%rbp)
.L17:
	movswl	-40(%rbp),%ecx
	movswl	-36(%rbp),%edx
	movl	$.LC13, %eax
	movq	-48(%rbp), %rbx
	.cfi_offset 3, -24
	movq	%rbx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	movl	$.LC12, %eax
	leaq	-18(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	__isoc99_scanf
	movzwl	-18(%rbp), %eax
	cmpw	-36(%rbp), %ax
	jl	.L17
	movzwl	-18(%rbp), %eax
	cmpw	-40(%rbp), %ax
	jg	.L17
	movzwl	-18(%rbp), %eax
	addq	$40, %rsp
	popq	%rbx
	leave
	ret
	.cfi_endproc
.LFE3:
	.size	ask_val, .-ask_val
.globl map_simple
	.type	map_simple, @function
map_simple:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	movq	%rdi, -40(%rbp)
	movl	%esi, %ebx
	.cfi_offset 3, -24
	movl	%edx, %eax
	movq	%rcx, -56(%rbp)
	movl	%r8d, %edx
	movb	%bl, -44(%rbp)
	movb	%al, -48(%rbp)
	movb	%dl, -60(%rbp)
	movzbl	-48(%rbp), %eax
	movl	$15, %edx
	movl	%edx, %ecx
	subb	%al, %cl
	movl	%ecx, %eax
	movb	%al, -17(%rbp)
	movb	$0, -19(%rbp)
	jmp	.L20
.L24:
	movb	$0, -18(%rbp)
	jmp	.L21
.L22:
	movq	-40(%rbp), %rax
	movq	-56(%rbp), %rdx
	movq	%rax, %rdi
	call	*%rdx
	addb	$1, -18(%rbp)
	addq	$2, -40(%rbp)
.L21:
	movzbl	-18(%rbp), %eax
	cmpb	-48(%rbp), %al
	jl	.L22
	cmpb	$0, -60(%rbp)
	je	.L23
	movl	$10, %edi
	call	putchar
.L23:
	movsbq	-17(%rbp),%rax
	addq	%rax, %rax
	addq	%rax, -40(%rbp)
	addb	$1, -19(%rbp)
.L20:
	movzbl	-19(%rbp), %eax
	cmpb	-44(%rbp), %al
	jl	.L24
	addq	$56, %rsp
	popq	%rbx
	leave
	ret
	.cfi_endproc
.LFE4:
	.size	map_simple, .-map_simple
.globl map_double
	.type	map_double, @function
map_double:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, %eax
	movq	%rcx, -48(%rbp)
	movl	%r8d, %edx
	movb	%al, -36(%rbp)
	movw	%dx, -52(%rbp)
	movzbl	-36(%rbp), %eax
	movl	$15, %edx
	movl	%edx, %ecx
	subb	%al, %cl
	movl	%ecx, %eax
	movb	%al, -1(%rbp)
	movb	$0, -3(%rbp)
	jmp	.L27
.L30:
	movb	$0, -2(%rbp)
	jmp	.L28
.L29:
	movswl	-52(%rbp),%edx
	movq	-24(%rbp), %rax
	movzwl	(%rax), %eax
	cwtl
	movq	-48(%rbp), %rcx
	movl	%edx, %esi
	movl	%eax, %edi
	call	*%rcx
	movq	-32(%rbp), %rdx
	movw	%ax, (%rdx)
	addq	$2, -24(%rbp)
	addq	$2, -32(%rbp)
	addb	$1, -2(%rbp)
.L28:
	movzbl	-2(%rbp), %eax
	cmpb	-36(%rbp), %al
	jl	.L29
	movsbq	-1(%rbp),%rax
	addq	%rax, %rax
	addq	%rax, -24(%rbp)
	movsbq	-1(%rbp),%rax
	addq	%rax, %rax
	addq	%rax, -32(%rbp)
	addb	$1, -3(%rbp)
.L27:
	movzbl	-3(%rbp), %eax
	cmpb	-36(%rbp), %al
	jl	.L30
	leave
	ret
	.cfi_endproc
.LFE5:
	.size	map_double, .-map_double
.globl map_triple
	.type	map_triple, @function
map_triple:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movl	%ecx, %eax
	movq	%r8, -56(%rbp)
	movb	%al, -44(%rbp)
	movzbl	-44(%rbp), %eax
	movl	$15, %edx
	movl	%edx, %ecx
	subb	%al, %cl
	movl	%ecx, %eax
	movb	%al, -1(%rbp)
	movb	$0, -3(%rbp)
	jmp	.L33
.L36:
	movb	$0, -2(%rbp)
	jmp	.L34
.L35:
	movq	-32(%rbp), %rax
	movzwl	(%rax), %eax
	movswl	%ax,%edx
	movq	-24(%rbp), %rax
	movzwl	(%rax), %eax
	cwtl
	movq	-56(%rbp), %rcx
	movl	%edx, %esi
	movl	%eax, %edi
	call	*%rcx
	movq	-40(%rbp), %rdx
	movw	%ax, (%rdx)
	addq	$2, -24(%rbp)
	addq	$2, -32(%rbp)
	addq	$2, -40(%rbp)
	addb	$1, -2(%rbp)
.L34:
	movzbl	-2(%rbp), %eax
	cmpb	-44(%rbp), %al
	jl	.L35
	movsbq	-1(%rbp),%rax
	addq	%rax, %rax
	addq	%rax, -24(%rbp)
	movsbq	-1(%rbp),%rax
	addq	%rax, %rax
	addq	%rax, -32(%rbp)
	movsbq	-1(%rbp),%rax
	addq	%rax, %rax
	addq	%rax, -40(%rbp)
	addb	$1, -3(%rbp)
.L33:
	movzbl	-3(%rbp), %eax
	cmpb	-44(%rbp), %al
	jl	.L36
	leave
	ret
	.cfi_endproc
.LFE6:
	.size	map_triple, .-map_triple
.globl map_cross
	.type	map_cross, @function
map_cross:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$72, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movq	%rdx, -56(%rbp)
	movl	%ecx, %eax
	movq	%r8, -72(%rbp)
	movb	%al, -60(%rbp)
	movb	$0, -17(%rbp)
	jmp	.L39
	.cfi_offset 3, -24
.L40:
	movsbl	-60(%rbp),%edx
	movq	-48(%rbp), %rcx
	movq	-40(%rbp), %rax
	movq	-72(%rbp), %rbx
	movq	%rcx, %rsi
	movq	%rax, %rdi
	call	*%rbx
	movq	-56(%rbp), %rdx
	movw	%ax, (%rdx)
	addq	$30, -40(%rbp)
	addq	$2, -48(%rbp)
	addq	$2, -56(%rbp)
	addb	$1, -17(%rbp)
.L39:
	movzbl	-17(%rbp), %eax
	cmpb	-60(%rbp), %al
	jl	.L40
	addq	$72, %rsp
	popq	%rbx
	leave
	ret
	.cfi_endproc
.LFE7:
	.size	map_cross, .-map_cross
.globl random_cell
	.type	random_cell, @function
random_cell:
.LFB8:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movl	$10, %esi
	movl	$0, %edi
	call	r_rand
	movl	%eax, %edx
	movq	-8(%rbp), %rax
	movw	%dx, (%rax)
	leave
	ret
	.cfi_endproc
.LFE8:
	.size	random_cell, .-random_cell
.globl init_array
	.type	init_array, @function
init_array:
.LFB9:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$24, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, %eax
	movb	%al, -28(%rbp)
	movsbl	-28(%rbp),%edx
	movsbl	-28(%rbp),%ebx
	.cfi_offset 3, -24
	movq	-24(%rbp), %rax
	movl	$0, %r8d
	movl	$random_cell, %ecx
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	map_simple
	addq	$24, %rsp
	popq	%rbx
	leave
	ret
	.cfi_endproc
.LFE9:
	.size	init_array, .-init_array
	.section	.rodata
.LC14:
	.string	"%hd\t"
	.text
.globl show_cell
	.type	show_cell, @function
show_cell:
.LFB10:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movzwl	(%rax), %eax
	movswl	%ax,%edx
	movl	$.LC14, %eax
	movl	%edx, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	leave
	ret
	.cfi_endproc
.LFE10:
	.size	show_cell, .-show_cell
	.section	.rodata
.LC15:
	.string	"%s:\n"
	.text
.globl show_array
	.type	show_array, @function
show_array:
.LFB11:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	movq	%rdi, -24(%rbp)
	movl	%esi, %ebx
	.cfi_offset 3, -24
	movl	%edx, %eax
	movq	%rcx, -40(%rbp)
	movb	%bl, -28(%rbp)
	movb	%al, -32(%rbp)
	movl	$.LC15, %eax
	movq	-40(%rbp), %rdx
	movq	%rdx, %rsi
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf
	cmpb	$1, -32(%rbp)
	setg	%al
	movzbl	%al, %ecx
	movsbl	-32(%rbp),%edx
	movsbl	-28(%rbp),%ebx
	movq	-24(%rbp), %rax
	movl	%ecx, %r8d
	movl	$show_cell, %ecx
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	map_simple
	movl	$10, %edi
	call	putchar
	addq	$40, %rsp
	popq	%rbx
	leave
	ret
	.cfi_endproc
.LFE11:
	.size	show_array, .-show_array
.globl add_to_cell
	.type	add_to_cell, @function
add_to_cell:
.LFB12:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movl	%edi, %edx
	movl	%esi, %eax
	movw	%dx, -4(%rbp)
	movw	%ax, -8(%rbp)
	movzwl	-4(%rbp), %edx
	movzwl	-8(%rbp), %eax
	leal	(%rdx,%rax), %eax
	leave
	ret
	.cfi_endproc
.LFE12:
	.size	add_to_cell, .-add_to_cell
	.section	.rodata
	.align 8
.LC16:
	.string	"Quel valeur souhaitez-vous ajouter aux cellules du tableau ?"
.LC17:
	.string	"R\303\251sultat"
	.text
.globl add_to_array
	.type	add_to_array, @function
add_to_array:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	%edx, %eax
	movb	%al, -52(%rbp)
	movl	$.LC16, %edx
	movl	$32767, %esi
	movl	$-32768, %edi
	.cfi_offset 3, -24
	call	ask_val
	movw	%ax, -18(%rbp)
	movswl	-18(%rbp),%ecx
	movsbl	-52(%rbp),%edx
	movq	-48(%rbp), %rbx
	movq	-40(%rbp), %rax
	movl	%ecx, %r8d
	movl	$add_to_cell, %ecx
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	map_double
	movsbl	-52(%rbp),%edx
	movsbl	-52(%rbp),%ebx
	movq	-48(%rbp), %rax
	movl	$.LC17, %ecx
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	show_array
	addq	$56, %rsp
	popq	%rbx
	leave
	ret
	.cfi_endproc
.LFE13:
	.size	add_to_array, .-add_to_array
	.section	.rodata
	.align 8
.LC18:
	.string	"Quel valeur souhaitez-vous soustraire aux cellules du tableau ?"
	.text
.globl soustract_to_array
	.type	soustract_to_array, @function
soustract_to_array:
.LFB14:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	%edx, %eax
	movb	%al, -52(%rbp)
	movl	$.LC18, %edx
	movl	$32767, %esi
	movl	$-32768, %edi
	.cfi_offset 3, -24
	call	ask_val
	movw	%ax, -18(%rbp)
	movzwl	-18(%rbp), %eax
	negl	%eax
	movswl	%ax,%ecx
	movsbl	-52(%rbp),%edx
	movq	-48(%rbp), %rbx
	movq	-40(%rbp), %rax
	movl	%ecx, %r8d
	movl	$add_to_cell, %ecx
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	map_double
	movsbl	-52(%rbp),%edx
	movsbl	-52(%rbp),%ebx
	movq	-48(%rbp), %rax
	movl	$.LC17, %ecx
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	show_array
	addq	$56, %rsp
	popq	%rbx
	leave
	ret
	.cfi_endproc
.LFE14:
	.size	soustract_to_array, .-soustract_to_array
.globl mutl_cell
	.type	mutl_cell, @function
mutl_cell:
.LFB15:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movl	%edi, %edx
	movl	%esi, %eax
	movw	%dx, -4(%rbp)
	movw	%ax, -8(%rbp)
	movzwl	-4(%rbp), %eax
	imulw	-8(%rbp), %ax
	leave
	ret
	.cfi_endproc
.LFE15:
	.size	mutl_cell, .-mutl_cell
	.section	.rodata
	.align 8
.LC19:
	.string	"Quel valeur souhaitez-vous multipliser cellules du tableau ?"
	.text
.globl mult_to_array
	.type	mult_to_array, @function
mult_to_array:
.LFB16:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$56, %rsp
	movq	%rdi, -40(%rbp)
	movq	%rsi, -48(%rbp)
	movl	%edx, %eax
	movb	%al, -52(%rbp)
	movl	$.LC19, %edx
	movl	$32767, %esi
	movl	$-32768, %edi
	.cfi_offset 3, -24
	call	ask_val
	movw	%ax, -18(%rbp)
	movswl	-18(%rbp),%ecx
	movsbl	-52(%rbp),%edx
	movq	-48(%rbp), %rbx
	movq	-40(%rbp), %rax
	movl	%ecx, %r8d
	movl	$mutl_cell, %ecx
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	map_double
	movsbl	-52(%rbp),%edx
	movsbl	-52(%rbp),%ebx
	movq	-48(%rbp), %rax
	movl	$.LC17, %ecx
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	show_array
	addq	$56, %rsp
	popq	%rbx
	leave
	ret
	.cfi_endproc
.LFE16:
	.size	mult_to_array, .-mult_to_array
.globl add_cells
	.type	add_cells, @function
add_cells:
.LFB17:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movl	%edi, %edx
	movl	%esi, %eax
	movw	%dx, -4(%rbp)
	movw	%ax, -8(%rbp)
	movzwl	-4(%rbp), %edx
	movzwl	-8(%rbp), %eax
	leal	(%rdx,%rax), %eax
	leave
	ret
	.cfi_endproc
.LFE17:
	.size	add_cells, .-add_cells
.globl add_arrays
	.type	add_arrays, @function
add_arrays:
.LFB18:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movl	%ecx, %eax
	movb	%al, -44(%rbp)
	movsbl	-44(%rbp),%ecx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rbx
	.cfi_offset 3, -24
	movq	-24(%rbp), %rax
	movl	$add_cells, %r8d
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	map_triple
	movsbl	-44(%rbp),%edx
	movsbl	-44(%rbp),%ebx
	movq	-40(%rbp), %rax
	movl	$.LC17, %ecx
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	show_array
	addq	$40, %rsp
	popq	%rbx
	leave
	ret
	.cfi_endproc
.LFE18:
	.size	add_arrays, .-add_arrays
.globl soustract_cells
	.type	soustract_cells, @function
soustract_cells:
.LFB19:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movl	%edi, %edx
	movl	%esi, %eax
	movw	%dx, -4(%rbp)
	movw	%ax, -8(%rbp)
	movzwl	-4(%rbp), %edx
	movzwl	-8(%rbp), %eax
	movl	%edx, %ecx
	subw	%ax, %cx
	movl	%ecx, %eax
	leave
	ret
	.cfi_endproc
.LFE19:
	.size	soustract_cells, .-soustract_cells
.globl soustract_arrays
	.type	soustract_arrays, @function
soustract_arrays:
.LFB20:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movl	%ecx, %eax
	movb	%al, -44(%rbp)
	movsbl	-44(%rbp),%ecx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rbx
	.cfi_offset 3, -24
	movq	-24(%rbp), %rax
	movl	$soustract_cells, %r8d
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	map_triple
	movsbl	-44(%rbp),%edx
	movsbl	-44(%rbp),%ebx
	movq	-40(%rbp), %rax
	movl	$.LC17, %ecx
	movl	%ebx, %esi
	movq	%rax, %rdi
	call	show_array
	addq	$40, %rsp
	popq	%rbx
	leave
	ret
	.cfi_endproc
.LFE20:
	.size	soustract_arrays, .-soustract_arrays
.globl cross_mult
	.type	cross_mult, @function
cross_mult:
.LFB21:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movl	%edx, %eax
	movb	%al, -36(%rbp)
	movw	$0, -2(%rbp)
	movb	$0, -3(%rbp)
	jmp	.L69
.L70:
	movq	-24(%rbp), %rax
	movzwl	(%rax), %edx
	movq	-32(%rbp), %rax
	movzwl	(%rax), %eax
	imull	%edx, %eax
	movl	%eax, %edx
	movzwl	-2(%rbp), %eax
	leal	(%rdx,%rax), %eax
	movw	%ax, -2(%rbp)
	addq	$2, -24(%rbp)
	addq	$30, -32(%rbp)
	addb	$1, -3(%rbp)
.L69:
	movzbl	-3(%rbp), %eax
	cmpb	-36(%rbp), %al
	jl	.L70
	movzwl	-2(%rbp), %eax
	leave
	ret
	.cfi_endproc
.LFE21:
	.size	cross_mult, .-cross_mult
.globl cross_arrays
	.type	cross_arrays, @function
cross_arrays:
.LFB22:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	movq	%rsp, %rbp
	.cfi_offset 6, -16
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	movq	%rdi, -24(%rbp)
	movq	%rsi, -32(%rbp)
	movq	%rdx, -40(%rbp)
	movl	%ecx, %eax
	movb	%al, -44(%rbp)
	movsbl	-44(%rbp),%ecx
	movq	-40(%rbp), %rdx
	movq	-32(%rbp), %rbx
	.cfi_offset 3, -24
	movq	-24(%rbp), %rax
	movl	$cross_mult, %r8d
	movq	%rbx, %rsi
	movq	%rax, %rdi
	call	map_cross
	movsbl	-44(%rbp),%edx
	movq	-40(%rbp), %rax
	movl	$.LC17, %ecx
	movl	$1, %esi
	movq	%rax, %rdi
	call	show_array
	addq	$40, %rsp
	popq	%rbx
	leave
	ret
	.cfi_endproc
.LFE22:
	.size	cross_arrays, .-cross_arrays
	.ident	"GCC: (SUSE Linux) 4.4.1 [gcc-4_4-branch revision 150839]"
	.section	.comment.SUSE.OPTs,"MS",@progbits,1
	.string	"ospwg"
	.section	.note.GNU-stack,"",@progbits
