#include "sugiCommon.h"
#include "DObj.h"
#include "memory.h"
#include "obj_manager.h"
#include "act-game.h"
#include "DisplayP2O.h"
#include "Primitive.h"
#include "RegistPacket.h"
#include "actressLight.h"
#include "clothAnimation.h"
#include "geometryManager.h"
#include "handManager.h"
#include "lodManager.h"
#include "matrixDrive.h"
#include "motionManager2.h"
#include "motionOrientManager.h"
#include "pool.h"
#include "quaternion.h"
#include "waterDot.h"
#include <libvu0.h>
#include "Matrix.h"

typedef struct { /* 0x10 */
    float x, y, z, w;
} __attribute__((aligned(16))) LLVec;

typedef struct LightLineExt {
    float *phase; /* 0x00 */
    float *speed; /* 0x04 */
    LLVec **line; /* 0x08 */
} LightLineExt;

/* The colour record LightLineDL builds for DrawLineG: four 32-bit components,
   and the ROM's frame places both of them on a 16-byte boundary. */
typedef struct { /* 0x10 */
    int r, g, b, a;
} __attribute__((aligned(16))) LLColor;

#include "boy.h"
#include "debug.h"
#include "main.h"
#include "GifPacket.h"
#include "lineManager.h"
#include "ios.h"

/* The boy's five generated cloth meshes, in the order InitBoyGeo hands them to
   InitCloth4D: the mantle, the tape belt and the three loose tape strips.
   MAIN.MAP names no symbol in boy.o's .data, so these names are ours, taken
   from the texture each mesh is drawn with.  The floats are the generator's
   own three-decimal output, read back from the ROM. */

static Cloth4DCol mantleMeshCols[5];

static Cloth4DCfg mantleMesh = {
    5, 6, 0, 0, 0x59, 0x59, 0x59, 0x80, "b_mantle", mantleMeshCols, 11.239f, 0,
};

static float mantleMeshUv[5][6][2] = {
    {{0.992f, 0.617f},
     {0.993f, 0.694f},
     {0.994f, 0.77f},
     {0.995f, 0.847f},
     {0.995f, 0.923f},
     {0.996f, 1.0f}},
    {{0.004f, 0.617f},
     {0.004f, 0.694f},
     {0.004f, 0.77f},
     {0.004f, 0.847f},
     {0.004f, 0.923f},
     {0.004f, 1.0f}},
    {{0.752f, 0.667f},
     {0.752f, 0.734f},
     {0.753f, 0.8f},
     {0.753f, 0.867f},
     {0.754f, 0.933f},
     {0.754f, 1.0f}},
    {{0.485f, 0.69f},
     {0.486f, 0.752f},
     {0.486f, 0.814f},
     {0.487f, 0.876f},
     {0.488f, 0.938f},
     {0.488f, 1.0f}},
    {{0.256f, 0.667f},
     {0.255f, 0.734f},
     {0.255f, 0.8f},
     {0.255f, 0.867f},
     {0.254f, 0.933f},
     {0.254f, 1.0f}},
};

static Cloth4DCol mantleMeshCols[5] = {
    {5.908f,
     {0},
     {9.617f, 97.683f, -3.421f, 1.0f},
     {0.22f, 0.438f, 0.872f, 0.0f},
     2,
     0.6f,
     1,
     0.4f,
     mantleMeshUv[0],
     {0},
     {0.32f, -5.877f, 0.505f, 0.0f}},
    {5.958f,
     {0},
     {5.324f, 97.805f, -2.397f, 1.0f},
     {0.096f, 0.526f, 0.845f, 0.0f},
     2,
     0.15f,
     1,
     0.85f,
     mantleMeshUv[2],
     {0},
     {0.171f, -5.902f, 0.803f, 0.0f}},
    {5.919f,
     {0},
     {0.009f, 97.685f, -1.686f, 1.0f},
     {0.0f, 0.571f, 0.821f, 0.0f},
     1,
     1.0f,
     -1,
     0.0f,
     mantleMeshUv[3],
     {0},
     {-0.002f, -5.878f, 0.695f, 0.0f}},
    {5.958f,
     {0},
     {-5.324f, 97.805f, -2.397f, 1.0f},
     {-0.095f, 0.526f, 0.845f, 0.0f},
     17,
     0.15f,
     1,
     0.85f,
     mantleMeshUv[4],
     {0},
     {-0.171f, -5.902f, 0.803f, 0.0f}},
    {5.908f,
     {0},
     {-9.617f, 97.683f, -3.421f, 1.0f},
     {-0.22f, 0.438f, 0.872f, 0.0f},
     17,
     0.6f,
     1,
     0.4f,
     mantleMeshUv[1],
     {0},
     {-0.32f, -5.877f, 0.505f, 0.0f}},
};

