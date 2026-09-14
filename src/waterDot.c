#include "common.h"
#include "sugiCommon.h"

typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) VECTOR;

/* One dot of the splash: 0x30 bytes, sized by AllocWaterDot's `mult ,0x30`. */
typedef struct WaterDot {
    /* 0x00 */ int used;
    /* 0x04 */ int frame;
    /* 0x08 */ int life;
    /* 0x0C */ float scale;
    /* 0x10 */ VECTOR pos;
    /* 0x20 */ VECTOR vel;
} WaterDot; /* 0x30 */

/* The per-emitter work AllocWaterDot mallocs (0x1C bytes) and registers in
 * D_00724BC0[D_0063BC48++]. */
typedef struct WaterDotWork {
    /* 0x00 */ int num;        /* ring size (AllocWaterDot's 2nd argument) */
    /* 0x04 */ int cur;        /* next ring slot */
    /* 0x08 */ WaterDot *dot;  /* num entries */
    /* 0x0C */ int num2;       /* the second ring's size */
    /* 0x10 */ int cur2;       /* the second ring's slot */
    /* 0x14 */ WaterDot *dot2; /* num2 entries */
    /* 0x18 */ int gobj;       /* the emitter the splash follows */
} WaterDotWork;                /* 0x1C */

extern WaterDotWork *D_00724BC0[]; /* the registered emitters */
extern int D_0063BC48;             /* how many are registered */
extern void _AddVectorXYZ(VECTOR *dst, VECTOR *a, VECTOR *b);
extern void setWaterDot(WaterDot *dot, VECTOR *pos, VECTOR *vel);
/* prototypes: their order is the inline tail's emission order */
void InitializeWaterDot(void);
void EntryWaterDot(WaterDotWork *w, VECTOR *pos, VECTOR *vel, float range);

inline void InitializeWaterDot(void)
{
    int i;

    D_0063BC48 = 0;
    for (i = 4; i >= 0; i--) {
        D_00724BC0[i] = 0;
    }
}

extern void *iosMallocDebug(void *heap, int size, char *file, int line);
extern void *D_0063A438;  /* the heap partition every waterDot record comes from */
extern char D_00621388[]; /* "src/waterDot.c", the __FILE__ the malloc tag carries */

/* The three .data templates AllocWaterDot block-copies, in ROM order at
   0x4ED170, 0x4ED190 and 0x4ED1C0. Each is an explicit initialiser, which is
   why the all-zero first one sits in .data rather than .bss. */
static WaterDotWork initWaterDotWork = {0, 0, 0, 0, 0, 0, 0};

static WaterDot initWaterDot = {
    0, 0, 128, 1.0f, {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}};

static WaterDot initWaterDot2 = {0, 0, 0, 0.0f, {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}};

/* waterDot.c:27-47 in the PAL listing. The line numbers the three
   iosMallocDebug calls carry ARE their source lines, 29, 33 and 38. */
WaterDotWork *AllocWaterDot(int gobj, int num, int num2)
{
    WaterDotWork *w;
    int i;

    w = iosMallocDebug(D_0063A438, sizeof(WaterDotWork), D_00621388, 29);
    *w = initWaterDotWork;

    w->num = num;
    w->dot = iosMallocDebug(D_0063A438, num * sizeof(WaterDot), D_00621388, 33);
    for (i = 0; i < num; i++)
        w->dot[i] = initWaterDot;

    w->num2 = num2;
    w->dot2 = iosMallocDebug(D_0063A438, num2 * sizeof(WaterDot), D_00621388, 38);
    for (i = 0; i < num2; i++)
        w->dot2[i] = initWaterDot2;

    w->gobj = gobj;

    D_00724BC0[D_0063BC48] = w;
    D_0063BC48++;

    return w;
}

extern void CopyVector(void *dst, void *src);

void setWaterDot(WaterDot *dot, VECTOR *pos, VECTOR *vel)
{
    int n;

    dot->used = 1;
    dot->frame = 0;
    n = (int)(crt_random_unit() * 64.0f + 32.0f);
    dot->life = n;
    dot->scale = 1.0 - (256 - n) * 0.00078125;
    CopyVector(&dot->pos, pos);
    CopyVector(&dot->vel, vel);
}

inline void EntryWaterDot(WaterDotWork *w, VECTOR *pos, VECTOR *vel, float range)
{
    VECTOR v = {random_signed_b() * range, random_signed_b() * range, random_signed_b() * range,
                1.0f};

    _AddVectorXYZ(&v, &v, pos);
    setWaterDot(&w->dot[w->cur], &v, vel);
    if (++w->cur == w->num)
        w->cur = 0;
}

extern int D_0028F4C0[];
extern void GetRootPosition(void *out, int gobj);
extern void *GetWindVector(int a0, void *pos);
extern void _ScaleVectorXYZ(void *dst, void *src, float k);

/* waterDot.c:71-78 in the PAL listing, rows inside ExecWaterDot's span but
   above its def line: a static helper with no out-of-line copy, inlined at
   its one call site. It ages one dot and reports whether it has expired. */
static inline int stepWaterDot(WaterDot *p)
{
    if (p->frame++ < 30) {
        /* The gravity step is the frame-rate quotient written out TWICE rather
           than held in a local, the same spelling src/clothAnimation.c uses for
           the identical term. cse collapses the second copy, but expanding it
           moves the p->scale argument load one issue slot later, which is the
           ROM's order. */
        p->vel.y += 60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 0.5f *
                    (60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
        _ScaleVectorXYZ(&p->vel, &p->vel, p->scale);
        _AddVectorXYZ(&p->pos, &p->pos, &p->vel);

        return 0;
    }
    return 1;
}

void ExecWaterDot(WaterDotWork *w)
{
    VECTOR wind;
    VECTOR pos;
    WaterDot *p;
    WaterDot *q;
    int i;

    GetRootPosition(&pos, w->gobj);
    _ScaleVectorXYZ(&wind, GetWindVector(0, &pos), 0.2f);

    p = w->dot;
    for (i = 0; i < w->num; i++) {
        if (p->used != 0) {
            if (stepWaterDot(p) != 0) {
                p->used = 0;
            }
        }
        p++;
    }

    q = w->dot2;
    for (i = 0; i < w->num2; i++) {
        if (q->used != 0) {
            q->used = 0;
        }
        q++;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/waterDot", DispWaterDot);
