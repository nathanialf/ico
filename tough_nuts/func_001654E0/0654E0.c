/* src/cod/0654E0.c — func_001654E0 */

extern char D_002A4C48[];

int func_001654E0(int *self)
{
    int *guard_p = (int *)(*(int **)((char *)self + 0x164))[0x670 / 4];
    if (guard_p[0x1DC / 4] == 0) return 0;
    {
        int idx = self[0x8 / 4];
        unsigned int *entry = (unsigned int *)(D_002A4C48 + idx * 0x4C);
        unsigned int field = entry[0x48 / 4];
        unsigned int v0;
        v0 = (field >> 18) & 1;
        if (v0 != 0) goto zero;
        v0 = (field >> 21) & 1;
        v0 = v0 ^ 1;
        if (v0 != 0) goto zero;
        return 1;
    }
zero:
    return 0;
}
