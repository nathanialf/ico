#include "layout_action.h"
#include "gamesys.h"
#include "op.h"
#include "debug.h"
#include "layout_texture.h"
#include "pad.h"
#include "gobj.h"
#include "adpcm_init.h"
#include "fightSound.h"
#include "gflag.h"
#include "kanbanBoot.h"
#include "script.h"
#include "GsBase.h"
#include <libcdvd.h>
#include <string.h>
#include "StageAnimation.h"
#include "Basic.h"
#include <stdlib.h>
#include "boyact.h"
#include "act-game.h"
#include "StageManager.h"
#include "s_init.h"
#include "typedef.h"
#include "main.h"
#include "frameDependSequence.h"
#include "matrixDrive.h"

static int _la_set_current_port_2(void *p, int first);
static int _la_set_current_port_lock_2(void *p, int first);
static void _la_set_preview_info(void);

/* the custom key map's sixteen pad button codes (iosPadConfCustom.bit),
   the default one bit per button */
typedef struct { /* field names derived */
    int code[16];
} KeyConf; /* derived name */

/* A card port's state as _la_memory_card_check finds it, read whole and
   through a one-bit view: currentPortLockState tests bits 1 and 3..5 of the
   word, and _la_set_current_port_new tests bit 1 and sets bits 2 and 6 of
   both ports through the bits. */
typedef union { /* field names derived */
    unsigned int w;

    struct {
        unsigned int card : 1;      /* a card is in the slot */
        unsigned int ps2Card : 1;   /* it is a PlayStation 2 card */
        unsigned int bothPs2 : 1;   /* both slots hold one */
        unsigned int formatted : 1; /* sceMcGetInfo's format flag */
        unsigned int hasSpace : 1;  /* 360 free clusters or more */
        unsigned int hasSave : 1;   /* the card holds this game's save files */
        unsigned int bothSave : 1;  /* both cards do */
    } bit;
} McPortFlags; /* derived name */

typedef struct {       /* field names derived */
    McPortFlags flags; /* 0x0 */
    int fileMask;      /* 0x4, one bit for each save file on the card */
} McPortInfo;          /* derived name */

/* the save preview the file select shows, the four words of typedef.h's
   McFileInfo: the stage, the play time and the save sofa's layout id, then a
   word no function of this build reads or writes */
struct McPreview { /* field names derived */
    int stage;     /* 0x00 */
    int playTime;  /* 0x04, in frames */
    int sofa;      /* 0x08 */
    int word0C;    /* 0x0C, no C reader */
}; /* derived name */

/* .sbss, twelve words: the port-0 lock state _la_set_current_port_2 records and the one
   _la_set_current_port_lock_2 records, the lock results for port 0 and port 1
   of _la_set_current_port_new, the icoMisc lock saved by the logo, the title
   continue and the title new game actions, the progress bar's last step, the
   save select's ready flag, the system save's retry count, the last card
   result, and the progress bar's total. */
static int portLockState; /* derived name */

static int lock2PortState; /* derived name */

static int port0LockResult; /* derived name */

static int port1LockResult; /* derived name */

static int logoIcoMiscLock; /* derived name */

static int continueIcoMiscLock; /* derived name */

static int newGameIcoMiscLock; /* derived name */

static int barLastStep; /* derived name */

static int saveSelectReady; /* derived name */

static int systemSaveRetry; /* derived name */

static int mcLastResult; /* derived name */

static int barTotal; /* derived name */

/* .bss: the two card ports' records, the preview
   record of the save being confirmed, the open request of the layout voice
   and the twenty game flags kept across a load. */
static McPortInfo mcPortInfo[2]; /* derived name */

static struct McPreview previewInfo; /* derived name */

static AdpcmOpenReq voiceOpenReq; /* derived name */

static signed char keepFlags[20]; /* derived name */

/* pad idx's trigger bit for the action, with the cursor sound it plays:
   circle (decide), triangle (cancel), left and right */
inline int PSH_POSITIVE(int idx) /* derived name */
{
    if (pad[idx].flags & 0x40) {
        ExecuteSEPackage(0, 91);
        return 1;
    }
    return 0;
}

inline int PSH_NEGATIVE(int idx) /* derived name */
{
    if (pad[idx].flags & 0x10) {
        ExecuteSEPackage(0, 92);
        return 1;
    }
    return 0;
}

inline int PSH_LEFT(int idx) /* derived name */
{
    if (pad[idx].flags & 0x8000) {
        ExecuteSEPackage(0, 90);
        return 1;
    }
    return 0;
}

inline int PSH_RIGHT(int idx) /* derived name */
{
    if (pad[idx].flags & 0x2000) {
        ExecuteSEPackage(0, 90);
        return 1;
    }
    return 0;
}

void la_TESTFUNCTION(void)
{
    debug_StdPrintfDummy("sync end\n");
}

/* .data: the game-flag ids the load carries across gflagInit.  The list
   holds five ids (this build's flag numbers) and progressive_bar's table
   and the key-config tables follow it; the keep/restore loops below
   walk twenty words. */
static int keepFlagNo[5] = {339, 335, 334, 336, 333}; /* derived name */

/* the busy mark progressive_bar draws beside its bar: a line through a
   7-by-7 box, one of four turns a step (its two ends per turn) */
static sceVu0IVECTOR barLine[4][2] = {{{0, 3, 0, 0}, {7, 3, 0, 0}},
                                      {{0, 0, 0, 0}, {7, 7, 0, 0}},
                                      {{3, 0, 0, 0}, {3, 7, 0, 0}},
                                      {{7, 0, 0, 0}, {0, 7, 0, 0}}}; /* derived name */

/* the eight pad button
   codes the key-config screen offers, and the six-plus-two slot assignments it
   edits. */
static int keyConfigCode[8] = {16, 128, 32, 64, 8, 2, 1, 4}; /* derived name */

static int keyConfigSlot[8] = {1, 2, 3, 4, 5, 0, 0, 0}; /* derived name */

/* the memory-card request block the layout actions drive */
McMgr mc = {{0}};

/* mcard.c's request entry points; they return iosMsgSend's result, which
   this TU reads only from iosMcSync: it declares the others void, which its
   calls pin, so it does not include mcard.h */
extern int iosMcSync(McMgr *mp);
extern void iosMcGetInfo(McMgr *mp);
extern void iosMcLoadProductBlock(McMgr *mp);
extern void iosMcGetBlockSaveInfo(McMgr *mp);
extern void iosMcLoadGameBlock(McMgr *mp, void *arg);
extern void iosMcFormat(McMgr *mp);
extern void iosMcSaveIconBlock(McMgr *mp);
extern void iosMcSaveProductBlock(McMgr *mp);
extern void iosMcSaveGameBlock(McMgr *mp, void *arg);
extern void iosMcDelete(McMgr *mp);
/* mcard.c's preview record */
extern int IosMcPreviewInfo[];

static int _la_mcard_error_check(void *req)
{
    char *w = (char *)req;

    if (*(int *)(w + 0x10) >= 0) {
        return 1;
    }
    switch (*(int *)(w + 0x10)) {
    case 0:
        return 1;
    case -2:
        debug_StdPrintfDummy("unformatted %d\n", *(int *)(w + 0x10));
        return -1;
    case -9:
        debug_StdPrintfDummy("not insert memory card %d\n", *(int *)(w + 0x10));
        return -1;
    case -4:
        debug_StdPrintfDummy("%s file not found\n", w + 0x47C);
        return -1;
    case -14:
        debug_StdPrintfDummy("%s Directory not found\n", w + 0x454);
        return -1;
    case -16:
        debug_StdPrintfDummy("segID %d check sum err rom:%d != load:%d\n", *(int *)(w + 0x24),
                             *(int *)(w + 0x50), *(int *)(w + 0x4C));
        return -1;
    case -15:
        debug_StdPrintfDummy("%s handler func ret err code\n", w + 0x47C);
        return -1;
    case -10:
        debug_StdPrintfDummy("memory over\n");
        return -1;
    default:
        debug_StdPrintfDummy("memory card another err %d\n", *(int *)(w + 0x10));
        return -2;
    }
}

