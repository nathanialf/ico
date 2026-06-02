/* src/cod/0AE370.c — func_001AE370 */

extern char D_004B3D10[];

void func_001AE370(void)
{
    int mask = 0xFFFF;
    char *p = D_004B3D10;
    int i = 0x8B;
    p += 0xA80;
    do {
        *(short *)(p + 2) = 0;
        *(short *)(p + 4) = (short)mask;
        p += 0x40;
        i--;
    } while (i >= 0);
}
