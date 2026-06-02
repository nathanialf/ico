void func_00251BD0(char *self, int a, int b, int c) {
    char *p = *(char **)(self + 0x40);
    *(int *)(p + 0x94) = a;
    *(int *)(p + 0x98) = b;
    *(int *)(p + 0x9C) = c;
}
