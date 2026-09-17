#include "common.h"
#include "debug.h"
#include "gamesys.h"
#include "memory.h"
#include "obj_manager.h"
#include "act-game.h"
#include "boyact.h"
#include "enemy_act.h"
#include "ebrain.h"
#include "geometryManager.h"
#include "multiBgaManager.h"

typedef union {
    unsigned long ll;
    unsigned int i;
} GVBits;

typedef struct {
    char _0[0x42];
    short f42;
    unsigned short f44;
    unsigned char f46;
    char _47;
    unsigned int f48;
} GVGeo2;

extern int D_0063A438;
/* kept local: this TU's uses of _ApplyRyGV do not fit the prototype in gv.h */
extern void _ApplyRyGV(void *a0, float a1);
extern StageLabelRange D_005F5D50[];
extern GVGeo2 D_002C2DC8[];
extern int stage_no;
extern int D_006E6D80[];
extern int fptodp(float f);
extern char D_0063AC08[];
extern char D_00308924[];

#include "generator.h"
#include <string.h>

inline int SearchActiveGenerator(void)
{
    char *g;

    g = (char *)isysGObjSearchFromObjKindID_begin(0x21);
    while (g != 0) {
        char *w = *(char **)(*(char **)(g + 0x15C) + 0x830);

        if (*(int *)(g + 0x16C) != 0) {
            if (*(int *)(w + 0x50) == 1) {
                return 1;
            }
        }
        g = (char *)isysGObjSearchFromObjKindID_next(g);
    }
    return 0;
}

extern void sceVu0ScaleVector(float *dst, float *src, float t);
extern void sceVu0AddVector(float *dst, float *a, float *b);
/* kept local: this TU's uses of _DistxzSqGV do not fit the prototype in gv.h */
extern float _DistxzSqGV(float *a, float *b);

int CheckGeneratorCollision(char *gobj, float *dir)
{
    float pos[4];
    float tmp[4];
    float p[4];
    char *g;

    g = (char *)isysGObjSearchFromObjKindID_begin(0x21);
    GetRootPosition(pos, gobj);
    sceVu0ScaleVector(tmp, dir, 100.0f);
    sceVu0AddVector(pos, pos, tmp);

    for (; g != 0; g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        char *w = *(char **)(*(char **)(g + 0x15C) + 0x830);

        if (*(int *)(g + 0x16C) == 0) {
            continue;
        }
        if (*(int *)(w + 0x50) != 1) {
            continue;
        }
        GetRootPosition(p, g);
        if (_DistxzSqGV(p, pos) < 22500.0f) {
            float d = p[1] - 50.0f - pos[1];

            if ((d < 0.0f ? -d : d) < 100.0f) {
                return 0;
            }
        }
    }
    return 1;
}

/* generator.c:366-381, a static inline helper of this TU: the listing gives
   GetGeneratorSafePosition the rows 367-381 twice, outside its own 386-422
   span.  The result is truncated to a byte at both call sites, so the helper
   returns an 8-bit type. */
typedef struct SafePosOffset {
    float x;
    float y;
    float z;
    int kind;
} SafePosOffset;

extern SafePosOffset generatorSubPosition[];

static inline unsigned char IsGeneratorSafePosition(float *pos)
{
    char *g;

    for (g = (char *)isysGObjSearchFromObjKindID_begin(0x11); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        float p[4];

        if (*(int *)(g + 0x16C) == 0) {
            continue;
        }
        GetRootPosition(p, g);
        if (_DistxzSqGV(pos, p) < 22500.0f) {
            float d = pos[1] - 50.0f - p[1];

            if ((d < 0.0f ? -d : d) < 100.0f) {
                return 0;
            }
        }
    }
    return 1;
}

