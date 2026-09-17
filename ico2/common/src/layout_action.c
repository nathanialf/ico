#include "common.h"
#include "layout_action.h"
#include "debug.h"
#include "layout_texture.h"
#include "pad.h"
#include "gobj.h"
#include "adpcm_init.h"
#include "fightSound.h"
#include "gflag.h"

struct S40 {
    char b[0x40];
};

typedef struct {
    int _0;
    int flags;
    char _8[0x50];
} R58;

typedef struct {
    unsigned int _0;
    int _4;
} R8;

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

extern R58 D_0028F8F0[];

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * PSH_POSITIVE_OR_NEGATIVE (line 730) into the two la_save_confirm_no_*
 * actions, so it is a public `inline` of the deferred tail; until the tail's
 * asm members are C its copy is emitted as a plain function at its ROM
 * position (before keyconfig_reset) and the callers inline this static
 * stand-in, which collapses at layout. */
static inline int pshPositiveOrNegative(int idx)
{
    int v = D_0028F8F0[idx].flags;
    if ((v & 0x40) != 0)
        goto one;
    if ((v & 0x10) == 0)
        goto zero;
one:
    return 1;
zero:
    return 0;
}

extern int D_0061D750[];

void la_TESTFUNCTION(void)
{
    debug_StdPrintfDummy(D_0061D750);
}

extern int D_0063B4F4;
extern int mc[];
/* kept local: this TU's uses of iosMcSync do not fit the prototype in mcard.h */
extern int iosMcSync(unsigned long *a0);
extern int D_0063B4E8;
extern int D_0063B4F0;
extern int D_0063B4E0;
extern R8 *D_0063B4D8;
extern int D_0063B550;
extern int D_0063C3E4;
extern int D_0063B528;
extern int D_00534CC0[];
extern int D_0028F4C0[];
extern int D_0028F8F4[];

typedef struct {
    int _0;
    char _4[0x10];
} R14;

typedef struct {
    R14 f[20];
    char _190[0x54];
    int _1E4;
    char _1E8[0x8];
} R1F0;

extern R1F0 D_0029B5F0[];
extern int D_005343C8[];
extern int D_0063B554;
extern int D_0063B558;
extern int D_0063C3E8;
extern int D_0063B4EC;
extern void stgmgrForceSwitchWithFade(float a0, float a1, int a2);
extern int D_0063B5C4;
extern int lock_execIcoMisc;
extern int D_0063B4DC;
extern int D_0063BE68;
extern int D_0063C3D4;
extern int D_0063B54C;
extern int D_0063B5F8;
extern int D_0063B620;
extern int D_0063AA00;
extern int D_0028F4D4[];
extern R8 D_0071D900[];
extern int D_0063B53C;
extern int D_0063B540;
extern int D_0063C3C4;
extern int D_0063C3C8;
extern int D_0063B530;
extern int D_0063B534;
extern int D_0063B538;
extern int D_0063C3C0;
extern int D_0063B52C;
extern int D_00534400[];
extern char D_0063B5A8[];
extern int D_0063C3D0;
extern int D_0063B548;
extern struct S40 D_0029BC00;
extern struct S40 D_0061D968;
extern int D_0063A538;
extern char *D_0063BE6C;
extern int D_0028F4D0[];
extern char *D_0063B4FC;
extern int D_0063B598;
extern int D_0063B59C;
extern int D_0063B5A0;
extern void CheckPoint(void);
extern char D_0061DA98[];
extern char D_0061DAB8[];
extern int stage_no;
extern int D_0063B4F8;
/* the memory-card error messages, VMA 0x61D760..0x61D840 */
extern char D_0061D760[];
extern char D_0061D770[];
extern char D_0061D790[];
extern char D_0061D7A8[];
extern char D_0061D7C0[];
extern char D_0061D7F0[];
extern char D_0061D810[];
extern char D_0061D820[];

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
        debug_StdPrintfDummy(D_0061D760, *(int *)(w + 0x10));
        return -1;
    case -9:
        debug_StdPrintfDummy(D_0061D770, *(int *)(w + 0x10));
        return -1;
    case -4:
        debug_StdPrintfDummy(D_0061D790, w + 0x47C);
        return -1;
    case -14:
        debug_StdPrintfDummy(D_0061D7A8, w + 0x454);
        return -1;
    case -16:
        debug_StdPrintfDummy(D_0061D7C0, *(int *)(w + 0x24), *(int *)(w + 0x50),
                             *(int *)(w + 0x4C));
        return -1;
    case -15:
        debug_StdPrintfDummy(D_0061D7F0, w + 0x47C);
        return -1;
    case -10:
        debug_StdPrintfDummy(D_0061D810);
        return -1;
    default:
        debug_StdPrintfDummy(D_0061D820, *(int *)(w + 0x10));
        return -2;
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/layout_action", _la_memory_card_check);

/* layout_action.c:1027-1031 in the listing: inlined three times into
   _la_set_current_port_2 and once into _la_set_current_port_lock_2, so it is a
   static inline here; it has no symbol of its own in the ROM and no census row,
   and the name is descriptive. */
