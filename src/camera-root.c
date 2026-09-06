#include "common.h"

union PendCopy {
    float f[8];
    long long q[4];
};

typedef struct { unsigned long _0, _8, _10, _18; } CamTgt;

extern int D_006E66C0[];
void SetWSMatrix(void *a0) {
    ConvertCameraSet(D_006E66C0, a0);
    MakeCameraMatrix(D_006E66C0);
}
/* The camera set the whole TU works on: position (0x00) plus the three
   fixed-point angles MatrixDrive rotates by (0x10/0x12/0x1C). */
typedef struct CameraSet2 {
    float pos[3];               /* 0x00 */
    char pad0c[0x10 - 0x0C];
    short rotX;                 /* 0x10 */
    short rotY;                 /* 0x12 */
    float fov;                  /* 0x14 */
    char pad18[0x1C - 0x18];
    short rotZ;                 /* 0x1C */
} CameraSet2;
/* What SetWSMatrix / DebugCameraSemiAuto hand in: eye (0x00) and look-at
   (0x10) points plus the field of view at 0x20, copied 8 bytes at a time. */
union CameraSetIn {
    float f[12];
    long long q[6];
};
extern float FSqrt(float v);
extern float atan2f(float y, float x);
extern void memset(void *p, int c, int n);
extern void sceVu0SubVector(void *dst, void *a, void *b);

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
    dst->rotX = atan2f(dir[1], FSqrt(dir[0] * dir[0] + dir[2] * dir[2]))
        * -32768.0f / 3.14159265f;
    dst->fov = in.f[8];
    dst->rotZ = 0;
}
extern void CopyMatrix(void *dst, void *src);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_RotMatrixX(int a0);
extern void MatrixDrive_RotMatrixY(short a0);
extern void MatrixDrive_RotMatrixZ(int a0);
extern void MatrixDrive_TransMatrix(float x, float y, float z);
extern void sceVu0TransposeMatrix(void *dst, void *src);
extern void sceVu0UnitMatrix(void *a0);

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
extern float GetTableCos(short a0);
extern float GetTableSin(short a0);
extern void gsb_MakeCommonMatrix(void);
extern void gsb_SetVSMatrix(int w, int h, float d);
extern void sceVu0CopyMatrix(void *dst, void *src);
extern char *matrixptr;
extern int D_0063A064;
extern int D_0063A068;

void MakeCameraMatrix(CameraSet2 *cs)
{
    float mat[16];
    MakeMatrixFromCameraSet2(mat, cs);
    MatrixDrive_PushMatrix();
    CopyMatrix(MatrixDrive_GetMatrix(), mat);
    gsb_SetVSMatrix(D_0063A064, D_0063A068,
                    GetTableCos(cs->fov * 32768.0f / 180.0f) * 1024.0f /
                        GetTableSin(cs->fov * 32768.0f / 180.0f));
    sceVu0CopyMatrix(matrixptr + 0x80, MatrixDrive_GetMatrix());
    MatrixDrive_PopMatrix();
    gsb_MakeCommonMatrix();
}
typedef struct EditPad {
    int flags;                  /* 0x00 */
    char pad04[0x58 - 0x04];
    int mode;                   /* 0x58 */
    int trg;                    /* 0x5C */
    char pad60[0xAC - 0x60];
    unsigned char stick[4];     /* 0xAC */
} EditPad;
extern EditPad D_0028F8F0;
extern int D_0063AB68;
extern void sceVu0ApplyMatrix(void *dst, void *m, void *v);

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
    v[0] = mx; v[1] = 0.0f; v[2] = mz; v[3] = 0.0f;
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_RotMatrixY(-set->rotY);
    sceVu0ApplyMatrix(out, MatrixDrive_GetMatrix(), v);
    set->pos[0] -= out[0];
    set->pos[2] += out[2];
    MatrixDrive_PopMatrix();
}
extern void CameraEditManual();
extern int D_006E66C0[];
extern void MakeCameraMatrix();

void DebugCameraManual(void)
{
    CameraEditManual(D_006E66C0, 0);
    MakeCameraMatrix(D_006E66C0);
}
extern void ConvertCameraSet(CameraSet2 *dst, union CameraSetIn *src);
extern int D_0063C290;
extern int D_006E66E0[];
extern void GetRootPosition(void *buf, int obj);
extern float _MoveGV(int *a0, int *a1, int *a2, float t);

