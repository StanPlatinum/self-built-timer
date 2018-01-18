	.file	"measure.c"
	.text
	.globl	non_atomic_incr
	.type	non_atomic_incr, @function
non_atomic_incr:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rdx
	movq	-8(%rbp), %rcx
#APP
# 9 "clock.h" 1
	mov (%rdx), %eax
	add $1, %eax
	mov %eax, (%rdx)
# 0 "" 2
#NO_APP
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	non_atomic_incr, .-non_atomic_incr
	.globl	ump_atomic_incr
	.type	ump_atomic_incr, @function
ump_atomic_incr:
.LFB3:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	-8(%rbp), %rdx
#APP
# 19 "clock.h" 1
	incl (%rax)
	
# 0 "" 2
#NO_APP
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	ump_atomic_incr, .-ump_atomic_incr
	.globl	smp_atomic_incr
	.type	smp_atomic_incr, @function
smp_atomic_incr:
.LFB4:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
	movq	-8(%rbp), %rax
	movq	-8(%rbp), %rdx
#APP
# 27 "clock.h" 1
	lock; incl (%rax)
	
# 0 "" 2
#NO_APP
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	smp_atomic_incr, .-smp_atomic_incr
	.globl	count_loop_asm
	.type	count_loop_asm, @function
count_loop_asm:
.LFB5:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
#APP
# 35 "clock.h" 1
	movq -8(%rbp), %rcx 
	1: inc %rax 
	movq %rax, (%rcx) 
	jmp 1b
# 0 "" 2
#NO_APP
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	count_loop_asm, .-count_loop_asm
	.globl	count_loop_asm_slow
	.type	count_loop_asm_slow, @function
count_loop_asm_slow:
.LFB6:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -8(%rbp)
#APP
# 46 "clock.h" 1
	movq -8(%rbp), %rcx 
	1: incq (%rcx) 
	jmp 1b
# 0 "" 2
#NO_APP
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE6:
	.size	count_loop_asm_slow, .-count_loop_asm_slow
	.section	.rodata
.LC1:
	.string	"20 times cost:%lld\n"
.LC2:
	.string	"counter:%d\n"
.LC4:
	.string	"percost:%f\n"
.LC5:
	.string	"rdtsc couple cost:%lld\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB7:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movl	$0, -24(%rbp)
	movl	.LC0(%rip), %eax
	movl	%eax, -20(%rbp)
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	call	rdtsc_start
	movq	%rax, -16(%rbp)
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	leaq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	ump_atomic_incr
	call	rdtsc_end
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, %rsi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	-24(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	subq	%rax, %rdx
	movq	%rdx, %rax
	testq	%rax, %rax
	js	.L7
	cvtsi2ssq	%rax, %xmm0
	jmp	.L8
.L7:
	movq	%rax, %rdx
	shrq	%rdx
	andl	$1, %eax
	orq	%rax, %rdx
	cvtsi2ssq	%rdx, %xmm0
	addss	%xmm0, %xmm0
.L8:
	movss	%xmm0, -20(%rbp)
	movss	-20(%rbp), %xmm0
	movss	.LC3(%rip), %xmm1
	divss	%xmm1, %xmm0
	unpcklps	%xmm0, %xmm0
	cvtps2pd	%xmm0, %xmm0
	movl	$.LC4, %edi
	movl	$1, %eax
	call	printf
	call	rdtsc_start
	movq	%rax, -16(%rbp)
	call	rdtsc_start
	call	rdtsc_end
	call	rdtsc_end
	movq	%rax, -8(%rbp)
	movq	-16(%rbp), %rax
	movq	-8(%rbp), %rdx
	subq	%rax, %rdx
	movq	%rdx, %rax
	movq	%rax, %rsi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE7:
	.size	main, .-main
	.section	.rodata
	.align 4
.LC0:
	.long	0
	.align 4
.LC3:
	.long	1101004800
	.ident	"GCC: (Ubuntu 4.8.4-2ubuntu1~14.04.3) 4.8.4"
	.section	.note.GNU-stack,"",@progbits
