#include "common.h"

typedef struct {
    char pad[0x134];
    int node_id;  /* 0x134 */
    char pad2[0x190 - 0x134 - 4];
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

int InitMotionFile(void *a0) {
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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", AddMotionMemorySize);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", GetMotionMemorySize);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", ResetDynamicMotionManager);

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

extern void func_00240968(void *a0, void *a1, float a2);
extern void *func_00105078(void);
extern void *func_00105090(void);
extern void func_00105058(void);
extern void func_00105068(void);
extern void func_001050A8(void *a0);
extern void func_00105108(float x, float y, float z);
extern void func_00104D20(void);
extern void func_00104D48(int a0);
extern void func_0023FDD8(void *a0, void *a1, void *a2);
extern void func_0023FED0(void *a0, void *a1);
extern void func_0023FE98(void *a0, void *a1);
extern void *GetLastQuaternion(void);
extern void *GetTableSin(void);
extern void func_0010E148(void *a0, void *a1, void *a2);
extern void func_0010E188(void *a0, void *a1, void *a2);
extern void func_0010E1D0(void *a0, void *a1);
extern void func_0010E300(void *a0);
extern void func_0010E448(void *a0, int a1);
extern void func_0010E4E8(void *a0, int a1);
extern void func_0010E588(void *a0, int a1);
extern void func_0010E088(void *a0, int a1, void *a2);
extern void GetInverseQuaternion(void *a0, void *a1);
extern void func_00260568(void *a0, int a1, int a2);
extern void GetCurrentQuaternion(void *dst, void *qa, void *qb, float t);
extern void InvertCurrentQuaternion(void *a0);
extern void RegularizeQuaternion(void *a0, void *a1);
extern void GetMatrixFromQuaternion(void *a0);
extern void GetSlerpQuaternionNoRegularize(void *a0);
extern void MatrixDrive_TurnZObjectMatrixXY(void *a0, void *a1, void *a2);
extern void MatrixDrive_GetTurnXAngleZY(void *a0, void *a1, void *a2);
extern void MatrixDrive_TransMatrix(void *a0, void *a1);
extern void MatrixDrive_PushMatrixWithNoCopy(void *o1, void *o2, float x, float y, float z);
extern void MatrixDrive_TransMatrixV(void *o1, void *o2, float x, float y, float z);
extern void MatrixDrive_GetMatrix(void *o1, void *o2, float x, float y, float z);
extern void MatrixDrive_ScaleMatrix(void *o1, void *o2, float x, float y, float z);
extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);
extern float MatrixDrive_GetTurnYEAngleXZ(void *a0);
extern void AddMotionMemorySize(void *a0, void *a1, void *a2, void *a3,
                                int a4, int a5, int a6, int a7, float w,
                                int s0, int s1);
