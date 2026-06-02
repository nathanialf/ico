extern float func_00168C18(int *buf, int *dest);

void func_0010AC88(long long *src, int *dest) {
    long long buf[2];
    buf[0] = src[0];
    buf[1] = src[1];
    *(float *)((char *)dest + 4) = func_00168C18((int *)buf, dest);
}