void GetGeneratorSafePosition(float *dst, char *gobj)
{
    float pos[4];
    int i;

    GetRootPosition(pos, gobj);
    if (IsGeneratorSafePosition(pos)) {
        dst[0] = pos[0];
        dst[1] = pos[1];
        dst[2] = pos[2];
        return;
    }

    {
        float probe[4];

        for (i = 0; i < 7; i++) {
            SafePosOffset *e = &generatorSubPosition[i];

            if (e->kind != *(int *)(gobj + 8)) {
                continue;
            }
            probe[0] = -e->x;
            probe[1] = -e->y;
            probe[2] = -e->z;
            if (IsGeneratorSafePosition(probe)) {
                dst[0] = probe[0];
                dst[1] = probe[1];
                dst[2] = probe[2];
                return;
            }
        }
        GetRootPosition(probe, gobj);
        dst[0] = probe[0];
        dst[1] = probe[1];
        dst[2] = probe[2];
    }
}

extern int D_0028F4C0[];

void switch_MainStatus(char *gobj, unsigned char st)
{
    float pos[4];
    char *w = *(char **)(*(char **)(gobj + 0x15C) + 0x830);

    if (st == *(int *)(w + 0x50)) {
        return;
    }

    switch (*(int *)(w + 0x50)) {
    case 0:
        if (!IsNeedGeneratorHard()) {
            *(int *)(w + 0x50) = 2;
            gamesysObjInfoUniqDataSet(gobj);
            break;
        }
        iosOmSendMail(gobj, 0, gobj);
        *(int *)(w + 0x50) = 1;
        *(int *)(w + 0x64) = ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 4;
        GetGeneratorSafePosition(pos, gobj);
        SetRootPosition(gobj, pos);
        gamesysObjInfoUniqDataSet(gobj);
        break;

    case 1:
        iosOmSendMail(gobj, 2, gobj);
        *(int *)(w + 0x50) = 2;
        gamesysObjInfoUniqDataSet(gobj);
        break;

    case 2:
        break;
    }
}

extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern char D_0063AC00[];

typedef struct GenBga {
    char *p;
    char f4;
    char pad[3];
} GenBga;

/* generator.c:467-473 and 475-479, two static inline helpers of this TU: the
   listing gives endfunc_BGA rows 468-478, outside its own 489-505 span. */
static inline char *ResetCurrentBga(char *gobj)
{
    char *w = *(char **)(*(char **)(gobj + 0x15C) + 0x830);

    if (*(int *)(w + 0x58) != -1) {
        char *e = w + *(int *)(w + 0x58) * 8;
        char *q;

        *(char *)(e + 0x34) = 0;
        q = w + *(int *)(w + 0x58) * 8;
        **(float **)(q + 0x30) = -1.0f;
    }
    return w;
}

static inline void EntryBga(char *gobj, char *w, int slot)
{
    float mtx[4];

    memset(mtx, 0, 16);
    mtx[3] = 1.0f;
    EntryMultiBgaManager(*(int *)(w + 0x30 + slot * 8), 0, -1, (void *)test_CURRENTROOT(gobj), mtx);
}

void endfunc_BGA(char *gobj)
{
    char *w = *(char **)(*(char **)(gobj + 0x15C) + 0x830);

    switch (*(int *)(w + 0x58)) {
    case 0: {
        char *cur;

        *(char *)(w + 0x3C) = 1;
        cur = ResetCurrentBga(gobj);
        EntryBga(gobj, cur, 1);
        *(int *)(cur + 0x58) = 1;
        break;
    }

    case 1:
        **(int **)(w + 0x38) = 0;
        break;

    case 2: {
        char *cur;

        *(char *)(w + 0x2C) = 1;
        cur = ResetCurrentBga(gobj);
        *(int *)(cur + 0x58) = -1;
        break;
    }

    default:
        debug_assert(__FILE__, 504);
        __assert(__FILE__, 504, D_0063AC00);
        break;
    }
}

