#include "common.h"

extern void *D_00629DE8;
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);

typedef struct GObj {
    char pad[0xB4];
    int *unkB4;
} GObj;

void GetDataFileName(void) {
    if (D_00629DE8 == 0) {
        return;
    }
    if (func_00178DB0(0x31) != 0) {
        return;
    }
    func_00178DD8(0x165);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", GetDataFileName2);

extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int scpSleepSpiderGroupOne(void *a0, int a1);
extern void actCreateSubThread(void *fn, int a1);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void AddWayPointTop(int a0, int a1);
extern void func_00178E08(int a0);
extern int func_0012A958(int a0);
extern void func_002370D8(void);
extern void func_00237128(void);
extern void func_00236EF0(void);
extern int D_004CEAA0[];
extern int D_0062BE38;

void func_002361C0(volatile int a0) {
    GObj *gobj = *(GObj **)(a0 + 0x164);
    if (D_00629DE8 != 0) {
        if (scpSleepSpiderGroupOne(D_00629DE8, 0x2000000) != 0) {
            actCreateSubThread((void *)func_002370D8, 0x15);
        }
        if (scpSleepSpiderGroupOne(D_00629DE8, 0x4000000) != 0) {
            actCreateSubThread((void *)func_00237128, 0x15);
        }
    }
    scpPlayStart(0x40, &D_0062BE38, 1, 1, 1);
    if (D_0062BE38 == 0) {
        while (D_0062BE38 == 0) {
            _ACTWait(1);
        }
    }
    stage_KillPlayBgAnimation(0x90, 1, 0);
    AddWayPointTop(0x21, 0);
    func_00178E08(0x2C);
    while (func_0012A958(0x90) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_004CEAA0[1] = (int)func_00236EF0;
    gobj->unkB4 = D_004CEAA0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int scpSleepSpiderGroupOne(void *a0, int a1);
extern void actCreateSubThread(void *fn, int a1);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void AddWayPointTop(int a0, int a1);
extern void func_00178E08(int a0);
extern int func_0012A958(int a0);
extern void func_00237360(void);
extern void func_00237178(void);
extern int D_004CEB60[];
extern int D_0062BE3C;

void func_00236300(volatile int a0) {
    GObj *gobj = *(GObj **)(a0 + 0x164);
    if (D_00629DE8 != 0) {
        if (scpSleepSpiderGroupOne(D_00629DE8, 0x3000000) != 0) {
            actCreateSubThread((void *)func_00237360, 0x15);
        }
    }
    scpPlayStart(0x41, &D_0062BE3C, 1, 1, 1);
    if (D_0062BE3C == 0) {
        while (D_0062BE3C == 0) {
            _ACTWait(1);
        }
    }
    stage_KillPlayBgAnimation(0x92, 1, 0);
    AddWayPointTop(0x22, 0);
    func_00178E08(0x2D);
    while (func_0012A958(0x92) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_004CEB60[1] = (int)func_00237178;
    gobj->unkB4 = D_004CEB60;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern int actInitialize(int a0);
extern int fallDownStartSE(void *a0);
extern char *actSt25aQueenDeadChk(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern int func_0012AA28(int a0, int a1, int a2);
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void scpActivateAllWithKind(void);
extern int D_0062A894;

void func_00236420(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (func_00178DB0(0x2E) == 0) {
        switch (fallDownStartSE(actSt25aQueenDeadChk(0x1B6))) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_KillPlayBgAnimation(0x93, 1, 0);
            while (func_0012A958(0x93) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            *(int *)(actSt25aQueenDeadChk(0x1B6) + 0x16C) = 0;
            lt_fade_status(0x33);
            D_0062A894 = 1;
            func_00178DD8(0x2E);
            scpDispOnAllWithKind();
            _ACTWait(0xF);
            stage_KillPlayBgAnimation(0x94, 1, 0);
            while (func_0012AA28(0x94, 0x94, 0) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            *(int *)(actSt25aQueenDeadChk(0x1CB) + 0x16C) = 1;
            while (func_0012A958(0x94) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            scpActivateAllWithKind();
            D_0062A894 = 0;
            lt_fade_status(0x32);
            break;
        }
    }
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
extern char *actSt25aQueenDeadChk(int a0);

void func_002365C0(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    Generator_Mask((int)actSt25aQueenDeadChk(0x1D5));
    while (func_00178DB0(0x32) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_Call((int)actSt25aQueenDeadChk(0x1D5));
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void gflagInit(int a0);

void func_00236688(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x8B) != 0) {
        gflagInit(0x1BD);
        gflagInit(0x1BE);
        gflagInit(0x1BF);
        gflagInit(0x1C0);
        gflagInit(0x1C1);
        gflagInit(0x1C2);
        gflagInit(0x1C3);
        gflagInit(0x1C4);
        gflagInit(0x1C5);
        gflagInit(0x1C6);
        gflagInit(0x1C7);
        gflagInit(0x1C8);
        gflagInit(0x1C9);
        gflagInit(0x1CA);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_00236738);


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void func_00179710(int, int, int, int, int, float, float, float, float, float, float);
extern float D_00629A3C, D_00629A40, D_00629A44, D_00629A48;

void func_002367F8(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_00179710(a0, 0x29, 0x8C, 0, 0x12, D_00629A3C, D_00629A40, D_00629A44, D_00629A3C, D_00629A40, D_00629A48);
}


extern float D_00629A4C, D_00629A50, D_00629A54, D_00629A58;

void func_00236858(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_00179710(a0, 0x2A, 0x8D, 0, 0x12, D_00629A4C, D_00629A50, D_00629A54, D_00629A4C, D_00629A50, D_00629A58);
}


extern float D_00629A5C, D_00629A60, D_00629A64, D_00629A68;

void func_002368B8(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_00179710(a0, 0x2B, 0x8E, 0, 0x12, D_00629A5C, D_00629A60, D_00629A64, D_00629A5C, D_00629A60, D_00629A68);
}


extern int func_00178DB0(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_004CEA20[];
extern void func_00236EF0(void);

void func_00236918(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    func_00178DB0(0x2C);
    D_004CEA20[1] = (int)func_00236EF0;
    gobj->unkB4 = D_004CEA20;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern int D_004CEAE0[];
extern int D_004CEAE0[];
extern void func_00237178(void);

void func_00236988(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    D_004CEAE0[1] = (int)func_00237178;
    gobj->unkB4 = D_004CEAE0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_002369F0);


extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004CEBA0[];
extern void func_002373C0(void);

void func_00236AA8(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x2F) == 0) {
        stage_KillPlayBgAnimation(0x95, 0, 0);
        D_004CEBA0[1] = (int)func_002373C0;
        gobj->unkB4 = D_004CEBA0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x95, 0, -1);
    }
}


extern int D_004CEBC0[];
extern void func_00237480(void);

void func_00236B40(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    D_004CEBC0[1] = (int)func_00237480;
    gobj->unkB4 = D_004CEBC0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}

extern int D_004CEBE0[];
extern void func_002374F8(void);

void func_00236BA8(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x82) != 0) {
        D_004CEBE0[1] = (int)func_002374F8;
        gobj->unkB4 = D_004CEBE0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CEC00[];
extern void func_00237530(void);

void func_00236C20(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x31) == 0) {
        D_004CEC00[1] = (int)func_00237530;
        gobj->unkB4 = D_004CEC00;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);

void func_00236C98(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_00178DB0(0x32) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0xB4);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}


void func_00236D28(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_00178DB0(0x32) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0xB4);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}

extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);

void func_00236DB8(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_00178DB0(0x32) == 0) {
        _ACTWait(1);
    }
    Generator_MaskOff(a0);
}