/* file-local: nothing outside this TU calls it */
static int _la_memory_card_check(McMgr *p, int step);

/* .sdata: these ten statics and the two globals after them, then each
   function's own statics before it */
static McPortInfo *curPortInfo = &mcPortInfo[0]; /* derived name */

static int lastPort = -1; /* derived name */

static int curPort = 0; /* derived name */

static int curFile = 0; /* derived name */

static int selectFile = -1; /* derived name */

static int nextStage = 1; /* derived name */

static int fileMask = 0; /* derived name */

static int actionStarted = 0; /* derived name */

static int fightSoundStopped = 0; /* derived name */

static SqEntry *layoutVoice = 0; /* derived name */

int layout_boot_flag = 0;

int enable_game_pause = 1;

/* the current port and port 0's card flags, printed; nothing calls it */
void _la_print_port_flags(void) /* derived name */
{
    debug_StdPrintfDummy("current:%d ec:%d  p2:%d  fo:%d  fr:%d  ed:%d\n", curPort,
                         mcPortInfo[0].flags.bit.card, mcPortInfo[0].flags.bit.ps2Card,
                         mcPortInfo[0].flags.bit.formatted, mcPortInfo[0].flags.bit.hasSpace,
                         mcPortInfo[0].flags.bit.hasSave);
}

static int _la_memory_card_check(McMgr *p, int step)
{
    int r;
    int i;

    curPortInfo = &mcPortInfo[p->port];
    switch (step) {
    case 0:
        curPortInfo->fileMask = 0;
        p->slot = 0;
        memset(&mcPortInfo[p->port], 0, 8);
        p->result = 0;
        iosMcGetInfo(p);
        mcLastResult = 0;
        step++;
        break;
    case 10:
        iosMcLoadProductBlock(p);
        step++;
        break;
    case 20:
        strcpy((char *)p + 0x47C, "game.");
        iosMcGetBlockSaveInfo(p);
        step++;
        break;
    case 1:
    case 11:
    case 21:
        if (iosMcSync(p)) {
            step++;
        }
        break;
    case 12:
    case 22:
        r = _la_mcard_error_check(p);
        if (r > 0) {
            step++;
        }
        if (r >= 0) {
            return step;
        }
        mcLastResult = p->result;
        if (p->result == -9 || r == -2) {
            curPortInfo->flags.w = (int)curPortInfo->flags.w & ~0x20;
            curPortInfo->flags.w = (int)curPortInfo->flags.w & ~2;
            curPortInfo->flags.w = (int)curPortInfo->flags.w & ~1;
        }
        /* falls through */
    case 2:
        step++;
        break;
    case 3:
        switch (p->type) {
        case 0:
            return 99;
        case 1:
        case 3:
            curPortInfo->flags.w |= 1;
            return 99;
        case 2:
            curPortInfo->flags.w |= 3;
            break;
        }
        switch (p->format) {
        case 0:
            return 99;
        case 1:
            curPortInfo->flags.w |= 8;
            break;
        }
        if (p->free >= 400) {
            curPortInfo->flags.w |= 0x10;
        } else {
            curPortInfo->flags.w = (int)curPortInfo->flags.w & ~0x10;
        }
        step = 10;
        break;
    case 13:
        step = 20;
        break;
    case 23:
        if (p->dirCount >= 11) {
            /* "already holds more saves than the set number" */
            debug_StdPrintfDummy(
                "debug_mcLoadMainBlock:既に設定された数以上のデータを保存してる\n");
        }
        for (i = 0; i < 10; i++) {
            if ((1 << i) & p->mask) {
                break;
            }
        }
        step = 99;
        if (i == 10) {
            break;
        }
        if (p->dirCount == 10) {
            curPortInfo->flags.w |= 0x20;
            curPortInfo->fileMask = p->mask;
        }
        break;
    }
    return step;
}

/* the current port's lock state: 1 when its record's bit 1 is set and bits
   3..5 are not 1, else -1; inlined three times into _la_set_current_port_2
   and once into _la_set_current_port_lock_2 */
static inline int currentPortLockState(void) /* derived name */
{
    return (((curPortInfo->flags.w >> 1) & 1) && (curPortInfo->flags.w & 0x38) != 8) ? 1 : -1;
}

static int port2Step = 0; /* derived name */

static int port2SubStep = 0; /* derived name */

static int port2Changed = 0; /* derived name */

static int port2Locked = 0; /* derived name */

static int _la_set_current_port_2(void *p, int first)
{
    McPortInfo tmp;
    int r;
    int q = 0;

    if (first != 0) {
        *(int *)((char *)p + 8) = 0;
        port2Step = 0;
        port2SubStep = 0;
        fileMask = 0;
        return 0;
    }
    curPortInfo = &mcPortInfo[*(int *)((char *)p + 8)];
    port2Step = _la_memory_card_check(p, port2Step);
    if (port2Step == 99) {
        switch (*(int *)((char *)p + 8)) {
        case 0:
            portLockState = currentPortLockState();
            port2Changed = (curPortInfo->flags.w >> 5) & 1;
            port2Locked = ((curPortInfo->flags.w >> 1) & 1) && (curPortInfo->flags.w & 0x38) != 8;
            /* the whole 8-byte record is copied to a local and never read
               again */
            tmp = *curPortInfo;
            *(int *)((char *)p + 8) = 1;
            port2Step = 0;
            break;
        case 1:
            port2Step = 100;
            switch (portLockState) {
            case 1:
                r = currentPortLockState();
                switch (r) {
                case 1:
                    r = curPortInfo->flags.w >> 5;
                    r &= 1;
                    if ((curPortInfo->flags.w >> 1) & 1) {
                        if ((curPortInfo->flags.w & 0x38) != 8) {
                            q = 1;
                        }
                    }
                    if (port2Locked != 0 && q != 0) {
                        mcPortInfo[0].flags.w |= 4;
                        mcPortInfo[1].flags.w |= 4;
                    }
                    if (port2Changed != 0 && r != 0) {
                        mcPortInfo[0].flags.w |= 0x40;
                        mcPortInfo[1].flags.w |= 0x40;
                    }
                    if (lastPort >= 0) {
                        curPort = lastPort;
                    } else if (port2Changed != 0) {
                        curPort = 0;
                    } else if ((curPortInfo->flags.w >> 5) & 1) {
                        curPort = 1;
                    }
                    break;
                case -1:
                    lastPort = r;
                    curPort = 0;
                    curPortInfo = &mcPortInfo[0];
                    curPortInfo->flags.w = (int)curPortInfo->flags.w & ~4;
                    curPortInfo->flags.w = (int)curPortInfo->flags.w & ~0x40;
                    break;
                }
                break;
            case -1:
                r = currentPortLockState();
                switch (r) {
                case 1:
                    curPort = r;
                    curPortInfo = &mcPortInfo[1];
                    curPortInfo->flags.w = (int)curPortInfo->flags.w & ~4;
                    curPortInfo->flags.w = (int)curPortInfo->flags.w & ~0x40;
                    break;
                case -1:
                    curPort = 0;
                    curPortInfo = &mcPortInfo[0];
                    if ((mcPortInfo[0].flags.w & 1) || (mcPortInfo[1].flags.w & 1)) {
                        mcPortInfo[0].flags.w |= 1;
                    }
                    if (((mcPortInfo[0].flags.w >> 1) & 1) || ((mcPortInfo[1].flags.w >> 1) & 1)) {
                        curPortInfo->flags.w |= 2;
                    }
                    curPortInfo->flags.w = (int)curPortInfo->flags.w & ~4;
                    curPortInfo->flags.w = (int)curPortInfo->flags.w & ~0x40;
                    _la_set_current_port_2(p, 1);
                    return -1;
                }
                break;
            }
            curPortInfo = &mcPortInfo[curPort];
            _la_set_current_port_2(p, 1);
            return 1;
        }
    }
    return 0;
}

