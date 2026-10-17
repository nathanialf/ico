#include "staticBlur.h"
#include "debug.h"
#include "Primitive.h"
#include "Texture.h"
#include <string.h>
#include <libvu0.h>
#include <stdio.h>
#include "GsBase.h"
#include "main.h"
#include "Matrix.h"
#include "include_asm.h"

static void blur(int n, void *col);

/* workBase: the GS block addresses of the work buffers Work0..Work3 the pass
   names use (FullScreenEffectBefore rewrites them).  sunScreen: calcSun's
   projected sun, integer screen coordinates.  sunView: the sun direction in
   view space, its z the in-front test.  sunDir: the world sun direction
   GetSunWorldPos hands out.  sunScreenOffset: the drawing-offset correction
   calcSun adds after the projection.  The int[4] runs are sprite rectangles
   in 12.4 fixed point and the float[4] points get their z written before the
   projection that yields a Z value. */
static int workBase[4] = {0x2800, 0x2C00, 0x3000, 0x3400}; /* derived name */

static int sunScreen[4] = {0, 0, 0, 0}; /* derived name */

static float sunView[4] = {0.0f, 0.0f, 0.0f, 1.0f}; /* derived name */

static float sunDir[4] = {1.0f, -1.5f, -1.0f, 1.0f}; /* derived name */

static float sunScreenOffset[4] = {-2048.0f, -2048.0f, 0.0f, 0.0f}; /* derived name */

static int work0ToFeedBackRect[4] = {-1024, -1024, 2048, 2048}; /* derived name */

/* three more rectangles auraInspireAfter copies through */
INCLUDE_ASM(D_004E66A0);

static int feedBackToWork0Rect[4] = {-1024, -1024, 2048, 2048}; /* derived name */

static float subWork1Point[4] = {0.0f, 0.0f, 0.0f, 1.0f}; /* derived name */

static int eyeGhostRect[4] = {-2048, -1024, 4096, 2048}; /* derived name */

static int eyeShrinkRect[4] = {-2048, -1024, 1024, 512}; /* derived name */

static int eyeTintRect[4] = {-2048, -1024, 4096, 2048}; /* derived name */

static int copyToWorkRect[4] = {-2044, -2044, 4096, 4096}; /* derived name */

static float pasteToFBPoint[4] = {0.0f, 0.0f, 0.0f, 1.0f}; /* derived name */

/* as in GifPacket.h, which this file does not include */
extern void gif_EndPacket(void);
/* void (int, int, int) here, void (long long, long long, long long) in GifPacket.h */
extern void gif_SetAlpha(int alpha, int mode, int fix);
/* void (int, int, int, int, int, int) here, void (unsigned long long, unsigned long long, unsigned int, unsigned int, int, int) in GifPacket.h */
extern void gif_SetDrawEnviroment(int fbp, int psm, int w, int h, int useoffset, int clear);
/* void (int, long long) here, void (long long, long long) in GifPacket.h */
extern void gif_SetGsReg(int reg, long long data);
/* as in GifPacket.h, which this file does not include */
extern void gif_SetZTest(int on);
/* as in GifPacket.h, which this file does not include */
extern void gif_SetZWrite(int on);
/* void (void *, unsigned int, void *, void *, int) here, void (int *, long long, int *, unsigned char *, int) in GifPacket.h */
extern void gif_SpriteSensitiveOrg(void *r, unsigned int z, void *uv, void *col, int prim);
/* as in GifPacket.h, which this file does not include */
extern void gif_StartPacketPri(int pri);

typedef struct { /* field names derived */
    int x, y, w, h;
} SprUV; /* derived name */

typedef struct { /* field names derived */
    unsigned char f[4];
} SprCol; /* derived name */

/* the texture rectangle of a whole 256x128 work buffer, half a texel in
   from each edge, read by eyeBlur and pasteFullScreenFlare */
static const SprUV workBufferUv = {8, 8, 4088, 2040}; /* derived name */

/* The post effect and aura feed modes FullScreenEffect* dispatch on and the
   requests the stage parameters make, the flare switch, the two sun fans,
   the sun switch, the depth fade start and width, the aura subtraction depth,
   then the sprite colours of the passes. */
static int postMode = 1; /* derived name */

static int postModeRequest = 1; /* derived name */

/* 0 in this build's .sdata */
static int flareOn = 0; /* derived name */

static int feedMode = 2; /* derived name */

static int feedModeRequest = 0; /* derived name */

static Fan2D *sunGlowFan = 0; /* derived name */

static Fan2D *sunCoreFan = 0; /* derived name */

static int sunOn = 0; /* derived name */

static float depthFadeStart = 100.0f; /* derived name */

static float depthFadeWidth = 400.0f; /* derived name */

