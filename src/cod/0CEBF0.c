void func_001CEBF0(char *self, float val) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    *(float *)(p + 0x44) = val;
}
