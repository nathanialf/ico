extern char D_00559CC0[];
extern char D_004CC1E0[];
extern void func_001A6E28(char *p);
extern int func_00205498(int x);

void func_00178930(int *self)
{
    int idx;
    char *base;
    if ((int)self[0x64/4] >= 0) {
        func_001A6E28(D_00559CC0);
        idx = self[0x64/4];
        base = D_004CC1E0 + idx * 64;
        func_00205498(*(int *)(base + 0x20));
        self[0x64/4] = -1;
    }
}
