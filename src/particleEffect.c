#include "common.h"

#include "ico/types.h"

typedef struct PEGeo PEGeo;   /* the allocated per-effect geometry object */
typedef struct { float v[4]; } PEVector;
typedef struct { float v[4]; } PEQuaternion;
typedef struct {
    int           used;      /* 0x00 */
    int           pause;     /* 0x04 */
    int           geoCtrl;   /* 0x08 */
    int           sensing;   /* 0x0C */
    PEVector     *sensPos;   /* 0x10 */
    PEQuaternion *sensQuat;  /* 0x14 */
    PEGeo        *geo;       /* 0x18 */
} PEffect;
extern PEffect D_00720220[];

typedef struct { long long q[20]; } PE160;

extern void CopyQuaternion();
extern void CopyVector();

void setParticleEffectGeometry(int a0, int a1, int a2)
{
    CopyVector(a0);
    CopyQuaternion(a0 + 0x10, a2);
}
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", _setParticleEffect);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", setParticleEffect);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", execParticleEffect);
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", dispParticleEffect);
extern char D_006208E0[];
extern char D_00620920[];
extern char D_00620908[];
extern int D_00721020[];
extern void debug_StdPrintfDummy();
extern int iosMallocDebugNoAssert(int heap, int size, char *file, int line);
extern void *iosFree(void *ptr);
extern int setParticleEffect(int geo, int *pkg, int part);

/* the listing's lines 129-137: a static free-slot search with no out-of-line
 * copy, inlined here. */
static inline int searchFreeParticleEffect(void)
{
    int i;

    for (i = 0; i < 0x80; i++) {
        if (D_00720220[i].used == 0) {
            if (D_00720220[i].geo != 0) {
                debug_StdPrintfDummy(D_006208E0);
                for (;;) {
                }
            }
            return i;
        }
    }
    return -1;
}

int SetParticleEffectByPartition(int no, PEVector *pos, PEQuaternion *quat, int part)
{
    int id;

    id = searchFreeParticleEffect();
    if (id < 0) {
        debug_StdPrintfDummy(D_00620920);
        return -1;
    }
    D_00720220[id].used = 1;
    D_00720220[id].geoCtrl = 1;
    D_00720220[id].geo = (PEGeo *)iosMallocDebugNoAssert(part, 0x80, D_00620908, 501);
    D_00720220[id].sensing = 0;
    D_00720220[id].sensPos = 0;
    D_00720220[id].sensQuat = 0;
    if (D_00720220[id].geo != 0) {
        setParticleEffectGeometry((int)D_00720220[id].geo, (int)pos, (int)quat);
        if (setParticleEffect((int)D_00720220[id].geo,
                              (int *)((char *)D_00721020 + no * 0xA0), part) == 0) {
            iosFree(D_00720220[id].geo);
            D_00720220[id].geo = 0;
            D_00720220[id].used = 0;
            id = -1;
        }
    } else {
        D_00720220[id].used = 0;
        id = -1;
    }
    return id;
}
extern char D_00620940[];
extern void prim_DeleteParticle(int a0);
extern void *iosFree(void *ptr);

/* INTERIM: the listing's lines 430-435 (a static helper with no out-of-line
 * copy) are inlined into every deleter in this TU. */
static inline void deleteParticleEffectGeo(int no)
{
    prim_DeleteParticle(*(int *)((char *)D_00720220[no].geo + 0x28));
    *(int *)((char *)D_00720220[no].geo + 0x28) = 0;
    iosFree(*(void **)((char *)D_00720220[no].geo + 0x24));
    iosFree(D_00720220[no].geo);
    D_00720220[no].geo = 0;
}

void SetParticleEffectGeometry(int a0, int a1, int a2) {
    if (a0 >= 0) {
        if (D_00720220[a0].used == 0) {
            debug_StdPrintfDummy(D_00620940);
        } else {
            setParticleEffectGeometry((int)D_00720220[a0].geo, a1, a2);
        }
    }
}
extern int execParticleEffect(void *a0);
void SetParticleEffectUpperLimit(int no, float f) {
    char *o;
    if (no >= 0) {
        o = (char *)D_00720220[no].geo;
        *(int *)(o + 0x38) = 1;
        *(float *)(o + 0x3C) = f;
        execParticleEffect(o);
    }
}
/* the listing's lines 159-164: the per-particle vector setup, a static helper
 * with no out-of-line copy shared by setParticleEffect / execParticleEffect /
 * ExecParticleEffect. */
