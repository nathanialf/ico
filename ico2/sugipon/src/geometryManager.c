#include "typedef.h"
#include "sugiCommon.h"
#include "geometryManager.h"
#include "debug_exception.h"
#include "gobj.h"
#include "girl_act.h"
#include "motionManager2.h"
#include <libvu0.h>
#include "Matrix.h"
#include "matrixDrive.h"
#include "quaternion.h"
#include "fieldCollision.h"
#include <assert.h>

/* The display object's root block (Sub15C root, typedef.h) holds the root
   position, its quaternion and the root height; the object it hangs from is
   the word at 0 and that object's node is parentNode. */
void GetRootQuaternionByDObj(void *q, Sub15C *dobj)
{
    GObj *parent;
    int idx;
    parent = *(GObj **)dobj;
    if (parent == 0)
        goto null_path;
    idx = dobj->parentNode;
    MultiQuaternion(q, (float *)parent->dobj->nodeQuat + (idx << 2), dobj->root.quat);
    return;
null_path:
    CopyQuaternion(q, dobj->root.quat);
}

void UpdateRootMatrixByDObj(Sub15C *dobj)
{
    struct MotRoot *p = &dobj->root;
    char *fobj = (char *)dobj->nodeMtx;
    GetMatrixFromQuaternionPos(fobj, p->quat, p->pos);
    {
        GObj *q = *(GObj **)dobj;
        if (q != 0) {
            sceVu0MulMatrix(fobj, (char *)q->dobj->nodeMtx + (dobj->parentNode << 6), fobj);
        }
    }
    *(float *)(fobj + 0x34) = *(float *)(fobj + 0x34) + p->height;
    GetRootQuaternionByDObj((float *)dobj->nodeQuat, dobj);
}

void GetRootQuaternion(void *q, GObj *obj)
{
    GetRootQuaternionByDObj(q, obj->dobj);
}

void UpdateRootMatrix(GObj *obj)
{
    UpdateRootMatrixByDObj(obj->dobj);
}

void SetRootBaseQuaternion(GObj *obj, void *q)
{
    CopyQuaternion(obj->dobj->root.baseQuat, q);
}

void SetRootQuaternion(GObj *obj, void *quat)
{
    float *q = obj->dobj->root.quat;
    Sub15C *p;
    CopyQuaternion(q, quat);
    p = obj->dobj;
    if (*(GObj **)p != 0) {
        Sub15C *m = (*(GObj **)p)->dobj;
        DivQuaternion(q, quat, (float *)m->nodeQuat + (p->parentNode << 2));
    }
}

void SetRootMatrixWithTransOffsetByDObj(void *dobj, float x, float y, float z)
{
    MatrixDrive_PushMatrix();
    CopyMatrix(MatrixDrive_GetMatrix(), (char *)dobj + 0x20);
    MatrixDrive_TransMatrix(x, y, z);
    CopyMatrix(*(void **)((char *)dobj + 0xC), MatrixDrive_GetMatrix());
    MatrixDrive_PopMatrix();
}

void SetRootMatrixWithTransOffset(GObj *obj, float x, float y, float z)
{
    SetRootMatrixWithTransOffsetByDObj(obj->dobj, x, y, z);
}

void GetRootMatrixRotOffsetByDObj(void *q, Sub15C *dobj)
{
    GetInverseQuaternion(q, dobj->quat);
    MultiQuaternion(q, q, (void *)dobj->nodeQuat);
}

void GetRootMatrixRotOffset(void *q, GObj *obj)
{
    GetRootMatrixRotOffsetByDObj(q, obj->dobj);
}

void SetRootMatrixRotOffsetByDObj(Sub15C *dobj, void *q)
{
    MatrixDrive_PushMatrix();
    CopyMatrix(MatrixDrive_GetMatrix(), (char *)dobj + 0x20);
    MultiMatrixByQuaternion(q);
    CopyMatrix((void *)dobj->nodeMtx, MatrixDrive_GetMatrix());
    MatrixDrive_PopMatrix();
    MultiQuaternion((void *)dobj->nodeQuat, (char *)dobj + 0x60, q);
}

void SetRootMatrixRotOffset(GObj *obj, void *q)
{
    SetRootMatrixRotOffsetByDObj(obj->dobj, q);
}

/* INTERIM stand-ins: the ROM inlines GetRootPosition (listing lines 55-64 and
 * 85) and SetDirectRootPositionNoFitting (lines 255-274) into the two
 * WithNodePoint entries, which sit AHEAD of them in the object because those
 * three are deferred-inline tail members. Their out-of-line copies stay plain
 * definitions at their ROM slots while the tail still has asm members. */
typedef union {
    float f[4];
    long long ll[2];
} SdrpVec4i;

