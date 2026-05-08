void func_0013F960(void *a0, int a1)
{
    int *p = *(int **)((char *)a0 + 0x2C);
    while (p != 0) {
        if (*(int *)((char *)p + 0x1C) == a1) {
            *(int *)((char *)p + 0x18) = 1;
        }
        p = *(int **)((char *)p + 0x8);
    }
}
