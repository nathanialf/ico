#include "debug.h"
#include "Basic.h"
#include "GsBase.h"
#include "Packet.h"
#include "RegistPacket.h"
#include "Shadow.h"
#include "StageAnimation.h"
#include "Texture.h"
#include "staticBlur.h"
#include <libvu0.h>
#include <eekernel.h>
#include <sifdev.h>
#include <stdio.h>
#include "typedef.h"
#include "gflag.h"
#include <eeregs.h>
#include "layout_texture.h"
#include "staffroll.h"
#include "camera-root.h"
#include <eekernel.h>
#include "ZFog.h"
#include "Light.h"
#include "Matrix.h"
#include "DmaPacket.h"
#include "DisplayList.h"
#include "main.h"
#include <libgraph.h>
#include <libcdvd.h>

/* declared here with an int count, not through string.h, as in
   layout_action.c and puddle.c */
extern void *memset(void *p, int c, int n);

/* GsBase.c's globals, tentative definitions: the frame buffer flags, the
   screen centre and size, then the XYOFFSET adjustment and the frame size
   gsb_SetVSMatrix records. */
int fbKeep;

int fbClear;

float center_X;

float center_Y;

int ScreenWidth;

int ScreenHeight;

/* currentScreenWidth is main.c's in this build; PAL's currentScreenHeight
   and screen offsets are not in the demo's .sdata */

int vsWidth; /* derived name */

int vsHeight; /* derived name */

/* The word gsb_Init clears (nothing reads it), the GS system flag, the zoom
   easing (target, current, speed) and the last projection distance
   gsb_SetVSMatrix was given.  This build has no stage lock state words in
   front of them (PAL's otherEditingLocked and editingSettings): the demo's
   .sdata of the TU opens with the two words gsb_Init and gsb_InitGSSystem
   use. */
static int gsInitState = 0; /* derived name */

static int gsSystemReady = 0; /* derived name */

static float zoomTarget = 1.0f; /* derived name */

static float zoomCurrent = 1.0f; /* derived name */

static float zoomSpeed = 1000.0f; /* derived name */

int currentFocusDistance = 1;

/* Point the double buffer's two display and two draw environments at the
 * frame this stage draws into: the low nine bits of each frame word carry the
 * buffer base in 64-word units and each draw env's ZBUF carries the zbuffer
 * base, its psm nibble and the mask bit. */
void gsb_SetFrame(sceGsDBuff *db, int a1, int a2, int psm, short zbp)
{
    sceGsDispEnv *disp1 = &db->disp[1];
    long long zb = ((long long)zbp << 32) | 0xC0;
    short h = (short)(unsigned short)ScreenHeight / 2;
    short w = ScreenWidth;

    *(int *)&disp1->dispfb &= ~0x1FF;
    *(int *)&db->disp[0].dispfb &= ~0x1FF;
    /* the four register words are rewritten through GifPkWord's union view */
    ((GifPkWord *)&db->draw1.frame)->d = (((GifPkWord *)&db->draw1.frame)->d & ~0x1FF) | 0x40;
    ((GifPkWord *)&db->draw0.frame)->d = (((GifPkWord *)&db->draw0.frame)->d & ~0x1FF) | 0x40;
    ((GifPkWord *)&db->draw1.zbuf)->d = ((long long)(psm & 0xF) << 24) | zb;
    ((GifPkWord *)&db->draw0.zbuf)->d = ((long long)(psm & 0xF) << 24) | zb;
    sceGsSetDefDispEnv(&db->disp[0], 0, w, h, 0, 0);
    sceGsSetDefDispEnv(disp1, 0, w, h, 0, 0);
}

/* Bring the GS up and set the double buffer up (JPN: the other way round)
 * for the frame size the stage record asks for: 512 by 448 interlaced,
 * 512 by 512 in the tall mode and 512 by 448 otherwise, then hand the first
 * frame over and put the view scale back to one. */