static Cloth4DCol tapeMeshCols[5];

static Cloth4DCfg tapeMesh = {
    5, 6, 0, 0, 0x59, 0x59, 0x59, 0x80, "b_mantle", tapeMeshCols, 11.352f, 0,
};

static float tapeMeshUv[5][6][2] = {
    {{0.004f, 0.466f},
     {0.003f, 0.373f},
     {0.002f, 0.28f},
     {0.002f, 0.187f},
     {0.001f, 0.093f},
     {0.0f, 0.0f}},
    {{0.992f, 0.466f},
     {0.993f, 0.374f},
     {0.994f, 0.281f},
     {0.995f, 0.189f},
     {0.995f, 0.096f},
     {0.996f, 0.004f}},
    {{0.488f, 0.465f},
     {0.487f, 0.372f},
     {0.486f, 0.279f},
     {0.486f, 0.186f},
     {0.485f, 0.093f},
     {0.484f, 0.0f}},
    {{0.752f, 0.466f},
     {0.752f, 0.373f},
     {0.753f, 0.28f},
     {0.753f, 0.187f},
     {0.754f, 0.093f},
     {0.754f, 0.0f}},
    {{0.256f, 0.466f},
     {0.255f, 0.374f},
     {0.255f, 0.281f},
     {0.255f, 0.189f},
     {0.254f, 0.096f},
     {0.254f, 0.004f}},
};

static Cloth4DCol tapeMeshCols[5] = {
    {8.261f,
     {0},
     {-9.427f, 105.429f, -13.729f, 1.0f},
     {-0.021f, 0.835f, -0.549f, 0.0f},
     18,
     0.2f,
     17,
     0.8f,
     tapeMeshUv[0],
     {0},
     {-0.672f, -7.233f, -3.933f, 0.0f}},
    {8.03f,
     {0},
     {-5.611f, 104.027f, -14.75f, 1.0f},
     {-0.107f, 0.664f, -0.74f, 0.0f},
     17,
     1.0f,
     -1,
     0.0f,
     tapeMeshUv[4],
     {0},
     {-0.25f, -6.953f, -4.009f, 0.0f}},
    {8.355f,
     {0},
     {0.078f, 105.776f, -15.346f, 1.0f},
     {0.004f, 0.647f, -0.763f, 0.0f},
     32,
     1.0f,
     -1,
     0.0f,
     tapeMeshUv[2],
     {0},
     {-0.016f, -7.303f, -4.06f, 0.0f}},
    {8.03f,
     {0},
     {5.611f, 104.027f, -14.75f, 1.0f},
     {0.11f, 0.664f, -0.74f, 0.0f},
     2,
     1.0f,
     -1,
     0.0f,
     tapeMeshUv[3],
     {0},
     {0.25f, -6.953f, -4.009f, 0.0f}},
    {8.26f,
     {0},
     {9.43f, 105.429f, -13.731f, 1.0f},
     {0.021f, 0.835f, -0.549f, 0.0f},
     3,
     0.2f,
     2,
     0.8f,
     tapeMeshUv[1],
     {0},
     {0.671f, -7.233f, -3.933f, 0.0f}},
};

static Cloth4DCol tapeBMeshCols[2];

static Cloth4DCfg tapeBMesh = {
    2, 5, 0, 0, 0x59, 0x59, 0x59, 0x80, "tape_b", tapeBMeshCols, 2.48f, 0,
};

/* the light-line work LightLineGeo sets up (MAIN.MAP boy.o .sdata), after the
   third mesh's texture name in the TU's .sdata */
LightLineExt *llExtGeo = 0;

static float tapeBMeshUv[2][5][2] = {
    {{0.005f, 0.992f}, {0.251f, 0.992f}, {0.497f, 0.991f}, {0.743f, 0.99f}, {0.99f, 0.99f}},
    {{0.01f, 0.008f}, {0.257f, 0.008f}, {0.503f, 0.008f}, {0.749f, 0.008f}, {0.995f, 0.008f}},
};

