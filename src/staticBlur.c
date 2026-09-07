#include "common.h"

struct D275 {
    char pad[0xEC];
    int field_EC;
    int field_F0;
    int field_F4;
    int field_F8;
};

extern int D_004ED020[];
extern void gif_EndPacket(void);
extern void gif_SetAlpha(int a, int b, int c);
extern void gif_SetDrawEnviroment(int fb, int b, int w, int h, int e, int f);
extern void gif_SetGsReg(int reg, long long val);
extern void gif_SetZTest(int on);
extern void gif_SetZWrite(int on);
extern void gif_SpriteSensitiveOrg(void *rect, int b, void *uv, void *col, int e);
extern void gif_StartPacketPri(int pri);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", blur);
extern int D_0063A064;
extern int D_0063A068;
extern int D_0063BB68;

void auraInspireBefore(void)
{
    int rect[4] = { -D_0063A064 / 2 * 16, -D_0063A068 / 2 * 16,
                    D_0063A064 * 16, D_0063A068 * 16 };

    gif_StartPacketPri(8);
    gif_SetGsReg(8, 5);

    gif_SetDrawEnviroment(D_004ED020[1], 0, D_0063A064, D_0063A068, 0, 0);

    gif_SetZTest(0);
    gif_SetZWrite(0);

    gif_SetAlpha(0, 2, 0);
    gif_SpriteSensitiveOrg(rect, 0, (void *)0, &D_0063BB68, 0);

    gif_SetZWrite(1);
    gif_SetZTest(1);

    gif_SetAlpha(1, 7, 0);
    gif_SetDrawEnviroment(D_004ED020[1], 0, D_0063A064, D_0063A068, 0, 0);

    gif_SetGsReg(8, 5);
    gif_SetGsReg(0x4A, 0);
    gif_EndPacket();
}
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", reduceCopyAlphaChannelOfWork1ToWork0);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", copyAlphaChannelOfWork0ToFeedBackArea);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", copyCurrentFBToFeedBackArea);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", blendWork0ToWork1);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", parallelAddFeedBackAreaToWork0);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", blurBlendFeedBackAreaToWork1);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", testAA);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", subWork1ToCurrentFB);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", auraInspireAfter);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", cleanUpFB);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", fillWork2);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", dispSun);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", pasteBackLightShadowToFB);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", makeMaskPatternToWork2);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", makeFullScreenFlareBefore);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", reduceWork2ToWork0);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", eyeBlur);
ASM_LIT4_SLOT(D_006396A8, 0.9f);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", makeFullScreenFlareAfter);
extern int D_004ED02C[];
typedef struct { int f[4]; } SprUV;
typedef struct { char f[4]; } SprCol;
extern SprUV D_00620DE0;
extern SprCol D_0063BB70[];

void pasteFullScreenFlare(void)
{
    int rect[4] = { -D_0063A064 / 2 * 16, -D_0063A068 / 2 * 16,
                    D_0063A064 * 16, D_0063A068 * 16 };
    SprUV uv;
    SprCol col;

    gif_StartPacketPri(7);

    gif_SetGsReg(6, D_004ED02C[0] | 0x20010000 | 0x5C0000000LL);

    gif_SetDrawEnviroment(0x800, 0, D_0063A064, D_0063A068, 0, 0);

    gif_SetZTest(0);
    gif_SetZWrite(0);
    gif_SetAlpha(1, 0, 0x80);

    uv = D_00620DE0;
    col = D_0063BB70[0];
    gif_SpriteSensitiveOrg(rect, 0, &uv, &col, 1);

    gif_SetZWrite(1);
    gif_SetGsReg(0x47, 0x5000D);

    gif_EndPacket();
}
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", copyToWork_233);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", copyToWork2);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", pasteToFB);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", depthField);
extern int D_004ED050[];
extern void _NormalizeVector();

void GetSunWorldPos(int a0)
{
    _NormalizeVector(a0, D_004ED050);
}
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", MotionBlur);
extern int D_004ED030[];
extern int D_004ED040[];
extern int D_004ED060[];
extern int matrixptr;
extern void _AddVectorXYZ(void *a0, void *a1, void *a2);
extern void _ApplyMatrix(void *a0, int a1, void *a2);
extern void _FTOI0Vector(void *a0, void *a1);
extern void _ScaleVector(void *a0, void *a1, float f);
extern void _ScaleVectorXYZ(void *a0, void *a1, float f);