void gsb_Init(void *db)
{
    int omode = 2;

    sceGsSyncV(0);
    fbClear = 1;
    gsInitState = 0;
    switch (systemStatus[0]) {
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
    sceGsSetDefDBuff(db, 0, ScreenWidth, ScreenHeight, 2, 0x30, fbClear);
    gsb_SetFrame(db, 0, 0, 0x30, 2);
    sceGsResetGraph(0, systemStatus[1] == 1, omode, 1);
    sceGsSyncV(0);
    buffer_ID = 0;
    FlushCache(0);
    sceGsSwapDBuff(db, buffer_ID);
    while (sceGsSyncPath(1, 0) != 0) {
        debug_StdPrintfDummy("wait gs init\n");
    }
    gsb_SetVSMatrix(ScreenWidth, ScreenHeight, 512.0f);
    shadow_Init();
    zoomTarget = 1.0f;
    zoomSpeed = 1000.0f;
    zoomCurrent = 1.0f;
}

/* Clear the frame buffer: a GIF packet of 23 A+D writes (the drawing
   state, then a black sprite into each of four frame buffer pages) sent
   down path 2 in one DMA and waited for. */
inline void gsb_ClearFrameBuffer(void)
{
    long long packet[48] = {
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
        0x1300000C0LL,
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

    FlushCache(0);
    *D2_QWC = 24;
    *D2_MADR = (unsigned int)packet & 0x0FFFFFFF;
    *D2_CHCR = 0x101;
    sceGsSyncPath(0, 0);
}

/* the reduction tint gsb_Reduction picks each frame and packs into the
   sprite colour */
static int reductionRed; /* derived name */

static int reductionGreen; /* derived name */

static int reductionBlue; /* derived name */

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
        ((long long)(ScreenWidth - 3) << 16) | 2 | ((long long)(ScreenHeight / 2 - 1) << 48),
        0x40,
        ((long long)(ScreenWidth / 64) << 14) | 0x664000800LL,
        6,
        0x60,
        0x14,
        0x30000,
        0x47,
        0x1300000C0LL,
        0x4E,
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

    FlushCache(0);
    *D2_QWC = 22;
    *D2_MADR = (int)pk & 0x0FFFFFFF;
    *D2_CHCR = 0x101;
    sceGsSyncPath(0, 0);
    reductionRed = fbKeep ? 128 : GlobalStageSetting.reductionCol[0];
    reductionGreen = fbKeep ? 128 : GlobalStageSetting.reductionCol[1];
    reductionBlue = fbKeep ? 128 : GlobalStageSetting.reductionCol[2];
}

/* the colour the kept frame is drawn back in */
static const unsigned char keepFrameColor[4] = {128, 128, 128, 128}; /* derived name */

/* as in GifPacket.h, which this TU does not include */
extern void gif_EndPacket(void);
/* void (int, long long) here, void (long long, long long) in GifPacket.h */
extern void gif_SetGsReg(int reg, long long data);
/* as in GifPacket.h, which this TU does not include */
extern void gif_StartPacketPriPath1(int pri);

/* A rectangle in 16ths of a pixel, the form the sprite corners are written
   in. */
typedef struct { /* field names derived */
    int x;
    int y;
    int w;
    int h;
} GsbRect; /* derived name */

/* The GS A+D writer, the payload word then the register word, a macro as in
 * Shadow.c and Texture.c. */
#define setGsReg(reg, val) /* derived name */                                                      \
    {                                                                                              \
        *PacketBufferStruct.ptr.d++ = (val);                                                       \
        *PacketBufferStruct.ptr.d++ = (reg);                                                       \
    }
/* RGBAQ packed from a four-byte colour, as Shadow.c packs it */
#define GIF_RGBA(c) /* derived name */                                                             \
    ((long long)(c)[0] | ((long long)(c)[1] << 8) | ((long long)(c)[2] << 16) |                    \
     ((long long)(c)[3] << 24))
/* The textured sprite at depth 0: PRIM, RGBAQ, then a UV and an XYZ2 pair for
 * each corner of the rect r (x, y, w, h in sixteenths) and its texture rect
 * uv, the far corner as x + fx with fx = w + 0x8000.  Shadow.c's spriteUV
 * with the depth left out; a MACRO for the same reason. */
#define spriteUV(r, uv, col, prim) /* derived name */                                              \
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
#define spriteRect(x, y, w, h, z, col, prim) /* derived name */                                    \
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

/* Draw the whole screen back over itself as one sprite in the kept colour. */
static void gsb_KeepFrameBuffer(void)
{
    GsbRect r0 = {-(ScreenWidth >> 1) * 16 - 4, -(ScreenHeight >> 1) * 16 - 4,
                  ScreenWidth * 16 + 16, ScreenHeight * 16 + 16};
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

/* the fade level gsb_fade steps from 0 to 128 and gsb_PostEffect prints (this
   build has no unused word after it) */
static float fadeLevel; /* derived name */

/* as in GifPacket.h, which this TU does not include */
extern void gif_StartPacketPri(int pri);
/* void (int, int, int, int, int, int) here, void (unsigned long long, unsigned long long, unsigned int, unsigned int, int, int) in GifPacket.h */
extern void gif_SetDrawEnviroment(int fbp, int psm, int w, int h, int useoffset, int clear);

/* The fade overlay: step the fade level by half the speed each frame, clamp
 * it to 0 to 128, stop or hand over to the continue state at the ends, and
 * draw the whole screen as one sprite in the fade colour.  The two end tests
 * are `&&` chains. */
static void gsb_fade(void)
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
    gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 0, 0);
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

/* gsb_scissorOnDemo's state: the demo state it last saw, the band level and
   its step */
static int scissorLastState = 50; /* derived name */

static float scissorLevel = 0.0f; /* derived name */

static float scissorStep = 0.0f; /* derived name */

/* as in GifPacket.h, which this TU does not include */
extern void gif_EndPacketPath1(void);

/* The letterbox the demo scenes fade in: two black bars, top and bottom,
 * whose alpha eases to 128 while the scene is state 55 (JPN layout 52) and back to 0
 * otherwise.  While the bars are visible they are drawn and the motion blur
 * is left alone; once they are gone the stage record's blur setting is
 * restored.  Each bar is drawn by a macro inside the two-iteration loop,
 * its first corner written before fx and fy are formed. */
static void gsb_scissorOnDemo(void)
{
    GsbRect r[2] = {
        {-(ScreenWidth >> 1) * 16, -(ScreenHeight >> 1) * 16 - 4, ScreenWidth * 16, 58 * 16},
        {-(ScreenWidth >> 1) * 16, ((ScreenHeight >> 1) - 58) * 16 + 4, ScreenWidth * 16, 58 * 16}};
    unsigned char col[4];
    int i;

    if (current_layout_id == 51 && scissorLastState != current_layout_id) {
        scissorStep = 2.5f;
    } else if (scissorLastState != current_layout_id) {
        scissorStep = -2.5f;
    }
    scissorLastState = current_layout_id;

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
        dl_SetDLPriority(12);
        gif_StartPacketPriPath1(dl_GetPri());
        memset(col, 0, 4);
        col[3] = 0x80;
        gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 0, 0);
        gif_SetGsReg(0x47, 0x30000);
        gif_SetGsReg(0x4E, 0x1300000C0LL);
        gif_SetGsReg(0x49, 0);
        gif_SetGsReg(0x42, ((long long)(int)scissorLevel << 32) | 0x64);
        for (i = 0; i < 2; i++) {
            spriteRect(r[i].x, r[i].y, r[i].w, r[i].h, -1LL, col, 0x446);
        }
        gif_EndPacketPath1();
    } else {
        SetMotionBlur(GlobalStageSetting.motionBlur);
    }
}

/* void (int, int, int) here, void (long long, long long, long long) in GifPacket.h */
extern void gif_SetAlpha(int alpha, int mode, int fix);
/* void (int, int, int, int, unsigned int, unsigned char *, int) here, void (int, int, int, int, long long, GifColor *, int) in GifPacket.h */
extern void gif_MakeSpriteNoTexture(int x, int y, int w, int h, unsigned int z, unsigned char *col,
                                    int prim);

