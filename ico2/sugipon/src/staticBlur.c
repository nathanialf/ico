#include "staticBlur.h"
#include "debug.h"
#include "Primitive.h"
#include "Texture.h"
#include <string.h>
#include <libvu0.h>
#include <stdio.h>
#include "GsBase.h"

struct D275 {
    char pad[0xE8];
    int field_E8;
    int field_EC;
    int field_F0;
    int field_F4;
    int field_F8;
    char pad2[0x104 - 0xFC];
    int field_104;
    char pad3[0x110 - 0x108];
    int field_110;
    int field_114;
    int field_118;
    int field_11C;
};

/* .data, owned by staticBlur.o and reached only from this file (MAIN.MAP line
   5986 gives the member, 0x100 in its link, and names no symbol in the run):
   the TU's whole run in ROM order, 0x4ED020..0x4ED0F0, 208 B.  The names are
   ours.  workBase: the GS block addresses of the work buffers Work0..Work3 the
   pass names use (FullScreenEffectBefore rewrites them).  sunScreen: calcSun's
   projected sun, integer screen coordinates.  sunView: the sun direction in
   view space, its z the in-front test.  sunDir: the world sun direction
   GetSunWorldPos hands out.  sunScreenOffset: the drawing-offset correction
   calcSun adds after the projection.  The int[4] runs are sprite rectangles
   in 12.4 fixed point and the float[4] points get their z written before the
   projection that yields a Z value. */
static int workBase[4] = {0x2800, 0x2C00, 0x3000, 0x3400};

static int sunScreen[4] = {0, 0, 0, 0};

static float sunView[4] = {0.0f, 0.0f, 0.0f, 1.0f};

static float sunDir[4] = {1.0f, -1.5f, -1.0f, 1.0f};

static float sunScreenOffset[4] = {-2048.0f, -2048.0f, 0.0f, 0.0f};

static int work0ToFeedBackRect[4] = {-1024, -1024, 2048, 2048};

static int feedBackToWork0Rect[4] = {-1024, -1024, 2048, 2048};

static float subWork1Point[4] = {0.0f, 0.0f, 0.0f, 1.0f};

static int eyeGhostRect[4] = {-2048, -1024, 4096, 2048};

static int eyeShrinkRect[4] = {-2048, -1024, 1024, 512};

static int eyeTintRect[4] = {-2048, -1024, 4096, 2048};

static int copyToWorkRect[4] = {-2044, -2044, 4096, 4096};

static float pasteToFBPoint[4] = {0.0f, 0.0f, 0.0f, 1.0f};

/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket(void);
/* kept local: this TU's uses of gif_SetAlpha do not fit the prototype in GifPacket.h */
extern void gif_SetAlpha(int a, int b, int c);
/* kept local: this TU's uses of gif_SetDrawEnviroment do not fit the prototype in GifPacket.h */
extern void gif_SetDrawEnviroment(int fb, int b, int w, int h, int e, int f);
/* kept local: this TU's uses of gif_SetGsReg do not fit the prototype in GifPacket.h */
extern void gif_SetGsReg(int reg, long long val);
/* kept local: this TU's uses of gif_SetZTest do not fit the prototype in GifPacket.h */
extern void gif_SetZTest(int on);
/* kept local: this TU's uses of gif_SetZWrite do not fit the prototype in GifPacket.h */
extern void gif_SetZWrite(int on);
/* kept local: this TU's uses of gif_SpriteSensitiveOrg do not fit the prototype in GifPacket.h */
extern void gif_SpriteSensitiveOrg(void *rect, unsigned int z, void *uv, void *col, int e);
/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int pri);

typedef struct {
    int x, y, w, h;
} SprUV;

typedef struct {
    unsigned char f[4];
} SprCol;

/* .rodata: the texture rectangle of a whole 256x128 work buffer, half a
   texel in from each edge, read by eyeBlur and pasteFullScreenFlare.  It is
   the TU's first .rodata object, ahead of the templates of every local
   initialiser, where no code-bearing row before copyCurrentFBToFeedBackArea
   reads it, so it is a file-scope constant and not a third template. */
static const SprUV workBufferUv = {8, 8, 4088, 2040}; /* derived name */

/* .sdata, owned by staticBlur.o and reached only from this file (MAIN.MAP
   line 7344 gives the member, 0xE4 in its link, and names no symbol in the
   run), in ROM order.  The post effect and aura feed modes FullScreenEffect*
   dispatch on and the requests the stage parameters make, the flare switch,
   the two sun fans, the sun switch, the depth fade depth and alpha, the aura
   subtraction depth, then the sprite colours of the passes. */
static int postMode = 1; /* derived name */

static int postModeRequest = 1; /* derived name */

static int flareOn = 1; /* derived name */

static int feedMode = 2; /* derived name */

static int feedModeRequest = 0; /* derived name */

static int sunGlowFan = 0; /* derived name */

static int sunCoreFan = 0; /* derived name */

static int sunOn = 0; /* derived name */

static float depthFadeDepth = 100.0f; /* derived name */

static float depthFadeAlpha = 400.0f; /* derived name */

static float auraInspireZ = 200.0f; /* derived name */

static SprCol blurPassCol = {{128, 128, 128, 0}}; /* derived name */

