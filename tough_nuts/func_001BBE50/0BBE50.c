extern int   D_00632010;
extern char  D_006185E8[];
extern int   func_0013A0F8(int handle, int size, char *file, int line);

int func_001BBE50(int unused, void *obj)
{
    int buf = func_0013A0F8(D_00632010, 0xC, D_006185E8, 0x1B);
    int *p = *(int **)((char *)obj + 0x30);
    *(int *)(buf + 4) = 0;
    *p = 0;
    *(int *)buf = (int)p;
    *(int *)(buf + 8) = 0;
    return buf;
}
