#include "common.h"
#include "itou_common.h"
#include "sugiCommon.h"

extern void ExecMotionOrient();
extern void iosOmSendMail(void *a0);
extern float acosf(float a0);
extern float sceVu0InnerProduct(void *a0, void *a1);
extern void sceVu0Normalize(void *dst, void *src);
extern void _ACTWait(int a0);
extern void Debug_StickControl(char *self);
/* Actor sub-thread body: the actor scheduler resumes this frame after every
   _ACTWait yield, so the entry GObj lives in its stack home, not a register. */
/* Actor sub-thread body: the actor scheduler resumes this frame after every
   _ACTWait yield, so the entry GObj lives in its stack home, not a register. */
extern void *actInitialize(void *a0);
extern void actCreateSubThread(void *entry, int prio);
extern void func_0019E7F8();
extern int SetMotionRequest(void *a0, int id, void *work);
extern char D_00555788[];
extern void *D_0063A438;
extern char *iosMallocDebug(void *heap, int size, char *file, int line);
extern void memset(void *dst, int c, int n);
extern void CopyVector(void *dst, void *src);
extern void InitMotionOrient(void *o, int a1, int a2, int a3, int a4, int a5);
extern void SetLodLevel(void *o, int lod);

typedef union {
    int i;
    float f;
} IntFloat;

extern void _ACTSendMailToBird();
extern void *isysGObjSearchFromObjKindID_begin(int id);
extern void *isysGObjSearchFromObjKindID_next(void *o);
/* prototypes: their order is the inline tail's emission order */
float vector_angle_degree(void *a0, void *a1);
void subBirdControl(void *volatile gobj);
void subBirdCollision(void *volatile gobj);
void actBirdStart(void *a0);
char *InitBirdGeo(char *a0, void *a1);
void BirdAI(void);
void _ACTSendMailToBirdAll(void *a0, void *a1);

inline float vector_angle_degree(void *a0, void *a1)
{
    float v0[4];
    float v1[4];
    sceVu0Normalize(v0, a0);
    sceVu0Normalize(v1, a1);
    return radians_to_degrees(acosf(sceVu0InnerProduct(v0, v1)));
}

extern void sceVu0CopyVector(void *dst, void *src);
extern void sceVu0ScaleVectorXYZ(void *dst, void *src, float s);
extern void sceVu0AddVector(void *dst, void *a, void *b);
extern void sceVu0DivVector(void *dst, void *src, float s);
extern float GetTableSin(short a0);

void interp_vector_sa(float *dst, float *a, float *b, float sa)
{
    float na[4];
    float nb[4];
    float va[4];
    float vb[4];
    float sum[4];
    float ang;
    /* fraction of the full angle that the `sa` step covers; a separate local
       from the parameter is what ROM's register file shows (`sa` dies at the
       divide, and this one lives on through the three GetTableSin calls). */
    float rate;

    sceVu0Normalize(na, a);
    sceVu0Normalize(nb, b);
    ang = acosf(sceVu0InnerProduct(na, nb));
    if (ang < sa) {
        sceVu0CopyVector(dst, nb);
        return;
    }

    rate = sa / ang;
    sceVu0ScaleVectorXYZ(va, na, GetTableSin((short)((1.0f - rate) * ang * 10430.378f)));
    sceVu0ScaleVectorXYZ(vb, nb, GetTableSin((short)(rate * ang * 10430.378f)));
    sceVu0AddVector(sum, va, vb);
    sceVu0DivVector(dst, sum, GetTableSin((short)(ang * 10430.378f)));
}

extern void GetRootPosition(void *dst, void *self);
extern void SetRootPosition(void *self, void *src);
extern void _GetMotionDirection(void *dst, void *self);
extern float _GetLengthXZ(void *a, void *b);

typedef struct BirdMailEntry {
    /* 0x0 */ unsigned int mail;
    /* 0x4 */ void *data;
} BirdMailEntry;

typedef struct BirdMailQueue {
    /* 0x00 */ int unk0;
    /* 0x04 */ int num;
    /* 0x08 */ BirdMailEntry e[1];
} BirdMailQueue;

typedef struct {
    float f[8];
} BirdMotBlock;