char *IsNeedGeneratorHard(char *mother)
{
    char *w = *(char **)(*(char **)(mother + 0x15C) + 0x830);
    char *g;
    int count = 0;
    int isCalling = (*(int *)(w + 0x50) == 1);

    if (mother != 0 && *(int *)(mother + 8) == 0xEAE) {
        int found = 0;

        g = (char *)isysGObjSearchFromObjLayoutID(0xEAD);
        if (g != 0) {
            GVGeo2 *gv = &D_002C2DC8[*(int *)(g + 8)];

            if (gv->f42 == -1 || gv->f42 > 0) {
                found = 1;
            }
            if (isEnemyActive(g)) {
                found = 1;
            }
        }
        return found ? g : 0;
    }

    for (g = (char *)isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        char *p = *(char **)(g + 0x164);

        if ((unsigned int)(*(unsigned long long *)(p + 0x18) >> 34) & 1) {
            continue;
        }
        if (mother == 0 || (*(int *)(mother + 8) != GetMotherGeneratorLabelAskEnemy(g) &&
                            D_002C2DC8[*(int *)(g + 8)].f44 != *(int *)(mother + 8))) {
            continue;
        }
        if (D_002C2DC8[*(int *)(g + 8)].f42 == -1 || D_002C2DC8[*(int *)(g + 8)].f42 > 0) {
            return g;
        }
        if (isEnemyActive(g)) {
            return g;
        }
    }

    for (g = (char *)isysGObjSearchFromObjKindID_begin(0x21); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {}

    for (g = (char *)isysGObjSearchFromObjKindID_begin(0x3E); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        char *p = *(char **)(g + 0x164);

        count += (int)(*(unsigned long long *)(p + 0x18) >> 32) & 1;
    }

    for (g = (char *)isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        char *p = *(char **)(g + 0x164);
        GVGeo2 *gv = &D_002C2DC8[*(int *)(g + 8)];

        if (*(int *)(g + 8) == 0xEAD) {
            continue;
        }
        if ((unsigned int)(*(unsigned long long *)(p + 0x18) >> 34) & 1) {
            if (count < 5) {
                continue;
            }
            return g;
        }
        if (mother != 0) {
            if (*(int *)(mother + 8) == GetMotherGeneratorLabelAskEnemy(g)) {
                continue;
            }
            if (D_002C2DC8[*(int *)(g + 8)].f44 == *(int *)(mother + 8)) {
                continue;
            }
        }
        if (isEnemyActive(g)) {
            return g;
        }
        if (gv->f42 == -1 || gv->f42 > 0) {
            if (!isCalling) {
                return g;
            }
            {
                char *m = GetMotherGeneratorGObjAskEnemy(g);

                if (m != 0 && IsOpenGenerator(m)) {
                    return g;
                }
            }
        }
    }
    return 0;
}

inline int IsEnableCallEnemyByTargetGObj(void *a0)
{
    GVGeo2 *g = &D_002C2DC8[*(int *)((char *)a0 + 0x8)];
    void *p = *(void **)((char *)a0 + 0x164);
    if (g->f44 != 0) {
        return 0;
    }
    if ((unsigned int)(*(unsigned long long *)((char *)p + 0x18) >> 34) & 1) {
        return 0;
    }
    if (((g->f48 >> 21) & 1) == 0 && (g->f42 == -1 || g->f42 > 0)) {
        return 1;
    }
    return 0;
}

inline void *IsEnableCallEnemy(char *self)
{
    char *g;

    for (g = (char *)isysGObjSearchFromObjKindID_begin(4); g != 0;
         g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        char *p = *(char **)(g + 0x164);
        int no = *(int *)(g + 8);
        GVGeo2 *gg = &D_002C2DC8[no];

        if (self != 0 && *(int *)(self + 8) == 0xEAE && no != 0xEAD) {
            continue;
        }
        if (D_002C2DC8[no].f44 != 0 && self != 0 && D_002C2DC8[no].f44 != *(int *)(self + 8)) {
            continue;
        }
        if ((unsigned int)(*(unsigned long long *)(p + 0x18) >> 34) & 1) {
            continue;
        }
        if ((gg->f48 >> 21) & 1) {
            continue;
        }
        if (gg->f42 == -1 || gg->f42 > 0) {
            return g;
        }
    }
    return 0;
}

inline char *DirectCallEnemy(char *gobj, char *mother, float *pos, float *dir, int a4)
{
    GVGeo2 *gg = &D_002C2DC8[*(int *)(gobj + 8)];

    gg->f48 = (gg->f48 | 0x200000) & 0xFFFBFFFF;

    debug_StdPrintfDummy("call enemy! = %d (%p : %d)\n", *(int *)(gobj + 8), mother,
                         (mother != 0) ? *(int *)(mother + 8) : -1);
    debug_StdPrintfDummy("[%8s] %8f %8f %8f %8f\n", D_0063AC08, fptodp(pos[0]), fptodp(pos[1]),
                         fptodp(pos[2]), fptodp(pos[3]));
    if (mother != 0) {
        SetMotherGenerator(*(int *)(gobj + 8), *(int *)(mother + 8));
    }
    if (gg->f42 != -1) {
        gg->f42--;
    }
    actEnemyRestart(gobj, pos, dir, a4, mother);
    ACTGame_SaveActorInformation(gobj);
    return gobj;
}

char *CallEnemy(char *mother, float *pos, float *dir, int a4)
{
    char *gobj = (char *)IsEnableCallEnemy(mother);

    if (gobj != 0) {
        return DirectCallEnemy(gobj, mother, pos, dir, a4);
    }
    return 0;
}

inline void LockEnemyGenerate(int *self)
{
    int *p;
    p = (int *)self[0x164 / 4];
    debug_StdPrintfDummy("lock! = %d\n", self[0x8 / 4]);
    *(long long *)((char *)p + 0x18) = *(long long *)((char *)p + 0x18) | 0x400000000LL;
}

inline void UnlockEnemyGenerate(void *a0)
{
    void *p = *(void **)((char *)a0 + 0x164);
    GVGeo2 *g = &D_002C2DC8[*(int *)((char *)a0 + 0x8)];
    debug_StdPrintfDummy("unlock! = %d\n", *(int *)((char *)a0 + 0x8));
    ((GVBits *)((char *)p + 0x18))->ll &= ~((unsigned long)0x8000 << 19);
    g->f48 = (g->f48 | 0x200000) & 0xFFFBFFFF;
}

inline void RestoreReviveCount(char *gobj)
{
    GVGeo2 *g = (GVGeo2 *)((char *)D_002C2DC8 + *(int *)(gobj + 8) * 0x4C);
    if (g->f42 != -1) {
        int n = (short)(g->f42 + 1);
        int lim = ((g->f48 >> 5) & 0x1F) + 1;
        n = (lim < n) ? lim : n;
        g->f42 = n;
        if (*(int *)(gobj + 8) == 0xEAD) {
            g->f42 = (g->f42 < 0) ? 0 : ((g->f42 > 1) ? 1 : g->f42);
        }
    }
}

void Generator_QuickCall(char *gobj)
{
    char *w = *(char **)(*(char **)(gobj + 0x15C) + 0x830);

    *(int *)(w + 0x50) = 1;
    gamesysObjInfoUniqDataSet(gobj);
    iosOmSendMail(gobj, 1, gobj);
}

inline void Generator_Call(char *a0)
{
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8) += 1;
}