static __inline__ void GetRootPositionByDObj_i(float *pos, Sub15C *src)
{
    struct MotRoot *root = &src->root;
    float f0;
    GObj *g = *(GObj **)src;
    if (g) {
        sceVu0ApplyMatrix(pos, (char *)g->dobj->nodeMtx + (src->parentNode << 6), root->pos);
    } else {
        CopyVector(pos, root->pos);
    }
    f0 = root->height;
    pos[1] += f0;
    pos[3] = 1.0f;
}

static __inline__ void GetRootPosition_i(float *pos, GObj *obj)
{
    GetRootPositionByDObj_i(pos, obj->dobj);
}

static __inline__ void SetRootPosition_ii(GObj *obj, void *pos)
{
    float buf[16];
    SdrpVec4i *p = (SdrpVec4i *)obj->dobj->root.pos;
    CopyVector(p, pos);
    p->f[1] = p->f[1] - *(float *)((char *)p + 0xC0);
    p->f[3] = 1.0f;
    {
        Sub15C *sub = obj->dobj;
        GObj *q = *(GObj **)sub;
        if (q != 0) {
            MatrixDrive_SetTransposeMatrix(buf,
                                           (float *)(q->dobj->nodeMtx + (sub->parentNode << 6)));
            sceVu0ApplyMatrix(p, buf, p);
        }
    }
}

static __inline__ void SetDirectRootPositionNoFitting_i(GObj *self, void *v)
{
    Sub15C *sub = self->dobj;
    float *p = sub->root.pos;
    float pos[4];
    float tmp[4];

    CopyVector(pos, v);
    CopyVector(tmp, p);
    SetRootPosition_ii(self, pos);
    CopyVector(sub->root.last, p);
    CopyVector(sub->root.savePos, p);
    self->dobj->ctrl.posReserve = 0;
    CopyVector(sub->root.clipFrom, v);
    CopyVector(sub->root.move, ZeroVector);
    CopyVector(sub->root.delta, ZeroVector);
}

void SetDirectRootPositionNoFittingWithNodePoint(GObj *gobj, int node, float *pos, float t)
{
    float v[4];
    float w[4];
    int idx;

    idx = GetSkeltonFocusNode(gobj, node);
    sceVu0SubVector(v, pos, (float *)(gobj->dobj->nodeMtx + (idx << 6)) + 12);
    sceVu0ScaleVector(v, v, t);
    GetRootPosition_i(w, gobj);
    sceVu0AddVector(w, w, v);
    SetDirectRootPositionNoFitting_i(gobj, w);
}

void SetDirectRootPositionNoFittingWithNodePointXZ(GObj *gobj, int node, float *pos, float t)
{
    float v[4];
    float w[4];
    int idx;

    idx = GetSkeltonFocusNode(gobj, node);
    sceVu0SubVector(v, pos, (float *)(gobj->dobj->nodeMtx + (idx << 6)) + 12);
    sceVu0ScaleVector(v, v, t);
    GetRootPosition_i(w, gobj);
    v[1] = 0.0f;
    sceVu0AddVector(w, w, v);
    SetDirectRootPositionNoFitting_i(gobj, w);
}

void SetDirectRootPositionWithNodePoint(GObj *gobj, int node, float *pos, float t)
{
    SetDirectRootPositionNoFittingWithNodePoint(gobj, node, pos, t);
    AdjustMotionHeightToNearestField(gobj);
}

/* The 0x15C slot is the engine's sub-object HANDLE: the code stores an int and
 * reads it back as a pointer, so every read of it is a union view and any store
 * in between forces the reload the ROM performs. */

#define SUBOF(o) (((SubHandle *)&((GObj *)(o))->dobj)->sub)

/* INTERIM: the January-2002 listing inlines LocalizeDirectionOrient into
 * LocalizeGeometry (its geometryManager.c:348-352 rows sit inside
 * LocalizeGeometry's :363-390 span).  The TU's out-of-line copy stays a plain
 * definition further down while the deferred-inline tail still has asm members,
 * so the body is repeated here as a static stand-in. */
static __inline__ void LocalizeDirectionOrient_i(GObj *self, int *link)
{
    float buf[16];
    GObj *obj = (GObj *)link[0];
    Sub15C *ctx = obj->dobj;
    CopyMatrix(buf, (void *)(ctx->nodeMtx + (link[1] << 6)));
    MatrixDrive_SetTransposeMatrix(buf, buf);
    sceVu0ApplyMatrix(self->dobj->ctrl.dir, buf, self->dobj->ctrl.dir);
    sceVu0Normalize(self->dobj->ctrl.dir, self->dobj->ctrl.dir);
    self->dobj->ctrl.dir[3] = 0;
}

