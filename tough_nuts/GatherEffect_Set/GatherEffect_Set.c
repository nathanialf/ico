extern void *InitParticleLayoutGeo(void *a0);

int GatherEffect_Set(int a0) {
    int acc = 0;
    if (a0 >= 0) {
        int *p = (int *)InitParticleLayoutGeo((void *)a0);
        int count;
        if (p == 0)
            return 1;
        count = *(int *)((char *)p + 0x30);
        if (count > 0) {
            char *base = *(char **)((char *)p + 0x24);
            int i = 0;
            int stride = 0x70;
            do {
                acc |= *(int *)(base + i * stride);
                stride = 0x70;
            } while (++i < count);
        }
    }
    return acc == 0;
}
