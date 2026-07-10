#include "common.h"

typedef struct ActB4Obj {
    char pad[0xB4];
    int *unkB4;
} ActB4Obj;

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_004CC900[];
extern void actSt05eEnd(void);

void actSt05bCrest01XL(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xB6) == 0) {
        D_004CC900[1] = (int)actSt05eEnd;
        gobj->unkB4 = D_004CC900;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CC940[];
extern void func_0021C580(void);

void actSt05bSekizoChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x9C) == 0) {
        D_004CC940[1] = (int)func_0021C580;
        gobj->unkB4 = D_004CC940;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004CC760[];
extern int D_004CC780[];
extern void actSt04lRope2Chk(void);

void actSt05bDoorXL(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xAB) != 0) {
        stage_KillPlayBgAnimation(0xC7, 0, 0xC8);
        D_004CC760[1] = (int)actSt04lRope2Chk;
        gobj->unkB4 = D_004CC760;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xC7, 0, 0);
        D_004CC780[1] = (int)actSt04lRope2Chk;
        gobj->unkB4 = D_004CC780;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004CC7E0[];
extern void actSt04lBrg1Chk(void);

void actSt05bMonyoDoorXL(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xC0) == 0) {
        stage_KillPlayBgAnimation(0xCD, 0, 0);
        D_004CC7E0[1] = (int)actSt04lBrg1Chk;
        gobj->unkB4 = D_004CC7E0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xCD, 0, -1);
    }
}


extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004CC800[];
extern void actSt04lRope3Chk(void);

void actSt05bSekizo(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xC1) == 0) {
        stage_KillPlayBgAnimation(0xCE, 0, 0);
        D_004CC800[1] = (int)actSt04lRope3Chk;
        gobj->unkB4 = D_004CC800;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xCE, 0, -1);
    }
}


extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004CC820[];
extern void actSt04lRope4Chk(void);

void actSt05bBallXL(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xC2) == 0) {
        stage_KillPlayBgAnimation(0xCF, 0, 0);
        D_004CC820[1] = (int)actSt04lRope4Chk;
        gobj->unkB4 = D_004CC820;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xCF, 0, -1);
    }
}


extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004CC840[];
extern void actSt04lBrg2Chk(void);

void actSt05bSolarXL(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xC3) == 0) {
        stage_KillPlayBgAnimation(0xD0, 0, 0);
        D_004CC840[1] = (int)actSt04lBrg2Chk;
        gobj->unkB4 = D_004CC840;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xD0, 0, -1);
    }
}


extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004CC860[];
extern void actSt04lSekizoChk(void);

void actSt05bSekizoEvent(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xC4) == 0) {
        stage_KillPlayBgAnimation(0xD1, 0, 0);
        D_004CC860[1] = (int)actSt04lSekizoChk;
        gobj->unkB4 = D_004CC860;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xD1, 0, -1);
    }
}


extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004CC880[];
extern void actSt04lGondolaChk(void);

void actSt05bGirlWay(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xC5) == 0) {
        stage_KillPlayBgAnimation(0xD2, 0, 0);
        D_004CC880[1] = (int)actSt04lGondolaChk;
        gobj->unkB4 = D_004CC880;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xD2, 0, -1);
    }
}


extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004CC8A0[];
extern void actSt04lMonyou01Chk(void);

void func_0021B580(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xC6) == 0) {
        stage_KillPlayBgAnimation(0xD3, 0, 0);
        D_004CC8A0[1] = (int)actSt04lMonyou01Chk;
        gobj->unkB4 = D_004CC8A0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xD3, 0, -1);
    }
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_0021B618(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x9B) == 0) {
        stage_KillPlayBgAnimation(0xB5, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xB5, 0, -1);
    }
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_0021B678(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x9C) == 0) {
        stage_KillPlayBgAnimation(0xB6, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xB6, 0, -1);
    }
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_0021B6D8(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x9D) == 0) {
        stage_KillPlayBgAnimation(0xB7, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xB7, 0, -1);
    }
}

extern void func_00178E08(int a0);
void func_0021B738(volatile int a0){ int x=a0; actInitialize(a0); _ACTWait(1);
if(func_00178DB0(0x9F)==0){ *(int*)(actSt25aQueenDeadChk(0x403) + 0x16C) = 0; *(int*)(actSt25aQueenDeadChk(0x404) + 0x16C) = 0; stage_KillPlayBgAnimation(0xB9,0,0); } else { stage_KillPlayBgAnimation(0xB9,0,-1); } }

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int actSt25aQueenDeadChk(int a0);
void func_0021B7B8(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xA0) == 0) {
        stage_KillPlayBgAnimation(0xBA, 0, 0);
        *(int *)(actSt25aQueenDeadChk(0x49F) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x4A0) + 0x16C) = 0;
    } else {
        stage_KillPlayBgAnimation(0xBA, 0, -1);
    }
}

extern int D_004CC960[];
extern void func_0021C5A8(void);
extern void gflagInit(int a0);

void func_0021B830(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xB8) == 0) {
        D_004CC960[1] = (int)func_0021C5A8;
        gobj->unkB4 = D_004CC960;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        gflagInit(0x3FF);
    }
}


extern int D_004CC980[];
extern void func_0021C5F0(void);

void func_0021B8B8(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xB9) == 0) {
        D_004CC980[1] = (int)func_0021C5F0;
        gobj->unkB4 = D_004CC980;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        gflagInit(0x400);
    }
}


extern int D_004CC9A0[];
extern void func_0021C638(void);

void func_0021B940(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xBA) != 0 || func_00178DB0(0xBC) != 0) {
        gflagInit(0x451);
    } else {
        D_004CC9A0[1] = (int)func_0021C638;
        gobj->unkB4 = D_004CC9A0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CC9C0[];
extern void func_0021C680(void);

void func_0021B9D8(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xBB) != 0 || func_00178DB0(0xBD) != 0) {
        gflagInit(0x452);
    } else {
        D_004CC9C0[1] = (int)func_0021C680;
        gobj->unkB4 = D_004CC9C0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CC9E0[];
extern void func_0021C6C8(void);

void func_0021BA70(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xBE) == 0) {
        D_004CC9E0[1] = (int)func_0021C6C8;
        gobj->unkB4 = D_004CC9E0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        gflagInit(0x453);
    }
}


extern int D_004CCA00[];
extern void func_0021C710(void);

void func_0021BAF8(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xBF) == 0) {
        D_004CCA00[1] = (int)func_0021C710;
        gobj->unkB4 = D_004CCA00;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        gflagInit(0x454);
    }
}


extern int D_004CCA20[];
extern void func_0021C758(void);

void func_0021BB80(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xBA) != 0 || func_00178DB0(0xBC) != 0) {
        gflagInit(0x403);
    } else {
        D_004CCA20[1] = (int)func_0021C758;
        gobj->unkB4 = D_004CCA20;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}

