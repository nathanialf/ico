extern int D_00553BE0[];
extern float func_00168C18(int *a, int *b);
extern void func_001A6E28(int *a);

void func_00106D68(int *self) {
    char *p = (char *)self[0x15C/4];
    float r = func_00168C18((int *)(p + 0x1D0), (int *)(p + 0x250));
    *(float *)(p + 0x254) = r;
    func_001A6E28(D_00553BE0);
}
