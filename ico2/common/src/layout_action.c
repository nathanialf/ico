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
#include "include_asm.h"

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
    int cleared;   /* 0x04 */
    int playTime;  /* 0x08, in frames */
    int sofa;      /* 0x0C; the record ends here in this build (four words, as
                      mcard.c's IosMcPreviewInfo) */
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

static int mcLoadMode; /* derived name */

/* .bss: the two card ports' records, the preview
   record of the save being confirmed, the open request of the layout voice
   and the twenty game flags kept across a load. */
static McPortInfo mcPortInfo[2]; /* derived name */

static struct McPreview previewInfo; /* derived name */

static AdpcmOpenReq voiceOpenReq; /* derived name */

static signed char keepFlags[20]; /* derived name */

void POSITIVE_SE(void);
void NEGATIVE_SE();
void CUR_SE(void);
inline int PSH_POSITIVE_OR_NEGATIVE(int idx);

void la_TESTFUNCTION(void)
{
    debug_StdPrintfDummy("sync end\n");
}

/* .data: the game-flag ids the load carries across gflagInit.  The list
   holds five ids (this build's flag numbers) and la_mc_confirm_save_file's
   table and the key-config tables follow it; the keep/restore loops below
   walk twenty words. */
static int keepFlagNo[5] = {339, 335, 334, 336, 333}; /* derived name */

/* la_mc_confirm_save_file's table of eight 16-byte rows */
INCLUDE_ASM(D_004DCC20);

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

INCLUDE_ASM(func_001A35D0);

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

/* PAL's fightSoundStopped word is not in this build's .sdata */
static SqEntry *layoutVoice = 0; /* derived name */

int startStagePauseDisableTimer = 0;

int layout_boot_flag = 0;

int enable_game_pause = 1;

INCLUDE_ASM(_la_memory_card_check);

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

/* This build's .sdata after lock2Locked is the stub-owned run D_0067AA94: the
   demo's state words here differ from PAL's (portNewStep through
   layoutActPushStartNew), and only stubs read them. */
INCLUDE_ASM(D_0067AA94);

INCLUDE_ASM(_la_set_current_port_new);

INCLUDE_ASM_LIT(la_boot_no_memory_card);

INCLUDE_ASM_LIT(la_boot_no_free_area);

inline void keyconfig_reset(void);

INCLUDE_ASM(la_vibe_select);

INCLUDE_ASM(la_title_continue_or_new);

INCLUDE_ASM(_la_set_preview_info);

INCLUDE_ASM(la_mc_file_select);

INCLUDE_ASM(_la_mask_preview_info);

INCLUDE_ASM(la_mc_load_file_select);

/* the play time of a save record split into hours, minutes and seconds and
   clamped to 99:59:59, inlined into _la_set_preview_info, la_load_processing
   and la_system_save_processing; the last two leave the results unused */
static inline void playTime(struct McPreview *p, int *hour, int *min, int *sec) /* derived name */
{
    int frames = p->playTime;
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

INCLUDE_ASM(la_load_game_memory_card_check);

INCLUDE_ASM(la_load_confirm_no_data);

INCLUDE_ASM(la_load_confirm_no_memory_card);

INCLUDE_ASM(la_load_processing);

INCLUDE_ASM(la_load_start_check);

INCLUDE_ASM(la_save_game_memory_card_check);

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

/* extra preview pages to re-mask; none in the release build */
#define LA_EXTRA_PREVIEW_PAGES 0

INCLUDE_ASM(la_mc_confirm_save_file);

INCLUDE_ASM(la_layout29_proc);

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

INCLUDE_ASM(progressive_bar);

INCLUDE_ASM(la_mc_save_file_select);

INCLUDE_ASM(la_save_start_check);

INCLUDE_ASM(la_save_confirm_overwrite);

INCLUDE_ASM(la_format_confirm);

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
}

INCLUDE_ASM(la_system_save_processing);

INCLUDE_ASM(la_save_processing);

INCLUDE_ASM_LIT(la_save_confirm_complete);

INCLUDE_ASM(la_end_confirm);

INCLUDE_ASM(la_delete_processing);

/* inlined into la_game_loop and into la_game_over_continue */
static inline void releaseGameLoopCursor(void) /* derived name */
{
    if (layoutVoice != 0 && layoutVoice->stream != 0) {
        layoutVoice->stream->fadeStep = 0x100;
    }
    layoutVoice = 0;
}

INCLUDE_ASM(la_game_loop);

INCLUDE_ASM(la_game_over_continue);

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
        lt_mask_property(i + 342, 1);
        lt_default_mask_property(i + 342, 1);
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

INCLUDE_ASM(la_key_config);

/* la_game_option is a stub; the demo's .rodata has none of PAL's option-screen
   item tables (screen modes, their animations, the two choices). */
INCLUDE_ASM(la_game_option);

/* inlined once, into la_adjust_screen */
static inline void clearAdjustScreenMarks(void) /* derived name */
{
    int i;

    for (i = 0; i < 15; i++) {
        lt_default_mask_property(i + 395, 1);
    }
}

INCLUDE_ASM(la_adjust_screen);

INCLUDE_ASM(la_boot_memory_card_check);

INCLUDE_ASM(la_boot_no_memory_card);

INCLUDE_ASM(la_boot_no_free_area);

INCLUDE_ASM(la_boot_confirm_memory_card);

INCLUDE_ASM(la_layout6_proc);

INCLUDE_ASM(la_scei_logo);

INCLUDE_ASM(la_title_demo);

INCLUDE_ASM(func_001A75B8);

INCLUDE_ASM(la_layout11_proc);

INCLUDE_ASM(la_mc_preview_info);

INCLUDE_ASM(la_mc_current_slot);

INCLUDE_ASM(la_mc_save_current_slot_select);

INCLUDE_ASM(la_general_mc_confirm);

INCLUDE_ASM(la_save_confirm_no_memory_card);

INCLUDE_ASM(la_save_confirm_no_free_area);

INCLUDE_ASM(la_format_processing);

INCLUDE_ASM(la_save_confirm_complete);

INCLUDE_ASM(la_layout39_proc);

INCLUDE_ASM(func_001A7E08);

INCLUDE_ASM(la_save_confirm_fail);

INCLUDE_ASM(la_format_confirm_fail);

INCLUDE_ASM(la_delete_start_check);

INCLUDE_ASM(la_delete_confirm);

INCLUDE_ASM(la_delete_confirm_complete);

INCLUDE_ASM(la_delete_confirm_fail);

INCLUDE_ASM(la_game_loading);

INCLUDE_ASM(la_playtime_count);

INCLUDE_ASM(la_game_demo);

INCLUDE_ASM(la_game_demo_pause);

INCLUDE_ASM_LIT(la_format_processing);

INCLUDE_ASM(la_game_pause);
