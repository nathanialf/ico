#include "common.h"
#include "debug.h"
#include "StageManager.h"
#include "backStage.h"
#include "kanban.h"
#include "gobj.h"
#include "s_init.h"
#include "act-game.h"
#include "commonact.h"
#include "fieldCollision.h"
#include "memory.h"
#include "brain.h"
#include "camera-root.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "GsBase.h"
#include <string.h>
#include <stdio.h>
#include <eekernel.h>
#include "gamesys.h"
#include "typedef.h"

/* debug_exception_screen.c.inc (compiled into debug_exception.o) */

typedef struct {
    float f[4];
} __attribute__((packed)) Blk16;

typedef struct {
    int x, y, w, h;
} FR;

extern char D_0061B440[];
extern char D_0063AE78[];
extern char D_0063AE80[];

void debug_Assert(char *fmt, ...)
{
    char buf[0x100];
    vsprintf(buf, fmt, (char *)__builtin_next_arg(fmt) - 56);
    debug_assertMessage(D_0061B440, 0x570, buf);
    __assert(D_0061B440, 0x570, D_0063AE78);
    debug_assert(D_0061B440, 0x571);
    __assert(D_0061B440, 0x571, D_0063AE80);
}

extern int D_0063AE84;

void debug_openLog(void)
{
    /* CRUTCH: zero-code frame reservation. ROM's frame holds 256 bytes of vars
       that nothing in the emitted body writes; the compiled-out log-open block
       (an sceOpen path behind the printf stubs) is where the buffer was used.
       Deleting the declaration shrinks the frame and changes the object. See
       docs/crutch_ledger.md. */
    volatile char buf[256];
    D_0063AE84 = -1;
}

/* sceWrite returns the byte count (SCE sifdev); the unused return value is
   what makes $v0 live-and-dying at each call site. */
extern int sceWrite();

void debug_LogPrintf(const char *fmt, ...)
{
    char buf[0x100];
    void *info;
    vsprintf(buf, fmt, (char *)__builtin_next_arg(fmt) - 0x38);
    info = strlen(buf);
    sceWrite(D_0063AE84, buf, info);
}

/* the debug-option table: 76 records of 0x1C bytes */
typedef struct {
    /* 0x00 */ char *name;
    /* 0x04 */ unsigned int col;
    /* 0x08 */ int *val;
    /* 0x0C */ int min;
    /* 0x10 */ int max;
    /* 0x14 */ char **strs;
    /* 0x18 */ void (*func)(int);
} DbgOpt;

extern DbgOpt D_0061A4D0[];
extern char D_0061B5B0[];
extern char D_0061B5F0[];
extern char D_0061B608[];
extern char D_0061B640[];
extern char D_0061B570[];
extern char D_0063AE98[];
extern char D_0063AEA0[];

void debug_SaveDebugOptionFile(void)
{
    char buf[0x100];
    int i;
    int fd;
    debug_StdPrintfDummy(D_0061B5B0);
    fd = debugSceOpen((int)D_0061B5F0, 0x602) < 0;
    if (fd) {
        debug_StdPrintfDummy(D_0061B608);
    } else {
        for (i = 0; i < 76; i++) {
            sprintf(buf, D_0063AE98, D_0061A4D0[i].name);
            sceWrite(fd, buf, strlen(buf));
            sprintf(buf, D_0063AEA0, *D_0061A4D0[i].val);
            sceWrite(fd, buf, strlen(buf));
        }
        debugSceClose(fd);
        debug_StdPrintfDummy(D_0061B640);
    }
    debug_StdPrintfDummy(D_0061B570);
    debug_openLog();
}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/debug", debug_GetDebugOption);

extern unsigned int D_0063AE8C;

void debug_SetDmaCallback(void)
{
    if ((int)D_0063AE8C != -1) {
        RemoveDmacHandler(1, D_0063AE8C);
    }
    D_0063AE8C = AddDmacHandler(1, (int)debug_CallbackGsFinish, -1);
    EnableDmac(1);
}

extern int D_0063AD28;
extern int D_0063AE64;
extern int debug_bar_flag;
extern int D_0063B134;
extern int D_0063B138;
extern int D_0063B13C;
extern int D_0063B140;
extern int D_0063B144;
extern int D_0063B148;
extern int D_0063B14C;
extern int D_0063B150;
extern int D_0063B154;
extern int D_0063B158;
extern int D_0063B15C;
extern int D_0063B160;
extern int D_0063B164;
extern int D_0063B168;
extern int D_0063B16C;
extern int D_0063B170;
extern int D_0063B174;
extern int D_0063B178;
extern int D_0063B17C;
extern int D_0063B180;
extern int D_0063B184;
extern int D_0063B188;
extern int D_0063B18C;
extern int D_0063B190;
extern int D_0063B194;
extern int D_0063B198;
extern int D_0063B19C;
extern int D_0063B1A0;
extern int D_0063B1A4;
extern int D_0063B1A8;
extern int D_0063B1AC;
extern int D_0063B1B0;
extern int D_0063B1B4;
extern int D_0063B1B8;
extern int D_0063B1BC;
extern int D_0063B1C0;
extern int D_0063B1C8;
extern int D_0063B1CC;
extern int D_0063B1D8;
extern int D_0063B1DC;
extern int D_0063B1E0;
extern int D_0063B1E4;
extern int D_0063B1E8;
extern int D_0063B1EC;
extern int D_0063B1F0;
extern int D_0063B1F4;
extern int D_0063B1F8;
extern int D_0063B1FC;
extern int D_0063B200;
extern int D_0063B204;
extern int D_0063B208;
extern int D_0063B20C;
extern int D_0063B210;
extern int D_0063B214;
extern int D_0063B218;
extern int D_0063B21C;
extern int D_0063B220;
extern int D_0063B224;
extern int D_0063B228;
extern int D_0063B22C;
extern int D_0063B230;
extern int D_0063B234;
extern int D_0063B238;
extern int D_0063B23C;
extern int D_0063B240;
extern int D_0063B244;
extern int D_0063B248;
extern int D_0063B24C;
extern int D_0063B250;
extern int D_0063B254;
extern int D_0063B258;
extern int D_0063B25C;
extern int D_0063B260;
extern int game_pause;
extern int D_00639EA0;

/* INTERIM: ChangeGirlControlMode (census function, own ROM slot later in this
   TU) is inlined here per the listing (rows src/debug.c:1188-1189 inside
   debug_VariableInit's ROM). While the tail still carries asm members its own
   definition cannot be marked `inline`, so this stand-in serves the call site.
   Fold the two together when the TU is complete. */
static inline void ChangeGirlControlMode_interim(int a0)
{
    if (a0 == 1) {
        D_00639EA0 = a0;
    }
}

void debug_VariableInit(void)
{
    D_0063B170 = 15;
    D_0063B160 = 0;
    D_0063B134 = 0;
    debug_bar_flag = 0;
    D_0063B1A4 = 0;
    D_0063B13C = 0;
    D_0063B140 = 0;
    D_0063B144 = 0;
    D_0063B15C = 0;
    D_0063B148 = 0;
    D_0063B14C = 0;
    D_0063B150 = 0;
    D_0063B154 = 0;
    D_0063B164 = 0;
    D_0063B158 = 0;
    D_0063B16C = 1;
    D_0063B168 = 1;
    D_0063B174 = 0;
    D_0063B178 = 0;
    D_0063B138 = 0;
    D_0063B17C = 0;
    D_0063B180 = 1;
    D_0063B184 = 0;
    D_0063B188 = 0;
    D_0063B18C = 1;
    D_0063B198 = 0;
    D_0063AE64 = 0;
    D_0063B194 = 0;
    D_0063B19C = 1;
    D_0063B1A8 = 0;
    D_0063B1AC = 1;
    D_0063B1B0 = 100;
    D_0063B1A0 = 0;
    D_0063B1B4 = 25;
    D_0063B1B8 = 100;
    D_0063B1BC = 0;
    D_0063B1C0 = 0;
    D_0063B1CC = 0;
    D_0063B1D8 = 0;
    D_0063B250 = 20;
    D_0063B254 = 0;
    D_0063B258 = 256;
    D_0063B25C = 0;
    D_0063B1DC = 0;
    D_0063B1E0 = 0;
    D_0063B1E4 = 4;
    D_0063B190 = 1;
    D_0063B1F0 = 1;
    D_0063B1F4 = 1;
    D_0063B1F8 = 1;
    D_0063B1FC = 1;
    D_0063B200 = 1;
    D_0063B204 = 1;
    D_0063AD28 = 0;
    D_0063B1E8 = 0;
    D_0063B1EC = 3;
    D_0063B20C = 1;
    D_0063B208 = 0;
    D_0063B210 = 1;
    D_0063B214 = 4;
    D_0063B218 = 4;
    D_0063B21C = 5;
    D_0063B220 = 0;
    D_0063B224 = 0;
    D_0063B228 = 0;
    D_0063B22C = 1;
    D_0063B230 = 0;
    D_0063B234 = 0;
    D_0063B238 = 0;
    D_0063B23C = 0;
    D_0063B240 = 0;
    D_0063B244 = 1;
    D_0063B248 = 1;
    D_0063B24C = 0;
    D_0063B260 = 0;
    D_0063B1C8 = 0;
    game_pause = 0;
    ChangeFieldCollisionDebugMode(0);
    ChangeGirlControlMode_interim(D_0063B24C);
}

extern int D_0063B110;
extern int D_0063B114;
extern int D_0063B118;
extern int D_0063B11C;
extern int D_0063B120;
extern int D_0063B124;
extern int D_0063B1C4;

void debug_Init(void)
{
    debug_ClearFontWindow();
    D_0063B110 = 0;
    D_0063B114 = 0;
    D_0063B118 = 0;
    D_0063B11C = 0;
    D_0063B120 = 0;
    D_0063B124 = 0;
    D_0063B1C4 = 0;
    *(volatile int *)0x10000010 = 0x82;
    *(volatile int *)0x10000810 = 0x82;
    debug_makeBackImage();
}

/* the areas debug_Load parcels its files into; the report prints how much of
   each one is in use once the file has been allocated out of it */
extern IosMemPart *D_0063A434; /* hara */
extern IosMemPart *D_0063A438; /* sugi */
extern IosMemPart *D_0063A43C; /* static object */
extern IosMemPart *D_0063A440; /* dynamic motion */
extern IosMemPart *D_0063A444; /* static motion */
extern IosMemPart *D_0063A44C; /* seki */
extern IosMemPart *D_0063A450; /* oomori */
extern IosMemPart *D_0063A454; /* horagai */
extern IosMemPart *D_0063A458; /* sound */
extern IosMemPart *D_0063A45C; /* sound_semi */
/* kept local: this TU's other raw-file calls do not fit sifdev.h's sceClose */
extern int sceLseek(int fd, int offset, int whence);
extern int sceRead(int fd, void *buf, int size);
extern char D_0061B7D8[]; /* "ico2Data/%s" */
extern char D_0061B7E8[]; /* "file is not exist(%s)\n" */
extern char D_0061B800[]; /* the coloured loading report: name, address, size */
extern char D_0061B840[]; /* " to seki area.(%2.1f%%)\n" */
extern char D_0061B860[]; /* " to sugi area.(%2.1f%%/%2.1f%%)\n" */
extern char D_0061B888[]; /* " to static object area.(%2.1f%%/%2.1f%%)\n" */
extern char D_0061B8B8[]; /* " to static motion area.(%2.1f%%/%2.1f%%)\n" */
extern char D_0061B8E8[]; /* " to dynamic motion area.(%2.1f%%/%2.1f%%)\n" */
extern char D_0061B918[]; /* " to hara-area.(%2.1f%%)\n" */
extern char D_0061B938[]; /* " to oomori area.(%2.1f%%)\n" */
extern char D_0061B958[]; /* " to horagai-area.\n" */
extern char D_0061B970[]; /* " to sound-area.\n" */
extern char D_0061B988[]; /* " to sound_semi-area.\n" */

