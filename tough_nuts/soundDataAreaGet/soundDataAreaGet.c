extern char D_006A3070[];

char *soundDataAreaGet(int *a0) {
    int key = *a0;
    char *p = D_006A3070;
    char *end = p + 0x300;
    char *r = p;
    do {
        char *snap = p;
        if (*(int *)p == key) goto found;
        p += 0x30;
        r = snap + 0x30;
    } while ((int)p < (int)end);
    return 0;
found:
    return r;
}
