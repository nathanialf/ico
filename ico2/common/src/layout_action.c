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

/* the custom key map's sixteen pad button codes (iosPadConfCustom.bit),
   the default one bit per button */
typedef struct {
    int code[16];
} KeyConf;

/* The port record's flag word is reached through a union member: the ROM's
   codegen at layout_action.c:1128 proves that store is an alias-set-0 access
   (it kills the cached curPortInfo load, which a plain scalar field store does
   not).  RECONSTRUCTION: the word member and a one-bit view of the low bits,
   the names ours.  Re-audit (completeness pass 57): a plain struct member
   changes the object, and reading bits 1 and 3..5 through a bit-field view in
   currentPortLockState's test changes the object, so that test reads the
   word.  The bit view is attested by _la_set_current_port_new (chain 3 pass
   145): its last test compares bit 1 against a register holding 1, which a
   shift-and-mask compare cannot give (fold rewrites (x & 1) != 1 as
   (x & 1) == 0), and it stores bits 2 and 6 of both ports with port 1 first
   on one listing line, the chained bit-field assignment.  The bytes show
   bits 1, 2, 5 and 6 used this way; the other fields fill the low byte. */
typedef union {
    unsigned int w;

    struct {
        unsigned int f0 : 1;
        unsigned int f1 : 1;
        unsigned int f2 : 1;
        unsigned int f3 : 1;
        unsigned int f4 : 1;
        unsigned int f5 : 1;
        unsigned int f6 : 1;
    } bit;
} R8Flags;

typedef struct {
    R8Flags _0;
    int _4;
} R8;

/* the five-word save preview record */
struct S14 {
    int w[5];
};

/* .sbss, layout_action.o's thirteen words in the ROM's order (MAIN.MAP line
   7618 gives the January object's 0x30 bytes and no symbol, so the names are
   ours): the port-0 lock state _la_set_current_port_2 records and the one
   _la_set_current_port_lock_2 records, the lock results for port 0 and port 1
   of _la_set_current_port_new, the icoMisc lock saved by the logo, the title
   continue and the title new game actions, the progress bar's last step, the
   save select's ready flag, the system save's retry count, the last card
   result, the load (1) or save (0) mode of the file select, and the progress
   bar's total. */
static int portLockState;

static int lock2PortState;

static int port0LockResult;

static int port1LockResult;

static int logoIcoMiscLock;

static int continueIcoMiscLock;

static int newGameIcoMiscLock;

static int barLastStep;

static int saveSelectReady;

static int systemSaveRetry;

static int mcLastResult;

static int mcLoadMode;

static int barTotal;

/* .bss, layout_action.o's objects in the ROM's order (MAIN.MAP line 7739, no
   symbol; the names are ours): the two card ports' records, the preview
   record of the save being confirmed, the open request of the layout voice
   and the twenty game flags kept across a load. */
static R8 mcPortInfo[2]; /* derived name */

static struct S14 previewInfo;

static AdpcmOpenReq voiceOpenReq;

static signed char keepFlags[20];

void POSITIVE_SE(void)
{
    soundSeDefPlay(412, 0xFFFFFFFE, 0, 0);
}

void NEGATIVE_SE()
{
    soundSeDefPlay(413, 0xFFFFFFFE, 0, 0);
}

void CUR_SE(void)
{
    soundSeDefPlay(411, 0xFFFFFFFE, 0, 0);
}

inline int PSH_POSITIVE_OR_NEGATIVE(int idx)
{
    int v = pad[idx].flags;
    if ((v & 0x40) != 0)
        goto one;
    if ((v & 0x10) == 0)
        goto zero;
one:
    return 1;
zero:
    return 0;
}

void la_TESTFUNCTION(void)
{
    debug_StdPrintfDummy("sync end\n");
}

/* .data, owned by layout_action.o and the first object of its run: the
   game-flag ids the load carries across gflagInit.  The ROM's list holds five
   ids and the key-config tables follow it; the keep/restore loops below walk
   twenty words. */
static int keepFlagNo[5] = {388, 384, 383, 385, 382}; /* derived name */

/* .data, owned by layout_action.o, after keepFlagNo: the eight pad button
   codes the key-config screen offers, and the six-plus-two slot assignments it
   edits. */
static int keyConfigCode[8] = {16, 128, 32, 64, 8, 2, 1, 4}; /* derived name */

static int keyConfigSlot[8] = {1, 2, 3, 4, 5, 0, 0, 0}; /* derived name */

/* .data, the last object of the run: the memory-card request block the
   layout actions drive (MAIN.MAP global).  The ROM places it on a 64-byte
   boundary after the key tables (MAIN.MAP too, at member offset 0x80), the
   alignment common/src/kanbanBoot.c's own request block carries. */
int mc[640] __attribute__((aligned(64))) = {0};

/* kept local: agrees with mcard.h, which this TU does not include (iosMcDelete, iosMcFormat, iosMcGetBlockSaveInfo, iosMcLoadGameBlock, iosMcLoadProductBlock, iosMcSaveGameBlock, iosMcSaveIconBlock, iosMcSaveProductBlock differ) */
extern int iosMcSync(unsigned long *a0);
extern int D_00534CC0[];

typedef struct {
    unsigned int _0;
    char _4[16];
} R14;

/* one card's save record; the bytes pin an alignment above 32 bits (the
   serial store keeps 0x1E4 out of the base), as the 16-aligned array at
   0x29B5F0 and its 0x1F0 stride do: a SIF DMA buffer for the card code */
typedef struct {
    R14 f[20];
    char pad190[80];
    int _1E0;
    int _1E4;
    char pad1E8[8];
} R1F0 __attribute__((aligned(16)));

/* kept local (mcard.h's entry points do not fit this file's calls): mcard.c's
   save records, read here as this file's R1F0, and its preview record */
extern R1F0 IosMcProductFile[];
/* kept local: agrees with mcard.h, which this TU does not include (iosMcGetBlockSaveInfo, iosMcLoadGameBlock differ) */
extern int IosMcPreviewInfo[];
extern int D_005343C8[];
extern int D_00534400[];
/* the custom pad configuration ios/pad.c owns; kept local: pad.h cannot
   declare it while camera-root.c declares it as a char array */
extern PadConf iosPadConfCustom;

/* the memory-card error messages, VMA 0x61D760..0x61D840 */

/* layout_action.c:762-806 in the listing.  The switch table is
   jtbl_0061D840 (17 arms, selector the card result at +0x10, cases -16..0). */
