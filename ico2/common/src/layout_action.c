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

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
#include "StageAnimation.h"
#include "Basic.h"
#endif

#include <stdlib.h>
#include "boyact.h"
#include "act-game.h"
#include "StageManager.h"
#include "s_init.h"
#include "typedef.h"
#include "main.h"

#ifdef VERSION_JUN26
#include "frameDependSequence.h"
#include "matrixDrive.h"
#endif

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

/* the save preview the file select shows, the five words of typedef.h's
   McFileInfo */
struct McPreview { /* field names derived */
    int stage;     /* 0x00 */
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    int playTime; /* 0x04, in frames */
    int sofa;     /* 0x08 */
    int word0C;   /* 0x0C, no C reader */
#else
    int cleared;  /* 0x04 */
    int playTime; /* 0x08, in frames */
    int sofa;     /* 0x0C */
    int word10;   /* 0x10, no C reader */
#endif
}; /* derived name */

/* .sbss, thirteen words: the port-0 lock state _la_set_current_port_2 records and the one
   _la_set_current_port_lock_2 records, the lock results for port 0 and port 1
   of _la_set_current_port_new, the icoMisc lock saved by the logo, the title
   continue and the title new game actions, the progress bar's last step, the
   save select's ready flag, the system save's retry count, the last card
   result, the load (1) or save (0) mode of the file select, and the progress
   bar's total. */
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

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
static int mcLoadMode; /* derived name */
#endif

static int barTotal; /* derived name */

/* .bss: the two card ports' records, the preview
   record of the save being confirmed, the open request of the layout voice
   and the twenty game flags kept across a load. */
static McPortInfo mcPortInfo[2]; /* derived name */

static struct McPreview previewInfo; /* derived name */

static AdpcmOpenReq voiceOpenReq; /* derived name */

static signed char keepFlags[20]; /* derived name */

#ifdef VERSION_JUN26
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
#else
void POSITIVE_SE(void)
{
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    soundSeDefPlay(400, 0xFFFFFFFE, 0, 0);
#else
    soundSeDefPlay(412, 0xFFFFFFFE, 0, 0);
#endif
}
#endif

#ifdef VERSION_JUN26
inline int PSH_NEGATIVE(int idx) /* derived name */
{
    if (pad[idx].flags & 0x10) {
        ExecuteSEPackage(0, 92);
        return 1;
    }
    return 0;
}
#else
void NEGATIVE_SE()
{
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    soundSeDefPlay(401, 0xFFFFFFFE, 0, 0);
#else
    soundSeDefPlay(413, 0xFFFFFFFE, 0, 0);
#endif
}
#endif

#ifdef VERSION_JUN26
inline int PSH_LEFT(int idx) /* derived name */
{
    if (pad[idx].flags & 0x8000) {
        ExecuteSEPackage(0, 90);
        return 1;
    }
    return 0;
}
#else
void CUR_SE(void)
{
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    soundSeDefPlay(399, 0xFFFFFFFE, 0, 0);
#else
    soundSeDefPlay(411, 0xFFFFFFFE, 0, 0);
#endif
}
#endif

#ifdef VERSION_JUN26
inline int PSH_RIGHT(int idx) /* derived name */
{
    if (pad[idx].flags & 0x2000) {
        ExecuteSEPackage(0, 90);
        return 1;
    }
    return 0;
}
#else
inline int PSH_POSITIVE_OR_NEGATIVE(int idx)
{
    int v = pad[idx].flags;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if ((v & 0x20) != 0)
        goto one;
    if ((v & 0x40) == 0)
        goto zero;
#else
    if ((v & 0x40) != 0)
        goto one;
    if ((v & 0x10) == 0)
        goto zero;
#endif
one:
    return 1;
zero:
    return 0;
}
#endif

void la_TESTFUNCTION(void)
{
    debug_StdPrintfDummy("sync end\n");
}

#ifdef VERSION_JUN26
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
#else
/* .data: the game-flag ids the load carries across gflagInit.  The list
   holds five ids and the key-config tables follow it; the keep/restore loops
   below walk twenty words. */
#ifdef VERSION_NTSC
static int keepFlagNo[5] = {355, 351, 350, 352, 349}; /* derived name */
#else
#ifdef VERSION_AUG6
static int keepFlagNo[5] = {354, 350, 349, 351, 348}; /* derived name */
#else
static int keepFlagNo[5] = {388, 384, 383, 385, 382}; /* derived name */
#endif
#endif
#endif

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

/* .sdata: these ten statics and the three globals after them, then each
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

#ifndef VERSION_JUN26
int startStagePauseDisableTimer = 0;
#endif

int layout_boot_flag = 0;

int enable_game_pause = 1;

#ifdef VERSION_JUN26
/* the current port and port 0's card flags, printed; nothing calls it */
void _la_print_port_flags(void) /* derived name */
{
    debug_StdPrintfDummy("current:%d ec:%d  p2:%d  fo:%d  fr:%d  ed:%d\n", curPort,
                         mcPortInfo[0].flags.bit.card, mcPortInfo[0].flags.bit.ps2Card,
                         mcPortInfo[0].flags.bit.formatted, mcPortInfo[0].flags.bit.hasSpace,
                         mcPortInfo[0].flags.bit.hasSave);
}
#endif

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
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
        (IosMcProductFile + p->port)->serial = 0;
        (IosMcProductFile + p->port)->fileNo = 0;
