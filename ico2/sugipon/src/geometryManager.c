#include "common.h"
#include "typedef.h"
#include "sugiCommon.h"
#include "geometryManager.h"
#include "debug_exception.h"
#include "gobj.h"
#include "girl_act.h"
#include "motionManager2.h"
#include <libvu0.h>

void GetRootQuaternionByDObj(int a0, int *a1)
{
    int *p;
    int *q;
    int idx;
    p = (int *)a1[0];
    if (p == 0)
        goto null_path;
    q = (int *)p[0x57];
    idx = a1[1];
    MultiQuaternion(a0, q[0x4] + (idx << 4), (int)a1 + 0xD0);
    return;
null_path:
    CopyQuaternion(a0, (int)a1 + 0xD0);
}

/* kept local: this TU's uses of GetMatrixFromQuaternionPos do not fit the prototype in quaternion.h */
extern void GetMatrixFromQuaternionPos(void *a0, void *a1, void *a2);

void UpdateRootMatrixByDObj(char *a0)
{
    char *p = a0 + 0xA0;
    char *fobj = *(char **)(a0 + 0xC);
    GetMatrixFromQuaternionPos(fobj, a0 + 0xD0, p);
    {
        char *q = *(char **)a0;
        if (q != 0) {
            sceVu0MulMatrix(fobj, *(char **)((char *)GOBJ_SUB(q) + 0xC) + (*(int *)(a0 + 0x4) << 6),
                            fobj);
        }
    }
    *(float *)(fobj + 0x34) = *(float *)(fobj + 0x34) + *(float *)(p + 0xC0);
    GetRootQuaternionByDObj(*(void **)(a0 + 0x10), a0);
}

void GetRootQuaternion(int a0, int a1)
{
    GetRootQuaternionByDObj(a0, (int)((GObj *)(a1))->p_15C);
}

void UpdateRootMatrix(int a0)
{
    UpdateRootMatrixByDObj((int)((GObj *)(a0))->p_15C);
}

/* kept local: this TU's uses of CopyQuaternion do not fit the prototype in quaternion.h */
extern void CopyQuaternion();

void SetRootBaseQuaternion(int a0)
{
    CopyQuaternion((int)((GObj *)(a0))->p_15C + 0xC0);
}

/* kept local: this TU's uses of DivQuaternion do not fit the prototype in quaternion.h */
extern void DivQuaternion(void *a0, void *a1, int a2);

void SetRootQuaternion(char *a0, void *a1)
{
    char *q = (char *)GOBJ_SUB(a0) + 0xD0;
    char *p;
    CopyQuaternion(q, a1);
    p = (char *)GOBJ_SUB(a0);
    if (*(int *)p != 0) {
        char *m = *(char **)(*(int *)p + 0x15C);
        DivQuaternion(q, a1, *(int *)(m + 0x10) + (*(int *)(p + 4) << 4));
    }
}

/* kept local: this TU's uses of CopyMatrix do not fit the prototype in matrixDrive.h */
extern void CopyMatrix();
/* kept local: this TU's uses of MatrixDrive_GetMatrix do not fit the prototype in matrixDrive.h */
extern int *MatrixDrive_GetMatrix();
/* kept local: this TU's uses of MatrixDrive_PopMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_PopMatrix();
/* kept local: this TU's uses of MatrixDrive_PushMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_PushMatrix();
/* kept local: this TU's uses of MatrixDrive_TransMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_TransMatrix(float a, float b, float c);

void SetRootMatrixWithTransOffsetByDObj(void *a0)
{
    register float rf12 __asm__("$f12");
    register float rf13 __asm__("$f13");
    register float rf14 __asm__("$f14");
    float a = rf12;
    float b = rf13;
    float c = rf14;
    MatrixDrive_PushMatrix();
    CopyMatrix(MatrixDrive_GetMatrix(), (void *)((char *)a0 + 0x20));
    MatrixDrive_TransMatrix(a, b, c);
    CopyMatrix((void *)*(int *)((char *)a0 + 0xC), MatrixDrive_GetMatrix());
    MatrixDrive_PopMatrix();
}

void SetRootMatrixWithTransOffset(int a0)
{
    SetRootMatrixWithTransOffsetByDObj((int)((GObj *)(a0))->p_15C);
}

/* kept local: this TU's uses of GetInverseQuaternion do not fit the prototype in quaternion.h */
extern void GetInverseQuaternion();
/* kept local: this TU's uses of MultiQuaternion do not fit the prototype in quaternion.h */
extern void MultiQuaternion();

void GetRootMatrixRotOffsetByDObj(int a0, int a1)
{
    GetInverseQuaternion(a0, a1 + 0x60);
    MultiQuaternion(a0, a0, *(int *)(a1 + 0x10));
}

