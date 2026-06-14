	.file	"serial_th.c"
	.text
	.globl	fd
	.bss
	.align 4
	.type	fd, @object
	.size	fd, 4
fd:
	.zero	4
	.section	.rodata
	.align 8
.LC0:
	.string	"Welcome to serial program test"
.LC1:
	.string	"/dev/ttyUSB2"
	.align 8
.LC2:
	.string	"open_port:Unable to open /dev/ttyUSB0\n"
.LC3:
	.string	"Error with tcsetattr = %s\n"
.LC4:
	.string	"tcsetattr success"
.LC5:
	.string	"Hello world\n"
.LC6:
	.string	"Thread1"
.LC7:
	.string	"write failed"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$258, %esi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	open@PLT
	movl	%eax, fd(%rip)
	movl	fd(%rip), %eax
	testl	%eax, %eax
	jns	.L2
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	perror@PLT
.L2:
	movl	fd(%rip), %eax
	leaq	-80(%rbp), %rdx
	movq	%rdx, %rsi
	movl	%eax, %edi
	call	tcgetattr@PLT
	leaq	-80(%rbp), %rax
	movl	$4098, %esi
	movq	%rax, %rdi
	call	cfsetispeed@PLT
	leaq	-80(%rbp), %rax
	movl	$4098, %esi
	movq	%rax, %rdi
	call	cfsetospeed@PLT
	movl	-72(%rbp), %eax
	orl	$2176, %eax
	movl	%eax, -72(%rbp)
	movl	-72(%rbp), %eax
	andl	$-49, %eax
	movl	%eax, -72(%rbp)
	movl	-72(%rbp), %eax
	orl	$48, %eax
	movl	%eax, -72(%rbp)
	movl	-72(%rbp), %eax
	andb	$-2, %ah
	movl	%eax, -72(%rbp)
	movl	-72(%rbp), %eax
	andl	$-65, %eax
	movl	%eax, -72(%rbp)
	movl	-72(%rbp), %eax
	andl	$-49, %eax
	movl	%eax, -72(%rbp)
	movl	-72(%rbp), %eax
	orl	$48, %eax
	movl	%eax, -72(%rbp)
	movl	-68(%rbp), %eax
	andl	$-28, %eax
	movl	%eax, -68(%rbp)
	movl	-76(%rbp), %eax
	andl	$-2, %eax
	movl	%eax, -76(%rbp)
	movl	fd(%rip), %eax
	leaq	-80(%rbp), %rdx
	movl	$0, %esi
	movl	%eax, %edi
	call	tcsetattr@PLT
	cmpl	$-1, %eax
	jne	.L3
	call	__errno_location@PLT
	movl	(%rax), %eax
	movl	%eax, %edi
	call	strerror@PLT
	movq	%rax, %rsi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	jmp	.L4
.L3:
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L4:
	movl	fd(%rip), %eax
	movl	$0, %edx
	movl	$4, %esi
	movl	%eax, %edi
	movl	$0, %eax
	call	fcntl@PLT
	movl	fd(%rip), %eax
	movl	$11, %edx
	leaq	.LC5(%rip), %rcx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	write@PLT
	movl	%eax, -96(%rbp)
	leaq	-88(%rbp), %rax
	leaq	.LC6(%rip), %rdx
	movq	%rdx, %rcx
	leaq	thfun(%rip), %rdx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create@PLT
	movl	%eax, -92(%rbp)
	cmpl	$0, -96(%rbp)
	jns	.L6
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
.L6:
	leaq	-97(%rbp), %rax
	movl	$1, %edx
	movq	%rax, %rsi
	movl	$0, %edi
	call	read@PLT
	movl	fd(%rip), %eax
	leaq	-97(%rbp), %rcx
	movl	$1, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	write@PLT
	nop
	jmp	.L6
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.globl	thfun
	.type	thfun, @function
thfun:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$32, %rsp
	movq	%rdi, -24(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
.L9:
	movl	fd(%rip), %eax
	leaq	-9(%rbp), %rcx
	movl	$1, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read@PLT
	leaq	-9(%rbp), %rax
	movl	$1, %edx
	movq	%rax, %rsi
	movl	$1, %edi
	call	write@PLT
	nop
	jmp	.L9
	.cfi_endproc
.LFE1:
	.size	thfun, .-thfun
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