/* Darken the whole frame by the stage record's brightness step: a full screen
 * white sprite in destination-alpha blend whose alpha is the step, clamped to
 * 0 to 15 and skipped at 0. */
static void gsb_controlBrightness(void)
{
    int v = systemStatus[0x2C / 4];

    if (v < 0) {
        v = systemStatus[0x2C / 4] = 0;
    }
    if (v >= 0x10) {
        v = systemStatus[0x2C / 4] = 0xF;
    }
    if (v != 0) {
        if (debug_font_flag & 1) {
            debug_Printf(0x212, ScreenHeight / 2 - 8, 0xCCCCCC00, "B");
        }
        gif_StartPacketPri(0xB);
        {
            unsigned char col[4] = {0xFF, 0xFF, 0xFF, systemStatus[0x2C / 4]};

            gif_SetGsReg(0x47, 0x30000);
            gif_SetGsReg(0x4E, 0x1300000C0LL);
            gif_SetAlpha(1, 7, 0);
            gif_MakeSpriteNoTexture((0x800 - ScreenWidth / 2) << 4, (0x800 - ScreenHeight / 2) << 4,
                                    ScreenWidth << 4, ScreenHeight << 4, 0xFFFFFFFF, col, 1);
            gif_EndPacketPath1();
        }
    }
}

/* A colour as the sprite family takes it, four bytes in RGBA order; the same
   record as Texture.c's TexColor. */
typedef struct { /* field names derived */
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} GsbColor; /* derived name */

/* as in GifPacket.h, which this TU does not include */
extern void gif_SetZTest(int on);
/* as in GifPacket.h, which this TU does not include */
extern void gif_SetZWrite(int on);
/* as in GifPacket.h, which this TU does not include, with GsbRect and GsbColor
 * for its GifRect and GifColor */
extern void gif_SpriteSensitiveOrg(GsbRect *r, long long z, GsbRect *uv, GsbColor *col, int prim);

/* Soften the frame's edges: the frame is reduced to a 256 square copy and,
 * when the second level is on, a 128 square one, and each level the stage
 * record (or the current sub target's row) turns on is blended back over the
 * 512 square buffer through the sensitive sprite.  Every TEX0 write is one
 * expression in field order, as Texture.c spells it. */
static void gsb_antiAlias(void)
{
    GsbColor col = {128, 128, 128, 128};
    GsbRect s0 = {4, 4, 8192, 8192};
    GsbRect s1 = {4, 4, 4096, 4096};
    GsbRect s2 = {4, 4, 2048, 2048};
    GsbRect d0 = {-4100, -4100, 8192, 8192};
    GsbRect d1 = {-2052, -2052, 4096, 4096};
    GsbRect d2 = {-1028, -1028, 2048, 2048};
    int lv[2] = {GlobalStageSetting.antiLevel0, GlobalStageSetting.antiLevel1};

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
    gif_SpriteSensitiveOrg(&d1, 0, &s0, &col, 0);
    if (lv[1] != 0) {
        gif_SetGsReg(6, 0x2800 | ((long long)4 << 14) | ((long long)tex_GetTWTH(256) << 26) |
                            ((long long)tex_GetTWTH(256) << 30) | ((long long)1 << 34));
        gif_SetDrawEnviroment(0x2C00, 0, 128, 128, 0, 0);
        gif_SpriteSensitiveOrg(&d2, 0, &s1, &col, 0);
    }
    gif_SetDrawEnviroment(0x800, 0, 512, 512, 0, 0);
    if (lv[1] != 0) {
        gif_SetAlpha(1, 2, lv[1]);
        gif_SetGsReg(6, 0x2C00 | ((long long)2 << 14) | ((long long)tex_GetTWTH(128) << 26) |
                            ((long long)tex_GetTWTH(128) << 30) | ((long long)1 << 34));
        gif_SpriteSensitiveOrg(&d0, 0, &s2, &col, 1);
    }
    if (lv[0] != 0) {
        gif_SetAlpha(1, 2, lv[0]);
        gif_SetGsReg(6, 0x2800 | ((long long)4 << 14) | ((long long)tex_GetTWTH(256) << 26) |
                            ((long long)tex_GetTWTH(256) << 30) | ((long long)1 << 34));
        gif_SpriteSensitiveOrg(&d0, 0, &s1, &col, 1);
    }
    gif_SetZWrite(1);
    gif_SetZTest(1);
    gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 0, 0);
    gif_EndPacket();
}

static void gsb_setNormalReg(int ctx)
{
    dl_SetDLPriority(ctx);
    gif_StartPacketPriPath1(dl_GetPri());
    gif_SetGsReg(0x47, 0x50000);
    gif_SetGsReg(0x4E, 0x300000C0);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x8000000080LL);
    gif_EndPacketPath1();
}

static void gsb_setSemitransReg(int ctx)
{
    dl_SetDLPriority(ctx);
    gif_StartPacketPriPath1(dl_GetPri());
    gif_SetGsReg(0x47, 0x5140D);
    gif_SetGsReg(0x4E, 0x300000C0);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x8000000080LL);
    gif_EndPacketPath1();
}

static void gsb_setSpecularReg(int ctx)
{
    dl_SetDLPriority(ctx);
    gif_StartPacketPriPath1(dl_GetPri());
    gif_SetGsReg(0x47, 0x5C000);
    gif_SetGsReg(0x4E, 0x1300000C0LL);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x8000000080LL);
    gif_EndPacketPath1();
}

static void gsb_setParticleReg(int ctx)
{
    dl_SetDLPriority(ctx);
    gif_StartPacketPriPath1(dl_GetPri());
    gif_SetGsReg(0x47, 0x50000);
    gif_SetGsReg(0x4E, 0x1300000C0LL);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x8000000080LL);
    gif_EndPacketPath1();
}

/* the head of the common matrix packet: the three constant rows of the VU
   parameter block (the unit w, the clip extents and a zero row) and the GIF
   tag of the strip the microcode sends */