static SprCol clearCol = {{0, 0, 0, 0}}; /* derived name */

static SprCol fillZCol = {{0, 0, 0, 192}}; /* derived name */

static SprCol alphaCopyCol = {{0, 0, 0, 128}}; /* derived name */

static SprCol whiteCol = {{128, 128, 128, 128}}; /* derived name */

static SprCol flareCol = {{139, 136, 132, 40}}; /* derived name */

static SprCol auraClearCol = {{0, 0, 0, 0}}; /* derived name */

/* staticBlur.c:141-164 in the listing, inlined twice into blur: one pass of
 * the blur, the buffer fb drawn from the texture buffer tex as one sprite,
 * the sprite rect or the texture rect shrunk by rm or um.  A file-scope
 * inline ahead of blur, not a nested function: its rows (142-163) precede
 * blur's own (168-172).  Row 142 is the parameter binding, which is where
 * the listing puts the tex load and the n + 6 of the first call, and the
 * rect and uv rows (154, 160) hold the subtractions, so the shrink is
 * applied here and not at the call.  The name is ours. */
static inline void blurPass(int fb, int tex, int rm, int um, void *col)
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

/* staticBlur.c:168-172: the first pass shrinks the sprite by n + 6 in the
 * blur colour, the second shrinks the texture back in the caller's colour. */
void blur(int n, void *col)
{
    blurPass(workBase[1], workBase[0], n + 6, 0, &blurPassCol);
    blurPass(workBase[0], workBase[1], 0, n + 6, col);
}

void auraInspireBefore(void)
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

/* kept local: main.c's global; this TU does not include main.h */
extern int systemStatus[];

/* .bss, owned by staticBlur.o (0x30, the run): the twelve texture and
   rectangle coordinates the two blur sprites are built from. */
/* */
static int blurUv[12];

extern int GlobalTimer;

/* .sbss, owned by staticBlur.o and reached only from this file (MAIN.MAP names
   no symbol in the run): the blur sprite's RGBA, whose alpha byte the ROM also
   addresses on its own. */
static SprCol blurCol;

extern int matrixptr;
/* kept local: this TU's uses of _ApplyMatrix do not fit the prototype in Matrix.h */
extern void _ApplyMatrix(void *a0, int a1, void *a2);

