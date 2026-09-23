#include "common.h"
#include "box.h"
#include "sugiCommon.h"
#include "switch.c.inc"
#include "DObj.h"
#include "debug.h"
#include "gamesys.h"
#include "generator.h"
#include "frameDependSequence.h"
#include "item.h"
#include "motionManager2.h"
#include "motionOrientManager.h"
#include "tableSin.h"
#include <libvu0.h>
#include <string.h>

void landingSE(int a0)
{
    ExecuteSEPackage(a0, 0x2);
}

void fallDownStartSE(int a0)
{
    ExecuteSEPackage(a0, 0x24);
}

void pushStartSE(int a0)
{
    ExecuteSEPackage(a0, 0x4);
}

void pullStartSE(int a0)
{
    ExecuteSEPackage(a0, 0xD);
}

void wallHitSE(int a0)
{
    ExecuteSEPackage(a0, 0x1E);
}

/* kept local: this TU's uses of StopSEPackage and StopSEPackageWithGroupVariation
   do not fit the prototypes in frameDependSequence.h */
extern void StopSEPackage(int a0);
extern void StopSEPackageWithGroupVariation(int a0, int a1);

/* box.c:232-241 in the listing: inlined into onPath and into
   ExecBoxMoveEndReaction, so it is a static inline here; it has no symbol of
   its own in the ROM and no census row, and the name is descriptive. */
static inline void stopBoxMoveSE(char *self)
{
    char *q = *(char **)((char *)GOBJ_SUB(self) + 0x830);

    StopSEPackage((int)self);
    StopSEPackageWithGroupVariation((int)self, 1);

    ExecuteSEPackage((int)self, 0x16);
    if (*(int *)(q + 0x140) != 0) {
        wallHitSE((int)self);
        *(int *)(q + 0x140) = 0;
    }
}

void initFallDown(char *a0)
{
    float pos[4];
    float pts[16];
    float n[4];
    char *p = (char *)GOBJ_SUB(a0)->f_830;

    GetRootPosition(pos, a0);
    GOBJ_SUB(a0)->f_78 = 0;
    *(int *)&GOBJ_SUB(a0)->f_4AC = 0;
    if (*(char **)(p + 0x68) != 0) {
        GetWallGlobalInfo((char *)pts, n, *(char **)(p + 0x68),
                          (char *)GOBJ_SUB(*(char **)(p + 0x60))->f_C + (*(int *)(p + 0x64) << 6));
        n[1] = 0.0f;
        sceVu0Normalize(n, n);
        SetIdentityQuaternion((char *)GOBJ_SUB(a0) + 0xC0);
        RotQuaternionY((char *)GOBJ_SUB(a0) + 0xC0, GetTableArcTan2(n[0], n[2]));
        GetRootQuaternion((int)((char *)GOBJ_SUB(a0) + 0xE0), (int)a0);
        DivQuaternion((int)((char *)GOBJ_SUB(a0) + 0xE0), (int)((char *)GOBJ_SUB(a0) + 0xE0),
                      (int)((char *)GOBJ_SUB(a0) + 0xC0));
        GetMatrixFromQuaternionPos(p + 0x70, (char *)GOBJ_SUB(a0) + 0xC0, (char *)pos);
        GOBJ_SUB(a0)->f_4A0 = 1143;
    } else {
        GOBJ_SUB(a0)->f_4A0 = 1143;
        GetRootQuaternion((int)((char *)GOBJ_SUB(a0) + 0xC0), (int)a0);
    }
}

/* kept local: this TU does not include matrixDrive.h, whose FSqrt and
   AddVectorXYZ prototypes do not fit this TU's uses of them. */
extern void CopyVector(void *dst, void *src);
extern void GetLowerPlaneCollision(void *work, void *pos);
extern int GetFloorAttribute(void *work);

int checkFieldContact(char *a0, float lim)
{
    char w[0xC0];
    float pos[4];
    float v[4];
    int r;

    GetRootPosition(pos, a0);
    CopyVector(v, pos);
    v[1] -= GOBJ_SUB(a0)->f_134;
    GetLowerPlaneCollision(w, v);
    r = CheckFieldContact(w, a0, pos, lim);
    if (*(int *)GOBJ_SUB(a0) != 0) {
        UnlinkParentOfDObj(a0);
    }
    *(int *)((char *)GOBJ_SUB(a0) + 0x5F8) = 0;
    switch (r) {
    case 1:
        if (a0 != *(char **)(w + 0x8C)) {
            if (*(char **)GOBJ_SUB(a0) != *(char **)(w + 0x8C) ||
                *(int *)((char *)GOBJ_SUB(a0) + 4) != *(int *)(w + 0x90)) {
                LinkParentOfDObj(a0, (PackedLL_19CAF0 *)(w + 0x8C));
                *(int *)((char *)GOBJ_SUB(a0) + 0x5F8) = GetFloorAttribute(w);
            }
        }
        *(float *)(w + 0x14) = *(float *)(w + 0x24) - 50.0f;
        SetDirectRootPosition(a0, w + 0x10);
        return 1;
    case 2:
        *(int *)((char *)GOBJ_SUB(a0) + 0x5F8) = GetFloorAttribute(w);
        return 2;
    }
    return 0;
}

/* kept local: this TU's uses of SetDirectRootPosition do not fit the prototype in geometryManager.h */
extern void SetDirectRootPosition(void *obj, void *pos);
/* kept local: this TU's uses of _ScaleVector do not fit the prototype in Matrix.h */
extern void _ScaleVector(void *dst, void *src, float k);
/* kept local: this TU's uses of AddVectorXYZ do not fit the prototype in matrixDrive.h */
extern void AddVectorXYZ(void *dst, void *a, void *b);
/* kept local: this TU's uses of ClipWallBoxStop do not fit the prototype in fieldCollision.h */
extern void ClipWallBoxStop(void *a0);
/* kept local: this TU's uses of _AddVector do not fit the prototype in Matrix.h */
extern void _AddVector(void *dst, void *a, void *b);
/* kept local: this TU's uses of _NormalizeVector do not fit the prototype in Matrix.h */
extern void _NormalizeVector(void *dst, void *src);
/* kept local: this TU's uses of ClipWall do not fit the prototype in fieldCollision.h */
extern void ClipWall(void *a0);
/* kept local: this TU does not include geometryManager.h, whose GetRootMatrix and
   GetCharGObjList prototypes do not fit this TU's uses of them. */
extern void SetRootPosition(void *obj, void *pos);

/* box.c:343-360 in the listing: inlined into execNormalMove twice (once with
   ClipWall, once with ClipWallBoxStop) and into inertiaMove once, so it is a
   static inline here; it has no symbol of its own in the ROM and no census
   row, and the name is descriptive.  The two constant arguments fold, which is
   why each inlining carries only one of the two clip calls.  The work buffer
   and the root-position scratch are the CALLER's: the ROM's frames place them
   among the caller's own locals, and execNormalMove's two expansions get two
   separate work buffers while sharing one output vector. */
static inline void checkBoxWallHit(char *self, char *w, float *base, float *out, int stop)
{
    char *p = (char *)GOBJ_SUB(self)->f_830;

    GetRootPosition(base, self);
    if (out != 0) {
        CopyVector(out, base);
    }
    *(float *)(w + 0x70) = (*(float *)(p + 0x24) < *(float *)(p + 0x28) ? *(float *)(p + 0x24)
                                                                        : *(float *)(p + 0x28)) *
                               50.0f -
                           5.0f;
    base[1] += 40.0f;
    CopyVector(w, base);
    CopyVector(w + 0x10, base);
    if (stop != 0) {
        ClipWallBoxStop(w);
    } else {
        ClipWall(w);
    }
    *(float *)(w + 0x24) -= 40.0f;
}

/* kept local: this TU's uses of these do not fit the prototypes in the headers
   that declare them */
extern void iosOmSendMail(int dst, int mail, void *arg);
extern void GetProjectionPosOfPlane(void *dst, void *plane, void *pos);
extern void CopyQuaternion(void *dst, void *src);
extern void _OuterProduct(void *dst, void *a, void *b);
extern void SetQuaternionByAxisRotateV(void *dst, int ang, void *axis);
extern void GetSlerpQuaternion(void *dst, void *a, void *b, float t);
extern void GetInverseQuaternion(void *dst, void *src);
extern void MultiQuaternion(void *dst, void *a, void *b);
extern void SetRootQuaternion(void *obj, void *q);
/* kept local: this TU's uses of IdentityQuaternion and YUnitVector do not fit
   the prototypes in quaternion.h and matrixDrive.h */
extern char IdentityQuaternion[];
extern char YUnitVector[];
/* the two debug lines the wall fit prints, rodata VMA 0x61EF20 and 0x61EF48;
   the second is EUC-JP, "this terrain is wrong (it is not cut to 100cm)" */
extern char D_0061EF20[];
extern char D_0061EF48[];

/* the record the clip work reports at +0x80: the contact point's x and z, and
   the hit flag the caller has just tested at +0x88.  The point and the flag
   are separate members and the staging copy fills them with two assignments,
   which is why the ROM emits the point's ldl/ldr/sdl/sdr as a block move of
   its own and the flag's lw/sw after it; the read back is one assignment of
   the whole record and comes out as a single twelve-byte move. */