void DebugCameraSemiAuto(void) {
    if (D_006E66E0[6] != 0) {
        if (_MoveGV(D_006E66C0, D_006E66C0, D_006E66E0, 50.0f) < 1.0f) {
            D_006E66E0[6] = 0;
        }
    } else {
        float buf[10];
        CameraEditManual(D_006E66C0, 1);
        buf[0] = ((float *)D_006E66C0)[0];
        buf[1] = ((float *)D_006E66C0)[1];
        buf[2] = ((float *)D_006E66C0)[2];
        buf[8] = ((float *)D_006E66C0)[5];
        GetRootPosition(&buf[4], D_0063C290);
        ConvertCameraSet(D_006E66C0, buf);
    }
    MakeCameraMatrix(D_006E66C0);
}
extern void CopyVector(void *, void *);
extern char *matrixptr;
extern int D_0063AB9C;
extern float D_0063C2A8;
extern void SetCameraTargetPosition(void *, void *, float);
extern float _DistGV(void *, void *);
extern void memset(void *, int, int);
extern void sceVu0AddVector(void *, void *, void *);
extern void sceVu0ApplyMatrix(void *, void *, void *);
extern void sceVu0ScaleVector(void *, void *, float);
extern void sceVu0TransposeMatrix(void *, void *);

void BackToGameCamera(void) {
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
    SetCameraTargetPosition(buf, buf + 0x10, D_0063C2A8);
}
extern void CameraGetOtherObjOffset(float *pos, float *outDist, int *outAngle);
extern int D_0063B1B0;
extern float D_006E66D4[];

void GetCameraInfomationFromGlobalPosition(int a0, int a1, int a2, int a3, int a4) {
    *(float *)a3 = D_006E66D4[0];
    *(float *)a4 = (float)D_0063B1B0 / 100.0f;
    CameraGetOtherObjOffset(a0, a1, a2);
}
typedef struct InsertCameraWork {
    int gobj;                   /* 0x00 */
    int w04;                    /* 0x04 */
    char pad08[0x10 - 0x08];
    float pos[3];               /* 0x10 */
    char pad1c[0x20 - 0x1C];
    float tgt[3];               /* 0x20 */
    char pad2c[0x30 - 0x2C];
    float blend;                /* 0x30 */
    unsigned char enable;       /* 0x34 */
    unsigned char cut;          /* 0x35 */
    unsigned char cutType;      /* 0x36 */
    unsigned char b37;          /* 0x37 */
    unsigned char b38;          /* 0x38 */
} InsertCameraWork;
extern InsertCameraWork D_006E6710;

extern int *D_00639EA4;
extern int GetEfStageCameraTargetID(void);
extern int isysGObjSearchFromObjLayoutID();

static inline int getCameraDefaultTargetGObj(void) {
    int id = GetEfStageCameraTargetID();
    if (id != 0) {
        int gobj = isysGObjSearchFromObjLayoutID(id);
        if (gobj != 0) {
            return gobj;
        }
    }
    return D_00639EA4;
}
extern int D_006E6700[];

/* The listing shows these two bodies inlined (rows at camera-root.c:227-230
   and :241) into Camctrl_ExitEveRock and InitCamera; neither has a symbol in
   baserom/pal/MAIN.MAP, so both names are ours. */
static inline void Camctrl_ForceTarget(int gobj)
{
    D_006E6700[2] = 0;
    D_006E6700[0] = gobj;
    D_006E6700[1] = 0;
}
static inline void Camctrl_Init(int gobj)
{
    D_006E6700[3] = 0;
    Camctrl_ForceTarget(gobj);
}
typedef struct { unsigned long _0, _8, _10, _18, _20, _28, _30, _38; } InsCamImage;
extern CamTgt D_002A5E70;
extern InsCamImage D_002A5E90;

/* camera-root.c:443 in the listing, inlined into InitCamera; it has no symbol
   in baserom/pal/MAIN.MAP, so this name is ours. */