static int lock2Restart = 1; /* derived name */

static int lock2Step = 0; /* derived name */

static int lock2SubStep = 0; /* derived name */

static int lock2Changed = 0; /* derived name */

static int lock2Locked = 0; /* derived name */

static int _la_set_current_port_lock_2(void *p, int first)
{
    McPortInfo tmp;
    int r;
    int a;
    int q;

    if (first != 0 || lock2Restart != 0) {
        *(int *)((char *)p + 8) = curPort;
        lock2Step = 0;
        lock2Restart = 0;
        lock2SubStep = 0;
        fileMask = 0;
        return 0;
    }
    curPortInfo = &mcPortInfo[*(int *)((char *)p + 8)];
    lock2Step = _la_memory_card_check(p, lock2Step);
    if (lock2Step != 99) {
        return 0;
    }
    r = currentPortLockState();
    lock2PortState = r;
    lock2Changed = (curPortInfo->flags.w >> 5) & 1;
    lock2Locked = ((curPortInfo->flags.w >> 1) & 1) && (curPortInfo->flags.w & 0x38) != 8;
    tmp = *curPortInfo;
    switch (lock2PortState) {
    case 1:
        a = curPortInfo->flags.w >> 5;
        a &= 1;
        q = 0;
        if ((curPortInfo->flags.w >> 1) & 1) {
            if ((curPortInfo->flags.w & 0x38) != 8) {
                q = 1;
            }
        }
        if (lock2Locked != 0 && q != 0) {
            mcPortInfo[*(int *)((char *)p + 8)].flags.w |= 4;
        }
        if (lock2Changed != 0 && a != 0) {
            mcPortInfo[*(int *)((char *)p + 8)].flags.w |= 0x40;
        }
        _la_set_current_port_lock_2(p, 1);
        return 1;
    case -1:
        curPortInfo = &mcPortInfo[curPort];
        curPortInfo->flags.w = (int)curPortInfo->flags.w & ~4;
        curPortInfo->flags.w = (int)curPortInfo->flags.w & ~0x40;
        return -1;
    }
    return 0;
}

static int portNewStep = 0; /* derived name */

static int portNewRestart = 1; /* derived name */

static int _la_set_current_port_new(McMgr *p, int first)
{
    int r = 0;
    int v;

    if (first) {
        portNewStep = 0;
        curPort = -1;
    }
    switch (portNewStep) {
    case 0:
    case 2:
        curPort++;
        portNewRestart = 1;
        portNewStep++;
        break;
    case 1:
        port0LockResult = _la_set_current_port_lock_2(p, portNewRestart);
        portNewRestart = 0;
        if (port0LockResult == 0) {
            break;
        }
        portNewStep++;
        break;
    case 3:
        port1LockResult = _la_set_current_port_lock_2(p, portNewRestart);
        portNewRestart = 0;
        if (port1LockResult == 0) {
            break;
        }
        portNewStep++;
        break;
    case 4:
        v = ((mcPortInfo[0].flags.w >> 1) & 1) && ((mcPortInfo[1].flags.w >> 1) & 1);
        mcPortInfo[0].flags.bit.bothPs2 = mcPortInfo[1].flags.bit.bothPs2 = v;
        v = ((mcPortInfo[0].flags.w >> 5) & 1) && ((mcPortInfo[1].flags.w >> 5) & 1);
        mcPortInfo[0].flags.bit.bothSave = mcPortInfo[1].flags.bit.bothSave = v;
        if (port0LockResult == 1) {
            curPort = 0;
            r = 1;
        } else if (port1LockResult == 1) {
            curPort = 1;
            r = 1;
        } else {
            if ((mcPortInfo[0].flags.w & 1) == 0 && mcPortInfo[1].flags.bit.card == 1) {
                curPort = 1;
            } else {
                curPort = 0;
            }
            r = -1;
        }
        p->port = curPort;
        curPortInfo = &mcPortInfo[curPort];
        break;
    }
    return r;
}

inline int la_boot_no_memory_card(int first, int item)
{
    debug_StdPrintfDummy("no memoca\n");
    return item;
}

inline int la_boot_no_free_area(int first, int item)
{
    debug_StdPrintfDummy("no free\n");
    return item;
}

inline int la_boot_memory_card_check(void)
{
    if (kanbanBootEnd == 0) {
        return -1;
    }
    systemStatus[11] = 7;
    layout_boot_flag = 1;
    lt_set_item_select_func(0);
    actionStarted = 0;
    return 0x33;
}

inline int la_boot_confirm_memory_card(void)
{
    if (PSH_POSITIVE(0)) {
        return lt_link_layout(0);
    }
    return -1;
}

inline int la_vibe_select(void)
{
    if (lt_fade_status() == 2 && (pad[0].flags & 0x40)) {
        soundSeDefPlay(403, 0xFFFFFFFF, 0, 0);
        switch (lt_current_property_item()) {
        case 8:
            iosPadActRequestEnable = 1;
            break;
        case 9:
            iosPadActRequestEnable = 0;
            break;
        }
        gflagInit();
        systemStatus[4] = 0;
        gflagOn(333);
        return -1;
    }
    if (PSH_NEGATIVE(0)) {
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 9;
    }
    return -1;
}

int title_demo_mode = 0;

static int continueDecided = 0; /* derived name */

inline int la_scei_logo(int first)
{
    if (first) {
        stgmgrNextStagePreLoadForceStageSet(0);
        logoIcoMiscLock = GlobalTimer;
        systemStatus[5] = 1;
        iosPadEnable();
        isysGObjActiveLink(0, 0);
        gflagOff(337);
        if (layout_boot_flag == 0) {
            layout_boot_flag = 1;
        }
    }
    return -1;
}

inline int la_title_demo(void)
{
    return -1;
}

int la_title_continue_or_new(int first)
{
    if (first) {
        continueIcoMiscLock = GlobalTimer;
        iosPadEnable();
        isysGObjActiveLink(0, 1);
        systemStatus[5] = 0;
        gflagOff(333);
        if (gflagChk(336) == 0) {
            gflagOn(336);
        }
        continueDecided = 0;
    }
    if (continueDecided != 0) {
        lt_item_select_disable = 0;
        lt_mask_property(14, 0);
        lt_mask_property(15, 0);
    } else {
        lt_item_select_disable = 1;
        lt_mask_property(14, 1);
        lt_mask_property(15, 1);
    }
    if (continueDecided != 0 && (pad[0].flags & 0x840) && lt_fade_status() == 2) {
        soundSeDefPlay(402, 0xFFFFFFFF, 0, 0);
        switch (lt_current_property_item()) {
        case 14:
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 17;
        case 15:
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 6;
        }
    }
    switch (_la_set_current_port_2(&mc, first)) {
    case 0:
        break;
    case 1:
        if ((curPortInfo->flags.w & 0x22) == 2) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 10;
        }
        continueDecided = 1;
        break;
    case -1:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 10;
    }
    return -1;
}

static int newGameDecided = 0; /* derived name */

int la_title_new_game_only(int first)
{
    if (first) {
        newGameIcoMiscLock = GlobalTimer;
        iosPadEnable();
        isysGObjActiveLink(0, 1);
        systemStatus[5] = 0;
        gflagOff(333);
        if (gflagChk(336) == 0) {
            gflagOn(336);
        }
        newGameDecided = 0;
        lastPort = -1;
    }
    if (newGameDecided != 0) {
        lt_item_select_disable = 0;
        lt_mask_property(16, 0);
    } else {
        lt_item_select_disable = 1;
        lt_mask_property(16, 1);
    }
    if (newGameDecided != 0 && (pad[0].flags & 0x840) && lt_fade_status() == 2) {
        soundSeDefPlay(402, 0xFFFFFFFF, 0, 0);
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 6;
    }
    switch (_la_set_current_port_2(&mc, first)) {
    case 0:
        break;
    case -1:
        newGameDecided = 1;
        break;
    case 1:
        if ((curPortInfo->flags.w >> 5) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 9;
        }
        newGameDecided = 1;
        break;
    }
    return -1;
}