void GetRootMatrixRotOffset(void *a0, int a1)
{
    GetRootMatrixRotOffsetByDObj(a0, (void *)GOBJ_SUB(a1));
}

/* kept local: this TU's uses of MultiMatrixByQuaternion do not fit the prototype in quaternion.h */
extern void MultiMatrixByQuaternion();

void SetRootMatrixRotOffsetByDObj(int *self, int *other)
{
    MatrixDrive_PushMatrix();
    CopyMatrix(MatrixDrive_GetMatrix(), (char *)self + 0x20);
    MultiMatrixByQuaternion(other);
    CopyMatrix((void *)self[0xC / 4], MatrixDrive_GetMatrix());
    MatrixDrive_PopMatrix();
    MultiQuaternion((void *)self[0x10 / 4], (char *)self + 0x60, other);
}

void SetRootMatrixRotOffset(int a0, void *a1)
{
    SetRootMatrixRotOffsetByDObj((void *)GOBJ_SUB(a0), a1);
}

/* kept local: this TU's uses of CopyVector do not fit the prototype in matrixDrive.h */
extern void CopyVector();
/* kept local: this TU's uses of MatrixDrive_SetTransposeMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_SetTransposeMatrix(void *a0, void *a1);
/* kept local: this TU's uses of ZeroVector do not fit the prototype in matrixDrive.h */
extern char ZeroVector[];

/* INTERIM stand-ins: the ROM inlines GetRootPosition (listing lines 55-64 and
 * 85) and SetDirectRootPositionNoFitting (lines 255-274) into the two
 * WithNodePoint entries, which sit AHEAD of them in the object because those
 * three are deferred-inline tail members. Their out-of-line copies stay plain
 * definitions at their ROM slots while the tail still has asm members. */
typedef union {
    float f[4];
    long long ll[2];
} SdrpVec4i;

static __inline__ void GetRootPositionByDObj_i(void *a0, char *src)
{
    float *p = (float *)(src + 0xA0);
    float f0;
    int *g = *(int **)src;
    if (g) {
        sceVu0ApplyMatrix(
            (int *)a0, *(int *)((int)((GObj *)((char *)g))->p_15C + 0xC) + (*(int *)(src + 4) << 6),
            (char *)p);
    } else {
        CopyVector((int)a0, (int)p);
    }
    f0 = p[0x30];
    *(float *)((char *)a0 + 0x4) += f0;
    *(float *)((char *)a0 + 0xC) = 1.0f;
}

static __inline__ void GetRootPosition_i(void *a0, char *outer)
{
    GetRootPositionByDObj_i(a0, (char *)((GObj *)(outer))->p_15C);
}

static __inline__ void SetRootPosition_ii(char *a0, void *a1)
{
    char buf[0x40];
    SdrpVec4i *p = (SdrpVec4i *)((char *)GOBJ_SUB(a0) + 0xA0);
    CopyVector(p, a1);
    p->f[1] = p->f[1] - *(float *)((char *)p + 0xC0);
    p->f[3] = 1.0f;
    {
        char *sub = (char *)GOBJ_SUB(a0);
        char *q = *(char **)sub;
        if (q != 0) {
            MatrixDrive_SetTransposeMatrix(buf,
                                           (char *)(GOBJ_SUB(q)->f_C + (*(int *)(sub + 4) << 6)));
            sceVu0ApplyMatrix(p, buf, p);
        }
    }
}

static __inline__ void SetDirectRootPositionNoFitting_i(char *self, void *v)
{
    Sub15C *sub = GOBJ_SUB(self);
    char *p = (char *)sub + 0xA0;
    char pos[0x10];
    char tmp[0x10];

    CopyVector(pos, v);
    CopyVector(tmp, p);
    SetRootPosition_ii(self, pos);
    CopyVector((char *)sub + 0x1F0, p);
    CopyVector((char *)sub + 0x110, p);
    GOBJ_SUB(self)->f_4EC = 0;
    CopyVector((char *)sub + 0x200, v);
    CopyVector((char *)sub + 0x130, ZeroVector);
    CopyVector((char *)sub + 0x170, ZeroVector);
}

void SetDirectRootPositionNoFittingWithNodePoint(char *gobj, int node, float *pos, float t)
{
    float v[4];
    float w[4];
    int idx;

    idx = GetSkeltonFocusNode(gobj, node);
    sceVu0SubVector(v, pos,
                    (char *)(*(int *)((int)((GObj *)(gobj))->p_15C + 0xC) + (idx << 6)) + 0x30);
    sceVu0ScaleVector(v, v, t);
    GetRootPosition_i(w, gobj);
    sceVu0AddVector(w, w, v);
    SetDirectRootPositionNoFitting_i(gobj, w);
}

