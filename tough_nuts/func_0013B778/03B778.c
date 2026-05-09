extern int D_002811C0[];

int func_0013B778(int a, int b)
{
    int *p = D_002811C0;
    int count = 0;
    do {
        count++;
        if (p[0] == a) {
            if (p[1] == b) {
                return p[2];
            }
        }
        p = (int *)((char *)p + 0x200);
    } while (count < 2);
    return -1;
}