static Cloth4DCol tapeBMeshCols[2] = {
    {1.825f,
     {0},
     {8.241f, 119.005f, -10.755f, 1.0f},
     {0.846f, 0.163f, 0.508f, 0.0f},
     33,
     1.0f,
     -1,
     0.0f,
     tapeBMeshUv[0],
     {0},
     {0.127f, -0.933f, -1.563f, 0.0f}},
    {1.567f,
     {0},
     {8.546f, 116.569f, -10.402f, 1.0f},
     {0.846f, 0.163f, 0.508f, 0.0f},
     33,
     1.0f,
     -1,
     0.0f,
     tapeBMeshUv[1],
     {0},
     {0.486f, -0.719f, -1.305f, 0.0f}},
};

static Cloth4DCol tapeBoro1MeshCols[2];

static Cloth4DCfg tapeBoro1Mesh = {
    2, 5, 0, 0, 0x59, 0x59, 0x59, 0x80, "tape_boro", tapeBoro1MeshCols, 2.277f, 0,
};

static float tapeBoro1MeshUv[2][5][2] = {
    {{0.023f, 0.008f}, {0.26f, 0.009f}, {0.496f, 0.01f}, {0.732f, 0.012f}, {0.969f, 0.013f}},
    {{0.117f, 0.987f}, {0.333f, 0.987f}, {0.548f, 0.987f}, {0.764f, 0.987f}, {0.979f, 0.987f}},
};

static Cloth4DCol tapeBoro1MeshCols[2] = {
    {2.166f,
     {0},
     {-7.434f, 118.357f, -5.971f, 1.0f},
     {-0.797f, 0.185f, 0.575f, 0.0f},
     33,
     1.0f,
     -1,
     0.0f,
     tapeBoro1MeshUv[0],
     {0},
     {-1.501f, -0.748f, -1.371f, 0.0f}},
    {2.19f,
     {0},
     {-7.644f, 120.421f, -6.91f, 1.0f},
     {-0.797f, 0.185f, 0.575f, 0.0f},
     33,
     1.0f,
     -1,
     0.0f,
     tapeBoro1MeshUv[1],
     {0},
     {-1.632f, -0.648f, -1.309f, 0.0f}},
};

static Cloth4DCol tapeBoro2MeshCols[2];

static Cloth4DCfg tapeBoro2Mesh = {
    2, 5, 0, 0, 0x59, 0x59, 0x59, 0x80, "tape_boro", tapeBoro2MeshCols, 3.186f, 0,
};

static float tapeBoro2MeshUv[2][5][2] = {
    {{0.117f, 0.987f}, {0.313f, 0.988f}, {0.509f, 0.988f}, {0.705f, 0.989f}, {0.901f, 0.99f}},
    {{0.211f, 0.008f}, {0.406f, 0.007f}, {0.6f, 0.007f}, {0.795f, 0.006f}, {0.99f, 0.005f}},
};

static Cloth4DCol tapeBoro2MeshCols[2] = {
    {1.891f,
     {0},
     {-2.205f, 114.505f, -18.416f, 1.0f},
     {-0.235f, 0.131f, -0.963f, 0.0f},
     33,
     1.0f,
     -1,
     0.0f,
     tapeBoro2MeshUv[1],
     {0},
     {1.274f, -0.694f, -1.213f, 0.0f}},
    {2.352f,
     {0},
     {-0.858f, 117.392f, -18.42f, 1.0f},
     {-0.235f, 0.131f, -0.963f, 0.0f},
     33,
     1.0f,
     -1,
     0.0f,
     tapeBoro2MeshUv[0],
     {0},
     {1.58f, -0.946f, -1.463f, 0.0f}},
};

/* RECONSTRUCTION, read from the ROM.  The 104-byte work record InitBoyGeo
   allocates and hangs at the object's work word: the crown in use and the
   head, body and three crown display objects, the stonized state and its BG
   animation, the five cloths, the pool reflection mesh, the water drops and
   the drip state actionOfWater runs. */
typedef struct BoyWork { /* field names derived */
    int crown;           /* 0x00, 1 or 2 picks crown1 or crown2, else crown0 */
    Sub15C *head;        /* 0x04 */
    Sub15C *body;        /* 0x08 */
    char *crown0;        /* 0x0C */
    char *crown1;        /* 0x10 */
    char *crown2;        /* 0x14 */
    int stone;           /* 0x18 */
    int stoneAnim;       /* 0x1C */
    /* the cloth handles InitCloth4D returns, held as char *: typed Cloth4D * or
       void * their stores in InitBoyGeo move across the 0x554 store (measured) */
    char *mantle;           /* 0x20 */
    char *tape;             /* 0x24 */
    char *tapeBoro1;        /* 0x28 */
    char *tapeB;            /* 0x2C */
    char *tapeBoro2;        /* 0x30 */
    PoolMesh refl;          /* 0x34 */
    WaterDotWork *waterDot; /* 0x54 */
    int wet;                /* 0x58 */
    float dripVel;          /* 0x5C */
    float drip;             /* 0x60 */
    float detail;           /* 0x64 */
} BoyWork;

