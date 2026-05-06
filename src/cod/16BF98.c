void func_0026BF98(char *self, char *node) {
    if (node != 0) {
        int idx = *(int *)(node + 0x4);
        char **arr = *(char ***)(self + 0x4C);
        *(char **)node = arr[idx];
        arr[idx] = node;
    }
}