static float auraInspireZ = 200.0f; /* derived name */

static SprCol blurPassCol = {{128, 128, 128, 0}}; /* derived name */

static SprCol clearCol = {{0, 0, 0, 0}}; /* derived name */

static SprCol fillZCol = {{0, 0, 0, 192}}; /* derived name */

static SprCol alphaCopyCol = {{0, 0, 0, 128}}; /* derived name */

static SprCol whiteCol = {{128, 128, 128, 128}}; /* derived name */

static SprCol flareCol = {{139, 136, 132, 40}}; /* derived name */

static SprCol auraClearCol = {{0, 0, 0, 0}}; /* derived name */

/* One pass of the blur, inlined twice into blur: the buffer fb drawn from
 * the texture buffer tex as one sprite, the sprite rect or the texture rect
 * shrunk by rm or um. */
static inline void blurPass(int fb, int tex, int rm, int um, void *col) /* derived name */
{
    gif_SetDrawEnviroment(fb, 0, 256, 128, 0, 0);

    gif_SetGsReg(6, tex | 0x20010000 | 0x15C0000000LL);
    gif_SetGsReg(0x14, 0x60);
    gif_SetGsReg(8, 5);
    gif_SetAlpha(1, 4, 0);
    {
        int rect[4] = {-2048, -1024, 4096 - rm, 2048 - rm};
        int uv[4] = {8, 8, 4096 - um, 2048 - um};

        gif_SpriteSensitiveOrg(rect, 0, uv, col, 0);
    }
}

/* the first pass shrinks the sprite by n + 6 in the blur colour, the second
 * shrinks the texture back in the caller's colour */
INCLUDE_ASM(blur);

static void auraInspireBefore(void)
{
    int rect[4] = {-ScreenWidth / 2 * 16, -ScreenHeight / 2 * 16, ScreenWidth * 16,
                   ScreenHeight * 16};

    gif_StartPacketPri(8);
    gif_SetGsReg(8, 5);

    gif_SetDrawEnviroment(workBase[1], 0, ScreenWidth, ScreenHeight, 0, 0);

    gif_SetZTest(0);
    gif_SetZWrite(0);

    gif_SetAlpha(0, 2, 0);
    gif_SpriteSensitiveOrg(rect, 0, (void *)0, &auraClearCol, 0);

    gif_SetZWrite(1);
    gif_SetZTest(1);

    gif_SetAlpha(1, 7, 0);
    gif_SetDrawEnviroment(workBase[1], 0, ScreenWidth, ScreenHeight, 0, 0);

    gif_SetGsReg(8, 5);
    gif_SetGsReg(0x4A, 0);
    gif_EndPacket();
}

INCLUDE_ASM(blendWork0ToWork1_35_staticBlur);

INCLUDE_ASM(parallelAddFeedBackAreaToWork0_43_staticBlur);

INCLUDE_ASM(blurBlendFeedBackAreaToWork1_31_staticBlur);

INCLUDE_ASM(testAA_63_staticBlur);

INCLUDE_ASM(subWork1ToCurrentFB_75_staticBlur);

/* This build keeps no blur-sprite coordinate block in .bss (no function of
   the demo addresses one). */

/* the blur sprite's RGBA */
static SprCol blurCol; /* derived name */

INCLUDE_ASM(auraInspireAfter);

INCLUDE_ASM(cleanUpFB_82_staticBlur);

INCLUDE_ASM(fillWork2_86_staticBlur);

INCLUDE_ASM(dispSun_90_staticBlur);

INCLUDE_ASM(pasteBackLightShadowToFB_94_staticBlur);

INCLUDE_ASM(makeMaskPatternToWork2_98_staticBlur);

INCLUDE_ASM(makeFullScreenFlareBefore);

INCLUDE_ASM(reduceWork2ToWork0_105_staticBlur);

INCLUDE_ASM(eyeBlur_109_staticBlur);

INCLUDE_ASM(makeFullScreenFlareAfter);

static void pasteFullScreenFlare(void)
{
    int rect[4] = {-ScreenWidth / 2 * 16, -ScreenHeight / 2 * 16, ScreenWidth * 16,
                   ScreenHeight * 16};
    SprUV uv;
    SprCol col;

    gif_StartPacketPri(7);

    gif_SetGsReg(6, workBase[3] | 0x20010000 | 0x5C0000000LL);

    gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 0, 0);

    gif_SetZTest(0);
    gif_SetZWrite(0);
    gif_SetAlpha(1, 0, 128);

    uv = workBufferUv;
    col = (SprCol){{128, 128, 128, 128}};
    gif_SpriteSensitiveOrg(rect, 0, &uv, &col, 1);

    gif_SetZWrite(1);
    gif_SetGsReg(0x47, 0x5000D);

    gif_EndPacket();
}

