extern char D_004B3D10[];
extern char D_004B3B68[];
extern void func_002641D8(char *p, int a, int len);
extern void func_001A1008(void);

void func_001ADBC0(void)
{
    int i;
    unsigned short (*a)[32] = (unsigned short (*)[32])D_004B3D10;
    for (i = 0; i < 0xB6; i++) {
        a[i][1] = 0;
        a[i][2] = 0xFFFF;
    }
    func_002641D8(D_004B3B68, 0, 0x1A0);
    func_001A1008();
}