static int filePort = -1; /* derived name */

/* the file select's item callback: the cursor moves five a row or one a
   column over the ten files and skips the empty ones */
inline int la_mc_saved_file_select(int item)
{
    int i = item - 27;

    do {
        if (pad[0].flags & 0x1000) {
            i += 5;
        } else if (pad[0].flags & 0x4000) {
            i -= 5;
        } else if (pad[0].flags & 0x8000) {
            i -= 1;
        } else if (pad[0].flags & 0x2000) {
            i += 1;
        } else if (IosMcProductFile[filePort].file[i].stage == 0xFFFFFFFF) {
            i++;
        }
        if (i < 0) {
            i += 10;
        }
        if (i >= 10) {
            i -= 10;
        }
    } while (IosMcProductFile[filePort].file[i].stage == 0xFFFFFFFF);
    return i + 27;
}

inline int la_mc_file_select(int first)
{
    int i;

    curFile = lt_current_property_item() - 27;

    if (actionStarted == 0) {
        lt_item_select_disable = 1;
        return -1;
    }

    for (i = 0; i < 10; i++) {
        if (((fileMask >> i) & 1) && IosMcProductFile[filePort].file[i].stage != 0xFFFFFFFF) {
            lt_mask_property(i + 27, 0);
            lt_mask_property(i + 17, 1);
        } else {
            lt_mask_property(i + 27, 1);
            lt_mask_property(i + 17, 0);
        }
    }

    previewInfo = *(struct McPreview *)&IosMcProductFile[filePort].file[curFile];

    return (pad[0].flags & 0x50) ? curFile : -1;
}

static inline void _la_mask_preview_info(void)
{
    int i;

    for (i = 0; i < 10; i++) {
        lt_mask_property(i + 41, 1);
        lt_mask_property(i + 51, 1);
        lt_mask_property(i + 61, 1);
        lt_mask_property(i + 71, 1);
        lt_mask_property(i + 81, 1);
        lt_mask_property(i + 91, 1);
    }
    lt_mask_property(39, 1);
    lt_mask_property(40, 1);
    for (i = 0; i < 39; i++) {
        lt_mask_property(i + 101, 1);
    }
}

/* the frames a second, 60 or 50 by the video mode, over the field rate */
#define FRAME_RATE ((60 - systemStatus[0] * 10) / systemStatus[1]) /* derived name */

/* the play time of a save record split into hours (mod 100), minutes and
   seconds, inlined into _la_set_preview_info (which clamps it to 99:59:59),
   la_load_processing, la_system_save_processing and la_save_processing; the
   last three leave the results unused */
static inline void playTime(struct McPreview *p, int *hour, int *min, int *sec) /* derived name */
{
    *sec = (p->playTime / FRAME_RATE) % 60;
    *min = (p->playTime / (FRAME_RATE * 60)) % 60;
    *hour = (p->playTime / (FRAME_RATE * 3600)) % 100;
}

static void _la_set_preview_info(void)
{
    int hour;
    int min;
    int sec;
    int n;

    _la_mask_preview_info();

    if (((fileMask >> curFile) & 1) == 0) {
        return;
    }
    if (IosMcProductFile[filePort].file[curFile].stage == 0xFFFFFFFF) {
        return;
    }

    playTime(&previewInfo, &hour, &min, &sec);
    if (hour >= 100) {
        hour = 99;
        min = 59;
        sec = 59;
    }

    hour = ((hour / 10 + 9) % 10) * 10 + (hour % 10 + 9) % 10;
    min = ((min / 10 + 9) % 10) * 10 + (min % 10 + 9) % 10;
    sec = ((sec / 10 + 9) % 10) * 10 + (sec % 10 + 9) % 10;

    lt_mask_property(41 + hour / 10, 0);
    lt_mask_property(51 + hour % 10, 0);
    lt_mask_property(61 + min / 10, 0);
    lt_mask_property(71 + min % 10, 0);
    lt_mask_property(81 + sec / 10, 0);
    lt_mask_property(91 + sec % 10, 0);
    lt_mask_property(39, 0);
    lt_mask_property(40, 0);

    n = previewInfo.stage;
    if (n >= 3 && n < 56) {
        switch (previewInfo.sofa) {
        case 287:
            n = 39;
            break;
        case 289:
            n = 40;
            break;
        }
        lt_mask_property(n + 98, 0);
    }
}

inline int la_mc_preview_info(void)
{
    if (fileMask == 0) {
        if ((1 >> curFile) & 1) {
            return -1;
        }
    }
    _la_set_preview_info();
    return -1;
}

inline int la_mc_current_slot(void)
{
    lt_mask_property(140, curPort);
    lt_mask_property(141, curPort ^ 1);
    return -1;
}

