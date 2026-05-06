void func_00190430(char *self, int val) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    *(int *)p = val;
}
