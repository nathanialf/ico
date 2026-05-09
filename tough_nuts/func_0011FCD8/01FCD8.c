extern int func_001FBAA8(int a, int b, int c);
extern int func_001FB8B8(int a, int b, int c);

int func_0011FCD8(short *self, int *a1)
{
    if (self[0x80 / 2] != -1) {
        int v = a1[0] + self[0x80 / 2] * 0x70;
        func_001FBAA8(2, v, 6);
        return func_001FB8B8(2, v, 6);
    }
    return 0;
}
