#include "common.h"

typedef struct {
    char pad[0x134];
    int node_id;  /* 0x134 */
    char pad2[0x18C - 0x134 - 4];
    unsigned int flags;  /* 0x18C */
    char pad3[0x190 - 0x18C - 4];
} MotionNode;
extern MotionNode D_00565060[];
extern int D_004C49A8[];

void pursueNodeList(int a0) {
    int i;
    for (i = 0; i <= 0x43D; i++) {
        if (D_00565060[i].node_id == a0) {
            D_004C49A8[i] = 0;
        }
    }
}

int CheckMotionIncludeFacialData(unsigned int *self)
{
    int r;
    unsigned int p = (unsigned int)self + 0x10;
    if (p < self[2]) r = 0; else r = -1;
    return r;
}

extern char D_004C5AE0[];
extern char D_004C5AF0[];
extern char D_004C5B00[];
extern char D_004C5B10[];
extern char D_004C5B20[];
extern void func_001D4A58(void *a0, void *a1, void *a2, void *a3, int a4);

void InitMotionMemorySize(void) {
    func_001D4A58(D_004C5AF0, D_004C5AE0, D_004C5B10, D_004C5AE0, -1);
    func_001D4A58(D_004C5B10, D_004C5AE0, D_004C5B00, D_004C5AE0, -1);
    func_001D4A58(D_004C5B00, D_004C5AE0, D_004C5B20, D_004C5AE0, -1);
    func_001D4A58(D_004C5B20, D_004C5AE0, D_004C5AF0, D_004C5AE0, -1);
}

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", limitHPAngleAndSetB);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", avoidReverseInterpOnCurrentMatrix);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", avoidReverseInterpOnCurrentMatrixWithLimit);

/* --- ResetStatic2MotionManager ------------------------------------- */

typedef struct {                /* element of D_00633478[], stride 0x40 */
    int f_0;
    unsigned int state;         /* 0x04 */
    int f_8, f_C;
    float pos[4];               /* 0x10 */
    float quat[4];              /* 0x20 */
    int next;                   /* 0x30 */
    int f_34;
    int f_38;                   /* 0x38 */
    int f_3C;
} MfMot;

typedef struct {                /* element of D_00633F24[], stride 0x20 */
    char _0[0x10];
    float quat[4];              /* 0x10 */
} MfOri;

typedef struct {                /* blend element, stride 0x40 */
    float rate;                 /* 0x00 */
    short f_4;                  /* 0x04 */
    short f_6;
    unsigned short f_8;         /* 0x08 */
    short f_A, f_C;
    short f_E;                  /* 0x0E */
    float q1[4];                /* 0x10 */
    float q2[4];                /* 0x20 */
    float q3[4];                /* 0x30 */
} MfBlend;

typedef struct {                /* at (*(int *)(D_0063347C+0x15C)) + 0xA0 */
    char _0[0x73C];
    MfBlend *blend;             /* 0x73C */
    void **mems;                /* 0x740 */
} MfHdr;

typedef struct {                /* *D_00633F3C */
    char _0[0x50];
    short f_50;                 /* 0x50 */
    char _52[0x204 - 0x52];
    int f_204;                  /* 0x204 */
    float f_208;                /* 0x208 */
    float f_20C;                /* 0x20C */
    char _210[0x20];
    int f_230;                  /* 0x230 */
    int f_234;                  /* 0x234 */
    char _238[0x8];
    float q_240[4];             /* 0x240 */
    float q_250[4];             /* 0x250 */
    char _260[0x30];
    int f_290;                  /* 0x290 */
    int f_294;                  /* 0x294 */
    char _298[0x8];
    float q_2A0[4];             /* 0x2A0 */
    float q_2B0[4];             /* 0x2B0 */
    float f_2C0;                /* 0x2C0 */
    int f_2C4;                  /* 0x2C4 */
    int f_2C8;                  /* 0x2C8 */
    char _2CC[4];
    float q_2D0[4];             /* 0x2D0 */
    int f_2E0;                  /* 0x2E0 */
    char _2E4[0xC];
    float q_2F0[4];             /* 0x2F0 */
    short f_300;                /* 0x300 */
    short f_302;                /* 0x302 */
    short f_304;                /* 0x304 */
    char _306[0x12];
    int f_318;                  /* 0x318 */
    int f_31C;                  /* 0x31C */
    char _320[0x10];
    int f_330;                  /* 0x330 */
    int f_334;                  /* 0x334 */
    char _338[0x28];
    int f_360;                  /* 0x360 */
    char _364[0x58];
    float f_3BC;                /* 0x3BC */
    float f_3C0;                /* 0x3C0 */
    float f_3C4;                /* 0x3C4 */
    float f_3C8;                /* 0x3C8 */
} MfMgr;

typedef struct {                /* *D_00633F40 */
    char _0[0x30];
    int f_30;                   /* 0x30 */
    char _34[0x34];
    int f_68;                   /* 0x68 */
    char _6C[0x154];
    void *f_1C0;                /* 0x1C0 */
} MfActor;

extern MfMot *D_00633478;
extern char *D_0063347C;
extern MfOri *D_00633F24;
extern MfMgr *D_00633F3C;
extern MfActor *D_00633F40;
extern char *D_00633F54;
extern float D_00633440;
extern unsigned short D_00633444;
extern unsigned short D_00633446;
extern unsigned short D_00633448;
extern unsigned short D_0063344A;
extern float D_00633F20;
extern int D_00633F44;
extern int D_00632D18;
extern int D_00632D60;
extern int D_00274EC0[];
extern float D_006312B4, D_006312B8, D_006312BC, D_006312C0, D_006312C4;
extern float D_006312C8, D_006312CC, D_006312D0, D_006312D4, D_006312D8;
extern float D_006312DC, D_006312E0, D_006312E4, D_006312E8, D_006312EC;
extern float D_00276140[];
extern float D_004C5B30[], D_004C5B40[], D_004C5B50[];
extern float D_00275860[], D_00275870[];
extern float D_00709750[], D_00709760[];

