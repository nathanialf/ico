extern int D_00631B7C;
extern char D_00553E00[];
extern char D_00553E28[];
extern char D_00660A40[];
extern void func_001A6E28(char *p);
extern void func_0010D520(void);
extern void func_0010D830(char *p, char *q);

void func_0010D4A8(void)
{
    int v;
    char *base;
    v = D_00631B7C;
    if (v < 0) {
        func_001A6E28(D_00553E00);
        func_0010D520();
        v = D_00631B7C;
    }
    v++;
    D_00631B7C = v;
    if (v >= 0x40) {
        func_001A6E28(D_00553E28);
        v = 0x3F;
        D_00631B7C = v;
    }
    base = D_00660A40 + D_00631B7C * 0x10;
    func_0010D830(base, base - 0x10);
}