void birdBeforeFunc(char *self)
{
    char *act = *(char **)(self + 0x164);
    char *w = *(char **)(*(char **)(self + 0x15C) + 0x830);
    float there[4];
    float here[4];
    int i;
    BirdMailQueue *q = (BirdMailQueue *)(self + 0x54);

    for (i = 0; i < q->num; i++) {
        BirdMailEntry *e = &q->e[i];
        float len;

        GetRootPosition(there, e->data);
        GetRootPosition(here, self);
        len = _GetLengthXZ(there, here);
        switch (e->mail) {
        case 0x1A7:
            if (len < 200.0f) {
                *(char *)(w + 0x10) = 1;
                GetRootPosition(w + 0x20, e->data);
            }
            break;

        case 0x1A8:
            if (len < 250.0f) {
                *(int *)(act + 0x130) = SetMotionRequest(self, 0x141, act + 0x620);
            }
            break;

        case 0xA: {
            int st = *(int *)(*(int *)(self + 0x15C) + 0x4A0);

            if (st >= 0x473 && st <= 0x475) {
                *(int *)(act + 0x130) = SetMotionRequest(self, 0x142, act + 0x620);
            }
            break;
        }

        case 0x7:
            *(int *)(act + 0x130) = SetMotionRequest(self, 0x141, act + 0x620);
            break;

        case 0x1A:
        case 0x1B:
            *(int *)(act + 0x130) = SetMotionRequest(self, 0x141, act + 0x620);
            break;

        case 0x1A3:
            *(int *)(act + 0x130) = SetMotionRequest(self, 0x141, act + 0x620);
            break;

        case 0x1A4:
            *(int *)(act + 0x130) = SetMotionRequest(self, 0x141, act + 0x620);
            break;

        case 0x1A5:
            *(int *)(act + 0x130) = SetMotionRequest(self, 0x141, act + 0x620);
            break;

        case 0x1A6:
            *(int *)(act + 0x130) = SetMotionRequest(self, 0x141, act + 0x620);
            break;
        }
    }
    q->num = 0;
    *(BirdMotBlock *)(act + 0x620) = *(BirdMotBlock *)(*(int *)(self + 0x15C) + 0x180);
}

void trans_bird(void *self, float *w)
{
    float down[4] = {0.0f, -1.0f, 0.0f, 0.0f};
    float pos[4];
    float dir[4];
    float fwd[4];
    float dv[4];

    w[4] = (w[0] - w[2]) * w[6] + w[2];
    w[5] = (w[1] - w[3]) * w[6] + w[3];
    w[6] = w[6] + w[7];
    if (w[6] > 1.0f) {
        w[6] = 1.0f;
    }
    GetRootPosition(pos, self);
    _GetMotionDirection(dir, self);
    sceVu0ScaleVectorXYZ(fwd, dir, w[4] * 0.7f);
    sceVu0ScaleVectorXYZ(dv, down, w[5]);
    sceVu0AddVector(fwd, fwd, dv);
    sceVu0AddVector(pos, pos, fwd);
    SetRootPosition(self, pos);
}

INCLUDE_ASM("asm/nonmatchings/src/act_bird", func_0019E7F8);
ASM_LIT4_SLOT(D_00639238, 6.2831855f);
ASM_LIT4_SLOT(D_0063923C, 0.08726647f);
ASM_LIT4_SLOT(D_00639240, 6.2831855f);
ASM_LIT4_SLOT(D_00639244, 0.28f);
ASM_LIT4_SLOT(D_00639248, 0.28f);
ASM_LIT4_SLOT(D_0063924C, 0.4f);
ASM_LIT4_SLOT(D_00639250, 0.7f);
ASM_LIT4_SLOT(D_00639254, 6.2831855f);
ASM_LIT4_SLOT(D_00639258, 6.2831855f);
ASM_LIT4_SLOT(D_0063925C, 0.2f);
ASM_LIT4_SLOT(D_00639260, 6.2831855f);
ASM_LIT4_SLOT(D_00639264, 0.016666668f);
ASM_LIT4_SLOT(D_00639268, 6.2831855f);
ASM_LIT4_SLOT(D_0063926C, 6.2831855f);
ASM_LIT4_SLOT(D_00639270, 0.034906585f);
ASM_LIT4_SLOT(D_00639274, -0.034906585f);
ASM_LIT4_SLOT(D_00639278, 0.6f);
ASM_LIT4_SLOT(D_0063927C, -1.3f);
ASM_LIT4_SLOT(D_00639280, 0.6f);
ASM_LIT4_SLOT(D_00639284, 0.14285715f);
ASM_LIT4_SLOT(D_00639288, 0.2f);

inline void subBirdControl(void *volatile gobj)
{
    _ACTWait(1);
    while (1) {
        Debug_StickControl(gobj);
        _ACTWait(1);
    }
}

inline void subBirdCollision(void *volatile gobj)
{
    _ACTWait(1);
    while (1) {
        _ACTWait(1);
    }
}

inline void actBirdStart(void *a0)
{
    char *w;

    w = (char *)actInitialize(a0);
    _ACTWait(1);
    actCreateSubThread(func_0019E7F8, 0x14);
    actCreateSubThread(subBirdControl, 0x15);
    actCreateSubThread(subBirdCollision, 0x15);
    *(int *)(w + 0x130) = SetMotionRequest(a0, 0x10E, w + 0x620);
}

