extern void (*D_00717904[])(int);
extern int D_00550924[];
extern int D_00717908[];

void func_0024C4F0(void) {
    void (*f)(int) = D_00717904[0];
    if (f == 0) return;
    if (D_00550924[0] != 0) return;
    f(D_00717908[0]);
}
