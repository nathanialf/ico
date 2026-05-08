extern int D_004BEE60[];

int func_001BA668(int *self, int a1)
{
    void (*fn)(int *);
    int *p;
    fn = (void (*)(int *))D_004BEE60[a1 * 2];
    p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    p[0x8 / 4] = a1;
    if (fn != 0) {
        fn(self);
    }
    return 1;
}
