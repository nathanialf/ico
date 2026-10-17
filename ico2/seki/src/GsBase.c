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
#include "include_asm.h"

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
INCLUDE_ASM(gsb_Init);

/* A frame buffer clear packet for the whole screen, 48 doublewords: a GIF tag
   of 23 A+D writes and the register pairs.  Nothing reads it: the send that
   copied it is gone from the retail body. */
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
INCLUDE_ASM(gsb_Reduction);

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
INCLUDE_ASM(gsb_KeepFrameBuffer);

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
INCLUDE_ASM(gsb_fade);

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
INCLUDE_ASM(gsb_scissorOnDemo);

/* void (int, int, int) here, void (long long, long long, long long) in GifPacket.h */
extern void gif_SetAlpha(int alpha, int mode, int fix);
/* void (int, int, int, int, unsigned int, unsigned char *, int) here, void (int, int, int, int, long long, GifColor *, int) in GifPacket.h */
extern void gif_MakeSpriteNoTexture(int x, int y, int w, int h, unsigned int z, unsigned char *col,
                                    int prim);

/* Darken the whole frame by the stage record's brightness step: a full screen
 * white sprite in destination-alpha blend whose alpha is the step, clamped to
 * 0 to 15 and skipped at 0. */
INCLUDE_ASM(gsb_controlBrightness);

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
INCLUDE_ASM(gsb_antiAlias);

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

INCLUDE_ASM(gsb_setSemitransReg);

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

/* Build the frame's common matrix packet: the three view matrices the stage
 * needs, the inverse of the view, and the display list that uploads them to
 * VU memory, opened once for each of the thirteen list priorities. */
INCLUDE_ASM(gsb_MakeCommonMatrix);

/* Open the frame's first display list: one DMA tag, the two VIF words that
 * hand path 1 to the GS, a second tag for the register run, and then the
 * default register set for each of the thirteen contexts. */
static void gsb_SetGsDefault(void);

INCLUDE_ASM(gsb_SetGsDefault);

/* Lay the film grain texture over the frame: the noise texture at texture
 * slot 10, drawn as one full screen sprite whose colour comes from the
 * stage record's grain tint for this target and whose UV step is the
 * record's grain scale, passed as raw bits in both halves of the register. */
static void gsb_filmNoise(void);

/* set by gsb_UpdateGSSystem once the frame is up, tested by gsb_PostEffect */
static int postEffectReady = 0; /* derived name */

/* Everything the frame still owes after the scene is drawn: the debug read
 * outs, the full screen effect, the shadow and fog passes, the motion blur,
 * the anti alias pass, the film grain and the brightness step, the kept frame
 * buffer, the staff roll and last the fade and the demo scissor. */
INCLUDE_ASM(gsb_PostEffect);

/* gsb_InitGSSystem's first call brings every module up */
static int firstGsInit = 1; /* derived name */

INCLUDE_ASM(gsb_InitGSSystem);

/* the frames gsb_SyncGSSystem has waited on the GS */
static int syncRetry = 0; /* derived name */

INCLUDE_ASM_LIT(gsb_SyncGSSystem);

/* One frame boundary: take the field parity from the GS CSR, run the
 * reduction pass, flip the double buffer and hand the display list back
 * either swapped or cleared, then reopen the frame's register set. */
INCLUDE_ASM(gsb_UpdateGSSystem);

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
INCLUDE_ASM(gsb_SetVSMatrixSub);

/* The view record gsb_SetVSMatrixSub builds the view and screen matrices
 * from: the zoom, the two aspect terms, the centre, and the near and far
 * planes. */
static float vsParam[10]; /* derived name */

/* Set the view and screen matrices for a frame of w by h at depth d: the
 * centre is the screen middle less the staff roll offset, the zoom eases
 * towards its target by a thousandth of the step, and the view record at
 * vsParam carries the centre, the aspect terms and the near and far
 * planes gsb_SetVSMatrixSub builds the matrices from. */
INCLUDE_ASM(gsb_SetVSMatrix);

/* Clip a box against the current matrix: transform its eight corners with the
 * matrix in $vf4 to $vf7 and read the clip flags out of $vi18.  All eight
 * corners outside one plane gives 0, no corner clipped at all gives -1, and
 * the second pass re-clips against a 0.99 w so a corner that only just crosses
 * the near plane still counts as visible: 2 when it does, 1 when it does not. */
INCLUDE_ASM(gsb_ClipBox);

inline int gsb_LoadStageSettings(void);

INCLUDE_ASM_LIT(gsb_LoadStageSettings);

inline int gsb_SaveStageSettings(void);

INCLUDE_ASM_LIT(gsb_SaveStageSettings);

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

INCLUDE_ASM(gsb_SetBGColor);

INCLUDE_ASM(gsb_GetBGColor);

INCLUDE_ASM(gsb_SetZoom);

INCLUDE_ASM(gsb_SyncGSSystem);

INCLUDE_ASM(gsb_LoadStageSettings);

INCLUDE_ASM(gsb_SaveStageSettings);

INCLUDE_ASM(gsb_ClearFrameBuffer);
