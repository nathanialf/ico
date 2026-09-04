#include "common.h"
#include "ico/types.h"
#include "vu0.h"

extern void GetMatrixFromQuaternionPos(void *a0, void *a1, void *a2);
extern void func_0023FE08(char *dst, char *src, int m);
extern void sceVu0ApplyMatrix(int *buf, char *p, int x);
extern void sceVu0Normalize(char *a0, char *a1);
extern char D_00271C10[];

void InitKeyInput(char *a0, char *a1)
{
    char buf[0x40];
    char *sub = *(char **)(a1 + 0x15C);
    char *p = sub + 0xA0;
    GetMatrixFromQuaternionPos(buf, sub + 0xD0, p);
    {
        char *q = *(char **)sub;
        if (q != 0) {
            func_0023FE08(buf, (char *)(*(int *)(*(char **)(q + 0x15C) + 0xC) + (*(int *)(sub + 4) << 6)), (int)buf);
        }
    }
    *(float *)(buf + 0x34) = *(float *)(buf + 0x34) + *(float *)(p + 0xB0);
    sceVu0ApplyMatrix((int *)a0, buf, (int)D_00271C10);
    *(int *)(a0 + 4) = 0;
    sceVu0Normalize(a0, a0);
}

/* NEAR-MISS (rc7, W3 convergence). LOGIC + STRUCTURE fully recovered; residual is
 * a coupled FP-register coloring + reorg delay-slot fill. Dev shape (3-elem clamp):
 *   extern float D_00628C04, D_00628C08;
 *   int LimitExistGeometry(float *a0, int *a1) {
 *       float mn = D_00628C04;                    // scpTriggerPosBox min: aliases *a0 store,
 *       int ret = 0, i;                           //   so must be a LOCAL to hoist
 *       for (i = 2; i >= 0; i--) {
 *           float v = *a0;
 *           if (v < mn)            { *a0 = mn; ret = 1; *a1 = 0; }
 *           else if (D_00628C08 < v) { *a0 = D_00628C08; ret = 1; *a1 = 0; }
 *           a1++; a0++;
 *       }
 *       return ret;
 *   }
 * Matched: min hoisted to f2 (local defeats *a0-alias reload), i=2..0 bgez loop,
 * v load, c.lt.s v,min + bc1f, min-clamp `b`+swc1-in-delay, max reloaded from gp
 * each iter (alias forces reload, matches ROM), c.lt.s max,v + bc1fl with a1+=4 in
 * the (annulled) delay, shared clamp tail (ret=1; *a1=0; a1++). Only residual (4
 * diff pairs): ROM v=f0, max=f1 with the max `lwc1 f1,gp` kept in the L460 block
 * (bc1f delay = NOP). gcc instead REORG-fills the bc1f delay with the max load
 * `l.s f0,D_00628C08` -> max=f0, v=f1 (the load steals f0 and swaps the pair). ~6
 * source forms (v temp/no temp, v>max, mx-in-else, inverted >=) all reorg-fill the
 * bc1f delay. NEXT LEVER: block reorg from stealing the else-block's first (max)
 * load into the bc1f delay so v keeps f0 (find the dev shape where the max load is
 * not the sole eligible delay candidate). NOT a floor.
 * W3 fan-3 -dg CONFIRM: v=reg89 live=5 -> f1; max=reg90 live=4 -> f0. max's
 * shorter reload live-range wins f0 (allocno_compare 12/4 > 12/5). COUPLING is
 * inherent: reading D_00628C08 DIRECTLY each iter (k0/k1/k3/k5/k6/k7, up/down
 * count, {}else, >=, ptr-loop) forces the alias RELOAD (== ROM) but spawns the
 * short-lived pseudo that steals f0 AND the bc1f delay. Caching in a local `mx`
 * (k2) flips v->f0 and empties the bc1f delay (== ROM regs!) but HOISTS mx out
 * of the loop -> no reload (diverges). No shape gives reload + v->f0 together. */
extern float D_00628C04, D_00628C08;

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", LimitExistGeometry);

extern void MatrixDrive_TurnObjectMatrix(int a0, int a1);
extern void MatrixDrive_TransMatrix(char *dst, char *src);
extern void func_0023FE08(char *dst, char *src, int m);

void GetRootMatrixTransOffsetByDObj(char *dst, char *src)
{
    char tmp[0x40];
    MatrixDrive_TransMatrix(tmp, src + 0x20);
    func_0023FE08(tmp, tmp, *(int *)(src + 0xC));
    MatrixDrive_TurnObjectMatrix((int)dst, (int)(tmp + 0x30));
}

extern void MatrixDrive_TransMatrix(char *dst, char *src);

