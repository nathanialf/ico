#include "common.h"

typedef struct {
    char pad[0x134];
    int node_id;  /* 0x134 */
    char pad2[0x18C - 0x134 - 4];
    unsigned int flags;  /* 0x18C */
    char pad3[0x190 - 0x18C - 4];
} MotionNode;
extern MotionNode D_0055DA10[];
extern int D_004C0A98[];

void pursueNodeList(int a0) {
    int i;
    for (i = 0; i <= 0x43F; i++) {
        if (D_0055DA10[i].node_id == a0) {
            D_004C0A98[i] = 0;
        }
    }
}

int CheckMotionIncludeFacialData(void *a0) {
    return (char *)a0 + 0x10 < *(char **)((char *)a0 + 0x8) ? 0 : -1;
}

extern void func_001D1DF0(void *a0, void *a1, void *a2, void *a3, int a4);
extern char D_004C1BE0[];
extern char D_004C1BF0[];
extern char D_004C1C00[];
extern char D_004C1C10[];
extern char D_004C1C20[];

void InitMotionMemorySize(void) {
    func_001D1DF0(D_004C1BF0, D_004C1BE0, D_004C1C10, D_004C1BE0, -1);
    func_001D1DF0(D_004C1C10, D_004C1BE0, D_004C1C00, D_004C1BE0, -1);
    func_001D1DF0(D_004C1C00, D_004C1BE0, D_004C1C20, D_004C1BE0, -1);
    func_001D1DF0(D_004C1C20, D_004C1BE0, D_004C1BF0, D_004C1BE0, -1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", limitHPAngleAndSetB);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", avoidReverseInterpOnCurrentMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", avoidReverseInterpOnCurrentMatrixWithLimit);

/* --- ResetStatic2MotionManager ------------------------------------- */

typedef struct {                /* element of D_0062B758[], stride 0x40 */
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

typedef struct {                /* element of D_0062C218[], stride 0x20 */
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

typedef struct {                /* at (*(int *)(D_0062B75C+0x15C)) + 0xA0 */
    char _0[0x72C];
    MfBlend *blend;             /* 0x72C */
    void **mems;                /* 0x730 */
} MfHdr;

typedef struct {                /* *D_0062C230 */
    char _0[0x50];
    short f_50;                 /* 0x50 */
    char _52[0x1F4 - 0x52];
    int f_1F4;                  /* 0x1F4 */
    float f_1F8;                /* 0x1F8 */
    float f_1FC;                /* 0x1FC */
    char _200[0x20];
    int f_220;                  /* 0x220 */
    int f_224;                  /* 0x224 */
    char _228[0x8];
    float q_230[4];             /* 0x230 */
    float q_240[4];             /* 0x240 */
    char _250[0x30];
    int f_280;                  /* 0x280 */
    int f_284;                  /* 0x284 */
    char _288[0x8];
    float q_290[4];             /* 0x290 */
    float q_2A0[4];             /* 0x2A0 */
    float f_2B0;                /* 0x2B0 */
    int f_2B4;                  /* 0x2B4 */
    int f_2B8;                  /* 0x2B8 */
    char _2BC[4];
    float q_2C0[4];             /* 0x2C0 */
    int f_2D0;                  /* 0x2D0 */
    char _2D4[0xC];
    float q_2E0[4];             /* 0x2E0 */
    short f_2F0;                /* 0x2F0 */
    short f_2F2;                /* 0x2F2 */
    short f_2F4;                /* 0x2F4 */
    char _2F6[0x12];
    int f_308;                  /* 0x308 */
    int f_30C;                  /* 0x30C */
    char _310[0x10];
    int f_320;                  /* 0x320 */
    int f_324;                  /* 0x324 */
    char _328[0x28];
    int f_350;                  /* 0x350 */
    char _354[0x58];
    float f_3AC;                /* 0x3AC */
    float f_3B0;                /* 0x3B0 */
    float f_3B4;                /* 0x3B4 */
    float f_3B8;                /* 0x3B8 */
} MfMgr;

typedef struct {                /* *D_0062C234 */
    char _0[0x30];
    int f_30;                   /* 0x30 */
    char _34[0x34];
    int f_68;                   /* 0x68 */
    char _6C[0x154];
    void *f_1C0;                /* 0x1C0 */
} MfActor;

extern MfMot *D_0062B758_m __asm__("D_0062B758");
extern char *D_0062B75C;
extern MfOri *D_0062C218;
extern MfMgr *D_0062C230;
extern MfActor *D_0062C234;
extern char *D_0062C248;
extern float D_0062B720;
extern unsigned short D_0062B724;
extern unsigned short D_0062B726;
extern unsigned short D_0062B728;
extern unsigned short D_0062B72A;
extern float D_0062C214;
extern int D_0062C238;
extern int D_0062AFE0;
extern int D_0062B028;
extern int D_00271240[];
extern float D_006295A8, D_006295AC, D_006295B0, D_006295B4, D_006295B8;
extern float D_006295BC, D_006295C0, D_006295C4, D_006295C8, D_006295CC;
extern float D_006295D0, D_006295D4, D_006295D8, D_006295DC, D_006295E0;
extern float D_002724B0[];
extern float D_004C1C30[], D_004C1C40[], D_004C1C50[];
extern float D_00271BE0[], D_00271BF0[];
extern float D_00703020[], D_00703030[];

extern void sceVu0ScaleVectorXYZ(void *a0, void *a1, float a2);
extern void *func_00105078(void);
extern void *func_00105090(void);
extern void MatrixDrive_PushMatrixWithNoCopy(void);
extern void MatrixDrive_PopMatrix(void);
extern void func_001050A8(void *a0);
extern void func_00105108(float x, float y, float z);
extern void func_00104D20(void);
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
extern void func_0010E448(void *a0, int a1);
extern void func_0010E4E8(void *a0, int a1);
extern void func_0010E588(void *a0, int a1);
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
    unsigned int st;

    e = &D_0062B758_m[idx];
    nd = &D_0062C218[idx];
    {
        MfHdr *h = (MfHdr *)(*(int *)(D_0062B75C + 0x15C) + 0xA0);
        b = &h->blend[idx];
        mem = h->mems[idx];
    }
    if (e->f_38 != -1) {
        sceVu0ScaleVectorXYZ(buf10, e->pos, D_0062B720);
        s0 = (char *)func_00105078() + 0x30;
        sceVu0ApplyMatrix(s0, func_00105090(), buf10);
    } else {
        D_0062B72A = 0;
        D_0062B728 = 0;
        D_0062B726 = 0;
        D_0062B724 = 0;
    }
    st = e->state;
    switch (st) {
    case 0x0:
    {
        void *s0;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), nd->quat);
        {
            void *pa = GetLastQuaternion();
            float *pb = D_004C1C40;
            void *pc;
            pc = GetLastQuaternion();
            MultiQuaternion(pa, pb, pc);
        }
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        return;
    }
    case 0x2C:
    {
        void *s0;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), nd->quat);
        DivQuaternion(GetLastQuaternion(), GetLastQuaternion(), D_004C1C30);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
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
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_002724B0);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        if (D_0062C230->f_308 != 0 && D_0062C230->f_2D0 != 0) {
            float w, u, v, one, t, rot;
            w = b->rate;
            one = 1.0f;
            v = one - w;
            t = D_0062C230->f_3AC * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1]));
            u = one - t;
            if (D_0062AFE0 != 0) {
                rot = D_006295A8 * (float)D_0062B028;
            } else {
                rot = *(float *)(D_0062C248 + 0x158);
            }
            b->rate = w + v * (t + u * rot);
        } else {
            float w, u, one, t, rot;
            t = D_0062C230->f_3AC * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1]));
            one = 1.0f;
            u = one - t;
            w = b->rate;
            if (D_0062AFE0 != 0) {
                rot = D_006295AC * (float)D_0062B028;
            } else {
                rot = *(float *)(D_0062C248 + 0x158);
            }
            b->rate = w * (one - (t + u * rot));
        }
        memset(v50, 0, 0x10);
        v50[3] = 1.0f;
        if (D_0062C238 == 2) {
            func_0010E588(v50, 0x71C);
        }
        GetCurrentQuaternion(q40, v50, qb, b->rate);
        MultiQuaternion(qa, qa, q40);
        InvertCurrentQuaternion(qa);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        RegularizeQuaternion(q40, D_0062C230->q_2C0);
        {
            void *pa = GetLastQuaternion();
            void *pc = GetLastQuaternion();
            MultiQuaternion(pa, q40, pc);
        }
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        return;
    }
    case 0x23:
    {
        void *s0;
        int q;
        float *qb;
        float *w;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        GetInverseQuaternion(q30, D_002724B0);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        func_0010E588(GetLastQuaternion(), D_0062C230->f_2F4);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        if (D_0062C230->f_308 != 0 && D_0062C230->f_2D0 != 0) {
            b->rate += (1.0f - b->rate) * (D_0062C230->f_3AC * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1])));
        } else {
            b->rate *= 1.0f - D_0062C230->f_3AC * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1]));
        }
        if (b->rate < D_006295B0) {
            float *q3;
            GetInverseQuaternion(b->q1, GetLastQuaternion());
            q3 = b->q3;
            GetMatrixFromQuaternion(q3);
            GetInverseQuaternion(b->q2, q3);
        } else {
            if (D_0062C238 == 4) {
                MatrixDrive_RotMatrixX(-0x8000);
            }
            {
                float *pb = D_0062C230->q_2E0;
                void *t = func_00105078();
                w = v70;
                AddVectorXYZ(w, (char *)t + 0x30, D_0062C230);
                w = v60;
                SubVectorXYZ(w, pb, v70);
            }
            v60[3] = 0;
            MatrixDrive_PushMatrixWithNoCopy();
            MatrixDrive_TransMatrix(func_00105078(), func_00105090());
            {
                void *t = func_00105078();
                w = v50;
                sceVu0ApplyMatrix(w, t, v60);
            }
            MatrixDrive_PopMatrix();
            MatrixDrive_GetTurnYAngleXZ(&g80[0], &g80[1], v50[0], v50[1], v50[2]);
            limitHPAngleAndSetB(&g80[2], &g80[3], &g80[4], mem, g80[0], 0, (short)-(unsigned short)g80[1], 0, 1.0f, 0, 1);
            {
                int h3 = -g80[3];
                g80[3] = h3;
                if (D_0062C238 == 4) {
                    h3 = -(short)h3;
                    g80[3] = h3;
                }
            }
            {
                int d0 = (unsigned short)g80[0] - (unsigned short)g80[2];
                D_0062C230->f_2F2 = (unsigned short)g80[1] - (unsigned short)g80[3];
                D_0062C230->f_2F0 = d0;
            }
            {
                float *q3 = b->q3;
                float *q2 = b->q2;
                w = v60;
                GetMatrixFromQuaternion(w);
                func_0010E448(w, (short)-(unsigned short)g80[2]);
                func_0010E588(w, (short)-(unsigned short)g80[3]);
                func_0010E4E8(w, (short)-(unsigned short)g80[4]);
                avoidReverseInterpOnCurrentMatrixWithLimit(b->q1, mem, q3, w, D_006295B4);
                MultiQuaternion(v70, GetLastQuaternion(), w);
                w = q90;
                DivQuaternion(w, v70, b->q1);
                GetCurrentQuaternion(qA0, w, D_002724B0, D_0062C230->f_3B4);
                GetCurrentQuaternion(q2, qA0, q2, D_0062C230->f_3B8);
                MultiQuaternion(b->q1, b->q1, q2);
                GetSlerpQuaternionNoRegularize(b->q1);
                DivQuaternion(q3, b->q1, GetLastQuaternion());
            }
        }
        {
            s0 = GetLastQuaternion();
            func_0010E448(s0, (short)(int)((float)-D_0062C230->f_50 * 2.5f));
            s0 = GetLastQuaternion();
            MultiQuaternion(q90, s0, qb);
            GetCurrentQuaternion(GetLastQuaternion(), b->q1, q90, b->rate);
            {
                void *pa = GetLastQuaternion();
                float *tbl = D_004C1C50;
                void *pc = GetLastQuaternion();
                MultiQuaternion(pa, tbl, pc);
            }
        }
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
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
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        GetInverseQuaternion(q30, D_002724B0);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        MultiQuaternion(GetLastQuaternion(), GetLastQuaternion(), qb);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        if (D_0062C230->f_30C != 0
            && ((D_0062C230->f_308 != 0 && D_0062C230->f_2D0 != 0)
                || D_0062C230->f_220 != 0 || D_0062C230->f_280 != 0)) {
            float w, u, v, one, t, rot;
            w = b->rate;
            one = 1.0f;
            v = one - w;
            t = D_0062C230->f_3AC * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1]));
            u = one - t;
            if (D_0062AFE0 != 0) {
                rot = D_006295B8 * (float)D_0062B028;
            } else {
                rot = *(float *)(D_0062C248 + 0x158);
            }
            b->rate = w + v * (t + u * rot);
        } else {
            float w, u, one, t, rot;
            t = D_0062C230->f_3AC * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1]));
            one = 1.0f;
            u = one - t;
            w = b->rate;
            if (D_0062AFE0 != 0) {
                rot = D_006295BC * (float)D_0062B028;
            } else {
                rot = *(float *)(D_0062C248 + 0x158);
            }
            b->rate = w * (one - (t + u * rot));
        }
        if (b->rate < D_006295C0) {
            GetInverseQuaternion(b->q1, GetLastQuaternion());
            GetMatrixFromQuaternion(b->q3);
            GetInverseQuaternion(b->q2, b->q3);
        } else {
            float *q1;
            float *q3 = b->q3;
            avoidReverseInterpOnCurrentMatrix(b->q1, mem, q3);
            q1 = b->q1;
            sumA = 0;
            n = D_0062C230->f_30C;
            cnt = 0;
            if (n == 1) {
                if (D_0062C230->f_280 != 0) {
                    float *pb = D_0062C230->q_290;
                    cnt = 1;
                    s0 = func_00105078();
                    w = v60;
                    AddVectorXYZ(w, (char *)s0 + 0x30, D_0062C230);
                    w = v50;
                    SubVectorXYZ(w, pb, v60);
                    v50[3] = 0;
                    MatrixDrive_PushMatrixWithNoCopy();
                    MatrixDrive_TransMatrix(func_00105078(), func_00105090());
                    {
                        void *t = func_00105078();
                        w = qA0;
                        sceVu0ApplyMatrix(w, t, v50);
                    }
                    MatrixDrive_PopMatrix();
                    MatrixDrive_TransMatrixV(&gB0[0], &gB0[1], qA0[0], qA0[1], qA0[2]);
                    sumA = gB0[0];
                }
                if (D_0062C230->f_30C == n && D_0062C230->f_220 != 0) {
                    float *pb = D_0062C230->q_230;
                    void *t;
                    cnt += 1;
                    t = func_00105078();
                    AddVectorXYZ(v70, (char *)t + 0x30, D_0062C230);
                    SubVectorXYZ(v60, pb, v70);
                    v60[3] = 0;
                    MatrixDrive_PushMatrixWithNoCopy();
                    MatrixDrive_TransMatrix(func_00105078(), func_00105090());
                    t = func_00105078();
                    w = v50;
                    sceVu0ApplyMatrix(w, t, v60);
                    MatrixDrive_PopMatrix();
                    MatrixDrive_GetTurnZAngleXY(&gB0[2], &gB0[3], v50[0], v50[1], v50[2]);
                    sumA -= gB0[2];
                }
            }
            sumB = sumA;
            hold = 0;
            if (D_0062C230->f_308 != 0 && D_0062C230->f_2D0 != 0) {
                float *pb = D_0062C230->q_2E0;
                void *t;
                t = func_00105078();
                w = qD0;
                AddVectorXYZ(w, (char *)t + 0x30, D_0062C230);
                w = vC0;
                SubVectorXYZ(w, pb, qD0);
                vC0[3] = 0;
                MatrixDrive_PushMatrixWithNoCopy();
                MatrixDrive_TransMatrix(func_00105078(), func_00105090());
                t = func_00105078();
                w = v60;
                sceVu0ApplyMatrix(w, t, vC0);
                MatrixDrive_PopMatrix();
                MatrixDrive_GetTurnYAngleXZ(&gE0[0], &gE0[1], v60[0], v60[1], v60[2]);
                if (D_0062C230->f_2D0 == 2) {
                    hold = gE0[1];
                    sumA = sumB + gE0[0];
                    sumB = sumA;
                } else {
                    hold = D_0062C230->f_2F2;
                    sumA = sumB + D_0062C230->f_2F0;
                    sumB += gE0[0] / 2;
                }
                cnt += 1;
            }
            if (cnt != 0) {
                sumA = sumA / cnt;
                sumB = sumB / cnt;
            }
            limitHPAngleAndSetB(&gE0[2], &gE0[3], &gE0[4], mem, (short)sumA, b->f_4,
                                (short)-hold, (short)-b->f_8, 1.0f, 0, 0);
            limitHPAngleAndSetB(&gE0[5], &gE0[6], &gE0[7], mem, (short)sumB, b->f_4,
                                (short)-hold, (short)-b->f_8, 1.0f, 0, 0);
            {
                int h6 = -gE0[6];
                gE0[6] = h6;
            }
            w = v70;
            GetMatrixFromQuaternion(w);
            func_0010E448(w, (short)-(unsigned short)gE0[2]);
            func_0010E588(w, (short)-(unsigned short)gE0[6]);
            func_0010E4E8(w, (short)-(unsigned short)gE0[4]);
            MultiQuaternion(vC0, GetLastQuaternion(), w);
            w = qD0;
            DivQuaternion(w, vC0, q1);
            GetCurrentQuaternion(qF0, w, D_002724B0, D_0062C230->f_3B4);
            GetCurrentQuaternion(b->q2, qF0, b->q2, D_0062C230->f_3B8);
            MultiQuaternion(q1, q1, b->q2);
            GetSlerpQuaternionNoRegularize(q1);
            DivQuaternion(q3, q1, GetLastQuaternion());
            {
                int step;
                t = (float)b->f_E;
                step = (int)(t + ((float)(gE0[6] - (short)b->f_8) * D_0062C230->f_3B4 - t) * D_0062C230->f_3B8);
                b->f_E = step;
                b->f_8 = b->f_8 + step;
                D_0062C230->f_2F4 = (int)((float)(short)b->f_8 * b->rate);
            }
        }
        s0 = GetLastQuaternion();
        func_0010E448(s0, (short)(int)((float)D_0062C230->f_50 * 2.5f));
        GetCurrentQuaternion(GetLastQuaternion(), b->q1, GetLastQuaternion(), b->rate);
        {
            void *pa = GetLastQuaternion();
            float *pc = D_0062C230->q_2C0;
            MultiQuaternion(pa, pc, GetLastQuaternion());
        }
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        _ApplyMatrix(D_00703020, func_00105078(), D_00271BF0);
        return;
    }
    case 0x12:
    {
        void *s0;
        float *qa;
        float *qb;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_002724B0);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        MultiQuaternion(qa, qa, qb);
        InvertCurrentQuaternion(qa);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
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
        float *qb;
        float *pb;
        float *qF0p;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        GetInverseQuaternion(q30, D_002724B0);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        memset(qA0, 0, 0x10);
        qA0[3] = 1.0f;
        pb = D_0062C230->q_290;
        AddVectorXYZ(v70, (char *)func_00105078() + 0x30, D_0062C230);
        SubVectorXYZ(v60, pb, v70);
        v60[3] = 0;
        MatrixDrive_PushMatrixWithNoCopy();
        MatrixDrive_TransMatrix(func_00105078(), func_00105090());
        sceVu0ApplyMatrix(vC0, func_00105078(), v60);
        MatrixDrive_PopMatrix();
        MatrixDrive_GetTurnXAngleZY(&g100[2], &g100[3], vC0[0], vC0[1], vC0[2]);
        limitHPAngleAndSetB(&g100[4], &g100[5], &g100[6], mem, g100[2], 0, g100[3], 0, 1.0f, 1, 0);
        if (D_0062C230->f_284 != 0) {
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
        nq = GetTableArcCos(_InnerProduct(v50, D_00271BF0));
        _OuterProduct(v60, v50, D_00271BF0);
        SetQuaternionByAxisRotateV(qD0, nq, v60);
        MultiQuaternion(qA0, qA0, qD0);
        if (D_0062C230->f_280 == 1) goto L13turn;
        if (D_0062C230->f_280 == 2) goto L13mul;
        qF0p = qF0;
        GetInverseQuaternion(qF0p, qb);
        GetCurrentQuaternion(D_0062C230->q_2C0, D_0062C230->q_2C0, D_002724B0, D_006295C4);
        w = v60;
        goto L13done;
      L13turn:
        {
            w = v60;
            qF0p = qF0;
            i = 0;
            ang = VectorLength(vC0);
            n = e->next;
            if (n == -1) goto none13;
            do {
                MfMot *o = &D_0062B758_m[n];
                w[i++] = D_0062B720 * VectorLength(o->pos);
                if (i >= 2) break;
                n = o->next;
none13:;
            } while (n != -1);
            v60[1] += D_0062B720 * VectorLength(
                D_0062B758_m[DebugDisp1CollisionWithColor(D_0062B75C, 0x20)].pos);
            MatrixDrive_PushMatrixWithNoCopy();
            {
                int k = DebugDisp1CollisionWithColor(D_0062B75C, 0x16);
                getQuaternionFromMatrix(func_00105078(), (char *)&D_0062C218[k] + 0x10);
            }
            func_00105108(5.0f, -3.0f, 0.0f);
            MatrixDrive_TurnObjectMatrix(v110, (char *)func_00105078() + 0x30);
            _AddVector(v70, D_0062B758_m[e->next].pos, v110);
            rot = D_0062B720 * VectorLength(v70);
            v130[0] = rot;
            v130[1] = 0.0f;
            v130[2] = 0.0f;
            v130[3] = 1.0f;
            _SubVectorXYZ(v130, v130, v110);
            _NormalizeVector(v130, v130);
            _OuterProduct(v120, v130, D_00271BF0);
            SetQuaternionByAxisRotateV(D_00703030, GetTableArcCos(_InnerProduct(D_00271BF0, v130)), v120);
            v60[1] = rot;
            MatrixDrive_PopMatrix();
            if (D_0062C230->f_2B4 == 0) {
                float t = v60[0] + v60[1];
                if (t < ang) {
                    ang = t;
                }
            }
            len2 = ang * ang;
            D_0062B728 = GetTableArcCos(
                (len2 + v60[0] * v60[0] - v60[1] * v60[1]) / ((v60[0] + v60[0]) * ang));
            D_0062B72A = GetTableArcCos(
                (len2 + v60[1] * v60[1] - v60[0] * v60[0]) / ((v60[1] + v60[1]) * ang));
            func_0010E448(qA0, g100[6]);
            func_0010E588(qA0, (short)D_0062B728);
            GetInverseQuaternion(qF0p, qA0);
            {
                float *pb = D_0062C230->q_290;
                void *t = func_00105078();
                AddVectorXYZ(v120, (char *)t + 0x30, D_0062C230);
                SubVectorXYZ(v70, pb, v120);
            }
            v70[3] = 0;
            _NormalizeVector(v70, v70);
            _OuterProduct(v110, v70, D_00703020);
            if (D_0062C230->f_350 == 2 && ang + 0.0f > v60[0] + v60[1]) {
                SetQuaternionByAxisRotateV(v120, (short)((ang + 0.0f - (v60[0] + v60[1])) * D_006295C8), v110);
                GetCurrentQuaternion(D_0062C230->q_2C0, D_0062C230->q_2C0, v120, D_006295CC);
            } else {
                GetCurrentQuaternion(D_0062C230->q_2C0, D_0062C230->q_2C0, D_002724B0, D_006295D0);
            }
        }
        goto L13done;
      L13mul:
        qF0p = qF0;
        MultiQuaternion(qF0p, qA0, D_0062C230->q_2A0);
        MultiQuaternion(qF0p, qF0p, qb);
        GetCurrentQuaternion(D_0062C230->q_2C0, D_0062C230->q_2C0, D_002724B0, D_006295D4);
        w = v60;
      L13done:
        GetCurrentQuaternion(b->q1, qF0p, b->q1, D_0062C230->f_2B0 * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1])));
        if (D_0062C230->f_280 != 0) {
            b->rate = b->rate + (1.0f - b->rate) * (D_0062C230->f_3B0 * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1])));
        } else {
            b->rate = b->rate * (1.0f - D_0062C230->f_3B0 * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1])));
        }
        GetCurrentQuaternion(w, b->q1, qb, b->rate);
        MultiQuaternion(q30, q30, w);
        InvertCurrentQuaternion(q30);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        D_0062C214 = b->rate;
        n = 1;
        if (!(D_006295D8 < b->rate)) {
            n = 0;
        }
        if (n != 0 && D_0062C230->f_2B8 == 0) {
            D_0062C230->f_2B4 = 1;
        } else {
            D_0062C230->f_2B4 = 0;
        }
        D_0062C230->f_2B8 = n;
        return;
    }
    case 0x14:
    {
        void *s0;
        int q;
        float *qa;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_002724B0);
        DivQuaternion(q20, nd->quat, e->quat);
        GetInverseQuaternion(v60, q20);
        if (D_0062C230->f_280 == 1) {
            SetQuaternionByAxisRotateWithNoRegularize(v60, (short)-(D_0062B728 + D_0062B72A), 0.0f, 0.0f, -1.0f);
            MultiQuaternion(v60, v60, D_00703030);
        }
        GetCurrentQuaternion(b->q1, v60, b->q1, D_0062C230->f_2B0 * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1])));
        GetCurrentQuaternion(v70, b->q1, q20, D_0062C214);
        MultiQuaternion(qa, qa, v70);
        InvertCurrentQuaternion(qa);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
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
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_002724B0);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        if (D_0062C230->f_320 != 0) {
            w = v60;
            GetInverseQuaternion(w, D_002724B0);
        } else {
            w = v60;
            GetInverseQuaternion(w, qb);
        }
        GetCurrentQuaternion(v70, w, qb, D_0062C214);
        MultiQuaternion(qa, qa, v70);
        InvertCurrentQuaternion(qa);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        if (D_0062C234->f_1C0 != 0
            && !((D_0055DA10[D_0062C234->f_30].flags >> 1) & 1)) {
            n = D_0062C234->f_68;
            if (n != 6) {
                if (n < 7) {
                    if (n == 0) {
                        goto no_swap;
                    }
                    goto swap_weapon;
                }
                if (n != 0xE && n != 0x13) {
swap_weapon:
                    t = CheckSwapableWeapon(D_0062C234->f_1C0) * D_006295DC;
                    t = D_006295E0 < t ? D_006295E0 : t;
                    GetCurrentQuaternion(b->q1, b->q1, GetLastQuaternion(), t);
                    GetInverseQuaternion(GetLastQuaternion(), b->q1);
                    GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
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
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        return;
    }
    case 0x2:
    {
        void *s0;
        float *qa;
        float *qb;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_002724B0);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        MultiQuaternion(qa, qa, qb);
        InvertCurrentQuaternion(qa);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
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
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_002724B0);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        memset(v110, 0, 0x10);
        qc = v110;
        v110[3] = 1.0f;
        {
            float *pb = D_0062C230->q_230;
            void *t = func_00105078();
            w = v170;
            AddVectorXYZ(w, (char *)t + 0x30, D_0062C230);
            w = v160;
            SubVectorXYZ(w, pb, v170);
        }
        v160[3] = 0;
        MatrixDrive_PushMatrixWithNoCopy();
        MatrixDrive_TransMatrix(func_00105078(), func_00105090());
        {
            void *t = func_00105078();
            w = v120;
            sceVu0ApplyMatrix(w, t, v160);
        }
        MatrixDrive_PopMatrix();
        MatrixDrive_GetTurnXAngleZY(&g180[0], &g180[1], v120[0], v120[1], v120[2]);
        limitHPAngleAndSetB(&g180[2], &g180[3], &g180[4], mem, g180[0], 0, g180[1], 0, 1.0f, 1, 0);
        if (D_0062C230->f_224 != 0) {
            _NormalizeVector(v150, v120);
        } else {
            short h1 = g180[3];
            short h0 = g180[2];
            float t = GetTableCos(h1);
            v150[0] = GetTableCos(h0) * t;
            v150[1] = p2o_SetDefaultEnviroment(h0) * t;
            v150[2] = -p2o_SetDefaultEnviroment(h1);
            v150[3] = 0;
        }
        nq = GetTableArcCos(_InnerProduct(v150, D_00271BF0));
        _OuterProduct(v160, v150, D_00271BF0);
        SetQuaternionByAxisRotateV(v130, nq, v160);
        MultiQuaternion(qc, qc, v130);
        if (D_0062C230->f_220 == 1) goto L3turn;
        if (D_0062C230->f_220 == 2) goto L3mul;
        GetInverseQuaternion(v70, qb);
        goto L3done;
      L3turn:
        {
            w = v160;
            i = 0;
            ang = VectorLength(v120);
            n = e->next;
            len2 = ang * ang;
            if (n == -1) goto none3;
            do {
                MfMot *o = &D_0062B758_m[n];
                w[i++] = D_0062B720 * VectorLength(o->pos);
                if (i >= 2) break;
                n = o->next;
none3:;
            } while (n != -1);
            w[1] += D_0062B720 * VectorLength(
                D_0062B758_m[DebugDisp1CollisionWithColor(D_0062B75C, 0x10)].pos);
            D_0062B728 = GetTableArcCos(
                (len2 + w[0] * w[0] - w[1] * w[1]) / ((w[0] + w[0]) * ang));
            D_0062B72A = GetTableArcCos(
                (len2 + w[1] * w[1] - w[0] * w[0]) / ((w[1] + w[1]) * ang));
            func_0010E448(qc, g180[4]);
            func_0010E588(qc, (short)D_0062B728);
            GetInverseQuaternion(v70, qc);
        }
        goto L3done;
      L3mul:
        MultiQuaternion(v70, qc, D_0062C230->q_240);
        MultiQuaternion(v70, v70, qb);
      L3done:
        GetCurrentQuaternion(b->q1, v70, b->q1, D_0062C230->f_3B0 * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1])));
        if (D_0062C230->f_220 != 0) {
            b->rate = b->rate + (1.0f - b->rate) * (D_0062C230->f_3B0 * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1])));
        } else {
            b->rate = b->rate * (1.0f - D_0062C230->f_3B0 * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1])));
        }
        GetCurrentQuaternion(v160, b->q1, qb, b->rate);
        MultiQuaternion(qa, qa, v160);
        InvertCurrentQuaternion(qa);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        D_0062C214 = b->rate;
        return;
    }
    case 0x4:
    {
        void *s0;
        int q;
        float *qa;
        float *qb;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_002724B0);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        GetInverseQuaternion(v160, qb);
        if (D_0062C230->f_220 == 1) {
            SetQuaternionByAxisRotateWithNoRegularize(v160, (short)-(D_0062B728 + D_0062B72A), 0.0f, 0.0f, -1.0f);
        }
        GetCurrentQuaternion(b->q1, v160, b->q1, D_0062C230->f_3B0 * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1])));
        GetCurrentQuaternion(v170, b->q1, qb, D_0062C214);
        MultiQuaternion(qa, qa, v170);
        InvertCurrentQuaternion(qa);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        return;
    }
    case 0x6:
    {
        void *s0;
        float *qa;
        float *qb;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_002724B0);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        if (D_0062C230->f_324 != 0) {
            GetInverseQuaternion(b->q1, D_002724B0);
        } else {
            GetInverseQuaternion(b->q1, qb);
        }
        GetCurrentQuaternion(v160, b->q1, qb, D_0062C214);
        MultiQuaternion(qa, qa, v160);
        InvertCurrentQuaternion(qa);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        return;
    }
    case 0x5:
    {
        void *s0;
        float *qa;
        float *qb;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_002724B0);
        qb = q20;
        DivQuaternion(qb, nd->quat, e->quat);
        if (D_0062C230->f_220 != 0) {
            if (D_0062C230->f_220 != 1) {
                MultiQuaternion(qa, qa, qb);
            }
        } else {
            MultiQuaternion(qa, qa, qb);
        }
        InvertCurrentQuaternion(qa);
        GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
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
        if (D_0062C230->f_1F4 != 0) {
            endflag = 0;
            i = 0;
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
            GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
            qa = q30;
            GetInverseQuaternion(qa, D_002724B0);
            qb = q20;
            DivQuaternion(qb, nd->quat, e->quat);
            func_00104D20();
            MatrixDrive_TurnObjectMatrix((char *)func_00105078() + 0x30, D_00271BE0);
            MultiMatrixByQuaternion(qb);
            func_00104D20();
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
                MfMot *o = &D_0062B758_m[n];
                sceVu0ScaleVectorXYZ(q190, o->pos, D_0062B720);
                func_001050A8(q190);
                MultiMatrixByQuaternion(D_0062C218[n].quat);
                wq[i++] = D_0062B720 * VectorLength(o->pos);
                if (i >= 2) goto done2D;
                n = o->next;
                }
            } while (n != -1);
            endflag = 1;