void LocalizeGeometry(GObj *gobj, int *dobj)
{
    float mtx[16];
    Sub15C *sub;
    struct MotRoot *m;

    sub = SUBOF(gobj);

    m = &sub->root;
    if (*(int *)sub != 0) {
        debug_assertMessage(
            "src/geometryManager.c", 371,
            "Fatal error! Geometry localize function called with GObj\n    that already have parent.\nExit...\n");
        __assert("src/geometryManager.c", 371, "e");
        debug_assert("src/geometryManager.c", 372);
        __assert("src/geometryManager.c", 372, "0");
    }

    m->pos[3] = 1.0f;
    m->pos[1] -= SUBOF(gobj)->root.height;
    m->last[1] -= SUBOF(gobj)->root.height;
    MatrixDrive_SetTransposeMatrix(mtx, (float *)(SUBOF(dobj[0])->nodeMtx + (dobj[1] << 6)));
    sceVu0ApplyMatrix(m->pos, mtx, m->pos);
    sceVu0ApplyMatrix(sub->root.last, mtx, sub->root.last);
    DivQuaternion(sub->root.quat, sub->root.quat,
                  (char *)SUBOF(dobj[0])->nodeQuat + (dobj[1] << 4));
    LocalizeDirectionOrient_i(gobj, dobj);
}

void GetGlobalDirectionOrient(float *dir, GObj *obj, void *src)
{
    CopyVector(dir, src);
    {
        Sub15C *sub = obj->dobj;
        GObj *a = *(GObj **)sub;
        if (a != 0) {
            Sub15C *inner_struct = a->dobj;
            int inner_field = inner_struct->nodeMtx;
            int idx = sub->parentNode;
            sceVu0ApplyMatrix(dir, (char *)inner_field + (idx << 6), src);
        }
    }
    *(int *)&dir[1] = 0;
    sceVu0Normalize(dir, dir);
}

void GlobalizeGeometry(GObj *gobj)
{
    Sub15C *sub = SUBOF(gobj);
    float *m = sub->root.pos;
    struct MotCtrl *w = &sub->ctrl;

    sub->root.pos[3] = 1.0f;
    if (*(GObj **)SUBOF(gobj) != 0) {
        sceVu0ApplyMatrix(
            m, (char *)SUBOF(*(GObj **)SUBOF(gobj))->nodeMtx + (SUBOF(gobj)->parentNode << 6), m);
        sceVu0ApplyMatrix(SUBOF(gobj)->root.last,
                          (char *)SUBOF(*(GObj **)SUBOF(gobj))->nodeMtx +
                              (SUBOF(gobj)->parentNode << 6),
                          SUBOF(gobj)->root.last);
    }
    SUBOF(gobj)->root.pos[1] = SUBOF(gobj)->root.pos[1] + SUBOF(gobj)->root.height;
    SUBOF(gobj)->root.last[1] = SUBOF(gobj)->root.last[1] + SUBOF(gobj)->root.height;
    GetRootQuaternion(sub->root.quat, gobj);
    GetGlobalDirectionOrient(sub->ctrl.dir, gobj, sub->ctrl.dir);
    w->dir[1] = 0;
    sceVu0Normalize(SUBOF(gobj)->ctrl.dir, SUBOF(gobj)->ctrl.dir);
    w->dir[3] = 0;
}

void GetRootVelocity(float *vel, GObj *obj)
{
    CopyVector(vel, obj->dobj->root.move);
}

void GetInitialInverseMatrixByDObj(char *mat, char *mdl)
{
    int no;
    SkelNode *nd;

    MatrixDrive_PushMatrix();
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    no = 0;
loop:
    {
        nd = (SkelNode *)(*(char **)(mdl + 0x8C) + (no << 6));
        MatrixDrive_PushMatrix();
        MatrixDrive_TransMatrixV(nd->pos);
        MultiMatrixByQuaternion(nd->quat);
        MatrixDrive_SetTransposeMatrix(mat + (no << 6), MatrixDrive_GetMatrix());
        if (nd->child != -1) {
            getInitialInverseMatrix(mat, mdl, nd->child);
        }
        MatrixDrive_PopMatrix();
    }
    if (nd->sibling != -1) {
        no = nd->sibling;
        goto loop;
    }
    MatrixDrive_PopMatrix();
}

void GetInitialInverseMatrix(char *mat, GObj *gobj)
{
    char *mdl;
    int no;
    SkelNode *nd;

    MatrixDrive_PushMatrix();
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    mdl = (char *)GOBJ_SUB(gobj);
    no = 0;
loop:
    {
        nd = (SkelNode *)(*(char **)(mdl + 0x8C) + (no << 6));
        MatrixDrive_PushMatrix();
        MatrixDrive_TransMatrixV(nd->pos);
        MultiMatrixByQuaternion(nd->quat);
        MatrixDrive_SetTransposeMatrix(mat + (no << 6), MatrixDrive_GetMatrix());
        if (nd->child != -1) {
            getInitialInverseMatrix(mat, mdl, nd->child);
        }
        MatrixDrive_PopMatrix();
    }
    if (nd->sibling != -1) {
        no = nd->sibling;
        goto loop;
    }
    MatrixDrive_PopMatrix();
}

