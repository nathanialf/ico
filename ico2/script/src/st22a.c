#include "common.h"

extern int D_00639EA4;
extern int D_0063C5AC;

typedef union StVec {
    float f[4];
    long long ll[2];
} StVec;

extern StVec D_00623090;
extern void stage_SetAnimation(int a0, int a1, int a2);
extern int stage_ContinueAnimation(int a0, int a1);
extern int stage_CheckAnimationFinish(int a0);
extern void scpPlayMot(int gobj, int mot);
extern void scpPlayMotDir(int gobj, void *dir);
extern void scpPlayPosSet(int gobj, float x, float y, float z);
extern void *test_CURRENTROOT(int gobj);
extern void sceVu0SubVector(void *out, void *a, void *b);
extern void _ACTWait(int n);
extern int D_0063AA08;
extern int D_0028F4C0[];
extern int D_0028F8F4[];

typedef struct St22Anims {
    int id[2];
} St22Anims;

extern int D_0063C050[];
extern void gflagOn(int flag);
extern void scpSekizouCheckPoint(void);
extern void lt_switch_layout(int n);
extern void scpPlayStart(int gobj);
extern void scpPlayEnd(int gobj);
extern void scpFadeIn(float t);
extern void scpFadeOut(float t, int a1, int a2, int a3);
extern int scpFadeChk(void);
extern int scpAdpcmPlayRequestNum(void);
extern int actCreateSubThread(void *entry, int prio);
extern void iosThreadSetPri(int th, int pri);
extern void StabilizeAllLayoutedCage(void);
extern void SetCameraFlag_GamecamCutBack(void);
extern void actSt22aIntroSub(volatile int a0);

void actSt22aIntroChk(volatile int a0)
{
    St22Anims anims;
    StVec pos;
    float dir[4];
    int th;
    int fin;
    unsigned int i;

    gflagOn(0x143);
    scpSekizouCheckPoint();
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpPlayStart(D_00639EA4);
    gflagOn(0x144);
    stage_SetAnimation(0x2F6, 1, 0);
    _ACTWait((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 10);
    scpFadeIn(6.0f);
    th = actCreateSubThread(actSt22aIntroSub, 0x15);
    D_0063C5AC = 0;
    while (D_0063C5AC == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }
    fin = D_0063C5AC ^ 1;
    if (fin != 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }
    iosThreadSetPri(th + 0x24, 0x22);
    if (fin != 0) {
        anims = *(St22Anims *)D_0063C050;
        for (i = 0; i < 2; i++) {
            stage_SetAnimation(anims.id[i], 1, -1);
            _ACTWait(1);
        }
        stage_SetAnimation(0x2F7, 1, -1);
        StabilizeAllLayoutedCage();
        scpPlayPosSet(D_00639EA4, -808.0f, 148.0f, -1053.0f);
        pos = D_00623090;
        sceVu0SubVector(dir, &pos, test_CURRENTROOT(D_00639EA4));
        scpPlayMotDir(D_00639EA4, dir);
        scpPlayMot(D_00639EA4, 0);
        _ACTWait(1);
        SetCameraFlag_GamecamCutBack();
        scpFadeIn(6.0f);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    } else {
        scpPlayMot(D_00639EA4, 0);
    }
    scpPlayEnd(D_00639EA4);
    lt_switch_layout(0x36);
    D_0063AA08 = 0;
}

void actSt22aIntroSub(volatile int a0)
{
    StVec pos;
    float dir[4];

    stage_SetAnimation(0x2F6, 1, 0);
    scpPlayMot(D_00639EA4, 0x18D);
    while (stage_ContinueAnimation(0x2F6, 0x2F7) == 0) {
        _ACTWait(1);
    }
    scpPlayPosSet(D_00639EA4, -707.0f, 148.0f, -1112.0f);
    pos = D_00623090;
    sceVu0SubVector(dir, &pos, test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);
    scpPlayMot(D_00639EA4, 0x18E);
    while (stage_CheckAnimationFinish(0x2F7) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0063C5AC = 1;
    _ACTWait(0);
}
