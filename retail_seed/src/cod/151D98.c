extern char *D_005524A4[];

void func_00251D98(int val) {
    char *p = *(char **)(D_005524A4[0] + 0x40);
    *(int *)(p + 0xD8) = val;
}
