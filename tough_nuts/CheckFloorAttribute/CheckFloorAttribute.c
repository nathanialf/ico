int CheckFloorAttribute(float *dst, void *a1) {
    unsigned char *src = (unsigned char *)a1;
    int count;
    float *sp;
    if (((signed char *)src)[1] != 0) goto ret0;
    count = src[3];
    if (count == 0) goto ret0;
    sp = (float *)(src + src[2] * 8 + 0x10);
    do {
        *dst = *sp;
        dst++;
        sp++;
        count--;
    } while (count != 0);
    return 1;
ret0:
    return 0;
}