void calcSun(void) {
    float buf[4];
    _NormalizeVector((int)buf, D_004ED050);
    _ScaleVector(buf, buf, 1000000.0f);
    buf[3] = 1.0f;
    _ApplyMatrix(buf, matrixptr + 0x100, buf);
    _ScaleVectorXYZ(buf, buf, 1.0f / buf[3]);
    _AddVectorXYZ(buf, buf, D_004ED060);
    _FTOI0Vector(D_004ED030, buf);
    _ApplyMatrix(D_004ED040, matrixptr + 0x80, D_004ED050);
}
extern int D_0063B13C;
extern void debug_Printf();
extern int sprintf();
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", colorSetting);
extern char D_00620EC0[];
extern int D_0063BB08;
extern int D_0063BB9C;
extern int D_0063BBA0;
extern char D_00620ED0[];
extern char D_00620EE0[];
extern char D_00620EF0[];
extern char D_00620F00[];
extern char D_00620F10[];
extern char D_0063BBA8[];
extern char D_0063BBB0[];
extern char D_0063BBB8[];
extern char D_0063BBC0[];
void dispPostInfo(void)
{
    char buf[256];

    if (D_0063BBA0 != D_0063BB08) {
        D_0063BB9C = 0;
    }
    D_0063BBA0 = D_0063BB08;
    if (D_0063BB9C < 60) {
        D_0063BB9C++;
    }
    if (((D_0063BB9C >> 1) & 1) == 0) {
        switch (D_0063BB08) {
        case 0:
            sprintf(buf, D_00620EC0);
            break;
        case 1:
            sprintf(buf, D_0063BBA8);
            break;
        case 2:
            sprintf(buf, D_0063BBB0);
            break;
        case 3:
            sprintf(buf, D_00620ED0);
            break;
        case 4:
            sprintf(buf, D_0063BBB8);
            break;
        case 5:
            sprintf(buf, D_00620EE0);
            break;
        case 6:
            sprintf(buf, D_0063BBC0);
            break;
        case 7:
            sprintf(buf, D_00620EF0);
            break;
        case 8:
            sprintf(buf, D_00620F00);
            break;
        }
        if (D_0063B13C & 1) {
            debug_Printf(0x1B8, 0x14, 0xFFFFFF00, D_00620F10, buf);
        }
    }
}

extern int D_0063BB14;
extern int D_0063BBC8;
extern int D_0063BBCC;
extern char D_00620F48[];
extern char D_0063BBD0[];
extern char D_0063BBD8[];
extern char D_0063BBE0[];

void dispFeedInfo(void)
{
    char buf[256];

    if (D_0063BBCC != D_0063BB14) {
        D_0063BBC8 = 0;
    }
    D_0063BBCC = D_0063BB14;
    if (D_0063BBC8 < 60) {
        D_0063BBC8++;
    }
    if (((D_0063BBC8 >> 1) & 1) == 0) {
        switch (D_0063BB14) {
        default:
            sprintf(buf, D_00620EC0);
            break;
        case 1:
            sprintf(buf, D_0063BBD0);
            break;
        case 2:
            sprintf(buf, D_0063BBD8);
            break;
        case 3:
            sprintf(buf, D_0063BBE0);
            break;
        }
        if (D_0063B13C & 1) {
            debug_Printf(0x1B8, 0x1E, 0xFFFFFF00, D_00620F48, buf);
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", FullScreenEffectBefore);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", FullScreenEffectAfter);
extern int D_0028FF00[];
extern int D_0063BB1C;
extern int D_0063BB20;
extern int D_0063BB24;
extern void CopyVector();
extern int prim_InitFan2D(int a, float e, int *b, unsigned int c, int d);
/* INTERIM (same pattern as GetSkeltonFocusNode in src/motionManager2.c): the
   listing inlines _initStaticBlur (staticBlur.c:1310-1311) into InitStaticBlur,
   so it is `inline` in the dev's TU; while this tail still has asm members a
   deferred inline would land at the object end instead of at its ROM slot, so
   the public body below stays a plain definition and this static stand-in
   serves the C caller.  Collapses to one `inline` definition at layout. */
static inline void initStaticBlur(void)
{
    D_0063BB1C = prim_InitFan2D(0x10, 80.0f, D_0028FF00, 0xFFFFFF80u, 0);
    D_0063BB20 = prim_InitFan2D(0x10, 80.0f, D_0028FF00, 0xFFFFFF80u, 0);
}

int InitStaticBlur(void)
{
    CopyVector(D_004ED050);
    D_004ED050[3] = 0;
    initStaticBlur();
    D_0063BB24 = 1;
    return 0;
}
void StaticBlur(void) {}
void StaticBlurDL(void) {}
extern int D_0063BB94;

void SetMotionBlur(int val) {
    D_0063BB94 = val;
}
extern int D_0028F808[];

void SetStaticBlur(int x) {
    D_0028F808[0] = x;
}
extern struct D275 D_0028F720;

void SetDepthFadeParam(float f12, float f13, int a0)
{
    D_0028F720.field_EC = (int)f12;
    D_0028F720.field_F0 = (int)f13;
    D_0028F720.field_F8 = a0;
}
extern float D_0063BB30;

void SetAuraInspireParam(float a0) {
    D_0063BB30 = a0;
}
void InitializeStaticBlur(void) {
    D_0063BB24 = 0;
}
void _initStaticBlur(void)
{
    D_0063BB1C = prim_InitFan2D(0x10, 80.0f, D_0028FF00, 0xFFFFFF80u, 0);
    D_0063BB20 = prim_InitFan2D(0x10, 80.0f, D_0028FF00, 0xFFFFFF80u, 0);
}
void SetAuraEffect(void) {}