void GetRootMatrixTransOffset(char *dst, char *outer)
{
    char *src = ((GObj *)(outer))->p_15C;
    char tmp[0x40];
    MatrixDrive_TransMatrix(tmp, src + 0x20);
    func_0023FE08(tmp, tmp, *(int *)(src + 0xC));
    MatrixDrive_TurnObjectMatrix((int)dst, (int)(tmp + 0x30));
}

extern void getQuaternionFromMatrix(void *a0, void *a1);

void func_00104548(void *a0, char *a1) {
    char buf0[0x40];
    char buf1[0x40];
    char *b1 = buf1;
    char *sub = *(char **)(a1 + 0x15C);
    char *p = sub + 0xA0;
    GetMatrixFromQuaternionPos(b1, sub + 0xD0, p);
    {
        char *q = *(char **)sub;
        if (q != 0) {
            func_0023FE08(b1, (char *)(*(int *)(*(char **)(q + 0x15C) + 0xC) + (*(int *)(sub + 4) << 6)), (int)b1);
        }
    }
    *(float *)(b1 + 0x34) = *(float *)(b1 + 0x34) + *(float *)(p + 0xB0);
    getQuaternionFromMatrix(buf0, *(char **)(a1 + 0x15C) + 0xE0);
    func_0023FE08(buf0, b1, (int)buf0);
    sceVu0ApplyMatrix((int *)a0, buf0, (int)D_00271C10);
}

extern void getQuaternionFromMatrix(void *a0, void *a1);

void func_00104618(void *dst, char *a1) {
    char buf[0x40];
    char *sub = *(char **)(a1 + 0x15C);
    char *p = sub + 0xA0;
    GetMatrixFromQuaternionPos(buf, sub + 0xD0, p);
    {
        char *q = *(char **)sub;
        if (q != 0) {
            func_0023FE08(buf, (char *)(*(int *)(*(char **)(q + 0x15C) + 0xC) + (*(int *)(sub + 4) << 6)), (int)buf);
        }
    }
    *(float *)(buf + 0x34) = *(float *)(buf + 0x34) + *(float *)(p + 0xB0);
    getQuaternionFromMatrix(dst, *(char **)(a1 + 0x15C) + 0xE0);
    func_0023FE08((char *)dst, buf, (int)dst);
}

extern void _ScaleVectorXYZ(void *buf, void *p1, float f);
extern void AddVectorXYZ(void *a, void *b, void *c);

void GetProjectionPosOfPlane(void *a0, void *a1, void *a2)
{
    int buf[4];
    register float dot __asm__("$f12");
    VU0_LSV_R(lqc2, 1, 0x0, a2);
    VU0_LSV(lqc2, 2, 0x0, a1);
    VU0_V3OP(vmul.xyz, 3, 1, 2);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_V3OP_BC(vaddw.x, 3, 3, 2, w);
    VU0_QMFC2_NI(v0, 3);
    VU0_MTC1(v0, 12);
    _ScaleVectorXYZ(buf, a1, -dot);
    AddVectorXYZ(a0, a2, buf);
    *(float *)((char *)a0 + 0xC) = 1.0f;
}

extern void _ScaleVectorXYZ(void *buf, void *p1, float f);
extern void _AddVectorXYZ(void *a, void *b, void *c);

float GetProjectionOfPlane(void *a0, void *a1, void *a2)
{
    int buf[4];
    float z = 0.0f;
    register float dot __asm__("$f20");
    VU0_LSV_R(lqc2, 1, 0x0, a2);
    VU0_LSV(lqc2, 2, 0x0, a1);
    VU0_V3OP(vmul.xyz, 3, 1, 2);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_V3OP_BC(vaddw.x, 3, 3, 2, w);
    VU0_QMFC2_NI(v0, 3);
    VU0_MTC1(v0, 20);
    {
        register float nd __asm__("$f12") = -dot;
        _ScaleVectorXYZ(buf, a1, nd + z);
    }
    _AddVectorXYZ(a0, a2, buf);
    return dot;
}

float GetProjectionOfPlaneWithKeepAway(void *a0, void *a1, void *a2, float t)
{
    int buf[4];
    register float dot __asm__("$f20");
    VU0_LSV_R(lqc2, 1, 0x0, a2);
    VU0_LSV(lqc2, 2, 0x0, a1);
    VU0_V3OP(vmul.xyz, 3, 1, 2);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_V3OP_BC(vaddw.x, 3, 3, 2, w);
    VU0_QMFC2_NI(v0, 3);
    VU0_MTC1(v0, 20);
    _ScaleVectorXYZ(buf, a1, -dot + t);
    _AddVectorXYZ(a0, a2, buf);
    return dot;
}

