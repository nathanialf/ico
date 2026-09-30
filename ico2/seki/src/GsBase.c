#include "debug.h"
#include "Basic.h"
#include "Packet.h"
#include "RegistPacket.h"
#include "Shadow.h"
#include "StageAnimation.h"
#include "Texture.h"
#include "staticBlur.h"
#include <libvu0.h>
#include <sifdev.h>
#include <stdio.h>
#include "typedef.h"
#include "gflag.h"
#include <eeregs.h>

/* Declared here, not through string.h: with newlib's prototype in scope gcc
   expands gsb_scissorOnDemo's four-byte zero fill as one store, and the ROM
   calls memset there.  The int count disagrees with the builtin's size_t,
   which is what keeps the builtin off in this file, as in layout_action.c
   and puddle.c. */
extern void *memset(void *p, int c, int n);

/* The TU's globals, MAIN.MAP's GsBase.o .sdata names, then the four words
   retail added after them (the XYOFFSET adjustment and the frame size
   gsb_SetVSMatrix records; MAIN.MAP's January object ends at
   currentScreenHeight, so their names are ours).  Tentative definitions: under
   -fno-common they land after the rest of the run, in this order.  The two
   offset names are read by gcse's name hash in their users: Shadow.c's
   frame layout moves under gsOffsetX/Y, offsetX/Y or dispOffsetX/Y, and
   screenOffsetX/Y keeps it, so the bytes pin that much of the names. */
int fbKeep;

int fbClear;

float center_X;

float center_Y;

int ScreenWidth;

int ScreenHeight;

int currentScreenWidth;

int currentScreenHeight;

int screenOffsetX; /* derived name */

int screenOffsetY; /* derived name */

int vsWidth; /* derived name */

int vsHeight; /* derived name */

/* The inline half of the TU's interface, declared in the order its deferred
   out-of-line copies are emitted (gcc writes them in first-declaration order;
   the definitions sit at their listing rows below). */
void gsb_SetBGColor(void *a0, int r, int g, int b);
void gsb_GetBGColor(unsigned char *a0);
void gsb_ResetFilmNoise(void);
void gsb_SetZoom(float a, float b);
int gsb_SyncGSSystem(void);
int gsb_LoadStageSettings(void);
int gsb_SaveStageSettings(void);
void gsb_ClearFrameBuffer(void);
int gsb_ResetSnap(void);
int gsb_TakeSnap(void);
int lockOtherEditing(void);
int unlockOtherEditing(void);
extern void sceGsSetDefDispEnv(int *env, int psm, short w, short h, short dx, short dy);

/* The head of the TU's .sdata run: the stage lock state, the word gsb_Init
   clears (read nowhere in the ROM), the
   GS system flag, the zoom easing (target, current, speed) and the last
   projection distance gsb_SetVSMatrix was given. */
static int otherEditingLocked = 0; /* derived name */

static int editingSettings = 0; /* derived name */

static int gsInitState = 0; /* derived name */

static int gsSystemReady = 0; /* derived name */

static float zoomTarget = 1.0f; /* derived name */

static float zoomCurrent = 1.0f; /* derived name */

static float zoomSpeed = 1000.0f; /* derived name */

int currentFocusDistance = 1;

/* Point the double buffer's two display and two draw environments at the
 * frame this stage draws into: the low nine bits of each frame word carry the
 * buffer base in 64-word units and the second qword of each draw env carries
 * the zbuffer base, its psm nibble and the mask bit. */
void gsb_SetFrame(int *db, int a1, int a2, int psm, short zbp)
{
    int *disp1 = db + 0x28 / 4;
    long long zb = ((long long)zbp << 32) | 0xC0;
    short h = (short)(unsigned short)ScreenHeight / 2;
    short w = ScreenWidth;

    *(int *)((char *)disp1 + 0x10) &= ~0x1FF;
    *(int *)((char *)db + 0x10) &= ~0x1FF;
    ((GifPkWord *)((char *)db + 0x150))->d =
        (((GifPkWord *)((char *)db + 0x150))->d & ~0x1FF) | 0x40;
    ((GifPkWord *)((char *)db + 0x60))->d = (((GifPkWord *)((char *)db + 0x60))->d & ~0x1FF) | 0x40;
    ((GifPkWord *)((char *)db + 0x160))->d = ((long long)(psm & 0xF) << 24) | zb;
    ((GifPkWord *)((char *)db + 0x70))->d = ((long long)(psm & 0xF) << 24) | zb;
    sceGsSetDefDispEnv(db, 0, w, h, 0, 0);
    sceGsSetDefDispEnv(disp1, 0, w, h, 0, 0);
}

extern int D_0028F4C0[];
extern int buffer_ID;
extern void sceGsSyncV(int a0);
extern void sceGsResetGraph(short mode, short inter, short omode, short ffmd);
extern void sceGsSetDefDBuff(void *db, short psm, short w, short h, short ztst, short zpsm,
                             short flag);
extern int sceGsSyncPath(int mode, int timeout);
extern void FlushCache(int mode);
extern void gsb_SetVSMatrix(int w, int h, float d);

/* Bring the GS up for the frame size the stage record asks for: 512 by 448
 * interlaced, 512 by 512 in the tall mode and 512 by 448 otherwise, then set
 * the double buffer up, hand the first frame over and put the view scale back
 * to one. */
void gsb_Init(void *db)
{
    int omode = 2;

    sceGsSyncV(0);
    fbClear = 1;
    gsInitState = 0;
    switch (D_0028F4C0[0]) {
    case 0:
        ScreenWidth = 0x200;
        ScreenHeight = 0x1C0;
        break;
    case 1:
        ScreenWidth = 0x200;
        ScreenHeight = 0x200;
        omode = 3;
        break;
    }
    sceGsResetGraph(0, D_0028F4C0[1] == 1, omode, 1);
    sceGsSetDefDBuff(db, 0, ScreenWidth, ScreenHeight, 2, 0x30, fbClear);
    gsb_SetFrame(db, 0, 0, 0x30, 2);
    sceGsSyncV(0);
    buffer_ID = 0;
    FlushCache(0);
    sceGsSwapDBuff(db, buffer_ID);
    while (sceGsSyncPath(1, 0) != 0) {
        debug_StdPrintfDummy("wait gs init\n");
    }
    gsb_SetVSMatrix(ScreenWidth, ScreenHeight, 512.0f);
    zoomTarget = 1.0f;
    zoomSpeed = 1000.0f;
    zoomCurrent = 1.0f;
}

/* A frame buffer clear packet for the whole screen, 48 doublewords: a GIF tag
   of 23 A+D writes and the register pairs.  Nothing in the ROM reads it (the
   bytes pin the table at this row, after gsb_Init's message, and its size,
   which is gsb_ClearFrameBuffer's frame; they do not pin its role), so the
   send that copied it is gone from the retail body. */
static const long long clearFramePacket[48] = {
    /* derived name */
    0x1000000000008017LL,
    0xE,
    0,
    0x4A,
    0x8000000048LL,
    0x42,
    0x700000007000LL,
    0x18,
    0x30000,
    0x47,
    0x130000000LL,
    0x4E,
    0x200000002000000LL,
    0x40,
    0,
    1,
    0x80000,
    0x4C,
    0x106,
    0,
    0xFFFFFFFF70007000LL,
    5,
    0xFFFFFFFF90009000LL,
    5,
    0x81000,
    0x4C,
    0x106,
    0,
    0xFFFFFFFF70007000LL,
    5,
    0xFFFFFFFF90009000LL,
    5,
    0x82000,
    0x4C,
    0x106,
    0,
    0xFFFFFFFF70007000LL,
    5,
    0xFFFFFFFF90009000LL,
    5,
    0x83000,
    0x4C,
    0x106,
    0,
    0xFFFFFFFF70007000LL,
    5,
    0xFFFFFFFF90009000LL,
    5,
};

inline void gsb_ClearFrameBuffer(void)
{
    volatile int local[96];
}

/* .sbss, owned by GsBase.o (MAIN.MAP line 7575; it names no symbol in the
   run, so the names are ours), in the ROM's run order: the reduction tint
   gsb_Reduction picks each frame and packs into the sprite colour. */
static int reductionRed;

static int reductionGreen;

static int reductionBlue;

extern int optionScreenMode;
extern StageSetting D_0028F720;
extern GsbPad D_0028F8F0[];

/* Reduce the frame into the feedback area: one 22 qword GIF packet, built on
 * the stack and sent down the GIF channel by hand, that first clears the
 * half height frame in black and then draws it back over itself through the
 * texture at 0x800 in the reduction tint, and last the tint this stage's
 * current target asks for. */
void gsb_Reduction(void)
{
    long long pk[44] = {
        0x1000000000008015LL,
        0xE,
        0,
        0x4A,
        0x8000000048LL,
        0x42,
        (long long)((ScreenWidth >> 6) & 0x3F) << 16,
        0x4C,
        ((long long)(0x800 - ScreenWidth / 2) << 4) | ((long long)(0x800 - ScreenHeight / 4) << 36),
        0x18,
        ((long long)(ScreenWidth - 1) << 16) | ((long long)(ScreenHeight / 2 - 1) << 48),
        0x40,
        0x30000,
        0x47,
        0x1300000C0LL,
        0x4E,
        0x106,
        0,
        0,
        1,
        (long long)(-ScreenWidth / 2 * 16 + 0x8000 - 4) |
            ((long long)(-ScreenHeight / 4 * 16 + 0x8000 - 4) << 16) | (-1LL << 32),
        5,
        (long long)(-ScreenWidth / 2 * 16 + 0x8000 + ScreenWidth * 16 - 4) |
            ((long long)(-ScreenHeight / 4 * 16 + 0x8000 + ScreenHeight / 2 * 16 - 4) << 16) |
            (-1LL << 32),
        5,
        ((long long)(ScreenWidth - 3) << 16) | 2 | ((long long)(D_0028F4C0[0] == 0 ? 2 : 8) << 32) |
            ((long long)(ScreenHeight / 2 - 1 - (D_0028F4C0[0] == 0 ? 2 : 8)) << 48),
        0x40,
        ((long long)(ScreenWidth / 64) << 14) | 0x664000800LL,
        6,
        0x60,
        0x14,
        0x116,
        0,
        (long long)reductionRed |
            ((long long)reductionBlue << 16 | (long long)reductionGreen << 8 | 0x80000000LL),
        1,
        0x80008,
        3,
        (long long)(-ScreenWidth / 2 * 16 + 0x8000 - 4) |
            ((long long)(-ScreenHeight / 4 * 16 + 0x8000 - 4) << 16) | (-1LL << 32),
        5,
        (long long)(ScreenWidth * 16 + 8) | ((long long)(ScreenHeight * 16 + 8) << 16),
        3,
        (long long)(-ScreenWidth / 2 * 16 + 0x8000 + ScreenWidth * 16 - 4) |
            ((long long)(-ScreenHeight / 4 * 16 + 0x8000 + ScreenHeight / 2 * 16 - 4) << 16) |
            (-1LL << 32),
        5,
        ((long long)ScreenWidth << 16) | ((long long)ScreenHeight << 48),
        0x40,
    };

    sceGsSyncPath(0, 0);
    FlushCache(0);
    *D2_QWC = 22;
    *D2_MADR = (int)pk & 0x0FFFFFFF;
    *D2_CHCR = 0x101;
    sceGsSyncPath(0, 0);
    if (D_0028F8F0[0].trg & 0x20) {
        debug_StdPrintfDummy("Film Noise:%d\n", optionScreenMode);
    }
    if (optionScreenMode) {
        reductionRed = fbKeep ? 128 : D_0028F720.targetCol[optionScreenMode - 1][0];
        reductionGreen = fbKeep ? 128 : D_0028F720.targetCol[optionScreenMode - 1][1];
        reductionBlue = fbKeep ? 128 : D_0028F720.targetCol[optionScreenMode - 1][2];
    } else {
        reductionRed = fbKeep ? 128 : D_0028F720.reductionCol[0];
        reductionGreen = fbKeep ? 128 : D_0028F720.reductionCol[1];
        reductionBlue = fbKeep ? 128 : D_0028F720.reductionCol[2];
    }
}