void dispClothes(char *gobj)
{
    BoyWork *w = GOBJ_SUB(gobj)->f_830;
    char *x;

    x = (char *)GOBJ_SUB(gobj)->p_874;
    DispCloth4D((Cloth4D *)w->mantle, x + 0x40, x);
    x = (char *)GOBJ_SUB(gobj)->p_874;
    DispCloth4D((Cloth4D *)w->tape, x + 0x40, x);
    x = (char *)GOBJ_SUB(gobj)->p_874;
    DispCloth4D((Cloth4D *)w->tapeB, x + 0x40, x);
    x = (char *)GOBJ_SUB(gobj)->p_874;
    DispCloth4D((Cloth4D *)w->tapeBoro1, x + 0x40, x);
    x = (char *)GOBJ_SUB(gobj)->p_874;
    DispCloth4D((Cloth4D *)w->tapeBoro2, x + 0x40, x);
}

/* census execClothes, a file static: girl.c has its own static twin of this name.
 * Listing rows 103-126. The five else-arm calls are one nested inline helper
 * (row 116 is its body, rows 118-122 its code-free calls), the construct this
 * programmer's clothAnimation.c uses for interHalf: each inlined copy
 * rematerialises the 0.98f literal at its own call, which is why the ROM loads
 * that constant five times, and the two arm-scoped values the helper reads are
 * homed in the frame and reloaded after every call. The helper's name and the
 * two locals' names are ours (a nested inline leaves no symbol). */
static void execClothes(char *gobj)
{
    BoyWork *w = GOBJ_SUB(gobj)->f_830;

    if (w->wet != 0) {
        GetCloth4DWithDetail(w->mantle, 0.0f, 0.5f, 1.0f, 0.0f);
        GetCloth4DWithDetail(w->tape, 0.0f, 0.5f, 1.0f, 0.0f);
        GetCloth4D(w->tapeB, 5.0f, 0.98f);
        GetCloth4D(w->tapeBoro1, 5.0f, 0.98f);
        GetCloth4D(w->tapeBoro2, 5.0f, 0.98f);
        w->detail = 1.0f;
    } else {
        float f = w->detail;
        float x = f * 5.0f + 3.0f;
        float wt = 1.0f - f;
        __inline__ void setClothDetail(void *cloth)
        {
            GetCloth4DWithDetail(cloth, x, 0.98f, 1.0f, wt);
        }

        setClothDetail(w->mantle);
        setClothDetail(w->tape);
        setClothDetail(w->tapeB);
        setClothDetail(w->tapeBoro1);
        setClothDetail(w->tapeBoro2);
        w->detail *= 0.999f;
    }
}

/* the one LightLineExt InitLightLineGeo fills; its definition closes the
   TU's .data, after the sync marker colours */
static LightLineExt lightLineExt; /* derived name */

LightLineExt *InitLightLineGeo(char *gobj, float *pos)
{
    LLVec v = {pos[0] + 500.0f, pos[1], pos[2] + 200.0f, 1.0f};
    int i;
    int j;
    int n;
    float f;

    llExtGeo = &lightLineExt;
    llExtGeo->phase = iosMallocDebug(ios_partition_sugipon, 0x190, "src/boy.c", 161);
    llExtGeo->speed = iosMallocDebug(ios_partition_sugipon, 0x190, "src/boy.c", 162);
    llExtGeo->line = iosMallocDebug(ios_partition_sugipon, 0x190, "src/boy.c", 163);
    for (i = 0; i < 100; i++) {
        llExtGeo->phase[i] = 0.0f;
        llExtGeo->speed[i] = random_unit() * 0.1f + 0.01f;
        llExtGeo->line[i] = iosMallocDebug(ios_partition_sugipon, 0x140, "src/boy.c", 168);
        CopyVector(llExtGeo->line[i], &v);
        llExtGeo->line[i][0].x += (float)((i - 0x32) * 5);
        for (j = 1; j < 20; j++) {
            CopyVector(&llExtGeo->line[i][j], &llExtGeo->line[i][j - 1]);
            if (random_unit() < 0.9f) {
                if (j & 1) {
                    llExtGeo->line[i][j].y -= (float)((int)(random_unit() * 10.0f) + 1) * 5.0f;
                } else {
                    n = (int)(random_signed() * 10.0f) + 1;
                    llExtGeo->line[i][j].x += (float)n * 5.0f;
                }
            } else {
                f = (float)((int)(random_unit() * 10.0f) + 1) * 5.0f;
                llExtGeo->line[i][j].y -= f;
                llExtGeo->line[i][j].x += f;
            }
        }
    }
    return llExtGeo;
}

