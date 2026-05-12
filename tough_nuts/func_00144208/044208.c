extern char D_006A98B0[];

void func_00144208(int a0, float f12)
{
    char *entry;
    short id;
    entry = &D_006A98B0[(a0 & 0xFF) * 64];
    id = *(short *)(entry + 0x10);
    if (id < 0) return;
    a0 = a0 >> 8;
    if (a0 != *(unsigned short *)entry) return;
    *(float *)(entry + 0x18) = f12;
}
