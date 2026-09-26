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

/* The port record's flag word is reached through a union member: the ROM's
   codegen at layout_action.c:1128 proves that store is an alias-set-0 access
   (it kills the cached D_0063B4D8 load, which a plain scalar field store does
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
   symbol; the names are ours): the preview record of the save being
   confirmed, the open request of the layout voice and the twenty game flags
   kept across a load.  The two card ports' records in front of them
   (0x71D900, 0x10 bytes) are the run's first object but stay the extern
   D_0071D900 for now: the first word of this object's .sdata run (0x63B4D8)
   is a pointer initialised to them, and that word cannot be this file's own
   object while the harness puts a named small object in .sdata.<name>
   (chain 3 pass 146). */
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
extern int D_0063B528;
extern int D_00534CC0[];
extern int D_0028F4C0[];
extern int D_0028F8F4[];

typedef struct {
    unsigned int _0;
    char _4[0x10];
} R14;

/* one card's save record; the bytes pin an alignment above 32 bits (the
   serial store keeps 0x1E4 out of the base), as the 16-aligned array at
   0x29B5F0 and its 0x1F0 stride do: a SIF DMA buffer for the card code */
typedef struct {
    R14 f[20];
    char _190[0x50];
    int _1E0;
    int _1E4;
    char _1E8[0x8];
} R1F0 __attribute__((aligned(16)));

extern R1F0 D_0029B5F0[];
extern int D_005343C8[];
extern int D_0063B554;
extern int D_0063B558;
extern int D_0063B4EC;
extern void stgmgrForceSwitchWithFade(float a0, float a1, int a2);
extern int D_0063B5C4;
extern int lock_execIcoMisc;
extern int D_0063B4DC;
extern int D_0063BE68;
extern int D_0063B54C;
extern int D_0063B5F8;
extern int D_0063B620;
extern int D_0063AA00;
extern int D_0028F4D4[];
extern R8 D_0071D900[];
extern int D_0063B53C;
extern int D_0063B540;
extern int D_0063B530;
extern int D_0063B534;
extern int D_0063B538;
extern int D_0063B52C;
extern int D_00534400[];
extern char D_0063B5A8[];
extern int D_0063B548;
extern int D_0029BC00[];
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

extern int D_0063B518;
extern int D_0063B51C;
extern int D_0063B520;
extern int D_0063B524;

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
    char _1C[4];
    int _20;
    char _24[0x20];
    int _44;
    char _48[0x434];
    McName _47C;
    char _482[0x53E];
    long long _9C0;
} McWork;

/* file-local: nothing outside this TU calls it */
int _la_memory_card_check(McWork *p, int a1);
extern char D_0061D888[];
extern void *memset(void *a0, int a1, int a2);
extern int iosMcGetInfo(void *a0);
/* kept local: this TU's uses of these two do not fit the prototypes in
   mcard.h (no caller reads a result; la_load_processing's registers after
   both calls are those of a void call) */
extern void iosMcLoadProductBlock(void *a0);
extern void iosMcGetBlockSaveInfo(void *a0);

/* layout_action.c:853-1006 in the listing.  The switch table is jtbl_0061D8D0
   (24 arms over the memory-card step, cases 0..23; VMA 0x61D8D0..0x61D930). */