void GetInitialSkeltonMatrixByDObj(char *mdl)
{
    int no;
    SkelNode *nd;
    char *dst;

    MatrixDrive_PushMatrix();
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_RotMatrixX(-0x8000);
    no = 0;
loop:
    {
        nd = (SkelNode *)(*(char **)(mdl + 0x8C) + (no << 6));
        MatrixDrive_PushMatrix();
        MatrixDrive_TransMatrixV(nd->pos);
        MultiMatrixByQuaternion(nd->quat);
        dst = *(char **)(mdl + 0xC) + (no << 6);
        CopyMatrix(dst, MatrixDrive_GetMatrix());
        if (nd->child != -1) {
            getInitialMatrix(mdl, nd->child);
        }
        MatrixDrive_PopMatrix();
    }
    if (nd->sibling != -1) {
        no = nd->sibling;
        goto loop;
    }
    MatrixDrive_PopMatrix();
}

/* .data, owned by geometryManager.o and read only here (MAIN.MAP names no
   symbol in the run; its geometryManager.o .data size 0x14 fixes the length).
   The object kinds the character list builder accepts, -1 terminated. */
static int charGObjKinds[5] = {1, 2, 4, 47, -1};

/* .bss, owned by geometryManager.o and reached only from this file (MAIN.MAP
   names no symbol in the run; its geometryManager.o .bss size 0x100 fixes the
   length, and matrixDrive's 0x1000 and quaternion's 0x400 tile the rest of the
   region exactly).  The live character objects the cylinder check walks. */
static GObj *charGObjList[64];

/* the TU's .sdata word after the two assert literals (MAIN.MAP names nothing
   in the run): the number of entries in charGObjList */
static int charGObjCount = 0; /* derived name */

/* listing lines 540-547: the kind test the list builder runs on every live
   object; inlined at its single call site. */
static inline int isCharGObj(char *o)
{
    int i;

    if (*(int *)(o + 0x4) == 1 && *(int *)(o + 0x16C) != 0) {
        for (i = 0; charGObjKinds[i] != -1; i++) {
            if (*(int *)(o + 0xC) == charGObjKinds[i]) {
                return 1;
            }
        }
    }
    return 0;
}

void MakeCharGObjList(void)
{
    GObj *o;

    o = isysGObjGetExist_begin();
    charGObjCount = 0;
    while (o != 0) {
        if (isCharGObj(o) != 0) {
            charGObjList[charGObjCount++] = o;
            if (charGObjCount >= 0x41) {
                debug_assertMessage("src/geometryManager.c", 558,
                                    "TOO MANY CHARACTERS EXIST ON THIS STAGE(>64)\n");
                __assert("src/geometryManager.c", 558, "e");
            }
        }
        o = isysGObjGetExist_next(o);
    }
    charGObjList[charGObjCount] = 0;
}

/* The wall-clip request handed to ClipWall / ClipWallE: the segment endpoints,
 * the clipped point at 0x20, the clip radius at 0x70, the owner to ignore at
 * 0x74 and the hit result at 0x88. */
typedef struct {
    /* 0x00 */ float from[4];
    /* 0x10 */ float to[4];
    /* 0x20 */ float out[4];
    /* 0x30 */ char _30[0x40];
    /* 0x70 */ float radius;
    /* 0x74 */ void *owner;
    /* 0x78 */ int _78;
    /* 0x7C */ int _7C;
    /* 0x80 */ char _80[8];
    /* 0x88 */ int hit;
    /* 0x8C */ char _8c[0x34];
} CylClipWork;

static __inline__ void GetRootPosition_cc(float *pos, GObj *obj)
{
    Sub15C *src = obj->dobj;
    struct MotRoot *root = &src->root;
    float f0;
    GObj *g = *(GObj **)src;
    if (g) {
        sceVu0ApplyMatrix(pos, (char *)g->dobj->nodeMtx + (src->parentNode << 6), root->pos);
    } else {
        CopyVector(pos, root->pos);
    }
    f0 = root->height;
    pos[1] += f0;
    pos[3] = 1.0f;
}

/* INTERIM: the January-2002 listing inlines SetRootPosition (its :180-188 rows)
 * and SetDirectRootPositionNoFitting (its :255-274 rows, which carry the
 * SetRootPosition rows inside them) into cylinderCollisionCheck; the TU's
 * out-of-line copies stay plain definitions further down while the
 * deferred-inline tail still has asm members, so their bodies are repeated here
 * as static stand-ins. */
