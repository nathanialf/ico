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

int InitMotionFile(unsigned int *self)
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

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", AddMotionMemorySize);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", GetMotionMemorySize);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", ResetDynamicMotionManager);

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

extern void func_00244448(void *a0, void *a1, float a2);
extern void *func_00105278(void);
extern void *func_00105290(void);
extern void func_00105258(void);
extern void func_00105268(void);
extern void func_001052A8(void *a0);
extern void func_00105308(float x, float y, float z);
extern void func_00104F20(void);
extern void func_00104F48(int a0);
extern void func_002438B8(void *a0, void *a1, void *a2);
extern void func_002439B0(void *a0, void *a1);
extern void func_00243978(void *a0, void *a1);
extern void *GetLastQuaternion(void);
extern void *GetTableSin(void);
extern void func_0010DDB8(void *a0, void *a1, void *a2);
extern void func_0010DDF8(void *a0, void *a1, void *a2);
extern void func_0010DE40(void *a0, void *a1);
extern void func_0010DF70(void *a0);
extern void func_0010E0B8(void *a0, int a1);
extern void func_0010E158(void *a0, int a1);
extern void func_0010E1F8(void *a0, int a1);
extern void func_0010DCF8(void *a0, int a1, void *a2);
extern void GetInverseQuaternion(void *a0, void *a1);
extern void func_002641D8(void *a0, int a1, int a2);
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
extern float func_0010E9A0(short a0);
extern float p2o_SetDefaultEnviroment(short a0);
extern int func_0010EAD0(float x);
extern int func_0010EB60(float x);
extern void func_00118648(void *a0, void *a1, void *a2);
extern void GetTableArcCos(void *self, int a1, float x, float y, float z);
extern float CheckSwapableWeapon(void *a0);
extern int DebugDisp1CollisionWithColor(void *a0, int a1);
extern void getQuaternionFromMatrix(void *a0, void *a1);

#define MFM_FRAME_SCALE_N(num) \
    ((num) / (float)((0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1]))
#define MFM_FRAME_SCALE MFM_FRAME_SCALE_N(60.0f)

#define MFM_SEL_ROT(dst, k)                                     \
    selrot = D_00632D18;                                        \
    if (selrot != 0) {                                          \
        rotk = (k);                                             \
        dst = (float)D_00632D60 * rotk;                         \
    } else {                                                    \
        dst = *(float *)(D_00633F54 + 0x158);                   \
    }

#define MFM_RATE_UP(rate, k, num)                                \
    {                                                           \
        (rate) = (rate) + (one - (rate)) * (D_00633F3C->f_3BC * MFM_FRAME_SCALE_N(num) \
            + (one - D_00633F3C->f_3BC * MFM_FRAME_SCALE_N(num)) * MFM_ROT(k)); \
    }

#define MFM_ROT(k) \
    (D_00632D18 != 0 ? (float)D_00632D60 * (k) : *(float *)(D_00633F54 + 0x158))
#define MFM_RATE_DOWN_N(rate, k, num)                          \
    {                                                           \
        (rate) = (rate) * (one - (D_00633F3C->f_3BC * MFM_FRAME_SCALE_N(num) \
            + (one - D_00633F3C->f_3BC * MFM_FRAME_SCALE_N(num)) * MFM_ROT(k))); \
    }

/* Take the world-space vector from this bone to the target point PB.
   WORLD receives the bone's own world position, DELTA the world vector
   from it to PB, with its w component cleared. */
static __inline__ void aimWorldDelta(float *world, float *delta, float *pb)
{
    void *t = func_00105278();
    MatrixDrive_TurnZObjectMatrixXY(world, (char *)t + 0x30, D_00633F3C);
    MatrixDrive_GetTurnXAngleZY(delta, pb, world);
    delta[3] = 0;
}

/* Turn-path sibling of aimWorldDelta: the aim target is read inside the
   helper rather than passed in by the caller. */
static __inline__ void aimWorldDeltaAim(float *world, float *delta)
{
    void *t = func_00105278();
    float *pq = D_00633F3C->q_2A0;
    MatrixDrive_TurnZObjectMatrixXY(world, (char *)t + 0x30, D_00633F3C);
    MatrixDrive_GetTurnXAngleZY(delta, pq, world);
    delta[3] = 0;
}

/* Bring the aim direction into the parent bone's frame and record the
   resulting turn angles in the motion memory.  LOCAL is the bone's local
   direction buffer; DELTA is the world vector from the bone to the target;
   OUT is the bone's five-short motion-memory block; MEM is the motion
   buffer. */