#endif
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
#ifndef VERSION_JUN26
        }
        switch (p->result) {
        case -16:
        case -15:
        case -4:
            p->result = -14;
            step = 99;
            r = 0;
            break;
#endif
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
#ifdef VERSION_JUN26
        if (p->free >= 400) {
#else
        if (p->free >= 360) {
#endif
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
#ifdef VERSION_JUN26
        if (p->dirCount == 10) {
            curPortInfo->flags.w |= 0x20;
            curPortInfo->fileMask = p->mask;
#else
        for (i = 0; i < 10; i++) {
            if (IosMcProductFile[p->port].file[i].stage != 0xFFFFFFFF) {
                break;
            }
        }
        if (i < 10) {
            if (p->dirCount == 10) {
                curPortInfo->flags.w |= 0x20;
                curPortInfo->fileMask = p->mask;
            }
#endif
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
#ifdef VERSION_JUN26
        v = ((mcPortInfo[0].flags.w >> 1) & 1) && ((mcPortInfo[1].flags.w >> 1) & 1);
        mcPortInfo[0].flags.bit.bothPs2 = mcPortInfo[1].flags.bit.bothPs2 = v;
        v = ((mcPortInfo[0].flags.w >> 5) & 1) && ((mcPortInfo[1].flags.w >> 5) & 1);
#else
        if (((mcPortInfo[0].flags.w >> 1) & 1) && ((mcPortInfo[1].flags.w >> 1) & 1))
            v = 1;
        else
            v = 0;
        mcPortInfo[0].flags.bit.bothPs2 = mcPortInfo[1].flags.bit.bothPs2 = v;
        if (((mcPortInfo[0].flags.w >> 5) & 1) && ((mcPortInfo[1].flags.w >> 5) & 1))
            v = 1;
        else
            v = 0;
#endif
        mcPortInfo[0].flags.bit.bothSave = mcPortInfo[1].flags.bit.bothSave = v;
        if (port0LockResult == 1) {
            curPort = 0;
            r = 1;
        } else if (port1LockResult == 1) {
            curPort = 1;
            r = 1;
        } else {
#ifdef VERSION_JUN26
            if ((mcPortInfo[0].flags.w & 1) == 0 && mcPortInfo[1].flags.bit.card == 1) {
#else
            if (((mcPortInfo[0].flags.w >> 1) & 1) == 0 && mcPortInfo[1].flags.bit.ps2Card == 1) {
#endif
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

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
inline int la_boot_memory_card_check(void)
{
    if (kanbanBootEnd == 0) {
        return -1;
    }
    systemStatus[11] = 7;
    layout_boot_flag = 1;
    lt_set_item_select_func(0);
    actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    return 0x34;
#else
    return 0x37;
#endif
}
#endif

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

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
inline void keyconfig_reset(void)
{
    KeyConf def = {{0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x0200,
                    0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000}};

    *(KeyConf *)iosPadConfCustom.bit = def;
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
#endif

#ifdef VERSION_JUN26
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
#endif

inline int la_boot_confirm_memory_card(void)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if (pad[0].flags & 0x20) {
#else
#ifdef VERSION_JUN26
    if (PSH_POSITIVE(0)) {
#else
    if (pad[0].flags & 0x40) {
#endif
#endif
        return lt_link_layout(0);
    }
    return -1;
}

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
int la_vibe_select(void)
{
    if (lt_fade_status() == 2 && (pad[0].flags & 0x840)) {
        soundSeDefPlay(403, 0xFFFFFFFF, 0, 0);
        switch (lt_current_property_item()) {
        case 8:
            iosPadActRequestEnable = 1;
            break;
        case 9:
            iosPadActRequestEnable = 0;
            break;
        }
        if (titleAdpcm != 0) {
            titleAdpcm->stream->fadeStep = 0x80;
        }
        titleAdpcm = 0;
        gflagInit();
        keyconfig_reset();
        systemStatus[4] = 0;
#ifdef VERSION_AUG6
        gflagOn(348);
#else
        gflagOn(349);
#endif
        return -1;
    }
    if (lt_fade_status() != 2) {
        return -1;
    }
    if ((pad[0].flags & 0x10) == 0) {
        return -1;
    }
    NEGATIVE_SE();
    lt_set_item_select_func(0);
    actionStarted = 0;
    return 9;
}

int title_demo_mode = 0;

static int continueDecided = 0; /* derived name */
#else
#ifdef VERSION_JUN26
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
#else
inline void keyconfig_reset(void)
{
    KeyConf def = {{0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x0200,
                    0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000}};

    *(KeyConf *)iosPadConfCustom.bit = def;
}

int la_vibe_select(void)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if (lt_fade_status() == 2 && (pad[0].flags & 0x820)) {
#else
    if (lt_fade_status() == 2 && (pad[0].flags & 0x840)) {
#endif
        soundSeDefPlay(415, 0xFFFFFFFF, 0, 0);
        switch (lt_current_property_item()) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        case 8:
#else
        case 14:
#endif
#else
        case 44:
#endif
            iosPadActRequestEnable = 1;
            break;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        case 9:
#else
        case 15:
#endif
#else
        case 45:
#endif
            iosPadActRequestEnable = 0;
            break;
        }
        if (titleAdpcm != 0) {
            titleAdpcm->stream->fadeStep = 0x80;
        }
        titleAdpcm = 0;
        gflagInit();
        keyconfig_reset();
        systemStatus[4] = 0;
        gflagOn(382);
        return -1;
    }
    if (lt_fade_status() != 2) {
        return -1;
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if ((pad[0].flags & 0x40) == 0) {
#else
    if ((pad[0].flags & 0x10) == 0) {
#endif
        return -1;
    }
    NEGATIVE_SE();
    lt_set_item_select_func(0);
    actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    return 0x9;
#else
    return 0xC;
#endif
}
#endif
#endif

inline int la_scei_logo(int first)
{
    if (first) {
        stgmgrNextStagePreLoadForceStageSet(0);
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        logoIcoMiscLock = GlobalTimer;
#else
        logoIcoMiscLock = lock_execIcoMisc;
#endif
        systemStatus[5] = 1;
        iosPadEnable();
        isysGObjActiveLink(0, 0);
#ifdef VERSION_NTSC
        gflagOff(353);
#else
#ifdef VERSION_AUG6
        gflagOff(352);
#else
#ifdef VERSION_JUN26
        gflagOff(337);
#else
        gflagOff(386);
#endif
#endif
#endif
        if (layout_boot_flag == 0) {
            layout_boot_flag = 1;
        }
    }
    return -1;
}

#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
inline int la_title_demo(void)
{
    return -1;
}

int la_title_continue_or_new(int first)
{
    if (first) {
#ifndef VERSION_JUN26
        opTitleLogoMode = 1;
#endif
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        continueIcoMiscLock = GlobalTimer;
#else
        continueIcoMiscLock = lock_execIcoMisc;
#endif
        iosPadEnable();
        isysGObjActiveLink(0, 1);
        systemStatus[5] = 0;
#ifdef VERSION_JUN26
        gflagOff(333);
        if (gflagChk(336) == 0) {
            gflagOn(336);
        }
        continueDecided = 0;
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        gflagOff(348);
        if (gflagChk(351) == 0) {
            gflagOn(351);
#else
        gflagOff(349);
        if (gflagChk(352) == 0) {
            gflagOn(352);
#endif
        }
        continueDecided = 0;
        lt_continue_selected = 0;
#endif
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
#ifndef VERSION_JUN26
        lt_continue_selected = 1;
#endif
        soundSeDefPlay(402, 0xFFFFFFFF, 0, 0);
        switch (lt_current_property_item()) {
        case 14:
#ifndef VERSION_JUN26
            opTitleLogoMode = 2;
#endif
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 17;
        case 15:
#ifndef VERSION_JUN26
            opTitleLogoMode = 2;
#endif
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
#ifndef VERSION_JUN26
        opTitleLogoMode = 1;
#endif
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        newGameIcoMiscLock = GlobalTimer;
#else
        newGameIcoMiscLock = lock_execIcoMisc;
#endif
        iosPadEnable();
        isysGObjActiveLink(0, 1);
        systemStatus[5] = 0;
#ifdef VERSION_JUN26
        gflagOff(333);
        if (gflagChk(336) == 0) {
            gflagOn(336);
        }
        newGameDecided = 0;
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        gflagOff(348);
        if (gflagChk(351) == 0) {
            gflagOn(351);
#else
        gflagOff(349);
        if (gflagChk(352) == 0) {
            gflagOn(352);
#endif
        }
        newGameDecided = 0;
        lt_continue_selected = 0;
#endif
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
#ifndef VERSION_JUN26
        lt_continue_selected = 1;
        opTitleLogoMode = 2;
#endif
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

#ifdef VERSION_JUN26
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
#else
static inline int la_mc_saved_file_select(int item)
{
    int i = item - 27;
    int old = i;

    lt_analog2Pad();
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
    if (old != i) {
        CUR_SE();
    }
    return i + 27;
}
#endif

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
#else
int title_demo_mode = 0;

inline int la_title_demo(void)
{
    return -1;
}

static int continueDecided = 0; /* derived name */

int la_title_continue_or_new(int first)
{
    if (first) {
        opTitleLogoMode = 1;
        continueIcoMiscLock = lock_execIcoMisc;
        iosPadEnable();
        isysGObjActiveLink(0, 1);
        systemStatus[5] = 0;
        gflagOff(382);
        if (gflagChk(385) == 0) {
            gflagOn(385);
        }
        continueDecided = 0;
        lt_continue_selected = 0;
    }
    if (continueDecided != 0) {
        lt_item_select_disable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        lt_mask_property(14, 0);
        lt_mask_property(15, 0);
#else
        lt_mask_property(20, 0);
        lt_mask_property(21, 0);
#endif
#else
        lt_mask_property(49, 0);
        lt_mask_property(50, 0);
#endif
    } else {
        lt_item_select_disable = 1;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        lt_mask_property(14, 1);
        lt_mask_property(15, 1);
#else
        lt_mask_property(20, 1);
        lt_mask_property(21, 1);
#endif
#else
        lt_mask_property(49, 1);
        lt_mask_property(50, 1);
#endif
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if (continueDecided != 0 && (pad[0].flags & 0x820) && lt_fade_status() == 2) {
#else
    if (continueDecided != 0 && (pad[0].flags & 0x840) && lt_fade_status() == 2) {
#endif
        lt_continue_selected = 1;
        soundSeDefPlay(414, 0xFFFFFFFF, 0, 0);
        switch (lt_current_property_item()) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        case 14:
#else
        case 20:
#endif
#else
        case 49:
#endif
            opTitleLogoMode = 2;
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
            return 0x11;
        case 15:
#else
            return 0x11;
        case 21:
#endif
#else
            return 0x14;
        case 50:
#endif
            opTitleLogoMode = 2;
            gFlagGameClear = 0;
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 6;
#else
            return 9;
#endif
        }
    }
    switch (_la_set_current_port_2(&mc, first)) {
    case 0:
        break;
    case 1:
        if ((curPortInfo->flags.w & 0x22) == 2) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0xA;
#else
            return 0xD;
#endif
        }
        continueDecided = 1;
        break;
    case -1:
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0xA;
#else
        return 0xD;
#endif
    }
    return -1;
}

static int newGameDecided = 0; /* derived name */

int la_title_new_game_only(int first)
{
    if (first) {
        opTitleLogoMode = 1;
        newGameIcoMiscLock = lock_execIcoMisc;
        iosPadEnable();
        isysGObjActiveLink(0, 1);
        systemStatus[5] = 0;
        gflagOff(382);
        if (gflagChk(385) == 0) {
            gflagOn(385);
        }
        newGameDecided = 0;
        lt_continue_selected = 0;
        lastPort = -1;
    }
    if (newGameDecided != 0) {
        lt_item_select_disable = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        lt_mask_property(16, 0);
#else
        lt_mask_property(22, 0);
#endif
#else
        lt_mask_property(51, 0);
#endif
    } else {
        lt_item_select_disable = 1;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        lt_mask_property(16, 1);
#else
        lt_mask_property(22, 1);
#endif
#else
        lt_mask_property(51, 1);
#endif
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if (newGameDecided != 0 && (pad[0].flags & 0x820) && lt_fade_status() == 2) {
#else
    if (newGameDecided != 0 && (pad[0].flags & 0x840) && lt_fade_status() == 2) {
#endif
        soundSeDefPlay(414, 0xFFFFFFFF, 0, 0);
        lt_continue_selected = 1;
        opTitleLogoMode = 2;
        gFlagGameClear = 0;
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 6;
#else
        return 9;
#endif
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
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 9;
#else
            return 0xC;
#endif
        }
        newGameDecided = 1;
        break;
    }
    return -1;
}

static int filePort = -1; /* derived name */

static int saveSerial = 0; /* derived name */

static int loadSerial = 0; /* derived name */

static int savedFileNo = 0; /* derived name */

static int fileMoved = 0; /* derived name */

static int fileFirst = 1; /* derived name */

static inline int la_mc_saved_file_select(int item)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
    int i = item - 27;
#else
    int i = item - 33;
#endif
#else
    int i = item - 62;
#endif
    int old = i;

    lt_analog2Pad();
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
    if (old != i) {
        CUR_SE();
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
    return i + 27;
#else
    return i + 33;
#endif
#else
    return i + 62;
#endif
}

/* the selected port's current file number, 0 when the port has no card or
   the file is empty; inlined into la_mc_file_select both directly and
   through mcFileNoOfPort below */
static inline int mcCurrentFileNo(void) /* derived name */
{
    int port = filePort;
    int no = (IosMcProductFile + port)->fileNo;
    if (mcPortInfo[port].fileMask == 0 || IosMcProductFile[port].file[no].stage == 0xFFFFFFFF)
        return 0;
    return no;
}

/* the saved file's number when the port holds the loaded save, else the
   current file's; inlined once, into la_mc_file_select */
static inline int mcFileNoOfPort(void) /* derived name */
{
    int port = filePort;

    if (loadSerial == (IosMcProductFile + port)->serial)
        return savedFileNo;
    return mcCurrentFileNo();
}

int la_mc_file_select(int first)
{
    int i;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
    curFile = lt_current_property_item() - 27;
#else
    curFile = lt_current_property_item() - 33;
#endif
#else
    curFile = lt_current_property_item() - 62;
#endif

    if (first) {
        fileFirst = 1;
        fileMoved = 0;
    }

    if (actionStarted == 0) {
        lt_item_select_disable = 1;
        return -1;
    }

    if (fileFirst != 0) {
        fileFirst = 0;
        if (mcLoadMode != 0) {
            curFile = mcCurrentFileNo();
        } else {
            curFile = mcFileNoOfPort();
        }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        texLayout[11].curItem = curFile + 27;
#else
        texLayout[11].curItem = curFile + 33;
#endif
#else
        texLayout[14].curItem = curFile + 62;
#endif
        fileMoved = 1;
    }

    for (i = 0; i < 10; i++) {
        if (((fileMask >> i) & 1) && IosMcProductFile[filePort].file[i].stage != 0xFFFFFFFF) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
            lt_mask_property(i + 27, 0);
            lt_mask_property(i + 17, 1);
#else
            lt_mask_property(i + 33, 0);
            lt_mask_property(i + 23, 1);
#endif
#else
            lt_mask_property(i + 62, 0);
            lt_mask_property(i + 52, 1);
#endif
        } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
            lt_mask_property(i + 27, 1);
            lt_mask_property(i + 17, 0);
#else
            lt_mask_property(i + 33, 1);
            lt_mask_property(i + 23, 0);
#endif
#else
            lt_mask_property(i + 62, 1);
            lt_mask_property(i + 52, 0);
#endif
        }
    }

    previewInfo = *(struct McPreview *)&IosMcProductFile[filePort].file[curFile];

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    return (pad[0].flags & 0x30) ? curFile : -1;
#else
    return (pad[0].flags & 0x50) ? curFile : -1;
#endif
}

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
static void _la_mask_preview_info(void)
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
        lt_mask_property(i + 102, 1);
    }
    lt_mask_property(101, 1);
}
#else
static void _la_mask_preview_info(void)
{
    int i;

    for (i = 0; i < 10; i++) {
        lt_mask_property(i + 47, 1);
        lt_mask_property(i + 57, 1);
        lt_mask_property(i + 67, 1);
        lt_mask_property(i + 77, 1);
        lt_mask_property(i + 87, 1);
        lt_mask_property(i + 97, 1);
    }
    lt_mask_property(45, 1);
    lt_mask_property(46, 1);
    for (i = 0; i < 39; i++) {
        lt_mask_property(i + 108, 1);
    }
    lt_mask_property(107, 1);
}
#endif
#else
static void _la_mask_preview_info(void)
{
    int i;

    for (i = 0; i < 10; i++) {
        lt_mask_property(i + 76, 1);
        lt_mask_property(i + 86, 1);
        lt_mask_property(i + 96, 1);
        lt_mask_property(i + 106, 1);
        lt_mask_property(i + 116, 1);
        lt_mask_property(i + 126, 1);
    }
    lt_mask_property(74, 1);
    lt_mask_property(75, 1);
    for (i = 0; i < 39; i++) {
        lt_mask_property(i + 137, 1);
    }
    lt_mask_property(136, 1);
}
#endif
#endif

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
/* the frames a second, 60 or 50 by the video mode, over the field rate */
#define FRAME_RATE ((60 - systemStatus[0] * 10) / systemStatus[1]) /* derived name */
#endif

/* the play time of a save record split into hours, minutes and seconds and
   clamped to 99:59:59, inlined into _la_set_preview_info, la_load_processing
   and la_system_save_processing; the last two leave the results unused */
static inline void playTime(struct McPreview *p, int *hour, int *min, int *sec) /* derived name */
{
#ifdef VERSION_JUN26
    *sec = (p->playTime / FRAME_RATE) % 60;
    *min = (p->playTime / (FRAME_RATE * 60)) % 60;
    *hour = (p->playTime / (FRAME_RATE * 3600)) % 100;
#else
    int frames = p->playTime;
#ifdef VERSION_AUG6

    *sec = (frames / FRAME_RATE) % 60;
    *min = (frames / (FRAME_RATE * 60)) % 60;
    *hour = frames / (FRAME_RATE * 3600);
#else
    int fps = ((60 - systemStatus[0] * 10) / systemStatus[1]) * systemStatus[1];

    *sec = (frames / fps) % 60;
    *min = (frames / (fps * 60)) % 60;
    *hour = frames / (fps * 3600);
#endif
    if (*hour >= 100) {
        *hour = 99;
        *min = 59;
        *sec = 59;
    }
#endif
}

#ifdef VERSION_NTSC
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
        case 299:
            n = 39;
            break;
        case 301:
            n = 40;
            break;
        }
        lt_mask_property(n + 98, 0);
    }
}
#else
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
#ifdef VERSION_JUN26
    if (hour >= 100) {
        hour = 99;
        min = 59;
        sec = 59;
    }
#endif

    hour = ((hour / 10 + 9) % 10) * 10 + (hour % 10 + 9) % 10;
    min = ((min / 10 + 9) % 10) * 10 + (min % 10 + 9) % 10;
    sec = ((sec / 10 + 9) % 10) * 10 + (sec % 10 + 9) % 10;

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
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
#ifdef VERSION_JUN26
        case 287:
            n = 39;
            break;
        case 289:
#else
        case 298:
            n = 39;
            break;
        case 300:
#endif
#else
#if !defined(VERSION_PAL) && !defined(VERSION_NTSC)
#if defined(VERSION_KOR) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    lt_mask_property(41 + hour / 10, 0);
    lt_mask_property(51 + hour % 10, 0);
    lt_mask_property(61 + min / 10, 0);
    lt_mask_property(71 + min % 10, 0);
    lt_mask_property(81 + sec / 10, 0);
    lt_mask_property(91 + sec % 10, 0);
    lt_mask_property(39, 0);
    lt_mask_property(40, 0);
#else
    lt_mask_property(47 + hour / 10, 0);
    lt_mask_property(57 + hour % 10, 0);
    lt_mask_property(67 + min / 10, 0);
    lt_mask_property(77 + min % 10, 0);
    lt_mask_property(87 + sec / 10, 0);
    lt_mask_property(97 + sec % 10, 0);
    lt_mask_property(45, 0);
    lt_mask_property(46, 0);
#endif
#else
    lt_mask_property(76 + hour / 10, 0);
    lt_mask_property(86 + hour % 10, 0);
    lt_mask_property(96 + min / 10, 0);
    lt_mask_property(106 + min % 10, 0);
    lt_mask_property(116 + sec / 10, 0);
    lt_mask_property(126 + sec % 10, 0);
    lt_mask_property(74, 0);
    lt_mask_property(75, 0);
#endif

    n = previewInfo.stage;
#if !defined(VERSION_PAL) && !defined(VERSION_NTSC)
    if (n == 61) {
#else
    if (n == 63) {
#endif
        n = 38;
    }
    if (n >= 3 && n < 56) {
        switch (previewInfo.sofa) {
        case 329:
            n = 39;
            break;
        case 331:
#endif
            n = 40;
            break;
        }
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        lt_mask_property(n + 98, 0);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        lt_mask_property(n + 99, 0);
#else
        lt_mask_property(n + 105, 0);
#endif
#else
        lt_mask_property(n + 134, 0);
#endif
        if (previewInfo.cleared != 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
            lt_mask_property(101, 0);
#else
            lt_mask_property(107, 0);
#endif
#else
            lt_mask_property(136, 0);
#endif
        }
#endif
    }
}
#endif

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

#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
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
#ifdef VERSION_JUN26
    if (PSH_POSITIVE(0)) {
#else
    if (pad[0].flags & 0x40) {
#endif
        curPort = lt_current_property_item() - 151;
        lastPort = curPort;
        curPortInfo = &mcPortInfo[curPort];
#ifndef VERSION_JUN26
        POSITIVE_SE();
#endif
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 16;
    }
#ifdef VERSION_JUN26
    if (PSH_NEGATIVE(0)) {
#else
    if (pad[0].flags & 0x10) {
        NEGATIVE_SE();
#endif
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 9;
    }
    return -1;
}
#else
inline int la_mc_current_slot(void)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
    lt_mask_property(141, curPort);
    lt_mask_property(142, curPort ^ 1);
#else
    lt_mask_property(147, curPort);
    lt_mask_property(148, curPort ^ 1);
#endif
#else
    lt_mask_property(176, curPort);
    lt_mask_property(177, curPort ^ 1);
#endif
    return -1;
}

/* the load screen's default item; inlined once, into
   la_load_game_memory_card_check */
static inline void setLoadGameStartItem(void) /* derived name */
{
    if (loadSerial == IosMcProductFile[0].serial || saveSerial != IosMcProductFile[1].serial) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        texLayout[14].defaultItem = 152;
#else
        texLayout[14].defaultItem = 158;
#endif
#else
        texLayout[17].defaultItem = 186;
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        texLayout[14].defaultItem = 153;
#else
        texLayout[14].defaultItem = 159;
#endif
#else
        texLayout[17].defaultItem = 187;
#endif
    }
}

int la_load_game_memory_card_check(int first)
{
    _la_mask_preview_info();
    mcLoadMode = 1;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
    lt_mask_property(141, 1);
    lt_mask_property(142, 1);
#else
    lt_mask_property(147, 1);
    lt_mask_property(148, 1);
#endif
#else
    lt_mask_property(176, 1);
    lt_mask_property(177, 1);
#endif
    switch (_la_set_current_port_2(&mc, first)) {
    case 0:
        if (mcLastResult == 0 || mcLastResult == -14) {
            return -1;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x13;
#else
        return 0x16;
#endif
    case -1:
        if ((curPortInfo->flags.w >> 1) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x14;
#else
            return 0x17;
#endif
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x13;
#else
        return 0x16;
#endif
    case 1:
        if ((curPortInfo->flags.w >> 6) & 1) {
            setLoadGameStartItem();
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0xE;
#else
            return 0x11;
#endif
        }
        if ((curPortInfo->flags.w >> 5) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x10;
#else
            return 0x13;
#endif
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x14;
#else
        return 0x17;
#endif
    }
    return -1;
}

inline int la_mc_load_current_slot_select(void)
{
    _la_mask_preview_info();
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
    if (pad[0].flags & 0x20) {
        curPort = lt_current_property_item() - 152;
#else
    if (pad[0].flags & 0x20) {
        curPort = lt_current_property_item() - 158;
#endif
#else
    if (pad[0].flags & 0x40) {
        curPort = lt_current_property_item() - 186;
#endif
        lastPort = curPort;
        curPortInfo = &mcPortInfo[curPort];
        POSITIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x10;
#else
        return 0x13;
#endif
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if (pad[0].flags & 0x40) {
#else
    if (pad[0].flags & 0x10) {
#endif
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x9;
#else
        return 0xC;
#endif
    }
    return -1;
}
#endif

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
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
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
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        lt_mask_property(38, 1);
        lt_mask_property(37, 1);
        lt_mask_property(161, 0);
        lt_mask_property(162, 0);
#else
        lt_mask_property(44, 1);
        lt_mask_property(43, 1);
        lt_mask_property(167, 0);
        lt_mask_property(168, 0);
#endif
#else
        lt_mask_property(73, 1);
        lt_mask_property(72, 1);
        lt_mask_property(195, 0);
        lt_mask_property(196, 0);
#endif
    } else {
        _la_mask_preview_info();
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        lt_mask_property(38, 0);
        lt_mask_property(37, 0);
        lt_mask_property(161, 1);
        lt_mask_property(162, 1);
#else
        lt_mask_property(44, 0);
        lt_mask_property(43, 0);
        lt_mask_property(167, 1);
        lt_mask_property(168, 1);
#endif
#else
        lt_mask_property(73, 0);
        lt_mask_property(72, 0);
        lt_mask_property(195, 1);
        lt_mask_property(196, 1);
#endif
#endif
    }
    lt_set_item_select_func((int)la_mc_saved_file_select);

#ifdef VERSION_JUN26
    if (PSH_NEGATIVE(0)) {
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 9;
    }

    if ((fileMask != 0 || loadFileChosen != 0) && PSH_POSITIVE(0)) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if (pad[0].flags & 0x40) {
#else
    if (pad[0].flags & 0x10) {
#endif
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
#if !defined(VERSION_PAL) && !defined(VERSION_JUN26)
        return 9;
#else
        return 12;
#endif
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if ((fileMask != 0 || loadFileChosen != 0) && (pad[0].flags & 0x20)) {
#else
    if ((fileMask != 0 || loadFileChosen != 0) && (pad[0].flags & 0x40)) {
#endif
        POSITIVE_SE();
#endif
        if (IosMcProductFile[filePort].file[item].stage != 0xFFFFFFFF) {
            selectFile = item;
            lastPort = filePort;
            lt_set_item_select_func(0);
            actionStarted = 0;
#if !defined(VERSION_PAL) && !defined(VERSION_JUN26)
            return 18;
#else
#ifdef VERSION_JUN26
            return 18;
#else
            return 21;
#endif
#endif
        }
    }

    r = _la_set_current_port_lock_2(&mc, first);
    switch (r) {
    case -1:
        if (((curPortInfo->flags.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if !defined(VERSION_PAL) && !defined(VERSION_JUN26)
            return 19;
#else
#ifdef VERSION_JUN26
            return 19;
#else
            return 22;
#endif
#endif
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
#if !defined(VERSION_PAL) && !defined(VERSION_JUN26)
        return 20;
#else
#ifdef VERSION_JUN26
        return 20;
#else
        return 23;
#endif
#endif
    case 1:
        if (((curPortInfo->flags.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if !defined(VERSION_PAL) && !defined(VERSION_JUN26)
            return 19;
#else
#ifdef VERSION_JUN26
            return 19;
#else
            return 22;
#endif
#endif
        }
        if ((curPortInfo->flags.w & 0x22) == 2) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if !defined(VERSION_PAL) && !defined(VERSION_JUN26)
            return 20;
#else
#ifdef VERSION_JUN26
            return 20;
#else
            return 23;
#endif
#endif
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
#if !defined(VERSION_PAL) && !defined(VERSION_JUN26)
                return 14;
#else
#ifdef VERSION_JUN26
                return 14;
#else
                return 17;
#endif
#endif
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

#ifdef VERSION_NTSC
int la_load_confirm_no_memory_card(int first)
{
    if (first) {
        _la_mask_preview_info();
    }
    if (PSH_POSITIVE_OR_NEGATIVE(0)) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 10;
    }
    switch (_la_set_current_port_lock_2(&mc, first)) {
    case 0:
        break;
    case -1:
        if ((curPortInfo->flags.w & 0x12) == 2 || (curPortInfo->flags.w & 0x22) == 2) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 20;
        }
        if ((curPortInfo->flags.w >> 1) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 17;
        }
        lock2Restart = 1;
        break;
    case 1:
        if ((curPortInfo->flags.w & 0x12) == 2 || (curPortInfo->flags.w & 0x22) == 2) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 20;
        }
        if ((curPortInfo->flags.w >> 1) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 17;
        }
        break;
    }
    return -1;
}
#else
int la_load_confirm_no_memory_card(int first)
{
    if (first) {
        _la_mask_preview_info();
    }
#ifdef VERSION_JUN26
    if (PSH_POSITIVE(0)) {
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 10;
#else
    if (PSH_POSITIVE_OR_NEGATIVE(0)) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0xA;
#else
#ifdef VERSION_AUG6
        return 10;
#else
        return 0xD;
#endif
#endif
#endif
    }
    switch (_la_set_current_port_lock_2(&mc, first)) {
    case 0:
        break;
    case -1:
#ifndef VERSION_JUN26
#ifdef VERSION_AUG6
        if ((curPortInfo->flags.w & 0x12) == 2) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 20;
#else
        if ((curPortInfo->flags.w & 0x32) == 2 || (curPortInfo->flags.w & 0x22) == 2) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x14;
#else
            return 0x17;
#endif
#endif
        }
#endif
        if ((curPortInfo->flags.w >> 1) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x11;
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 17;
#else
            return 0x14;
#endif
#endif
        }
        lock2Restart = 1;
        break;
    case 1:
#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
        if ((curPortInfo->flags.w & 0x32) == 2 || (curPortInfo->flags.w & 0x22) == 2) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x14;
#else
            return 0x17;
#endif
        }
#endif
        if ((curPortInfo->flags.w >> 1) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x11;
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 17;
#else
            return 0x14;
#endif
#endif
        }
        break;
    }
    return -1;
}
#endif

int la_load_confirm_no_data(int first)
{
    if (first) {
        _la_mask_preview_info();
    }
#ifdef VERSION_JUN26
    if (PSH_POSITIVE(0)) {
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 10;
#else
    if (PSH_POSITIVE_OR_NEGATIVE(0)) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0xA;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        return 10;
#else
        return 0xD;
#endif
#endif
#endif
    }
    switch (_la_set_current_port_lock_2(&mc, first)) {
    case 0:
        break;
    case -1:
        if (((curPortInfo->flags.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x13;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 19;
#else
            return 0x16;
#endif
#endif
        }
        lock2Restart = 1;
        break;
    case 1:
        if ((curPortInfo->flags.w >> 5) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x11;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 17;
#else
            return 0x14;
#endif
#endif
        }
        break;
    }
    return -1;
}

#ifdef VERSION_NTSC
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
#else
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
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x2B;
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 42;
#else
        return 0x2E;
#endif
#endif
    case -1:
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x2B;
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 42;
#else
        return 0x2E;
#endif
#endif
    case 1:
        if (filePort != curPort) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x2B;
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 42;
#else
            return 0x2E;
#endif
#endif
        }
        if ((curPortInfo->flags.w & 3) != 3) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x13;
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 19;
#else
            return 0x16;
#endif
#endif
        }
        if ((curPortInfo->fileMask >> selectFile) & 1) {
            fileMask = 0x3FF;
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x16;
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 22;
#else
            return 0x19;
#endif
#endif
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 20;
    }
    return -1;
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x14;
#else
        return 0x17;
#endif
    }
    return -1;
}

/* the saved file's serial read from the port's record, with the file number
   kept beside it; inlined into la_load_processing directly and into
   la_save_processing through mcSetSavedFile */
static inline int mcSetFileNo(int port, int no) /* derived name */
{
    int serial = (IosMcProductFile + port)->serial;

    savedFileNo = no;
    return serial;
#endif
}
#endif

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
#ifdef VERSION_JUN26
    case 9:
        gflagKeepState();
        gflagInit();
        gamesysMemoryLoad(gameSysMemoryFuncList, gameSysMainSaveBuff, 0);
        gflagRestoreState();
        systemStatus[3] = 1;
        systemStatus[4] = 1;
        /* falls through */
    case 6:
#else
    case 6:
    case 9:
#endif
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
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 43;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 42;
#else
        return 46;
#endif
#endif
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
#ifndef VERSION_JUN26
        gflagKeepState();
        gflagInit();
        gamesysMemoryLoad(gameSysMemoryFuncList, gameSysMainSaveBuff, 0);
        gflagRestoreState();
        systemStatus[3] = 1;
        systemStatus[4] = 1;
#endif
        debug_StdPrintfDummy("case 10\n");
        loadStep = 0;
        *(struct McPreview *)IosMcPreviewInfo =
            *(struct McPreview *)&IosMcProductFile[mc.port].file[mc.fileNo];
        playTime((struct McPreview *)IosMcPreviewInfo, &hour, &min, &sec);
#ifdef VERSION_JUN26
        debug_StdPrintfDummy("stage no %d\n", gFlagSaveStage);
        seEnvForceClose = 1;
        soundDataSegAllClose(0, 2);
        stgmgrForceSwitchWithFade(gFlagSaveStage, 0.5f, 4.0f);
#else
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
        loadSerial = mcSetFileNo(mc.port, mc.fileNo);
#endif
        debug_StdPrintfDummy("stage no %d\n", gFlagSaveStage);
        seEnvForceClose = 1;
        if (titleAdpcm != 0) {
            titleAdpcm->stream->fadeStep = 0x40;
        }
        titleAdpcm = 0;
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
        if (gflagChk(395)) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 6;
#else
            return 9;
#endif
        }
#endif
        stgmgrForceSwitchWithFade(gFlagSaveStage, 0.05f, 4.0f);
#endif
        ACTGame_SetActors_Debug(gFlagSaveStage, 0);
        return -1;
    case 20:
        lt_set_item_select_func(0);
        actionStarted = 0;
#if !defined(VERSION_PAL) && !defined(VERSION_JUN26)
        return 17;
#else
#ifdef VERSION_JUN26
        return 17;
#else
        return 20;
#endif
#endif
    }
    return -1;
}

inline int la_general_mc_confirm(void)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if (pad[0].flags & 0x20) {
#else
#ifdef VERSION_JUN26
    if (PSH_POSITIVE(0)) {
#else
    if (pad[0].flags & 0x40) {
#endif
#endif
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

#ifdef VERSION_JUN26
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
#else
/* extra preview pages to re-mask; none in the release build */
#define LA_EXTRA_PREVIEW_PAGES 0

static int saveVoice = 0; /* derived name */

static int saveVoiceOpened = 0; /* derived name */

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
int la_mc_confirm_save_file(int first, int item)
{
    int i;

    _la_mask_preview_info();
    lt_mask_property(140, 1);
    lt_mask_property(141, 1);
    if (first) {
        systemStatus[5] = 1;
        if (fightSoundProcessRequestStatus() == 0) {
            fightSoundProcessRequestPause();
            fightSoundStopped = 1;
        }
        CheckPoint();
        saveVoiceOpened = 0;
    }
    if (saveVoiceOpened == 0) {
        if (AdpcmFreeAreaGet() != 0) {
            saveVoice = openLayoutVoice(21);
            saveVoiceOpened = 1;
        }
    } else {
        _la_mask_preview_info();
        /* a loop over extra preview pages, built with a count of 0 in the
           release build, so its body never runs */
        for (i = 0; i < LA_EXTRA_PREVIEW_PAGES; i++) {
            _la_mask_preview_info();
        }
        if (saveVoice != 0) {
            layoutVoice = soundDataOpenSync(&voiceOpenReq);
            if (layoutVoice != (SqEntry *)0xFFFFFFFF) {
                saveVoice = 0;
                if (layoutVoice != 0) {
                    AdpcmPlay(layoutVoice->stream);
                    return -1;
                }
            }
            return -1;
        }
        {
            if (lt_fade_status() == 2) {
                switch (item) {
                case 183:
                    POSITIVE_SE();
                    lt_set_item_select_func(0);
                    actionStarted = 0;
                    return 26;
                case 184:
                    NEGATIVE_SE();
                    systemStatus[5] = 0;
                    lt_set_item_select_func(0);
                    actionStarted = 0;
                    return 50;
                }
            }
            if (lt_fade_status() != 2) {
                return -1;
            }
            if ((pad[0].flags & 0x10) == 0) {
                return -1;
            }
            NEGATIVE_SE();
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 50;
        }
    }
    return -1;
}
#else
static int saveVoiceWait = 0; /* derived name */

int la_mc_confirm_save_file(int first, int item)
{
    int i;

    _la_mask_preview_info();
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
    lt_mask_property(141, 1);
    lt_mask_property(142, 1);
#else
    lt_mask_property(147, 1);
    lt_mask_property(148, 1);
#endif
#else
    lt_mask_property(176, 1);
    lt_mask_property(177, 1);
#endif
    if (first) {
        systemStatus[5] = 1;
        fightSoundProcessRequestPause();
        fightSoundStopped = 1;
        CheckPoint();
        saveVoiceOpened = 0;
        saveVoiceWait = 0;
    }
    if (saveVoiceOpened == 0) {
        if (AdpcmFreeAreaGet() != 0) {
            saveVoice = openLayoutVoice(0x16);
            saveVoiceOpened = 1;
        } else {
            debug_StdPrintfDummy("ADPCM一杯で開けませんでした。\n");
            if (AdpcmNotUseIopAreaFree() != 0) {
                debug_StdPrintfDummy(
                    "オープンされていないのにも関わらず使われていないIOP領域発見&強制解放\n");
                return -1;
            }
            if (saveVoiceWait-- < 0) {
                AdpcmFadeCloseAll(0x3FFF);
                return -1;
            }
        }
    } else {
        _la_mask_preview_info();
        /* a loop over extra preview pages, built with a count of 0 in the
           release build, so its body never runs */
        for (i = 0; i < LA_EXTRA_PREVIEW_PAGES; i++) {
            _la_mask_preview_info();
        }
        if (saveVoice != 0) {
            layoutVoice = soundDataOpenSync(&voiceOpenReq);
            if (layoutVoice != (SqEntry *)0xFFFFFFFF) {
                saveVoice = 0;
                if (layoutVoice != 0) {
                    AdpcmPlay(layoutVoice->stream);
                    return -1;
                }
            }
            return -1;
        }
        {
            if (lt_fade_status() == 2) {
                switch (item) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
                case 184:
#else
                case 190:
#endif
#else
                case 214:
#endif
                    POSITIVE_SE();
                    lt_set_item_select_func(0);
                    actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
                    return 0x1B;
                case 185:
#else
                    return 0x1B;
                case 191:
#endif
#else
                    return 0x1E;
                case 215:
#endif
                    NEGATIVE_SE();
                    systemStatus[5] = 0;
                    lt_set_item_select_func(0);
                    actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
                    return 0x33;
#else
                    return 0x36;
#endif
                }
            }
            if (lt_fade_status() != 2) {
                return -1;
            }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            if ((pad[0].flags & 0x40) == 0) {
#else
            if ((pad[0].flags & 0x10) == 0) {
#endif
                return -1;
            }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            if (stage_no == 0x3D) {
#else
            if (stage_no == 0x3F) {
#endif
                return -1;
            }
            NEGATIVE_SE();
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x33;
#else
            return 0x36;
#endif
        }
    }
    return -1;
}

/* the save side of setLoadGameStartItem, inlined twice into
   la_save_game_memory_card_check */
static inline void setSaveGameStartItem(void) /* derived name */
{
    if (loadSerial == IosMcProductFile[0].serial || loadSerial != IosMcProductFile[1].serial) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        texLayout[15].defaultItem = 152;
#else
        texLayout[15].defaultItem = 158;
#endif
#else
        texLayout[18].defaultItem = 186;
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        texLayout[15].defaultItem = 153;
#else
        texLayout[15].defaultItem = 159;
#endif
#else
        texLayout[18].defaultItem = 187;
#endif
    }
}
#endif
#endif

int la_save_game_memory_card_check(int first)
{
    _la_mask_preview_info();
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    lt_mask_property(140, 1);
    lt_mask_property(141, 1);
#else
    mcLoadMode = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
    lt_mask_property(141, 1);
    lt_mask_property(142, 1);
#else
    lt_mask_property(147, 1);
    lt_mask_property(148, 1);
#endif
#else
    lt_mask_property(176, 1);
    lt_mask_property(177, 1);
#endif
#endif
    debug_StdPrintfDummy("save game check port %d\n", curPort);
    switch (_la_set_current_port_new(&mc, first)) {
    case 0:
        break;
    case -1:
        debug_StdPrintfDummy("fail\n");
        if ((curPortInfo->flags.w & 3) == 3) {
            if ((curPortInfo->flags.w >> 2) & 1) {
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
                lt_set_item_select_func(0);
                actionStarted = 0;
                return 15;
#else
                setSaveGameStartItem();
                lt_set_item_select_func(0);
                actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
                return 0xF;
#else
                return 0x12;
#endif
#endif
            }
            if (((curPortInfo->flags.w >> 4) & 1) == 0) {
                lt_set_item_select_func(0);
                actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
                return 0x1D;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
                return 28;
#else
                return 0x20;
#endif
#endif
            }
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x1C;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 27;
#else
        return 0x1F;
#endif
#endif
    case 1:
        debug_StdPrintfDummy("sucess :%d %d %d\n", (curPortInfo->flags.w >> 5) & 1,
                             (curPortInfo->flags.w >> 4) & 1, (curPortInfo->flags.w & 0xA) == 2);
        if ((curPortInfo->flags.w >> 2) & 1) {
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 15;
#else
            setSaveGameStartItem();
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0xF;
#else
            return 0x12;
#endif
#endif
        }
        if ((curPortInfo->flags.w & 0x30) != 0 || (curPortInfo->flags.w & 0xA) == 2) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x1E;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 29;
#else
            return 0x21;
#endif
#endif
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 28;
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x1D;
#else
        return 0x20;
#endif
    }
    return -1;
}

inline int la_mc_save_current_slot_select(void)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if (pad[0].flags & 0x20) {
#else
    if (pad[0].flags & 0x40) {
#endif
        POSITIVE_SE();
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        curPort = lt_current_property_item() - 152;
#else
        curPort = lt_current_property_item() - 158;
#endif
#else
        curPort = lt_current_property_item() - 186;
#endif
        lastPort = curPort;
        curPortInfo = &mcPortInfo[curPort];
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x1E;
#else
        return 0x21;
#endif
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if (pad[0].flags & 0x40) {
#else
    if (pad[0].flags & 0x10) {
#endif
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x19;
#else
        return 0x1C;
#endif
#endif
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

#ifdef VERSION_JUN26
/* gif_Line's z words go as 32-bit unsigned ints here too (lui/ori) */
extern void gif_Line(int *v0, int *v1, unsigned int z0, unsigned int z1, SprCol *col, int prim);
#endif

static int barStep = 0; /* derived name */

static int barFrame = 0; /* derived name */

#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
inline int la_mc_save_current_slot_select(void)
{
#ifdef VERSION_JUN26
    if (PSH_POSITIVE(0)) {
#else
    if (pad[0].flags & 0x40) {
        POSITIVE_SE();
#endif
        curPort = lt_current_property_item() - 151;
        lastPort = curPort;
        curPortInfo = &mcPortInfo[curPort];
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 29;
    }
#ifdef VERSION_JUN26
    if (PSH_NEGATIVE(0)) {
#else
    if (pad[0].flags & 0x10) {
        NEGATIVE_SE();
#endif
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 25;
    }
    return -1;
}
#endif

static void progressive_bar(void)
{
    int n;
#ifdef VERSION_JUN26
    sceVu0IVECTOR p0;
    sceVu0IVECTOR p1;
#endif

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
#if !defined(VERSION_PAL) && !defined(VERSION_JUN26)
        SprRect frame = {80, 6, -160, 6};
#else
#ifdef VERSION_JUN26
        SprRect frame = {80, 6, -160, 6};
#else
        SprRect frame = {80, 11, -160, 5};
#endif
#endif
        SprCol frameCol = {128, 128, 128, 32};

        gif_Sprite(&frame, 0xFFFFFFFF, 0, &frameCol, 1);
    }
    {
#if !defined(VERSION_PAL) && !defined(VERSION_JUN26)
        SprRect back = {78, 7, -156, 4};
#else
#ifdef VERSION_JUN26
        SprRect back = {78, 7, -156, 4};
#else
        SprRect back = {78, 12, -156, 3};
#endif
#endif
        SprCol backCol = {0, 0, 0, 32};

        gif_Sprite(&back, 0xFFFFFFFF, 0, &backCol, 1);
    }
    {
        int w = (float)barStep / (float)barTotal * -160.0f;
#if !defined(VERSION_PAL) && !defined(VERSION_JUN26)
        SprRect bar = {-80 - w, 8, w, 2};
#else
#ifdef VERSION_JUN26
        SprRect bar = {-80 - w, 8, w, 2};
#else
        SprRect bar = {-80 - w, 13, w, 1};
#endif
#endif
        SprCol barCol = {64, 255, 64, 32};

        gif_Sprite(&bar, 0xFFFFFFFF, 0, &barCol, 1);
#ifdef VERSION_JUN26
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
#endif
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
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        lt_mask_property(38, 1);
        lt_mask_property(37, 1);
        lt_mask_property(208, 0);
        lt_mask_property(209, 0);
    } else {
        lt_mask_property(38, 0);
        lt_mask_property(37, 0);
        lt_mask_property(208, 1);
        lt_mask_property(209, 1);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        lt_mask_property(38, 1);
        lt_mask_property(37, 1);
        lt_mask_property(210, 0);
        lt_mask_property(211, 0);
#else
        lt_mask_property(44, 1);
        lt_mask_property(43, 1);
        lt_mask_property(216, 0);
        lt_mask_property(217, 0);
#endif
#else
        lt_mask_property(73, 1);
        lt_mask_property(72, 1);
        lt_mask_property(239, 0);
        lt_mask_property(240, 0);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        lt_mask_property(38, 0);
        lt_mask_property(37, 0);
        lt_mask_property(210, 1);
        lt_mask_property(211, 1);
#else
        lt_mask_property(44, 0);
        lt_mask_property(43, 0);
        lt_mask_property(216, 1);
        lt_mask_property(217, 1);
#endif
#else
        lt_mask_property(73, 0);
        lt_mask_property(72, 0);
        lt_mask_property(239, 1);
        lt_mask_property(240, 1);
#endif
#endif
    }

    if (actionStarted != 0) {
#ifdef VERSION_JUN26
        if (PSH_NEGATIVE(0)) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 25;
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        if (pad[0].flags & 0x40) {
#else
        if (pad[0].flags & 0x10) {
#endif
            NEGATIVE_SE();
            lt_set_item_select_func(0);
            actionStarted = 0;
#if !defined(VERSION_PAL) && !defined(VERSION_JUN26)
            return 25;
#else
            return 28;
#endif
#endif
        }
    }

#ifdef VERSION_JUN26
    if ((fileMask != 0 || saveSelectReady != 0) && PSH_POSITIVE(0)) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if ((fileMask != 0 || saveSelectReady != 0) && (pad[0].flags & 0x20)) {
#else
    if ((fileMask != 0 || saveSelectReady != 0) && (pad[0].flags & 0x40)) {
#endif
        POSITIVE_SE();
#endif
        selectFile = item;
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 31;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 30;
#else
        return 34;
#endif
#endif
    }

    r = _la_set_current_port_lock_2(&mc, first);
    switch (r) {
    case -1:
        if (((curPortInfo->flags.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 28;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 27;
#else
            return 31;
#endif
#endif
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 29;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 28;
#else
        return 32;
#endif
#endif
    case 1:
        if (((mcPortInfo[filePort].flags.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if !defined(VERSION_PAL) && !defined(VERSION_JUN26)
            return 25;
#else
#ifdef VERSION_JUN26
            return 25;
#else
            return 28;
#endif
#endif
        }
        if (fileMask != 0) {
            if (saveCardChanged == 0) {
                if (((curPortInfo->flags.w >> 2) & 1) != 0) {
                    lt_set_item_select_func(0);
                    actionStarted = 0;
#if !defined(VERSION_PAL) && !defined(VERSION_JUN26)
                    return 15;
#else
#ifdef VERSION_JUN26
                    return 15;
#else
                    return 18;
#endif
#endif
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
#ifdef VERSION_JUN26
    if (PSH_POSITIVE(0)) {
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 25;
#else
    if (PSH_POSITIVE_OR_NEGATIVE(0)) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x19;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        return 25;
#else
        return 0x1C;
#endif
#endif
#endif
    }
    switch (_la_set_current_port_lock_2(&mc, first)) {
    case 0:
        break;
    case -1:
        if ((curPortInfo->flags.w >> 1) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x1B;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 26;
#else
            return 0x1E;
#endif
#endif
        }
        lock2Restart = 1;
        break;
    case 1:
        if ((curPortInfo->flags.w >> 1) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x1B;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 26;
#else
            return 0x1E;
#endif
#endif
        }
        break;
    }
    return -1;
}

inline int la_save_confirm_no_free_area(int first)
{
#ifdef VERSION_JUN26
    if (PSH_POSITIVE(0)) {
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 25;
#else
    if (PSH_POSITIVE_OR_NEGATIVE(0)) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x19;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        return 25;
#else
        return 0x1C;
#endif
#endif
#endif
    }
    switch (_la_set_current_port_lock_2(&mc, first)) {
    case 0:
        break;
    case -1:
        if (((curPortInfo->flags.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x1C;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 27;
#else
            return 0x1F;
#endif
#endif
        }
        lock2Restart = 1;
        break;
    case 1:
        if ((curPortInfo->flags.w >> 4) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x1B;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 26;
#else
            return 0x1E;
#endif
#endif
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
#ifdef VERSION_JUN26
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 26;
#else
        if (((curPortInfo->flags.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x1C;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
            return 27;
#else
            return 0x1F;
#endif
#endif
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x1B;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        return 26;
#else
        return 0x1E;
#endif
#endif
#endif
    case 1:
        if (filePort != curPort) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x29;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 40;
#else
            return 0x2C;
#endif
#endif
        }
        if ((curPortInfo->flags.w & 0xA) == 2) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x21;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 32;
#else
            return 0x24;
#endif
#endif
        }
        if ((curPortInfo->fileMask >> selectFile) & 1) {
            if (IosMcProductFile[filePort].file[selectFile].stage != 0xFFFFFFFF) {
                lt_set_item_select_func(0);
                actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
                return 0x20;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
                return 31;
#else
                return 0x23;
#endif
#endif
            }
            if (curPortInfo->fileMask != 0) {
                debug_StdPrintfDummy("already exist save data\n");
                lt_set_item_select_func(0);
                actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
                return 0x23;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
                return 34;
#else
                return 0x26;
#endif
#endif
            }
        }
        debug_StdPrintfDummy("new save. system data making..\n");
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x24;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 35;
#else
        return 0x27;
#endif
#endif
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
#ifdef VERSION_JUN26
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
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if (lt_fade_status() == 2 && (pad[0].flags & 0x40)) {
#else
    if (lt_fade_status() == 2 && (pad[0].flags & 0x10)) {
#endif
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        return 29;
    }
    switch (item) {
    case 183:
    case 187:
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x1E;
#else
        return 0x21;
#endif
    }
    switch (item) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
    case 184:
    case 188:
#else
    case 190:
    case 194:
#endif
#else
    case 214:
    case 218:
#endif
#endif
        POSITIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        return 0x23;
    case 185:
    case 189:
#else
        return 0x23;
    case 191:
    case 195:
#endif
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        return 34;
    case 184:
    case 188:
#else
        return 0x26;
    case 215:
    case 219:
#endif
#endif
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x1E;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        return 29;
#else
        return 0x21;
#endif
#endif
#endif
    }
    switch (_la_set_current_port_lock_2(&mc, first)) {
    case 0:
        break;
    case -1:
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x1C;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 27;
#else
        return 0x1F;
#endif
#endif
    case 1:
        if (saveCardChanged == 0) {
            if (((curPortInfo->flags.w >> 2) & 1) == 0) {
                break;
            }
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0xF;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 15;
#else
            return 0x12;
#endif
#endif
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
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x1B;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 26;
#else
        return 0x1E;
#endif
#endif
    }
    return -1;
}

int la_format_confirm(int first, int item)
{
    if (first) {
        filePort = curPort;
    }
#ifdef VERSION_JUN26
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
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if (lt_fade_status() == 2 && (pad[0].flags & 0x40)) {
#else
    if (lt_fade_status() == 2 && (pad[0].flags & 0x10)) {
#endif
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        return 29;
    }
    switch (item) {
    case 183:
    case 187:
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x1E;
#else
        return 0x21;
#endif
    }
    switch (item) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
    case 184:
    case 188:
#else
    case 190:
    case 194:
#endif
#else
    case 214:
    case 218:
#endif
#endif
        POSITIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        return 0x22;
    case 185:
    case 189:
#else
        return 0x22;
    case 191:
    case 195:
#endif
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        return 33;
    case 184:
    case 188:
#else
        return 0x25;
    case 215:
    case 219:
#endif
#endif
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x1E;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        return 29;
#else
        return 0x21;
#endif
#endif
#endif
    }
    switch (_la_set_current_port_lock_2(&mc, first)) {
    case 0:
        break;
    case -1:
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x1C;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 27;
#else
        return 0x1F;
#endif
#endif
    case 1:
        if (saveCardChanged == 0) {
            if (((curPortInfo->flags.w >> 2) & 1) == 0) {
                break;
            }
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0xF;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 15;
#else
            return 0x12;
#endif
#endif
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
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x1B;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 26;
#else
        return 0x1E;
#endif
#endif
    }
    return -1;
}

static int formatStep = 0; /* derived name */

#ifdef VERSION_NTSC
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
#else
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
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x2A;
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 41;
#else
        return 0x2D;
#endif
#endif
    case 4:
        formatStep++;
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 35;
    }
    return -1;
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x24;
#else
        return 0x27;
#endif
    }
    return -1;
}

/* the CD real-time clock record sceCdReadClock fills in, declared here as
   seki/src/GsBase.c declares it */
typedef struct sceCdCLOCK {
    unsigned char stat;
    unsigned char second;
    unsigned char minute;
    unsigned char hour;
    unsigned char pad;
    unsigned char day;
    unsigned char month;
    unsigned char year;
} sceCdCLOCK;

/* the save serial, the clock packed into one word or a random number when
   the clock cannot be read; inlined into la_system_save_processing */
static inline int mcMakeSerial(void) /* derived name */
{
    sceCdCLOCK clock;

    sceCdReadClock(&clock);
    if (clock.stat != 0) {
        return rand();
    }
    return ((clock.year & 7) << 26) + (clock.day << 20) + (clock.hour << 14) + (clock.minute << 7) +
           clock.second;
#endif
}
#endif

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
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 41;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 40;
#else
        return 44;
#endif
#endif
    case 4:
        for (i = 0; i < 10; i++) {
            IosMcProductFile[mc.port].file[i].stage = 0xFFFFFFFF;
        }
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
        while ((IosMcProductFile[mc.port].serial = mcMakeSerial()) == 0)
            ;
#endif
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
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 35;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 34;
#else
            return 38;
#endif
#endif
        }
        break;
    }
    return -1;
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
}

/* the save side's readback, the serial kept as both the saved and the
   current one; inlined into la_save_processing */
static inline void mcSetSavedFile(void) /* derived name */
{
    int serial = mcSetFileNo(mc.port, mc.fileNo);

    loadSerial = serial;
    saveSerial = serial;
#endif
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
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 40;
    case 4:
        IosMcPreviewInfo[0] = stage_no;
        IosMcPreviewInfo[2] = GetSaveSofaLayoutID();
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 41;
#else
        return 44;
#endif
    case 4:
        IosMcPreviewInfo[0] = stage_no;
        IosMcPreviewInfo[3] = GetSaveSofaLayoutID();
        IosMcPreviewInfo[1] = gFlagGameClear;
#endif
        *(struct McPreview *)&IosMcProductFile[mc.port].file[mc.fileNo] =
            *(struct McPreview *)IosMcPreviewInfo;
        playTime((struct McPreview *)IosMcPreviewInfo, &hour, &min, &sec);
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
        (IosMcProductFile + mc.port)->fileNo = mc.fileNo;
        if ((IosMcProductFile + mc.port)->serial == (IosMcProductFile + (mc.port ^ 1))->serial) {
            do {
                while ((IosMcProductFile[mc.port].serial = mcMakeSerial()) == 0)
                    ;
            } while ((IosMcProductFile + mc.port)->serial ==
                     (IosMcProductFile + (mc.port ^ 1))->serial);
        }
        mcSetSavedFile();
#endif
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
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 38;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 37;
#else
        return 41;
#endif
#endif
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
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        debug_StdPrintfDummy("%d %d %d\n", 233, 234, item);
    }
    switch (item) {
    case 233:
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        debug_StdPrintfDummy("%d %d %d\n", 235, 236, item);
#else
        debug_StdPrintfDummy("%d %d %d\n", 241, 242, item);
#endif
#else
        debug_StdPrintfDummy("%d %d %d\n", 264, 265, item);
#endif
    }
    switch (item) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
    case 235:
#else
    case 241:
#endif
#else
    case 264:
#endif
#endif
        systemStatus[5] = 0;
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        return 0x33;
    case 236:
#else
        return 0x33;
    case 242:
#endif
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 50;
    case 234:
#else
        return 0x36;
    case 265:
#endif
#endif
        nextStage = 1;
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x3C;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 59;
#else
        return 0x3F;
#endif
#endif
    }
    return -1;
}

#ifdef VERSION_NTSC
int la_end_confirm(void)
{
    int item;

    if (lt_fade_status() == 2 && (pad[0].flags & 0x10)) {
        NEGATIVE_SE();
        item = lt_current_property_item();
        if (item >= 239) {
            if (item < 241) {
                lt_set_item_select_func(0);
                actionStarted = 0;
                return 37;
            }
            if (item < 375) {
                if (item >= 373) {
                    lt_set_item_select_func(0);
                    actionStarted = 0;
                    return 53;
                }
            }
        }
    }
    if (pad[0].flags & 0x40) {
        debug_StdPrintfDummy("%d\n", lt_current_property_item());
        switch (lt_current_property_item()) {
        case 239:
        case 373:
            POSITIVE_SE();
            gflagInit();
            fightSoundProcessRequestPause();
            fightSoundClose();
            soundDataSegAllClose(0, 2);
            nextStage = 1;
            stgmgrForceSwitchWithFade(1, 0.025f, 4.0f);
        case 240:
            NEGATIVE_SE();
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 37;
        case 374:
            NEGATIVE_SE();
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 53;
        }
    }
    return -1;
}

static int deleteStep = 0; /* derived name */
#else
#ifdef VERSION_JUN26
inline int la_end_confirm(void)
{
    if (PSH_POSITIVE(0)) {
        debug_StdPrintfDummy("%d\n", lt_current_property_item());
        switch (lt_current_property_item()) {
        case 239:
        case 373:
            gflagInit();
            sampleModeDemoEndTimeOut();
        case 240:
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 37;
        }
    }
    return -1;
}
#else
int la_end_confirm(void)
{
    int item;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if (lt_fade_status() == 2 && (pad[0].flags & 0x40)) {
#else
    if (lt_fade_status() == 2 && (pad[0].flags & 0x10)) {
#endif
        NEGATIVE_SE();
        item = lt_current_property_item();
#ifdef VERSION_AUG6
        if (item >= 239) {
            if (item < 241) {
                lt_set_item_select_func(0);
                actionStarted = 0;
                return 37;
            }
            if (item < 375) {
                if (item >= 373) {
                    lt_set_item_select_func(0);
                    actionStarted = 0;
                    return 53;
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        if (item >= 241) {
            if (item < 243) {
#else
        if (item >= 247) {
            if (item < 249) {
#endif
#else
        if (item >= 270) {
            if (item < 272) {
#endif
                lt_set_item_select_func(0);
                actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
                return 0x26;
#else
                return 0x29;
#endif
            }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
            if (item < 397) {
                if (item >= 395) {
#else
            if (item < 403) {
                if (item >= 401) {
#endif
#else
            if (item < 426) {
                if (item >= 424) {
#endif
                    lt_set_item_select_func(0);
                    actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
                    return 0x36;
#else
                    return 0x39;
#endif
#endif
                }
            }
        }
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if (pad[0].flags & 0x20) {
#else
    if (pad[0].flags & 0x40) {
#endif
        debug_StdPrintfDummy("%d\n", lt_current_property_item());
        switch (lt_current_property_item()) {
#ifdef VERSION_AUG6
        case 239:
        case 373:
            POSITIVE_SE();
            gflagInit();
            nextStage = 1;
            stgmgrForceSwitchWithFade(1, 0.025f, 4.0f);
        case 240:
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        case 241:
        case 395:
#else
        case 247:
        case 401:
#endif
#else
        case 270:
        case 424:
#endif
            POSITIVE_SE();
            optionScreenMode = 0;
            gflagInit();
            fightSoundProcessRequestPause();
            fightSoundClose();
            soundDataSegAllClose(0, 2);
            nextStage = 1;
            stgmgrForceSwitchWithFade(1, 0.025f, 4.0f);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        case 242:
#else
        case 248:
#endif
#else
        case 271:
#endif
#endif
            NEGATIVE_SE();
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
            return 0x26;
        case 396:
#else
            return 0x26;
        case 402:
#endif
#else
#ifdef VERSION_AUG6
            return 37;
        case 374:
#else
            return 0x29;
        case 425:
#endif
#endif
            NEGATIVE_SE();
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x36;
#else
#ifdef VERSION_AUG6
            return 53;
#else
            return 0x39;
#endif
#endif
        }
    }
    return -1;
}
#endif
#endif

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
static int deleteStep = 0; /* derived name */
#endif

inline int la_save_confirm_yesno(void)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if (pad[0].flags & 0x40) {
#else
#ifdef VERSION_JUN26
    if (PSH_NEGATIVE(0)) {
#else
    if (pad[0].flags & 0x10) {
#endif
#endif
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
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x1B;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 26;
#else
        return 0x1E;
#endif
#endif
    case 1:
        if ((curPortInfo->fileMask >> selectFile) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x2E;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 45;
#else
            return 0x31;
#endif
#endif
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x1E;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 29;
#else
        return 0x21;
#endif
#endif
    }
    return -1;
}

inline int la_delete_confirm(int first, int item)
{
    switch (item) {
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    case 183:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 46;
    case 184:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 26;
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
    case 184:
#else
    case 190:
#endif
#else
    case 214:
#endif
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        return 0x2F;
    case 185:
#else
        return 0x2F;
    case 191:
#endif
#else
        return 0x32;
    case 215:
#endif
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x1B;
#else
        return 0x1E;
#endif
#endif
    }
    return -1;
}

#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
static int deleteStep = 0; /* derived name */
#endif

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
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x30;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 47;
#else
        return 0x33;
#endif
#endif
    }
    return -1;
}

inline int la_delete_confirm_complete(void)
{
#ifdef VERSION_JUN26
    if (PSH_NEGATIVE(0)) {
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 26;
    }
    return -1;
#else
    int ret;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if ((pad[0].flags & 0x40) == 0)
        goto fail;
#else
    if ((pad[0].flags & 0x10) == 0)
        goto fail;
#endif
    lt_set_item_select_func(0);
    actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    ret = 0x1B;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    ret = 26;
#else
    ret = 0x1E;
#endif
#endif
    goto out;
fail:
    ret = -1;
out:
    return ret;
#endif
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

#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
inline void la_playtime_count(void)
{
    if (systemStatus[5] == 0) {
#ifdef VERSION_NTSC
        IosMcPreviewInfo[1]++;
#else
        IosMcPreviewInfo[2]++;
#endif
    }
}
#endif

/* inlined into la_game_loop and into la_game_over_continue */
static inline void releaseGameLoopCursor(void) /* derived name */
{
    if (layoutVoice != 0 && layoutVoice->stream != 0) {
        layoutVoice->stream->fadeStep = 0x100;
    }
    layoutVoice = 0;
}

#ifdef VERSION_JUN26
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
                nextStage = gFlagSaveStage;
                releaseGameLoopCursor();
                lt_set_item_select_func(0);
                actionStarted = 0;
                return 59;
            }
            break;
        case 379:
            if (PSH_POSITIVE(0)) {
                gflagInit();
                sampleModeDemoEndTimeOut();
            }
            break;
        }
    }
    return -1;
}
#else
int laoutActionPauseRequest = 0;

#ifdef VERSION_NTSC
int la_game_loop(int first)
{
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
    if (layoutActPushStartNew != 0) {
        laoutActionPauseRequest++;
    } else {
        laoutActionPauseRequest = 0;
    }
    if ((startStagePauseDisableTimer >= 11 && (pad[0].flags & 0x800)) ||
        (float)laoutActionPauseRequest >
            (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 0.5f) {
        if (enable_game_pause == 0) {
            return -1;
        }
        if (gflagChk(307) != 0) {
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

static int gameOverVoiceOpened = 0; /* derived name */

inline int la_game_demo(int first)
{
    if (first) {
        if (stage_no == 1) {
            iosPadDisable();
        }
    }
    if ((pad[0].flags & 0x800) && gflagChk(355)) {
        debug_StdPrintfDummy("push start\n");
        gflagOff(355);
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
        iosPadActStopAll();
    }
    if (lt_fade_status() != 2) {
        return -1;
    }
    if (((pad[0].flags & 0x40) && lt_current_property_item() == 264) || (pad[0].flags & 0x810)) {
        NEGATIVE_SE(0);
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
        enable_game_pause = 1;
        iosPadEnable();
        scpBoyControlReadDisable = 0;
        systemStatus[5] = 1;
        AdpcmFadeCloseAll(0x200);
        soundSePlayModeStop(1);
        soundSePlayModeStop(0);
        iosPadActStopAll();
        gameOverVoiceOpened = 0;
    } else if (gameOverVoiceOpened == 0) {
        if (AdpcmFreeAreaGet() != 0) {
            gameOverVoice = openLayoutVoice(50);
            gameOverVoiceOpened = 1;
        }
    } else if (gameOverVoice != 0) {
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
            if ((pad[0].flags & 0x40) == 0) {
                return -1;
            }
            POSITIVE_SE();
            systemStatus[4] = 1;
            nextStage = gFlagSaveStage;
            releaseGameLoopCursor();
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 59;
        case 379:
            if ((pad[0].flags & 0x40) == 0) {
                return -1;
            }
            POSITIVE_SE();
            gflagInit();
            nextStage = 1;
            releaseGameLoopCursor();
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 59;
        }
    }
    return -1;
}
#else
int la_game_loop(int first)
{
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    IosMcPreviewInfo[1]++;
#endif
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
    if (layoutActPushStartNew != 0) {
        laoutActionPauseRequest++;
    } else {
        laoutActionPauseRequest = 0;
    }
    if ((startStagePauseDisableTimer >= 11 && (pad[0].flags & 0x800)) ||
        (float)laoutActionPauseRequest >
            (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 0.5f) {
        if (enable_game_pause == 0) {
            return -1;
        }
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        if (gflagChk(306) != 0) {
#else
        if (gflagChk(338) != 0) {
#endif
            return -1;
        }
        systemStatus[5] = 1;
        layoutActPushStartNew = 0;
        adpcmPauseRequest(1);
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x36;
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 53;
    }
    return -1;
}

static int gameOverVoice = 0; /* derived name */

static int gameOverVoiceOpened = 0; /* derived name */

inline int la_game_demo(int first)
{
    if (first) {
        if (stage_no == 1) {
            iosPadDisable();
        }
    }
    if ((pad[0].flags & 0x800) && gflagChk(354)) {
        debug_StdPrintfDummy("push start\n");
        gflagOff(354);
        title_demo_mode ^= 1;
        nextStage = stage_after_skipping_demo;
        stgmgrForceSwitchWithFade(nextStage, 8.0f, 4.0f);
        if (stage_after_skipping_demo == 0xFFFFFFFF) {
            stage_after_skipping_demo = 1;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 59;
#else
        return 0x39;
#endif
#endif
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
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    return 51;
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    return 0x34;
#else
    return 0x37;
#endif
}

inline int la_game_demo(int first)
{
    if (first) {
        if (stage_no == 1) {
            iosPadDisable();
        }
    }
    if ((pad[0].flags & 0x800) && gflagChk(388)) {
        debug_StdPrintfDummy("push start\n");
        gflagOff(388);
        title_demo_mode ^= 1;
        nextStage = stage_after_skipping_demo;
        stgmgrForceSwitchWithFade(nextStage, 8.0f, 4.0f);
        if (stage_after_skipping_demo == 0xFFFFFFFF) {
            stage_after_skipping_demo = 1;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x3C;
#else
        return 0x3F;
#endif
    }
    return -1;
#endif
}

inline int la_game_pause(int first)
{
    if (first) {
        systemStatus[5] = 1;
#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
        iosPadActStopAll();
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        texLayout[55].defaultItem = 279;
#else
        texLayout[55].defaultItem = 285;
#endif
#else
        texLayout[58].defaultItem = 308;
#endif
#endif
    }
    if (lt_fade_status() != 2) {
        return -1;
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
    if (((pad[0].flags & 0x20) && lt_current_property_item() == 266) || (pad[0].flags & 0x840)) {
#else
    if (((pad[0].flags & 0x20) && lt_current_property_item() == 272) || (pad[0].flags & 0x840)) {
#endif
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    if (((pad[0].flags & 0x40) && lt_current_property_item() == 264) || (pad[0].flags & 0x810)) {
#else
    if (((pad[0].flags & 0x40) && lt_current_property_item() == 295) || (pad[0].flags & 0x810)) {
#endif
#endif
        NEGATIVE_SE(0);
        adpcmPauseRequest(0);
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x33;
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        return 50;
#else
        return 0x36;
#endif
#endif
    }
    return -1;
}

#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
static int gameOverVoice = 0; /* derived name */

static int gameOverVoiceOpened = 0; /* derived name */
#endif

int la_game_over_continue(int first)
{
    if (first) {
#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
        if (fadeStatus != 0) {
            scpFadeIn(3.0f);
        }
#endif
        enable_game_pause = 1;
        iosPadEnable();
        scpBoyControlReadDisable = 0;
        systemStatus[5] = 1;
        AdpcmFadeCloseAll(0x200);
#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
        AdpcmNotUseIopAreaFree();
#endif
        soundSePlayModeStop(1);
        soundSePlayModeStop(0);
        iosPadActStopAll();
        gameOverVoiceOpened = 0;
    } else if (gameOverVoiceOpened == 0) {
        if (AdpcmFreeAreaGet() != 0) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
            gameOverVoice = openLayoutVoice(50);
#else
            gameOverVoice = openLayoutVoice(0x34);
#endif
            gameOverVoiceOpened = 1;
        }
    } else if (gameOverVoice != 0) {
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
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        case 400:
            if ((pad[0].flags & 0x20) == 0 || lt_fade_status() != 2) {
#else
        case 406:
            if ((pad[0].flags & 0x20) == 0 || lt_fade_status() != 2) {
#endif
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
        case 378:
            if ((pad[0].flags & 0x40) == 0) {
#else
        case 429:
            if ((pad[0].flags & 0x40) == 0 || lt_fade_status() != 2) {
#endif
#endif
                return -1;
            }
            POSITIVE_SE();
            systemStatus[4] = 1;
            nextStage = gFlagSaveStage;
            releaseGameLoopCursor();
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
            return 0x3C;
        case 401:
            if ((pad[0].flags & 0x20) == 0 || lt_fade_status() != 2) {
#else
            return 0x3C;
        case 407:
            if ((pad[0].flags & 0x20) == 0 || lt_fade_status() != 2) {
#endif
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 59;
        case 379:
            if ((pad[0].flags & 0x40) == 0) {
#else
            return 0x3F;
        case 430:
            if ((pad[0].flags & 0x40) == 0 || lt_fade_status() != 2) {
#endif
#endif
                return -1;
            }
            POSITIVE_SE();
#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
            optionScreenMode = 0;
#endif
            gflagInit();
            nextStage = 1;
            releaseGameLoopCursor();
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 0x3C;
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 59;
#else
            return 0x3F;
#endif
#endif
        }
    }
    return -1;
}
#endif
#endif

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
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        lt_mask_property(i + 313, 1);
        lt_default_mask_property(i + 313, 1);
#else
        lt_mask_property(i + 319, 1);
        lt_default_mask_property(i + 319, 1);
#endif
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        lt_mask_property(i + 291, 1);
        lt_default_mask_property(i + 291, 1);
#else
        lt_mask_property(i + 342, 1);
        lt_default_mask_property(i + 342, 1);
#endif
#endif
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

#ifdef VERSION_NTSC
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
            POSITIVE_SE();
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
    if (pad[0].flags & 0x40) {
        if (lt_current_property_item() == 340) {
            for (i = 7; i >= 0; i--) {
                keyConfigSlot[i] = i;
            }
            NEGATIVE_SE();
        }
        if (lt_current_property_item() == 339) {
            POSITIVE_SE();
            for (i = 0; i < 16; i++) {
                if ((keyConfigMask >> i) & 1) {
                    iosPadConfCustom.bit[i] = 0;
                } else {
                    iosPadConfCustom.bit[i] = 1 << i;
                }
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
    if ((pad[0].flags & 0x40) != 0) {
        switch (lt_current_property_item()) {
        case 269:
            POSITIVE_SE();
            if (mode == 0) {
                mode = 1;
            } else {
                mode = 0;
            }
            soundOutputModeSet(mode);
            break;
        case 274:
            POSITIVE_SE();
            iosPadActRequestEnable ^= 1;
            break;
        case 281:
            NEGATIVE_SE();
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 53;
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
#else
int la_key_config(int first)
{
    int i;
    int sel;
    int m;
    int k;
    int n;

#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
    sel = lt_current_property_item() - 285;
    if (first) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
    sel = lt_current_property_item() - 307;
#else
    sel = lt_current_property_item() - 313;
#endif
#else
    sel = lt_current_property_item() - 336;
#endif
    if (first) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        texLayout[55].defaultItem = 294;
#else
        texLayout[55].defaultItem = 300;
#endif
#else
        texLayout[58].defaultItem = 323;
#endif
#endif
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
#ifndef VERSION_JUN26
            POSITIVE_SE();
#endif
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
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
#ifdef VERSION_JUN26
        lt_mask_property(i * 8 + 291 + keyConfigSlot[i], 0);
    }
    if (PSH_POSITIVE(0)) {
        if (lt_current_property_item() == 340) {
#else
        lt_mask_property(i * 8 + 291 + keyConfigSlot[i], 0);
    }
    if (pad[0].flags & 0x40) {
        if (lt_current_property_item() == 340) {
#endif
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        lt_mask_property(i * 8 + 313 + keyConfigSlot[i], 0);
        lt_default_mask_property(i * 8 + 313 + keyConfigSlot[i], 0);
#else
        lt_mask_property(i * 8 + 319 + keyConfigSlot[i], 0);
        lt_default_mask_property(i * 8 + 319 + keyConfigSlot[i], 0);
#endif
#else
        lt_mask_property(i * 8 + 342 + keyConfigSlot[i], 0);
        lt_default_mask_property(i * 8 + 342 + keyConfigSlot[i], 0);
#endif
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
    if (pad[0].flags & 0x20) {
        if (lt_current_property_item() == 362) {
#else
    if (pad[0].flags & 0x20) {
        if (lt_current_property_item() == 368) {
#endif
#else
    if (pad[0].flags & 0x40) {
        if (lt_current_property_item() == 391) {
#endif
#endif
            for (i = 7; i >= 0; i--) {
                keyConfigSlot[i] = i;
            }
#ifdef VERSION_JUN26
        }
        if (lt_current_property_item() == 339) {
            for (i = 0; i < 16; i++) {
                iosPadConfCustom.bit[i] = 0;
#else
            NEGATIVE_SE();
        }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        if (lt_current_property_item() == 361) {
#else
        if (lt_current_property_item() == 367) {
#endif
#else
#ifdef VERSION_AUG6
        if (lt_current_property_item() == 339) {
#else
        if (lt_current_property_item() == 390) {
#endif
#endif
            POSITIVE_SE();
            for (i = 0; i < 16; i++) {
                if ((keyConfigMask >> i) & 1) {
                    iosPadConfCustom.bit[i] = 0;
                } else {
                    iosPadConfCustom.bit[i] = 1 << i;
                }
#endif
            }
            for (i = 0; i < 8; i++) {
                iosPadConfCustom.bit[keyBitIndex(keyConfigCode[keyConfigSlot[i]])] =
                    keyConfigCode[i];
            }
            keyconfigMaskAll();
            for (i = 0; i < 6; i++) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
                lt_default_mask_property(i * 8 + 313 + keyConfigSlot[i], 0);
                lt_mask_property(i * 8 + 313 + keyConfigSlot[i], 0);
#else
                lt_default_mask_property(i * 8 + 319 + keyConfigSlot[i], 0);
                lt_mask_property(i * 8 + 319 + keyConfigSlot[i], 0);
#endif
#else
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
                lt_default_mask_property(i * 8 + 291 + keyConfigSlot[i], 0);
                lt_mask_property(i * 8 + 291 + keyConfigSlot[i], 0);
#else
                lt_default_mask_property(i * 8 + 342 + keyConfigSlot[i], 0);
                lt_mask_property(i * 8 + 342 + keyConfigSlot[i], 0);
#endif
#endif
            }
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
            return 54;
        }
    }
    if (pad[0].flags & 0x800) {
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 50;
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 55;
#else
            return 58;
#endif
        }
#endif
    }
    return -1;
}

#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
/* the option screen's layout items: the five screen modes, the stage
   animation each mode plays (-1 for none), and the two choices of the control
   type (item 318, JPN and CN 295, KOR 289) followed by the two of the setting item 325 (JPN and CN 302, KOR
   296) toggles, in one
   table; the code reaches the second pair through an offset pointer */
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
static const int screenModeItem[5] = {274, 275, 276, 277, 278}; /* derived name */
#else
static const int screenModeItem[5] = {280, 281, 282, 283, 284}; /* derived name */
#endif
#else
static const int screenModeItem[5] = {303, 304, 305, 306, 307}; /* derived name */
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
static const int screenModeAnim[5] = {-1, 63, 64, 65, 66}; /* derived name */
#else
static const int screenModeAnim[5] = {-1, 67, 68, 69, 70}; /* derived name */
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
static const int choiceItem[4] = {292, 293, 299, 300}; /* derived name */
#else
static const int choiceItem[4] = {298, 299, 305, 306}; /* derived name */
#endif
#else
static const int choiceItem[4] = {321, 322, 328, 329}; /* derived name */
#endif
#endif

int la_game_option(void)
{
    int mode;
#ifdef VERSION_JUN26

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
#else
#ifdef VERSION_AUG6

    mode = soundOutputModeGet();
    if ((pad[0].flags & 0x40) != 0) {
        switch (lt_current_property_item()) {
        case 269:
            POSITIVE_SE();
            if (mode == 0) {
                mode = 1;
            } else {
                mode = 0;
            }
            soundOutputModeSet(mode);
            break;
        case 274:
            POSITIVE_SE();
            iosPadActRequestEnable ^= 1;
            break;
        case 281:
#else
    int cur;
    int sel;
    int item;

    mode = soundOutputModeGet();
    lt_analog2Pad();
    if ((pad[0].now & 0xA000) != 0) {
        cur = optionControlType;
        sel = optionScreenMode;
        switch (lt_current_property_item()) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        case 271:
#else
        case 277:
#endif
#else
        case 300:
#endif
            if ((pad[0].flags & 0x8000) != 0) {
                sel--;
                if (sel < 0) {
                    sel = 4;
                }
                CUR_SE();
            } else if ((pad[0].flags & 0x2000) != 0) {
                sel++;
                if (sel >= 5) {
                    sel = 0;
                }
                CUR_SE();
            }
            break;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        case 289:
#else
        case 295:
#endif
#else
        case 318:
#endif
            if ((pad[0].flags & 0xA000) != 0) {
                cur = cur == 0;
                CUR_SE();
            }
            break;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        case 284:
#else
        case 290:
#endif
#else
        case 313:
#endif
            if ((pad[0].flags & 0xA000) != 0) {
                iosPadActRequestEnable = iosPadActRequestEnable == 0;
                CUR_SE();
            }
            break;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        case 279:
#else
        case 285:
#endif
#else
        case 308:
#endif
            if ((pad[0].flags & 0xA000) != 0) {
                if (mode == 1) {
                    mode = 0;
                } else {
                    mode = 1;
                }
                soundOutputModeSet(mode);
                CUR_SE();
            }
            break;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        case 296:
#else
        case 302:
#endif
#else
        case 325:
#endif
            if ((pad[0].flags & 0xA000) != 0) {
                girlControlMode = girlControlMode == 0;
                CUR_SE();
            }
            break;
        }
        if (sel != optionScreenMode) {
            if (screenModeAnim[optionScreenMode] != -1) {
                stage_SetLoopFlag(screenModeAnim[optionScreenMode], 0);
                stage_SetAnimation(screenModeAnim[optionScreenMode], -1, -2);
            }
            item = screenModeAnim[sel];
            if (item != -1) {
                stage_SetLoopFlag(item, 1);
                stage_SetAnimation(item, 1, 0);
            }
            optionScreenMode = sel;
        }
        optionControlType = cur;
    }
    for (sel = 0; sel < 5; sel++) {
        lt_default_mask_property(screenModeItem[sel], 1);
    }
    lt_default_mask_property(screenModeItem[optionScreenMode], 0);
    for (sel = 0; sel < 2; sel++) {
        lt_default_mask_property(choiceItem[sel], 1);
    }
    lt_default_mask_property(choiceItem[optionControlType], 0);
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
    if ((pad[0].flags & 0x20) != 0) {
        if (lt_current_property_item() == 301) {
#else
    if ((pad[0].flags & 0x20) != 0) {
        if (lt_current_property_item() == 307) {
#endif
#else
    if ((pad[0].flags & 0x40) != 0) {
        if (lt_current_property_item() == 330) {
#endif
#endif
            NEGATIVE_SE();
            lt_set_item_select_func(0);
            actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            return 54;
#else
#ifdef VERSION_AUG6
            return 53;
#else
            return 57;
#endif
#endif
#endif
        }
    }
    if (mode == 0) {
#if defined(VERSION_AUG6) || defined(VERSION_JUN26)
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
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        lt_default_mask_property(282, 0);
        lt_default_mask_property(283, 1);
#else
        lt_default_mask_property(288, 0);
        lt_default_mask_property(289, 1);
#endif
#else
        lt_default_mask_property(311, 0);
        lt_default_mask_property(312, 1);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        lt_default_mask_property(282, 1);
        lt_default_mask_property(283, 0);
#else
        lt_default_mask_property(288, 1);
        lt_default_mask_property(289, 0);
#endif
#else
        lt_default_mask_property(311, 1);
        lt_default_mask_property(312, 0);
#endif
    }
    if (iosPadActRequestEnable != 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        lt_default_mask_property(287, 0);
        lt_default_mask_property(288, 1);
#else
        lt_default_mask_property(293, 0);
        lt_default_mask_property(294, 1);
#endif
#else
        lt_default_mask_property(316, 0);
        lt_default_mask_property(317, 1);
#endif
    } else {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        lt_default_mask_property(287, 1);
        lt_default_mask_property(288, 0);
#else
        lt_default_mask_property(293, 1);
        lt_default_mask_property(294, 0);
#endif
#else
        lt_default_mask_property(316, 1);
        lt_default_mask_property(317, 0);
#endif
    }
    for (sel = 0; sel < 2; sel++) {
        lt_default_mask_property((choiceItem + 2)[sel], 1);
    }
    lt_default_mask_property((choiceItem + 2)[girlControlMode], 0);
#endif
    return -1;
}
#endif

/* inlined once, into la_adjust_screen */
static inline void clearAdjustScreenMarks(void) /* derived name */
{
    int i;

    for (i = 0; i < 15; i++) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
        lt_default_mask_property(i + 366, 1);
#else
        lt_default_mask_property(i + 372, 1);
#endif
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
        lt_default_mask_property(i + 344, 1);
#else
        lt_default_mask_property(i + 395, 1);
#endif
#endif
    }
}

int la_adjust_screen(void)
{
#ifdef VERSION_JUN26
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
#else
    int v;

#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
    texLayout[55].defaultItem = 295;
#else
    texLayout[55].defaultItem = 301;
#endif
#else
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
    texLayout[58].defaultItem = 324;
#endif
#endif
    lt_analog2Pad();
    if (pad[0].flags & 0x8000) {
        v = systemStatus[11];
        if (v > 0) {
            CUR_SE();
            systemStatus[11] = v - 1;
        }
    } else if (pad[0].flags & 0x2000) {
        v = systemStatus[11];
        if (v < 14) {
            CUR_SE();
            systemStatus[11] = v + 1;
        }
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if (pad[0].flags & 0x40) {
#else
    if (pad[0].flags & 0x10) {
#endif
        NEGATIVE_SE();
#endif
        systemStatus[11] = 7;
    }
    clearAdjustScreenMarks();
#ifdef VERSION_JUN26
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
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
#ifdef VERSION_KOR
    lt_default_mask_property(systemStatus[11] + 366, 0);
    if (pad[0].flags & 0x20) {
#else
    lt_default_mask_property(systemStatus[11] + 372, 0);
    if (pad[0].flags & 0x20) {
#endif
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    lt_default_mask_property(systemStatus[11] + 344, 0);
#else
    lt_default_mask_property(systemStatus[11] + 395, 0);
#endif
    if (pad[0].flags & 0x40) {
#endif
        POSITIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
        return 0x37;
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        return 54;
#else
        return 0x3A;
#endif
#endif
#endif
    }
    return -1;
}

unsigned int stage_after_skipping_demo = 0;

int layoutActPushStartNew = 0;