void auraInspireAfter(int mode)
{
    /* halfRect and halfUv (rows 245 and 254, both initialised in the ROM) are
       read only by the DEBUG build's half-height preview of work buffer 1 in
       the code-free rows 542-619 ahead of the switch (preview ours). */
    int halfRect[4] = {-ScreenWidth / 2 * 16, -ScreenHeight / 4 * 16, ScreenWidth * 16,
                       ScreenHeight / 2 * 16};
    int uv[4] = {8, 8, ScreenWidth * 16, ScreenHeight * 16};
    int rect[4] = {-ScreenWidth / 2 * 16, -ScreenHeight / 2 * 16, ScreenWidth * 16,
                   ScreenHeight * 16};
    int halfUv[4] = {8, 28, ScreenWidth * 16, ScreenHeight / 2 * 16};

    void reduceCopyAlphaChannelOfWork1ToWork0(void)
    {
        int suv[4] = {blurUv[0] + 16, blurUv[1] + 16, ScreenWidth * 16 + blurUv[2],
                      ScreenHeight * 16 + blurUv[3]};
        int srect[4] = {blurUv[4] - 2048, blurUv[5] - 1032, 4096,
                        systemStatus[0] == 0 ? 1792 : 2048};

        gif_SetGsReg(6, workBase[1] | ((long long)(ScreenWidth / 64) << 14) | 0x664000000LL);

        gif_SetDrawEnviroment(workBase[0], 0, 0x100, 0x80, 0, 0);

        gif_SetAlpha(1, 5, 0);
        gif_SpriteSensitiveOrg(srect, 0, suv, &alphaCopyCol, 1);
    }

    void copyAlphaChannelOfWork0ToFeedBackArea(void)
    {
        int suv[4] = {blurUv[6], blurUv[7], blurUv[8] + 4096, blurUv[9] + 2048};
        int srect[4] = {blurUv[10] - 1024, blurUv[11] - 1024, 2048, 2048};

        gif_SetGsReg(6, workBase[0] | 0x20010000 | 0x5C0000000LL);

        gif_SetDrawEnviroment(0x3F00, 0, 0x80, 0x80, 0, 0);

        gif_SetAlpha(1, 5, 0);
        gif_SpriteSensitiveOrg(srect, 0, suv, &alphaCopyCol, 1);
    }

    inline void pasteFeedBackAreaToFB(void)
    {
        int suv[4] = {8, 8, 2048, systemStatus[0] ? 2048 : 1792};

        gif_SetGsReg(6, 0x5DC00BF00LL);

        gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 0, 0);

        gif_SetAlpha(1, 7, 0);
        gif_SpriteSensitiveOrg(rect, 0, suv, &blurCol, 1);
    }

    void copyCurrentFBToFeedBackArea(void)
    {
        if (systemStatus[0] == 0) {
            SprUV a = {-1024, 768, 2048, 256};

            gif_SetDrawEnviroment(0x3F00, 0, 0x80, 0x80, 0, 0);

            gif_SetAlpha(0, 2, 0);
            gif_SpriteSensitiveOrg(&a, 0, (void *)0, &clearCol, 0);
        }
        {
            int suv[4] = {8, 8, ScreenWidth * 16, ScreenHeight * 16};
            int srect[4] = {-1024, -1024, 2048, systemStatus[0] ? 2048 : 1792};

            gif_SetGsReg(6, ((long long)(ScreenWidth / 64) << 14) | 0x664000800LL);

            gif_SetDrawEnviroment(0x3F00, 0, 0x80, 0x80, 0, 0);

            gif_SetAlpha(0, 2, 0);
            gif_SpriteSensitiveOrg(srect, 0, suv, &whiteCol, 0);
        }
    }

    void blurBlendFeedBackAreaToWork1(void)
    {
        void blendWork0ToWork1(void)
        {
            SprUV a = {8, 8, 2048, 2048};
            int srect[4] = {-ScreenWidth / 2 * 16, -ScreenHeight / 2 * 16, ScreenWidth * 16,
                            ScreenHeight * 16};

            gif_SetGsReg(6, workBase[0] | 0x1C008000 | 0x5C0000000LL);

            gif_SetDrawEnviroment(workBase[1], 0, ScreenWidth, ScreenHeight, 0, 0);

            gif_SetAlpha(1, 0, blurCol.f[3]);
            gif_SpriteSensitiveOrg(srect, 0, &a, &blurCol, 1);
        }

        inline void copyFeedBackAreaToWork0(void)
        {
            SprUV a = {-1024, -1024, 2048, 2048};

            gif_SetDrawEnviroment(workBase[0], 0, 0x80, 0x80, 0, 0);

            gif_SetAlpha(0, 2, 0);
            gif_SpriteSensitiveOrg(&a, 0, (void *)0, &clearCol, 0);
        }

        void parallelAddFeedBackAreaToWork0(void)
        {
            inline void addTap(int x, int y)
            {
                SprUV a = {8, 8, 2048, 2048};
                int srect[4] = {x, y, 2048, 2048};

                gif_SetGsReg(6, 0x5DC00BF00LL);

                gif_SetDrawEnviroment(workBase[0], 0, 0x80, 0x80, 0, 0);

                gif_SetAlpha(1, 0, 32);
                gif_SpriteSensitiveOrg(srect, 0, &a, &whiteCol, 1);
            }

            addTap(-1014, -1014);
            addTap(-1014, -1034);
            addTap(-1034, -1014);
            addTap(-1034, -1034);
        }

        copyFeedBackAreaToWork0();
        parallelAddFeedBackAreaToWork0();
        blendWork0ToWork1();
    }

    inline void pasteWork0ToFeedBackArea(void)
    {
        gif_SetGsReg(6, workBase[1] | ((long long)(ScreenWidth / 64) << 14) | 0x664000000LL);

        gif_SetDrawEnviroment(0x3F00, 0, 0x80, 0x80, 0, 0);

        gif_SetAlpha(0, 2, 0);
        gif_SpriteSensitiveOrg(work0ToFeedBackRect, 0, uv, &whiteCol, 0);
    }

    inline void pasteFeedBackAreaToWork0(void)
    {
        gif_SetDrawEnviroment(0x3F00, 0, 0x80, 0x80, 0, 0);

        gif_SetAlpha(0, 2, 0);
        gif_SpriteSensitiveOrg(feedBackToWork0Rect, 0, (void *)0, &alphaCopyCol, 0);
    }

    inline void pasteWork1ToFB(void)
    {
        gif_SetGsReg(6, workBase[1] | ((long long)(ScreenWidth / 64) << 14) | 0x664000000LL);

        gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 0, 0);

        gif_SetAlpha(1, 5, 0);
        gif_SpriteSensitiveOrg(rect, 0, uv, &alphaCopyCol, 1);
    }

    void testAA(void)
    {
        int srect[4] = {-ScreenWidth / 5 * 16, -ScreenHeight / 5 * 16, ScreenWidth / 4 * 16,
                        ScreenHeight / 4 * 16};

        gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 0, 0);

        {
            unsigned char c1[4] = {0, 0, 0, 0};
            unsigned char c2[4] = {0, 0, 0, 128};

            gif_SetAlpha(1, 5, 0);
            gif_SpriteSensitiveOrg(rect, 0, (void *)0, c1, 1);
            gif_SpriteSensitiveOrg(srect, 0, (void *)0, c2, 1);
        }
    }

    inline void addWork1ToFB(void)
    {
        gif_SetGsReg(6, workBase[1] | ((long long)(ScreenWidth / 64) << 14) | 0x664000000LL);

        gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 0, 0);

        gif_SetAlpha(1, 0, 128);
        gif_SpriteSensitiveOrg(rect, 0, uv, &whiteCol, 1);
    }

    inline void addWork1ToFBWithZ(void)
    {
        gif_SetGsReg(6, workBase[1] | ((long long)(ScreenWidth / 64) << 14) | 0x664000000LL);

        gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 0, 0);

        gif_SetAlpha(1, 0, 128);
        gif_SetGsReg(0x47, 0x34000);
        gif_SpriteSensitiveOrg(rect, 0, uv, &whiteCol, 1);
        gif_SetZTest(0);
    }

    void subWork1ToCurrentFB(void)
    {
        float v[4];

        gif_SetZTest(1);
        gif_SetZWrite(0);

        gif_SetGsReg(6, workBase[1] | ((long long)(ScreenWidth / 64) << 14) | 0x664000000LL);

        gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 0, 0);

        subWork1Point[2] = auraInspireZ;
        _ApplyMatrix(v, matrixptr + 192, subWork1Point);

        gif_SetAlpha(1, 1, 128);
        gif_SpriteSensitiveOrg(rect, (int)(v[2] * 16.0f / v[3]), uv, &whiteCol, 1);

        gif_SetZTest(0);
        gif_SetZWrite(0);
    }

    gif_StartPacketPri(8);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(8, 5);
    gif_SetGsReg(0x14, 96);

    gif_SetZTest(0);
    gif_SetZWrite(0);