inline void Generator_ResetCount(char *a0)
{
    *(char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x12) = 1;
}

inline void Generator_Mask(char *a0)
{
    *(char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x10) = 1;
}

inline void Generator_MaskOff(char *a0)
{
    *(char *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x10) = 0;
}

void Generator_Delete(void *a0)
{
    switch_MainStatus(a0, 0);
}

int GetMotherGenerator(int label)
{
    int info[2];
    int x;
    int st;
    int i;
    int j;
    int best;
    int ret;

    if (label == 3757) {
        return 3758;
    }

    GetKidnapInfo(&info[0], &info[1]);
    if (info[0] != -1 && info[0] == label) {
        return info[1];
    }

    x = (int)((D_002C2DC8 + label)->f48 << 27) >> 27;
    if (x != -1) {
        st = GetStageFromLabel(label);
        for (i = D_005F5D50[st].labelTop; i < D_005F5D50[st].labelEnd; i++) {
            GVGeo2 *g = &D_002C2DC8[i];

            if (g->f46 == 0x21) {
                if (((int)(g->f48 << 27) >> 27) == x) {
                    return i;
                }
            }
        }
    }

    best = 0;
    ret = -1;
    st = GetStageFromLabel(label);
    for (j = D_005F5D50[st].labelTop; j < D_005F5D50[st].labelEnd; j++) {
        GVGeo2 *g = &D_002C2DC8[j];

        if (g->f46 == 0x21) {
            int v = (g->f48 >> 17) & 1;

            if (best < v) {
                best = v;
                ret = j;
            }
        }
    }
    return ret;
}

