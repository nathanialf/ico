void func_0013C488(int **dst, char *src)
{
    dst[0] = (int *)src;
    dst[1] = (int *)(src + *(unsigned short *)(src + 2) * 4);
    dst[2] = (int *)(src + *(unsigned short *)(src + 6) * 4);
    dst[3] = (int *)(src + *(unsigned short *)(src + 0xA) * 4);
}
