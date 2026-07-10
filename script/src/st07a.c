#include "common.h"

typedef struct GObj {
    char pad[0xB4];
    int *unkB4;
} GObj;

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_004CCE40[];
extern void actSt08bDoor(volatile int a0);

void actSt07aInit(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xF0) == 0) {
        stage_KillPlayBgAnimation(0x136, 0, 0);
        D_004CCE40[1] = (int)actSt08bDoor;
        gobj->unkB4 = D_004CCE40;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x136, 0, -1);
    }
}


extern int D_004CCE60[];
extern int D_004CCE80[];
extern void actSt06aDoorDownChk(volatile int a0);

void actSt07aEnd(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x101) != 0) {
        stage_KillPlayBgAnimation(0xC8, 0, 0xC8);
        D_004CCE60[1] = (int)actSt06aDoorDownChk;
        gobj->unkB4 = D_004CCE60;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xC8, 0, 0);
        D_004CCE80[1] = (int)actSt06aDoorDownChk;
        gobj->unkB4 = D_004CCE80;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt07aChanChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xDA) == 0) {
        stage_KillPlayBgAnimation(0x118, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x118, 0, -1);
    }
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt07aChanEffect(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xDB) == 0) {
        stage_KillPlayBgAnimation(0x119, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x119, 0, -1);
    }
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt07aTsuroChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xDC) == 0) {
        stage_KillPlayBgAnimation(0x11A, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x11A, 0, -1);
    }
}

extern void func_00178E08(int a0);
void actSt07aTsuroEffect(volatile int a0){ int x=a0; actInitialize(a0); _ACTWait(1);
if(func_00178DB0(0xE2)==0){ stage_KillPlayBgAnimation(0x11C,0,0); *(int*)(actSt25aQueenDeadChk(0x518) + 0x16C) = 0; *(int*)(actSt25aQueenDeadChk(0x519) + 0x16C) = 0; } else { stage_KillPlayBgAnimation(0x11C,0,-1); } }

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int actSt25aQueenDeadChk(int a0);
void actSt07aSekizoChk(volatile int a0){
 int x = a0;
 actInitialize(a0);
 _ACTWait(1);
 if(func_00178DB0(0xE3) == 0){
  stage_KillPlayBgAnimation(0x11D, 0, 0);
  *(int*)(actSt25aQueenDeadChk(0x5AD) + 0x16C) = 0;
  *(int*)(actSt25aQueenDeadChk(0x5AE) + 0x16C) = 0;
 } else {
  stage_KillPlayBgAnimation(0x11D, 0, -1);
 } }

extern void gflagInit(int a0);
extern int D_004CCEE0[];
extern void actSt08bDoorDownChk(volatile int a0);

void actSt07aEne(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xF1) == 0) {
        D_004CCEE0[1] = (int)actSt08bDoorDownChk;
        gobj->unkB4 = D_004CCEE0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        gflagInit(0x514);
    }
}


extern int D_004CCF00[];
extern void actSt08bKuren(volatile int a0);

void actSt07aEneChk(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xF2) == 0) {
        D_004CCF00[1] = (int)actSt08bKuren;
        gobj->unkB4 = D_004CCF00;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        gflagInit(0x515);
    }
}


extern int D_004CCF20[];
extern void actSt08bEne(volatile int a0);

void actSt07aChan(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xF3) != 0 || func_00178DB0(0xF5) != 0) {
        gflagInit(0x560);
    } else {
        D_004CCF20[1] = (int)actSt08bEne;
        gobj->unkB4 = D_004CCF20;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CCF40[];
extern void actSt08bEnemy1(volatile int a0);

void actSt07aTsuro(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xF4) != 0 || func_00178DB0(0xF6) != 0) {
        gflagInit(0x561);
    } else {
        D_004CCF40[1] = (int)actSt08bEnemy1;
        gobj->unkB4 = D_004CCF40;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CCF60[];
extern void actSt08bEnemy2(volatile int a0);

void actSt07aIntro(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xF7) == 0) {
        D_004CCF60[1] = (int)actSt08bEnemy2;
        gobj->unkB4 = D_004CCF60;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        gflagInit(0x562);
    }
}


extern int D_004CCF80[];
extern void actSt08bKurenMain(volatile int a0);

void actSt07aSekizo(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xF8) == 0) {
        D_004CCF80[1] = (int)actSt08bKurenMain;
        gobj->unkB4 = D_004CCF80;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        gflagInit(0x563);
    }
}


extern int D_004CCFA0[];
extern void actSt08aGirlYoro(volatile int a0);

void actSt07aGene1(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xF3) != 0 || func_00178DB0(0xF5) != 0) {
        gflagInit(0x518);
    } else {
        D_004CCFA0[1] = (int)actSt08aGirlYoro;
        gobj->unkB4 = D_004CCFA0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CCFC0[];
extern void actSt08bDoorEvent(volatile int a0);

void actSt07aGene2(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xF4) != 0 || func_00178DB0(0xF6) != 0) {
        gflagInit(0x519);
    } else {
        D_004CCFC0[1] = (int)actSt08bDoorEvent;
        gobj->unkB4 = D_004CCFC0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


void actSt07aGene3(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xF7)) {
        gflagInit(0x5AD);
    }
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void gflagInit(int a0);

void actSt07aEne2(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xF8)) {
        gflagInit(0x5AE);
    }
}

extern int D_004CCD60[];
extern void func_0021E7E0(volatile int a0);

void actSt07aGene2_1(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xF9) == 0) {
        stage_KillPlayBgAnimation(0x12F, 0, 0);
        D_004CCD60[1] = (int)func_0021E7E0;
        gobj->unkB4 = D_004CCD60;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x12F, 0, -1);
    }
}


extern int D_004CCD80[];
extern void func_0021E8D8(volatile int a0);

void actSt07aGene2_2(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xFA) == 0) {
        stage_KillPlayBgAnimation(0x130, 0, 0);
        D_004CCD80[1] = (int)func_0021E8D8;
        gobj->unkB4 = D_004CCD80;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x130, 0, -1);
    }
}


extern int D_004CCDA0[];
extern void actSt06aInit(volatile int a0);

void actSt07aGene2_3(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xFB) == 0) {
        stage_KillPlayBgAnimation(0x131, 0, 0);
        D_004CCDA0[1] = (int)actSt06aInit;
        gobj->unkB4 = D_004CCDA0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x131, 0, -1);
    }
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_004CCDC0[];
extern void actSt06aSuimon(void);

void actSt07ChanEvent(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xFC) == 0) {
        stage_KillPlayBgAnimation(0x132, 0, 0);
        D_004CCDC0[1] = (int)actSt06aSuimon;
        gobj->unkB4 = D_004CCDC0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x132, 0, -1);
    }
}

