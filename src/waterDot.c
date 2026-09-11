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

INCLUDE_ASM("asm/nonmatchings/src/waterDot", AllocWaterDot);

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

/* ExecWaterDot's 0.2f, the TU pool's second slot, while that function is asm */
ASM_LIT4_SLOT(D_006396D4, 0.2f);
INCLUDE_ASM("asm/nonmatchings/src/waterDot", ExecWaterDot);
INCLUDE_ASM("asm/nonmatchings/src/waterDot", DispWaterDot);
