int func_001CE998(char *self, int idx) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    int *arr = *(int **)(p + 0x14);
    return arr[idx] == 0;
}