static int eyeBlurAlpha = 150; /* derived name */

INCLUDE_ASM(copyToWork_126_staticBlur);

INCLUDE_ASM(copyToWork2_130_staticBlur);

INCLUDE_ASM(pasteToFB_134_staticBlur);

static SprCol copyToWorkCol = {{128, 128, 128, 0}}; /* derived name */

static SprCol copyToWork2Col = {{128, 128, 128, 0}}; /* derived name */

static SprCol pasteToFBCol = {{128, 128, 128, 128}}; /* derived name */

static SprCol depthPassCol = {{128, 128, 128, 0}}; /* derived name */

/* One blend pass of the depth-of-field chain: shrink the work buffer named by
   `n` into its twin, taking the previous pass's shrink (`pre`) as the source
   rectangle and this pass's (`cur`) as the destination. */
static inline int depthFieldPass(int n, int cur, int pre) /* derived name */
{
    int tex = workBase[n];

    gif_SetDrawEnviroment(workBase[1 - n], 0, 256, 128, 0, 0);
    gif_SetGsReg(6, tex | 0x20010000 | 0x15C0000000LL);

    if (pre < cur) {
        gif_SetGsReg(0x14, 0x40);
    } else {
        gif_SetGsReg(0x14, 0x20);
    }
    gif_SetGsReg(8, 5);
    gif_SetAlpha(1, 4, 0);

    {
        int rect[4] = {-2032, -1008, 4064 - cur, 2016 - cur};
        int uv[4] = {24, 24, 4064 - pre, 2016 - pre};

        gif_SpriteSensitiveOrg(rect, 0, uv, &depthPassCol, 0);
    }
    return cur;
}

INCLUDE_ASM(depthField);

void GetSunWorldPos(float *pos)
{
    _NormalizeVector(pos, sunDir);
}

static int motionBlurAlpha = 0; /* derived name */

INCLUDE_ASM_LIT(blendWork0ToWork1_35_staticBlur);

INCLUDE_ASM_LIT(blurBlendFeedBackAreaToWork1_31_staticBlur);

INCLUDE_ASM_LIT(reduceWork2ToWork0_105_staticBlur);

INCLUDE_ASM_LIT(eyeBlur_109_staticBlur);

INCLUDE_ASM_LIT(copyToWork2_130_staticBlur);

void MotionBlur(void)
{
    SprCol col = {{128, 128, 128, 128}};
    SprUV uv = {4, 4, ScreenWidth * 16, ScreenHeight / 2 * 16};
    SprUV rect = {-ScreenWidth / 2 * 16 - 4, -ScreenHeight / 2 * 16 - 4, ScreenWidth * 16,
                  ScreenHeight * 16};

    if (motionBlurAlpha == 0) {
        return;
    }
    if (currentScreenWidth != 0) {
        return;
    }
    if (debug_font_flag & 1) {
        debug_Printf(300, 40, 0xFFFFFF00, "MBLUR %d", motionBlurAlpha);
    }

    gif_StartPacketPri(7);

    gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 0, 0);

    gif_SetGsReg(6, ((long long)(ScreenWidth / 64) << 14) | 0x664100000LL);
    gif_SetGsReg(0x3B, 0x8000000080LL);
    gif_SetGsReg(0x47, 0x3000C);

    gif_SetZWrite(0);
    gif_SetAlpha(1, 2, motionBlurAlpha);
    gif_SpriteSensitiveOrg(&rect, -1, &uv, &col, 1);
    gif_SetZWrite(1);

    gif_SetGsReg(0x47, 0x5000D);
    gif_EndPacket();
}

INCLUDE_ASM(calcSun);

static int colorSettingItem = 0; /* derived name */

/* one step of colorSetting, inlined at all four switch arms */
static inline void colorSettingStep(unsigned char *p, int d) /* derived name */
{
    int v = *p;

    v += d;
    if (v < 0) {
        v = 0;
    }
    if (v > 255) {
        v = 255;
    }
    *p = v;
}

static void colorSetting(void)
{
    char buf[256];
    int f = pad[1].rep;
    int d;

    if (f & 0x1000) {
        colorSettingItem--;
    }
    if (f & 0x4000) {
        colorSettingItem++;
    }
    if (colorSettingItem >= 4) {
        colorSettingItem = 0;
    }
    if (colorSettingItem < 0) {
        colorSettingItem = 3;
    }
    d = 0;
    if (f & 0x2000) {
        d = 1;
    }
    if (f & 0x8000) {
        d = -1;
    }

    switch (colorSettingItem) {
    case 0:
    default:
        sprintf(buf, "BLUR R: %d", flareCol.f[0]);
        colorSettingStep(&flareCol.f[0], d);
        break;
    case 1:
        sprintf(buf, "BLUR G: %d", flareCol.f[1]);
        colorSettingStep(&flareCol.f[1], d);
        break;
    case 2:
        sprintf(buf, "BLUR B: %d", flareCol.f[2]);
        colorSettingStep(&flareCol.f[2], d);
        break;
    case 3:
        sprintf(buf, "BLUR BASE: %d", flareCol.f[3]);
        colorSettingStep(&flareCol.f[3], d);
        break;
    }
    if (debug_font_flag & 1) {
        debug_Printf(440, 40, 0xFFFFFF00, buf);
    }
}

