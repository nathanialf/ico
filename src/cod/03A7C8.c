extern int *D_006A6990[];
extern void func_0013A2F8(int *p);

void func_0013A7C8(void) {
    int *p;
    int i;
    int **q = D_006A6990;
    i = 0xFF;
    do {
        p = *q++;
        if (p != 0) {
            func_0013A2F8(p);
        }
        i--;
    } while (i >= 0);
}