#ifdef DEBUG
    if (mode == 4) {
        gif_SetGsReg(6, workBase[1] | ((long long)(ScreenWidth / 64) << 14) | 0x664000000LL);
        gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 0, 0);
        gif_SetAlpha(0, 2, 0);
        gif_SpriteSensitiveOrg(halfRect, 0, halfUv, &whiteCol, 0);
    }
#endif
    switch (mode) {
    case 2:
        reduceCopyAlphaChannelOfWork1ToWork0();
        copyAlphaChannelOfWork0ToFeedBackArea();
        pasteFeedBackAreaToFB();
        if (systemStatus[5] == 0) {
            copyCurrentFBToFeedBackArea();
        }
        break;
    case 1:
        blurBlendFeedBackAreaToWork1();
        addWork1ToFB();
        if (systemStatus[5] == 0) {
            pasteWork0ToFeedBackArea();
        }
        break;
    case 3:
        pasteWork1ToFB();
        blurBlendFeedBackAreaToWork1();
        addWork1ToFBWithZ();
        if (systemStatus[5] == 0) {
            pasteWork0ToFeedBackArea();
        }
        break;
    }
    if (GlobalTimer) {
        pasteFeedBackAreaToWork0();
    }

    gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 0, 0);

    gif_SetZWrite(1);
    gif_SetZTest(1);
    gif_EndPacket();
}

void makeFullScreenFlareBefore(int mode)
{
    int rect[4] = {-ScreenWidth / 2 * 16, -ScreenHeight / 2 * 16, ScreenWidth * 16,
                   ScreenHeight * 16};

    int uv[4] = {0, 0, ScreenWidth * 16, ScreenHeight * 16};

    void cleanUpFB(void)
    {
        gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 0, 0);

        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetAlpha(1, 5, 0);
        gif_SpriteSensitiveOrg(rect, 0, (void *)0, &clearCol, 1);

        gif_SetZTest(1);
        gif_SpriteSensitiveOrg(rect, 1, (void *)0, &fillZCol, 1);
        gif_SetAlpha(0, 4, 0);
        gif_SetZWrite(1);
        gif_SetGsReg(0x47, 0x5000D);
    }

    void fillWork2(void)
    {
        gif_SetZTest(0);
        gif_SetZWrite(0);

        {
            unsigned char col[4] = {0, 0, 0, 192};
            SprUV r = {-2048, -512, 4096, 1024};

            gif_SetAlpha(1, 2, 0x80);
            gif_SetDrawEnviroment(workBase[2] + ScreenWidth * ScreenHeight / 64, 0, 0x100, 0x40, 0,
                                  0);

            gif_SpriteSensitiveOrg(&r, 0, (void *)0, col, 1);
        }
        {
            unsigned char col2[4] = {0, 0, 0, 192};

            if (mode & 2) {
                col2[0] = col2[1] = col2[2] = 128;
            }
            gif_SetAlpha(1, 2, 0);
            gif_SetDrawEnviroment(workBase[2], 0, ScreenWidth, ScreenHeight, 0, 0);

            gif_SpriteSensitiveOrg(rect, 0, (void *)0, col2, 0);
        }
        gif_SetZWrite(1);
        gif_SetZTest(1);
    }

    void dispSun(void)
    {
        if (0.0f < sunView[2] && -ScreenWidth < sunScreen[0] && sunScreen[0] < ScreenWidth &&
            -ScreenHeight < sunScreen[1] && sunScreen[1] < ScreenHeight) {
            float v[4];

            sceVu0ITOF0Vector(v, sunScreen);
            gif_StartPacketPri(7);
            gif_SetAlpha(1, 5, 0);
            gif_EndPacket();

            prim_SetFan2D(sunGlowFan, 40.0f, v, 0x505050C0U, 0xC0U);
            prim_DispFan2D(sunGlowFan, 0);
            prim_SetFan2D(sunCoreFan, 15.0f, v, 0xFFFFFFC0U, 0xFFFFFFC0U);
            prim_DispFan2D(sunCoreFan, 0);
        }
    }

    void pasteBackLightShadowToFB(void)
    {
        gif_SetGsReg(6, workBase[2] | ((long long)(ScreenWidth / 64) << 14) | 0x664000000LL);

        gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 0, 0);

        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetAlpha(1, 2, 0x60);
        gif_SetGsReg(0x47, 0x30815);

        {
            int suv[4] = {8, 8, ScreenWidth * 16 - 8, ScreenHeight * 16 - 8};
            SprCol col = {{128, 128, 128, 128}};

            gif_SpriteSensitiveOrg(rect, 0, suv, &col, 1);
        }
        gif_SetZWrite(1);
        gif_SetGsReg(0x47, 0x5000D);
    }

    void makeMaskPatternToWork2(void)
    {
        gif_SetGsReg(6, ((long long)(ScreenWidth / 64) << 14) | 0x664000800LL);
        gif_SetGsReg(0x14, 0x60);

        gif_SetDrawEnviroment(workBase[2], 0, ScreenWidth, ScreenHeight, 0, 0);

        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetAlpha(0, 4, 0);
        gif_SetGsReg(0x47, 0x30815);

        gif_SpriteSensitiveOrg(rect, 0, uv, &alphaCopyCol, 0);

        gif_SetZWrite(1);
        gif_SetGsReg(0x47, 0x5000D);
    }

    gif_StartPacketPri(7);

    gif_SetGsReg(8, 5);

    cleanUpFB();

    fillWork2();
    gif_EndPacket();

    if (sunOn) {
        dispSun();
    }

    gif_StartPacketPri(7);
    makeMaskPatternToWork2();
    gif_EndPacket();
}