void SetDirectRootPositionNoFittingWithNodePointXZ(char *gobj, int node, float *pos, float t)
{
    float v[4];
    float w[4];
    int idx;

    idx = GetSkeltonFocusNode(gobj, node);
    sceVu0SubVector(v, pos,
                    (char *)(*(int *)((int)((GObj *)(gobj))->p_15C + 0xC) + (idx << 6)) + 0x30);
    sceVu0ScaleVector(v, v, t);
    GetRootPosition_i(w, gobj);
    v[1] = 0.0f;
    sceVu0AddVector(w, w, v);
    SetDirectRootPositionNoFitting_i(gobj, w);
}

void SetDirectRootPositionWithNodePoint(char *gobj, int node, float *pos, float t)
{
    SetDirectRootPositionNoFittingWithNodePoint(gobj, node, pos, t);
    AdjustMotionHeightToNearestField(gobj);
}

extern char D_0054D750[];
extern char D_0054D768[];
extern char D_00639EF0[];
extern char D_00639EF8[];
extern void __assert(char *file, int line, char *expr);

/* The 0x15C slot is the engine's sub-object HANDLE: the code stores an int and
 * reads it back as a pointer, so every read of it is a union view and any store
 * in between forces the reload the ROM performs. */

#define SUBOF(o) (((SubHandle *)((o) + 0x15C))->p)

/* kept local: this TU's uses of DivQuaternion do not fit the prototype in quaternion.h */
extern void DivQuaternion();

/* INTERIM: the January-2002 listing inlines LocalizeDirectionOrient into
 * LocalizeGeometry (its geometryManager.c:348-352 rows sit inside
 * LocalizeGeometry's :363-390 span).  The TU's out-of-line copy stays a plain
 * definition further down while the deferred-inline tail still has asm members,
 * so the body is repeated here as a static stand-in. */
static __inline__ void LocalizeDirectionOrient_i(int *self, int *a1)
{
    int buf[16];
    char *obj = (char *)a1[0];
    char *ctx = ((GObj *)(obj))->p_15C;
    CopyMatrix(buf, (void *)(*(int *)(ctx + 0xC) + (a1[1] << 6)));
    MatrixDrive_SetTransposeMatrix((char *)buf, (char *)buf);
    sceVu0ApplyMatrix((int *)((char *)((GObj *)((char *)self))->p_15C + 0x520), (int)buf,
                      (char *)((GObj *)((char *)self))->p_15C + 0x520);
    sceVu0Normalize((int *)((char *)((GObj *)((char *)self))->p_15C + 0x520),
                    (int *)((char *)((GObj *)((char *)self))->p_15C + 0x520));
    ((GObj *)((char *)self))->p_15C->f_52C = 0;
}

void LocalizeGeometry(char *gobj, int *dobj)
{
    int mtx[16];
    char *sub;
    char *m;

    sub = SUBOF(gobj);

    m = sub + 0xA0;
    if (*(int *)sub != 0) {
        debug_assertMessage(D_0054D750, 371, D_0054D768);
        __assert(D_0054D750, 371, D_00639EF0);
        debug_assert(D_0054D750, 372);
        __assert(D_0054D750, 372, D_00639EF8);
    }

    *(float *)(m + 0xC) = 1.0f;
    *(float *)(m + 0x4) -= *(float *)(SUBOF(gobj) + 0x160);
    *(float *)(m + 0x154) -= *(float *)(SUBOF(gobj) + 0x160);
    MatrixDrive_SetTransposeMatrix(mtx, *(char **)(SUBOF((char *)dobj[0]) + 0xC) + (dobj[1] << 6));
    sceVu0ApplyMatrix(m, mtx, m);
    sceVu0ApplyMatrix(sub + 0x1F0, mtx, sub + 0x1F0);
    DivQuaternion(sub + 0xD0, sub + 0xD0,
                  *(char **)(SUBOF((char *)dobj[0]) + 0x10) + (dobj[1] << 4));
    LocalizeDirectionOrient_i((int *)gobj, dobj);
}

void GetGlobalDirectionOrient(int *self, int *other, char *p)
{
    CopyVector((int)self, (int)p);
    {
        char *sub = ((GObj *)((char *)other))->p_15C;
        char *a = *(char **)sub;
        if (a != 0) {
            char *inner_struct = ((GObj *)(a))->p_15C;
            int inner_field = *(int *)(inner_struct + 0xC);
            int idx = *(int *)(sub + 0x4);
            sceVu0ApplyMatrix(self, inner_field + (idx << 6), p);
        }
    }
    *(int *)((char *)self + 0x4) = 0;
    sceVu0Normalize(self, self);
}