int debug_Load(char **dst, char *name, int kind)
{
    char buf[0x100];
    int size;
    int sz;
    int fd;

    sprintf(buf, D_0061B7D8, name);
    fd = debugSceOpen((int)buf, 1);
    if (fd < 0) {
        debug_StdPrintfDummy(D_0061B7E8, name);
        return -1;
    }
    size = sceLseek(fd, 0, 2);
    sceLseek(fd, 0, 0);
    sz = (size / 16 + 1) * 16;
    {
        /* The line every arm prints once it has the file's address. It is a
           nested function, and that is what puts dst, name and size in the
           frame: each arm reads them back from their home slots rather than
           out of a register. The block is what lets it be declared here, after
           the size rounding, which is where the listing's rows for its body
           sit (debug.c:1952, between the rounding at 1950 and the switch at
           1955) and which is what decides the conditional move's sense in that
           rounding: with the nested function above it the value is already in
           the frame and gcc emits movn against the other arm. The line numbers
           the iosMallocDebug calls pass are the source's own __LINE__, read
           off the listing. */
        inline void loadReport(void)
        {
            debug_StdPrintfDummy(D_0061B800, name, *dst, size);
        }
        switch (kind) {
        case 0:
        default:
            *dst = iosMallocDebug(D_0063A44C, sz, D_0061B440, 1958);
            loadReport();
            debug_StdPrintfDummy(D_0061B840,
                                 (*dst + sz - D_0063A44C->start) * 100.0f / 10059776.0f);
            break;
        case 1:
            *dst = iosMallocDebug(D_0063A438, sz, D_0061B440, 1965);
            loadReport();
            debug_StdPrintfDummy(D_0061B860, sz * 100.0f / 524288.0f,
                                 (*dst + sz - D_0063A438->start) * 100.0f / 524288.0f);
            break;
        case 2:
            *dst = iosMallocDebug(D_0063A43C, sz, D_0061B440, 1973);
            loadReport();
            debug_StdPrintfDummy(D_0061B888, sz * 100.0f / 2.0f,
                                 (*dst + sz - D_0063A43C->start) * 100.0f / 2.0f);
            break;
        case 3:
            *dst = iosMallocDebug(D_0063A444, sz, D_0061B440, 1982);
            loadReport();
            debug_StdPrintfDummy(D_0061B8B8, sz * 100.0f / 1179648.0f,
                                 (*dst + sz - D_0063A444->start) * 100.0f / 1179648.0f);
            break;
        case 5:
            *dst = iosMallocDebug(D_0063A440, sz, D_0061B440, 1991);
            loadReport();
            debug_StdPrintfDummy(D_0061B8E8, sz * 100.0f / 3670016.0f,
                                 (*dst + sz - D_0063A440->start) * 100.0f / 3670016.0f);
            break;
        case 6:
            *dst = iosMallocDebug(D_0063A434, sz, D_0061B440, 2000);
            loadReport();
            debug_StdPrintfDummy(D_0061B918, (*dst + sz - D_0063A434->start) * 100.0f);
            break;
        case 7:
            *dst = iosMallocDebug(D_0063A450, sz, D_0061B440, 2007);
            loadReport();
            debug_StdPrintfDummy(D_0061B938, (*dst + sz - D_0063A450->start) * 100.0f / 327680.0f);
            break;
        case 8:
            *dst = iosMallocDebug(D_0063A454, sz, D_0061B440, 2014);
            loadReport();
            debug_StdPrintfDummy(D_0061B958);
            break;
        case 9:
            *dst = iosMallocDebug(D_0063A458, sz, D_0061B440, 2019);
            loadReport();
            debug_StdPrintfDummy(D_0061B970);
            break;
        case 10:
            *dst = iosMallocDebug(D_0063A45C, sz, D_0061B440, 2024);
            loadReport();
            debug_StdPrintfDummy(D_0061B988);
            break;
        }
    }
    sceRead(fd, *dst, size);
    debugSceClose(fd);
    FlushCache(0);
    sceGsSyncPath(0, 0);
    return size;
}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/debug", debug_MakeFont);

/* D_00619BB0 = the 8x8 1bpp font bitmap (8 bytes per glyph);
   D_00706AD0 = the glyph re-expanded to 8 shorts (shifted left one column);
   D_00704AD0 = the 3x3-dilated outline, 16 shorts per glyph. */
extern unsigned char D_00619BB0[];
extern unsigned short D_00704AD0[];
extern unsigned short D_00706AD0[];

void debug_makeBackImage(void)
{
    int i;
    int j;
    unsigned char *src;
    unsigned short *a;
    unsigned short *b;
    for (i = 0; i < 256; i++) {
        src = &D_00619BB0[i * 8];
        a = &D_00704AD0[i * 16];
        b = &D_00706AD0[i * 8];

        for (j = 0; j < 16; j++) {
            a[j] = 0;
            b[j] = 0;
        }
        for (j = 0; j < 8; j++)
            b[j + 1] = src[j] << 1;
        a[0] = b[0] | (b[0] << 1) | (b[0] >> 1) | b[1] | (b[1] << 1) | (b[1] >> 1);
        for (j = 1; j < 9; j++)
            a[j] = b[j - 1] | (b[j - 1] << 1) | (b[j - 1] >> 1) | b[j] | (b[j] << 1) | (b[j] >> 1) |
                   b[j + 1] | (b[j + 1] << 1) | (b[j + 1] >> 1);
        for (j = 0; j < 10; j++)
            a[j] = a[j] << 1;
        for (j = 0; j < 10; j++)
            a[j] = a[j] & ~b[j];
    }
    debug_MakeFont();
}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/debug", debug_PrintCharacter);

extern int D_0063AEB0;
/* kept local: this TU's uses of gif_CheckOpen do not fit the prototype in GifPacket.h */
extern int gif_CheckOpen(void);
/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket(void);
/* kept local: this TU's uses of gif_SetAlpha do not fit the prototype in GifPacket.h */
extern void gif_SetAlpha(int a0, int a1, int a2);
/* kept local: this TU's uses of gif_SetZTest do not fit the prototype in GifPacket.h */
extern void gif_SetZTest(int a0);
/* kept local: this TU's uses of gif_SetZWrite do not fit the prototype in GifPacket.h */
extern void gif_SetZWrite(int a0);
/* kept local: this TU's uses of gif_Sprite do not fit the prototype in GifPacket.h */
extern void gif_Sprite(void *a0, unsigned int a1, int a2, void *a3, int a4);
/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int a0);

void debug_PrintFont(int a0, int a1, int a2, char *a3)
{
    FR buf[2];
    int r;

    buf[1].x = a0 - 0x142;
    buf[1].y = a1 - 0x71;
    r = strlen(a3);
    buf[1].h = 9;
    buf[1].w = r * 0xC + 4;
    buf[0] = buf[1];

    if (gif_CheckOpen() != 0) {
        return;
    }
    if (D_0063B13C & 2) {
        gif_StartPacketPri(0xB);
        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetAlpha(1, 2, 0x80);
        gif_Sprite(&buf[0], 0xFFFFFFFDU, 0, &D_0063AEB0, 1);
        gif_EndPacket();
    } else {
        gif_StartPacketPri(0xB);
        gif_SetZTest(0);
        gif_SetAlpha(1, 2, 0x80);
        gif_EndPacket();
    }
    debug_PrintCharacter(a3, a0, a1, (unsigned)a2 >> 24, ((unsigned)a2 >> 16) & 0xFF,
                         ((unsigned)a2 >> 8) & 0xFF, 0x70);
}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/debug", debug_FlushFontWindow);

void debug_FlushFont(void)
{
    debug_FlushFontWindow();
}

/* The bar colours are 4-byte GS colour records this TU only sees as far
   (incomplete-array) symbols; their byte alignment is what makes every copy
   an lwl/lwr pair. */
typedef struct {
    unsigned char r, g, b, a;
} DbgCol;

extern DbgCol D_0063AEB8[];
extern DbgCol D_0063AEC0[];
extern DbgCol D_0063AEC8[];
extern DbgCol D_0063AED0[];
extern DbgCol D_0063AED8[];

typedef struct {
    int x, y, z;
} DbgPos;

typedef struct {
    int x, y, z, w;
} DbgVtx;

extern Brain D_002A5580[];
extern float brainGetLevel(Brain *b, BrainTarget *t);
/* kept local: this TU's uses of gif_Line do not fit the prototype in GifPacket.h */
extern void gif_Line(void *v0, void *v1, unsigned int z0, unsigned int z1, void *col, int prim);

/* The four corners of a marker box, shared by draw_batsu and draw_shikaku
   (the listing inlines lines 2379-2393 into both).  `q` carries no traffic in
   the shipped build, but the ROM's inlined frame proves the slot: the offsets
   table is addressed as <inline frame base>+0x10, i.e. 16 bytes of this
   function's locals sit in front of it.  The table is built element by element
   (not copied from .rodata) because `r` makes the initialiser non-constant. */
static inline void make_mark_points(DbgVtx *v, DbgPos *p, int r)
{
    DbgPos q; /* unused in the 2001 source too: ROM's frame keeps its 16-byte slot
                   ahead of the offsets table (0xD0, not 0xC0), and the listing
                   has exactly one declaration line here (2381). */
    int ofs[4][2] = {{-r, -r}, {r, -r}, {-r, r}, {r, r}};
    int i;

    for (i = 0; i < 4; i++) {
        v[i].x = p->x;
        v[i].y = p->y;
        v[i].z = p->z;
        v[i].x += ofs[i][0];
        v[i].y += ofs[i][1];
    }
}

void debug_brainBar(void)
{
    void draw_batsu(DbgPos * p)
    {
        DbgCol col = D_0063AEB8[0];
        DbgVtx v[4];

        make_mark_points(v, p, 3);
        gif_Line(&v[0], &v[3], 0xFFFFFFFFU, 0xFFFFFFFFU, &col, 1);
        gif_Line(&v[1], &v[2], 0xFFFFFFFFU, 0xFFFFFFFFU, &col, 1);
    }
    void draw_shikaku(DbgPos * p)
    {
        DbgCol col = D_0063AEB8[0];
        DbgVtx v[4];

        make_mark_points(v, p, 3);
        gif_Line(&v[0], &v[1], 0xFFFFFFFFU, 0xFFFFFFFFU, &col, 1);
        gif_Line(&v[1], &v[3], 0xFFFFFFFFU, 0xFFFFFFFFU, &col, 1);
        gif_Line(&v[3], &v[2], 0xFFFFFFFFU, 0xFFFFFFFFU, &col, 1);
        gif_Line(&v[2], &v[0], 0xFFFFFFFFU, 0xFFFFFFFFU, &col, 1);
    }
    DbgCol c0 = D_0063AEC0[0];
    DbgCol c1 = D_0063AEC8[0];
    DbgCol c2 = D_0063AED0[0];
    DbgCol c3 = D_0063AED8[0];
    DbgPos a;
    DbgPos b;
    DbgPos c;
    Brain *brain;
    DbgCol *col;
    int i;
    int y;
    int ytop;

    ytop = -100;
    y = ytop;
    gif_StartPacketPri(0xB);
    gif_SetAlpha(1, 2, c3.a);
    brain = &D_002A5580[0];
    for (i = 0; i < 40; i++) {
        b.x = 300;
        a.y = b.y = y;
        if (brain->tgt[i].gobj == 0) {
            continue;
        }
        y += 4;
        a.y = b.y = y;
        a.x = 300.0f - brainGetLevel(brain, &brain->tgt[i]) * 20.0f;
        if (brain->idx == i) {
            col = &c2;
        } else if (brainGetLevel(brain, &brain->tgt[i]) < brain->f14) {
            col = &c0;
        } else {
            col = &c1;
        }
        gif_Line(&a, &b, 0xFFFFFFFFU, 0xFFFFFFFFU, col, 1);
        if (*(int *)(brain->tgt[i].gobj + 0xC) == 0x3D) {
            /* a.z is never written: the ROM reads sp+0x48 uninitialised here
               too, so the 2001 source carried the same bug. */
            c.x = a.x;
            c.y = a.y;
            c.z = a.z;
            c.x -= 15;
            if (brain->tgt[i].b19) {
                draw_shikaku(&c);
            } else {
                draw_batsu(&c);
            }
            c.x += 10;
            if (brainCheckView(brain, &brain->tgt[i])) {
                draw_shikaku(&c);
            } else {
                draw_batsu(&c);
            }
            c.x += 15;
            if (brain->tgt[i].b18) {
                draw_shikaku(&c);
            } else {
                draw_batsu(&c);
            }
        }
        y += 4;
    }
    b.x = 300.0f - brain->f14 * 20.0f;
    a.x = b.x;
    a.y = ytop;
    b.y = y;
    gif_Line(&a, &b, 0xFFFFFFFFU, 0xFFFFFFFFU, &c2, 1);
    a.x = b.x = 260;
    a.y = ytop;
    b.y = y;
    gif_Line(&a, &b, 0xFFFFFFFFU, 0xFFFFFFFFU, &c1, 1);
    a.x = b.x = 220;
    a.y = ytop;
    b.y = y;
    gif_Line(&a, &b, 0xFFFFFFFFU, 0xFFFFFFFFU, &c0, 1);
    gif_EndPacket();
}

