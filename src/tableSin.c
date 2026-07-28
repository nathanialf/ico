#include "common.h"

#include "vu0.h"






extern void func_001185D0();
extern void getQuaternionFromMatrix();
extern int * func_00105278();
extern void RegularizeQuaternion();
extern int D_00553E48[];
extern void SetIdentityQuaternion();
extern char D_00553E00[];
extern void debug_assertMessage();
extern char D_00553E28[];
extern int D_00660A30[];
extern int D_00631B7C;
int *GetTableSin(void)
{
    return &D_00660A30[D_00631B7C * 4];
}

void GetTableCos(void)
{
    int v = D_00631B7C;
    if (v < 0) {
        debug_assertMessage(D_00553E00);
        SetIdentityQuaternion();
        v = D_00631B7C;
    }
    v++;
    D_00631B7C = v;
    if (v >= 0x40) {
        debug_assertMessage(D_00553E28);
        v = 0x3F;
        D_00631B7C = v;
    }
}

void InitTableSin(void)
{
    D_00631B7C -= 1;
    if (D_00631B7C < 0) {
        debug_assertMessage(D_00553E48);
        D_00631B7C = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/tableSin", GetTableArcSin);

extern float _InverseCurrentMatrix(int *self, void *p, float arg);
extern float func_0010E9A0(int x);
extern float p2o_SetDefaultEnviroment(int x);

void GetTableArcCos(int *self, int a1, float x, float y, float z) {
    char buf[0x10];
    int half = (a1 << 16) >> 17;
    float f;
    *(float *)(buf + 0) = x;
    *(float *)(buf + 4) = y;
    *(float *)(buf + 8) = z;
    *(int *)(buf + 0xC) = 0;
    f = p2o_SetDefaultEnviroment(half);
    _InverseCurrentMatrix(self, buf, f);
    *(float *)((char *)self + 0xC) = func_0010E9A0(half);
}

extern void _SetCurrentMatrix(void *out, int *p);
extern float func_00117C20(float t);

void GetTableArcTan2(float *out, float *in, float x, float y, float z) {
    float v[4];
    float r[4];
    float s1, s2;
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 0.0f;
    s1 = func_00117C20((in[0] + 1.0f) * 0.5f);
    s2 = func_00117C20((1.0f - in[0]) * 0.5f);
    _SetCurrentMatrix(r, (int *)v);
    out[0] = r[0] * s2;
    out[1] = r[1] * s2;
    out[2] = r[2] * s2;
    out[3] = s1;
}

INCLUDE_ASM("asm/nonmatchings/src/tableSin", func_0010DCF8);

INCLUDE_ASM("asm/nonmatchings/src/tableSin", func_0010DD58);

INCLUDE_ASM("asm/nonmatchings/src/tableSin", func_0010DDB8);

void func_0010DDF8(int self, int a1, int a2)
{
    int buf[4];
    RegularizeQuaternion(buf, a2);
    func_0010DDB8(self, buf, a1);
}

INCLUDE_ASM("asm/nonmatchings/src/tableSin", func_0010DE40);

INCLUDE_ASM("asm/nonmatchings/src/tableSin", func_0010DEC0);

void func_0010DF70(void *src)
{
    int local[16];
    void *r1, *r2;
    getQuaternionFromMatrix(local, src);
    r1 = func_00105278();
    r2 = func_00105278();
    func_001185D0(r1, r2, local);
}

INCLUDE_ASM("asm/nonmatchings/src/tableSin", func_0010DFB8);

INCLUDE_ASM("asm/nonmatchings/src/tableSin", func_0010E0B8);

INCLUDE_ASM("asm/nonmatchings/src/tableSin", func_0010E158);

INCLUDE_ASM("asm/nonmatchings/src/tableSin", func_0010E1F8);

INCLUDE_ASM("asm/nonmatchings/src/tableSin", func_0010E298);