inline void LightLineGeo(void)
{
    int i;

    for (i = 0; i < 100; i++) {
        llExtGeo->phase[i] += llExtGeo->speed[i];
        if (llExtGeo->phase[i] > 1.0f) {
            llExtGeo->speed[i] = random_unit() * 0.01f + 0.001f;
            llExtGeo->phase[i] = 0;
        }
    }
}

void LightLineDL(void)
{
    int i;
    /* The ROM gives i a frame slot of its own at 0x0, ahead of the five
       16-byte records: this helper reads the enclosing loop's index rather
       than taking it as an argument, which puts i in the parent's frame at
       the point the helper is declared.  It is inlined at both call sites,
       so no static chain is built. */
    inline int LightLineVtx(LLVec * dst, float ph)
    {
        float f = ph * 18.99998f;
        LLVec *p = llExtGeo->line[i];

        sceVu0InterVector(dst, &p[(int)f + 1], &p[(int)f], f - (int)f);

        dst->w = 1.0f;

        return (int)f;
    }
    LLColor c0;
    LLColor c1;
    LLVec p0;
    LLVec p1;
    LLVec mid;
    float t;
    float bright;
    float d;
    int n0;
    int n1;
    int r0, g0, b0;
    int r1, g1, b1;

    gif_StartPacketPri(11);
    memset(&c0, 0, sizeof(c0));
    c0.a = 255;
    memset(&c1, 0, sizeof(c1));
    c1.a = 255;
    bright = 2.5f;
    gif_SetAlpha(1, 5, 255);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());

    for (i = 0; i < 100; i++) {
        for (t = 0.0f; t + 0.05f < llExtGeo->phase[i] && t + 0.05f < 0.4f; t += 0.05f) {
            d = 0.4f - t;
            n0 = LightLineVtx(&p0, llExtGeo->phase[i] - t);
            n1 = LightLineVtx(&p1, llExtGeo->phase[i] - t - 0.05f);

            r0 = d * 32.0f * bright;
            g0 = d * 128.0f * bright;
            b0 = d * 255.0f * bright;

            r1 = (d - 0.05f) * 32.0f * bright;
            g1 = (d - 0.05f) * 128.0f * bright;
            b1 = (d - 0.05f) * 255.0f * bright;

            c0.r = (r0 < 256) ? r0 : 255;
            c0.g = (g0 < 256) ? g0 : 255;
            c0.b = (b0 < 256) ? b0 : 255;

            c1.r = (r1 < 256) ? r1 : 255;
            c1.g = (g1 < 256) ? g1 : 255;
            c1.b = (b1 < 256) ? b1 : 255;

            if (n0 == n1) {
                DrawLineG(&p0, &c0, &p1, &c1, 0x800000);
            } else {
                CopyVector(&mid, &llExtGeo->line[i][n0]);
                DrawLineG(&p0, &c0, &mid, &c0, 0x800000);
                DrawLineG(&mid, &c0, &p1, &c1, 0x800000);
            }
        }
    }
    gif_EndPacket();
}

inline void SelectBoyCrown(char *a0, int a1)
{
    ((BoyWork *)GOBJ_SUB(a0)->f_830)->crown = a1;
}

/* The display-list record's 0x38 word carries single bits set and cleared with
   ld/or/sd and ld/and/sd, and a 16-bit field two bytes into the same
   container reached with a plain sh; the same union src/enemyParts.c uses. */

/* The two points the boy's mantle hangs from, once for each cloth.  MAIN.MAP
   names no symbol in boy.o's .data, so these names are ours. */
static ClothHangCfg mantleHang[3] = {
    {1, -5.0f, 30.0f, 20.0f, 1, {0}, 0.0f, -10.0f, {0}, 1.0f, -1.0f, {0}},
    {1, -15.0f, 15.0f, 20.0f, 0, {0}, 0.0f, -10.0f, {0}, 1.0f, -1.0f, {0}},
    {-1, 0.0f, 0.0f, 0.0f, 0, {0}, 0.0f, 0.0f, {0}, 0.0f, 0.0f, {0}},
};