static inline void InsertCamera_Clear(void)
{
    *(InsCamImage *)&D_006E6710 = D_002A5E90;
}
extern void InitCameraEditor(void);
extern void InitIco2Camera(void);
extern int D_0028F720[];
extern int D_0063AB98;
extern int D_0063ABA0;
extern int D_0063ABA4;
extern int D_0063ABA8;
extern char D_0063C298;
extern unsigned char D_0063C299;
extern char D_0063C2AC;
extern int D_0063C2A0;
extern int D_0063C2B0;
extern int D_0063C2B4;
extern int D_0063C2B8;
void InitCamera(void)
{
    int gobj = getCameraDefaultTargetGObj();
    InsertCamera_Clear();
    D_0063AB9C = gobj;
    D_0063C2A0 = 3;
    *(CamTgt *)D_006E66E0 = *(CamTgt *)D_006E66C0 = D_002A5E70;
    Camctrl_Init(gobj);
    InitIco2Camera();
    InitCameraEditor();
    D_006E66E0[6] = 0;
    D_0063C298 = 0;
    D_0063C299 = 0;
    D_0063C2AC = 0;
    D_0063AB98 = 0;
    D_0063ABA4 = 0;
    D_0063ABA0 = 0;
    D_0063ABA8 = 0;
    D_0063B1B0 = 100;
    D_0063C2B0 = D_0028F720[0x180 / 4];
    D_0063C2B4 = D_0028F720[0x184 / 4];
    D_0063C2B8 = D_0028F720[0x190 / 4];
}
ASM_LIT4_SLOT(D_00639134, 3.14159265f);
ASM_LIT4_SLOT(D_00639138, 3.14159265f);
INCLUDE_ASM("asm/nonmatchings/src/camera-root", SetCameraMatrix);
void Camctrl_ExitEveRock(void) {
    if (D_006E6700[2] < 4) {
        Camctrl_ForceTarget(D_0063AB9C);
    }
}
void Camctrl_SetTarget(int a0, int a1, int a2)
{
    if (a2 < D_006E6700[2]) {
        return;
    }
    D_006E6700[0] = a0;
    D_006E6700[1] = a1;
    D_006E6700[2] = a2;
}
extern int D_0063C294;

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
   GetCameraDefaultTargetGObj into InitCamera, so it is `inline` in the dev's
   TU; while SetCameraMatrix is still asm a deferred inline would land at the
   object end instead of here, so the public body stays a plain definition at
   its ROM position and InitCamera calls the static stand-in below. Collapses
   to one `inline` definition at layout. */
int GetCameraDefaultTargetGObj(void) {
    int id = GetEfStageCameraTargetID();
    if (id != 0) {
        int gobj = isysGObjSearchFromObjLayoutID(id);
        if (gobj != 0) {
            return gobj;
        }
    }
    return D_00639EA4;
}
void CameraSetTargetGObj(int a, int b) {
    D_0063C290 = a;
    D_0063C294 = b;
}
extern void sceVu0SubVector(void *, void *, void *);

void CameraChangeTargetParallel(int a0, int a1) {
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
    *(CamTgt *)D_006E66E0 = *(CamTgt *)D_006E66C0;
    sceVu0AddVector(D_006E66E0, D_006E66E0, buf);
    D_006E66E0[6] = 1;
}
int CameraGetTarget(void) {
    return D_0063C290;
}
extern int D_0063C294;

void CameraGetTargets(int *a0, int *a1) {
    *a0 = D_0063C290;
    *a1 = D_0063C294;
}
extern int D_0063C2A0;
extern int D_006E66F8[];

void CameraSetMode(int x) {
    D_0063C2A0 = x;
    D_006E66F8[0] = 0;
}
int CameraGetMode(void) {
    return D_0063C2A0;
}
extern float _GetDirection(void *v);
extern void sceVu0Normalize(void *dst, void *src);

void CameraGetOtherObjOffset(float *pos, float *outDist, int *outAngle)
{
    float v[4];
    int ang;
    *outDist = _DistGV(D_006E66C0, pos);
    sceVu0SubVector(v, pos, D_006E66C0);
    sceVu0Normalize(v, v);
    ang = (int)(_GetDirection(v) / 3.14159265f * 180.0f)
        - ((CameraSet2 *)D_006E66C0)->rotY * 180 / 32768;
    if (ang > 180) {
        ang -= 360;
    }
    if (ang <= -180) {
        ang += 360;
    }
    *outAngle = ang;
}
extern int InsertCamera_isEnable(void);

void InsertCamera_Set(float *pos, float *tgt, int gobj)
{
    if (InsertCamera_isEnable()) {
        D_006E6710.gobj = gobj;
        D_006E6710.w04 = 0;
        D_006E6710.pos[0] = pos[0]; D_006E6710.pos[1] = pos[1]; D_006E6710.pos[2] = pos[2];
        D_006E6710.tgt[0] = tgt[0]; D_006E6710.tgt[1] = tgt[1]; D_006E6710.tgt[2] = tgt[2];
        D_006E6710.enable = 1;
        D_006E6710.cut = 1;
        D_006E6710.cutType = 0;
        D_006E6710.b37 = 1;
        D_006E6710.b38 = 1;
        D_006E6710.blend = -1.0f;
    }
}
void InsertCamera_SetNoraml(float *pos, float *tgt, int gobj, int cutType)
{
    if (InsertCamera_isEnable()) {
        D_006E6710.gobj = gobj;
        D_006E6710.w04 = 0;
        sceVu0ScaleVector(D_006E6710.pos, pos, -1.0f);
        sceVu0ScaleVector(D_006E6710.tgt, tgt, -1.0f);
        D_006E6710.enable = 1;
        D_006E6710.cut = 1;
        D_006E6710.cutType = cutType;
        D_006E6710.b37 = 1;
        D_006E6710.b38 = 1;
        D_006E6710.blend = -1.0f;
    }
}
void InsertCamera_SetDetail(float *pos, float *tgt, int gobj, int cutType, int b37, int b38, float blend)
{
    if (InsertCamera_isEnable()) {
        D_006E6710.gobj = gobj;
        D_006E6710.w04 = 0;
        sceVu0ScaleVector(D_006E6710.pos, pos, -1.0f);
        sceVu0ScaleVector(D_006E6710.tgt, tgt, -1.0f);
        D_006E6710.enable = 1;
        D_006E6710.cut = 1;
        D_006E6710.cutType = cutType;
        D_006E6710.b37 = b37;
        D_006E6710.b38 = b38;
        D_006E6710.blend = blend;
    }
}

