extern char D_002E4D64[];

void func_00193F78(void)
{
    *(short *)(D_002E4D64 + 0x42) = 0;
    *(int *)(D_002E4D64 + 0x48) = (*(int *)(D_002E4D64 + 0x48) | 0x200000) & ~0x40000;
}
