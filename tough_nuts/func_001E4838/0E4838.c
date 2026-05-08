extern char D_00565060[];

int func_001E4838(void *a0)
{
    void *p = *(void **)((char *)a0 + 0x15C);
    int idx = *(int *)((char *)p + 0x4A0);
    return ((unsigned int)*(int *)(D_00565060 + idx * 0x190 + 0x184) >> 28) & 3;
}