static __inline__ void aimLocalToMemory(float *local, float *delta,
                                        short *out, void *mem)
{
    func_00105258();
    MatrixDrive_TransMatrix(func_00105278(), func_00105290());
    {
        void *t = func_00105278();
        func_002438B8(local, t, delta);
    }
    func_00105268();
    MatrixDrive_ScaleMatrix(&out[0], &out[1], local[0], local[1], local[2]);
    AddMotionMemorySize(&out[2], &out[3], &out[4], mem,
                        out[0], 0, out[1], 0, 1.0f, 1, 0);
}

/* Aim the bone, turn the current matrix by the result, and carry that turn
   into the next matrix.  DIR receives the aim direction -- read straight out
   of the live matrix while the aim is being driven, otherwise rebuilt from the
   pair of turn angles ANG that was just recorded into the motion memory; the
   rotation the current matrix picks up from it is applied to NEXT and also
   returned.  V is the bone's local direction buffer. */
static __inline__ int aimDirectionRotApply(float *dir, float *next, float *v,
                                           short *ang, int drive)
{
    int nq;

    if (drive != 0) {
        _SetCurrentMatrix(dir, v);
    } else {
        short h1 = ang[1];
        short h0 = ang[0];
        float t = func_0010E9A0(h1);
        dir[0] = func_0010E9A0(h0) * t;
        dir[1] = p2o_SetDefaultEnviroment(h0) * t;
        dir[2] = -p2o_SetDefaultEnviroment(h1);
        dir[3] = 0;
    }
    nq = func_0010EB60(_MulCurrentMatrixR(dir, D_00275870));
    _MulCurrentMatrixL(next, dir, D_00275870);
    return nq;
}

/* Aim the bone, then turn the resulting aim angle into a quaternion about the
   bone axis in OUT.  Returns the rotation index, as aimDirectionRotApply does. */
static __inline__ int aimRotApply(float *dir, float *next, float *v, short *ang,
                                  int drive, float *out)
{
    int nq = aimDirectionRotApply(dir, next, v, ang, drive);
    func_0010DCF8(out, nq, next);
    return nq;
}

/* Factored per the file's aim* helper idiom (three banked siblings).  Formals
   are passed straight to the callees; the 11-arg AddMotionMemorySize tail is
   what makes the helper inlinable (sibcall door).  ROM's arm-0x23 codegen
   (hard-dest arg materialisations, no cross-arm carrier) requires the inline
   producer -- see the R400-E walk in the session ledger. */
