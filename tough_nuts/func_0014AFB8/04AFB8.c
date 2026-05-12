extern int D_006AA4B0[1000];

unsigned int func_0014AFB8(int a0, int key)
{
    char *base = (char *)D_006AA4B0;
    int n;
    int i;
    char *p;
    n = *(int *)(base + 0x4B0);
    if (n > 0) {
        i = 0;
        p = base;
        while (1) {
            if (*(int *)p == key) {
                return *(unsigned char *)(p + 0x320);
            }
            i++;
            p += 4;
            if (i >= n) break;
        }
    }
    return 0;
}
