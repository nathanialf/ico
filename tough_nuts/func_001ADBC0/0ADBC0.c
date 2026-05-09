extern char D_004B3D10[];
extern char D_004B3B68[];
extern void func_002641D8(char *p, int a, int len);
extern void func_001A1008(void);

void func_001ADBC0(void) {
    char *p = D_004B3D10;
    int i = 0xB5;
    do {
        *(short *)(p + 0x2) = 0;
        *(short *)(p + 0x4) = (short)0xFFFF;
        p += 0x40;
        i--;
    } while (i >= 0);
    func_002641D8(D_004B3B68, 0, 0x1A0);
    func_001A1008();
}