void InsertCamera_Exec(float *cam, int *cut, int *cutType, int *enable)
{
    *cut = 0;
    *cutType = 0;
    *enable = 0;
    if (D_006E6710.enable) {
        if (D_006E6710.cut) {
            *cut = 1;
            *cutType = D_006E6710.cutType;
            D_006E6710.cut = 0;
            D_006E6710.cutType = 0;
        }
        cam[0] = D_006E6710.pos[0]; cam[1] = D_006E6710.pos[1]; cam[2] = D_006E6710.pos[2];
        cam[4] = D_006E6710.tgt[0]; cam[5] = D_006E6710.tgt[1]; cam[6] = D_006E6710.tgt[2];
        *enable = 1;
    }
}
int *GetCurrentCameraSet2(void) {
    return D_006E66C0;
}
extern char D_0063C2AC;

void SetCameraFlag_LwsCutBack(void) {
    D_0063C2AC = 1;
}
extern char D_0063C298;

void SetCameraFlag_GamecamCutBack(void) {
    D_0063C298 = 1;
}
extern int D_0063C2B0;
extern int D_0063C2B4;
void SetHandCameraLimitInDemo(int a0, int a1) {
    D_0063C2B0 = a0;
    D_0063C2B4 = a1;
}
extern int D_0028F720[];
extern int D_0063C2B0;
extern int D_0063C2B4;
void ResetHandCameraLimitInDemo(void) {
    D_0063C2B0 = D_0028F720[0x180 / 4];
    D_0063C2B4 = D_0028F720[0x184 / 4];
}
extern int D_0063C2B8;
void SetZoomMaxValInDemo(int a0) {
    D_0063C2B8 = a0;
}
extern int D_0063C2B8;
extern int D_0028F8B0[];
void ResetZoomMaxValInDemo(void) {
    D_0063C2B8 = D_0028F8B0[0];
}
extern int D_0028F8A0[];
extern int D_0063C2B0;
int UpdateHandCameraLimitP(void) {
    D_0063C2B0 = D_0028F8A0[0];
    return 0;
}
extern int D_0028F8A4[];
extern int D_0063C2B4;
int UpdateHandCameraLimitV(void) {
    D_0063C2B4 = D_0028F8A4[0];
    return 0;
}
int UpdateZoomMaxVallInDemo(void) {
    D_0063C2B8 = D_0028F8B0[0];
    return 0;
}
extern int D_006E6708[];

int InsertCamera_isEnable(void) {
    return D_006E6708[0] < 2;
}

void CameraSetCameraPosition(float *src) {
    if (D_0063C2A0 != 3) {
        ((float *)D_006E66C0)[0] = src[0];
        ((float *)D_006E66C0)[1] = src[1];
        ((float *)D_006E66C0)[2] = src[2];
        ((float *)D_006E66E0)[0] = src[0];
        ((float *)D_006E66E0)[1] = src[1];
        ((float *)D_006E66E0)[2] = src[2];
    }
}
void CameraSetTargetPos(void) {}
extern int D_0063AB98;

void *GetCameraPos(void) {
    if (D_0063AB98 == 0) {
        return 0;
    }
    return D_006E66C0;
}
void GetCameraInfo_tmp(void *dst, float *out) {
    union PendCopy *s = (union PendCopy *)D_006E66C0;
    union PendCopy *d = (union PendCopy *)dst;
    d->q[0] = s->q[0];
    d->q[1] = s->q[1];
    d->q[2] = s->q[2];
    d->q[3] = s->q[3];
    *out = D_0063B1B0 / 100.0f;
}
extern unsigned char D_0063C299;

void testcamerazoom(void) {
    D_0063C299 = 1;
}
extern int D_0063AB6C;

void SetMonitorCameraInitializeFlag(void) {
    D_0063AB6C = 1;
}