static const struct { /* field names derived */
    sceVu0FVECTOR row[3];
    sceVu0IVECTOR tag;
} commonMatrixHead = {
    /* derived name */
    {{0.0f, 0.0f, 0.0f, 1.0f}, {4095.0f, 4095.0f, 0.0f, 16777215.0f}, {0.0f, 0.0f, 0.0f, 0.0f}},
    {0x8000, 0x302EC000, 0x512, 0},
};

/* Build the frame's common matrix packet: the two view matrices the stage
 * needs, the matrix at 0x280, the sun's camera matrix (looking down the sun
 * direction from a million units out) times the inverse of the view, and the
 * display list that uploads them to VU memory, opened once for each of the
 * thirteen list priorities. */
void gsb_MakeCommonMatrix(void)
{
    float pos[4];
    float up[4] = {0.0f, 1.0f, 0.0f, 0.0f};
    float sun[4];
    float sunMatrix[4][4];
    float invView[4][4];
    GifPkWord *p;
    GifPkWord *q;
    int i;

    if (game_pause == 0) {
        return;
    }
    i = 0;
    _MulMatrix(matrixptr + 0x100, matrixptr + 0xC0, matrixptr + 0x80);
    _MulMatrix(matrixptr + 0x200, matrixptr + 0x1C0, matrixptr + 0x80);
    _InversMatrix(matrixptr + 0x2C0, matrixptr + 0x80);
    GetSunWorldPos(sun);
    _ScaleVector(pos, sun, 1000000.0f);
    _SetCameraMatrix(sunMatrix, pos, sun, up);
    _UnitVector(sunMatrix[3]);
    _CopyMatrix(invView, matrixptr + 0x2C0);
    _UnitVector(invView[3]);
    p = (GifPkWord *)PacketBufferStruct.ptr.d;
    PacketBufferStruct.gif.c = 0;
    PacketBufferStruct.dma.c = (char *)p;
    PacketBufferStruct.end.c = 0;
    PacketBufferStruct.tail.c = (char *)p;
    p[0].d = 0x10000011;
    PacketBufferStruct.ptr.c = (char *)p + 8;
    p[1].w[0] = 0x13000000;
    PacketBufferStruct.ptr.c = (char *)p + 0xC;
    PacketBufferStruct.gif.c = (char *)p + 0xC;
    p[1].w[1] = 0x6C100000;
    PacketBufferStruct.ptr.c = (char *)p + 0x10;
    _CopyMatrix((char *)p + 0x10, &commonMatrixHead);
    PacketBufferStruct.ptr.c = PacketBufferStruct.ptr.c + 0x40;
    _CopyMatrix(PacketBufferStruct.ptr.d, matrixptr + 0x100);
    PacketBufferStruct.ptr.c = PacketBufferStruct.ptr.c + 0x40;
    _CopyMatrix(PacketBufferStruct.ptr.d, matrixptr + 0x280);
    PacketBufferStruct.ptr.c = PacketBufferStruct.ptr.c + 0x40;
    _MulMatrix(PacketBufferStruct.ptr.d, sunMatrix, invView);
    q = (GifPkWord *)PacketBufferStruct.ptr.d;
    PacketBufferStruct.ptr.c = (char *)q + 0x40;
    q[8].w[0] = 0x13000000;
    PacketBufferStruct.ptr.c = (char *)q + 0x44;
    q[8].w[1] = 0;
    PacketBufferStruct.ptr.c = (char *)q + 0x48;
    q[9].w[0] = 0;
    PacketBufferStruct.ptr.c = (char *)q + 0x4C;
    q[9].w[1] = 0;
    PacketBufferStruct.ptr.c = (char *)q + 0x50;
    PacketBufferStruct.tail.c = (char *)q + 0x50;
    q[10].d = 0x60000000;
    PacketBufferStruct.ptr.c = (char *)q + 0x58;
    q[11].w[0] = 0;
    PacketBufferStruct.ptr.c = (char *)q + 0x5C;
    q[11].w[1] = 0;
    PacketBufferStruct.ptr.c = (char *)q + 0x60;
    do {
        dl_SetDLPriority(i);
        i++;
        dl_OpenDma(5, PacketBufferStruct.dma.c, 0);
        dl_CloseDma();
    } while (i < 0xD);
}

/* set by gsb_SetGsDefault once the frame is up, tested by gsb_PostEffect */
static int postEffectReady = 0; /* derived name */

/* Open the frame's first display list: one DMA tag, the two VIF words that
 * hand path 1 to the GS, a second tag for the register run, and then the
 * default register set for each of the thirteen contexts. */
static void gsb_SetGsDefault(void)
{
    DpkCtl *d = &PacketBufferStruct;
    GifPkWord *p = (GifPkWord *)d->ptr.d;

    d->gif.c = 0;
    d->tail.c = (char *)p;
    d->dma.c = (char *)p;
    d->end.c = 0;
    p[0].d = 0x10000000;
    d->ptr.c = (char *)p + 8;
    p[1].w[0] = 0x3000100;
    d->ptr.c = (char *)p + 0xC;
    p[1].w[1] = 0x2000180;
    d->ptr.c = (char *)p + 0x10;
    d->tail.c = (char *)p + 0x10;
    p[2].d = 0x60000000;
    d->ptr.c = (char *)p + 0x18;
    p[3].w[0] = 0;
    d->ptr.c = (char *)p + 0x1C;
    p[3].w[1] = 0;
    d->ptr.c = (char *)p + 0x20;
    dl_SetDLPriority(0);
    dl_OpenDma(5, d->dma.c, 0);
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
    postEffectReady = 0;
    shadow_Reset();
    postEffectReady = 1;
    FullScreenEffectBefore();
}

/* Everything the frame still owes after the scene is drawn: the debug read
 * outs, the full screen effect, the shadow and fog passes, the motion blur,
 * the anti alias pass, the film grain and the brightness step, the kept frame
 * buffer, the staff roll and last the fade and the demo scissor. */
