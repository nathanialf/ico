int func_001EA228(char *self, char *src) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    *(unsigned short *)(p + 0x20) = *(unsigned short *)(src + 0x30);
    *(int *)(p + 0x24) = *(short *)(src + 0x32);
    return 1;
}