/* the colour the kept frame is drawn back in, {112, 112, 112, 128} in the
   TU's .sdata at VMA 0x639F98.  `const` is what the ROM proves: its four
   byte loads issue ahead of the sprite's first packet store, and a QImode
   load may pass a store only as an unchanging read (alias.c true_dependence) */
static const unsigned char keepFrameColor[4] = {112, 112, 112, 128}; /* derived name */

/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket(void);
/* kept local: this TU's uses of gif_SetGsReg do not fit the prototype in GifPacket.h */
extern void gif_SetGsReg(int a0, long long a1);
/* kept local: this TU's uses of gif_StartPacketPriPath1 do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPriPath1(int a0);
extern GifDpk PacketBufferStruct;

/* A rectangle in 16ths of a pixel, the form the sprite corners are written
   in.  RECONSTRUCTION: the record is 16 bytes and ROM's ldl/ldr pairs copy
   it whole out of its initialiser temporary. */
typedef struct {
    int x;
    int y;
    int w;
    int h;
} GsbRect;

/* The GS A+D writer, the payload word then the register word, a MACRO as in
 * Shadow.c and Texture.c: the listing puts every writer's stores on the line
 * of the use (GsBase.c:957 carries the whole sprite, 1025 two registers). */
#define setGsReg(reg, val)                                                                         \
    {                                                                                              \
        *PacketBufferStruct.ptr++ = (val);                                                         \
        *PacketBufferStruct.ptr++ = (reg);                                                         \
    }
/* RGBAQ packed from a four-byte colour, as Shadow.c packs it */
#define GIF_RGBA(c)                                                                                \
    ((long long)(c)[0] | ((long long)(c)[1] << 8) | ((long long)(c)[2] << 16) |                    \
     ((long long)(c)[3] << 24))
/* The textured sprite at depth 0: PRIM, RGBAQ, then a UV and an XYZ2 pair for
 * each corner of the rect r (x, y, w, h in sixteenths) and its texture rect
 * uv, the far corner as x + fx with fx = w + 0x8000.  Shadow.c's spriteUV
 * with the depth left out; a MACRO for the same reason. */
#define spriteUV(r, uv, col, prim)                                                                 \
    {                                                                                              \
        setGsReg(0x00, prim);                                                                      \
        setGsReg(0x01, GIF_RGBA(col));                                                             \
        setGsReg(0x03, (long long)(uv)[0] | ((long long)(uv)[1] << 16));                           \
        setGsReg(0x05, (long long)((r)[0] + 0x8000) | ((long long)((r)[1] + 0x8000) << 16));       \
        setGsReg(0x03, (long long)((uv)[0] + (uv)[2]) | ((long long)((uv)[1] + (uv)[3]) << 16));   \
        {                                                                                          \
            int fx = (r)[2] + 0x8000;                                                              \
            int fy = (r)[3] + 0x8000;                                                              \
                                                                                                   \
            setGsReg(0x05, (long long)((r)[0] + fx) | ((long long)((r)[1] + fy) << 16));           \
        }                                                                                          \
    }
/* The untextured sprite at depth z: PRIM, RGBAQ and the two XYZ2 corners of
 * the rect x, y, w, h, the far corner as x + fx with fx = w + 0x8000.
 * Shadow.c's spriteRect with gif_MakeSpriteNoTexture's parameters; a MACRO
 * for the same reason. */
#define spriteRect(x, y, w, h, z, col, prim)                                                       \
    {                                                                                              \
        setGsReg(0x00, prim);                                                                      \
        setGsReg(0x01, GIF_RGBA(col));                                                             \
        setGsReg(0x05,                                                                             \
                 (long long)((x) + 0x8000) | ((long long)((y) + 0x8000) << 16) | ((z) << 32));     \
        {                                                                                          \
            int fx = (w) + 0x8000;                                                                 \
            int fy = (h) + 0x8000;                                                                 \
                                                                                                   \
            setGsReg(0x05, (long long)((x) + fx) | ((long long)((y) + fy) << 16) | ((z) << 32));   \
        }                                                                                          \
    }

/* GsBase.c:942-958 in the listing: the two rect initialisers (942, 946), the
 * packet open and the five register writes (948-953), the whole textured
 * sprite on one line (957) and the close (958).  Draw the whole screen back
 * over itself as one sprite in the kept colour. */
void gsb_KeepFrameBuffer(void)
{
    GsbRect r0 = {-(ScreenWidth >> 1) * 16 - 12, -(ScreenHeight >> 1) * 16 - 12,
                  ScreenWidth * 16 + 32, ScreenHeight * 16 + 32};
    GsbRect r1 = {8, 8, ScreenWidth * 16, ScreenHeight / 2 * 16};

    gif_StartPacketPriPath1(11);
    gif_SetGsReg(0x47, 0x30000);
    gif_SetGsReg(0x4E, 0x1300000C0LL);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x8000000080LL);
    gif_SetGsReg(6, ((long long)(ScreenWidth / 64) << 14) | (0xC482LL << 19));
    spriteUV(&r0.x, &r1.x, keepFrameColor, 0x116);
    gif_EndPacket();
}

/* The rest of GsBase.o's .sbss run, after the reduction tint: the fade level
   gsb_fade steps from 0 to 128 and gsb_PostEffect prints, then one word no
   instruction in the ROM reads or writes (checked over every gp-relative and
   absolute access in .text), so that name is positional and ours.  MAIN.MAP
   line 7575 sizes the January object at 0x10, four words; the retail object
   has the fifth. */
static float fadeLevel;

static int gsbUnusedWord;

/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int pri);
/* kept local: this TU's uses of gif_SetDrawEnviroment do not fit the prototype in GifPacket.h */
extern void gif_SetDrawEnviroment(int a0, int a1, int w, int h, int a4, int a5);

/* The fade overlay: step the fade level by half the speed each frame, clamp
 * it to 0 to 128, stop or hand over to the continue state at the ends, and
 * draw the whole screen as one sprite in the fade colour.  The two end tests
 * are `&&` chains, not nested ifs: the ROM's short circuit path out of the
 * first condition falls into the SECOND condition's test, which is why the
 * else arm is entered twice and materialises 0.0 again at 0x001130B0, and a
 * nested if would jump past it instead (223 instructions against ROM's 224). */
void gsb_fade(void)
{
    GsbRect r = {-(ScreenWidth >> 1) * 16, -(ScreenHeight >> 1) * 16, ScreenWidth * 16,
                 ScreenHeight * 16};

    switch (fadeStatus) {
    case 1:
        if (0.0f < fadeSpeed) {
            fadeLevel = 0.0f;
            fadeStatus = 2;
        } else if (fadeSpeed < 0.0f) {
            fadeStatus = 2;
            fadeLevel = 144.0f;
        }
        /* FALLTHROUGH */
    case 2:
        fadeLevel = fadeLevel + fadeSpeed * 0.5f;
        break;
    case 3:
        break;
    default:
        goto clear;
    }
    if (0.0f < fadeSpeed && 128.0f <= fadeLevel) {
        if (fadeContinue != 0) {
            fadeStatus = 3;
        } else {
            fadeStatus = 0;
        }
    } else if (fadeSpeed < 0.0f && fadeLevel < 0.0f) {
        if (fadeContinue != 0) {
            fadeStatus = 3;
        } else {
            fadeStatus = 0;
        }
    }
    if (128.0f <= fadeLevel) {
        fadeColor[3] = 128;
    } else if (fadeLevel < 0.0f) {
        fadeColor[3] = 0;
    } else {
        fadeColor[3] = fadeLevel;
    }
    gif_StartPacketPri(0xB);
    gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 1, 0);
    gif_SetGsReg(0x47, 0x30000);
    gif_SetGsReg(0x4E, 0x1300000C0LL);
    setGsReg(0x49, 0);
    setGsReg(0x42, 0x44);
    spriteRect(r.x, r.y, r.w, r.h, -1LL, fadeColor, 0x446);
    gif_EndPacket();
    if (debug_font_flag & 1) {
        debug_Printf(0x208, ScreenHeight / 2 - 8, 0xCCCCCC00, "F");
    }
    return;
clear:
    fadeColor[3] = 0;
    fadeStatus = 0;
}

extern int optionScreenMode;
extern StageSetting D_0028F720;

void gsb_SetMotionBlur(void)
{
    int i = optionScreenMode;

    if (i == 0) {
        SetMotionBlur(D_0028F720.motionBlur);
    } else {
        SetMotionBlur(D_0028F720.subMotionBlur[i - 1]);
    }
}

extern int D_0063B60C;

/* gsb_scissorOnDemo's state: the demo state it last saw, the band level and
   its step */
static int scissorLastState = 54; /* derived name */

static float scissorLevel = 0.0f; /* derived name */

static float scissorStep = 0.0f; /* derived name */

extern void SetMotionBlur(int on);
extern void gif_EndPacketPath1(void);
/* kept local: this TU's uses of dl_GetPri do not fit the prototype in DisplayList.h */
extern int dl_GetPri(void);
/* kept local: this TU's uses of dl_SetDLPriority do not fit the prototype in DisplayList.h */
extern void dl_SetDLPriority();

/* The letterbox the demo scenes fade in: two black bars, top and bottom,
 * whose alpha eases to 128 while the scene is state 55 and back to 0
 * otherwise.  While the bars are visible they are drawn and the motion blur
 * is left alone; once they are gone the stage record's blur setting is
 * restored.  The listing (GsBase.c:1067-1126) puts the two-bar initialiser on
 * 1067, the two state tests on 1092, the ease and the two clamps on 1097 to
 * 1106, the `&&` window on 1109, and the whole sprite on 1121 inside the
 * two-iteration loop of 1120: a macro, with its first corner written before
 * fx and fy are formed, which is the order the loop's invariants come out
 * in. */
