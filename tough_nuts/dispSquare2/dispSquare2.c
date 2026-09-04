#include "common.h"

extern int D_0062C230;
extern int D_0062C22C;
extern int D_0062C218;
extern int D_0062C224;
extern int D_0062B758;
extern float D_00703094[];

int dispSquare2(int type, float thresh) {
    int *v3 = (int *)D_0062C230;
    int st;
    int i;
    int count;

    float f0;

    if (v3[0x220 / 4] != 0) {
        if (type == 6) goto ret_neg1;
        if (type == 0xB) goto ret_neg1;
    }
    st = v3[0x280 / 4];
    if (st != 0) {
        if (type == 0x16) goto ret_neg1;
        if (type == 0x1B) goto ret_neg1;
    }
    count = D_0062C22C;
    for (i = 0; i < count; i++) {
        if (*(int *)(D_0062B758 + i * 64 + 4) == type) {
            if (*(int *)(D_0062C218 + i * 32) >= 0xF9) goto ret_neg1;
            f0 = *(float *)(D_0062C224 + i * 16 + 4) + D_00703094[0];
            if (f0 < 0.0f) {
                f0 = -f0;
                if (f0 < thresh) goto ret_type;
                goto ret_neg1;
            }
            if (!(f0 < thresh)) goto ret_neg1;
            goto ret_type;
        }
    }
    return -1;
ret_neg1:
    return -1;
ret_type:
    return type;
}


extern int D_0062C230;
extern int D_0062C234;

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", findActPoint);


extern int func_00105078(void);
extern int func_00104D20(void);
extern void MatrixDrive_PopMatrix(void);
extern void MatrixDrive_TurnObjectMatrix(int a0, int a1);
extern int D_0062C234;
extern void memset(void *a0, int a1, int a2);
extern void func_001050A8(void *a0);
extern void sceVu0ApplyMatrix(int *a0, int a1, char *a2);
extern void ClipWallBoxStop(void *a0);
extern float GetPointDistance(void *a0, void *a1);
extern char D_004C1C60[];
extern char D_004C1C70[];

void checkActPointWithHeight(void) {
    char buf[0xC0];
    memset(buf, 0, 0xC0);
    func_00104D20();
    func_001050A8(D_004C1C60);
    MatrixDrive_TurnObjectMatrix((int)buf, func_00105078() + 0x30);
    sceVu0ApplyMatrix((int *)(buf + 0x10), func_00105078(), D_004C1C70);
    MatrixDrive_PopMatrix();
    ClipWallBoxStop(buf);
    if (*(int *)(buf + 0x88) != 0) {
        float a;
        int *D;
        a = GetPointDistance(buf + 0x20, buf);
        D = (int *)D_0062C234;
        *(float *)((char *)D + 0x170) = a;
        *(int *)((char *)D + 0x108) = 1;
        *(int *)((char *)D + 0x14) = *(int *)((char *)D + 0x14) | 0x1000;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", clearCollisionStatus);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", checkUpperWallState);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", checkWallSideState);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", checkWallState);

extern void _UnitMatrix(int a0);
extern int func_00105078(void);
extern float GetYProjectionOfPlane(int a0, int a1);
extern void func_00105108(float, float, float);
extern void MultiMatrixByQuaternion(char *p);
extern int func_00104D20(void);
extern void checkWallState(void);
extern void MatrixDrive_PopMatrix(void);
extern void clearCollisionStatus(void);
extern int D_0062C230;
extern int D_0062C234;

void checkCliffState(void)
{
    _UnitMatrix(func_00105078());
    {
        register float *p = (float *)D_0062C230;
        float r = GetYProjectionOfPlane(D_0062C230 + 0x120, D_0062C230);
        func_00105108(p[0], r, *(float *)(D_0062C230 + 8));
    }
    MultiMatrixByQuaternion((char *)D_0062C230 + 0x30);
    func_00104D20();
    checkWallState();
    MatrixDrive_PopMatrix();
    if (*(int *)(D_0062C234 + 0xE4) != 0) {
        func_00104D20();
        clearCollisionStatus();
        MatrixDrive_PopMatrix();
    }
}

extern int D_0062C230;
extern int func_00105078(void);
extern void func_00105108(float, float, float);
extern void MultiMatrixByQuaternion(char *p);
extern void _UnitMatrix(int a0);
extern void checkWallState(void);

