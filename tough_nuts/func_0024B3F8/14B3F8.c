extern int D_005508C8[];
extern void func_0024B3E8(int x, int y);

void func_0024B3F8(void)
{
    int *p = D_005508C8;
    int i = 0;
    do {
        i++;
        func_0024B3E8(p[0], p[1]);
        p += 2;
    } while (i < 6);
}
