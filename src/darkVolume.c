#include "common.h"
#include "sugiCommon.h"

extern void CopyVector(void *dst, void *src);
extern int D_004E7470[];
extern float D_0063B7D4;
extern float D_006394AC;
extern int D_004E7460[];
extern void darkVolume(void *a0, float a1, float a2, float a3);
extern int D_00639EA8;
extern void ExecuteSEPackage(int a0, int a1);
extern int D_0063B7BC;
extern float D_0063B7C0;
extern int D_0063B7C4;
extern int D_0063B7C8;
extern float D_0063B7CC;
/* prototypes: their order is the inline tail's emission order */
int InitDarkVolumeGeo(char *a0);
void DarkVolumeDL(void);
void ExecGameOverEffect(void);
void StartGameOverEffect(int a0, float t);
void StartQueenAttackEffect(int a0, float t);
void ResetGameOverEffect(void);

INCLUDE_ASM("asm/nonmatchings/src/darkVolume", draw);
INCLUDE_ASM("asm/nonmatchings/src/darkVolume", drawHT);
INCLUDE_ASM("asm/nonmatchings/src/darkVolume", renderViewCoordZSphere);

inline void ExecGameOverEffect(void) {}

INCLUDE_ASM("asm/nonmatchings/src/darkVolume", sonic);
INCLUDE_ASM("asm/nonmatchings/src/darkVolume", darkVolume);

/* listing lines 526-533: arm the game-over dark volume, shared by
   StartGameOverEffect and StartQueenAttackEffect */
static inline void setGameOverEffect(int a0, float t)
{
    D_0063B7BC = 1;
    D_0063B7C0 = 0;
    D_0063B7C4 = 1;
    D_0063B7C8 = 0;
    CopyVector((int)D_004E7460, a0);
    D_0063B7CC = t;
}

inline void StartGameOverEffect(int a0, float t)
{
    if (D_00639EA8 != 0) {
        ExecuteSEPackage(D_00639EA8, 0x7A);
        ExecuteSEPackage(D_00639EA8, 0x7B);
        ExecuteSEPackage(D_00639EA8, 0x7C);
        ExecuteSEPackage(D_00639EA8, 0x7D);
        ExecuteSEPackage(D_00639EA8, 0x7E);
    }
    setGameOverEffect(a0, t);
}

inline void StartQueenAttackEffect(int a0, float t)
{
    setGameOverEffect(a0, t);
    D_0063B7C8 = 1;
    D_0063B7C4 = 0;
}

inline void ResetGameOverEffect(void)
{
    D_0063B7BC = 0;
    D_0063B7C4 = 0;
}

void SetDarkVolumeEffect(int a0, float a1)
{
    D_0063B7D4 = a1;
    CopyVector(D_004E7470, (void *)a0);
}

extern float D_0063949C;
extern float D_006394A0;
extern float D_006394A4;
extern float D_006394A8;
extern float D_0063B7D0;
extern int D_0028F4D4[];
extern int D_00639EA4;
extern void GetRootPosition(void *out, void *gobj);
extern void iosOmSendMail(void *to, int msg, void *from);
extern void *isysGObjSearchFromObjKindID_begin(int kind);
extern void *isysGObjSearchFromObjKindID_next(void *gobj);
extern void sonic(void *pos, float t);

/* listing lines 566-568: the per-object hit test, inlined at all three sites */
static inline void sendGameOverMail(void *gobj, float r2)
{
    float pos[4];

    GetRootPosition(pos, gobj);
    if (distance_squared(pos, D_004E7460) < r2) {
        iosOmSendMail(gobj, 0x22, gobj);
    }
}

void DispGameOverEffect(void)
{
    void *g;

    if (D_0063B7BC != 0) {
        sonic(D_004E7460, D_0063B7C0);
        darkVolume(D_004E7460, D_0063B7C0, 1.0f, 30.0f);
        if (D_0063B7C4 != 0) {
            float r2 = D_0063B7C0 * D_0063B7C0;

            g = (void *)D_00639EA4;
            if (g != 0) {
                sendGameOverMail(g, r2);
            }
            for (g = isysGObjSearchFromObjKindID_begin(4); g != 0;
                 g = isysGObjSearchFromObjKindID_next(g)) {
                sendGameOverMail(g, r2);
            }
            for (g = isysGObjSearchFromObjKindID_begin(0x3E); g != 0;
                 g = isysGObjSearchFromObjKindID_next(g)) {
                sendGameOverMail(g, r2);
            }
        }
        if (D_0063B7C0 < D_0063949C && D_0028F4D4[0] == 0) {
            D_0063B7C0 = D_0063B7C0 + D_0063B7CC;
        }
    } else {
        if (D_0063B7D4 < D_006394A0 && D_0063B7D0 < 1.0f) {
            return;
        }
        darkVolume(D_004E7470, D_0063B7D0, D_006394A4, 0.0f);
        if (D_0028F4D4[0] != 0) {
            return;
        }
        D_0063B7D0 = D_0063B7D0 + (D_0063B7D4 - D_0063B7D0) * D_006394A8;
        D_0063B7D4 = 0.0f;
    }
}

void GetGameOverEffectCenterPosition(int a0)
{
    CopyVector(a0, D_004E7460);
}

INCLUDE_ASM("asm/nonmatchings/src/darkVolume", InitGameOverEffect);

inline int InitDarkVolumeGeo(char *a0)
{
    **(int **)(*(char **)(a0 + 0x15C) + 0xC) = 0;
    return 0;
}

void SetupDarkVolume(void *a0, float a1, float a2)
{
    darkVolume(a0, a1, 1.0f, a2);
}

void DarkVolumeGeo(char *a0)
{
    float *p;

    *(int *)(*(int *)(a0 + 0x15C) + 0x74) = 0;
    p = *(float **)(*(int *)(a0 + 0x15C) + 0xC);
    if (D_006394AC < *p) {
        SetupDarkVolume((char *)p + 0x30, *p * 50.0f, 10.0f);
    }
}

inline void DarkVolumeDL(void) {}
