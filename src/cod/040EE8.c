extern int D_006A94E0[];

void func_00140EE8(short a0)
{
    int *p = D_006A94E0;
    int *end = (int *)((char *)p + 0xB0);
    do {
        if (*p != 0) {
            *(short *)((char *)p + 0x44) = a0;
        }
        p = (int *)((char *)p + 0x58);
    } while ((int)p < (int)end);
}
