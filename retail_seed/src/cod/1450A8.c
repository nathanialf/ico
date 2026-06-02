void func_002450A8(int *self, int x) {
    *(volatile int *)(self + 0) = x;
    *(volatile int *)(self + 2) = 0;
    *(volatile int *)(self + 1) = x;
}
