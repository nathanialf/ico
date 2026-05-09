extern char D_00557CC8[];
extern char D_00557CD8[];
extern char D_00557CF0[];
extern int D_00632240;
extern int func_00135EB8(int x, char *p, int b);
extern void func_001A6E28(char *p);

void func_00141340(void) {
    int v = func_00135EB8(0x78000, D_00557CC8, 0xFE);
    D_00632240 = v;
    if (v < 0) {
        func_001A6E28(D_00557CD8);
    } else {
        ((void (*)(char *, int, int))func_001A6E28)(D_00557CF0, v, 0x78000);
    }
}
