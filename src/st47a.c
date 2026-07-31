#include "common.h"

typedef struct ActB4Obj {
    char pad[0xC4];
    int *unkC4;
} ActB4Obj;



extern void *D_00631AE8;
extern void func_0017B258(int bit_idx);
extern int func_0017B230(int a0);
extern void AddWayPointTop();
extern void stage_KillPlayBgAnimation();
extern void BoxBarSoundOn(int a0, int a1);
extern int D_00274EC0[];
extern int D_004D38B0[];
extern int *D_00631AE4;
extern int D_00631AE8__p4 __asm__("D_00631AE8");
extern void _ACTWait(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void actSt47aEnd(volatile int a0);
extern int func_0012AB50(int a0, int a1, int a2);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int actInitialize(int a0);
extern void func_0017B288(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);

void actSt47aInit(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    int i = 0;
    while (i < (0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1]) {
        if (scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x2D3), 0x1000000) != 0 ||
            scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x2D4), 0x1000000) != 0 ||
            scpSleepSpiderGroupOne((int)D_00631AE4, 0x1000000) != 0 ||
            (D_00631AE8__p4 != 0 && scpSleepSpiderGroupOne(D_00631AE8__p4, 0x1000000) != 0)) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0x65, 1, 0);
    soundSeDefPlayWithVolumeRate(0x4AC, 0, 0, 1);
    while (func_0012AB50(0x65, 0x2D, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    if (scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x2D3), 0x1000000) != 0 ||
        scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x2D4), 0x1000000) != 0 ||
        scpSleepSpiderGroupOne((int)D_00631AE4, 0x1000000) != 0 ||
        scpSleepSpiderGroupOne(D_00631AE8__p4, 0x1000000) != 0) {
        func_0017B258(0x36);
    }
    D_004D38B0[1] = (int)actSt47aEnd;
    obj->unkC4 = D_004D38B0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D38D0[];
extern volatile float D_006316EC;
extern volatile float D_006316F0;
extern volatile float D_006316F4;
extern void _ACTWait(int a0);
extern void actSt47aInit(volatile int a0);
extern int func_0012AB50(int a0, int a1, int a2);
extern void func_0017B288(int a0);
extern void func_0017E870(float a0, float a1, float a2, float a3);
extern int scpKillSpiderGroup(int a0, int a1);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);

void actSt47aEnd(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    while (scpKillSpiderGroup((int)a0, 0x1000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);
    func_0017B288(0x36);
    stage_KillPlayBgAnimation(0x65, 1, 0x2E);
    soundSeDefPlayWithVolumeRate(0x4AC, 0, 0, 1);
    while (func_0012AB50(0x65, 0x32, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    func_0017E870(D_006316EC, D_006316F0, D_006316F4, 100.0f);
    while (func_0012AB50(0x65, 0x5A, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_004D38D0[1] = (int)actSt47aInit;
    obj->unkC4 = D_004D38D0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D3930[];
extern void actSt47aHane1Up(volatile int a0);

void actSt47aSekizo1Chk(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    int i = 0;
    while (i < (0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1]) {
        if (scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x2D3), 0x2000000) != 0 ||
            scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x2D4), 0x2000000) != 0 ||
            scpSleepSpiderGroupOne((int)D_00631AE4, 0x2000000) != 0 ||
            (D_00631AE8__p4 != 0 && scpSleepSpiderGroupOne(D_00631AE8__p4, 0x2000000) != 0)) {
            i++;
        } else {
            i = 0;
        }
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0x66, 1, 0);
    soundSeDefPlayWithVolumeRate(0x4AC, 0, 0, 1);
    while (func_0012AB50(0x66, 0x2D, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    if (scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x2D3), 0x2000000) != 0 ||
        scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x2D4), 0x2000000) != 0 ||
        scpSleepSpiderGroupOne((int)D_00631AE4, 0x2000000) != 0 ||
        scpSleepSpiderGroupOne(D_00631AE8__p4, 0x2000000) != 0) {
        func_0017B258(0x37);
    }
    D_004D3930[1] = (int)actSt47aHane1Up;
    obj->unkC4 = D_004D3930;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHane1Up);

INCLUDE_ASM("asm/nonmatchings/src/st47a", actSt47aHane2Up);

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D39D0[];
extern void _ACTWait(int a0);
extern void actSt47aHane2Up(volatile int a0);
extern int func_0012AA80(int a0);
extern void func_0017B288(int a0);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);

