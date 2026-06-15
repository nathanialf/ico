int CheckFloorAttribute(float *dst, void *a1) {
    unsigned char *src = (unsigned char *)a1;
    if (((signed char *)src)[1] == 0) {
        int count = src[3];
        if (count != 0) {
            float *sp = (float *)(src + src[2] * 8 + 0x10);
            while (count != 0) {
                *dst = *sp;
                dst++;
                sp++;
                count--;
            }
            return 1;
        }
    }
    return 0;
}