typedef union {
    float f[4];
    long long ll[2];
} CylVec4;

static __inline__ void SetRootPosition_c(GObj *obj, void *pos)
{
    float buf[16];
    CylVec4 *p = (CylVec4 *)obj->dobj->root.pos;
    CopyVector(p, pos);
    p->f[1] = p->f[1] - *(float *)((char *)p + 0xC0);
    p->f[3] = 1.0f;
    {
        Sub15C *sub = obj->dobj;
        GObj *q = *(GObj **)sub;
        if (q != 0) {
            MatrixDrive_SetTransposeMatrix(buf,
                                           (float *)(q->dobj->nodeMtx + (sub->parentNode << 6)));
            sceVu0ApplyMatrix(p, buf, p);
        }
    }
}

static __inline__ void SetDirectRootPositionNoFitting_c(GObj *self, void *v)
{
    Sub15C *sub = self->dobj;
    float *p = sub->root.pos;
    float pos[4];
    float tmp[4];

    CopyVector(pos, v);
    CopyVector(tmp, p);
    SetRootPosition_c(self, pos);
    CopyVector(sub->root.last, p);
    CopyVector(sub->root.savePos, p);
    self->dobj->ctrl.posReserve = 0;
    CopyVector(sub->root.clipFrom, v);
    CopyVector(sub->root.move, ZeroVector);
    CopyVector(sub->root.delta, ZeroVector);
}

int cylinderCollisionCheck(GObj *self, float *ppos, GObj *target, float r, float rr, float h,
                           float s, float t, int ctrl, int exceptOwn)
{
    float pos[4];
    float v[4];
    float d1[4];
    float d2[4];
    float d3[4];
    CylClipWork w;
    float dy;
    float len;
    float over;
    float a;
    float b;
    float c;

    GetRootPosition_cc(pos, target);
    dy = pos[1] - ppos[1];
    if (!((dy < 0.0f ? -dy : dy) < h)) {
        goto fail;
    }
    sceVu0SubVector(v, pos, ppos);
    v[1] = 0.0f;
    len = VectorLengthSquare(v);
    if (!(len < rr)) {
        goto fail;
    }
    over = r - _Sqrt(len);
    sceVu0Normalize(v, v);
    sceVu0ScaleVector(d1, v, over * s);
    sceVu0SubVector(d2, ppos, d1);
    sceVu0ScaleVector(d1, v, over * t);
    sceVu0AddVector(d3, pos, d1);

    if (self != 0) {
        if (exceptOwn != 0) {
            w.owner = self;
            w._78 = -1;
            w._7C = 0;
            w.radius = SUBOF(self)->root.radius;
            CopyVector(w.from, ppos);
            CopyVector(w.to, d2);
            ClipWallE(&w);
            if (w.hit != 0) {
                CopyVector(d2, w.out);
            }
            w.radius = SUBOF(target)->root.radius;
            CopyVector(w.from, pos);
            CopyVector(w.to, d3);
            ClipWallE(&w);
            if (w.hit != 0) {
                CopyVector(d3, w.out);
            }
            goto moved;
        }
        w.radius = SUBOF(self)->root.radius;
        CopyVector(w.from, ppos);
        CopyVector(w.to, d2);
        ClipWall(&w);
        if (w.hit != 0) {
            CopyVector(d2, w.out);
        }
    }
    w.radius = SUBOF(target)->root.radius;
    CopyVector(w.from, pos);
    CopyVector(w.to, d3);
    ClipWall(&w);
    if (w.hit != 0) {
        CopyVector(d3, w.out);
    }
moved:
    if (ctrl != 0) {
        if (self != 0) {
            b = SUBOF(self)->root.last[1];
            c = SUBOF(self)->root.clipFrom[1];
            a = SUBOF(self)->root.move[1];
            SetDirectRootPositionNoFitting_c(self, d2);
            SUBOF(self)->root.move[1] = a;
            SUBOF(self)->root.last[1] = b;
            SUBOF(self)->root.clipFrom[1] = c;
        }
        b = SUBOF(target)->root.last[1];
        c = SUBOF(target)->root.clipFrom[1];
        a = SUBOF(target)->root.move[1];
        SetDirectRootPositionNoFitting_c(target, d3);
        SUBOF(target)->root.move[1] = a;
        SUBOF(target)->root.last[1] = b;
        SUBOF(target)->root.clipFrom[1] = c;
    } else {
        if (self != 0) {
            SetRootPosition_c(self, d2);
        }
        SetRootPosition_c(target, d3);
    }
    return 1;
fail:
    return 0;
}