extern void sceVu0ScaleVectorXYZ(void *a0, void *a1, float a2);
extern void *func_00105278(void);
extern void *func_00105290(void);
extern void MatrixDrive_PushMatrixWithNoCopy(void);
extern void MatrixDrive_PopMatrix(void);
extern void func_001052A8(void *a0);
extern void func_00105308(float x, float y, float z);
extern void func_00104F20(void);
extern void MatrixDrive_RotMatrixX(int a0);
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);
extern void sceVu0TransposeMatrix(void *a0, void *a1);
extern void sceVu0Normalize(void *a0, void *a1);
extern void *GetLastQuaternion(void);
extern void *GetTableSin(void);
extern void MultiQuaternion(void *a0, void *a1, void *a2);
extern void DivQuaternion(void *a0, void *a1, void *a2);
extern void GetMatrixFromQuaternionRotElem(void *a0, void *a1);
extern void MultiMatrixByQuaternion(void *a0);
extern void func_0010E0B8(void *a0, int a1);
extern void func_0010E158(void *a0, int a1);
extern void func_0010E1F8(void *a0, int a1);
extern void SetQuaternionByAxisRotateV(void *a0, int a1, void *a2);
extern void GetInverseQuaternion(void *a0, void *a1);
extern void memset(void *a0, int a1, int a2);
extern void GetCurrentQuaternion(void *dst, void *qa, void *qb, float t);
extern void InvertCurrentQuaternion(void *a0);
extern void RegularizeQuaternion(void *a0, void *a1);
extern void GetMatrixFromQuaternion(void *a0);
extern void GetSlerpQuaternionNoRegularize(void *a0);
extern void AddVectorXYZ(void *a0, void *a1, void *a2);
extern void SubVectorXYZ(void *a0, void *a1, void *a2);
extern void MatrixDrive_TransMatrix(void *a0, void *a1);
extern void MatrixDrive_GetTurnYAngleXZ(void *o1, void *o2, float x, float y, float z);
extern void MatrixDrive_TransMatrixV(void *o1, void *o2, float x, float y, float z);
extern void MatrixDrive_GetTurnZAngleXY(void *o1, void *o2, float x, float y, float z);
extern void MatrixDrive_GetTurnXAngleZY(void *o1, void *o2, float x, float y, float z);
extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);
extern float VectorLength(void *a0);
extern void limitHPAngleAndSetB(void *a0, void *a1, void *a2, void *a3,
                                int a4, int a5, int a6, int a7, float w,
                                int s0, int s1);
extern void avoidReverseInterpOnCurrentMatrix(void *a0, void *a1, void *a2);
extern void avoidReverseInterpOnCurrentMatrixWithLimit(void *a0, void *a1, void *a2, void *a3, float w);
extern void _NormalizeVector(void *a0, void *a1);
extern void _OuterProduct(void *a0, void *a1, void *a2);
extern float _InnerProduct(void *a0, void *a1);
extern void _AddVector(void *a0, void *a1, void *a2);
extern void _SubVectorXYZ(void *a0, void *a1, void *a2);
extern float GetTableCos(short a0);
extern float p2o_SetDefaultEnviroment(short a0);
extern int GetTableArcSin(float x);
extern int GetTableArcCos(float x);
extern void _ApplyMatrix(void *a0, void *a1, void *a2);
extern void SetQuaternionByAxisRotateWithNoRegularize(void *self, int a1, float x, float y, float z);
extern float CheckSwapableWeapon(void *a0);
extern int DebugDisp1CollisionWithColor(void *a0, int a1);
extern void getQuaternionFromMatrix(void *a0, void *a1);

#define MFM_FRAME_SCALE_N(num) \
    ((num) / (float)((0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1]))
#define MFM_FRAME_SCALE MFM_FRAME_SCALE_N(60.0f)

#define MFM_SEL_ROT(dst, k)                                     \
    if (D_00632D18 != 0) {                                      \
        rotk = (k);                                             \
        dst = (float)D_00632D60 * rotk;                         \
    } else {                                                    \
        dst = *(float *)(D_00633F54 + 0x158);                   \
    }

#define MFM_RATE_UP(rate, k, num)                                  \
    {                                                           \
        float w, u, v, one, t, rot;                            \
        one = 1.0f;                                            \
        w = (rate);                                            \
        v = one - w;                                           \
        t = D_00633F3C->f_3BC * MFM_FRAME_SCALE_N(num);        \
        u = one - t;                                           \
        MFM_SEL_ROT(rot, k);                                   \
        (rate) = w + v * (t + u * rot);                        \
    }

#define MFM_RATE_DOWN(rate, k)                                   \
    {                                                           \
        float one, w, u, t, rot;                                \
        one = 1.0f;                                             \
        w = (rate);                                             \
        t = D_00633F3C->f_3BC * MFM_FRAME_SCALE;          \
        u = one - t;                                            \
        MFM_SEL_ROT(rot, k);                                    \
        (rate) = w * (one - (t + u * rot));                     \
    }