int _la_memory_card_check(McWork *p, int a1)
{
    int r;
    int i;

    D_0063B4D8 = &D_0071D900[p->_8];
    switch (a1) {
    case 0:
        D_0063B4D8->_4 = 0;
        p->_C = 0;
        memset(&D_0071D900[p->_8], 0, 8);
        p->_10 = 0;
        iosMcGetInfo(p);
        mcLastResult = 0;
        /* the pointer form, not D_0029B5F0[p->_8]: the ROM's addu takes the
           scaled index first, which the subscript spelling does not give */
        (D_0029B5F0 + p->_8)->_1E4 = 0;
        (D_0029B5F0 + p->_8)->_1E0 = 0;
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
            D_0063B4D8->_0.w = (int)D_0063B4D8->_0.w & ~0x20;
            D_0063B4D8->_0.w = (int)D_0063B4D8->_0.w & ~2;
            D_0063B4D8->_0.w = (int)D_0063B4D8->_0.w & ~1;
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
            D_0063B4D8->_0.w |= 1;
            return 99;
        case 2:
            D_0063B4D8->_0.w |= 3;
            break;
        }
        switch (p->_20) {
        case 0:
            return 99;
        case 1:
            D_0063B4D8->_0.w |= 8;
            break;
        }
        if (p->_18 >= 360) {
            D_0063B4D8->_0.w |= 0x10;
        } else {
            D_0063B4D8->_0.w = (int)D_0063B4D8->_0.w & ~0x10;
        }
        a1 = 10;
        break;
    case 13:
        a1 = 20;
        break;
    case 23:
        if (p->_44 >= 11) {
            debug_StdPrintfDummy(D_0061D888);
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
            if (D_0029B5F0[p->_8].f[i]._0 != 0xFFFFFFFF) {
                break;
            }
        }
        if (i < 10) {
            if (p->_44 == 10) {
                D_0063B4D8->_0.w |= 0x20;
                D_0063B4D8->_4 = p->_9C0;
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
    return (((D_0063B4D8->_0.w >> 1) & 1) && (D_0063B4D8->_0.w & 0x38) != 8) ? 1 : -1;
}

/* layout_action.c:1039-1150 in the listing.  The three inlined copies of
   currentPortLockState are the listing's line 1029 rows. */
int _la_set_current_port_2(void *p, int a1)
{
    R8 tmp;
    int r;
    int q = 0;

    if (a1 != 0) {
        *(int *)((char *)p + 8) = 0;
        D_0063B518 = 0;
        D_0063B51C = 0;
        D_0063B4F0 = 0;
        return 0;
    }
    D_0063B4D8 = &D_0071D900[*(int *)((char *)p + 8)];
    D_0063B518 = _la_memory_card_check(p, D_0063B518);
    if (D_0063B518 == 99) {
        switch (*(int *)((char *)p + 8)) {
        case 0:
            portLockState = currentPortLockState();
            D_0063B520 = (D_0063B4D8->_0.w >> 5) & 1;
            D_0063B524 = ((D_0063B4D8->_0.w >> 1) & 1) && (D_0063B4D8->_0.w & 0x38) != 8;
            /* listing line 1069: the whole 8-byte record is copied to the frame
               and never read again (the ROM ldl/ldr/sdl/sdr pair). */
            tmp = *D_0063B4D8;
            *(int *)((char *)p + 8) = 1;
            D_0063B518 = 0;
            break;
        case 1:
            D_0063B518 = 100;
            switch (portLockState) {
            case 1:
                r = currentPortLockState();
                switch (r) {
                case 1:
                    r = D_0063B4D8->_0.w >> 5;
                    r &= 1;
                    if ((D_0063B4D8->_0.w >> 1) & 1) {
                        if ((D_0063B4D8->_0.w & 0x38) != 8) {
                            q = 1;
                        }
                    }
                    if (D_0063B524 != 0 && q != 0) {
                        D_0071D900[0]._0.w |= 4;
                        D_0071D900[1]._0.w |= 4;
                    }
                    if (D_0063B520 != 0 && r != 0) {
                        D_0071D900[0]._0.w |= 0x40;
                        D_0071D900[1]._0.w |= 0x40;
                    }
                    if (D_0063B4DC >= 0) {
                        D_0063B4E0 = D_0063B4DC;
                    } else if (D_0063B520 != 0) {
                        D_0063B4E0 = 0;
                    } else if ((D_0063B4D8->_0.w >> 5) & 1) {
                        D_0063B4E0 = 1;
                    }
                    break;
                case -1:
                    D_0063B4DC = r;
                    D_0063B4E0 = 0;
                    D_0063B4D8 = &D_0071D900[0];
                    D_0063B4D8->_0.w = (int)D_0063B4D8->_0.w & ~4;
                    D_0063B4D8->_0.w = (int)D_0063B4D8->_0.w & ~0x40;
                    break;
                }
                break;
            case -1:
                r = currentPortLockState();
                switch (r) {
                case 1:
                    D_0063B4E0 = r;
                    D_0063B4D8 = &D_0071D900[1];
                    D_0063B4D8->_0.w = (int)D_0063B4D8->_0.w & ~4;
                    D_0063B4D8->_0.w = (int)D_0063B4D8->_0.w & ~0x40;
                    break;
                case -1:
                    D_0063B4E0 = 0;
                    D_0063B4D8 = &D_0071D900[0];
                    if ((D_0071D900[0]._0.w & 1) || (D_0071D900[1]._0.w & 1)) {
                        D_0071D900[0]._0.w |= 1;
                    }
                    if (((D_0071D900[0]._0.w >> 1) & 1) || ((D_0071D900[1]._0.w >> 1) & 1)) {
                        D_0063B4D8->_0.w |= 2;
                    }
                    D_0063B4D8->_0.w = (int)D_0063B4D8->_0.w & ~4;
                    D_0063B4D8->_0.w = (int)D_0063B4D8->_0.w & ~0x40;
                    _la_set_current_port_2(p, 1);
                    return -1;
                }
                break;
            }
            D_0063B4D8 = &D_0071D900[D_0063B4E0];
            _la_set_current_port_2(p, 1);
            return 1;
        }
    }
    return 0;
}

/* layout_action.c:1157-1218 in the listing. */
int _la_set_current_port_lock_2(void *p, int a1)
{
    R8 tmp;
    int r;
    int a;
    int q;

    if (a1 != 0 || D_0063B528 != 0) {
        *(int *)((char *)p + 8) = D_0063B4E0;
        D_0063B52C = 0;
        D_0063B528 = 0;
        D_0063B530 = 0;
        D_0063B4F0 = 0;
        return 0;
    }
    D_0063B4D8 = &D_0071D900[*(int *)((char *)p + 8)];
    D_0063B52C = _la_memory_card_check(p, D_0063B52C);
    if (D_0063B52C != 99) {
        return 0;
    }
    r = currentPortLockState();
    lock2PortState = r;
    D_0063B534 = (D_0063B4D8->_0.w >> 5) & 1;
    D_0063B538 = ((D_0063B4D8->_0.w >> 1) & 1) && (D_0063B4D8->_0.w & 0x38) != 8;
    tmp = *D_0063B4D8;
    switch (lock2PortState) {
    case 1:
        a = D_0063B4D8->_0.w >> 5;
        a &= 1;
        q = 0;
        if ((D_0063B4D8->_0.w >> 1) & 1) {
            if ((D_0063B4D8->_0.w & 0x38) != 8) {
                q = 1;
            }
        }
        if (D_0063B538 != 0 && q != 0) {
            D_0071D900[*(int *)((char *)p + 8)]._0.w |= 4;
        }
        if (D_0063B534 != 0 && a != 0) {
            D_0071D900[*(int *)((char *)p + 8)]._0.w |= 0x40;
        }
        _la_set_current_port_lock_2(p, 1);
        return 1;
    case -1:
        D_0063B4D8 = &D_0071D900[D_0063B4E0];
        D_0063B4D8->_0.w = (int)D_0063B4D8->_0.w & ~4;
        D_0063B4D8->_0.w = (int)D_0063B4D8->_0.w & ~0x40;
        return -1;
    }
    return 0;
}

/* layout_action.c:1222-1288 in the listing.  The switch table is jtbl_0061D930
   (5 arms, selector D_0063B53C, cases 0..4). */
int _la_set_current_port_new(McWork *p, int a1)
{
    int r = 0;
    int v;

    if (a1) {
        D_0063B53C = 0;
        D_0063B4E0 = -1;
    }
    switch (D_0063B53C) {
    case 0:
    case 2:
        D_0063B4E0++;
        D_0063B540 = 1;
        D_0063B53C++;
        break;
    case 1:
        port0LockResult = _la_set_current_port_lock_2(p, D_0063B540);
        D_0063B540 = 0;
        if (port0LockResult == 0) {
            break;
        }
        D_0063B53C++;
        break;
    case 3:
        port1LockResult = _la_set_current_port_lock_2(p, D_0063B540);
        D_0063B540 = 0;
        if (port1LockResult == 0) {
            break;
        }
        D_0063B53C++;
        break;
    case 4:
        if (((D_0071D900[0]._0.w >> 1) & 1) && ((D_0071D900[1]._0.w >> 1) & 1))
            v = 1;
        else
            v = 0;
        D_0071D900[0]._0.bit.f2 = D_0071D900[1]._0.bit.f2 = v;
        if (((D_0071D900[0]._0.w >> 5) & 1) && ((D_0071D900[1]._0.w >> 5) & 1))
            v = 1;
        else
            v = 0;
        D_0071D900[0]._0.bit.f6 = D_0071D900[1]._0.bit.f6 = v;
        if (port0LockResult == 1) {
            D_0063B4E0 = 0;
            r = 1;
        } else if (port1LockResult == 1) {
            D_0063B4E0 = 1;
            r = 1;
        } else {
            if (((D_0071D900[0]._0.w >> 1) & 1) == 0 && D_0071D900[1]._0.bit.f1 == 1) {
                D_0063B4E0 = 1;
            } else {
                D_0063B4E0 = 0;
            }
            r = -1;
        }
        p->_8 = D_0063B4E0;
        D_0063B4D8 = &D_0071D900[D_0063B4E0];
        break;
    }
    return r;
}

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
    *(struct S40 *)D_0029BC00 = tmp;
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
        continueIcoMiscLock = lock_execIcoMisc;
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
        if ((D_0063B4D8->_0.w & 0x22) == 2) {
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
        newGameIcoMiscLock = lock_execIcoMisc;
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
        if ((D_0063B4D8->_0.w >> 5) & 1) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0xC;
        }
        D_0063B54C = 1;
        break;
    }
    return -1;
}

