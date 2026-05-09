extern char D_00632428[];
extern void func_001A6E28(char *str, int i);
extern void func_0016A1D8(int *p);

void func_0016A240(int *p) {
    int i = 0;
    do {
        func_001A6E28(D_00632428, i);
        i++;
        func_0016A1D8(p);
        p = (int *)((char *)p + 0x10);
    } while (i < 4);
}