void gsb_scissorOnDemo(void)
{
    GsbRect r[2] = {
        {-(ScreenWidth >> 1) * 16, -(ScreenHeight >> 1) * 16 - 4, ScreenWidth * 16, 58 * 16},
        {-(ScreenWidth >> 1) * 16, ((ScreenHeight >> 1) - 58) * 16 + 4, ScreenWidth * 16, 58 * 16}};
    unsigned char col[4];
    int i;

    if (D_0063B60C == 55 && scissorLastState != D_0063B60C) {
        scissorStep = 2.5f;
    } else if (scissorLastState != D_0063B60C) {
        scissorStep = -2.5f;
    }
    scissorLastState = D_0063B60C;

    scissorLevel = scissorLevel + scissorStep;
    if (scissorLevel <= 0.0f) {
        scissorLevel = 0.0f;
        scissorStep = 0.0f;
    }
    if (128.0f <= scissorLevel) {
        scissorLevel = 128.0f;
        scissorStep = 0.0f;
    }
    if (0.0f < scissorLevel && scissorLevel <= 128.0f) {
        if (debug_font_flag & 1) {
            debug_Printf(0x21C, ScreenHeight / 2 - 8, 0xCCCCCC00, "D");
        }
        dl_SetDLPriority(11);
        gif_StartPacketPriPath1(dl_GetPri());
        memset(col, 0, 4);
        col[3] = 0x80;
        gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 1, 0);
        gif_SetGsReg(0x47, 0x30000);
        gif_SetGsReg(0x4E, 0x300000C0);
        gif_SetGsReg(0x49, 0);
        gif_SetGsReg(0x42, ((long long)(int)scissorLevel << 32) | 0x64);
        for (i = 0; i < 2; i++) {
            spriteRect(r[i].x, r[i].y, r[i].w, r[i].h, -1LL, col, 0x446);
        }
        gif_EndPacketPath1();
    } else {
        SetMotionBlur(D_0028F720.motionBlur);
    }
}

extern int D_0028F4C0[];
/* kept local: this TU's uses of gif_SetGsReg do not fit the prototype in GifPacket.h */
extern void gif_SetGsReg(int a0, long long a1);
/* kept local: this TU's uses of gif_EndPacketPath1 do not fit the prototype in GifPacket.h */
extern void gif_EndPacketPath1(void);
/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int pri);
/* kept local: this TU's uses of gif_SetAlpha do not fit the prototype in GifPacket.h */
extern void gif_SetAlpha(int a0, int a1, int a2);
/* kept local: this TU's uses of gif_MakeSpriteNoTexture do not fit the prototype in GifPacket.h */
extern void gif_MakeSpriteNoTexture(int x, int y, int w, int h, unsigned int z, unsigned char *col,
                                    int prim);

/* Darken the whole frame by the stage record's brightness step: a full screen
 * white sprite in destination-alpha blend whose alpha is the step, clamped to
 * 0 to 15 and skipped at 0. */
void gsb_controlBrightness(void)
{
    int v = D_0028F4C0[0x2C / 4];

    if (v < 0) {
        v = D_0028F4C0[0x2C / 4] = 0;
    }
    if (v >= 0x10) {
        v = D_0028F4C0[0x2C / 4] = 0xF;
    }
    if (v != 0) {
        if (debug_font_flag & 1) {
            debug_Printf(0x212, ScreenHeight / 2 - 8, 0xCCCCCC00, "B");
        }
        gif_StartPacketPri(0xB);
        {
            unsigned char col[4] = {0xFF, 0xFF, 0xFF, D_0028F4C0[0x2C / 4]};

            gif_SetGsReg(0x47, 0x30000);
            gif_SetGsReg(0x4E, 0x1300000C0LL);
            gif_SetAlpha(1, 7, 0);
            gif_MakeSpriteNoTexture((0x800 - ScreenWidth / 2) << 4, (0x800 - ScreenHeight / 2) << 4,
                                    ScreenWidth << 4, ScreenHeight << 4, 0xFFFFFFFE, col, 1);
            gif_EndPacketPath1();
        }
    }
}

/* A colour as the sprite family takes it, four bytes in RGBA order; the same
   record as Texture.c's TexColor. */
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} GsbColor;

extern void gif_SetZTest(int on);
extern void gif_SetZWrite(int on);
extern int tex_GetTWTH(int size);
extern void gif_SpriteSensitiveOrg(int *r, long long z, int *uv, unsigned char *col, int prim);

/* Soften the frame's edges: the frame is reduced to a 256 square copy and,
 * when the second level is on, a 128 square one, and each level the stage
 * record (or the current sub target's row) turns on is blended back over the
 * 512 square buffer through the sensitive sprite.  The listing
 * (GsBase.c:1181-1247) puts the colour and each rectangle on its own line,
 * the two level reads on two lines per arm, and every TEX0 write on one line
 * in field order, as Texture.c spells it: fold pairs that chain into
 * (TW | TCC) | (TH | TBP and TBW), which leaves the TCC bit a constant of its
 * own that the four writes share in $s1. */
void gsb_antiAlias(void)
{
    GsbColor col = {128, 128, 128, 128};
    GsbRect s0 = {4, 4, 8192, 8192};
    GsbRect s1 = {4, 4, 4096, 4096};
    GsbRect s2 = {4, 4, 2048, 2048};
    GsbRect d0 = {-4100, -4100, 8192, 8192};
    GsbRect d1 = {-2052, -2052, 4096, 4096};
    GsbRect d2 = {-1028, -1028, 2048, 2048};
    int lv[2];

    if (optionScreenMode == 0) {
        lv[0] = D_0028F720.f0FC;
        lv[1] = D_0028F720.f100;
    } else {
        lv[0] = D_0028F720.f19C[optionScreenMode].a;
        lv[1] = D_0028F720.f19C[optionScreenMode].b;
    }
    if (lv[0] == 0 && lv[1] == 0) {
        return;
    }
    gif_StartPacketPri(10);
    gif_SetZTest(0);
    gif_SetZWrite(0);
    gif_SetDrawEnviroment(0x2800, 0, 256, 256, 0, 0);
    gif_SetGsReg(6, 0x800 | ((long long)8 << 14) | ((long long)tex_GetTWTH(512) << 26) |
                        ((long long)tex_GetTWTH(512) << 30) | ((long long)1 << 34));
    gif_SetAlpha(0, 2, 128);
    gif_SpriteSensitiveOrg(&d1.x, 0, &s0.x, (unsigned char *)&col, 0);
    if (lv[1] != 0) {
        gif_SetGsReg(6, 0x2800 | ((long long)4 << 14) | ((long long)tex_GetTWTH(256) << 26) |
                            ((long long)tex_GetTWTH(256) << 30) | ((long long)1 << 34));
        gif_SetDrawEnviroment(0x2C00, 0, 128, 128, 0, 0);
        gif_SpriteSensitiveOrg(&d2.x, 0, &s1.x, (unsigned char *)&col, 0);
    }
    gif_SetDrawEnviroment(0x800, 0, 512, 512, 1, 0);
    if (lv[1] != 0) {
        gif_SetAlpha(1, 2, lv[1]);
        gif_SetGsReg(6, 0x2C00 | ((long long)2 << 14) | ((long long)tex_GetTWTH(128) << 26) |
                            ((long long)tex_GetTWTH(128) << 30) | ((long long)1 << 34));
        gif_SpriteSensitiveOrg(&d0.x, 0, &s2.x, (unsigned char *)&col, 1);
    }
    if (lv[0] != 0) {
        gif_SetAlpha(1, 2, lv[0]);
        gif_SetGsReg(6, 0x2800 | ((long long)4 << 14) | ((long long)tex_GetTWTH(256) << 26) |
                            ((long long)tex_GetTWTH(256) << 30) | ((long long)1 << 34));
        gif_SpriteSensitiveOrg(&d0.x, 0, &s1.x, (unsigned char *)&col, 1);
    }
    gif_SetZWrite(1);
    gif_SetZTest(1);
    gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 1, 0);
    gif_EndPacket();
}

/* kept local: this TU's uses of gif_EndPacketPath1 do not fit the prototype in GifPacket.h */
extern void gif_EndPacketPath1(void);
/* kept local: this TU's uses of gif_SetGsReg do not fit the prototype in GifPacket.h */
extern void gif_SetGsReg(int a0, long long a1);
/* kept local: this TU's uses of gif_StartPacketPriPath1 do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPriPath1(int a0);

void gsb_setNormalReg(int ctx)
{
    dl_SetDLPriority();
    gif_StartPacketPriPath1(dl_GetPri());
    gif_SetGsReg(0x47, 0x50000);
    gif_SetGsReg(0x4E, 0x300000C0);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x8000000080LL);
    gif_EndPacketPath1();
}

void gsb_setSemitransReg(int ctx)
{
    dl_SetDLPriority();
    gif_StartPacketPriPath1(dl_GetPri());
    gif_SetGsReg(0x47, 0x5140D);
    gif_SetGsReg(0x4E, 0x300000C0);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x810000807FLL);
    gif_EndPacketPath1();
}

void gsb_setSpecularReg(int ctx)
{
    dl_SetDLPriority();
    gif_StartPacketPriPath1(dl_GetPri());
    gif_SetGsReg(0x47, 0x5C000);
    gif_SetGsReg(0x4E, 0x1300000C0LL);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x8000000080LL);
    gif_EndPacketPath1();
}

void gsb_setParticleReg(int ctx)
{
    dl_SetDLPriority();
    gif_StartPacketPriPath1(dl_GetPri());
    gif_SetGsReg(0x47, 0x50000);
    gif_SetGsReg(0x4E, 0x1300000C0LL);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x8000000080LL);
    gif_EndPacketPath1();
}

extern int game_pause;
extern char *matrixptr;
extern void _MulMatrix(void *d, void *a, void *b);
extern void _InversMatrix(void *d, void *s);
extern void _CopyMatrix(void *d, void *s);
/* kept local: this TU's uses of dl_OpenDma do not fit the prototype in DisplayList.h */
extern void dl_OpenDma(int a0, char *a1, int a2);
/* kept local: this TU's uses of dl_CloseDma do not fit the prototype in DisplayList.h */
extern void dl_CloseDma(void);

/* the head of the common matrix packet: the three constant rows of the VU
   parameter block (the unit w, the clip extents and a zero row) and the GIF
   tag of the strip the microcode sends */