static ClothHangCfg tapeHang[3] = {
    {1, -5.0f, 30.0f, 20.0f, 1, {0}, 0.0f, 13.0f, {0}, 1.0f, -1.0f, {0}},
    {1, -15.0f, 15.0f, 20.0f, 0, {0}, 0.0f, 13.0f, {0}, 1.0f, -1.0f, {0}},
    {-1, 0.0f, 0.0f, 0.0f, 0, {0}, 0.0f, 0.0f, {0}, 0.0f, 0.0f, {0}},
};

BoyWork *InitBoyGeo(char *gobj, void *csv)
{
    BoyWork *w;
    BoyWork *p;
    int i;

    w = iosMallocDebug(ios_partition_sugipon, sizeof(BoyWork), "src/boy.c", 280);
    /* the work word stored and read back as char *: the bytes pin that alias
       set here (the cloth stores below must stay ordered against the reload) */
    *(char **)(*(char **)(gobj + 0x15C) + 0x830) = (char *)w;
    p = (BoyWork *)*(char **)(*(char **)(gobj + 0x15C) + 0x830);
    p->mantle = (char *)InitCloth4D(gobj, &mantleMesh, mantleHang);
    p->tape = (char *)InitCloth4D(gobj, &tapeMesh, tapeHang);
    p->tapeB = (char *)InitCloth4D(gobj, &tapeBMesh, 0);
    p->tapeBoro1 = (char *)InitCloth4D(gobj, &tapeBoro1Mesh, 0);
    p->tapeBoro2 = (char *)InitCloth4D(gobj, &tapeBoro2Mesh, 0);
    *(int *)(*(char **)(gobj + 0x15C) + 0x554) = 1;
    w->head = (Sub15C *)CSVSYSTEM_InitDObj(2, csv);
    w->body = (Sub15C *)CSVSYSTEM_InitDObj(3, csv);
    if (w->body->f_C != 0) {
        iosFree(w->body->f_C & 0xFFFFFFF);
    }
    if (w->body->f_10 != 0) {
        iosFree(w->body->f_10 & 0xFFFFFFF);
    }
    w->body->f_C = 0;
    w->body->f_10 = 0;
    w->body->f_C = (int)iosMallocDebug(ios_partition_seki, 128, "src/boy.c", 291);
    w->body->f_10 = (int)iosMallocDebug(ios_partition_seki, 32, "src/boy.c", 291);
    w->body->f_8 = 2;
    if ((int)w->body->p_870 != 0) {
        iosFree((int)w->body->p_870 & 0xFFFFFFF);
    }
    w->body->p_870 = iosMallocDebug(ios_partition_seki, 160, "src/boy.c", 291);
    for (i = 0; i < 2; i++) {
        ((struct DObjNode *)(i * 80 + (int)w->body->p_870))->flags.ll &= ~1;
        ((struct DObjNode *)(i * 80 + (int)w->body->p_870))->flags.ll &= ~2;
        ((struct DObjNode *)(i * 80 + (int)w->body->p_870))->pos[0] = 0.0f;
        ((struct DObjNode *)(i * 80 + (int)w->body->p_870))->pos[1] = 0.0f;
        ((struct DObjNode *)(i * 80 + (int)w->body->p_870))->pos[2] = 0.0f;
        ((struct DObjNode *)(i * 80 + (int)w->body->p_870))->pos[3] = 1.0f;
        ((struct DObjNode *)(i * 80 + (int)w->body->p_870))->flags.ll &= ~4;
        ((struct DObjNode *)(i * 80 + (int)w->body->p_870))->fade = 0.0f;
        ((struct DObjNode *)(i * 80 + (int)w->body->p_870))->alpha = 1.0f;
        *(short *)(i * 80 + (int)w->body->p_870 + 0x3A) = 0;
        ((struct DObjNode *)(i * 80 + (int)w->body->p_870))->scale[0] = 1.0f;
        ((struct DObjNode *)(i * 80 + (int)w->body->p_870))->scale[1] = 1.0f;
        ((struct DObjNode *)(i * 80 + (int)w->body->p_870))->scale[2] = 1.0f;
    }
    w->body->dispType = 2;
    w->crown0 = CSVSYSTEM_InitDObj(1, csv);
    w->crown1 = CSVSYSTEM_InitDObj(15, csv);
    w->crown2 = CSVSYSTEM_InitDObj(16, csv);
    (*(BoyWork **)(*(char **)(gobj + 0x15C) + 0x830))->crown = 0;
    sceVu0UnitMatrix(w->crown0 + 0x20);
    InitMotionOrient(gobj, 0, 0x503, 0, 0xC, 0);
    InitLightLineGeo(gobj, csv);
    SetLodLevel(gobj, 2);
    w->stone = 0;
    w->stoneAnim = 0;
    w->refl.nrow = 20;
    w->refl.ncol = 20;
    w->refl.f_8 = 300.0f;
    w->refl.f_C = 300.0f;
    w->refl.color = 0x80808080;
    InitLimitedPoolReflactionMesh(&w->refl);
    w->waterDot = AllocWaterDot((int)gobj, 30, 5);
    w->wet = 0;
    w->dripVel = 0.0f;
    w->drip = 0.0f;
    w->detail = 0.0f;
    return w;
}

