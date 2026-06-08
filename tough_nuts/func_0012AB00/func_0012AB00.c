void func_0012AB00(int target, int val)
{
    int n = D_0062BF54;
    char *p = (char *)D_0066DBD8;
    int i;
    if (n <= 0) return;
    i = n;
    do {
        int *entry1 = *(int **)(p + 0x280);
        if (target == entry1[0x58 / 4]) {
            int *entry2 = *(int **)(p + 0x284);
            *(float *)((char *)entry2 + 0x1C) = (float)val;
        }
        p += 0x290;
    } while (--i);
}
