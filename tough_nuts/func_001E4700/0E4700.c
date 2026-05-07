void func_001E4700(int *a0, int a1, int a2)
{
    int *v1 = (int *)((char *)a0[0x15C / 4] + 0x470);
    if (v1[0x18 / 4] != 0) {
        return;
    }
    v1[0x20 / 4] = a1;
    v1[0x1C / 4] = a2;
}
