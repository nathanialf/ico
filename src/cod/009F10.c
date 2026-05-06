char func_00109F10(char *self, int idx) {
    char *sub = *(char **)(self + 0x15C);
    char *table = *(char **)(sub + 0x810);
    return table[idx];
}
