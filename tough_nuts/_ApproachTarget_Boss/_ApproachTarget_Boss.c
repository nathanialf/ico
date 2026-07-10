static inline unsigned char _ApproachTargetReady_Boss(int self)
{
    int *d;
    if (*(int *)(*(int *)(self + 0x164) + 0x128) == 0) {
        return 0;
    }
    if (D_00629DE8 == 0) {
        return 0;
    }
    d = *(int **)(D_00629DE8 + 0x164);
    if (d == 0) {
        return 0;
    }
    if (d[0x30 / 4] != 0x6B) {
        return 0;
    }
    if (d[0x124 / 4] != self) {
        return 0;
    }
    return 1;
}

void _ApproachTarget_Boss(volatile int a0)
{
    void _ACTWait(int a0);
    void iosOmBeforeFuncStandard(void *a0, int a1, void *a2);
    void ACTParaStatus_Clear(void *a0);
    void func_00178E08(int a0);

    *(long long *)(*(int *)(a0 + 0x164) + 0x140) &= ~0x100000000LL;
    func_0018F2A0((void *)a0, 4);

    if (_ApproachTargetReady_Boss(a0)) {
        void *self2 = (void *)a0;
        int p = *(int *)((char *)self2 + 0x164);
        void *q;
        *(void **)(p + 0x128) = (void *)D_00629DE8;
        iosOmBeforeFuncStandard((void *)D_00629DE8, 0x2F, self2);
        q = *(void **)(p + 0x128);
        *(int *)(*(int *)((char *)q + 0x15C) + 0x74) = 1;
        ACTParaStatus_Clear(q);
        func_00178E08(0x167);
        *(void **)(p + 0x128) = 0;
        if (*(int *)(p + 0x30) == 5) {
            func_0018F2A0((void *)a0, 4);
        }
    }
    for (;;) {
        _ACTWait(0x1E);
        *(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x670) + 0x200) = 0;
        *(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x670) + 0x20C) = D_0062A670;
    }
}
