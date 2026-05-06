extern char *D_00631AE4;

void func_0017EA00(void) {
    char *p = D_00631AE4;
    if (p != 0) {
        char *sub = *(char **)(p + 0x164);
        *(long long *)(sub + 0x20) |= 0x1000LL;
    }
}
