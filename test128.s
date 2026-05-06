	.file	1 "/tmp/test128.c"
	.section .mdebug.eabi64
	.previous
gcc2_compiled.:
__gnu_compiled_c:
	.text
	.align	2
	.p2align 3,,7
	.globl	copy
	.text
	.ent	copy
copy:
	.frame	$sp,0,$31		# vars= 0, regs= 0/0, args= 0, extra= 0
	.mask	0x00000000,0
	.fmask	0x00000000,0
	ldl	$2,7($5)
	ldr	$2,0($5)
	ldl	$3,15($5)
	ldr	$3,8($5)
	sdl	$2,7($4)
	sdr	$2,0($4)
	sdl	$3,15($4)
	.set	noreorder
	.set	nomacro
	j	$31
	sdr	$3,8($4)
	.set	macro
	.set	reorder

	.end	copy