static int gsb_PostEffect(void)
{
    if (debug_font_flag & 1) {
        debug_Printf(0xA, ScreenHeight / 2 - 8, 0xCCCCCC00, "LID:%3d / FADE%d:%3.0f(%d)",
                     current_layout_id, fadeStatus, fadeLevel, fadeColor[3]);
    }
    if (systemStatus[0x18 / 4] != 0 && (debug_font_flag & 1)) {
        debug_Printf(0x230, ScreenHeight / 2 - 8, 0xCCCCCC00, "L");
    }
    if (systemStatus[0x14 / 4] != 0 && (debug_font_flag & 1)) {
        debug_Printf(0x23A, ScreenHeight / 2 - 8, 0xCCCCCC00, "P");
    }
    if (postEffectReady != 0) {
        shadow_Draw();
        fog_DrawFog();
    }
    MotionBlur();
    gsb_controlBrightness();
    FullScreenEffectAfter();
    if (fbKeep != 0) {
        gsb_KeepFrameBuffer();
        if (debug_font_flag & 1) {
            debug_Printf(0x226, ScreenHeight / 2 - 8, 0xCCCCCC00, "K");
        }
    }
    if (staffRollStartFlag != 0) {
        staffRollMain();
        if (staffRollStartFlag != 0) {
            gsb_scissorOnDemo();
        }
    }
    gsb_antiAlias();
    gsb_fade();
    return fbKeep;
}

/* gsb_InitGSSystem's first call brings every module up */
static int firstGsInit = 1; /* derived name */

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
        gsb_Init(&db);
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
    gsSystemReady = 1;
}

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
    return 0;
}

/* One frame boundary: take the field parity from the GS CSR, run the
 * reduction pass, flip the double buffer and hand the display list back
 * either swapped or cleared, then reopen the frame's register set. */
void gsb_UpdateGSSystem(void)
{
    sceGsDrawEnv *draw;

    odd_even = (*GS_CSR >> 13) & 1;
    gsb_PostEffect();
    gsb_Reduction();
    if (gsSystemReady == 0) {
        dl_Clear();
        return;
    }
    debug_FlushFont();
    frame_count++;
    buffer_ID = frame_count & 1;
    FlushCache(0);
    sceGsSwapDBuff(&db, buffer_ID);
    if (buffer_ID != 0) {
        draw = &db.draw1;
    } else {
        draw = &db.draw0;
    }
    sceGsSetHalfOffset(draw, (short)((float)screen_offset_x + 2048.0f),
                       (short)((float)screen_offset_y + 2048.0f), odd_even == 0);
    tex_ResetVram();
    dl_Swap();
    gsb_SetGsDefault();
    if (staffRollStartFlag == 0) {
        gsb_scissorOnDemo();
    }
}

/* Reset the GS between stages: reopen the paths, reset the VU0 and the DMA,
 * put the graphics mode back, take the field parity out of the GS CSR and
 * flip the double buffer, then re-open the frame's display list. */
void gsb_ResetGSSystem(void)
{
    sceGsDrawEnv *draw;

    sceGsResetPath();
    sceVpu0Reset();
    dma_init();
    sceGsResetGraph(0, systemStatus[1] == 1, (unsigned short)systemStatus[0] + 2, 1);
    frame_count++;
    buffer_ID = frame_count & 1;
    odd_even = (*GS_CSR >> 13) & 1;
    FlushCache(0);
    sceGsSwapDBuff(&db, buffer_ID);
    if (buffer_ID != 0) {
        draw = &db.draw1;
    } else {
        draw = &db.draw0;
    }
    sceGsSetHalfOffset(draw, (short)((float)screen_offset_x + 2048.0f),
                       (short)((float)screen_offset_y + 2048.0f), odd_even == 0);
    tex_ResetVram();
    dl_Swap();
    gsb_SetGsDefault();
}

/* the 768 unit screen the projection proj is scaled to in this build */
static const float vsScreenSize[] = {768.0f, 768.0f, 0.0f, 0.0f}; /* derived name */

/* Build the view matrices from the record gsb_SetVSMatrix fills (vs[0] the
 * zoom, vs[1] and vs[2] the aspect terms, vs[3] and vs[4] the centre, vs[5]
 * and vs[6] the depth range, vs[7] and vs[8] the near and far planes): the
 * screen matrix screen, the perspective projection proj for the 1500 unit
 * screen, the one projHalf for the half size screen, the viewport viewport,
 * and the pair built on a 500 unit screen at matrixptr+0x640 and +0x680.  The 500 unit pair's
 * scale terms are locals of their own. */
static void gsb_SetVSMatrixSub(float *screen, float *proj, float *viewport, float *vs)
{
    float m0[16];
    float sx;
    float sy;
    float zn;
    float zf;

    sx = vs[7] * vsScreenSize[0] / vs[0];
    sy = vs[7] * vsScreenSize[1] / vs[0];

    zn = (-vs[6] * vs[7] + vs[5] * vs[8]) / (-vs[7] + vs[8]);

    zf = vs[8] * vs[7] * (-vs[5] + vs[6]) / (-vs[7] + vs[8]);

    _UnitMatrix(screen);
    screen[0] = vs[0];
    screen[5] = vs[0];
    screen[10] = 0.0f;
    screen[15] = 0.0f;
    screen[14] = 1.0f;
    screen[11] = 1.0f;

    _UnitMatrix(m0);
    /* clang-format off */
    m0[0] = vs[1]; m0[5] = vs[2]; m0[10] = zf;
    m0[12] = vs[3]; m0[13] = vs[4]; m0[14] = zn;
    /* clang-format on */
    _MulMatrix(screen, m0, screen);

    _UnitMatrix(proj);
    proj[0] = (vs[7] + vs[7]) / (sx + sx);
    proj[5] = (vs[7] + vs[7]) / (sy + sy);
    proj[10] = (vs[8] + vs[7]) / (vs[8] - vs[7]);
    proj[14] = vs[8] * vs[7] * -2.0f / (vs[8] - vs[7]);
    proj[11] = 1.0f;
    proj[15] = 0.0f;

    _UnitMatrix(viewport);
    viewport[0] = vs[0] * vs[1] * sx / vs[7];
    viewport[5] = vs[0] * vs[2] * sy / vs[7];
    viewport[10] = (-vs[6] + vs[5]) * 0.5f;
    viewport[12] = vs[3];
    viewport[13] = vs[4];
    viewport[14] = (vs[6] + vs[5]) * 0.5f;
    viewport[15] = 1.0f;
}