void _checkCliffAndWall(void)
{
    _UnitMatrix(func_00105078());
    {
        register float *p = (float *)D_0062C230;
        func_00105108(p[0], p[1] + p[112] + 10.0f, p[2]);
    }
    MultiMatrixByQuaternion((char *)D_0062C230 + 0x30);
    checkWallState();
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", checkCliffAndWallStateOfLastPlane);

extern void gif_SpriteOffset();
extern void gif_SetAlpha();
extern int func_00104D20(void);
extern int func_00105078(void);
extern void f2400F8(int) __asm__("sceVu0UnitMatrix");
extern void func_00105108(float, float, float);
extern void MatrixDrive_ScaleMatrix(float, float, float);
extern void InitMotionMemorySize(int);
extern void MatrixDrive_PopMatrix(void);
extern void func_0010F9D0();
extern int D_0062C230;

void checkCliffAndWallStateAtJump(void)
{
    register float *p;
    int v;
    gif_SpriteOffset(0xB);
    gif_SetAlpha(1, 5, 0x80);
    func_00104D20();
    v = func_00105078();
    f2400F8(v);
    p = (float *)D_0062C230;
    func_00105108(p[104], p[105], p[106]);
    MatrixDrive_ScaleMatrix(8.0f, 8.0f, 8.0f);
    InitMotionMemorySize(0xFF);
    MatrixDrive_PopMatrix();
    func_0010F9D0();
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", dispActNode);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", dispLastNode);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", _getGeometryOfMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", execPositionReserver);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", GetGeometryOfMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", GetMatrixOfMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001D8398);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", getInitialMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", adjustSideWall);

extern int D_0062C230;
extern void ClipWallCheckCB(void *a0);
extern int GetWallAttribute(void *a0);
extern int adjustSideWall(int a0, int a1, int a2);

int SkelTest(int a0, int a1, int p, int a3, int a4) {
    int flag;
    int mag;
    int mask;

    *(int *)(p + 0x70) = 0;
    MatrixDrive_TurnObjectMatrix(p, a3);
    sceVu0ApplyMatrix((int *)(p + 0x10), a1, (char *)a0);
    ClipWallBoxStop((void *)p);

    if (*(int *)(p + 0x88) != 0) {
        goto disp_one;
    }
    if (*(int *)(D_0062C230 + 0x314) != 0) {
        ClipWallCheckCB((void *)p);
        if (*(int *)(p + 0x88) != 0) {
            flag = 0;
            mag = GetWallAttribute((void *)p);
            switch (*(int *)(D_0062C230 + 0x314)) {
            default:
            case 1:
                mask = 0x20000000;
                break;
            case 2:
                mask = 0x10000000;
                break;
            }
            if (mag & mask) {
                flag = 1;
                if (mag & 0x0FFFFFFF) {
                    return -1;
                }
            }
            if (flag != 0) {
                return adjustSideWall(p, 0, a4);
            }
            goto block12;
        }
    }
block12:
    MatrixDrive_TurnObjectMatrix(p, p + 0x10);
    MatrixDrive_TurnObjectMatrix(p + 0x10, a3 + 0x10);
    ClipWallBoxStop((void *)p);
    if (*(int *)(p + 0x88) != 0) {
disp_one:
        return adjustSideWall(p, 1, a4);
    }
    return 0;
}


extern int D_0062B75C;
extern int D_0062C230;
extern void iosOmSendMail(int a0, int a1, int a2);
extern void MatrixDrive_TurnObjectMatrix(int a0, int a1);

void SkelTestGeo(void) {
    iosOmSendMail(D_0062B75C, 0x18, D_0062B75C);
    MatrixDrive_TurnObjectMatrix(D_0062C230 + 0x140, D_0062C230);
}

void SetHitCollisionDisplay(void) {
    iosOmSendMail(D_0062B75C, 0xF0, D_0062B75C);
    MatrixDrive_TurnObjectMatrix(D_0062C230 + 0x140, D_0062C230);
}

extern void func_00105108(float, float, float);
extern int func_00105078(void);
extern void MultiMatrixByQuaternion(char *p);
extern float D_00703094[];
extern int func_00104D20(void);
extern int sceVu0UnitMatrix(int);
extern void checkActPointWithHeight(void);
extern void MatrixDrive_PopMatrix(void);

void checkWallUpperWall(void)
{
    int v;
    func_00104D20();
    v = func_00105078();
    sceVu0UnitMatrix(v);
    {
        register float *p = (float *)D_0062C230;
        func_00105108(p[0], p[1] - D_00703094[0], p[2]);
    }
    MultiMatrixByQuaternion((char *)D_0062C230 + 0x30);
    checkActPointWithHeight();
    MatrixDrive_PopMatrix();
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", getGeometryOfMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001D9E10);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DA508);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", avoidSideAdjustWall);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DAAC0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DB538);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DB620);

typedef struct { long long x; } __attribute__((packed, aligned(4))) PackedLL_19CAF0;

