#include "common.h"

/* prototypes: their order is the inline tail's emission order */
void kanbanBootInit(void);
void kanbanBootStart(void);
extern int D_0028F4EC[];
extern int D_0063B4BC;
extern int D_0063B4C4;
extern int D_0063B4D0;
extern int fadeStatus;

inline void kanbanBootInit(void)
{
    D_0063B4BC = 0;
    D_0028F4EC[0] = 0;
    D_0063B4D0 = 0;
    fadeStatus = 0;
    D_0063B4C4 = 0;
}

/* memory-card request block shared with ios/mcard.c (the same object the
   debug menu drives); only the words this file touches are named. */
typedef struct {
    /* the iosMc flag word.  This file clears a bit in it as ONE 64-bit
       quantity (ROM: ld/and/sd) while ios/mcard.c takes the same block a
       word at a time, so the field carries both views. */
    union {
        long long ll;
        int w[2];
    } f0; /* 0x00 */

    int f8;  /* 0x08 */
    int fC;  /* 0x0C */
    int f10; /* 0x10 */
    int f14; /* 0x14 */
    int f18; /* 0x18 */
    int f1C; /* 0x1C */
    int f20; /* 0x20 */
} McReq;

typedef struct {
    int *obj; /* 0x00 */
    int f4;   /* 0x04 */
    int f8;   /* 0x08 */
} KanbanReq;

typedef struct {
    char _0[0x1E8];
    int f1E8; /* 0x1E8 */
    int f1EC; /* 0x1EC */
} KanbanStageRec;

extern McReq D_0071CF00;
extern KanbanStageRec D_0029B5F0[];
extern int D_00534010[];
extern int D_0028F4C0[];
extern int D_0028F4D8[];
extern int D_0063A054;
extern int D_0063B4C0;
extern int D_0063B4C8;
extern int D_0063B4CC;
extern KanbanReq *D_0063C3A0;
extern KanbanReq *D_0063C3A4;
extern int D_0063C3A8;
extern int D_0063C3AC;
extern int D_0063C3B0;
extern int NonLinearCameraMove;
extern void iosMcChdirProduct(McReq *mc);
extern int iosMcSync(McReq *mc);
extern void iosMcLoadProductBlock(McReq *mc);
extern void gsResetFunc(int a0);
extern int sceScfGetLanguage(void);
extern KanbanReq *kanbanReqAdd(int a0, int a1);
extern void kanbanReqDel(KanbanReq *r);
extern void kanbanReqDelFade(KanbanReq *r);
extern void isysGObjActiveLink(int a0, int a1);
extern void stgmgrForceSwitchWithFade(int a0, float a1, float a2);
extern void lt_switch_layout(int a0);

