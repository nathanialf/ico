#include "box.h"
#include "sugiCommon.h"
#include "main.h"
#include "matrixDrive.h"
#include "fieldCollision.h"
#include "quaternion.h"
#include "DObj.h"
#include "Primitive.h"
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
#include "motionFileManager.h"
#include "sceneManager.h"
#include "Matrix.h"
#include "motionManager.h"
#include "GifPacket.h"
#include <math.h>
#include "stageMultiBgaManager.h"
#include "DisplayP2O.h"
#include "lineManager.h"
#include "attackhit.h"
#include "obj_manager.h"
#include "memory.h"
#include "geometryManager.h"
#include "ios.h"
#include "particleEffect.h"
#include "switch.c.inc"

/* The 416-byte box work block InitBoxGeo allocates and seeds from the
   template below (VMA 0x4E6030).  RECONSTRUCTION: the record and every name
   are ours, from what box.c does at each offset.  aligned(8) because the
   seeding copy is the ROM's doubleword loop. */
typedef struct BoxWork { /* field names derived */
    int serial;          /* 0x000, the box's number, mod 30 */
    GObj *holder;        /* 0x004, the character holding the box, mailed 25 when it falls */
    char pad008[8];
    float holdPoint[4]; /* 0x010, the hold point GetBoxHoldPoint last reported */
    int mode;     /* 0x020, 0 still, 1 auto move, 2 falling, 3 to 5 the fall's phases, 6 aligning */
    float scaleX; /* 0x024, the layout's X scale */
    float scaleZ; /* 0x028, the layout's Z scale */
    int colData;  /* 0x02C, the collision ReInitBoxGeo restores */
    int moveFrames; /* 0x030, the frames left of an auto move */
    char pad034[12];
    float vel[4];   /* 0x040, the move per frame */
    int frontPoint; /* 0x050, the path point nearest the front axle */
    int rearPoint;  /* 0x054, the path point nearest the rear axle */
    int route;      /* 0x058, the routeTable index */
    int pointCount; /* 0x05C, the route's point count */
    WallCfg wall;   /* 0x060, the wall the box last hit */
    char pad06C[4];
    float mtx[4][4];      /* 0x070, the box's matrix */
    float waterHeight[4]; /* 0x0B0, the water height GetWaterReaction reports */
    float tilt[4];        /* 0x0C0, the floating box's tilt */
    float tiltVel[4];     /* 0x0D0, the tilt's velocity */
    float lastOffset[4];  /* 0x0E0, the last frame's float offset */
    float tiltForce[4];   /* 0x0F0, the force added to the tilt each frame */
    float lastPos[4];     /* 0x100, the last frame's position */
    int moving;           /* 0x110, set while a push or pull is under way */
    int seStopped;        /* 0x114, set once the move sound has been stopped at the path's end */
    short floatPhase;     /* 0x118, the bob's sine phase */
    short pad11A;
    char *wheelDObj;  /* 0x11C, the wheel DObj dispWheels draws */
    short wheelAngle; /* 0x120, the wheels' X rotation */
    short pad122;
    float wheelRadius; /* 0x124 */
    float wheelHeight; /* 0x128 */
    float wheelFront;  /* 0x12C, the front axle's Z */
    float wheelRear;   /* 0x130, the rear axle's Z */
    float friction;    /* 0x134, the move's damping, 0.85 or 0.98 */
    int autoDir;       /* 0x138, the direction moveBoxAutoMatic last moved in */
    char pad13C[4];
    int stopWall; /* 0x140, set while a box-stop wall is ahead */
    char pad144[12];
    float tiltQuat[4];  /* 0x150, the slope tilt the root quaternion takes */
    Sub15C *effectDObj; /* 0x160, the effect DObj */
    int charHit;        /* 0x164, set when a character pushed the floating box this frame */
    char pad168[8];
    float floatAnchor[4]; /* 0x170, the floating box's resting X and Z */
    int subGObj;          /* 0x180, the layouted sub GObj, held as a word: InitBoxGeo's store of it
                    precedes the sub object's disp store, which a GObj * store is scheduled past */
    char pad184[12];
    float moveDir[4]; /* 0x190, the direction of the last push */
} __attribute__((aligned(8))) BoxWork;

void landingSE(GObj *a0)
{
    ExecuteSEPackage(a0, 0x2);
}

void fallDownStartSE(GObj *a0)
{
    ExecuteSEPackage(a0, 0x24);
}

void pushStartSE(GObj *a0)
{
    ExecuteSEPackage(a0, 0x4);
}

void pullStartSE(GObj *a0)
{
    ExecuteSEPackage(a0, 0xD);
}

void wallHitSE(GObj *a0)
{
    ExecuteSEPackage(a0, 0x1E);
}

/* box.c:232-241 in the listing: inlined into onPath and into
   ExecBoxMoveEndReaction, so it is a static inline here; it has no symbol of
   its own in the ROM and no census row, and the name is descriptive. */
static inline void stopBoxMoveSE(GObj *self)
{
    BoxWork *q = GOBJ_SUB(self)->work;

    StopSEPackage(self);
    StopSEPackageWithGroupVariation(self, 1);

    ExecuteSEPackage(self, 0x16);
    if (q->stopWall != 0) {
        wallHitSE(self);
        q->stopWall = 0;
    }
}

void initFallDown(GObj *a0)
{
    float pos[4];
    float pts[16];
    float n[4];
    BoxWork *p = GOBJ_SUB(a0)->work;

    GetRootPosition(pos, a0);
    GOBJ_SUB(a0)->colRotate = 0;
    *(int *)&GOBJ_SUB(a0)->ctrl.animFrame = 0;
    if (p->wall.n != 0) {
        GetWallGlobalInfo((char *)pts, n, p->wall.n,
                          (char *)GOBJ_SUB(p->wall.o.obj)->nodeMtx + (p->wall.o.node << 6));
        n[1] = 0.0f;
        sceVu0Normalize(n, n);
        SetIdentityQuaternion(GOBJ_SUB(a0)->root.baseQuat);
        RotQuaternionY(GOBJ_SUB(a0)->root.baseQuat, GetTableArcTan2(n[0], n[2]));
        GetRootQuaternion(GOBJ_SUB(a0)->root.motionQuat, a0);
        DivQuaternion(GOBJ_SUB(a0)->root.motionQuat, GOBJ_SUB(a0)->root.motionQuat,
                      GOBJ_SUB(a0)->root.baseQuat);
        GetMatrixFromQuaternionPos(p->mtx[0], GOBJ_SUB(a0)->root.baseQuat, (char *)pos);
        GOBJ_SUB(a0)->ctrl.motion = 1143;
    } else {
        GOBJ_SUB(a0)->ctrl.motion = 1143;
        GetRootQuaternion(GOBJ_SUB(a0)->root.baseQuat, a0);
    }
}

/* kept local: this TU does not include matrixDrive.h, whose FSqrt and
   AddVectorXYZ prototypes do not fit this TU's uses of them. */
extern void GetLowerPlaneCollision(void *work, void *pos);

int checkFieldContact(GObj *a0, float lim)
{
    ClipBuf w;
    float pos[4];
    float v[4];
    int r;

    GetRootPosition(pos, a0);
    CopyVector(v, pos);
    v[1] -= GOBJ_SUB(a0)->root.move[1];
    GetLowerPlaneCollision(&w, v);
    r = CheckFieldContact(&w, a0, pos, lim);
    if (*(int *)GOBJ_SUB(a0) != 0) {
        UnlinkParentOfDObj(a0);
    }
    GOBJ_SUB(a0)->ctrl.floorAttr = 0;
    switch (r) {
    case 1:
        if (a0 != w.floor.o.obj) {
            if (*(GObj **)GOBJ_SUB(a0) != w.floor.o.obj ||
                *(int *)((char *)GOBJ_SUB(a0) + 4) != w.floor.o.node) {
                LinkParentOfDObj(a0, (PackedLL_19CAF0 *)&w.floor);
                GOBJ_SUB(a0)->ctrl.floorAttr = GetFloorAttribute(&w);
            }
        }
        w.pt[1][1] = w.pt[2][1] - 50.0f;
        SetDirectRootPosition(a0, w.pt[1]);
        return 1;
    case 2:
        GOBJ_SUB(a0)->ctrl.floorAttr = GetFloorAttribute(&w);
        return 2;
    }
    return 0;
}

/* kept local: this TU does not include geometryManager.h, whose GetRootMatrix and
   GetCharGObjList prototypes do not fit this TU's uses of them. */

/* box.c:343-360 in the listing: inlined into execNormalMove twice (once with
   ClipWall, once with ClipWallBoxStop) and into inertiaMove once, so it is a
   static inline here; it has no symbol of its own in the ROM and no census
   row, and the name is descriptive.  The two constant arguments fold, which is
   why each inlining carries only one of the two clip calls.  The work buffer
   and the root-position scratch are the CALLER's: the ROM's frames place them
   among the caller's own locals, and execNormalMove's two expansions get two
   separate work buffers while sharing one output vector. */