/* The view record gsb_SetVSMatrixSub builds the view and screen matrices
 * from: the zoom, the two aspect terms, the centre, and the near and far
 * planes. */
static float vsParam[10]; /* derived name */

/* Set the view and screen matrices for a frame of w by h at depth d: the
 * centre is the screen middle less the staff roll offset, the zoom eases
 * towards its target by a thousandth of the step, and the view record at
 * vsParam carries the centre, the aspect terms and the near and far
 * planes gsb_SetVSMatrixSub builds the matrices from. */
void gsb_SetVSMatrix(int w, int h, float d)
{
    float zoom;

    center_X = center_Y = 2048.0f;
    currentFocusDistance = d;
    vsWidth = w;
    vsHeight = h;
    if (zoomTarget != zoomCurrent) {
        zoomCurrent = zoomCurrent + (zoomTarget - zoomCurrent) * zoomSpeed * 0.001f;
    }
    if (staffRollStartFlag != 0) {
        center_X = center_X - staffRollCenterOffsetX;
    }
    zoom = (float)GlobalStageSetting.viewScale * zoomCurrent * d * (float)ScreenWidth / 640.0f /
           100.0f;
    vsParam[0] = zoom;
    vsParam[3] = center_X;
    vsParam[4] = center_Y;
    vsParam[5] = 1.0f;
    vsParam[6] = 536870880.0f;
    vsParam[1] = (float)w / (float)ScreenWidth;
    vsParam[7] = 2.0f;
    vsParam[8] = 262144.0f;
    vsParam[2] =
        (float)ScreenHeight * 4.0f / ((float)ScreenWidth * 3.0f) * (float)h / (float)ScreenHeight;
    gsb_SetVSMatrixSub((float *)(matrixptr + 0xC0), (float *)(matrixptr + 0x1C0),
                       (float *)(matrixptr + 0x280), vsParam);
}

/* the sign of a, as a factor */
#define SIGN(a) ((a) < 0.0f ? -1.0f : ((a) > 0.0f ? 1.0f : 0.0f)) /* derived name */

/* Clip a box against the current matrix: project its eight corners with the
 * matrix in $vf4 to $vf7 to integer screen coordinates (centred, sign
 * corrected by depth) and test them.  0 when every corner is behind the eye
 * or past one screen edge, -1 when every corner is in front and inside the
 * guard band, 2 when a corner is nearer than 500, else 1; pad 2's 0x200
 * button forces 1. */
int gsb_ClipBox(float *p)
{
    sceVu0IVECTOR v[8];
    int i;

    if (pad[1].now & 0x200) {
        return 1;
    }
    for (i = 0; i < 8; i++, p += 4) {
        __asm__ __volatile__(".set noreorder\n\t"
                             "lqc2 $vf8, 0x0(%0)\n\t"
                             "vmulax.xyzw ACC, $vf4, $vf8x\n\t"
                             "vmadday.xyzw ACC, $vf5, $vf8y\n\t"
                             "vmaddaz.xyzw ACC, $vf6, $vf8z\n\t"
                             "vmaddw.xyzw $vf10, $vf7, $vf8w\n\t"
                             "vdiv Q, $vf0w, $vf10w\n\t"
                             "vwaitq\n\t"
                             "vmulq.xyz $vf10, $vf10, Q\n\t"
                             "vftoi0.xyzw $vf10, $vf10\n\t"
                             "sqc2 $vf10, 0x0(%1)\n\t"
                             ".set reorder"
                             :
                             : "r"(p), "r"(v[i])
                             : "memory");
        v[i][0] -= 2048;
        v[i][1] -= 2048;
        v[i][0] = v[i][0] * SIGN(v[i][2]);
        v[i][1] = v[i][1] * SIGN(v[i][2]);
    }
    if (v[0][3] <= 0 && v[1][3] <= 0 && v[2][3] <= 0 && v[3][3] <= 0 && v[4][3] <= 0 &&
        v[5][3] <= 0 && v[6][3] <= 0 && v[7][3] <= 0) {
        return 0;
    }
    if (v[0][0] < -ScreenWidth / 2 && v[1][0] < -ScreenWidth / 2 && v[2][0] < -ScreenWidth / 2 &&
        v[3][0] < -ScreenWidth / 2 && v[4][0] < -ScreenWidth / 2 && v[5][0] < -ScreenWidth / 2 &&
        v[6][0] < -ScreenWidth / 2 && v[7][0] < -ScreenWidth / 2) {
        return 0;
    }
    if (v[0][0] > ScreenWidth / 2 && v[1][0] > ScreenWidth / 2 && v[2][0] > ScreenWidth / 2 &&
        v[3][0] > ScreenWidth / 2 && v[4][0] > ScreenWidth / 2 && v[5][0] > ScreenWidth / 2 &&
        v[6][0] > ScreenWidth / 2 && v[7][0] > ScreenWidth / 2) {
        return 0;
    }
    if (v[0][1] < -ScreenHeight / 2 && v[1][1] < -ScreenHeight / 2 && v[2][1] < -ScreenHeight / 2 &&
        v[3][1] < -ScreenHeight / 2 && v[4][1] < -ScreenHeight / 2 && v[5][1] < -ScreenHeight / 2 &&
        v[6][1] < -ScreenHeight / 2 && v[7][1] < -ScreenHeight / 2) {
        return 0;
    }
    if (v[0][1] > ScreenHeight / 2 && v[1][1] > ScreenHeight / 2 && v[2][1] > ScreenHeight / 2 &&
        v[3][1] > ScreenHeight / 2 && v[4][1] > ScreenHeight / 2 && v[5][1] > ScreenHeight / 2 &&
        v[6][1] > ScreenHeight / 2 && v[7][1] > ScreenHeight / 2) {
        return 0;
    }
    if (v[0][3] > 0 && v[1][3] > 0 && v[2][3] > 0 && v[3][3] > 0 && v[4][3] > 0 && v[5][3] > 0 &&
        v[6][3] > 0 && v[7][3] > 0 && v[0][0] >= -2048 && v[1][0] >= -2048 && v[2][0] >= -2048 &&
        v[3][0] >= -2048 && v[4][0] >= -2048 && v[5][0] >= -2048 && v[6][0] >= -2048 &&
        v[7][0] >= -2048 && v[0][0] <= 2048 && v[1][0] <= 2048 && v[2][0] <= 2048 &&
        v[3][0] <= 2048 && v[4][0] <= 2048 && v[5][0] <= 2048 && v[6][0] <= 2048 &&
        v[7][0] <= 2048 && v[0][1] >= -2048 && v[1][1] >= -2048 && v[2][1] >= -2048 &&
        v[3][1] >= -2048 && v[4][1] >= -2048 && v[5][1] >= -2048 && v[6][1] >= -2048 &&
        v[7][1] >= -2048 && v[0][1] <= 2048 && v[1][1] <= 2048 && v[2][1] <= 2048 &&
        v[3][1] <= 2048 && v[4][1] <= 2048 && v[5][1] <= 2048 && v[6][1] <= 2048 &&
        v[7][1] <= 2048) {
        return -1;
    }
    if (v[0][3] < 500 || v[1][3] < 500 || v[2][3] < 500 || v[3][3] < 500 || v[4][3] < 500 ||
        v[5][3] < 500 || v[6][3] < 500 || v[7][3] < 500) {
        return 2;
    }
    return 1;
}