int kanbanBootMcCheck(void)
{
    McReq *mc = &D_0071CF00;
    KanbanStageRec *r;
    int *lp;
    int lang;
    int ret = 0;

    switch (D_0063B4C0) {
    case 0:
        D_0063C3A4 = 0;
        /* fallthrough */
    case 1:
        D_0063C3AC = 0;
        D_0063C3A8 = 3;
        D_0063B4C0++;
        /* fallthrough */
    case 2:
        D_0063A054 = 1;
        mc->f8 = D_0063C3AC;
        mc->fC = 0;
        mc->f0.ll &= ~2;
        iosMcChdirProduct(mc);
        D_0063B4C0++;
        /* fallthrough */
    case 3:
        if (iosMcSync(mc) != 0) {
            D_0063B4C0++;
        }
        break;
    case 4:
        if (mc->f14 == 2) {
            D_0063C3A8 = 0;
            if (mc->f10 == 0 && D_0063B4CC == 0) {
                D_0063B4C0 = 95;
                break;
            }
            if (mc->f20 == 0 || mc->f10 == 0 || mc->f18 >= 360) {
                D_0063B4C0 = 100;
                break;
            }
            D_0063C3A8 = 4;
        }
        if (D_0063C3AC == 0) {
            D_0063C3AC = 1;
            D_0063B4C0 = 2;
        } else {
            D_0063B4C0 = 90;
        }
        break;
    case 90:
        if (D_0063C3A8 == 3) {
            if (--D_0063B4C8 > 0) {
                D_0063B4C0 = 1;
                break;
            }
        }
        D_0063B4C8 = 0;
        D_0063B4C0 = 100;
        break;
    case 95:
        iosMcLoadProductBlock(mc);
        D_0063B4C0++;
        break;
    case 96:
        if (iosMcSync(mc) == 0) {
            break;
        }
        if (mc->f10 != 0) {
            D_0063B4C0 = 100;
            break;
        }
        D_0063B4C0++;
        r = &D_0029B5F0[mc->f8];
        NonLinearCameraMove = r->f1E8;
        D_0028F4C0[0] = r->f1EC;
        gsResetFunc(0);
        break;
    case 97:
        if (D_0028F4D8[0] != 0) {
            break;
        }
        D_0063B4C0 = 190;
        break;
    case 100:
        if (D_0028F4D8[0] != 0) {
            break;
        }
        D_0063B4C0 = 101;
        break;
    case 101:
        if (D_0063B4CC != 0) {
            D_0063B4C0 = 300;
            break;
        }
        D_0063C3A8 = -1;
        lang = sceScfGetLanguage();
        lp = D_00534010;
        switch (lang) {
        case 1:
            *lp = 26;
            break;
        case 2:
            *lp = 27;
            break;
        case 3:
            *lp = 30;
            break;
        case 4:
            *lp = 28;
            break;
        case 5:
            *lp = 29;
            break;
        }
        D_0063C3A0 = kanbanReqAdd(0, 2);
        D_0063B4C0++;
        break;
    case 102:
        if (D_0063C3A0->f8 != 1) {
            break;
        }
        switch (D_0063C3A0->obj[11]) {
        case 26:
            NonLinearCameraMove = 2;
            break;
        case 27:
            NonLinearCameraMove = 3;
            break;
        case 28:
            NonLinearCameraMove = 4;
            break;
        case 29:
            NonLinearCameraMove = 5;
            break;
        case 30:
            NonLinearCameraMove = 6;
            break;
        }
        kanbanReqDelFade(D_0063C3A0);
        D_0063B4C0 = 190;
        D_0063B4CC = 1;
        break;
    case 190:
        D_0063B4C0 = 191;
        break;
    case 191:
        stgmgrForceSwitchWithFade(1, 255.0f, 0.0f);
        lt_switch_layout(7);
        /* fallthrough */
    case 192:
    case 193:
        D_0063B4C0++;
        break;
    case 194:
        if (D_0028F4D8[0] != 0) {
            break;
        }
        if (D_0063C3A8 != 0) {
            D_0063B4C0 = 200;
        } else {
            D_0063B4C0 = 300;
        }
        isysGObjActiveLink(0, 1);
        break;
    case 200:
        D_0063C3A0 = kanbanReqAdd(1, 2);
        D_0063C3B0 = D_0028F4C0[0];
        D_0063B4C0++;
        break;
    case 201:
        switch (D_0063C3A0->obj[11]) {
        case 33:
            D_0028F4C0[0] = 1;
            break;
        case 34:
            D_0028F4C0[0] = 0;
            break;
        }
        if (D_0063C3B0 != D_0028F4C0[0]) {
            D_0063C3B0 = D_0028F4C0[0];
            gsResetFunc(0);
        }
        if (D_0063C3A0->f8 != 1) {
            break;
        }
        kanbanReqDelFade(D_0063C3A0);
        D_0063B4C0++;
        break;
    case 202:
        if (D_0063C3A8 != 0) {
            D_0063B4C0 = 1;
        } else {
            D_0063B4C0 = 300;
        }
        isysGObjActiveLink(0, 1);
        break;
    case 300:
        if (D_0063C3A8 == 0) {
            D_0063B4C0 = -1;
            break;
        }
        D_0063B4C0 = 301;
        /* fallthrough */
    case 301:
        D_0063A054 = 0;
        fadeStatus = 0;
        D_0063C3A0 = kanbanReqAdd(5, 2);
        if (D_0063C3A4 != 0) {
            kanbanReqDel(D_0063C3A4);
        }
        D_0063C3A4 = kanbanReqAdd(D_0063C3A8, 1);
        D_0063B4C0++;
        break;
    case 302:
        if (D_0063C3A0->f8 != 1) {
            break;
        }
        if (D_0063C3A0->obj[11] == 41) {
            D_0063B4C0 = -1;
            kanbanReqDelFade(D_0063C3A4);
            kanbanReqDelFade(D_0063C3A0);
            break;
        }
        kanbanReqDelFade(D_0063C3A4);
        kanbanReqDelFade(D_0063C3A0);
        D_0063B4C0 = 1;
        break;
    default:
        D_0063A054 = 0;
        fadeStatus = 0;
        ret = 1;
        break;
    }
    return ret;
}

extern int D_0028F4D4[];
extern KanbanReq *D_0063C3B4;
extern int D_0063C3B8;
extern void kanbanReqAllDelFade(void);

void kanbanBootMain(void)
{
    switch (D_0063B4BC) {
    case 0:
        isysGObjActiveLink(0, 1);
        D_0028F4D4[0] = 0;
        D_0063B4C0 = 0;
        D_0063B4BC++;
        /* fallthrough */
    case 1:
        if (D_0063B4C4 != 0) {
            D_0063B4BC++;
        }
        break;
    case 2:
        if (kanbanBootMcCheck() == 0) {
            return;
        }
        kanbanReqAllDelFade();
        D_0063C3B4 = kanbanReqAdd(2, 1);
        D_0063B4BC++;
        break;
    case 3:
        D_0063C3B8 = (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 5;
        D_0063B4BC++;
        /* fallthrough */
    case 4:
        D_0063C3B8--;
        if (D_0063C3B8 != -1) {
            break;
        }
        D_0063B4BC++;
        /* fallthrough */
    case 5:
        if (D_0028F4D8[0] != 0) {
            return;
        }
        D_0063B4BC++;
        break;
    case 6:
        kanbanReqAllDelFade();
        D_0063B4BC++;
        break;
    case 7:
        if (D_0063C3B4->obj != 0) {
            return;
        }
        D_0063B4D0 = 1;
        D_0063B4BC++;
        break;
    }
}

inline void kanbanBootStart(void)
{
    D_0063B4C4 = 1;
}