static inline void checkBoxWallHit(GObj *self, ClipBuf *w, float *base, float *out, int stop)
{
    BoxWork *p = GOBJ_SUB(self)->work;

    GetRootPosition(base, self);
    if (out != 0) {
        CopyVector(out, base);
    }
    w->rad = (p->scaleX < p->scaleZ ? p->scaleX : p->scaleZ) * 50.0f - 5.0f;
    base[1] += 40.0f;
    CopyVector(w->pt[0], base);
    CopyVector(w->pt[1], base);
    if (stop != 0) {
        ClipWallBoxStop(w);
    } else {
        ClipWall(w);
    }
    w->pt[2][1] -= 40.0f;
}

/* kept local: this TU's uses of these do not fit the prototypes in the headers
   that declare them */

/* the two debug lines the wall fit prints, rodata VMA 0x61EF20 and 0x61EF48;
   the second is EUC-JP, "this terrain is wrong (it is not cut to 100cm)" */

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
int execNormalMove(GObj *self, int stop)
{
    ClipBuf stopWork;
    float pos[4];
    ClipBuf work;
    float wn[4];
    BoxWallRec wn2;
    float plTop[4];
    float plSide[4];
    float up[4];
    float proj[4];
    float axis[4];
    float norm[4];
    float rot[4];
    BoxWork *p = GOBJ_SUB(self)->work;
    int ret = 1;
    float hw;
    float d;
    float dy;
    float adj;
    short ang;

    if (stop != 0) {
        checkBoxWallHit(self, &stopWork, pos, 0, 1);
        if (stopWork.wall.n != 0) {
            ret = 0;
            SetDirectRootPosition(self, stopWork.pt[2]);
        }
    }

    if (checkFieldContact(self, 110.0f) != 1) {
        if (p->holder != 0) {
            iosOmSendMail(p->holder, 25, self);
            p->holder = 0;
        }
        initFallDown(self);
        fallDownStartSE(self);
        p->mode = 2;
    } else {
        if (stop == 0) {
            checkBoxWallHit(self, &work, wn, pos, 0);
            if (work.wall.n != 0) {
                wn2.pt = *(BoxWallPt *)&work.wall.o;
                wn2.hit = (int)work.wall.n;
                *(BoxWallRec *)wn = wn2;

                hw = (p->scaleX < p->scaleZ ? p->scaleX : p->scaleZ) * 50.0f;

                CopyVector(up, pos);
                up[1] += 50.0f;
                GetPureVerticalPlane(plTop, plSide, 0, (int *)wn, 0);

                d = plane_distance(up, plSide);

                if (hw - 10.0f < d) {
                    CopyQuaternion(p->tiltQuat, IdentityQuaternion);
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
                        debug_StdPrintfDummy("height: %f   dist: %f  ofs: %f %x \n", dy, d, adj,
                                             ang);

                        GetSlerpQuaternion(p->tiltQuat, rot, p->tiltQuat, 0.5f);
                    } else {
                        /* EUC-JP: "this terrain is wrong (it is not divided into 100 cm)" */
                        debug_StdPrintfDummy("この地形はおかしいです(100cmに区切られていません)\n");
                        GetSlerpQuaternion(p->tiltQuat, IdentityQuaternion, p->tiltQuat, 0.5f);
                    }
                }
            } else {
                GetSlerpQuaternion(p->tiltQuat, IdentityQuaternion, p->tiltQuat, 0.5f);
            }
            GetInverseQuaternion(axis, (char *)GOBJ_SUB(self) + 0x60);
            MultiQuaternion(proj, axis, p->tiltQuat);
            SetRootQuaternion(self, proj);
        } else {
            SetIdentityQuaternion(p->tiltQuat);
        }
    }

    return ret;
}

/* box.c:461-478 in the listing: inlined once, into execAutoMove, so it has no
   symbol of its own in the ROM and no census row; the name is descriptive. */
static inline void setBoxStopWallFlag(GObj *self, float *vel)
{
    ClipBuf w;
    float dir[4];
    BoxWork *p = GOBJ_SUB(self)->work;

    memset(&w, 0, 0xC0);
    _NormalizeVector(dir, vel);
    _ScaleVector(dir, dir, (p->scaleX < p->scaleZ ? p->scaleX : p->scaleZ) * 50.0f + 25.0f);
    GetRootPosition(w.pt[0], self);
    AddVectorXYZ(w.pt[1], w.pt[0], dir);
    ClipWallBoxStop(&w);
    if (w.wall.n != 0) {
        p->stopWall = 1;
    } else {
        p->stopWall = 0;
    }
}