typedef struct {
    float x;
    float z;
} BoxWallPt;

typedef struct {
    BoxWallPt pt;
    int hit;
} BoxWallRec;

/* box.c:362-457 in the listing. */
int execNormalMove(char *self, int stop)
{
    char stopWork[0xC0];
    float pos[4];
    char work[0xC0];
    float wn[4];
    BoxWallRec wn2;
    float plTop[4];
    float plSide[4];
    float up[4];
    float proj[4];
    float axis[4];
    float norm[4];
    float rot[4];
    char *p = (char *)GOBJ_SUB(self)->f_830;
    int ret = 1;
    float hw;
    float d;
    float dy;
    float adj;
    int ang;

    if (stop != 0) {
        checkBoxWallHit(self, stopWork, pos, 0, 1);
        if (*(int *)(stopWork + 0x88) != 0) {
            ret = 0;
            SetDirectRootPosition(self, stopWork + 0x20);
        }
    }

    if (checkFieldContact(self, 110.0f) != 1) {
        if (*(int *)(p + 4) != 0) {
            iosOmSendMail(*(int *)(p + 4), 25, self);
            *(int *)(p + 4) = 0;
        }
        initFallDown(self);
        fallDownStartSE(self);
        *(int *)(p + 0x20) = 2;
    } else {
        if (stop == 0) {
            checkBoxWallHit(self, work, wn, pos, 0);
            if (*(int *)(work + 0x88) != 0) {
                wn2.pt = *(BoxWallPt *)(work + 0x80);
                wn2.hit = *(int *)(work + 0x88);
                *(BoxWallRec *)wn = wn2;

                hw = (*(float *)(p + 0x24) < *(float *)(p + 0x28) ? *(float *)(p + 0x24)
                                                                  : *(float *)(p + 0x28)) *
                     50.0f;

                CopyVector(up, pos);
                up[1] += 50.0f;
                GetPureVerticalPlane(plTop, plSide, 0, (int *)wn, 0);

                d = plane_distance(up, plSide);

                if (hw - 10.0f < d) {
                    CopyQuaternion(p + 0x150, IdentityQuaternion);
                } else {
                    GetProjectionPosOfPlane(proj, plSide, up);
                    GetProjectionPosOfPlane(proj, plTop, proj);

                    dy = up[1] - proj[1];
                    if (dy < 60.0f) {
                        adj = dy * (1.0f - d / hw);
                        pos[1] = pos[1] - adj;
                        SetDirectRootPosition(self, pos);

                        axis[0] = 0.0f;
                        axis[1] = dy;
                        axis[2] = d + hw;
                        axis[3] = 0.0f;

                        _NormalizeVector(axis, axis);
                        _OuterProduct(norm, YUnitVector, plSide);
                        ang = GetTableArcTan2(axis[0], axis[2]);
                        SetQuaternionByAxisRotateV(rot, ang, norm);
                        debug_StdPrintfDummy(D_0061EF20, dy, d, adj, ang);

                        GetSlerpQuaternion(p + 0x150, rot, p + 0x150, 0.5f);
                    } else {
                        debug_StdPrintfDummy(D_0061EF48);
                        GetSlerpQuaternion(p + 0x150, IdentityQuaternion, p + 0x150, 0.5f);
                    }
                }
            } else {
                GetSlerpQuaternion(p + 0x150, IdentityQuaternion, p + 0x150, 0.5f);
            }
            GetInverseQuaternion(axis, (char *)GOBJ_SUB(self) + 0x60);
            MultiQuaternion(proj, axis, p + 0x150);
            SetRootQuaternion(self, proj);
        } else {
            SetIdentityQuaternion(p + 0x150);
        }
    }

    return ret;
}

/* box.c:461-478 in the listing: inlined once, into execAutoMove, so it has no
   symbol of its own in the ROM and no census row; the name is descriptive. */
static inline void setBoxStopWallFlag(char *self, float *vel)
{
    char w[0xC0];
    float dir[4];
    char *p = (char *)GOBJ_SUB(self)->f_830;

    memset(w, 0, 0xC0);
    _NormalizeVector(dir, vel);
    _ScaleVector(dir, dir,
                 (*(float *)(p + 0x24) < *(float *)(p + 0x28) ? *(float *)(p + 0x24)
                                                              : *(float *)(p + 0x28)) *
                         50.0f +
                     25.0f);
    GetRootPosition(w, self);
    AddVectorXYZ(w + 0x10, w, dir);
    ClipWallBoxStop(w);
    if (*(int *)(w + 0x88) != 0) {
        *(int *)(p + 0x140) = 1;
    } else {
        *(int *)(p + 0x140) = 0;
    }
}

int execAutoMove(char *a0)
{
    float pos[4];
    char *p = (char *)GOBJ_SUB(a0)->f_830;

    GetRootPosition(pos, a0);
    _AddVector(pos, pos, p + 0x40);
    SetDirectRootPosition(a0, pos);
    execNormalMove(a0, 0);
    setBoxStopWallFlag(a0, (float *)(p + 0x40));
    if (--*(int *)(p + 0x30) <= 0) {
        *(int *)(p + 0x20) = 0;
    }
    return 1;
}

static inline float getAlign(float v, float g)
{
    if (0.0f <= v) {
        return (float)(int)((v + g * 0.5f) / g) * g;
    }
    return -getAlign(-v, g);
}

static inline void alignPosition(char *self, float *dst, float *src, float grid)
{
    float npos[4];
    char *n = (char *)(int)GOBJ_SUB(self);
    float cx = *(float *)(n + 0x50);
    float cz = *(float *)(n + 0x58);

    CopyVector(npos, src);
    npos[0] = getAlign(src[0] - cx, grid) + cx;
    npos[2] = getAlign(src[2] - cz, grid) + cz;

    CopyVector(dst, npos);
}

int AlignBox(char *a0, float grid)
{
    float pos[4];
    float quat[4];
    Sub15C *sub = GOBJ_SUB(a0);
    char *q = *(char **)((char *)sub + 0x830);

    GetInverseQuaternion(quat, (char *)sub + 0x60);
    SetRootQuaternion(a0, quat);
    GetRootPosition(pos, a0);
    alignPosition(a0, pos, pos, grid);
    SetDirectRootPosition(a0, pos);
    *(int *)(q + 0x20) = 0;
    return 0;
}

/* declared here: box.c includes no header that declares the ios allocators
   (ico2/fumi/include/memory.h has them with an IosMemPart * partition) */
extern void *iosMallocDebug(void *part, int size, char *file, int line);
extern void iosFree(void *p);
/* the heap partition the wheel buffers come from and the "src/box.c" file
   string the debug allocator records, both read by VMA: D_0063A44C is the
   gp-relative partition handle, D_0061EF80 is at rodata VMA 0x61EF80 */
extern void *D_0063A44C;
extern char D_0061EF80[];
extern GenGeo D_002C2DC8[];

/* box.c:546-565 in the listing.  Lines 558 to 560 are one call-site line in
   the listing, the same DObj-buffer setup ico2/omori/src/chain.c expands by
   hand at its own line 1245 (InitChainGeo, matched): the wheel count is 2
   here, so the three allocation sizes are 2<<6, 2<<4 and 2*80 bytes and the
   560 the allocator records is the dev source line. */
