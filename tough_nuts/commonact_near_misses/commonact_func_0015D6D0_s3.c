void func_0015D6D0(volatile int a0) {
    char *s164 = *(char **)(a0 + 0x164);
    int b1, b2, b3;
    CylinderCollision((void *)a0, s164 + 0x5A0);
    b1 = a0;
    b2 = a0;
    b3 = a0;
    *(int *)(*(int *)(*(int *)(b1 + 0x164) + 0x670) + 0x250) = 0;
    *(void **)(s164 + 0x150) = *(void **)(s164 + 0x60C);
    *(int *)(*(int *)(*(int *)(b2 + 0x164) + 0x670) + 0x258) = 0;
    *(int *)(*(int *)(*(int *)(b3 + 0x164) + 0x670) + 0x25C) = 0;
    for (;;) {
        int c1 = a0;
        int c2 = a0;
        int c3 = a0;
        *(int *)(*(int *)(*(int *)(c1 + 0x164) + 0x678) + 0x3A0) =
            (0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1] * 3;
        if (*(int *)(*(int *)(*(int *)(c2 + 0x164) + 0x670) + 0x250) >
            *(int *)(*(int *)(*(int *)(c3 + 0x164) + 0x670) + 0x254)) {
            BoxBarSoundOn((void *)a0, 0x6C);
        }
        *(int *)(*(int *)(*(int *)(a0 + 0x164) + 0x670) + 0x250) += 1;
        _ACTWait__p4(1);
    }
}
