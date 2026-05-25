extern int D_006A6F30[];
extern int func_00100410(void);
extern int func_0013A0F8(int a0, int a1, const char *fmt, int line);
extern void func_0013A250(int a0, int a1, int a2);
extern int func_0013A5B8(char *a, int b, int c);
extern void func_001A6E28();
extern int D_00632000;
extern const char D_005578D0[];
extern const char D_00557970[];

void func_0013D498(int a0)
{
    int *obj = (int *) D_006A6F30[func_00100410()];
    if (obj[0x48 / 4] == 0)
    {
        int m;
        obj[0x48 / 4] = 1;
        do { } while (0);
        m = func_0013A0F8(D_00632000, 0x50, D_005578D0, 0x1DE);
        obj[0x4C / 4] = m;
        func_0013A250(m, m + 0x30, 8);
    }
    {
        int q = func_0013A5B8((char *) obj[0x4C / 4], a0, 0);
        func_001A6E28(D_00557970, q);
    }
}