inline int gsb_LoadStageSettings(void)
{
    char buf[256];
    int fd;
    sprintf(buf, "object/stagesetting/%s.ssb", stageData[stage_no].key2);
    fd = debugSceOpen(buf, 1);
    if (fd < 0) {
        debug_StdPrintfDummy("gsb_LoadStageSettings: host file open error.\n");
    } else {
        debug_StdPrintfDummy("Load stage settings file. %s\n", buf);
        sceRead(fd, &GlobalStageSetting, 0x130);
        debugSceClose(fd);
    }
    return -1;
}

inline int gsb_SaveStageSettings(void)
{
    char buf[256];
    int fd;
    sprintf(buf, "object/stagesetting/%s.ssb", stageData[stage_no].key2);
    fd = debugSceOpen(buf, 0x602);
    if (fd < 0) {
        debug_StdPrintfDummy("gsb_SaveStageSettings: host file open error.\n");
    } else {
        sceWrite(fd, &GlobalStageSetting, 0x130);
        debug_StdPrintfDummy("Save stage settings file. %s\n", buf);
        debugSceClose(fd);
    }
    return -1;
}

/* one row of the stage setting page: a label, the word it edits, its
   range, its default and its step, and the callback to run once the value
   has moved. */
typedef struct GsbToolItem { /* field names derived */
    char *name;              /* 0x00 */
    void *val;               /* 0x04 */
    int min;                 /* 0x08 */
    int max;                 /* 0x0C */
    int def;                 /* 0x10 */
    int step;                /* 0x14 */
    int (*fn)();             /* 0x18 */
} GsbToolItem;               /* derived name */

/* the seventeen rows of the stage setting page, each naming a word of the
   stage record */
static const GsbToolItem stageSettingItems[] = {
    /* derived name */
    {" HighLight Color R   ", &GlobalStageSetting.reductionCol[0], 0, 255, 128, 1, 0},
    {" HighLight Color G   ", &GlobalStageSetting.reductionCol[1], 0, 255, 128, 1, 0},
    {" HighLight Color B   ", &GlobalStageSetting.reductionCol[2], 0, 255, 128, 1, 0},
    {" Zoom Offset         ", &GlobalStageSetting.viewScale, 50, 400, 100, 1, 0},
    {" Def Tex Sample Mode ", &GlobalStageSetting.texSampleMode, 0, 5, 5, 1,
     tex_RemakeRegistersSampleMin},
    {" Post Effect         ", &GlobalStageSetting.postEffect, 0, 8, 0, 1, 0},
    {" Feedback Effect     ", &GlobalStageSetting.feedbackEffect, 0, 3, 0, 1, 0},
    {" Feedback Effect R   ", &GlobalStageSetting.feedbackCol[0], 0, 255, 0, 1, 0},
    {" Feedback Effect G   ", &GlobalStageSetting.feedbackCol[1], 0, 255, 0, 1, 0},
    {" Feedback Effect B   ", &GlobalStageSetting.feedbackCol[2], 0, 255, 0, 1, 0},
    {" Feedback Effect A   ", &GlobalStageSetting.feedbackCol[3], 0, 255, 0, 1, 0},
    {" DepthField Level    ", &GlobalStageSetting.depthFieldLevel, 0, 1000, 100, 1, 0},
    {" DepthField Start    ", &GlobalStageSetting.depthFieldStart, 0, 20000, 2000, 20, 0},
    {" DepthField Width    ", &GlobalStageSetting.depthFieldWidth, 0, 20000, 10000, 20, 0},
    {" Motion Blur         ", &GlobalStageSetting.motionBlur, 0, 127, 32, 1, 0},
    {" AntiLevel0          ", &GlobalStageSetting.antiLevel0, 0, 255, 24, 1, 0},
    {" AntiLevel1          ", &GlobalStageSetting.antiLevel1, 0, 255, 24, 1, 0},
};

/* the unselected and selected row colours */
static const unsigned int stageSettingRowColor[] = {0xFFFFFF00, 0xFF000000}; /* derived name */

/* the word a boolean row prints */
static char *stageSettingOnOffText[] = {"Off", "On"}; /* derived name */

static int stageSettingRow = 0; /* derived name */ /* the highlighted row */

/* The stage setting page of the debug menu: seventeen editable words of the
 * stage record, the pad keys that walk and change them, and the key that dumps
 * the page to the log. */