void actSt47aRopeChk(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    while (func_0017B230(0x36) != 0 && func_0017B230(0x37) != 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);
    func_0017B288(0x38);
    stage_KillPlayBgAnimation(0x68, 1, 0);
    soundSeDefPlayWithVolumeRate(0x4AD, 0, 0, 1);
    _ACTWait(0x32);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, 0, 1);
    while (func_0012AA80(0x68) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_004D39D0[1] = (int)actSt47aHane2Up;
    obj->unkC4 = D_004D39D0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int actSt25aQueenDeadChk(int a0);

void actSt47aEnemy1(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0); Generator_Mask(actSt25aQueenDeadChk(0x2CB));
 while(func_0017B230(0x3A)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); Generator_Call(actSt25aQueenDeadChk(0x2CB)); }

extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int actSt25aQueenDeadChk(int a0);

void actSt47aTorch(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0); Generator_Mask(actSt25aQueenDeadChk(0x2CC));
 while(func_0017B230(0x3C)==0){ _ACTWait(1); }
 Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_Call(actSt25aQueenDeadChk(0x2CC)); }

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D3850[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void func_00236C70(volatile int a0);

void actSt47aSekizo1(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x33) == 0) {
        D_004D3850[1] = (int)func_00236C70;
        gobj->unkC4 = D_004D3850;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D3970[];
extern int D_004D3990[];
extern void actSt47aHane2Up(volatile int a0);
extern void actSt47aRopeChk(volatile int a0);

void actSt47aSekizo2(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x38) == 0) {
        stage_KillPlayBgAnimation(0x67, 0, 0);
        D_004D3970[1] = (int)actSt47aHane2Up;
        gobj->unkC4 = D_004D3970;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x67, 0, -1);
        D_004D3990[1] = (int)actSt47aRopeChk;
        gobj->unkC4 = D_004D3990;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D3870[];
extern int D_004D3890[];
extern void actSt47aEnd(volatile int a0);
extern void actSt47aInit(volatile int a0);

void actSt47aSekizo3(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x36) == 0) {
        stage_KillPlayBgAnimation(0x65, 0, 0);
        D_004D3870[1] = (int)actSt47aInit;
        gobj->unkC4 = D_004D3870;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x65, 0, 0x2D);
        D_004D3890[1] = (int)actSt47aEnd;
        gobj->unkC4 = D_004D3890;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D38F0[];
extern int D_004D3910[];
extern void actSt47aHane1Up(volatile int a0);
extern void actSt47aSekizo1Chk(volatile int a0);

void actSt47aSekizo4(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x37) == 0) {
        stage_KillPlayBgAnimation(0x66, 0, 0);
        D_004D38F0[1] = (int)actSt47aSekizo1Chk;
        gobj->unkC4 = D_004D38F0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x66, 0, 0x2D);
        D_004D3910[1] = (int)actSt47aHane1Up;
        gobj->unkC4 = D_004D3910;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D39F0[];
extern void func_00236D20(volatile int a0);

void actSt47aHane1(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x39) == 0) {
        D_004D39F0[1] = (int)func_00236D20;
        gobj->unkC4 = D_004D39F0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);

void actSt47aHane2(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0x3A)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); _ACTWait(0x1E); Generator_Call(a0); }

extern int D_004D3A10[];
extern void func_00236D90(volatile int a0);

void actSt47aRope(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x3B) == 0) {
        D_004D3A10[1] = (int)func_00236D90;
        gobj->unkC4 = D_004D3A10;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

void actSt47aBarricade(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0x3C)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

void actSt47aExit(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00236C70);

extern void func_0017B288(int a0);
extern int D_00631AE8__6d20 __asm__("D_00631AE8");

void func_00236D20(volatile int a0) {
    if (D_00631AE8__6d20 == 0) {
        _ACTWait(0);
    }
    while (scpSleepSpiderGroupOne(D_00631AE8__6d20, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    func_0017B288(0x166);
    func_0017B258(0x39);
    func_0017B258(0x3A);
}

extern int D_00631AE8__6d90 __asm__("D_00631AE8");

void func_00236D90(volatile int a0) {
    if (D_00631AE8__6d90 == 0) {
        _ACTWait(0);
    }
    while (D_00631AE8__6d90 == 0 ||
           scpSleepSpiderGroupOne(actSt25aQueenDeadChk(0x2D4), 0x4000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x12C);
    func_0017B258(0x3B);
    func_0017B258(0x3C);
}

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00236E10);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00236F38);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237088);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237230);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237338);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237428);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237518);