inline void SetMotherGenerator(int no, int label)
{
    int i;
    int j;
    int cnt;

    if (no == 0xEAD) {
        return;
    }
    cnt = 0;
    for (i = D_005F5D50[stage_no].labelTop; i < D_005F5D50[stage_no].labelEnd; i++) {
        GVGeo2 *g = &D_002C2DC8[i];
        if (g->f46 == 0x21) {
            if (i == label) {
                GVGeo2 *m = &D_002C2DC8[no];
                m->f48 = ((int)m->f48 & ~0x3C00) | ((cnt & 0xF) << 10);
                return;
            }
            cnt++;
        }
    }
}

inline void Generator_Init(void)
{
    int i;
    int j;

    for (i = 0; i < 3759; i++) {
        GVGeo2 *g = &D_002C2DC8[i];
        unsigned int x = g->f48 & 0xFFDFFFFF;
        unsigned int y = x & 0xFFFBFFFF;

        y |= ((x >> 19) & 1) << 18;
        g->f48 = y;
        g->f42 = (y >> 5) & 0x1F;
        if ((y >> 19) & 1) {
            unsigned int z = y | 0x40000;
            g->f48 = z;
            if ((int)((z >> 5) & 0x1F) != -1) {
                g->f42++;
            }
        }
    }
}

inline void ReturnEnemyToGenerator(int a0)
{
    GVGeo2 *g = &D_002C2DC8[a0];
    unsigned int x = g->f48 & 0xFFDFFFFF;
    unsigned int y = x & 0xFFFBFFFF;
    y |= ((x >> 19) & 1) << 18;
    g->f48 = y;
    if ((y >> 19) & 1) {
        unsigned int z = y | 0x40000;
        g->f48 = z;
        if ((int)((z >> 5) & 0x1F) != -1) {
            g->f42++;
        }
    }
}

inline int *GetbufpGeneratorPacket(void)
{
    return D_006E6D80;
}

inline int GetsizeGeneratorPacket(void)
{
    return 11277;
}

void ReadGeneratorPacket(void)
{
    unsigned char *p = (unsigned char *)GetbufpGeneratorPacket();
    int i;
    int j;

    for (i = 0; i < 3759; i++) {
        GVGeo2 *g = &D_002C2DC8[i];
        unsigned int b = *p++;
        unsigned int x = (b >> 4) << 10;

        g->f48 = ((int)g->f48 & ~0x3C00) | x;
        g->f48 = (g->f48 & ~0x200000) | ((b & 1) << 21);
    }

    for (i = 0; i < 3759; i++) {
        GVGeo2 *g = &D_002C2DC8[i];
        char c = *(char *)p++;

        g->f48 = (g->f48 & ~0x40000) | ((c & 1) << 18);
    }

    for (i = 0; i < 3759; i++) {
        D_002C2DC8[i].f42 = (char)*p;
        p++;
    }
}

void MakeGeneratorPacket(void)
{
    char *p = (char *)GetbufpGeneratorPacket();
    int i;
    int j;

    for (i = 0; i < 3759; i++) {
        *p++ = (((int)(D_002C2DC8[i].f48 << 18) >> 28) << 4) | ((D_002C2DC8[i].f48 >> 21) & 1);
    }

    for (i = 0; i < 3759; i++) {
        *p++ = (D_002C2DC8[i].f48 >> 18) & 1;
    }

    for (i = 0; i < 3759; i++) {
        *p++ = D_002C2DC8[i].f42;
    }
}

inline void ResetReviveCountEnemy(int a0)
{
    int idx = *(int *)(a0 + 0x8);
    char *base = (char *)D_002C2DC8 + idx * 0x4C;
    *(short *)(base + 0x42) = 0;
}

inline void SetInfoSpKidnapEnemy(void)
{
    int new_var;
    new_var = 0x42;
    *((short *)(D_00308924 + new_var)) = 0;
    *((int *)(D_00308924 + 0x48)) = ((*((int *)(D_00308924 + 0x48))) | 0x200000) & (~0x40000);
}

inline void SetInfoSpKidnapGenerator(short *a0)
{
    a0[0] = 1;
    a0[1] = 1;
}

