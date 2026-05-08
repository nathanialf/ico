extern int D_00631B7C;
extern char D_00553E00[];
extern char D_00553E28[];
extern void func_001A6E28(char *p);
extern void func_0010D520(void);

void func_0010DAD0(void)
{
    int v = D_00631B7C;
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
}