static inline void setParticleVector(char *d, char *s)
{
    CopyVector(d, s + 0x10);
    *(float *)(d + 0x0C) = *(float *)(s + 0x34);
    *(float *)(d + 0x1C) = *(float *)(s + 0x3C) * 128.0f;
    *(float *)(d + 0x10) = *(float *)(s + 0x60);
    *(float *)(d + 0x14) = *(float *)(s + 0x64);
    *(float *)(d + 0x18) = 128.0f;
}

/* the listing's lines 374-378. */
static inline void updateParticleVectors(int no)
{
    char *g;
    char *d;
    char *s;
    int i;

    g = (char *)D_00720220[no].geo;
    d = *(char **)(*(char **)(g + 0x28) + 0x190);
    s = *(char **)(g + 0x24);
    for (i = 0; i < *(int *)(g + 0x30); i++) {
        setParticleVector(d, s);
        s += 0x70;
        d += 0x20;
    }
}

void ExecParticleEffect(int no)
{
    int (*proc)(void *);

    if (D_00720220[no].used == 0) {
        return;
    }
    if (D_00720220[no].pause != 0) {
        return;
    }
    if (D_00720220[no].geoCtrl != 0) {
        if (D_00720220[no].sensing != 0) {
            SetParticleEffectGeometry(no, (int)D_00720220[no].sensPos,
                                      (int)D_00720220[no].sensQuat);
        }
        if (execParticleEffect(D_00720220[no].geo) == 0) {
            deleteParticleEffectGeo(no);
            D_00720220[no].used = 0;
        }
    } else {
        updateParticleVectors(no);
        proc = *(int (**)(void *))((char *)D_00720220[no].geo + 0x64);
        if (proc != 0) {
            if (proc(D_00720220[no].geo) == 0) {
                deleteParticleEffectGeo(no);
                D_00720220[no].used = 0;
            }
        }
    }
}
extern int D_0063A450;
extern char D_00620908[];
extern int iosMallocDebugNoAssert(int heap, int size, char *file, int line);
extern int setParticleEffect(int geo, int *pkg, int part);

void ResetParticleEffectPackages(int *pkg)
{
    PEVector pos;
    PEQuaternion quat;
    int part;
    int i;

    part = D_0063A450;
    for (i = 0; i < 0x80; i++) {
        if (D_00720220[i].used != 0 &&
            *(int **)((char *)D_00720220[i].geo + 0x20) == pkg) {
            CopyVector(&pos, D_00720220[i].geo);
            CopyQuaternion(&quat, (char *)D_00720220[i].geo + 0x10);
            deleteParticleEffectGeo(i);
            D_00720220[i].geo =
                (PEGeo *)iosMallocDebugNoAssert(part, 0x80, D_00620908, 663);
            D_00720220[i].used = 1;
            setParticleEffectGeometry((int)D_00720220[i].geo, (int)&pos, (int)&quat);
            setParticleEffect((int)D_00720220[i].geo, pkg, part);
        }
    }
}
extern PE160 D_004ECDF0;
extern char D_00620980[];
extern int D_00721020[];
extern void debug_StdPrintfDummy();
extern void memcpy(void *dst, int *a1, int a2);

void SetParticleEffectPackage(int a0, int *a1, int a2) {
    *(PE160 *)((unsigned char *)D_00721020 + a0 * 0xA0) = D_004ECDF0;
    if (*(int *)&D_004ECDF0 != *a1) {
        debug_StdPrintfDummy(D_00620980, *a1);
    }
    memcpy(((unsigned char *)D_00721020 + a0 * 0xA0), a1, a2);
}
extern PEffect D_004ECDD0;

