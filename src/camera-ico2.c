#include "common.h"

typedef struct {
    int w[23];
} S5C;

typedef union Mat4 {
    float f[4];
    long long q[2];
} Mat4;

typedef struct StageParam {
    char pad0[0x118];
    int camSetId; /* 0x118 */
    char pad11c[0x184 - 0x11C];
    float rate; /* 0x184 */
    char pad188[0x194 - 0x188];
} StageParam;

typedef struct CamSetItem {
    char pad[0x48];
    void *end;
} CamSetItem;

typedef struct {
    int w[19];
} S4C;

typedef struct CamSetHdr {
    char pad0[8];
    int count; /* 0x08 */
    char pad0c[4];
    CamSetItem items[1]; /* 0x10 */
} CamSetHdr;

extern void *D_0063ABB0;
extern int D_0063ABB4;
extern void ReflectCameraSetBinary(S4C *src, int count);
extern StageParam D_005F5D50[];
extern int stage_no;
extern int *D_00639EA4;
extern void GetBoyRootPositionForCamera();
extern void GetRootPosition(void *a0, char *outer);
extern void CameraGetTargets(int *a0, int *a1);
extern float D_006E6560[3];
extern float D_006E6570[3];
extern float D_006E6580[3];
extern float D_006E6590[3];
extern float D_006E6620[3];
extern float D_006E6630[3];
extern void sceVu0ScaleVector(void *a, void *b, float s);
extern float D_0063AB4C[];
extern char *D_0063C264;
extern int D_0063C26C;
extern void memset(float *a0, int a1, int a2);
extern char D_006E64F4[];
extern void SetMonitorCameraInitializeFlag();
extern Mat4 D_00555050;
extern int D_0063AB9C;
extern float FSqrt(float v);
extern void _ApplyRyGV(void *a0, float v);
extern float _GetDirection(void *a0);
extern void _InterGV(void *a0, void *a1, void *a2, float f12, float f13);
extern void sceVu0AddVector(void *dst, void *a, void *b);
extern void sceVu0Normalize(void *a0, void *a1);
extern void sceVu0SubVector(void *dst, void *a, void *b);
extern void *test_CURRENTORIENT(int a0);

typedef struct IosPadStick {
    int x; /* 0x00 */
    int y; /* 0x04 */
    char pad08[0x14 - 0x08];
    float mag; /* 0x14 */
    char pad18[0x20 - 0x18];
} IosPadStick;

extern char iosPadConfDefault[];
extern int iosPadConnect(void *pad, int slot, int port, void *conf);
extern void iosPadRead(void *pad);
extern int iosPadGetStick(void *pad, IosPadStick *out, int a2, int a3, int a4, int a5);
extern float D_0063AB48;
extern int D_0063C274;

typedef struct PluralCameraSet {
    int id;    /* 0x00 */
    void *set; /* 0x04 */
} PluralCameraSet;

extern PluralCameraSet D_006E6640[];
extern char D_00555060[];
extern char D_00555090[];
extern char D_0063AB58[];
extern int D_0063C284;
extern void debug_StdPrintfDummy();
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern void *ReadCameraSet(char *name, int stage);
extern char D_002AD010[][0x20];
extern char D_00555078[];
extern float D_006E6500[];
extern char D_006E6500__pn[] __asm__("D_006E6500");
extern char D_006E6620__pn[] __asm__("D_006E6620");
extern char D_006E6630__pn[] __asm__("D_006E6630");
extern void func_00240038_p(void *a0, void *a1, float f) __asm__("sceVu0ScaleVector");
extern void sceVu0ScaleVector__pn(void *a0, float f) __asm__("sceVu0ScaleVector");
/* prototypes: their order is the inline tail's emission order */
void GetHandCameraStickInfo(float *outX, float *outZ, float *outMag);
void SetCameraZoomOffsetRatio(float val);
int GetCameraGroupCurrent(void);
int GetCameraGroupFromGObj(void *obj);
int GetCameraGroupFromPosition(float *pos);
void AddPluralCameraSet(int id, char *name);
void InitPluralCameraSet(void);
void *GetPluralCameraSet(int id);
void MakeCameraSetBinary(S4C *src, int count, S4C *dst);
int GetSizeOfCameraSetBinary(S4C *p, int n);
void SetCameraTargetPosition(void *a0, float a1);

inline void SetCameraZoomOffsetRatio(float val)
{
    D_0063AB48 = val;
}

void CameraSetCameraSet(int id)
{
    CamSetItem *p;
    CamSetItem *end;
    int n;
    int i;

    D_0063ABB0 = GetPluralCameraSet(id);
    D_0063ABB4 = n = *(int *)((char *)D_0063ABB0 + 8);
    p = (CamSetItem *)((char *)D_0063ABB0 + 0x10);
    end = &p[n];
    for (i = 0; i < n; i++) {
        p[i].end = end;
    }
    ReflectCameraSetBinary((S4C *)p, n);
}

void CameraSetCameraSet_Default(void)
{
    CameraSetCameraSet(D_005F5D50[stage_no].camSetId);
}

