#include "common.h"

#include "vu0.h"
typedef struct {
    float v[4];
} LVec;

typedef union { float f[4]; long long ll[2]; } QVec;


typedef struct { QVec x; QVec y; QVec z; QVec w; } QMat33;
typedef struct { QVec x; QVec y; QVec z; } QMat3;

typedef struct QueenMailEntry {
    /* 0x0 */ unsigned int mail;
    /* 0x4 */ void *data;
} QueenMailEntry;

typedef struct QueenMailQueue {
    /* 0x00 */ int unk0;
    /* 0x04 */ int num;
    /* 0x08 */ QueenMailEntry e[1];
} QueenMailQueue;

extern int D_0063A438;
extern int stage_no;
extern int D_0063B13C;
extern int D_00556DA8[];
extern int D_00556DB0[];
extern char D_00556DB8[];
extern int debug_Printf(int x, int y, unsigned int col, char *s, ...);
extern void *isysGObjSearchFromObjLayoutID(int id);
extern void GetRootMatrix(void *m, char *g);
extern void CopyMatrix(void *dst, void *src);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);
extern void sceVu0AddVector(void *a0, void *a1, void *a2);
extern float fmodf(float a, float b);
extern void LightTorchOffOfWeapon(void *o);
extern void ExecuteSEPackage(int a0, int a1);
extern int D_006EA7F0[];
extern int D_002A60B0[];
extern int D_002A7740[];
extern int D_002A6BB0[];
extern const char D_00556D90[];
extern void sceVu0CopyVector(void *dst, void *src);
extern const char D_00556DC8[];
extern const char D_00556DD8[];
extern int scpGameStat_BoyWeaponkind(void);
extern int iosOmSendMail(char *gop, int msg, void *sender);
extern void debug_StdPrintfDummy();
extern void queen_barrier_set_damage(void);
extern int InitCloth4D(char *g, void *a1, void *a2);
extern void InitMotionOrient(char *g, int a1, int a2, int a3, int a4, int a5);
extern void SetLodLevel(char *g, int lod);
extern int D_0028F4D4[];
extern int D_0063C300;
extern char *D_00639EA4;
extern void ExecMotionOrient(char *g);
extern void SetActressLight(char *g, int a1, int a2, int a3);
extern void GetCloth4D(void *cloth, float x, float y);
extern int CylinderCollision(char *self, int group, float r, float h, float s);
extern void ACTDispLwsBoyStonize_InQueenStage(char *g);
extern void p2o_SetDefaultEnviroment(void);
extern void p2o_DispVU1(char *g);
extern void DispCloth4D(void *cloth, void *a1, void *a2);
extern const char D_00556D80[];
extern void *iosMallocDebug(int heap, int size, const char *file, int line);
extern void *memset(void *p, int c, int n);
extern void GetRootPosition(void *work, char *g);
extern char *actInitialize(char *g);
extern void actInitialize_ext_charcter(char *g);
extern void _ACTWait(int n);
extern void actCreateSubThread(void (*func)(), int prio);
extern int SetMotionRequest(char *g, int motion, void *p);
extern void queen_barrier_disp_init(void);
extern void queen_barrier_anim(void);
extern void subQueenBrainMain();
extern void subQueenControl();
extern void gene_enemy();
extern char *isysGObjSearchFromObjKindID_begin(int kind);
extern char *isysGObjSearchFromObjKindID_next(char *g);
extern void sceVu0CopyMatrix(void *a0, void *a1);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);

/* PAL listing rows 87-90: a static identity-3x3 helper, expanded into
 * QueenBarrierGeo (and QueenBallGeo). */
static inline void UnitMatrix33(QMat3 *m) {
    m->x.f[0] = 1.0f; m->x.f[1] = 0.0f; m->x.f[2] = 0.0f; m->x.f[3] = 0.0f;
    m->y.f[0] = 0.0f; m->y.f[1] = 1.0f; m->y.f[2] = 0.0f; m->y.f[3] = 0.0f;
    m->z.f[0] = 0.0f; m->z.f[1] = 0.0f; m->z.f[2] = 1.0f; m->z.f[3] = 0.0f;
}