void InitParticleEffects(void)
{
    int i;

    for (i = 0; i < 0x80; i++) {
        D_00720220[i] = D_004ECDD0;
    }
}
void ExecParticleEffects(void) {
    int i;
    for (i = 0; i < 0x80; i++) {
        ExecParticleEffect(i);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/particleEffect", DispParticleEffects);
void DeleteParticleEffect(int no)
{
    if (D_00720220[no].used != 0 || D_00720220[no].geo != 0) {
        deleteParticleEffectGeo(no);
        D_00720220[no].used = 0;
    }
}
void SetParticleEffectPauseFlag(int a0, int a1) {
    D_00720220[a0].pause = a1;
}
extern int D_0063A450;
extern int SetParticleEffectByPartition(int no, PEVector *pos, PEQuaternion *quat, int part);

int SetParticleEffect(int no, PEVector *pos, PEQuaternion *quat)
{
    return SetParticleEffectByPartition(no, pos, quat, D_0063A450);
}
/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * SetParticleEffect's line 532 into SetParticleEffectActiveSensing, so it is a
 * public `inline` of the deferred tail; until the tail's asm members are C its
 * out-of-line copy stays the plain definition above and this caller inlines the
 * static stand-in SetParticleEffect_inl, which collapses at layout. */
static inline int SetParticleEffect_inl(int no, PEVector *pos, PEQuaternion *quat)
{
    return SetParticleEffectByPartition(no, pos, quat, D_0063A450);
}

int SetParticleEffectActiveSensing(int no, PEVector *pos, PEQuaternion *quat)
{
    int id;

    id = SetParticleEffect_inl(no, pos, quat);
    if (id != -1) {
        D_00720220[id].sensing = 1;
        D_00720220[id].sensPos = pos;
        D_00720220[id].sensQuat = quat;
    }
    return id;
}
int *GetParticleEffectPackage(int idx)
{
    return (int *)((char *)D_00721020 + idx * 0xA0);
}
void DeleteParticleEffectsByPackage(int *pkg)
{
    int i;

    for (i = 0; i < 0x80; i++) {
        if (D_00720220[i].used != 0 &&
            *(int **)((char *)D_00720220[i].geo + 0x20) == pkg) {
            deleteParticleEffectGeo(i);
            D_00720220[i].used = 0;
        }
    }
}
/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * GetParticleEffectPackage's line 118 and DeleteParticleEffectsByPackage's
 * lines 673-676 into DeleteParticleEffectsByID, so both are public `inline`s of
 * the deferred tail; until the tail's asm members are C their out-of-line copies
 * stay the plain definitions above and this caller inlines the static stand-ins,
 * which collapse at layout. */
static inline int *GetParticleEffectPackage_inl(int idx)
{
    return (int *)((char *)D_00721020 + idx * 0xA0);
}

static inline void DeleteParticleEffectsByPackage_inl(int *pkg)
{
    int i;

    for (i = 0; i < 0x80; i++) {
        if (D_00720220[i].used != 0 &&
            *(int **)((char *)D_00720220[i].geo + 0x20) == pkg) {
            deleteParticleEffectGeo(i);
            D_00720220[i].used = 0;
        }
    }
}

void DeleteParticleEffectsByID(int id)
{
    DeleteParticleEffectsByPackage_inl(GetParticleEffectPackage_inl(id));
}
int GetParticleEffectData(int a0) {
    return (int)D_00720220[a0].geo;
}
void DisableParticleEffectGeometryControl(int a0) {
    D_00720220[a0].geoCtrl = 0;
}
extern char D_0062A278[];
int GetParticleIDWithName(char *name) {
    int i;
    for (i = 0; i < 0x3D; i++) {
        if (strcmp(D_0062A278 + i * 0x50, name) == 0) {
            return i;
        }
    }
    return -1;
}
int GetParticleLoopFlag(int a0)
{
    int *p;
    if (a0 < 0) {
        return -1;
    }
    p = (int *)((char *)D_00721020 + a0 * 0xA0);
    return p[1] == 1;
}
extern void sceVu0CopyVector(void *dst, void *src);

void ParticleEffects_SetAllGoal(void *goal)
{
    int i;

    for (i = 0; i < 0x80; i++) {
        if (D_00720220[i].used != 0) {
            char *v = (char *)D_00720220[i].geo;
            if (v != 0) {
                sceVu0CopyVector(v + 0x50, goal);
            }
        }
    }
}
void SetParticleEffectClipEnableFlag(int a0, int a1) {
    if (a0 >= 0) {
        *(int *)((char *)D_00720220[a0].geo + 0x34) = a1;
    }
}
void SetParticleEffectDrainLevel(int a0, float f) {
    if (a0 >= 0) {
        *(float *)((char *)D_00720220[a0].geo + 0x40) = f;
    }
}
