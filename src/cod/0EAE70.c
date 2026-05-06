int func_001EAE70(char *self, int idx) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    int *arr = *(int **)(p + 0x24);
    int prev = arr[idx];
    arr[idx] = 0;
    return prev;
}