inline int RestoreGeneratorGeo(float *dst, float *src)
{
    dst[0] = src[4];
    dst[1] = src[5];
    dst[2] = src[6];
    return 1;
}

inline int RestoreGeneratorExtGeo(char *a0, short *a1)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    *(int *)(p + 0x50) = a1[0x18];
    *(int *)(p + 8) = a1[0x19];
    if (a1[0x18] == 1) {
        *(int *)(p + 0x54) = 2;
        iosOmSendMail(a0, 1, a0);
    }
    return 1;
}

inline int MemoryGenerator(short *a0, char *a1)
{
    char *p = *(char **)(*(char **)(a1 + 0x15C) + 0x830);
    a0[0] = *(unsigned short *)(p + 0x50);
    a0[1] = *(unsigned short *)(p + 8);
    return 1;
}

/* The pending-BGA request queue of the generator actor: the count lives at
   gobj+0x58 and the entries run from gobj+0x5C.  `kind` is unsigned: the
   switch below has no slti range test, which is what an unsigned switch
   operand does to ee-gcc's case tree. */
typedef struct GenReqEntry {
    unsigned int kind;
    int f4;
} GenReqEntry;

typedef struct GenReq {
    int f0;
    int count;
} GenReq;

void generatorBeforeFunc(char *gobj)
{
    char *w = *(char **)(*(char **)(gobj + 0x15C) + 0x830);
    GenReq *q = (GenReq *)(gobj + 0x54);
    int i;

    for (i = 0; i < q->count; i++) {
        switch (((GenReqEntry *)(gobj + 0x5C))[i].kind) {
        case 0: {
            char *cur;

            *(char *)(w + 0x34) = 1;
            cur = ResetCurrentBga(gobj);
            EntryBga(gobj, cur, 0);
            *(int *)(cur + 0x58) = 0;
            break;
        }

        case 1: {
            char *cur;

            *(char *)(w + 0x3C) = 1;
            cur = ResetCurrentBga(gobj);
            EntryBga(gobj, cur, 1);
            *(int *)(cur + 0x58) = 1;
            break;
        }

        case 2:
            *(int *)(w + 0x60) = ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 4;
            break;
        }
    }
    q->count = 0;
}

inline char *InitGeneratorGeo(char *gobj, char *src)
{
    char *p = iosMallocDebug(D_0063A438, 0x70, __FILE__, 1230);
    int i;
    int j;

    *(int *)(p + 0x0) = 0;
    *(int *)(p + 0x4) = 0;
    *(int *)(p + 0x8) = 0;
    *(char *)(p + 0x10) = 0;
    *(char *)(p + 0x12) = 0;
    *(int *)(p + 0x14) = *(int *)(src + 0x30);
    *(int *)(p + 0xC) = 0;

    *(int *)(p + 0x50) = 0;
    *(int *)(p + 0x54) = 0;
    *(int *)(p + 0x58) = -1;
    *(int *)(p + 0x5C) = -1;
    *(int *)(p + 0x60) = -1;
    *(int *)(p + 0x64) = 0;

    *(float *)(p + 0x20) = 0.0f;
    *(float *)(p + 0x24) = 0.0f;
    *(float *)(p + 0x28) = 1.0f;
    *(float *)(p + 0x2C) = 0.0f;
    _ApplyRyGV(p + 0x20, *(float *)(src + 0x14));

    {
        char *r = p + 0x34;
        int *q = (int *)(p + 0x30);

        for (i = 0; i < 4; i++) {
            *q = InitMultiBgaManager(1);
            *r = 0;
            q += 2;
            r += 8;
        }
    }

    return p;
}

extern void sceVu0ApplyMatrix(void *dst, void *m, void *v);
/* kept local: this TU's uses of debug_Arrow do not fit the prototype in camera-editor.h */
extern void debug_Arrow(float len, void *from, void *to, int r, int g, int b);
extern char *D_00639EA8;

/* generator.c:1259-1270, a static inline helper of this TU: the listing gives
   GeneratorGeo the rows 1262-1268, outside its own 1274-1410 span. */