void GetRootPositionForCamera(int a0, int a1)
{
    if (a1 == D_00639EA4) {
        GetBoyRootPositionForCamera(a0, a1);
    } else {
        GetRootPosition(a0, a1);
    }
}

inline void SetCameraTargetPosition(void *a0, float a1)
{
    sceVu0ScaleVector__pn(D_006E6500__pn, -1.0f);
    func_00240038_p(D_006E6500__pn + 0x10, a0, -1.0f);
    func_00240038_p(D_006E6620__pn, a0, -1.0f);
    func_00240038_p(D_006E6630__pn, a0, -1.0f);
    *(float *)(D_006E6500__pn + 0x20) = a1;
}

void ico2camera_GetTargetPos(int a0)
{
    unsigned char flag = a0;
    int p1;
    int p2;
    float v0[4];
    float v1[4];
    float v2[4];
    float A[4];
    float B[4];
    float C[4];
    int i;

    CameraGetTargets(&p1, &p2);
    if (p1 == 0) {
        return;
    }
    if (p2 != 0) {
        GetRootPositionForCamera(A, p1);
        GetRootPositionForCamera(B, p2);
        sceVu0ScaleVector(A, A, -1.0f);
        sceVu0ScaleVector(B, B, -1.0f);
        v1[0] = A[0];
        v1[1] = A[1];
        v1[2] = A[2];
        v0[0] = B[0];
        v0[1] = B[1];
        v0[2] = B[2];
        v2[0] = A[0];
        v2[1] = A[1];
        v2[2] = A[2];
    } else {
        GetRootPositionForCamera(C, p1);
        sceVu0ScaleVector(C, C, -1.0f);
        v0[0] = C[0];
        v0[1] = C[1];
        v0[2] = C[2];
        v1[0] = C[0];
        v1[1] = C[1];
        v1[2] = C[2];
        v2[0] = C[0];
        v2[1] = C[1];
        v2[2] = C[2];
    }
    {
        D_006E6590[0] = v2[0];
        D_006E6590[1] = v2[1];
        D_006E6590[2] = v2[2];
    }
    if (flag != 0) {
        float a0 = v0[0];
        float a1 = v0[1];
        float a2 = v0[2];
        D_006E6560[0] = a0;
        D_006E6560[1] = a1;
        D_006E6560[2] = a2;
        D_006E6620[0] = a0;
        D_006E6620[1] = a1;
        D_006E6620[2] = a2;
        D_006E6630[0] = v1[0];
        D_006E6630[1] = v1[1];
        D_006E6630[2] = v1[2];
    }
    for (i = 0; i < 3; i++) {
        D_006E6570[i] = (v0[i] + D_006E6620[i] * 3.0f) * 0.25f;
        D_006E6580[i] = (v1[i] + D_006E6630[i] * 3.0f) * 0.25f;
    }
    D_006E6620[0] = D_006E6570[0];
    D_006E6620[1] = D_006E6570[1];
    D_006E6620[2] = D_006E6570[2];
    D_006E6630[0] = D_006E6580[0];
    D_006E6630[1] = D_006E6580[1];
    D_006E6630[2] = D_006E6580[2];
}

int ico2camera_GetGroupNearest(float *query)
{
    int result = -1;
    float min = D_0063AB4C[0];
    int i;
    for (i = 0; i < D_0063C26C; i++) {
        float buf[4];
        char *entry = D_0063C264 + i * 0x4C;
        float *center = (float *)(entry + 0x20);
        float *range = (float *)(entry + 0x2C);
        int k;
        memset(buf, 0, 0x10);
        for (k = 0; k < 3; k++) {
            float d = query[k] - center[k];
            float r;
            float t;
            if (d < 0.0f)
                d = -d;
            r = range[k];
            if (r < 0.0f)
                r = -r;
            if (r < 0.0f)
                t = 0.0f;
            else if (d < r)
                t = d;
            else
                t = r;
            buf[k] = d - t;
        }
        {
            float sum = buf[0] * buf[0] + buf[1] * buf[1] + buf[2] * buf[2];
            if (sum < min) {
                result = i;
                min = sum;
            }
        }
    }
    return result;
}

void initMonitorCamera(int a0)
{
    /* The two block-local quantities here are the %hi address of D_006E64F4 and
     * the constant 1.  local-alloc orders them by QTY_CMP_PRI =
     * floor_log2(n_refs)*n_refs*size / (death-birth); both have 2 refs and one
     * word, so it reduces to 1/lifetime, and whichever is born LAST wins $2.
     * The ROM has the address in $2 AND emits its `lui` first, which the two
     * orderings cannot both give: writing the constant into a local before the
     * store (`char flag = 1; D_006E64F4[0] = flag;`) fixes the registers but
     * then emits `li` first (2 diffs), and the plain `D_006E64F4[0] = 1;` emits
     * `lui` first but puts the constant in $2 (3 diffs).  Not retired. */
    register char *p = D_006E64F4;
    register int one __asm__("$3") = 1;
    int masked = a0 & 0xFF;
    *p = (char)one;
    if (masked == 0) {
        return;
    }
    SetMonitorCameraInitializeFlag(masked);
}