static const struct {
    sceVu0FVECTOR row[3];
    sceVu0IVECTOR tag;
} commonMatrixHead = {
    /* derived name */
    {{0.0f, 0.0f, 0.0f, 1.0f}, {4095.0f, 4095.0f, 0.0f, 16777215.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {0x8000, 0x302EC000, 0x512, 0},
};

/* Build the frame's common matrix packet: the three view matrices the stage
 * needs, the inverse of the view, and the display list that uploads them to
 * VU memory, opened once for each of the thirteen list priorities. */
void gsb_MakeCommonMatrix(void)
{
    GifPkWord *p;
    GifPkWord *q;
    int i;

    if (game_pause == 0) {
        return;
    }
    i = 0;
    _MulMatrix(matrixptr + 0x100, matrixptr + 0xC0, matrixptr + 0x80);
    _MulMatrix(matrixptr + 0x200, matrixptr + 0x1C0, matrixptr + 0x80);
    _MulMatrix(matrixptr + 0x280, matrixptr + 0x240, matrixptr + 0x80);
    _InversMatrix(matrixptr + 0x380, matrixptr + 0x80);
    p = (GifPkWord *)PacketBufferStruct.ptr;
    PacketBufferStruct.gif = 0;
    PacketBufferStruct.dma = (char *)p;
    PacketBufferStruct.end = 0;
    PacketBufferStruct.tail = (char *)p;
    p[0].d = 0x10000011;
    PacketBufferStruct.ptr = (unsigned long long *)((char *)p + 8);
    p[1].w[0] = 0x13000000;
    PacketBufferStruct.ptr = (unsigned long long *)((char *)p + 0xC);
    PacketBufferStruct.gif = (char *)p + 0xC;
    p[1].w[1] = 0x6C100000;
    PacketBufferStruct.ptr = (unsigned long long *)((char *)p + 0x10);
    _CopyMatrix((char *)p + 0x10, &commonMatrixHead);
    PacketBufferStruct.ptr = (unsigned long long *)((char *)PacketBufferStruct.ptr + 0x40);
    _CopyMatrix(PacketBufferStruct.ptr, matrixptr + 0x100);
    PacketBufferStruct.ptr = (unsigned long long *)((char *)PacketBufferStruct.ptr + 0x40);
    _CopyMatrix(PacketBufferStruct.ptr, matrixptr + 0x340);
    PacketBufferStruct.ptr = (unsigned long long *)((char *)PacketBufferStruct.ptr + 0x40);
    _CopyMatrix(PacketBufferStruct.ptr, matrixptr + 0x380);
    q = (GifPkWord *)PacketBufferStruct.ptr;
    PacketBufferStruct.ptr = (unsigned long long *)((char *)q + 0x40);
    q[8].w[0] = 0x13000000;
    PacketBufferStruct.ptr = (unsigned long long *)((char *)q + 0x44);
    q[8].w[1] = 0;
    PacketBufferStruct.ptr = (unsigned long long *)((char *)q + 0x48);
    q[9].w[0] = 0;
    PacketBufferStruct.ptr = (unsigned long long *)((char *)q + 0x4C);
    q[9].w[1] = 0;
    PacketBufferStruct.ptr = (unsigned long long *)((char *)q + 0x50);
    PacketBufferStruct.tail = (char *)q + 0x50;
    q[10].d = 0x60000000;
    PacketBufferStruct.ptr = (unsigned long long *)((char *)q + 0x58);
    q[11].w[0] = 0;
    PacketBufferStruct.ptr = (unsigned long long *)((char *)q + 0x5C);
    q[11].w[1] = 0;
    PacketBufferStruct.ptr = (unsigned long long *)((char *)q + 0x60);
    do {
        dl_SetDLPriority(i);
        i++;
        dl_OpenDma(5, PacketBufferStruct.dma, 0);
        dl_CloseDma();
    } while (i < 0xD);
}

/* Open the frame's first display list: one DMA tag, the two VIF words that
 * hand path 1 to the GS, a second tag for the register run, and then the
 * default register set for each of the thirteen contexts. */
void gsb_SetGsDefault(void)
{
    GifDpk *d = &PacketBufferStruct;
    GifPkWord *p = (GifPkWord *)d->ptr;

    d->gif = 0;
    d->tail = (char *)p;
    d->dma = (char *)p;
    d->end = 0;
    p[0].d = 0x10000000;
    d->ptr = (unsigned long long *)((char *)p + 8);
    p[1].w[0] = 0x3000100;
    d->ptr = (unsigned long long *)((char *)p + 0xC);
    p[1].w[1] = 0x2000180;
    d->ptr = (unsigned long long *)((char *)p + 0x10);
    d->tail = (char *)p + 0x10;
    p[2].d = 0x60000000;
    d->ptr = (unsigned long long *)((char *)p + 0x18);
    p[3].w[0] = 0;
    d->ptr = (unsigned long long *)((char *)p + 0x1C);
    p[3].w[1] = 0;
    d->ptr = (unsigned long long *)((char *)p + 0x20);
    dl_SetDLPriority(0);
    dl_OpenDma(5, d->dma, 0);
    dl_CloseDma();
    gsb_MakeCommonMatrix();
    gsb_setNormalReg(0);
    gsb_setSemitransReg(1);
    gsb_setSemitransReg(2);
    gsb_setParticleReg(6);
    gsb_setSpecularReg(4);
    gsb_setNormalReg(7);
    gsb_setNormalReg(8);
    gsb_setNormalReg(9);
    gsb_setNormalReg(0xA);
    gsb_setNormalReg(0xB);
    gsb_setNormalReg(0xC);
}

/* Lay the film grain texture over the frame: the noise texture at texture
 * slot 10, drawn as one full screen sprite whose colour comes from the
 * stage record's grain tint for this target and whose UV step is the
 * record's grain scale, passed as raw bits in both halves of the register. */
void gsb_filmNoise(void)
{
    int n = tex_GetTextureNo("sandstorm_spr");
    float scale;

    if (n < 0) {
        return;
    }
    scale = D_0028F720.grainScale;
    tex_TransTexture(n, 0xA);
    gif_StartPacketPriPath1(dl_GetPri());
    gif_SetGsReg(8, 0);
    gif_SetGsReg(0x4E, 0x1300000C0LL);
    gif_SetGsReg(0x47, 0x30000);
    gif_SetGsReg(0x49, 0);
    gif_SetGsReg(0x42, 0x44);
    gif_SetGsReg(0, 0x56);
    gif_SetGsReg(1, ((long long)D_0028F720.targetCol[optionScreenMode - 1][3] << 24) |
                        0x3F80000000808080LL);
    gif_SetGsReg(2, 0);
    gif_SetGsReg(5, 0xFFFFFFFF70007000LL);
    gif_SetGsReg(2, ((long long)*(unsigned int *)&scale << 32) | *(unsigned int *)&scale);
    gif_SetGsReg(5, 0xFFFFFFFF90009000LL);
    gif_EndPacketPath1();
}

/* the stage animation group each film noise target loops, -1 for none */
static const int filmNoiseGroup[] = {-1, 67, 68, 69, 70}; /* derived name */

inline void gsb_ResetFilmNoise(void)
{
    int i;
    for (i = 0; i < 5; i++) {
        if (filmNoiseGroup[i] != -1) {
            if (i == optionScreenMode) {
                stage_SetLoopFlag(filmNoiseGroup[i], 1);
                debug_StdPrintfDummy("set film noise %d\n", optionScreenMode);
            } else {
                stage_SetLoopFlag(filmNoiseGroup[i], 0);
                debug_StdPrintfDummy("clear film noise %d\n", optionScreenMode);
            }
        }
    }
}

extern int D_0063B60C;
extern int staffRollStartFlag;
extern void FullScreenEffectAfter(void);
extern void shadow_Draw(void);
extern void fog_DrawFog(void);
extern void MotionBlur(void);
extern void gsb_antiAlias(void);
extern void gsb_KeepFrameBuffer(void);
extern void staffRollMain(void);
extern void gsb_fade(void);
extern void gsb_scissorOnDemo(void);

/* set by gsb_UpdateGSSystem once the frame is up, tested by gsb_PostEffect */
static int postEffectReady = 0; /* derived name */

/* Everything the frame still owes after the scene is drawn: the debug read
 * outs, the full screen effect, the shadow and fog passes, the motion blur,
 * the anti alias pass, the film grain and the brightness step, the kept frame
 * buffer, the staff roll and last the fade and the demo scissor. */
int gsb_PostEffect(void)
{
    if (debug_font_flag & 1) {
        debug_Printf(0xA, ScreenHeight / 2 - 8, 0xCCCCCC00, "LID:%3d / FADE%d:%3.0f(%d)",
                     D_0063B60C, fadeStatus, fadeLevel, fadeColor[3]);
    }
    if (D_0028F4C0[0x18 / 4] != 0 && (debug_font_flag & 1)) {
        debug_Printf(0x230, ScreenHeight / 2 - 8, 0xCCCCCC00, "L");
    }
    if (D_0028F4C0[0x14 / 4] != 0 && (debug_font_flag & 1)) {
        debug_Printf(0x23A, ScreenHeight / 2 - 8, 0xCCCCCC00, "P");
    }
    FullScreenEffectAfter();
    if (postEffectReady != 0) {
        shadow_Draw();
    }
    fog_DrawFog();
    MotionBlur();
    gsb_antiAlias();
    if (gFlagGameClear > 0 && optionScreenMode != 0) {
        gsb_filmNoise();
    }
    gsb_controlBrightness();
    if (fbKeep != 0) {
        gsb_KeepFrameBuffer();
        if (debug_font_flag & 1) {
            debug_Printf(0x226, ScreenHeight / 2 - 8, 0xCCCCCC00, "K");
        }
    }
    if (staffRollStartFlag != 0) {
        staffRollMain();
    }
    gsb_fade();
    gsb_scissorOnDemo();
    return fbKeep;
}

/* gsb_InitGSSystem's first call brings every module up */
static int firstGsInit = 1; /* derived name */

extern int screen_offset_y;
extern int screen_offset_x;
extern char D_0028F4F0[];
extern void sceGsResetPath(void);
extern void sceGsSyncV(int a0);
/* kept local: the declaration in GsBase.h changes this TU codegen */
extern void gsb_Init(void *p);
/* kept local: this TU's uses of dl_Init do not fit the prototype in DisplayList.h */
extern void dl_Init(void);

void gsb_InitGSSystem(void)
{
    screen_offset_y = 0;
    screen_offset_x = 0;
    if (firstGsInit != 0) {
        sceGsResetPath();
        sceVpu0Reset();
        debug_StdPrintfDummy("dma init\n");
        dma_init();
        debug_StdPrintfDummy("matrix init\n");
        matrix_init();
        debug_StdPrintfDummy("texture init\n");
        tex_Init();
        debug_StdPrintfDummy("gs init\n");
        sceGsSyncV(0);
        gsb_Init(D_0028F4F0);
        sceGsSyncV(0);
        dl_Init();
        firstGsInit = 0;
    } else {
        debug_StdPrintfDummy("dma init\n");
        dma_init();
        debug_StdPrintfDummy("texture init\n");
        tex_Init();
    }
    resetmallocseki();
    pac_Init();
    reg_Init();
    shadow_Init();
    gsSystemReady = 1;
    screenOffsetX = screenOffsetY = 0;
}

/* Six zero words of .sdata between gsb_InitGSSystem's flag and
   gsb_SyncGSSystem's counter: nothing in the ROM reads or writes them.  The
   bytes pin their place, the value and that each is at most eight bytes; they
   do not pin their types, their split or their role. */
static int gsbUnused0 = 0; /* derived name */

static int gsbUnused1 = 0; /* derived name */

static int gsbUnused2 = 0; /* derived name */

static int gsbUnused3 = 0; /* derived name */

static int gsbUnused4 = 0; /* derived name */

static int gsbUnused5 = 0; /* derived name */

inline int gsb_ResetSnap(void) {}

inline int gsb_TakeSnap(void) {}

extern int sceGsSyncPath(int mode, int timeout);
/* kept local: the declaration in GsBase.h changes this TU codegen */
extern void gsb_ResetGSSystem(void);

/* the frames gsb_SyncGSSystem has waited on the GS */
static int syncRetry = 0; /* derived name */

inline int gsb_SyncGSSystem(void)
{
    if (sceGsSyncPath(1, 0)) {
        syncRetry++;
        if (syncRetry >= 11) {
            debug_StdPrintfDummy("reset gs\n");
            gsb_ResetGSSystem();
            syncRetry = 0;
        }
        return 1;
    }
    syncRetry = 0;
    gsb_PostEffect();
    return 0;
}

extern int frame_count;
extern int buffer_ID;
extern int odd_even;
extern int GlobalTimer;
extern void sceGsSetHalfOffset(void *env, short x, short y, int field);
extern void gsb_Reduction(void);
extern void debug_FlushFont(void);
extern void FlushCache(int mode);
extern void shadow_Reset(void);
extern void FullScreenEffectBefore(void);
extern void light_ResetLight(void);
extern void tex_ResetVram(void);

/* One frame boundary: take the field parity from the GS CSR, run the
 * reduction pass, flip the double buffer and hand the display list back
 * either swapped or cleared, then reopen the frame's register set. */
void gsb_UpdateGSSystem(int keep)
{
    char *draw;

    odd_even = (*GS_CSR >> 13) & 1;
    gsb_Reduction();
    if (gsSystemReady == 0) {
        dl_Clear();
        return;
    }
    debug_FlushFont();
    frame_count++;
    buffer_ID = frame_count & 1;
    FlushCache(0);
    sceGsSwapDBuff(D_0028F4F0, buffer_ID);
    if (buffer_ID != 0) {
        draw = D_0028F4F0 + 0x150;
    } else {
        draw = D_0028F4F0 + 0x60;
    }
    sceGsSetHalfOffset(draw, (short)((float)screen_offset_x + 2048.0f),
                       (short)((float)screen_offset_y + 2048.0f), odd_even == 0);
    tex_ResetVram();
    if (keep == 0) {
        dl_Swap();
    } else {
        dl_Clear();
    }
    gsb_SetGsDefault();
    postEffectReady = 0;
    shadow_Reset();
    postEffectReady = 1;
    FullScreenEffectBefore();
    currentScreenWidth = GlobalTimer;
    light_ResetLight();
}

extern int D_0028F4C0[];
/* kept local: this TU passes every argument of sceGsResetGraph as a short */
extern void sceGsResetGraph(short mode, short inter, short omode, short ffmd);
extern void sceGsSetHalfOffset(void *env, short x, short y, int field);

/* Reset the GS between stages: reopen the paths, reset the VU0 and the DMA,
 * put the graphics mode back, take the field parity out of the GS CSR and
 * flip the double buffer, then re-open the frame's display list. */
void gsb_ResetGSSystem(void)
{
    char *draw;

    sceGsResetPath();
    sceVpu0Reset();
    dma_init();
    sceGsResetGraph(0, D_0028F4C0[1] == 1, (unsigned short)D_0028F4C0[0] + 2, 1);
    frame_count++;
    buffer_ID = frame_count & 1;
    odd_even = (*GS_CSR >> 13) & 1;
    FlushCache(0);
    sceGsSwapDBuff(D_0028F4F0, buffer_ID);
    if (buffer_ID != 0) {
        draw = D_0028F4F0 + 0x150;
    } else {
        draw = D_0028F4F0 + 0x60;
    }
    sceGsSetHalfOffset(draw, (short)((float)screen_offset_x + 2048.0f),
                       (short)((float)screen_offset_y + 2048.0f), odd_even == 0);
    tex_ResetVram();
    dl_Swap();
    gsb_SetGsDefault();
}

extern void _UnitMatrix(float *m);

/* the 1500 unit screen the projection b is scaled to */
static const float vsScreenSize[] = {1500.0f, 1500.0f, 0.0f, 0.0f}; /* derived name */

/* Build the view matrices from the record gsb_SetVSMatrix fills (vs[0] the
 * zoom, vs[1] and vs[2] the aspect terms, vs[3] and vs[4] the centre, vs[5]
 * and vs[6] the depth range, vs[7] and vs[8] the near and far planes): the
 * screen matrix a, the perspective projection b for the 1500 unit screen,
 * the one c for the half size screen, the viewport d, and the pair built on
 * a 500 unit screen at matrixptr+0x640 and +0x680.  The listing
 * (GsBase.c:2009-2134) gives each assignment its own line in this order,
 * except the two rows of three that fill the scale, depth and centre terms;
 * the 500 unit pair's scale terms at 2125-2126 are locals of their own, which
 * is what keeps sx and sy short enough to take $f21 and $f22. */
void gsb_SetVSMatrixSub(float *a, float *b, float *c, float *d, float *vs)
{
    sceVu0FVECTOR v = {ScreenWidth / 2, ScreenHeight / 2, 0.0f, 0.0f};
    float m0[16];
    float m1[16];
    float sx;
    float sy;
    float cx;
    float cy;
    float zn;
    float zf;
    float rx;
    float ry;

    sx = vs[7] * vsScreenSize[0] / vs[0];
    sy = vs[7] * vsScreenSize[1] / vs[0];

    cx = vs[7] * v[0] / vs[0];
    cy = vs[7] * v[1] / vs[0];

    zn = (-vs[6] * vs[7] + vs[5] * vs[8]) / (-vs[7] + vs[8]);

    zf = vs[8] * vs[7] * (-vs[5] + vs[6]) / (-vs[7] + vs[8]);

    _UnitMatrix(a);
    a[0] = vs[0];
    a[5] = vs[0];
    a[10] = 0.0f;
    a[15] = 0.0f;
    a[14] = 1.0f;
    a[11] = 1.0f;

    _UnitMatrix(m0);
    /* clang-format off */
    m0[0] = vs[1]; m0[5] = vs[2]; m0[10] = zf;
    m0[12] = vs[3]; m0[13] = vs[4]; m0[14] = zn;
    /* clang-format on */
    _MulMatrix(a, m0, a);

    _UnitMatrix(b);
    b[0] = (vs[7] + vs[7]) / (sx + sx);
    b[5] = (vs[7] + vs[7]) / (sy + sy);
    b[10] = (vs[8] + vs[7]) / (vs[8] - vs[7]);
    b[14] = vs[8] * vs[7] * -2.0f / (vs[8] - vs[7]);
    b[11] = 1.0f;
    b[15] = 0.0f;

    _UnitMatrix(d);
    d[0] = vs[0] * vs[1] * sx / vs[7];
    d[5] = vs[0] * vs[2] * sy / vs[7];
    d[10] = (-vs[6] + vs[5]) * 0.5f;
    d[12] = vs[3];
    d[13] = vs[4];
    d[14] = (vs[6] + vs[5]) * 0.5f;
    d[15] = 1.0f;

    _UnitMatrix(c);
    c[0] = (vs[7] + vs[7]) / (cx + cx);
    c[5] = (vs[7] + vs[7]) / (cy + cy);
    c[10] = (vs[8] + vs[7]) / (vs[8] - vs[7]);
    c[14] = vs[8] * vs[7] * -2.0f / (vs[8] - vs[7]);
    c[11] = 1.0f;
    c[15] = 0.0f;

    _UnitMatrix(m1);
    m1[0] = 500.0f;
    m1[5] = 500.0f;
    m1[10] = 0.0f;
    m1[15] = 0.0f;
    m1[14] = 1.0f;
    m1[11] = 1.0f;

    _UnitMatrix(m0);
    /* clang-format off */
    m0[0] = vs[1]; m0[5] = vs[2]; m0[10] = zf;
    m0[12] = vs[3]; m0[13] = vs[4]; m0[14] = zn;
    /* clang-format on */
    _MulMatrix(matrixptr + 0x640, m0, m1);

    rx = vs[7] * v[0] / 500.0f;
    ry = vs[7] * v[1] / 500.0f;
    _UnitMatrix(m1);
    m1[0] = (vs[7] + vs[7]) / (rx + rx);
    m1[5] = (vs[7] + vs[7]) / (ry + ry);
    m1[10] = (vs[8] + vs[7]) / (vs[8] - vs[7]);
    m1[14] = vs[8] * vs[7] * -2.0f / (vs[8] - vs[7]);
    m1[11] = 1.0f;
    m1[15] = 0.0f;
    _CopyMatrix(matrixptr + 0x680, m1);
}

extern float staffRollCenterOffsetX;
extern int D_0028F948[];

/* The view record gsb_SetVSMatrixSub builds the view and screen matrices
 * from: the zoom, the two aspect terms, the centre, and the near and far
 * planes.  MAIN.MAP names no symbol inside GsBase.o's .bss, so the name is
 * a reconstruction; the extent (10 floats) is the ROM run's. */
static float vsParam[10];

extern void tex_UpdateMipMapLevel(float lv);
extern void gsb_SetVSMatrixSub(float *a, float *b, float *c, float *d, float *vs);

/* Set the view and screen matrices for a frame of w by h at depth d: the
 * centre is the screen middle less the staff roll offset, the zoom eases
 * towards its target by a thousandth of the step, and the view record at
 * vsParam carries the centre, the aspect terms and the near and far
 * planes gsb_SetVSMatrixSub builds the matrices from. */
void gsb_SetVSMatrix(int w, int h, float d)
{
    float zoom;

    center_X = center_Y = 2048.0f;
    if (d == 0.0f) {
        d = (float)currentFocusDistance;
    } else {
        currentFocusDistance = d;
    }
    vsWidth = w;
    vsHeight = h;
    if (zoomTarget != zoomCurrent) {
        zoomCurrent = zoomCurrent + (zoomTarget - zoomCurrent) * zoomSpeed * 0.001f;
    }
    if (staffRollStartFlag != 0) {
        center_X = center_X - staffRollCenterOffsetX;
    }
    zoom = (float)D_0028F720.viewScale * zoomCurrent * d * (float)debug_zoom_per *
           (float)ScreenWidth / 640.0f / 100.0f / 100.0f;
    vsParam[0] = zoom;
    if (debug_snapshot_reserve != 0 || (D_0028F948[0] & 0x800) != 0) {
        vsParam[0] = zoom * (float)debug_snapshot_num / 100.0f;
    }
    tex_UpdateMipMapLevel((float)D_0028F720.viewScale * zoomCurrent * (float)debug_zoom_per *
                          (float)ScreenWidth / 640.0f / 100.0f);
    vsParam[3] = center_X;
    vsParam[4] = center_Y;
    vsParam[5] = 1.0f;
    vsParam[6] = 536870880.0f;
    vsParam[7] = 2.0f;
    vsParam[1] = (float)w / (float)ScreenWidth;
    vsParam[8] = 262144.0f;
    vsParam[2] =
        (float)ScreenHeight * 4.0f / ((float)ScreenWidth * 3.0f) * (float)h / (float)ScreenHeight;
    gsb_SetVSMatrixSub(matrixptr + 0xC0, matrixptr + 0x1C0, matrixptr + 0x240, matrixptr + 0x340,
                       vsParam);
}

/* Clip a box against the current matrix: transform its eight corners with the
 * matrix in $vf4 to $vf7 and read the clip flags out of $vi18.  All eight
 * corners outside one plane gives 0, no corner clipped at all gives -1, and
 * the second pass re-clips against a 0.99 w so a corner that only just crosses
 * the near plane still counts as visible: 2 when it does, 1 when it does not. */
int gsb_ClipBox(float *p)
{
    int all = 0x3F;
    int any = 0;
    int c = 0;
    float *q = p;
    int i;

    for (i = 0; i < 8; q += 4, i++) {
        int cf;

        __asm__ __volatile__(".set noreorder\n\t"
                             "lqc2 $vf8, 0x0(%1)\n\t"
                             "vmulax.xyzw ACC, $vf4, $vf8x\n\t"
                             "vmadday.xyzw ACC, $vf5, $vf8y\n\t"
                             "vmaddaz.xyzw ACC, $vf6, $vf8z\n\t"
                             "vmaddw.xyzw $vf10, $vf7, $vf0w\n\t"
                             "vclipw.xyz $vf10, $vf10w\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "cfc2.ni %0, $vi18\n\t"
                             ".set reorder"
                             : "=r"(cf)
                             : "r"(q)
                             : "memory");
        all &= cf;
        any |= cf;
    }
    if (all & 0x2F) {
        return 0;
    }
    if ((any & 0x2F) == 0) {
        return -1;
    }
    for (i = 0; i < 8; p += 4, i++) {
        int cf;

        __asm__ __volatile__(".set noreorder\n\t"
                             "mfc1 $8, %1\n\t"
                             "lqc2 $vf8, 0x0(%2)\n\t"
                             "qmtc2.ni $8, $vf1\n\t"
                             "vmulx.w $vf1, $vf0, $vf1x\n\t"
                             "vmulax.xyzw ACC, $vf4, $vf8x\n\t"
                             "vmadday.xyzw ACC, $vf5, $vf8y\n\t"
                             "vmaddaz.xyzw ACC, $vf6, $vf8z\n\t"
                             "vmaddw.xyzw $vf10, $vf7, $vf0w\n\t"
                             "vclipw.xyz $vf10, $vf1w\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "cfc2.ni %0, $vi18\n\t"
                             ".set reorder"
                             : "=r"(cf)
                             : "f"(0.99f), "r"(p)
                             : "memory");
        c |= cf;
    }
    return (c & 0x20) ? 2 : 1;
}

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

extern int stage_no;
extern char D_005F5D90[];

inline int gsb_LoadStageSettings(void)
{
    char buf[0x100];
    int fd;
    sprintf(buf, "object/stagesetting/%s.ssb", D_005F5D90 + stage_no * 0x194);
    fd = debugSceOpen(buf, 1);
    if (fd < 0) {
        debug_StdPrintfDummy("gsb_LoadStageSettings: host file open error.\n");
    } else {
        debug_StdPrintfDummy("Load stage settings file. %s\n", buf);
        sceRead(fd, &D_0028F720, 0x1D0);
        debugSceClose(fd);
    }
    return -1;
}

/* Scratch for the editing log: first the log file's name, then the line
 * appended to it.  MAIN.MAP names no symbol inside GsBase.o's .bss, so the
 * name is a reconstruction; the extent is the ROM run's. */
static char logBuf[256];

extern int sceCdReadClock(sceCdCLOCK *c);

void appendLogFile(void)
{
    sceCdCLOCK clock;
    int fd;

    sceCdReadClock(&clock);
    sprintf(logBuf, "object/stagesetting/change.txt");
    fd = debugSceOpen(logBuf, 0x302);
    if (fd < 0) {
        debug_StdPrintfDummy("change.txt open error.\n");
        return;
    }
    sprintf(logBuf, "%04x/%02x/%02x %02x:%02x:%02x : stage %s  edit by %s\n", clock.year | 0x2000,
            clock.month, clock.day, clock.hour, clock.minute, clock.second,
            D_005F5D90 + stage_no * 0x194, "horagai");
    sceLseek(fd, 0, 2);
    sceWrite(fd, logBuf, strlen(logBuf));
    debugSceClose(fd);
    debug_StdPrintfDummy(logBuf);
}

inline int gsb_SaveStageSettings(void)
{
    char buf[0x100];
    int fd;
    if (otherEditingLocked == 0) {
        sprintf(buf, "object/stagesetting/%s.ssb", D_005F5D90 + stage_no * 0x194);
        fd = debugSceOpen(buf, 0x602);
        if (fd < 0) {
            debug_StdPrintfDummy("gsb_SaveStageSettings: host file open error.\n");
            return -1;
        }
        sceWrite(fd, &D_0028F720, 0x1D0);
        debug_StdPrintfDummy("Save stage settings file. %s\n", buf);
        debugSceClose(fd);
        appendLogFile();
    }
    return -1;
}

/* one row of the film noise debug menu (the same shape ico2/seki/src/ZFog.c
   carries for the fog tool): a label, the word it edits, whether that word is
   a float, its range, its default and its step, and the callback to run once
   the value has moved. */
typedef struct GsbToolItem {
    char *name;   /* 0x00 */
    void *val;    /* 0x04 */
    int isFloat;  /* 0x08 */
    float min;    /* 0x0C */
    float max;    /* 0x10 */
    float def;    /* 0x14 */
    float step;   /* 0x18 */
    void (*fn)(); /* 0x1C */
} GsbToolItem;

/* the four pages of seven rows, one page per render target, each row naming
   a word of the stage record */
static const GsbToolItem filmNoiseItems[4][7] = {
    /* derived name */
    {
        {" HighLight Color R ", &D_0028F720.targetCol[0][0], 0, 0.0f, 255.0f, 128.0f, 1.0f, 0},
        {" HighLight Color G ", &D_0028F720.targetCol[0][1], 0, 0.0f, 255.0f, 128.0f, 1.0f, 0},
        {" HighLight Color B ", &D_0028F720.targetCol[0][2], 0, 0.0f, 255.0f, 128.0f, 1.0f, 0},
        {" Noise Level       ", &D_0028F720.targetCol[0][3], 0, 0.0f, 255.0f, 8.0f, 1.0f, 0},
        {" Motion Blur       ", &D_0028F720.subMotionBlur[0], 0, 0.0f, 127.0f, 32.0f, 1.0f, 0},
        {" AntiLevel0        ", &D_0028F720.f19C[0].a, 0, 0.0f, 255.0f, 24.0f, 1.0f, 0},
        {" AntiLevel1        ", &D_0028F720.f19C[0].b, 0, 0.0f, 255.0f, 24.0f, 1.0f, 0},
    },
    {
        {" HighLight Color R ", &D_0028F720.targetCol[1][0], 0, 0.0f, 255.0f, 128.0f, 1.0f, 0},
        {" HighLight Color G ", &D_0028F720.targetCol[1][1], 0, 0.0f, 255.0f, 128.0f, 1.0f, 0},
        {" HighLight Color B ", &D_0028F720.targetCol[1][2], 0, 0.0f, 255.0f, 128.0f, 1.0f, 0},
        {" Noise Level       ", &D_0028F720.targetCol[1][3], 0, 0.0f, 255.0f, 16.0f, 1.0f, 0},
        {" Motion Blur       ", &D_0028F720.subMotionBlur[1], 0, 0.0f, 127.0f, 32.0f, 1.0f, 0},
        {" AntiLevel0        ", &D_0028F720.f19C[1].a, 0, 0.0f, 255.0f, 24.0f, 1.0f, 0},
        {" AntiLevel1        ", &D_0028F720.f19C[1].b, 0, 0.0f, 255.0f, 24.0f, 1.0f, 0},
    },
    {
        {" HighLight Color R ", &D_0028F720.targetCol[2][0], 0, 0.0f, 255.0f, 128.0f, 1.0f, 0},
        {" HighLight Color G ", &D_0028F720.targetCol[2][1], 0, 0.0f, 255.0f, 128.0f, 1.0f, 0},
        {" HighLight Color B ", &D_0028F720.targetCol[2][2], 0, 0.0f, 255.0f, 128.0f, 1.0f, 0},
        {" Noise Level       ", &D_0028F720.targetCol[2][3], 0, 0.0f, 255.0f, 24.0f, 1.0f, 0},
        {" Motion Blur       ", &D_0028F720.subMotionBlur[2], 0, 0.0f, 127.0f, 32.0f, 1.0f, 0},
        {" AntiLevel0        ", &D_0028F720.f19C[2].a, 0, 0.0f, 255.0f, 24.0f, 1.0f, 0},
        {" AntiLevel1        ", &D_0028F720.f19C[2].b, 0, 0.0f, 255.0f, 24.0f, 1.0f, 0},
    },
    {
        {" HighLight Color R ", &D_0028F720.targetCol[3][0], 0, 0.0f, 255.0f, 128.0f, 1.0f, 0},
        {" HighLight Color G ", &D_0028F720.targetCol[3][1], 0, 0.0f, 255.0f, 128.0f, 1.0f, 0},
        {" HighLight Color B ", &D_0028F720.targetCol[3][2], 0, 0.0f, 255.0f, 128.0f, 1.0f, 0},
        {" Noise Level       ", &D_0028F720.targetCol[3][3], 0, 0.0f, 255.0f, 32.0f, 1.0f, 0},
        {" Motion Blur       ", &D_0028F720.subMotionBlur[3], 0, 0.0f, 127.0f, 32.0f, 1.0f, 0},
        {" AntiLevel0        ", &D_0028F720.f19C[3].a, 0, 0.0f, 255.0f, 24.0f, 1.0f, 0},
        {" AntiLevel1        ", &D_0028F720.f19C[3].b, 0, 0.0f, 255.0f, 24.0f, 1.0f, 0},
    },
};

/* the unselected and selected row colours, ZFog's fogRowColor idiom: the
   unspecified bound keeps the 8-byte object out of small data under -G 8,
   which is where the ROM has it */
static const unsigned int filmNoiseRowColor[] = {0xFFFFFF00, 0xFF000000}; /* derived name */

/* .data, VMA 0x00290810: the word a boolean row prints.  Its two strings are
   the .sdata run's "On" then "Off": gcc writes an initialiser's string
   constants after the table, last one first.  MAIN.MAP names no symbol in this
   run and the array name is ours. */
static char *filmNoiseOnOffText[] = {"Off", "On"};

static int filmNoiseRow = 0; /* derived name */ /* the highlighted row */

extern GsbPad D_0028F8F0[];

/* The film noise page of the debug menu: seven editable words of the stage
 * record for the target this page names, the pad keys that walk and change
 * them, the key that dumps the page to the log, and the key that copies this
 * target's tint and blur over the main ones. */
int gsb_FilmNoiseTool(int target)
{
    int i;
    int ret = 0;
    int page = target;

    debug_PrintfDummy(10, 30, 0xFF800000, "Film Noise Pattern %d", target);

    for (i = 0; i < 7; i++) {
        if (filmNoiseItems[target][i].min == 0.0f && filmNoiseItems[target][i].max == 1.0f &&
            filmNoiseItems[target][i].isFloat == 0) {
            debug_PrintfDummy(18, (i + 1) * 8 + 30, filmNoiseRowColor[(filmNoiseRow == i) ? 1 : 0],
                              "%s : %s", filmNoiseItems[target][i].name,
                              filmNoiseOnOffText[*(int *)filmNoiseItems[target][i].val]);
        } else if (filmNoiseItems[target][i].isFloat == 0) {
            debug_PrintfDummy(18, (i + 1) * 8 + 30, filmNoiseRowColor[(filmNoiseRow == i) ? 1 : 0],
                              "%s : %d", filmNoiseItems[target][i].name,
                              *(int *)filmNoiseItems[target][i].val);
        } else {
            debug_PrintfDummy(18, (i + 1) * 8 + 30, filmNoiseRowColor[(filmNoiseRow == i) ? 1 : 0],
                              "%s : %f", filmNoiseItems[target][i].name,
                              *(float *)filmNoiseItems[target][i].val);
        }
    }

    if (D_0028F8F0[0].rep & 0x4000) {
        if (++filmNoiseRow >= 7) {
            filmNoiseRow = 0;
        }
    }
    if (D_0028F8F0[0].rep & 0x1000) {
        if (--filmNoiseRow < 0) {
            filmNoiseRow = 6;
        }
    }
    if (D_0028F8F0[0].rep & 0x2000) {
        if (filmNoiseItems[page][filmNoiseRow].isFloat == 0) {
            int v = (float)*(int *)filmNoiseItems[page][filmNoiseRow].val +
                    filmNoiseItems[page][filmNoiseRow].step;

            *(int *)filmNoiseItems[page][filmNoiseRow].val = v;
            if (filmNoiseItems[page][filmNoiseRow].max < (float)v) {
                *(int *)filmNoiseItems[page][filmNoiseRow].val =
                    filmNoiseItems[page][filmNoiseRow].min;
            }
        } else {
            float v = *(float *)filmNoiseItems[page][filmNoiseRow].val +
                      filmNoiseItems[page][filmNoiseRow].step;

            *(float *)filmNoiseItems[page][filmNoiseRow].val = v;
            if (filmNoiseItems[page][filmNoiseRow].max < v) {
                *(float *)filmNoiseItems[page][filmNoiseRow].val =
                    filmNoiseItems[page][filmNoiseRow].min;
            }
        }
        if (filmNoiseItems[page][filmNoiseRow].fn != 0) {
            filmNoiseItems[page][filmNoiseRow].fn(0);
        }
    }
    if (D_0028F8F0[0].rep & 0x8000) {
        if (filmNoiseItems[page][filmNoiseRow].isFloat == 0) {
            int v = (float)*(int *)filmNoiseItems[page][filmNoiseRow].val -
                    filmNoiseItems[page][filmNoiseRow].step;

            *(int *)filmNoiseItems[page][filmNoiseRow].val = v;
            if ((float)v < filmNoiseItems[page][filmNoiseRow].min) {
                *(int *)filmNoiseItems[page][filmNoiseRow].val =
                    filmNoiseItems[page][filmNoiseRow].max;
            }
        } else {
            float v = *(float *)filmNoiseItems[page][filmNoiseRow].val -
                      filmNoiseItems[page][filmNoiseRow].step;

            *(float *)filmNoiseItems[page][filmNoiseRow].val = v;
            if (v < filmNoiseItems[page][filmNoiseRow].min) {
                *(float *)filmNoiseItems[page][filmNoiseRow].val =
                    filmNoiseItems[page][filmNoiseRow].max;
            }
        }
        if (filmNoiseItems[page][filmNoiseRow].fn != 0) {
            filmNoiseItems[page][filmNoiseRow].fn(0);
        }
    }
    if (D_0028F8F0[0].trg & 0x10) {
        if (filmNoiseItems[page][filmNoiseRow].isFloat == 0) {
            *(int *)filmNoiseItems[page][filmNoiseRow].val = filmNoiseItems[page][filmNoiseRow].def;
        } else {
            *(float *)filmNoiseItems[page][filmNoiseRow].val =
                filmNoiseItems[page][filmNoiseRow].def;
        }
    }
    if (D_0028F8F0[0].trg & 0x20) {
        for (i = 0; i < 7; i++) {
            if (filmNoiseItems[page][i].min == 0.0f && filmNoiseItems[page][i].max == 1.0f &&
                filmNoiseItems[page][i].isFloat == 0) {
                debug_StdPrintfDummy("StageSetting %s => %s\n", filmNoiseItems[page][i].name,
                                     filmNoiseOnOffText[*(int *)filmNoiseItems[page][i].val]);
            } else if (filmNoiseItems[page][i].isFloat == 0) {
                debug_StdPrintfDummy("StageSetting %s => %d\n", filmNoiseItems[page][i].name,
                                     *(int *)filmNoiseItems[page][i].val);
            } else {
                debug_StdPrintfDummy("StageSetting %s => %f\n", filmNoiseItems[page][i].name,
                                     *(float *)filmNoiseItems[page][i].val);
            }
        }
        ret = 1;
    }
    if (D_0028F8F0[0].trg & 0x80) {
        D_0028F720.targetCol[target][0] = D_0028F720.reductionCol[0];
        D_0028F720.targetCol[target][1] = D_0028F720.reductionCol[1];
        D_0028F720.targetCol[target][2] = D_0028F720.reductionCol[2];
        D_0028F720.subMotionBlur[target] = D_0028F720.motionBlur;
        D_0028F720.f19C[target].a = D_0028F720.f0FC;
        D_0028F720.f19C[target].b = D_0028F720.f100;
    }
    if (D_0028F8F0[0].trg & 0x40) {
        ret = -1;
    }
    if (ret != 0) {
        filmNoiseRow = 0;
    }
    return ret;
}

extern int UpdateHandCameraLimitP(void);
extern int UpdateHandCameraLimitV(void);
extern int UpdateZoomMaxVallInDemo(void);

/* the twenty one rows of the stage setting page, each naming a word of the
   stage record (the words at 0xE4..0xF0, 0xF8, 0x104..0x11C and 0x180..0x190
   are still padding in typedef.h's StageSetting) */
static const GsbToolItem stageSettingItems[] = {
    /* derived name */
    {" HighLight Color R   ", &D_0028F720.reductionCol[0], 0, 0.0f, 255.0f, 128.0f, 1.0f, 0},
    {" HighLight Color G   ", &D_0028F720.reductionCol[1], 0, 0.0f, 255.0f, 128.0f, 1.0f, 0},
    {" HighLight Color B   ", &D_0028F720.reductionCol[2], 0, 0.0f, 255.0f, 128.0f, 1.0f, 0},
    {" Zoom Offset         ", &D_0028F720.viewScale, 0, 5e+01f, 4e+02f, 1e+02f, 1.0f, 0},
    {" Def Tex Sample Mode ", &D_0028F720.pad0E4[0], 0, 0.0f, 5.0f, 5.0f, 1.0f,
     tex_RemakeRegistersSampleMin},
    {" Post Effect         ", &D_0028F720.pad0E4[4], 0, 0.0f, 8.0f, 0.0f, 1.0f, 0},
    {" Feedback Effect     ", &D_0028F720.pad104[0], 0, 0.0f, 3.0f, 0.0f, 1.0f, 0},
    {" Feedback Effect R   ", &D_0028F720.pad104[12], 0, 0.0f, 255.0f, 0.0f, 1.0f, 0},
    {" Feedback Effect G   ", &D_0028F720.pad104[16], 0, 0.0f, 255.0f, 0.0f, 1.0f, 0},
    {" Feedback Effect B   ", &D_0028F720.pad104[20], 0, 0.0f, 255.0f, 0.0f, 1.0f, 0},
    {" Feedback Effect A   ", &D_0028F720.pad104[24], 0, 0.0f, 255.0f, 0.0f, 1.0f, 0},
    {" DepthField Level    ", &D_0028F720.pad0F8[0], 0, 0.0f, 1e+03f, 1e+02f, 1.0f, 0},
    {" DepthField Start    ", &D_0028F720.pad0E4[8], 0, 0.0f, 2e+04f, 2e+03f, 2e+01f, 0},
    {" DepthField Width    ", &D_0028F720.pad0E4[12], 0, 0.0f, 2e+04f, 1e+04f, 2e+01f, 0},
    {" HandCamera Limit P  ", &D_0028F720.pad174[12], 0, 0.0f, 1.8e+02f, 1.2e+02f, 1.0f,
     UpdateHandCameraLimitP},
    {" HandCamera Limit V  ", &D_0028F720.pad174[16], 0, 0.0f, 9e+01f, 8e+01f, 1.0f,
     UpdateHandCameraLimitV},
    {" ZOOM MAX IN DEMO    ", &D_0028F720.pad174[28], 0, 0.0f, 3e+02f, 2e+02f, 1.0f,
     UpdateZoomMaxVallInDemo},
    {" Motion Blur         ", &D_0028F720.motionBlur, 0, 0.0f, 127.0f, 32.0f, 1.0f, 0},
    {" AntiLevel0          ", &D_0028F720.f0FC, 0, 0.0f, 255.0f, 0.0f, 1.0f, 0},
    {" AntiLevel1          ", &D_0028F720.f100, 0, 0.0f, 255.0f, 0.0f, 1.0f, 0},
    {" Film Noise Tex Rep  ", &D_0028F720.grainScale, 1, 1.0f, 8.0f, 6.0f, 0.1f, 0},
};

/* the unselected and selected row colours, as filmNoiseRowColor */
static const unsigned int stageSettingRowColor[] = {0xFFFFFF00, 0xFF000000}; /* derived name */

/* .data, VMA 0x00290818: the stage setting page's own copy of the same pair.
   MAIN.MAP names no symbol in this run; the name is ours. */
static char *stageSettingOnOffText[] = {"Off", "On"};

static int stageSettingRow = 0; /* derived name */ /* the highlighted row */

/* The stage setting page of the debug menu: twenty one editable words of the
 * stage record, the pad keys that walk and change them, and the key that dumps
 * the page to the log. */
int gsb_StageSettingTool(void)
{
    int i;
    int ret = 0;

    debug_PrintfDummy(10, 30, 0xFF800000, "StageSetting Tool");

    for (i = 0; i < 21; i++) {
        if (stageSettingItems[i].min == 0.0f && stageSettingItems[i].max == 1.0f &&
            stageSettingItems[i].isFloat == 0) {
            debug_PrintfDummy(18, (i + 1) * 8 + 30,
                              stageSettingRowColor[(stageSettingRow == i) ? 1 : 0], "%s : %s",
                              stageSettingItems[i].name,
                              stageSettingOnOffText[*(int *)stageSettingItems[i].val]);
        } else if (stageSettingItems[i].isFloat == 0) {
            debug_PrintfDummy(18, (i + 1) * 8 + 30,
                              stageSettingRowColor[(stageSettingRow == i) ? 1 : 0], "%s : %d",
                              stageSettingItems[i].name, *(int *)stageSettingItems[i].val);
        } else {
            debug_PrintfDummy(18, (i + 1) * 8 + 30,
                              stageSettingRowColor[(stageSettingRow == i) ? 1 : 0], "%s : %f",
                              stageSettingItems[i].name, *(float *)stageSettingItems[i].val);
        }
    }

    if (D_0028F8F0[0].rep & 0x4000) {
        if (++stageSettingRow >= 21) {
            stageSettingRow = 0;
        }
    }
    if (D_0028F8F0[0].rep & 0x1000) {
        if (--stageSettingRow < 0) {
            stageSettingRow = 20;
        }
    }
    if (D_0028F8F0[0].rep & 0x2000) {
        if (stageSettingItems[stageSettingRow].isFloat == 0) {
            int v = (float)*(int *)stageSettingItems[stageSettingRow].val +
                    stageSettingItems[stageSettingRow].step;

            *(int *)stageSettingItems[stageSettingRow].val = v;
            if (stageSettingItems[stageSettingRow].max < (float)v) {
                *(int *)stageSettingItems[stageSettingRow].val =
                    stageSettingItems[stageSettingRow].min;
            }
        } else {
            float v = *(float *)stageSettingItems[stageSettingRow].val +
                      stageSettingItems[stageSettingRow].step;

            *(float *)stageSettingItems[stageSettingRow].val = v;
            if (stageSettingItems[stageSettingRow].max < v) {
                *(float *)stageSettingItems[stageSettingRow].val =
                    stageSettingItems[stageSettingRow].min;
            }
        }
        if (stageSettingItems[stageSettingRow].fn != 0) {
            stageSettingItems[stageSettingRow].fn(0);
        }
    }
    if (D_0028F8F0[0].rep & 0x8000) {
        if (stageSettingItems[stageSettingRow].isFloat == 0) {
            int v = (float)*(int *)stageSettingItems[stageSettingRow].val -
                    stageSettingItems[stageSettingRow].step;

            *(int *)stageSettingItems[stageSettingRow].val = v;
            if ((float)v < stageSettingItems[stageSettingRow].min) {
                *(int *)stageSettingItems[stageSettingRow].val =
                    stageSettingItems[stageSettingRow].max;
            }
        } else {
            float v = *(float *)stageSettingItems[stageSettingRow].val -
                      stageSettingItems[stageSettingRow].step;

            *(float *)stageSettingItems[stageSettingRow].val = v;
            if (v < stageSettingItems[stageSettingRow].min) {
                *(float *)stageSettingItems[stageSettingRow].val =
                    stageSettingItems[stageSettingRow].max;
            }
        }
        if (stageSettingItems[stageSettingRow].fn != 0) {
            stageSettingItems[stageSettingRow].fn(0);
        }
    }
    if (D_0028F8F0[0].trg & 0x10) {
        if (stageSettingItems[stageSettingRow].isFloat == 0) {
            *(int *)stageSettingItems[stageSettingRow].val = stageSettingItems[stageSettingRow].def;
        } else {
            *(float *)stageSettingItems[stageSettingRow].val =
                stageSettingItems[stageSettingRow].def;
        }
    }
    if (D_0028F8F0[0].trg & 0x20) {
        for (i = 0; i < 21; i++) {
            if (stageSettingItems[i].min == 0.0f && stageSettingItems[i].max == 1.0f &&
                stageSettingItems[i].isFloat == 0) {
                debug_StdPrintfDummy("StageSetting %s => %s\n", stageSettingItems[i].name,
                                     stageSettingOnOffText[*(int *)stageSettingItems[i].val]);
            } else if (stageSettingItems[i].isFloat == 0) {
                debug_StdPrintfDummy("StageSetting %s => %d\n", stageSettingItems[i].name,
                                     *(int *)stageSettingItems[i].val);
            } else {
                debug_StdPrintfDummy("StageSetting %s => %f\n", stageSettingItems[i].name,
                                     *(float *)stageSettingItems[i].val);
            }
        }
        ret = 1;
    }
    if (D_0028F8F0[0].trg & 0x40) {
        ret = -1;
    }
    if (ret != 0) {
        stageSettingRow = 0;
    }
    return ret;
}

/* The stage lock file's name, and the owner name read back out of it.
 * MAIN.MAP names no symbol inside GsBase.o's .bss, so both names are
 * reconstructions; the extents are the ROM run's. */
static char lockFileName[256];

static char lockOwner[72];

void updateOtherEditingLockFlag(void)
{
    char buf[0x100];
    int fd;

    sprintf(lockFileName, "object/stagesetting/%s.lock", D_005F5D90 + stage_no * 0x194);
    otherEditingLocked = 0;
    fd = debugSceOpen(lockFileName, 1);
    if (fd >= 0) {
        sceRead(fd, buf, 0x100);
        debugSceClose(fd);
        sscanf(buf, "%s\n", lockOwner);
    }
    if (fd < 0 || strcmp("nouser", lockOwner) == 0) {
        debug_StdPrintfDummy("no lock\n");
        editingSettings = 0;
    } else if (strcmp("horagai", lockOwner) != 0) {
        debug_StdPrintfDummy("lock by \"%s\"\n", lockOwner);
        otherEditingLocked = 1;
    } else {
        editingSettings = 1;
    }
}

/* the line-2873 helper the PAL listing shows inlined at the head of
   updateOtherEditingLockFlag, createLockFile and removeLockFile */
/* static helper the listing places at GsBase.c line 2873, inlined at the head of
 * updateOtherEditingLockFlag, createLockFile and removeLockFile; never emitted
 * out of line, so it has no MAIN.MAP symbol and this name is ours. */
static inline char *makeLockFileName(void)
{
    sprintf(lockFileName, "object/stagesetting/%s.lock", D_005F5D90 + stage_no * 0x194);
    return lockFileName;
}

int createLockFile(void)
{
    char buf[0x100];
    char *name = makeLockFileName();
    int fd = debugSceOpen(name, 0x602);
    if (fd < 0) {
        debug_StdPrintfDummy("cant create lock file\n");
        return 0;
    }
    sprintf(buf, "%s\n", "horagai");
    sceWrite(fd, buf, strlen(buf) + 1);
    debugSceClose(fd);
    debug_StdPrintfDummy(" create lock file \"%s\" by %s\n", name, buf);
    editingSettings = 1;
    return 1;
}

int removeLockFile(void)
{
    char buf[0x100];
    char *name = makeLockFileName();
    int fd = debugSceOpen(name, 0x602);
    if (fd < 0) {
        debug_StdPrintfDummy("cant remove lock file\n");
        return 0;
    }
    sprintf(buf, "%s\n", "nouser");
    sceWrite(fd, buf, strlen(buf) + 1);
    debugSceClose(fd);
    debug_StdPrintfDummy(" remove lock file \"%s\" by %s\n", name, "horagai");
    editingSettings = 0;
    return 1;
}

typedef struct {
    char *name;  /* 0x0 */
    int (*fn)(); /* 0x4 */
    int arg;     /* 0x8 */
} GsbMenuItem;

/* The four pages another TU owns, and the four this one defines below. */
extern int light_Tool(void);
extern int shadow_Tool(void);
extern int fog_FogTool(void);

/* The background colour the display list is cleared to, one component per
 * word of an integer quadword: gsb_SetBGColor writes the four words and
 * gsb_GetBGColor reads them back as bytes.  The quadword's alignment is the
 * one that puts GsBase.o's .bss on a 16-byte boundary (0x67BA60) after
 * tableSin.o's 0x12012-byte run.  MAIN.MAP names no symbol inside GsBase.o's
 * .bss, so the name is a reconstruction; the extent is the ROM run's. */
static sceVu0IVECTOR bgColor;

inline void gsb_SetBGColor(void *a0, int r, int g, int b)
{
    unsigned long long bg = ((long long)b << 16) | ((long long)g << 8);
    unsigned long long v = r | 0x3F80000000000000ULL;
    v |= bg;
    bgColor[0] = r;
    v |= 0x80000000;
    bgColor[1] = g;
    bgColor[2] = b;
    bgColor[3] = 0x80;
    *(unsigned long long *)((char *)a0 + 0x1F0) = v;
    *(unsigned long long *)((char *)a0 + 0x100) = v;
}

inline void gsb_GetBGColor(unsigned char *a0)
{
    a0[0] = bgColor[0];
    a0[1] = bgColor[1];
    a0[2] = bgColor[2];
    a0[3] = bgColor[3];
}

inline void gsb_SetZoom(float a, float b)
{
    zoomTarget = a;
    zoomSpeed = b;
}

/* kept local: the declaration in GsBase.h changes this TU codegen */
extern void updateOtherEditingLockFlag(void);

inline int lockOtherEditing(void)
{
    updateOtherEditingLockFlag();
    if (otherEditingLocked != 0) {
        return -1;
    }
    createLockFile();
    gsb_LoadStageSettings();
    return -1;
}

inline int unlockOtherEditing(void)
{
    updateOtherEditingLockFlag();
    if (otherEditingLocked != 0) {
        return -1;
    }
    gsb_LoadStageSettings();
    removeLockFile();
    return -1;
}

static GsbMenuItem lockedMenu[] = {
    {"LOCK OTHER EDITING", lockOtherEditing, 0},
};

static GsbMenuItem stageSettingMenu[] = {
    {"Light Tool", light_Tool, 0},
    {"Shadow Tool", shadow_Tool, 0},
    {"Fog Tool", fog_FogTool, 0},
    {"Film Noise 1", gsb_FilmNoiseTool, 0},
    {"Film Noise 2", gsb_FilmNoiseTool, 1},
    {"Film Noise 3", gsb_FilmNoiseTool, 2},
    {"Film Noise 4", gsb_FilmNoiseTool, 3},
    {"Other Settings", gsb_StageSettingTool, 0},
    {"Load Settings", gsb_LoadStageSettings, 0},
    {"Save Settings", gsb_SaveStageSettings, 0},
    {"UnLock Quit", unlockOtherEditing, 0},
};

/* the unselected and selected row colours, as filmNoiseRowColor */
static const unsigned int menuRowColor[] = {0xFFFFFF00, 0xFF000000}; /* derived name */

/* the menu row under the cursor and the page it opened, -1 for none */
static int menuCursor = 0; /* derived name */

static int menuSelected = -1; /* derived name */

int gsb_StageSetting(void)
{
    int i;
    editingSettings = 1;
    if (menuSelected >= 0) {
        if (stageSettingMenu[menuSelected].fn != 0) {
            int r = stageSettingMenu[menuSelected].fn(stageSettingMenu[menuSelected].arg);
            if (r == -1) {
                menuSelected = r;
            }
            return 0;
        }
    }
    if (editingSettings) {
        for (i = 0; i < 11; i++) {
            debug_PrintfDummy(18, (i + 1) * 8 + 0x1E, menuRowColor[(menuCursor == i) ? 1 : 0], "%s",
                              stageSettingMenu[i].name);
        }
        if (D_0028F8F0[0].rep & 0x4000) {
            menuCursor++;
            if (menuCursor >= 11)
                menuCursor = 0;
        }
        if (D_0028F8F0[0].rep & 0x1000) {
            menuCursor--;
            if (menuCursor < 0)
                menuCursor = 10;
        }
        if (D_0028F8F0[0].trg & 0x20) {
            menuSelected = menuCursor;
        }
    } else {
        debug_PrintfDummy(26, 22, 0xFFFFFFFF, "NO ONE EDITS THIS STAGE'S SETTING.");
        debug_PrintfDummy(18, 38, menuRowColor[1], "%s", lockedMenu[0].name);
        if (D_0028F8F0[0].trg & 0x20) {
            lockedMenu[0].fn(1);
        }
    }
    return (D_0028F8F0[0].trg & 0x40) ? -1 : 0;
}
