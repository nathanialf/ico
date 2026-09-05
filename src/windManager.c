#include "common.h"

/* PAL listing (windManager.c): SetWindManager (line 21) and InitWindManager
 * (35) are inline and expand into ReinitWindManager, whose rows are exactly
 * InitWindManager's plus its own trailing line 72; ExecWindManager is the
 * TU's only plain function.  The object order Exec, Reinit, Set, Init,
 * GetRegularized is the prototype order of the deferred inline tail. */
typedef struct WindParam {
    /* the splat label D_005F5E1C sits on this member; the entry's direction
       vector lives 0xC bytes in front of it. */
    float pos[3];          /* +0x00 */
    char  pad0[0x8C - 0x0C];
    float amp;             /* +0x8C */
    float speed;           /* +0x90 */
    char  pad1[0x194 - 0x94];
} WindParam;

extern WindParam D_005F5E1C[];
extern int D_0063BC60;
extern float D_0063BC64;
extern float D_0063BC68;
extern float D_0063BC6C;
extern float D_0063BC70;
extern float D_0063BC74;
extern float D_0063BC78;
extern int D_0063BC7C;
extern float D_00639708;
extern int D_0028F4C0[];
extern float _GetRandom(void);
extern void InitWindField(int a0, float *a1, float *a2, float a3);
extern void ExecWindField(float f);
extern int GetWindVector(float *power, void *pos);

/* prototypes: their order is the inline tail's emission order */
void ReinitWindManager(void);
void SetWindManager(float a, float b, float c, float d, float e, float f, float g, float h);
void InitWindManager(int no);
float GetRegularizedWindSpeed(void *pos);

inline void SetWindManager(float a, float b, float c, float d, float e, float f, float g, float h) {
    float buf1[4] = {a, b, c, 1.0f};
    float buf2[4] = {d, e, f, 0.0f};

    D_0063BC64 = g;
    D_0063BC68 = 1.0f / g;
    D_0063BC6C = h;
    D_0063BC70 = 1.0f / h;
    D_0063BC74 = g;
    D_0063BC78 = g;
    InitWindField(1, buf1, buf2, g);
}
inline void InitWindManager(int no) {
    float *pos = D_005F5E1C[no].pos;
    float *dir = (float *)&D_005F5E1C[no] - 3;

    SetWindManager(pos[0], pos[1], pos[2], dir[0], dir[1], dir[2],
                   D_005F5E1C[no].speed, D_005F5E1C[no].amp);
    D_0063BC60 = no;
}
void ExecWindManager(void) {
    D_0063BC7C++;
    if (D_0063BC7C >= 0x33) {
        float r = _GetRandom();
        D_0063BC7C = 0;
        D_0063BC74 = D_0063BC64 * ((r + r - 1.0f) * D_0063BC6C + 1.0f);
    }
    D_0063BC78 = D_0063BC78 + (D_0063BC74 - D_0063BC78) * D_00639708;
    ExecWindField(D_0063BC78);
}
inline float GetRegularizedWindSpeed(void *pos) {
    float s;

    if (D_0063BC64 == 0.0f || D_0063BC6C == 0.0f) {
        return 1.0f;
    }
    GetWindVector(&s, pos);
    return (s / (60.0f / (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1])) * D_0063BC68 - (1.0f - D_0063BC6C)) * 0.5f * D_0063BC70;
}
inline void ReinitWindManager(void) {
    InitWindManager(D_0063BC60);
}
