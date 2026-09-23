#include "common.h"
#include "camera-root.h"
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

union PendCopy {
    float f[8];
    long long q[4];
};

/* the camera position and the point it looks at, the pair InitCamera seeds
   both camera work areas with; the halves are named after the same pair in
   InsertCameraWork */
typedef struct {
    float pos[4];
    float tgt[4];
} CamTgt __attribute__((aligned(16)));

/* The camera set the whole TU works on: position (0x00) plus the three
   fixed-point angles MatrixDrive rotates by (0x10/0x12/0x1C).  The word at
   0x18 is the semi-auto move flag DebugCameraSemiAuto runs the camera to its
   target with, cleared on every mode change. */
typedef struct CameraSet2 {
    float pos[3]; /* 0x00 */
    char pad0c[0x10 - 0x0C];
    short rotX; /* 0x10 */
    short rotY; /* 0x12 */
    float fov;  /* 0x14 */
    int moving; /* 0x18 */
    short rotZ; /* 0x1C */
} CameraSet2;

/* What SetWSMatrix / DebugCameraSemiAuto hand in: eye (0x00) and look-at
   (0x10) points plus the field of view at 0x20, copied 8 bytes at a time. */
union CameraSetIn {
    float f[12];
    long long q[6];
};

/* The camera target request Camctrl_SetTarget files and Camctrl_Exec hands to
   CameraSetTargetGObj once a frame: the object the camera follows, its sub
   object, the priority the request was filed at and the priority that ran the
   frame before. */
typedef struct CamCtrl {
    int gobj;    /* 0x00 */
    int subGObj; /* 0x04 */
    int pri;     /* 0x08 */
    int lastPri; /* 0x0C */
} CamCtrl;

typedef struct InsertCameraWork {
    int gobj; /* 0x00 */
    int w04;  /* 0x04 */
    char pad08[0x10 - 0x08];
    float pos[3]; /* 0x10 */
    char pad1c[0x20 - 0x1C];
    float tgt[3]; /* 0x20 */
    char pad2c[0x30 - 0x2C];
    float blend;           /* 0x30 */
    unsigned char enable;  /* 0x34 */
    unsigned char cut;     /* 0x35 */
    unsigned char cutType; /* 0x36 */
    unsigned char b37;     /* 0x37 */
    unsigned char b38;     /* 0x38 */
    char pad39[0x40 - 0x39];
    /* a VU0 quadword record: pos and tgt are quadword vectors and the ROM's own
       copy of it moves 8 bytes at a time */
} InsertCameraWork __attribute__((aligned(16)));

/* .bss, owned by camera-root.o and reached only from this file (MAIN.MAP line
   7713 sizes the run at 0xC0 and names no symbol in it), in the ROM's run
   order: the camera set the default mode interpolates away from, the live
   camera, the set the semi-auto camera is running to, the target request and
   the insert-camera request. */
static union CameraSetIn prevCameraSet;

static CameraSet2 cameraSet;

static CameraSet2 targetCameraSet;

static CamCtrl camctrl;

static InsertCameraWork insertCamera;

/* .sbss, owned by camera-root.o and reached only from this file, in the ROM's
   run order: the two ends of the zoom range, the target object and its sub
   object, the two cut-back requests, the zoom blend ratio, the camera mode,
   the zoom distance and field of view, the lws cut-back request and the four
   demo limits.  MAIN.MAP line 7600 sizes this member's .sbss at 0x25, which
   is the block down to lwsCutBack; the retail revision added the four demo
   limits after it and the run the ROM carries is 0x38.  MAIN.MAP names no
   symbol here, so every name is ours; handCameraLimitP and handCameraLimitV
   take the P and V of their own exported setters. */
static int zoomRangeMin;

static int zoomRangeMax;

static int cameraTargetGObj;

static int cameraTargetSubGObj;

static unsigned char gamecamCutBack;

static unsigned char zoomRequest;

static float zoomBlend;

static int cameraMode;

static float cameraZoom;

static float cameraFov;

static unsigned char lwsCutBack;

static int handCameraLimitP;

static int handCameraLimitV;

static int zoomMaxInDemo;

static int zoomBase;

void SetWSMatrix(void *a0)
{
    ConvertCameraSet(&cameraSet, a0);
    MakeCameraMatrix(&cameraSet);
}

