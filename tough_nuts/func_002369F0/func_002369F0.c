extern char *actSt25aQueenDeadChk(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004CEB80[];
extern void func_00236420(void);

void func_002369F0(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x2E) == 0) {
        stage_KillPlayBgAnimation(0x93, 0, 0);
        *(int *)(actSt25aQueenDeadChk(0x1CB) + 0x16C) = 0;
        D_004CEB80[1] = (int)func_00236420;
        gobj->unkB4 = D_004CEB80;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x94, 0, -1);
        *(int *)(actSt25aQueenDeadChk(0x1CB) + 0x16C) = 1;
    }
}
