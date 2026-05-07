extern int D_00632C80;
extern void func_00247608(int a0);

int func_001AA580(void)
{
    register int rv __asm__("$2") = 0;
    int s0 = D_00632C80;
    int sentinel = -1;
    if (s0 != sentinel) {
        D_00632C80 = sentinel;
        func_00247608(s0);
        D_00632C80 = sentinel;
    }
    return rv;
}
