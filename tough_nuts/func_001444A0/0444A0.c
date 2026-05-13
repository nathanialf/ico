/* src/cod/0444A0.c — func_001444A0 */

extern void func_00140138(int *p);
extern unsigned char D_006A95B0[];

void func_001444A0(void)
{
    int p = (int)&D_006A95B0[0];
    int end = p + 0x300;
    do {
        if (*(unsigned short *)(p + 2) == 0x11) {
            func_00140138((int *)p);
        }
        p += 0x30;
    } while (p < end);
}