extern void GetMotionMemorySize(void *a0, void *a1, void *a2);
extern void ResetDynamicMotionManager(void *a0, void *a1, void *a2, void *a3, float w);
extern void _SetCurrentMatrix(void *a0, void *a1);
extern void _MulCurrentMatrixL(void *a0, void *a1, void *a2);
extern float _MulCurrentMatrixR(void *a0, void *a1);
extern void _ApplyCurrentMatrix(void *a0, void *a1, void *a2);
extern void _TransposeRotationCurrentMatrix(void *a0, void *a1, void *a2);
extern float func_0010ED30(short a0);
extern float p2o_SetDefaultEnviroment(short a0);
extern int func_0010EE60(float x);
extern int func_0010EEF0(float x);
extern void func_00118A70(void *a0, void *a1, void *a2);
extern void GetTableArcCos(void *self, int a1, float x, float y, float z);
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
    float *pv;
    unsigned int st;

    e = &D_0062B758_m[idx];
    nd = &D_0062C218[idx];
    {
        MfHdr *h = (MfHdr *)(*(int *)(D_0062B75C + 0x15C) + 0xA0);
        b = &h->blend[idx];
        mem = h->mems[idx];
    }
    if (e->f_38 != -1) {
        func_00240968(buf10, e->pos, D_0062B720);
        s0 = (char *)func_00105078() + 0x30;
        func_0023FDD8(s0, func_00105090(), buf10);
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
        func_0010E148(GetLastQuaternion(), GetTableSin(), nd->quat);
        {
            float *tbl;
            void *pa = GetLastQuaternion();
            void *pc;
            tbl = D_004C1C40;
            pc = GetLastQuaternion();
            func_0010E148(pa, tbl, pc);
        }
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        return;
    }
    case 0x2C:
    {
        void *s0;
        func_0010E148(GetLastQuaternion(), GetTableSin(), nd->quat);
        func_0010E188(GetLastQuaternion(), GetLastQuaternion(), D_004C1C30);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
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
        func_0010E148(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_002724B0);
        qb = q20;
        func_0010E188(qb, nd->quat, e->quat);
        if (D_0062C230->f_308 != 0 && D_0062C230->f_2D0 != 0) {
            float w, u, v, one;
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
            float w, u, one;
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
        func_00260568(v50, 0, 0x10);
        v50[3] = 1.0f;
        if (D_0062C238 == 2) {
            func_0010E588(v50, 0x71C);
        }
        GetCurrentQuaternion(q40, v50, qb, b->rate);
        func_0010E148(qa, qa, q40);
        InvertCurrentQuaternion(qa);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        RegularizeQuaternion(q40, D_0062C230->q_2C0);
        {
            void *pa = GetLastQuaternion();
            void *pc = GetLastQuaternion();
            func_0010E148(pa, q40, pc);
        }
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        return;
    }
    case 0x23:
    {
        void *s0;
        int q;
        float *qb;
        float *q1;
        float *w;
        float *w2;
        func_0010E148(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        GetInverseQuaternion(q30, D_002724B0);
        qb = q20;
        func_0010E188(qb, nd->quat, e->quat);
        func_0010E588(GetLastQuaternion(), D_0062C230->f_2F4);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        if (D_0062C230->f_308 != 0 && D_0062C230->f_2D0 != 0) {
            b->rate += (1.0f - b->rate) * (D_0062C230->f_3AC * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1])));
        } else {
            b->rate *= 1.0f - D_0062C230->f_3AC * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1]));
        }
        if (b->rate < D_006295B0) {
            float *q3;
            q1 = b->q1;
            GetInverseQuaternion(q1, GetLastQuaternion());
            q3 = b->q3;
            GetMatrixFromQuaternion(q3);
            GetInverseQuaternion(b->q2, q3);
        } else {
            if (D_0062C238 == 4) {
                func_00104D48(-0x8000);
            }
            {
                float *pb = D_0062C230->q_2E0;
                void *t = func_00105078();
                w = v70;
                MatrixDrive_TurnZObjectMatrixXY(w, (char *)t + 0x30, D_0062C230);
                w = v60;
                w2 = v70;
                MatrixDrive_GetTurnXAngleZY(w, pb, w2);
            }
            v60[3] = 0;
            func_00105058();
            MatrixDrive_TransMatrix(func_00105078(), func_00105090());
            {
                void *t = func_00105078();
                w = v50;
                w2 = v60;
                func_0023FDD8(w, t, w2);
            }
            func_00105068();
            MatrixDrive_PushMatrixWithNoCopy(&g80[0], &g80[1], v50[0], v50[1], v50[2]);
            AddMotionMemorySize(&g80[2], &g80[3], &g80[4], mem, g80[0], 0, (short)-(unsigned short)g80[1], 0, 1.0f, 0, 1);
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
                q1 = b->q1;
                w = v60;
                GetMatrixFromQuaternion(w);
                func_0010E448(w, (short)-(unsigned short)g80[2]);
                func_0010E588(w, (short)-(unsigned short)g80[3]);
                func_0010E4E8(w, (short)-(unsigned short)g80[4]);
                ResetDynamicMotionManager(q1, mem, q3, w, D_006295B4);
                w2 = v70;
                func_0010E148(w2, GetLastQuaternion(), w);
                w = q90;
                func_0010E188(w, w2, q1);
                w2 = qA0;
                GetCurrentQuaternion(w2, w, D_002724B0, D_0062C230->f_3B4);
                GetCurrentQuaternion(q2, w2, q2, D_0062C230->f_3B8);
                func_0010E148(q1, q1, q2);
                GetSlerpQuaternionNoRegularize(q1);
                func_0010E188(q3, q1, GetLastQuaternion());
            }
        }
        {
            float *tbl = D_004C1C50;
            s0 = GetLastQuaternion();
            func_0010E448(s0, (short)(int)((float)-D_0062C230->f_50 * 2.5f));
            s0 = GetLastQuaternion();
            func_0010E148(q90, s0, qb);
            GetCurrentQuaternion(GetLastQuaternion(), q1, q90, b->rate);
            {
                void *pa = GetLastQuaternion();
                void *pc = GetLastQuaternion();
                func_0010E148(pa, tbl, pc);
            }
        }
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        return;
    }
    case 0x1:
    {
        void *s0;
        int q;
        int n;
        float t;
        float rot;
        float ang;
        int sumA;
        int sumB;
        int cnt;
        int hold;
        float *w;
        float *w2;
        float *qb;
        float *q1a;
        func_0010E148(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        GetInverseQuaternion(q30, D_002724B0);
        qb = q20;
        func_0010E188(qb, nd->quat, e->quat);
        func_0010E148(GetLastQuaternion(), GetLastQuaternion(), qb);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        if (D_0062C230->f_30C != 0
            && ((D_0062C230->f_308 != 0 && D_0062C230->f_2D0 != 0)
                || D_0062C230->f_220 != 0 || D_0062C230->f_280 != 0)) {
            float w, u, v, one;
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
            float w, u, one;
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
        q1a = b->q1;
        if (b->rate < D_006295C0) {
            GetInverseQuaternion(q1a, GetLastQuaternion());
            GetMatrixFromQuaternion(b->q3);
            GetInverseQuaternion(b->q2, b->q3);
        } else {
            float *q1;
            float *q3 = b->q3;
            GetMotionMemorySize(q1a, mem, q3);
            q1 = q1a;
            sumA = 0;
            n = D_0062C230->f_30C;
            cnt = 0;
            if (n == 1) {
                if (D_0062C230->f_280 != 0) {
                    float *pb = D_0062C230->q_290;
                    cnt = 1;
                    s0 = func_00105078();
                    w = v60;
                    MatrixDrive_TurnZObjectMatrixXY(w, (char *)s0 + 0x30, D_0062C230);
                    w = v50;
                    w2 = v60;
                    MatrixDrive_GetTurnXAngleZY(w, pb, w2);
                    v50[3] = 0;
                    func_00105058();
                    MatrixDrive_TransMatrix(func_00105078(), func_00105090());
                    {
                        void *t = func_00105078();
                        w = qA0;
                        w2 = v50;
                        func_0023FDD8(w, t, w2);
                    }
                    func_00105068();
                    MatrixDrive_TransMatrixV(&gB0[0], &gB0[1], qA0[0], qA0[1], qA0[2]);
                    sumA = gB0[0];
                }
                if (D_0062C230->f_30C == n && D_0062C230->f_220 != 0) {
                    float *pb = D_0062C230->q_230;
                    void *t;
                    cnt += 1;
                    t = func_00105078();
                    w = v70;
                    MatrixDrive_TurnZObjectMatrixXY(w, (char *)t + 0x30, D_0062C230);
                    w = v60;
                    w2 = v70;
                    MatrixDrive_GetTurnXAngleZY(w, pb, w2);
                    v60[3] = 0;
                    func_00105058();
                    MatrixDrive_TransMatrix(func_00105078(), func_00105090());
                    t = func_00105078();
                    w = v50;
                    w2 = v60;
                    func_0023FDD8(w, t, w2);
                    func_00105068();
                    MatrixDrive_GetMatrix(&gB0[2], &gB0[3], v50[0], v50[1], v50[2]);
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
                MatrixDrive_TurnZObjectMatrixXY(w, (char *)t + 0x30, D_0062C230);
                w = vC0;
                w2 = qD0;
                MatrixDrive_GetTurnXAngleZY(w, pb, w2);
                vC0[3] = 0;
                func_00105058();
                MatrixDrive_TransMatrix(func_00105078(), func_00105090());
                t = func_00105078();
                w = v60;
                w2 = vC0;
                func_0023FDD8(w, t, w2);
                func_00105068();
                MatrixDrive_PushMatrixWithNoCopy(&gE0[0], &gE0[1], v60[0], v60[1], v60[2]);
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
            AddMotionMemorySize(&gE0[2], &gE0[3], &gE0[4], mem, (short)sumA, b->f_4,
                                (short)-hold, (short)-b->f_8, 1.0f, 0, 0);
            AddMotionMemorySize(&gE0[5], &gE0[6], &gE0[7], mem, (short)sumB, b->f_4,
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
            w2 = vC0;
            func_0010E148(w2, GetLastQuaternion(), w);
            w = qD0;
            func_0010E188(w, w2, q1);
            w2 = qF0;
            GetCurrentQuaternion(w2, w, D_002724B0, D_0062C230->f_3B4);
            GetCurrentQuaternion(b->q2, w2, b->q2, D_0062C230->f_3B8);
            func_0010E148(q1, q1, b->q2);
            GetSlerpQuaternionNoRegularize(q1);
            func_0010E188(q3, q1, GetLastQuaternion());
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
        GetCurrentQuaternion(GetLastQuaternion(), q1a, GetLastQuaternion(), b->rate);
        {
            void *pa = GetLastQuaternion();
            float *pc = D_0062C230->q_2C0;
            func_0010E148(pa, pc, GetLastQuaternion());
        }
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        func_00118A70(D_00703020, func_00105078(), D_00271BF0);
        return;
    }
    case 0x12:
    {
        void *s0;
        float *qa;
        float *qb;
        func_0010E148(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_002724B0);
        qb = q20;
        func_0010E188(qb, nd->quat, e->quat);
        func_0010E148(qa, qa, qb);
        InvertCurrentQuaternion(qa);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        return;
    }
    case 0x13:
    {
        void *s0;
        int q;
        int n;
        int i;
        float t;
        float rot;
        float len2;
        float ang;
        float *qa;
        float *qb;
        float *w;
        float *w2;
        float *qs;
        float *qn;
        float *pb;
        func_0010E148(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_002724B0);
        qb = q20;
        func_0010E188(qb, nd->quat, e->quat);
        qs = qA0;
        func_00260568(qs, 0, 0x10);
        qA0[3] = 1.0f;
        pb = D_0062C230->q_290;
        MatrixDrive_TurnZObjectMatrixXY(v70, (char *)func_00105078() + 0x30, D_0062C230);
        MatrixDrive_GetTurnXAngleZY(v60, pb, v70);
        v60[3] = 0;
        func_00105058();
        MatrixDrive_TransMatrix(func_00105078(), func_00105090());
        func_0023FDD8(vC0, func_00105078(), v60);
        func_00105068();
        MatrixDrive_ScaleMatrix(&g100[2], &g100[3], vC0[0], vC0[1], vC0[2]);
        AddMotionMemorySize(&g100[4], &g100[5], &g100[6], mem, g100[2], 0, g100[3], 0, 1.0f, 1, 0);
        if (D_0062C230->f_284 != 0) {
            _SetCurrentMatrix(v50, vC0);
        } else {
            short h1 = g100[5];
            short h0 = g100[4];
            t = func_0010ED30(h1);
            v50[0] = func_0010ED30(h0) * t;
            v50[1] = p2o_SetDefaultEnviroment(h0) * t;
            v50[2] = -p2o_SetDefaultEnviroment(h1);
            v50[3] = 0;
        }
        n = func_0010EEF0(_MulCurrentMatrixR(v50, D_00271BF0));
        _MulCurrentMatrixL(v60, v50, D_00271BF0);
        func_0010E088(qD0, n, v60);
        func_0010E148(qA0, qA0, qD0);
        if (D_0062C230->f_280 != 1) {
            if (D_0062C230->f_280 != 2) {
                GetInverseQuaternion(qF0, qb);
                GetCurrentQuaternion(D_0062C230->q_2C0, D_0062C230->q_2C0, D_002724B0, D_006295C4);
                pv = v60;
            } else {
                func_0010E148(qF0, qs, D_0062C230->q_2A0);
                func_0010E148(qF0, qF0, qb);
                GetCurrentQuaternion(D_0062C230->q_2C0, D_0062C230->q_2C0, D_002724B0, D_006295D4);
                pv = v60;
            }
        } else {
            i = 0;
            qn = v130;
            ang = MatrixDrive_GetTurnYEAngleXZ(vC0);
            n = e->next;
            if (n != -1) {
                pv = v60;
loop13:
                {
                    MfMot *o = &D_0062B758_m[n];
                    pv[i++] = D_0062B720 * MatrixDrive_GetTurnYEAngleXZ(o->pos);
                    if (i >= 2) goto done13;
                    n = o->next;
                    if (n != -1) goto loop13;
                }
done13:;
            } else {
                pv = v60;
            }
            v60[1] += D_0062B720 * MatrixDrive_GetTurnYEAngleXZ(
                D_0062B758_m[DebugDisp1CollisionWithColor(D_0062B75C, 0x20)].pos);
            func_00105058();
            getQuaternionFromMatrix(func_00105078(),
                (char *)&D_0062C218[DebugDisp1CollisionWithColor(D_0062B75C, 0x16)] + 0x10);
            func_00105108(5.0f, -3.0f, 0.0f);
            MatrixDrive_TurnObjectMatrix(v110, (char *)func_00105078() + 0x30);
            _ApplyCurrentMatrix(v70, D_0062B758_m[e->next].pos, v110);
            rot = D_0062B720 * MatrixDrive_GetTurnYEAngleXZ(v70);
            v130[0] = rot;
            v130[1] = 0.0f;
            v130[2] = 0.0f;
            v130[3] = 1.0f;
            _TransposeRotationCurrentMatrix(qn, qn, v110);
            _SetCurrentMatrix(qn, qn);
            _MulCurrentMatrixL(v120, qn, D_00271BF0);
            func_0010E088(D_00703030, func_0010EEF0(_MulCurrentMatrixR(D_00271BF0, qn)), v120);
            v60[1] = rot;
            func_00105068();
            if (D_0062C230->f_2B4 == 0) {
                t = v60[0] + v60[1];
                if (t < ang) {
                    ang = t;
                }
            }
            len2 = ang * ang;
            D_0062B728 = func_0010EEF0(
                (len2 + v60[0] * v60[0] - v60[1] * v60[1]) / ((v60[0] + v60[0]) * ang));
            D_0062B72A = func_0010EEF0(
                (len2 + v60[1] * v60[1] - v60[0] * v60[0]) / ((v60[1] + v60[1]) * ang));
            func_0010E448(qA0, g100[6]);
            func_0010E588(qA0, D_0062B728);
            GetInverseQuaternion(qF0, qA0);
            {
                float *pb = D_0062C230->q_290;
                void *t = func_00105078();
                w = v120;
                MatrixDrive_TurnZObjectMatrixXY(w, (char *)t + 0x30, D_0062C230);
                w = v70;
                w2 = v120;
                MatrixDrive_GetTurnXAngleZY(w, pb, w2);
            }
            v70[3] = 0;
            _SetCurrentMatrix(v70, v70);
            _MulCurrentMatrixL(v110, v70, D_00703020);
            if (D_0062C230->f_350 == 2 && v60[0] + v60[1] < ang + 0.0f) {
                func_0010E088(v120, (short)((ang + 0.0f - (v60[0] + v60[1])) * D_006295C8), v110);
                GetCurrentQuaternion(D_0062C230->q_2C0, D_0062C230->q_2C0, v120, D_006295CC);
            } else {
                GetCurrentQuaternion(D_0062C230->q_2C0, D_0062C230->q_2C0, D_002724B0, D_006295D0);
            }
        }
        GetCurrentQuaternion(b->q1, qF0, b->q1, D_0062C230->f_2B0 * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1])));
        if (D_0062C230->f_280 != 0) {
            b->rate = b->rate + (1.0f - b->rate) * (D_0062C230->f_3B0 * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1])));
        } else {
            b->rate = b->rate * (1.0f - D_0062C230->f_3B0 * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1])));
        }
        GetCurrentQuaternion(pv, b->q1, qb, b->rate);
        func_0010E148(qa, qa, pv);
        InvertCurrentQuaternion(qa);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
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
        float *qb;
        func_0010E148(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_002724B0);
        qb = q20;
        func_0010E188(qb, nd->quat, e->quat);
        GetInverseQuaternion(v60, qb);
        if (D_0062C230->f_280 == 1) {
            GetTableArcCos(v60, (short)-(D_0062B728 + D_0062B72A), 0.0f, 0.0f, -1.0f);
            func_0010E148(v60, v60, D_00703030);
        }
        GetCurrentQuaternion(b->q1, v60, b->q1, D_0062C230->f_2B0 * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1])));
        GetCurrentQuaternion(v70, b->q1, qb, D_0062C214);
        func_0010E148(qa, qa, v70);
        InvertCurrentQuaternion(qa);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        return;
    }
    case 0x16:
    {
        void *s0;
        int n;
        float t;
        float *qa;
        float *qb;
        func_0010E148(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_002724B0);
        qb = q20;
        func_0010E188(qb, nd->quat, e->quat);
        if (D_0062C230->f_320 != 0) {
            pv = v60;
            GetInverseQuaternion(v60, D_002724B0);
        } else {
            pv = v60;
            GetInverseQuaternion(v60, qb);
        }
        GetCurrentQuaternion(v70, pv, qb, D_0062C214);
        func_0010E148(qa, qa, v70);
        InvertCurrentQuaternion(qa);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        if (D_0062C234->f_1C0 != 0
            && !((*(unsigned int *)((char *)&D_0055DA10[D_0062C234->f_30] + 0x18C) >> 1) & 1)) {
            n = D_0062C234->f_68;
            if (n != 6) {
                if (n < 7) {
                    if (n != 0) {
                        goto swap_weapon;
                    }
                    goto no_swap;
                }
                if (n != 0xE && n != 0x13) {
swap_weapon:
                    t = CheckSwapableWeapon(D_0062C234->f_1C0) * D_006295DC;
                    t = D_006295E0 < t ? D_006295E0 : t;
                    GetCurrentQuaternion(b->q1, b->q1, GetLastQuaternion(), t);
                    GetInverseQuaternion(GetLastQuaternion(), b->q1);
                    func_0010E1D0(func_00105078(), GetLastQuaternion());
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
            func_0010E148(pa, pc, nd->quat);
        }
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        return;
    }
    case 0x2:
    {
        void *s0;
        float *qa;
        float *qb;
        func_0010E148(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_002724B0);
        qb = q20;
        func_0010E188(qb, nd->quat, e->quat);
        func_0010E148(qa, qa, qb);
        InvertCurrentQuaternion(qa);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        return;
    }
    case 0x3:
    {
        void *s0;
        int q;
        int n;
        int i;
        float t;
        float len2;
        float ang;
        float *qa;
        float *pv;
        float *w;
        float *w2;
        float *qb;
        float *qc;
        func_0010E148(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_002724B0);
        qb = q20;
        func_0010E188(qb, nd->quat, e->quat);
        func_00260568(v110, 0, 0x10);
        qc = v110;
        v110[3] = 1.0f;
        {
            float *pb = D_0062C230->q_230;
            void *t = func_00105078();
            w = v170;
            MatrixDrive_TurnZObjectMatrixXY(w, (char *)t + 0x30, D_0062C230);
            w = v160;
            w2 = v170;
            MatrixDrive_GetTurnXAngleZY(w, pb, w2);
        }
        v160[3] = 0;
        func_00105058();
        MatrixDrive_TransMatrix(func_00105078(), func_00105090());
        {
            void *t = func_00105078();
            w = v120;
            w2 = v160;
            func_0023FDD8(w, t, w2);
        }
        func_00105068();
        MatrixDrive_ScaleMatrix(&g180[0], &g180[1], v120[0], v120[1], v120[2]);
        AddMotionMemorySize(&g180[2], &g180[3], &g180[4], mem, g180[0], 0, g180[1], 0, 1.0f, 1, 0);
        if (D_0062C230->f_224 != 0) {
            _SetCurrentMatrix(v150, v120);
        } else {
            short h1 = g180[3];
            short h0 = g180[2];
            t = func_0010ED30(h1);
            v150[0] = func_0010ED30(h0) * t;
            v150[1] = p2o_SetDefaultEnviroment(h0) * t;
            v150[2] = -p2o_SetDefaultEnviroment(h1);
            v150[3] = 0;
        }
        n = func_0010EEF0(_MulCurrentMatrixR(v150, D_00271BF0));
        _MulCurrentMatrixL(v160, v150, D_00271BF0);
        func_0010E088(v130, n, v160);
        func_0010E148(qc, qc, v130);
        if (D_0062C230->f_220 != 1) {
            if (D_0062C230->f_220 != 2) {
                GetInverseQuaternion(v70, qb);
            } else {
                func_0010E148(v70, qc, D_0062C230->q_240);
                func_0010E148(v70, v70, qb);
            }
            pv = v160;
        } else {
            i = 0;
            ang = MatrixDrive_GetTurnYEAngleXZ(v120);
            n = e->next;
            if (n != -1) {
                len2 = ang * ang;
                pv = v160;
loop3:
                {
                    MfMot *o = &D_0062B758_m[n];
                    pv[i++] = D_0062B720 * MatrixDrive_GetTurnYEAngleXZ(o->pos);
                    if (i >= 2) goto done3;
                    n = o->next;
                    if (n != -1) goto loop3;
                }
done3:;
            } else {
                len2 = ang * ang;
                pv = v160;
            }
            v160[1] += D_0062B720 * MatrixDrive_GetTurnYEAngleXZ(
                D_0062B758_m[DebugDisp1CollisionWithColor(D_0062B75C, 0x10)].pos);
            D_0062B728 = func_0010EEF0(
                (len2 + v160[0] * v160[0] - v160[1] * v160[1]) / ((v160[0] + v160[0]) * ang));
            D_0062B72A = func_0010EEF0(
                (len2 + v160[1] * v160[1] - v160[0] * v160[0]) / ((v160[1] + v160[1]) * ang));
            func_0010E448(qc, g180[4]);
            func_0010E588(qc, D_0062B728);
            GetInverseQuaternion(v70, qc);
        }
        GetCurrentQuaternion(b->q1, v70, b->q1, D_0062C230->f_3B0 * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1])));
        if (D_0062C230->f_220 != 0) {
            b->rate = b->rate + (1.0f - b->rate) * (D_0062C230->f_3B0 * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1])));
        } else {
            b->rate = b->rate * (1.0f - D_0062C230->f_3B0 * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1])));
        }
        GetCurrentQuaternion(pv, b->q1, qb, b->rate);
        func_0010E148(qa, qa, pv);
        InvertCurrentQuaternion(qa);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        D_0062C214 = b->rate;
        return;
    }
    case 0x4:
    {
        void *s0;
        int q;
        float *qa;
        float *qb;
        func_0010E148(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_002724B0);
        qb = q20;
        func_0010E188(qb, nd->quat, e->quat);
        GetInverseQuaternion(v160, qb);
        if (D_0062C230->f_220 == 1) {
            GetTableArcCos(v160, (short)-(D_0062B728 + D_0062B72A), 0.0f, 0.0f, -1.0f);
        }
        GetCurrentQuaternion(b->q1, v160, b->q1, D_0062C230->f_3B0 * (60.0f / (float)((0x3C - D_00271240[0] * 0xA) / D_00271240[1])));
        GetCurrentQuaternion(v170, b->q1, qb, D_0062C214);
        func_0010E148(qa, qa, v170);
        InvertCurrentQuaternion(qa);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        return;
    }
    case 0x6:
    {
        void *s0;
        float *qa;
        float *qb;
        func_0010E148(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_002724B0);
        qb = q20;
        func_0010E188(qb, nd->quat, e->quat);
        if (D_0062C230->f_324 != 0) {
            GetInverseQuaternion(b->q1, D_002724B0);
        } else {
            GetInverseQuaternion(b->q1, qb);
        }
        GetCurrentQuaternion(v160, b->q1, qb, D_0062C214);
        func_0010E148(qa, qa, v160);
        InvertCurrentQuaternion(qa);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        return;
    }
    case 0x5:
    {
        void *s0;
        float *qa;
        float *qb;
        func_0010E148(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_002724B0);
        qb = q20;
        func_0010E188(qb, nd->quat, e->quat);
        if (D_0062C230->f_220 != 0) {
            if (D_0062C230->f_220 != 1) {
                func_0010E148(qa, qa, qb);
            }
        } else {
            func_0010E148(qa, qa, qb);
        }
        InvertCurrentQuaternion(qa);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        return;
    }
    case 0x2D:
    case 0x31:
    {
        void *s0;
        int n;
        int i;
        float len2;
        float ang;
        float *qa;
        float *qb;
        float *pv;
        int endflag;
        float *w170;
        float *w190;
        if (D_0062C230->f_1F4 != 0) {
            endflag = 0;
            i = 0;
            func_0010E148(GetLastQuaternion(), GetTableSin(), e->quat);
            func_0010E1D0(func_00105078(), GetLastQuaternion());
            qa = q30;
            GetInverseQuaternion(qa, D_002724B0);
            qb = q20;
            func_0010E188(qb, nd->quat, e->quat);
            func_00104D20();
            MatrixDrive_TurnObjectMatrix((char *)func_00105078() + 0x30, D_00271BE0);
            func_0010E300(qb);
            func_00104D20();
            n = e->next;
            pv = v160;
            if (n == -1) {
                w170 = v170;
                endflag = 1;
            } else {
                w170 = v170;
                w190 = q190;
loop2D:
                {
                    MfMot *o = &D_0062B758_m[n];
                    func_00240968(w190, o->pos, D_0062B720);
                    func_001050A8(w190);
                    func_0010E300(D_0062C218[n].quat);
                    pv[i++] = D_0062B720 * MatrixDrive_GetTurnYEAngleXZ(o->pos);
                    if (i >= 2) goto done2D;
                    n = o->next;
                    if (n != -1) goto loop2D;
                    endflag = 1;
                }
done2D:;
            }
            MatrixDrive_TurnObjectMatrix(w170, (char *)func_00105078() + 0x30);
            if (e->state == 0x2D) {
                v170[1] += D_0062C230->f_1F8;
            } else if (e->state == 0x31) {
                v170[1] += D_0062C230->f_1FC;
            }
            ang = MatrixDrive_GetTurnYEAngleXZ(w170);
            func_00105068();
            len2 = ang * ang;
            s0 = func_00105078();
            func_0023FED0(s0, s0);
            func_0023FDD8(w170, s0, w170);
            func_0023FE98(w170, w170);
            D_0062B724 = func_0010EE60(v170[1]);
            D_0062B726 = -func_0010EE60(v170[2]);
            D_0062B728 = func_0010EEF0(
                (len2 + v160[0] * v160[0] - v160[1] * v160[1]) / ((v160[0] + v160[0]) * ang));
            D_0062B72A = func_0010EEF0(
                (len2 + v160[1] * v160[1] - v160[0] * v160[0]) / ((v160[1] + v160[1]) * ang));
            func_00105068();
            if (endflag == 0) {
                func_0010E148(qa, qa, qb);
                func_0010E588(qa, (short)D_0062B724);
                func_0010E4E8(qa, (short)D_0062B726);
                func_0010E588(qa, (short)-D_0062B728);
            } else {
                func_0010E148(qa, qa, qb);
            }
            InvertCurrentQuaternion(qa);
            func_0010E1D0(func_00105078(), GetLastQuaternion());
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
            func_0010E148(GetLastQuaternion(), GetTableSin(), e->quat);
            func_0010E1D0(func_00105078(), GetLastQuaternion());
            qa = q30;
            GetInverseQuaternion(qa, D_002724B0);
            func_0010E188(q20, nd->quat, e->quat);
            func_0010E588(qa, (short)(D_0062B728 + D_0062B72A));
            InvertCurrentQuaternion(qa);
            func_0010E1D0(func_00105078(), GetLastQuaternion());
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
            func_0010E148(GetLastQuaternion(), GetTableSin(), e->quat);
            func_0010E1D0(func_00105078(), GetLastQuaternion());
            qa = q30;
            GetInverseQuaternion(qa, D_002724B0);
            qb = q20;
            func_0010E188(qb, nd->quat, e->quat);
            func_0010E588(qa, (short)-D_0062B72A);
            func_0010E4E8(qa, (short)-D_0062B726);
            func_0010E588(qa, (short)-D_0062B724);
            func_0010E148(qa, qa, D_0062C218[e->f_38].quat);
            func_0010E148(qa, qa, qb);
            InvertCurrentQuaternion(qa);
            func_0010E1D0(func_00105078(), GetLastQuaternion());
            return;
        }
sin_tail:
        {
            void *p0;
            p0 = GetLastQuaternion();
            func_0010E148(p0, GetTableSin(), nd->quat);
            p0 = func_00105078();
            func_0010E1D0(p0, GetLastQuaternion());
            return;
        }
    }
    default:
    {
        void *s0;
        func_0010E148(GetLastQuaternion(), GetTableSin(), nd->quat);
        func_0010E1D0(func_00105078(), GetLastQuaternion());
        return;
    }
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", CheckMotionIncludeFacialData);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", func_001D5928);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", func_001D5AF0);

extern char *D_0062B758;
extern char *D_0062C244;
extern float D_0062B720;
extern char D_00703040[];
extern char D_00703080[];
extern void _PushVu0Registers(void *buf, void *p1, float f);
extern void func_0010E250(void *a0, void *a1, void *a2);
extern void getQuaternionFromMatrix(void *a0, void *a1);
extern void *func_00105078(void);
extern void *func_00105090(void);
extern void func_001189F8(void *a0, void *a1, void *a2);

void func_001D5C50(int a0) {
    char *elemA = D_0062B758 + a0 * 0x40;
    char *elemB = D_0062C244 + a0 * 0x20;
    void *x;
    if (*(int *)(elemA + 0x38) != -1) {
        _PushVu0Registers(D_00703080, elemA + 0x10, D_0062B720);
        func_0010E250(D_00703040, elemB + 0x10, D_00703080);
    } else {
        getQuaternionFromMatrix(D_00703040, elemB + 0x10);
    }
    x = func_00105078();
    func_001189F8(x, func_00105090(), D_00703040);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionFileManager", func_001D5D00);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00611A30;  /* stride 0x4 */

/* end struct shapes */