static int postInfoTimer = 0; /* derived name */

static int postInfoLast = -1; /* derived name */

static void dispPostInfo(void)
{
    char buf[256];

    if (postInfoLast != postMode) {
        postInfoTimer = 0;
    }
    postInfoLast = postMode;
    if (postInfoTimer < 60) {
        postInfoTimer++;
    }
    if (((postInfoTimer >> 1) & 1) == 0) {
        switch (postMode) {
        case 0:
            sprintf(buf, "NOEFFECT");
            break;
        case 1:
            sprintf(buf, "SBLUR");
            break;
        case 2:
            sprintf(buf, "DEPTH");
            break;
        case 3:
            sprintf(buf, "SBLUR+DEPTH");
            break;
        case 4:
            sprintf(buf, "GLOW");
            break;
        case 5:
            sprintf(buf, "GLOW+DEPTH");
            break;
        case 6:
            sprintf(buf, "BLSBLUR");
            break;
        case 7:
            sprintf(buf, "BLSBLUR+DEPTH");
            break;
        case 8:
            sprintf(buf, "NO ACTION");
            break;
        }
        if (debug_font_flag & 1) {
            debug_Printf(440, 20, 0xFFFFFF00, "BLUR: %s", buf);
        }
    }
}

static int feedInfoTimer = 0; /* derived name */

static int feedInfoLast = -1; /* derived name */

static void dispFeedInfo(void)
{
    char buf[256];

    if (feedInfoLast != feedMode) {
        feedInfoTimer = 0;
    }
    feedInfoLast = feedMode;
    if (feedInfoTimer < 60) {
        feedInfoTimer++;
    }
    if (((feedInfoTimer >> 1) & 1) == 0) {
        switch (feedMode) {
        default:
            sprintf(buf, "NOEFFECT");
            break;
        case 1:
            sprintf(buf, "AURA");
            break;
        case 2:
            sprintf(buf, "MIRAGE");
            break;
        case 3:
            sprintf(buf, "AURA V2");
            break;
        }
        if (debug_font_flag & 1) {
            debug_Printf(440, 30, 0xFFFFFF00, "FEED: %s", buf);
        }
    }
}

INCLUDE_ASM(FullScreenEffectBefore);

INCLUDE_ASM(FullScreenEffectAfter);

/* declared here: matrixDrive.h is not included */
extern float ZeroPoint[4];
extern void CopyVector(float *dst, float *src);

/* a file-static copy of _initStaticBlur, which InitStaticBlur inlines;
   _initStaticBlur keeps its own body, which holds 80.0f across both calls */
static inline void initStaticBlur(void) /* derived name */
{
    sunGlowFan = prim_InitFan2D(16, 80.0f, ZeroPoint, 0xFFFFFF80u, 0);
    sunCoreFan = prim_InitFan2D(16, 80.0f, ZeroPoint, 0xFFFFFF80u, 0);
}

/* No caller exists.  The binary copies sunDir from a1 as it arrives, so the
   direction is the second parameter; a0 is not read. */
int InitStaticBlur(int unused, float *dir)
{
    CopyVector(sunDir, dir);
    sunDir[3] = 0;
    initStaticBlur();
    sunOn = 1;
    return 0;
}

void StaticBlur(void) {}

void StaticBlurDL(void) {}

void SetMotionBlur(int val)
{
    motionBlurAlpha = val;
}

void SetStaticBlur(int x)
{
    GlobalStageSetting.postEffect = x;
}

void SetDepthFadeParam(float start, float width, int level)
{
    GlobalStageSetting.depthFieldStart = (int)start;
    GlobalStageSetting.depthFieldWidth = (int)width;
    GlobalStageSetting.depthFieldLevel = level;
}

void SetAuraInspireParam(float z)
{
    auraInspireZ = z;
}

void InitializeStaticBlur(void)
{
    sunOn = 0;
}

void _initStaticBlur(void)
{
    sunGlowFan = prim_InitFan2D(16, 80.0f, ZeroPoint, 0xFFFFFF80u, 0);
    sunCoreFan = prim_InitFan2D(16, 80.0f, ZeroPoint, 0xFFFFFF80u, 0);
}

void SetAuraEffect(void) {}
