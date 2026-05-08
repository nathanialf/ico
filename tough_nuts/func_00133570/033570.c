extern int func_00131C90(int *p, int *self, int n);

int func_00133570(int *self, int max, int *p)
{
    unsigned int v = (unsigned int)p[0x138/4] - (unsigned int)p[0x24/4];
    int n;
    if ((int)v < max) {
        n = v;
    } else {
        n = max;
    }
    if (n != 0) {
        func_00131C90(p, self, n);
    }
    return n;
}