struct CFS { long long a, b; };
extern struct CFS D_0061C310;
extern void soundSeDefPlayWithVolumeRate__75c8(int a0, int a1, void *a2, int a3) __asm__("soundSeDefPlayWithVolumeRate");

void func_002375C8(volatile int a0) {
    struct CFS buf;
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    buf = D_0061C310;
    soundSeDefPlayWithVolumeRate__75c8(0x52A, 0, &buf, 1);
    stage_KillPlayBgAnimation(0x7A, 0, 0);
}

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237638);


void func_002376F0(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x11D) == 0) {
        stage_KillPlayBgAnimation(0x7B, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x7B, 0, -1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237750);

extern unsigned int D_004D3BB0[8];
extern void func_00237AD8(volatile int a0);

void func_002377E8(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x11f) == 0) {
        D_004D3BB0[1] = (unsigned int)func_00237AD8;
        gobj->unkC4 = (int *)D_004D3BB0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern unsigned int D_004D3A30[8];
extern int D_006325B4__7860 __asm__("D_006325B4");

void func_00237860(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_006325B4__7860 = 0;
    *(int *)(gobj + 0xC0) = (int)D_004D3A30;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct KSubB_b898 {
    char pad[0xC0];
    int unkC0;
    int *unkC4;
} KSubB_b898;

extern volatile int D_006325B4__b898 __asm__("D_006325B4");
extern unsigned int D_004D3A70[8];
extern unsigned int D_004D3A90[8];
extern void func_00236E10(volatile int a0);
extern void func_00237930(volatile int a0);

void func_00237898(volatile int a0) {
    KSubB_b898 *s = *(KSubB_b898 **)(a0 + 0x164);
    D_006325B4__b898 = 1;
    s->unkC0 = 0;
    if (func_0017B230(0x11B) != 0) {
        D_004D3A70[1] = (unsigned int)func_00236E10;
        s->unkC4 = (int *)D_004D3A70;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
    D_004D3A90[1] = (unsigned int)func_00237930;
    s->unkC4 = (int *)D_004D3A90;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237930);

extern unsigned int D_004D3B10[8];
extern int D_006325B4__7A00 __asm__("D_006325B4");

void func_00237A00(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_006325B4__7A00 = 0;
    *(int *)(gobj + 0xC0) = (int)D_004D3B10;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct KSubB_ba38 {
    char pad[0xC0];
    int unkC0;
    int *unkC4;
} KSubB_ba38;

extern volatile int D_006325B4__ba38 __asm__("D_006325B4");
extern unsigned int D_004D3B50[8];
extern unsigned int D_004D3B70[8];
extern void func_00237338(volatile int a0);
extern void func_00237428(volatile int a0);

void func_00237A38(volatile int a0) {
    KSubB_ba38 *s = *(KSubB_ba38 **)(a0 + 0x164);
    D_006325B4__ba38 = 1;
    s->unkC0 = 0;
    if (func_0017B230(0x11E) == 0) {
        D_004D3B50[1] = (unsigned int)func_00237338;
        s->unkC4 = (int *)D_004D3B50;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        D_004D3B70[1] = (unsigned int)func_00237428;
        s->unkC4 = (int *)D_004D3B70;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237AD8);

void func_00237B78(void)
{
    if (func_0017B230(0x120) == 0) {
        stage_KillPlayBgAnimation(0x80, 0, 0);
        AddWayPointTop(4, 0);
    } else {
        stage_KillPlayBgAnimation(0x80, 0, -1);
        AddWayPointTop(4, 1);
    }
}

void func_00237BD0(void)
{
    if (D_00631AE8 != 0) {
        if (func_0017B230(0x120) != 0) {
            if (func_0017B230(0x123) == 0) {
                func_0017B258(0x166);
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237C18);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237D18);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237E98);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238000);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002381C0);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238320);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238480);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002385E0);

extern unsigned int D_004D3BF0[8];
extern void func_00238B88(volatile int a0);

void func_00238740(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x120) == 0) {
        D_004D3BF0[1] = (unsigned int)func_00238B88;
        gobj->unkC4 = (int *)D_004D3BF0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern unsigned int D_004D3C50[8];
extern void func_00238C18(volatile int a0);

void func_002387B8(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x121) != 0) {
        stage_KillPlayBgAnimation(0x7F, 0, 0);
        _ACTWait(0xA);
        stage_KillPlayBgAnimation(0x7F, 0, 0x1F4);
    } else {
        stage_KillPlayBgAnimation(0x7F, 0, 0);
    }
    D_004D3C50[1] = (unsigned int)func_00238C18;
    gobj->unkC4 = (int *)D_004D3C50;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern unsigned int D_004D3CF0[8];
