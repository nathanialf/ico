int func_00245068(int *p) {
    unsigned int v = *p;
    *p = (int)v & -257;
    return (v >> 8) & 1;
}
