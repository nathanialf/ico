void func_00203CB8(char *self, int val) {
    char *sub = *(char **)(self + 0x164);
    if (sub != 0) {
        *(int *)(sub + 0x438) = val;
    }
}
