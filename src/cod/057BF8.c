extern int *func_0015EFF8(int *self);
extern void func_00104360(int *self, int *a1);

void func_00157BF8(int *self, int *a1) {
    int *p = func_0015EFF8(self);
    *(float *)((char *)a1 + 4) = *(float *)((char *)p + 4);
    func_00104360(self, a1);
}