void LocalizeDirectionOrient(GObj *self, int *link)
{
    float buf[16];
    GObj *obj = (GObj *)link[0];
    Sub15C *ctx = obj->dobj;
    CopyMatrix(buf, (void *)(ctx->nodeMtx + (link[1] << 6)));
    MatrixDrive_SetTransposeMatrix(buf, buf);
    sceVu0ApplyMatrix(self->dobj->ctrl.dir, buf, self->dobj->ctrl.dir);
    sceVu0Normalize(self->dobj->ctrl.dir, self->dobj->ctrl.dir);
    self->dobj->ctrl.dir[3] = 0;
}

/* INTERIM: ROM inlines GetRootPosition into both cylinder-collision walkers and
 * inlines CylinderCollisionWithControlDynamics into CylinderCollision; the TU's
 * out-of-line copies stay plain definitions while the deferred-inline tail
 * still has asm members, so their bodies are repeated here as static stand-ins. */
static __inline__ void GetRootPosition_ic(float *pos, GObj *obj)
{
    Sub15C *src = obj->dobj;
    struct MotRoot *root = &src->root;
    float f0;
    GObj *g = *(GObj **)src;
    if (g) {
        sceVu0ApplyMatrix(pos, (char *)g->dobj->nodeMtx + (src->parentNode << 6), root->pos);
    } else {
        CopyVector(pos, root->pos);
    }
    f0 = root->height;
    pos[1] += f0;
    pos[3] = 1.0f;
}

/* kept local: girl_act.c defines it inline just before its own user, with no
   earlier declaration there, so girl_act.h does not carry it */
extern int isMustCheckCylinder(void *a, void *b);

/* No caller in the ROM, so the bytes cannot decide the return type: int as sugipon's scalar getters. */
int GetCylinderCollision(GObj *self, GObj *target, float r, float h, float s, int ctrl)
{
    float pos[4];

    GetRootPosition_ic(pos, self);
    return cylinderCollisionCheck(self, pos, target, r, r * r, h, s, 1.0f - s, ctrl, 0);
}

int GetCylinderCollisionWithExceptOwnCollision(GObj *self, GObj *target, float r, float h, float s,
                                               float t, int ctrl)
{
    float pos[4];

    GetRootPosition_ic(pos, self);
    return cylinderCollisionCheck(self, pos, target, r, r * r, h, s, t, ctrl, 1);
}

static __inline__ int CylinderCollisionWithControlDynamics_i(GObj *self, int group, int ctrl,
                                                             float r, float h, float s)
{
    float pos[4];
    int hit = 0;
    int i;
    GObj *o;
    Sub15C *sub;
    float rr;

    sub = GOBJ_SUB(self);
    if (sub->cylinderOn == 0 || sub->root.word328 == 0) {
        return 0;
    }
    GetRootPosition_ic(pos, self);
    rr = r * r;
    for (i = 0, o = charGObjList[0]; i < charGObjCount; i++, o = charGObjList[i]) {
        if (o->kind != group)
            continue;
        if (o == self)
            continue;
        {
            Sub15C *osub = GOBJ_SUB(o);
            if (osub->cylinderOn == 0 || osub->root.word328 == 0) {
                if (isMustCheckCylinder(self, o) == 0)
                    continue;
            }
        }
        hit = cylinderCollisionCheck(self, pos, o, r, rr, h, s, 1.0f - s, ctrl, 0);
    }
    return hit;
}

int CylinderCollision(GObj *self, int group, float r, float h, float s)
{
    return CylinderCollisionWithControlDynamics_i(self, group, 1, r, h, s);
}

int CylinderCollisionWithControlDynamics(GObj *self, int group, int ctrl, float r, float h, float s)
{
    float pos[4];
    int hit = 0;
    int i;
    GObj *o;
    Sub15C *sub;
    float rr;

    sub = GOBJ_SUB(self);
    if (sub->cylinderOn == 0 || sub->root.word328 == 0) {
        return 0;
    }
    GetRootPosition_ic(pos, self);
    rr = r * r;
    for (i = 0, o = charGObjList[0]; i < charGObjCount; i++, o = charGObjList[i]) {
        if (o->kind != group)
            continue;
        if (o == self)
            continue;
        {
            Sub15C *osub = GOBJ_SUB(o);
            if (osub->cylinderOn == 0 || osub->root.word328 == 0) {
                if (isMustCheckCylinder(self, o) == 0)
                    continue;
            }
        }
        hit = cylinderCollisionCheck(self, pos, o, r, rr, h, s, 1.0f - s, ctrl, 0);
    }
    return hit;
}

