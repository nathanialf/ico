extern int *func_00258C38(int idx);

int func_0025DCB0(unsigned int a0) {
    if (a0 < 0x30) {
        unsigned char *p = (unsigned char *)func_00258C38(a0);
        if (p[0x51] == 3) {
            p[0x51] = 0;
        }
    }
    return -1;
}
