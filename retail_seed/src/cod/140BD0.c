extern int D_00633B98;
extern int D_00712CC0[];
extern char D_00633BA0[];
extern void func_001A6E28(char *fmt, int idx);

void func_00240BD0(int self) {
    int n;
    int i;
    n = D_00633B98;
    i = 0;
    if (n > 0) {
        do {
            if (self == D_00712CC0[i]) {
                func_001A6E28(D_00633BA0, i);
                n = D_00633B98;
            }
            i++;
        } while (i < n);
    }
}
