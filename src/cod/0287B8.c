void func_001287B8(char *a0, float f12)
{
    if (f12 > 0.0f) {
        *((float *)(((char *)(*((int *)(a0 + 0x824)))) + 0x3C)) = f12;
        return;
    }
    {
        float src = *((float *)(((char *)(*((int *)(a0 + 0x820)))) + 0x3C));
        *((float *)(((char *)(*((int *)(a0 + 0x824)))) + 0x3C)) = src;
    }
}
