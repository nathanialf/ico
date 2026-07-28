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
extern void stage_KillPlayBgAnimation__p4(int a0, int a1, int a2) __asm__("stage_KillPlayBgAnimation");

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
    stage_KillPlayBgAnimation__p4(0x65, 1, 0);
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
extern void stage_KillPlayBgAnimation__p4(int a0, int a1, int a2) __asm__("stage_KillPlayBgAnimation");

void actSt47aEnd(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    while (scpKillSpiderGroup((int)a0, 0x1000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);
    func_0017B288(0x36);
    stage_KillPlayBgAnimation__p4(0x65, 1, 0x2E);
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
    stage_KillPlayBgAnimation__p4(0x66, 1, 0);
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
extern void stage_KillPlayBgAnimation__p4(int a0, int a1, int a2) __asm__("stage_KillPlayBgAnimation");

void actSt47aRopeChk(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    while (func_0017B230(0x36) != 0 && func_0017B230(0x37) != 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);
    func_0017B288(0x38);
    stage_KillPlayBgAnimation__p4(0x68, 1, 0);
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
extern void stage_KillPlayBgAnimation__p4(int a0, int a1, int a2) __asm__("stage_KillPlayBgAnimation");

void actSt47aSekizo2(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x38) == 0) {
        stage_KillPlayBgAnimation__p4(0x67, 0, 0);
        D_004D3970[1] = (int)actSt47aHane2Up;
        gobj->unkC4 = D_004D3970;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation__p4(0x67, 0, -1);
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
        stage_KillPlayBgAnimation__p4(0x65, 0, 0);
        D_004D3870[1] = (int)actSt47aInit;
        gobj->unkC4 = D_004D3870;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation__p4(0x65, 0, 0x2D);
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
        stage_KillPlayBgAnimation__p4(0x66, 0, 0);
        D_004D38F0[1] = (int)actSt47aSekizo1Chk;
        gobj->unkC4 = D_004D38F0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation__p4(0x66, 0, 0x2D);
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

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00236D20);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00236D90);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00236E10);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00236F38);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237088);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237230);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237338);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237428);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237518);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002375C8);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237638);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002376F0);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237750);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002377E8);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237860);

typedef struct KSubB_b898 {
    char pad[0xC0];
    int unkC0;
    int *unkC4;
} KSubB_b898;

extern volatile int D_006325B4__b898 __asm__("D_006325B4");
extern unsigned int D_004D3A70[8];
extern unsigned int D_004D3A90[8];
extern void BoxBarSoundOn__b898(int a0, int a1) __asm__("BoxBarSoundOn");
extern void _ACTWait__b898(int a0) __asm__("_ACTWait");
extern int func_0017B230__b898(int a0) __asm__("func_0017B230");
extern void func_00236E10(volatile int a0);
extern void func_00237930(volatile int a0);

void func_00237898(volatile int a0) {
    KSubB_b898 *s = *(KSubB_b898 **)(a0 + 0x164);
    D_006325B4__b898 = 1;
    s->unkC0 = 0;
    if (func_0017B230__b898(0x11B) != 0) {
        D_004D3A70[1] = (unsigned int)func_00236E10;
        s->unkC4 = (int *)D_004D3A70;
        BoxBarSoundOn__b898(a0, 0x18D);
        _ACTWait__b898(0);
    }
    D_004D3A90[1] = (unsigned int)func_00237930;
    s->unkC4 = (int *)D_004D3A90;
    BoxBarSoundOn__b898(a0, 0x18D);
    _ACTWait__b898(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237930);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00237A00);

typedef struct KSubB_ba38 {
    char pad[0xC0];
    int unkC0;
    int *unkC4;
} KSubB_ba38;

extern volatile int D_006325B4__ba38 __asm__("D_006325B4");
extern unsigned int D_004D3B50[8];
extern unsigned int D_004D3B70[8];
extern void BoxBarSoundOn__ba38(int a0, int a1) __asm__("BoxBarSoundOn");
extern void _ACTWait__ba38(int a0) __asm__("_ACTWait");
extern int func_0017B230__ba38(int a0) __asm__("func_0017B230");
extern void func_00237338(volatile int a0);
extern void func_00237428(volatile int a0);

void func_00237A38(volatile int a0) {
    KSubB_ba38 *s = *(KSubB_ba38 **)(a0 + 0x164);
    D_006325B4__ba38 = 1;
    s->unkC0 = 0;
    if (func_0017B230__ba38(0x11E) == 0) {
        D_004D3B50[1] = (unsigned int)func_00237338;
        s->unkC4 = (int *)D_004D3B50;
        BoxBarSoundOn__ba38(a0, 0x18D);
        _ACTWait__ba38(0);
    } else {
        D_004D3B70[1] = (unsigned int)func_00237428;
        s->unkC4 = (int *)D_004D3B70;
        BoxBarSoundOn__ba38(a0, 0x18D);
        _ACTWait__ba38(0);
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

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238740);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002387B8);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238868);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002388D0);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238950);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002389C8);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238A70);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238B18);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238B88);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238BC0);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238C18);

typedef struct KSub_c60 {
    char pad[0xC0];
    int unkC0;
    int *unkC4;
} KSub_c60;

extern int D_006325B4__c60 __asm__("D_006325B4");
extern unsigned int D_004D3C70[8];
extern unsigned int D_004D3C90[8];
extern void BoxBarSoundOn__c60(int a0, int a1) __asm__("BoxBarSoundOn");
extern void _ACTWait__c60(int a0) __asm__("_ACTWait");
extern void lt_fade_status__c60(int a0) __asm__("lt_fade_status");
extern void scpDispOnAllWithKind__c60(void) __asm__("scpDispOnAllWithKind");
extern int func_0017B230__c60(int a0) __asm__("func_0017B230");
extern void func_00237E98(volatile int a0);
extern void func_00237D18(volatile int a0);

void func_00238C60(volatile int a0) {
    KSub_c60 *s = *(KSub_c60 **)(a0 + 0x164);
    s->unkC0 = 0;
    lt_fade_status__c60(0x33);
    D_006325B4__c60 = 1;
    scpDispOnAllWithKind__c60();
    if (func_0017B230__c60(0x121) != 0) {
        D_004D3C70[1] = (unsigned int)func_00237E98;
        s->unkC4 = (int *)D_004D3C70;
        BoxBarSoundOn__c60(a0, 0x18D);
        _ACTWait__c60(0);
    }
    D_004D3C90[1] = (unsigned int)func_00237D18;
    s->unkC4 = (int *)D_004D3C90;
    BoxBarSoundOn__c60(a0, 0x18D);
    _ACTWait__c60(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238D08);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238DD8);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238E50);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00238F10);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00239138);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002393C0);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_002394D8);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00239680);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_00239710);

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

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A3B8);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A418);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A478);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A4D8);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A548);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A5B0);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A668);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A700);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A768);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A7E0);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A858);

INCLUDE_ASM("asm/nonmatchings/src/st47a", func_0023A8E8);


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