static int eyeBlurAlpha = 150; /* derived name */

void makeFullScreenFlareAfter(int mode)
{
    void reduceWork2ToWork0(void)
    {
        gif_SetGsReg(6, workBase[2] | ((long long)(ScreenWidth / 64) << 14) | 0x664000000LL);
        gif_SetGsReg(0x14, 0x60);

        gif_SetDrawEnviroment(workBase[0], 0, 0x100, 0x80, 0, 0);

        gif_SetZTest(0);
        gif_SetZWrite(0);
        {
            SprUV r = {-2048, -1024, 4096, 2048};

            int uv[4] = {64, 64, ScreenWidth * 16, ScreenHeight * 16};
            SprCol col = {{128, 128, 128, 128}};

            gif_SpriteSensitiveOrg(&r, 0, uv, &col, 0);
        }
        gif_SetZWrite(1);
        gif_SetGsReg(0x47, 0x5000D);
    }

    void eyeBlur(int alpha, SprCol *col)
    {
        int rect[4] = {-ScreenWidth / 2 * 16, -ScreenHeight / 2 * 16, ScreenWidth * 16,
                       ScreenHeight * 16};

        gif_SetGsReg(0x14, 0x60);

        gif_SetDrawEnviroment(workBase[3], 0, 0x100, 0x80, 0, 0);

        gif_SetGsReg(6, workBase[0] | 0x20010000 | 0x5C0000000LL);

        gif_SetZTest(0);
        gif_SetZWrite(0);
        {
            SprUV a = {-2048, -1024, 4096, 2048};

            SprUV b = workBufferUv;

            unsigned char c[4] = {alpha, alpha, alpha, 128};

            gif_SetAlpha(1, 7, 0);
            gif_SpriteSensitiveOrg(&a, 0, &b, c, 0);
        }

        if ((mode & 2) == 0 && sunOn && 0.0f < sunView[2] && -ScreenWidth < sunScreen[0] &&
            sunScreen[0] < ScreenWidth && -ScreenHeight < sunScreen[1] &&
            sunScreen[1] < ScreenHeight) {
            int arr[4];
            SprCol c1;
            SprCol c2;
            SprUV d;
            int i;

            gif_SetGsReg(0x14, 0x60);

            gif_SetDrawEnviroment(workBase[3], 0, 0x100, 0x80, 0, 0);

            gif_SetGsReg(8, 5);

            for (i = 1; i < 5; i++) {
                int x0 = (sunScreen[0] + ScreenWidth / 2) * 4096 / ScreenWidth;
                int y0 = (sunScreen[1] + ScreenHeight / 2) * 2048 / ScreenHeight;
                int x = x0 * i / 5;
                int y = y0 * i / 5;
                int x1 = 4112 - (4096 - x0) * i / 5;
                int y1 = 2064 - (2048 - y0) * i / 5;

                arr[0] = x;
                arr[1] = y;
                arr[2] = x1 - x;
                arr[3] = y1 - y;
                c1 = (SprCol){{128, 128, 128, 128}};

                if (0 < x && x < 4095 && 0 < y && y < 4095 && 0 < x1 && x1 < 4095 && 0 < y1 &&
                    y1 < 4095) {
                    gif_SetAlpha(1, 0, alpha / (i + 1));
                    gif_SpriteSensitiveOrg(eyeGhostRect, 0, arr, &c1, 1);
                }
            }

            gif_SetGsReg(0x14, 0x60);

            gif_SetGsReg(6, workBase[3] | 0x20010000 | 0x5C0000000LL);

            gif_SetDrawEnviroment(workBase[1], 0, 0x100, 0x80, 0, 0);
            {
                int x0 = (sunScreen[0] + ScreenWidth / 2) * 4096 / ScreenWidth;
                int y0 = (sunScreen[1] + ScreenHeight / 2) * 2048 / ScreenHeight;
                int px = x0 * 0.9f;
                int py = y0 * 0.9f;
                int px1 = 4096.0f - (4096 - x0) * 0.9f;
                int py1 = 2048.0f - (2048 - y0) * 0.9f;

                arr[0] = px;
                arr[1] = py;
                arr[2] = px1 - px;
                arr[3] = py1 - py;
                c2 = (SprCol){{128, 128, 128, 128}};

                gif_SetAlpha(1, 4, 0);
                gif_SpriteSensitiveOrg(eyeShrinkRect, 0, arr, &c2, 0);
            }

            gif_SetGsReg(0x14, 0x40);

            gif_SetGsReg(6, workBase[1] | 0x20010000 | 0x5C0000000LL);

            gif_SetDrawEnviroment(workBase[3], 0, 0x100, 0x80, 0, 0);
            d = (SprUV){520, 264, 0, 0};
            {
                int rate = 10;
                unsigned char cc[4] = {(col->f[0] - 128) * (col->f[3] * rate) / 128,
                                       (col->f[1] - 128) * (col->f[3] * rate) / 128,
                                       (col->f[2] - 128) * (col->f[3] * rate) / 128,
                                       col->f[3] + 128};

                gif_SetAlpha(1, 5, 0);
                gif_SpriteSensitiveOrg(eyeTintRect, 0, &d, cc, 1);
            }

            if (mode & 1) {
                gif_SetGsReg(0x14, 0x40);

                gif_SetGsReg(6, workBase[1] | 0x20010000 | 0x5C0000000LL);

                gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 0, 0);

                gif_SetZTest(0);
                gif_SetZWrite(0);
                gif_SetAlpha(1, 1, 0x60);
                gif_SetGsReg(0x47, 0x34003);
                {
                    SprUV e = {520, 264, 0, 0};

                    gif_SpriteSensitiveOrg(rect, 0, &e, &whiteCol, 1);
                }
                gif_SetZWrite(1);
                gif_SetGsReg(0x47, 0x5000D);
            }

            gif_SetGsReg(0x14, 0x60);
            gif_SetZWrite(1);
            gif_SetZTest(1);
        }
    }

    inline void pasteWork0ToFB(void)
    {
        gif_SetDrawEnviroment(workBase[0], 0, 0x100, 0x80, 0, 0);

        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetAlpha(1, 0, 0);
        {
            SprUV r = {-2048, -1024, 4096, 2048};

            gif_SpriteSensitiveOrg(&r, 0, (void *)0, &alphaCopyCol, 1);
        }
        gif_SetZWrite(1);
        gif_SetZTest(1);
    }

    gif_StartPacketPri(7);

    reduceWork2ToWork0();

    gif_SetZTest(0);
    gif_SetZWrite(0);
    {
        SprCol col = flareCol;
        int i;

        if ((mode & 2) == 0) {
            col.f[3] = 0;
        } else {
            col.f[3] = col.f[3] / 10;
        }
        for (i = 0; i < 10; i++) {
            blur(i + 10, &col);
        }
    }
    gif_SetZTest(1);
    gif_SetZWrite(1);
    {
        SprCol col = flareCol;

        eyeBlur(eyeBlurAlpha, &col);
    }

    pasteWork0ToFB();

    gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 0, 0);

    gif_EndPacket();
}

