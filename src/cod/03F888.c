void func_0013F888(void *a0)
{
    int *p = *(int **)((char *)a0 + 0x2C);
    while (p != 0) {
        *(int *)((char *)p + 0x18) = 1;
        p = *(int **)((char *)p + 0x8);
    }
}
