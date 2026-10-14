#include "camera-root.h"
#include "debug.h"
#include "gobj.h"
#include "boyact.h"
#include "camera-editor.h"
#include "GsBase.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "tableSin.h"
#include <math.h>
#include <string.h>
#include <libvu0.h>
#include "hand-camera.h"
#include "BgAnimation.h"
#include "act-game.h"
#include "main.h"
#include "gv.h"
#include "commonact.h"
#include "pad.h"
#include "camera-ico2.h"
#include "poly-flat.h"
#include "include_asm.h"

static int InsertCamera_isEnable(void);

union PendCopy { /* field names derived */
    float f[8];
    long long q[4];
};

/* the camera position and the point it looks at, the pair InitCamera seeds
   both camera work areas with; the halves are named after the same pair in
   InsertCameraWork */
typedef struct { /* field names derived */
    float pos[4];
    float tgt[4];
} CamTgt __attribute__((aligned(16)));

/* The camera set the whole TU works on: position (0x00) plus the three
   fixed-point angles MatrixDrive rotates by (0x10/0x12/0x1C).  The word at
   0x18 is the semi-auto move flag DebugCameraSemiAuto runs the camera to its
   target with, cleared on every mode change. */
typedef struct CameraSet2 { /* field names derived */
    float pos[3];           /* 0x00 */
    char pad0c[4];
    short rotX; /* 0x10 */
    short rotY; /* 0x12 */
    float fov;  /* 0x14 */
    int moving; /* 0x18 */
    short rotZ; /* 0x1C */
} CameraSet2;   /* derived name */

/* What SetWSMatrix / DebugCameraSemiAuto hand in: eye (0x00) and look-at
   (0x10) points plus the field of view at 0x20, copied as doublewords. */
union CameraSetIn { /* field names derived */
    float f[12];
    long long q[6];
};

/* The camera target request Camctrl_SetTarget files and Camctrl_Exec hands to
   CameraSetTargetGObj once a frame: the object the camera follows, its sub
   object, the priority the request was filed at and the priority that ran the
   frame before. */
typedef struct CamCtrl { /* field names derived */
    GObj *gobj;          /* 0x00 */
    GObj *subGObj;       /* 0x04 */
    int pri;             /* 0x08 */
    int lastPri;         /* 0x0C */
} CamCtrl;               /* derived name */

typedef struct InsertCameraWork { /* field names derived */
    int frames;                   /* 0x00, how long the insert camera runs */
    int count;                    /* 0x04, the frames it has run */
    char pad08[8];
    float pos[3]; /* 0x10 */
    char pad1c[4];
    float tgt[3]; /* 0x20 */
    char pad2c[4];
    unsigned char enable;  /* 0x30 */
    unsigned char cut;     /* 0x31 */
    unsigned char zoom;    /* 0x32, the zoom request while it runs */
    unsigned char cutBack; /* 0x33, cut back to the game camera at the end */
    char pad34[12];
    /* a VU0 quadword record: pos and tgt are quadword vectors */
} InsertCameraWork __attribute__((aligned(16)));

/* The camera set the default mode interpolates away from, the live camera,
   the set the semi-auto camera is running to, the target request and the
   insert-camera request. */
static union CameraSetIn prevCameraSet; /* derived name */

static CameraSet2 cameraSet; /* derived name */

static CameraSet2 targetCameraSet; /* derived name */

static CamCtrl camctrl; /* derived name */

static InsertCameraWork insertCamera; /* derived name */

/* The zoom base the zoom range is measured from and the two ends of the
   range, the target object and its sub object, the two cut-back requests,
   the camera mode, the zoom distance and field of view, and the lws cut-back
   request. */
static int zoomBase; /* derived name */

static int zoomRangeMin; /* derived name */

static int zoomRangeMax; /* derived name */

static GObj *cameraTargetGObj; /* derived name */

static GObj *cameraTargetSubGObj; /* derived name */

static unsigned char gamecamCutBack; /* derived name */

static unsigned char zoomRequest; /* derived name */

static int cameraMode; /* derived name */

static float cameraZoom; /* derived name */

static float cameraFov; /* derived name */

static unsigned char lwsCutBack; /* derived name */

void ConvertCameraSet(CameraSet2 *dst, union CameraSetIn *src);

void SetWSMatrix(void *src)
{
    ConvertCameraSet(&cameraSet, src);
    MakeCameraMatrix(&cameraSet);
}

INCLUDE_ASM(ConvertCameraSet);

static void MakeMatrixFromCameraSet2(void *dst, CameraSet2 *cs);

INCLUDE_ASM(MakeCameraMatrix);

/* the manual camera's speed, 1 to 4 on the pad's buttons */
static int manualCameraSpeed = 2; /* derived name */

