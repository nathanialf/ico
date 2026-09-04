extern int D_00631AE8__mccb __asm__("D_00631AE8");
extern int ACTReserveTarget(int a0, void *a1, int a2);
extern void actEnemyKidnapBegin(void *a0, float f12);
extern void memset(void *a0, int a1, int a2);
extern void func_0010E158(void *self, short y);
extern void GetHeightOfFieldPlaneDifference(int a0, void *a1, int a2, int a3, void *a4,
                                            float f12, float f13, float f14, float f15);
extern void ACTGameCollisionOff(int a0);
extern void func_001919A0__mccb(void *a0, int a1) __asm__("func_001919A0");

int MoveChestForCatchBoy(void *a0) {
    float buf[4];
    int *s17 = *(int **)((char *)a0 + 0x164);

    if (D_00631AE8__mccb == 0) {
        return 0;
    }
    if (ACTReserveTarget(D_00631AE8__mccb, a0, 0xEF) == 0) {
        return 0;
    }
    if (*(int *)(*(int *)((char *)D_00631AE8__mccb + 0x164) + 0x30) == 0x6B) {
        return 0;
    }
    actEnemyKidnapBegin(a0, 50.0f);
    memset(buf, 0, 0x10);
    buf[3] = 1.0f;
    func_0010E158(buf, -0x8000);
    GetHeightOfFieldPlaneDifference(D_00631AE8__mccb, a0, 2,
        *(int *)(*(int *)(*(int **)((char *)a0 + 0x164) + 0x670 / 4) + 0x1EC),
        buf, 18.0f, 0.0f, 0.0f, 1.0f);
    s17[0x138 / 4] = D_00631AE8__mccb;
    *(int *)(*(int *)((char *)D_00631AE8__mccb + 0x164) + 0x134) = (int)a0;
    ACTGameCollisionOff(D_00631AE8__mccb);
    func_001919A0__mccb(a0, 9);
    func_001919A0__mccb(a0, 7);
    return 1;
}

