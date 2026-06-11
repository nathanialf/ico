int GetEnemyHitNodeFlag(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int count = *(int *)((char *)p + 0x88);
    int result = 0;
    if (count > 0) {
        int *q = *(int **)((char *)p + 0x7F0);
        int *base = *(int **)((char *)q + 0x14);
        int i;
        for (i = 0; i < count; i++) {
            if (base[i] == 0) {
                result++;
            }
        }
    }
    return result;
}