void pasteFullScreenFlare(void)
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
    gif_SetAlpha(1, 0, 0x80);

    uv = workBufferUv;
    col = (SprCol){{128, 128, 128, 128}};
    gif_SpriteSensitiveOrg(rect, 0, &uv, &col, 1);

    gif_SetZWrite(1);
    gif_SetGsReg(0x47, 0x5000D);

    gif_EndPacket();
}

static SprCol copyToWorkCol = {{128, 128, 128, 0}}; /* derived name */

static SprCol copyToWork2Col = {{128, 128, 128, 0}}; /* derived name */

static SprCol pasteToFBCol = {{128, 128, 128, 128}}; /* derived name */

static SprCol depthPassCol = {{128, 128, 128, 0}}; /* derived name */

/* One blend pass of the depth-of-field chain: shrink the work buffer named by
   `n` into its twin, taking the previous pass's shrink (`pre`) as the source
   rectangle and this pass's (`cur`) as the destination. */
static inline int depthFieldPass(int n, int cur, int pre)
{
    int tex = workBase[n];

    gif_SetDrawEnviroment(workBase[1 - n], 0, 256, 128, 0, 0);
    gif_SetGsReg(6, tex | 0x20010000 | 0x15C0000000LL);

    if (pre < cur) {
        gif_SetGsReg(0x14, 64);
    } else {
        gif_SetGsReg(0x14, 32);
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

void depthField(float depth, float alpha, float rate)
{
    void copyToWork(void)
    {
        gif_SetGsReg(6, ((long long)(ScreenWidth / 64) << 14) | 0x664000800LL);

        gif_SetDrawEnviroment(workBase[1], 0, 256, 256, 0, 0);

        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetAlpha(0, 4, 0);
        gif_SetGsReg(0x47, 0);
        gif_SetGsReg(0x14, 96);

        {
            int uv[4] = {8, 8, ScreenWidth * 16, 8192};

            gif_SpriteSensitiveOrg(copyToWorkRect, 0, uv, &copyToWorkCol, 0);
        }
        gif_SetZWrite(1);
        gif_SetZTest(1);
        gif_SetGsReg(0x47, 0x5000D);
    }

    void copyToWork2(void)
    {
        gif_SetDrawEnviroment(workBase[0], 0, 256, 128, 0, 0);
        gif_SetGsReg(6, workBase[1] | 0x20010000 | 0x1600000000LL);
        gif_SetGsReg(0x14, 96);
        gif_SetAlpha(1, 4, 0);
        gif_SetZTest(0);
        gif_SetZWrite(0);

        {
            SprUV src = {-2044, -1020, 4096, 2048};
            SprUV dst = {8, 8, 4096, 4096};

            gif_SpriteSensitiveOrg(&src, 0, &dst, &copyToWork2Col, 0);
        }
    }

    void pasteToFB(float z, float rate)
    {
        gif_SetGsReg(6, workBase[0] | 0x20010000 | 0x5C0000000LL);

        gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 0, 0);

        gif_SetGsReg(0x14, 96);
        gif_SetZWrite(0);
        gif_SetGsReg(0x47, 0x50000);
        gif_SetAlpha(1, 2, (int)(rate * 128.0f));

        {
            int rect[4] = {-ScreenWidth / 2 * 16 - 4, -ScreenHeight / 2 * 16 - 4, ScreenWidth * 16,
                           ScreenHeight * 16};
            int uv[4] = {16, 16, 4096, systemStatus[0] == 0 ? 1792 : 2048};
            float v[4];

            pasteToFBPoint[2] = z;
            _ApplyMatrix(v, matrixptr + 192, pasteToFBPoint);

            if (rate == 1.0f) {
                gif_SpriteSensitiveOrg(rect, (int)(v[2] * 16.0f / v[3]), uv, &pasteToFBCol, 0);
            } else {
                gif_SpriteSensitiveOrg(rect, (int)(v[2] * 16.0f / v[3]), uv, &pasteToFBCol, 1);
            }
        }
        gif_SetGsReg(0x47, 0x5000D);
    }

    int w = 50;
    int cur;
    int pre;
    int i;

    gif_StartPacketPri(7);
    gif_SetGsReg(8, 5);

    copyToWork();
    copyToWork2();

    gif_SetZTest(0);
    gif_SetZWrite(0);

    pre = 0;
    cur = w;
    pre = depthFieldPass(0, cur, pre);
    cur = w * 4 / 5;
    pre = depthFieldPass(1, cur, pre);
    cur = w * 3 / 5;
    pre = depthFieldPass(0, cur, pre);
    cur = w * 2 / 5;
    pre = depthFieldPass(1, cur, pre);
    cur = w * 1 / 5;
    pre = depthFieldPass(0, cur, pre);
    cur = 0;
    pre = depthFieldPass(1, cur, pre);

    gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 0, 0);

    for (i = 1; i < 4; i++) {
        pasteToFB(depth + alpha * i * 0.25f, i * 0.25f);
    }
    pasteToFB(depth + alpha, 1.0f);

    gif_EndPacket();
}