typedef struct MotSyncPair { /* 0x08 */
    int girl;                /* 0x00 */
    int boy;                 /* 0x04 */
} MotSyncPair;

extern MotSyncPair motSyncPairs[]; /* derived name */

/* the two wire spheres the girl-to-boy position sync draws when the debug flag
   is on: blue for the girl, orange for the boy */
static int girlSyncMarkerColor[4] = {64, 96, 128, 128};

static int boySyncMarkerColor[4] = {255, 96, 64, 128};

static LightLineExt lightLineExt = {0, 0, 0};

void synchronizeMotionOutputOriginForGirl(char *gobj)
{
    float d[4];
    float v[4];
    MotSyncPair *p;
    int i;
    int okA = 0;
    int okB = 0;

    if (girlGObj != 0) {
        p = motSyncPairs;
        for (i = 0; i < 5; i++) {
            if (GOBJ_SUB(girlGObj)->f_4A0 == p->girl) {
                okA = 1;
            }
            if (GOBJ_SUB(gobj)->f_4A0 == p->boy) {
                okB = 1;
            }
            p++;
        }
        if (okA != 0 && okB != 0) {
            _InterVectorXYZ(v, (char *)GOBJ_SUB(girlGObj) + 0x100, (char *)GOBJ_SUB(gobj) + 0x100,
                            0.9f);
            _SubVectorXYZ(d, v, (char *)GOBJ_SUB(girlGObj) + 0x100);
            d[1] = 0.0f;
            GetRootPosition(v, girlGObj);
            _AddVectorXYZ(v, v, d);
            SetDirectRootPositionNoFitting(girlGObj, v);
            if (debug_wallhitcoldisp != 0) {
                gif_StartPacketPri(0xB);
                gif_SetAlpha(1, 5, 0x80);
                _UnitMatrix(MatrixDrive_GetMatrix());
                MatrixDrive_TransMatrixV((char *)GOBJ_SUB(girlGObj) + 0x100);
                prim_DispWireSphere(10.0f, girlSyncMarkerColor, 16, 8);
                _UnitMatrix(MatrixDrive_GetMatrix());
                MatrixDrive_TransMatrixV((char *)GOBJ_SUB(gobj) + 0x100);
                prim_DispWireSphere(10.0f, boySyncMarkerColor, 16, 8);
                gif_EndPacket();
            }
        }
    }
}

void actionOfWater(char *gobj)
{
    float pos[4];
    BoyWork *w = GOBJ_SUB(gobj)->f_830;
    int node;

    ExecWaterDot((int)w->waterDot);
    if (GOBJ_SUB(gobj)->f_4D8 == 0xB) {
        w->wet = 1;
        w->dripVel = 5.0f;
        w->drip = 0.0f;
    } else {
        w->wet = 0;
        w->dripVel = w->dripVel * 0.98f;
        w->drip = w->drip + w->dripVel;
        if (1.0f < w->drip) {
            node = GetSkeltonFocusNode(gobj, 0x16);
            CopyVector(pos, (char *)GOBJ_SUB(gobj)->f_C + (node << 6) + 0x30);
            EntryWaterDot((int)w->waterDot, pos, ZeroVector, 8.0f);
            node = GetSkeltonFocusNode(gobj, 0x6);
            CopyVector(pos, (char *)GOBJ_SUB(gobj)->f_C + (node << 6) + 0x30);
            EntryWaterDot((int)w->waterDot, pos, ZeroVector, 8.0f);
            node = GetSkeltonFocusNode(gobj, 0x2C);
            CopyVector(pos, (char *)GOBJ_SUB(gobj)->f_C + (node << 6) + 0x30);
            EntryWaterDot((int)w->waterDot, pos, ZeroVector, 10.0f);
            w->drip = 0.0f;
        }
    }
}

