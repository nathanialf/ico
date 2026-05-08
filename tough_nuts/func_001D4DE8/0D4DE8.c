extern int D_00565060[];
extern int D_004C49A8[];

void func_001D4DE8(void)
{
    int *base = (int *)((char *)D_00565060 + 0x134);
    int *out = D_004C49A8;
    int i;
    for (i = 0x43D; i >= 0; i--) {
        if (*base == 4) *out = 0;
        out++;
        base = (int *)((char *)base + 0x190);
    }
}