void GetRootMatrixByDObj(float *m, Sub15C *src)
{
    struct MotRoot *root = &src->root;
    GetMatrixFromQuaternionPos(m, root->quat, root->pos);
    {
        GObj *g = *(GObj **)src;
        if (g) {
            sceVu0MulMatrix(m, (char *)g->dobj->nodeMtx + (src->parentNode << 6), m);
        }
    }
    m[13] += root->height;
}

void GetRootMatrix(void *mtx, GObj *obj)
{
    float *m = mtx;
    Sub15C *src = obj->dobj;
    struct MotRoot *root = &src->root;
    GetMatrixFromQuaternionPos(m, root->quat, root->pos);
    {
        GObj *g = *(GObj **)src;
        if (g) {
            sceVu0MulMatrix(m, (char *)g->dobj->nodeMtx + (src->parentNode << 6), m);
        }
    }
    m[13] += root->height;
}

void GetRootPositionByDObj(void *dst, Sub15C *src)
{
    float *pos = dst;
    struct MotRoot *root = &src->root;
    float f0;
    GObj *g = *(GObj **)src;
    if (g) {
        sceVu0ApplyMatrix(pos, (char *)g->dobj->nodeMtx + (src->parentNode << 6), root->pos);
    } else {
        CopyVector(pos, root->pos);
    }
    f0 = root->height;
    pos[1] += f0;
    pos[3] = 1.0f;
}

/* INTERIM: ROM inlines SetRootPosition into this function and into
 * SetDirectRootPositionNoFitting; the TU's out-of-line copy stays a plain
 * definition while the deferred-inline tail still has asm members. */
typedef union {
    float f[4];
    long long ll[2];
} SdrpVec4;

static __inline__ void SetRootPosition_i(GObj *obj, void *pos)
{
    float buf[16];
    SdrpVec4 *p = (SdrpVec4 *)obj->dobj->root.pos;
    CopyVector(p, pos);
    p->f[1] = p->f[1] - *(float *)((char *)p + 0xC0);
    p->f[3] = 1.0f;
    {
        Sub15C *sub = obj->dobj;
        GObj *q = *(GObj **)sub;
        if (q != 0) {
            MatrixDrive_SetTransposeMatrix(buf,
                                           (float *)(q->dobj->nodeMtx + (sub->parentNode << 6)));
            sceVu0ApplyMatrix(p, buf, p);
        }
    }
}

void SetDirectRootPosition(GObj *self, void *v)
{
    Sub15C *sub = self->dobj;
    float *p = sub->root.pos;
    float pos[4];
    float tmp[4];

    CopyVector(pos, v);
    CopyVector(tmp, p);
    SetRootPosition_i(self, pos);
    CopyVector(sub->root.last, p);
    CopyVector(sub->root.savePos, p);
    self->dobj->ctrl.posReserve = 0;
    CopyVector(sub->root.clipFrom, v);
    CopyVector(sub->root.move, ZeroVector);
    CopyVector(sub->root.delta, ZeroVector);
    AdjustMotionHeightToNearestField(self);
}

void SetDirectRootPositionNoFitting(GObj *self, void *v)
{
    Sub15C *sub = self->dobj;
    float *p = sub->root.pos;
    float pos[4];
    float tmp[4];

    CopyVector(pos, v);
    CopyVector(tmp, p);
    SetRootPosition_i(self, pos);
    CopyVector(sub->root.last, p);
    CopyVector(sub->root.savePos, p);
    self->dobj->ctrl.posReserve = 0;
    CopyVector(sub->root.clipFrom, v);
    CopyVector(sub->root.move, ZeroVector);
    CopyVector(sub->root.delta, ZeroVector);
}

/* The root position at (char *)sub+0xA0 is a 4-lane vector the engine also moves as
 * two quadwords (CopyVector); the union is the TU's view of it. */

void SetRootPosition(GObj *obj, void *pos)
{
    float buf[16];
    Vec4 *p = (Vec4 *)obj->dobj->root.pos;
    CopyVector(p, pos);
    p->f[1] = p->f[1] - *(float *)((char *)p + 0xC0);
    p->f[3] = 1.0f;
    {
        Sub15C *sub = obj->dobj;
        GObj *q = *(GObj **)sub;
        if (q != 0) {
            MatrixDrive_SetTransposeMatrix(buf,
                                           (float *)(q->dobj->nodeMtx + (sub->parentNode << 6)));
            sceVu0ApplyMatrix(p, buf, p);
        }
    }
}

void GetRootPosition(void *dst, GObj *obj)
{
    float *pos = dst;
    Sub15C *src = obj->dobj;
    struct MotRoot *root = &src->root;
    float f0;
    GObj *g = *(GObj **)src;
    if (g) {
        sceVu0ApplyMatrix(pos, (char *)g->dobj->nodeMtx + (src->parentNode << 6), root->pos);
    } else {
        CopyVector(pos, root->pos);
    }
    f0 = root->height;
    pos[1] += f0;
    pos[3] = 1.0f;
}