/* kept local: this TU's uses of _NormalizeVector do not fit the prototype in Matrix.h */
extern void _NormalizeVector();

void GetSunWorldPos(int a0)
{
    _NormalizeVector(a0, sunDir);
}

static int motionBlurAlpha = 0; /* derived name */

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
        /* "MBLUR %d" is "MBLUR %d": the blur strength is the value printed */
        debug_Printf(300, 40, 0xFFFFFF00, (int)"MBLUR %d", motionBlurAlpha);
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

/* kept local: this TU's uses of _AddVectorXYZ do not fit the prototype in Matrix.h */
extern void _AddVectorXYZ(void *a0, void *a1, void *a2);
/* kept local: this TU's uses of _FTOI0Vector do not fit the prototype in Matrix.h */
extern void _FTOI0Vector(void *a0, void *a1);
/* kept local: this TU's uses of _ScaleVector do not fit the prototype in Matrix.h */
extern void _ScaleVector(void *a0, void *a1, float f);
/* kept local: this TU's uses of _ScaleVectorXYZ do not fit the prototype in Matrix.h */
extern void _ScaleVectorXYZ(void *a0, void *a1, float f);

void calcSun(void)
{
    float buf[4];
    _NormalizeVector((int)buf, sunDir);
    _ScaleVector(buf, buf, 1000000.0f);
    buf[3] = 1.0f;
    _ApplyMatrix(buf, matrixptr + 0x100, buf);
    _ScaleVectorXYZ(buf, buf, 1.0f / buf[3]);
    _AddVectorXYZ(buf, buf, sunScreenOffset);
    _FTOI0Vector(sunScreen, buf);
    _ApplyMatrix(sunView, matrixptr + 0x80, sunDir);
}

extern int D_0028F954[];

static int colorSettingItem = 0; /* derived name */

/* staticBlur.c:1401-1405 in the PAL listing: rows outside colorSetting's own
   span (1410-1455), i.e. a static helper the listing inlines at all four
   switch arms. */
static inline void colorSettingStep(unsigned char *p, int d)
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