void ResetStatic2MotionManager(int idx) {
    float buf10[4];             /* sp 0x10 */
    float q20[4];               /* sp 0x20 */
    float q30[4];               /* sp 0x30 */
    float q40[4];               /* sp 0x40 */
    float v50[4];               /* sp 0x50 */
    float v60[4];               /* sp 0x60 */
    float v70[4];               /* sp 0x70 */
    short g80[5];               /* sp 0x80 */
    float q90[4];               /* sp 0x90 */
    float qA0[4];               /* sp 0xA0 */
    short gB0[4];               /* sp 0xB0 */
    float vC0[4];               /* sp 0xC0 */
    float qD0[4];               /* sp 0xD0 */
    short gE0[8];               /* sp 0xE0 */
    float qF0[4];               /* sp 0xF0 */
    short g100[7];              /* sp 0x100 ([2..6] used) */
    float v110[4];              /* sp 0x110 */
    float v120[4];              /* sp 0x120 */
    float v130[4];              /* sp 0x130 */
    float pad140[4];            /* sp 0x140 (unused) */
    float v150[4];              /* sp 0x150 */
    float v160[4];              /* sp 0x160 */
    float v170[4];              /* sp 0x170 */
    short g180[5];              /* sp 0x180 */
    float q190[4];              /* sp 0x190 */
    void *mem;                  /* sp 0x1A0 */
    MfMot *e;
    MfBlend *b;
    MfOri *nd;
    void *s0;
    float *w;
    float rotk;
    unsigned int st;

    e = &D_00633478[idx];
    nd = &D_00633F24[idx];
    {
        MfHdr *h = (MfHdr *)(*(int *)(D_0063347C + 0x15C) + 0xA0);
        b = &h->blend[idx];
        mem = h->mems[idx];
    }
    if (e->f_38 != -1) {
        sceVu0ScaleVectorXYZ(buf10, e->pos, D_00633440);
        s0 = (char *)func_00105278() + 0x30;
        sceVu0ApplyMatrix(s0, func_00105290(), buf10);
    } else {
        D_0063344A = 0;
        D_00633448 = 0;
        D_00633446 = 0;
        D_00633444 = 0;
    }
    st = e->state;
    switch (st) {
    case 0x0:
    {
        void *s0;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), nd->quat);
        {
            void *pa = GetLastQuaternion();
            float *pb = D_004C5B40;
            void *pc;
            pc = GetLastQuaternion();
            MultiQuaternion(pa, pb, pc);
        }
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        return;
    }
    case 0x2C:
    {
        void *s0;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), nd->quat);
        DivQuaternion(GetLastQuaternion(), GetLastQuaternion(), D_004C5B30);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        return;
    }
    case 0x22:
    {
        void *s0;
        int q;
        float t;
        float rot;
        float *qa;
        float *qb;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_00276140);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        if (D_00633F3C->f_318 != 0 && D_00633F3C->f_2E0 != 0) {
            MFM_RATE_UP(b->rate, D_006312B4, 60.0f);
        } else {
            MFM_RATE_DOWN(b->rate, D_006312B8);
        }
        memset(v50, 0, 0x10);
        v50[3] = 1.0f;
        if (D_00633F44 == 2) {
            func_0010E1F8(v50, 0x71C);
        }
        GetCurrentQuaternion(q40, v50, qb, b->rate);
        MultiQuaternion(qa, qa, q40);
        InvertCurrentQuaternion(qa);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        RegularizeQuaternion(q40, D_00633F3C->q_2D0);
        {
            void *pa = GetLastQuaternion();
            void *pc = GetLastQuaternion();
            MultiQuaternion(pa, q40, pc);
        }
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        return;
    }
    case 0x23:
    {
        void *s0;
        int q;
        float *qb;
        float *w;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        GetInverseQuaternion(q30, D_00276140);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        func_0010E1F8(GetLastQuaternion(), D_00633F3C->f_304);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        if (D_00633F3C->f_318 != 0 && D_00633F3C->f_2E0 != 0) {
            b->rate += (1.0f - b->rate) * (D_00633F3C->f_3BC * MFM_FRAME_SCALE);
        } else {
            b->rate *= 1.0f - D_00633F3C->f_3BC * MFM_FRAME_SCALE;
        }
        if (b->rate < D_006312BC) {
            float *q3;
            GetInverseQuaternion(b->q1, GetLastQuaternion());
            q3 = b->q3;
            GetMatrixFromQuaternion(q3);
            GetInverseQuaternion(b->q2, q3);
        } else {
            float *q1 = b->q1;
            if (D_00633F44 == 4) {
                MatrixDrive_RotMatrixX(-0x8000);
            }
            {
                float *pb = D_00633F3C->q_2F0;
                void *t = func_00105278();
                AddVectorXYZ(v70, (char *)t + 0x30, D_00633F3C);
                w = v60;
                SubVectorXYZ(w, pb, v70);
            }
            v60[3] = 0;
            MatrixDrive_PushMatrixWithNoCopy();
            MatrixDrive_TransMatrix(func_00105278(), func_00105290());
            {
                void *t = func_00105278();
                w = v50;
                sceVu0ApplyMatrix(w, t, v60);
            }
            MatrixDrive_PopMatrix();
            MatrixDrive_GetTurnYAngleXZ(&g80[0], &g80[1], v50[0], v50[1], v50[2]);
            limitHPAngleAndSetB(&g80[2], &g80[3], &g80[4], mem, g80[0], 0, (short)-(unsigned short)g80[1], 0, 1.0f, 0, 1);
            {
                int h3 = -g80[3];
                g80[3] = h3;
                if (D_00633F44 == 4) {
                    h3 = -(short)h3;
                    g80[3] = h3;
                }
            }
            {
                int d0 = (unsigned short)g80[0] - (unsigned short)g80[2];
                int d2 = (unsigned short)g80[1] - (unsigned short)g80[3];
                D_00633F3C->f_300 = d0;
                D_00633F3C->f_302 = d2;
            }
            {
                float *q3 = b->q3;
                float *q2 = b->q2;
                w = v60;
                GetMatrixFromQuaternion(w);
                func_0010E0B8(w, (short)-(unsigned short)g80[2]);
                func_0010E1F8(w, (short)-(unsigned short)g80[3]);
                func_0010E158(w, (short)-(unsigned short)g80[4]);
                avoidReverseInterpOnCurrentMatrixWithLimit(q1, mem, q3, w, D_006312C0);
                s0 = v70;
                MultiQuaternion(s0, GetLastQuaternion(), w);
                w = q90;
                DivQuaternion(w, s0, q1);
                GetCurrentQuaternion(qA0, w, D_00276140, D_00633F3C->f_3C4);
                GetCurrentQuaternion(q2, qA0, q2, D_00633F3C->f_3C8);
                MultiQuaternion(q1, q1, q2);
                GetSlerpQuaternionNoRegularize(q1);
                DivQuaternion(q3, q1, GetLastQuaternion());
            }
        }
        {
            s0 = GetLastQuaternion();
            func_0010E0B8(s0, (short)(int)((float)-D_00633F3C->f_50 * 2.5f));
            s0 = GetLastQuaternion();
            MultiQuaternion(q90, s0, qb);
            GetCurrentQuaternion(GetLastQuaternion(), b->q1, q90, b->rate);
            {
                void *pa = GetLastQuaternion();
                float *tbl = D_004C5B50;
                void *pc = GetLastQuaternion();
                MultiQuaternion(pa, tbl, pc);
            }
        }
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        return;
    }
    case 0x1:
    {
        void *s0;
        int q;
        int n;
        int nq;
        float t;
        float rot;
        float ang;
        int sumA;
        int sumB;
        int cnt;
        int hold;
        float *w;
        float *qb;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        GetInverseQuaternion(q30, D_00276140);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        MultiQuaternion(GetLastQuaternion(), GetLastQuaternion(), qb);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        if (D_00633F3C->f_31C != 0
            && ((D_00633F3C->f_318 != 0 && D_00633F3C->f_2E0 != 0)
                || D_00633F3C->f_230 != 0 || D_00633F3C->f_290 != 0)) {
            MFM_RATE_UP(b->rate, D_006312C4, 60.0f);
        } else {
            MFM_RATE_DOWN(b->rate, D_006312C8);
        }
        if (b->rate < D_006312CC) {
            GetInverseQuaternion(b->q1, GetLastQuaternion());
            GetMatrixFromQuaternion(b->q3);
            GetInverseQuaternion(b->q2, b->q3);
        } else {
            float *q1;
            float *q2;
            float *q3 = b->q3;
            float *pD0 = qD0;
            float one = 1.0f;
            avoidReverseInterpOnCurrentMatrix(b->q1, mem, q3);
            q1 = b->q1;
            n = D_00633F3C->f_31C;
            cnt = 0;
            sumA = 0;
            if (n == 1) {
                if (D_00633F3C->f_290 != 0) {
                    float *pb = D_00633F3C->q_2A0;
                    cnt = 1;
                    s0 = func_00105278();
                    w = v60;
                    AddVectorXYZ(w, (char *)s0 + 0x30, D_00633F3C);
                    w = v50;
                    SubVectorXYZ(w, pb, v60);
                    v50[3] = 0;
                    MatrixDrive_PushMatrixWithNoCopy();
                    MatrixDrive_TransMatrix(func_00105278(), func_00105290());
                    {
                        void *t = func_00105278();
                        w = qA0;
                        sceVu0ApplyMatrix(w, t, v50);
                    }
                    MatrixDrive_PopMatrix();
                    MatrixDrive_TransMatrixV(&gB0[0], &gB0[1], qA0[0], qA0[1], qA0[2]);
                    sumA = gB0[0];
                }
                if (D_00633F3C->f_31C == n && D_00633F3C->f_230 != 0) {
                    float *pb = D_00633F3C->q_240;
                    void *t;
                    cnt += 1;
                    t = func_00105278();
                    AddVectorXYZ(v70, (char *)t + 0x30, D_00633F3C);
                    w = v60;
                    SubVectorXYZ(w, pb, v70);
                    v60[3] = 0;
                    MatrixDrive_PushMatrixWithNoCopy();
                    MatrixDrive_TransMatrix(func_00105278(), func_00105290());
                    t = func_00105278();
                    w = v50;
                    sceVu0ApplyMatrix(w, t, v60);
                    MatrixDrive_PopMatrix();
                    MatrixDrive_GetTurnZAngleXY(&gB0[2], &gB0[3], v50[0], v50[1], v50[2]);
                    sumA -= gB0[2];
                }
            }
            hold = 0;
            sumB = sumA;
            if (D_00633F3C->f_318 != 0 && D_00633F3C->f_2E0 != 0) {
                float *pb = D_00633F3C->q_2F0;
                void *t;
                t = func_00105278();
                AddVectorXYZ(pD0, (char *)t + 0x30, D_00633F3C);
                SubVectorXYZ(vC0, pb, pD0);
                vC0[3] = 0;
                MatrixDrive_PushMatrixWithNoCopy();
                MatrixDrive_TransMatrix(func_00105278(), func_00105290());
                t = func_00105278();
                w = v60;
                sceVu0ApplyMatrix(w, t, vC0);
                MatrixDrive_PopMatrix();
                MatrixDrive_GetTurnYAngleXZ(&gE0[0], &gE0[1], v60[0], v60[1], v60[2]);
                if (D_00633F3C->f_2E0 == 2) {
                    sumA = sumB + gE0[0];
                    hold = gE0[1];
                    sumB = sumA;
                } else {
                    sumA = sumB + D_00633F3C->f_300;
                    hold = D_00633F3C->f_302;
                    sumB += gE0[0] / 2;
                }
                cnt += 1;
            }
            if (cnt != 0) {
                sumA = sumA / cnt;
                sumB = sumB / cnt;
            }
            limitHPAngleAndSetB(&gE0[2], &gE0[3], &gE0[4], mem, (short)sumA, b->f_4,
                                (short)-hold, (short)-b->f_8, one, 0, 0);
            limitHPAngleAndSetB(&gE0[5], &gE0[6], &gE0[7], mem, (short)sumB, b->f_4,
                                (short)-hold, (short)-b->f_8, one, 0, 0);
            q2 = b->q2;
            {
                int h6 = -gE0[6];
                gE0[6] = h6;
            }
            w = v70;
            GetMatrixFromQuaternion(w);
            func_0010E0B8(w, (short)-(unsigned short)gE0[2]);
            func_0010E1F8(w, (short)-(unsigned short)gE0[6]);
            func_0010E158(w, (short)-(unsigned short)gE0[4]);
            MultiQuaternion(vC0, GetLastQuaternion(), w);
            DivQuaternion(pD0, vC0, q1);
            GetCurrentQuaternion(qF0, pD0, D_00276140, D_00633F3C->f_3C4);
            GetCurrentQuaternion(q2, qF0, q2, D_00633F3C->f_3C8);
            MultiQuaternion(q1, q1, q2);
            GetSlerpQuaternionNoRegularize(q1);
            DivQuaternion(q3, q1, GetLastQuaternion());
            {
                int step;
                t = (float)b->f_E;
                step = (int)(t + ((float)(gE0[6] - (short)b->f_8) * D_00633F3C->f_3C4 - t) * D_00633F3C->f_3C8);
                b->f_E = step;
                b->f_8 = b->f_8 + step;
                D_00633F3C->f_304 = (int)((float)(short)b->f_8 * b->rate);
            }
        }
        s0 = GetLastQuaternion();
        func_0010E0B8(s0, (short)(int)((float)D_00633F3C->f_50 * 2.5f));
        GetCurrentQuaternion(GetLastQuaternion(), b->q1, GetLastQuaternion(), b->rate);
        {
            void *pa = GetLastQuaternion();
            float *pc = D_00633F3C->q_2D0;
            MultiQuaternion(pa, pc, GetLastQuaternion());
        }
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        _ApplyMatrix(D_00709750, func_00105278(), D_00275870);
        return;
    }
    case 0x12:
    {
        void *s0;
        float *qa;
        float *qb;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_00276140);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        MultiQuaternion(qa, qa, qb);
        InvertCurrentQuaternion(qa);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        return;
    }
    case 0x13:
    {
        void *s0;
        int q;
        int n;
        int nq;
        int i;
        float t;
        float rot;
        float len2;
        float ang;
        float *qa;
        float *qb;
        float *pb;
        float *w13;
        int fl;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_00276140);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        memset(qA0, 0, 0x10);
        qA0[3] = 1.0f;
        {
            float *pb = D_00633F3C->q_2A0;
            void *t = func_00105278();
            w13 = v70;
            AddVectorXYZ(w13, (char *)t + 0x30, D_00633F3C);
            w13 = v60;
            SubVectorXYZ(w13, pb, v70);
        }
        v60[3] = 0;
        MatrixDrive_PushMatrixWithNoCopy();
        MatrixDrive_TransMatrix(func_00105278(), func_00105290());
        {
            void *t = func_00105278();
            w13 = vC0;
            sceVu0ApplyMatrix(w13, t, v60);
        }
        MatrixDrive_PopMatrix();
        MatrixDrive_GetTurnXAngleZY(&g100[2], &g100[3], vC0[0], vC0[1], vC0[2]);
        limitHPAngleAndSetB(&g100[4], &g100[5], &g100[6], mem, g100[2], 0, g100[3], 0, 1.0f, 1, 0);
        if (D_00633F3C->f_294 != 0) {
            _NormalizeVector(v50, vC0);
        } else {
            short h1 = g100[5];
            short h0 = g100[4];
            float t = GetTableCos(h1);
            v50[0] = GetTableCos(h0) * t;
            v50[1] = p2o_SetDefaultEnviroment(h0) * t;
            v50[2] = -p2o_SetDefaultEnviroment(h1);
            v50[3] = 0;
        }
        nq = GetTableArcCos(_InnerProduct(v50, D_00275870));
        _OuterProduct(v60, v50, D_00275870);
        pb = qD0;
        SetQuaternionByAxisRotateV(pb, nq, v60);
        pb = qA0;
        MultiQuaternion(pb, pb, qD0);
        if (D_00633F3C->f_290 == 1) goto L13turn;
        if (D_00633F3C->f_290 == 2) goto L13mul;
        GetInverseQuaternion(qF0, qb);
        GetCurrentQuaternion(D_00633F3C->q_2D0, D_00633F3C->q_2D0, D_00276140, D_006312D0);
        w13 = v60;
        goto L13done;
      L13turn:
        {
            float *p70;
            w13 = v60;
            p70 = v70;
            i = 0;
            ang = VectorLength(vC0);
            n = e->next;
            if (n == -1) goto none13;
            do {
                MfMot *o = &D_00633478[n];
                v60[i++] = D_00633440 * VectorLength(o->pos);
                if (i >= 2) break;
                n = o->next;
none13:;
            } while (n != -1);
            v60[1] += D_00633440 * VectorLength(
                D_00633478[DebugDisp1CollisionWithColor(D_0063347C, 0x20)].pos);
            MatrixDrive_PushMatrixWithNoCopy();
            {
                int k = DebugDisp1CollisionWithColor(D_0063347C, 0x16);
                getQuaternionFromMatrix(func_00105278(), (char *)&D_00633F24[k] + 0x10);
            }
            func_00105308(5.0f, -3.0f, 0.0f);
            MatrixDrive_TurnObjectMatrix(v110, (char *)func_00105278() + 0x30);
            _AddVector(p70, D_00633478[e->next].pos, v110);
            rot = D_00633440 * VectorLength(p70);
            v130[0] = rot;
            v130[1] = 0.0f;
            v130[2] = 0.0f;
            v130[3] = 1.0f;
            _SubVectorXYZ(v130, v130, v110);
            _NormalizeVector(v130, v130);
            _OuterProduct(v120, v130, D_00275870);
            {
                int k = GetTableArcCos(_InnerProduct(D_00275870, v130));
                SetQuaternionByAxisRotateV(D_00709760, k, v120);
            }
            v60[1] = rot;
            MatrixDrive_PopMatrix();
            if (D_00633F3C->f_2C4 == 0) {
                float t = v60[0] + v60[1];
                if (t < ang) {
                    ang = t;
                }
            }
            len2 = ang * ang;
            D_00633448 = GetTableArcCos(
                (len2 + v60[0] * v60[0] - v60[1] * v60[1]) / ((v60[0] + v60[0]) * ang));
            D_0063344A = GetTableArcCos(
                (len2 + v60[1] * v60[1] - v60[0] * v60[0]) / ((v60[1] + v60[1]) * ang));
            func_0010E0B8(qA0, g100[6]);
            func_0010E1F8(qA0, (short)D_00633448);
            GetInverseQuaternion(qF0, qA0);
            {
                void *t = func_00105278();
                float *pb = D_00633F3C->q_2A0;
                AddVectorXYZ(v120, (char *)t + 0x30, D_00633F3C);
                SubVectorXYZ(v70, pb, v120);
            }
            v70[3] = 0;
            _NormalizeVector(p70, p70);
            _OuterProduct(v110, p70, D_00709750);
            if (D_00633F3C->f_360 == 2 && ang + 0.0f > v60[0] + v60[1]) {
                SetQuaternionByAxisRotateV(v120, (short)((ang + 0.0f - (v60[0] + v60[1])) * D_006312D4), v110);
                GetCurrentQuaternion(D_00633F3C->q_2D0, D_00633F3C->q_2D0, v120, D_006312D8);
            } else {
                GetCurrentQuaternion(D_00633F3C->q_2D0, D_00633F3C->q_2D0, D_00276140, D_006312DC);
            }
        }
        goto L13done;
      L13mul:
        MultiQuaternion(qF0, qA0, D_00633F3C->q_2B0);
        MultiQuaternion(qF0, qF0, qb);
        GetCurrentQuaternion(D_00633F3C->q_2D0, D_00633F3C->q_2D0, D_00276140, D_006312E0);
        w13 = v60;
      L13done:
        GetCurrentQuaternion(b->q1, qF0, b->q1, D_00633F3C->f_2C0 * MFM_FRAME_SCALE);
        if (D_00633F3C->f_290 != 0) {
            b->rate = b->rate + (1.0f - b->rate) * (D_00633F3C->f_3C0 * MFM_FRAME_SCALE);
        } else {
            b->rate = b->rate * (1.0f - D_00633F3C->f_3C0 * MFM_FRAME_SCALE);
        }
        GetCurrentQuaternion(w13, b->q1, qb, b->rate);
        MultiQuaternion(qa, qa, w13);
        InvertCurrentQuaternion(qa);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        D_00633F20 = b->rate;
        fl = 1;
        if (!(D_006312E4 < b->rate)) {
            fl = 0;
        }
        if (fl != 0 && D_00633F3C->f_2C8 == 0) {
            D_00633F3C->f_2C4 = 1;
        } else {
            D_00633F3C->f_2C4 = 0;
        }
        D_00633F3C->f_2C8 = fl;
        return;
    }
    case 0x14:
    {
        void *s0;
        int q;
        float *qa;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_00276140);
        DivQuaternion(q20, nd->quat, e->quat);
        GetInverseQuaternion(v60, q20);
        if (D_00633F3C->f_290 == 1) {
            SetQuaternionByAxisRotateWithNoRegularize(v60, (short)-(D_00633448 + D_0063344A), 0.0f, 0.0f, -1.0f);
            MultiQuaternion(v60, v60, D_00709760);
        }
        GetCurrentQuaternion(b->q1, v60, b->q1, D_00633F3C->f_2C0 * MFM_FRAME_SCALE);
        GetCurrentQuaternion(v70, b->q1, q20, D_00633F20);
        MultiQuaternion(qa, qa, v70);
        InvertCurrentQuaternion(qa);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        return;
    }
    case 0x16:
    {
        void *s0;
        int n;
        int nq;
        float t;
        float *qa;
        float *qb;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_00276140);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        if (D_00633F3C->f_330 != 0) {
            GetInverseQuaternion(v60, D_00276140);
        } else {
            GetInverseQuaternion(v60, qb);
        }
        GetCurrentQuaternion(v70, v60, qb, D_00633F20);
        MultiQuaternion(qa, qa, v70);
        InvertCurrentQuaternion(qa);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        if (D_00633F40->f_1C0 != 0
            && !(((D_00565060 + D_00633F40->f_30)->flags >> 1) & 1)) {
            n = D_00633F40->f_68;
            if (n != 6) {
                if (n < 7) {
                    if (n == 0) {
                        goto no_swap;
                    }
                    goto swap_weapon;
                }
                if (n != 0xE && n != 0x13) {
swap_weapon:
                    t = CheckSwapableWeapon(D_00633F40->f_1C0) * D_006312E8;
                    t = D_006312EC < t ? D_006312EC : t;
                    GetCurrentQuaternion(b->q1, b->q1, GetLastQuaternion(), t);
                    GetInverseQuaternion(GetLastQuaternion(), b->q1);
                    GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
                    return;
                }
                goto no_swap;
            }
        }
