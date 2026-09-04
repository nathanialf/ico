/* __fixdfdi — parked near-miss (clean rc14; barrier form reaches the shape
 * but needs a RETIRED crutch). Apply replacing the INCLUDE_ASM line.
 * The `_i` decls are typed __asm__ aliases (prototypes, not crutches).
 *
 * ROM keeps the literal 0 in a callee-saved reg ($s1, `daddu s1,zero,zero`) and
 * reuses it as the 2nd arg to dpcmp and 1st arg to dpsub, with
 * a0 in $s0; frame is -0x30 (saves s1). The clean form below passes $0 directly
 * (frame -0x20, rc14). Forcing the 0 into $s1 across the calls is the MATERIALIZE
 * idiom (`__asm__("":"+r"(zero))`), which is retired — left parked until a clean
 * dev shape (or permuter) reproduces it. */
extern long func_0025D748_i(int a0) __asm__("__fixunsdfdi");
extern int func_0025F4A0_i(int a0, int a1) __asm__("dpcmp");
extern int func_0025EF10_i(int a0, int a1) __asm__("dpsub");

long __fixdfdi(int a0) {
    int ret = func_0025F4A0_i(a0, 0);
    if (ret < 0) {
        ret = func_0025EF10_i(0, a0);
        return -func_0025D748_i(ret);
    }
    return func_0025D748_i(a0);
}
