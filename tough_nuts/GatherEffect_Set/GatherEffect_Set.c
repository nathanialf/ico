extern void *InitParticleLayoutGeo(void *a0);

int GatherEffect_Set(int a0) {
    int acc = 0;
    char *p;
    char *base;
    int count;
    int i;
    int stride;
    if (a0 < 0)
        goto done;
    p = (char *)InitParticleLayoutGeo((void *)a0);
    if (p == 0)
        return 1;
    base = *(char **)(p + 0x24);
    count = *(int *)(p + 0x30);
    if (count <= 0)
        goto done;
    i = 0;
    stride = 0x70;
    do {
        acc |= *(int *)(base + i * stride);
        stride = 0x70;
    } while (++i < count);
done:
    return acc == 0;
}
