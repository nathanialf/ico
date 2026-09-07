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
extern void gif_SpriteSensitiveOrg(void *rect, unsigned int z, void *uv, void *col, int e);
extern void gif_StartPacketPri(int pri);

typedef struct { int f[4]; } SprUV;
typedef struct { unsigned char f[4]; } SprCol;
extern int D_004ED02C[];
extern SprUV D_00620DE0;
extern SprCol D_0063BB70[];

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
extern int D_004ED028[];
extern int D_004ED030[];
extern float D_004ED048[];
extern int D_0063BB1C;
extern int D_0063BB20;
extern int D_0063BB24;
extern int D_0063BB40;
extern int D_0063BB48;
extern SprCol D_0063BB50;
extern SprUV D_00620E20;
extern void memset(void *dst, int c, int n);
extern void prim_DispFan2D(int handle, int a);
extern void prim_SetFan2D(int handle, float radius, void *pos, unsigned int c0,
                          unsigned int c1);
extern void sceVu0ITOF0Vector(void *dst, void *src);

void makeFullScreenFlareBefore(int mode)
{
    int rect[4] = { -D_0063A064 / 2 * 16, -D_0063A068 / 2 * 16,
                    D_0063A064 * 16, D_0063A068 * 16 };

    int uv[4] = { 0, 0, D_0063A064 * 16, D_0063A068 * 16 };

    void cleanUpFB(void)
    {
        gif_SetDrawEnviroment(0x800, 0, D_0063A064, D_0063A068, 0, 0);

        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetAlpha(1, 5, 0);
        gif_SpriteSensitiveOrg(rect, 0, (void *)0, &D_0063BB40, 1);

        gif_SetZTest(1);
        gif_SpriteSensitiveOrg(rect, 1, (void *)0, &D_0063BB48, 1);
        gif_SetAlpha(0, 4, 0);
        gif_SetZWrite(1);
        gif_SetGsReg(0x47, 0x5000D);
    }

    void fillWork2(void)
    {
        gif_SetZTest(0);
        gif_SetZWrite(0);

        {
            unsigned char col[4] = { 0, 0, 0, 192 };
            SprUV r = D_00620E20;

            gif_SetAlpha(1, 2, 0x80);
            gif_SetDrawEnviroment(D_004ED020[2] + D_0063A064 * D_0063A068 / 64,
                                  0, 0x100, 0x40, 0, 0);

            gif_SpriteSensitiveOrg(&r, 0, (void *)0, col, 1);
        }
        {
            unsigned char col2[4] = { 0, 0, 0, 192 };

            if (mode & 2) {
                col2[0] = col2[1] = col2[2] = 128;
            }
            gif_SetAlpha(1, 2, 0);
            gif_SetDrawEnviroment(D_004ED020[2], 0, D_0063A064, D_0063A068, 0, 0);

            gif_SpriteSensitiveOrg(rect, 0, (void *)0, col2, 0);
        }
        gif_SetZWrite(1);
        gif_SetZTest(1);
    }

    void dispSun(void)
    {
        if (0.0f < D_004ED048[0] && -D_0063A064 < D_004ED030[0]
            && D_004ED030[0] < D_0063A064 && -D_0063A068 < D_004ED030[1]
            && D_004ED030[1] < D_0063A068) {
            float v[4];

            sceVu0ITOF0Vector(v, D_004ED030);
            gif_StartPacketPri(7);
            gif_SetAlpha(1, 5, 0);
            gif_EndPacket();

            prim_SetFan2D(D_0063BB1C, 40.0f, v, 0x505050C0U, 0xC0U);
            prim_DispFan2D(D_0063BB1C, 0);
            prim_SetFan2D(D_0063BB20, 15.0f, v, 0xFFFFFFC0U, 0xFFFFFFC0U);
            prim_DispFan2D(D_0063BB20, 0);
        }
    }

    void pasteBackLightShadowToFB(void)
    {
        gif_SetGsReg(6, D_004ED028[0] | ((long long)(D_0063A064 / 64) << 14)
                            | 0x664000000LL);

        gif_SetDrawEnviroment(0x800, 0, D_0063A064, D_0063A068, 0, 0);

        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetAlpha(1, 2, 0x60);
        gif_SetGsReg(0x47, 0x30815);

        {
            int suv[4] = { 8, 8, D_0063A064 * 16 - 8, D_0063A068 * 16 - 8 };
            SprCol col = D_0063BB70[0];

            gif_SpriteSensitiveOrg(rect, 0, suv, &col, 1);
        }
        gif_SetZWrite(1);
        gif_SetGsReg(0x47, 0x5000D);
    }

    void makeMaskPatternToWork2(void)
    {
        gif_SetGsReg(6, ((long long)(D_0063A064 / 64) << 14) | 0x664000800LL);
        gif_SetGsReg(0x14, 0x60);

        gif_SetDrawEnviroment(D_004ED028[0], 0, D_0063A064, D_0063A068, 0, 0);

        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetAlpha(0, 4, 0);
        gif_SetGsReg(0x47, 0x30815);

        gif_SpriteSensitiveOrg(rect, 0, uv, &D_0063BB50, 0);

        gif_SetZWrite(1);
        gif_SetGsReg(0x47, 0x5000D);
    }

    gif_StartPacketPri(7);

    gif_SetGsReg(8, 5);

    cleanUpFB();

    fillWork2();
    gif_EndPacket();

    if (D_0063BB24) {
        dispSun();
    }

    gif_StartPacketPri(7);
    makeMaskPatternToWork2();
    gif_EndPacket();
}
extern int D_004ED0A0[];
extern int D_004ED0B0[];
extern int D_004ED0C0[];
extern SprUV D_00620E30;
extern SprUV D_00620E40;
extern SprCol D_0063BB58;
extern SprCol D_0063BB60;
extern int D_0063BB74;
extern void blur(int n, void *col);

