extern char D_006A98B0[];

float func_001441C8(int a0)
{
    char *entry;
    short id;
    entry = &D_006A98B0[(a0 & 0xFF) * 64];
    id = *(short *)(entry + 0x10);
    if (id < 0) return 0.0f;
    if ((a0 >> 8) != *(unsigned short *)entry) return 0.0f;
    return *(float *)(entry + 0x18);
}