int _la_mcard_error_check(void *a0)
{
    char *w = (char *)a0;

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

/* the product-block file-name field, six bytes; every writer copies the
   TU's one "game." literal into it (VMA 0x63B510 in .sdata) */
typedef struct {
    char b[6];
} McName;

/* the memory-card work area the layout actions pass around; the ROM reorders a
   load of _8 across a store to the int mcLastResult, which only a typed
   struct field reference is free to do */
typedef struct {
    char _0[8];
    int _8;
    int _C;
    int _10;
    int _14;
    int _18;
    char pad1C[4];
    int _20;
    char pad24[32];
    int _44;
    char pad48[1076];
    McName _47C;
    char pad482[1342];
    long long _9C0;
} McWork;

/* file-local: nothing outside this TU calls it */
int _la_memory_card_check(McWork *p, int a1);
/* kept local: agrees with mcard.h, which this TU does not include (iosMcDelete, iosMcFormat, iosMcGetBlockSaveInfo, iosMcLoadGameBlock, iosMcLoadProductBlock, iosMcSaveGameBlock, iosMcSaveIconBlock, iosMcSaveProductBlock differ) */
extern int iosMcGetInfo(void *a0);
/* kept local: returns void here, int in mcard.h */
extern void iosMcLoadProductBlock(void *a0);
/* kept local: returns void here, int in mcard.h */
extern void iosMcGetBlockSaveInfo(void *a0);

/* .sdata, layout_action.o's run in the ROM's order (VMA 0x63B4D8..0x63B5F8,
   0x120 B; MAIN.MAP's January object is 0x10C): these ten statics, the three
   MAIN.MAP globals after them, then each function's own statics before it,
   with the short literals the functions emit between them.  The names of the
   statics are ours. */
static R8 *curPortInfo = &mcPortInfo[0]; /* derived name */

static int lastPort = -1; /* derived name */

static int curPort = 0; /* derived name */

static int curFile = 0; /* derived name */

static int selectFile = -1; /* derived name */

static int nextStage = 1; /* derived name */

static int fileMask = 0; /* derived name */

static int actionStarted = 0; /* derived name */

static int fightSoundStopped = 0; /* derived name */

static char *layoutVoice = 0; /* derived name */

int startStagePauseDisableTimer = 0;

int layout_boot_flag = 0;

int enable_game_pause = 1;

/* layout_action.c:853-1006 in the listing.  The switch table is jtbl_0061D8D0
   (24 arms over the memory-card step, cases 0..23; VMA 0x61D8D0..0x61D930). */
int _la_memory_card_check(McWork *p, int a1)
{
    int r;
    int i;

    curPortInfo = &mcPortInfo[p->_8];
    switch (a1) {
    case 0:
        curPortInfo->_4 = 0;
        p->_C = 0;
        memset(&mcPortInfo[p->_8], 0, 8);
        p->_10 = 0;
        iosMcGetInfo(p);
        mcLastResult = 0;
        /* the pointer form, not IosMcProductFile[p->_8]: the ROM's addu takes the
           scaled index first, which the subscript spelling does not give */
        (IosMcProductFile + p->_8)->_1E4 = 0;
        (IosMcProductFile + p->_8)->_1E0 = 0;
        a1++;
        break;
    case 10:
        iosMcLoadProductBlock(p);
        a1++;
        break;
    case 20:
        strcpy((char *)p + 0x47C, "game.");
        iosMcGetBlockSaveInfo(p);
        a1++;
        break;
    case 1:
    case 11:
    case 21:
        if (iosMcSync((unsigned long *)p)) {
            a1++;
        }
        break;
    case 12:
    case 22:
        r = _la_mcard_error_check(p);
        if (r > 0) {
            a1++;
        }
        switch (p->_10) {
        case -16:
        case -15:
        case -4:
            p->_10 = -14;
            a1 = 99;
            r = 0;
            break;
        }
        if (r >= 0) {
            return a1;
        }
        mcLastResult = p->_10;
        if (p->_10 == -9 || r == -2) {
            curPortInfo->_0.w = (int)curPortInfo->_0.w & ~0x20;
            curPortInfo->_0.w = (int)curPortInfo->_0.w & ~2;
            curPortInfo->_0.w = (int)curPortInfo->_0.w & ~1;
        }
        /* falls through */
    case 2:
        a1++;
        break;
    case 3:
        switch (p->_14) {
        case 0:
            return 99;
        case 1:
        case 3:
            curPortInfo->_0.w |= 1;
            return 99;
        case 2:
            curPortInfo->_0.w |= 3;
            break;
        }
        switch (p->_20) {
        case 0:
            return 99;
        case 1:
            curPortInfo->_0.w |= 8;
            break;
        }
        if (p->_18 >= 360) {
            curPortInfo->_0.w |= 0x10;
        } else {
            curPortInfo->_0.w = (int)curPortInfo->_0.w & ~0x10;
        }
        a1 = 10;
        break;
    case 13:
        a1 = 20;
        break;
    case 23:
        if (p->_44 >= 11) {
            debug_StdPrintfDummy(
                "debug_mcLoadMainBlock:既に設定された数以上のデータを保存してる\n");
        }
        for (i = 0; i < 10; i++) {
            if ((1 << i) & p->_9C0) {
                break;
            }
        }
        a1 = 99;
        if (i == 10) {
            break;
        }
        for (i = 0; i < 10; i++) {
            if (IosMcProductFile[p->_8].f[i]._0 != 0xFFFFFFFF) {
                break;
            }
        }
        if (i < 10) {
            if (p->_44 == 10) {
                curPortInfo->_0.w |= 0x20;
                curPortInfo->_4 = p->_9C0;
            }
        }
        break;
    }
    return a1;
}

/* layout_action.c:1027-1031 in the listing: inlined three times into
   _la_set_current_port_2 and once into _la_set_current_port_lock_2, so it is a
   static inline here; it has no symbol of its own in the ROM and no census row,
   and the name is descriptive. */
static inline int currentPortLockState(void)
{
    return (((curPortInfo->_0.w >> 1) & 1) && (curPortInfo->_0.w & 0x38) != 8) ? 1 : -1;
}

static int port2Step = 0; /* derived name */

static int port2SubStep = 0; /* derived name */

static int port2Changed = 0; /* derived name */

static int port2Locked = 0; /* derived name */

/* layout_action.c:1039-1150 in the listing.  The three inlined copies of
   currentPortLockState are the listing's line 1029 rows. */
int _la_set_current_port_2(void *p, int a1)
{
    R8 tmp;
    int r;
    int q = 0;

    if (a1 != 0) {
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
            port2Changed = (curPortInfo->_0.w >> 5) & 1;
            port2Locked = ((curPortInfo->_0.w >> 1) & 1) && (curPortInfo->_0.w & 0x38) != 8;
            /* listing line 1069: the whole 8-byte record is copied to the frame
               and never read again (the ROM ldl/ldr/sdl/sdr pair). */
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
                    r = curPortInfo->_0.w >> 5;
                    r &= 1;
                    if ((curPortInfo->_0.w >> 1) & 1) {
                        if ((curPortInfo->_0.w & 0x38) != 8) {
                            q = 1;
                        }
                    }
                    if (port2Locked != 0 && q != 0) {
                        mcPortInfo[0]._0.w |= 4;
                        mcPortInfo[1]._0.w |= 4;
                    }
                    if (port2Changed != 0 && r != 0) {
                        mcPortInfo[0]._0.w |= 0x40;
                        mcPortInfo[1]._0.w |= 0x40;
                    }
                    if (lastPort >= 0) {
                        curPort = lastPort;
                    } else if (port2Changed != 0) {
                        curPort = 0;
                    } else if ((curPortInfo->_0.w >> 5) & 1) {
                        curPort = 1;
                    }
                    break;
                case -1:
                    lastPort = r;
                    curPort = 0;
                    curPortInfo = &mcPortInfo[0];
                    curPortInfo->_0.w = (int)curPortInfo->_0.w & ~4;
                    curPortInfo->_0.w = (int)curPortInfo->_0.w & ~0x40;
                    break;
                }
                break;
            case -1:
                r = currentPortLockState();
                switch (r) {
                case 1:
                    curPort = r;
                    curPortInfo = &mcPortInfo[1];
                    curPortInfo->_0.w = (int)curPortInfo->_0.w & ~4;
                    curPortInfo->_0.w = (int)curPortInfo->_0.w & ~0x40;
                    break;
                case -1:
                    curPort = 0;
                    curPortInfo = &mcPortInfo[0];
                    if ((mcPortInfo[0]._0.w & 1) || (mcPortInfo[1]._0.w & 1)) {
                        mcPortInfo[0]._0.w |= 1;
                    }
                    if (((mcPortInfo[0]._0.w >> 1) & 1) || ((mcPortInfo[1]._0.w >> 1) & 1)) {
                        curPortInfo->_0.w |= 2;
                    }
                    curPortInfo->_0.w = (int)curPortInfo->_0.w & ~4;
                    curPortInfo->_0.w = (int)curPortInfo->_0.w & ~0x40;
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

/* layout_action.c:1157-1218 in the listing. */
int _la_set_current_port_lock_2(void *p, int a1)
{
    R8 tmp;
    int r;
    int a;
    int q;

    if (a1 != 0 || lock2Restart != 0) {
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
    lock2Changed = (curPortInfo->_0.w >> 5) & 1;
    lock2Locked = ((curPortInfo->_0.w >> 1) & 1) && (curPortInfo->_0.w & 0x38) != 8;
    tmp = *curPortInfo;
    switch (lock2PortState) {
    case 1:
        a = curPortInfo->_0.w >> 5;
        a &= 1;
        q = 0;
        if ((curPortInfo->_0.w >> 1) & 1) {
            if ((curPortInfo->_0.w & 0x38) != 8) {
                q = 1;
            }
        }
        if (lock2Locked != 0 && q != 0) {
            mcPortInfo[*(int *)((char *)p + 8)]._0.w |= 4;
        }
        if (lock2Changed != 0 && a != 0) {
            mcPortInfo[*(int *)((char *)p + 8)]._0.w |= 0x40;
        }
        _la_set_current_port_lock_2(p, 1);
        return 1;
    case -1:
        curPortInfo = &mcPortInfo[curPort];
        curPortInfo->_0.w = (int)curPortInfo->_0.w & ~4;
        curPortInfo->_0.w = (int)curPortInfo->_0.w & ~0x40;
        return -1;
    }
    return 0;
}

static int portNewStep = 0; /* derived name */

static int portNewRestart = 1; /* derived name */

/* layout_action.c:1222-1288 in the listing.  The switch table is jtbl_0061D930
   (5 arms, selector portNewStep, cases 0..4). */
int _la_set_current_port_new(McWork *p, int a1)
{
    int r = 0;
    int v;

    if (a1) {
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
        if (((mcPortInfo[0]._0.w >> 1) & 1) && ((mcPortInfo[1]._0.w >> 1) & 1))
            v = 1;
        else
            v = 0;
        mcPortInfo[0]._0.bit.f2 = mcPortInfo[1]._0.bit.f2 = v;
        if (((mcPortInfo[0]._0.w >> 5) & 1) && ((mcPortInfo[1]._0.w >> 5) & 1))
            v = 1;
        else
            v = 0;
        mcPortInfo[0]._0.bit.f6 = mcPortInfo[1]._0.bit.f6 = v;
        if (port0LockResult == 1) {
            curPort = 0;
            r = 1;
        } else if (port1LockResult == 1) {
            curPort = 1;
            r = 1;
        } else {
            if (((mcPortInfo[0]._0.w >> 1) & 1) == 0 && mcPortInfo[1]._0.bit.f1 == 1) {
                curPort = 1;
            } else {
                curPort = 0;
            }
            r = -1;
        }
        p->_8 = curPort;
        curPortInfo = &mcPortInfo[curPort];
        break;
    }
    return r;
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
    return 0x37;
}

inline int la_boot_no_memory_card(int a0, int a1)
{
    debug_StdPrintfDummy("no memoca\n");
    return a1;
}

inline int la_boot_no_free_area(int a0, int a1)
{
    debug_StdPrintfDummy("no free\n");
    return a1;
}

inline int la_boot_confirm_memory_card(void)
{
    if (pad[0].flags & 0x40) {
        return lt_link_layout(0);
    }
    return -1;
}

inline void keyconfig_reset(void)
{
    KeyConf def = {{0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x0200,
                    0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000}};

    *(KeyConf *)iosPadConfCustom.bit = def;
}

/* layout_action.c:1455-1490 in the listing. */
int la_vibe_select(void)
{
    if (lt_fade_status() == 2 && (pad[0].flags & 0x840)) {
        soundSeDefPlay(415, 0xFFFFFFFF, 0, 0);
        switch (lt_current_property_item()) {
        case 0x2C:
            iosPadActRequestEnable = 1;
            break;
        case 0x2D:
            iosPadActRequestEnable = 0;
            break;
        }
        if (titleAdpcm != 0) {
            ((AdpcmObj *)titleAdpcm)->stream->f44 = 0x80;
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
    if ((pad[0].flags & 0x10) == 0) {
        return -1;
    }
    NEGATIVE_SE();
    lt_set_item_select_func(0);
    actionStarted = 0;
    return 0xC;
}

inline int la_scei_logo(int a0)
{
    if (a0) {
        stgmgrNextStagePreLoadForceStageSet(0);
        logoIcoMiscLock = lock_execIcoMisc;
        systemStatus[5] = 1;
        iosPadEnable();
        isysGObjActiveLink(0, 0);
        gflagOff(386);
        if (layout_boot_flag == 0) {
            layout_boot_flag = 1;
        }
    }
    return -1;
}

int title_demo_mode = 0;

inline int la_title_demo(void)
{
    return -1;
}

static int continueDecided = 0; /* derived name */

/* layout_action.c:1579-1630 in the listing. */
int la_title_continue_or_new(int a0)
{
    if (a0) {
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
        lt_mask_property(0x31, 0);
        lt_mask_property(0x32, 0);
    } else {
        lt_item_select_disable = 1;
        lt_mask_property(0x31, 1);
        lt_mask_property(0x32, 1);
    }
    if (continueDecided != 0 && (pad[0].flags & 0x840) && lt_fade_status() == 2) {
        lt_continue_selected = 1;
        soundSeDefPlay(414, 0xFFFFFFFF, 0, 0);
        switch (lt_current_property_item()) {
        case 0x31:
            opTitleLogoMode = 2;
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x14;
        case 0x32:
            opTitleLogoMode = 2;
            gFlagGameClear = 0;
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 9;
        }
    }
    switch (_la_set_current_port_2(mc, a0)) {
    case 0:
        break;
    case 1:
        if ((curPortInfo->_0.w & 0x22) == 2) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0xD;
        }
        continueDecided = 1;
        break;
    case -1:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0xD;
    }
    return -1;
}

static int newGameDecided = 0; /* derived name */

/* layout_action.c:1647-1700 in the listing. */
int la_title_new_game_only(int a0)
{
    if (a0) {
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
        lt_mask_property(51, 0);
    } else {
        lt_item_select_disable = 1;
        lt_mask_property(51, 1);
    }
    if (newGameDecided != 0 && (pad[0].flags & 0x840) && lt_fade_status() == 2) {
        soundSeDefPlay(414, 0xFFFFFFFF, 0, 0);
        lt_continue_selected = 1;
        opTitleLogoMode = 2;
        gFlagGameClear = 0;
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 9;
    }
    switch (_la_set_current_port_2(mc, a0)) {
    case 0:
        break;
    case -1:
        newGameDecided = 1;
        break;
    case 1:
        if ((curPortInfo->_0.w >> 5) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0xC;
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

inline int la_mc_saved_file_select(int a0)
{
    int i = a0 - 0x3E;
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
        } else if (IosMcProductFile[filePort].f[i]._0 == 0xFFFFFFFF) {
            i++;
        }
        if (i < 0) {
            i += 10;
        }
        if (i >= 10) {
            i -= 10;
        }
    } while (IosMcProductFile[filePort].f[i]._0 == 0xFFFFFFFF);
    if (old != i) {
        CUR_SE();
    }
    return i + 0x3E;
}

extern int D_00534324[];

/* layout_action.c:1780-1786 in the listing: inlined into la_mc_file_select
   both directly and through mcFileNoOfPort below, so it is a static inline here; it
   has no symbol of its own in the ROM and no census row, and the name is
   descriptive.  The test is an `||` returning 0 (listing 1784/1785, the
   `return no;` on 1786 only ever lands in a delay slot): its drop-through
   label keeps jump.c from hoisting the zero, so both copies keep the ROM's
   branches and share one zero block. */
static inline int mcCurrentFileNo(void)
{
    int port = filePort;
    int no = (IosMcProductFile + port)->_1E0;
    if (mcPortInfo[port]._4 == 0 || IosMcProductFile[port].f[no]._0 == 0xFFFFFFFF)
        return 0;
    return no;
}

/* layout_action.c:1789-1794 in the listing: inlined once, into
   la_mc_file_select, so it is a static inline here too. */
static inline int mcFileNoOfPort(void)
{
    int port = filePort;

    if (loadSerial == (IosMcProductFile + port)->_1E4)
        return savedFileNo;
    return mcCurrentFileNo();
}

/* layout_action.c:1836-1912 in the listing. */
int la_mc_file_select(int a0)
{
    int i;

    curFile = lt_current_property_item() - 62;

    if (a0) {
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
        D_00534324[0] = curFile + 62;
        fileMoved = 1;
    }

    for (i = 0; i < 10; i++) {
        if (((fileMask >> i) & 1) && IosMcProductFile[filePort].f[i]._0 != 0xFFFFFFFF) {
            lt_mask_property(i + 62, 0);
            lt_mask_property(i + 52, 1);
        } else {
            lt_mask_property(i + 62, 1);
            lt_mask_property(i + 52, 0);
        }
    }

    previewInfo = *(struct S14 *)&IosMcProductFile[filePort].f[curFile];

    return (pad[0].flags & 0x50) ? curFile : -1;
}

/* layout_action.c:1924-1942 in the listing. */
void _la_mask_preview_info(void)
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

/* layout_action.c:826-841 in the listing: the play time of a save record
   split into hours, minutes and seconds and clamped to 99:59:59, inlined into
   _la_set_preview_info, la_load_processing and la_system_save_processing; it
   has no symbol of its own in the ROM and the name is ours.  Where the
   results are unused (the other two sites) only the frame rate and the
   divide checks survive, which is why their rows show 829-832 without the
   frame read (827) or the clamp (840). */
static inline void playTime(struct S14 *p, int *hour, int *min, int *sec)
{
    int frames = p->w[2];
    int fps = ((60 - systemStatus[0] * 10) / systemStatus[1]) * systemStatus[1];

    *sec = (frames / fps) % 60;
    *min = (frames / (fps * 60)) % 60;
    *hour = frames / (fps * 3600);
    if (*hour >= 100) {
        *hour = 99;
        *min = 59;
        *sec = 59;
    }
}

/* layout_action.c:1946-2012 in the listing, with the play-time split of lines
   827-840 inlined into it. */
void _la_set_preview_info(void)
{
    int hour;
    int min;
    int sec;
    int n;

    _la_mask_preview_info();

    if (((fileMask >> curFile) & 1) == 0) {
        return;
    }
    if (IosMcProductFile[filePort].f[curFile]._0 == 0xFFFFFFFF) {
        return;
    }

    playTime(&previewInfo, &hour, &min, &sec);

    hour = ((hour / 10 + 9) % 10) * 10 + (hour % 10 + 9) % 10;
    min = ((min / 10 + 9) % 10) * 10 + (min % 10 + 9) % 10;
    sec = ((sec / 10 + 9) % 10) * 10 + (sec % 10 + 9) % 10;

    lt_mask_property(76 + hour / 10, 0);
    lt_mask_property(86 + hour % 10, 0);
    lt_mask_property(96 + min / 10, 0);
    lt_mask_property(106 + min % 10, 0);
    lt_mask_property(116 + sec / 10, 0);
    lt_mask_property(126 + sec % 10, 0);
    lt_mask_property(74, 0);
    lt_mask_property(75, 0);

    n = previewInfo.w[0];
    if (n == 0x3F) {
        n = 38;
    }
    if (n >= 3 && n < 56) {
        switch (previewInfo.w[3]) {
        case 329:
            n = 39;
            break;
        case 331:
            n = 40;
            break;
        }
        lt_mask_property(n + 134, 0);
        if (previewInfo.w[1] != 0) {
            lt_mask_property(136, 0);
        }
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
    lt_mask_property(0xB0, curPort);
    lt_mask_property(0xB1, curPort ^ 1);
    return -1;
}

/* layout_action.c:1808-1814 in the listing: inlined once, into
   la_load_game_memory_card_check, so it is a static inline here; it has no
   symbol of its own in the ROM and no census row, and the name is descriptive. */
static inline void setLoadGameStartItem(void)
{
    if (loadSerial == IosMcProductFile[0]._1E4 || saveSerial != IosMcProductFile[1]._1E4) {
        D_005343C8[0] = 186;
    } else {
        D_005343C8[0] = 187;
    }
}

/* layout_action.c:2071-2102 in the listing. */
int la_load_game_memory_card_check(int a0)
{
    _la_mask_preview_info();
    mcLoadMode = 1;
    lt_mask_property(0xB0, 1);
    lt_mask_property(0xB1, 1);
    switch (_la_set_current_port_2(mc, a0)) {
    case 0:
        if (mcLastResult == 0 || mcLastResult == -14) {
            return -1;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x16;
    case -1:
        if ((curPortInfo->_0.w >> 1) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x17;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x16;
    case 1:
        if ((curPortInfo->_0.w >> 6) & 1) {
            setLoadGameStartItem();
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x11;
        }
        if ((curPortInfo->_0.w >> 5) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x13;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x17;
    }
    return -1;
}

inline int la_mc_load_current_slot_select(void)
{
    _la_mask_preview_info();
    if (pad[0].flags & 0x40) {
        curPort = lt_current_property_item() - 0xBA;
        lastPort = curPort;
        curPortInfo = &mcPortInfo[curPort];
        POSITIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x13;
    }
    if (pad[0].flags & 0x10) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0xC;
    }
    return -1;
}

/* the two load-select trace messages, VMA 0x63B570 and 0x63B578 (.sdata) */

static int loadCardChanged = 1; /* derived name */

static int loadFileChosen = 0; /* derived name */

/* layout_action.c:2139-2235 in the listing. */
int la_mc_load_file_select(int a0, int a1)
{
    int r;

    if (a0) {
        fileMask = 0;
        lastPort = filePort = curPort;
        loadFileChosen = 0;
    }

    if (fileMask != 0) {
        _la_set_preview_info();
        lt_mask_property(73, 1);
        lt_mask_property(72, 1);
        lt_mask_property(195, 0);
        lt_mask_property(196, 0);
    } else {
        _la_mask_preview_info();
        lt_mask_property(73, 0);
        lt_mask_property(72, 0);
        lt_mask_property(195, 1);
        lt_mask_property(196, 1);
    }
    lt_set_item_select_func((int)la_mc_saved_file_select);

    if (pad[0].flags & 0x10) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 12;
    }

    if ((fileMask != 0 || loadFileChosen != 0) && (pad[0].flags & 0x40)) {
        POSITIVE_SE();
        if (IosMcProductFile[filePort].f[a1]._0 != 0xFFFFFFFF) {
            selectFile = a1;
            lastPort = filePort;
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 21;
        }
    }

    r = _la_set_current_port_lock_2(mc, a0);
    switch (r) {
    case -1:
        if (((curPortInfo->_0.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 22;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 23;
    case 1:
        if (((curPortInfo->_0.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 22;
        }
        if ((curPortInfo->_0.w & 0x22) == 2) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 23;
        }
        break;
    case 0:
    default:
        return -1;
    }

    if (fileMask != 0) {
        if (loadCardChanged == 0) {
            if (((curPortInfo->_0.w >> 6) & 1) != 0) {
                debug_StdPrintfDummy("1 to 2\n");
                lt_set_item_select_func(0);
                actionStarted = 0;
                return 17;
            }
        } else if (((curPortInfo->_0.w >> 6) & 1) == 0) {
            debug_StdPrintfDummy("2 to 1\n");
            loadCardChanged = (curPortInfo->_0.w >> 6) & 1;
        }
    } else {
        loadCardChanged = (curPortInfo->_0.w >> 6) & 1;
        fileMask = curPortInfo->_4;
        actionStarted = r;
        if ((curPortInfo->_0.w & 0xA) == 2) {
            loadFileChosen = r;
        }
    }
    return -1;
}

/* layout_action.c:2245-2267 in the listing. */
int la_load_confirm_no_memory_card(int a0)
{
    if (a0) {
        _la_mask_preview_info();
    }
    if (PSH_POSITIVE_OR_NEGATIVE(0)) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0xD;
    }
    switch (_la_set_current_port_lock_2(mc, a0)) {
    case 0:
        break;
    case -1:
        if ((curPortInfo->_0.w & 0x32) == 2 || (curPortInfo->_0.w & 0x22) == 2) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x17;
        }
        if ((curPortInfo->_0.w >> 1) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x14;
        }
        lock2Restart = 1;
        break;
    case 1:
        if ((curPortInfo->_0.w & 0x32) == 2 || (curPortInfo->_0.w & 0x22) == 2) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x17;
        }
        if ((curPortInfo->_0.w >> 1) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x14;
        }
        break;
    }
    return -1;
}

/* layout_action.c:2276-2311 in the listing. */
int la_load_confirm_no_data(int a0)
{
    if (a0) {
        _la_mask_preview_info();
    }
    if (PSH_POSITIVE_OR_NEGATIVE(0)) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0xD;
    }
    switch (_la_set_current_port_lock_2(mc, a0)) {
    case 0:
        break;
    case -1:
        if (((curPortInfo->_0.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x16;
        }
        lock2Restart = 1;
        break;
    case 1:
        if ((curPortInfo->_0.w >> 5) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x14;
        }
        break;
    }
    return -1;
}

/* layout_action.c:2320-2352 in the listing. */
int la_load_start_check(int a0)
{
    switch (_la_set_current_port_lock_2(mc, a0)) {
    case 0:
        fileMask = 0x3FF;
        if (mcLastResult == 0 || mcLastResult == -14) {
            return -1;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x2E;
    case -1:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x2E;
    case 1:
        if (filePort != curPort) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x2E;
        }
        if ((curPortInfo->_0.w & 3) != 3) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x16;
        }
        if ((curPortInfo->_4 >> selectFile) & 1) {
            fileMask = 0x3FF;
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x19;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x17;
    }
    return -1;
}

/* the load-phase messages in .rodata, VMA 0x61D9A8..0x61DA30 */
/* "chk:%d\n" and "case 4\n", short strings in this TU's .sdata at VMA
   0x63B588 and 0x63B590 */

/* the current game's save record, as in la_system_save_processing */
/* kept local: returns void here, int in mcard.h */
extern void iosMcLoadGameBlock(void *a0, int a1);

/* layout_action.c:1796-1800 in the listing: the saved file's serial read
   from the port's record, with the file number kept beside it; inlined into
   la_load_processing directly and into la_save_processing through
   mcSetSavedFile, with no symbol of its own in the ROM (the name is ours). */
static inline int mcSetFileNo(int port, int no)
{
    int serial = (IosMcProductFile + port)->_1E4;

    savedFileNo = no;
    return serial;
}

/* layout_action.c:2370-2371 in the listing: the game flags the load carries
   across gflagInit, parked in keepFlags; inlined into la_load_processing, with
   no symbol of its own in the ROM (the name is ours).  The counter is
   unsigned: the ROM's guard is sltiu. */
static inline void gflagKeepState(void)
{
    unsigned int i;

    for (i = 0; i < 20; i++) {
        keepFlags[i] = gflagChk(keepFlagNo[i]);
    }
}

/* layout_action.c:2378-2382 in the listing, the other half of the pair. */
static inline void gflagRestoreState(void)
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

/* layout_action.c:2393-2536 in the listing, with the menu-close pair of lines
   707-708, the play time of lines 829-832, the flag-keeping pair of lines
   2370-2382 and the serial readback of lines 1798-1799 inlined into it.  The
   switch table is jtbl_0061DA40 (21 arms, selector loadStep, cases 0-10 and
   20). */
int la_load_processing(int a0)
{
    int err;
    int hour;
    int min;
    int sec;

    debug_StdPrintfDummy("load processing\n");
    if (a0) {
        loadStep = 0;
    }

    switch (loadStep) {
    case 0:
        strcpy((char *)mc + 0x47C, "game.");
        mc[16] = selectFile;
        mc[2] = curPort;
        mc[3] = 0;
        iosMcGetBlockSaveInfo(mc);
        loadStep++;
        break;
    case 1:
    case 3:
        if (iosMcSync((unsigned long *)mc) != 0) {
            loadStep++;
        }
        break;
    case 2:
        loadStep++;
        break;
    case 6:
    case 9:
        debug_StdPrintfDummy("case %d\n", loadStep);
        err = _la_mcard_error_check(mc);
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
        return 46;
    case 4:
        debug_StdPrintfDummy("case 4\n");
        if (((1 << mc[16]) & ((McWork *)mc)->_9C0) == 0) {
            loadStep = 20;
        } else {
            iosMcLoadProductBlock(mc);
            loadStep++;
        }
        break;
    case 5:
    case 8:
        debug_StdPrintfDummy("case %d\n", loadStep);
        if (iosMcSync((unsigned long *)mc) != 0) {
            loadStep++;
        }
        break;
    case 7:
        debug_StdPrintfDummy("case %d\n", loadStep);
        debug_StdPrintfDummy("=== LoadGameBlock ===\n");
        iosMcLoadGameBlock(mc, gameSysMainSaveBuff);
        loadStep++;
        break;
    case 10:
        gflagKeepState();
        gflagInit();
        gamesysMemoryLoad(gameSysMemoryFuncList, gameSysMainSaveBuff, 0);
        gflagRestoreState();
        systemStatus[3] = 1;
        systemStatus[4] = 1;
        debug_StdPrintfDummy("case 10\n");
        loadStep = 0;
        *(struct S14 *)IosMcPreviewInfo = *(struct S14 *)&IosMcProductFile[mc[2]].f[mc[16]];
        playTime((struct S14 *)IosMcPreviewInfo, &hour, &min, &sec);
        loadSerial = mcSetFileNo(mc[2], mc[16]);
        debug_StdPrintfDummy("stage no %d\n", gFlagSaveStage);
        seEnvForceClose = 1;
        if (titleAdpcm != 0) {
            ((AdpcmObj *)titleAdpcm)->stream->f44 = 0x40;
        }
        titleAdpcm = 0;
        if (gflagChk(395)) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 9;
        }
        stgmgrForceSwitchWithFade(gFlagSaveStage, 0.05f, 4.0f);
        ACTGame_SetActors_Debug(gFlagSaveStage, 0);
        return -1;
    case 20:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 20;
    }
    return -1;
}

inline int la_general_mc_confirm(void)
{
    if (pad[0].flags & 0x40) {
        return lt_current_property_item();
    }
    return -1;
}

/* layout_action.c:2565-2570 in the listing: inlined into la_game_over_continue
   and into la_mc_confirm_save_file with different data numbers, so the number is
   its parameter; it is a static inline here, with no symbol of its own in the
   ROM and no census row, and the name is descriptive. */
static inline int openLayoutVoice(int no)
{
    if (layoutVoice != 0) {
        return 0;
    }
    soundDataOpen(&voiceOpenReq, 2, no, 1, 0);
    return 1;
}

/* layout_action.c:2591-2678 in the listing. */
/* extra preview pages to re-mask; none in the release build */
#define LA_EXTRA_PREVIEW_PAGES 0

static int saveVoice = 0; /* derived name */

static int saveVoiceOpened = 0; /* derived name */

static int saveVoiceWait = 0; /* derived name */

int la_mc_confirm_save_file(int a0, int a1)
{
    int i;

    _la_mask_preview_info();
    lt_mask_property(0xB0, 1);
    lt_mask_property(0xB1, 1);
    if (a0) {
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
        /* RECONSTRUCTION: the ROM pads 0x1BBF5C with a nop so that the label
           at 0x1BBF60 (listing line 2663) is 8-aligned, the alignment final.c
           gives the first label after a loop-begin note, so a once-run loop
           began in the window between the else label and the voice-open test
           (a loop there that holds any of the test's exits reorders it; chain 3
           pass 145 measured each).  The call on line 2637 is the only code in
           that window and the listing's lines 2638-2639 carry none; the bytes
           pin the loop, not the wrapper's spelling. */
        _la_mask_preview_info();
        /* A loop over extra preview pages, built with a count of 0 in the
           release build.  WHAT THE BYTES PIN: the loop-begin note of a loop
           here, which aligns the label after it (the ROM's pad nop); its body
           never runs, so it leaves no code (listing rows 2638-2639 are
           code-free).  WHAT THEY CANNOT PIN: what the loop counted or did;
           the count's name and the body are ours. */
        for (i = 0; i < LA_EXTRA_PREVIEW_PAGES; i++) {
            _la_mask_preview_info();
        }
        if (saveVoice != 0) {
            layoutVoice = soundDataOpenSync(&voiceOpenReq);
            if (layoutVoice != (char *)0xFFFFFFFF) {
                saveVoice = 0;
                if (layoutVoice != 0) {
                    AdpcmPlay(((AdpcmObj *)layoutVoice)->stream);
                    return -1;
                }
            }
            return -1;
        }
        {
            if (lt_fade_status() == 2) {
                switch (a1) {
                case 214:
                    POSITIVE_SE();
                    lt_set_item_select_func(0);
                    actionStarted = 0;
                    return 0x1E;
                case 215:
                    NEGATIVE_SE();
                    systemStatus[5] = 0;
                    lt_set_item_select_func(0);
                    actionStarted = 0;
                    return 0x36;
                }
            }
            if (lt_fade_status() != 2) {
                return -1;
            }
            if ((pad[0].flags & 0x10) == 0) {
                return -1;
            }
            if (stage_no == 0x3F) {
                return -1;
            }
            NEGATIVE_SE();
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x36;
        }
    }
    return -1;
}

/* the save-slot report strings, VMA 0x61DB00 and 0x61DB20 */

/* layout_action.c:1816-1822 in the listing: the save-side twin of
   setLoadGameStartItem, inlined twice into la_save_game_memory_card_check, so
   it is a static inline here; it has no symbol of its own in the ROM and no
   census row, and the name is descriptive. */
static inline void setSaveGameStartItem(void)
{
    if (loadSerial == IosMcProductFile[0]._1E4 || loadSerial != IosMcProductFile[1]._1E4) {
        D_00534400[0] = 186;
    } else {
        D_00534400[0] = 187;
    }
}

/* layout_action.c:2689-2722 in the listing. */
int la_save_game_memory_card_check(int a0)
{
    _la_mask_preview_info();
    mcLoadMode = 0;
    lt_mask_property(0xB0, 1);
    lt_mask_property(0xB1, 1);
    debug_StdPrintfDummy("save game check port %d\n", curPort);
    switch (_la_set_current_port_new(mc, a0)) {
    case 0:
        break;
    case -1:
        debug_StdPrintfDummy("fail\n");
        if ((curPortInfo->_0.w & 3) == 3) {
            if ((curPortInfo->_0.w >> 2) & 1) {
                setSaveGameStartItem();
                lt_set_item_select_func(0);
                actionStarted = 0;
                return 0x12;
            }
            if (((curPortInfo->_0.w >> 4) & 1) == 0) {
                lt_set_item_select_func(0);
                actionStarted = 0;
                return 0x20;
            }
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x1F;
    case 1:
        debug_StdPrintfDummy("sucess :%d %d %d\n", (curPortInfo->_0.w >> 5) & 1,
                             (curPortInfo->_0.w >> 4) & 1, (curPortInfo->_0.w & 0xA) == 2);
        if ((curPortInfo->_0.w >> 2) & 1) {
            setSaveGameStartItem();
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x12;
        }
        if ((curPortInfo->_0.w & 0x30) != 0 || (curPortInfo->_0.w & 0xA) == 2) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x21;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x20;
    }
    return -1;
}

inline int la_mc_save_current_slot_select(void)
{
    if (pad[0].flags & 0x40) {
        POSITIVE_SE();
        curPort = lt_current_property_item() - 0xBA;
        lastPort = curPort;
        curPortInfo = &mcPortInfo[curPort];
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x21;
    }
    if (pad[0].flags & 0x10) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x1C;
    }
    return -1;
}

/* The sprite rectangle and colour the gif helpers take, the same pair
   layout_texture.c reconstructs. */
typedef struct {
    int x;
    int y;
    int w;
    int h;
} SprRect;

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} SprCol;

/* kept local: agrees with GifPacket.h, which this TU does not include (gif_Sprite differs) */
extern void gif_StartPacketPri(int pri);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_Sprite differs) */
extern void gif_SetZTest(int a0);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_Sprite differs) */
extern void gif_SetZWrite(int a0);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_Sprite differs) */
extern void gif_SetAlpha(long long a0, long long a1, long long a2);
/* kept local: z is unsigned int here, long long in GifPacket.h */
extern void gif_Sprite(int *r, unsigned int z, int *uv, unsigned char *col, int prim);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_Sprite differs) */
extern void gif_EndPacket(void);

static int barStep = 0; /* derived name */

static int barFrame = 0; /* derived name */

/* layout_action.c:2793-2850 in the listing. */
void progressive_bar(void)
{
    int n;

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
        SprRect frame = {80, 11, -160, 5};
        SprCol frameCol = {128, 128, 128, 32};

        gif_Sprite(&frame, 0xFFFFFFFF, 0, &frameCol, 1);
    }
    {
        SprRect back = {78, 12, -156, 3};
        SprCol backCol = {0, 0, 0, 32};

        gif_Sprite(&back, 0xFFFFFFFF, 0, &backCol, 1);
    }
    {
        int w = (float)barStep / (float)barTotal * -160.0f;
        SprRect bar = {-80 - w, 13, w, 1};
        SprCol barCol = {64, 255, 64, 32};

        gif_Sprite(&bar, 0xFFFFFFFF, 0, &barCol, 1);
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

/* the two save-select trace messages, VMA 0x61DB58 and 0x61DB68 */

static int saveCardChanged = 1; /* derived name */

/* layout_action.c:2860-2951 in the listing. */
int la_mc_save_file_select(int a0, int a1)
{
    int r;

    if (a0) {
        fileMask = 0;
        lastPort = filePort = curPort;
        saveSelectReady = 0;
        barTotal = 2;
        barStep = 0;
    }

    if (actionStarted != 0) {
        _la_set_preview_info();
        lt_mask_property(73, 1);
        lt_mask_property(72, 1);
        lt_mask_property(239, 0);
        lt_mask_property(240, 0);
    } else {
        lt_mask_property(73, 0);
        lt_mask_property(72, 0);
        lt_mask_property(239, 1);
        lt_mask_property(240, 1);
    }

    if (actionStarted != 0) {
        if (pad[0].flags & 0x10) {
            NEGATIVE_SE();
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 28;
        }
    }

    if ((fileMask != 0 || saveSelectReady != 0) && (pad[0].flags & 0x40)) {
        POSITIVE_SE();
        selectFile = a1;
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 34;
    }

    r = _la_set_current_port_lock_2(mc, a0);
    switch (r) {
    case -1:
        if (((curPortInfo->_0.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 31;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 32;
    case 1:
        if (((mcPortInfo[filePort]._0.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 28;
        }
        if (fileMask != 0) {
            if (saveCardChanged == 0) {
                if (((curPortInfo->_0.w >> 2) & 1) != 0) {
                    lt_set_item_select_func(0);
                    actionStarted = 0;
                    return 18;
                }
            } else if (((curPortInfo->_0.w >> 2) & 1) == 0) {
                saveCardChanged = 0;
            }
        } else {
            saveCardChanged = (curPortInfo->_0.w >> 2) & 1;
            if ((curPortInfo->_0.w >> 3) & 1) {
                debug_StdPrintfDummy("format 2\n");
                saveSelectReady = r;
            } else if ((curPortInfo->_0.w & 0xA) == 2) {
                debug_StdPrintfDummy("unformat 2\n");
                if (filePort == curPort) {
                    actionStarted = r;
                }
                saveSelectReady = r;
                return -1;
            }
        }
        if (filePort == curPort) {
            fileMask = curPortInfo->_4;
            actionStarted = 1;
        }
        break;
    case 0:
    default:
        return -1;
    }
    return -1;
}

inline int la_save_confirm_no_memory_card(int a0)
{
    if (PSH_POSITIVE_OR_NEGATIVE(0)) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x1C;
    }
    switch (_la_set_current_port_lock_2(mc, a0)) {
    case 0:
        break;
    case -1:
        if ((curPortInfo->_0.w >> 1) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x1E;
        }
        lock2Restart = 1;
        break;
    case 1:
        if ((curPortInfo->_0.w >> 1) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x1E;
        }
        break;
    }
    return -1;
}

inline int la_save_confirm_no_free_area(int a0)
{
    if (PSH_POSITIVE_OR_NEGATIVE(0)) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x1C;
    }
    switch (_la_set_current_port_lock_2(mc, a0)) {
    case 0:
        break;
    case -1:
        if (((curPortInfo->_0.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x1F;
        }
        lock2Restart = 1;
        break;
    case 1:
        if ((curPortInfo->_0.w >> 4) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x1E;
        }
        break;
    }
    return -1;
}

/* the save-slot messages, VMA 0x61DB78 and 0x61DB98 */

/* layout_action.c:3016-3045 in the listing. */
int la_save_start_check(int a0)
{
    switch (_la_set_current_port_lock_2(mc, a0)) {
    case 0:
        break;
    case -1:
        if (((curPortInfo->_0.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x1F;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x1E;
    case 1:
        if (filePort != curPort) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x2C;
        }
        if ((curPortInfo->_0.w & 0xA) == 2) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x24;
        }
        if ((curPortInfo->_4 >> selectFile) & 1) {
            if (IosMcProductFile[filePort].f[selectFile]._0 != 0xFFFFFFFF) {
                lt_set_item_select_func(0);
                actionStarted = 0;
                return 0x23;
            }
            if (curPortInfo->_4 != 0) {
                debug_StdPrintfDummy("already exist save data\n");
                lt_set_item_select_func(0);
                actionStarted = 0;
                return 0x26;
            }
        }
        debug_StdPrintfDummy("new save. system data making..\n");
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x27;
    }
    return -1;
}

/* layout_action.c:3055-3098 in the listing. */
int la_save_confirm_overwrite(int a0, int a1)
{
    if (a0) {
        filePort = curPort;
    }
    fileMask = 0x3FF;
    _la_set_preview_info();
    if (lt_fade_status() == 2 && (pad[0].flags & 0x10)) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x21;
    }
    switch (a1) {
    case 214:
    case 218:
        POSITIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x26;
    case 215:
    case 219:
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x21;
    }
    switch (_la_set_current_port_lock_2(mc, a0)) {
    case 0:
        break;
    case -1:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x1F;
    case 1:
        if (saveCardChanged == 0) {
            if (((curPortInfo->_0.w >> 2) & 1) == 0) {
                break;
            }
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x12;
        }
        if ((curPortInfo->_0.w >> 2) & 1) {
            break;
        }
        saveCardChanged = 0;
        if (filePort == curPort) {
            break;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x1E;
    }
    return -1;
}

/* layout_action.c:3107-3143 in the listing. */
int la_format_confirm(int a0, int a1)
{
    if (a0) {
        filePort = curPort;
    }
    if (lt_fade_status() == 2 && (pad[0].flags & 0x10)) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x21;
    }
    switch (a1) {
    case 214:
    case 218:
        POSITIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x25;
    case 215:
    case 219:
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x21;
    }
    switch (_la_set_current_port_lock_2(mc, a0)) {
    case 0:
        break;
    case -1:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x1F;
    case 1:
        if (saveCardChanged == 0) {
            if (((curPortInfo->_0.w >> 2) & 1) == 0) {
                break;
            }
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x12;
        }
        if ((curPortInfo->_0.w >> 2) & 1) {
            break;
        }
        saveCardChanged = 0;
        if (filePort == curPort) {
            break;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x1E;
    }
    return -1;
}

/* kept local: returns void here, int in mcard.h */
extern void iosMcFormat(void *a0);

static int formatStep = 0; /* derived name */

inline int la_format_processing(int a0)
{
    if (a0) {
        formatStep = 0;
    }
    switch (formatStep) {
    case 0:
        mc[2] = curPort;
        mc[3] = 0;
        iosMcFormat(mc);
        formatStep++;
        break;
    case 1:
    case 3:
        if (iosMcSync((unsigned long *)mc) == 0) {
            break;
        }
        formatStep++;
        break;
    case 2:
        if (_la_mcard_error_check(mc) > 0) {
            formatStep++;
            break;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x2D;
    case 4:
        formatStep++;
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x27;
    }
    return -1;
}

/* the system-save error message, VMA 0x61DBB8 */
/* kept local: returns void here, int in mcard.h */
extern void iosMcSaveIconBlock(void *a0);
/* kept local: returns void here, int in mcard.h */
extern void iosMcSaveProductBlock(void *a0);
/* kept local: returns void here, int in mcard.h */
extern void iosMcSaveGameBlock(void *a0, int a1);

/* the current game's save record (la_save_confirm_complete copies the
   preview from it) */
/* kept local: this TU's spelling predates sce/libc/string.h; the game compiled
   with builtins live, so a copy of a constant string is the builtin block
   move */

/* the CD real-time clock record sceCdReadClock fills in; kept local because
   the disc records no declaration-only header and seki/src/GsBase.c carries
   the same pair for the same reason. */
typedef struct {
    unsigned char stat;
    unsigned char second;
    unsigned char minute;
    unsigned char hour;
    unsigned char pad;
    unsigned char day;
    unsigned char month;
    unsigned char year;
} sceCdCLOCK;

extern int sceCdReadClock(sceCdCLOCK *clock);

/* layout_action.c:1766-1776 in the listing: the save serial, the clock
   packed into one word or a random number when the clock cannot be read;
   inlined into la_system_save_processing, with no symbol of its own in the
   ROM (the name is ours). */
static inline int mcMakeSerial(void)
{
    sceCdCLOCK clock;

    sceCdReadClock(&clock);
    if (clock.stat != 0) {
        return rand();
    }
    return ((clock.year & 7) << 26) + (clock.day << 20) + (clock.hour << 14) + (clock.minute << 7) +
           clock.second;
}

static int systemSaveStep = 0; /* derived name */

/* layout_action.c:3203-3294 in the listing, with the serial builder of lines
   1768-1775 and the play time of lines 826-841 inlined into it (its results
   are unused here, so the record passed is not visible in the bytes).  The
   switch table is jtbl_0061DBD0 (11 arms, selector systemSaveStep, cases 0-10). */
int la_system_save_processing(int a0)
{
    int err;
    int i;
    int hour;
    int min;
    int sec;

    curPortInfo = &mcPortInfo[mc[2]];
    if (a0) {
        systemSaveStep = 0;
        systemSaveRetry = 0;
        barTotal = 14;
    }

    progressive_bar();

    switch (systemSaveStep) {
    case 0:
        strcpy((char *)mc + 0x47C, "game.");
        mc[16] = systemSaveRetry;
        mc[2] = curPort;
        mc[3] = 0;
        iosMcGetBlockSaveInfo(mc);
        systemSaveStep++;
        curPortInfo->_0.w = (int)curPortInfo->_0.w & ~0x80;
        barStep++;
        break;
    case 2:
        iosMcSaveIconBlock(mc);
        systemSaveStep++;
        break;
    case 6:
    case 9:
        err = _la_mcard_error_check(mc);
        if (err > 0) {
            systemSaveStep++;
            debug_StdPrintfDummy("McSave phase:%d  %x\n", systemSaveStep, err);
            return -1;
        }
        curPortInfo->_0.w |= 0x80;
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 44;
    case 4:
        for (i = 0; i < 10; i++) {
            IosMcProductFile[mc[2]].f[i]._0 = 0xFFFFFFFF;
        }
        while ((IosMcProductFile[mc[2]]._1E4 = mcMakeSerial()) == 0)
            ;
        playTime((struct S14 *)IosMcPreviewInfo, &hour, &min, &sec);
        iosMcSaveProductBlock(mc);
        systemSaveStep++;
        barStep++;
        break;
    case 1:
    case 3:
    case 5:
    case 8:
        if (iosMcSync((unsigned long *)mc) != 0) {
            systemSaveStep++;
        }
        break;
    case 7:
        iosMcSaveGameBlock(mc, gameSysMainSaveBuff);
        systemSaveStep++;
        barStep++;
        break;
    case 10:
        systemSaveStep = 7;
        systemSaveRetry++;
        mc[16] = systemSaveRetry;
        if (systemSaveRetry >= 10) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 38;
        }
        break;
    }
    return -1;
}

/* the second save-phase message, VMA 0x61DC00 */

/* layout_action.c:1802-1805 in the listing: the save side's readback, the
   serial kept as both the saved and the current one; inlined into
   la_save_processing (the name is ours). */
static inline void mcSetSavedFile(void)
{
    int serial = mcSetFileNo(mc[2], mc[16]);

    loadSerial = serial;
    saveSerial = serial;
}

static int saveStep = 0; /* derived name */

/* layout_action.c:3309-3410 in the listing, with the menu-close pair of lines
   707-708, the play time of lines 829-832, the serial builder of lines
   1768-1775 and the readback of lines 1798-1804 inlined into it.  The switch
   table is jtbl_0061DC10 (11 arms, selector saveStep, cases 0-10). */
int la_save_processing(int a0)
{
    int err;
    int hour;
    int min;
    int sec;

    curPortInfo = &mcPortInfo[mc[2]];
    if (a0) {
        fileMask = 0;
        saveStep = 0;
    }

    progressive_bar();

    switch (saveStep) {
    case 0:
        strcpy((char *)mc + 0x47C, "game.");
        mc[16] = selectFile;
        mc[2] = curPort;
        mc[3] = 0;
        iosMcGetBlockSaveInfo(mc);
        saveStep++;
        curPortInfo->_0.w = (int)curPortInfo->_0.w & ~0x80;
        break;
    case 1:
        if (iosMcSync((unsigned long *)mc) != 0) {
            saveStep = 4;
        }
        break;
    case 2:
        iosMcSaveIconBlock(mc);
        saveStep++;
        break;
    case 6:
    case 9:
        err = _la_mcard_error_check(mc);
        if (err > 0) {
            saveStep++;
            debug_StdPrintfDummy("McSave phase:%d  %x\n", saveStep, err);
            return -1;
        }
        curPortInfo->_0.w |= 0x80;
        debug_StdPrintfDummy("save error? %d\n", saveStep);
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 44;
    case 4:
        IosMcPreviewInfo[0] = stage_no;
        IosMcPreviewInfo[3] = GetSaveSofaLayoutID();
        IosMcPreviewInfo[1] = gFlagGameClear;
        *(struct S14 *)&IosMcProductFile[mc[2]].f[mc[16]] = *(struct S14 *)IosMcPreviewInfo;
        playTime((struct S14 *)IosMcPreviewInfo, &hour, &min, &sec);
        (IosMcProductFile + mc[2])->_1E0 = mc[16];
        if ((IosMcProductFile + mc[2])->_1E4 == (IosMcProductFile + (mc[2] ^ 1))->_1E4) {
            do {
                while ((IosMcProductFile[mc[2]]._1E4 = mcMakeSerial()) == 0)
                    ;
            } while ((IosMcProductFile + mc[2])->_1E4 == (IosMcProductFile + (mc[2] ^ 1))->_1E4);
        }
        mcSetSavedFile();
        iosMcSaveProductBlock(mc);
        saveStep++;
        break;
    case 3:
    case 5:
    case 8:
        if (iosMcSync((unsigned long *)mc) != 0) {
            saveStep++;
            barStep++;
        }
        break;
    case 7:
        CheckPoint();
        iosMcSaveGameBlock(mc, gameSysMainSaveBuff);
        saveStep++;
        break;
    case 10:
        saveStep = 0;
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 41;
    }
    return -1;
}

inline int la_save_confirm_complete(int a0, int a1)
{
    if (a0) {
        previewInfo = *(struct S14 *)IosMcPreviewInfo;
        fileMask = 0x3FF;
        _la_set_preview_info();
        debug_StdPrintfDummy("save complete %d %d\n", fileMask, curFile);
    }
    if (a1 != -1) {
        debug_StdPrintfDummy("%d %d %d\n", 0x108, 0x109, a1);
    }
    switch (a1) {
    case 0x108:
        systemStatus[5] = 0;
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x36;
    case 0x109:
        nextStage = 1;
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x3F;
    }
    return -1;
}

/* layout_action.c:3462-3499 in the listing. */
int la_end_confirm(void)
{
    int item;

    if (lt_fade_status() == 2 && (pad[0].flags & 0x10)) {
        NEGATIVE_SE();
        item = lt_current_property_item();
        if (item >= 270) {
            if (item < 272) {
                lt_set_item_select_func(0);
                actionStarted = 0;
                return 0x29;
            }
            if (item < 426) {
                if (item >= 424) {
                    lt_set_item_select_func(0);
                    actionStarted = 0;
                    return 0x39;
                }
            }
        }
    }
    if (pad[0].flags & 0x40) {
        debug_StdPrintfDummy("%d\n", lt_current_property_item());
        switch (lt_current_property_item()) {
        case 270:
        case 424:
            POSITIVE_SE();
            optionScreenMode = 0;
            gflagInit();
            fightSoundProcessRequestPause();
            fightSoundClose();
            soundDataSegAllClose(0, 2);
            nextStage = 1;
            stgmgrForceSwitchWithFade(1, 0.025f, 4.0f);
        case 271:
            NEGATIVE_SE();
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x29;
        case 425:
            NEGATIVE_SE();
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x39;
        }
    }
    return -1;
}

inline int la_save_confirm_yesno(void)
{
    if (pad[0].flags & 0x10) {
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

inline int la_delete_start_check(int a0)
{
    switch (_la_set_current_port_2(mc, a0)) {
    case 0:
        break;
    case -1:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x1E;
    case 1:
        if ((curPortInfo->_4 >> selectFile) & 1) {
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x31;
        }
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x21;
    }
    return -1;
}

inline int la_delete_confirm(int a0, int a1)
{
    switch (a1) {
    case 0xD6:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x32;
    case 0xD7:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x1E;
    }
    return -1;
}

/* kept local: returns void here, int in mcard.h */
extern void iosMcDelete(void *a0);

static int deleteStep = 0; /* derived name */

/* layout_action.c:3601-3642 in the listing. */
int la_delete_processing(int a0)
{
    if (a0) {
        mc[16] = selectFile;
        deleteStep = 2;
    }
    switch (deleteStep) {
    case 2:
        strcpy((char *)mc + 0x47C, (char *)mc + 0x4E0 + (mc[16] << 6));
        iosMcDelete(mc);
        deleteStep++;
        break;
    case 3:
        if (iosMcSync((unsigned long *)mc) == 0) {
            break;
        }
        deleteStep++;
        break;
    case 4:
        if (_la_mcard_error_check(mc) == 0) {
            break;
        }
        deleteStep++;
        break;
    case 5:
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x33;
    }
    return -1;
}

inline int la_delete_confirm_complete(void)
{
    int ret;
    if ((pad[0].flags & 0x10) == 0)
        goto fail;
    lt_set_item_select_func(0);
    actionStarted = 0;
    ret = 0x1E;
    goto out;
fail:
    ret = -1;
out:
    return ret;
}

inline int la_delete_confirm_fail(void)
{
    return -1;
}

inline int la_game_loading(int a0)
{
    if (a0 != 0) {
        systemStatus[6] = 1;
    }
    return -1;
}

inline void la_playtime_count(void)
{
    if (systemStatus[5] == 0) {
        IosMcPreviewInfo[2]++;
    }
}

/* layout_action.c:2576-2582 in the listing: inlined into la_game_loop and into
   la_game_over_continue, so it is a static inline here; it has no symbol of its
   own in the ROM and no census row, and the name is descriptive. */
static inline void releaseGameLoopCursor(void)
{
    if (layoutVoice != 0 && ((AdpcmObj *)layoutVoice)->stream != 0) {
        ((AdpcmObj *)layoutVoice)->stream->f44 = 0x100;
    }
    layoutVoice = 0;
}

int laoutActionPauseRequest = 0;

/* layout_action.c:3720-3748 in the listing. */
int la_game_loop(int a0)
{
    if (a0) {
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
        if (gflagChk(338) != 0) {
            return -1;
        }
        systemStatus[5] = 1;
        layoutActPushStartNew = 0;
        adpcmPauseRequest(1);
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x39;
    }
    return -1;
}

inline int la_game_demo_pause(int a0)
{
    if (a0) {
        systemStatus[5] = 1;
    }
    if ((pad[0].flags & 0x800) == 0) {
        return -1;
    }
    lt_set_item_select_func(0);
    actionStarted = 0;
    return 0x37;
}

inline int la_game_demo(int a0)
{
    if (a0) {
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
        return 0x3F;
    }
    return -1;
}

inline int la_game_pause(int a0)
{
    if (a0) {
        systemStatus[5] = 1;
        iosPadActStopAll();
        D_00534CC0[0] = 0x134;
    }
    if (lt_fade_status() != 2) {
        return -1;
    }
    if (((pad[0].flags & 0x40) && lt_current_property_item() == 0x127) || (pad[0].flags & 0x810)) {
        NEGATIVE_SE(0);
        adpcmPauseRequest(0);
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x36;
    }
    return -1;
}

static int gameOverVoice = 0; /* derived name */

static int gameOverVoiceOpened = 0; /* derived name */

/* layout_action.c:3837-3900 in the listing. */
int la_game_over_continue(int a0)
{
    if (a0) {
        if (fadeStatus != 0) {
            scpFadeIn(3.0f);
        }
        enable_game_pause = 1;
        iosPadEnable();
        scpBoyControlReadDisable = 0;
        systemStatus[5] = 1;
        AdpcmFadeCloseAll(0x200);
        AdpcmNotUseIopAreaFree();
        soundSePlayModeStop(1);
        soundSePlayModeStop(0);
        iosPadActStopAll();
        gameOverVoiceOpened = 0;
    } else if (gameOverVoiceOpened == 0) {
        if (AdpcmFreeAreaGet() != 0) {
            gameOverVoice = openLayoutVoice(0x34);
            gameOverVoiceOpened = 1;
        }
    } else if (gameOverVoice != 0) {
        layoutVoice = soundDataOpenSync(&voiceOpenReq);
        if (layoutVoice != (char *)0xFFFFFFFF) {
            gameOverVoice = 0;
            if (layoutVoice != 0) {
                AdpcmPlay(((AdpcmObj *)layoutVoice)->stream);
                return -1;
            }
        }
    } else {
        switch (lt_current_property_item()) {
        case 0x1AD:
            if ((pad[0].flags & 0x40) == 0 || lt_fade_status() != 2) {
                return -1;
            }
            POSITIVE_SE();
            systemStatus[4] = 1;
            nextStage = gFlagSaveStage;
            releaseGameLoopCursor();
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x3F;
        case 0x1AE:
            if ((pad[0].flags & 0x40) == 0 || lt_fade_status() != 2) {
                return -1;
            }
            POSITIVE_SE();
            optionScreenMode = 0;
            gflagInit();
            nextStage = 1;
            releaseGameLoopCursor();
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 0x3F;
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

/* layout_action.c:3941-3947 in the listing: the key-config property sweep,
   inlined into la_key_config twice; it has no symbol of its own in the ROM and
   no census row, so the name is descriptive. */
static inline void keyconfigMaskAll(void)
{
    int i;

    for (i = 0; i < 48; i++) {
        lt_mask_property(i + 342, 1);
        lt_default_mask_property(i + 342, 1);
    }
}

/* layout_action.c:4079-4085 in the listing */
static inline int keyBitIndex(int v)
{
    int i;

    for (i = 0; i < 16; i++) {
        if ((v >> i) & 1) {
            return i;
        }
    }
    return -1;
}

/* layout_action.c:4087-4093 in the listing */
static inline int keyCodeIndex(int v)
{
    int i;

    for (i = 0; i < 8; i++) {
        if (v == keyConfigCode[i]) {
            return i;
        }
    }
    return -1;
}

/* layout_action.c:4095-4100 in the listing */
static inline int keyAssignIndex(int v)
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

/* layout_action.c:4053-4237 in the listing. */
int la_key_config(int a0)
{
    int i;
    int sel;
    int m;
    int k;
    int n;

    sel = lt_current_property_item() - 336;
    if (a0) {
        D_00534CC0[0] = 323;
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
        lt_mask_property(i * 8 + 342 + keyConfigSlot[i], 0);
        lt_default_mask_property(i * 8 + 342 + keyConfigSlot[i], 0);
    }
    if (pad[0].flags & 0x40) {
        if (lt_current_property_item() == 391) {
            for (i = 7; i >= 0; i--) {
                keyConfigSlot[i] = i;
            }
            NEGATIVE_SE();
        }
        if (lt_current_property_item() == 390) {
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
                lt_default_mask_property(i * 8 + 342 + keyConfigSlot[i], 0);
                lt_mask_property(i * 8 + 342 + keyConfigSlot[i], 0);
            }
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 58;
        }
    }
    return -1;
}

/* the option screen's layout items: the five screen modes, the stage
   animation each mode plays (-1 for none), and the two choices of the control
   type (item 318) followed by the two of the setting item 325 toggles.  The
   last four are one table: two 8-byte tables would be small data under -G 8,
   and the ROM keeps them in .rodata; its code reaches the second pair from
   that pair's own address constant, which the offset pointer spells. */
static const int screenModeItem[5] = {303, 304, 305, 306, 307}; /* derived name */

static const int screenModeAnim[5] = {-1, 67, 68, 69, 70}; /* derived name */

static const int choiceItem[4] = {321, 322, 328, 329}; /* derived name */

/* layout_action.c:4272-4371 in the listing.  The switch table is jtbl_0061DCC0
   (26 arms over the property item, cases 300..325; VMA 0x61DCC0..0x61DD28). */
int la_game_option(void)
{
    int mode;
    int cur;
    int sel;
    int item;

    mode = soundOutputModeGet();
    lt_analog2Pad();
    if ((pad[0].now & 0xA000) != 0) {
        cur = optionControlType;
        sel = optionScreenMode;
        switch (lt_current_property_item()) {
        case 300:
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
        case 318:
            if ((pad[0].flags & 0xA000) != 0) {
                cur = cur == 0;
                CUR_SE();
            }
            break;
        case 313:
            if ((pad[0].flags & 0xA000) != 0) {
                iosPadActRequestEnable = iosPadActRequestEnable == 0;
                CUR_SE();
            }
            break;
        case 308:
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
        case 325:
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
    if ((pad[0].flags & 0x40) != 0) {
        if (lt_current_property_item() == 330) {
            NEGATIVE_SE();
            lt_set_item_select_func(0);
            actionStarted = 0;
            return 57;
        }
    }
    if (mode == 0) {
        lt_default_mask_property(311, 0);
        lt_default_mask_property(312, 1);
    } else {
        lt_default_mask_property(311, 1);
        lt_default_mask_property(312, 0);
    }
    if (iosPadActRequestEnable != 0) {
        lt_default_mask_property(316, 0);
        lt_default_mask_property(317, 1);
    } else {
        lt_default_mask_property(316, 1);
        lt_default_mask_property(317, 0);
    }
    for (sel = 0; sel < 2; sel++) {
        lt_default_mask_property((choiceItem + 2)[sel], 1);
    }
    lt_default_mask_property((choiceItem + 2)[girlControlMode], 0);
    return -1;
}

/* layout_action.c:4383-4386 in the listing: inlined once, into la_adjust_screen,
   so it is a static inline here; it has no symbol of its own in the ROM and no
   census row, and the name is descriptive. */
static inline void clearAdjustScreenMarks(void)
{
    int i;

    for (i = 0; i < 15; i++) {
        lt_default_mask_property(i + 395, 1);
    }
}

/* layout_action.c:4390-4427 in the listing. */
int la_adjust_screen(void)
{
    int v;

    D_00534CC0[0] = 324;
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
    if (pad[0].flags & 0x10) {
        NEGATIVE_SE();
        systemStatus[11] = 7;
    }
    clearAdjustScreenMarks();
    lt_default_mask_property(systemStatus[11] + 395, 0);
    if (pad[0].flags & 0x40) {
        POSITIVE_SE();
        lt_set_item_select_func(0);
        actionStarted = 0;
        return 0x3A;
    }
    return -1;
}

unsigned int stage_after_skipping_demo = 0;

int layoutActPushStartNew = 0;