int execAutoMove(GObj *a0)
{
    float pos[4];
    BoxWork *p = GOBJ_SUB(a0)->work;

    GetRootPosition(pos, a0);
    _AddVector(pos, pos, p->vel);
    SetDirectRootPosition(a0, pos);
    execNormalMove(a0, 0);
    setBoxStopWallFlag(a0, (float *)p->vel);
    if (--p->moveFrames <= 0) {
        p->mode = 0;
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

static inline void alignPosition(GObj *self, float *dst, float *src, float grid)
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

int AlignBox(GObj *a0, float grid)
{
    float pos[4];
    float quat[4];
    Sub15C *sub = GOBJ_SUB(a0);
    BoxWork *q = sub->work;

    GetInverseQuaternion(quat, (char *)sub + 0x60);
    SetRootQuaternion(a0, quat);
    GetRootPosition(pos, a0);
    alignPosition(a0, pos, pos, grid);
    SetDirectRootPosition(a0, pos);
    q->mode = 0;
    return 0;
}

/* declared here: box.c includes no header that declares the ios allocators
   (ico2/fumi/include/memory.h has them with an IosMemPart * partition) */
/* kept local: this TU's view of ios.c's partition handle is a pointer, which
   initWheels' schedule needs (ios.h declares the handles int) */
extern GenGeo objLayout[];

/* box.c:546-565 in the listing.  Lines 558 to 560 are one call-site line in
   the listing, the same DObj-buffer setup ico2/omori/src/chain.c expands by
   hand at its own line 1245 (InitChainGeo, matched): the wheel count is 2
   here, so the three allocation sizes are 2<<6, 2<<4 and 2*80 bytes and the
   560 the allocator records is the dev source line. */
void initWheels(GObj *self, float *lay)
{
    BoxWork *w = GOBJ_SUB(self)->work;
    int i;

    if (objLayout[self->labelId].accessary == 26 ||
        accessary[GOBJ_SUB(self)->accessary].model == 0x610) {
        w->wheelDObj = 0;
    } else {
        w->wheelDObj = CSVSYSTEM_InitDObj(accessary[GOBJ_SUB(self)->accessary].model, lay);
        if (*(int *)(w->wheelDObj + 0xC) != 0) {
            iosFree((void *)(*(int *)(w->wheelDObj + 0xC) & 0x0FFFFFFF));
        }
        if (*(int *)(w->wheelDObj + 0x10) != 0) {
            iosFree((void *)(*(int *)(w->wheelDObj + 0x10) & 0x0FFFFFFF));
        }
        *(int *)(w->wheelDObj + 0xC) = 0;
        *(int *)(w->wheelDObj + 0x10) = 0;
        *(int *)(w->wheelDObj + 0xC) = (int)iosMallocDebug(ios_partition_seki, 128, __FILE__, 560);
        *(int *)(w->wheelDObj + 0x10) = (int)iosMallocDebug(ios_partition_seki, 32, __FILE__, 560);
        *(int *)(w->wheelDObj + 0x8) = 2;
        if (*(int *)(w->wheelDObj + 0x870) != 0) {
            iosFree((void *)(*(int *)(w->wheelDObj + 0x870) & 0x0FFFFFFF));
        }
        *(int *)(w->wheelDObj + 0x870) =
            (int)iosMallocDebug(ios_partition_seki, 160, __FILE__, 560);

        for (i = 0; i < 2; i++) {
            {
                struct DObjNode *e =
                    (struct DObjNode *)(i * 80 + (int)*(char **)(w->wheelDObj + 0x870));
                e->flags.ll &= ~1;
            }
            {
                struct DObjNode *e =
                    (struct DObjNode *)(i * 80 + (int)*(char **)(w->wheelDObj + 0x870));
                e->flags.ll &= ~2;
            }
            {
                struct DObjNode *e =
                    (struct DObjNode *)(i * 80 + (int)*(char **)(w->wheelDObj + 0x870));
                e->pos[0] = 0.0f;
            }
            {
                struct DObjNode *e =
                    (struct DObjNode *)(i * 80 + (int)*(char **)(w->wheelDObj + 0x870));
                e->pos[1] = 0.0f;
            }
            {
                struct DObjNode *e =
                    (struct DObjNode *)(i * 80 + (int)*(char **)(w->wheelDObj + 0x870));
                e->pos[2] = 0.0f;
            }
            {
                struct DObjNode *e =
                    (struct DObjNode *)(i * 80 + (int)*(char **)(w->wheelDObj + 0x870));
                e->pos[3] = 1.0f;
            }
            {
                struct DObjNode *e =
                    (struct DObjNode *)(i * 80 + (int)*(char **)(w->wheelDObj + 0x870));
                e->flags.ll &= ~4;
            }
            {
                struct DObjNode *e =
                    (struct DObjNode *)(i * 80 + (int)*(char **)(w->wheelDObj + 0x870));
                e->fade = 0;
            }
            {
                struct DObjNode *e =
                    (struct DObjNode *)(i * 80 + (int)*(char **)(w->wheelDObj + 0x870));
                e->alpha = 1.0f;
            }
            {
                char *e = (char *)(i * 80 + (int)*(char **)(w->wheelDObj + 0x870));
                *(short *)(e + 0x3A) = 0;
            }
            {
                struct DObjNode *e =
                    (struct DObjNode *)(i * 80 + (int)*(char **)(w->wheelDObj + 0x870));
                e->scale[0] = 1.0f;
            }
            {
                struct DObjNode *e =
                    (struct DObjNode *)(i * 80 + (int)*(char **)(w->wheelDObj + 0x870));
                e->scale[1] = 1.0f;
            }
            {
                struct DObjNode *e =
                    (struct DObjNode *)(i * 80 + (int)*(char **)(w->wheelDObj + 0x870));
                e->scale[2] = 1.0f;
            }
        }
        *(short *)(w->wheelDObj + 0x84C) = 2;

        /* the sub-object handle at 0x15C read through the TU's IntFloat union
           (alias set 0), as the wheel-float stores are: the ROM keeps the first
           handle load behind the 0x84C store above, which a plain int read,
           free to move past a short store, does not give */
        ((IntFloat *)&w->wheelHeight)->f =
            accessary[*(int *)(((IntFloat *)&self->dobj)->i + 0x844)].pivot[0];
        ((IntFloat *)&w->wheelFront)->f =
            accessary[*(int *)(((IntFloat *)&self->dobj)->i + 0x844)].pivot[1];
        ((IntFloat *)&w->wheelRear)->f =
            accessary[*(int *)(((IntFloat *)&self->dobj)->i + 0x844)].pivot[2];
    }
}

/* box.c:567-572 in the listing: inlined once, into action's case 0, so it is a
   static inline here; it has no symbol of its own in the ROM and no census row,
   and the name is descriptive.  10430.3779f is 65536 / (2 * pi), the repo's
   spelling of the radian-to-angle-table factor (ico2/seki/src/Primitive.c). */
static inline void updateBoxWheelAngle(GObj *self)
{
    BoxWork *p = GOBJ_SUB(self)->work;

    if (p->wheelDObj != 0) {
        p->wheelAngle = (short)((float)p->wheelAngle - p->vel[2] * 10430.3779f / p->wheelRadius);
    }
}

void dispWheels(GObj *a0)
{
    BoxWork *p = GOBJ_SUB(a0)->work;

    if (p->wheelDObj == 0) {
        return;
    }
    CopyMatrix(MatrixDrive_GetMatrix(), *(void **)&GOBJ_SUB(a0)->nodeMtx);
    MatrixDrive_TransMatrix(0.0f, p->wheelHeight, 0.0f);
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrix(0.0f, 0.0f, p->wheelFront);
    MatrixDrive_RotMatrixX(p->wheelAngle);
    CopyMatrix(*(void **)(p->wheelDObj + 0xC), MatrixDrive_GetMatrix());
    MatrixDrive_PopMatrix();
    MatrixDrive_TransMatrix(0.0f, 0.0f, p->wheelRear);
    MatrixDrive_RotMatrixX((short)(*(unsigned short *)&p->wheelAngle + 0x4000));
    CopyMatrix((char *)*(void **)(p->wheelDObj + 0xC) + 0x40, MatrixDrive_GetMatrix());
    p2o_DispVU1DObjMulti(p->wheelDObj);
}

/* one 16-byte route point */
typedef float PathPt[4];

/* The routes a box can be pushed along, box.o's .data after switch.c's
   lever template (VMA 0x4E5AB0..0x4E5F30): each a list of points ending in
   one whose fourth word is the largest float (countPathPoints stops at a
   fourth word of 10.0f or more).  Routes 9 and 18 to 29 are empty.  The
   names are ours: MAIN.MAP gives box.o's .data no symbols. */
static PathPt route1[] = {
    {-3380.0f, -3500.0f, 100.0f, 1.0f},  {-3380.0f, -3500.0f, 5700.0f, 1.0f},
    {-3337.0f, -3500.0f, 5890.0f, 1.0f}, {-3200.0f, -3500.0f, 6050.0f, 1.0f},
    {-3150.0f, -3500.0f, 6090.0f, 1.0f}, {-2930.0f, -3500.0f, 6150.0f, 1.0f},
    {-1000.0f, -3500.0f, 6150.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
};

static PathPt route2[] = {
    {0.0f, -50.0f, 0.0f, 1.0f},          {-300.0f, -50.0f, 0.0f, 1.0f},
    {-1000.0f, -50.0f, 700.0f, 1.0f},    {-1000.0f, -50.0f, 1400.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
};

static PathPt route3[] = {
    {-525.0f, 1450.0f, -1650.0f, 1.0f},
    {-1700.0f, 1450.0f, -1650.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
};

static PathPt route4[] = {
    {6500.0f, -3470.0f, -1450.0f, 1.0f},
    {6500.0f, -3470.0f, 3400.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
};

static PathPt route5[] = {
    {500.0f, 2650.0f, -2050.0f, 1.0f},
    {500.0f, 2650.0f, -2600.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
};

static PathPt route6[] = {
    {-2890.0f, -3510.0f, 6150.0f, 1.0f},
    {1000.0f, -3510.0f, 6150.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
};

static PathPt route7[] = {
    {-3400.0f, -3450.0f, -2300.0f, 1.0f}, {-3400.0f, -3450.0f, 5680.0f, 1.0f},
    {-3290.0f, -3450.0f, 6000.0f, 1.0f},  {-3000.0f, -3450.0f, 6150.0f, 1.0f},
    {1100.0f, -3450.0f, 6150.0f, 1.0f},   {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
};

static PathPt route8[] = {
    {-4750.0f, 650.0f, 3300.0f, 1.0f},
    {-4750.0f, 650.0f, 3900.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
};

static PathPt route9[] = {
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
};

static PathPt route10[] = {
    {-380.0f, -50.0f, -570.0f, 1.0f},
    {-220.0f, -50.0f, -570.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
};

static PathPt route11[] = {
    {-380.0f, -50.0f, -1370.0f, 1.0f},
    {-220.0f, -50.0f, -1370.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
};

static PathPt route12[] = {
    {-380.0f, -50.0f, -2170.0f, 1.0f},
    {-220.0f, -50.0f, -2170.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
};

static PathPt route13[] = {
    {-380.0f, -50.0f, -2970.0f, 1.0f},
    {-220.0f, -50.0f, -2970.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
};

static PathPt route14[] = {
    {380.0f, -50.0f, -570.0f, 1.0f},
    {220.0f, -50.0f, -570.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
};

static PathPt route15[] = {
    {380.0f, -50.0f, -1370.0f, 1.0f},
    {220.0f, -50.0f, -1370.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
};

static PathPt route16[] = {
    {380.0f, -50.0f, -2170.0f, 1.0f},
    {220.0f, -50.0f, -2170.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
};

static PathPt route17[] = {
    {380.0f, -50.0f, -2970.0f, 1.0f},
    {220.0f, -50.0f, -2970.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 3.40282347e+38f},
};

static PathPt route18[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}};

static PathPt route19[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}};

static PathPt route20[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}};

static PathPt route21[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}};

static PathPt route22[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}};

static PathPt route23[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}};

static PathPt route24[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}};

static PathPt route25[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}};

static PathPt route26[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}};

static PathPt route27[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}};

static PathPt route28[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}};

static PathPt route29[] = {{0.0f, 0.0f, 0.0f, 3.40282347e+38f}};

/* the route a box's layout names (the low half of its kind word) indexes
   this table; route 0 is no route and the last two slots are empty */
static PathPt *routeTable[32] = {
    0,       route1,  route2,  route3,  route4,  route5,  route6,  route7,  route8,  route9,
    route10, route11, route12, route13, route14, route15, route16, route17, route18, route19,
    route20, route21, route22, route23, route24, route25, route26, route27, route28, route29,
};

/* GetBoxHoldPoint's four hold-point candidates in the box's local frame and
   the four offsets added back after they are scaled by the box's half
   extents */
static float holdPointLocal[4][4] = {
    {0.0f, 0.0f, 50.0f, 1.0f},
    {50.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, -50.0f, 1.0f},
    {-50.0f, 0.0f, 0.0f, 1.0f},
};

static float holdPointOffset[4][4] = {
    {0.0f, 0.0f, 10.0f, 1.0f},
    {10.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, -10.0f, 1.0f},
    {-10.0f, 0.0f, 0.0f, 1.0f},
};

static BoxWork boxWorkInit = {
    0,
    0,
    {0},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0,
    1.0f,
    1.0f,
    0,
    0,
    {0},
    {0.0f, 0.0f, 0.0f, 0.0f},
    2,
    1,
    0,
    0,
    {{0, -1}, 0},
    {0},
    {{0.0f}},
    {0},
    {0.0f},
    {0.0f},
    {0.0f},
    {0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    10.0f,
    30.0f,
    50.0f,
    -50.0f,
    0.9f,
    0,
    {0},
    0,
    {0},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0,
    0,
    {0},
    {0.0f, 0.0f, 0.0f, 1.0f},
    0,
    {0},
    {0.0f, 0.0f, 1.0f, 0.0f},
};

/* the Y axis the side plane is built from */
static float yAxis[4] = {0.0f, 1.0f, 0.0f, 0.0f};

/* box.c:595-600 in the listing: inlined once, into InitBoxGeo, so it is a
   static inline here; it has no symbol of its own in the ROM and no census
   row, and the name is ours.  A route array ends at the first point whose
   fourth word is 10.0f or more. */
static inline int countPathPoints(int route)
{
    PathPt *pts = routeTable[route];
    int i;

    for (i = 1; pts[i][3] < 10.0f; i++) {}

    return i;
}

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
    PathPt *pts = routeTable[path[0]];
    float best = 3.40282347e+38f;
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
        sceVu0OuterProduct(pl, yAxis, dir);
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

void onPathInitialize(GObj *a0)
{
    BoxWork *p = GOBJ_SUB(a0)->work;
    float front[4];
    float rear[4];
    /* The wheel offset is one variable assigned on each wheel's line. What the
       bytes pin: 50.0f and -50.0f share one register, the -50.0f load waits
       for the front multiply (listing rows 680 and 681), which two separate
       constants never give (measured: 50.0f in $f1, 1.0f in $f2, -50.0f
       hoisted into $f3; `-ofs` gives a neg.s). What they cannot pin: the
       variable's name and the row its declaration sat on. */
    float ofs;
    Vec16 fv = {{0.0f, 0.0f, p->scaleZ * (ofs = 50.0f), 1.0f}};
    Vec16 rv = {{0.0f, 0.0f, p->scaleZ * (ofs = -50.0f), 1.0f}};
    float quat[4];

    p->frontPoint = p->rearPoint = -1;
    sceVu0ApplyMatrix(front, (void *)GOBJ_SUB(a0)->nodeMtx, &fv);
    sceVu0ApplyMatrix(rear, (void *)GOBJ_SUB(a0)->nodeMtx, &rv);
    getNearestPosition(front, (int *)&p->frontPoint, (int *)&p->route);
    getNearestPosition(rear, (int *)&p->rearPoint, (int *)&p->route);
    debug_StdPrintfDummy("front pos: %f, %f, %f\n", front[0], front[1], front[2]);
    debug_StdPrintfDummy("rear  pos: %f, %f, %f\n", rear[0], rear[1], rear[2]);
    if (distance_squared(front, rear) < 0.010000001f) {
        GetRootQuaternion(quat, a0);
        RotQuaternionY(quat, 16384);
        SetRootQuaternion(a0, quat);
        UpdateRootMatrix(a0);
    }
}

/* kept local: this TU's uses of these do not fit the prototypes in the headers
   that declare them */

/* the debug switch the wall-fit trace is printed under */

/* the four trace lines, rodata VMA 0x61EFC0, 0x61EFD0, 0x61EFE0 and 0x61EFF0 */

/* the two route colours onPath draws the route and its end points in, one
   word per channel, RGBA */
static int routeFrontColor[4] = {0, 128, 255, 128};

static int routeRearColor[4] = {255, 128, 0, 128};

/* box.c:710-813 in the listing.  10430.378 is 32768 / pi, the repo's spelling
   of the radian-to-angle-table factor.  Rows 718, 720 and 721 are the three
   initialised declarations: the quaternion's mostly-zero initialiser clears
   with memset and stores w, and each wheel offset is built in a temporary and
   block-copied, as onPathInitialize's are; the offsets are VECTOR records, whose
   one clobber (a union initialiser emits two) lets the stores clear early
   enough for the ROM's schedule. */
int onPath(GObj *self)
{
    BoxWork *p = GOBJ_SUB(self)->work;
    Vec4 front;
    Vec4 rear;
    float q[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    VECTOR fwd = {0.0f, 0.0f, p->scaleZ * 50.0f, 1.0f};
    VECTOR bwd = {0.0f, 0.0f, p->scaleZ * -50.0f, 1.0f};
    PathPt *pts = routeTable[p->route];
    Vec4 mid;
    Vec4 ofs;
    float m[16];
    Vec4 dir;
    int hitFront;
    int hitRear;
    int i;

    sceVu0ApplyMatrix(&front, (void *)GOBJ_SUB(self)->nodeMtx, &fwd);
    sceVu0ApplyMatrix(&rear, (void *)GOBJ_SUB(self)->nodeMtx, &bwd);

    hitFront = getNearestPosition(front.f, (int *)&p->frontPoint, (int *)&p->route);
    hitRear = getNearestPosition(rear.f, (int *)&p->rearPoint, (int *)&p->route);

    RotQuaternionY(q, (short)(atan2f(front.f[0] - rear.f[0], front.f[2] - rear.f[2]) * 10430.378f));
    SetRootQuaternion(self, q);

    if (hitFront != 0 || hitRear != 0) {
        if (hitFront != 0) {
            GetMatrixFromQuaternion(m, q);
            CopyVector(&ofs, &bwd);
            ofs.f[2] -= 1.0f;
            sceVu0ApplyMatrix(&ofs, m, &ofs);
            AddVectorXYZ(&mid, &front, &ofs);
        } else {
            GetMatrixFromQuaternion(m, q);
            CopyVector(&ofs, &fwd);
            ofs.f[2] += 1.0f;
            sceVu0ApplyMatrix(&ofs, m, &ofs);
            AddVectorXYZ(&mid, &rear, &ofs);
        }

        if (2.0f < (p->vel[2] < 0.0f ? -p->vel[2] : p->vel[2])) {
            p->stopWall = 1;
        }

        if (hitFront != 0) {
            _SubVectorXYZ(&dir, &front, (char *)GOBJ_SUB(self)->nodeMtx + 0x30);
            debug_StdPrintfDummy("hit with front\n");
        }
        if (hitRear != 0) {
            _SubVectorXYZ(&dir, &rear, (char *)GOBJ_SUB(self)->nodeMtx + 0x30);
            debug_StdPrintfDummy("hit with rear\n");
        }
        _NormalizeVector(&dir, &dir);
        if (0.0f < _InnerProduct(&dir, p->moveDir)) {
            debug_StdPrintfDummy("se stopped\n");
            stopBoxMoveSE(self);
            p->seStopped = 1;
        } else {
            debug_StdPrintfDummy("but different orient, then se not stop\n");
        }

        mid.f[1] = front.f[1];
    } else {
        sceVu0AddVector(&mid, &front, &rear);
        sceVu0ScaleVector(&mid, &mid, 0.5f);
    }

    mid.f[3] = 1.0f;
    SetDirectRootPosition(self, &mid);

    UpdateRootMatrix(self);

    if (debug_skel_flag != 0) {
        gif_StartPacketPri(11);
        gif_SetZWrite(0);
        gif_SetZTest(1);
        sceVu0UnitMatrix(MatrixDrive_GetMatrix());
        for (i = 1; pts[i][3] < 10.0f; i++) {
            DrawLineG(pts[i - 1], routeFrontColor, pts[i], routeFrontColor, -1);
        }
        CopyMatrix(MatrixDrive_GetMatrix(), (void *)GOBJ_SUB(self)->nodeMtx);
        MatrixDrive_TransMatrix(0.0f, 0.0f, p->scaleZ * 50.0f);
        prim_DispWireSphere(10.0f, routeFrontColor, 4, 4);
        CopyMatrix(MatrixDrive_GetMatrix(), (void *)GOBJ_SUB(self)->nodeMtx);
        MatrixDrive_TransMatrix(0.0f, 0.0f, p->scaleZ * -50.0f);
        prim_DispWireSphere(10.0f, routeRearColor, 4, 4);
        gif_EndPacket();
    }

    return hitFront | hitRear;
}

/* No caller in the ROM, so the bytes cannot decide the return type: float as sugipon's scalar getters. */
inline float GetDistanceOfGObj(void *a0, void *a1)
{
    float v[4];
    float w[4];
    GetRootPosition(v, a1);
    GetRootPosition(w, a0);
    sceVu0SubVector(v, v, w);
    return FSqrt(sceVu0InnerProduct(v, v));
}

extern void GetFloatingMotion(void *mot, void *dir, int *m, int a3, int t0, int t1, float t);

int playAnimationCore(GObj *a0)
{
    float mot[4];
    float rot[4];
    float dir[4];
    float pos[4];
    float q[4];
    BoxWork *p = GOBJ_SUB(a0)->work;

    GetFloatingMotion(mot, dir, motionTable[GOBJ_SUB(a0)->ctrl.motion], 1, 0, 0,
                      GOBJ_SUB(a0)->ctrl.animFrame);
    dir[3] = 1.0f;
    sceVu0ApplyMatrix(pos, p->mtx[0], dir);
    CopyQuaternion(q, GOBJ_SUB(a0)->root.baseQuat);
    MultiQuaternion(q, q, rot);
    RotQuaternionX(q, -32768);
    RotQuaternionY(q, -16384);
    MultiQuaternion(q, q, GOBJ_SUB(a0)->root.motionQuat);
    SetRootQuaternion(a0, q);
    sceVu0SubVector(&GOBJ_SUB(a0)->root.move[0], pos, GOBJ_SUB(a0)->root.last);
    CopyVector(GOBJ_SUB(a0)->root.last, pos);
    SetRootPosition(a0, pos);
    ExecFrameDependSequence(a0);
    return UpdateFrameCounter(a0);
}

/* box.c:867-877 in the listing: inlined once, into execFallDown's case 3, so it
   is a static inline here; it has no symbol of its own in the ROM and no census
   row, and the name is descriptive.  The frame-rate divisor is the one
   moveBoxAutoMatic uses, written twice and shared by cse. */
static inline void execBoxFall(GObj *self)
{
    float v[4];

    GetRootPosition(v, self);
    ((IntFloat *)(*(char **)(((char *)self) + 0x15C) + 0x134))->f +=
        60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 0.5f *
        (60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]));
    AddVectorXYZ(v, v, *(char **)(((char *)self) + 0x15C) + 0x130);
    SetRootPosition(self, v);
    if (LimitExistGeometry(v, *(char **)(((char *)self) + 0x15C) + 0x130) != 0) {
        ((BoxWork *)GOBJ_SUB(self)->work)->mode = -1;
    }
}

/* the local Z axis the floating box's facing is rebuilt from */
static float floatFacingAxis[4] = {0.0f, 0.0f, 1.0f, 0.0f};

/* box.c:882-951 in the listing.  0.31830987 is 1 / pi and the ROM keeps two
   copies of it, one per arm of the sign test, the way it keeps two copies of
   every other constant that appears once in each arm. */
int MoveFloatingBox(GObj *self, GObj *other, float *dst, void *src, float lim)
{
    float pos[4];
    float opos[4];
    float tp[4];
    float m[16];
    BoxWork *w = GOBJ_SUB(self)->work;
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
        MatrixDrive_RotMatrixY(
            GetTableArcTan2(GOBJ_SUB(self)->ctrl.dir[0], GOBJ_SUB(self)->ctrl.dir[2]));
        MatrixDrive_RotMatrixY(ang);
        sceVu0ApplyMatrix(GOBJ_SUB(self)->ctrl.dir, MatrixDrive_GetMatrix(), floatFacingAxis);

        SetRootPosition(self, pos);

        opos[0] = opos[0] - dx * 0.05f;
        opos[2] = opos[2] - dz * 0.05f;
        SetRootPosition(other, opos);
    }

    GetCylinderCollisionWithExceptOwnCollision(self, other, 70.0f, 50.0f, 0.5f, 0.5f, 0);

    w->charHit = 1;
    return 1;
}

/* the eight horizontal push-out directions the floating box is tested along */
static float floatPushDir[8][4] = {
    {0.0f, 0.0f, 1.0f, 1.0f},  {0.0f, 0.0f, -1.0f, 1.0f},  {1.0f, 0.0f, 0.0f, 1.0f},
    {-1.0f, 0.0f, 0.0f, 1.0f}, {-1.0f, 0.0f, -1.0f, 1.0f}, {1.0f, 0.0f, -1.0f, 1.0f},
    {1.0f, 0.0f, 1.0f, 1.0f},  {-1.0f, 0.0f, 1.0f, 1.0f},
};

/* box.c:965-988 in the listing: inlined once, into execFloating, so it is a
   static inline here; it has no symbol of its own in the ROM and no census
   row, and the name is descriptive.  The clip work, the matrix and the two
   scratch vectors are the CALLER's: the ROM's frame places them among
   execFloating's own locals, ahead of the word whose address goes to
   GetWaterReaction. */
static inline void pushOutFloatingBox(ClipBuf *cw, float *m, float *sv, float *dv, float *pos,
                                      float *q, float r)
{
    float *dir;
    float len;
    int i;

    memset(cw, 0, sizeof(ClipBuf));
    /* the counter is only read by the test, so loop.c reverses it: the ROM
       counts down from 7 while the direction pointer still walks up. */
    for (i = 0, dir = floatPushDir[0]; i < 8; i++, dir += 4) {
        CopyVector(cw->pt[0], pos);
        GetMatrixFromQuaternionPos(m, q, pos);
        _ScaleVectorXYZ(sv, dir, r);
        _ApplyMatrix(cw->pt[1], m, sv);
        ClipWall(cw);
        if (cw->wall.n != 0) {
            _SubVectorXYZ(dv, cw->pt[2], cw->pt[1]);
            len = VectorLengthSquare(dv);
            if (1.0f < len) {
                _ScaleVector(dv, dv, 1.0f / _Sqrt(len));
            }
            _AddVectorXYZ(pos, pos, dv);
        }
    }
}

/* The same prototype fieldCollision.h gives; dropping this redeclaration moves
   avoidCharGObj's w+0x88 load from $2 to $3 (measured, complete66 row). */

void avoidCharGObj(GObj *a0, GObj *a1)
{
    ClipBuf w;
    float pos[4];
    int hit;

    w.rad = (30.0f < GOBJ_SUB(a1)->root.radius) ? GOBJ_SUB(a1)->root.radius : 30.0f;
    GetRootPosition(pos, a1);
    pos[1] += GOBJ_SUB(a1)->root.projHeight + 10.0f;
    CopyVector(&w, pos);
    CopyVector(w.pt[1], pos);
    w.filter.o.obj = a0;
    w.filter.o.node = -1;
    w.filter.n = 0;
    ClipWallE(&w);
    if (w.wall.n != 0) {
        switch (GOBJ_SUB(a1)->ctrl.rootUpdateMode) {
        case 7:
        case 8:
        case 10:
        case 15:
        case 16:
            hit = (char *)GOBJ_SUB(a1)->root.wall.o.obj == a0;
            break;
        default:
            hit = 1;
            break;
        }
        if (hit != 0) {
            GetCylinderCollisionWithExceptOwnCollision(a0, a1, (w.rad + 50.0f) * 1.414f, 100.0f,
                                                       0.5f, 0.0f, 1);
            UpdateRootMatrix(a0);
        }
    }
}

/* kept local: this TU's uses of these do not fit the prototypes in
   motionManager2.h, quaternion.h and stageMultiBgaManager.h */
extern int GetWaterReaction(void *w, int *hit, void *plane, void *pos, void *vel, float low,
                            float mid, float high, float k, float acc);

/* the two characters the floating box has to keep clear of, the boy and the
   girl, as sceneManager.c sets them */

/* the world Y axis the box's tilt is measured around */
static float floatTiltAxis[4] = {0.0f, 1.0f, 0.0f, 0.0f};

void execFloating(GObj *self)
{
    ClipBuf fw;
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
    ClipBuf cw;
    float cm[16];
    float sv[4];
    float dv[4];
    int hit;
    BoxWork *w = GOBJ_SUB(self)->work;
    float len;
    float r;

    if (boyGObj != 0) {
        if (w->charHit == 0) {
            GetCylinderCollisionWithExceptOwnCollision(self, boyGObj, 50.0f, 50.0f, 0.0f, 1.0f, 1);
            avoidCharGObj(self, boyGObj);
        }
    }
    if (girlGObj != 0) {
        GetCylinderCollisionWithExceptOwnCollision(self, girlGObj, 70.700005f, 50.0f, 0.0f, 1.0f,
                                                   1);
        avoidCharGObj(self, girlGObj);
    }
    GetRootPosition(pos, self);
    GetLowerPlaneCollision(&fw, pos);
    len = VectorLengthSquare(GOBJ_SUB(self)->root.move);
    if (100.0f < len) {
        _ScaleVectorXYZ(GOBJ_SUB(self)->root.move, GOBJ_SUB(self)->root.move, 3.0f / _Sqrt(len));
    }
    /* the three water-probe heights are written as additions of the offset, not
       as subtractions: the ROM adds -50.0f and -25.0f and gcc 2.9 emits sub.s
       for a written subtraction (line 1128 below is one). */
    if (GetWaterReaction(w->waterHeight, &hit, &fw, pos, GOBJ_SUB(self)->root.move, pos[1] + -50.0f,
                         pos[1] + -25.0f, pos[1] + 50.0f, 0.9f,
                         60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * -0.1f *
                             (60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1])) *
                             3.0f) != 0) {
        if (fw.pt[2][1] - 50.0f < pos[1]) {
            pos[1] = fw.pt[2][1] - 50.0f;
        }
        _SubVector(d, pos, w->floatAnchor);
        d[1] = 0.0f;
        /* 0.1f * 0.1f, not 0.01f: the pool word is 0x3C23D70B, one ulp above
           the float nearest 0.01. */
        if (0.1f * 0.1f < VectorLengthSquare(d)) {
            _SubVector(d, pos, w->floatAnchor);
            w->floatAnchor[0] = pos[0];
            w->floatAnchor[2] = pos[2];
        } else {
            pos[0] = w->floatAnchor[0];
            pos[2] = w->floatAnchor[2];
        }
        memset(g, 0, 0x10);
        g[1] = -35.0f;
        sceVu0ScaleVectorXYZ(acc, w->tilt, -0.01f);
        sceVu0AddVector(w->tiltVel, w->tiltVel, acc);
        sceVu0AddVector(w->tiltVel, w->tiltVel, w->tiltForce);
        sceVu0ScaleVectorXYZ(w->tiltVel, w->tiltVel, 0.95f);
        sceVu0AddVector(w->tilt, w->tilt, w->tiltVel);
        sceVu0OuterProduct(axis, floatTiltAxis, w->tilt);
        CopyQuaternion(q, IdentityQuaternion);
        RotQuaternionY(q,
                       GetTableArcTan2(GOBJ_SUB(self)->ctrl.dir[0], GOBJ_SUB(self)->ctrl.dir[2]));
        SetQuaternionByAxisRotateV(rot, (short)(VectorLength(w->tilt) * 20.48f / 50.0f), axis);
        MultiQuaternion(q, q, rot);
        SetRootQuaternion(self, q);
        GetMatrixFromQuaternion(m, rot);
        sceVu0ApplyMatrix(ofs, m, g);
        ofs[1] = 0.0f;
        sceVu0SubVector(sub, ofs, w->lastOffset);
        sceVu0SubVector(pos, pos, sub);
        CopyVector(w->lastOffset, ofs);
        r = w->scaleX > w->scaleZ ? w->scaleX * 50.0f : w->scaleZ * 50.0f;
        pushOutFloatingBox(&cw, cm, sv, dv, pos, q, r);
        _AddVectorXYZ(cw.pt[0], pos, ofs);
        cw.pt[0][3] = 0.0f;
        _SubVector(GOBJ_SUB(self)->root.move, cw.pt[0], w->lastPos);
        GOBJ_SUB(self)->root.move[3] = 0;
        CopyVector(w->lastPos, cw.pt[0]);
        SetRootPosition(self, pos);
    }
    GOBJ_SUB(self)->root.move[1] += GetTableSin(w->floatPhase) * 0.1f;
    w->floatPhase += 2048;
    w->charHit = 0;
    if (w->floatPhase == 0) {
        CopyVector(cw.pt[0], pos);
        cw.pt[0][1] = w->waterHeight[0];
        EntryStageMultiBgaManager(491, cw.pt[0], IdentityQuaternion);
    }
}

/* the facing a floating box starts with */
static float floatInitFacing[4] = {0.0f, 0.0f, 1.0f, 0.0f};

void initFloating(GObj *a0)
{
    BoxWork *p = GOBJ_SUB(a0)->work;

    GOBJ_SUB(a0)->colData = p->effectDObj->colData;
    GOBJ_SUB(a0)->colRotate = 1;
    CopyQuaternion(GOBJ_SUB(a0)->root.baseQuat, IdentityQuaternion);
    SetRootQuaternion(a0, IdentityQuaternion);
    CopyVector(p->lastOffset, ZeroVector);
    CopyVector(p->tilt, ZeroVector);
    CopyVector(p->tiltVel, ZeroVector);
    GetRootPosition(p->lastPos, a0);
    CopyVector(GOBJ_SUB(a0)->ctrl.dir, floatInitFacing);
    p->floatPhase = 0;
    execFloating(a0);
}

int _checkItemBreak(void *pos)
{
    float p[4];
    float d[4];
    GObj *o;

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

void initLanding(GObj *a0)
{
    float pos[4];
    float plane[4];
    float v[4];
    BoxWork *p = GOBJ_SUB(a0)->work;

    GetRootPosition(pos, a0);
    CopyVector(&GOBJ_SUB(a0)->root.move[0], ZeroVector);
    *(int *)&GOBJ_SUB(a0)->ctrl.animFrame = 0;
    GOBJ_SUB(a0)->ctrl.motion = 1144;
    if (p->wall.n != 0) {
        float d;

        GetPureVerticalPlane(0, plane, 0, (int *)&p->wall, 1);
        d = GetDistanceFromPlane(plane, pos);
        plane[3] = 0.0f;
        sceVu0ScaleVectorXYZ(v, plane, -(d - 50.0f));
        AddVectorXYZ(pos, pos, v);
    }
    _checkItemBreak(pos);
    GetMatrixFromQuaternionPos(p->mtx[0], GOBJ_SUB(a0)->root.baseQuat, (char *)pos);
}

/* box.c:1308-1313 and 1315-1321 in the listing: both are inlined once, into
   action's case 4 (the inner one inside the outer one), so they are static
   inlines here; neither has a symbol of its own in the ROM or a census row, and
   the names are descriptive. */
static inline void resetBoxRootQuaternion(GObj *self, float *q)
{
    GetInverseQuaternion(q, (char *)GOBJ_SUB(self) + 0x60);
    SetRootQuaternion(self, q);
    GOBJ_SUB(self)->colRotate = 1;
}

static inline void playBoxAnimation(GObj *self, float *q)
{
    if (playAnimationCore(self) != 0) {
        BoxWork *p = GOBJ_SUB(self)->work;

        p->mode = 0;
        resetBoxRootQuaternion(self, q);
    }
}

/* box.c:1325-1339 in the listing: inlined once, into execFallDown, so it is a
   static inline here; it has no symbol of its own in the ROM and no census row,
   and the name is descriptive. */
static inline void attackBoxFallCenter(GObj *self)
{
    float plane[4];
    float pos[4];
    BoxWork *q = GOBJ_SUB(self)->work;

    if (q->wall.n != 0) {
        GetPureVerticalPlane(0, plane, 0, (int *)&q->wall, 1);
        plane[3] = 0.0f;
        GetRootPosition(pos, self);
        pos[1] += 50.0f;
        AttackCenter_WithDir(self, 17, pos, plane, 60.0f);
    }
}

void execFallDown(GObj *a0)
{
    BoxWork *p = GOBJ_SUB(a0)->work;

    switch (p->mode) {
    case 2:
        if (playAnimationCore(a0) != 0) {
            p->mode = 3;
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
        p->mode = 4;
        landingSE(a0);
        break;
    case 2:
        initFloating(a0);
        p->mode = 5;
        landingSE(a0);
        break;
    }
}

void inertiaMove(GObj *a0)
{
    float pos[4];
    float tmp[4];
    ClipBuf w;
    float base[4];
    BoxWork *p = GOBJ_SUB(a0)->work;

    if (onPath(a0) != 0) {
        CopyVector(p->vel, ZeroVector);
    }
    GetRootPosition(pos, a0);
    sceVu0ScaleVectorXYZ(p->vel, p->vel, p->friction);
    sceVu0ApplyMatrix(tmp, (void *)GOBJ_SUB(a0)->nodeMtx, p->vel);
    sceVu0AddVector(pos, pos, tmp);
    SetRootPosition(a0, pos);
    checkBoxWallHit(a0, &w, base, pos, 1);
    if (w.wall.n != 0) {
        SetRootPosition(a0, pos);
        CopyVector(p->vel, ZeroVector);
    }
}

inline int IsThisBoxTruck(GObj *a0)
{
    BoxWork *p = GOBJ_SUB(a0)->work;

    return p->route;
}

void action(GObj *a0)
{
    /* the float view carries the up vector; the union is what the ROM's
       schedule needs, its alias-set-0 store keeping the matrix read after it */
    Vec4u v;
    BoxWork *p = GOBJ_SUB(a0)->work;

    switch (p->mode) {
    case 0:
        if (p->route != 0) {
            inertiaMove(a0);
            updateBoxWheelAngle(a0);
            memset(&v, 0, 16);
            v.f[2] = 1.0f;
            _ApplyMatrix(GOBJ_SUB(a0)->ctrl.dir, (void *)GOBJ_SUB(a0)->nodeMtx, &v);
        }
        CopyVector(GOBJ_SUB(a0)->root.move, ZeroVector);
        break;
    case 1:
    case 6:
        execAutoMove(a0);
        CopyVector(GOBJ_SUB(a0)->root.move, ZeroVector);
        break;
    case 2:
    case 3:
        execFallDown(a0);
        break;
    case 4:
        playBoxAnimation(a0, v.f);
        CopyVector(GOBJ_SUB(a0)->root.move, ZeroVector);
        break;
    case 5:
        execFloating(a0);
        break;
    case -1:
    default:
        debug_StdPrintfDummy("box die!!!\n");
        CopyVector(GOBJ_SUB(a0)->root.move, ZeroVector);
        break;
    }
    if (p->mode != 6) {
        if (*(int *)(p->subGObj + 0x16C) != 0) {
            *(int *)(p->subGObj + 0x16C) = 0;
        }
    }
}

inline void GetBoxGlobalHoldPoint(void *a0, void *a1, void *a2)
{
    float buf[16];
    GetRootMatrix(buf, a1);
    sceVu0ApplyMatrix(a0, buf, a2);
}

/* box.c:1477-1520 in the listing.  The clip work buffer is declared in a block
   of its own after the candidate loop: the ROM's frame puts it at sp+0x60,
   above the 64-byte matrix the inlined GetBoxGlobalHoldPoint keeps at sp+0x20,
   so it is allocated after the first inlining and not with the function's
   top-level locals.  The two squared-distance spellings are the listing's:
   sugiCommon.h:97 in the first iteration, sugiCommon.h:87 in the rest. */
int GetBoxHoldPoint(float *out, GObj *self, void *chara)
{
    float pos[4];
    float p[4];
    BoxWork *q = GOBJ_SUB(self)->work;
    int best = 0;
    float min = 0.0f;
    float d;
    int i;

    GetRootPosition(pos, chara);
    for (i = 0; i < 4; i++) {
        GetBoxGlobalHoldPoint(p, self, holdPointLocal[i]);
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
    CopyVector(out, holdPointLocal[best]);
    out[0] *= q->scaleX;
    out[2] *= q->scaleZ;
    AddVectorXYZ(out, out, holdPointOffset[best]);
    q->holder = chara;
    CopyVector(q->holdPoint, out);
    {
        ClipBuf w;

        memset(&w, 0, 0xC0);
        GetBoxGlobalHoldPoint(w.pt[1], self, ZeroPoint);
        GetBoxGlobalHoldPoint(&w, self, out);
        ClipWall(&w);
        if (w.wall.n != 0) {
            if (CompareAttribute(GetWallAttribute(&w), 0xB00) ||
                CompareAttribute(GetWallAttribute(&w), 0x400)) {
                return 0;
            }
        }
    }
    return 1;
}

inline int CanHoldBox(GObj *a0)
{
    BoxWork *p = GOBJ_SUB(a0)->work;

    return p->mode == 0;
}

static inline void setupClipWork(ClipBuf *w, GObj *obj, float *dir, float len, float h)
{
    float t[4];

    _ScaleVector(t, dir, len);
    GetRootPosition(w->pt[0], obj);
    w->pt[0][1] += h;
    _AddVectorXYZ(w->pt[1], w->pt[0], t);
}

static inline int checkBoxStopWall(GObj *obj, float *dir)
{
    ClipBuf w;
    int r = 1;

    memset(&w, 0, 0xC0);
    setupClipWork(&w, obj, dir, 145.0f, 40.0f);
    ClipWallBoxStop(&w);
    if (w.wall.n != 0) {
        r = 0;
    }
    return r;
}

static inline int checkMoveWall(GObj *obj, float *dir)
{
    ClipBuf w;
    int r = 1;

    memset(&w, 0, 0xC0);
    setupClipWork(&w, obj, dir, 245.0f, 0.0f);
    ClipWall(&w);
    if (w.wall.n != 0) {
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

static inline int checkCharGObjs(GObj *obj, GObj *holder, float *dir)
{
    float pos[4];
    float pos2[4];
    float d[4];
    GObj **list;
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
            if (move(d, w + w, w, GOBJ_SUB(*list)->root.radius + 5.0f) != 0) {
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
    GObj *o;

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

static inline int checkItemHit(GObj *obj, float *dir)
{
    float pos[4];
    float d[4];
    float to[4];

    _ScaleVectorXYZ(d, dir, 100.0f);
    GetRootPosition(pos, obj);
    _AddVectorXYZ(to, pos, d);
    return _checkItemCollision(to);
}

int moveBoxAutoMatic(GObj *a0, int a1)
{
    float v[4];
    float v2[4];
    BoxWork *p = GOBJ_SUB(a0)->work;
    float t = 30.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
    float w = t * t;
    int r;

    switch (a1) {
    default:
        p->friction = 0.85f;
        AddVectorXYZ(p->vel, p->vel, ZeroVector);
        break;
    case 1:
        memset(v, 0, 16);
        v[2] = w * 0.5f;
        p->friction = 0.98f;
        AddVectorXYZ(p->vel, p->vel, v);
        break;
    case -1:
        memset(v2, 0, 16);
        v2[2] = w * -0.5f;
        p->friction = 0.98f;
        AddVectorXYZ(p->vel, p->vel, v2);
        break;
    }
    if (p->autoDir != a1) {
        StopSEPackageWithGroupVariation(a0, 1);
        if (a1 != 0) {
            ExecuteSEPackageWithGroupVariation(a0, 29, 1);
        }
    }
    p->autoDir = a1;
    if (onPath(a0) != 0) {
        CopyVector(p->vel, ZeroVector);
    }
    UpdateRootMatrix(a0);
    r = execNormalMove(a0, 1);
    UpdateRootMatrix(a0);
    return r;
}

int MoveBoxWithHoldPoint(GObj *a0, void *a1, GObj *a2, int a3, float *a4)
{
    float plane[4];
    float nv[4];
    float hp[4];
    float pos[4];
    float mv[4];
    BoxWork *q = GOBJ_SUB(a0)->work;
    int idx;
    int hit;
    float dot;
    float dist;

    CopyVector(q->moveDir, a4);
    GetBoxGlobalHoldPoint(hp, a0, a1);
    GetRootPosition(pos, a0);
    sceVu0SubVector(nv, hp, pos);
    sceVu0Normalize(nv, nv);

    dot = sceVu0InnerProduct(nv, hp);
    SetSimplePlane(plane, nv[0], nv[1], nv[2], -dot);

    idx = GetSkeltonFocusNode(a2, a3);
    dist = GetDistanceFromPlane(plane, (char *)GOBJ_SUB(a2)->nodeMtx + (idx << 6) + 0x30);

    sceVu0ScaleVector(mv, nv, dist);

    if (((BoxWork *)GOBJ_SUB(a0)->work)->route != 0) {
        float m[16];

        _ScaleVector(mv, mv, 0.05f);
        MatrixDrive_SetTransposeMatrix(m, (void *)GOBJ_SUB(a0)->nodeMtx);
        sceVu0ApplyMatrix(mv, m, mv);
        AddVectorXYZ(q->vel, q->vel, mv);
        if (onPath(a0) != 0) {
            CopyVector(q->vel, ZeroVector);
        }
        if (stage_no == 8) {
            if (q->serial == 0 && q->seStopped == 0) {
                pushStartSE(a0);
            }
        }
        ReviveCarryableItemsWithBoundary(pos, 100.0f);
    } else if (checkCharGObjs(a0, a2, a4) && checkBoxStopWall(a0, a4) &&
               CheckGeneratorCollision(a0, a4) && checkItemHit(a0, a4)) {
        q->moveFrames = (0x3C - systemStatus[0] * 0xA) / systemStatus[1] *
                        (GetNbMotionFrames(GOBJ_SUB(a2)->ctrl.motion) - 1) / 0x1E;
        _ScaleVectorXYZ(q->vel, a4, 100.0f / (float)q->moveFrames);

        hit = checkMoveWall(a0, a4);
        if (hit) {
            q->mode = 1;
        } else {
            float npos[4];
            float d[4];

            GetRootPosition(npos, a0);
            _ScaleVector(d, a4, 100.0f);
            _AddVectorXYZ(npos, npos, d);
            q->mode = 6;
            alignPosition(a0, npos, npos, 100.0f);
            npos[1] -= 1.0f;
            debug_StdPrintfDummy("near wall to %f, %f, %f\n", npos[0], npos[1], npos[2]);
            CopyVector(*(char **)(*(char **)(q->subGObj + 0x15C) + 0xC) + 0x30, npos);
            *(int *)(q->subGObj + 0x16C) = 1;
        }
        if (GOBJ_SUB(a2)->ctrl.cliffWallHit != 0) {
            q->wall = GOBJ_SUB(a2)->root.cliffWall;
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

inline int BoxRideFunc(ObjNode *a0, GObj *a1)
{
    GObj *obj = a0->obj;
    Sub15C *p15c = GOBJ_SUB(obj);
    BoxWork *s0 = p15c->work;
    char buf[32];
    if (s0->mode != 5) {
        return 0;
    }
    p15c->root.move[1] += 0.5f;
    GetRootPosition(buf + 0x10, obj);
    CopyVector(buf, GOBJ_SUB(a1)->root.pos);
    *(int *)(buf + 4) = 0;
    sceVu0AddVector(s0->tiltVel, s0->tiltVel, buf);
    return 1;
}

inline void ExecBoxMoveStartReaction(GObj *a0, int a1)
{
    BoxWork *q = GOBJ_SUB(a0)->work;
    if (q->route != 0) {
        if (q->moving != 0) {
            goto end;
        }
    }
    if (a1 >= 0) {
        pushStartSE(a0);
        q->seStopped = 0;
    } else {
        pullStartSE(a0);
        q->seStopped = 0;
    }
end:
    q->moving = 1;
}

inline void ExecBoxMoveEndReaction(GObj *a0)
{
    BoxWork *q = GOBJ_SUB(a0)->work;
    if (q->route == 0 || q->moving != 0) {
        stopBoxMoveSE(a0);
    }
    q->moving = 0;
}

void ReInitBoxGeo(GObj *a0)
{
    BoxWork *p = GOBJ_SUB(a0)->work;

    debug_StdPrintfDummy("BOXREINIT\n");
    GOBJ_SUB(a0)->colData = p->colData;
    if (checkFieldContact(a0, 100000.0f) == 0) {
        /* EUC-JP: "the box is placed where there is no ground; its behaviour cannot be guaranteed (is the box before the collision definition?)" */
        debug_StdPrintfDummy(
            "\033[36m箱が地面の無いところに初期配置されています。\n動作が保証できません(コリジョン定義より前に箱がありませんか?)\033[m\n");
    } else {
        int m = GOBJ_SUB(a0)->ctrl.floorAttr;

        if (m == 0x40 || m == 0x50) {
            initFloating(a0);
            p->mode = 5;
            /* EUC-JP: "box initially placed on the water bottom" */
            debug_StdPrintfDummy("箱初期水底配置\n");
        } else {
            p->mode = 0;
            AlignBox(a0, 100.0f);
            execNormalMove(a0, 1);
            /* EUC-JP: "box initially placed normally" */
            debug_StdPrintfDummy("箱初期通常配置\n");
        }
    }
    UpdateRootMatrix(a0);
}

/* the box serial counter, the TU's one named .sdata object (after
   getNearestPosition's FLT_MAX pool word, before InitBoxGeo's "%d\n"), and the
   empty layout record the effect DObj is built from (sceneManager's data at
   VMA 0x4E45C0) */
static unsigned char boxSerial = 0; /* derived name */

/* The 64-byte layout record InitBoxGeo is handed; the word at 0x30 packs the
   route number in its low half and the sub-box model in its high half. */
typedef struct {
    char pad00[32];
    float scale[4]; /* 0x20 */
    int kind;       /* 0x30 */
    char pad34[12];
} __attribute__((aligned(8))) BoxLayout;

/* The parent-link record LinkParentOfDObj copies as one word pair: the
   parent GObj and the node index. */
typedef struct {
    int gobj;  /* 0x0 */
    int index; /* 0x4 */
} BoxLink;

/* box.c:2014-2102 in the listing. */
BoxWork *InitBoxGeo(GObj *self, BoxLayout *lay)
{
    BoxWork *w = iosMallocDebug(ios_partition_sugipon, 416, __FILE__, 2017);
    char *o;
    char *g;
    int sub;

    GOBJ_SUB(self)->work = w;

    *w = boxWorkInit;

    w->serial = boxSerial;
    boxSerial = (boxSerial + 1) % 30;

    ((IntFloat *)&w->scaleX)->f = lay->scale[0];
    ((IntFloat *)&w->scaleZ)->f = lay->scale[2];
    ((IntFloat *)((char *)GOBJ_SUB(self)->nodes + 0x20))->f =
        ((IntFloat *)((char *)GOBJ_SUB(self)->nodes + 0x24))->f =
            ((IntFloat *)((char *)GOBJ_SUB(self)->nodes + 0x28))->f = 1.0f;

    w->colData = GOBJ_SUB(self)->colData;

    w->effectDObj = CSVSYSTEM_InitDObj(63, &InitialSObjSimpleSetting);

    w->route = lay->kind & 0xFFFF;
    *(void **)((char *)GOBJ_SUB(self) + 0x81C) = (void *)BoxRideFunc;

    g = CreateLayoutedGObj(0, 64, -1, 0, lay, 0, 7, 0);
    w->subGObj = (int)g;

    GOBJ_SUB(g)->disp = 1;
    *(int *)(g + 0x16C) = 0;

    if (w->route != 0) {
        w->pointCount = countPathPoints(w->route);
        w->friction = 0.98f;
        onPathInitialize(self);
        onPath(self);
        initWheels(self, (float *)lay);
        execNormalMove(self, 1);
        debug_StdPrintfDummy("%d\n", w->pointCount);

        if ((lay->kind & 0xFFFF0000) != 0) {
            BoxLayout r = *lay;
            BoxLink lnk = {(int)self, 0};
            Vec4 v;
            Vec4 q;

            r.scale[0] = 1.0f;
            r.scale[1] = 1.0f;
            r.scale[2] = 1.0f;
            r.scale[3] = 1.0f;
            r.kind = 1;

            sub = accessary[GOBJ_SUB(self)->accessary].subModel;
            o = CreateLayoutedGObj(23, accessary[sub].model, sub, 0, &r, 0, 7, 0);

            LinkParentOfDObj(o, (PackedLL_19CAF0 *)&lnk);

            q.f[0] = accessary[GOBJ_SUB(self)->accessary].subPos[0];
            q.f[1] = accessary[GOBJ_SUB(self)->accessary].subPos[1];
            q.f[2] = accessary[GOBJ_SUB(self)->accessary].subPos[2];
            q.f[3] = 1.0f;
            v = q;

            CopyVector(GOBJ_SUB(o)->root.pos, &v);

            memset(&q, 0, 16);
            q.f[3] = 1.0f;
            RotQuaternionY(
                &q, (short)(accessary[GOBJ_SUB(self)->accessary].subRotY * 32768.0f / 180.0f));
            CopyVector(GOBJ_SUB(o)->root.quat, &q);

            SetSwitchTriggerFunc(o, (void *)moveBoxAutoMatic);

            w->friction = 0.85f;
        }
        UpdateRootMatrix(self);
        return w;
    }

    w->tiltForce[0] = random_signed() * 50.0f * 0.5f;
    w->tiltForce[1] = random_signed() * 50.0f * 0.5f;
    ReInitBoxGeo(self);

    return w;
}

void BoxGeo(GObj *a0)
{
    BoxWork *p = GOBJ_SUB(a0)->work;

    action(a0);
    UpdateRootMatrix(a0);
    if ((*(int *)p)++ >= 0x1F) {
        *(int *)p = 0;
        gamesysObjInfoUniqDataSet(a0);
    }
}

inline void BoxDL(GObj *a0)
{
    BoxWork *q = GOBJ_SUB(a0)->work;
    p2o_SetDefaultEnviroment();
    p2o_DispVU1(a0);
    if (q->route != 0) {
        dispWheels(a0);
    }
    if (systemStatus[5] != 0) {
        StopSEPackageWithGroupVariation(a0, 1);
        ((BoxWork *)GOBJ_SUB(a0)->work)->autoDir = 0;
    }
}

inline int BoxGeoRestore(float *a0, float *a1)
{
    a0[0] = a1[4];
    a0[1] = a1[5];
    a0[2] = a1[6];
    a0[4] = a1[8];
    a0[5] = a1[9];
    a0[6] = a1[10];
    debug_StdPrintfDummy("%f, %f, %f\n", a0[8], a0[9], a0[10]);
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

int GetBoxMode(GObj *a0)
{
    BoxWork *q = GOBJ_SUB(a0)->work;

    return q->mode;
}