extern void func_00238D08(volatile int a0);

void func_00238868(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    D_004D3CF0[1] = (unsigned int)func_00238D08;
    gobj->unkC4 = (int *)D_004D3CF0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}


void func_002388D0(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x11A) != 0) {
        *(int *)(actSt25aQueenDeadChk(0x73E) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x73F) + 0x16C) = 0;
        func_0017B288(0x11A);
    } else {
        *(int *)(actSt25aQueenDeadChk(0x740) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x741) + 0x16C) = 0;
    }
}

extern unsigned int D_004D3D10[8];
extern void func_00238DD8(volatile int a0);

void func_00238950(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x123) == 0) {
        D_004D3D10[1] = (unsigned int)func_00238DD8;
        gobj->unkC4 = (int *)D_004D3D10;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}


void func_002389C8(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_0017B230(0x124) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}


void func_00238A70(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_0017B230(0x124) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}


void func_00238B18(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_0017B230(0x124) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
}

extern unsigned int D_004D3BD0[8];
extern int D_006325B4__8B88 __asm__("D_006325B4");

void func_00238B88(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_006325B4__8B88 = 0;
    *(int *)(gobj + 0xC0) = (int)D_004D3BD0;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct { char pad[0xC0]; void *f_C0; void *unkC4; } GObjC0_bc0;
extern int *D_004D3C10__bc0[] __asm__("D_004D3C10");
extern int D_006325B4__bc0 __asm__("D_006325B4");
extern void func_00237C18(volatile int a0);

void func_00238BC0(volatile int a0) {
    GObjC0_bc0 *obj = *(GObjC0_bc0 **)(a0 + 0x164);
    D_006325B4__bc0 = 1;
    D_004D3C10__bc0[1] = (int *)func_00237C18;
    obj->f_C0 = 0;
    obj->unkC4 = (void *)D_004D3C10__bc0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern unsigned int D_004D3C30[8];
extern int D_006325B4__8c18 __asm__("D_006325B4");
extern void scpActivateAllWithKind(void);

void func_00238C18(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    lt_fade_status(0x32);
    D_006325B4__8c18 = 0;
    scpActivateAllWithKind();
    *(int *)(gobj + 0xC0) = (int)D_004D3C30;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct KSub_c60 {
    char pad[0xC0];
    int unkC0;
    int *unkC4;
} KSub_c60;

extern int D_006325B4__c60 __asm__("D_006325B4");
extern unsigned int D_004D3C70[8];
extern unsigned int D_004D3C90[8];
extern void func_00237E98(volatile int a0);
extern void func_00237D18(volatile int a0);

void func_00238C60(volatile int a0) {
    KSub_c60 *s = *(KSub_c60 **)(a0 + 0x164);
    s->unkC0 = 0;
    lt_fade_status(0x33);
    D_006325B4__c60 = 1;
    scpDispOnAllWithKind();
    if (func_0017B230(0x121) != 0) {
        D_004D3C70[1] = (unsigned int)func_00237E98;
        s->unkC4 = (int *)D_004D3C70;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
    D_004D3C90[1] = (unsigned int)func_00237D18;
    s->unkC4 = (int *)D_004D3C90;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238D08);

extern int D_00631AE8__8dd8 __asm__("D_00631AE8");

void func_00238DD8(volatile int a0) {
    if (D_00631AE8__8dd8 == 0) {
        _ACTWait(0);
    }
    while (func_0017B230(0x120) == 0 ||
           scpSleepSpiderGroupOne(D_00631AE8__8dd8, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    func_0017B258(0x123);
    func_0017B258(0x124);
}

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238E50);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238F10);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00239138);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002393C0);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002394D8);

extern unsigned int D_004D3E10[8];
extern void func_002394D8(volatile int a0);
extern volatile float D_0063173C, D_00631740, D_00631744;
extern void warpGirlInStage(float f12, float f13, float f14);

void func_00239680(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    warpGirlInStage(D_0063173C, D_00631740, D_00631744);
    if (func_0017B230(0x12C) == 0) {
        D_004D3E10[1] = (unsigned int)func_002394D8;
        gobj->unkC4 = (int *)D_004D3E10;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}


void func_00239710(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x83, 0, 0);
}

void func_00239750(void)
{
    if (func_0017B230(0x2C) != 0) {
        stage_KillPlayBgAnimation(0x91, 0, 0);
        AddWayPointTop(0x21, 1);
    } else {
        stage_KillPlayBgAnimation(0x90, 0, 0);
        AddWayPointTop(0x21, 0);
    }
    if (func_0017B230(0x2D) != 0) {
        stage_KillPlayBgAnimation(0x93, 0, 0);
        AddWayPointTop(0x22, 1);
    } else {
        stage_KillPlayBgAnimation(0x92, 0, 0);
        AddWayPointTop(0x22, 0);
    }
}

void func_002397F8(void)
{
    if (D_00631AE8 == 0) {
        return;
    }
    if (func_0017B230(0x31) != 0) {
        return;
    }
    return func_0017B258(0x166);
}

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00239830);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00239B50);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00239C58);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00239DA8);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00239EB0);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00239FE0);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A180);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A248);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A2F8);