static void CameraEditManual(CameraSet2 *set, int noLock)
{
    float mz = 0.0f, mx = 0.0f;
    int d;
    int t;
    float v[4];
    float out[4];

    if (pad[1].flags & 0x1000) {
        manualCameraSpeed = 1;
    }
    if (pad[1].flags & 0x2000) {
        manualCameraSpeed = 2;
    }
    if (pad[1].flags & 0x4000) {
        manualCameraSpeed = 3;
    }
    if (pad[1].flags & 0x8000) {
        manualCameraSpeed = 4;
    }

    d = 128 - pad[1].ana[1];
    if ((d < 0 ? -d : d) < 50) {
        d = 0;
    }
    if (pad[1].now & 2) {
        if ((d < 0 ? -d : d) >= 51) {
            if (d < 50) {
                t = (d + 50) * 10;
                set->pos[1] -= (float)(manualCameraSpeed * t) / 78.0f;
            }
            if (d >= 51) {
                t = (d - 50) * 10;
                set->pos[1] -= (float)(manualCameraSpeed * t) / 78.0f;
            }
        }
    } else {
        if ((d < 0 ? -d : d) >= 51) {
            if (d < 50) {
                set->rotX -= (d + 50) * (d + 50) * 5 / 78;
            }
            if (d >= 51) {
                set->rotX += (d - 50) * (d - 50) * 5 / 78;
            }
        }
    }

    d = 128 - pad[1].ana[0];
    if ((d < 0 ? -d : d) < 50) {
        d = 0;
    }
    if ((d < 0 ? -d : d) >= 51) {
        if (d < 50) {
            set->rotY += (d + 50) * (d + 50) * 5 / 78;
        }
        if (d >= 51) {
            set->rotY -= (d - 50) * (d - 50) * 5 / 78;
        }
    }

    d = 128 - pad[1].ana[3];
    if ((d < 0 ? -d : d) < 50) {
        d = 0;
    }
    if ((d < 0 ? -d : d) >= 51) {
        if (noLock || (pad[0].now & 1) == 0) {
            if (d < 50) {
                t = (d + 50) * 10;
                mz = (float)(manualCameraSpeed * t) / 78.0f;
            }
            if (d >= 51) {
                t = (d - 50) * 10;
                mz = (float)(manualCameraSpeed * t) / 78.0f;
            }
        }
    }

    d = 128 - pad[1].ana[2];
    if ((d < 0 ? -d : d) < 50) {
        d = 0;
    }
    if ((d < 0 ? -d : d) >= 51) {
        if ((pad[0].now & 0x200) == 0) {
            if (d < 50) {
                t = (d + 50) * 10;
                mx = (float)(manualCameraSpeed * t) / 78.0f;
            }
            if (d >= 51) {
                t = (d - 50) * 10;
                mx = (float)(manualCameraSpeed * t) / 78.0f;
            }
        }
    }

    MatrixDrive_PushMatrix();
    v[0] = mx;
    v[1] = 0.0f;
    v[2] = mz;
    v[3] = 0.0f;
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_RotMatrixY(-set->rotY);
    sceVu0ApplyMatrix(out, MatrixDrive_GetMatrix(), v);
    set->pos[0] -= out[0];
    set->pos[2] += out[2];
    MatrixDrive_PopMatrix();
}

static void DebugCameraManual(void)
{
    CameraEditManual(&cameraSet, 0);
    MakeCameraMatrix(&cameraSet);
}

static void DebugCameraSemiAuto(void)
{
    if (targetCameraSet.moving != 0) {
        if (_MoveGV(cameraSet.pos, cameraSet.pos, targetCameraSet.pos, 50.0f) < 1.0f) {
            targetCameraSet.moving = 0;
        }
    } else {
        union CameraSetIn buf;
        CameraEditManual(&cameraSet, 1);
        buf.f[0] = cameraSet.pos[0];
        buf.f[1] = cameraSet.pos[1];
        buf.f[2] = cameraSet.pos[2];
        buf.f[8] = cameraSet.fov;
        GetRootPosition(&buf.f[4], cameraTargetGObj);
        ConvertCameraSet(&cameraSet, &buf);
    }
    MakeCameraMatrix(&cameraSet);
}

static void BackToGameCamera(void)
{
    struct {             /* field names derived */
        float target[4]; /* the point the camera looks at */
        float eye[4];    /* the camera position */
        float m[16];     /* the view rotation, transposed */
        float root[4];   /* the target object's root */
        float trans[4];  /* the view translation */
    } buf;

    float f20v;
    memset(buf.target, 0, 16);
    buf.target[2] = 1.0f;
    sceVu0TransposeMatrix(buf.m, matrixptr + 0x80);
    CopyVector(buf.trans, matrixptr + 0xB0);
    buf.trans[3] = 0.0f;
    sceVu0ApplyMatrix(buf.eye, buf.m, buf.trans);
    sceVu0ScaleVector(buf.eye, buf.eye, -1.0f);
    GetRootPosition(buf.root, default_cameratarget_gobj);
    f20v = _DistGV(buf.eye, buf.root);
    buf.target[3] = 0.0f;
    sceVu0ApplyMatrix(buf.target, buf.m, buf.target);
    sceVu0ScaleVector(buf.target, buf.target, f20v);
    sceVu0AddVector(buf.target, buf.target, buf.eye);
    SetCameraTargetPosition(buf.target, buf.eye, cameraFov);
}