extern char D_00704680[];
extern char D_0063AE90[];

int debug_MakeBarString(char *p, int a, int b, FR fr, long long x, int line)
{
    char buf[16];
    int i;
    int len;

    len = strlen(p);
    if (len == 0) {
        return 0;
    }
    D_00704680[0] = 0;
    for (i = 0; i < len; i++, p++) {
        if (*p == '$') {
            switch (p[1]) {
            case 'P':
                sprintf(buf, D_0063AE90, a);
                strcat(D_00704680, buf);
                break;
            case 'T':
                sprintf(buf, D_0063AE90, b);
                strcat(D_00704680, buf);
                break;
            }
            p++;
            i++;
        } else {
            buf[0] = *p;
            buf[1] = 0;
            strcat(D_00704680, buf);
        }
    }
    if (strlen(D_00704680) != 0 && (D_0063B13C & 1)) {
        debug_Printf((int)(x + 0x148), fr.y + line * 7 + (fr.h + 0x71), 0xFFFFFF00u,
                     (int)D_00704680);
    }
    return strlen(D_00704680);
}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/debug", debug_DrawBar);

/* the profiler ring: 0x400 entries of 28 bytes, filled by debug_SetBar. */
typedef struct {
    char name[12];        /* 0x00 */
    unsigned char col[4]; /* 0x0C */
    char *file;           /* 0x10 */
    short count;          /* 0x14 */
    short pad16;          /* 0x16 */
    int line;             /* 0x18 */
} DebugBar;

extern DebugBar D_00708880[];
extern int D_0063C384;
extern int D_0063AE68;
extern int D_0028F4C0[];
extern int frame_count;
extern char D_0061BA18[];
extern char D_0061BA28[];