extern int matrixptr;
extern void sceVu0TransposeMatrix(void *dst, void *src);
extern void sceVu0UnitMatrix(void *m);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_TransMatrix(float x, float y, float z);
/* libvu0 sceVu0MulMatrix; the repo carries it under its vendor placeholder. */
extern void func_0025D440(void *dst, void *a, void *b);
extern void DispWireString(char *s);
extern void vsprintf();

void Debug_WireString_Bird(float *pos, char *fmt, ...)
{
    float m[16];
    char buf[0x100];
    void *args = (char *)__builtin_next_arg(fmt) - 0x30;

    MatrixDrive_PushMatrix();
    sceVu0TransposeMatrix(m, (void *)(matrixptr + 0x80));
    m[3] = m[7] = m[11] = 0.0f;
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrix(pos[0], pos[1], pos[2]);
    func_0025D440(MatrixDrive_GetMatrix(), MatrixDrive_GetMatrix(), m);
    MatrixDrive_PushMatrix();
    vsprintf(buf, fmt, args);
    MatrixDrive_TransMatrix(0.0f, -50.0f, 0.0f);
    DispWireString(buf);
    MatrixDrive_PopMatrix();
    MatrixDrive_PopMatrix();
}

extern char *D_00639EC0;
extern char *D_00639ED0;
extern int iosPadConnect(void *pad, int slot, int port, void *conf);
extern void iosPadRead(void *pad);
extern int iosPadGetStick(void *pad, void *out, int a2, int a3, int a4, int a5);
extern int CorrectStickInfo(void *dir, void *stick);
extern void ConvertStickToAbsCoord(void *out, void *stick);

void Debug_StickControl(char *self)
{
    float dir[4];
    char *ext = *(char **)(self + 0x164);

    if (self == D_00639EC0) {
        char *pad = ext + 0x2D8;
        char *stick = ext + 0x338;

        iosPadConnect(pad, 0, 0, ext + 0x1E8);
        iosPadRead(pad);
        iosPadGetStick(pad, stick, 0, 2, 2, 0);
        _GetMotionDirection(dir, self);
        *(int *)(ext + 0x340) = CorrectStickInfo(dir, stick);
        if (*(float *)(ext + 0x34C) > 0.001f) {
            ConvertStickToAbsCoord(ext + 0x120, stick);
        }
    } else if (self == D_00639ED0) {
        iosPadConnect(ext + 0x2D8, 0, 1, ext + 0x1E8);
    } else {
        iosPadConnect(ext + 0x2D8, 0, 1, ext + 0x1E8);
    }
}

void func_0019FE30(int a0, int a1, int a2, int a3)
{
    ExecMotionOrient(a0, a1, a2, a3);
}

extern void p2o_DispVU1Default(void *gobj);
extern int stage_DispBgAnimation(void *p);
extern void lightning_test(void);
extern int stage_no;

/* census: ito/src/act_bird.c BirdDL, def line 1024 */
void func_0019FE38(void *gobj)
{
    char *w;

    p2o_DispVU1Default(gobj);
    w = *(char **)(*(char **)((char *)gobj + 0x15C) + 0x830);
    if (*(int *)(w + 0x30) != 0) {
        if (stage_DispBgAnimation(w + 0x30) != 0) {
            *(int *)(w + 0x30) = 0;
        }
    }
    if (stage_no == 0x54) {
        lightning_test();
    }
}

inline char *InitBirdGeo(char *a0, void *a1)
{
    char *w;

    w = iosMallocDebug(D_0063A438, 0x40, D_00555788, 978);
    memset(w, 0, 0x40);
    CopyVector(w, a1);
    w[0x10] = 0;
    InitMotionOrient(a0, 0x975, 0x9A3, -1, -1, 0x46E);

    *(int *)(*(int *)(a0 + 0x15C) + 0x544) = 1;
    *(int *)(*(int *)(a0 + 0x15C) + 0x54C) = 0;
    *(int *)(*(int *)(a0 + 0x15C) + 0x548) = 1;
    *(int *)(*(int *)(a0 + 0x15C) + 0x550) = 0;
    ((IntFloat *)(*(int *)(a0 + 0x15C) + 0x4AC))->f = random_unit() * 100.0f;
    ((IntFloat *)(*(int *)(a0 + 0x15C) + 0x4B0))->f =
        ((IntFloat *)(*(int *)(a0 + 0x15C) + 0x4AC))->f;
    *(int *)(*(int *)(a0 + 0x15C) + 0x4C4) = 0;
    SetLodLevel(a0, 3);
    return w;
}

inline void BirdAI(void) {}

void _ACTSendMailToBird(void *a0, void *a1, void *a2)
{
    iosOmSendMail(a0);
}

inline void _ACTSendMailToBirdAll(void *a0, void *a1)
{
    void *obj = isysGObjSearchFromObjKindID_begin(0x20);
    while (obj != 0) {
        _ACTSendMailToBird(obj, a0, a1);
        obj = isysGObjSearchFromObjKindID_next(obj);
    }
}