extern int D_006594C0[];

void *func_00104838(void) {
    return D_006594C0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", getInitialInverseMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_001048F0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104998);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", ExecKeyInput);

extern int D_00629E40;
extern unsigned char D_006595C0[];
extern void sceVu0UnitMatrix(void *a0);
extern void InitTableSin(void);
extern void SetIdentityQuaternion(void);

void func_00104CF0(void) {
    D_00629E40 = 0;
    sceVu0UnitMatrix(D_006595C0);
    InitTableSin();
    SetIdentityQuaternion();
}

extern void CopyMatrix(void *dst, void *src);

void func_00104D20(void) {
    int n = ++D_00629E40;
    CopyMatrix(&D_006595C0[n * 64], &D_006595C0[n * 64 - 0x40]);
}

extern float GetTableCos(int x);
extern float p2o_SetDefaultEnviroment(int x);
extern float D_00271C60[];

void MatrixDrive_RotMatrixX(int a0)
{
    int h = (short)a0;
    float r1 = GetTableCos(h);
    float r2 = p2o_SetDefaultEnviroment(h);
    D_00271C60[10] = r1;
    D_00271C60[5] = r1;
    D_00271C60[9] = -r2;
    D_00271C60[6] = r2;
    func_0023FE08((char *)&D_006595C0[D_00629E40 * 64], (char *)&D_006595C0[D_00629E40 * 64], (int)D_00271C60);
}

extern float GetTableCos(int x);
extern float p2o_SetDefaultEnviroment(int x);
extern float D_00271CA0[];

void MatrixDrive_RotMatrixY(int a0)
{
    int h = (short)a0;
    float r1 = GetTableCos(h);
    float r2 = p2o_SetDefaultEnviroment(h);
    D_00271CA0[10] = r1;
    D_00271CA0[0] = r1;
    D_00271CA0[2] = -r2;
    D_00271CA0[8] = r2;
    func_0023FE08((char *)&D_006595C0[D_00629E40 * 64], (char *)&D_006595C0[D_00629E40 * 64], (int)D_00271CA0);
}

extern float GetTableCos(int x);
extern float p2o_SetDefaultEnviroment(int x);
extern float D_00271CE0[];

void MatrixDrive_RotMatrixZ(int a0)
{
    int h = (short)a0;
    float r1 = GetTableCos(h);
    float r2 = p2o_SetDefaultEnviroment(h);
    D_00271CE0[5] = r1;
    D_00271CE0[0] = r1;
    D_00271CE0[4] = -r2;
    D_00271CE0[1] = r2;
    func_0023FE08((char *)&D_006595C0[D_00629E40 * 64], (char *)&D_006595C0[D_00629E40 * 64], (int)D_00271CE0);
}

extern float D_00271D20[];

void MatrixDrive_ScaleMatrix(float x, float y, float z) {
    D_00271D20[0] = x;
    D_00271D20[5] = y;
    D_00271D20[10] = z;
    func_0023FE08(&D_006595C0[D_00629E40 * 64], &D_006595C0[D_00629E40 * 64], D_00271D20);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", MatrixDrive_TurnViewMatrix);

extern int D_00629E40;

void MatrixDrive_PushMatrixWithNoCopy(void) {
    D_00629E40++;
}

void MatrixDrive_PopMatrix(void) {
    D_00629E40--;
}

extern unsigned char D_006595C0[];

void *func_00105078(void) {
    return &D_006595C0[D_00629E40 * 64];
}

extern unsigned char D_00659580[];

void *func_00105090(void) {
    return &D_00659580[D_00629E40 * 64];
}

extern void sceVu0ApplyMatrix(int *buf, char *p, int x);

void func_001050A8(int a0)
{
    int buf[4];
    sceVu0ApplyMatrix(buf, &D_006595C0[D_00629E40 * 64], a0);
    *(float *)&buf[3] = 1.0f;
    MatrixDrive_TurnObjectMatrix(&D_006595C0[D_00629E40 * 64 + 0x30], buf);
}

void func_00105108(float f12, float f13, float f14) {
    float buf[4];
    float buf2[4];
    float *q = buf2;
    buf[0] = f12;
    buf[1] = f13;
    buf[2] = f14;
    buf[3] = 1.0f;
    sceVu0ApplyMatrix((int *)q, (char *)&D_006595C0[D_00629E40 * 0x40], (int)buf);
    q[3] = 1.0f;
    MatrixDrive_TurnObjectMatrix((int)(&D_006595C0[D_00629E40 * 0x40] + 0x30), (int)q);
}