done2D:;
            MatrixDrive_TurnObjectMatrix(v170, (char *)func_00105078() + 0x30);
            if (e->state == 0x2D) goto add1F8;
            if (e->state == 0x31) goto add1FC;
            goto addend;
add1F8:
            v170[1] += D_0062C230->f_1F8;
            goto addend;
add1FC:
            v170[1] += D_0062C230->f_1FC;
addend:;
            ang = VectorLength(v170);
            MatrixDrive_PopMatrix();
            len2 = ang * ang;
            s0 = func_00105078();
            sceVu0TransposeMatrix(s0, s0);
            sceVu0ApplyMatrix(v170, s0, v170);
            sceVu0Normalize(v170, v170);
            D_0062B724 = GetTableArcSin(v170[1]);
            D_0062B726 = -GetTableArcSin(v170[2]);
            D_0062B728 = GetTableArcCos(
                (len2 + v160[0] * v160[0] - v160[1] * v160[1]) / ((v160[0] + v160[0]) * ang));
            D_0062B72A = GetTableArcCos(
                (len2 + v160[1] * v160[1] - v160[0] * v160[0]) / ((v160[1] + v160[1]) * ang));
            MatrixDrive_PopMatrix();
            if (endflag == 0) {
                MultiQuaternion(qa, qa, qb);
                func_0010E588(qa, (short)D_0062B724);
                func_0010E4E8(qa, (short)D_0062B726);
                func_0010E588(qa, (short)-D_0062B728);
            } else {
                MultiQuaternion(qa, qa, qb);
            }
            InvertCurrentQuaternion(qa);
            GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
            return;
        }
        goto sin_tail;
    }
    case 0x2E:
    case 0x32:
    {
        void *s0;
        float *qa;
        if (D_0062C230->f_1F4 != 0) {
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
            GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
            qa = q30;
            GetInverseQuaternion(qa, D_002724B0);
            DivQuaternion(q20, nd->quat, e->quat);
            func_0010E588(qa, (short)(D_0062B728 + D_0062B72A));
            InvertCurrentQuaternion(qa);
            GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
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
        if (D_0062C230->f_1F4 != 0) {
        MultiQuaternion(GetLastQuaternion(), GetTableSin(), e->quat);
            GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
            qa = q30;
            GetInverseQuaternion(qa, D_002724B0);
            qb = q20;
            DivQuaternion(qb, nd->quat, e->quat);
            func_0010E588(qa, (short)-D_0062B72A);
            func_0010E4E8(qa, (short)-D_0062B726);
            func_0010E588(qa, (short)-D_0062B724);
            MultiQuaternion(qa, qa, D_0062C218[e->f_38].quat);
            MultiQuaternion(qa, qa, qb);
            InvertCurrentQuaternion(qa);
            GetMatrixFromQuaternionRotElem(func_00105078(), GetLastQuaternion());
            return;
        }
sin_tail:
        {
            void *p0;
            p0 = GetLastQuaternion();
            MultiQuaternion(p0, GetTableSin(), nd->quat);
            p0 = func_00105078();
            GetMatrixFromQuaternionRotElem(p0, GetLastQuaternion());
            return;
        }
    }
    default:
    {
        void *p0;
        p0 = GetLastQuaternion();
        MultiQuaternion(p0, GetTableSin(), nd->quat);
        p0 = func_00105078();
        GetMatrixFromQuaternionRotElem(p0, GetLastQuaternion());
        return;
    }
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", EditRotEmphasys);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", getFinalMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", getFinalMatrixWithNaturalGeometry);

extern char *D_0062B758;
extern char *D_0062C244;
extern float D_0062B720;
extern char D_00703040[];
extern char D_00703080[];
extern void _ScaleVectorXYZ(void *buf, void *p1, float f);
extern void GetMatrixFromQuaternionPos(void *a0, void *a1, void *a2);
extern void getQuaternionFromMatrix(void *a0, void *a1);
extern void *func_00105078(void);
extern void *func_00105090(void);
extern void _MulMatrix(void *a0, void *a1, void *a2);

void _calcNaturalGeometry(int a0) {
    char *elemA = D_0062B758 + a0 * 0x40;
    char *elemB = D_0062C244 + a0 * 0x20;
    void *x;
    if (*(int *)(elemA + 0x38) != -1) {
        _ScaleVectorXYZ(D_00703080, elemA + 0x10, D_0062B720);
        GetMatrixFromQuaternionPos(D_00703040, elemB + 0x10, D_00703080);
    } else {
        getQuaternionFromMatrix(D_00703040, elemB + 0x10);
    }
    x = func_00105078();
    _MulMatrix(x, func_00105090(), D_00703040);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", func_001D5D00);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00611A30;  /* stride 0x4 */

/* end struct shapes */