void GetCameraInfomationFromGlobalPosition(float *pos, float *outDist, int *outAngle, float *fov,
                                           float *zoom)
{
    *fov = cameraSet.fov;
    *zoom = (float)debug_zoom_per / 100.0f;
    CameraGetOtherObjOffset(pos, outDist, outAngle);
}

/* GetCameraDefaultTargetGObj's body, for InitCamera and the camera step */
static inline GObj *getCameraDefaultTargetGObj(void) /* derived name */
{
    int id = GetEfStageCameraTargetID();
    if (id != 0) {
        GObj *gobj = isysGObjSearchFromObjLayoutID(id);
        if (gobj != 0) {
            return gobj;
        }
    }
    return boyGObj;
}

/* hand the camera to gobj at no priority, for Camctrl_ExitEveRock and
   InitCamera */
static inline void Camctrl_ForceTarget(GObj *gobj) /* derived name */
{
    camctrl.pri = 0;
    camctrl.gobj = gobj;
    camctrl.subGObj = 0;
}

static inline void Camctrl_Init(GObj *gobj) /* derived name */
{
    camctrl.lastPri = 0;
    Camctrl_ForceTarget(gobj);
}

/* the pair InitCamera starts every stage from: the camera one metre up,
   looking at a point just over half a metre up */
static CamTgt cameraTargetDefault =
    /* derived name */ {{0.0f, 100.0f, 0.0f, 0.0f}, {0.0f, 52.0f, 0.0f, 0.0f}};

/* the cleared insert-camera request: no target, no blend, one cut pending */
static InsertCameraWork insertCameraClear = {
    /* derived name */
    0, 0, {0}, {0.0f, 0.0f, 0.0f}, {0}, {0.0f, 0.0f, 0.0f}, {0}, 0, 1, 0, 0, {0}};

/* clear the insert-camera request */
static inline void InsertCamera_Clear(void) /* derived name */
{
    insertCamera = insertCameraClear;
}

int CameraCalclated_f;

GObj *default_cameratarget_gobj;

int InsertCameraWorkingFlag;

int monitorCameraHold; /* derived name */

INCLUDE_ASM(InitCamera);

typedef struct { /* field names derived */
    int step;    /* 0x00 */
    int max;     /* 0x04 */
} CamZoomStep;   /* derived name */

/* one quadword copied whole out of the const table */
union CamQuad { /* field names derived */
    float f[4];
    long long q[2];
};

/* one step of the camera target queue */
static inline void Camctrl_Exec(void) /* derived name */
{
    float pos[4];
    int last;

    if ((last = camctrl.lastPri) == 1 && camctrl.pri == 0 && default_cameratarget_gobj != 0 &&
        IsPointIsInScreen(pos, test_CURRENTROOT(default_cameratarget_gobj)) < 0.0f) {
        InsertCameraWorkingFlag = last;
    }
    CameraSetTargetGObj(camctrl.gobj, camctrl.subGObj);
    camctrl.lastPri = camctrl.pri;
}

/* release the target once its priority drops below the demo level;
   Camctrl_ExitEveRock is the same shape with 4 */
static inline void Camctrl_ExitNormal(void) /* derived name */
{
    if (camctrl.pri < 3) {
        Camctrl_ForceTarget(default_cameratarget_gobj);
    }
}

/* InsertCamera_isEnable's body, for the camera step below */
static inline unsigned char insertCamera_isEnable(void) /* derived name */
{
    if (camctrl.pri < 2) {
        return 1;
    }
    return 0;
}

/* one step of the insert camera */
static inline void InsertCamera_Step(void) /* derived name */
{
    if (insertCamera_isEnable() == 0) {
        insertCamera.enable = 0;
    }
    if (insertCamera.enable != 0) {
        if (insertCamera.count < insertCamera.frames) {
            insertCamera.count = insertCamera.count + 1;
            zoomRequest = insertCamera.zoom;
        } else {
            insertCamera.enable = 0;
            gamecamCutBack = insertCamera.cutBack;
        }
    }
}

/* CameraSetMode's body: set the mode and stop the target set's move */
static inline void cameraSetMode(int mode) /* derived name */
{
    cameraMode = mode;
    targetCameraSet.moving = 0;
}

