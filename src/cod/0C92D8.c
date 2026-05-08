extern int *func_0013A0F8(int a0, int a1, char *p, int line);
extern int func_001C5BA0(char *p);
extern int D_00632010;
extern char D_00618960[];
extern char D_004C0960[];

int *func_001C92D8(void)
{
    int *p = func_0013A0F8(D_00632010, 0x290, D_00618960, 0x41);
    *p = func_001C5BA0(D_004C0960);
    return p;
}
