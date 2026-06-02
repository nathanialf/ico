extern void func_0013F6B8(void *a0);

void func_0013F8C0(void *a0)
{
    void *p = *(void **)((char *)a0 + 0x2C);
    while (p != 0) {
        func_0013F6B8(p);
        p = *(void **)((char *)p + 0x8);
    }
}
