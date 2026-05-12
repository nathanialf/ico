/* src/cod/04A6B8.c — func_0014A6B8 */

extern int *D_00631AE4;
extern unsigned char D_0055CFD8[];

int func_0014A6B8(int *a0)
{
    int *p = (int *)a0[0x59];
    char *entry;
    int idx;
    if (a0 != D_00631AE4) return 0;
    idx = p[0xC];
    entry = (char *)&D_0055CFD8[0] + idx * 0x50;
    if ((((unsigned int)*(int *)(entry + 0x4C) >> 9) & 1) == 0) return 0;
    return p[0x60];
}
