int func_00245088(int *p) {
    unsigned int v = *p;
    *p = v & ~0x100;
    return (v >> 8) & 1;
}
