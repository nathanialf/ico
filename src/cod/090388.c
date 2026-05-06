int func_00190388(char *self) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    return *(int *)(p + 0x68) == *(int *)(p + 0x74) - 1;
}
