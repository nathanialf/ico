extern char D_006A3070[];

char *soundDataAreaGet(int *a0) {
    int key = *a0;
    char *p = D_006A3070;
    char *q = D_006A3070;
    char *ret = D_006A3070;
    char *end = D_006A3070 + 0x300;
    do {
        if (*(int *)p == key) goto found;
        p += 0x30;
        q += 0x30;
        ret += 0x30;
    } while ((int)q < (int)end);
    return 0;
found:
    return ret;
}