static inline int currentPortLockState(void)
{
    return (((D_0063B4D8->_0 >> 1) & 1) && (D_0063B4D8->_0 & 0x38) != 8) ? 1 : -1;
}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/layout_action", _la_set_current_port_2);
INCLUDE_ASM("asm/nonmatchings/ico2/common/src/layout_action", _la_set_current_port_lock_2);
INCLUDE_ASM("asm/nonmatchings/ico2/common/src/layout_action", _la_set_current_port_new);

/* INTERIM (see the PSH_POSITIVE_OR_NEGATIVE note at the head of this file): the
 * listing inlines keyconfig_reset (line 1438) into la_vibe_select, so it is a
 * public `inline` of the deferred tail; until that tail is reordered its copy is
 * emitted as a plain function at its ROM position (after
 * PSH_POSITIVE_OR_NEGATIVE) and the caller inlines this static stand-in, which
 * collapses at layout. */
static inline void keyconfigReset(void)
{
    struct S40 tmp;

    tmp = D_0061D968;
    D_0029BC00 = tmp;
}

/* layout_action.c:1455-1490 in the listing. */
int la_vibe_select(void)
{
    if (lt_fade_status() == 2 && (D_0028F8F4[0] & 0x840)) {
        soundSeDefPlay(415, 0xFFFFFFFF, 0, 0);
        switch (lt_current_property_item()) {
        case 0x2C:
            D_0063A538 = 1;
            break;
        case 0x2D:
            D_0063A538 = 0;
            break;
        }
        if (D_0063BE6C != 0) {
            *(short *)(*(int *)(D_0063BE6C + 0x2C) + 0x44) = 0x80;
        }
        D_0063BE6C = 0;
        gflagInit();
        keyconfigReset();
        D_0028F4D0[0] = 0;
        gflagOn(382);
        return -1;
    }
    if (lt_fade_status() != 2) {
        return -1;
    }
    if ((D_0028F8F4[0] & 0x10) == 0) {
        return -1;
    }
    NEGATIVE_SE();
    lt_set_item_select_func(0);
    D_0063B4F4 = 0;
    return 0xC;
}

/* layout_action.c:1579-1630 in the listing. */
int la_title_continue_or_new(int a0)
{
    if (a0) {
        D_0063BE68 = 1;
        D_0063C3D0 = lock_execIcoMisc;
        iosPadEnable();
        isysGObjActiveLink(0, 1);
        D_0028F4D4[0] = 0;
        gflagOff(382);
        if (gflagChk(385) == 0) {
            gflagOn(385);
        }
        D_0063B548 = 0;
        D_0063B5F8 = 0;
    }
    if (D_0063B548 != 0) {
        D_0063B620 = 0;
        lt_mask_property(0x31, 0);
        lt_mask_property(0x32, 0);
    } else {
        D_0063B620 = 1;
        lt_mask_property(0x31, 1);
        lt_mask_property(0x32, 1);
    }
    if (D_0063B548 != 0 && (D_0028F8F4[0] & 0x840) && lt_fade_status() == 2) {
        D_0063B5F8 = 1;
        soundSeDefPlay(414, 0xFFFFFFFF, 0, 0);
        switch (lt_current_property_item()) {
        case 0x31:
            D_0063BE68 = 2;
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x14;
        case 0x32:
            D_0063BE68 = 2;
            D_0063AA00 = 0;
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 9;
        }
    }
    switch (_la_set_current_port_2(mc, a0)) {
    case 0:
        break;
    case 1:
        if ((D_0063B4D8->_0 & 0x22) == 2) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0xD;
        }
        D_0063B548 = 1;
        break;
    case -1:
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0xD;
    }
    return -1;
}