typedef struct CamWork {
    Mat4 eye; /* 0x00 */
    Mat4 at;  /* 0x10 */
    Mat4 ext; /* 0x20 */
} CamWork;

typedef struct CameraState {
    char pad0[0x44];
    unsigned char active; /* 0x44 */
    char pad45[0x50 - 0x45];
    CamWork work;   /* 0x50 */
    float dbgA[4];  /* 0x80 */
    float dbgB[4];  /* 0x90 */
    float moveDist; /* 0xA0 */
    float atRate;   /* 0xA4 */
} CameraState;

extern CameraState D_006E64B0;
extern int D_0063ABA8;
extern int D_0063ABAC;
extern int D_0063C270;
extern float D_0063C278;
extern float D_0063C27C;
extern int D_0028F4C0[];
extern float _DistGV(void *a0, void *a1);

/* The retail build compiles out this function's debug arms (listing lines
 * 1033-1063 and 1109-1131 carry no instructions), which is why `vDbg` is read
 * at the writeback with nothing having written it, `vDiff` is written and never
 * read, `vSpare` survives only as a frame slot, and the 1098 loop keeps its
 * counter with an empty body. */
void monitorMonitorCamera(CamWork *cam, CamWork *out)
{
    float vDiff[4];
    float vDbg[4];
    float vEye[4];
    float vOut[4];
    float vAt[4];
    float vAt2[4];
    float vSpare[4];
    int p1;
    int p2;
    int flag;
    int i;
    int k;
    int held;
    int mode;
    float len;
    float t;
    float d;
    float d1;
    float d2;
    float r1;
    float r2;

    flag = 0;
    for (i = 0; i < 3; i++) {
        if (1000000.0f < cam->at.f[i] || cam->at.f[i] < -1000000.0f) {
            flag = 1;
            break;
        }
    }
    if (D_006E64B0.active != 0) {
        D_006E64B0.work = *cam;
        D_006E64B0.moveDist = 0.0f;
        D_006E64B0.atRate = 0.0f;
        D_006E64B0.active = 0;
        if (flag != 0 && D_0063C270 < 10) {
            D_006E64B0.active = 1;
        }
        D_006E64B0.dbgA[0] = 0.0f;
        D_006E64B0.dbgA[1] = 0.0f;
        D_006E64B0.dbgA[2] = 0.0f;
        D_006E64B0.dbgB[0] = 0.0f;
        D_006E64B0.dbgB[1] = 0.0f;
        D_006E64B0.dbgB[2] = 0.0f;
        *out = *cam;
        return;
    }
    if (D_0063ABA8 != 0) {
        *cam = D_006E64B0.work;
    }
    *out = *cam;
    vDiff[0] = cam->eye.f[0] - D_006E64B0.work.eye.f[0];
    vDiff[1] = cam->eye.f[1] - D_006E64B0.work.eye.f[1];
    vDiff[2] = cam->eye.f[2] - D_006E64B0.work.eye.f[2];
    sceVu0SubVector(vEye, cam, &D_006E64B0.work);
    len = FSqrt(vEye[0] * vEye[0] + vEye[1] * vEye[1] + vEye[2] * vEye[2]);
    if (D_0063C278 * 30.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 11.0f < len) {
        if (D_0063C278 * 30.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) <
            D_006E64B0.moveDist) {
            D_006E64B0.moveDist =
                D_0063C278 * 30.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
        }
        if (D_006E64B0.moveDist < len) {
            len = D_006E64B0.moveDist +
                  D_0063C278 * 30.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 30.0f;
            sceVu0Normalize(vEye, vEye);
            sceVu0ScaleVector(vEye, vEye, len);
            sceVu0AddVector(out, &D_006E64B0.work, vEye);
        } else {
            len = D_0063C278 * 30.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
            sceVu0Normalize(vEye, vEye);
            sceVu0ScaleVector(vEye, vEye, len);
            sceVu0AddVector(out, &D_006E64B0.work, vEye);
        }
    } else {
        _InterGV(out, cam, &D_006E64B0.work, 10.0f, 1.0f);
        for (k = 0; k < 3; k++) {}
    }
    sceVu0SubVector(vOut, out, &D_006E64B0.work);
    t = FSqrt(vOut[0] * vOut[0] + vOut[1] * vOut[1] + vOut[2] * vOut[2]);
    D_006E64B0.moveDist = t;
    held = 0;
    d = D_0063C27C * 30.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    if (d < 0.0f) {
        d = -d;
    }
    sceVu0SubVector(vAt, &cam->at, &D_006E64B0.work.at);
    len = FSqrt(vAt[0] * vAt[0] + vAt[1] * vAt[1] + vAt[2] * vAt[2]);
    sceVu0Normalize(vAt, vAt);
    CameraGetTargets(&p1, &p2);
    if (p1 == D_00639EA4) {
        held = (p2 == 0);
    }
    if (held == 0 && 95.0f <= d) {
        d = (float)(600 / ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
    }
    if (d * 9.0f < len) {
        D_006E64B0.atRate = D_006E64B0.atRate + 0.5f;
        if (d < D_006E64B0.atRate) {
            D_006E64B0.atRate = d;
        }
        sceVu0ScaleVector(vAt, vAt, D_006E64B0.atRate);
        sceVu0AddVector(&out->at, &D_006E64B0.work.at, vAt);
    } else {
        mode = 8;
        if (held != 0) {
            if (115.0f <= d) {
                mode = 1;
            } else if (105.0f <= d) {
                mode = 2;
            } else if (95.0f <= d) {
                mode = 4;
            }
        }
        _InterGV(&out->at, &cam->at, &D_006E64B0.work.at,
                 mode * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 30.0f,
                 30.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
        sceVu0SubVector(vAt, &out->at, &D_006E64B0.work.at);
        len = FSqrt(vAt[0] * vAt[0] + vAt[1] * vAt[1] + vAt[2] * vAt[2]);
        if (d < len) {
            len = d;
        }
        sceVu0Normalize(vAt, vAt);
        sceVu0ScaleVector(vAt, vAt, len);
        sceVu0AddVector(&out->at, &D_006E64B0.work.at, vAt);
        sceVu0SubVector(vAt2, &out->at, &D_006E64B0.work.at);
        len = FSqrt(vAt2[0] * vAt2[0] + vAt2[1] * vAt2[1] + vAt2[2] * vAt2[2]);
        D_006E64B0.atRate = len;
        if (d < len) {
            D_006E64B0.atRate = d;
        }
    }
    if (out->ext.f[0] - D_006E64B0.work.ext.f[0] != 0.0f) {
        d1 = _DistGV(out, cam);
        d2 = _DistGV(out, &D_006E64B0.work);
        if (d1 + d2 != 0.0f) {
            out->ext.f[0] = (out->ext.f[0] * d2 + D_006E64B0.work.ext.f[0] * d1) / (d1 + d2);
        }
    }
    if (D_0063ABAC != 0) {
        r1 = (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 30.0;
        r2 = 3.0 / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
        _InterGV(out, cam, &D_006E64B0.work, r1, r2);
        _InterGV(&out->at, &cam->at, &D_006E64B0.work.at, r1, r2);
        out->ext.f[0] = (cam->ext.f[0] * r2 + D_006E64B0.work.ext.f[0] * r1) / (r1 + r2);
    }
    D_006E64B0.work = *out;
    D_006E64B0.dbgA[0] = vDbg[0];
    D_006E64B0.dbgA[1] = vDbg[1];
    D_006E64B0.dbgA[2] = vDbg[2];
}

void ChaseCamera(float *a0, float *a1)
{
    Mat4 v0;
    Mat4 v1;
    Mat4 mat;
    Mat4 v3;
    float t;
    mat = D_00555050;
    t = _GetDirection(test_CURRENTORIENT(D_0063AB9C));
    _ApplyRyGV(&mat, (float)(int)(t / 3.1415927f * 180.0f) * 3.1415927f / 180.0f);
    sceVu0AddVector(&v0, a0, &mat);
    sceVu0SubVector(&v3, a1, a0);
    v3.f[1] = 0.0f;
    FSqrt(v3.f[0] * v3.f[0] + v3.f[1] + v3.f[2] * v3.f[2]);
    sceVu0Normalize(&v3, &v3);
    sceVu0ScaleVector(&v3, &v3, -500.0f);
    sceVu0AddVector(&v1, &v3, a0);
    v1.f[1] = a0[1] + 200.0f;
    _InterGV(a1, &v0, &v1, 4.0f, 5.0f);
    a1[0] = v0.f[0];
    a1[1] = v0.f[1];
    a1[2] = v0.f[2];
    a1[4] = a0[0];
    a1[5] = a0[1];
    a1[6] = a0[2];
    a1[8] = 50.0f;
}

extern char *D_0063C264;
extern int D_0063C270;
extern float D_0063C278;
extern float D_0063C27C;
extern int D_0028F4C0[];
extern int D_0063B178;
extern void debug_Marker(void *buf, int a1, int a2, int a3, float f12, float f13);

/* Static helper at camera-ico2.c lines 149-158 of the listing, hosted by both
 * InitIco2Camera and CameraMove, so the name is ours: it scales the two
 * hand-camera correction rates by the frame budget and reports the frame step.
 * The divisor is spelled out at every use, as the same idiom is in
 * src/hand-camera.c, so cse keeps a single `div` and the redundant div_trap
 * insns survive with no encoding of their own. */
static inline int setHandCameraRates(float a, float b)
{
    D_0063C278 = a * 60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    D_0063C27C = b * 60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    return (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1];
}

typedef struct CamMoveItem { /* 0x5C */
    float v[3];              /* 0x00 */
    float pos[3];            /* 0x0C */
    float ofs[3];            /* 0x18 */
    int flag;                /* 0x24 */
    float w28;               /* 0x28 */
    char pad2C[0x30 - 0x2C];
    float range; /* 0x30 */
    char pad34[0x38 - 0x34];
    float w38; /* 0x38 */
    float w3C; /* 0x3C */
    float w40; /* 0x40 */
    float w44; /* 0x44 */
    char pad48[0x50 - 0x48];
    float z[3]; /* 0x50 */
} CamMoveItem;

typedef struct CamSetGroup { /* 0x4C */
    char pad0[0x38];
    int first; /* 0x38 */
    int last;  /* 0x3C */
    int mode;  /* 0x40 */
    char pad44[0x48 - 0x44];
    CamMoveItem *items; /* 0x48 */
} CamSetGroup;

#define CAMSET_GROUP(n) ((CamSetGroup *)(D_0063C264 + (n) * 0x4C))

extern float D_006E6320[];
extern float D_006E6190[];
extern int D_0063AB50;
extern void SetLimitHandCameraCorrect(float a, float b);

/* camera-ico2.c lines 362-380 of the listing: the mean and the standard
 * deviation of the first `n` weights, written back through two pointers. */
static inline void cameraWeightStat(float *arr, int n, float *outSd, float *outMean)
{
    float var;
    int j;

    *outMean = 0.0f;
    for (j = 0; j < n; j++) {
        *outMean = *outMean + arr[j];
    }
    *outMean = *outMean / (float)n;
    var = 0.0f;
    for (j = 0; j < n; j++) {
        float t = arr[j] - *outMean;
        var = var + t * t;
    }
    *outSd = FSqrt(var / (float)n);
}

void CameraMove(int group, float *pos, float *out, float *ofsA, float *ofsB)
{
    float acc[4];
    Mat4 q;
    float sd;
    float mean;
    CamMoveItem *p;
    CamMoveItem *r;
    int i;
    int j;
    float sum;
    float total;
    float w;
    float u;
    float d;
    float t;
    float rate;
    float e0;
    float e1;
    float e2;
    float e3;
    float e4;

    if (CAMSET_GROUP(group)->mode == 2) {
        ChaseCamera(pos, out);
        return;
    }
    ofsA[0] = 300.0f;
    ofsA[1] = 100.0f;
    ofsA[2] = 0.0f;
    sum = ofsA[2];
    i = 0;
    for (p = &CAMSET_GROUP(group)->items[CAMSET_GROUP(group)->first];
         p != &CAMSET_GROUP(group)->items[CAMSET_GROUP(group)->last]; p++) {
        if (p->flag != 0) {
            {
                Mat4 tv;
                memset(tv.f, 0, 0x10);
                tv.f[0] = p->pos[0];
                tv.f[1] = p->pos[1];
                tv.f[2] = p->pos[2];
                q = tv;
            }
            d = _DistGV(pos, &q);
            D_006E6190[i] = D_006E6320[i] = d;
            sum = sum + d;
            i++;
        }
    }
    if (i == 1) {
        D_006E6320[0] = 1.0f;
    } else if (i < 5) {
        i = 0;
        for (p = &CAMSET_GROUP(group)->items[CAMSET_GROUP(group)->first];
             p != &CAMSET_GROUP(group)->items[CAMSET_GROUP(group)->last]; p++) {
            if (p->flag != 0) {
                D_006E6320[i] = (sum - D_006E6320[i]) * (sum - D_006E6320[i]);
                i++;
            }
        }
    } else {
        cameraWeightStat(D_006E6320, i, &sd, &mean);
        i = 0;
        for (p = &CAMSET_GROUP(group)->items[CAMSET_GROUP(group)->first];
             p != &CAMSET_GROUP(group)->items[CAMSET_GROUP(group)->last]; p++) {
            if (p->flag != 0) {
                D_006E6320[i] = (D_006E6320[i] - mean) * 10.0f / sd + 50.0f;
                if (D_006E6320[i] < 0.0f || 100.0f < D_006E6320[i]) {
                    D_006E6320[i] = 0.0f;
                }
                D_006E6320[i] = 100.0f - D_006E6320[i];
                if (D_006E6320[i] < 40.0f) {
                    D_006E6320[i] = 0.0f;
                } else {
                    D_006E6320[i] = D_006E6320[i] - 40.0f;
                }
                D_006E6320[i] = (D_006E6320[i] * D_006E6320[i]) * (D_006E6320[i] * D_006E6320[i]);
                i++;
            }
        }
    }
    i = 0;
    for (p = &CAMSET_GROUP(group)->items[CAMSET_GROUP(group)->first];
         p != &CAMSET_GROUP(group)->items[CAMSET_GROUP(group)->last]; p++) {
        if (p->flag != 0) {
            if (p->range != 0.0f && D_006E6190[i] < p->range) {
                u = (D_006E6190[i] - 100.0f) / p->range;
                rate = u < 0.0001f ? 0.0001f : (1.0f < u ? 1.0f : u);
                j = 0;
                for (r = &CAMSET_GROUP(group)->items[CAMSET_GROUP(group)->first];
                     r != &CAMSET_GROUP(group)->items[CAMSET_GROUP(group)->last]; r++) {
                    if (r->flag != 0) {
                        if (j != i) {
                            D_006E6320[j] = D_006E6320[j] * rate;
                        }
                        j++;
                    }
                }
            }
            i++;
        }
    }
    total = 0.0f;
    i = 0;
    for (p = &CAMSET_GROUP(group)->items[CAMSET_GROUP(group)->first];
         p != &CAMSET_GROUP(group)->items[CAMSET_GROUP(group)->last]; p++) {
        if (p->flag != 0) {
            total = total + D_006E6320[i];
            i++;
        }
    }
    acc[0] = acc[1] = acc[2] = 0.0f;
    ofsA[0] = 0.0f;
    ofsA[1] = 0.0f;
    ofsA[2] = 0.0f;
    ofsB[0] = 0.0f;
    ofsB[1] = 0.0f;
    ofsB[2] = 0.0f;
    e0 = 0.0f;
    e1 = 0.0f;
    e2 = 0.0f;
    e3 = 0.0f;
    e4 = 0.0f;
    i = 0;
    for (p = &CAMSET_GROUP(group)->items[CAMSET_GROUP(group)->first];
         p != &CAMSET_GROUP(group)->items[CAMSET_GROUP(group)->last]; p++) {
        if (p->flag != 0) {
            w = D_006E6320[i] / total;
            acc[0] = acc[0] + p->v[0] * w;
            acc[1] = acc[1] + p->v[1] * w;
            acc[2] = acc[2] + p->v[2] * w;
            e0 = e0 + p->w28 * w;
            e1 = e1 + p->w38 * w;
            e2 = e2 + p->w3C * w;
            e3 = e3 + p->w40 * w;
            e4 = e4 + p->w44 * w;
            ofsA[0] = ofsA[0] + p->ofs[0] * w;
            ofsA[1] = ofsA[1] + p->ofs[1] * w;
            ofsA[2] = ofsA[2] + p->ofs[2] * w;
            ofsB[0] = ofsB[0] + p->z[0] * w;
            ofsB[1] = ofsB[1] + p->z[1] * w;
            ofsB[2] = ofsB[2] + p->z[2] * w;
            if (D_0063B178 != 0) {
                if (0.0f < p->range) {
                    debug_Marker(p->pos, (int)(w * 255.0f), 0, 0, p->range, (float)D_0063AB50);
                } else {
                    debug_Marker(p->pos, 0, (int)(w * 255.0f), 0, 100.0f, (float)D_0063AB50);
                }
            }
            i++;
        }
    }
    D_0063AB50 = D_0063AB50 + 2;
    out[0] = acc[0];
    out[1] = acc[1];
    out[2] = acc[2];
    out[4] = pos[0];
    out[5] = pos[1];
    out[6] = pos[2];
    setHandCameraRates(e1, e2);
    SetLimitHandCameraCorrect(e3, e4);
    out[8] = e0;
}

inline int GetSizeOfCameraSetBinary(S4C *p, int n)
{
    int size = n * 0x4C;
    int i;
    for (i = 0; i < n; i++) {
        size += (p->w[15] - p->w[14]) * 0x5C;
        p++;
    }
    return size;
}

inline void MakeCameraSetBinary(S4C *src, int count, S4C *dst)
{
    S4C **new_var;
    int total = 0;
    S4C *sEnd = src + count;
    S5C *out = (S5C *)(dst + count);
    int outBase = (int)out;
    new_var = &sEnd;
    if (src == (*new_var)) {
        return;
    }
    do {
        S5C *is;
        *dst = *src;
        dst->w[14] = total;
        dst->w[18] = outBase;
        is = ((S5C *)src->w[18]) + src->w[14];
        while (is != (((S5C *)src->w[18]) + src->w[15])) {
            *out = *is;
            out++;
            total++;
            is++;
        }

        dst->w[15] = total;
        dst++;
        src++;
    } while (src != sEnd);
}

extern char *D_0063C260;
extern char *D_0063C268;
extern int D_0063A450;
extern void iosFree(void *p);
extern char *iosMallocDebug(int heap, int size, char *file, int line);

void ReflectCameraSetBinary(S4C *src, int count)
{
    if (D_0063C260 != 0) {
        iosFree(D_0063C260);
    }

    D_0063C260 = iosMallocDebug(D_0063A450, GetSizeOfCameraSetBinary(src, count), D_00555060, 1577);
    D_0063C264 = D_0063C260;
    D_0063C268 = D_0063C260 + count * 0x4C;
    D_0063C26C = count;
    MakeCameraSetBinary(src, count, (S4C *)D_0063C260);
}

extern int D_0063C270;
extern float D_0063C278;
extern float D_0063C27C;
extern unsigned char D_0063C280;
extern int D_0028F4C0[];
extern void InitHandCameraCorrect(void);

void InitIco2Camera(void)
{
    D_0063C270 = 0;
    D_0063C260 = 0;
    CameraSetCameraSet_Default();
    initMonitorCamera(1);
    D_0063C274 = -1;
    D_0063C280 = 1;
    setHandCameraRates(D_005F5D50[stage_no].rate, 10.0f);
    InitHandCameraCorrect();
}

extern float D_002A5E60[3];
extern int ACTNotNeedCameraOffset(char *a0);

void GetTargetOffset(char *gobj, float *v, unsigned char flag)
{
    float ofs[4];
    float w[4];
    char *p;
    int n;
    int need;

    if ((int)gobj == D_0063AB9C && gobj != 0) {
        n = (int)(_GetDirection(test_CURRENTORIENT((int)gobj)) / 3.1415927f * 180.0f);
        ofs[0] = v[0];
        ofs[1] = v[1];
        ofs[2] = -v[2];
        need = ACTNotNeedCameraOffset(gobj) ? 1 : flag;
        if (need) {
            D_002A5E60[0] = 0.0f;
            D_002A5E60[1] = 0.0f;
            D_002A5E60[2] = 0.0f;
        }
        _ApplyRyGV(ofs, (float)n * 3.1415927f / 180.0f);
        p = *(char **)(gobj + 0x15C);
        if (3.0f < FSqrt(*(float *)(p + 0x130) * *(float *)(p + 0x130) +
                         *(float *)(p + 0x138) * *(float *)(p + 0x138))) {
            sceVu0SubVector(w, ofs, D_002A5E60);
            if (FSqrt(w[0] * w[0] + w[1] * w[1] + w[2] * w[2]) < 1.5f) {
                D_002A5E60[0] = ofs[0];
                D_002A5E60[1] = ofs[1];
                D_002A5E60[2] = ofs[2];
            } else {
                sceVu0Normalize(w, w);
                sceVu0ScaleVector(w, w, 1.5f);
                sceVu0AddVector(D_002A5E60, D_002A5E60, w);
            }
        }
        v[0] = D_002A5E60[0];
        v[1] = D_002A5E60[1];
        v[2] = D_002A5E60[2];
    }
}

inline void GetHandCameraStickInfo(float *outX, float *outZ, float *outMag)
{
    int padCtx[0x60 / 4];
    IosPadStick st;

    iosPadConnect(padCtx, 0, 0, iosPadConfDefault);
    iosPadRead(padCtx);
    iosPadGetStick(padCtx, &st, 1, 2, 2, 0);
    {
        Mat4 dir = {{(float)st.x - 127.5f, 0.0f, (float)st.y - 127.5f, 0.0f}};

        sceVu0Normalize(&dir, &dir);
        *outMag = st.mag;
        *outX = dir.f[0] * *outMag;
        *outZ = dir.f[2] * *outMag;
    }
}

extern int D_0063ABA4;
extern int D_0063B178;
extern void CameraMove(int group, float *pos, float *out, float *ofsA, float *ofsB);
extern void InsertCamera_Exec(float *cam, int *cut, int *cutType, int *enable);
extern void SetWSMatrix(void *cam);
extern void debug_Marker(void *buf, int a1, int a2, int a3, float f12, float f13);
extern unsigned char IsAbleBoyControl(void);
extern void ClearHandCameraCorrect(void);
extern void HandCameraCorrect(void *a0, void *a1, int a2, float f12, float f13, float f14);

/* The camera-group search the listing places at camera-ico2.c lines 921-946:
 * a static helper shared by GetCameraGroupFromGObj, GetCameraGroupFromPosition
 * and SetCameraMatrix_Ico2. */
static inline int findCameraGroupContaining(float *pos)
{
    int result = -1;
    int i;
    for (i = 0; i < D_0063C26C; i++) {
        int k = 0;
        char *entry = D_0063C264 + i * 0x4C;
        float *range = (float *)(entry + 0x2C);
        float *center = (float *)(entry + 0x20);
        float *p = pos;
        do {
            if (*p < *center - *range) {
                break;
            }
            if (*center + *range < *p) {
                break;
            }
            p++;
            range++;
            center++;
        } while (++k < 3);
        if (k == 3) {
            result = i;
            break;
        }
    }
    return result;
}

void SetCameraMatrix_Ico2(int flag)
{
    CamWork cw = D_006E64B0.work;
    float vA[4];
    float vB[4];
    CamWork cw2;
    int cut;
    int cutType;
    int enable;
    int mode = 1;
    int changed = 0;
    unsigned char f8;
    int group;

    if (D_0063C280 != 0) {
        flag = 1;
        D_0063C280 = 0;
        changed = 1;
    }
    if (flag) {
        changed = mode;
    }
    f8 = flag;
    ico2camera_GetTargetPos(f8);
    group = findCameraGroupContaining(D_006E6590);
    if (changed && group == -1) {
        group = ico2camera_GetGroupNearest(D_006E6590);
    }
    if (group == -1) {
        cw = D_006E64B0.work;
        cw.at.f[0] = D_006E6570[0];
        cw.at.f[1] = D_006E6570[1];
        cw.at.f[2] = D_006E6570[2];
        memset(vA, 0, 0x10);
        GetTargetOffset((char *)D_0063AB9C, vA, 0);
        sceVu0ScaleVector(vA, vA, D_0063AB48);
        sceVu0AddVector(cw.at.f, cw.at.f, vA);
    } else {
        if (flag != 0 ||
            (D_0063C274 != -1 && *(int *)(D_0063C264 + group * 0x4C + 0x44) !=
                                     *(int *)(D_0063C264 + D_0063C274 * 0x4C + 0x44))) {
            initMonitorCamera(1);
            f8 = 1;
        }
        memset(vA, 0, 0x10);
        memset(vB, 0, 0x10);
        CameraMove(group, D_006E6580, (float *)&cw, vA, vB);
        cw.at.f[0] = D_006E6570[0];
        cw.at.f[1] = D_006E6570[1];
        cw.at.f[2] = D_006E6570[2];
        GetTargetOffset((char *)D_0063AB9C, vA, f8);
        sceVu0ScaleVector(vA, vA, D_0063AB48);
        sceVu0ScaleVector(vB, vB, D_0063AB48);
        sceVu0AddVector(cw.at.f, cw.at.f, vA);
        sceVu0AddVector(cw.at.f, cw.at.f, vB);
        D_0063C274 = group;
    }
    InsertCamera_Exec((float *)&cw, &cut, &cutType, &enable);
    if (cut != 0) {
        initMonitorCamera(cutType == 0);
    }
    if (enable != 0) {
        mode = 0;
        D_0063ABA4 = 1;
    }
    monitorMonitorCamera(&cw, &cw2);
    cw = cw2;
    if (D_0063B178 != 0) {
        debug_Marker(cw.at.f, 0, 0, 255, 100.0f, 0.0f);
    }
    sceVu0ScaleVector(&cw, &cw, -1.0f);
    sceVu0ScaleVector(cw.at.f, cw.at.f, -1.0f);
    {
        float sx;
        float sz;
        float mag;

        GetHandCameraStickInfo(&sx, &sz, &mag);
        if (D_0028F4C0[5] != 0 || IsAbleBoyControl() == 0 || mode == 0) {
            ClearHandCameraCorrect();
        } else {
            HandCameraCorrect(&cw, cw.at.f, 0, sx, sz,
                              60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
        }
    }
    SetWSMatrix(&cw);
    D_0063C270 = D_0063C270 + 1;
}

inline void *GetPluralCameraSet(int id)
{
    int i;

    for (i = 0; i < D_0063C284; i++) {
        if (D_006E6640[i].id == id) {
            return D_006E6640[i].set;
        }
    }
    debug_StdPrintfDummy(D_00555078, D_002AD010[id]);
    debug_assert(D_00555060, 0x7F4);
    __assert(D_00555060, 0x7F4, D_0063AB58);
    return 0;
}

inline void AddPluralCameraSet(int id, char *name)
{
    PluralCameraSet *p;

    if (D_0063C284 >= 10) {
        debug_StdPrintfDummy(D_00555090, 10);
        debug_assert(D_00555060, 0x7FD);
        __assert(D_00555060, 0x7FD, D_0063AB58);
    }
    p = &D_006E6640[D_0063C284];
    p->id = id;
    p->set = ReadCameraSet(name, stage_no);
    D_0063C284++;
}

inline void InitPluralCameraSet(void)
{
    D_0063C284 = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", ReadCameraSet);

inline int GetCameraGroupCurrent(void)
{
    return D_0063C274;
}

inline int GetCameraGroupFromGObj(void *obj)
{
    float buf[4];
    float *bp;
    int result;
    int i;
    GetRootPosition(buf, obj);
    sceVu0ScaleVector(buf, buf, -1.0f);
    bp = buf;
    result = -1;
    for (i = 0; i < D_0063C26C; i++) {
        int k = 0;
        char *entry = D_0063C264 + i * 0x4C;
        float *range = (float *)(entry + 0x2C);
        float *center = (float *)(entry + 0x20);
        float *p = bp;
        do {
            if (*p < *center - *range) {
                break;
            }
            if (*center + *range < *p) {
                break;
            }
            p++;
            range++;
            center++;
        } while (++k < 3);
        if (k == 3) {
            result = i;
            break;
        }
    }
    return result;
}

inline int GetCameraGroupFromPosition(float *pos)
{
    float buf[4];
    float *bp;
    int result;
    int i;
    sceVu0ScaleVector(buf, pos, -1.0f);
    bp = buf;
    result = -1;
    for (i = 0; i < D_0063C26C; i++) {
        int k = 0;
        char *entry = D_0063C264 + i * 0x4C;
        float *range = (float *)(entry + 0x2C);
        float *center = (float *)(entry + 0x20);
        float *p = bp;
        do {
            if (*p < *center - *range) {
                break;
            }
            if (*center + *range < *p) {
                break;
            }
            p++;
            range++;
            center++;
        } while (++k < 3);
        if (k == 3) {
            result = i;
            break;
        }
    }
    return result;
}
