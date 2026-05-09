extern int   D_00633780;
extern int   D_00633784;
extern int   D_00632014;
extern int   D_00632024;
extern int   D_00633788[];
extern char  D_0061A890[];
extern char  D_0061A8A8[];
extern void  func_001A6E28(char *p);
extern void  func_001AD768(char *buf, int sz);
extern void  func_00263FF0(char *buf, int sz, int *list);
extern int   func_0013A0F8(int a0, int a1, char *file, int line);

int func_001F6CB0(int size)
{
    int rv = 0;
    if (D_00633780 == -1) {
        func_001A6E28(D_0061A890);
        func_001AD768(D_0061A8A8, 0x174);
        func_00263FF0(D_0061A8A8, 0x174, D_00633788);
    }
    if (D_00633780 == 0) {
        D_00633784 = D_00633784 + 0x30 + size;
        rv = func_0013A0F8(D_00632014, size, D_0061A8A8, 0x17B);
    } else if (D_00633780 == 1) {
        rv = func_0013A0F8(D_00632024, size, D_0061A8A8, 0x17E);
    }
    return rv;
}
