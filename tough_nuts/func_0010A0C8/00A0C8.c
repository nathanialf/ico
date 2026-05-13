int func_0010A0C8(float *dst, char *src)
{
    int i, n;
    float *p;
    if (src[1] != 0) return 0;
    n = (unsigned char)src[3];
    if (n == 0) return 0;
    p = (float *)(src + (unsigned char)src[2] * 8 + 0x10);
    for (i = 0; i < n; i++) {
        *dst++ = *p++;
    }
    return 1;
}