int gsb_StageSettingTool(void)
{
    int i;
    int ret = 0;

    debug_PrintfDummy(10, 50, 0xFF800000, "StageSetting Tool");

    for (i = 0; i < 17; i++) {
        if (stageSettingItems[i].min == 0 && stageSettingItems[i].max == 1) {
            debug_PrintfDummy(18, (i + 1) * 8 + 50,
                              stageSettingRowColor[(stageSettingRow == i) ? 1 : 0], "%s : %s",
                              stageSettingItems[i].name,
                              stageSettingOnOffText[*(int *)stageSettingItems[i].val]);
        } else {
            debug_PrintfDummy(18, (i + 1) * 8 + 50,
                              stageSettingRowColor[(stageSettingRow == i) ? 1 : 0], "%s : %d",
                              stageSettingItems[i].name, *(int *)stageSettingItems[i].val);
        }
    }

    if (pad[0].rep & 0x4000) {
        if (++stageSettingRow >= 17) {
            stageSettingRow = 0;
        }
    }
    if (pad[0].rep & 0x1000) {
        if (--stageSettingRow < 0) {
            stageSettingRow = 16;
        }
    }
    if (pad[0].rep & 0x2000) {
        int v = *(int *)stageSettingItems[stageSettingRow].val +
                stageSettingItems[stageSettingRow].step;

        *(int *)stageSettingItems[stageSettingRow].val = v;
        if (stageSettingItems[stageSettingRow].max < v) {
            *(int *)stageSettingItems[stageSettingRow].val = stageSettingItems[stageSettingRow].min;
        }
        if (stageSettingItems[stageSettingRow].fn != 0) {
            stageSettingItems[stageSettingRow].fn(0);
        }
    }
    if (pad[0].rep & 0x8000) {
        int v = *(int *)stageSettingItems[stageSettingRow].val -
                stageSettingItems[stageSettingRow].step;

        *(int *)stageSettingItems[stageSettingRow].val = v;
        if (v < stageSettingItems[stageSettingRow].min) {
            *(int *)stageSettingItems[stageSettingRow].val = stageSettingItems[stageSettingRow].max;
        }
        if (stageSettingItems[stageSettingRow].fn != 0) {
            stageSettingItems[stageSettingRow].fn(0);
        }
    }
    if (pad[0].flags & 0x10) {
        *(int *)stageSettingItems[stageSettingRow].val = stageSettingItems[stageSettingRow].def;
    }
    if (pad[0].flags & 0x20) {
        for (i = 0; i < 17; i++) {
            if (stageSettingItems[i].min == 0 && stageSettingItems[i].max == 1) {
                debug_StdPrintfDummy("StageSetting %s => %s\n", stageSettingItems[i].name,
                                     stageSettingOnOffText[*(int *)stageSettingItems[i].val]);
            } else {
                debug_StdPrintfDummy("StageSetting %s => %d\n", stageSettingItems[i].name,
                                     *(int *)stageSettingItems[i].val);
            }
        }
        ret = 1;
    }
    if (pad[0].flags & 0x40) {
        ret = -1;
    }
    if (ret != 0) {
        stageSettingRow = 0;
    }
    return ret;
}

typedef struct { /* field names derived */
    char *name;  /* 0x0 */
    int (*fn)(); /* 0x4 */
} GsbMenuItem;   /* derived name */

/* The background colour the display list is cleared to, one component per
 * word of an integer quadword: gsb_SetBGColor writes the four words and
 * gsb_GetBGColor reads them back as bytes. */
static sceVu0IVECTOR bgColor; /* derived name */

static GsbMenuItem stageSettingMenu[] = {
    {"Light Tool", light_Tool},
    {"Shadow Tool", shadow_Tool},
    {"Fog Tool", fog_FogTool},
    {"Other Settings", gsb_StageSettingTool},
    {"Load Settings", gsb_LoadStageSettings},
    {"Save Settings", gsb_SaveStageSettings},
}; /* derived name */

/* the unselected and selected row colours, as stageSettingRowColor */
static const unsigned int menuRowColor[] = {0xFFFFFF00, 0xFF000000}; /* derived name */

/* the menu row under the cursor and the page it opened, -1 for none */
static int menuCursor = 0; /* derived name */

static int menuSelected = -1; /* derived name */

int gsb_StageSetting(void)
{
    int i;
    if (menuSelected >= 0) {
        if (stageSettingMenu[menuSelected].fn != 0) {
            int r = stageSettingMenu[menuSelected].fn(0);
            if (r == -1) {
                menuSelected = r;
            }
            return 0;
        }
    }
    for (i = 0; i < 6; i++) {
        debug_PrintfDummy(18, (i + 1) * 8 + 50, menuRowColor[(menuCursor == i) ? 1 : 0], "%s",
                          stageSettingMenu[i].name);
    }
    if (pad[0].rep & 0x4000) {
        menuCursor++;
        if (menuCursor >= 6)
            menuCursor = 0;
    }
    if (pad[0].rep & 0x1000) {
        menuCursor--;
        if (menuCursor < 0)
            menuCursor = 5;
    }
    if (pad[0].flags & 0x20) {
        menuSelected = menuCursor;
    }
    return (pad[0].flags & 0x40) ? -1 : 0;
}

inline void gsb_SetBGColor(void *db, int r, int g, int b)
{
    unsigned long long bg = ((long long)b << 16) | ((long long)g << 8);
    unsigned long long v = r | 0x3F80000000000000ULL;
    v |= bg;
    bgColor[0] = r;
    v |= 0x80000000;
    bgColor[1] = g;
    bgColor[2] = b;
    bgColor[3] = 0x80;
    *(unsigned long long *)((char *)db + 0x1F0) = v;
    *(unsigned long long *)((char *)db + 0x100) = v;
}

inline void gsb_GetBGColor(unsigned char *col)
{
    col[0] = bgColor[0];
    col[1] = bgColor[1];
    col[2] = bgColor[2];
    col[3] = bgColor[3];
}

inline void gsb_SetZoom(float target, float speed)
{
    zoomTarget = target;
    zoomSpeed = speed;
}