void GetRootOrient(char *a0, GObj *a1)
{
    char buf[64];
    Sub15C *sub = GOBJ_SUB(a1);
    struct MotRoot *root = &sub->root;
    GetMatrixFromQuaternionPos(buf, root->quat, root->pos);
    {
        char *q = *(char **)sub;
        if (q != 0) {
            sceVu0MulMatrix(buf, (char *)(GOBJ_SUB(q)->nodeMtx + (sub->parentNode << 6)), buf);
        }
    }
    *(float *)(buf + 0x34) = *(float *)(buf + 0x34) + root->height;
    sceVu0ApplyMatrix((int *)a0, buf, ZUnitVector);
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

void GetRootMatrixTransOffsetByDObj(float *dst, char *src)
{
    char tmp[64];
    MatrixDrive_SetTransposeMatrix(tmp, src + 0x20);
    sceVu0MulMatrix(tmp, tmp, *(int *)(src + 0xC));
    CopyVector(dst, (tmp + 0x30));
}

void GetRootMatrixTransOffset(float *dst, GObj *src)
{
    char tmp[64];
    Sub15C *p = GOBJ_SUB(src);
    MatrixDrive_SetTransposeMatrix(tmp, (char *)p + 0x20);
    sceVu0MulMatrix(tmp, tmp, p->nodeMtx);
    CopyVector(dst, (tmp + 0x30));
}

void GetRootMotionOrient(char *a0, GObj *a1)
{
    char m[64];
    char buf[64];
    char *b = buf;
    Sub15C *sub = GOBJ_SUB(a1);
    struct MotRoot *root = &sub->root;
    GetMatrixFromQuaternionPos(b, root->quat, root->pos);
    {
        char *q = *(char **)sub;
        if (q != 0) {
            sceVu0MulMatrix(b, (char *)(GOBJ_SUB(q)->nodeMtx + (sub->parentNode << 6)), b);
        }
    }
    *(float *)(b + 0x34) = *(float *)(b + 0x34) + root->height;
    GetMatrixFromQuaternion(m, GOBJ_SUB(a1)->root.motionQuat);
    sceVu0MulMatrix(m, b, m);
    sceVu0ApplyMatrix((int *)a0, m, ZUnitVector);
}

void GetRootMotionMatrix(char *a0, GObj *a1)
{
    char buf[64];
    Sub15C *sub = GOBJ_SUB(a1);
    struct MotRoot *root = &sub->root;
    GetMatrixFromQuaternionPos(buf, root->quat, root->pos);
    {
        char *q = *(char **)sub;
        if (q != 0) {
            sceVu0MulMatrix(buf, (char *)(GOBJ_SUB(q)->nodeMtx + (sub->parentNode << 6)), buf);
        }
    }
    *(float *)(buf + 0x34) = *(float *)(buf + 0x34) + root->height;
    GetMatrixFromQuaternion(a0, GOBJ_SUB(a1)->root.motionQuat);
    sceVu0MulMatrix(a0, buf, a0);
}

void GetProjectionPosOfPlane(void *a0, void *a1, void *a2)
{
    float buf[4];
    float dot;
    dot = plane_distance(a2, a1);
    _ScaleVectorXYZ(buf, a1, -dot);
    AddVectorXYZ(a0, a2, buf);
    *(float *)((char *)a0 + 0xC) = 1.0f;
}

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

GObj **GetCharGObjList(void)
{
    return charGObjList;
}

void getInitialInverseMatrix(char *mat, char *mdl, int no)
{
    SkelNode *nd = (SkelNode *)(*(char **)(mdl + 0x8C) + (no << 6));
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(nd->pos);
    MultiMatrixByQuaternion(nd->quat);
    MatrixDrive_SetTransposeMatrix(mat + (no << 6), MatrixDrive_GetMatrix());
    if (nd->child != -1) {
        getInitialInverseMatrix(mat, mdl, nd->child);
    }
    MatrixDrive_PopMatrix();
    if (nd->sibling != -1) {
        getInitialInverseMatrix(mat, mdl, nd->sibling);
    }
}

void getInitialMatrix(char *mdl, int no)
{
    SkelNode *nd = (SkelNode *)(*(char **)(mdl + 0x8C) + (no << 6));
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(nd->pos);
    MultiMatrixByQuaternion(nd->quat);
    CopyMatrix(*(char **)(mdl + 0xC) + (no << 6), MatrixDrive_GetMatrix());
    if (nd->child != -1) {
        getInitialMatrix(mdl, nd->child);
    }
    MatrixDrive_PopMatrix();
    if (nd->sibling != -1) {
        getInitialMatrix(mdl, nd->sibling);
    }
}
