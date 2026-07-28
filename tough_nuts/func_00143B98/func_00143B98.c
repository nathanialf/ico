extern long long D_00633CD8;
extern char D_00557CC8[];
extern char D_00557D60[];
extern unsigned int D_00632220_a[] __asm__("D_00632220");
extern void func_001AD768(char *s, int code);
extern void func_00263FF0(char *s, int code, unsigned int *p);
extern void func_001A6E28();
int func_00143B98(int *a0, int *a1)
{
    long long mask = D_00633CD8;
    long long one = 1;
    int i = 0;
    long long bit = one << i;
    long long v;
loop:
    if ((mask & bit) == 0) goto found;
    i++;
    if (i < 0x40) { bit = one << i; goto loop; }
    func_001AD768(D_00557CC8, 0x1F4);
    func_00263FF0(D_00557CC8, 0x1F4, D_00632220_a);
    bit = one << i;
found:
    v = *(long long *)((char *)a0 + 0x18);
    *(long long *)((char *)a0 + 0x18) = v | bit;
    D_00633CD8 = D_00633CD8 | bit;
    if (i >= 5) {
        func_001A6E28(D_00557D60);
        func_001AD768(D_00557CC8, 0x1F8);
        func_00263FF0(D_00557CC8, 0x1F8, D_00632220_a);
    }
    *a1 = i;
    if (i < 0) return (i << 14) + 0x1D9020;
    return (i << 14) + 0x1E0000;
}