void synchronizeMotionOutputOriginForGirl(char *gobj);
void actionOfWater(char *gobj);

void BoyGeo(char *gobj)
{
    HandManager(gobj);
    ExecMotionOrient(gobj);
    synchronizeMotionOutputOriginForGirl(gobj);
    execClothes(gobj);
    ExecuteSlipProc(gobj);
    SetActressLight(gobj, 0x23, 0x2C, 0x1D7);
    if (CylinderCollision(gobj, 4, 50.0f, 50.0f, 0.7f) != 0) {
        iosOmSendMail(gobj, 6, gobj);
    }
    CylinderCollision(gobj, 2, ACTGame_FLAG_TETSUNAGI() != 0 ? 15.0f : 30.0f, 50.0f, 0.7f);
    actionOfWater(gobj);
}

void dispSubParts(char *gobj)
{
    BoyWork *w = GOBJ_SUB(gobj)->f_830;
    char *a;
    char *c;
    int node;

    a = (char *)w->head;
    node = GetSkeltonFocusNode(gobj, 35);
    CopyMatrix(*(char **)(a + 0xC), (char *)GOBJ_SUB(gobj)->f_C + (node << 6));
    p2o_DispVU1DObj(w->head);
    a = (char *)w->body;
    node = GetSkeltonFocusNode(gobj, 0x14);
    CopyMatrix(*(char **)(a + 0xC), (char *)GOBJ_SUB(gobj)->f_C + (node << 6));
    c = (char *)w->body->f_C + 0x40;
    node = GetSkeltonFocusNode(gobj, 0x4);
    CopyMatrix(c, (char *)GOBJ_SUB(gobj)->f_C + (node << 6));
    p2o_DispVU1DObjMulti(w->body);
}

void dispCrown(char *gobj)
{
    BoyWork *w = GOBJ_SUB(gobj)->f_830;
    int node = GetSkeltonFocusNode(gobj, 0x23);
    char *obj;

    switch (w->crown) {
    case 1:
        obj = w->crown1;
        break;
    case 2:
        obj = w->crown2;
        break;
    default:
        obj = w->crown0;
        break;
    }
    CopyMatrix(MatrixDrive_GetMatrix(), (char *)GOBJ_SUB(gobj)->f_C + (node << 6));
    MatrixDrive_RotMatrixX(-0x8000);
    CopyMatrix(*(char **)(obj + 0xC), MatrixDrive_GetMatrix());
    reg_DispAccessoryWithShadow((Sub15C *)obj, GOBJ_SUB(gobj));
}

inline void SetBoyStonizedVisual(char *a0)
{
    BoyWork *crown = GOBJ_SUB(a0)->f_830;
    AdjustMotionHeightToNearestField(a0);
    crown->stone = 1;
    crown->stoneAnim = 0;
    GOBJ_SUB(a0)->f_62C = 0;
}

/* kept local: float (int, void *, void *, float) here, float (int, float, void *, void *) in StageAnimation.h */
extern float stage_PlayBgAnimation(int obj, void *a1, void *a2, float f);
void dispSubParts(char *gobj);

void BoyDL(char *gobj)
{
    char pos[0x10];
    char quat[0x10];
    BoyWork *w = GOBJ_SUB(gobj)->f_830;
    PoolMesh *m;
    Sub15C *sub;
    int r;

    ExecutePauseSlipProc(gobj);
    if (w->stone != 0) {
        GetRootPosition(pos, gobj);
        GetRootQuaternion(quat, gobj);
        RotQuaternionY(quat, -0x8000);
        r = (int)stage_PlayBgAnimation(0x1E8, pos, quat, (float)w->stoneAnim);
        if (systemStatus[5] == 0 && r != -1) {
            w->stoneAnim = r;
        }
    } else {
        p2o_SetDefaultEnviroment();
        p2o_DispVU1(gobj);
        dispSubParts(gobj);
        dispCrown(gobj);
        dispClothes(gobj);
    }
    if (stage_no == 0x27 && 20.0f < GOBJ_SUB(gobj)->f_644 && GOBJ_SUB(gobj)->f_648 != 0 &&
        CheckPoolHasGridMesh((char *)GOBJ_SUB(gobj)->f_648) == 0) {
        sub = GOBJ_SUB(gobj);
        m = (PoolMesh *)(sub->f_830 + 0x34);
        SetLimitedPoolReflactionMesh(m, sub->f_648, gobj);
        DispLimitedPoolReflactionMesh(m);
    }
    DispWaterDot((int)w->waterDot);
}