/* layout_action.c:1647-1700 in the listing. */
int la_title_new_game_only(int a0)
{
    if (a0) {
        D_0063BE68 = 1;
        D_0063C3D4 = lock_execIcoMisc;
        iosPadEnable();
        isysGObjActiveLink(0, 1);
        D_0028F4D4[0] = 0;
        gflagOff(382);
        if (gflagChk(385) == 0) {
            gflagOn(385);
        }
        D_0063B54C = 0;
        D_0063B5F8 = 0;
        D_0063B4DC = -1;
    }
    if (D_0063B54C != 0) {
        D_0063B620 = 0;
        lt_mask_property(51, 0);
    } else {
        D_0063B620 = 1;
        lt_mask_property(51, 1);
    }
    if (D_0063B54C != 0 && (D_0028F8F4[0] & 0x840) && lt_fade_status() == 2) {
        soundSeDefPlay(414, 0xFFFFFFFF, 0, 0);
        D_0063B5F8 = 1;
        D_0063BE68 = 2;
        D_0063AA00 = 0;
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 9;
    }
    switch (_la_set_current_port_2(mc, a0)) {
    case 0:
        break;
    case -1:
        D_0063B54C = 1;
        break;
    case 1:
        if ((D_0063B4D8->_0 >> 5) & 1) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0xC;
        }
        D_0063B54C = 1;
        break;
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/layout_action", la_mc_file_select);

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

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/layout_action", _la_set_preview_info);

/* layout_action.c:1808-1814 in the listing: inlined once, into
   la_load_game_memory_card_check, so it is a static inline here; it has no
   symbol of its own in the ROM and no census row, and the name is descriptive. */
static inline void setLoadGameStartItem(void)
{
    if (D_0063B558 == D_0029B5F0[0]._1E4 || D_0063B554 != D_0029B5F0[1]._1E4) {
        D_005343C8[0] = 186;
    } else {
        D_005343C8[0] = 187;
    }
}

/* layout_action.c:2071-2102 in the listing. */
int la_load_game_memory_card_check(int a0)
{
    _la_mask_preview_info();
    D_0063C3E8 = 1;
    lt_mask_property(0xB0, 1);
    lt_mask_property(0xB1, 1);
    switch (_la_set_current_port_2(mc, a0)) {
    case 0:
        if (D_0063C3E4 == 0 || D_0063C3E4 == -14) {
            return -1;
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x16;
    case -1:
        if ((D_0063B4D8->_0 >> 1) & 1) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x17;
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x16;
    case 1:
        if ((D_0063B4D8->_0 >> 6) & 1) {
            setLoadGameStartItem();
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x11;
        }
        if ((D_0063B4D8->_0 >> 5) & 1) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x13;
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x17;
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/layout_action", la_mc_load_file_select);

/* layout_action.c:2245-2267 in the listing. */
int la_load_confirm_no_memory_card(int a0)
{
    if (a0) {
        _la_mask_preview_info();
    }
    if (pshPositiveOrNegative(0)) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0xD;
    }
    switch (_la_set_current_port_lock_2(mc, a0)) {
    case 0:
        break;
    case -1:
        if ((D_0063B4D8->_0 & 0x32) == 2 || (D_0063B4D8->_0 & 0x22) == 2) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x17;
        }
        if ((D_0063B4D8->_0 >> 1) & 1) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x14;
        }
        D_0063B528 = 1;
        break;
    case 1:
        if ((D_0063B4D8->_0 & 0x32) == 2 || (D_0063B4D8->_0 & 0x22) == 2) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x17;
        }
        if ((D_0063B4D8->_0 >> 1) & 1) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
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
    if (pshPositiveOrNegative(0)) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0xD;
    }
    switch (_la_set_current_port_lock_2(mc, a0)) {
    case 0:
        break;
    case -1:
        if (((D_0063B4D8->_0 >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x16;
        }
        D_0063B528 = 1;
        break;
    case 1:
        if ((D_0063B4D8->_0 >> 5) & 1) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
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
        D_0063B4F0 = 0x3FF;
        if (D_0063C3E4 == 0 || D_0063C3E4 == -14) {
            return -1;
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x2E;
    case -1:
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x2E;
    case 1:
        if (D_0063B550 != D_0063B4E0) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x2E;
        }
        if ((D_0063B4D8->_0 & 3) != 3) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x16;
        }
        if ((D_0063B4D8->_4 >> D_0063B4E8) & 1) {
            D_0063B4F0 = 0x3FF;
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x19;
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x17;
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/layout_action", la_load_processing);

extern int fadeStatus;
extern void scpFadeIn(float sec);
extern int D_0063AA08;
extern void soundSePlayModeStop(int a0);
extern void iosPadActStopAll(void);
extern int D_0063B5E4;
extern int D_0063B5E8;
extern char D_0071D928[];
extern void soundDataOpen(void *p, int a1, int a2, int a3, int t0);
extern char *soundDataOpenSync(void *p);
extern int D_0063AA04;

/* layout_action.c:2565-2570 in the listing: inlined into la_game_over_continue
   and into la_mc_confirm_save_file with different data numbers, so the number is
   its parameter; it is a static inline here, with no symbol of its own in the
   ROM and no census row, and the name is descriptive. */
static inline int openLayoutVoice(int no)
{
    if (D_0063B4FC != 0) {
        return 0;
    }
    soundDataOpen(D_0071D928, 2, no, 1, 0);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/layout_action", la_mc_confirm_save_file);

/* the save-slot report strings, VMA 0x61DB00 and 0x61DB20 */
extern char D_0061DB00[];
extern char D_0061DB20[];

/* layout_action.c:1816-1822 in the listing: the save-side twin of
   setLoadGameStartItem, inlined twice into la_save_game_memory_card_check, so
   it is a static inline here; it has no symbol of its own in the ROM and no
   census row, and the name is descriptive. */
static inline void setSaveGameStartItem(void)
{
    if (D_0063B558 == D_0029B5F0[0]._1E4 || D_0063B558 != D_0029B5F0[1]._1E4) {
        D_00534400[0] = 186;
    } else {
        D_00534400[0] = 187;
    }
}

/* layout_action.c:2689-2722 in the listing. */
int la_save_game_memory_card_check(int a0)
{
    _la_mask_preview_info();
    D_0063C3E8 = 0;
    lt_mask_property(0xB0, 1);
    lt_mask_property(0xB1, 1);
    debug_StdPrintfDummy(D_0061DB00, D_0063B4E0);
    switch (_la_set_current_port_new(mc, a0)) {
    case 0:
        break;
    case -1:
        debug_StdPrintfDummy(D_0063B5A8);
        if ((D_0063B4D8->_0 & 3) == 3) {
            if ((D_0063B4D8->_0 >> 2) & 1) {
                setSaveGameStartItem();
                lt_set_item_select_func(0);
                D_0063B4F4 = 0;
                return 0x12;
            }
            if (((D_0063B4D8->_0 >> 4) & 1) == 0) {
                lt_set_item_select_func(0);
                D_0063B4F4 = 0;
                return 0x20;
            }
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x1F;
    case 1:
        debug_StdPrintfDummy(D_0061DB20, (D_0063B4D8->_0 >> 5) & 1, (D_0063B4D8->_0 >> 4) & 1,
                             (D_0063B4D8->_0 & 0xA) == 2);
        if ((D_0063B4D8->_0 >> 2) & 1) {
            setSaveGameStartItem();
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x12;
        }
        if ((D_0063B4D8->_0 & 0x30) != 0 || (D_0063B4D8->_0 & 0xA) == 2) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x21;
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x20;
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

/* the progress-bar frame and fill rectangles, VMA 0x61DB38 and 0x61DB48 */
extern SprRect D_0061DB38;
extern SprRect D_0061DB48;
extern SprCol D_0063B5B8[];
extern SprCol D_0063B5C0[];
extern int D_0063A054;
extern int D_0063C3EC;
extern int D_0063B5B0;
extern int D_0063B5B4;
extern int D_0063C3D8;
/* kept local: this TU's uses of these do not fit the prototypes in GifPacket.h */
extern void gif_StartPacketPri(int pri);
extern void gif_SetZTest(int on);
extern void gif_SetZWrite(int on);
extern void gif_SetAlpha(int a, int b, int c);
extern void gif_Sprite(void *rect, unsigned int z, void *uv, void *col, int prim);
extern void gif_EndPacket(void);

/* layout_action.c:2793-2850 in the listing. */
void progressive_bar(void)
{
    SprRect frame;
    SprCol frameCol;
    SprRect back;
    SprCol backCol;
    SprRect bar;
    SprCol barCol;
    int n;
    int w;

    if (D_0063A054 != 0) {
        return;
    }
    if (D_0028F4C0[7] <= 0) {
        return;
    }
    n = D_0028F4C0[8];
    gif_StartPacketPri(12);
    gif_SetZWrite(0);
    gif_SetZTest(0);
    gif_SetAlpha(1, 2, 64);
    frame = D_0061DB38;
    frameCol = D_0063B5B8[0];
    gif_Sprite(&frame, 0xFFFFFFFF, 0, &frameCol, 1);
    back = D_0061DB48;
    memset(&backCol, 0, 4);
    backCol.a = 0x20;
    gif_Sprite(&back, 0xFFFFFFFF, 0, &backCol, 1);
    w = (float)D_0063B5B0 / (float)D_0063C3EC * -160.0f;
    bar.x = -80 - w;
    bar.y = 13;
    bar.w = w;
    bar.h = 1;
    barCol = D_0063B5C0[0];
    gif_Sprite(&bar, 0xFFFFFFFF, 0, &barCol, 1);
    gif_SetZTest(1);
    gif_SetZWrite(1);
    gif_SetAlpha(1, 4, 128);
    gif_EndPacket();
    if (n != D_0063C3D8) {
        D_0063C3D8 = n;
        D_0063B5B4++;
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/layout_action", la_mc_save_file_select);

/* the save-slot messages, VMA 0x61DB78 and 0x61DB98 */
extern char D_0061DB78[];
extern char D_0061DB98[];

/* layout_action.c:3016-3045 in the listing. */
int la_save_start_check(int a0)
{
    switch (_la_set_current_port_lock_2(mc, a0)) {
    case 0:
        break;
    case -1:
        if (((D_0063B4D8->_0 >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x1F;
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x1E;
    case 1:
        if (D_0063B550 != D_0063B4E0) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x2C;
        }
        if ((D_0063B4D8->_0 & 0xA) == 2) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x24;
        }
        if ((D_0063B4D8->_4 >> D_0063B4E8) & 1) {
            if (D_0029B5F0[D_0063B550].f[D_0063B4E8]._0 != 0xFFFFFFFF) {
                lt_set_item_select_func(0);
                D_0063B4F4 = 0;
                return 0x23;
            }
            if (D_0063B4D8->_4 != 0) {
                debug_StdPrintfDummy(D_0061DB78);
                lt_set_item_select_func(0);
                D_0063B4F4 = 0;
                return 0x26;
            }
        }
        debug_StdPrintfDummy(D_0061DB98);
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x27;
    }
    return -1;
}

/* layout_action.c:3055-3098 in the listing. */
int la_save_confirm_overwrite(int a0, int a1)
{
    if (a0) {
        D_0063B550 = D_0063B4E0;
    }
    D_0063B4F0 = 0x3FF;
    _la_set_preview_info();
    if (lt_fade_status() == 2 && (D_0028F8F4[0] & 0x10)) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x21;
    }
    switch (a1) {
    case 214:
    case 218:
        POSITIVE_SE();
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x26;
    case 215:
    case 219:
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x21;
    }
    switch (_la_set_current_port_lock_2(mc, a0)) {
    case 0:
        break;
    case -1:
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x1F;
    case 1:
        if (D_0063B5C4 == 0) {
            if (((D_0063B4D8->_0 >> 2) & 1) == 0) {
                break;
            }
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x12;
        }
        if ((D_0063B4D8->_0 >> 2) & 1) {
            break;
        }
        D_0063B5C4 = 0;
        if (D_0063B550 == D_0063B4E0) {
            break;
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x1E;
    }
    return -1;
}

/* layout_action.c:3107-3143 in the listing. */
int la_format_confirm(int a0, int a1)
{
    if (a0) {
        D_0063B550 = D_0063B4E0;
    }
    if (lt_fade_status() == 2 && (D_0028F8F4[0] & 0x10)) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x21;
    }
    switch (a1) {
    case 214:
    case 218:
        POSITIVE_SE();
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x25;
    case 215:
    case 219:
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x21;
    }
    switch (_la_set_current_port_lock_2(mc, a0)) {
    case 0:
        break;
    case -1:
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x1F;
    case 1:
        if (D_0063B5C4 == 0) {
            if (((D_0063B4D8->_0 >> 2) & 1) == 0) {
                break;
            }
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x12;
        }
        if ((D_0063B4D8->_0 >> 2) & 1) {
            break;
        }
        D_0063B5C4 = 0;
        if (D_0063B550 == D_0063B4E0) {
            break;
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x1E;
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/layout_action", la_system_save_processing);
INCLUDE_ASM("asm/nonmatchings/ico2/common/src/layout_action", la_save_processing);

extern char stage_after_skipping_demo[];
extern int CurrentTargetGObjSub;
extern void gflagInit(void);
extern void fightSoundProcessRequestPause(void);
/* kept local: this TU's uses of soundDataSegAllClose do not fit the prototype in s_init.h */
extern void soundDataSegAllClose(int a0, int a1);

/* layout_action.c:3462-3499 in the listing. */
int la_end_confirm(void)
{
    int item;

    if (lt_fade_status() == 2 && (D_0028F8F0[0].flags & 0x10)) {
        NEGATIVE_SE();
        item = lt_current_property_item();
        if (item >= 270) {
            if (item < 272) {
                lt_set_item_select_func(0);
                D_0063B4F4 = 0;
                return 0x29;
            }
            if (item < 426) {
                if (item >= 424) {
                    lt_set_item_select_func(0);
                    D_0063B4F4 = 0;
                    return 0x39;
                }
            }
        }
    }
    if (D_0028F8F0[0].flags & 0x40) {
        debug_StdPrintfDummy(stage_after_skipping_demo, lt_current_property_item());
        switch (lt_current_property_item()) {
        case 270:
        case 424:
            POSITIVE_SE();
            CurrentTargetGObjSub = 0;
            gflagInit();
            fightSoundProcessRequestPause();
            fightSoundClose();
            soundDataSegAllClose(0, 2);
            D_0063B4EC = 1;
            stgmgrForceSwitchWithFade(0.025f, 4.0f, 1);
        case 271:
            NEGATIVE_SE();
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x29;
        case 425:
            NEGATIVE_SE();
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x39;
        }
    }
    return -1;
}

extern int layoutActPushStartNew;
/* kept local: this TU's uses of iosMcDelete do not fit the prototype in mcard.h */
extern void iosMcDelete(void *a0);
extern char *strcpy(char *dst, char *src);

/* layout_action.c:3601-3642 in the listing. */
int la_delete_processing(int a0)
{
    if (a0) {
        mc[16] = D_0063B4E8;
        layoutActPushStartNew = 2;
    }
    switch (layoutActPushStartNew) {
    case 2:
        strcpy((char *)mc + 0x47C, (char *)mc + 0x4E0 + (mc[16] << 6));
        iosMcDelete(mc);
        layoutActPushStartNew++;
        break;
    case 3:
        if (iosMcSync((unsigned long *)mc) == 0) {
            break;
        }
        layoutActPushStartNew++;
        break;
    case 4:
        if (_la_mcard_error_check(mc) == 0) {
            break;
        }
        layoutActPushStartNew++;
        break;
    case 5:
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x33;
    }
    return -1;
}

extern int D_0063B5F4;
extern int laoutActionPauseRequest;
extern int startStagePauseDisableTimer;
extern int enable_game_pause;

/* layout_action.c:2576-2582 in the listing: inlined into la_game_loop and into
   la_game_over_continue, so it is a static inline here; it has no symbol of its
   own in the ROM and no census row, and the name is descriptive. */
static inline void releaseGameLoopCursor(void)
{
    if (D_0063B4FC != 0 && *(int *)(D_0063B4FC + 0x2C) != 0) {
        *(short *)(*(char **)(D_0063B4FC + 0x2C) + 0x44) = 0x100;
    }
    D_0063B4FC = 0;
}

/* layout_action.c:3720-3748 in the listing. */
int la_game_loop(int a0)
{
    if (a0) {
        if (D_0063B4F8 != 0) {
            fightSoundProcessRequestStart();
            D_0063B4F8 = 0;
        }
        releaseGameLoopCursor();
        D_0028F4C0[2] = 1;
        D_0028F4C0[5] = 0;
        iosPadEnable();
        isysGObjActiveLink(0, 1);
        D_0063B5F4 = 0;
    }
    if (D_0063B5F4 != 0) {
        laoutActionPauseRequest++;
    } else {
        laoutActionPauseRequest = 0;
    }
    if ((startStagePauseDisableTimer >= 11 && (D_0028F8F4[0] & 0x800)) ||
        (float)laoutActionPauseRequest >
            (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 0.5f) {
        if (enable_game_pause == 0) {
            return -1;
        }
        if (gflagChk(338) != 0) {
            return -1;
        }
        D_0028F4D4[0] = 1;
        D_0063B5F4 = 0;
        adpcmPauseRequest(1);
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x39;
    }
    return -1;
}

/* layout_action.c:3837-3900 in the listing. */
int la_game_over_continue(int a0)
{
    if (a0) {
        if (fadeStatus != 0) {
            scpFadeIn(3.0f);
        }
        enable_game_pause = 1;
        iosPadEnable();
        D_0063AA08 = 0;
        D_0028F4D4[0] = 1;
        AdpcmFadeCloseAll(0x200);
        AdpcmNotUseIopAreaFree();
        soundSePlayModeStop(1);
        soundSePlayModeStop(0);
        iosPadActStopAll();
        D_0063B5E8 = 0;
    } else if (D_0063B5E8 == 0) {
        if (AdpcmFreeAreaGet() != 0) {
            D_0063B5E4 = openLayoutVoice(0x34);
            D_0063B5E8 = 1;
        }
    } else if (D_0063B5E4 != 0) {
        D_0063B4FC = soundDataOpenSync(D_0071D928);
        if (D_0063B4FC != (char *)0xFFFFFFFF) {
            D_0063B5E4 = 0;
            if (D_0063B4FC != 0) {
                AdpcmPlay(*(void **)(D_0063B4FC + 0x2C));
                return -1;
            }
        }
    } else {
        switch (lt_current_property_item()) {
        case 0x1AD:
            if ((D_0028F8F4[0] & 0x40) == 0 || lt_fade_status() != 2) {
                return -1;
            }
            POSITIVE_SE();
            D_0028F4D0[0] = 1;
            D_0063B4EC = D_0063AA04;
            releaseGameLoopCursor();
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x3F;
        case 0x1AE:
            if ((D_0028F8F4[0] & 0x40) == 0 || lt_fade_status() != 2) {
                return -1;
            }
            POSITIVE_SE();
            CurrentTargetGObjSub = 0;
            gflagInit();
            D_0063B4EC = 1;
            releaseGameLoopCursor();
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x3F;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/layout_action", la_key_config);
INCLUDE_ASM("asm/nonmatchings/ico2/common/src/layout_action", la_game_option);

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
    if (D_0028F8F0[0].flags & 0x8000) {
        v = D_0028F4C0[11];
        if (v > 0) {
            CUR_SE();
            D_0028F4C0[11] = v - 1;
        }
    } else if (D_0028F8F0[0].flags & 0x2000) {
        v = D_0028F4C0[11];
        if (v < 14) {
            CUR_SE();
            D_0028F4C0[11] = v + 1;
        }
    }
    if (D_0028F8F0[0].flags & 0x10) {
        NEGATIVE_SE();
        D_0028F4C0[11] = 7;
    }
    clearAdjustScreenMarks();
    lt_default_mask_property(D_0028F4C0[11] + 395, 0);
    if (D_0028F8F0[0].flags & 0x40) {
        POSITIVE_SE();
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x3A;
    }
    return -1;
}

extern int D_0063B4D0;
extern int D_0028F4EC[];
extern int layout_boot_flag;

int la_boot_memory_card_check(void)
{
    if (D_0063B4D0 == 0) {
        return -1;
    }
    D_0028F4EC[0] = 7;
    layout_boot_flag = 1;
    lt_set_item_select_func(0);
    D_0063B4F4 = 0;
    return 0x37;
}

extern int D_0061D948[];

int la_boot_no_memory_card(int a0, int a1)
{
    debug_StdPrintfDummy(D_0061D948);
    return a1;
}

extern int D_0061D958[];

int la_boot_no_free_area(int a0, int a1)
{
    debug_StdPrintfDummy(D_0061D958);
    return a1;
}

int la_boot_confirm_memory_card(void)
{
    if (D_0028F8F4[0] & 0x40) {
        return lt_link_layout(0);
    }
    return -1;
}

extern int D_0028F4D4[];
extern int D_0063C3CC;
/* kept local: this TU's uses of stgmgrNextStagePreLoadForceStageSet do not fit the prototype in StageManager.h */
extern void stgmgrNextStagePreLoadForceStageSet(int val);

int la_scei_logo(int a0)
{
    if (a0) {
        stgmgrNextStagePreLoadForceStageSet(0);
        D_0063C3CC = lock_execIcoMisc;
        D_0028F4D4[0] = 1;
        iosPadEnable();
        isysGObjActiveLink(0, 0);
        gflagOff(386);
        if (layout_boot_flag == 0) {
            layout_boot_flag = 1;
        }
    }
    return -1;
}

int la_title_demo(void)
{
    return -1;
}

extern int D_0063B4E4;

int la_mc_preview_info(void)
{
    if (D_0063B4F0 == 0) {
        if ((1 >> D_0063B4E4) & 1) {
            return -1;
        }
    }
    _la_set_preview_info();
    return -1;
}

int la_mc_current_slot(void)
{
    lt_mask_property(0xB0, D_0063B4E0);
    lt_mask_property(0xB1, D_0063B4E0 ^ 1);
    return -1;
}

int la_mc_load_current_slot_select(void)
{
    _la_mask_preview_info();
    if (D_0028F8F4[0] & 0x40) {
        D_0063B4E0 = lt_current_property_item() - 0xBA;
        D_0063B4DC = D_0063B4E0;
        D_0063B4D8 = &D_0071D900[D_0063B4E0];
        POSITIVE_SE();
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x13;
    }
    if (D_0028F8F4[0] & 0x10) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0xC;
    }
    return -1;
}

int la_mc_save_current_slot_select(void)
{
    if (D_0028F8F4[0] & 0x40) {
        POSITIVE_SE();
        D_0063B4E0 = lt_current_property_item() - 0xBA;
        D_0063B4DC = D_0063B4E0;
        D_0063B4D8 = &D_0071D900[D_0063B4E0];
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x21;
    }
    if (D_0028F8F4[0] & 0x10) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x1C;
    }
    return -1;
}

int la_general_mc_confirm(void)
{
    if (D_0028F8F4[0] & 0x40) {
        return lt_current_property_item();
    }
    return -1;
}

int la_save_confirm_no_memory_card(int a0)
{
    if (pshPositiveOrNegative(0)) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x1C;
    }
    switch (_la_set_current_port_lock_2(mc, a0)) {
    case 0:
        break;
    case -1:
        if ((D_0063B4D8->_0 >> 1) & 1) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x1E;
        }
        D_0063B528 = 1;
        break;
    case 1:
        if ((D_0063B4D8->_0 >> 1) & 1) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x1E;
        }
        break;
    }
    return -1;
}

int la_save_confirm_no_free_area(int a0)
{
    if (pshPositiveOrNegative(0)) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x1C;
    }
    switch (_la_set_current_port_lock_2(mc, a0)) {
    case 0:
        break;
    case -1:
        if (((D_0063B4D8->_0 >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x1F;
        }
        D_0063B528 = 1;
        break;
    case 1:
        if ((D_0063B4D8->_0 >> 4) & 1) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x1E;
        }
        break;
    }
    return -1;
}

extern int D_0063B5C8;
/* kept local: the declaration in mcard.h changes this TU codegen */
extern void iosMcFormat(void *a0);

int la_format_processing(int a0)
{
    if (a0) {
        D_0063B5C8 = 0;
    }
    switch (D_0063B5C8) {
    case 0:
        mc[2] = D_0063B4E0;
        mc[3] = 0;
        iosMcFormat(mc);
        D_0063B5C8++;
        break;
    case 1:
    case 3:
        if (iosMcSync((unsigned long *)mc) == 0) {
            break;
        }
        D_0063B5C8++;
        break;
    case 2:
        if (_la_mcard_error_check(mc) > 0) {
            D_0063B5C8++;
            break;
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x2D;
    case 4:
        D_0063B5C8++;
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x27;
    }
    return -1;
}

struct S14 {
    int w[5];
};

extern int D_0071D910[];
extern int D_0029B9D0[];
extern int D_0061DC40[];
extern int D_0061DC58[];

int la_save_confirm_complete(int a0, int a1)
{
    if (a0) {
        *(struct S14 *)D_0071D910 = *(struct S14 *)D_0029B9D0;
        D_0063B4F0 = 0x3FF;
        _la_set_preview_info();
        debug_StdPrintfDummy(D_0061DC40, D_0063B4F0, D_0063B4E4);
    }
    if (a1 != -1) {
        debug_StdPrintfDummy(D_0061DC58, 0x108, 0x109, a1);
    }
    switch (a1) {
    case 0x108:
        D_0028F4D4[0] = 0;
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x36;
    case 0x109:
        D_0063B4EC = 1;
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x3F;
    }
    return -1;
}

int la_save_confirm_fail(void)
{
    return -1;
}

int la_format_confirm_fail(void)
{
    return -1;
}

int la_delete_start_check(int a0)
{
    switch (_la_set_current_port_2(mc, a0)) {
    case 0:
        break;
    case -1:
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x1E;
    case 1:
        if ((D_0063B4D8->_4 >> D_0063B4E8) & 1) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x31;
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x21;
    }
    return -1;
}

int la_delete_confirm(int a0, int a1)
{
    switch (a1) {
    case 0xD6:
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x32;
    case 0xD7:
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x1E;
    }
    return -1;
}

int la_delete_confirm_complete(void)
{
    int ret;
    if ((D_0028F8F4[0] & 0x10) == 0)
        goto fail;
    lt_set_item_select_func(0);
    D_0063B4F4 = 0;
    ret = 0x1E;
    goto out;
fail:
    ret = -1;
out:
    return ret;
}

int la_delete_confirm_fail(void)
{
    return -1;
}

extern int D_0028F4D8[];

int la_game_loading(int a0)
{
    if (a0 != 0) {
        D_0028F4D8[0] = 1;
    }
    return -1;
}

void la_playtime_count(void)
{
    if (D_0028F4D4[0] == 0) {
        D_0029B9D0[2]++;
    }
}

extern int title_demo_mode;
extern int D_0063B5F0;
extern int D_0061DC68[];

/* kept local: the declaration in StageManager.h changes this TU codegen */

int la_game_demo(int a0)
{
    if (a0) {
        if (stage_no == 1) {
            iosPadDisable();
        }
    }
    if ((D_0028F8F4[0] & 0x800) && gflagChk(388)) {
        debug_StdPrintfDummy(D_0061DC68);
        gflagOff(388);
        title_demo_mode ^= 1;
        D_0063B4EC = D_0063B5F0;
        stgmgrForceSwitchWithFade(8.0f, 4.0f, D_0063B4EC);
        if (D_0063B5F0 == 0xFFFFFFFF) {
            D_0063B5F0 = 1;
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x3F;
    }
    return -1;
}

int la_game_demo_pause(int a0)
{
    if (a0) {
        D_0028F4D4[0] = 1;
    }
    if ((D_0028F8F4[0] & 0x800) == 0) {
        return -1;
    }
    lt_set_item_select_func(0);
    D_0063B4F4 = 0;
    return 0x37;
}

int la_game_pause(int a0)
{
    if (a0) {
        D_0028F4D4[0] = 1;
        iosPadActStopAll();
        D_00534CC0[0] = 0x134;
    }
    if (lt_fade_status() != 2) {
        return -1;
    }
    if (((D_0028F8F0[0].flags & 0x40) && lt_current_property_item() == 0x127) ||
        (D_0028F8F0[0].flags & 0x810)) {
        NEGATIVE_SE(0);
        adpcmPauseRequest(0);
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x36;
    }
    return -1;
}

int la_switching_stage(void)
{
    if (fightSoundPlayChk() == 0) {
        stgmgrForceSwitchWithFade(0.4f, 4.0f, D_0063B4EC);
    }
    return -1;
}

int la_save_confirm_yesno(void)
{
    if (D_0028F8F4[0] & 0x10) {
        return lt_current_property_item();
    }
    return -1;
}

int PSH_POSITIVE_OR_NEGATIVE(int idx)
{
    int v = D_0028F8F0[idx].flags;
    if ((v & 0x40) != 0)
        goto one;
    if ((v & 0x10) == 0)
        goto zero;
one:
    return 1;
zero:
    return 0;
}

void keyconfig_reset(void)
{
    struct S40 tmp;
    tmp = D_0061D968;
    D_0029BC00 = tmp;
}

extern int D_0063B550;

int la_mc_saved_file_select(int a0)
{
    int i = a0 - 0x3E;
    int old = i;

    lt_analog2Pad();
    do {
        if (D_0028F8F4[0] & 0x1000) {
            i += 5;
        } else if (D_0028F8F4[0] & 0x4000) {
            i -= 5;
        } else if (D_0028F8F4[0] & 0x8000) {
            i -= 1;
        } else if (D_0028F8F4[0] & 0x2000) {
            i += 1;
        } else if (D_0029B5F0[D_0063B550].f[i]._0 == 0xFFFFFFFF) {
            i++;
        }
        if (i < 0) {
            i += 10;
        }
        if (i >= 10) {
            i -= 10;
        }
    } while (D_0029B5F0[D_0063B550].f[i]._0 == 0xFFFFFFFF);
    if (old != i) {
        CUR_SE();
    }
    return i + 0x3E;
}
