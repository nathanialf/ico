#include "common.h"
#include "sugiCommon.h"

typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) VECTOR;
/* One dot of the splash: 0x30 bytes, sized by AllocWaterDot's `mult ,0x30`. */
typedef struct WaterDot {
    char unk[0x30];
} WaterDot;
/* The per-emitter work AllocWaterDot mallocs (0x1C bytes) and registers in
 * D_00724BC0[D_0063BC48++]. */
typedef struct WaterDotWork {
    /* 0x00 */ int num;         /* ring size (AllocWaterDot's 2nd argument) */
    /* 0x04 */ int cur;         /* next ring slot */
    /* 0x08 */ WaterDot *dot;   /* num entries */
} WaterDotWork;
extern WaterDotWork *D_00724BC0[];   /* the registered emitters */
extern int D_0063BC48;               /* how many are registered */
extern void _AddVectorXYZ(VECTOR *dst, VECTOR *a, VECTOR *b);
extern void setWaterDot(WaterDot *dot, VECTOR *pos, int kind);
/* prototypes: their order is the inline tail's emission order */
void InitializeWaterDot(void);
void EntryWaterDot(WaterDotWork *w, VECTOR *pos, int kind, float range);
inline void InitializeWaterDot(void)
{
    int i;

    D_0063BC48 = 0;
    for (i = 4; i >= 0; i--) {
        D_00724BC0[i] = 0;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/waterDot", AllocWaterDot);
INCLUDE_ASM("asm/nonmatchings/src/waterDot", setWaterDot);
inline void EntryWaterDot(WaterDotWork *w, VECTOR *pos, int kind, float range)
{
    VECTOR v = { random_signed_b() * range, random_signed_b() * range,
                 random_signed_b() * range, 1.0f };

    _AddVectorXYZ(&v, &v, pos);
    setWaterDot(&w->dot[w->cur], &v, kind);
    if (++w->cur == w->num)
        w->cur = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/waterDot", ExecWaterDot);
INCLUDE_ASM("asm/nonmatchings/src/waterDot", DispWaterDot);
