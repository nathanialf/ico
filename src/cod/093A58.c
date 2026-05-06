int func_00193A58(short *dst, char *self) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    dst[0] = *(unsigned short *)(p + 0x50);
    dst[1] = *(unsigned short *)(p + 0x8);
    return 1;
}