void initWheels(char *self, float *lay)
{
    char *w = (char *)GOBJ_SUB(self)->f_830;
    int i;

    if (D_002C2DC8[((int *)self)[2]].f30 == 26 ||
        D_002A79B8[*(int *)((char *)GOBJ_SUB(self) + 0x844)].dobj0 == 0x610) {
        *(int *)(w + 0x11C) = 0;
    } else {
        *(char **)(w + 0x11C) =
            CSVSYSTEM_InitDObj(D_002A79B8[*(int *)((char *)GOBJ_SUB(self) + 0x844)].dobj0, lay);
        if (*(int *)(*(char **)(w + 0x11C) + 0xC) != 0) {
            iosFree((void *)(*(int *)(*(char **)(w + 0x11C) + 0xC) & 0x0FFFFFFF));
        }
        if (*(int *)(*(char **)(w + 0x11C) + 0x10) != 0) {
            iosFree((void *)(*(int *)(*(char **)(w + 0x11C) + 0x10) & 0x0FFFFFFF));
        }
        *(int *)(*(char **)(w + 0x11C) + 0xC) = 0;
        *(int *)(*(char **)(w + 0x11C) + 0x10) = 0;
        *(int *)(*(char **)(w + 0x11C) + 0xC) =
            (int)iosMallocDebug(D_0063A44C, 128, D_0061EF80, 560);
        *(int *)(*(char **)(w + 0x11C) + 0x10) =
            (int)iosMallocDebug(D_0063A44C, 32, D_0061EF80, 560);
        *(int *)(*(char **)(w + 0x11C) + 0x8) = 2;
        if (*(int *)(*(char **)(w + 0x11C) + 0x870) != 0) {
            iosFree((void *)(*(int *)(*(char **)(w + 0x11C) + 0x870) & 0x0FFFFFFF));
        }
        *(int *)(*(char **)(w + 0x11C) + 0x870) =
            (int)iosMallocDebug(D_0063A44C, 160, D_0061EF80, 560);

        for (i = 0; i < 2; i++) {
            {
                char *e = (char *)(i * 80 + (int)*(char **)(*(char **)(w + 0x11C) + 0x870));
                ((DlFlag *)(e + 0x38))->ll &= ~1;
            }
            {
                char *e = (char *)(i * 80 + (int)*(char **)(*(char **)(w + 0x11C) + 0x870));
                ((DlFlag *)(e + 0x38))->ll &= ~2;
            }
            {
                char *e = (char *)(i * 80 + (int)*(char **)(*(char **)(w + 0x11C) + 0x870));
                *(float *)(e + 0x40) = 0.0f;
            }
            {
                char *e = (char *)(i * 80 + (int)*(char **)(*(char **)(w + 0x11C) + 0x870));
                *(float *)(e + 0x44) = 0.0f;
            }
            {
                char *e = (char *)(i * 80 + (int)*(char **)(*(char **)(w + 0x11C) + 0x870));
                *(float *)(e + 0x48) = 0.0f;
            }
            {
                char *e = (char *)(i * 80 + (int)*(char **)(*(char **)(w + 0x11C) + 0x870));
                *(float *)(e + 0x4C) = 1.0f;
            }
            {
                char *e = (char *)(i * 80 + (int)*(char **)(*(char **)(w + 0x11C) + 0x870));
                ((DlFlag *)(e + 0x38))->ll &= ~4;
            }
            {
                char *e = (char *)(i * 80 + (int)*(char **)(*(char **)(w + 0x11C) + 0x870));
                *(int *)(e + 0x30) = 0;
            }
            {
                char *e = (char *)(i * 80 + (int)*(char **)(*(char **)(w + 0x11C) + 0x870));
                *(float *)(e + 0x34) = 1.0f;
            }
            {
                char *e = (char *)(i * 80 + (int)*(char **)(*(char **)(w + 0x11C) + 0x870));
                *(short *)(e + 0x3A) = 0;
            }
            {
                char *e = (char *)(i * 80 + (int)*(char **)(*(char **)(w + 0x11C) + 0x870));
                *(float *)(e + 0x20) = 1.0f;
            }
            {
                char *e = (char *)(i * 80 + (int)*(char **)(*(char **)(w + 0x11C) + 0x870));
                *(float *)(e + 0x24) = 1.0f;
            }
            {
                char *e = (char *)(i * 80 + (int)*(char **)(*(char **)(w + 0x11C) + 0x870));
                *(float *)(e + 0x28) = 1.0f;
            }
        }
        *(short *)(*(char **)(w + 0x11C) + 0x84C) = 2;

        /* the sub-object handle at 0x15C read through the TU's IntFloat union
           (alias set 0), as the wheel-float stores are: the ROM keeps the first
           handle load behind the 0x84C store above, which a plain int read,
           free to move past a short store, does not give */
        ((IntFloat *)(w + 0x128))->f =
            D_002A79B8[*(int *)(((IntFloat *)(self + 0x15C))->i + 0x844)].f0C;
        ((IntFloat *)(w + 0x12C))->f =
            D_002A79B8[*(int *)(((IntFloat *)(self + 0x15C))->i + 0x844)].f10;
        ((IntFloat *)(w + 0x130))->f =
            D_002A79B8[*(int *)(((IntFloat *)(self + 0x15C))->i + 0x844)].f14;
    }
}

/* box.c:567-572 in the listing: inlined once, into action's case 0, so it is a
   static inline here; it has no symbol of its own in the ROM and no census row,
   and the name is descriptive.  10430.3779f is 65536 / (2 * pi), the repo's
   spelling of the radian-to-angle-table factor (ico2/seki/src/Primitive.c). */
static inline void updateBoxWheelAngle(char *self)
{
    char *p = (char *)GOBJ_SUB(self)->f_830;

    if (*(int *)(p + 0x11C) != 0) {
        *(short *)(p + 0x120) = (short)((float)*(short *)(p + 0x120) -
                                        *(float *)(p + 0x48) * 10430.3779f / *(float *)(p + 0x124));
    }
}

void dispWheels(char *a0)
{
    char *p = (char *)GOBJ_SUB(a0)->f_830;

    if (*(char **)(p + 0x11C) == 0) {
        return;
    }
    CopyMatrix(MatrixDrive_GetMatrix(), *(void **)&GOBJ_SUB(a0)->f_C);
    MatrixDrive_TransMatrix(0.0f, *(float *)(p + 0x128), 0.0f);
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrix(0.0f, 0.0f, *(float *)(p + 0x12C));
    MatrixDrive_RotMatrixX(*(short *)(p + 0x120));
    CopyMatrix(*(void **)(*(char **)(p + 0x11C) + 0xC), MatrixDrive_GetMatrix());
    MatrixDrive_PopMatrix();
    MatrixDrive_TransMatrix(0.0f, 0.0f, *(float *)(p + 0x130));
    MatrixDrive_RotMatrixX((short)(*(unsigned short *)(p + 0x120) + 0x4000));
    CopyMatrix((char *)*(void **)(*(char **)(p + 0x11C) + 0xC) + 0x40, MatrixDrive_GetMatrix());
    p2o_DispVU1DObjMulti(*(void **)(p + 0x11C));
}

/* the per-route point arrays (a pointer table in the TU's .data at VMA
   0x4E5F30) and the Y axis the side plane is built from (VMA 0x4E61D0,
   { 0.0f, 1.0f, 0.0f, 0.0f }) */
extern float *D_004E5F30[];
extern float D_004E61D0[];
/* the largest float, 0x7F7FFFFF, in the TU's .sdata at VMA 0x63B738; the
   declaration withholds its size so the load keeps the ROM's %hi/%lo */
extern float D_0063B738[];

/* one 16-byte route point */
typedef float PathPt[4];

/* box.c:603-672 in the listing.  The signed plane distance is what the
   projection is scaled by and its magnitude is what the nearest test keeps,
   which is why the ROM copies the value into the argument register before it
   negates it.  0.707 is the ROM's spelling of the 45 degree axis test. */
int getNearestPosition(float *out, int *pidx, int *path)
{
    float pos[4];
    float seg[4];
    float dir[4];
    float proj[4];
    float pl[4];
    float foot[4];
    PathPt *pts = (PathPt *)D_004E5F30[path[0]];
    float best = D_0063B738[0];
    int bi = -1;
    int start;
    int end;
    int i;
    float dist;
    float ad;
    float t;

    if (*pidx != -1) {
        start = *pidx - 1;
        start = 0 < start ? start : 1;
        end = *pidx + 2;
        end = path[1] < end ? path[1] : end;
    } else {
        start = 0;
        end = path[1] - 1;
    }

    for (i = start; i < end; i++) {
        sceVu0SubVector(seg, pts[i], pts[i - 1]);
        seg[1] = 0.0f;
        sceVu0Normalize(dir, seg);
        sceVu0OuterProduct(pl, D_004E61D0, dir);
        pl[1] = 0.0f;
        sceVu0Normalize(pl, pl);
        pl[3] = -(pl[0] * pts[i][0] + pl[2] * pts[i][2]);
        dist = pl[0] * out[0] + pl[2] * out[2] + pl[3];
        ad = dist < 0.0f ? -dist : dist;
        pl[1] = 0.0f;
        pl[3] = 0.0f;
        sceVu0ScaleVector(proj, pl, dist);
        SubVectorXYZ(foot, out, proj);

        if (0.707f < (dir[0] < 0.0f ? -dir[0] : dir[0])) {
            t = (foot[0] - pts[i - 1][0]) / seg[0];
        } else {
            t = (foot[2] - pts[i - 1][2]) / seg[2];
        }
        if (0.0f <= t && t <= 1.0f) {
            CopyVector(out, foot);
            *pidx = i;
            return 0;
        }
        if (ad < best) {
            best = ad;
            bi = i;
            if (t < 0.0f) {
                CopyVector(pos, pts[i - 1]);
            } else {
                CopyVector(pos, pts[i]);
            }
        }
    }
    out[0] = pos[0];
    out[2] = pos[2];
    out[3] = 1.0f;

    *pidx = bi;
    return 1;
}

extern char D_0061EF90[];
extern char D_0061EFA8[];

