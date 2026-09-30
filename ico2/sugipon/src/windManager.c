#include "sugiCommon.h"

/* PAL listing (windManager.c): SetWindManager (line 21) and InitWindManager
 * (35) are inline and expand into ReinitWindManager, whose rows are exactly
 * InitWindManager's plus its own trailing line 72; ExecWindManager is the
 * TU's only plain function.  The object order Exec, Reinit, Set, Init,
 * GetRegularized is the prototype order of the deferred inline tail. */
typedef struct WindParam {
    /* the splat label D_005F5E1C sits on this member; the entry's direction
       vector lives 0xC bytes in front of it. */
    float pos[3]; /* +0x00 */
    char pad0[0x8C - 0x0C];
    float amp;   /* +0x8C */
    float speed; /* +0x90 */
    char pad1[0x194 - 0x94];
} WindParam;

extern WindParam D_005F5E1C[];

/* The TU's .sdata (MAIN.MAP names nothing in it), in ROM order: the wind kind,
   the base speed and its variance with their reciprocals, and the gust state. */
static int windKind = -1; /* derived name */

static float windSpeed = 0; /* derived name */

static float windSpeedInv = 0; /* derived name */

static float windVariance = 0; /* derived name */

static float windVarianceInv = 0; /* derived name */

static float gustAim = 0; /* derived name */

static float gustSpeed = 0; /* derived name */

static int gustTimer = 0; /* derived name */

extern int D_0028F4C0[];
/* kept local: this TU's uses of InitWindField do not fit the prototype in windField.h */
extern void InitWindField(int a0, float *a1, float *a2, float a3);
/* kept local: this TU's uses of ExecWindField do not fit the prototype in windField.h */
extern void ExecWindField(float f);
/* kept local: this TU's uses of GetWindVector do not fit the prototype in windField.h */
extern int GetWindVector(float *power, void *pos);

#include "windManager.h"

inline void SetWindManager(float a, float b, float c, float d, float e, float f, float g, float h)
{
    float buf1[4] = {a, b, c, 1.0f};
    float buf2[4] = {d, e, f, 0.0f};

    windSpeed = g;
    windSpeedInv = 1.0f / g;
    windVariance = h;
    windVarianceInv = 1.0f / h;
    gustAim = g;
    gustSpeed = g;
    InitWindField(1, buf1, buf2, g);
}

inline void InitWindManager(int no)
{
    float *pos = D_005F5E1C[no].pos;
    float *dir = (float *)&D_005F5E1C[no] - 3;

    SetWindManager(pos[0], pos[1], pos[2], dir[0], dir[1], dir[2], D_005F5E1C[no].speed,
                   D_005F5E1C[no].amp);
    windKind = no;
}

void ExecWindManager(void)
{
    gustTimer++;
    if (gustTimer >= 0x33) {
        float r = random_unit();
        gustTimer = 0;
        gustAim = windSpeed * ((r + r - 1.0f) * windVariance + 1.0f);
    }
    gustSpeed = gustSpeed + (gustAim - gustSpeed) * 0.1f;
    ExecWindField(gustSpeed);
}

inline float GetRegularizedWindSpeed(void *pos)
{
    float s;

    if (windSpeed == 0.0f || windVariance == 0.0f) {
        return 1.0f;
    }
    GetWindVector(&s, pos);
    return (s / (60.0f / (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1])) * windSpeedInv -
            (1.0f - windVariance)) *
           0.5f * windVarianceInv;
}

inline void ReinitWindManager(void)
{
    InitWindManager(windKind);
}
