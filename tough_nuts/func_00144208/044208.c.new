extern char D_006A98B0[];

void func_00144208(int a0, float f12)
{
    char *entry = &D_006A98B0[(a0 & 0xFF) * 64];
    if (*(short *)(entry + 0x10) < 0) return;
    if ((a0 >> 8) != *(unsigned short *)entry) return;
    *(float *)(entry + 0x18) = f12;
}
