extern char D_0066CB50[];
extern int D_0062BF40;
extern int D_0062BF48;
extern void pac_makeMaterialTable(int a0);
extern void pac_makeMaterialTableLine(void);
extern int pac_setGifTag(int a0, int a1, unsigned long long a2);

int pac_closeTag(int a0, int a1) {
    register int mask = 0x0FFFFFFF;
    char *base = D_0066CB50;
    unsigned int count = (unsigned int)((*(int *)(base + 0x2C) & mask) - *(int *)(base + 0x28)) >> 4;
    if (count == 1) {
        *(int *)(base + 0x20) = 0;
        *(int *)(base + 0x24) = 0;
        *(int *)(base + 0x28) = 0;
        return 0;
    }
    pac_makeMaterialTable(count);
    {
        unsigned int n = (unsigned int)((*(int *)(base + 0x2C) & mask) - *(int *)(base + 0x28)) >> 4;
        int div = *(int *)(base + 0x30);
        unsigned long long q = (n - 1) / div;
        volatile int * volatile *pp = (volatile int * volatile *)(base + 0x20);
        volatile int *head;
        int r;
        pac_setGifTag(a0, a1, q);
        pac_makeMaterialTableLine();
        head = *pp;
        *head = 0;
        r = ((unsigned int)((*(int *)(base + 0x2C) & mask) - (int)head) >> 4) << 4;
        (*pp)[1] = 0;
        D_0062BF40 += r;
        D_0062BF48 += 1;
        return r;
    }
}