int la_load_game_memory_card_check(int first)
{
    _la_mask_preview_info();
    lt_mask_property(140, 1);
    lt_mask_property(141, 1);
    switch (_la_set_current_port_2(&mc, first)) {
    case 0:
        if (mcLastResult == 0 || mcLastResult == -14) {
            return -1;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 19;
    case -1:
        if ((curPortInfo->flags.w >> 1) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 20;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 19;
    case 1:
        if ((curPortInfo->flags.w >> 6) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 14;
        }
        if ((curPortInfo->flags.w >> 5) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 16;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 20;
    }
    return -1;
}

int la_mc_load_current_slot_select(void)
{
    _la_mask_preview_info();
    if (PSH_POSITIVE(0)) {
        curPort = lt_current_property_item() - 151;
        lastPort = curPort;
        curPortInfo = &mcPortInfo[curPort];
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 16;
    }
    if (PSH_NEGATIVE(0)) {
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 9;
    }
    return -1;
}

static int loadCardChanged = 1; /* derived name */

static int loadFileChosen = 0; /* derived name */

int la_mc_load_file_select(int first, int item)
{
    int r;

    if (first) {
        fileMask = 0;
        lastPort = filePort = curPort;
        loadFileChosen = 0;
    }

    if (fileMask != 0) {
        _la_set_preview_info();
        lt_mask_property(38, 1);
        lt_mask_property(37, 1);
        lt_mask_property(160, 0);
        lt_mask_property(161, 0);
    } else {
        _la_mask_preview_info();
        lt_mask_property(38, 0);
        lt_mask_property(37, 0);
        lt_mask_property(160, 1);
        lt_mask_property(161, 1);
    }
    lt_set_item_select_func((int)la_mc_saved_file_select);

    if (PSH_NEGATIVE(0)) {
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 9;
    }

    if ((fileMask != 0 || loadFileChosen != 0) && PSH_POSITIVE(0)) {
        if (IosMcProductFile[filePort].file[item].stage != 0xFFFFFFFF) {
            selectFile = item;
            lastPort = filePort;
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 18;
        }
    }

    r = _la_set_current_port_lock_2(&mc, first);
    switch (r) {
    case -1:
        if (((curPortInfo->flags.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 19;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 20;
    case 1:
        if (((curPortInfo->flags.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 19;
        }
        if ((curPortInfo->flags.w & 0x22) == 2) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 20;
        }
        break;
    case 0:
    default:
        return -1;
    }

    if (fileMask != 0) {
        if (loadCardChanged == 0) {
            if (((curPortInfo->flags.w >> 6) & 1) != 0) {
                debug_StdPrintfDummy("1 to 2\n");
                lt_set_item_select_func(0);
                actionStarted = 0;
                return 14;
            }
        } else if (((curPortInfo->flags.w >> 6) & 1) == 0) {
            debug_StdPrintfDummy("2 to 1\n");
            loadCardChanged = (curPortInfo->flags.w >> 6) & 1;
        }
    } else {
        loadCardChanged = (curPortInfo->flags.w >> 6) & 1;
        fileMask = curPortInfo->fileMask;
        actionStarted = r;
        if ((curPortInfo->flags.w & 0xA) == 2) {
            loadFileChosen = r;
        }
    }
    return -1;
}

int la_load_confirm_no_memory_card(int first)
{
    if (first) {
        _la_mask_preview_info();
    }
    if (PSH_POSITIVE(0)) {
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 10;
    }
    switch (_la_set_current_port_lock_2(&mc, first)) {
    case 0:
        break;
    case -1:
        if ((curPortInfo->flags.w >> 1) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 17;
        }
        lock2Restart = 1;
        break;
    case 1:
        if ((curPortInfo->flags.w >> 1) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 17;
        }
        break;
    }
    return -1;
}

int la_load_confirm_no_data(int first)
{
    if (first) {
        _la_mask_preview_info();
    }
    if (PSH_POSITIVE(0)) {
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 10;
    }
    switch (_la_set_current_port_lock_2(&mc, first)) {
    case 0:
        break;
    case -1:
        if (((curPortInfo->flags.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 19;
        }
        lock2Restart = 1;
        break;
    case 1:
        if ((curPortInfo->flags.w >> 5) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 17;
        }
        break;
    }
    return -1;
}

int la_load_start_check(int first)
{
    switch (_la_set_current_port_lock_2(&mc, first)) {
    case 0:
        fileMask = 0x3FF;
        if (mcLastResult == 0 || mcLastResult == -14) {
            return -1;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 42;
    case -1:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 42;
    case 1:
        if (filePort != curPort) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 42;
        }
        if ((curPortInfo->flags.w & 3) != 3) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 19;
        }
        if ((curPortInfo->fileMask >> selectFile) & 1) {
            fileMask = 0x3FF;
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 22;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 20;
    }
    return -1;
}

/* the game flags the load carries across gflagInit, parked in keepFlags;
   inlined into la_load_processing */
static inline void gflagKeepState(void) /* derived name */
{
    unsigned int i;

    for (i = 0; i < 20; i++) {
        keepFlags[i] = gflagChk(keepFlagNo[i]);
    }
}

/* the other half of the pair */
static inline void gflagRestoreState(void) /* derived name */
{
    unsigned int i;

    for (i = 0; i < 20; i++) {
        if (keepFlags[i]) {
            gflagOn(keepFlagNo[i]);
        } else {
            gflagOff(keepFlagNo[i]);
        }
    }
}

static int loadStep = 0; /* derived name */

int la_load_processing(int first)
{
    int err;
    int hour;
    int min;
    int sec;

    debug_StdPrintfDummy("load processing\n");
    if (first) {
        loadStep = 0;
    }

    switch (loadStep) {
    case 0:
        strcpy(mc.path, "game.");
        mc.fileNo = selectFile;
        mc.port = curPort;
        mc.slot = 0;
        iosMcGetBlockSaveInfo(&mc);
        loadStep++;
        break;
    case 1:
    case 3:
        if (iosMcSync(&mc) != 0) {
            loadStep++;
        }
        break;
    case 2:
        loadStep++;
        break;
    case 9:
        gflagKeepState();
        gflagInit();
        gamesysMemoryLoad(gameSysMemoryFuncList, gameSysMainSaveBuff, 0);
        gflagRestoreState();
        systemStatus[3] = 1;
        systemStatus[4] = 1;
        /* falls through */
    case 6:
        debug_StdPrintfDummy("case %d\n", loadStep);
        err = _la_mcard_error_check(&mc);
        if (err > 0) {
            loadStep++;
            debug_StdPrintfDummy("McLoad phase:%d  %x\n", loadStep, err);
            debug_StdPrintfDummy("phase++\n");
            return -1;
        }
        debug_StdPrintfDummy("through\n");
        debug_StdPrintfDummy("chk:%d\n", err);
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 42;
    case 4:
        debug_StdPrintfDummy("case 4\n");
        if (((1 << mc.fileNo) & mc.mask) == 0) {
            loadStep = 20;
        } else {
            iosMcLoadProductBlock(&mc);
            loadStep++;
        }
        break;
    case 5:
    case 8:
        debug_StdPrintfDummy("case %d\n", loadStep);
        if (iosMcSync(&mc) != 0) {
            loadStep++;
        }
        break;
    case 7:
        debug_StdPrintfDummy("case %d\n", loadStep);
        debug_StdPrintfDummy("=== LoadGameBlock ===\n");
        iosMcLoadGameBlock(&mc, gameSysMainSaveBuff);
        loadStep++;
        break;
    case 10:
        debug_StdPrintfDummy("case 10\n");
        loadStep = 0;
        *(struct McPreview *)IosMcPreviewInfo =
            *(struct McPreview *)&IosMcProductFile[mc.port].file[mc.fileNo];
        playTime((struct McPreview *)IosMcPreviewInfo, &hour, &min, &sec);
        debug_StdPrintfDummy("stage no %d\n", gFlagGameClear);
        seEnvForceClose = 1;
        soundDataSegAllClose(0, 2);
        stgmgrForceSwitchWithFade(gFlagGameClear, 0.5f, 4.0f);
        ACTGame_SetActors_Debug(gFlagGameClear, 0);
        return -1;
    case 20:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 17;
    }
    return -1;
}

inline int la_general_mc_confirm(void)
{
    if (PSH_POSITIVE(0)) {
        return lt_current_property_item();
    }
    return -1;
}

/* opens layout voice number no; inlined into la_game_over_continue and into
   la_mc_confirm_save_file with different numbers */
static inline int openLayoutVoice(int no) /* derived name */
{
    if (layoutVoice != 0) {
        return 0;
    }
    soundDataOpen(&voiceOpenReq, 2, no, 1, 0);
    return 1;
}

static int saveVoice = 0; /* derived name */

int la_mc_confirm_save_file(int first, int item)
{
    lt_mask_property(140, 1);
    lt_mask_property(141, 1);
    if (first) {
        systemStatus[5] = 1;
        if (fightSoundProcessRequestStatus() == 0) {
            fightSoundProcessRequestPause();
            fightSoundStopped = 1;
        }
        saveVoice = openLayoutVoice(24);
        CheckPoint();
    }
    _la_mask_preview_info();
    if (saveVoice != 0) {
        layoutVoice = soundDataOpenSync(&voiceOpenReq);
        if (layoutVoice != (SqEntry *)0xFFFFFFFF) {
            saveVoice = 0;
            if (layoutVoice != 0) {
                AdpcmPlay(layoutVoice->stream);
            }
        }
        return -1;
    }
    switch (item) {
    case 183:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 26;
    case 184:
        systemStatus[5] = 0;
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 50;
    }
    return -1;
}

int la_save_game_memory_card_check(int first)
{
    _la_mask_preview_info();
    lt_mask_property(140, 1);
    lt_mask_property(141, 1);
    debug_StdPrintfDummy("save game check port %d\n", curPort);
    switch (_la_set_current_port_new(&mc, first)) {
    case 0:
        break;
    case -1:
        debug_StdPrintfDummy("fail\n");
        if ((curPortInfo->flags.w & 3) == 3) {
            if ((curPortInfo->flags.w >> 2) & 1) {
                lt_set_item_select_func(0);
                actionStarted = 0;
                return 15;
            }
            if (((curPortInfo->flags.w >> 4) & 1) == 0) {
                lt_set_item_select_func(0);
                actionStarted = 0;
                return 28;
            }
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 27;
    case 1:
        debug_StdPrintfDummy("sucess :%d %d %d\n", (curPortInfo->flags.w >> 5) & 1,
                             (curPortInfo->flags.w >> 4) & 1, (curPortInfo->flags.w & 0xA) == 2);
        if ((curPortInfo->flags.w >> 2) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 15;
        }
        if ((curPortInfo->flags.w & 0x30) != 0 || (curPortInfo->flags.w & 0xA) == 2) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 29;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 28;
    }
    return -1;
}

/* the sprite rectangle and colour the gif helpers take, the same pair
   layout_texture.c declares */
typedef struct { /* field names derived */
    int x;
    int y;
    int w;
    int h;
} SprRect; /* derived name */

typedef struct { /* field names derived */
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} SprCol; /* derived name */

/* GifPacket.h's entry points, which this TU does not include; gif_Sprite
   takes z as an unsigned int here, a long long in the header */
extern void gif_StartPacketPri(int pri);
extern void gif_SetZTest(int on);
extern void gif_SetZWrite(int on);
extern void gif_SetAlpha(long long alpha, long long mode, long long fix);
extern void gif_Sprite(SprRect *r, unsigned int z, SprRect *uv, SprCol *col, int prim);
extern void gif_EndPacket(void);
/* gif_Line's z words go as 32-bit unsigned ints here too (lui/ori) */
extern void gif_Line(int *v0, int *v1, unsigned int z0, unsigned int z1, SprCol *col, int prim);

static int barStep = 0; /* derived name */

static int barFrame = 0; /* derived name */

inline int la_mc_save_current_slot_select(void)
{
    if (PSH_POSITIVE(0)) {
        curPort = lt_current_property_item() - 151;
        lastPort = curPort;
        curPortInfo = &mcPortInfo[curPort];
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 29;
    }
    if (PSH_NEGATIVE(0)) {
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 25;
    }
    return -1;
}

static void progressive_bar(void)
{
    int n;
    sceVu0IVECTOR p0;
    sceVu0IVECTOR p1;

    if (fbKeep != 0) {
        return;
    }
    if (systemStatus[7] <= 0) {
        return;
    }
    n = systemStatus[8];
    gif_StartPacketPri(12);
    gif_SetZWrite(0);
    gif_SetZTest(0);
    gif_SetAlpha(1, 2, 64);
    {
        SprRect frame = {80, 6, -160, 6};
        SprCol frameCol = {128, 128, 128, 32};

        gif_Sprite(&frame, 0xFFFFFFFF, 0, &frameCol, 1);
    }
    {
        SprRect back = {78, 7, -156, 4};
        SprCol backCol = {0, 0, 0, 32};

        gif_Sprite(&back, 0xFFFFFFFF, 0, &backCol, 1);
    }
    {
        int w = (float)barStep / (float)barTotal * -160.0f;
        SprRect bar = {-80 - w, 8, w, 2};
        SprCol barCol = {64, 255, 64, 32};

        gif_Sprite(&bar, 0xFFFFFFFF, 0, &barCol, 1);
    }
    {
        SprCol lineCol = {128, 128, 128, 32};

        CopyIVector(p0, barLine[barFrame % 4][0]);
        CopyIVector(p1, barLine[barFrame % 4][1]);
        p0[0] += 252;
        p1[0] += 252;
        p0[1] += 17;
        p1[1] += 17;
        gif_Line(p0, p1, 0xFFFFFFFF, 0xFFFFFFFF, &lineCol, 1);
    }
    gif_SetZTest(1);
    gif_SetZWrite(1);
    gif_SetAlpha(1, 4, 128);
    gif_EndPacket();
    if (n != barLastStep) {
        barLastStep = n;
        barFrame++;
    }
}

static int saveCardChanged = 1; /* derived name */

int la_mc_save_file_select(int first, int item)
{
    int r;

    if (first) {
        fileMask = 0;
        lastPort = filePort = curPort;
        saveSelectReady = 0;
        barTotal = 2;
        barStep = 0;
    }

    if (actionStarted != 0) {
        _la_set_preview_info();
        lt_mask_property(38, 1);
        lt_mask_property(37, 1);
        lt_mask_property(208, 0);
        lt_mask_property(209, 0);
    } else {
        lt_mask_property(38, 0);
        lt_mask_property(37, 0);
        lt_mask_property(208, 1);
        lt_mask_property(209, 1);
    }

    if (actionStarted != 0) {
        if (PSH_NEGATIVE(0)) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 25;
        }
    }

    if ((fileMask != 0 || saveSelectReady != 0) && PSH_POSITIVE(0)) {
        selectFile = item;
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 30;
    }

    r = _la_set_current_port_lock_2(&mc, first);
    switch (r) {
    case -1:
        if (((curPortInfo->flags.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 27;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 28;
    case 1:
        if (((mcPortInfo[filePort].flags.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 25;
        }
        if (fileMask != 0) {
            if (saveCardChanged == 0) {
                if (((curPortInfo->flags.w >> 2) & 1) != 0) {
                    lt_set_item_select_func(0);
                    actionStarted = 0;
                    return 15;
                }
            } else if (((curPortInfo->flags.w >> 2) & 1) == 0) {
                saveCardChanged = 0;
            }
        } else {
            saveCardChanged = (curPortInfo->flags.w >> 2) & 1;
            if ((curPortInfo->flags.w >> 3) & 1) {
                debug_StdPrintfDummy("format 2\n");
                saveSelectReady = r;
            } else if ((curPortInfo->flags.w & 0xA) == 2) {
                debug_StdPrintfDummy("unformat 2\n");
                if (filePort == curPort) {
                    actionStarted = r;
                }
                saveSelectReady = r;
                return -1;
            }
        }
        if (filePort == curPort) {
            fileMask = curPortInfo->fileMask;
            actionStarted = 1;
        }
        break;
    case 0:
    default:
        return -1;
    }
    return -1;
}

inline int la_save_confirm_no_memory_card(int first)
{
    if (PSH_POSITIVE(0)) {
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 25;
    }
    switch (_la_set_current_port_lock_2(&mc, first)) {
    case 0:
        break;
    case -1:
        if ((curPortInfo->flags.w >> 1) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 26;
        }
        lock2Restart = 1;
        break;
    case 1:
        if ((curPortInfo->flags.w >> 1) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 26;
        }
        break;
    }
    return -1;
}

inline int la_save_confirm_no_free_area(int first)
{
    if (PSH_POSITIVE(0)) {
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 25;
    }
    switch (_la_set_current_port_lock_2(&mc, first)) {
    case 0:
        break;
    case -1:
        if (((curPortInfo->flags.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 27;
        }
        lock2Restart = 1;
        break;
    case 1:
        if ((curPortInfo->flags.w >> 4) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 26;
        }
        break;
    }
    return -1;
}

int la_save_start_check(int first)
{
    switch (_la_set_current_port_lock_2(&mc, first)) {
    case 0:
        break;
    case -1:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 26;
    case 1:
        if (filePort != curPort) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 40;
        }
        if ((curPortInfo->flags.w & 0xA) == 2) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 32;
        }
        if ((curPortInfo->fileMask >> selectFile) & 1) {
            if (IosMcProductFile[filePort].file[selectFile].stage != 0xFFFFFFFF) {
                lt_set_item_select_func(0);
                actionStarted = 0;
                return 31;
            }
            if (curPortInfo->fileMask != 0) {
                debug_StdPrintfDummy("already exist save data\n");
                lt_set_item_select_func(0);
                actionStarted = 0;
                return 34;
            }
        }
        debug_StdPrintfDummy("new save. system data making..\n");
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 35;
    }
    return -1;
}

int la_save_confirm_overwrite(int first, int item)
{
    if (first) {
        filePort = curPort;
    }
    fileMask = 0x3FF;
    _la_set_preview_info();
    switch (item) {
    case 183:
    case 187:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 34;
    case 184:
    case 188:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 29;
    }
    switch (_la_set_current_port_lock_2(&mc, first)) {
    case 0:
        break;
    case -1:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 27;
    case 1:
        if (saveCardChanged == 0) {
            if (((curPortInfo->flags.w >> 2) & 1) == 0) {
                break;
            }
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 15;
        }
        if ((curPortInfo->flags.w >> 2) & 1) {
            break;
        }
        saveCardChanged = 0;
        if (filePort == curPort) {
            break;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 26;
    }
    return -1;
}

int la_format_confirm(int first, int item)
{
    if (first) {
        filePort = curPort;
    }
    switch (item) {
    case 183:
    case 187:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 33;
    case 184:
    case 188:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 29;
    }
    switch (_la_set_current_port_lock_2(&mc, first)) {
    case 0:
        break;
    case -1:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 27;
    case 1:
        if (saveCardChanged == 0) {
            if (((curPortInfo->flags.w >> 2) & 1) == 0) {
                break;
            }
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 15;
        }
        if ((curPortInfo->flags.w >> 2) & 1) {
            break;
        }
        saveCardChanged = 0;
        if (filePort == curPort) {
            break;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 26;
    }
    return -1;
}

static int formatStep = 0; /* derived name */

inline int la_format_processing(int first)
{
    if (first) {
        formatStep = 0;
    }
    switch (formatStep) {
    case 0:
        mc.port = curPort;
        mc.slot = 0;
        iosMcFormat(&mc);
        formatStep++;
        break;
    case 1:
    case 3:
        if (iosMcSync(&mc) == 0) {
            break;
        }
        formatStep++;
        break;
    case 2:
        if (_la_mcard_error_check(&mc) > 0) {
            formatStep++;
            break;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 41;
    case 4:
        formatStep++;
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 35;
    }
    return -1;
}

static int systemSaveStep = 0; /* derived name */

int la_system_save_processing(int first)
{
    int err;
    int i;
    int hour;
    int min;
    int sec;

    curPortInfo = &mcPortInfo[mc.port];
    if (first) {
        systemSaveStep = 0;
        systemSaveRetry = 0;
        barTotal = 14;
    }

    progressive_bar();

    switch (systemSaveStep) {
    case 0:
        strcpy(mc.path, "game.");
        mc.fileNo = systemSaveRetry;
        mc.port = curPort;
        mc.slot = 0;
        iosMcGetBlockSaveInfo(&mc);
        systemSaveStep++;
        curPortInfo->flags.w = (int)curPortInfo->flags.w & ~0x80;
        barStep++;
        break;
    case 2:
        iosMcSaveIconBlock(&mc);
        systemSaveStep++;
        break;
    case 6:
    case 9:
        err = _la_mcard_error_check(&mc);
        if (err > 0) {
            systemSaveStep++;
            debug_StdPrintfDummy("McSave phase:%d  %x\n", systemSaveStep, err);
            return -1;
        }
        curPortInfo->flags.w |= 0x80;
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 40;
    case 4:
        for (i = 0; i < 10; i++) {
            IosMcProductFile[mc.port].file[i].stage = 0xFFFFFFFF;
        }
        playTime((struct McPreview *)IosMcPreviewInfo, &hour, &min, &sec);
        iosMcSaveProductBlock(&mc);
        systemSaveStep++;
        barStep++;
        break;
    case 1:
    case 3:
    case 5:
    case 8:
        if (iosMcSync(&mc) != 0) {
            systemSaveStep++;
        }
        break;
    case 7:
        iosMcSaveGameBlock(&mc, gameSysMainSaveBuff);
        systemSaveStep++;
        barStep++;
        break;
    case 10:
        systemSaveStep = 7;
        systemSaveRetry++;
        mc.fileNo = systemSaveRetry;
        if (systemSaveRetry >= 10) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 34;
        }
        break;
    }
    return -1;
}

static int saveStep = 0; /* derived name */

int la_save_processing(int first)
{
    int err;
    int hour;
    int min;
    int sec;

    curPortInfo = &mcPortInfo[mc.port];
    if (first) {
        fileMask = 0;
        saveStep = 0;
    }

    progressive_bar();

    switch (saveStep) {
    case 0:
        strcpy(mc.path, "game.");
        mc.fileNo = selectFile;
        mc.port = curPort;
        mc.slot = 0;
        iosMcGetBlockSaveInfo(&mc);
        saveStep++;
        curPortInfo->flags.w = (int)curPortInfo->flags.w & ~0x80;
        break;
    case 1:
        if (iosMcSync(&mc) != 0) {
            saveStep = 4;
        }
        break;
    case 2:
        iosMcSaveIconBlock(&mc);
        saveStep++;
        break;
    case 6:
    case 9:
        err = _la_mcard_error_check(&mc);
        if (err > 0) {
            saveStep++;
            debug_StdPrintfDummy("McSave phase:%d  %x\n", saveStep, err);
            return -1;
        }
        curPortInfo->flags.w |= 0x80;
        debug_StdPrintfDummy("save error? %d\n", saveStep);
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 40;
    case 4:
        IosMcPreviewInfo[0] = stage_no;
        IosMcPreviewInfo[2] = GetSaveSofaLayoutID();
        *(struct McPreview *)&IosMcProductFile[mc.port].file[mc.fileNo] =
            *(struct McPreview *)IosMcPreviewInfo;
        playTime((struct McPreview *)IosMcPreviewInfo, &hour, &min, &sec);
        iosMcSaveProductBlock(&mc);
        saveStep++;
        break;
    case 3:
    case 5:
    case 8:
        if (iosMcSync(&mc) != 0) {
            saveStep++;
            barStep++;
        }
        break;
    case 7:
        CheckPoint();
        iosMcSaveGameBlock(&mc, gameSysMainSaveBuff);
        saveStep++;
        break;
    case 10:
        saveStep = 0;
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 37;
    }
    return -1;
}

inline int la_save_confirm_complete(int first, int item)
{
    if (first) {
        previewInfo = *(struct McPreview *)IosMcPreviewInfo;
        fileMask = 0x3FF;
        _la_set_preview_info();
        debug_StdPrintfDummy("save complete %d %d\n", fileMask, curFile);
    }
    if (item != -1) {
        debug_StdPrintfDummy("%d %d %d\n", 233, 234, item);
    }
    switch (item) {
    case 233:
        systemStatus[5] = 0;
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 50;
    case 234:
        nextStage = 1;
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 59;
    }
    return -1;
}

/* main.c's demo-only switch to stage 102 (systemStatus[5] = 1, the movie's
   return stage 92), not yet named */
extern void func_00102790(void);

inline int la_end_confirm(void)
{
    if (PSH_POSITIVE(0)) {
        debug_StdPrintfDummy("%d\n", lt_current_property_item());
        switch (lt_current_property_item()) {
        case 239:
        case 373:
            gflagInit();
            func_00102790();
        case 240:
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 37;
        }
    }
    return -1;
}

static int deleteStep = 0; /* derived name */

inline int la_save_confirm_yesno(void)
{
    if (PSH_NEGATIVE(0)) {
        return lt_current_property_item();
    }
    return -1;
}

inline int la_save_confirm_fail(void)
{
    return -1;
}

inline int la_format_confirm_fail(void)
{
    return -1;
}

inline int la_delete_start_check(int first)
{
    switch (_la_set_current_port_2(&mc, first)) {
    case 0:
        break;
    case -1:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 26;
    case 1:
        if ((curPortInfo->fileMask >> selectFile) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 45;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 29;
    }
    return -1;
}

inline int la_delete_confirm(int first, int item)
{
    switch (item) {
    case 183:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 46;
    case 184:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 26;
    }
    return -1;
}

int la_delete_processing(int first)
{
    if (first) {
        mc.fileNo = selectFile;
        deleteStep = 2;
    }
    switch (deleteStep) {
    case 2:
        strcpy(mc.path, mc.dir[mc.fileNo].EntryName);
        iosMcDelete(&mc);
        deleteStep++;
        break;
    case 3:
        if (iosMcSync(&mc) == 0) {
            break;
        }
        deleteStep++;
        break;
    case 4:
        if (_la_mcard_error_check(&mc) == 0) {
            break;
        }
        deleteStep++;
        break;
    case 5:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 47;
    }
    return -1;
}

inline int la_delete_confirm_complete(void)
{
    if (PSH_NEGATIVE(0)) {
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 26;
    }
    return -1;
}

inline int la_delete_confirm_fail(void)
{
    return -1;
}

inline int la_game_loading(int first)
{
    if (first != 0) {
        systemStatus[6] = 1;
    }
    return -1;
}

/* inlined into la_game_loop and into la_game_over_continue */
static inline void releaseGameLoopCursor(void) /* derived name */
{
    if (layoutVoice != 0 && layoutVoice->stream != 0) {
        layoutVoice->stream->fadeStep = 0x100;
    }
    layoutVoice = 0;
}

inline int la_game_loop(int first)
{
    IosMcPreviewInfo[1]++;
    if (first) {
        if (fightSoundStopped != 0) {
            fightSoundProcessRequestStart();
            fightSoundStopped = 0;
        }
        releaseGameLoopCursor();
        systemStatus[2] = 1;
        systemStatus[5] = 0;
        iosPadEnable();
        isysGObjActiveLink(0, 1);
        layoutActPushStartNew = 0;
    }
    if ((pad[0].flags & 0x800) || layoutActPushStartNew != 0) {
        if (enable_game_pause == 0) {
            return -1;
        }
        systemStatus[5] = 1;
        layoutActPushStartNew = 0;
        adpcmPauseRequest(1);
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 53;
    }
    return -1;
}

static int gameOverVoice = 0; /* derived name */

inline int la_game_demo(int first)
{
    if (first) {
        iosPadDisable();
    }
    if ((pad[0].flags & 0x800) && gflagChk(339)) {
        debug_StdPrintfDummy("push start\n");
        gflagOff(339);
        title_demo_mode ^= 1;
        nextStage = stage_after_skipping_demo;
        stgmgrForceSwitchWithFade(nextStage, 8.0f, 4.0f);
        if (stage_after_skipping_demo == 0xFFFFFFFF) {
            stage_after_skipping_demo = 1;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 59;
    }
    return -1;
}

inline int la_game_demo_pause(int first)
{
    if (first) {
        systemStatus[5] = 1;
    }
    if ((pad[0].flags & 0x800) == 0) {
        return -1;
    }
    lt_set_item_select_func(0);
    actionStarted = 0;
    return 51;
}

inline int la_game_pause(int first)
{
    if (first) {
        systemStatus[5] = 1;
    }
    if ((pad[0].flags & 0x800) || ((pad[0].flags & 0x40) && lt_current_property_item() == 264)) {
        adpcmPauseRequest(0);
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 50;
    }
    return -1;
}

int la_game_over_continue(int first)
{
    if (first) {
        iosPadEnable();
        systemStatus[5] = 1;
        soundSePlayModeStop(1);
        soundSePlayModeStop(0);
        gameOverVoice = openLayoutVoice(48);
    }
    if (gameOverVoice != 0) {
        layoutVoice = soundDataOpenSync(&voiceOpenReq);
        if (layoutVoice != (SqEntry *)0xFFFFFFFF) {
            gameOverVoice = 0;
            if (layoutVoice != 0) {
                AdpcmPlay(layoutVoice->stream);
                return -1;
            }
        }
    } else {
        switch (lt_current_property_item()) {
        case 378:
            if (PSH_POSITIVE(0)) {
                systemStatus[4] = 1;
                nextStage = gFlagGameClear;
                releaseGameLoopCursor();
                lt_set_item_select_func(0);
                actionStarted = 0;
                return 59;
            }
            break;
        case 379:
            if (PSH_POSITIVE(0)) {
                gflagInit();
                func_00102790();
            }
            break;
        }
    }
    return -1;
}

inline int la_switching_stage(void)
{
    if (fightSoundPlayChk() == 0) {
        stgmgrForceSwitchWithFade(nextStage, 0.4f, 4.0f);
    }
    return -1;
}

/* the key-config property sweep, inlined into la_key_config twice */
static inline void keyconfigMaskAll(void) /* derived name */
{
    int i;

    for (i = 0; i < 48; i++) {
        lt_mask_property(i + 291, 1);
        lt_default_mask_property(i + 291, 1);
    }
}

/* the lowest set bit of v, -1 for none */
static inline int keyBitIndex(int v) /* derived name */
{
    int i;

    for (i = 0; i < 16; i++) {
        if ((v >> i) & 1) {
            return i;
        }
    }
    return -1;
}

/* the index of pad code v in keyConfigCode, -1 for none */
static inline int keyCodeIndex(int v) /* derived name */
{
    int i;

    for (i = 0; i < 8; i++) {
        if (v == keyConfigCode[i]) {
            return i;
        }
    }
    return -1;
}

/* the slot assigned pad code v, -1 for none */
static inline int keyAssignIndex(int v) /* derived name */
{
    int i;

    for (i = 0; i < 8; i++) {
        if (v == keyConfigCode[keyConfigSlot[i]]) {
            return i;
        }
    }
    return -1;
}

static int keyConfigMask = 0xFF; /* derived name */

int la_key_config(int first)
{
    int i;
    int sel;
    int m;
    int k;
    int n;

    sel = lt_current_property_item() - 285;
    if (first) {
        for (i = 0; i < 16; i++) {
            if ((keyConfigMask >> i) & 1) {
                keyConfigSlot[keyCodeIndex(iosPadConfCustom.bit[i])] = keyCodeIndex(1 << i);
            }
        }
    }
    if (sel >= 0 && sel < 6) {
        m = pad[0].flags & keyConfigMask;
        if (m != 0 && m == pad[0].flags) {
            k = keyCodeIndex(m);
            if (k != -1) {
                n = keyAssignIndex(m);
                if (n != -1) {
                    keyConfigSlot[n] = keyConfigSlot[sel];
                }
                keyConfigSlot[sel] = k;
            }
        }
    }
    keyconfigMaskAll();
    for (i = 0; i < 6; i++) {
        lt_mask_property(i * 8 + 291 + keyConfigSlot[i], 0);
    }
    if (PSH_POSITIVE(0)) {
        if (lt_current_property_item() == 340) {
            for (i = 7; i >= 0; i--) {
                keyConfigSlot[i] = i;
            }
        }
        if (lt_current_property_item() == 339) {
            for (i = 0; i < 16; i++) {
                iosPadConfCustom.bit[i] = 0;
            }
            for (i = 0; i < 8; i++) {
                iosPadConfCustom.bit[keyBitIndex(keyConfigCode[keyConfigSlot[i]])] =
                    keyConfigCode[i];
            }
            keyconfigMaskAll();
            for (i = 0; i < 6; i++) {
                lt_default_mask_property(i * 8 + 291 + keyConfigSlot[i], 0);
                lt_mask_property(i * 8 + 291 + keyConfigSlot[i], 0);
            }
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 54;
        }
    }
    if (pad[0].flags & 0x800) {
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 50;
    }
    return -1;
}

int la_game_option(void)
{
    int mode;

    mode = soundOutputModeGet();
    if (PSH_POSITIVE(0)) {
        switch (lt_current_property_item()) {
        case 269:
            if (mode == 0) {
                mode = 1;
            } else {
                mode = 0;
            }
            soundOutputModeSet(mode);
            break;
        case 274:
            iosPadActRequestEnable ^= 1;
            break;
        }
    }
    if (mode == 0) {
        lt_default_mask_property(272, 0);
        lt_default_mask_property(273, 1);
    } else {
        lt_default_mask_property(272, 1);
        lt_default_mask_property(273, 0);
    }
    if (iosPadActRequestEnable != 0) {
        lt_default_mask_property(277, 0);
        lt_default_mask_property(278, 1);
    } else {
        lt_default_mask_property(277, 1);
        lt_default_mask_property(278, 0);
    }
    return -1;
}

/* inlined once, into la_adjust_screen */
static inline void clearAdjustScreenMarks(void) /* derived name */
{
    int i;

    for (i = 0; i < 15; i++) {
        lt_default_mask_property(i + 344, 1);
    }
}

int la_adjust_screen(void)
{
    if (PSH_LEFT(0)) {
        if (systemStatus[11] > 0) {
            systemStatus[11]--;
        }
    } else if (PSH_RIGHT(0)) {
        if (systemStatus[11] < 14) {
            systemStatus[11]++;
        }
    }
    if (PSH_NEGATIVE(0)) {
        systemStatus[11] = 7;
    }
    clearAdjustScreenMarks();
    lt_default_mask_property(systemStatus[11] + 344, 0);
    if (PSH_POSITIVE(0)) {
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 54;
    }
    if (pad[0].flags & 0x800) {
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 50;
    }
    return -1;
}

unsigned int stage_after_skipping_demo = 0;

int layoutActPushStartNew = 0;