static __inline__ void aimPushTurn(float *v50, float *v60, float *v70, short *g80, void *mem)
{
    void *p;
            {
                void *q;
                {
                    float *pb = D_00633F3C->q_2F0;
                    void *t = func_00105278();
                    MatrixDrive_TurnZObjectMatrixXY(v70, (char *)t + 0x30, D_00633F3C);
                    MatrixDrive_GetTurnXAngleZY(v60, pb, v70);
                }
                v60[3] = 0;
                func_00105258();
                MatrixDrive_TransMatrix(func_00105278(), func_00105290());
                {
                    void *t = func_00105278();
                    func_002438B8(v50, t, v60);
                }
                func_00105268();
                p = &g80[0];
                q = &g80[1];
                MatrixDrive_PushMatrixWithNoCopy(p, q, v50[0], v50[1], v50[2]);
            }
            AddMotionMemorySize(&g80[2], &g80[3], &g80[4], mem, g80[0], 0, (short)-(unsigned short)g80[1], 0, 1.0f, 0, 1);
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
    float m[3][4];              /* sp 0x150 */
    short g180[5];              /* sp 0x180 */
    float q190[4];              /* sp 0x190 */
    void *mem;                  /* sp 0x1A0 */
    MfMot *e;
    MfBlend *b;
    MfOri *nd;
    void *s0;
    float *qc;
    float *qp;
    float *q2p;
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
        func_00244448(buf10, e->pos, D_00633440);
        s0 = (char *)func_00105278() + 0x30;
        func_002438B8(s0, func_00105290(), buf10);
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
        func_0010DDB8(GetLastQuaternion(), GetTableSin(), nd->quat);
        {
            void *pa = GetLastQuaternion();
            float *pb = D_004C5B40;
            void *pc;
            pc = GetLastQuaternion();
            func_0010DDB8(pa, pb, pc);
        }
        func_0010DE40(func_00105278(), GetLastQuaternion());
        return;
    }
    case 0x2C:
    {
        void *s0;
        func_0010DDB8(GetLastQuaternion(), GetTableSin(), nd->quat);
        func_0010DDF8(GetLastQuaternion(), GetLastQuaternion(), D_004C5B30);
        func_0010DE40(func_00105278(), GetLastQuaternion());
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
        func_0010DDB8(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010DE40(func_00105278(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_00276140);
        qb = q20;
        func_0010DDF8(qb, nd->quat, e->quat);
        if (D_00633F3C->f_318 != 0 && D_00633F3C->f_2E0 != 0) {
            float one = 1.0f;
            MFM_RATE_UP(b->rate, D_006312B4, 60.0f);
        } else {
            float one = 1.0f;
            MFM_RATE_DOWN_N(b->rate, D_006312B8, 60.0f);
        }
        func_002641D8(v50, 0, 0x10);
        v50[3] = 1.0f;
        if (D_00633F44 == 2) {
            func_0010E1F8(v50, 0x71C);
        }
        GetCurrentQuaternion(q40, v50, qb, b->rate);
        func_0010DDB8(qa, qa, q40);
        InvertCurrentQuaternion(qa);
        func_0010DE40(func_00105278(), GetLastQuaternion());
        RegularizeQuaternion(q40, D_00633F3C->q_2D0);
        {
            void *pa = GetLastQuaternion();
            void *pc = GetLastQuaternion();
            func_0010DDB8(pa, q40, pc);
        }
        func_0010DE40(func_00105278(), GetLastQuaternion());
        return;
    }
    case 0x23:
    {
        void *s0;
        int q;
        float *qb;
        float *w;
        void *p;
        func_0010DDB8(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010DE40(func_00105278(), GetLastQuaternion());
        GetInverseQuaternion(q30, D_00276140);
        qb = q20;
        func_0010DDF8(qb, nd->quat, e->quat);
        func_0010E1F8(GetLastQuaternion(), D_00633F3C->f_304);
        func_0010DE40(func_00105278(), GetLastQuaternion());
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
            if (D_00633F44 == 4) {
                func_00104F48(-0x8000);
            }
        aimPushTurn(v50, v60, v70, g80, mem);
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
                float *q1 = b->q1;
                float *q3 = b->q3;
                float *q2 = b->q2;
                w = v60;
                GetMatrixFromQuaternion(w);
                func_0010E0B8(w, (short)-(unsigned short)g80[2]);
                func_0010E1F8(w, (short)-(unsigned short)g80[3]);
                func_0010E158(w, (short)-(unsigned short)g80[4]);
                ResetDynamicMotionManager(q1, mem, q3, w, D_006312C0);
                p = v70;
                func_0010DDB8(p, GetLastQuaternion(), w);
                w = q90;
                func_0010DDF8(w, p, q1);
                GetCurrentQuaternion(qA0, w, D_00276140, D_00633F3C->f_3C4);
                GetCurrentQuaternion(q2, qA0, q2, D_00633F3C->f_3C8);
                func_0010DDB8(q1, q1, q2);
                GetSlerpQuaternionNoRegularize(q1);
                func_0010DDF8(q3, q1, GetLastQuaternion());
            }
        }
        {
            s0 = GetLastQuaternion();
            func_0010E0B8(s0, (short)(int)((float)-D_00633F3C->f_50 * 2.5f));
            s0 = GetLastQuaternion();
            func_0010DDB8(q90, s0, qb);
            GetCurrentQuaternion(GetLastQuaternion(), b->q1, q90, b->rate);
            {
                void *pa = GetLastQuaternion();
                float *tbl = D_004C5B50;
                void *pc = GetLastQuaternion();
                func_0010DDB8(pa, tbl, pc);
            }
        }
        func_0010DE40(func_00105278(), GetLastQuaternion());
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
        float wgt;
        float *w;
        float *qb;

        float *pC0;
        func_0010DDB8(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010DE40(func_00105278(), GetLastQuaternion());
        GetInverseQuaternion(q30, D_00276140);
        qb = q20;
        func_0010DDF8(qb, nd->quat, e->quat);
        func_0010DDB8(GetLastQuaternion(), GetLastQuaternion(), qb);
        func_0010DE40(func_00105278(), GetLastQuaternion());
        if (D_00633F3C->f_31C != 0
            && ((D_00633F3C->f_318 != 0 && D_00633F3C->f_2E0 != 0)
                || D_00633F3C->f_230 != 0 || D_00633F3C->f_290 != 0)) {
            float one = 1.0f;
            MFM_RATE_UP(b->rate, D_006312C4, 60.0f);
        } else {
            float one = 1.0f;
            MFM_RATE_DOWN_N(b->rate, D_006312C8, 60.0f);
        }
        wgt = 1.0f;
        if (b->rate < D_006312CC) {
            GetInverseQuaternion(b->q1, GetLastQuaternion());
            GetMatrixFromQuaternion(b->q3);
            GetInverseQuaternion(b->q2, b->q3);
        } else {
            float *q1 = b->q1;
            float *q3 = b->q3;
            float *w2;
            float *qc;
            float *q2c;
            float *qt;
            float *qf;
            float *wd;
            GetMotionMemorySize(b->q1, mem, q3);
            n = D_00633F3C->f_31C;
            sumA = 0;
            hold = 0;
            cnt = 0;
            if (n == 1) {
                if (D_00633F3C->f_290 != 0) {
                    float *pb = D_00633F3C->q_2A0;
                    cnt = 1;
                    s0 = func_00105278();
                    w = v60;
                    MatrixDrive_TurnZObjectMatrixXY(w, (char *)s0 + 0x30, D_00633F3C);
                    w = v50;
                    MatrixDrive_GetTurnXAngleZY(w, pb, v60);
                    v50[3] = 0;
                    func_00105258();
                    MatrixDrive_TransMatrix(func_00105278(), func_00105290());
                    {
                        void *t = func_00105278();
                        w = qA0;
                        func_002438B8(w, t, v50);
                    }
                    func_00105268();
                    MatrixDrive_TransMatrixV(&gB0[0], &gB0[1], qA0[0], qA0[1], qA0[2]);
                    sumA = gB0[0];
                }
                if (D_00633F3C->f_31C == n && D_00633F3C->f_230 != 0) {
                    float *pb = D_00633F3C->q_240;
                    void *t;
                    cnt += 1;
                    t = func_00105278();
                    w = v70;
                    MatrixDrive_TurnZObjectMatrixXY(w, (char *)t + 0x30, D_00633F3C);
                    w = v60;
                    w2 = v70;
                    MatrixDrive_GetTurnXAngleZY(w, pb, w2);
                    v60[3] = 0;
                    func_00105258();
                    MatrixDrive_TransMatrix(func_00105278(), func_00105290());
                    t = func_00105278();
                    w = v50;
                    func_002438B8(w, t, v60);
                    func_00105268();
                    MatrixDrive_GetMatrix(&gB0[2], &gB0[3], v50[0], v50[1], v50[2]);
                    sumA -= gB0[2];
                }
            }
            sumB = sumA;
            if (D_00633F3C->f_318 != 0 && D_00633F3C->f_2E0 != 0) {
                float *pb = D_00633F3C->q_2F0;
                void *t;
                t = func_00105278();
                w = qD0;
                MatrixDrive_TurnZObjectMatrixXY(w, (char *)t + 0x30, D_00633F3C);
                w = vC0;
                qc = qD0;
                MatrixDrive_GetTurnXAngleZY(w, pb, qc);
                vC0[3] = 0;
                func_00105258();
                MatrixDrive_TransMatrix(func_00105278(), func_00105290());
                t = func_00105278();
                w = v60;
                pC0 = vC0;
                func_002438B8(w, t, pC0);
                func_00105268();
                MatrixDrive_PushMatrixWithNoCopy(&gE0[0], &gE0[1], v60[0], v60[1], v60[2]);
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
            AddMotionMemorySize(&gE0[2], &gE0[3], &gE0[4], mem, (short)sumA, b->f_4,
                                (short)-hold, (short)-b->f_8, wgt, 0, 0);
            q2c = b->q2;
            /* These three assignments are dead as written.  They are not an
               accident and not a tidy-up target: the 2001 source provably
               contained them.  Each is the first mention of one frame
               address in this block, which is what leaves the real
               assignment further down as the second mention -- the only
               form that reproduces the instructions the shipped code
               actually has.  Kept under the scoped exception recorded as
               RULING-VESTIGIAL-EXCEPTION; see the legitimate list in
               CLAUDE.md before touching them. */
            w = vC0;
            w = v70;
            w = qD0;
            AddMotionMemorySize(&gE0[5], &gE0[6], &gE0[7], mem, (short)sumB, b->f_4,
                                (short)-hold, (short)-b->f_8, wgt, 0, 0);
            {
                int h6 = -gE0[6];
                gE0[6] = h6;
            }
            w = v70;
            GetMatrixFromQuaternion(w);
            func_0010E0B8(w, (short)-(unsigned short)gE0[2]);
            func_0010E1F8(w, (short)-(unsigned short)gE0[6]);
            func_0010E158(w, (short)-(unsigned short)gE0[4]);
            qt = vC0;
            func_0010DDB8(qt, GetLastQuaternion(), w);
            wd = qD0;
            func_0010DDF8(wd, qt, q1);
            qf = qF0;
            GetCurrentQuaternion(qf, wd, D_00276140, D_00633F3C->f_3C4);
            GetCurrentQuaternion(q2c, qf, q2c, D_00633F3C->f_3C8);
            func_0010DDB8(q1, q1, q2c);
            GetSlerpQuaternionNoRegularize(q1);
            func_0010DDF8(q3, q1, GetLastQuaternion());
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
            func_0010DDB8(pa, pc, GetLastQuaternion());
        }
        func_0010DE40(func_00105278(), GetLastQuaternion());
        func_00118648(D_00709750, func_00105278(), D_00275870);
        return;
    }
    case 0x12:
    {
        void *s0;
        float *qa;
        float *qb;
        func_0010DDB8(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010DE40(func_00105278(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_00276140);
        qb = q20;
        func_0010DDF8(qb, nd->quat, e->quat);
        func_0010DDB8(qa, qa, qb);
        InvertCurrentQuaternion(qa);
        func_0010DE40(func_00105278(), GetLastQuaternion());
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
        float *p70;
        float *pv;
        float *pv60;
        float *pC0;
        int fl;
        func_0010DDB8(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010DE40(func_00105278(), GetLastQuaternion());
        qp = q30;
        GetInverseQuaternion(qp, D_00276140);
        q2p = q20;
        func_0010DDF8(q2p, nd->quat, e->quat);
        func_002641D8(qA0, 0, 0x10);
        qA0[3] = 1.0f;
        aimWorldDelta(v70, v60, D_00633F3C->q_2A0);
        aimLocalToMemory(vC0, v60, &g100[2], mem);
        pv60 = v60;
        nq = aimDirectionRotApply(v50, v60, vC0, &g100[4], D_00633F3C->f_294);
        p70 = v50;
        qc = p70;
        p70 = qD0;
        pv = pv60;
        func_0010DCF8(p70, nq, pv);
        p70 = qA0;
        pv = qD0;
        func_0010DDB8(p70, p70, pv);
        if (D_00633F3C->f_290 == 1) goto L13turn;
        if (D_00633F3C->f_290 == 2) goto L13mul;
        GetInverseQuaternion(qF0, q2p);
        GetCurrentQuaternion(D_00633F3C->q_2D0, D_00633F3C->q_2D0, D_00276140, D_006312D0);
        goto L13done;
      L13turn:
        {
            ang = MatrixDrive_GetTurnYEAngleXZ(pv60 + 24);
            i = 0;
            n = e->next;
            if (n == -1) goto none13;
            do {
                MfMot *o = &D_00633478[n];
                {
                    float tv = D_00633440 * MatrixDrive_GetTurnYEAngleXZ(o->pos);
                    float *wv = qc + 4;
                    float *d = wv + i;
                    i++;
                    *d = tv;
                }
                if (i >= 2) break;
                n = o->next;
none13:;
            } while (n != -1);
            v60[1] += D_00633440 * MatrixDrive_GetTurnYEAngleXZ(
                D_00633478[DebugDisp1CollisionWithColor(D_0063347C, 0x20)].pos);
            func_00105258();
            {
                int k = DebugDisp1CollisionWithColor(D_0063347C, 0x16);
                getQuaternionFromMatrix(func_00105278(), (char *)&D_00633F24[k] + 0x10);
            }
            func_00105308(5.0f, -3.0f, 0.0f);
            MatrixDrive_TurnObjectMatrix(v110, (char *)func_00105278() + 0x30);
            p70 = v70;
            _ApplyCurrentMatrix(p70, D_00633478[e->next].pos, v110);
            rot = D_00633440 * MatrixDrive_GetTurnYEAngleXZ(p70);
            v130[0] = rot;
            v130[1] = 0.0f;
            v130[2] = 0.0f;
            v130[3] = 1.0f;
            _TransposeRotationCurrentMatrix(v130, v130, v110);
            _SetCurrentMatrix(v130, v130);
            pC0 = v120;
            _MulCurrentMatrixL(pC0, v130, D_00275870);
            {
                int k = func_0010EB60(_MulCurrentMatrixR(D_00275870, v130));
                func_0010DCF8(D_00709760, k, pC0);
            }
            pC0 = v110;
            pv60[1] = rot;
            func_00105268();
            if (D_00633F3C->f_2C4 == 0) {
                float t = v60[0] + v60[1];
                if (t < ang) {
                    ang = t;
                }
            }
            len2 = ang * ang;
            D_00633448 = func_0010EB60(
                (len2 + v60[0] * v60[0] - v60[1] * v60[1]) / ((v60[0] + v60[0]) * ang));
            D_0063344A = func_0010EB60(
                (len2 + v60[1] * v60[1] - v60[0] * v60[0]) / ((v60[1] + v60[1]) * ang));
            func_0010E0B8(qA0, g100[6]);
            func_0010E1F8(qA0, (short)D_00633448);
            GetInverseQuaternion(qF0, qA0);
            aimWorldDeltaAim(v120, v70);
            _SetCurrentMatrix(p70, p70);
            _MulCurrentMatrixL(pC0, p70, D_00709750);
            if (D_00633F3C->f_360 == 2 && ang + 0.0f > v60[0] + v60[1]) {
                func_0010DCF8(v120, (short)((ang + 0.0f - (v60[0] + v60[1])) * D_006312D4), pC0);
                GetCurrentQuaternion(D_00633F3C->q_2D0, D_00633F3C->q_2D0, v120, D_006312D8);
            } else {
                GetCurrentQuaternion(D_00633F3C->q_2D0, D_00633F3C->q_2D0, D_00276140, D_006312DC);
            }
        }
        goto L13done;
      L13mul:
        func_0010DDB8(qF0, qA0, D_00633F3C->q_2B0);
        func_0010DDB8(qF0, qF0, q2p);
        GetCurrentQuaternion(D_00633F3C->q_2D0, D_00633F3C->q_2D0, D_00276140, D_006312E0);
      L13done:
        GetCurrentQuaternion(b->q1, qF0, b->q1, D_00633F3C->f_2C0 * MFM_FRAME_SCALE);
        if (D_00633F3C->f_290 != 0) {
            b->rate += (1.0f - b->rate) * (D_00633F3C->f_3C0 * MFM_FRAME_SCALE);
        } else {
            b->rate *= 1.0f - D_00633F3C->f_3C0 * MFM_FRAME_SCALE;
        }
        GetCurrentQuaternion(qc + 4, b->q1, q2p, b->rate);
        func_0010DDB8(qp, qp, qc + 4);
        InvertCurrentQuaternion(qp);
        func_0010DE40(func_00105278(), GetLastQuaternion());
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
        func_0010DDB8(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010DE40(func_00105278(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_00276140);
        func_0010DDF8(q20, nd->quat, e->quat);
        GetInverseQuaternion(v60, q20);
        if (D_00633F3C->f_290 == 1) {
            GetTableArcCos(v60, (short)-(D_00633448 + D_0063344A), 0.0f, 0.0f, -1.0f);
            func_0010DDB8(v60, v60, D_00709760);
        }
        GetCurrentQuaternion(b->q1, v60, b->q1, D_00633F3C->f_2C0 * MFM_FRAME_SCALE);
        GetCurrentQuaternion(v70, b->q1, q20, D_00633F20);
        func_0010DDB8(qa, qa, v70);
        InvertCurrentQuaternion(qa);
        func_0010DE40(func_00105278(), GetLastQuaternion());
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
        func_0010DDB8(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010DE40(func_00105278(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_00276140);
        qb = q20;
        func_0010DDF8(qb, nd->quat, e->quat);
        if (D_00633F3C->f_330 != 0) {
            GetInverseQuaternion(v60, D_00276140);
        } else {
            GetInverseQuaternion(v60, qb);
        }
        GetCurrentQuaternion(v70, v60, qb, D_00633F20);
        func_0010DDB8(qa, qa, v70);
        InvertCurrentQuaternion(qa);
        func_0010DE40(func_00105278(), GetLastQuaternion());
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
                    func_0010DE40(func_00105278(), GetLastQuaternion());
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
            func_0010DDB8(pa, pc, nd->quat);
        }
        func_0010DE40(func_00105278(), GetLastQuaternion());
        return;
    }
    case 0x2:
    {
        void *s0;
        float *qa;
        float *qb;
        func_0010DDB8(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010DE40(func_00105278(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_00276140);
        qb = q20;
        func_0010DDF8(qb, nd->quat, e->quat);
        func_0010DDB8(qa, qa, qb);
        InvertCurrentQuaternion(qa);
        func_0010DE40(func_00105278(), GetLastQuaternion());
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
        float *qc;
        float *qb;
        func_0010DDB8(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010DE40(func_00105278(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_00276140);
        qb = q20;
        func_0010DDF8(qb, nd->quat, e->quat);
        func_002641D8(v110, 0, 0x10);
        v110[3] = 1.0f;
        aimWorldDelta(m[2], m[1], D_00633F3C->q_240);
        aimLocalToMemory(v120, m[1], &g180[0], mem);
        aimRotApply(m[0], m[1], v120, &g180[2], D_00633F3C->f_234, v130);
        func_0010DDB8(v110, v110, v130);
        if (D_00633F3C->f_230 == 1) goto L3turn;
        qc = v70;
        if (D_00633F3C->f_230 == 2) goto L3mul;
        GetInverseQuaternion(qc, qb);
        goto L3done;
      L3turn:
        {
            ang = MatrixDrive_GetTurnYEAngleXZ(v120);
            i = 0;
            n = e->next;
            if (n == -1) goto none3;
            do {
                MfMot *o = &D_00633478[n];
                {
                    float tv = D_00633440 * MatrixDrive_GetTurnYEAngleXZ(o->pos);
                    float *d = m[1];
                    d += i;
                    i++;
                    *d = tv;
                }
                if (i >= 2) break;
                n = o->next;
none3:;
            } while (n != -1);
            m[1][1] += D_00633440 * MatrixDrive_GetTurnYEAngleXZ(
                D_00633478[DebugDisp1CollisionWithColor(D_0063347C, 0x10)].pos);
            len2 = ang * ang;
            D_00633448 = func_0010EB60(
                (len2 + m[1][0] * m[1][0] - m[1][1] * m[1][1]) / ((m[1][0] + m[1][0]) * ang));
            D_0063344A = func_0010EB60(
                (len2 + m[1][1] * m[1][1] - m[1][0] * m[1][0]) / ((m[1][1] + m[1][1]) * ang));
            func_0010E0B8(v110, g180[4]);
            func_0010E1F8(v110, (short)D_00633448);
            GetInverseQuaternion(v70, v110);
        }
        goto L3done;
      L3mul:
        func_0010DDB8(qc, v110, D_00633F3C->q_250);
        func_0010DDB8(qc, qc, qb);
      L3done:
        GetCurrentQuaternion(b->q1, v70, b->q1, D_00633F3C->f_3C0 * MFM_FRAME_SCALE);
        if (D_00633F3C->f_230 != 0) {
            b->rate = b->rate + (1.0f - b->rate) * (D_00633F3C->f_3C0 * MFM_FRAME_SCALE);
        } else {
            b->rate = b->rate * (1.0f - D_00633F3C->f_3C0 * MFM_FRAME_SCALE);
        }
        GetCurrentQuaternion(m[1], b->q1, qb, b->rate);
        func_0010DDB8(qa, qa, m[1]);
        InvertCurrentQuaternion(qa);
        func_0010DE40(func_00105278(), GetLastQuaternion());
        D_00633F20 = b->rate;
        return;
    }
    case 0x4:
    {
        void *s0;
        int q;
        float *qa;
        float *qb;
        func_0010DDB8(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010DE40(func_00105278(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_00276140);
        qb = q20;
        func_0010DDF8(qb, nd->quat, e->quat);
        GetInverseQuaternion(m[1], qb);
        if (D_00633F3C->f_230 == 1) {
            GetTableArcCos(m[1], (short)-(D_00633448 + D_0063344A), 0.0f, 0.0f, -1.0f);
        }
        GetCurrentQuaternion(b->q1, m[1], b->q1, D_00633F3C->f_3C0 * MFM_FRAME_SCALE);
        GetCurrentQuaternion(m[2], b->q1, qb, D_00633F20);
        func_0010DDB8(qa, qa, m[2]);
        InvertCurrentQuaternion(qa);
        func_0010DE40(func_00105278(), GetLastQuaternion());
        return;
    }
    case 0x6:
    {
        void *s0;
        float *qa;
        float *qb;
        func_0010DDB8(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010DE40(func_00105278(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_00276140);
        qb = q20;
        func_0010DDF8(qb, nd->quat, e->quat);
        if (D_00633F3C->f_334 != 0) {
            GetInverseQuaternion(b->q1, D_00276140);
        } else {
            GetInverseQuaternion(b->q1, qb);
        }
        GetCurrentQuaternion(m[1], b->q1, qb, D_00633F20);
        func_0010DDB8(qa, qa, m[1]);
        InvertCurrentQuaternion(qa);
        func_0010DE40(func_00105278(), GetLastQuaternion());
        return;
    }
    case 0x5:
    {
        void *s0;
        float *qa;
        float *qb;
        func_0010DDB8(GetLastQuaternion(), GetTableSin(), e->quat);
        func_0010DE40(func_00105278(), GetLastQuaternion());
        qa = q30;
        GetInverseQuaternion(qa, D_00276140);
        qb = q20;
        func_0010DDF8(qb, nd->quat, e->quat);
        if (D_00633F3C->f_230 != 0) {
            if (D_00633F3C->f_230 != 1) {
                func_0010DDB8(qa, qa, qb);
            }
        } else {
            func_0010DDB8(qa, qa, qb);
        }
        InvertCurrentQuaternion(qa);
        func_0010DE40(func_00105278(), GetLastQuaternion());
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
        if (D_00633F3C->f_204 != 0) {
            endflag = 0;
            i = 0;
        func_0010DDB8(GetLastQuaternion(), GetTableSin(), e->quat);
            func_0010DE40(func_00105278(), GetLastQuaternion());
            qa = q30;
            GetInverseQuaternion(qa, D_00276140);
            qb = q20;
            func_0010DDF8(qb, nd->quat, e->quat);
            func_00104F20();
            MatrixDrive_TurnObjectMatrix((char *)func_00105278() + 0x30, D_00275860);
            func_0010DF70(qb);
            func_00104F20();
            n = e->next;
            if (n != -1) {
                goto body2D;
            }
            endflag = 1;
            goto done2D;
            do {
body2D:;
                {
                MfMot *o = &D_00633478[n];
                func_00244448(q190, o->pos, D_00633440);
                func_001052A8(q190);
                func_0010DF70(D_00633F24[n].quat);
                m[1][i++] = D_00633440 * MatrixDrive_GetTurnYEAngleXZ(o->pos);
                if (i >= 2) goto done2D;
                n = o->next;
                }
            } while (n != -1);
            endflag = 1;
done2D:;
            MatrixDrive_TurnObjectMatrix(m[2], (char *)func_00105278() + 0x30);
            if (e->state == 0x2D) goto add1F8;
            if (e->state == 0x31) goto add1FC;
            goto addend;
add1F8:
            m[2][1] += D_00633F3C->f_208;
            goto addend;
add1FC:
            m[2][1] += D_00633F3C->f_20C;
addend:;
            ang = MatrixDrive_GetTurnYEAngleXZ(m[2]);
            func_00105268();
            len2 = ang * ang;
            s0 = func_00105278();
            func_002439B0(s0, s0);
            func_002438B8(m[2], s0, m[2]);
            func_00243978(m[2], m[2]);
            D_00633444 = func_0010EAD0(m[2][1]);
            D_00633446 = -func_0010EAD0(m[2][2]);
            D_00633448 = func_0010EB60(
                (len2 + m[1][0] * m[1][0] - m[1][1] * m[1][1]) / ((m[1][0] + m[1][0]) * ang));
            D_0063344A = func_0010EB60(
                (len2 + m[1][1] * m[1][1] - m[1][0] * m[1][0]) / ((m[1][1] + m[1][1]) * ang));
            func_00105268();
            if (endflag == 0) {
                func_0010DDB8(qa, qa, qb);
                func_0010E1F8(qa, (short)D_00633444);
                func_0010E158(qa, (short)D_00633446);
                func_0010E1F8(qa, (short)-D_00633448);
            } else {
                func_0010DDB8(qa, qa, qb);
            }
            InvertCurrentQuaternion(qa);
            func_0010DE40(func_00105278(), GetLastQuaternion());
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
        func_0010DDB8(GetLastQuaternion(), GetTableSin(), e->quat);
            func_0010DE40(func_00105278(), GetLastQuaternion());
            qa = q30;
            GetInverseQuaternion(qa, D_00276140);
            func_0010DDF8(q20, nd->quat, e->quat);
            func_0010E1F8(qa, (short)(D_00633448 + D_0063344A));
            InvertCurrentQuaternion(qa);
            func_0010DE40(func_00105278(), GetLastQuaternion());
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
        func_0010DDB8(GetLastQuaternion(), GetTableSin(), e->quat);
            func_0010DE40(func_00105278(), GetLastQuaternion());
            qa = q30;
            GetInverseQuaternion(qa, D_00276140);
            qb = q20;
            func_0010DDF8(qb, nd->quat, e->quat);
            func_0010E1F8(qa, (short)-D_0063344A);
            func_0010E158(qa, (short)-D_00633446);
            func_0010E1F8(qa, (short)-D_00633444);
            func_0010DDB8(qa, qa, D_00633F24[e->f_38].quat);
            func_0010DDB8(qa, qa, qb);
            InvertCurrentQuaternion(qa);
            func_0010DE40(func_00105278(), GetLastQuaternion());
            return;
        }
sin_tail:
        {
            void *p0;
            p0 = GetLastQuaternion();
            func_0010DDB8(p0, GetTableSin(), nd->quat);
            p0 = func_00105278();
            func_0010DE40(p0, GetLastQuaternion());
            return;
        }
    }
    default:
    {
        void *p0;
        p0 = GetLastQuaternion();
        func_0010DDB8(p0, GetTableSin(), nd->quat);
        p0 = func_00105278();
        func_0010DE40(p0, GetLastQuaternion());
        return;
    }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", CheckMotionIncludeFacialData);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", func_001D8590);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", func_001D8758);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", func_001D88B8);

INCLUDE_ASM("asm/nonmatchings/src/motionFileManager", func_001D8968);