extern void GetMatrixFromQuaternion(int);
extern void func_0010E4E8(int, int);
extern void SetMotionBlendlessNode(int);
extern PackedLL_19CAF0 D_0062A6A0;
extern float D_0062B720;
extern int D_0062B75C;
extern int D_0062C230;
extern int D_0062C248;
extern char D_00271BD0[];
extern char D_00703090[];
extern char D_007030B0[];

PackedLL_19CAF0 func_001DB710(int a0) {
    float *p;
    float x, y, z;

    GetMatrixFromQuaternion(D_0062C230 + 0x30);
    func_0010E4E8(D_0062C230 + 0x30, -0x8000);
    MatrixDrive_TurnObjectMatrix(D_0062C230, (int)D_00703090);

    p = (float *)D_0062C230;
    x = p[0] - *(float *)(D_0062C248 + 0x124);
    p[0] = x;
    y = p[1] - *(float *)(D_0062C248 + 0x128);
    p[1] = y;
    z = p[2] + *(float *)(D_0062C248 + 0x12C);
    p[2] = z;
    if (a0 == 0xE) {
        float inv = 1.0f / D_0062B720;
        p[1] = y * inv;
        p[0] = x * -inv;
        p[2] = z * -inv;
    } else {
        p[0] = -x;
        p[2] = -z;
    }
    MatrixDrive_TurnObjectMatrix((int)p + 0x140, (int)p);
    MatrixDrive_TurnObjectMatrix(D_0062C230 + 0x80, (int)D_00271BD0);
    MatrixDrive_TurnObjectMatrix(D_0062C230 + 0x10, (int)D_00271BD0);

    {
        typedef struct { char _a[0xB0]; int f_B0; char _b[0xBC]; int f_170; } MotObj;
        extern MotObj *D_0062C230_o __asm__("D_0062C230");
        D_0062C230_o->f_170 = -1;
        D_0062C230_o->f_B0 = 0;
        SetMotionBlendlessNode(D_0062B75C);
    }
    MatrixDrive_TurnObjectMatrix(D_0062C230 + 0xC0, (int)D_007030B0);

    return D_0062A6A0;
}


INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DB870);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DB9A0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DBBB8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DBFF8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DC208);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DC428);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DC640);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DCB70);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DCE78);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DD3A8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DD6E8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionManager", func_001DD9B8);

extern void gif_SpriteOffset();
extern void gif_SetAlpha();
extern void func_001DD6E8();
extern void func_0010F9D0();

void dispSkelton(void) {
    int v;
    gif_SpriteOffset(0xB);
    gif_SetAlpha(1, 5, 0x80);
    func_00104D20();
    v = func_00105078();
    sceVu0UnitMatrix(v);
    func_001DD6E8(0);
    MatrixDrive_PopMatrix();
    func_0010F9D0();
}

extern int D_0062B758;
extern int D_0062AF90;
extern void func_0010F048();
extern void func_001DDAB8_a(char *) __asm__("dispSkelton");

void func_001DDB10(char *a0) {
    int sub = *(int *)(a0 + 0x15C);
    int v;
    D_0062B75C = (int)a0;
    v = *(int *)(sub + 0x8C);
    D_0062B758 = v;
    if (v != 0) {
        func_0010F048();
        if (D_0062AF90 != 0) {
            func_001DDAB8_a(a0);
        }
    }
}

extern void MatrixDrive_RotMatrixX(int a0);
extern void func_001DD9B8(int a0, int a1);
extern void func_0023FE08(int a0, int a1, int a2);

void func_001DDB68(char *a0) {
    int sub = *(int *)(a0 + 0x15C);
    int v;
    int i;
    D_0062B75C = (int)a0;
    v = *(int *)(sub + 0x8C);
    D_0062B758 = v;
    if (v != 0) {
        int s2;
        sceVu0UnitMatrix(func_00105078());
        MatrixDrive_RotMatrixX(-0x8000);
        func_001DD9B8(*(int *)(a0 + 0x15C), 0);
        s2 = *(int *)(a0 + 0x15C);
        for (i = 0; i < *(int *)(s2 + 0x88); i++) {
            int e = *(int *)(s2 + 0xC) + i * 0x40;
            func_0023FE08(e, s2 + 0x20, e);
            s2 = *(int *)(a0 + 0x15C);
        }
        if (D_0062AF90 != 0) {
            func_001DDAB8_a(a0);
        }
    }
}


extern int D_0062B718;
extern int D_0062B71C;

void func_001DDC28(int a0, int a1) {
    D_0062B718 = a0;
    D_0062B71C = a1;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00611DE0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00611E60;  /* stride 0x4 */

/* end struct shapes */
