#include "StageManager.h"
#include "layout_texture.h"
#include "gobj.h"
#include "kanbanBoot.h"
#include <libscf.h>
#include "kanban.h"
#include "GsBase.h"
#include "main.h"
#include "Basic.h"
#include "debug.h"

/* kanbanBoot.o's .sdata run (VMA 0x63B4BC..0x63B4D4, 0x18 B; MAIN.MAP's
   January object is 0x10), in the ROM's order: the boot sequence's step, the
   card check's step, the start request, the card retry count, the boot sign's
   done flag and kanbanBootEnd (MAIN.MAP global). */
static int bootStep = 0; /* derived name */

static int mcCheckStep = 0; /* derived name */

static int bootStarted = 0; /* derived name */

static int mcRetryCount = 10; /* derived name */

static int bootKanbanDone = 0; /* derived name */

int kanbanBootEnd = 0;

inline void kanbanBootInit(void)
{
    bootStep = 0;
    systemStatus[11] = 0;
    kanbanBootEnd = 0;
    fadeStatus = 0;
    bootStarted = 0;
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
   no symbol in the run): the boot-time memory-card request block, on the
   64-byte alignment of a DMA transfer buffer (the 0x30 zero bytes before it
   are that alignment's fill). */
static McReq bootMcReq __attribute__((aligned(64)));
/* kept local: mcard.c's save records, read here as this file's view */
extern KanbanStageRec IosMcProductFile[];
extern int D_00534010[];

/* .sbss, owned by kanbanBoot.o and reached only from this file (MAIN.MAP names
   no symbol in the run), in the ROM's run order. */
static KanbanReq *bootKanban; /* the sign the boot sequence is showing */

static KanbanReq *bootKanbanSub; /* the second sign shown beside it */

static int mcKanbanId; /* the sign id the card check picked: 3 none, 0 ok, 4 full, -1 clear */

static int mcPort; /* the card slot being checked, 0 then 1 */

static int bootVideoMode; /* the video mode in force when the sign went up */

/* kept local: returns void here, int in mcard.h */
extern void iosMcChdirProduct(void *a0);
/* kept local: agrees with mcard.h, which this TU does not include (iosMcChdirProduct, iosMcLoadProductBlock differ) */
extern int iosMcSync(unsigned long *a0);
/* kept local: returns void here, int in mcard.h */
extern void iosMcLoadProductBlock(void *a0);
extern KanbanReq *kanbanReqAdd(int a0, int a1);

int kanbanBootMcCheck(void)
{
    McReq *mc = &bootMcReq;
    KanbanStageRec *r;
    int *lp;
    int lang;
    int ret = 0;

    switch (mcCheckStep) {
    case 0:
        bootKanbanSub = 0;
        /* fallthrough */
    case 1:
        mcPort = 0;
        mcKanbanId = 3;
        mcCheckStep++;
        /* fallthrough */
    case 2:
        fbKeep = 1;
        mc->f8 = mcPort;
        mc->fC = 0;
        mc->f0.ll &= ~2;
        iosMcChdirProduct(mc);
        mcCheckStep++;
        /* fallthrough */
    case 3:
        if (iosMcSync(mc) != 0) {
            mcCheckStep++;
        }
        break;
    case 4:
        if (mc->f14 == 2) {
            mcKanbanId = 0;
            if (mc->f10 == 0 && bootKanbanDone == 0) {
                mcCheckStep = 95;
                break;
            }
            if (mc->f20 == 0 || mc->f10 == 0 || mc->f18 >= 360) {
                mcCheckStep = 100;
                break;
            }
            mcKanbanId = 4;
        }
        if (mcPort == 0) {
            mcPort = 1;
            mcCheckStep = 2;
        } else {
            mcCheckStep = 90;
        }
        break;
    case 90:
        if (mcKanbanId == 3) {
            if (--mcRetryCount > 0) {
                mcCheckStep = 1;
                break;
            }
        }
        mcRetryCount = 0;
        mcCheckStep = 100;
        break;
    case 95:
        iosMcLoadProductBlock(mc);
        mcCheckStep++;
        break;
    case 96:
        if (iosMcSync(mc) == 0) {
            break;
        }
        if (mc->f10 != 0) {
            mcCheckStep = 100;
            break;
        }
        mcCheckStep++;
        r = &IosMcProductFile[mc->f8];
        NonLinearCameraMove = r->f1E8;
        systemStatus[0] = r->f1EC;
        gsResetFunc(0);
        break;
    case 97:
        if (systemStatus[6] != 0) {
            break;
        }
        mcCheckStep = 190;
        break;
    case 100:
        if (systemStatus[6] != 0) {
            break;
        }
        mcCheckStep = 101;
        break;
    case 101:
        if (bootKanbanDone != 0) {
            mcCheckStep = 300;
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
        mcCheckStep++;
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
        mcCheckStep = 190;
        bootKanbanDone = 1;
        break;
    case 190:
        mcCheckStep = 191;
        break;
    case 191:
        stgmgrForceSwitchWithFade(1, 255.0f, 0.0f);
        lt_switch_layout(7);
        /* fallthrough */
    case 192:
    case 193:
        mcCheckStep++;
        break;
    case 194:
        if (systemStatus[6] != 0) {
            break;
        }
        if (mcKanbanId != 0) {
            mcCheckStep = 200;
        } else {
            mcCheckStep = 300;
        }
        isysGObjActiveLink(0, 1);
        break;
    case 200:
        bootKanban = kanbanReqAdd(1, 2);
        bootVideoMode = systemStatus[0];
        mcCheckStep++;
        break;
    case 201:
        switch (bootKanban->obj[11]) {
        case 33:
            systemStatus[0] = 1;
            break;
        case 34:
            systemStatus[0] = 0;
            break;
        }
        if (bootVideoMode != systemStatus[0]) {
            bootVideoMode = systemStatus[0];
            gsResetFunc(0);
        }
        if (bootKanban->f8 != 1) {
            break;
        }
        kanbanReqDelFade(bootKanban);
        mcCheckStep++;
        break;
    case 202:
        if (mcKanbanId != 0) {
            mcCheckStep = 1;
        } else {
            mcCheckStep = 300;
        }
        isysGObjActiveLink(0, 1);
        break;
    case 300:
        if (mcKanbanId == 0) {
            mcCheckStep = -1;
            break;
        }
        mcCheckStep = 301;
        /* fallthrough */
    case 301:
        fbKeep = 0;
        fadeStatus = 0;
        bootKanban = kanbanReqAdd(5, 2);
        if (bootKanbanSub != 0) {
            kanbanReqDel(bootKanbanSub);
        }
        bootKanbanSub = kanbanReqAdd(mcKanbanId, 1);
        mcCheckStep++;
        break;
    case 302:
        if (bootKanban->f8 != 1) {
            break;
        }
        if (bootKanban->obj[11] == 41) {
            mcCheckStep = -1;
            kanbanReqDelFade(bootKanbanSub);
            kanbanReqDelFade(bootKanban);
            break;
        }
        kanbanReqDelFade(bootKanbanSub);
        kanbanReqDelFade(bootKanban);
        mcCheckStep = 1;
        break;
    default:
        fbKeep = 0;
        fadeStatus = 0;
        ret = 1;
        break;
    }
    return ret;
}

static KanbanReq *waitKanban; /* the "please wait" sign */

static int waitTimer; /* frames left on that sign */

void kanbanBootMain(void)
{
    switch (bootStep) {
    case 0:
        isysGObjActiveLink(0, 1);
        systemStatus[5] = 0;
        mcCheckStep = 0;
        bootStep++;
        /* fallthrough */
    case 1:
        if (bootStarted != 0) {
            bootStep++;
        }
        break;
    case 2:
        if (kanbanBootMcCheck() == 0) {
            return;
        }
        kanbanReqAllDelFade();
        waitKanban = kanbanReqAdd(2, 1);
        bootStep++;
        break;
    case 3:
        waitTimer = (60 - systemStatus[0] * 10) / systemStatus[1] * 5;
        bootStep++;
        /* fallthrough */
    case 4:
        waitTimer--;
        if (waitTimer != -1) {
            break;
        }
        bootStep++;
        /* fallthrough */
    case 5:
        if (systemStatus[6] != 0) {
            return;
        }
        bootStep++;
        break;
    case 6:
        kanbanReqAllDelFade();
        bootStep++;
        break;
    case 7:
        if (waitKanban->obj != 0) {
            return;
        }
        kanbanBootEnd = 1;
        bootStep++;
        break;
    }
}

inline void kanbanBootStart(void)
{
    bootStarted = 1;
}
