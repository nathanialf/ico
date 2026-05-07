extern int D_0070D4D8[];

/* See 0E8D30.c for the explicit-register-vars rationale. Write variant:
 * stride goes to $v1, base to $v0 so the sw uses $v0 for its base. */
void func_001F1148(int idx, int val)
{
    register int s __asm__("$3") = 0x18;
    register int *b __asm__("$2") = D_0070D4D8;
    register int prod __asm__("$4") = idx * s;
    b = (int *)((char *)b + prod);
    *(int *)((char *)b + 0x14) = val;
}
