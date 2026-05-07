int func_001D4E70(unsigned int *self)
{
    int r;
    unsigned int p = (unsigned int)self + 0x10;
    if (p < self[2]) r = 0; else r = -1;
    return r;
}
