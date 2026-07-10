typedef struct GObj {
    char pad[0xB4];
    int *unkB4;
} GObj;

extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void BoxBarSoundOn(int a0, int a1);
extern void warpGirlInStage(float, float, float);
extern int D_004CE9E0[];
extern int GetDataFileName2(void);
extern float D_00629A38;

void func_00236738(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x28) == 0) {
        stage_KillPlayBgAnimation(0x8B, 0, 0);
        D_004CE9E0[1] = (int)GetDataFileName2;
        gobj->unkB4 = D_004CE9E0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x8B, 0, -1);
        if (func_00178DB0(0x7B) == 0) {
            warpGirlInStage(D_00629A38, 272.0f, 0.0f);
        }
    }
}
