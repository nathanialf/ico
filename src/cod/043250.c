extern char D_006A98B0[];
extern int func_0025DA68(int a0);

void func_00143250(int a0)
{
    char *entry;
    short id;
    entry = &D_006A98B0[(a0 & 0xFF) * 64];
    id = *(short *)(entry + 0x10);
    if (id < 0) return;
    a0 = a0 >> 8;
    if (a0 != *(unsigned short *)entry) return;
    func_0025DA68(id);
}
