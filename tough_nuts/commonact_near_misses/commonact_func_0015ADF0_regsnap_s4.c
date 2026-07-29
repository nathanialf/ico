void func_0015ADF0(volatile int a0) {
    char *s164 = *(char **)(a0 + 0x164);
    int self15C = a0;
    void *self = (void *)a0;
    int *other = 0;
    int *target;
    int *cand;
    char *s15C;

    *(void **)(s164 + 0x18) = (void *)func_0015F650;
    s15C = *(char **)(self15C + 0x15C);
    *(int *)(s15C + 0x5F8) = 0;
    if (func_00165418(self, &other)) {
        target = other;
        goto found;
    }
    if ((func_00165488((void *)a0) && (cand = D_00631AE4__adf0) != 0) ||
        (cand = D_00631AE8__adf0) != 0) {
        target = cand;
        goto found;
    }
    target = D_00631AE4__adf0v;
found:
    ReviveEnemyParticle((void *)a0, 0);
    actCommonDown__adf0((void *)a0, target,
                  (D_00631AE8__adf0 != 0 &&
                   *(int *)(*(int *)((char *)D_00631AE8__adf0 + 0x164) + 0x30) == 0x6B &&
                   *(int *)(*(int *)((char *)D_00631AE8__adf0 + 0x164) + 0x134) == a0) ||
                      D_00632DB4 != 0);
}