void colorSetting(void)
{
    char buf[256];
    int f = D_0028F954[0];
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

void dispPostInfo(void)
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

void dispFeedInfo(void)
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

/* kept local: main.c's global; this TU does not include main.h */
extern struct D275 GlobalStageSetting;

void FullScreenEffectBefore(void)
{
    if (debug_fullscreen_effect == 0) {
        return;
    }

    postModeRequest = GlobalStageSetting.field_E8;
    feedModeRequest = GlobalStageSetting.field_104;

    blurCol.f[0] = GlobalStageSetting.field_110;
    blurCol.f[1] = GlobalStageSetting.field_114;
    blurCol.f[2] = GlobalStageSetting.field_118;
    blurCol.f[3] = GlobalStageSetting.field_11C;

    if (postMode != postModeRequest) {
        postMode = postModeRequest;
    }
    if (feedMode != feedModeRequest) {
        feedMode = feedModeRequest;
    }

    dispPostInfo();
    dispFeedInfo();

    if (sunOn)
        if (debug_font_flag & 1)
            debug_Printf(250, 40, 0xFFFFFF00, "SUN");

    workBase[0] = 0x2800;
    workBase[1] = 0x2A00;
    workBase[2] = 0x2E00;
    workBase[3] = 0x3000;

    if (systemStatus[0] == 1) {
        tex_LockHeadTBP(0x3A00, 8);
    } else {
        tex_LockHeadTBP(0x3800, 8);
    }

    if (sunOn) {
        calcSun();
    }

    switch (postMode) {
    case 1:
    case 3:
        if (flareOn) {
            makeFullScreenFlareBefore(0);
        }
        break;
    case 4:
    case 5:
        if (flareOn) {
            makeFullScreenFlareBefore(2);
        }
        break;
    case 6:
    case 7:
        if (flareOn) {
            makeFullScreenFlareBefore(1);
        }
        break;
    case 2:
    case 8:
        break;
    }

    if (feedMode) {
        auraInspireBefore();
    }
}

void FullScreenEffectAfter(void)
{
    if (debug_fullscreen_effect == 0) {
        return;
    }

    switch (postMode) {
    case 1:
        if (flareOn) {
            makeFullScreenFlareAfter(0);
            pasteFullScreenFlare();
        }
        break;
    case 2:
        depthField(depthFadeDepth, depthFadeAlpha, 1.0f);
        break;
    case 3:
        if (flareOn) {
            makeFullScreenFlareAfter(0);
        }
        depthField(depthFadeDepth, depthFadeAlpha, 1.0f);
        if (flareOn) {
            pasteFullScreenFlare();
        }
        break;
    case 4:
        if (flareOn) {
            makeFullScreenFlareAfter(2);
            pasteFullScreenFlare();
        }
        break;
    case 5:
        if (flareOn) {
            makeFullScreenFlareAfter(2);
        }
        depthField(depthFadeDepth, depthFadeAlpha, 1.0f);
        if (flareOn) {
            pasteFullScreenFlare();
        }
        break;
    case 6:
        if (flareOn) {
            makeFullScreenFlareAfter(1);
            pasteFullScreenFlare();
        }
        break;
    case 7:
        if (flareOn) {
            makeFullScreenFlareAfter(1);
        }
        depthField(depthFadeDepth, depthFadeAlpha, 1.0f);
        if (flareOn) {
            pasteFullScreenFlare();
        }
        break;
    case 8:
        break;
    }

    if (feedMode) {
        auraInspireAfter(feedMode);
    }

    depthFadeDepth = GlobalStageSetting.field_EC;
    depthFadeAlpha = GlobalStageSetting.field_F0;

    tex_UnlockHeadTBP(7);
    tex_UnlockHeadTBP(8);
}

/* kept local: this TU's uses of ZeroPoint do not fit the prototype in matrixDrive.h */
extern int ZeroPoint[];
/* kept local: this TU's uses of CopyVector do not fit the prototype in matrixDrive.h */
extern void CopyVector();

/* INTERIM (same pattern as GetSkeltonFocusNode in src/motionManager2.c): the
   listing inlines _initStaticBlur (staticBlur.c:1310-1311) into InitStaticBlur,
   so it is `inline` in the dev's TU; while this tail still has asm members a
   deferred inline would land at the object end instead of at its ROM slot, so
   the public body below stays a plain definition and this static stand-in
   serves the C caller.  Collapses to one `inline` definition at layout. */
static inline void initStaticBlur(void)
{
    sunGlowFan = prim_InitFan2D(0x10, 80.0f, ZeroPoint, 0xFFFFFF80u, 0);
    sunCoreFan = prim_InitFan2D(0x10, 80.0f, ZeroPoint, 0xFFFFFF80u, 0);
}

int InitStaticBlur(void)
{
    CopyVector(sunDir);
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

extern int D_0028F808[];

void SetStaticBlur(int x)
{
    D_0028F808[0] = x;
}

void SetDepthFadeParam(float f12, float f13, int a0)
{
    GlobalStageSetting.field_EC = (int)f12;
    GlobalStageSetting.field_F0 = (int)f13;
    GlobalStageSetting.field_F8 = a0;
}

void SetAuraInspireParam(float a0)
{
    auraInspireZ = a0;
}

void InitializeStaticBlur(void)
{
    sunOn = 0;
}

void _initStaticBlur(void)
{
    sunGlowFan = prim_InitFan2D(0x10, 80.0f, ZeroPoint, 0xFFFFFF80u, 0);
    sunCoreFan = prim_InitFan2D(0x10, 80.0f, ZeroPoint, 0xFFFFFF80u, 0);
}

void SetAuraEffect(void) {}