void makeFullScreenFlareAfter(int mode)
{
    void reduceWork2ToWork0(void)
    {
        gif_SetGsReg(6, D_004ED020[2] | ((long long)(D_0063A064 / 64) << 14)
                            | 0x664000000LL);
        gif_SetGsReg(0x14, 0x60);

        gif_SetDrawEnviroment(D_004ED020[0], 0, 0x100, 0x80, 0, 0);

        gif_SetZTest(0);
        gif_SetZWrite(0);
        {
            SprUV r = D_00620E30;

            int uv[4] = { 64, 64,
                          D_0063A064 * 16, D_0063A068 * 16 };
            SprCol col = D_0063BB70[0];

            gif_SpriteSensitiveOrg(&r, 0, uv, &col, 0);
        }
        gif_SetZWrite(1);
        gif_SetGsReg(0x47, 0x5000D);
    }

    void eyeBlur(int alpha, SprCol *col)
    {
        int rect[4] = { -D_0063A064 / 2 * 16, -D_0063A068 / 2 * 16,
                        D_0063A064 * 16, D_0063A068 * 16 };

        gif_SetGsReg(0x14, 0x60);

        gif_SetDrawEnviroment(D_004ED020[3], 0, 0x100, 0x80, 0, 0);

        gif_SetGsReg(6, D_004ED020[0] | 0x20010000 | 0x5C0000000LL);

        gif_SetZTest(0);
        gif_SetZWrite(0);
        {
            SprUV a = D_00620E30;

            SprUV b = D_00620DE0;

            unsigned char c[4] = { alpha, alpha, alpha, 128 };

            gif_SetAlpha(1, 7, 0);
            gif_SpriteSensitiveOrg(&a, 0, &b, c, 0);
        }

        if ((mode & 2) == 0 && D_0063BB24 && 0.0f < D_004ED048[0]
            && -D_0063A064 < D_004ED030[0] && D_004ED030[0] < D_0063A064
            && -D_0063A068 < D_004ED030[1] && D_004ED030[1] < D_0063A068) {
            int arr[4];
            SprCol c1;
            SprCol c2;
            SprUV d;
            int i;

            gif_SetGsReg(0x14, 0x60);

            gif_SetDrawEnviroment(D_004ED020[3], 0, 0x100, 0x80, 0, 0);

            gif_SetGsReg(8, 5);

            for (i = 1; i < 5; i++) {
                int x0 = (D_004ED030[0] + D_0063A064 / 2) * 4096 / D_0063A064;
                int y0 = (D_004ED030[1] + D_0063A068 / 2) * 2048 / D_0063A068;
                int x = x0 * i / 5;
                int y = y0 * i / 5;
                int x1 = 4112 - (4096 - x0) * i / 5;
                int y1 = 2064 - (2048 - y0) * i / 5;

                arr[0] = x; arr[1] = y; arr[2] = x1 - x; arr[3] = y1 - y;
                c1 = D_0063BB70[0];

                if (0 < x && x < 4095 && 0 < y && y < 4095 && 0 < x1
                    && x1 < 4095 && 0 < y1 && y1 < 4095) {
                    gif_SetAlpha(1, 0, alpha / (i + 1));
                    gif_SpriteSensitiveOrg(D_004ED0A0, 0, arr, &c1, 1);
                }
            }

            gif_SetGsReg(0x14, 0x60);

            gif_SetGsReg(6, D_004ED020[3] | 0x20010000 | 0x5C0000000LL);

            gif_SetDrawEnviroment(D_004ED020[1], 0, 0x100, 0x80, 0, 0);
            {
                int x0 = (D_004ED030[0] + D_0063A064 / 2) * 4096 / D_0063A064;
                int y0 = (D_004ED030[1] + D_0063A068 / 2) * 2048 / D_0063A068;
                int px = x0 * 0.9f;
                int py = y0 * 0.9f;
                int px1 = 4096.0f - (4096 - x0) * 0.9f;
                int py1 = 2048.0f - (2048 - y0) * 0.9f;

                arr[0] = px; arr[1] = py; arr[2] = px1 - px; arr[3] = py1 - py;
                c2 = D_0063BB70[0];

                gif_SetAlpha(1, 4, 0);
                gif_SpriteSensitiveOrg(D_004ED0B0, 0, arr, &c2, 0);
            }

            gif_SetGsReg(0x14, 0x40);

            gif_SetGsReg(6, D_004ED020[1] | 0x20010000 | 0x5C0000000LL);

            gif_SetDrawEnviroment(D_004ED020[3], 0, 0x100, 0x80, 0, 0);
            d = D_00620E40;
            {
                int rate = 10;
                unsigned char cc[4] = {
                    (col->f[0] - 128) * (col->f[3] * rate) / 128,
                    (col->f[1] - 128) * (col->f[3] * rate) / 128,
                    (col->f[2] - 128) * (col->f[3] * rate) / 128,
                    col->f[3] + 128
                };

                gif_SetAlpha(1, 5, 0);
                gif_SpriteSensitiveOrg(D_004ED0C0, 0, &d, cc, 1);
            }

            if (mode & 1) {
                gif_SetGsReg(0x14, 0x40);

                gif_SetGsReg(6, D_004ED020[1] | 0x20010000 | 0x5C0000000LL);

                gif_SetDrawEnviroment(0x800, 0, D_0063A064, D_0063A068, 0, 0);

                gif_SetZTest(0);
                gif_SetZWrite(0);
                gif_SetAlpha(1, 1, 0x60);
                gif_SetGsReg(0x47, 0x34003);
                {
                    SprUV e = D_00620E40;

                    gif_SpriteSensitiveOrg(rect, 0, &e, &D_0063BB58, 1);
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
        gif_SetDrawEnviroment(D_004ED020[0], 0, 0x100, 0x80, 0, 0);

        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetAlpha(1, 0, 0);
        {
            SprUV r = D_00620E30;

            gif_SpriteSensitiveOrg(&r, 0, (void *)0, &D_0063BB50, 1);
        }
        gif_SetZWrite(1);
        gif_SetZTest(1);
    }

    gif_StartPacketPri(7);

    reduceWork2ToWork0();

    gif_SetZTest(0);
    gif_SetZWrite(0);
    {
        SprCol col = D_0063BB60;
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
        SprCol col = D_0063BB60;

        eyeBlur(D_0063BB74, &col);
    }

    pasteWork0ToFB();

    gif_SetDrawEnviroment(0x800, 0, D_0063A064, D_0063A068, 0, 0);

    gif_EndPacket();
}
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
