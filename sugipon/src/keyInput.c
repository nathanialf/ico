#include "common.h"
#include "ico/types.h"
#include "vu0.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", InitKeyInput);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", ExecKeyInput);

extern void MatrixDrive_TurnObjectMatrix(int a0, int a1);
extern void MatrixDrive_TransMatrix(char *dst, char *src);
extern void func_0023FE08(char *dst, char *src, int m);

void func_00104498(char *dst, char *src)
{
    char tmp[0x40];
    MatrixDrive_TransMatrix(tmp, src + 0x20);
    func_0023FE08(tmp, tmp, *(int *)(src + 0xC));
    MatrixDrive_TurnObjectMatrix((int)dst, (int)(tmp + 0x30));
}

extern void MatrixDrive_TransMatrix(char *dst, char *src);

void func_001044F0(char *dst, char *outer)
{
    char *src = ((GObj *)(outer))->p_15C;
    char tmp[0x40];
    MatrixDrive_TransMatrix(tmp, src + 0x20);
    func_0023FE08(tmp, tmp, *(int *)(src + 0xC));
    MatrixDrive_TurnObjectMatrix((int)dst, (int)(tmp + 0x30));
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104548);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104618);

extern void _PushVu0Registers(void *buf, void *p1, float f);
extern void MatrixDrive_TurnZObjectMatrixXY(void *a, void *b, void *c);

void func_001046C8(void *a0, void *a1, void *a2)
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
    _PushVu0Registers(buf, a1, -dot);
    MatrixDrive_TurnZObjectMatrixXY(a0, a2, buf);
    *(float *)((char *)a0 + 0xC) = 1.0f;
}

extern void _PushVu0Registers(void *buf, void *p1, float f);
extern void _RotTransPersCurrentMatrix(void *a, void *b, void *c);

float func_00104740(void *a0, void *a1, void *a2)
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
        _PushVu0Registers(buf, a1, nd + z);
    }
    _RotTransPersCurrentMatrix(a0, a2, buf);
    return dot;
}

float func_001047C0(void *a0, void *a1, void *a2, float t)
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
    _PushVu0Registers(buf, a1, -dot + t);
    _RotTransPersCurrentMatrix(a0, a2, buf);
    return dot;
}

extern int D_006594C0[];

void *func_00104838(void) {
    return D_006594C0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104848);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_001048F0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104998);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104A80);

extern int D_00629E40;
extern unsigned char D_006595C0[];
extern void func_002400F8(void *a0);
extern void func_0010ED88(void);
extern void SetIdentityQuaternion(void);

void func_00104CF0(void) {
    D_00629E40 = 0;
    func_002400F8(D_006595C0);
    func_0010ED88();
    SetIdentityQuaternion();
}

extern void MatrixDrive_TurnXObjectMatrixYZ(void *dst, void *src);

void func_00104D20(void) {
    int n = ++D_00629E40;
    MatrixDrive_TurnXObjectMatrixYZ(&D_006595C0[n * 64], &D_006595C0[n * 64 - 0x40]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104D48);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104DC0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104E38);

extern float D_00271D20[];

void func_00104EB0(float x, float y, float z) {
    D_00271D20[0] = x;
    D_00271D20[5] = y;
    D_00271D20[10] = z;
    func_0023FE08(&D_006595C0[D_00629E40 * 64], &D_006595C0[D_00629E40 * 64], D_00271D20);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104EE0);

extern int D_00629E40;

void func_00105058(void) {
    D_00629E40++;
}

void func_00105068(void) {
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

extern void func_0023FDD8(int *buf, char *p, int x);

void func_001050A8(int a0)
{
    int buf[4];
    func_0023FDD8(buf, &D_006595C0[D_00629E40 * 64], a0);
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
    func_0023FDD8((int *)q, (char *)&D_006595C0[D_00629E40 * 0x40], (int)buf);
    q[3] = 1.0f;
    MatrixDrive_TurnObjectMatrix((int)(&D_006595C0[D_00629E40 * 0x40] + 0x30), (int)q);
}