void GlobalizeGeometry(char *gobj)
{
    char *sub = SUBOF(gobj);
    char *m = sub + 0xA0;
    char *w = sub + 0x470;

    *(float *)(sub + 0xAC) = 1.0f;
    if (*(char **)SUBOF(gobj) != 0) {
        sceVu0ApplyMatrix(
            m, *(char **)(SUBOF(*(char **)SUBOF(gobj)) + 0xC) + (*(int *)(SUBOF(gobj) + 0x4) << 6),
            m);
        sceVu0ApplyMatrix(SUBOF(gobj) + 0x1F0,
                          *(char **)(SUBOF(*(char **)SUBOF(gobj)) + 0xC) +
                              (*(int *)(SUBOF(gobj) + 0x4) << 6),
                          SUBOF(gobj) + 0x1F0);
    }
    *(float *)(SUBOF(gobj) + 0xA4) =
        *(float *)(SUBOF(gobj) + 0xA4) + *(float *)(SUBOF(gobj) + 0x160);
    *(float *)(SUBOF(gobj) + 0x1F4) =
        *(float *)(SUBOF(gobj) + 0x1F4) + *(float *)(SUBOF(gobj) + 0x160);
    GetRootQuaternion(sub + 0xD0, gobj);
    GetGlobalDirectionOrient(sub + 0x520, gobj, sub + 0x520);
    *(int *)(w + 0xB4) = 0;
    sceVu0Normalize(SUBOF(gobj) + 0x520, SUBOF(gobj) + 0x520);
    *(int *)(w + 0xBC) = 0;
}

void GetRootVelocity(int a0, int a1)
{
    CopyVector(a0, (int)((GObj *)(a1))->p_15C + 0x130);
}

/* kept local: this TU's uses of MatrixDrive_TransMatrixV do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_TransMatrixV(void *a0);
/* kept local: this TU's uses of MatrixDrive_RotMatrixX do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_RotMatrixX(int a0);

void GetInitialInverseMatrixByDObj(char *mat, char *mdl)
{
    int no;
    char *nd;

    MatrixDrive_PushMatrix();
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    no = 0;
loop:
    {
        nd = *(char **)(mdl + 0x8C) + (no << 6);
        MatrixDrive_PushMatrix();
        MatrixDrive_TransMatrixV(nd + 0x10);
        MultiMatrixByQuaternion(nd + 0x20);
        MatrixDrive_SetTransposeMatrix(mat + (no << 6), MatrixDrive_GetMatrix());
        if (*(int *)(nd + 0x30) != -1) {
            getInitialInverseMatrix(mat, mdl, *(int *)(nd + 0x30));
        }
        MatrixDrive_PopMatrix();
    }
    if (*(int *)(nd + 0x34) != -1) {
        no = *(int *)(nd + 0x34);
        goto loop;
    }
    MatrixDrive_PopMatrix();
}

void GetInitialInverseMatrix(char *mat, char *gobj)
{
    char *mdl;
    int no;
    char *nd;

    MatrixDrive_PushMatrix();
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    mdl = (char *)GOBJ_SUB(gobj);
    no = 0;
loop:
    {
        nd = *(char **)(mdl + 0x8C) + (no << 6);
        MatrixDrive_PushMatrix();
        MatrixDrive_TransMatrixV(nd + 0x10);
        MultiMatrixByQuaternion(nd + 0x20);
        MatrixDrive_SetTransposeMatrix(mat + (no << 6), MatrixDrive_GetMatrix());
        if (*(int *)(nd + 0x30) != -1) {
            getInitialInverseMatrix(mat, mdl, *(int *)(nd + 0x30));
        }
        MatrixDrive_PopMatrix();
    }
    if (*(int *)(nd + 0x34) != -1) {
        no = *(int *)(nd + 0x34);
        goto loop;
    }
    MatrixDrive_PopMatrix();
}

void GetInitialSkeltonMatrixByDObj(char *mdl)
{
    int no;
    char *nd;
    char *dst;

    MatrixDrive_PushMatrix();
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_RotMatrixX(-0x8000);
    no = 0;
loop:
    {
        nd = *(char **)(mdl + 0x8C) + (no << 6);
        MatrixDrive_PushMatrix();
        MatrixDrive_TransMatrixV(nd + 0x10);
        MultiMatrixByQuaternion(nd + 0x20);
        dst = *(char **)(mdl + 0xC) + (no << 6);
        CopyMatrix(dst, MatrixDrive_GetMatrix());
        if (*(int *)(nd + 0x30) != -1) {
            getInitialMatrix(mdl, *(int *)(nd + 0x30));
        }
        MatrixDrive_PopMatrix();
    }
    if (*(int *)(nd + 0x34) != -1) {
        no = *(int *)(nd + 0x34);
        goto loop;
    }
    MatrixDrive_PopMatrix();
}

extern int D_0028FEB8[];

/* .bss, owned by geometryManager.o and reached only from this file (MAIN.MAP
   names no symbol in the run; its geometryManager.o .bss size 0x100 fixes the
   length, and matrixDrive's 0x1000 and quaternion's 0x400 tile the rest of the
   region exactly).  The live character objects the cylinder check walks. */
