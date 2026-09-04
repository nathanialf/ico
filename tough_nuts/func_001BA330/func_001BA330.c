#include "matching.h"
typedef void (*FsmFn)(int *);
typedef struct { FsmFn a; FsmFn b; } FsmPair;
extern FsmFn D_004BEE60[16];
extern float D_004BEEA0[32];
extern float D_004BEF20[16];
extern const char D_00618590[40];
extern const float D_0063112C;
extern const float D_00631130[1];
extern void func_001BA2E0(int *self);
extern void func_001BA090(int *self);
extern void func_001B99B0(int *self);
extern int func_00105278(void);
extern void _MulMatrix(int a, int b, int c);
extern void func_001CF930(int a, int b, float f);
extern void func_00105F20(int a, int b);
extern void MatrixDrive_RotMatrixZ(int a);
extern void MatrixDrive_RotMatrixX(int a);
extern void func_001A6E28(int a);
void func_001BA330(int *self)
{
    int *p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    int state = p[0x8 / 4];

    switch (state) {
    default:
        if (p[0x274 / 4] < 10) {
            p[0x274 / 4] = p[0x274 / 4] + 1;
            func_001BA2E0(self);
            state = p[0x8 / 4];
        }
        p[0x8 / 4] = ((int (*)(int *))((FsmPair *)D_004BEE60)[state].b)(self);
        {
            int *pp = (int *)((int *)self[0x15C / 4])[0x800 / 4];
            int t = pp[0x270 / 4] + 1;
            pp[0x270 / 4] = t;
            if (t >= 0x21) {
                pp[0x270 / 4] = 0;
            }
        }
        break;
    case 5:
        p[0x8 / 4] = 4;
        break;
    case 4:
        p[0x8 / 4] = 6;
        break;
    case 6:
        self[0x16C / 4] = 0;
        break;
    case 7:
        break;
    }

    func_001BA090(self);
    func_001B99B0(self);
    {
        int r = func_00105278();
        _MulMatrix(r, ((int *)self[0x15C / 4])[0xC / 4], (int)D_004BEEA0);
    }
    {
        int r = func_00105278();
        func_001CF930(p[0x19C / 4], r, 1.0f);
    }
    if (p[0x4 / 4] != 0) {
        int r3 = func_00105278();
        func_00105F20(r3, ((int *)self[0x15C / 4])[0xC / 4]);
        MatrixDrive_RotMatrixZ(0x4000);
        MatrixDrive_RotMatrixX(0x4000);
        {
            int *sub = (int *)self[0x15C / 4];
            int r4 = func_00105278();
            _MulMatrix(sub[0xC / 4], r4, (int)D_004BEF20);
        }
    }
    {
        int *sub = (int *)self[0x15C / 4];
        float diff = *(float *)((char *)sub + 0x54)
                   - *(float *)((char *)((int *)sub[0xC / 4]) + 0x34);
        if (diff < 0.0f) {
            diff = -diff;
            if (D_0063112C < diff) {
                goto hit;
            }
            return;
        }
        if (!(D_00631130[0] < diff)) {
            return;
        }
    hit:
        *(int *)((char *)sub + 0x5F8) = 0x800;
        func_001A6E28((int)D_00618590);
    }
}