void debug_DispBar(void)
{
    float inv;
    int va;
    int vb;
    int n;
    inv = 1.0f / (270000.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
    vb = (float)(D_00708880[D_0063C384 - 1].count * 100) * inv;
    va = (float)(D_0063AE68 * 100) * inv;

    if (D_0063B140 != 0 || (D_0063B13C & 1) != 0)
        debug_Printf(10, 10, 0xFFFFFF00u, (int)D_0061BA18, vb, va, frame_count);
    if (D_0063B138 != 0)
        debug_brainBar();
    if (debug_bar_flag != 0)
        debug_DrawBar();
    if (D_0063B114 != 0 || D_0063B124 != 0) {
        n = 1;
        if (D_0063B114 != 0)
            n = D_0063B114;
        if (D_0063B140 != 0 || (D_0063B13C & 1) != 0)
            debug_Printf(10, 20, 0xFFFFFF00u, (int)D_0061BA28, D_0063B110, D_0063B114,
                         D_0063B110 / n, D_0063B118, D_0063B124 / 1024, D_0063B11C);
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/debug", debug_ResizeSnapShot);

/* 24-bit BMP file header, offset by two pad bytes so the 32-bit fields land
   4-aligned on the stack; the file image starts at &hdr.bfType. */
typedef struct {
    unsigned char pad[2];    /* 0x00 */
    unsigned char bfType[2]; /* 0x02 */
    int bfSize;              /* 0x04 */
    int bfReserved;          /* 0x08 */
    int bfOffBits;           /* 0x0C */
    int biSize;              /* 0x10 */
    int biWidth;             /* 0x14 */
    int biHeight;            /* 0x18 */
    short biPlanes;          /* 0x1C */
    short biBitCount;        /* 0x1E */
    int biCompression;       /* 0x20 */
    int biSizeImage;         /* 0x24 */
    int biXPelsPerMeter;     /* 0x28 */
    int biYPelsPerMeter;     /* 0x2C */
    int biClrUsed;           /* 0x30 */
    int biClrImportant;      /* 0x34 */
} BmpHeader;

void debug_WriteBMP(int fd, int w, int h, unsigned int *src)
{
    unsigned char line[w * 3];
    BmpHeader hdr;
    unsigned char *s;
    unsigned char *d;
    int x;
    int y;
    hdr.pad[0] = 0;
    hdr.pad[1] = 0;
    hdr.bfType[0] = 0x42;
    hdr.bfType[1] = 0x4D;
    hdr.bfOffBits = 0x36;
    hdr.biSize = 0x28;
    hdr.biPlanes = 1;
    hdr.biBitCount = 24;
    hdr.biCompression = 0;
    hdr.biXPelsPerMeter = 0;
    hdr.biYPelsPerMeter = 0;
    hdr.biClrUsed = 0;
    hdr.biClrImportant = 0;
    hdr.biWidth = w;
    hdr.biHeight = h;
    hdr.biSizeImage = w * h * 3;
    hdr.bfSize = hdr.biSizeImage + 0x36;
    sceWrite(fd, hdr.bfType, 0x36);
    for (y = h - 1; y >= 0; y--) {
        s = (unsigned char *)&src[y * w];
        d = line;
        for (x = 0; x < w; x++, d += 3) {
            d[0] = s[2];
            d[1] = s[1];
            d[2] = s[0];
            s += 4;
        }
        sceWrite(fd, line, w * 3);
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/debug", debug_SnapShot);

extern char D_0061BAA8[];
extern char D_0061BAC0[];
extern char D_0063AF38[];
extern char D_0063AF40[];
extern char D_0063AF48[];
extern char D_0063AF50[];

void debug_DispQW(void *p, int size)
{
    int isf = 0;
    int i;
    int j;

    switch (size) {
    case 0:
        isf = 1;
        size = 4;
        debug_StdPrintfDummy(D_0061BAA8, p);
        break;
    case 1:
    case 2:
    case 4:
    case 8:
    case 16:
        debug_StdPrintfDummy(D_0061BAC0, p, size);
        break;
    default:
        return;
    }
    for (i = 0; i < 16 / size; i++) {
        if (isf == 0) {
            for (j = 16 / (16 / size) - 1; j >= 0; j--) {
                debug_StdPrintfDummy(D_0063AF38, ((unsigned char *)p)[i * size + j]);
            }
            debug_StdPrintfDummy(D_0063AF40);
        } else {
            debug_StdPrintfDummy(D_0063AF48, ((float *)p)[i]);
        }
    }
    debug_StdPrintfDummy(D_0063AF50);
}

void debug_Printf(int a, int b, unsigned int c, int x, ...)
{
    char buf[0x100];
    void *args = (char *)__builtin_next_arg(x) - 0x20;
    vsprintf(buf, x, args);
    debug_PrintFont(a, b, c, buf);
}

void debug_Printf2(int a, int b, unsigned int c, int x, ...)
{
    char buf[0x100];
    void *args = (char *)__builtin_next_arg(x) - 0x20;
    vsprintf(buf, x, args);
    debug_PrintFont(a, b, c, buf);
}

/* the on-screen font window's line table: 27 records of 0x38 bytes, the colour
   word at +0 and the text at +4 (the strncpy below bounds it at 50) */
typedef struct {
    int col;
    char text[52];
} DbgFontLine;

extern DbgFontLine D_007082D0[];
extern int D_0063AEB4;

void debug_PrintFontWindow(int col, char *fmt, ...)
{
    char buf[0x100];
    char *p = buf;
    int nl = 0;
    int i;

    vsprintf(buf, fmt, (char *)__builtin_next_arg(fmt) - 0x30);
    if (buf[0] == '\n') {
        D_0063AE64++;
        p = &buf[1];
    }
    if (D_0063AE64 == D_0063AEB4) {
        for (i = 0; i < D_0063AEB4 - 1; i++) {
            D_007082D0[i] = D_007082D0[i + 1];
        }
        D_0063AE64--;
        D_007082D0[D_0063AEB4 - 1].text[0] = 0;
    }
    if (p[strlen(p) - 1] == '\n') {
        p[strlen(p) - 1] = 0;
        nl = 1;
    }
    strncpy(D_007082D0[D_0063AE64].text, p, 50);
    D_007082D0[D_0063AE64].col = col;
    if (nl) {
        D_0063AE64++;
    }
    if (D_0063AE64 == D_0063AEB4) {
        for (i = 0; i < D_0063AEB4 - 1; i++) {
            D_007082D0[i] = D_007082D0[i + 1];
        }
        D_0063AE64--;
        D_007082D0[D_0063AEB4 - 1].text[0] = 0;
    }
}

void debug_PrintfDummy(int a0, int a1, unsigned int a2, int a3, ...) {}

void debug_PrintFontWindowDummy(int a0, int a1, ...) {}

void debug_StdPrintfDummy(char *fmt, ...)
{
    (void)fmt;
}

extern char D_007046C0[];
extern char D_0063AF58[];
extern char D_0063AF60[];
extern char D_0061BB28[];
extern float dptofp(double v);

void debug_PrintFontf(int x, int y, char *p, ...)
{
    char *d;
    char *va;
    char *f;
    char c;
    float v;
    d = D_007046C0;
    va = (char *)__builtin_next_arg(p) - 0x28;
    if (*p == 0) {
        *d = 0;
        return;
    }
    do {
        c = *p;
        if (c == '\n') {
            *d = 0;
            if (D_0063B13C & 1) {
                debug_Printf(x, y, 0xFFFFFF00u, (int)D_007046C0);
            }
            d = D_007046C0;
            y += 8;
        } else if (c != '%') {
            *d = *p;
            d++;
        } else {
            p++;
            switch (*p) {
            case 'd':
                va += 8;
                f = D_0063AE90;
                d += sprintf(d, f, *(int *)(va - 8));
                break;
            case 'x':
                va += 8;
                f = D_0063AF58;
                d += sprintf(d, f, *(int *)(va - 8));
                break;
            case 'f':
                va += 8;
                v = dptofp(*(double *)(va - 8));
                f = D_0063AF60;
                d += sprintf(d, f, v);
                break;
            default:
                f = D_0061BB28;
                debug_StdPrintfDummy(f);
                break;
            }
        }
        p++;
    } while (*p != 0);
    *d = 0;
}

extern const char D_0061BB40[];

void debug_PrintMatrix(float *arg)
{
    int i;
    for (i = 3; i >= 0; i--) {
        debug_StdPrintfDummy((int)D_0061BB40, arg[0], arg[1], arg[2], arg[3]);
        arg += 4;
    }
    debug_StdPrintfDummy((int)D_0063AF50);
}

extern char D_0061BB50[];
extern char D_0061BB68[];

void debug_DispVu1FReg(int no, int mode)
{
    int i;
    float f[4];
    int buf[4];
    if (mode != 0) {
        if (no >= 0) {
            __asm__ __volatile__("ctc2.ni %0, $vi1" : : "r"(no * 16 + 0x400));
            __asm__ __volatile__("vlqi.xyzw $vf2, ($vi1++)");
            __asm__ __volatile__("sqc2 $vf2, 0(%0)" : : "r"(f) : "memory");
            debug_StdPrintfDummy(D_0061BB50, no, f[0], f[1], f[2], f[3]);
        } else {
            __asm__ __volatile__("ctc2.ni %0, $vi1" : : "r"(0x400));
            for (i = 0; i < 32; i++) {
                __asm__ __volatile__("vlqi.xyzw $vf2, ($vi1++)");
                __asm__ __volatile__("sqc2 $vf2, 0(%0)" : : "r"(f) : "memory");
                debug_StdPrintfDummy(D_0061BB50, i, f[0], f[1], f[2], f[3]);
            }
        }
    } else {
        if (no >= 0) {
            __asm__ __volatile__("ctc2.ni %0, $vi1" : : "r"(no * 16 + 0x400));
            __asm__ __volatile__("vlqi.xyzw $vf2, ($vi1++)");
            __asm__ __volatile__("sqc2 $vf2, 0(%0)" : : "r"(buf) : "memory");
            debug_StdPrintfDummy(D_0061BB68, no, buf[0], buf[1], buf[2], buf[3]);
        } else {
            __asm__ __volatile__("ctc2.ni %0, $vi1" : : "r"(0x400));
            for (i = 0; i < 32; i++) {
                __asm__ __volatile__("vlqi.xyzw $vf2, ($vi1++)");
                __asm__ __volatile__("sqc2 $vf2, 0(%0)" : : "r"(buf) : "memory");
                debug_StdPrintfDummy(D_0061BB68, i, buf[0], buf[1], buf[2], buf[3]);
            }
        }
    }
}

typedef struct {
    int _0;
    int hold;
    int _8;
    int trg;
} DbgReverbPad;

extern DbgReverbPad D_0028F8F0[];

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/debug", debug_Mode);

extern char D_0061BC38[];
extern char D_0063AF70[];
extern char D_0063AF78[];

int debug_SelectCsvWindowVal(int a0, int a1, int a2, int a3, int count, int a5, int (*fn)(int, int),
                             int a7)
{
    char buf[count][0x25];
    int i;
    for (i = 0; i < count; i++) {
        if (fn != 0) {
            int r = fn(i, a7);
            sprintf(buf[i], D_0063AF70, i, r);
        } else {
            sprintf(buf[i], D_0063AF78, i);
        }
        if ((unsigned int)strlen(buf[i]) >= 0x26) {
            buf[i][0x24] = 0;
            debug_StdPrintfDummy((int)D_0061BC38);
        }
    }
    return debug_SelectCsvWindow(a0, a1, a2, a3, (char *)buf, 0x25, 0, 0, count, a5);
}

extern int D_0063AF90[];

void getLineBuffer(int a0, int a1, int a2)
{
    sprintf(a0, D_0063AF90, a1, a2);
}

extern int D_0063AF80[];

void getBuffer(int a0)
{
    sprintf(a0, D_0063AF80);
}

extern int D_0063AF7C;
extern int D_0028F4C4[];
extern char D_0063AF88[];

/* INTERIM: `_debug_SelectCsvWindow` is `inline` in the 2001 source -- the four
   public wrappers inline it, and the ELF also carries the out-of-line copy as
   its own census function (matched at its ROM slot later in this file).  gcc
   2.9 emits an `inline` definition at the END of the object in
   first-declaration order, which would move that copy off its ROM slot while
   this TU's tail still holds INCLUDE_ASM members, so the body is duplicated
   here as a static stand-in; fold the two together once the tail is C. */
static inline int _debug_SelectCsvWindow_inl(char *title, int x, int y, int rows, int base,
                                             int stride, int off, int deref, int n, int *psel,
                                             void (*getline)(), int (*colfunc)(int))
{
    char buf[0x100];
    int sel;
    int i;
    int half;
    int k;
    int top;
    int end;
    int yy;
    int len;
    int v;
    int col;

    sel = *psel;
    debug_PrintfDummy(x, y, 0xFFFFFF00u, (int)D_0063AF80, (int)title);
    if ((D_0028F8F0[0]._0 & 2) == 0) {
        if (D_0028F8F0[0].hold & 0x80) {
            D_0063B13C ^= 2;
        }
        if (sel >= n) {
            sel = n - 1;
        }
        if (D_0028F8F0[0].trg & 0x4000) {
            sel++;
            if (sel >= n) {
                sel = 0;
            }
        }
        if (D_0028F8F0[0].trg & 0x1000) {
            sel--;
            if (sel < 0) {
                sel = n - 1;
            }
        }
        if (n < rows) {
            rows = n;
        }
        half = (int)(((float)rows - 0.5f) * 0.5f);
        if (sel < half) {
            k = sel;
        } else if (n - (rows - half) < sel) {
            k = rows - (n - sel);
        } else {
            k = half;
        }
        top = sel - k;
        yy = y + 8;
        for (i = top; i < top + rows; i++) {
            if (i - top == k) {
                col = 0xFF404000;
            } else if (colfunc == 0) {
                col = 0xFFFFFF00;
            } else {
                col = colfunc(i);
            }
            v = base + stride * i + off;
            if (deref == 1) {
                v = *(int *)v;
            }
            len = D_0063AF7C;
            getline(buf, i, v);
            if (len >= 2) {
                if (len >= 0x100) {
                    len = 0xFF;
                }
                buf[len - 1] = -110;
                buf[len] = 0;
            } else {
                buf[0] = 0;
            }
            debug_PrintfDummy(x, yy, col, (int)D_0063AF88, (int)buf);
            yy += 8;
        }
        if (D_0063AF7C <= 0xFFFE) {
            D_0063AF7C += D_0028F4C4[0];
        }
        *psel = sel;
        if (D_0028F8F0[0].hold & 0x20) {
            D_0063AF7C = 0;
            return 1;
        } else if (D_0028F8F0[0].hold & 0x140) {
            D_0063AF7C = 0;
            return -1;
        }
    }
    return 0;
}

int debug_SelectCsvWindow(char *title, int x, int y, int rows, void *base, int stride, int off,
                          int deref, int n, int *psel)
{
    return _debug_SelectCsvWindow_inl(title, x, y, rows, (int)base, stride, off, deref, n, psel,
                                      getBuffer, 0);
}

extern StgPre D_005F5D50[];
extern int D_0028F4D8[];
extern char D_0063AF98[];
extern char D_0061BC78[];
extern int stage_no;
extern int mpegPlayReturnStage;
extern int enable_game_pause;
extern int D_0063A650;
extern int D_0063AA08;

int debug_SelectStageMain(int ret, int stage)
{
    if (D_0028F4D8[0] != 0) {
        return 0;
    }
    if (ret > 0) {
        debug_StdPrintfDummy(D_0061BC78, stage);
        if (stage != 0) {
            int on = 1;
            if (strstr(D_005F5D50[stage].dataFile, D_0063AF98) == 0) {
                mpegPlayReturnStage = stage_no;
                soundDataSegAllClose(0, 2);
                D_0063A650 = on;
                enable_game_pause = on;
                kanbanInit(0);
                gflagOn(394);
                D_0063AA08 = 0;
                stgmgrForceSwitch(stage);
                gflagOff(388);
                ACTGame_SetActors_Debug(stage, on);
            }
        }
    }
    return ret;
}

extern char D_0061BC88[];
extern int D_0063AE6C;

int debug_SelectStage(void)
{
    return debug_SelectStageMain(_debug_SelectCsvWindow_inl(D_0061BC88, 10, 80, 11, (int)D_005F5D50,
                                                            404, 0x20, 0, 106, &D_0063AE6C,
                                                            getLineBuffer, 0),
                                 D_0063AE6C);
}

/* memory-card request block */
/* one sceMcTblGetDir record: the file name sits at +0x20 in a 0x40-byte entry
   (debug_selectFile forms the table base as mc+0x4C0 and the name as
   mc + i*0x40 + 0x4E0). */

typedef struct {
    long long f0; /* 0x00 -- iosMc flag word, 64-bit */
    int f8;       /* 0x08 */
    int fC;       /* 0x0C */
    int ret;      /* 0x10 */
    int f14;      /* 0x14 */
    int f18;      /* 0x18 */
    int f1C;      /* 0x1C */
    char _20[0x4];
    int f24; /* 0x24 */
    char _28[0x18];
    int sel; /* 0x40 */
    int num; /* 0x44 -- entries filled in by iosMcGetDir */
    int _48;
    int f4C; /* 0x4C */
    int f50; /* 0x50 */
    char _54[0x400];
    char name454[0x28]; /* 0x454 */
    char name47C[0x24]; /* 0x47C */
    char _4A0[0x20];    /* 0x4A0 */
    McDirEnt dir[8];    /* 0x4C0 -- sceMcTblGetDir records, 0x40 each */
    char _6C0[0x300];
    long long blockFlags; /* 0x9C0 -- one bit per save block, set where a block holds data */
} McReq;

extern int D_0028F8F4[];

/* src/debug.c:4426-4435 in the listing: the sibling of debug_mcConfirm that
   prints an already-formatted message instead of a fixed prompt. */
static inline int debug_mcAsk(char *msg)
{
    int yes = 0;
    debug_PrintfDummy(80, 70, 0xFFFFFF00u, (int)D_0063AF80, (int)msg);
    if (D_0028F8F4[0] & 0x20) {
        yes = 1;
    }
    if (D_0028F8F4[0] & 0x40) {
        yes = -1;
    }
    return yes;
}

extern char D_0061BCE0[];
extern char D_0061BD10[];
extern char D_0061BD28[];
extern char D_0061BD40[];
extern char D_0061BD70[];
extern char D_0061BD90[];
extern char D_0061BDA0[];

int debug_mcRetErrCheck(McReq *mc)
{
    char buf[0x40];
    int r;
    if (mc->ret >= 0) {
        return 1;
    }
    switch (mc->ret) {
    case 0:
        r = 1;
        break;
    case -9:
    case -2:
        sprintf(buf, D_0061BCE0, mc->ret);
        r = debug_mcAsk(buf) ? -1 : 0;
        break;
    case -4:
        sprintf(buf, D_0061BD10, mc->name47C);
        r = debug_mcAsk(buf) ? -1 : 0;
        break;
    case -14:
        sprintf(buf, D_0061BD28, mc->name454);
        r = debug_mcAsk(buf) ? -1 : 0;
        break;
    case -16:
        sprintf(buf, D_0061BD40, mc->f24, mc->f50, mc->f4C);
        r = debug_mcAsk(buf) ? -1 : 0;
        break;
    case -15:
        sprintf(buf, D_0061BD70, mc->name47C);
        r = debug_mcAsk(buf) ? -1 : 0;
        break;
    case -10:
        sprintf(buf, D_0061BD90);
        r = debug_mcAsk(buf) ? -1 : 0;
        break;
    default:
        sprintf(buf, D_0061BDA0, mc->ret);
        r = debug_mcAsk(buf) ? -1 : 0;
        break;
    }
    return r;
}

/* src/debug.c:4415-4423 in the listing: a static helper both mc(Un)format
   inline -- prints the confirmation prompt and reads the pad:
   circle (0x20) = yes -> 1, cross (0x40) = cancel -> -1, otherwise 0. */
extern char D_0061BC98[];

static inline int debug_mcConfirm(char *msg)
{
    int yes = 0;
    debug_PrintfDummy(80, 70, 0xFFFFFF00u, (int)D_0061BC98, (int)msg);
    if (D_0028F8F4[0] & 0x20) {
        yes = 1;
    }
    return (D_0028F8F4[0] & 0x40) ? -1 : yes;
}

/* the "*" wildcard pattern D_0063AFC0 is copied into the request block's name
   field as a 2-byte object, not by strcpy */
typedef struct {
    char c[2];
} McPat;

extern char D_0063AFC0[];
extern int D_0063AFB8;
extern char D_0061BE08[];
extern char D_0061BE18[];
/* kept local: this TU's uses of iosMcChdirProduct do not fit the prototype in mcard.h */
extern void iosMcChdirProduct(McReq *mc);
/* kept local: this TU's uses of iosMcGetDir do not fit the prototype in mcard.h */
extern void iosMcGetDir(McReq *mc);
/* kept local: this TU's uses of iosMcSync do not fit the prototype in mcard.h */
extern int iosMcSync();

int debug_selectFile(McReq *mc)
{
    int i;
    int r = 0;
    int ret = 0;

    switch (D_0063AFB8) {
    case 0:
        mc->f0 &= ~2;
        iosMcChdirProduct(mc);
        D_0063AFB8++;
        break;
    case 1:
    case 4:
        if (iosMcSync(mc)) {
            D_0063AFB8++;
        }
        break;
    case 2:
    case 5:
        if ((ret = debug_mcRetErrCheck(mc)) != 0) {
            D_0063AFB8++;
        }
        break;
    case 3:
        *(McPat *)mc->name47C = *(McPat *)D_0063AFC0;
        iosMcGetDir(mc);
        D_0063AFB8++;
        break;
    case 6:
        for (i = 0; i < mc->num; i++) {
            debug_StdPrintfDummy(D_0061BE08, mc->dir[i].name,
                                 ((McDirEnt *)((char *)mc + (i << 6) + 0x4C0))->size);
        }
        D_0063AFB8++;
        break;
    default:
        debug_SelectCsvWindow(D_0061BE18, 0x50, 0x46, 0xA, mc->dir, 0x40, 0x20, 0, mc->num,
                              &mc->sel);
        if (D_0028F8F4[0] & 0x20) {
            r = 1;
        }
        if (D_0028F8F4[0] & 0x40) {
            r = -1;
        }
        break;
    }
    if (ret < 0) {
        r = -1;
    }
    if (r) {
        D_0063AFB8 = 0;
    }
    return r;
}

extern int D_0063AFD4;
extern char D_0063AFD8[];
extern char D_0061BE50[];
extern char D_0061BE90[];
extern char D_0063AFE0[];
extern char D_004DA788[];
extern char D_004DD700[];
/* kept local: this TU's uses of iosMcGetBlockSaveInfo do not fit the prototype in mcard.h */
extern void iosMcGetBlockSaveInfo(McReq *mc);
/* kept local: this TU's uses of iosMcSaveIconBlock do not fit the prototype in mcard.h */
extern void iosMcSaveIconBlock(McReq *mc);
/* kept local: this TU's uses of iosMcSaveProductBlock do not fit the prototype in mcard.h */
extern void iosMcSaveProductBlock(McReq *mc);
/* kept local: this TU's uses of iosMcSaveGameBlock do not fit the prototype in mcard.h */
extern void iosMcSaveGameBlock(McReq *mc, void *buf);
extern int debug_SelectCsvWindowVal(int a0, int a1, int a2, int a3, int count, int a5,
                                    int (*fn)(int, int), int a7);

/* the default save-file name "game." lives in .sdata as 6 bytes */
typedef struct {
    char c[6];
} McName6;

int debug_mcSaveMainBlock(McReq *mc)
{
    int r = 0;
    int ret = 0;

    switch (D_0063AFD4) {
    case 0:
        *(McName6 *)mc->name47C = *(McName6 *)D_0063AFD8;
        iosMcGetBlockSaveInfo(mc);
        D_0063AFD4++;
        break;
    case 1:
        if (iosMcSync(mc)) {
            D_0063AFD4++;
        }
        break;
    case 2:
    case 8:
    case 13:
        if ((ret = debug_mcRetErrCheck(mc)) != 0) {
            D_0063AFD4++;
        }
        break;
    case 3:
        if (mc->num >= 11) {
            debug_StdPrintfDummy(D_0061BE50);
        }
        r = debug_SelectCsvWindowVal((int)D_0061BE90, 0x50, 0x46, 0xA, 0xA, (int)&mc->sel,
                                     (int (*)(int, int))debug_saveNumFunc, (int)mc);
        if (r > 0) {
            r = 0;
            D_0063AFD4++;
        }
        break;
    case 4:
        iosMcSaveIconBlock(mc);
        D_0063AFD4++;
        break;
    case 6:
        iosMcSaveProductBlock(mc);
        D_0063AFD4++;
        break;
    case 5:
    case 7:
    case 12:
        debug_PrintfDummy(120, 70, 0xFFFFFF00u, (int)D_0063AFE0, (int)mc->name47C);
        if (iosMcSync(mc)) {
            D_0063AFD4++;
        }
        break;
    case 9:
        gamesysMemorySave(D_004DA788, D_004DD700, 0);
        iosMcSaveGameBlock(mc, D_004DD700);
        D_0063AFD4++;
        break;
    default:
        r = 1;
        break;
    }
    if (ret < 0) {
        r = -1;
    }
    if (r) {
        D_0063AFD4 = 0;
    }
    return r;
}

extern int D_0063AFE8;
extern char D_0061BED8[];
extern char D_0063AFF0[];
extern char D_0061BF18[];
/* kept local: this TU's uses of iosMcLoadProductBlock do not fit the prototype in mcard.h */
extern void iosMcLoadProductBlock(McReq *mc);
/* kept local: this TU's uses of iosMcLoadGameBlock do not fit the prototype in mcard.h */
extern void iosMcLoadGameBlock(McReq *mc, void *buf);

int debug_mcLoadMainBlock(McReq *mc)
{
    int r = 0;
    int ret = 0;

    switch (D_0063AFE8) {
    case 0:
        *(McName6 *)mc->name47C = *(McName6 *)D_0063AFD8;
        iosMcGetBlockSaveInfo(mc);
        D_0063AFE8++;
        break;
    case 1:
        if (iosMcSync(mc)) {
            D_0063AFE8++;
        }
        break;
    case 2:
    case 6:
    case 10:
        if ((ret = debug_mcRetErrCheck(mc)) != 0) {
            D_0063AFE8++;
        }
        break;
    case 3:
        if (mc->num >= 11) {
            debug_StdPrintfDummy(D_0061BED8);
        }
        r = debug_SelectCsvWindowVal((int)D_0061BE90, 0x50, 0x46, 0xA, 0xA, (int)&mc->sel,
                                     (int (*)(int, int))debug_saveNumFunc, (int)mc);
        if (r > 0) {
            r = 0;
            D_0063AFE8++;
        }
        break;
    case 4:
        if (((1 << mc->sel) & mc->blockFlags) == 0) {
            D_0063AFE8 = 99;
            break;
        }
        iosMcLoadProductBlock(mc);
        D_0063AFE8++;
        break;
    case 5:
    case 8:
        debug_PrintfDummy(120, 70, 0xFFFFFF00u, (int)D_0063AFF0, (int)mc->name47C);
        if (iosMcSync(mc)) {
            D_0063AFE8++;
        }
        break;
    case 7:
        iosMcLoadGameBlock(mc, D_004DD700);
        D_0063AFE8++;
        break;
    case 9:
        gamesysMemoryLoad(D_004DA788, D_004DD700, 0);
        D_0063AA08 = 0;
        D_0063AFE8++;
        break;
    case 99:
        if (debug_mcAsk(D_0061BF18)) {
            D_0063AFE8 = 3;
        }
        break;
    default:
        r = 1;
        break;
    }
    if (ret < 0) {
        r = -1;
    }
    if (r) {
        D_0063AFE8 = 0;
    }
    return r;
}

extern char D_0061C0C0[];
extern char D_0061C0D0[];
extern int D_0063AFF8;
extern int debug_selectFile(McReq *mc);
/* kept local: this TU's uses of iosMcDelete do not fit the prototype in mcard.h */
extern void iosMcDelete(McReq *mc);

int debug_mcDeleteFile(McReq *mc)
{
    char buf[0x20];
    int ret = 0;
    int r;

    switch (D_0063AFF8) {
    case 0:
        ret = debug_selectFile(mc);
        if (ret) {
            D_0063AFF8++;
        }
        if (ret > 0) {
            ret = 0;
        }
        break;
    case 1:
        sprintf(buf, D_0061C0C0, mc->dir[mc->sel].name);
        r = debug_mcConfirm(buf);
        if (r > 0) {
            D_0063AFF8++;
        } else if (r < 0) {
            D_0063AFF8 = 0;
        }
        break;
    case 2:
        strcpy(mc->name47C, mc->dir[mc->sel].name);
        iosMcDelete(mc);
        D_0063AFF8++;
        break;
    case 3:
        debug_PrintfDummy(120, 70, 0xFFFFFF00u, (int)D_0061C0D0, (int)mc->name47C);
        if (iosMcSync(mc)) {
            D_0063AFF8++;
        }
        break;
    case 4:
        if (debug_mcRetErrCheck(mc)) {
            D_0063AFF8++;
        }
        break;
    default:
        ret = 1;
        break;
    }
    if (ret) {
        D_0063AFF8 = 0;
    }
    return ret;
}

/* one line of the memory-card menu: the label debug_SelectCsvWindow prints and
   the state machine it hands control to */
typedef struct {
    char *label;
    int (*fn)();
} McMenuItem;

/* the card-state line: the iosMc state code, its colour and its caption */
typedef struct {
    int type;
    unsigned int col;
    char *msg;
} McTypeMsg;

extern McReq mc;
extern int D_0063B000;
extern int D_0063AFFC;
/* kept local: this TU's uses of iosMcGetInfo do not fit the prototype in mcard.h */
extern void iosMcGetInfo(McReq *mc);

int debug_MemoryCard(void)
{
    McMenuItem menu[6] = {
        {"LOAD", debug_mcLoadMainBlock}, {"SAVE", debug_mcSaveMainBlock},
        {"DELETE", debug_mcDeleteFile},  {"FORMAT", debug_mcFormat},
        {"UNFORMAT", debug_mcUnformat},  {"TEST", debug_mcTest},
    };
    McTypeMsg tm[3] = {
        {-1, 0x00FFFF00, "Formatted"},
        {-2, 0x00FFFF00, "Unformatted"},
        {0, 0xFF222200, "No card"},
    };
    McTypeMsg *p;
    int r;
    int (*fn)();

    switch (D_0063B000) {
    case 0:
        mc.fC = 0;
        mc.f8 = 0;
        iosMcGetInfo(&mc);
        D_0063B000++;
        break;
    case 1:
        if (iosMcSync(&mc)) {
            D_0063B000++;
        }
        break;
    case 2:
        p = tm;
        while (mc.f1C != p->type && p->type != 0) {
            p++;
        }
        if (mc.f14 != 2) {
            p = &tm[2];
        }
        debug_PrintfDummy(10, 60, p->col, (int)"Memory card port 0: %s free:%d Kbytes", (int)p->msg,
                          mc.f18);
        if (mc.ret >= -2) {
            r = debug_SelectCsvWindow("MENU", 0xA, 0x44, 0xA, menu, 8, 0, 1, 6, &D_0063AFFC);
            if (r == 1) {
                D_0063B000++;
            } else if (r == -1) {
                D_0063B000 = 0;
                return -1;
            }
        } else if (D_0028F8F4[0] & 0x40) {
            D_0063B000 = 0;
            return -1;
        }
        break;
    default:
        fn = menu[D_0063AFFC].fn;
        if (fn != 0) {
            if (fn(&mc) != 0) {
                D_0063B000 = 0;
                return 1;
            }
        }
        break;
    }
    return 0;
}

/* INTERIM (see _debug_SelectCsvWindow_inl above): debug_SelectCsvWindowWithLineColor
   is `inline` in the 2001 source, so its callers inline it while the ELF also
   carries the out-of-line copy at its own ROM slot. */
static inline int debug_SelectCsvWindowWithLineColor_inl(char *title, int x, int y, int rows,
                                                         int base, int stride, int off, int deref,
                                                         int n, int *psel, int (*colfunc)(int))
{
    return _debug_SelectCsvWindow_inl(title, x, y, rows, base, stride, off, deref, n, psel,
                                      getLineBuffer, colfunc);
}

extern char *D_00639EA4;
extern int D_0063B040;
extern int D_0063B044;
extern char D_0063B048[];
extern GsysObjInfo D_005D6DB0[];

int debug_SETest(int reset)
{
    int r;

    if (reset != 0) {
        D_0063B044 = -1;
    }
    r = debug_SelectCsvWindowWithLineColor_inl(D_0063B048, 0xA, 0x3C, 0xA, (int)D_005D6DB0, 0x3C, 0,
                                               0, 0x592, &D_0063B040, debug_SETest_color);
    if (r > 0) {
        D_0063B044 = soundSeDefPlay(D_0063B040, 0, GOBJ_SUB(D_00639EA4)->f_C + 0x30, 1);
        return 0;
    }
    if (r < 0) {
        soundSeGroupStop(1);
    }
    return r;
}

extern int SgGetSlotStatus(int a0, int slot);
extern char D_0063B050[];
extern char D_0063B058[];

void debug_SESlotDisp(void)
{
    unsigned char mask[6];
    char buf[32];
    char tmp[16];
    int i = 0;
    int k;
    int bit;
    int y;
    int col;
    memset(mask, 0, 6);
    for (; i < 48; i++) {
        if (SgGetSlotStatus(0, i) == 2) {
            mask[i / 8] |= 1 << (i % 8);
        }
    }
    for (k = 0; k < 2; k++) {
        col = 0xFFFFFF00;
        if (k != 0) {
            col = 0xFF000000;
        }
        for (i = 0; i < 48; i++) {
            y = i / 8 * 8 + 100;
            bit = i % 8;
            if (bit == 0) {
                buf[0] = 0;
            }
            if (((mask[i / 8] >> bit) & 1) == k) {
                sprintf(tmp, D_0063B050, i);
            } else {
                sprintf(tmp, D_0063B058);
            }
            strcat(buf, tmp);
            if (bit == 7) {
                debug_PrintfDummy(400, y, col, (int)D_0063AF80, (int)buf);
            }
        }
    }
}

extern int D_0070F880[];
extern char D_0063B068[];
extern char D_0063B070[];
extern char D_0055F828[];
extern char D_0061C1D0[];
extern char D_007048C0[];

char *debugCdvdLoadInfoSegDispFunc(int idx, int page)
{
    char buf[0x10];
    int d;
    d = *(int *)((char *)D_0070F880 + (page * 0xD0 + idx * 8)) -
        *(int *)((char *)D_0070F880 + (page * 0xD0 + idx * 8) + 4);
    if (d < 0) {
        sprintf(buf, D_0063B068, -d);
    } else {
        sprintf(buf, D_0063B070, d);
    }
    sprintf(D_007048C0, D_0061C1D0, D_0055F828 + idx * 0x24,
            *(int *)((char *)D_0070F880 + (page * 0xD0 + idx * 8)),
            *(int *)((char *)D_0070F880 + (page * 0xD0 + idx * 8) + 4), buf);
    return D_007048C0;
}

/* src/debug.c:5364-5376 in the listing: the sibling of debug_ListPadControlGobj
   that lists the actor GObjs the debug menu can print (kinds 1, 2, 4 and 0x2F). */
typedef struct {
    char *name;
    void *obj;
} DbgGobjEnt;

extern ObjKindEnt D_002C1270[];

static inline int debug_ListActGobj(DbgGobjEnt *list)
{
    void *g;
    int n = 0;
    for (g = isysGObjGetExist_begin(); g != 0; g = isysGObjGetExist_next(g)) {
        int kind = ((PObjGObj *)g)->kind;
        switch (kind) {
        case 1:
        case 2:
        case 4:
        case 0x2F:
            list[n].name = ((ObjKindEnt *)((char *)D_002C1270 + kind * 0x64))->name;
            list[n].obj = g;
            n++;
        }
    }
    return n;
}

extern char D_0061C210[];
extern int D_0063B080;

int debug_SelectActGobj(int reset)
{
    DbgGobjEnt list[10];
    int n;
    int r;
    n = debug_ListActGobj(list);
    if (reset != 0) {
        D_0063B080 = 0;
    }
    r = debug_SelectCsvWindow(D_0061C210, 0xA, 0x32, 0xB, list, 8, 0, 1, n, &D_0063B080);
    if (D_0063B080 >= 0) {
        _ACTDebugPrint(list[D_0063B080].obj);
    }
    return (r == -1) ? -1 : 0;
}

/* one editable row of the debug box: its label and the value shown */
typedef struct {
    char *name;
    int val;
} DbgBoxVal;

extern float D_007048E0[]; /* the box centre */
extern float D_007048F0[]; /* its half extents */
extern int D_0063C378;     /* the selected row */
extern void DebugDispBox(float *centre, float *width);
/* The literals these two functions read stay blob-owned by address until the
   stubs between them land and the TU's plain .rodata and .sdata runs close
   up: the object's plain sections must stay contiguous with the ROM's. */
extern char D_0061C240[]; /* ">>%8s = %d\n" */
extern char D_0061C250[]; /* "  %8s = %d\n" */
extern char D_0061C260[]; /* "[%s] %4d %4d %4d" */
extern char D_0063B088[]; /* "centerX" */
extern char D_0063B090[]; /* "centerY" */
extern char D_0063B098[]; /* "centerZ" */
extern char D_0063B0A0[]; /* " widthX" */
extern char D_0063B0A8[]; /* " widthY" */
extern char D_0063B0B0[]; /* " widthZ" */
extern char D_0063B0B8[]; /* "center" */
extern char D_0063B0C0[]; /* " width" */
extern char D_0063B0D0[]; /* " radius" */

int debug_DispBox(int on)
{
    int i;
    int step;
    int num;

    if (on) {
        if (D_00639EA4 != 0) {
            GetRootPosition(D_007048E0, D_00639EA4);
        } else {
            D_007048E0[0] = 0.0f;
            D_007048E0[1] = 0.0f;
            D_007048E0[2] = 0.0f;
        }
        D_007048F0[0] = 100.0f;
        D_007048F0[1] = 100.0f;
        D_007048F0[2] = 100.0f;
        D_0063C378 = 0;
    }
    if (D_0028F8F0[0].trg & 0x1000) {
        D_0063C378--;
    }
    if (D_0028F8F0[0].trg & 0x4000) {
        D_0063C378++;
    }
    num = 6;
    D_0063C378 = (D_0063C378 + num) % num;
    step = (D_0028F8F0[0].trg & 0x2000) ? 100 : 0;
    if (D_0028F8F0[0].trg & 0x8000) {
        step = -100;
    }
    switch (D_0063C378) {
    case 0:
        D_007048E0[0] += (float)step;
        break;
    case 1:
        D_007048E0[1] += (float)step;
        break;
    case 2:
        D_007048E0[2] += (float)step;
        break;
    case 3:
        D_007048F0[0] += (float)step;
        break;
    case 4:
        D_007048F0[1] += (float)step;
        break;
    case 5:
        D_007048F0[2] += (float)step;
        break;
    }
    {
        DbgBoxVal list[6] = {
            {D_0063B088, (int)D_007048E0[0]}, {D_0063B090, (int)D_007048E0[1]},
            {D_0063B098, (int)D_007048E0[2]}, {D_0063B0A0, (int)D_007048F0[0]},
            {D_0063B0A8, (int)D_007048F0[1]}, {D_0063B0B0, (int)D_007048F0[2]},
        };

        for (i = 0; i < 6; i++) {
            if (i == D_0063C378) {
                debug_PrintfDummy(10, i * 10 + 80, 0xFFFFFF00u, (int)D_0061C240, (int)list[i].name,
                                  list[i].val);
            } else {
                debug_PrintfDummy(10, i * 10 + 80, 0xFFFFFF00u, (int)D_0061C250, (int)list[i].name,
                                  list[i].val);
            }
        }
    }
    CameraSetMode(1);
    DebugDispBox(D_007048E0, D_007048F0);
    if (D_0063B13C & 1) {
        debug_Printf(10, 150, 0xFFFFFF00u, (int)D_0061C260, (int)D_0063B0B8, (int)D_007048E0[0],
                     (int)D_007048E0[1], (int)D_007048E0[2]);
    }
    if (D_0063B13C & 1) {
        debug_Printf(10, 160, 0xFFFFFF00u, (int)D_0061C260, (int)D_0063B0C0, (int)D_007048F0[0],
                     (int)D_007048F0[1], (int)D_007048F0[2]);
    }
    return (D_0028F8F0[0].hold & 0x40) ? -1 : 0;
}

/* one editable value of the debug ball: its label and the cell it moves */
typedef struct {
    char *name;
    float *val;
} DbgBallVal;

typedef struct {
    DbgBallVal v[4];
} DbgBallList;

/* the four-row initialiser template (centerX, centerY, centerZ, radius), blob-owned
   by address until the TU's plain .rodata run closes up */
extern const DbgBallList D_0061C298;
extern Col4 D_0061C2C0;    /* { 0, 0x10, 0x20, 0x80 } : wire sphere colour */
extern float D_00704900[]; /* the ball's centre */
extern float D_0063B0C8;   /* its radius */
extern int D_0063C37C;     /* the selected row */
extern void GetRootPosition(void *a0, char *outer);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void MatrixDrive_TransMatrixV(void *a0);
extern void sceVu0UnitMatrix(void *m);
extern void prim_DispWireSphere(float r, void *col, int nu, int nv);
extern int scpTriggerPosBall(float *pos, float *target, float r);

int debug_DispBall(int on)
{
    DbgBallList list = D_0061C298;
    float pos[4];
    Col4 col;
    int i;
    int hit;
    int step;
    int num;

    num = 4;
    hit = 0;
    if (on) {
        if (D_00639EA4 != 0) {
            GetRootPosition(D_00704900, D_00639EA4);
        } else {
            D_00704900[0] = 0.0f;
            D_00704900[1] = 0.0f;
            D_00704900[2] = 0.0f;
        }
        D_0063B0C8 = 100.0f;
        D_0063C37C = 0;
    }
    if (D_0028F8F0[0].trg & 0x1000) {
        D_0063C37C--;
    }
    if (D_0028F8F0[0].trg & 0x4000) {
        D_0063C37C++;
    }
    D_0063C37C = (D_0063C37C + num) % num;
    step = (D_0028F8F0[0].trg & 0x2000) ? 10 : 0;
    if (D_0028F8F0[0].trg & 0x8000) {
        step = -10;
    }
    switch (D_0063C37C) {
    case 0:
        D_00704900[0] += (float)step;
        break;
    case 1:
        D_00704900[1] += (float)step;
        break;
    case 2:
        D_00704900[2] += (float)step;
        break;
    case 3:
        D_0063B0C8 += (float)step;
        break;
    }
    for (i = 0; i < num; i++) {
        if (i == D_0063C37C) {
            if (D_0063B13C & 1) {
                debug_Printf(10, i * 10 + 80, 0xFFFFFF00u, (int)D_0061C240, (int)list.v[i].name,
                             (int)*list.v[i].val);
            }
        } else {
            if (D_0063B13C & 1) {
                debug_Printf(10, i * 10 + 80, 0xFFFFFF00u, (int)D_0061C250, (int)list.v[i].name,
                             (int)*list.v[i].val);
            }
        }
    }
    CameraSetMode(1);
    if (D_00639EA4 != 0) {
        GetRootPosition(pos, D_00639EA4);
        hit = scpTriggerPosBall(pos, D_00704900, D_0063B0C8);
    }
    MatrixDrive_PushMatrix();
    col = D_0061C2C0;
    if (hit) {
        col.c[0] = 255;
    }
    gif_StartPacketPri(11);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrixV(D_00704900);
    prim_DispWireSphere(D_0063B0C8, &col, 16, 8);
    gif_EndPacket();
    MatrixDrive_PopMatrix();
    return (D_0028F8F0[0].hold & 0x40) ? -1 : 0;
}

/* iosPadGetStick's output block: the raw pair at +0 and +4, the camera-space
   pair at +0xC/+0x10 and the stick deflection at +0x14 (the same record
   effectTool.c and camera-ico2.c read) */
typedef struct {
    int x;         /* 0x00 */
    int y;         /* 0x04 */
    int unk08;     /* 0x08 */
    float fx;      /* 0x0C */
    float fz;      /* 0x10 */
    float mag;     /* 0x14 */
    char unk18[8]; /* 0x18 */
} DbgPadStick;

/* the wall record ClipCollision leaves at +0x80 of the ray: the polygon it hit,
   the triangle within it and the hit flag, exactly the three words
   DebugDisp1Collision reads back */
typedef struct {
    void *poly;
    int tri;
} DbgWallRef;

typedef struct {
    DbgWallRef ref;
    int hit;
} DbgWallHit;

/* the ray debug_CollisionTest drives through ClipCollision: the two end points,
   the hit point it fills in, and the wall and floor results it reports */
typedef struct {
    float src[4];    /* 0x00 */
    float dst[4];    /* 0x10 */
    float hit[4];    /* 0x20 */
    char _30[64];    /* 0x30 */
    int f70;         /* 0x70 */
    char _74[12];    /* 0x74 */
    DbgWallHit wall; /* 0x80 */
    char _8C[8];     /* 0x8C */
    int floorHit;    /* 0x94 */
} DbgRay;

extern char D_0061C300[];     /* "Collision Test" */
extern char *D_004D9D58[];    /* the three row labels: move all, move src, move dst */
extern int D_0063C380;        /* the selected row */
extern DbgRay D_00704910;     /* the ray the test drives */
extern char D_0061C310[];     /* "HIT: %p,%d" */
extern char D_0061C320[];     /* "ATTR: %x" */
extern char D_0061C330[];     /* "SRC: %f, %f, %f" */
extern char D_0061C340[];     /* "DST: %f, %f, %f" */
extern const Col4 D_004D9D70; /* the wall hit sphere colour */
extern const Col4 D_004D9D80; /* the floor hit sphere colour */
extern char iosPadConfDefault[];
extern int iosPadConnect(void *dev, int a1, int a2, void *conf);
extern int iosPadRead(void *dev);
extern int iosPadGetStick(void *dev, void *out, int mode, int a3, int a4, int a5);
extern void iosPadStickCameraCoord(void *out, float *stick);
/* kept local: this TU's use of _AddVector does not fit the prototype in Matrix.h */
extern void _AddVector(void *dst, void *a, void *b);
extern void CopyVector(void *dst, void *src);
extern void DebugDisp1Collision(void *hit);

int debug_CollisionTest(int reset)
{
    float v[4];
    VECTOR mv;
    int padCtx[0x60 / 4];
    DbgPadStick st0;
    DbgPadStick st1;
    DbgWallHit wall;
    int r;

    r = debug_SelectCsvWindow(D_0061C300, 10, 50, 11, D_004D9D58, 4, 0, 1, 3, &D_0063C380);
    if (reset != 0) {
        GetRootPosition(D_00704910.src, D_00639EA4);
        CopyVector(D_00704910.dst, D_00704910.src);
        D_00704910.f70 = 0;
        D_00704910.dst[2] += 100.0f;
    }
    memset(&mv, 0, sizeof(mv));
    iosPadConnect(padCtx, 0, 0, iosPadConfDefault);
    iosPadRead(padCtx);
    iosPadGetStick(padCtx, &st0, 0, 2, 2, 0);
    iosPadGetStick(padCtx, &st1, 1, 2, 2, 0);
    iosPadStickCameraCoord(v, (float *)&st1);
    if (padCtx[2] & 8) {
        if (st1.mag > 0.001f) {
            mv.y = st1.fz * st1.mag * 16.0f;
        }
    } else {
        if (st1.mag > 0.001f) {
            mv.x = v[0] * st1.mag * 16.0f;
            mv.z = v[2] * st1.mag * 16.0f;
        }
    }
    switch (D_0063C380) {
    case 1:
        _AddVector(D_00704910.src, D_00704910.src, &mv);
        break;
    case 2:
        _AddVector(D_00704910.dst, D_00704910.dst, &mv);
        break;
    case 0:
    default:
        _AddVector(D_00704910.src, D_00704910.src, &mv);
        _AddVector(D_00704910.dst, D_00704910.dst, &mv);
        break;
    }
    ClipCollision((int *)&D_00704910);
    if (D_00704910.wall.hit != 0) {
        wall.ref = D_00704910.wall.ref;
        wall.hit = D_00704910.wall.hit;
        *(DbgWallHit *)&mv = wall;
        gif_StartPacketPri(11);
        gif_SetZWrite(0);
        gif_SetZTest(0);
        gif_SetAlpha(1, 0, 0x80);
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrixV(D_00704910.hit);
        prim_DispWireSphere(5.0f, (void *)&D_004D9D70, 8, 4);
        gif_EndPacket();
        DebugDisp1Collision(&mv);
        debug_PrintfDummy(80, 180, 0xFFFFFF00u, (int)D_0061C310, (int)D_00704910.wall.ref.poly,
                          D_00704910.wall.ref.tri);
        debug_PrintfDummy(80, 190, 0xFFFFFF00u, (int)D_0061C320,
                          GetWallAttribute((int)&D_00704910));
    }
    if (D_00704910.floorHit != 0) {
        gif_StartPacketPri(11);
        gif_SetZWrite(0);
        gif_SetZTest(0);
        gif_SetAlpha(1, 0, 0x80);
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_TransMatrixV(D_00704910.hit);
        prim_DispWireSphere(5.0f, (void *)&D_004D9D80, 8, 4);
        gif_EndPacket();
    }
    debug_PrintfDummy(80, 160, 0xFFFFFF00u, (int)D_0061C330, D_00704910.src[0], D_00704910.src[1],
                      D_00704910.src[2]);
    debug_PrintfDummy(80, 170, 0xFFFFFF00u, (int)D_0061C340, D_00704910.dst[0], D_00704910.dst[1],
                      D_00704910.dst[2]);
    CameraSetMode(1);
    DrawCollisionRay((char *)&D_00704910);
    DrawCollision(0);
    return r;
}

/* one debug-menu entry: the label the selector prints, the handler, and a
   "stay in the menu" flag */
typedef struct {
    char *label;
    int (*fn)(int);
    int stay;
} DbgMenuItem;

extern DbgMenuItem D_004D9D90[];
extern char *D_004D9ED8[];
extern int D_0063B0F0;
extern int D_0063B0F4;
extern int D_0063B0F8;
extern int D_0063B0FC;
extern int D_0063AE74;
extern char D_0061C528[];
extern char D_0061C538[];
extern char D_0061C548[];
extern char D_0061C558[];
extern char D_0061C570[];

static inline void debug_MenuHelp(void)
{
    int x;
    int y;
    int i;

    debug_PrintfDummy(220, 70, 0xFFFFFF80u, (int)D_0061C558);
    x = 0xF0;
    y = 0x50;
    i = 0;
    while (D_004D9ED8[i] != 0) {
        debug_PrintfDummy(x, y, 0x80808080u, (int)D_0063AF80, (int)D_004D9ED8[i]);
        y += 10;
        if (y >= 301) {
            y = 0x50;
            x += 200;
        }
        i++;
    }
}

static inline void debug_MenuBlink(void)
{
    if (D_0063B0F0 >> 4) {
        debug_PrintfDummy(220, 60, 0x80C0FF80u, (int)D_0061C528, (int)D_0061C538, (int)D_0061C548);
    }
    D_0063B0F0++;
    if (D_0063B0F0 >= 0x41) {
        D_0063B0F0 = 0;
    }
}

void debug_Menu(void)
{
    int state;
    int r;
    int (*fn)(int);

    if ((D_0028F8F0[0]._0 & 2) == 0) {
        if (D_0028F8F0[0].hold & 0x100) {
            if (D_0063B0F4 == 0) {
                D_0063AE74 = 1;
                D_0063B0F4 = 1;
                D_0063B0F8 = 0;
                return;
            }
        }
    }
    state = D_0063B0F4;
    if (state == 1) {
        r = debug_SelectCsvWindow(D_0061C570, 0xA, 0x32, 0xB, D_004D9D90, 0xC, 0, 1, 0x1B,
                                  &D_0063B0F8);
        switch (r) {
        case 0:
            break;
        case -1:
            D_0063B0F4 = 0;
            D_0063AE74 = 0;
            break;
        default:
            D_0063B0F4 = 2;
            D_0063B0FC = state;
            break;
        }
        debug_MenuHelp();
        debug_MenuBlink();
    } else if (state == 2) {
        fn = D_004D9D90[D_0063B0F8].fn;
        if (fn == 0) {
            D_0063B0F4 = 0;
            D_0063AE74 = 0;
        } else {
            r = fn(D_0063B0FC);
            D_0063B0FC = 0;
            if (r == -1) {
                D_0063B0F4 = 1;
            } else if (r != 0) {
                if (D_004D9D90[D_0063B0F8].stay == 0) {
                    D_0063B0F4 = 1;
                } else {
                    D_0063B0F4 = 0;
                    D_0063AE74 = 0;
                }
            }
        }
    }
}

void debug_Menu_off(void)
{
    D_0063B0F4 = 0;
}

void debug_BeginTimer(int a0)
{
    *(volatile int *)0x10000800 = 0;
    *(volatile int *)0x10000810 = a0 | 0x80;
}

extern Blk16 D_0061B7C8;

float debug_GetTimerSec(void)
{
    Blk16 buf;
    int v;
    float f2;

    buf = D_0061B7C8;
    if (*(volatile unsigned int *)0x10000810 & 0x800) {
        return -1.0f;
    }
    v = *(volatile int *)0x10000800;
    f2 = (float)(unsigned int)v;
    return f2 / buf.f[*(volatile unsigned int *)0x10000810 & 3] / 60.0f;
}

float debug_GetTimerCount(void)
{
    if ((*(volatile int *)0x10000810) & 0x800) {
        return -1.0f;
    }
    return (float)(*(volatile unsigned int *)0x10000800);
}

void debug_ClearFontWindow(void)
{
    char *p = (char *)D_007082D0;
    int i;
    p += 0x5B4;
    for (i = 0x1A; i >= 0; i--) {
        *p = 0;
        p -= 0x38;
    }
    D_0063AE64 = 0;
}

void debug_ResizeFontWindowHeight(int val)
{
    D_0063AEB4 = val;
}

/* Profiler bar table: 0x400 entries of 0x1C bytes; D_0063C384 = live count.
   Callers pass (label, colour, __FILE__, __LINE__) -- see the call sites in
   main.c and motionManager2.c, where a3 is literally the caller's line number.
   +0x14 samples the EE timer T0_COUNT at 0x10000000; volatile because it is a
   hardware counter (and the ROM's 32-bit `lw` shows the read is not narrowed). */
extern int D_0063B1D4;
extern char D_0063AF30[];

void debug_SetBar(char *name, unsigned int col, char *file, int line)
{
    DebugBar *p = &D_00708880[D_0063C384];
    if (D_0063B1D4 == 0 && D_0063C384 != 0x400) {
        sprintf(p->name, D_0063AF30, name);
        p->count = *(volatile int *)0x10000000;
        p->col[0] = col >> 24;
        p->col[1] = col >> 16;
        p->col[2] = col >> 8;
        p->col[3] = col;
        p->file = file;
        p->line = line;
        D_0063C384++;
    }
}

/* debug_SetBar with the inverted D_0063B1D4 gate (records only while the
   profiler flag is set). */
void debug_SetBar2(char *name, unsigned int col, char *file, int line)
{
    DebugBar *p = &D_00708880[D_0063C384];
    if (D_0063B1D4 != 0 && D_0063C384 != 0x400) {
        sprintf(p->name, D_0063AF30, name);
        p->count = *(volatile int *)0x10000000;
        p->col[0] = col >> 24;
        p->col[1] = col >> 16;
        p->col[2] = col >> 8;
        p->col[3] = col;
        p->file = file;
        p->line = line;
        D_0063C384++;
    }
}

void debug_ResetBar(void)
{
    D_0063B120 = 0;
    *(volatile int *)0x10000000 = 0;
    D_0063B11C = 0;
    D_0063B118 = 0;
    D_0063B114 = 0;
    D_0063B110 = 0;
    D_0063B124 = 0;
    D_0063C384 = 0;
}

extern char D_0061BB80[];

void debug_DispVu1IReg(int no)
{
    int i;
    int buf[4];
    if (no >= 0) {
        __asm__ __volatile__("ctc2.ni %0, $vi1" : : "r"(no * 16 + 0x420));
        __asm__ __volatile__("vlqi.xyzw $vf2, ($vi1++)");
        __asm__ __volatile__("sqc2 $vf2, %0" : "=m"(buf) : : "memory");
        debug_StdPrintfDummy(D_0061BB80, no, buf[0], buf[1], buf[2], buf[3]);
    } else {
        __asm__ __volatile__("ctc2.ni %0, $vi1" : : "r"(0x420));
        for (i = 0; i < 16; i++) {
            __asm__ __volatile__("vlqi.xyzw $vf2, ($vi1++)");
            __asm__ __volatile__("sqc2 $vf2, %0" : "=m"(buf) : : "memory");
            debug_StdPrintfDummy(D_0061BB80, i, buf[0], buf[1], buf[2], buf[3]);
        }
    }
}

extern char D_0061BBA0[];

void debug_DispVu1SReg(int no)
{
    int i;
    int buf[4];
    if (no >= 0) {
        __asm__ __volatile__("ctc2.ni %0, $vi1" : : "r"(no * 16 + 0x420));
        __asm__ __volatile__("vlqi.xyzw $vf2, ($vi1++)");
        __asm__ __volatile__("sqc2 $vf2, %0" : "=m"(buf) : : "memory");
        debug_StdPrintfDummy(D_0061BBA0, no, buf[0], buf[1], buf[2], buf[3]);
    } else {
        __asm__ __volatile__("ctc2.ni %0, $vi1" : : "r"(0x420));
        for (i = 0; i < 16; i++) {
            __asm__ __volatile__("vlqi.xyzw $vf2, ($vi1++)");
            __asm__ __volatile__("sqc2 $vf2, %0" : "=m"(buf) : : "memory");
            debug_StdPrintfDummy(D_0061BBA0, i, buf[0], buf[1], buf[2], buf[3]);
        }
    }
}

void debug_DispMatrix(int *a0)
{
    int *p = a0;
    int i;
    for (i = 3; i >= 0; i--) {
        debug_DispQW(p, 0);
        p = (int *)((char *)p + 0x10);
    }
}

void debug_SetBarDummy(void) {}

int debug_SelectCsvWindowWithLine(char *title, int x, int y, int rows, void *base, int stride,
                                  int off, int deref, int n, int *psel)
{
    return _debug_SelectCsvWindow_inl(title, x, y, rows, (int)base, stride, off, deref, n, psel,
                                      getLineBuffer, 0);
}

int debug_TryToGetStartStage(void)
{
    return -1;
}

extern int D_0061C580[];
extern int D_0063B100;
extern int D_0063B108[];
extern int D_007049D0[];
extern int sceOpen(void *a0, int a1);

int debugSceOpen(int a0, int a1)
{
    sprintf(D_007049D0, D_0063B108, D_0061C580, a0);
    return D_0063B100 = sceOpen(D_007049D0, a1);
}

extern int sceClose();

int debugSceClose(int a0)
{
    if (a0 == D_0063B100) {
        D_0063B100 = -1;
    }
    return sceClose();
}

int debugSceCloseFdNew(void)
{
    int r = 0;
    int h = D_0063B100;
    if (h != -1) {
        D_0063B100 = -1;
        r = sceClose(h);
        D_0063B100 = -1;
    }
    return r;
}

void debug_closeLog(void) {}

void debugCdvdLoadInfoSegInit(int idx)
{
    int *p;
    char *new_var2;
    int new_var;
    int i;
    new_var2 = (char *)D_0070F880;
    p = (int *)((new_var2 + (idx * 0xD0)) + 0xC8);
    if (1) {
        for (i = 0x19; i >= 0; i--) {
            new_var = (*p = 0);
            p = (p = (int *)(((char *)p) - 8));
        }
    }
}

void debugCdvdLoadInfoSegAdd(int page, int idx, int delta)
{
    *(int *)((char *)D_0070F880 + (page * 0xD0 + idx * 8)) += delta;
}

void debugCdvdLoadInfoSegCls(int page, int idx)
{
    *(int *)((char *)D_0070F880 + (page * 0xD0 + idx * 8)) = 0;
}

extern int D_0028F4F0[];

int gsResetFunc(void)
{
    gsb_Init(D_0028F4F0);
    return 1;
}

void ChangeGirlControlMode(int a0)
{
    if (a0 == 1) {
        D_00639EA0 = a0;
    }
}

int debug_CallbackGsFinish(void)
{
    D_0063AE68 = *(volatile int *)0x10000000;
    return 0;
}

extern char D_0061B4A8[];
extern char D_0061B4E8[];
extern char D_0061B500[];
extern char D_0061B538[];

void debug_SaveStartStageFile(int stage)
{
    char buf[0x100];
    debug_StdPrintfDummy(D_0061B4A8);
    if (debugSceOpen((int)D_0061B4E8, 0x602) < 0) {
        debug_StdPrintfDummy(D_0061B500);
    } else {
        sprintf(buf, D_0063AE90, stage);
        sceWrite(0, buf, strlen(buf));
        debug_StdPrintfDummy(D_0061B538, stage);
        debugSceClose(0);
    }
    debug_StdPrintfDummy(D_0061B570);
    debug_openLog();
}

int _debug_SelectCsvWindow(char *title, int x, int y, int rows, int base, int stride, int off,
                           int deref, int n, int *psel, void (*getline)(), int (*colfunc)(int))
{
    char buf[0x100];
    int sel;
    int i;
    int half;
    int k;
    int top;
    int end;
    int yy;
    int len;
    int v;
    int col;

    sel = *psel;
    debug_PrintfDummy(x, y, 0xFFFFFF00u, (int)D_0063AF80, (int)title);
    if ((D_0028F8F0[0]._0 & 2) == 0) {
        if (D_0028F8F0[0].hold & 0x80) {
            D_0063B13C ^= 2;
        }
        if (sel >= n) {
            sel = n - 1;
        }
        if (D_0028F8F0[0].trg & 0x4000) {
            sel++;
            if (sel >= n) {
                sel = 0;
            }
        }
        if (D_0028F8F0[0].trg & 0x1000) {
            sel--;
            if (sel < 0) {
                sel = n - 1;
            }
        }
        if (n < rows) {
            rows = n;
        }
        half = (int)(((float)rows - 0.5f) * 0.5f);
        if (sel < half) {
            k = sel;
        } else if (n - (rows - half) < sel) {
            k = rows - (n - sel);
        } else {
            k = half;
        }
        top = sel - k;
        yy = y + 8;
        for (i = top; i < top + rows; i++) {
            if (i - top == k) {
                col = 0xFF404000;
            } else if (colfunc == 0) {
                col = 0xFFFFFF00;
            } else {
                col = colfunc(i);
            }
            v = base + stride * i + off;
            if (deref == 1) {
                v = *(int *)v;
            }
            len = D_0063AF7C;
            getline(buf, i, v);
            if (len >= 2) {
                if (len >= 0x100) {
                    len = 0xFF;
                }
                buf[len - 1] = -110;
                buf[len] = 0;
            } else {
                buf[0] = 0;
            }
            debug_PrintfDummy(x, yy, col, (int)D_0063AF88, (int)buf);
            yy += 8;
        }
        if (D_0063AF7C <= 0xFFFE) {
            D_0063AF7C += D_0028F4C4[0];
        }
        *psel = sel;
        if (D_0028F8F0[0].hold & 0x20) {
            D_0063AF7C = 0;
            return 1;
        } else if (D_0028F8F0[0].hold & 0x140) {
            D_0063AF7C = 0;
            return -1;
        }
    }
    return 0;
}

int debug_SelectCsvWindowWithLineColor(char *title, int x, int y, int rows, void *base, int stride,
                                       int off, int deref, int n, int *psel, int (*colfunc)(int))
{
    return _debug_SelectCsvWindow_inl(title, x, y, rows, (int)base, stride, off, deref, n, psel,
                                      getLineBuffer, colfunc);
}

extern int D_0063AFA0;
extern int D_0063AFA4;
extern char D_0063AFA8[];
extern char D_0061BCA8[];
/* kept local: this TU's uses of iosMcFormat do not fit the prototype in mcard.h */
extern void iosMcFormat(int port);
/* kept local: this TU's uses of iosMcSync do not fit the prototype in mcard.h */
extern int iosMcSync(int port);

int debug_mcFormat(int port)
{
    int r;
    switch (D_0063AFA0) {
    case 0:
        r = debug_mcConfirm(D_0063AFA8);
        if (r != 1) {
            return r;
        }
        iosMcFormat(port);
        D_0063AFA0++;
        break;
    case 1:
        if (D_0063AFA4++ & 0x10) {
            debug_PrintfDummy(120, 70, 0xFFFFFF00u, (int)D_0061BCA8);
        }
        if (iosMcSync(port) != 0) {
            D_0063AFA0++;
        }
        break;
    default:
        D_0063AFA0 = 0;
        return 1;
    }
    return 0;
}

extern int D_0063AFB0;
extern int D_0063AFB4;
extern char D_0061BCB8[];
extern char D_0061BCC8[];
/* kept local: this TU's uses of iosMcUnformat do not fit the prototype in mcard.h */
extern void iosMcUnformat(int port);

int debug_mcUnformat(int port)
{
    int r;
    switch (D_0063AFB0) {
    case 0:
        r = debug_mcConfirm(D_0061BCB8);
        if (r != 1) {
            return r;
        }
        iosMcUnformat(port);
        D_0063AFB0++;
        break;
    case 1:
        if (D_0063AFB4++ & 0x10) {
            debug_PrintfDummy(120, 70, 0xFFFFFF00u, (int)D_0061BCC8);
        }
        if (iosMcSync(port) != 0) {
            D_0063AFB0++;
        }
        break;
    default:
        D_0063AFB0 = 0;
        return 1;
    }
    return 0;
}

extern char D_0063AFC8[];
extern char D_0063AFD0[];

void *debug_saveNumFunc(int a0, void *a1)
{
    if ((1 << a0) & ((McReq *)a1)->blockFlags) {
        return D_0063AFC8;
    }
    return D_0063AFD0;
}

/* kept local: this TU's uses of iosMcTest do not fit the prototype in mcard.h */
extern void iosMcTest(void);

int debug_mcTest(void)
{
    iosMcTest();
    return 1;
}

/* kept local: the declaration in staffroll.h changes this TU codegen */
extern void staffRollStart(int a0, float a1);

int debug_STAFFROLLTest(void)
{
    staffRollStart(0x80, 1.0f);
    return 1;
}

extern unsigned short D_0030C4E0[];

int debug_SETest_color(int idx)
{
    int new_var;
    int v3 = D_005D6DB0[idx].f_20;
    unsigned short a4 = *((unsigned short *)(((char *)D_0030C4E0) + (v3 * 2)));
    int v0 = 0x80808000;
    int a3 = -0x100;
    if (new_var = a4 != 0) {
        v0 = a3;
    }
    return v0;
}

/* pad state block: +0x4 held buttons, +0xC newly-pressed (trigger) buttons */
extern char D_0061C1A8[];

int debug_reverbTest(void)
{
    int depth = soundReverbDepthGet();
    if (D_0028F8F0[0].trg & 0x1000) {
        if (depth <= 99) {
            depth++;
        }
    }
    if (D_0028F8F0[0].trg & 0x4000) {
        depth -= (0 < depth);
    }
    soundReverbDepthSet(depth);
    debug_PrintfDummy(10, 80, 0xFFFFFF00u, (int)D_0061C1A8, soundReverbDepthGet());
    return (D_0028F8F0[0].hold & 0x60) != 0;
}

extern int D_0063B060;
extern int D_0063B05C;
extern char D_0061C1C0[];
extern char D_00559D50[];

int debug_AdpcmTest(int a0)
{
    int r;
    if (a0 != 0) {
        D_0063B060 = -1;
    }
    r = debug_SelectCsvWindow(D_0061C1C0, 10, 0x3C, 10, D_00559D50, 0x40, 0, 0, 0x69, &D_0063B05C);
    if (r > 0) {
        if (D_0063B05C != 0) {
            scpAdpcmPlayRequestFunc(D_0063B05C, 0, 1, 1, 1);
        }
    }
    return r;
}

typedef struct {
    char s[20];
} DbgTitle20;

typedef struct {
    long long a;
    long long b;
    unsigned short c;
    unsigned char d;
} DbgTitle19;

extern DbgTitle20 D_0061C1E0;
extern DbgTitle19 D_0061C1F8;
extern int D_0063B078;
extern int D_0063B07C;

int debugCdvdLoadInfoSegDisp(void)
{
    char title[0x20];
    int r;
    *(DbgTitle20 *)title = D_0061C1E0;
    if (D_0063B078 != 0) {
        DbgTitle19 *t = (DbgTitle19 *)title;
        t->a = D_0061C1F8.a;
        t->b = D_0061C1F8.b;
        t->c = D_0061C1F8.c;
        t->d = D_0061C1F8.d;
    }
    r = debug_SelectCsvWindowVal((int)title, 0x50, 0x46, 0xA, 0x1A, (int)&D_0063B07C,
                                 (int (*)(int, int))debugCdvdLoadInfoSegDispFunc, D_0063B078);
    if (D_0028F8F4[0] & 0x10) {
        int i;
        int *p = (int *)((char *)D_0070F880 + D_0063B078 * 0xD0);
        for (i = 0x19; i >= 0; i--) {
            p[1] = p[0];
            p += 2;
        }
    }
    return r;
}

int debug_GameOver(void)
{
    debug_Menu_off();
    return -1;
}

int debug_EndingDemo(void)
{
    debug_Menu_off();
    return -1;
}

int debug_BackStageTest(void)
{
    backStageProcessInStage(10000000.0f);
    return 1;
}

int debug_tsuresariTimeZero(void)
{
    backStageDebugTimeZero();
    return 1;
}

int debug_hintStart(void)
{
    void *gobj;
    for (gobj = isysGObjGetExist_begin(); gobj != 0; gobj = isysGObjGetExist_next(gobj)) {
        if (IsTopHint(gobj)) {
            DebugHintStart(gobj);
            break;
        }
    }
    return 1;
}

/* src/debug.c:5380-5397 in the listing: a static helper that builds the
   {name, gobj} list of the pad-controllable objects (kind 2 = boy, 4 = girl). */
static inline int debug_ListPadControlGobj(DbgGobjEnt *list)
{
    void *g;
    int n = 0;
    for (g = isysGObjGetExist_begin(); g != 0; g = isysGObjGetExist_next(g)) {
        int kind = ((PObjGObj *)g)->kind;
        if (kind == 2 || kind == 4) {
            list[n].obj = g;
            list[n].name = ((ObjKindEnt *)((char *)D_002C1270 + kind * 0x64))->name;
            n++;
        }
    }
    return n;
}

extern int D_0063B084;
extern void *D_00639ED0;
extern char D_0061C228[];

int debug_SelectPad2ControlGobj(int reset)
{
    DbgGobjEnt list[10];
    int n;
    int r;
    n = debug_ListPadControlGobj(list);
    if (reset != 0) {
        D_0063B084 = 0;
    }
    r = debug_SelectCsvWindow(D_0061C228, 0xA, 0x32, 0xB, list, 8, 0, 1, n, &D_0063B084);
    if (r > 0) {
        D_00639ED0 = list[D_0063B084].obj;
        return 1;
    }
    return (r == -1) ? -1 : 0;
}

int debug_FreeCamera(int a0)
{
    if (a0 != 0) {
        CameraSetMode(1);
    }
    CameraSetMode(1);
    return (D_0028F8F4[0] & 0x100) ? -1 : 0;
}
