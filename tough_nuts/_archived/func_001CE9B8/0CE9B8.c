int func_001CE9B8(char *self)
{
    int *obj = *(int **)(self + 0x15C);
    int count = obj[0x22];
    int zc = 0;
    if (count > 0) {
        int *p = *(int **)((char *)obj[0x200] + 0x14);
        do {
            int v = *p;
            int next = zc + 1;
            p++;
            count--;
            if (v == 0) zc = next;
        } while (count != 0);
    }
    return zc;
}
