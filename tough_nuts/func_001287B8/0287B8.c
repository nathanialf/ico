void func_001287B8(char *a0, float f12)
{
    char *dst = *(char **)(a0 + 0x824);
    if (f12 > 0.0f) {
        *(float *)(dst + 0x3C) = f12;
    } else {
        char *src = *(char **)(a0 + 0x820);
        *(float *)(dst + 0x3C) = *(float *)(src + 0x3C);
    }
}
