#include "common.h"

typedef struct GObj__p4 {
    char pad[0xC4];
    int *unkB4;
} GObj__p4;

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D2230[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actSt08bDoor(volatile int a0);
extern int func_0017B230(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt07aInit(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xF0) == 0) {
        stage_KillPlayBgAnimation(0x137, 0, 0);
        D_004D2230[1] = (int)actSt08bDoor;
        gobj->unkB4 = D_004D2230;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x137, 0, -1);
    }
}

extern int D_004D2250[];
extern int D_004D2270[];
extern void actSt06aDoorDownChk(volatile int a0);

void actSt07aEnd(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x101) != 0) {
        stage_KillPlayBgAnimation(0xC9, 0, 0xC8);
        D_004D2250[1] = (int)actSt06aDoorDownChk;
        gobj->unkB4 = D_004D2250;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xC9, 0, 0);
        D_004D2270[1] = (int)actSt06aDoorDownChk;
        gobj->unkB4 = D_004D2270;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int func_0017B230(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt07aChanChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xDA) == 0) {
        stage_KillPlayBgAnimation(0x119, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x119, 0, -1);
    }
}

void actSt07aChanEffect(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xDB) == 0) {
        stage_KillPlayBgAnimation(0x11A, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x11A, 0, -1);
    }
}

void actSt07aTsuroChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xDC) == 0) {
        stage_KillPlayBgAnimation(0x11B, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x11B, 0, -1);
    }
}

extern int actSt25aQueenDeadChk(int a0);

void actSt07aTsuroEffect(volatile int a0){ int x=a0; actInitialize(a0); _ACTWait(1);
if(func_0017B230(0xE2)==0){ stage_KillPlayBgAnimation(0x11D,0,0); *(int*)(actSt25aQueenDeadChk(0x51C) + 0x16C) = 0; *(int*)(actSt25aQueenDeadChk(0x51D) + 0x16C) = 0; } else { stage_KillPlayBgAnimation(0x11D,0,-1); } }

void actSt07aSekizoChk(volatile int a0){
 int x = a0;
 actInitialize(a0);
 _ACTWait(1);
 if(func_0017B230(0xE3) == 0){
  stage_KillPlayBgAnimation(0x11E, 0, 0);
  *(int*)(actSt25aQueenDeadChk(0x5B3) + 0x16C) = 0;
  *(int*)(actSt25aQueenDeadChk(0x5B4) + 0x16C) = 0;
 } else {
  stage_KillPlayBgAnimation(0x11E, 0, -1);
 } }

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D22D0[];
extern void actSt08bDoorDownChk(volatile int a0);
extern void gflagInit(int a0);

void actSt07aEne(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xF1) == 0) {
        D_004D22D0[1] = (int)actSt08bDoorDownChk;
        gobj->unkB4 = D_004D22D0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        gflagInit(0x518);
    }
}

extern int D_004D22F0[];
extern void actSt08bKuren(volatile int a0);

void actSt07aEneChk(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xF2) == 0) {
        D_004D22F0[1] = (int)actSt08bKuren;
        gobj->unkB4 = D_004D22F0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        gflagInit(0x519);
    }
}

extern int D_004D2310[];
extern void actSt08bEne(volatile int a0);

void actSt07aChan(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xF3) != 0 || func_0017B230(0xF5) != 0) {
        gflagInit(0x566);
    } else {
        D_004D2310[1] = (int)actSt08bEne;
        gobj->unkB4 = D_004D2310;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D2330[];
extern void actSt08bEnemy1(volatile int a0);

void actSt07aTsuro(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xF4) != 0 || func_0017B230(0xF6) != 0) {
        gflagInit(0x567);
    } else {
        D_004D2330[1] = (int)actSt08bEnemy1;
        gobj->unkB4 = D_004D2330;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D2350[];
extern void actSt08bEnemy2(volatile int a0);

void actSt07aIntro(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xF7) == 0) {
        D_004D2350[1] = (int)actSt08bEnemy2;
        gobj->unkB4 = D_004D2350;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        gflagInit(0x568);
    }
}

extern int D_004D2370[];
extern void actSt08bKurenMain(volatile int a0);

void actSt07aSekizo(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xF8) == 0) {
        D_004D2370[1] = (int)actSt08bKurenMain;
        gobj->unkB4 = D_004D2370;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        gflagInit(0x569);
    }
}

extern int D_004D2390[];
extern void actSt08aGirlYoro(volatile int a0);

void actSt07aGene1(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xF3) != 0 || func_0017B230(0xF5) != 0) {
        gflagInit(0x51C);
    } else {
        D_004D2390[1] = (int)actSt08aGirlYoro;
        gobj->unkB4 = D_004D2390;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D23B0[];
extern void actSt08bDoorEvent(volatile int a0);

void actSt07aGene2(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xF4) != 0 || func_0017B230(0xF6) != 0) {
        gflagInit(0x51D);
    } else {
        D_004D23B0[1] = (int)actSt08bDoorEvent;
        gobj->unkB4 = D_004D23B0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int func_0017B230(int a0);
extern void gflagInit(int a0);

void actSt07aGene3(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xF7)) {
        gflagInit(0x5B3);
    }
}

void actSt07aEne2(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xF8)) {
        gflagInit(0x5B4);
    }
}

extern int D_004D2150[];
extern void func_00221820(volatile int a0);

void actSt07aGene2_1(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xF9) == 0) {
        stage_KillPlayBgAnimation(0x130, 0, 0);
        D_004D2150[1] = (int)func_00221820;
        gobj->unkB4 = D_004D2150;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x130, 0, -1);
    }
}

extern int D_004D2170[];
extern void func_00221978(volatile int a0);

void actSt07aGene2_2(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xFA) == 0) {
        stage_KillPlayBgAnimation(0x131, 0, 0);
        D_004D2170[1] = (int)func_00221978;
        gobj->unkB4 = D_004D2170;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x131, 0, -1);
    }
}

extern int D_004D2190[];
extern void actSt06aInit(volatile int a0);

void actSt07aGene2_3(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xFB) == 0) {
        stage_KillPlayBgAnimation(0x132, 0, 0);
        D_004D2190[1] = (int)actSt06aInit;
        gobj->unkB4 = D_004D2190;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x132, 0, -1);
    }
}

extern int D_004D21B0[];
extern void actSt06aSuimon(void);

void actSt07ChanEvent(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xFC) == 0) {
        stage_KillPlayBgAnimation(0x133, 0, 0);
        D_004D21B0[1] = (int)actSt06aSuimon;
        gobj->unkB4 = D_004D21B0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x133, 0, -1);
    }
}