void scale_m34(LVec *a0, void *a1, float f) {
    sceVu0CopyMatrix(a0, a1);
    sceVu0ScaleVector(a0, a0, f);
    sceVu0ScaleVector(a0 + 1, a0 + 1, f);
    return sceVu0ScaleVector(a0 + 2, a0 + 2, f);
}
/* census: static effect_end_func (another TU holds the public symbol name). */
INCLUDE_ASM("asm/nonmatchings/src/queen", func_001A27D0);
INCLUDE_ASM("asm/nonmatchings/src/queen", queenBeforeFunc);
INCLUDE_ASM("asm/nonmatchings/src/queen", gene_enemy);
INCLUDE_ASM("asm/nonmatchings/src/queen", subQueenBrainMain);
ASM_LIT4_SLOT(D_006392C0, 0.001f);
/* census: static Debug_StickControl; the symbol name is held by act_bird's copy, so the
   placeholder stays until this one is C (then it is a file-static of that name). */
INCLUDE_ASM("asm/nonmatchings/src/queen", func_001A34D8);
void *InitQueenGeo(char *g) {
    char *ext = *(char **)(g + 0x15C);
    char *w;
    int i;

    w = (char *)iosMallocDebug(D_0063A438, 0x18, D_00556D80, 732);
    memset(w, 0, 0x18);
    for (i = 3; i >= 0; i--) {
        D_006EA7F0[i] = 0;
    }
    *(int *)(w + 0xC) = 1;
    *(int *)(w + 0x10) = InitCloth4D(g, D_002A60B0, D_002A7740);
    *(int *)(w + 0x14) = InitCloth4D(g, D_002A6BB0, 0);
    *(char **)(ext + 0x830) = w;
    InitMotionOrient(g, 0x967, 0x975, 0xC, 0x18, 0x430);
    SetLodLevel(g, 2);
    actInitialize(g);
    actInitialize_ext_charcter(g);
    return w;
}
void QueenGeo(char *g) {
    char *w;

    if (D_0028F4D4[0] == 0) {
        D_0063C300++;
    }
    ExecMotionOrient(g);
    SetActressLight(g, 0x23, 0x2C, 0x1D8);
    w = *(char **)(*(char **)(g + 0x15C) + 0x830);
    if (*(int *)(w + 0xC) != 0) {
        GetCloth4D(*(void **)(w + 0x10), 3.0f, 0.98f);
        GetCloth4D(*(void **)(w + 0x14), 5.0f, 0.9f);
    }
    CylinderCollision(g, 1, 100.0f, 100.0f, 0.001f);
}
void QueenDL(char *g) {
    char *w;

    if (D_00639EA4 != 0) {
        ACTDispLwsBoyStonize_InQueenStage(D_00639EA4);
    }
    p2o_SetDefaultEnviroment();
    p2o_DispVU1(g);
    w = *(char **)(*(char **)(g + 0x15C) + 0x830);
    if (*(int *)(w + 0xC) != 0) {
        DispCloth4D(*(void **)(w + 0x10),
                    *(char **)(*(char **)(g + 0x15C) + 0x874) + 0x40,
                    *(char **)(*(char **)(g + 0x15C) + 0x874));
    }
    DispCloth4D(*(void **)(w + 0x14),
                *(char **)(*(char **)(g + 0x15C) + 0x874) + 0x40,
                *(char **)(*(char **)(g + 0x15C) + 0x874));
}
/* PAL listing rows 871-873 belong to a static angle-wrap helper. */
static inline float WrapRad(float a) {
    a = fmodf(a, 6.2831854820251465f);
    if (a > 3.1415927410125732f) {
        a -= 6.2831854820251465f;
    } else if (a < -3.1415927410125732f) {
        a += 6.2831854820251465f;
    }
    return a;
}