extern int D_0063B4E4;
extern int D_0063B55C;
extern int D_0063B560;
extern int D_0063B564;
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
    int port = D_0063B550;
    int no = (D_0029B5F0 + port)->_1E0;
    if (D_0071D900[port]._4 == 0 || D_0029B5F0[port].f[no]._0 == 0xFFFFFFFF)
        return 0;
    return no;
}

/* layout_action.c:1789-1794 in the listing: inlined once, into
   la_mc_file_select, so it is a static inline here too. */
static inline int mcFileNoOfPort(void)
{
    int port = D_0063B550;

    if (D_0063B558 == (D_0029B5F0 + port)->_1E4)
        return D_0063B55C;
    return mcCurrentFileNo();
}

/* layout_action.c:1836-1912 in the listing. */
int la_mc_file_select(int a0)
{
    int i;

    D_0063B4E4 = lt_current_property_item() - 62;

    if (a0) {
        D_0063B564 = 1;
        D_0063B560 = 0;
    }

    if (D_0063B4F4 == 0) {
        D_0063B620 = 1;
        return -1;
    }

    if (D_0063B564 != 0) {
        D_0063B564 = 0;
        if (mcLoadMode != 0) {
            D_0063B4E4 = mcCurrentFileNo();
        } else {
            D_0063B4E4 = mcFileNoOfPort();
        }
        D_00534324[0] = D_0063B4E4 + 62;
        D_0063B560 = 1;
    }

    for (i = 0; i < 10; i++) {
        if (((D_0063B4F0 >> i) & 1) && D_0029B5F0[D_0063B550].f[i]._0 != 0xFFFFFFFF) {
            lt_mask_property(i + 62, 0);
            lt_mask_property(i + 52, 1);
        } else {
            lt_mask_property(i + 62, 1);
            lt_mask_property(i + 52, 0);
        }
    }

    previewInfo = *(struct S14 *)&D_0029B5F0[D_0063B550].f[D_0063B4E4];

    return (D_0028F8F0[0].flags & 0x50) ? D_0063B4E4 : -1;
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
    int fps = ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * D_0028F4C0[1];

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

    if (((D_0063B4F0 >> D_0063B4E4) & 1) == 0) {
        return;
    }
    if (D_0029B5F0[D_0063B550].f[D_0063B4E4]._0 == 0xFFFFFFFF) {
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
    mcLoadMode = 1;
    lt_mask_property(0xB0, 1);
    lt_mask_property(0xB1, 1);
    switch (_la_set_current_port_2(mc, a0)) {
    case 0:
        if (mcLastResult == 0 || mcLastResult == -14) {
            return -1;
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x16;
    case -1:
        if ((D_0063B4D8->_0.w >> 1) & 1) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x17;
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x16;
    case 1:
        if ((D_0063B4D8->_0.w >> 6) & 1) {
            setLoadGameStartItem();
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x11;
        }
        if ((D_0063B4D8->_0.w >> 5) & 1) {
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

extern int D_0063B568;
extern int D_0063B56C;
/* the two load-select trace messages, VMA 0x63B570 and 0x63B578 (.sdata) */
extern char D_0063B570[];
extern char D_0063B578[];
int la_mc_saved_file_select(int a0);

/* layout_action.c:2139-2235 in the listing. */
int la_mc_load_file_select(int a0, int a1)
{
    int r;

    if (a0) {
        D_0063B4F0 = 0;
        D_0063B4DC = D_0063B550 = D_0063B4E0;
        D_0063B56C = 0;
    }

    if (D_0063B4F0 != 0) {
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

    if (D_0028F8F4[0] & 0x10) {
        NEGATIVE_SE();
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 12;
    }

    if ((D_0063B4F0 != 0 || D_0063B56C != 0) && (D_0028F8F4[0] & 0x40)) {
        POSITIVE_SE();
        if (D_0029B5F0[D_0063B550].f[a1]._0 != 0xFFFFFFFF) {
            D_0063B4E8 = a1;
            D_0063B4DC = D_0063B550;
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 21;
        }
    }

    r = _la_set_current_port_lock_2(mc, a0);
    switch (r) {
    case -1:
        if (((D_0063B4D8->_0.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 22;
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 23;
    case 1:
        if (((D_0063B4D8->_0.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 22;
        }
        if ((D_0063B4D8->_0.w & 0x22) == 2) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 23;
        }
        break;
    case 0:
    default:
        return -1;
    }

    if (D_0063B4F0 != 0) {
        if (D_0063B568 == 0) {
            if (((D_0063B4D8->_0.w >> 6) & 1) != 0) {
                debug_StdPrintfDummy(D_0063B570);
                lt_set_item_select_func(0);
                D_0063B4F4 = 0;
                return 17;
            }
        } else if (((D_0063B4D8->_0.w >> 6) & 1) == 0) {
            debug_StdPrintfDummy(D_0063B578);
            D_0063B568 = (D_0063B4D8->_0.w >> 6) & 1;
        }
    } else {
        D_0063B568 = (D_0063B4D8->_0.w >> 6) & 1;
        D_0063B4F0 = D_0063B4D8->_4;
        D_0063B4F4 = r;
        if ((D_0063B4D8->_0.w & 0xA) == 2) {
            D_0063B56C = r;
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
        if ((D_0063B4D8->_0.w & 0x32) == 2 || (D_0063B4D8->_0.w & 0x22) == 2) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x17;
        }
        if ((D_0063B4D8->_0.w >> 1) & 1) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x14;
        }
        D_0063B528 = 1;
        break;
    case 1:
        if ((D_0063B4D8->_0.w & 0x32) == 2 || (D_0063B4D8->_0.w & 0x22) == 2) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x17;
        }
        if ((D_0063B4D8->_0.w >> 1) & 1) {
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
        if (((D_0063B4D8->_0.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x16;
        }
        D_0063B528 = 1;
        break;
    case 1:
        if ((D_0063B4D8->_0.w >> 5) & 1) {
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
        if (mcLastResult == 0 || mcLastResult == -14) {
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
        if ((D_0063B4D8->_0.w & 3) != 3) {
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

extern int D_0063B580;
/* the load-phase messages in .rodata, VMA 0x61D9A8..0x61DA30 */
extern int D_0061D9A8[];
extern int D_0061D9C0[];
extern int D_0061D9D0[];
extern int D_0061D9E8[];
extern int D_0061D9F8[];
extern int D_0061DA08[];
extern int D_0061DA20[];
extern int D_0061DA30[];
/* "chk:%d\n" and "case 4\n", short strings in this TU's .sdata at VMA
   0x63B588 and 0x63B590 */
extern int D_0063B588[];
extern int D_0063B590[];
/* the twenty game-flag ids the load carries across gflagInit */
extern int D_004E3B40[];
extern char D_004DA788[];
extern char D_004DD700[];
extern int D_0063A650;
extern int D_0063AA04;
/* the current game's save record, as in la_system_save_processing */
extern int D_0029B9D0[];
/* kept local with gamesys.h's prototype, which this TU does not include */
extern void gamesysMemoryLoad(void **tbl, int a1, void *a2);
/* kept local: this TU's uses of iosMcLoadGameBlock do not fit the prototype
   in mcard.h, exactly as in common/src/debug.c */
extern void iosMcLoadGameBlock(void *a0, void *buf);
extern void ACTGame_SetActors_Debug(int a0, int a1);

/* layout_action.c:1796-1800 in the listing: the saved file's serial read
   from the port's record, with the file number kept beside it; inlined into
   la_load_processing directly and into la_save_processing through
   mcSetSavedFile, with no symbol of its own in the ROM (the name is ours). */
static inline int mcSetFileNo(int port, int no)
{
    int serial = (D_0029B5F0 + port)->_1E4;

    D_0063B55C = no;
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
        keepFlags[i] = gflagChk(D_004E3B40[i]);
    }
}

/* layout_action.c:2378-2382 in the listing, the other half of the pair. */
static inline void gflagRestoreState(void)
{
    unsigned int i;

    for (i = 0; i < 20; i++) {
        if (keepFlags[i]) {
            gflagOn(D_004E3B40[i]);
        } else {
            gflagOff(D_004E3B40[i]);
        }
    }
}

/* layout_action.c:2393-2536 in the listing, with the menu-close pair of lines
   707-708, the play time of lines 829-832, the flag-keeping pair of lines
   2370-2382 and the serial readback of lines 1798-1799 inlined into it.  The
   switch table is jtbl_0061DA40 (21 arms, selector D_0063B580, cases 0-10 and
   20). */
int la_load_processing(int a0)
{
    int err;
    int hour;
    int min;
    int sec;

    debug_StdPrintfDummy(D_0061D9A8);
    if (a0) {
        D_0063B580 = 0;
    }

    switch (D_0063B580) {
    case 0:
        strcpy((char *)mc + 0x47C, "game.");
        mc[16] = D_0063B4E8;
        mc[2] = D_0063B4E0;
        mc[3] = 0;
        iosMcGetBlockSaveInfo(mc);
        D_0063B580++;
        break;
    case 1:
    case 3:
        if (iosMcSync((unsigned long *)mc) != 0) {
            D_0063B580++;
        }
        break;
    case 2:
        D_0063B580++;
        break;
    case 6:
    case 9:
        debug_StdPrintfDummy(D_0061D9C0, D_0063B580);
        err = _la_mcard_error_check(mc);
        if (err > 0) {
            D_0063B580++;
            debug_StdPrintfDummy(D_0061D9D0, D_0063B580, err);
            debug_StdPrintfDummy(D_0061D9E8);
            return -1;
        }
        debug_StdPrintfDummy(D_0061D9F8);
        debug_StdPrintfDummy(D_0063B588, err);
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 46;
    case 4:
        debug_StdPrintfDummy(D_0063B590);
        if (((1 << mc[16]) & ((McWork *)mc)->_9C0) == 0) {
            D_0063B580 = 20;
        } else {
            iosMcLoadProductBlock(mc);
            D_0063B580++;
        }
        break;
    case 5:
    case 8:
        debug_StdPrintfDummy(D_0061D9C0, D_0063B580);
        if (iosMcSync((unsigned long *)mc) != 0) {
            D_0063B580++;
        }
        break;
    case 7:
        debug_StdPrintfDummy(D_0061D9C0, D_0063B580);
        debug_StdPrintfDummy(D_0061DA08);
        iosMcLoadGameBlock(mc, D_004DD700);
        D_0063B580++;
        break;
    case 10:
        gflagKeepState();
        gflagInit();
        gamesysMemoryLoad(D_004DA788, D_004DD700, 0);
        gflagRestoreState();
        D_0028F4C0[3] = 1;
        D_0028F4C0[4] = 1;
        debug_StdPrintfDummy(D_0061DA20);
        D_0063B580 = 0;
        *(struct S14 *)D_0029B9D0 = *(struct S14 *)&D_0029B5F0[mc[2]].f[mc[16]];
        playTime((struct S14 *)D_0029B9D0, &hour, &min, &sec);
        D_0063B558 = mcSetFileNo(mc[2], mc[16]);
        debug_StdPrintfDummy(D_0061DA30, D_0063AA04);
        D_0063A650 = 1;
        if (D_0063BE6C != 0) {
            *(short *)(*(int *)(D_0063BE6C + 0x2C) + 0x44) = 0x40;
        }
        D_0063BE6C = 0;
        if (gflagChk(395)) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 9;
        }
        stgmgrForceSwitchWithFade(0.05f, 4.0f, D_0063AA04);
        ACTGame_SetActors_Debug(D_0063AA04, 0);
        return -1;
    case 20:
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 20;
    }
    return -1;
}

extern int fadeStatus;
extern void scpFadeIn(float sec);
extern int D_0063AA08;
extern void soundSePlayModeStop(int a0);
extern void iosPadActStopAll(void);
extern int D_0063B5E4;
extern int D_0063B5E8;
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
    soundDataOpen(&voiceOpenReq, 2, no, 1, 0);
    return 1;
}

/* layout_action.c:2591-2678 in the listing. */
int la_mc_confirm_save_file(int a0, int a1)
{
    _la_mask_preview_info();
    lt_mask_property(0xB0, 1);
    lt_mask_property(0xB1, 1);
    if (a0) {
        D_0028F4D4[0] = 1;
        fightSoundProcessRequestPause();
        D_0063B4F8 = 1;
        CheckPoint();
        D_0063B59C = 0;
        D_0063B5A0 = 0;
    }
    if (D_0063B59C == 0) {
        if (AdpcmFreeAreaGet() != 0) {
            D_0063B598 = openLayoutVoice(0x16);
            D_0063B59C = 1;
        } else {
            debug_StdPrintfDummy(D_0061DA98);
            if (AdpcmNotUseIopAreaFree() != 0) {
                debug_StdPrintfDummy(D_0061DAB8);
                return -1;
            }
            if (D_0063B5A0-- < 0) {
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
        do {
            _la_mask_preview_info();
        } while (0);
        if (D_0063B598 != 0) {
            D_0063B4FC = soundDataOpenSync(&voiceOpenReq);
            if (D_0063B4FC != (char *)0xFFFFFFFF) {
                D_0063B598 = 0;
                if (D_0063B4FC != 0) {
                    AdpcmPlay(*(void **)(D_0063B4FC + 0x2C));
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
                    D_0063B4F4 = 0;
                    return 0x1E;
                case 215:
                    NEGATIVE_SE();
                    D_0028F4D4[0] = 0;
                    lt_set_item_select_func(0);
                    D_0063B4F4 = 0;
                    return 0x36;
                }
            }
            if (lt_fade_status() != 2) {
                return -1;
            }
            if ((D_0028F8F4[0] & 0x10) == 0) {
                return -1;
            }
            if (stage_no == 0x3F) {
                return -1;
            }
            NEGATIVE_SE();
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x36;
        }
    }
    return -1;
}

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
    mcLoadMode = 0;
    lt_mask_property(0xB0, 1);
    lt_mask_property(0xB1, 1);
    debug_StdPrintfDummy(D_0061DB00, D_0063B4E0);
    switch (_la_set_current_port_new(mc, a0)) {
    case 0:
        break;
    case -1:
        debug_StdPrintfDummy(D_0063B5A8);
        if ((D_0063B4D8->_0.w & 3) == 3) {
            if ((D_0063B4D8->_0.w >> 2) & 1) {
                setSaveGameStartItem();
                lt_set_item_select_func(0);
                D_0063B4F4 = 0;
                return 0x12;
            }
            if (((D_0063B4D8->_0.w >> 4) & 1) == 0) {
                lt_set_item_select_func(0);
                D_0063B4F4 = 0;
                return 0x20;
            }
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 0x1F;
    case 1:
        debug_StdPrintfDummy(D_0061DB20, (D_0063B4D8->_0.w >> 5) & 1, (D_0063B4D8->_0.w >> 4) & 1,
                             (D_0063B4D8->_0.w & 0xA) == 2);
        if ((D_0063B4D8->_0.w >> 2) & 1) {
            setSaveGameStartItem();
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x12;
        }
        if ((D_0063B4D8->_0.w & 0x30) != 0 || (D_0063B4D8->_0.w & 0xA) == 2) {
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
extern int fbKeep;
extern int D_0063B5B0;
extern int D_0063B5B4;
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

    if (fbKeep != 0) {
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
    w = (float)D_0063B5B0 / (float)barTotal * -160.0f;
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
    if (n != barLastStep) {
        barLastStep = n;
        D_0063B5B4++;
    }
}

/* the two save-select trace messages, VMA 0x61DB58 and 0x61DB68 */
extern char D_0061DB58[];
extern char D_0061DB68[];

/* layout_action.c:2860-2951 in the listing. */
int la_mc_save_file_select(int a0, int a1)
{
    int r;

    if (a0) {
        D_0063B4F0 = 0;
        D_0063B4DC = D_0063B550 = D_0063B4E0;
        saveSelectReady = 0;
        barTotal = 2;
        D_0063B5B0 = 0;
    }

    if (D_0063B4F4 != 0) {
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

    if (D_0063B4F4 != 0) {
        if (D_0028F8F4[0] & 0x10) {
            NEGATIVE_SE();
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 28;
        }
    }

    if ((D_0063B4F0 != 0 || saveSelectReady != 0) && (D_0028F8F4[0] & 0x40)) {
        POSITIVE_SE();
        D_0063B4E8 = a1;
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 34;
    }

    r = _la_set_current_port_lock_2(mc, a0);
    switch (r) {
    case -1:
        if (((D_0063B4D8->_0.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 31;
        }
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 32;
    case 1:
        if (((D_0071D900[D_0063B550]._0.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 28;
        }
        if (D_0063B4F0 != 0) {
            if (D_0063B5C4 == 0) {
                if (((D_0063B4D8->_0.w >> 2) & 1) != 0) {
                    lt_set_item_select_func(0);
                    D_0063B4F4 = 0;
                    return 18;
                }
            } else if (((D_0063B4D8->_0.w >> 2) & 1) == 0) {
                D_0063B5C4 = 0;
            }
        } else {
            D_0063B5C4 = (D_0063B4D8->_0.w >> 2) & 1;
            if ((D_0063B4D8->_0.w >> 3) & 1) {
                debug_StdPrintfDummy(D_0061DB58);
                saveSelectReady = r;
            } else if ((D_0063B4D8->_0.w & 0xA) == 2) {
                debug_StdPrintfDummy(D_0061DB68);
                if (D_0063B550 == D_0063B4E0) {
                    D_0063B4F4 = r;
                }
                saveSelectReady = r;
                return -1;
            }
        }
        if (D_0063B550 == D_0063B4E0) {
            D_0063B4F0 = D_0063B4D8->_4;
            D_0063B4F4 = 1;
        }
        break;
    case 0:
    default:
        return -1;
    }
    return -1;
}

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
        if (((D_0063B4D8->_0.w >> 1) & 1) == 0) {
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
        if ((D_0063B4D8->_0.w & 0xA) == 2) {
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
            if (((D_0063B4D8->_0.w >> 2) & 1) == 0) {
                break;
            }
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x12;
        }
        if ((D_0063B4D8->_0.w >> 2) & 1) {
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
            if (((D_0063B4D8->_0.w >> 2) & 1) == 0) {
                break;
            }
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x12;
        }
        if ((D_0063B4D8->_0.w >> 2) & 1) {
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

extern int D_0063B5CC;
/* the system-save error message, VMA 0x61DBB8 */
extern int D_0061DBB8[];
/* kept local: this TU's uses of the block calls do not fit the prototypes in
   mcard.h, exactly as in common/src/debug.c */
extern void iosMcSaveIconBlock(void *a0);
extern void iosMcSaveProductBlock(void *a0);
extern void iosMcSaveGameBlock(void *a0, void *buf);
extern char D_004DD700[];
/* the current game's save record (la_save_confirm_complete copies the
   preview from it) */
extern int D_0029B9D0[];
/* kept local: this TU's spelling predates sce/libc/string.h; the game compiled
   with builtins live, so a copy of a constant string is the builtin block
   move */
extern char *strcpy(char *dst, const char *src);

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
extern int rand(void);

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

/* layout_action.c:3203-3294 in the listing, with the serial builder of lines
   1768-1775 and the play time of lines 826-841 inlined into it (its results
   are unused here, so the record passed is not visible in the bytes).  The
   switch table is jtbl_0061DBD0 (11 arms, selector D_0063B5CC, cases 0-10). */
int la_system_save_processing(int a0)
{
    int err;
    int i;
    int hour;
    int min;
    int sec;

    D_0063B4D8 = &D_0071D900[mc[2]];
    if (a0) {
        D_0063B5CC = 0;
        systemSaveRetry = 0;
        barTotal = 14;
    }

    progressive_bar();

    switch (D_0063B5CC) {
    case 0:
        strcpy((char *)mc + 0x47C, "game.");
        mc[16] = systemSaveRetry;
        mc[2] = D_0063B4E0;
        mc[3] = 0;
        iosMcGetBlockSaveInfo(mc);
        D_0063B5CC++;
        D_0063B4D8->_0.w = (int)D_0063B4D8->_0.w & ~0x80;
        D_0063B5B0++;
        break;
    case 2:
        iosMcSaveIconBlock(mc);
        D_0063B5CC++;
        break;
    case 6:
    case 9:
        err = _la_mcard_error_check(mc);
        if (err > 0) {
            D_0063B5CC++;
            debug_StdPrintfDummy(D_0061DBB8, D_0063B5CC, err);
            return -1;
        }
        D_0063B4D8->_0.w |= 0x80;
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 44;
    case 4:
        for (i = 0; i < 10; i++) {
            D_0029B5F0[mc[2]].f[i]._0 = 0xFFFFFFFF;
        }
        while ((D_0029B5F0[mc[2]]._1E4 = mcMakeSerial()) == 0)
            ;
        playTime((struct S14 *)D_0029B9D0, &hour, &min, &sec);
        iosMcSaveProductBlock(mc);
        D_0063B5CC++;
        D_0063B5B0++;
        break;
    case 1:
    case 3:
    case 5:
    case 8:
        if (iosMcSync((unsigned long *)mc) != 0) {
            D_0063B5CC++;
        }
        break;
    case 7:
        iosMcSaveGameBlock(mc, D_004DD700);
        D_0063B5CC++;
        D_0063B5B0++;
        break;
    case 10:
        D_0063B5CC = 7;
        systemSaveRetry++;
        mc[16] = systemSaveRetry;
        if (systemSaveRetry >= 10) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 38;
        }
        break;
    }
    return -1;
}

extern int D_0063B5D0;
/* the second save-phase message, VMA 0x61DC00 */
extern int D_0061DC00[];
extern int GetSaveSofaLayoutID(void);

/* layout_action.c:1802-1805 in the listing: the save side's readback, the
   serial kept as both the saved and the current one; inlined into
   la_save_processing (the name is ours). */
static inline void mcSetSavedFile(void)
{
    int serial = mcSetFileNo(mc[2], mc[16]);

    D_0063B558 = serial;
    D_0063B554 = serial;
}

/* layout_action.c:3309-3410 in the listing, with the menu-close pair of lines
   707-708, the play time of lines 829-832, the serial builder of lines
   1768-1775 and the readback of lines 1798-1804 inlined into it.  The switch
   table is jtbl_0061DC10 (11 arms, selector D_0063B5D0, cases 0-10). */
int la_save_processing(int a0)
{
    int err;
    int hour;
    int min;
    int sec;

    D_0063B4D8 = &D_0071D900[mc[2]];
    if (a0) {
        D_0063B4F0 = 0;
        D_0063B5D0 = 0;
    }

    progressive_bar();

    switch (D_0063B5D0) {
    case 0:
        strcpy((char *)mc + 0x47C, "game.");
        mc[16] = D_0063B4E8;
        mc[2] = D_0063B4E0;
        mc[3] = 0;
        iosMcGetBlockSaveInfo(mc);
        D_0063B5D0++;
        D_0063B4D8->_0.w = (int)D_0063B4D8->_0.w & ~0x80;
        break;
    case 1:
        if (iosMcSync((unsigned long *)mc) != 0) {
            D_0063B5D0 = 4;
        }
        break;
    case 2:
        iosMcSaveIconBlock(mc);
        D_0063B5D0++;
        break;
    case 6:
    case 9:
        err = _la_mcard_error_check(mc);
        if (err > 0) {
            D_0063B5D0++;
            debug_StdPrintfDummy(D_0061DBB8, D_0063B5D0, err);
            return -1;
        }
        D_0063B4D8->_0.w |= 0x80;
        debug_StdPrintfDummy(D_0061DC00, D_0063B5D0);
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 44;
    case 4:
        D_0029B9D0[0] = stage_no;
        D_0029B9D0[3] = GetSaveSofaLayoutID();
        D_0029B9D0[1] = D_0063AA00;
        *(struct S14 *)&D_0029B5F0[mc[2]].f[mc[16]] = *(struct S14 *)D_0029B9D0;
        playTime((struct S14 *)D_0029B9D0, &hour, &min, &sec);
        (D_0029B5F0 + mc[2])->_1E0 = mc[16];
        if ((D_0029B5F0 + mc[2])->_1E4 == (D_0029B5F0 + (mc[2] ^ 1))->_1E4) {
            do {
                while ((D_0029B5F0[mc[2]]._1E4 = mcMakeSerial()) == 0)
                    ;
            } while ((D_0029B5F0 + mc[2])->_1E4 == (D_0029B5F0 + (mc[2] ^ 1))->_1E4);
        }
        mcSetSavedFile();
        iosMcSaveProductBlock(mc);
        D_0063B5D0++;
        break;
    case 3:
    case 5:
    case 8:
        if (iosMcSync((unsigned long *)mc) != 0) {
            D_0063B5D0++;
            D_0063B5B0++;
        }
        break;
    case 7:
        CheckPoint();
        iosMcSaveGameBlock(mc, D_004DD700);
        D_0063B5D0++;
        break;
    case 10:
        D_0063B5D0 = 0;
        lt_set_item_select_func(0);
        D_0063B4F4 = 0;
        return 41;
    }
    return -1;
}

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
        D_0063B4FC = soundDataOpenSync(&voiceOpenReq);
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

/* the eight pad button codes the key-config screen offers, VMA 0x004E3B58, and
   the six-plus-two slot assignments it edits, VMA 0x004E3B78 */
extern int D_004E3B58[];
extern int D_004E3B78[];
extern int D_0063B5EC;
/* the custom pad configuration ios/pad.c owns, reached here as its words */
extern int iosPadConfCustom[];

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
        if (v == D_004E3B58[i]) {
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
        if (v == D_004E3B58[D_004E3B78[i]]) {
            return i;
        }
    }
    return -1;
}

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
            if ((D_0063B5EC >> i) & 1) {
                D_004E3B78[keyCodeIndex(D_0029BC00[i])] = keyCodeIndex(1 << i);
            }
        }
    }
    if (sel >= 0 && sel < 6) {
        m = D_0028F8F0[0].flags & D_0063B5EC;
        if (m != 0 && m == D_0028F8F0[0].flags) {
            k = keyCodeIndex(m);
            POSITIVE_SE();
            if (k != -1) {
                n = keyAssignIndex(m);
                if (n != -1) {
                    D_004E3B78[n] = D_004E3B78[sel];
                }
                D_004E3B78[sel] = k;
            }
        }
    }
    keyconfigMaskAll();
    for (i = 0; i < 6; i++) {
        lt_mask_property(i * 8 + 342 + D_004E3B78[i], 0);
        lt_default_mask_property(i * 8 + 342 + D_004E3B78[i], 0);
    }
    if (D_0028F8F0[0].flags & 0x40) {
        if (lt_current_property_item() == 391) {
            for (i = 7; i >= 0; i--) {
                D_004E3B78[i] = i;
            }
            NEGATIVE_SE();
        }
        if (lt_current_property_item() == 390) {
            POSITIVE_SE();
            for (i = 0; i < 16; i++) {
                if ((D_0063B5EC >> i) & 1) {
                    iosPadConfCustom[i + 44] = 0;
                } else {
                    iosPadConfCustom[i + 44] = 1 << i;
                }
            }
            for (i = 0; i < 8; i++) {
                D_0029BC00[keyBitIndex(D_004E3B58[D_004E3B78[i]])] = D_004E3B58[i];
            }
            keyconfigMaskAll();
            for (i = 0; i < 6; i++) {
                lt_default_mask_property(i * 8 + 342 + D_004E3B78[i], 0);
                lt_mask_property(i * 8 + 342 + D_004E3B78[i], 0);
            }
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 58;
        }
    }
    return -1;
}

extern int CurrentTargetGObj;
extern int D_00639EA0;
/* the option screen's layout item id tables, VMA 0x61DC78, 0x61DC90, 0x61DCA8
   and 0x61DCB0, each 16-byte aligned in this TU's .rodata */
extern int D_0061DC78[];
extern int D_0061DC90[];
extern int D_0061DCA8[];
extern int D_0061DCB0[];
/* kept local: this TU carries no other use of s_init.h or StageAnimation.h */
extern int soundOutputModeGet(void);
extern void soundOutputModeSet(int a0);
extern void stage_SetLoopFlag(int key, int a1);
extern void stage_SetAnimation(int a0, int a1, int a2);

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
    if ((D_0028F8F0[0]._0 & 0xA000) != 0) {
        cur = CurrentTargetGObj;
        sel = CurrentTargetGObjSub;
        switch (lt_current_property_item()) {
        case 300:
            if ((D_0028F8F0[0].flags & 0x8000) != 0) {
                sel--;
                if (sel < 0) {
                    sel = 4;
                }
                CUR_SE();
            } else if ((D_0028F8F0[0].flags & 0x2000) != 0) {
                sel++;
                if (sel >= 5) {
                    sel = 0;
                }
                CUR_SE();
            }
            break;
        case 318:
            if ((D_0028F8F0[0].flags & 0xA000) != 0) {
                cur = cur == 0;
                CUR_SE();
            }
            break;
        case 313:
            if ((D_0028F8F0[0].flags & 0xA000) != 0) {
                D_0063A538 = D_0063A538 == 0;
                CUR_SE();
            }
            break;
        case 308:
            if ((D_0028F8F0[0].flags & 0xA000) != 0) {
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
            if ((D_0028F8F0[0].flags & 0xA000) != 0) {
                D_00639EA0 = D_00639EA0 == 0;
                CUR_SE();
            }
            break;
        }
        if (sel != CurrentTargetGObjSub) {
            if (D_0061DC90[CurrentTargetGObjSub] != -1) {
                stage_SetLoopFlag(D_0061DC90[CurrentTargetGObjSub], 0);
                stage_SetAnimation(D_0061DC90[CurrentTargetGObjSub], -1, -2);
            }
            item = D_0061DC90[sel];
            if (item != -1) {
                stage_SetLoopFlag(item, 1);
                stage_SetAnimation(item, 1, 0);
            }
            CurrentTargetGObjSub = sel;
        }
        CurrentTargetGObj = cur;
    }
    for (sel = 0; sel < 5; sel++) {
        lt_default_mask_property(D_0061DC78[sel], 1);
    }
    lt_default_mask_property(D_0061DC78[CurrentTargetGObjSub], 0);
    for (sel = 0; sel < 2; sel++) {
        lt_default_mask_property(D_0061DCA8[sel], 1);
    }
    lt_default_mask_property(D_0061DCA8[CurrentTargetGObj], 0);
    if ((D_0028F8F0[0].flags & 0x40) != 0) {
        if (lt_current_property_item() == 330) {
            NEGATIVE_SE();
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
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
    if (D_0063A538 != 0) {
        lt_default_mask_property(316, 0);
        lt_default_mask_property(317, 1);
    } else {
        lt_default_mask_property(316, 1);
        lt_default_mask_property(317, 0);
    }
    for (sel = 0; sel < 2; sel++) {
        lt_default_mask_property(D_0061DCB0[sel], 1);
    }
    lt_default_mask_property(D_0061DCB0[D_00639EA0], 0);
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
/* kept local: this TU's uses of stgmgrNextStagePreLoadForceStageSet do not fit the prototype in StageManager.h */
extern void stgmgrNextStagePreLoadForceStageSet(int val);

int la_scei_logo(int a0)
{
    if (a0) {
        stgmgrNextStagePreLoadForceStageSet(0);
        logoIcoMiscLock = lock_execIcoMisc;
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
        if ((D_0063B4D8->_0.w >> 1) & 1) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x1E;
        }
        D_0063B528 = 1;
        break;
    case 1:
        if ((D_0063B4D8->_0.w >> 1) & 1) {
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
        if (((D_0063B4D8->_0.w >> 1) & 1) == 0) {
            lt_set_item_select_func(0);
            D_0063B4F4 = 0;
            return 0x1F;
        }
        D_0063B528 = 1;
        break;
    case 1:
        if ((D_0063B4D8->_0.w >> 4) & 1) {
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

extern int D_0029B9D0[];
extern int D_0061DC40[];
extern int D_0061DC58[];

int la_save_confirm_complete(int a0, int a1)
{
    if (a0) {
        previewInfo = *(struct S14 *)D_0029B9D0;
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
    *(struct S40 *)D_0029BC00 = tmp;
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
