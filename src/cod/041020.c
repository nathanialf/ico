short func_00141020(char *self, int idx) {
    char *base = *(char **)(self + 0x2C);
    base += idx * 4;
    return *(short *)(base + 0x3C);
}
