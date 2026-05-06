extern char *D_00631AE8;

void func_00175C70(int x) {
    char *p = D_00631AE8;
    if (p != 0) {
        char *sub = *(char **)(p + 0x164);
        char *q = *(char **)(sub + 0x678);
        *(int *)(q + 0x3C0) = x;
    }
}
