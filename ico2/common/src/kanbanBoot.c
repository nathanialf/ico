#include "common.h"
#include "StageManager.h"
#include "layout_texture.h"
#include "gobj.h"
#include "kanbanBoot.h"
#include <libscf.h>
#include "kanban.h"

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
    /* the product block iosMcLoadProductBlock reads into.  Its length is the
       ROM's own: the run this object owns is 0xA00 bytes and nothing in the
       ROM forms an address inside it, so the tail is one buffer. */
    char block[0xA00 - 0x24];
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

/* .bss, owned by kanbanBoot.o and reached only from this file (MAIN.MAP names
   no symbol in the run): the boot-time memory-card request block. */
static McReq bootMcReq;

extern KanbanStageRec D_0029B5F0[];
extern int D_00534010[];
extern int D_0028F4C0[];
extern int D_0028F4D8[];
extern int fbKeep;
extern int D_0063B4C0;
extern int D_0063B4C8;
extern int D_0063B4CC;

/* .sbss, owned by kanbanBoot.o and reached only from this file (MAIN.MAP names
   no symbol in the run), in the ROM's run order. */
static KanbanReq *bootKanban; /* the sign the boot sequence is showing */

static KanbanReq *bootKanbanSub; /* the second sign shown beside it */

static int mcKanbanId; /* the sign id the card check picked: 3 none, 0 ok, 4 full, -1 clear */

static int mcPort; /* the card slot being checked, 0 then 1 */

static int bootVideoMode; /* the video mode in force when the sign went up */

extern int NonLinearCameraMove;
/* kept local: this TU's uses of iosMcChdirProduct do not fit the prototype in mcard.h */
extern void iosMcChdirProduct(McReq *mc);
/* kept local: this TU's uses of iosMcSync do not fit the prototype in mcard.h */
extern int iosMcSync(McReq *mc);
/* kept local: this TU's uses of iosMcLoadProductBlock do not fit the prototype in mcard.h */
extern void iosMcLoadProductBlock(McReq *mc);
/* kept local: this TU's uses of gsResetFunc do not fit the prototype in debug.h */
extern void gsResetFunc(int a0);
extern KanbanReq *kanbanReqAdd(int a0, int a1);

int kanbanBootMcCheck(void)
{
    McReq *mc = &bootMcReq;
    KanbanStageRec *r;
    int *lp;
    int lang;
    int ret = 0;

    switch (D_0063B4C0) {
    case 0:
        bootKanbanSub = 0;
        /* fallthrough */
    case 1:
        mcPort = 0;
        mcKanbanId = 3;
        D_0063B4C0++;
        /* fallthrough */
    case 2:
        fbKeep = 1;
        mc->f8 = mcPort;
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
            mcKanbanId = 0;
            if (mc->f10 == 0 && D_0063B4CC == 0) {
                D_0063B4C0 = 95;
                break;
            }
            if (mc->f20 == 0 || mc->f10 == 0 || mc->f18 >= 360) {
                D_0063B4C0 = 100;
                break;
            }
            mcKanbanId = 4;
        }
        if (mcPort == 0) {
            mcPort = 1;
            D_0063B4C0 = 2;
        } else {
            D_0063B4C0 = 90;
        }
        break;
    case 90:
        if (mcKanbanId == 3) {
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
        mcKanbanId = -1;
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
        bootKanban = kanbanReqAdd(0, 2);
        D_0063B4C0++;
        break;
    case 102:
        if (bootKanban->f8 != 1) {
            break;
        }
        switch (bootKanban->obj[11]) {
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
        kanbanReqDelFade(bootKanban);
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
        if (mcKanbanId != 0) {
            D_0063B4C0 = 200;
        } else {
            D_0063B4C0 = 300;
        }
        isysGObjActiveLink(0, 1);
        break;
    case 200:
        bootKanban = kanbanReqAdd(1, 2);
        bootVideoMode = D_0028F4C0[0];
        D_0063B4C0++;
        break;
    case 201:
        switch (bootKanban->obj[11]) {
        case 33:
            D_0028F4C0[0] = 1;
            break;
        case 34:
            D_0028F4C0[0] = 0;
            break;
        }
        if (bootVideoMode != D_0028F4C0[0]) {
            bootVideoMode = D_0028F4C0[0];
            gsResetFunc(0);
        }
        if (bootKanban->f8 != 1) {
            break;
        }
        kanbanReqDelFade(bootKanban);
        D_0063B4C0++;
        break;
    case 202:
        if (mcKanbanId != 0) {
            D_0063B4C0 = 1;
        } else {
            D_0063B4C0 = 300;
        }
        isysGObjActiveLink(0, 1);
        break;
    case 300:
        if (mcKanbanId == 0) {
            D_0063B4C0 = -1;
            break;
        }
        D_0063B4C0 = 301;
        /* fallthrough */
    case 301:
        fbKeep = 0;
        fadeStatus = 0;
        bootKanban = kanbanReqAdd(5, 2);
        if (bootKanbanSub != 0) {
            kanbanReqDel(bootKanbanSub);
        }
        bootKanbanSub = kanbanReqAdd(mcKanbanId, 1);
        D_0063B4C0++;
        break;
    case 302:
        if (bootKanban->f8 != 1) {
            break;
        }
        if (bootKanban->obj[11] == 41) {
            D_0063B4C0 = -1;
            kanbanReqDelFade(bootKanbanSub);
            kanbanReqDelFade(bootKanban);
            break;
        }
        kanbanReqDelFade(bootKanbanSub);
        kanbanReqDelFade(bootKanban);
        D_0063B4C0 = 1;
        break;
    default:
        fbKeep = 0;
        fadeStatus = 0;
        ret = 1;
        break;
    }
    return ret;
}

extern int D_0028F4D4[];

static KanbanReq *waitKanban; /* the "please wait" sign */

static int waitTimer; /* frames left on that sign */

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
        waitKanban = kanbanReqAdd(2, 1);
        D_0063B4BC++;
        break;
    case 3:
        waitTimer = (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 5;
        D_0063B4BC++;
        /* fallthrough */
    case 4:
        waitTimer--;
        if (waitTimer != -1) {
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
        if (waitKanban->obj != 0) {
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