#define CAM_ABS(x) ((x) < 0 ? -(x) : (x))

/* set when the monitor camera must start over */
static int monitorCameraInit = 0; /* derived name */

INCLUDE_ASM(SetCameraMatrix);

void Camctrl_ExitEveRock(void)
{
    if (camctrl.pri < 4) {
        Camctrl_ForceTarget(default_cameratarget_gobj);
    }
}

void Camctrl_SetTarget(GObj *gobj, GObj *subGObj, int pri)
{
    if (pri < camctrl.pri) {
        return;
    }
    camctrl.gobj = gobj;
    camctrl.subGObj = subGObj;
    camctrl.pri = pri;
}

/* the object the camera follows by default: the stage's camera target, or
   the boy */
GObj *GetCameraDefaultTargetGObj(void)
{
    int id = GetEfStageCameraTargetID();
    if (id != 0) {
        GObj *gobj = isysGObjSearchFromObjLayoutID(id);
        if (gobj != 0) {
            return gobj;
        }
    }
    return boyGObj;
}

void CameraSetTargetGObj(GObj *gobj, GObj *subGObj)
{
    cameraTargetGObj = gobj;
    cameraTargetSubGObj = subGObj;
}

void CameraChangeTargetParallel(GObj *oldTarget, GObj *newTarget)
{
    struct {           /* field names derived */
        float move[4]; /* the step from the old target to the new one */
        float from[4]; /* the old target's root */
        float to[4];   /* the new target's root */
    } buf;

    if (oldTarget == 0) {
        buf.move[0] = 0.0f;
        buf.move[1] = 0.0f;
        buf.move[2] = 0.0f;
    } else {
        GetRootPosition(buf.from, oldTarget);
        GetRootPosition(buf.to, newTarget);
        sceVu0SubVector(buf.move, buf.to, buf.from);
    }
    *(CamTgt *)&targetCameraSet = *(CamTgt *)&cameraSet;
    sceVu0AddVector(targetCameraSet.pos, targetCameraSet.pos, buf.move);

    targetCameraSet.moving = 1;
}

GObj *CameraGetTarget(void)
{
    return cameraTargetGObj;
}

void CameraGetTargets(GObj **gobj, GObj **subGObj)
{
    *gobj = cameraTargetGObj;
    *subGObj = cameraTargetSubGObj;
}

void CameraSetMode(int mode)
{
    cameraMode = mode;
    targetCameraSet.moving = 0;
}

int CameraGetMode(void)
{
    return cameraMode;
}

void CameraGetOtherObjOffset(float *pos, float *outDist, int *outAngle)
{
    float v[4];
    int ang;
    *outDist = _DistGV(cameraSet.pos, pos);
    sceVu0SubVector(v, pos, cameraSet.pos);
    sceVu0Normalize(v, v);
    ang = (int)(_GetDirection(v) / 3.14159265f * 180.0f) - cameraSet.rotY * 180 / 32768;
    if (ang > 180) {
        ang -= 360;
    }
    if (ang <= -180) {
        ang += 360;
    }
    *outAngle = ang;
}

INCLUDE_ASM(InsertCamera_Set);

INCLUDE_ASM(InsertCamera_SetNoraml);

INCLUDE_ASM(InsertCamera_Exec);

int *GetCurrentCameraSet2(void)
{
    return (int *)&cameraSet;
}

void SetCameraFlag_LwsCutBack(void)
{
    lwsCutBack = 1;
}

void SetCameraFlag_GamecamCutBack(void)
{
    gamecamCutBack = 1;
}

static int InsertCamera_isEnable(void)
{
    return camctrl.pri < 2;
}

void CameraSetCameraPosition(float *src)
{
    if (cameraMode != 3) {
        cameraSet.pos[0] = src[0];
        cameraSet.pos[1] = src[1];
        cameraSet.pos[2] = src[2];
        targetCameraSet.pos[0] = src[0];
        targetCameraSet.pos[1] = src[1];
        targetCameraSet.pos[2] = src[2];
    }
}

void CameraSetTargetPos(void) {}

void *GetCameraPos(void)
{
    if (CameraCalclated_f == 0) {
        return 0;
    }
    return &cameraSet;
}

void GetCameraInfo_tmp(void *dst, float *out)
{
    union PendCopy *s = (union PendCopy *)&cameraSet;
    union PendCopy *d = (union PendCopy *)dst;
    d->q[0] = s->q[0];
    d->q[1] = s->q[1];
    d->q[2] = s->q[2];
    d->q[3] = s->q[3];
    *out = debug_zoom_per / 100.0f;
}

void testcamerazoom(void)
{
    zoomRequest = 1;
}

void SetMonitorCameraInitializeFlag(void)
{
    monitorCameraInit = 1;
}