void QueenBarrierGeo(char *g) {
    QVec pos;
    QVec rootPos;
    QMat33 m1;
    QMat3 rot;
    QVec trans;
    QVec ofs;
    QVec axis;
    QMat33 m3;
    char *w;
    char *queen;
    char *qw;
    int *tbl;
    unsigned int i;
    unsigned int found;
    unsigned int mine;

    memset(&pos, 0, sizeof(pos));
    pos.f[1] = 2000.0f;
    w = *(char **)(*(char **)(g + 0x15C) + 0x830);
    queen = isysGObjSearchFromObjKindID_begin(0x2F);
    qw = *(char **)(*(char **)(queen + 0x15C) + 0x830);
    if (stage_no == 0x25) {
        tbl = D_00556DA8;
    } else {
        tbl = D_00556DB0;
    }
    mine = 0;
    if (D_0063B13C & 1) {
        debug_Printf(0xA, 0x46, 0xFFFFFFFF, D_00556DB8, *(int *)(w + 0x18));
    }
    for (i = 0; i < 1; i++) {
        char *o = (char *)isysGObjSearchFromObjLayoutID(tbl[i]);

        if (o == 0) {
            continue;
        }
        if (*(signed char *)(*(char **)(*(char **)(o + 0x15C) + 0x830) + 0x12) != 0) {
            continue;
        }
        break;
    }
    found = i;
    for (i = 0; i < 1; i++) {
        if (*(int *)(g + 8) == tbl[i]) {
            mine = i;
            break;
        }
    }
    GetRootPosition(&rootPos, queen);
    if (*(signed char *)(w + 0x12) == 0 || *(int *)(queen + 0x16C) == 0 ||
        (*(int *)qw & 0xFF0000FF) != 0 || *(signed char *)(qw + 1) == 0) {
        GetRootMatrix(&m1, g);
        sceVu0CopyVector(&m1.w, &pos);
        CopyMatrix(*(void **)(*(char **)(g + 0x15C) + 0xC), &m1);
    } else {
        axis.f[0] = 0.05235987901687622f;
        axis.f[1] = 0.0872664675116539f;
        axis.f[2] = 0.12217305600643158f;
        axis.f[3] = 0.0f;
        ofs = axis;
        sceVu0ScaleVector(&ofs, &ofs,
                          (float)(unsigned int)(-mine) * 0.019999999552965164f +
                              0.05000000074505806f);
        sceVu0AddVector(w + 0x20, w + 0x20, &ofs);
        *(float *)(w + 0x20) = WrapRad(*(float *)(w + 0x20));
        *(float *)(w + 0x24) = WrapRad(*(float *)(w + 0x24));
        *(float *)(w + 0x28) = WrapRad(*(float *)(w + 0x28));
        UnitMatrix33(&rot);
        sceVu0CopyVector(&trans, w);
        CopyMatrix(*(void **)(*(char **)(g + 0x15C) + 0xC), &rot);
    }
    if (*(signed char *)(w + 0x10) != 0 && mine == found - 1) {
        void *weapon;

        *(int *)(qw + 4) = 0;
        weapon = (void *)*(int *)(*(int *)(D_00639EA4 + 0x164) + 0x150);
        if (weapon != 0) {
            LightTorchOffOfWeapon(weapon);
        }
        *(int *)(qw + 8) = 0x12;
        ExecuteSEPackage((int)g, 0x5F);
        *(int *)(w + 0x18) = *(int *)(w + 0x18) + 1;
        if (*(int *)(w + 0x18) >= 5) {
            GetRootMatrix(&m3, g);
            sceVu0CopyVector(&m3.w, &pos);
            CopyMatrix(*(void **)(*(char **)(g + 0x15C) + 0xC), &m3);
            *(char *)(w + 0x12) = 0;
            ExecuteSEPackage((int)D_00639EA4, 0x62);
        }
    }
    if (*(int *)(qw + 8) > 0) {
        *(int *)(qw + 8) = *(int *)(qw + 8) - 1;
    }
    *(char *)(w + 0x10) = 0;
    queen_barrier_anim();
}
extern void queen_barrier_disp_proc(float);
void QueenBarrierDL(char *g) {
    char *b = *(char **)(*(char **)(g + 0x15C) + 0x830);
    if (*(signed char *)(b + 0x12)) {
        queen_barrier_disp_proc(1.0f - *(int *)(b + 0x18) / 5.0f);
    }
}
ASM_LIT4_SLOT(D_00639320, 5000.0f);
INCLUDE_ASM("asm/nonmatchings/src/queen", QueenBallGeo);

