extern int D_00633780;
extern int D_00632024;
extern char D_0061A8A8[];
extern int func_0013A0F8(int a0, int a1, char *a2, int a3);

int func_001F6DB8(int a0)
{
    int saved = D_00633780;
    int rv;
    D_00633780 = 1;
    rv = func_0013A0F8(D_00632024, a0, D_0061A8A8, 0x17E);
    D_00633780 = saved;
    return rv;
}
