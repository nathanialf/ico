extern int D_00632014;
extern char D_0061AC60[];
extern int D_004C7710[];
extern int func_0013A0F8(int handle, int size, char *file, int line);

void func_001FBB48(void)
{
    D_004C7710[0] = 0;
    D_004C7710[1] = func_0013A0F8(D_00632014, 0x80000, D_0061AC60, 0x86) | 0x30000000;
    D_004C7710[2] = func_0013A0F8(D_00632014, 0x80000, D_0061AC60, 0x87) | 0x30000000;
    D_004C7710[4] = (D_004C7710 + D_004C7710[0])[1];
}
