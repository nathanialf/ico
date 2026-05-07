extern char D_00280F88[];

int func_00137FD8(long *a0)
{
    register long *v1 __asm__("$3");
    register int a3 __asm__("$7");
    register char *a0_arg __asm__("$4");
    register long *a1_arg __asm__("$5");
    register int a2_arg __asm__("$6");
    register long v0 __asm__("$2");
    register int rv __asm__("$2");

    __asm__ volatile("daddu %0, %1, $0" : "=r"(v1) : "r"(a0));
    __asm__ volatile("addiu %0, $0, 0x6" : "=r"(v0));
    __asm__ volatile("sw %0, 4(%1)" : : "r"(v0), "r"(v1) : "memory");
    __asm__ volatile("addiu %0, $0, -2" : "=r"(a3));
    __asm__ volatile("lui %0, %%hi(D_00280F88)" : "=r"(a0_arg));
    __asm__ volatile("daddu %0, %1, $0" : "=r"(a1_arg) : "r"(v1));
    __asm__ volatile("ld %0, 0(%1)" : "=r"(v0) : "r"(v1));
    __asm__ volatile("addiu %0, %0, %%lo(D_00280F88)" : "+r"(a0_arg));
    __asm__ volatile("daddu %0, $0, $0" : "=r"(a2_arg));
    __asm__ volatile("and %0, %0, %1" : "+r"(v0) : "r"(a3));
    __asm__ volatile("sd %0, 0(%1)" : : "r"(v0), "r"(v1) : "memory");
    __asm__ volatile("jal func_0013A5B8" : "=r"(rv) : "r"(a0_arg), "r"(a1_arg), "r"(a2_arg), "r"(a3) : "$31", "memory");
    return rv;
}
