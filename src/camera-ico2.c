#include "common.h"

typedef struct { int w[23]; } S5C;

typedef union Mat4 { float f[4]; long long q[2]; } Mat4;

typedef struct StageParam {
    char pad0[0x118];
    int camSetId;               /* 0x118 */
    char pad11c[0x184 - 0x11C];
    float rate;                 /* 0x184 */
    char pad188[0x194 - 0x188];
} StageParam;

typedef struct CamSetItem {
    char pad[0x48];
    void *end;
} CamSetItem;
typedef struct { int w[19]; } S4C;
typedef struct CamSetHdr {
    char pad0[8];
    int count; /* 0x08 */
    char pad0c[4];
    CamSetItem items[1]; /* 0x10 */
} CamSetHdr;

extern void *D_0063ABB0;
extern int D_0063ABB4;
extern int GetPluralCameraSet(int key);
extern void ReflectCameraSetBinary(S4C *src, int count);

INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", CameraSetCameraSet);
extern StageParam D_005F5D50[];
extern int stage_no;

void CameraSetCameraSet_Default(void) {
    CameraSetCameraSet(D_005F5D50[stage_no].camSetId);
}
extern int *D_00639EA4;
extern void GetBoyRootPositionForCamera();
extern void GetRootPosition(void *a0, char *outer);

void GetRootPositionForCamera(int a0, int a1)
{
    if (a1 == D_00639EA4) {
        GetBoyRootPositionForCamera(a0, a1);
    } else {
        GetRootPosition(a0, a1);
    }
}
extern void CameraGetTargets(int *a0, int *a1);
extern float D_006E6560[3];
extern float D_006E6570[3];
extern float D_006E6580[3];
extern float D_006E6590[3];
extern float D_006E6620[3];
extern float D_006E6630[3];
extern void sceVu0ScaleVector(void *a, void *b, float s);

void ico2camera_GetTargetPos(int a0) {
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
extern float D_0063AB4C[];
extern char *D_0063C264;
extern int D_0063C26C;
extern void memset(float *a0, int a1, int a2);

int ico2camera_GetGroupNearest(float *query) {
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
                if (d < 0.0f) d = -d;
                r = range[k];
                if (r < 0.0f) r = -r;
                if (r < 0.0f) t = 0.0f;
                else if (d < r) t = d;
                else t = r;
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
extern char D_006E64F4[];
extern void SetMonitorCameraInitializeFlag();

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
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", monitorMonitorCamera);
extern Mat4 D_00555050;
extern float D_00639120;
extern int D_0063AB9C;
extern float FSqrt(float v);
extern void _ApplyRyGV(void *a0, float v);
extern float _GetDirection(void *a0);
extern void _InterGV(void *a0, void *a1, void *a2, float f12, float f13);
extern void sceVu0AddVector(void *dst, void *a, void *b);
extern void sceVu0Normalize(void *a0, void *a1);
extern void sceVu0SubVector(void *dst, void *a, void *b);
extern void *test_CURRENTORIENT(int a0);

void ChaseCamera(float *a0, float *a1) {
    Mat4 v0;
    Mat4 v1;
    Mat4 mat;
    Mat4 v3;
    float t;
    mat = D_00555050;
    t = _GetDirection(test_CURRENTORIENT(D_0063AB9C));
    _ApplyRyGV(&mat, (float)(int)(t / D_00639120 * 180.0f) * D_00639120 / 180.0f);
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
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", CameraMove);
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", ReflectCameraSetBinary);
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", InitIco2Camera);
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", GetTargetOffset);
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", SetCameraMatrix_Ico2);
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", ReadCameraSet);
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", GetHandCameraStickInfo);
extern float D_0063AB48;

void SetCameraZoomOffsetRatio(float val) {
    D_0063AB48 = val;
}
extern int D_0063C274;

int GetCameraGroupCurrent(void) {
    return D_0063C274;
}
int GetCameraGroupFromGObj(void *obj) {
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
int GetCameraGroupFromPosition(float *pos) {
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
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", AddPluralCameraSet);
extern int D_0063C284;

void InitPluralCameraSet(void) {
    D_0063C284 = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/camera-ico2", GetPluralCameraSet);
void MakeCameraSetBinary(S4C *src, int count, S4C *dst)
{
  S4C **new_var;
  int total = 0;
  S4C *sEnd = src + count;
  S5C *out = (S5C *) (dst + count);
  int outBase = (int) out;
  new_var = &sEnd;
  if (src == (*new_var))
  {
    return;
  }
  do
  {
    S5C *is;
    *dst = *src;
    dst->w[14] = total;
    dst->w[18] = outBase;
    is = ((S5C *) src->w[18]) + src->w[14];
    while (is != (((S5C *) src->w[18]) + src->w[15]))
    {
      *out = *is;
      out++;
      total++;
      is++;
    }

    dst->w[15] = total;
    dst++;
    src++;
  }
  while (src != sEnd);
}
int GetSizeOfCameraSetBinary(S4C *p, int n) {
    int size = n * 0x4C;
    int i;
    for (i = 0; i < n; i++) {
        size += (p->w[15] - p->w[14]) * 0x5C;
        p++;
    }
    return size;
}
extern float D_006E6500[];

extern char D_006E6500__pn[] __asm__("D_006E6500");
extern char D_006E6620__pn[] __asm__("D_006E6620");
extern char D_006E6630__pn[] __asm__("D_006E6630");
extern void func_00240038_p(void *a0, void *a1, float f) __asm__("sceVu0ScaleVector");
extern void sceVu0ScaleVector__pn(void *a0, float f) __asm__("sceVu0ScaleVector");

void SetCameraTargetPosition(void *a0, float a1) {
    sceVu0ScaleVector__pn(D_006E6500__pn, -1.0f);
    func_00240038_p(D_006E6500__pn + 0x10, a0, -1.0f);
    func_00240038_p(D_006E6620__pn, a0, -1.0f);
    func_00240038_p(D_006E6630__pn, a0, -1.0f);
    *(float *)(D_006E6500__pn + 0x20) = a1;
}
