extern int D_00632010;
extern char D_00619D98[];
extern short *func_0013A0F8(int handle, int size, char *file, int line);
extern int func_00264D60(void);

short *func_001E6968(int a0, int *self)
{
    short *r = func_0013A0F8(D_00632010, 12, D_00619D98, 0x1C);
    *(int *)r = self[0x30 / 4];
    r[2] = (short)func_00264D60();
    r[3] = (short)func_00264D60();
    r[4] = (short)func_00264D60();
    r[5] = 0;
    return r;
}