void ConvertCameraSet(CameraSet2 *dst, union CameraSetIn *src)
{
    union CameraSetIn in;
    float dir[4];
    in = *src;
    dst->pos[0] = in.f[0];
    dst->pos[1] = in.f[1];
    dst->pos[2] = in.f[2];
    memset(dir, 0, 16);
    dir[3] = 1.0f;
    sceVu0SubVector(dir, &in.f[4], &in.f[0]);
    FSqrt(dir[0] * dir[0] + dir[2] * dir[2]);
    dst->rotY = atan2f(dir[0], dir[2]) * 32768.0f / 3.14159265f;
    dst->rotX = atan2f(dir[1], FSqrt(dir[0] * dir[0] + dir[2] * dir[2])) * -32768.0f / 3.14159265f;
    dst->fov = in.f[8];
    dst->rotZ = 0;
}

void MakeMatrixFromCameraSet2(void *dst, CameraSet2 *cs)
{
    MatrixDrive_PushMatrix();
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_RotMatrixY(cs->rotY);
    MatrixDrive_RotMatrixX(cs->rotX);
    MatrixDrive_RotMatrixZ(cs->rotZ);
    sceVu0TransposeMatrix(MatrixDrive_GetMatrix(), MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrix(-cs->pos[0], -cs->pos[1], -cs->pos[2]);
    CopyMatrix(dst, MatrixDrive_GetMatrix());
    MatrixDrive_PopMatrix();
}

extern char *matrixptr;
extern int ScreenWidth;
extern int ScreenHeight;

void MakeCameraMatrix(CameraSet2 *cs)
{
    float mat[16];
    MakeMatrixFromCameraSet2(mat, cs);
    MatrixDrive_PushMatrix();
    CopyMatrix(MatrixDrive_GetMatrix(), mat);
    gsb_SetVSMatrix(ScreenWidth, ScreenHeight,
                    GetTableCos(cs->fov * 32768.0f / 180.0f) * 1024.0f /
                        GetTableSin(cs->fov * 32768.0f / 180.0f));
    sceVu0CopyMatrix(matrixptr + 0x80, MatrixDrive_GetMatrix());
    MatrixDrive_PopMatrix();
    gsb_MakeCommonMatrix();
}

typedef struct EditPad {
    int flags; /* 0x00 */
    int trg04; /* 0x04 */
    char pad08[0x58 - 0x08];
    int mode; /* 0x58 */
    int trg;  /* 0x5C */
    char pad60[0xAC - 0x60];
    unsigned char stick[4]; /* 0xAC */
} EditPad;

extern EditPad D_0028F8F0;
extern int D_0063AB68;

void CameraEditManual(CameraSet2 *set, int noLock)
{
    float mz = 0.0f, mx = 0.0f;
    int d;
    int t;
    float v[4];
    float out[4];

    if (D_0028F8F0.trg & 0x1000) {
        D_0063AB68 = 1;
    }
    if (D_0028F8F0.trg & 0x2000) {
        D_0063AB68 = 2;
    }
    if (D_0028F8F0.trg & 0x4000) {
        D_0063AB68 = 3;
    }
    if (D_0028F8F0.trg & 0x8000) {
        D_0063AB68 = 4;
    }

    d = 0x80 - D_0028F8F0.stick[1];
    if ((d < 0 ? -d : d) < 0x32) {
        d = 0;
    }
    if (D_0028F8F0.mode & 2) {
        if ((d < 0 ? -d : d) >= 0x33) {
            if (d < 0x32) {
                t = (d + 0x32) * 10;
                set->pos[1] -= (float)(D_0063AB68 * t) / 78.0f;
            }
            if (d >= 0x33) {
                t = (d - 0x32) * 10;
                set->pos[1] -= (float)(D_0063AB68 * t) / 78.0f;
            }
        }
    } else {
        if ((d < 0 ? -d : d) >= 0x33) {
            if (d < 0x32) {
                set->rotX -= (d + 0x32) * (d + 0x32) * 5 / 78;
            }
            if (d >= 0x33) {
                set->rotX += (d - 0x32) * (d - 0x32) * 5 / 78;
            }
        }
    }

    d = 0x80 - D_0028F8F0.stick[0];
    if ((d < 0 ? -d : d) < 0x32) {
        d = 0;
    }
    if ((d < 0 ? -d : d) >= 0x33) {
        if (d < 0x32) {
            set->rotY += (d + 0x32) * (d + 0x32) * 5 / 78;
        }
        if (d >= 0x33) {
            set->rotY -= (d - 0x32) * (d - 0x32) * 5 / 78;
        }
    }

    d = 0x80 - D_0028F8F0.stick[3];
    if ((d < 0 ? -d : d) < 0x32) {
        d = 0;
    }
    if ((d < 0 ? -d : d) >= 0x33) {
        if (noLock || (D_0028F8F0.flags & 1) == 0) {
            if (d < 0x32) {
                t = (d + 0x32) * 10;
                mz = (float)(D_0063AB68 * t) / 78.0f;
            }
            if (d >= 0x33) {
                t = (d - 0x32) * 10;
                mz = (float)(D_0063AB68 * t) / 78.0f;
            }
        }
    }

    d = 0x80 - D_0028F8F0.stick[2];
    if ((d < 0 ? -d : d) < 0x32) {
        d = 0;
    }
    if ((d < 0 ? -d : d) >= 0x33) {
        if ((D_0028F8F0.flags & 0x200) == 0) {
            if (d < 0x32) {
                t = (d + 0x32) * 10;
                mx = (float)(D_0063AB68 * t) / 78.0f;
            }
            if (d >= 0x33) {
                t = (d - 0x32) * 10;
                mx = (float)(D_0063AB68 * t) / 78.0f;
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

void DebugCameraManual(void)
{
    CameraEditManual(&cameraSet, 0);
    MakeCameraMatrix(&cameraSet);
}

extern void ConvertCameraSet(CameraSet2 *dst, union CameraSetIn *src);
/* kept local: this TU's uses of _MoveGV do not fit the prototype in gv.h */
extern float _MoveGV(void *a0, void *a1, void *a2, float t);

void DebugCameraSemiAuto(void)
{
    if (targetCameraSet.moving != 0) {
        if (_MoveGV(&cameraSet, &cameraSet, &targetCameraSet, 50.0f) < 1.0f) {
            targetCameraSet.moving = 0;
        }
    } else {
        float buf[10];
        CameraEditManual(&cameraSet, 1);
        buf[0] = cameraSet.pos[0];
        buf[1] = cameraSet.pos[1];
        buf[2] = cameraSet.pos[2];
        buf[8] = cameraSet.fov;
        GetRootPosition(&buf[4], cameraTargetGObj);
        ConvertCameraSet(&cameraSet, buf);
    }
    MakeCameraMatrix(&cameraSet);
}

extern int D_0063AB9C;
/* kept local: this TU's uses of SetCameraTargetPosition do not fit the prototype in camera-ico2.h */
extern void SetCameraTargetPosition(void *, void *, float);
/* kept local: this TU's uses of _DistGV do not fit the prototype in gv.h */
extern float _DistGV(void *, void *);

void BackToGameCamera(void)
{
    char buf[0x80];
    float f20v;
    memset(buf, 0, 0x10);
    *(float *)(buf + 8) = 1.0f;
    sceVu0TransposeMatrix(buf + 0x20, matrixptr + 0x80);
    CopyVector(buf + 0x70, matrixptr + 0xB0);
    *(int *)(buf + 0x7C) = 0;
    sceVu0ApplyMatrix(buf + 0x10, buf + 0x20, buf + 0x70);
    sceVu0ScaleVector(buf + 0x10, buf + 0x10, -1.0f);
    GetRootPosition(buf + 0x60, D_0063AB9C);
    f20v = _DistGV(buf + 0x10, buf + 0x60);
    *(int *)(buf + 0xC) = 0;
    sceVu0ApplyMatrix(buf, buf + 0x20, buf);
    sceVu0ScaleVector(buf, buf, f20v);
    sceVu0AddVector(buf, buf, buf + 0x10);
    SetCameraTargetPosition(buf, buf + 0x10, cameraFov);
}

extern int D_0063B1B0;

void GetCameraInfomationFromGlobalPosition(int a0, int a1, int a2, int a3, int a4)
{
    *(float *)a3 = cameraSet.fov;
    *(float *)a4 = (float)D_0063B1B0 / 100.0f;
    CameraGetOtherObjOffset(a0, a1, a2);
}

extern int *D_00639EA4;

static inline int getCameraDefaultTargetGObj(void)
{
    int id = GetEfStageCameraTargetID();
    if (id != 0) {
        int gobj = isysGObjSearchFromObjLayoutID(id);
        if (gobj != 0) {
            return gobj;
        }
    }
    return D_00639EA4;
}

/* The listing shows these two bodies inlined (rows at camera-root.c:227-230
   and :241) into Camctrl_ExitEveRock and InitCamera; neither has a symbol in
   baserom/pal/MAIN.MAP, so both names are ours. */
static inline void Camctrl_ForceTarget(int gobj)
{
    camctrl.pri = 0;
    camctrl.gobj = gobj;
    camctrl.subGObj = 0;
}

static inline void Camctrl_Init(int gobj)
{
    camctrl.lastPri = 0;
    Camctrl_ForceTarget(gobj);
}

/* the pair InitCamera starts every stage from: the camera one metre up,
   looking at a point just over half a metre up.  MAIN.MAP names no symbol in
   camera-root.o's .data, so both names here are ours. */
static CamTgt cameraTargetDefault = {{0.0f, 100.0f, 0.0f, 0.0f}, {0.0f, 52.0f, 0.0f, 0.0f}};

/* the cleared insert-camera request: no target, no blend, one cut pending */
static InsertCameraWork insertCameraClear = {
    0, 0, {0}, {0.0f, 0.0f, 0.0f}, {0}, {0.0f, 0.0f, 0.0f}, {0}, -1.0f, 0, 1, 0, 0, 1, {0}};

/* camera-root.c:443 in the listing, inlined into InitCamera; it has no symbol
   in baserom/pal/MAIN.MAP, so this name is ours. */
static inline void InsertCamera_Clear(void)
{
    insertCamera = insertCameraClear;
}

/* kept local: this TU's uses of InitIco2Camera do not fit the prototype in camera-ico2.h */
extern void InitIco2Camera(void);
extern int D_0028F720[];
extern int D_0063AB98;
extern int D_0063ABA0;
extern int D_0063ABA4;
extern int D_0063ABA8;

void InitCamera(void)
{
    int gobj = getCameraDefaultTargetGObj();
    InsertCamera_Clear();
    D_0063AB9C = gobj;
    cameraMode = 3;
    *(CamTgt *)&targetCameraSet = *(CamTgt *)&cameraSet = cameraTargetDefault;
    Camctrl_Init(gobj);
    InitIco2Camera();
    InitCameraEditor();
    targetCameraSet.moving = 0;
    gamecamCutBack = 0;
    zoomRequest = 0;
    lwsCutBack = 0;
    D_0063AB98 = 0;
    D_0063ABA4 = 0;
    D_0063ABA0 = 0;
    D_0063ABA8 = 0;
    D_0063B1B0 = 100;
    handCameraLimitP = D_0028F720[0x180 / 4];
    handCameraLimitV = D_0028F720[0x184 / 4];
    zoomMaxInDemo = D_0028F720[0x190 / 4];
}

/* camera-root.c lines 1051-1352.  The listing inlines five helpers into this
   body: GetCameraDefaultTargetGObj (rows 970-978), the camera-control step at
   rows 255-270, InsertCamera_isEnable (428-431) with the insert-camera step at
   rows 455-471, CameraSetMode (547-548) and the target release at row 281.
   Only the first and the last two have census names; the two insert/control
   steps sit inside coalesced spans and their names here are ours. */

typedef struct {
    int step; /* 0x00 */
    int max;  /* 0x04 */
} CamZoomStep;

typedef struct {
    CamZoomStep e[3];
} CamZoomTbl;

/* the one scratch quadword-and-a-half the body reuses: the screen test's
   output point first, then the three zoom steps */
/* one quadword copied whole out of the const table */
union CamQuad {
    float f[4];
    long long q[2];
};

union CamWork {
    float v[4];
    CamZoomTbl zoom;
};

extern int D_0028F4C0[];
extern int D_0063AB98;
extern char *matrixptr;
extern void BackToGameCamera(void);
extern int D_0063ABA0;
extern int D_0063ABA4;
extern int D_0063ABAC;
extern int D_0063AB9C;
extern float IsPointIsInScreen();
/* same prototype as commonact.h's, kept local: this TU includes no commonact.h */
extern void *test_CURRENTROOT(void *gobj);
extern void CameraSetTargetGObj(int a, int b);

/* rows 255-270: one step of the camera target queue.  The name is ours. */
static inline void Camctrl_Exec(void)
{
    float pos[4];
    int last;

    if (camctrl.pri != 0) {
        D_0063ABAC = 0;
    }
    if (D_0063ABAC != 0) {
        D_0063ABAC = D_0063ABAC - 1;
    }
    if ((last = camctrl.lastPri) == 1 && camctrl.pri == 0 && D_0063AB9C != 0 &&
        IsPointIsInScreen(pos, test_CURRENTROOT((void *)D_0063AB9C)) < 0.0f) {
        D_0063ABAC = (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1];
        D_0063ABA0 = last;
    }
    CameraSetTargetGObj(camctrl.gobj, camctrl.subGObj);
    camctrl.lastPri = camctrl.pri;
}

/* row 281: release the target once its priority drops below the demo level.
   The name is ours; Camctrl_ExitEveRock is the same shape with 4. */
static inline void Camctrl_ExitNormal(void)
{
    if (camctrl.pri < 3) {
        Camctrl_ForceTarget(D_0063AB9C);
    }
}

/* rows 428-431, inlined here; the out-of-line body the earlier InsertCamera_*
   setters call lives at its ROM address. */
static inline unsigned char insertCamera_isEnable(void)
{
    if (camctrl.pri < 2) {
        return 1;
    }
    return 0;
}

/* rows 455-471: one step of the insert camera.  The name is ours. */
static inline void InsertCamera_Step(void)
{
    if (insertCamera_isEnable() == 0) {
        insertCamera.enable = 0;
    }
    if (insertCamera.enable != 0) {
        if (insertCamera.w04 < insertCamera.gobj) {
            insertCamera.w04 = insertCamera.w04 + 1;
            zoomRequest = insertCamera.b37;
            zoomBlend = insertCamera.blend;
        } else {
            insertCamera.enable = 0;
            gamecamCutBack = insertCamera.b38;
        }
    }
}

/* rows 547-548, inlined here; CameraSetMode keeps its out-of-line body. */
static inline void cameraSetMode(int x)
{
    cameraMode = x;
    targetCameraSet.moving = 0;
}

#define CAM_ABS(x) ((x) < 0 ? -(x) : (x))

extern int ScreenWidth;
extern int ScreenHeight;
extern char D_0063AB70[]; /* "FREECAM" */
extern char D_0063AB78[]; /* "GAMECAM" */
extern char D_0063AB80[]; /* "HANDCAM" */
extern char D_0063AB88[]; /* "PATHCAM" */
extern unsigned char D_0063AB90;
extern int D_0063AB94;
extern int D_0063AB6C;
extern int D_0063B134;
extern int D_0063B13C;
extern int D_0063B144;
extern int D_0063B1B0;
extern int D_0063B244;
extern int GlobalTimer;
extern char D_00555170[]; /* "%d,%d,%d %d" */
extern const union CamQuad D_00555180;
extern const union CamQuad D_00555190;
extern char iosPadConfCustom[];
extern float _ACTGame_GetParamF(int id);
extern void _ApplyRyGV(void *v, float ry);
extern float _GetDirection(void *v);
extern void _InterGV(void *dst, void *a, void *b, float ta, float tb);
extern void ClearHandCameraCorrect(void);
extern void CopyMatrix(void *dst, void *src);
extern void CopyVector(void *dst, void *src);
extern void DebugCameraManual(void);
extern void DebugCameraSemiAuto(void);
extern void GetHandCameraStickInfo(float *outX, float *outZ, float *outMag);
/* GetRootPosition and MatrixDrive_SetTransposeMatrix come from their owners' headers */
extern void HandCameraCorrect(void *a0, void *a1, int a2, float f12, float f13, float f14);
extern void SetCameraMatrix_Ico2(int cut);
extern void SetCameraZoomOffsetRatio(float r);
extern void SetLimitHandCameraCorrect(float x, float z);
extern void SetWSMatrix(void *a0);
extern void bga_ResetCamera(void);
extern int bga_GetCameraMatrix(void *m);
extern float bga_GetZoom(void);
extern void debug_Printf(int x, int y, unsigned int col, char *fmt, ...);
extern void gsb_MakeCommonMatrix(void);
extern void gsb_SetVSMatrix(int w, int h, float d);
extern int iosPadConnect(void *pad, int slot, int port, void *conf);
extern void iosPadRead(void *pad);
extern void sceVu0AddVector(void *dst, void *a, void *b);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *v);
extern void sceVu0CopyMatrix(void *dst, void *src);
extern void sceVu0ScaleVector(void *dst, void *src, float s);
extern void sceVu0TransposeMatrix(void *dst, void *src);
extern int test_CURRENTORIENT(int gobj);

void SetCameraMatrix(void)
{
    float m[16];
    int gobj;
    int root;
    int useDemo;
    int zoomMax;
    int target;
    int step;
    char *pad;
    float zoom;

    useDemo = 0;
    gobj = getCameraDefaultTargetGObj();
    D_0063AB9C = gobj;
    D_0063AB98 = 1;
    D_0063ABA0 = 0;
    D_0063ABA4 = 0;
    zoomBlend = -1.0f;
    Camctrl_Exec();
    cameraZoom = 0.0f;
    if (bga_GetCameraMatrix(m) != 0) {
        cameraMode = 4;
        cameraZoom = bga_GetZoom();
    } else if (cameraMode == 4) {
        cameraSetMode(3);
        BackToGameCamera();
        bga_ResetCamera();
        gamecamCutBack = lwsCutBack;
        lwsCutBack = 0;
    }
    InsertCamera_Step();
    switch (cameraMode) {
    case 0:
        break;
    case 2:
        DebugCameraSemiAuto();
        if (D_0063B144 != 0 || (D_0063B13C & 1) != 0) {
            debug_Printf(220, 30, 0xFFFFFF00, D_0063AB70);
        }
        if ((D_0028F8F0.flags & 2) != 0 && (D_0028F8F0.trg04 & 0x100) != 0) {
            cameraSetMode(3);
        }
        break;
    case 3:
        if (D_0063B134 != 0) {
            goto handCamera;
        }
        SetCameraMatrix_Ico2(gamecamCutBack);
        gamecamCutBack = 0;
        if (D_0063B144 != 0 || (D_0063B13C & 1) != 0) {
            debug_Printf(220, 30, 0xFFFFFF00, D_0063AB78);
        }
        break;
    case 1:
    handCamera:
        DebugCameraManual();
        if (D_0063B144 != 0 || (D_0063B13C & 1) != 0) {
            debug_Printf(220, 30, 0xFFFFFF00, D_0063AB80);
        }
        if ((D_0028F8F0.trg04 & 0x100) != 0) {
            cameraSetMode(3);
        }
        break;
    case 4: {
        float ofs[4];
        float mt[16];
        float pos[4];
        float eye[4];

        if (D_0063B134 != 0) {
            goto handCamera;
        }
        SetLimitHandCameraCorrect((float)handCameraLimitP, (float)handCameraLimitV);
        if (D_0063B144 != 0 || (D_0063B13C & 1) != 0) {
            debug_Printf(220, 30, 0xFFFFFF00, D_0063AB88);
        }
        if (D_0063B144 != 0 || (D_0063B13C & 1) != 0) {
            debug_Printf(310, 30, 0xFFFFFF00, D_00555170, (int)m[12], (int)m[13], (int)m[14],
                         (int)cameraZoom);
        }
        sceVu0TransposeMatrix(mt, m);
        CopyVector(ofs, &m[12]);
        ofs[3] = 0.0f;
        sceVu0ApplyMatrix(&cameraSet, mt, ofs);
        sceVu0ScaleVector(&cameraSet, &cameraSet, -1.0f);
        useDemo = D_0063B244 != 0;
        if (D_0063B244 != 0) {
            if (handCameraLimitP != 0 || handCameraLimitV != 0) {
                union CameraSetIn in;
                union CameraSetIn set;
                float stickX;
                float stickZ;
                float stickMag;

                MatrixDrive_PushMatrix();
                *(union CamQuad *)eye = D_00555180;
                CopyMatrix(MatrixDrive_GetMatrix(), m);
                MatrixDrive_SetTransposeMatrix(MatrixDrive_GetMatrix(), MatrixDrive_GetMatrix());
                eye[3] = 0.0f;
                sceVu0ApplyMatrix(eye, MatrixDrive_GetMatrix(), eye);
                sceVu0AddVector(pos, &cameraSet, eye);
                MatrixDrive_PopMatrix();
                GetHandCameraStickInfo(&stickX, &stickZ, &stickMag);
                if (GlobalTimer != 0) {
                    ClearHandCameraCorrect();
                    D_0063B1B0 = zoomBase;
                }
                HandCameraCorrect(&cameraSet, pos, 1, stickX, stickZ,
                                  60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
                in.f[0] = cameraSet.pos[0];
                in.f[1] = cameraSet.pos[1];
                in.f[2] = cameraSet.pos[2];
                in.f[4] = pos[0];
                in.f[5] = pos[1];
                in.f[6] = pos[2];
                ConvertCameraSet((CameraSet2 *)&set, &in);
                MakeMatrixFromCameraSet2(m, (CameraSet2 *)&set);
            }
        }
        zoom = cameraZoom;
        if (zoom == 0.0f) {
            if (zoom == 0.0f) {
                zoom = GetTableCos(cameraSet.fov * 32768.0f / 180.0f) * 1024.0f /
                       GetTableSin(cameraSet.fov * 32768.0f / 180.0f);
            }
            cameraZoom = zoom;
            cameraFov = cameraSet.fov;
        } else {
            cameraFov = atan2f(1024.0f / zoom, 1.0f) * 180.0f / 3.14159265f;
        }
        gsb_SetVSMatrix(ScreenWidth, ScreenHeight, cameraZoom);
        sceVu0CopyMatrix(matrixptr + 0x80, m);
        gsb_MakeCommonMatrix();
        break;
    }
    default: {
        union CameraSetIn in;
        float eye[4];
        float rootPos[4];
        union CamQuad ofs;
        float ry;

        root = D_0063AB9C;
        GetRootPosition(rootPos, root);
        ofs = D_00555190;
        ry = (float)(int)(_GetDirection(test_CURRENTORIENT(root)) / 3.14159265f * 180.0f) *
             3.14159265f / 180.0f;
        _ApplyRyGV(ofs.f, ry);
        sceVu0AddVector(eye, rootPos, ofs.f);
        _InterGV(&in.f[4], rootPos, &prevCameraSet.f[4], 10.0f, 1.0f);
        _InterGV(&in, eye, &prevCameraSet, 48.0f, 1.0f);
        in.f[8] = 50.0f;
        SetWSMatrix(&in);
        prevCameraSet = in;
        break;
    }
    }
    Camctrl_ExitNormal();
    {
        CamZoomStep zp[3] = {
            {10, 200}, {10, 200}, {(int)_ACTGame_GetParamF(12), (int)_ACTGame_GetParamF(11)}};
        int padCtx[0x30 / 4];
        int ply;

        if (useDemo != 0) {
            zoomMax = zoomMaxInDemo;
        } else {
            zoomMax = zp[0].max;
        }
        iosPadConnect(padCtx, 0, 0, iosPadConfCustom);
        if (D_0063AB90 != 0) {
            D_0063AB90 = 0;
            zoomBase = D_0063B1B0;
        }
        iosPadRead(padCtx);
        ply = D_00639EA4;
        if (ply != 0 && useDemo == 0) {
            ply = *(int *)((char *)ply + 0x164);
            pad = (char *)ply + 0x2D8;
        } else {
            pad = (char *)padCtx;
        }
        if (zoomRequest != 0) {
            step = 2;
        } else if (*(int *)(pad + 8) & 2) {
            step = 1;
        } else {
            step = 0;
        }
        zoomRangeMin = zoomBase;
        zoomRangeMax = zoomBase + zoomMax;
        if (zoomRequest == 2) {
            zoomRangeMax = zoomBase * 0.75;
        }
        target = step != 0 ? zoomRangeMax : zoomBase;
        zoomRequest = 0;
        if (zoomBlend < 0.0f) {
            if (CAM_ABS(D_0063B1B0 - target) < zp[step].step * 5) {
                D_0063B1B0 = ((float)D_0063B1B0 * 4.0f + (float)target) / 5.0f;
            } else if (target < D_0063B1B0) {
                D_0063B1B0 = D_0063B1B0 - zp[step].step;
            } else if (D_0063B1B0 < target) {
                D_0063B1B0 = D_0063B1B0 + zp[step].step;
            }
        } else {
            D_0063B1B0 = (float)D_0063B1B0 * (1.0f - zoomBlend) + (float)target * zoomBlend;
        }
        SetCameraZoomOffsetRatio(1.0f - (float)(D_0063B1B0 - zoomRangeMin) /
                                            (float)(zoomRangeMax - zoomRangeMin));
    }
    GlobalTimer = 0;
    if (D_0063AB94 != cameraMode || D_0063AB6C != 0) {
        GlobalTimer = 1;
    }
    D_0063AB94 = cameraMode;
    D_0063AB6C = 0;
}

void Camctrl_ExitEveRock(void)
{
    if (camctrl.pri < 4) {
        Camctrl_ForceTarget(D_0063AB9C);
    }
}

void Camctrl_SetTarget(int a0, int a1, int a2)
{
    if (a2 < camctrl.pri) {
        return;
    }
    camctrl.gobj = a0;
    camctrl.subGObj = a1;
    camctrl.pri = a2;
}

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
   GetCameraDefaultTargetGObj into InitCamera, so it is `inline` in the dev's
   TU; while SetCameraMatrix is still asm a deferred inline would land at the
   object end instead of here, so the public body stays a plain definition at
   its ROM position and InitCamera calls the static stand-in below. Collapses
   to one `inline` definition at layout. */
int GetCameraDefaultTargetGObj(void)
{
    int id = GetEfStageCameraTargetID();
    if (id != 0) {
        int gobj = isysGObjSearchFromObjLayoutID(id);
        if (gobj != 0) {
            return gobj;
        }
    }
    return D_00639EA4;
}

void CameraSetTargetGObj(int a, int b)
{
    cameraTargetGObj = a;
    cameraTargetSubGObj = b;
}

void CameraChangeTargetParallel(int a0, int a1)
{
    char buf[0x30];
    if (a0 == 0) {
        *(int *)(buf + 0) = 0;
        *(int *)(buf + 4) = 0;
        *(int *)(buf + 8) = 0;
    } else {
        GetRootPosition(buf + 0x10, a0);
        GetRootPosition(buf + 0x20, a1);
        sceVu0SubVector(buf, buf + 0x20, buf + 0x10);
    }
    *(CamTgt *)&targetCameraSet = *(CamTgt *)&cameraSet;
    sceVu0AddVector(&targetCameraSet, &targetCameraSet, buf);
    targetCameraSet.moving = 1;
}

int CameraGetTarget(void)
{
    return cameraTargetGObj;
}

void CameraGetTargets(int *a0, int *a1)
{
    *a0 = cameraTargetGObj;
    *a1 = cameraTargetSubGObj;
}

void CameraSetMode(int x)
{
    cameraMode = x;
    targetCameraSet.moving = 0;
}

int CameraGetMode(void)
{
    return cameraMode;
}

/* kept local: this TU's uses of _GetDirection do not fit the prototype in gv.h */
extern float _GetDirection(void *v);

void CameraGetOtherObjOffset(float *pos, float *outDist, int *outAngle)
{
    float v[4];
    int ang;
    *outDist = _DistGV(&cameraSet, pos);
    sceVu0SubVector(v, pos, &cameraSet);
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

void InsertCamera_Set(float *pos, float *tgt, int gobj)
{
    if (InsertCamera_isEnable()) {
        insertCamera.gobj = gobj;
        insertCamera.w04 = 0;
        insertCamera.pos[0] = pos[0];
        insertCamera.pos[1] = pos[1];
        insertCamera.pos[2] = pos[2];
        insertCamera.tgt[0] = tgt[0];
        insertCamera.tgt[1] = tgt[1];
        insertCamera.tgt[2] = tgt[2];
        insertCamera.enable = 1;
        insertCamera.cut = 1;
        insertCamera.cutType = 0;
        insertCamera.b37 = 1;
        insertCamera.b38 = 1;
        insertCamera.blend = -1.0f;
    }
}

void InsertCamera_SetNoraml(float *pos, float *tgt, int gobj, int cutType)
{
    if (InsertCamera_isEnable()) {
        insertCamera.gobj = gobj;
        insertCamera.w04 = 0;
        sceVu0ScaleVector(insertCamera.pos, pos, -1.0f);
        sceVu0ScaleVector(insertCamera.tgt, tgt, -1.0f);
        insertCamera.enable = 1;
        insertCamera.cut = 1;
        insertCamera.cutType = cutType;
        insertCamera.b37 = 1;
        insertCamera.b38 = 1;
        insertCamera.blend = -1.0f;
    }
}

void InsertCamera_SetDetail(float *pos, float *tgt, int gobj, int cutType, int b37, int b38,
                            float blend)
{
    if (InsertCamera_isEnable()) {
        insertCamera.gobj = gobj;
        insertCamera.w04 = 0;
        sceVu0ScaleVector(insertCamera.pos, pos, -1.0f);
        sceVu0ScaleVector(insertCamera.tgt, tgt, -1.0f);
        insertCamera.enable = 1;
        insertCamera.cut = 1;
        insertCamera.cutType = cutType;
        insertCamera.b37 = b37;
        insertCamera.b38 = b38;
        insertCamera.blend = blend;
    }
}

void InsertCamera_Exec(float *cam, int *cut, int *cutType, int *enable)
{
    *cut = 0;
    *cutType = 0;
    *enable = 0;
    if (insertCamera.enable) {
        if (insertCamera.cut) {
            *cut = 1;
            *cutType = insertCamera.cutType;
            insertCamera.cut = 0;
            insertCamera.cutType = 0;
        }
        cam[0] = insertCamera.pos[0];
        cam[1] = insertCamera.pos[1];
        cam[2] = insertCamera.pos[2];
        cam[4] = insertCamera.tgt[0];
        cam[5] = insertCamera.tgt[1];
        cam[6] = insertCamera.tgt[2];
        *enable = 1;
    }
}

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

void SetHandCameraLimitInDemo(int a0, int a1)
{
    handCameraLimitP = a0;
    handCameraLimitV = a1;
}

void ResetHandCameraLimitInDemo(void)
{
    handCameraLimitP = D_0028F720[0x180 / 4];
    handCameraLimitV = D_0028F720[0x184 / 4];
}

void SetZoomMaxValInDemo(int a0)
{
    zoomMaxInDemo = a0;
}

extern int D_0028F8B0[];

void ResetZoomMaxValInDemo(void)
{
    zoomMaxInDemo = D_0028F8B0[0];
}

extern int D_0028F8A0[];

int UpdateHandCameraLimitP(void)
{
    handCameraLimitP = D_0028F8A0[0];
    return 0;
}

extern int D_0028F8A4[];

int UpdateHandCameraLimitV(void)
{
    handCameraLimitV = D_0028F8A4[0];
    return 0;
}

int UpdateZoomMaxVallInDemo(void)
{
    zoomMaxInDemo = D_0028F8B0[0];
    return 0;
}

int InsertCamera_isEnable(void)
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
    if (D_0063AB98 == 0) {
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
    *out = D_0063B1B0 / 100.0f;
}

void testcamerazoom(void)
{
    zoomRequest = 1;
}

extern int D_0063AB6C;

void SetMonitorCameraInitializeFlag(void)
{
    D_0063AB6C = 1;
}