void onPathInitialize(char *a0)
{
    float front[4];
    float rear[4];
    char *p = (char *)GOBJ_SUB(a0)->f_830;
    /* one offset variable for both wheels: the ROM loads 50.0f and -50.0f
       into the same register, each on its own vector's line */
    float ofs;
    Vec16 fv = {{0.0f, 0.0f, *(float *)(p + 0x28) * (ofs = 50.0f), 1.0f}};
    Vec16 rv = {{0.0f, 0.0f, *(float *)(p + 0x28) * (ofs = -50.0f), 1.0f}};
    float quat[4];

    *(int *)(p + 0x50) = *(int *)(p + 0x54) = -1;
    sceVu0ApplyMatrix(front, (void *)GOBJ_SUB(a0)->f_C, &fv);
    sceVu0ApplyMatrix(rear, (void *)GOBJ_SUB(a0)->f_C, &rv);
    getNearestPosition(front, (int *)(p + 0x50), (int *)(p + 0x58));
    getNearestPosition(rear, (int *)(p + 0x54), (int *)(p + 0x58));
    debug_StdPrintfDummy(D_0061EF90, front[0], front[1], front[2]);
    debug_StdPrintfDummy(D_0061EFA8, rear[0], rear[1], rear[2]);
    if (distance_squared(front, rear) < 0.010000001f) {
        GetRootQuaternion((int)quat, (int)a0);
        RotQuaternionY(quat, 16384);
        SetRootQuaternion(a0, quat);
        UpdateRootMatrix(a0);
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", onPath);

/* kept local: this TU's uses of FSqrt do not fit the prototype in matrixDrive.h */
extern float FSqrt(float f);

inline float GetDistanceOfGObj(void *a0, void *a1)
{
    char v[0x10];
    char w[0x10];
    GetRootPosition(v, a1);
    GetRootPosition(w, a0);
    sceVu0SubVector(v, v, w);
    return FSqrt(sceVu0InnerProduct(v, v));
}

extern int *D_004EB758[];
extern void GetFloatingMotion(void *mot, void *dir, int *m, int a3, int t0, int t1, float t);

int playAnimationCore(char *a0)
{
    float mot[4];
    float rot[4];
    float dir[4];
    float pos[4];
    float q[4];
    char *p = (char *)GOBJ_SUB(a0)->f_830;

    GetFloatingMotion(mot, dir, D_004EB758[GOBJ_SUB(a0)->f_4A0], 1, 0, 0, GOBJ_SUB(a0)->f_4AC);
    dir[3] = 1.0f;
    sceVu0ApplyMatrix(pos, p + 0x70, dir);
    CopyQuaternion(q, (char *)GOBJ_SUB(a0) + 0xC0);
    MultiQuaternion(q, q, rot);
    RotQuaternionX(q, -32768);
    RotQuaternionY(q, -16384);
    MultiQuaternion(q, q, (char *)GOBJ_SUB(a0) + 0xE0);
    SetRootQuaternion(a0, q);
    sceVu0SubVector(&GOBJ_SUB(a0)->f_130, pos, (char *)GOBJ_SUB(a0) + 0x1F0);
    CopyVector((char *)GOBJ_SUB(a0) + 0x1F0, pos);
    SetRootPosition(a0, pos);
    ExecFrameDependSequence(a0);
    return UpdateFrameCounter(a0);
}

extern int D_0028F4C0[];
/* kept local: this TU's uses of LimitExistGeometry do not fit the prototype in geometryManager.h */
extern int LimitExistGeometry(void *pos, void *vel);

/* box.c:867-877 in the listing: inlined once, into execFallDown's case 3, so it
   is a static inline here; it has no symbol of its own in the ROM and no census
   row, and the name is descriptive.  The frame-rate divisor is the one
   moveBoxAutoMatic uses, written twice and shared by cse. */
static inline void execBoxFall(char *self)
{
    float v[4];

    GetRootPosition(v, self);
    ((IntFloat *)(*(char **)(self + 0x15C) + 0x134))->f +=
        60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 0.5f *
        (60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
    AddVectorXYZ(v, v, *(char **)(self + 0x15C) + 0x130);
    SetRootPosition(self, v);
    if (LimitExistGeometry(v, *(char **)(self + 0x15C) + 0x130) != 0) {
        *(int *)((char *)GOBJ_SUB(self)->f_830 + 0x20) = -1;
    }
}

/* kept local: this TU's uses of _Sqrt do not fit the prototype in matrixDrive.h */
extern float _Sqrt(float f);
extern int GetCylinderCollisionWithExceptOwnCollision(char *self, int target, float r, float h,
                                                      float s, float t, int ctrl);
/* the local Z axis the floating box's facing is rebuilt from, VMA 0x4E6200,
   { 0.0f, 0.0f, 1.0f, 0.0f } */
extern float D_004E6200[];

/* box.c:882-951 in the listing.  0.31830987 is 1 / pi and the ROM keeps two
   copies of it, one per arm of the sign test, the way it keeps two copies of
   every other constant that appears once in each arm. */
int MoveFloatingBox(char *self, char *other, float *dst, void *src, float lim)
{
    float pos[4];
    float opos[4];
    float tp[4];
    float m[16];
    char *w = (char *)GOBJ_SUB(self)->f_830;
    float dx;
    float dz;
    float len;

    GetRootMatrix(m, self);
    _ApplyMatrix(tp, m, src);
    GetRootPosition(pos, self);
    GetRootPosition(opos, other);

    dx = dst[0] - tp[0];
    dz = dst[2] - tp[2];
    len = _Sqrt(dx * dx + dz * dz);

    if (lim < len) {
        float over = len - lim;
        float ox;
        float oz;
        float tx;
        float tz;
        float l1;
        float l2;
        float px;
        float pz;
        float ax;
        float az;
        float d;
        int ang;

        dx = dx * (over / len);
        dz = dz * (over / len);

        ox = tp[0] - pos[0];
        oz = tp[2] - pos[2];

        tx = ox + dx * 0.2f;
        tz = oz + dz * 0.2f;
        l2 = FSqrt(tx * tx + tz * tz);
        l1 = FSqrt(ox * ox + oz * oz);
        px = tx * l1 / l2;
        pz = tz * l1 / l2;

        pos[0] = pos[0] + (tx - px);
        pos[2] = pos[2] + (tz - pz);
        ax = px - ox;
        az = pz - oz;
        d = FSqrt(ax * ax + az * az) * 32768.0f;
        ang = (short)(ox * az - oz * ax < 0.0f ? d / l1 * 0.31830987f : -d / l1 * 0.31830987f);

        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        MatrixDrive_RotMatrixY(GetTableArcTan2(*(float *)((char *)GOBJ_SUB(self) + 0x520),
                                               *(float *)((char *)GOBJ_SUB(self) + 0x528)));
        MatrixDrive_RotMatrixY(ang);
        sceVu0ApplyMatrix((char *)GOBJ_SUB(self) + 0x520, MatrixDrive_GetMatrix(), D_004E6200);

        SetRootPosition(self, pos);

        opos[0] = opos[0] - dx * 0.05f;
        opos[2] = opos[2] - dz * 0.05f;
        SetRootPosition(other, opos);
    }

    GetCylinderCollisionWithExceptOwnCollision(self, (int)other, 70.0f, 50.0f, 0.5f, 0.5f, 0);

    *(int *)(w + 0x164) = 1;
    return 1;
}

/* kept local: this TU's uses of _AddVectorXYZ do not fit the prototype in Matrix.h */
extern void _AddVectorXYZ(void *dst, void *a, void *b);
/* kept local: this TU's uses of _SubVector do not fit the prototype in Matrix.h */
extern void _SubVector(void *dst, void *a, void *b);
/* kept local: this TU's uses of _ScaleVectorXYZ do not fit the prototype in Matrix.h */
extern void _ScaleVectorXYZ(void *dst, void *src, float k);
/* kept local: this TU's uses of these do not fit the prototypes in Matrix.h,
   matrixDrive.h and quaternion.h */
extern void _SubVectorXYZ(void *dst, void *a, void *b);
extern float VectorLength(void *v);
extern float VectorLengthSquare(void *v);
extern void GetMatrixFromQuaternionPos(void *m, void *q, void *pos);
/* the eight horizontal push-out directions the floating box is tested along,
   VMA 0x4E6210, eight vectors */
extern float D_004E6210[];

/* box.c:965-988 in the listing: inlined once, into execFloating, so it is a
   static inline here; it has no symbol of its own in the ROM and no census
   row, and the name is descriptive.  The clip work, the matrix and the two
   scratch vectors are the CALLER's: the ROM's frame places them among
   execFloating's own locals, ahead of the word whose address goes to
   GetWaterReaction. */
static inline void pushOutFloatingBox(char *cw, float *m, float *sv, float *dv, float *pos,
                                      float *q, float r)
{
    float *dir;
    float len;
    int i;

    memset(cw, 0, 0xC0);
    /* the counter is only read by the test, so loop.c reverses it: the ROM
       counts down from 7 while the direction pointer still walks up. */
    for (i = 0, dir = D_004E6210; i < 8; i++, dir += 4) {
        CopyVector(cw, pos);
        GetMatrixFromQuaternionPos(m, q, pos);
        _ScaleVectorXYZ(sv, dir, r);
        _ApplyMatrix(cw + 0x10, m, sv);
        ClipWall(cw);
        if (*(int *)(cw + 0x88) != 0) {
            _SubVectorXYZ(dv, cw + 0x20, cw + 0x10);
            len = VectorLengthSquare(dv);
            if (1.0f < len) {
                _ScaleVector(dv, dv, 1.0f / _Sqrt(len));
            }
            _AddVectorXYZ(pos, pos, dv);
        }
    }
}

/* kept local: this TU's uses of ClipWallE do not fit the prototype in fieldCollision.h */
extern void ClipWallE(void *a0);

void avoidCharGObj(char *a0, char *a1)
{
    char w[0xC0];
    float pos[4];
    int hit;

    *(float *)(w + 0x70) = (30.0f < *(float *)((char *)GOBJ_SUB(a1) + 0x3D8))
                               ? *(float *)((char *)GOBJ_SUB(a1) + 0x3D8)
                               : 30.0f;
    GetRootPosition(pos, a1);
    pos[1] += *(float *)((char *)GOBJ_SUB(a1) + 0x270) + 10.0f;
    CopyVector(w, pos);
    CopyVector(w + 0x10, pos);
    *(char **)(w + 0x74) = a0;
    *(int *)(w + 0x78) = -1;
    *(int *)(w + 0x7C) = 0;
    ClipWallE(w);
    if (*(int *)(w + 0x88) != 0) {
        switch (*(int *)((char *)GOBJ_SUB(a1) + 0x4D8)) {
        case 7:
        case 8:
        case 10:
        case 15:
        case 16:
            hit = *(char **)((char *)GOBJ_SUB(a1) + 0x180) == a0;
            break;
        default:
            hit = 1;
            break;
        }
        if (hit != 0) {
            GetCylinderCollisionWithExceptOwnCollision(
                a0, (int)a1, (*(float *)(w + 0x70) + 50.0f) * 1.414f, 100.0f, 0.5f, 0.0f, 1);
            UpdateRootMatrix(a0);
        }
    }
}

/* kept local: this TU's uses of these do not fit the prototypes in
   motionManager2.h, quaternion.h and stageMultiBgaManager.h */
extern int GetWaterReaction(void *w, int *hit, void *plane, void *pos, void *vel, float low,
                            float mid, float high, float k, float acc);
extern void RotQuaternionY(void *q, int ang);
extern void GetMatrixFromQuaternion(void *m, void *q);
extern void EntryStageMultiBgaManager(int kind, void *pos, void *rot);
/* the two characters the floating box has to keep clear of, the boy and the
   girl, as sceneManager.c sets them */
extern char *D_00639EA4;
extern char *D_00639EA8;
/* the world Y axis the box's tilt is measured around, VMA 0x4E6290,
   { 0.0f, 1.0f, 0.0f, 0.0f } */
extern float D_004E6290[];

void execFloating(char *self)
{
    char fw[0xC0];
    float pos[4];
    float d[4];
    float g[4];
    float sub[4];
    float axis[4];
    float ofs[4];
    float acc[4];
    float q[4];
    float rot[4];
    float m[16];
    char cw[0xC0];
    float cm[16];
    float sv[4];
    float dv[4];
    int hit;
    char *w = (char *)GOBJ_SUB(self)->f_830;
    float len;
    float r;

    if (D_00639EA4 != 0) {
        if (*(int *)(w + 0x164) == 0) {
            GetCylinderCollisionWithExceptOwnCollision(self, (int)D_00639EA4, 50.0f, 50.0f, 0.0f,
                                                       1.0f, 1);
            avoidCharGObj(self, D_00639EA4);
        }
    }
    if (D_00639EA8 != 0) {
        GetCylinderCollisionWithExceptOwnCollision(self, (int)D_00639EA8, 70.700005f, 50.0f, 0.0f,
                                                   1.0f, 1);
        avoidCharGObj(self, D_00639EA8);
    }
    GetRootPosition(pos, self);
    GetLowerPlaneCollision(fw, pos);
    len = VectorLengthSquare((char *)GOBJ_SUB(self) + 0x130);
    if (100.0f < len) {
        _ScaleVectorXYZ((char *)GOBJ_SUB(self) + 0x130, (char *)GOBJ_SUB(self) + 0x130,
                        3.0f / _Sqrt(len));
    }
    /* the three water-probe heights are written as additions of the offset, not
       as subtractions: the ROM adds -50.0f and -25.0f and gcc 2.9 emits sub.s
       for a written subtraction (line 1128 below is one). */
    if (GetWaterReaction(w + 0xB0, &hit, fw, pos, (char *)GOBJ_SUB(self) + 0x130, pos[1] + -50.0f,
                         pos[1] + -25.0f, pos[1] + 50.0f, 0.9f,
                         60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * -0.1f *
                             (60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1])) * 3.0f) !=
        0) {
        if (*(float *)(fw + 0x24) - 50.0f < pos[1]) {
            pos[1] = *(float *)(fw + 0x24) - 50.0f;
        }
        _SubVector(d, pos, w + 0x170);
        d[1] = 0.0f;
        /* 0.1f * 0.1f, not 0.01f: the pool word is 0x3C23D70B, one ulp above
           the float nearest 0.01. */
        if (0.1f * 0.1f < VectorLengthSquare(d)) {
            _SubVector(d, pos, w + 0x170);
            *(float *)(w + 0x170) = pos[0];
            *(float *)(w + 0x178) = pos[2];
        } else {
            pos[0] = *(float *)(w + 0x170);
            pos[2] = *(float *)(w + 0x178);
        }
        memset(g, 0, 0x10);
        g[1] = -35.0f;
        sceVu0ScaleVectorXYZ(acc, w + 0xC0, -0.01f);
        sceVu0AddVector(w + 0xD0, w + 0xD0, acc);
        sceVu0AddVector(w + 0xD0, w + 0xD0, w + 0xF0);
        sceVu0ScaleVectorXYZ(w + 0xD0, w + 0xD0, 0.95f);
        sceVu0AddVector(w + 0xC0, w + 0xC0, w + 0xD0);
        sceVu0OuterProduct(axis, D_004E6290, w + 0xC0);
        CopyQuaternion(q, IdentityQuaternion);
        RotQuaternionY(q, GetTableArcTan2(*(float *)((char *)GOBJ_SUB(self) + 0x520),
                                          *(float *)((char *)GOBJ_SUB(self) + 0x528)));
        SetQuaternionByAxisRotateV(rot, (short)(VectorLength(w + 0xC0) * 20.48f / 50.0f), axis);
        MultiQuaternion(q, q, rot);
        SetRootQuaternion(self, q);
        GetMatrixFromQuaternion(m, rot);
        sceVu0ApplyMatrix(ofs, m, g);
        ofs[1] = 0.0f;
        sceVu0SubVector(sub, ofs, w + 0xE0);
        sceVu0SubVector(pos, pos, sub);
        CopyVector(w + 0xE0, ofs);
        r = *(float *)(w + 0x24) > *(float *)(w + 0x28) ? *(float *)(w + 0x24) * 50.0f
                                                        : *(float *)(w + 0x28) * 50.0f;
        pushOutFloatingBox(cw, cm, sv, dv, pos, q, r);
        _AddVectorXYZ(cw, pos, ofs);
        *(float *)(cw + 0xC) = 0.0f;
        _SubVector((char *)GOBJ_SUB(self) + 0x130, cw, w + 0x100);
        *(int *)((char *)GOBJ_SUB(self) + 0x13C) = 0;
        CopyVector(w + 0x100, cw);
        SetRootPosition(self, pos);
    }
    *(float *)((char *)GOBJ_SUB(self) + 0x134) += GetTableSin(*(short *)(w + 0x118)) * 0.1f;
    *(short *)(w + 0x118) += 2048;
    *(int *)(w + 0x164) = 0;
    if (*(short *)(w + 0x118) == 0) {
        CopyVector(cw, pos);
        *(float *)(cw + 4) = *(float *)(w + 0xB0);
        EntryStageMultiBgaManager(491, cw, IdentityQuaternion);
    }
}

/* kept local: this TU's uses of IdentityQuaternion do not fit the prototype in quaternion.h */
/* kept local: this TU's uses of ZeroVector do not fit the prototype in matrixDrive.h */
extern char ZeroVector[];
extern char D_004E62A0[];

void initFloating(char *a0)
{
    char *p = (char *)GOBJ_SUB(a0)->f_830;

    GOBJ_SUB(a0)->f_70 = *(int *)(*(int *)(p + 0x160) + 0x70);
    GOBJ_SUB(a0)->f_78 = 1;
    CopyQuaternion((char *)(int)GOBJ_SUB(a0) + 0xC0, IdentityQuaternion);
    SetRootQuaternion(a0, IdentityQuaternion);
    CopyVector(p + 0xE0, ZeroVector);
    CopyVector(p + 0xC0, ZeroVector);
    CopyVector(p + 0xD0, ZeroVector);
    GetRootPosition(p + 0x100, a0);
    CopyVector((char *)(int)GOBJ_SUB(a0) + 0x520, D_004E62A0);
    *(short *)(p + 0x118) = 0;
    execFloating(a0);
}

/* kept local: this TU's uses of SetSimplePlane do not fit the prototype in fieldCollision.h */
extern void SetSimplePlane(void *plane, float x, float y, float z, float d);
/* kept local: this TU's uses of GetDistanceFromPlane do not fit the prototype in fieldCollision.h */
extern float GetDistanceFromPlane(void *plane, void *pos);
/* kept local: this TU's uses of MatrixDrive_SetTransposeMatrix do not fit the prototype in matrixDrive.h */
extern void MatrixDrive_SetTransposeMatrix(void *dst, void *src);
/* kept local: this TU's uses of GetCharGObjList do not fit the prototype in geometryManager.h */
extern char **GetCharGObjList(void);
/* kept local: this TU's uses of ClipWall do not fit the prototype in fieldCollision.h */
extern void ClipWall(void *a0);
extern char D_0061F048[];
/* kept local: this TU's uses of UpdateRootMatrix do not fit the prototype in geometryManager.h */
extern void UpdateRootMatrix(void *a0);
extern int moveXPlus(float *a0, float f12, float f13, float f14);
extern int moveXMinus(float *a0, float f12, float f13, float f14);
extern int moveZPlus(float *a0, float f12, float f13, float f14);
extern int moveZMinus(float *a0, float f12, float f13, float f14);
extern int stage_no;
extern char D_0061F080[];

int _checkItemBreak(void *pos)
{
    float p[4];
    float d[4];
    char *o;

    /* listing lines 1259 and 1263 sit inside this function's own span, so
       the test is a nested inline function (the name is ours). What the
       bytes pin: the range is an integer argument converted at each compare,
       so fold evaluates the converted limit once per axis ahead of the
       ternary's two arms (the ROM's three 50.0f loads, none hoisted out of
       the loop), and only the helper's result is materialised. What they
       cannot pin: the parameter's integer type or its name. */
    inline int isNearItem(float *v, int r)
    {
        if ((v[0] < 0.0f ? -v[0] : v[0]) < r && (v[1] < 0.0f ? -v[1] : v[1]) < r &&
            (v[2] < 0.0f ? -v[2] : v[2]) < r) {
            return 1;
        }
        return 0;
    }

    for (o = isysGObjSearchFromObjKindID_begin(19); o != 0;
         o = isysGObjSearchFromObjKindID_next(o)) {
        if (CheckItemDead(o) != 0) {
            continue;
        }
        GetRootPosition(p, o);
        _SubVectorXYZ(d, p, pos);
        if (isNearItem(d, 50) != 0) {
            BreakItemFromOutside(o);
        }
    }
    return 1;
}

void initLanding(char *a0)
{
    float pos[4];
    float plane[4];
    float v[4];
    char *p = (char *)GOBJ_SUB(a0)->f_830;

    GetRootPosition(pos, a0);
    CopyVector(&GOBJ_SUB(a0)->f_130, ZeroVector);
    *(int *)&GOBJ_SUB(a0)->f_4AC = 0;
    GOBJ_SUB(a0)->f_4A0 = 1144;
    if (*(char **)(p + 0x68) != 0) {
        float d;

        GetPureVerticalPlane(0, plane, 0, (int *)(p + 0x60), 1);
        d = GetDistanceFromPlane(plane, pos);
        plane[3] = 0.0f;
        sceVu0ScaleVectorXYZ(v, plane, -(d - 50.0f));
        AddVectorXYZ(pos, pos, v);
    }
    _checkItemBreak(pos);
    GetMatrixFromQuaternionPos(p + 0x70, (char *)GOBJ_SUB(a0) + 0xC0, (char *)pos);
}

/* box.c:1308-1313 and 1315-1321 in the listing: both are inlined once, into
   action's case 4 (the inner one inside the outer one), so they are static
   inlines here; neither has a symbol of its own in the ROM or a census row, and
   the names are descriptive. */
static inline void resetBoxRootQuaternion(char *self, float *q)
{
    GetInverseQuaternion(q, (char *)GOBJ_SUB(self) + 0x60);
    SetRootQuaternion(self, q);
    GOBJ_SUB(self)->f_78 = 1;
}

static inline void playBoxAnimation(char *self, float *q)
{
    if (playAnimationCore(self) != 0) {
        char *p = (char *)GOBJ_SUB(self)->f_830;

        *(int *)(p + 0x20) = 0;
        resetBoxRootQuaternion(self, q);
    }
}

/* kept local: this TU's uses of AttackCenter_WithDir do not fit the prototype in attackhit.h */
extern void AttackCenter_WithDir(char *self, int kind, void *pos, void *dir, float r);

/* box.c:1325-1339 in the listing: inlined once, into execFallDown, so it is a
   static inline here; it has no symbol of its own in the ROM and no census row,
   and the name is descriptive. */
static inline void attackBoxFallCenter(char *self)
{
    float plane[4];
    float pos[4];
    char *q = (char *)GOBJ_SUB(self)->f_830;

    if (*(char **)(q + 0x68) != 0) {
        GetPureVerticalPlane(0, plane, 0, (int *)(q + 0x60), 1);
        plane[3] = 0.0f;
        GetRootPosition(pos, self);
        pos[1] += 50.0f;
        AttackCenter_WithDir(self, 17, pos, plane, 60.0f);
    }
}

void execFallDown(char *a0)
{
    char *p = (char *)GOBJ_SUB(a0)->f_830;

    switch (*(int *)(p + 0x20)) {
    case 2:
        if (playAnimationCore(a0) != 0) {
            *(int *)(p + 0x20) = 3;
        }
        break;
    case 3:
        execBoxFall(a0);
        break;
    }
    attackBoxFallCenter(a0);
    switch (checkFieldContact(a0, 50.0f)) {
    case 1:
        initLanding(a0);
        *(int *)(p + 0x20) = 4;
        landingSE((int)a0);
        break;
    case 2:
        initFloating(a0);
        *(int *)(p + 0x20) = 5;
        landingSE((int)a0);
        break;
    }
}

void inertiaMove(char *a0)
{
    float pos[4];
    float tmp[4];
    char w[0xC0];
    float base[4];
    char *p = (char *)GOBJ_SUB(a0)->f_830;

    if (onPath(a0) != 0) {
        CopyVector(p + 0x40, ZeroVector);
    }
    GetRootPosition(pos, a0);
    sceVu0ScaleVectorXYZ(p + 0x40, p + 0x40, *(float *)(p + 0x134));
    sceVu0ApplyMatrix(tmp, (void *)GOBJ_SUB(a0)->f_C, p + 0x40);
    sceVu0AddVector(pos, pos, tmp);
    SetRootPosition(a0, pos);
    checkBoxWallHit(a0, w, base, pos, 1);
    if (*(int *)(w + 0x88) != 0) {
        SetRootPosition(a0, pos);
        CopyVector(p + 0x40, ZeroVector);
    }
}

inline int IsThisBoxTruck(char *a0)
{
    return *(int *)(*(char **)((char *)GOBJ_SUB(a0) + 0x830) + 0x58);
}

void action(char *a0)
{
    /* the float view carries the up vector; the union is what the ROM's
       schedule needs, its alias-set-0 store keeping the matrix read after it */
    Vec4u v;
    char *p = (char *)GOBJ_SUB(a0)->f_830;

    switch (*(int *)(p + 0x20)) {
    case 0:
        if (*(int *)(p + 0x58) != 0) {
            inertiaMove(a0);
            updateBoxWheelAngle(a0);
            memset(&v, 0, 16);
            v.f[2] = 1.0f;
            _ApplyMatrix((char *)GOBJ_SUB(a0) + 0x520, (void *)GOBJ_SUB(a0)->f_C, &v);
        }
        CopyVector((char *)GOBJ_SUB(a0) + 0x130, ZeroVector);
        break;
    case 1:
    case 6:
        execAutoMove(a0);
        CopyVector((char *)GOBJ_SUB(a0) + 0x130, ZeroVector);
        break;
    case 2:
    case 3:
        execFallDown(a0);
        break;
    case 4:
        playBoxAnimation(a0, v.f);
        CopyVector((char *)GOBJ_SUB(a0) + 0x130, ZeroVector);
        break;
    case 5:
        execFloating(a0);
        break;
    case -1:
    default:
        debug_StdPrintfDummy(D_0061F048);
        CopyVector((char *)GOBJ_SUB(a0) + 0x130, ZeroVector);
        break;
    }
    if (*(int *)(p + 0x20) != 6) {
        if (*(int *)(*(int *)(p + 0x180) + 0x16C) != 0) {
            *(int *)(*(int *)(p + 0x180) + 0x16C) = 0;
        }
    }
}

/* kept local: this TU's uses of GetRootMatrix do not fit the prototype in geometryManager.h */
extern void GetRootMatrix();

inline void GetBoxGlobalHoldPoint(void *a0, void *a1, void *a2)
{
    float buf[16];
    GetRootMatrix(buf, a1);
    sceVu0ApplyMatrix(a0, buf, a2);
}

/* kept local: this TU's uses of GetWallAttribute and CompareAttribute do not
   fit the prototypes in fieldCollision.h */
extern int GetWallAttribute(void *w);
extern int CompareAttribute(int attr, int mask);
/* kept local: this TU does not include matrixDrive.h, whose other prototypes
   do not fit this TU's uses of them. */
extern float ZeroPoint[4];
/* The four hold-point candidates in the box's local frame and the four
   offsets added back after they are scaled by the box's half extents; both
   live in the TU's .data run (VMA 0x4E5FB0 and 0x4E5FF0, 4 x 16 bytes each). */
extern float D_004E5FB0[4][4];
extern float D_004E5FF0[4][4];

/* box.c:1477-1520 in the listing.  The clip work buffer is declared in a block
   of its own after the candidate loop: the ROM's frame puts it at sp+0x60,
   above the 64-byte matrix the inlined GetBoxGlobalHoldPoint keeps at sp+0x20,
   so it is allocated after the first inlining and not with the function's
   top-level locals.  The two squared-distance spellings are the listing's:
   sugiCommon.h:97 in the first iteration, sugiCommon.h:87 in the rest. */
int GetBoxHoldPoint(float *out, char *self, void *chara)
{
    float pos[4];
    float p[4];
    char *q = *(char **)((char *)GOBJ_SUB(self) + 0x830);
    int best = 0;
    float min = 0.0f;
    float d;
    int i;

    GetRootPosition(pos, chara);
    for (i = 0; i < 4; i++) {
        GetBoxGlobalHoldPoint(p, self, D_004E5FB0[i]);
        if (i == 0) {
            min = distance_squared_b(p, pos);
            best = 0;
        } else {
            if ((d = distance_squared(p, pos)) < min) {
                min = d;
                best = i;
            }
        }
    }
    CopyVector(out, D_004E5FB0[best]);
    out[0] *= *(float *)(q + 0x24);
    out[2] *= *(float *)(q + 0x28);
    AddVectorXYZ(out, out, D_004E5FF0[best]);
    *(void **)(q + 4) = chara;
    CopyVector(q + 0x10, out);
    {
        char w[0xC0];

        memset(w, 0, 0xC0);
        GetBoxGlobalHoldPoint(w + 0x10, self, ZeroPoint);
        GetBoxGlobalHoldPoint(w, self, out);
        ClipWall(w);
        if (*(int *)(w + 0x88) != 0) {
            if (CompareAttribute(GetWallAttribute(w), 0xB00) ||
                CompareAttribute(GetWallAttribute(w), 0x400)) {
                return 0;
            }
        }
    }
    return 1;
}

inline int CanHoldBox(char *a0)
{
    return *(int *)(*(char **)((char *)GOBJ_SUB(a0) + 0x830) + 0x20) == 0;
}

typedef struct {
    float x, y, z;
} BoxVec3;

static inline void setupClipWork(char *w, char *obj, float *dir, float len, float h)
{
    float t[4];

    _ScaleVector(t, dir, len);
    GetRootPosition(w, obj);
    *(float *)(w + 4) += h;
    _AddVectorXYZ(w + 0x10, w, t);
}

static inline int checkBoxStopWall(char *obj, float *dir)
{
    char w[0xC0];
    int r = 1;

    memset(w, 0, 0xC0);
    setupClipWork(w, obj, dir, 145.0f, 40.0f);
    ClipWallBoxStop(w);
    if (*(int *)(w + 0x88) != 0) {
        r = 0;
    }
    return r;
}

static inline int checkMoveWall(char *obj, float *dir)
{
    char w[0xC0];
    int r = 1;

    memset(w, 0, 0xC0);
    setupClipWork(w, obj, dir, 245.0f, 0.0f);
    ClipWall(w);
    if (*(int *)(w + 0x88) != 0) {
        r = 0;
    }
    return r;
}

static inline int moveXPlus(float *a0, float f12, float f13, float f14)
{
    float w;
    float f0;
    int rv;
    f13 = f13 + f14;
    w = a0[2];
    if (w < 0.0f) {
        if (-w < f13)
            goto p4;
        return 0;
    }
    rv = 0;
    if (!(w < f13))
        goto end;
p4:
    w = a0[1];
    if (w < 0.0f) {
        if (-w < f13)
            goto rng;
        return 0;
    }
    rv = 0;
    if (!(w < f13))
        goto end;
rng:
    f0 = f12 - f13;
    if (!(f0 + f14 < a0[0])) {
        rv = 0;
        goto end;
    }
    if (a0[0] < f12 + f13)
        return 1;
    rv = 0;
end:
    return rv;
}

static inline int moveXMinus(float *a0, float f12, float f13, float f14)
{
    float w;
    float f0;
    int rv;
    f13 = f13 + f14;
    w = a0[2];
    if (w < 0.0f) {
        if (-w < f13)
            goto p4;
        return 0;
    }
    rv = 0;
    if (!(w < f13))
        goto end;
p4:
    w = a0[1];
    if (w < 0.0f) {
        if (-w < f13)
            goto rng;
        return 0;
    }
    rv = 0;
    if (!(w < f13))
        goto end;
rng:
    f0 = f12 - f13;
    if (!(f0 + f14 < -a0[0])) {
        rv = 0;
        goto end;
    }
    if (-a0[0] < f12 + f13)
        return 1;
    rv = 0;
end:
    return rv;
}

static inline int moveZPlus(float *a0, float f12, float f13, float f14)
{
    float w;
    float f0;
    int rv;
    f13 = f13 + f14;
    w = a0[0];
    if (w < 0.0f) {
        if (-w < f13)
            goto p4;
        return 0;
    }
    rv = 0;
    if (!(w < f13))
        goto end;
p4:
    w = a0[1];
    if (w < 0.0f) {
        if (-w < f13)
            goto rng;
        return 0;
    }
    rv = 0;
    if (!(w < f13))
        goto end;
rng:
    f0 = f12 - f13;
    if (!(f0 + f14 < a0[2])) {
        rv = 0;
        goto end;
    }
    if (a0[2] < f12 + f13)
        return 1;
    rv = 0;
end:
    return rv;
}

static inline int moveZMinus(float *a0, float f12, float f13, float f14)
{
    float w;
    float f0;
    int rv;
    f13 = f13 + f14;
    w = a0[0];
    if (w < 0.0f) {
        if (-w < f13)
            goto p4;
        return 0;
    }
    rv = 0;
    if (!(w < f13))
        goto end;
p4:
    w = a0[1];
    if (w < 0.0f) {
        if (-w < f13)
            goto rng;
        return 0;
    }
    rv = 0;
    if (!(w < f13))
        goto end;
rng:
    f0 = f12 - f13;
    if (!(f0 + f14 < -a0[2])) {
        rv = 0;
        goto end;
    }
    if (-a0[2] < f12 + f13)
        return 1;
    rv = 0;
end:
    return rv;
}

static inline int checkCharGObjs(char *obj, char *holder, float *dir)
{
    float pos[4];
    float pos2[4];
    float d[4];
    char **list;
    int (*move)(float *, float, float, float);
    float w = 50.0f;

    list = GetCharGObjList();
    GetRootPosition(pos, obj);
    if ((dir[0] < 0.0f ? -dir[0] : dir[0]) > (dir[2] < 0.0f ? -dir[2] : dir[2])) {
        if (0.0f <= dir[0]) {
            move = moveXPlus;
        } else {
            move = moveXMinus;
        }
    } else if (0.0f <= dir[2]) {
        move = moveZPlus;
    } else {
        move = moveZMinus;
    }
    while (*list != 0) {
        if (*list != holder) {
            GetRootPosition(pos2, *list);
            _SubVector(d, pos2, pos);
            if (move(d, w + w, w, *(float *)(*(char **)(*list + 0x15C) + 0x3D8) + 5.0f) != 0) {
                return 0;
            }
        }
        list++;
    }
    return 1;
}

int _checkItemCollision(void *pos)
{
    float p[4];
    float d[4];
    char *o;

    /* listing lines 1735 and 1739: the same nested range test as
       _checkItemBreak's (see the comment there for what the bytes pin) */
    inline int isNearItem(float *v, int r)
    {
        if ((v[0] < 0.0f ? -v[0] : v[0]) < r && (v[1] < 0.0f ? -v[1] : v[1]) < r &&
            (v[2] < 0.0f ? -v[2] : v[2]) < r) {
            return 1;
        }
        return 0;
    }

    for (o = isysGObjSearchFromObjKindID_begin(19); o != 0;
         o = isysGObjSearchFromObjKindID_next(o)) {
        if (CheckItemDead(o) != 0) {
            continue;
        }
        GetRootPosition(p, o);
        _SubVectorXYZ(d, p, pos);
        if (isNearItem(d, 50) != 0) {
            return 0;
        }
    }
    return 1;
}

static inline int checkItemHit(char *obj, float *dir)
{
    float pos[4];
    float d[4];
    float to[4];

    _ScaleVectorXYZ(d, dir, 100.0f);
    GetRootPosition(pos, obj);
    _AddVectorXYZ(to, pos, d);
    return _checkItemCollision(to);
}

int moveBoxAutoMatic(char *a0, int a1)
{
    float v[4];
    float v2[4];
    char *p = (char *)GOBJ_SUB(a0)->f_830;
    float t = 30.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    float w = t * t;
    int r;

    switch (a1) {
    default:
        *(float *)(p + 0x134) = 0.85f;
        AddVectorXYZ(p + 0x40, p + 0x40, ZeroVector);
        break;
    case 1:
        memset(v, 0, 16);
        v[2] = w * 0.5f;
        *(float *)(p + 0x134) = 0.98f;
        AddVectorXYZ(p + 0x40, p + 0x40, v);
        break;
    case -1:
        memset(v2, 0, 16);
        v2[2] = w * -0.5f;
        *(float *)(p + 0x134) = 0.98f;
        AddVectorXYZ(p + 0x40, p + 0x40, v2);
        break;
    }
    if (*(int *)(p + 0x138) != a1) {
        StopSEPackageWithGroupVariation((int)a0, 1);
        if (a1 != 0) {
            ExecuteSEPackageWithGroupVariation(a0, 29, 1);
        }
    }
    *(int *)(p + 0x138) = a1;
    if (onPath(a0) != 0) {
        CopyVector(p + 0x40, ZeroVector);
    }
    UpdateRootMatrix(a0);
    r = execNormalMove(a0, 1);
    UpdateRootMatrix(a0);
    return r;
}

int MoveBoxWithHoldPoint(char *a0, void *a1, char *a2, int a3, float *a4)
{
    float plane[4];
    float nv[4];
    float hp[4];
    float pos[4];
    float mv[4];
    char *q = *(char **)((char *)GOBJ_SUB(a0) + 0x830);
    int idx;
    int hit;
    float dot;
    float dist;

    CopyVector(q + 0x190, a4);
    GetBoxGlobalHoldPoint(hp, a0, a1);
    GetRootPosition(pos, a0);
    sceVu0SubVector(nv, hp, pos);
    sceVu0Normalize(nv, nv);

    dot = sceVu0InnerProduct(nv, hp);
    SetSimplePlane(plane, nv[0], nv[1], nv[2], -dot);

    idx = GetSkeltonFocusNode(a2, a3);
    dist = GetDistanceFromPlane(plane, *(char **)((char *)GOBJ_SUB(a2) + 0xC) + (idx << 6) + 0x30);

    sceVu0ScaleVector(mv, nv, dist);

    if (*(int *)(*(char **)((char *)GOBJ_SUB(a0) + 0x830) + 0x58) != 0) {
        float m[16];

        _ScaleVector(mv, mv, 0.05f);
        MatrixDrive_SetTransposeMatrix(m, *(void **)((char *)GOBJ_SUB(a0) + 0xC));
        sceVu0ApplyMatrix(mv, m, mv);
        AddVectorXYZ(q + 0x40, q + 0x40, mv);
        if (onPath(a0) != 0) {
            CopyVector(q + 0x40, ZeroVector);
        }
        if (stage_no == 8) {
            if (*(int *)q == 0 && *(int *)(q + 0x114) == 0) {
                pushStartSE((int)a0);
            }
        }
        ReviveCarryableItemsWithBoundary(pos, 100.0f);
    } else if (checkCharGObjs(a0, a2, a4) && checkBoxStopWall(a0, a4) &&
               CheckGeneratorCollision(a0, a4) && checkItemHit(a0, a4)) {
        *(int *)(q + 0x30) = (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] *
                             (GetNbMotionFrames(GOBJ_SUB(a2)->f_4A0) - 1) / 0x1E;
        _ScaleVectorXYZ(q + 0x40, a4, 100.0f / (float)*(int *)(q + 0x30));

        hit = checkMoveWall(a0, a4);
        if (hit) {
            *(int *)(q + 0x20) = 1;
        } else {
            float npos[4];
            float d[4];

            GetRootPosition(npos, a0);
            _ScaleVector(d, a4, 100.0f);
            _AddVectorXYZ(npos, npos, d);
            *(int *)(q + 0x20) = 6;
            alignPosition(a0, npos, npos, 100.0f);
            npos[1] -= 1.0f;
            debug_StdPrintfDummy(D_0061F080, npos[0], npos[1], npos[2]);
            CopyVector(*(char **)(*(char **)(*(char **)(q + 0x180) + 0x15C) + 0xC) + 0x30, npos);
            *(int *)(*(char **)(q + 0x180) + 0x16C) = 1;
        }
        if (GOBJ_SUB(a2)->f_56C != 0) {
            *(BoxVec3 *)(q + 0x60) = *(BoxVec3 *)((char *)GOBJ_SUB(a2) + 0x190);
        }
    } else {
        return 0;
    }
    UpdateRootMatrix(a0);
    {
        int rv = execNormalMove(a0, 1);
        UpdateRootMatrix(a0);
        return rv;
    }
}

inline int BoxRideFunc(int *a0, char *a1)
{
    char *obj = (char *)*a0;
    Sub15C *p15c = GOBJ_SUB(obj);
    char *s0 = *(char **)((char *)p15c + 0x830);
    char buf[0x20];
    if (*(int *)(s0 + 0x20) != 5) {
        return 0;
    }
    p15c->f_134 += 0.5f;
    GetRootPosition(buf + 0x10, obj);
    CopyVector(buf, (char *)GOBJ_SUB(a1) + 0xA0);
    *(int *)(buf + 4) = 0;
    sceVu0AddVector(s0 + 0xD0, s0 + 0xD0, buf);
    return 1;
}

inline void ExecBoxMoveStartReaction(char *a0, int a1)
{
    char *q = *(char **)((char *)GOBJ_SUB(a0) + 0x830);
    if (*(int *)(q + 0x58) != 0) {
        if (*(int *)(q + 0x110) != 0) {
            goto end;
        }
    }
    if (a1 >= 0) {
        pushStartSE((int)a0);
        *(int *)(q + 0x114) = 0;
    } else {
        pullStartSE((int)a0);
        *(int *)(q + 0x114) = 0;
    }
end:
    *(int *)(q + 0x110) = 1;
}

inline void ExecBoxMoveEndReaction(char *a0)
{
    char *q = *(char **)((char *)GOBJ_SUB(a0) + 0x830);
    if (*(int *)(q + 0x58) == 0 || *(int *)(q + 0x110) != 0) {
        stopBoxMoveSE(a0);
    }
    *(int *)(q + 0x110) = 0;
}

extern char D_0061F0A0[];
extern char D_0061F0B0[];
extern char D_0061F128[];
extern char D_0061F138[];

void ReInitBoxGeo(char *a0)
{
    char *p = *(char **)((char *)GOBJ_SUB(a0) + 0x830);

    debug_StdPrintfDummy(D_0061F0A0);
    GOBJ_SUB(a0)->f_70 = *(int *)(p + 0x2C);
    if (checkFieldContact(a0, 100000.0f) == 0) {
        debug_StdPrintfDummy(D_0061F0B0);
    } else {
        int m = GOBJ_SUB(a0)->f_5F8;

        if (m == 0x40 || m == 0x50) {
            initFloating(a0);
            *(int *)(p + 0x20) = 5;
            debug_StdPrintfDummy(D_0061F128);
        } else {
            *(int *)(p + 0x20) = 0;
            AlignBox(a0, 100.0f);
            execNormalMove(a0, 1);
            debug_StdPrintfDummy(D_0061F138);
        }
    }
    UpdateRootMatrix(a0);
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/box", InitBoxGeo);

void BoxGeo(char *a0)
{
    char *p = *(char **)((char *)GOBJ_SUB(a0) + 0x830);

    action(a0);
    UpdateRootMatrix(a0);
    if ((*(int *)p)++ >= 0x1F) {
        *(int *)p = 0;
        gamesysObjInfoUniqDataSet(a0);
    }
}

/* kept local: this TU's uses of p2o_SetDefaultEnviroment do not fit the prototype in DisplayP2O.h */
extern int p2o_SetDefaultEnviroment(int a0);
/* kept local: this TU's uses of p2o_DispVU1 do not fit the prototype in DisplayP2O.h */
extern void p2o_DispVU1(void *a0);
extern int D_0028F4D4[];

inline void BoxDL(char *a0)
{
    char *q = *(char **)((char *)GOBJ_SUB(a0) + 0x830);
    p2o_SetDefaultEnviroment((int)a0);
    p2o_DispVU1(a0);
    if (*(int *)(q + 0x58) != 0) {
        dispWheels(a0);
    }
    if (D_0028F4D4[0] != 0) {
        StopSEPackageWithGroupVariation((int)a0, 1);
        *(int *)(*(char **)((char *)GOBJ_SUB(a0) + 0x830) + 0x138) = 0;
    }
}

extern char D_0061F148[];

inline int BoxGeoRestore(float *a0, float *a1)
{
    a0[0] = a1[4];
    a0[1] = a1[5];
    a0[2] = a1[6];
    a0[4] = a1[8];
    a0[5] = a1[9];
    a0[6] = a1[10];
    debug_StdPrintfDummy(D_0061F148, a0[8], a0[9], a0[10]);
    return 1;
}

inline int BoxExtGeoRestore(void)
{
    return 1;
}

inline int BoxMemoryFunc(void)
{
    return 1;
}

int GetBoxMode(char *a0)
{
    return *(int *)(*(char **)((char *)GOBJ_SUB(a0) + 0x830) + 0x20);
}
