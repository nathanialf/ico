int func_0010A0C8(float *dst, char *src)
{
    int i;
    int n;
    int idx;
    int offset;
    float *p;
    if (src[1] != 0) return 0;
    n = (unsigned char)src[3];
    if (n == 0) return 0;
    idx = (unsigned char)src[2];
    offset = idx * 8 + 0x10;
    p = (float *)(src + offset);
    for (i = 0; i < n; i++) {
        *dst++ = *p++;
    }
    return 1;
}