extern float D_00631754, D_00631758, D_0063175C, D_00631760;
extern void func_0017BF78(int a0, int a1, int a2, int a3, int a4, float f0, float f1, float f2, float f3, float f4, float f5);

void func_0023A3B8(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_0017BF78(a0, 0x29, 0x8d, 0, 0x12, D_00631754, D_00631758, D_0063175C, D_00631754, D_00631758, D_00631760);
}

extern float D_00631764, D_00631768, D_0063176C, D_00631770;
extern void func_0017BF78(int a0, int a1, int a2, int a3, int a4, float f0, float f1, float f2, float f3, float f4, float f5);

void func_0023A418(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_0017BF78(a0, 0x2a, 0x8e, 0, 0x12, D_00631764, D_00631768, D_0063176C, D_00631764, D_00631768, D_00631770);
}

extern float D_00631774, D_00631778, D_0063177C, D_00631780;
extern void func_0017BF78(int a0, int a1, int a2, int a3, int a4, float f0, float f1, float f2, float f3, float f4, float f5);

void func_0023A478(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_0017BF78(a0, 0x2b, 0x8f, 0, 0x12, D_00631774, D_00631778, D_0063177C, D_00631774, D_00631778, D_00631780);
}

extern int D_004D3E70[];
extern void func_0023AAB8(volatile int a0);

void func_0023A4D8(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    func_0017B230(0x2C);
    D_004D3E70[1] = (int)func_0023AAB8;
    gobj->unkC4 = D_004D3E70;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D3F30[];
extern void func_0023AC30(volatile int a0);

void func_0023A548(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    D_004D3F30[1] = (int)func_0023AC30;
    gobj->unkC4 = D_004D3F30;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A5B0);

extern unsigned int D_004D3FF0[8];
extern void func_0023AD68(volatile int a0);

void func_0023A668(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x2F) == 0) {
        stage_KillPlayBgAnimation(0x96, 0, 0);
        D_004D3FF0[1] = (unsigned int)func_0023AD68;
        gobj->unkC4 = (int *)D_004D3FF0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x96, 0, -1);
    }
}

extern int D_004D4010[];
extern void func_0023AE28(volatile int a0);

void func_0023A700(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    D_004D4010[1] = (int)func_0023AE28;
    gobj->unkC4 = D_004D4010;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D4030[];
extern void func_0023AEA0(volatile int a0);

void func_0023A768(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x82) != 0) {
        D_004D4030[1] = (int)func_0023AEA0;
        gobj->unkC4 = D_004D4030;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D4050[];
extern void func_0023AED8(volatile int a0);

void func_0023A7E0(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x31) == 0) {
        D_004D4050[1] = (int)func_0023AED8;
        gobj->unkC4 = D_004D4050;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}


void func_0023A858(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_0017B230(0x32) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0xB4);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}


void func_0023A8E8(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_0017B230(0x32) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0xb4);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}


/* .data — carved VMA 0X4D3A30..0X4D3E50 (33 symbols), bytes verified against baserom/baseelf.rom */
unsigned int D_004D3A30[8] = {
    0x00000179, 0x00237898, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3A50[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3A70[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3A90[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3AB0[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3AD0[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3AF0[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3B10[8] = {
    0x00000178, 0x00237A38, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3B30[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3B50[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3B70[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3B90[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3BB0[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3BD0[8] = {
    0x00000178, 0x00238BC0, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3BF0[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3C10[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3C30[8] = {
    0x00000179, 0x00238C60, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3C50[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3C70[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3C90[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3CB0[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3CD0[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3CF0[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3D10[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3D30[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3D50[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3D70[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3D90[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3DB0[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3DD0[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3DF0[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3E10[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D3E30[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