no_swap:
        GetInverseQuaternion(b->q1, GetLastQuaternion());
        return;
    }
    case 0x15:
    {
        void *s0;
        GetInverseQuaternion(GetLastQuaternion(), GetTableSin());
        {
            void *pa = GetLastQuaternion();
            void *pc = GetLastQuaternion();
            MultiQuaternion(pa, pc, nd->quat);
        }
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        return;
    }
    case 0x2:
    {
        void *s0;
        float *qa;
        float *qb;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_00276140);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        MultiQuaternion(qa, qa, qb);
        InvertCurrentQuaternion(qa);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        return;
    }
    case 0x3:
    {
        void *s0;
        int q;
        int n;
        int nq;
        int i;
        float t;
        float len2;
        float ang;
        float *qa;
        float *w;
        float *qb;
        float *qc;
        float *p130;
        float *p150;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_00276140);
        qb = q20;
        qc = v110;
        DivQuaternion(qb, nd->quat, e->quat);
        memset(v110, 0, 0x10);
        v110[3] = 1.0f;
        {
            float *pb = D_00633F3C->q_240;
            void *t = func_00105278();
            w = v170;
            AddVectorXYZ(w, (char *)t + 0x30, D_00633F3C);
            w = v160;
            SubVectorXYZ(w, pb, v170);
        }
        v160[3] = 0;
        MatrixDrive_PushMatrixWithNoCopy();
        MatrixDrive_TransMatrix(func_00105278(), func_00105290());
        {
            void *t = func_00105278();
            w = v120;
            sceVu0ApplyMatrix(w, t, v160);
        }
        MatrixDrive_PopMatrix();
        MatrixDrive_GetTurnXAngleZY(&g180[0], &g180[1], v120[0], v120[1], v120[2]);
        limitHPAngleAndSetB(&g180[2], &g180[3], &g180[4], mem, g180[0], 0, g180[1], 0, 1.0f, 1, 0);
        p150 = v150;
        if (D_00633F3C->f_234 != 0) {
            _NormalizeVector(p150, v120);
        } else {
            short h1 = g180[3];
            short h0 = g180[2];
            float t = GetTableCos(h1);
            v150[0] = GetTableCos(h0) * t;
            v150[1] = p2o_SetDefaultEnviroment(h0) * t;
            v150[2] = -p2o_SetDefaultEnviroment(h1);
            v150[3] = 0;
        }
        nq = GetTableArcCos(_InnerProduct(p150, D_00275870));
        p130 = v130;
        _OuterProduct(v160, p150, D_00275870);
        SetQuaternionByAxisRotateV(p130, nq, v160);
        MultiQuaternion(qc, qc, p130);
        if (D_00633F3C->f_230 == 1) goto L3turn;
        if (D_00633F3C->f_230 == 2) goto L3mul;
        GetInverseQuaternion(v70, qb);
        w = v160;
        goto L3done;
      L3turn:
        {
            w = v160;
            i = 0;
            ang = VectorLength(v120);
            n = e->next;
            if (n == -1) goto none3;
            do {
                MfMot *o = &D_00633478[n];
                w[i++] = D_00633440 * VectorLength(o->pos);
                if (i >= 2) break;
                n = o->next;
none3:;
            } while (n != -1);
            v160[1] += D_00633440 * VectorLength(
                D_00633478[DebugDisp1CollisionWithColor(D_0063347C, 0x10)].pos);
            len2 = ang * ang;
            D_00633448 = GetTableArcCos(
                (len2 + v160[0] * v160[0] - v160[1] * v160[1]) / ((v160[0] + v160[0]) * ang));
            D_0063344A = GetTableArcCos(
                (len2 + v160[1] * v160[1] - v160[0] * v160[0]) / ((v160[1] + v160[1]) * ang));
            func_0010E0B8(qc, g180[4]);
            func_0010E1F8(qc, (short)D_00633448);
            GetInverseQuaternion(v70, qc);
        }
        goto L3done;
      L3mul:
        MultiQuaternion(v70, qc, D_00633F3C->q_250);
        MultiQuaternion(v70, v70, qb);
        w = v160;
      L3done:
        GetCurrentQuaternion(b->q1, v70, b->q1, D_00633F3C->f_3C0 * MFM_FRAME_SCALE);
        if (D_00633F3C->f_230 != 0) {
            b->rate = b->rate + (1.0f - b->rate) * (D_00633F3C->f_3C0 * MFM_FRAME_SCALE);
        } else {
            b->rate = b->rate * (1.0f - D_00633F3C->f_3C0 * MFM_FRAME_SCALE);
        }
        GetCurrentQuaternion(w, b->q1, qb, b->rate);
        MultiQuaternion(qa, qa, w);
        InvertCurrentQuaternion(qa);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        D_00633F20 = b->rate;
        return;
    }
    case 0x4:
    {
        void *s0;
        int q;
        float *qa;
        float *qb;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_00276140);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        GetInverseQuaternion(v160, qb);
        if (D_00633F3C->f_230 == 1) {
            SetQuaternionByAxisRotateWithNoRegularize(v160, (short)-(D_00633448 + D_0063344A), 0.0f, 0.0f, -1.0f);
        }
        GetCurrentQuaternion(b->q1, v160, b->q1, D_00633F3C->f_3C0 * MFM_FRAME_SCALE);
        GetCurrentQuaternion(v170, b->q1, qb, D_00633F20);
        MultiQuaternion(qa, qa, v170);
        InvertCurrentQuaternion(qa);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        return;
    }
    case 0x6:
    {
        void *s0;
        float *qa;
        float *qb;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_00276140);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        if (D_00633F3C->f_334 != 0) {
            GetInverseQuaternion(b->q1, D_00276140);
        } else {
            GetInverseQuaternion(b->q1, qb);
        }
        GetCurrentQuaternion(v160, b->q1, qb, D_00633F20);
        MultiQuaternion(qa, qa, v160);
        InvertCurrentQuaternion(qa);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        return;
    }
    case 0x5:
    {
        void *s0;
        float *qa;
        float *qb;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_00276140);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        if (D_00633F3C->f_230 != 0) {
            if (D_00633F3C->f_230 != 1) {
                MultiQuaternion(qa, qa, qb);
            }
        } else {
            MultiQuaternion(qa, qa, qb);
        }
        InvertCurrentQuaternion(qa);
        GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
        return;
    }
    case 0x2D:
    case 0x31:
    {
        void *s0;
        int n;
        int nq;
        int i;
        float len2;
        float ang;
        float *qa;
        float *qb;
        int endflag;
        float *wq;
        if (D_00633F3C->f_204 != 0) {
            endflag = 0;
            i = 0;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
            GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
            qa = q30;
            GetInverseQuaternion(qa, D_00276140);
            qb = q20;
            DivQuaternion(qb, nd->quat, e->quat);
            func_00104F20();
            MatrixDrive_TurnObjectMatrix((char *)func_00105278() + 0x30, D_00275860);
            MultiMatrixByQuaternion(qb);
            func_00104F20();
            n = e->next;
            if (n != -1) {
                wq = v160;
                goto body2D;
            }
            wq = v160;
            endflag = 1;
            goto done2D;
            do {
body2D:;
                {
                MfMot *o = &D_00633478[n];
                sceVu0ScaleVectorXYZ(q190, o->pos, D_00633440);
                func_001052A8(q190);
                MultiMatrixByQuaternion(D_00633F24[n].quat);
                v160[i++] = D_00633440 * VectorLength(o->pos);
                if (i >= 2) goto done2D;
                n = o->next;
                }
            } while (n != -1);
            endflag = 1;
done2D:;
            MatrixDrive_TurnObjectMatrix(v170, (char *)func_00105278() + 0x30);
            if (e->state == 0x2D) goto add1F8;
            if (e->state == 0x31) goto add1FC;
            goto addend;
add1F8:
            v170[1] += D_00633F3C->f_208;
            goto addend;
add1FC:
            v170[1] += D_00633F3C->f_20C;
addend:;
            ang = VectorLength(v170);
            MatrixDrive_PopMatrix();
            len2 = ang * ang;
            s0 = func_00105278();
            sceVu0TransposeMatrix(s0, s0);
            sceVu0ApplyMatrix(v170, s0, v170);
            sceVu0Normalize(v170, v170);
            D_00633444 = GetTableArcSin(v170[1]);
            D_00633446 = -GetTableArcSin(v170[2]);
            D_00633448 = GetTableArcCos(
                (len2 + v160[0] * v160[0] - v160[1] * v160[1]) / ((v160[0] + v160[0]) * ang));
            D_0063344A = GetTableArcCos(
                (len2 + v160[1] * v160[1] - v160[0] * v160[0]) / ((v160[1] + v160[1]) * ang));
            MatrixDrive_PopMatrix();
            if (endflag == 0) {
                MultiQuaternion(qa, qa, qb);
                func_0010E1F8(qa, (short)D_00633444);
                func_0010E158(qa, (short)D_00633446);
                func_0010E1F8(qa, (short)-D_00633448);
            } else {
                MultiQuaternion(qa, qa, qb);
            }
            InvertCurrentQuaternion(qa);
            GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
            return;
        }
        goto sin_tail;
    }
    case 0x2E:
    case 0x32:
    {
        void *s0;
        float *qa;
        if (D_00633F3C->f_204 != 0) {
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
            GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
            qa = q30;
            GetInverseQuaternion(qa, D_00276140);
            DivQuaternion(q20, nd->quat, e->quat);
            func_0010E1F8(qa, (short)(D_00633448 + D_0063344A));
            InvertCurrentQuaternion(qa);
            GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
            return;
        }
        goto sin_tail;
    }
    case 0x2F:
    case 0x33:
    {
        void *s0;
        float *qa;
        float *qb;
        if (D_00633F3C->f_204 != 0) {
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
            GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
            qa = q30;
            GetInverseQuaternion(qa, D_00276140);
            qb = q20;
            DivQuaternion(qb, nd->quat, e->quat);
            func_0010E1F8(qa, (short)-D_0063344A);
            func_0010E158(qa, (short)-D_00633446);
            func_0010E1F8(qa, (short)-D_00633444);
            MultiQuaternion(qa, qa, D_00633F24[e->f_38].quat);
            MultiQuaternion(qa, qa, qb);
            InvertCurrentQuaternion(qa);
            GetMatrixFromQuaternionRotElem(func_00105278(), GetLastQuaternion());
            return;
        }
sin_tail:
        {
            void *p0;
            p0 = GetLastQuaternion();
            MultiQuaternion(p0, GetTableSin(), nd->quat);
            p0 = func_00105278();
            GetMatrixFromQuaternionRotElem(p0, GetLastQuaternion());
            return;
        }
    }
    default:
    {
        void *p0;
        p0 = GetLastQuaternion();
        MultiQuaternion(p0, GetTableSin(), nd->quat);
        p0 = func_00105278();
        GetMatrixFromQuaternionRotElem(p0, GetLastQuaternion());
        return;
    }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", EditRotEmphasys);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", getFinalMatrix);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", getFinalMatrixWithNaturalGeometry);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", _calcNaturalGeometry);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", func_001D8968);

