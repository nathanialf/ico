int func_00245088(int *p) {
    unsigned int v = *p;
    *p = (int)v & -257;
    return (v >> 8) & 1;
}