static inline void SetGeneratorAimVector(char *gobj)
{
    char *w = *(char **)(*(char **)(gobj + 0x15C) + 0x830);
    float m[16];
    float v[4];

    UpdateRootMatrix(gobj);

    memset(v, 0, 16);
    v[2] = 1.0f;
    GetRootMatrix(m, gobj);
    v[3] = 0.0f;
    sceVu0ApplyMatrix(w + 0x20, m, v);
}

/* generator.c:481-486, a static inline helper of this TU: the listing gives
   GeneratorGeo the rows 469-485, i.e. ResetCurrentBga and EntryBga inlined
   inside this wrapper. */
static inline void EntryGeneratorBga2(char *gobj)
{
    char *cur = ResetCurrentBga(gobj);

    EntryBga(gobj, cur, 2);
    *(int *)(cur + 0x58) = 2;
}

/* generator.c:636-648, a static inline helper of this TU: the listing gives
   GeneratorGeo the rows 639-647.  The result is truncated to a byte at the
   call site, so the helper returns an 8-bit type. */
static inline unsigned char IsGeneratorCalling(void)
{
    char *g;

    g = (char *)isysGObjSearchFromObjKindID_begin(0x21);
    while (g != 0) {
        char *w = *(char **)(*(char **)(g + 0x15C) + 0x830);

        if (*(int *)(g + 0x16C) != 0) {
            if (*(int *)(w + 0xC) != 0) {
                if (*(int *)(w + 0x50) == 1) {
                    return 1;
                }
            }
        }
        g = (char *)isysGObjSearchFromObjKindID_next(g);
    }
    return 0;
}

/* generator.c:758-779, a static inline helper of this TU: the listing gives
   GeneratorGeo the rows 761-776. */
static inline void CallEnemyFromGenerator(char *gobj, float *pos, float *dir)
{
    char *w = *(char **)(*(char **)(gobj + 0x15C) + 0x830);

    if (CallEnemy(gobj, pos, dir, *(int *)(w + 0x14)) != 0) {
        float mtx[4];

        memset(mtx, 0, 16);
        mtx[3] = 1.0f;
        EntryMultiBgaManager(*(int *)(w + 0x48), 0, -1, (void *)test_CURRENTROOT(gobj), mtx);
    }
}

