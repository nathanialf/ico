extern char D_006A3070[];

char *soundDataAreaGet(int *a0) {
    int key = *a0;
    char *p = D_006A3070;
    char *r = D_006A3070;
    char *end = D_006A3070 + 0x300;
    do {
        char *next = r + 0x30;
        if (*(int *)p == key) goto found;
        p += 0x30;
        r = next;
    } while ((int)p < (int)end);
    return 0;
found:
    return r;
}
