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
#include "include_asm.h"

/* .sdata: the boot sequence's step, the
   card check's step, the start request, the card retry count and
   kanbanBootEnd. */
static int bootStep = 0; /* derived name */

static int mcCheckStep = 0; /* derived name */

static int bootStarted = 0; /* derived name */

static int mcRetryCount = 10; /* derived name */

int kanbanBootEnd = 0;

inline void kanbanBootInit(void)
{
    bootStep = 0;
    systemStatus[11] = 0;
    kanbanBootEnd = 0;
    fadeStatus = 0;
    bootStarted = 0;
}

/* .bss: the boot-time memory-card request block */
static McMgr bootMcReq; /* derived name */

/* .sbss */
static Kanban *bootKanban; /* derived name */ /* the sign the boot sequence is showing */

static Kanban *bootKanbanSub; /* derived name */ /* the second sign shown beside it */

/* the sign id the card check picked: 3 none, 0 ok, 4 full, -1 clear */
static int mcKanbanId; /* derived name */

static int mcPort; /* derived name */ /* the card slot being checked, 0 then 1 */

/* mcard.c's request entry points; they return iosMsgSend's result, which
   this TU reads only from iosMcSync: it declares the others void, which its
   calls pin, so it does not include mcard.h */
extern void iosMcChdirProduct(McMgr *mp);
extern int iosMcSync(McMgr *mp);
extern void iosMcLoadProductBlock(McMgr *mp);

INCLUDE_ASM(kanbanBootMcCheck);

static Kanban *waitKanban; /* derived name */ /* the "please wait" sign */

static int waitTimer; /* derived name */ /* frames left on that sign */

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
        waitKanban = kanbanReqAdd(0, 1);
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
        if (waitKanban->layout != 0) {
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
