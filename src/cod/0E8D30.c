extern int D_007097F0[];

/*
 * GCC explicit-register vars below are NOT inline asm — they're regalloc
 * directives. ee-gcc 2.9-991111 otherwise reuses $a0 for the addu result
 * and folds the +0x14 offset into the lui+addiu, producing 7 functionally
 * identical but byte-different instructions. The pins force stride to
 * $v0, base to $v1, mult result to $a0, leaving the lw to use the +0x14
 * offset against the base in $v1 — matching the original codegen.
 */
int func_001E8D30(int idx)
{
    register int s __asm__("$2") = 0x18;
    register int *b __asm__("$3") = D_007097F0;
    register int prod __asm__("$4") = idx * s;
    b = (int *)((char *)b + prod);
    return *(int *)((char *)b + 0x14);
}