static int charGObjList[64];

extern int D_00639EFC;
extern char D_0054D7C8[];

/* listing lines 540-547: the kind test the list builder runs on every live
   object; inlined at its single call site. */
static inline int isCharGObj(char *o)
{
    int i;

    if (*(int *)(o + 0x4) == 1 && *(int *)(o + 0x16C) != 0) {
        for (i = 0; D_0028FEB8[i] != -1; i++) {
            if (*(int *)(o + 0xC) == D_0028FEB8[i]) {
                return 1;
            }
        }
    }
    return 0;
}

void MakeCharGObjList(void)
{
    char *o;

    o = isysGObjGetExist_begin();
    D_00639EFC = 0;
    while (o != 0) {
        if (isCharGObj(o) != 0) {
            charGObjList[D_00639EFC++] = (int)o;
            if (D_00639EFC >= 0x41) {
                debug_assertMessage(D_0054D750, 0x22E, D_0054D7C8);
                __assert(D_0054D750, 0x22E, D_00639EF0);
            }
        }
        o = isysGObjGetExist_next(o);
    }
    charGObjList[D_00639EFC] = 0;
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/geometryManager", cylinderCollisionCheck);

/* kept local: this TU's uses of MatrixDrive_SetTransposeMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_SetTransposeMatrix();

void LocalizeDirectionOrient(int *self, int *a1)
{
    int buf[16];
    char *obj = (char *)a1[0];
    char *ctx = ((GObj *)(obj))->p_15C;
    CopyMatrix(buf, (void *)(*(int *)(ctx + 0xC) + (a1[1] << 6)));
    MatrixDrive_SetTransposeMatrix((char *)buf, (char *)buf);
    sceVu0ApplyMatrix((int *)((char *)((GObj *)((char *)self))->p_15C + 0x520), (int)buf,
                      (char *)((GObj *)((char *)self))->p_15C + 0x520);
    sceVu0Normalize((int *)((char *)((GObj *)((char *)self))->p_15C + 0x520),
                    (int *)((char *)((GObj *)((char *)self))->p_15C + 0x520));
    ((GObj *)((char *)self))->p_15C->f_52C = 0;
}

/* INTERIM: ROM inlines GetRootPosition into both cylinder-collision walkers and
 * inlines CylinderCollisionWithControlDynamics into CylinderCollision; the TU's
 * out-of-line copies stay plain definitions while the deferred-inline tail
 * still has asm members, so their bodies are repeated here as static stand-ins. */
static __inline__ void GetRootPosition_ic(void *a0, char *outer)
{
    char *src = ((GObj *)(outer))->p_15C;
    float *p = (float *)(src + 0xA0);
    float f0;
    int *g = *(int **)src;
    if (g) {
        sceVu0ApplyMatrix(
            (int *)a0, *(int *)((int)((GObj *)((char *)g))->p_15C + 0xC) + (*(int *)(src + 4) << 6),
            (char *)p);
    } else {
        CopyVector((int)a0, (int)p);
    }
    f0 = p[0x30];
    *(float *)((char *)a0 + 0x4) += f0;
    *(float *)((char *)a0 + 0xC) = 1.0f;
}

int GetCylinderCollision(char *self, int target, float r, float h, float s, int ctrl)
{
    float pos[4];

    GetRootPosition_ic(pos, self);
    return cylinderCollisionCheck(self, pos, target, r, r * r, h, s, 1.0f - s, ctrl, 0);
}

int GetCylinderCollisionWithExceptOwnCollision(char *self, int target, float r, float h, float s,
                                               float t, int ctrl)
{
    float pos[4];

    GetRootPosition_ic(pos, self);
    return cylinderCollisionCheck(self, pos, target, r, r * r, h, s, t, ctrl, 1);
}

static __inline__ int CylinderCollisionWithControlDynamics_i(char *self, int group, int ctrl,
                                                             float r, float h, float s)
{
    float pos[4];
    int hit = 0;
    int i;
    char *o;
    char *sub;
    float rr;

    sub = (char *)GOBJ_SUB(self);
    if (*(int *)(sub + 0x7C) == 0 || *(int *)(sub + 0x3C8) == 0) {
        return 0;
    }
    GetRootPosition_ic(pos, self);
    rr = r * r;
    for (i = 0, o = (char *)charGObjList[0]; i < D_00639EFC; i++, o = (char *)charGObjList[i]) {
        if (*(int *)(o + 0xC) != group)
            continue;
        if (o == self)
            continue;
        {
            Sub15C *osub = GOBJ_SUB(o);
            if (osub->f_7C == 0 || *(int *)((char *)osub + 0x3C8) == 0) {
                if (isMustCheckCylinder(self, o) == 0)
                    continue;
            }
        }
        hit = cylinderCollisionCheck(self, pos, (int)o, r, rr, h, s, 1.0f - s, ctrl, 0);
    }
    return hit;
}

int CylinderCollision(char *self, int group, float r, float h, float s)
{
    return CylinderCollisionWithControlDynamics_i(self, group, 1, r, h, s);
}

int CylinderCollisionWithControlDynamics(char *self, int group, int ctrl, float r, float h, float s)
{
    float pos[4];
    int hit = 0;
    int i;
    char *o;
    char *sub;
    float rr;

    sub = (char *)GOBJ_SUB(self);
    if (*(int *)(sub + 0x7C) == 0 || *(int *)(sub + 0x3C8) == 0) {
        return 0;
    }
    GetRootPosition_ic(pos, self);
    rr = r * r;
    for (i = 0, o = (char *)charGObjList[0]; i < D_00639EFC; i++, o = (char *)charGObjList[i]) {
        if (*(int *)(o + 0xC) != group)
            continue;
        if (o == self)
            continue;
        {
            Sub15C *osub = GOBJ_SUB(o);
            if (osub->f_7C == 0 || *(int *)((char *)osub + 0x3C8) == 0) {
                if (isMustCheckCylinder(self, o) == 0)
                    continue;
            }
        }
        hit = cylinderCollisionCheck(self, pos, (int)o, r, rr, h, s, 1.0f - s, ctrl, 0);
    }
    return hit;
}

/* kept local: this TU's uses of GetMatrixFromQuaternionPos do not fit the prototype in quaternion.h */
extern void GetMatrixFromQuaternionPos();

void GetRootMatrixByDObj(void *a0, char *src)
{
    float *p = (float *)(src + 0xA0);
    GetMatrixFromQuaternionPos(a0, src + 0xD0, p);
    {
        int *g = *(int **)src;
        if (g) {
            sceVu0MulMatrix(a0,
                            (char *)(*(int *)((int)((GObj *)((char *)g))->p_15C + 0xC) +
                                     (*(int *)(src + 4) << 6)),
                            (int)a0);
        }
    }
    *(float *)((char *)a0 + 0x34) += p[0x30];
}

void GetRootMatrix(void *a0, char *outer)
{
    char *src = ((GObj *)(outer))->p_15C;
    float *p = (float *)(src + 0xA0);
    GetMatrixFromQuaternionPos(a0, src + 0xD0, p);
    {
        int *g = *(int **)src;
        if (g) {
            sceVu0MulMatrix(a0,
                            (char *)(*(int *)((int)((GObj *)((char *)g))->p_15C + 0xC) +
                                     (*(int *)(src + 4) << 6)),
                            (int)a0);
        }
    }
    *(float *)((char *)a0 + 0x34) += p[0x30];
}

void GetRootPositionByDObj(void *a0, char *src)
{
    float *p = (float *)(src + 0xA0);
    float f0;
    int *g = *(int **)src;
    if (g) {
        sceVu0ApplyMatrix(
            (int *)a0, *(int *)((int)((GObj *)((char *)g))->p_15C + 0xC) + (*(int *)(src + 4) << 6),
            (char *)p);
    } else {
        CopyVector((int)a0, (int)p);
    }
    f0 = p[0x30];
    *(float *)((char *)a0 + 0x4) += f0;
    *(float *)((char *)a0 + 0xC) = 1.0f;
}

/* INTERIM: ROM inlines SetRootPosition into this function and into
 * SetDirectRootPositionNoFitting; the TU's out-of-line copy stays a plain
 * definition while the deferred-inline tail still has asm members. */
typedef union {
    float f[4];
    long long ll[2];
} SdrpVec4;

static __inline__ void SetRootPosition_i(char *a0, void *a1)
{
    char buf[0x40];
    SdrpVec4 *p = (SdrpVec4 *)((char *)GOBJ_SUB(a0) + 0xA0);
    CopyVector(p, a1);
    p->f[1] = p->f[1] - *(float *)((char *)p + 0xC0);
    p->f[3] = 1.0f;
    {
        char *sub = (char *)GOBJ_SUB(a0);
        char *q = *(char **)sub;
        if (q != 0) {
            MatrixDrive_SetTransposeMatrix(buf,
                                           (char *)(GOBJ_SUB(q)->f_C + (*(int *)(sub + 4) << 6)));
            sceVu0ApplyMatrix(p, buf, p);
        }
    }
}

void SetDirectRootPosition(char *self, void *v)
{
    Sub15C *sub = GOBJ_SUB(self);
    char *p = (char *)sub + 0xA0;
    char pos[0x10];
    char tmp[0x10];

    CopyVector(pos, v);
    CopyVector(tmp, p);
    SetRootPosition_i(self, pos);
    CopyVector((char *)sub + 0x1F0, p);
    CopyVector((char *)sub + 0x110, p);
    GOBJ_SUB(self)->f_4EC = 0;
    CopyVector((char *)sub + 0x200, v);
    CopyVector((char *)sub + 0x130, ZeroVector);
    CopyVector((char *)sub + 0x170, ZeroVector);
    AdjustMotionHeightToNearestField(self);
}

void SetDirectRootPositionNoFitting(char *self, void *v)
{
    Sub15C *sub = GOBJ_SUB(self);
    char *p = (char *)sub + 0xA0;
    char pos[0x10];
    char tmp[0x10];

    CopyVector(pos, v);
    CopyVector(tmp, p);
    SetRootPosition_i(self, pos);
    CopyVector((char *)sub + 0x1F0, p);
    CopyVector((char *)sub + 0x110, p);
    GOBJ_SUB(self)->f_4EC = 0;
    CopyVector((char *)sub + 0x200, v);
    CopyVector((char *)sub + 0x130, ZeroVector);
    CopyVector((char *)sub + 0x170, ZeroVector);
}

/* The root position at sub+0xA0 is a 4-lane vector the engine also moves as
 * two quadwords (CopyVector); the union is the TU's view of it. */

void SetRootPosition(char *a0, void *a1)
{
    char buf[0x40];
    Vec4 *p = (Vec4 *)((char *)GOBJ_SUB(a0) + 0xA0);
    CopyVector(p, a1);
    p->f[1] = p->f[1] - *(float *)((char *)p + 0xC0);
    p->f[3] = 1.0f;
    {
        char *sub = (char *)GOBJ_SUB(a0);
        char *q = *(char **)sub;
        if (q != 0) {
            MatrixDrive_SetTransposeMatrix(buf,
                                           (char *)(GOBJ_SUB(q)->f_C + (*(int *)(sub + 4) << 6)));
            sceVu0ApplyMatrix(p, buf, p);
        }
    }
}

void GetRootPosition(void *a0, char *outer)
{
    char *src = ((GObj *)(outer))->p_15C;
    float *p = (float *)(src + 0xA0);
    float f0;
    int *g = *(int **)src;
    if (g) {
        sceVu0ApplyMatrix(
            (int *)a0, *(int *)((int)((GObj *)((char *)g))->p_15C + 0xC) + (*(int *)(src + 4) << 6),
            (char *)p);
    } else {
        CopyVector((int)a0, (int)p);
    }
    f0 = p[0x30];
    *(float *)((char *)a0 + 0x4) += f0;
    *(float *)((char *)a0 + 0xC) = 1.0f;
}

/* kept local: this TU's uses of ZUnitVector do not fit the prototype in matrixDrive.h */
extern char ZUnitVector[];

void GetRootOrient(char *a0, char *a1)
{
    char buf[0x40];
    char *sub = (char *)GOBJ_SUB(a1);
    char *p = sub + 0xA0;
    GetMatrixFromQuaternionPos(buf, sub + 0xD0, p);
    {
        char *q = *(char **)sub;
        if (q != 0) {
            sceVu0MulMatrix(buf, (char *)(GOBJ_SUB(q)->f_C + (*(int *)(sub + 4) << 6)), (int)buf);
        }
    }
    *(float *)(buf + 0x34) = *(float *)(buf + 0x34) + *(float *)(p + 0xC0);
    sceVu0ApplyMatrix((int *)a0, buf, (int)ZUnitVector);
    *(int *)(a0 + 4) = 0;
    sceVu0Normalize(a0, a0);
}

int LimitExistGeometry(float *pos, int *exist)
{
    int ret = 0;
    int i;

    for (i = 2; i >= 0; exist++, pos++, i--) {
        if (*pos < -100000.0f) {
            *pos = -100000.0f;
            *exist = 0;
            ret = 1;
        } else if (*pos > 100000.0f) {
            *pos = 100000.0f;
            *exist = 0;
            ret = 1;
        }
    }
    return ret;
}

void GetRootMatrixTransOffsetByDObj(char *dst, char *src)
{
    char tmp[0x40];
    MatrixDrive_SetTransposeMatrix(tmp, src + 0x20);
    sceVu0MulMatrix(tmp, tmp, *(int *)(src + 0xC));
    CopyVector((int)dst, (int)(tmp + 0x30));
}

void GetRootMatrixTransOffset(char *dst, char *src)
{
    char tmp[0x40];
    Sub15C *p = GOBJ_SUB(src);
    MatrixDrive_SetTransposeMatrix(tmp, (char *)p + 0x20);
    sceVu0MulMatrix(tmp, tmp, p->f_C);
    CopyVector((int)dst, (int)(tmp + 0x30));
}

/* kept local: this TU's uses of GetMatrixFromQuaternion do not fit the prototype in quaternion.h */
extern void GetMatrixFromQuaternion(int dst, int src);

void GetRootMotionOrient(char *a0, char *a1)
{
    char m[0x40];
    char buf[0x40];
    char *b = buf;
    char *sub = (char *)GOBJ_SUB(a1);
    char *p = sub + 0xA0;
    GetMatrixFromQuaternionPos(b, sub + 0xD0, p);
    {
        char *q = *(char **)sub;
        if (q != 0) {
            sceVu0MulMatrix(b, (char *)(GOBJ_SUB(q)->f_C + (*(int *)(sub + 4) << 6)), (int)b);
        }
    }
    *(float *)(b + 0x34) = *(float *)(b + 0x34) + *(float *)(p + 0xC0);
    GetMatrixFromQuaternion((int)m, (int)((char *)GOBJ_SUB(a1) + 0xE0));
    sceVu0MulMatrix(m, b, (int)m);
    sceVu0ApplyMatrix((int *)a0, m, (int)ZUnitVector);
}

void GetRootMotionMatrix(char *a0, char *a1)
{
    char buf[0x40];
    char *sub = (char *)GOBJ_SUB(a1);
    char *p = sub + 0xA0;
    GetMatrixFromQuaternionPos(buf, sub + 0xD0, p);
    {
        char *q = *(char **)sub;
        if (q != 0) {
            sceVu0MulMatrix(buf, (char *)(GOBJ_SUB(q)->f_C + (*(int *)(sub + 4) << 6)), (int)buf);
        }
    }
    *(float *)(buf + 0x34) = *(float *)(buf + 0x34) + *(float *)(p + 0xC0);
    GetMatrixFromQuaternion((int)a0, (int)((char *)GOBJ_SUB(a1) + 0xE0));
    sceVu0MulMatrix(a0, buf, (int)a0);
}

/* kept local: this TU's uses of AddVectorXYZ do not fit the prototype in matrixDrive.h */
extern void AddVectorXYZ(void *a0, void *a1, void *a2);
/* kept local: this TU's uses of _ScaleVectorXYZ do not fit the prototype in Matrix.h */
extern void _ScaleVectorXYZ(void *a0, void *a1, float f);

void GetProjectionPosOfPlane(void *a0, void *a1, void *a2)
{
    float buf[4];
    float dot;
    dot = plane_distance(a2, a1);
    _ScaleVectorXYZ(buf, a1, -dot);
    AddVectorXYZ(a0, a2, buf);
    *(float *)((char *)a0 + 0xC) = 1.0f;
}

/* kept local: this TU's uses of _AddVectorXYZ do not fit the prototype in Matrix.h */
extern void _AddVectorXYZ(void *a0, void *a1, void *a2);

float GetProjectionOfPlane(void *a0, void *a1, void *a2)
{
    float buf[4];
    float f = 0.0f;
    float dot;
    dot = plane_distance(a2, a1);
    _ScaleVectorXYZ(buf, a1, -dot + f);
    _AddVectorXYZ(a0, a2, buf);
    return dot;
}

float GetProjectionOfPlaneWithKeepAway(void *a0, void *a1, void *a2, float f)
{
    float buf[4];
    float dot;
    dot = plane_distance(a2, a1);
    _ScaleVectorXYZ(buf, a1, -dot + f);
    _AddVectorXYZ(a0, a2, buf);
    return dot;
}

extern int charGObjList[];

int *GetCharGObjList(void)
{
    return charGObjList;
}

/* kept local: this TU's uses of MatrixDrive_TransMatrixV do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_TransMatrixV();

void getInitialInverseMatrix(char *mat, char *mdl, int no)
{
    char *nd = *(char **)(mdl + 0x8C) + (no << 6);
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(nd + 0x10);
    MultiMatrixByQuaternion(nd + 0x20);
    MatrixDrive_SetTransposeMatrix(mat + (no << 6), MatrixDrive_GetMatrix());
    if (*(int *)(nd + 0x30) != -1) {
        getInitialInverseMatrix(mat, mdl, *(int *)(nd + 0x30));
    }
    MatrixDrive_PopMatrix();
    if (*(int *)(nd + 0x34) != -1) {
        getInitialInverseMatrix(mat, mdl, *(int *)(nd + 0x34));
    }
}

void getInitialMatrix(char *mdl, int no)
{
    char *nd = *(char **)(mdl + 0x8C) + (no << 6);
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(nd + 0x10);
    MultiMatrixByQuaternion(nd + 0x20);
    CopyMatrix(*(char **)(mdl + 0xC) + (no << 6), MatrixDrive_GetMatrix());
    if (*(int *)(nd + 0x30) != -1) {
        getInitialMatrix(mdl, *(int *)(nd + 0x30));
    }
    MatrixDrive_PopMatrix();
    if (*(int *)(nd + 0x34) != -1) {
        getInitialMatrix(mdl, *(int *)(nd + 0x34));
    }
}
