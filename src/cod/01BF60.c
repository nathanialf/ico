extern void func_00118FD8(int p, int four);

void func_0011BF60(int *p, int len)
{
    int n = len >> 4;
    if (n > 0) {
        int *cur = p;
        do {
            func_00118FD8((int)cur, 4);
            cur = (int *)((char *)cur + 0x10);
        } while (--n != 0);
    }
}