INCLUDE_ASM("asm/nonmatchings/src/queen", QueenBallDL);
void actQueenStart(char *g) {
    char *sub = actInitialize(g);

    actInitialize_ext_charcter(g);
    _ACTWait(1);
    actCreateSubThread(subQueenBrainMain, 0x14);
    actCreateSubThread(subQueenControl, 0x15);
    actCreateSubThread(gene_enemy, 0x15);
    *(int *)(sub + 0x130) = SetMotionRequest(g, 0x10E, sub + 0x620);
    *(int *)(*(int *)(g + 0x15C) + 0x7C) = 1;
}
void QueenStartAttack(void) {
    char *g;

    g = isysGObjSearchFromObjKindID_begin(0x2F);
    *(char *)(*(char **)(*(char **)(g + 0x15C) + 0x830) + 1) = 1;

    g = isysGObjSearchFromObjKindID_begin(0x36);
    while (g != 0) {
        *(char *)(*(char **)(*(char **)(g + 0x15C) + 0x830) + 0x12) = 1;
        g = isysGObjSearchFromObjKindID_next(g);
    }
}
int QueenInqDead(void) {
    char *g = isysGObjSearchFromObjKindID_begin(0x2F);
    return *(signed char *)(*(char **)(*(char **)(g + 0x15C) + 0x830) + 3);
}
int QueenBoysWeaponPower(void) {
    char *g = isysGObjSearchFromObjKindID_begin(0x2F);
    return *(int *)(*(char **)(*(char **)(g + 0x15C) + 0x830) + 4);
}
float QueenBarrierRadius(char *a0) {
    return *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x14);
}
int QueenBarrierInqBreakable(void) {
    char *b;
    int ret = 0;

    b = *(char **)(*(char **)(isysGObjSearchFromObjKindID_begin(0x2F) + 0x15C) + 0x830);
    if (*(int *)(b + 4) > 0 || *(int *)(b + 8) > 0) {
        ret = 1;
    }
    return ret;
}
void queenBarrierBeforeFunc(char *g) {
    QueenMailQueue *q = (QueenMailQueue *)(g + 0x54);
    char *w = *(char **)(*(char **)(g + 0x15C) + 0x830);
    char *other;
    int i;

    for (i = 0; i < q->num; i++) {
        QueenMailEntry *e = &q->e[i];

        if (e->mail == 0xD) {
            debug_StdPrintfDummy(D_00556D90);
            *(char *)(w + 0x10) = 1;
            *(char *)(w + 0x11) = 1;
            other = isysGObjSearchFromObjKindID_begin(0x35);
            if (other != 0) {
                *(char *)(*(char **)(*(char **)(other + 0x15C) + 0x830) + 0x1A) = 1;
            }
            queen_barrier_set_damage();
        }
    }
    q->num = 0;
}
int InqQueenBarrierExist(void) {
    char *g;
    int exist = 0;

    g = isysGObjSearchFromObjKindID_begin(0x36);
    if (g != 0) {
        exist = *(int *)(*(char **)(*(char **)(g + 0x15C) + 0x830) + 0x18) < 5;
    }
    return exist;
}
void *InitQueenBarrierGeo(char *g) {
    char *w;

    char *ext = *(char **)(g + 0x15C);

    w = (char *)iosMallocDebug(D_0063A438, 0x30, D_00556D80, 991);
    memset(w, 0, 0x30);
    *(char **)(ext + 0x830) = w;
    *(float *)(w + 0x14) = 300.0f;
    GetRootPosition(w, g);
    actInitialize(g);
    actInitialize_ext_charcter(g);
    queen_barrier_disp_init();
    return w;
}
float QueenBallRadius(char *a0) {
    return *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x14) * 100.0f;
}
float GetQueenBallThickness(void) {
    return 150.0f;
}
void queenBallBeforeFunc(char *g) {
    QueenMailQueue *q = (QueenMailQueue *)(g + 0x54);
    char *w = *(char **)(*(char **)(g + 0x15C) + 0x830);
    int i;

    for (i = 0; i < q->num; i++) {
        QueenMailEntry *e = &q->e[i];

        if (e->mail != 0xD) {
            debug_StdPrintfDummy(D_00556DC8, e->mail);
        } else if (scpGameStat_BoyWeaponkind() == 5) {
            debug_StdPrintfDummy(D_00556DD8);
            *(char *)(w + 0x18) = 1;
            iosOmSendMail(D_00639EA4, 0x1A9, g);
        }
    }
    q->num = 0;
}
void *InitQueenBallGeo(char *g) {
    char *w;

    char *ext = *(char **)(g + 0x15C);

    w = (char *)iosMallocDebug(D_0063A438, 0x20, D_00556D80, 1284);
    *(char **)(ext + 0x830) = w;
    memset(w, 0, 0x20);
    *(float *)(w + 0x14) = 0.0f;
    GetRootPosition(w, g);
    actInitialize(g);
    actInitialize_ext_charcter(g);
    return w;
}
INCLUDE_ASM("asm/nonmatchings/src/queen", subQueenControl);
