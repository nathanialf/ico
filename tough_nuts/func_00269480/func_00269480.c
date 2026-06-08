int func_00269480(long long x) {
    int lx = (int)x;
    int hx = (int)(x >> 32);
    hx &= 0x7fffffff;
    hx |= (unsigned int)(lx | -lx) >> 31;
    hx = 0x7ff00000 - hx;
    return (unsigned int)hx >> 31;
}