void GeneratorGeo(char *gobj)
{
    char *w = *(char **)(*(char **)(gobj + 0x15C) + 0x830);
    int hard = 0;
    StageLabelRange *sd = &D_005F5D50[stage_no];
    int noBoy = ((sd->f190 >> 1) & 1) && D_00639EA8 == 0;

    *(int *)(w + 0xC) = (int)IsNeedGeneratorHard(gobj);
    if (*(int *)(w + 0xC) != 0) {
        if (*(int *)(w + 0x64) < 30) {
            *(int *)(w + 0x64) = 30;
        }
    }

    if (*(int *)(w + 0) >= 12) {
        if (*(unsigned char *)(w + 0x12) != 0) {
            *(int *)(w + 8) = 0;
            *(char *)(w + 0x12) = 0;
        }

        if (isysGObjSearchFromObjKindID_begin(0x2F) != 0) {
            *(char *)(w + 0x11) = 1;
        } else {
            *(char *)(w + 0x11) = 0;
        }

        SetGeneratorAimVector(gobj);

        if (noBoy) {
            *(int *)(w + 8) = 0;
        }

        if (*(int *)(w + 8) == 0) {
            if (*(unsigned char *)(w + 0x10) == 0) {
                if (!noBoy) {
                    *(int *)(w + 4) = *(int *)(w + 4) + 1;
                    if (*(int *)(w + 4) >= 11) {
                        Generator_Call(gobj);
                        *(int *)(w + 4) = 0;
                    }
                }
            }
        }

        switch (*(int *)(w + 0x54)) {
        case 0:
            if (*(int *)(w + 8) != 0) {
                *(int *)(w + 0x54) = 1;
                *(int *)(w + 0x5C) = ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 2;
                switch_MainStatus(gobj, 1);
            }
            break;

        case 1:
            *(int *)(w + 0x5C) = *(int *)(w + 0x5C) - 1;
            if (*(int *)(w + 0x5C) < 0) {
                *(int *)(w + 0x54) = 2;
            }
            break;

        case 2:
            hard = 1;
            break;

        default:
            debug_assert(__FILE__, 1371);
            __assert(__FILE__, 1371, D_0063AC00);
            break;
        }

        if (*(unsigned char *)(w + 0x11) != 0) {
            hard = 1;
        }

        {
            float pos[4];
            int i;

            if (hard) {
                if (((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 2 < *(int *)(w + 0)) {
                    if (*(int *)(w + 8) != 0) {
                        GetRootPosition(pos, gobj);
                        for (i = 0; i < *(int *)(w + 8); i++) {
                            CallEnemyFromGenerator(gobj, pos, (float *)(w + 0x20));
                        }
                        *(int *)(w + 8) = 0;
                    }
                }
            }

            if (!IsGeneratorCalling()) {
                if (*(int *)(w + 0x64) == 0) {
                    switch_MainStatus(gobj, 0);
                }
            }

            if (*(int *)(w + 0x60) != -1) {
                if (*(int *)(w + 0x60) == 0) {
                    *(char *)(w + 0x44) = 1;
                    EntryGeneratorBga2(gobj);
                    *(int *)(w + 0x60) = -1;
                } else {
                    *(int *)(w + 0x60) = *(int *)(w + 0x60) - 1;
                }
            }

            debug_Arrow(100.0f, (void *)test_CURRENTROOT(gobj), w + 0x20, 0xFF, 0, 0xFF);
        }
    }

    if (*(int *)(w + 0x64) != 0) {
        *(int *)(w + 0x64) = *(int *)(w + 0x64) - 1;
    }
    *(int *)(w + 0) = *(int *)(w + 0) + 1;
}

/* generator.c:1414-1420, a static inline helper of this TU: the listing gives
   its rows 1417-1419 to GeneratorDL, outside GeneratorDL's own line span. */
static inline void SetGeneratorBgaRootPosition(char *gobj, GenBga *tbl)
{
    float pos[3];
    int i;
    int j;

    /* test_CURRENTROOT is unprototyped in this TU (C89 default int), as its
       earlier call sites need; the root matrix is read through a float view. */
    pos[0] = ((float *)test_CURRENTROOT(gobj))[0];
    pos[1] = ((float *)test_CURRENTROOT(gobj))[1];
    pos[2] = ((float *)test_CURRENTROOT(gobj))[2];

    for (i = 0; i < 4; i++) {
        char *p = tbl[i].p;

        *(float *)(p + 0x10) = pos[0];
        *(float *)(p + 0x14) = pos[1];
        *(float *)(p + 0x18) = pos[2];
    }
}

void GeneratorDL(char *gobj)
{
    char *w = *(char **)(*(char **)(gobj + 0x15C) + 0x830);
    GenBga *tbl = (GenBga *)(w + 0x30);
    int idx;

    SetGeneratorBgaRootPosition(gobj, tbl);

    if (*(unsigned char *)(w + 0x11)) {
        DispMultiBgaManagerWithKind(508, *(int *)(w + 0x38), 1);
    } else {
        DispMultiBgaManagerWithKind(507, *(int *)(w + 0x30), 1);
        DispMultiBgaManagerWithKind(508, *(int *)(w + 0x38), 1);
        DispMultiBgaManagerWithKind(509, *(int *)(w + 0x40), 1);
        DispMultiBgaManagerWithKind(506, *(int *)(w + 0x48), 1);
    }

    idx = *(int *)(w + 0x58);
    if (idx != -1) {
        GenBga *e = &tbl[idx];

        if (*(float *)e->p < 0.0f) {
            endfunc_BGA(gobj);
        }
    }
}

inline int GeneratorWorkEnd(char *a0)
{
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8) == 0;
}

inline int IsOpenGenerator(char *gobj)
{
    char *w = *(char **)(*(char **)(gobj + 0x15C) + 0x830);
    int ret = 0;
    if (*(int *)(w + 0x50) == 1) {
        GVGeo2 *g = (GVGeo2 *)(*(int *)(gobj + 8) * sizeof(GVGeo2) + (char *)D_002C2DC8);
        ret = (((int)(g->f48 << 27) >> 27) == -2) ? 0 : *(int *)(w + 0x50);
    }
    return ret;
}
