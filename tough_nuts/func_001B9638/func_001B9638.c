#include "matching.h"
typedef struct { float m[16]; } Mtx44;
struct Frame12 { long long ll; int w; } __attribute__((packed));
extern void func_0019F530(void);
extern void func_00118388(int dst, int src, int v);
extern void func_00105F00(int a, int b);
extern void func_001685E0(int dst);
extern void func_001B8CE0(int *self, int arg2);
extern void func_0019F4E8(int *self, int buf);
extern void func_00102858(int *self);
extern void func_00104140(int dst, int *self);
extern void func_00118648(int a, int b, int c);
extern int func_00168A40(int dst);
extern int func_00168A60(int dst);
extern int func_0010A068(int *self, int sel);
extern int func_0010A048(int *self, int sel);
extern float func_0010D078(int x);
extern void func_0013FF88(int *self, int a, int b);
extern void func_00168538(int dst);
extern int func_00106390(int dst, int *self, int v, float f);
extern int D_00274EC0[];
extern char D_004BECD0[];
extern char D_004BECF0[];
extern char D_004BEBA0[];
extern char D_00275850[];
int func_001B9638(int *self)
{
    struct Frame12 buf;
    float m10[16];
    char *d = D_004BECD0;
    int sel;
    float t;

    if (*(int *)((char *)self[0x15C / 4]) != 0) {
        func_0019F530();
    }
    {
        int q = (0x3C - D_00274EC0[0] * 10) / D_00274EC0[1];
        t = 60.0f / (float)q;
        *(float *)((char *)self[0x15C / 4] + 0x134) =
            *(float *)((char *)self[0x15C / 4] + 0x134) + t * 0.5f * t;
    }
    func_00118388((int)((char *)self[0x15C / 4] + 0xA0),
                  (int)((char *)self[0x15C / 4] + 0xA0),
                  (int)((char *)self[0x15C / 4] + 0x130));
    func_00105F00((int)d, (int)((char *)self[0x15C / 4] + 0x1F0));
    func_00105F00((int)(d + 0x10), (int)((char *)self[0x15C / 4] + 0xA0));
    *(float *)(d + 0x4) = *(float *)(d + 0x4) - 50.0f;
    func_001685E0((int)d);

    if (*(int *)(d + 0x88) != 0) {
        buf.w = *(int *)(d + 0x88);
        buf.ll = ((struct Frame12 *)(d + 0x80))->ll;
        sel = 1;
    } else if (*(int *)(d + 0x94) != 0) {
        buf.w = *(int *)(d + 0x94);
        buf.ll = ((struct Frame12 *)(d + 0x8C))->ll;
        sel = 1;
    } else {
        sel = 0;
    }

    if (sel == 0) {
        *(float *)(d + 0x14) = *(float *)(d + 0x14) + 500.0f;
        func_00168538((int)d);
        if (func_00106390((int)d, self,
                          (int)((char *)self[0x15C / 4] + 0xA0), 50.0f) == 2) {
            func_00105F00((int)((char *)self[0x15C / 4] + 0x130), (int)D_00275850);
            func_0013FF88(self, 0x1A, (int)self);
            return -1;
        }
        return -1;
    }

    func_00105F00((int)((char *)self[0x15C / 4] + 0xA0), (int)D_004BECF0);
    func_00105F00((int)((char *)self[0x15C / 4] + 0x130), (int)D_00275850);
    func_001B8CE0(self, (int)(D_004BECF0 + 0x80));
    func_0019F4E8(self, (int)&buf);
    func_00102858(self);
    func_00104140((int)m10, self);
    {
        char *s1 = (char *)((int *)self[0x15C / 4])[0x800 / 4] + 0x20;
        char *bb = D_004BEBA0;
        int k;
        for (k = 3; k >= 0; k--) {
            func_00118648((int)s1, (int)m10, (int)bb);
            func_00118648((int)(s1 + 0x10), (int)m10, (int)bb);
            bb += 0x10;
            s1 += 0x50;
        }
    }

    d = D_004BECD0;
    if (*(int *)(d + 0x88) != 0) {
        *(int *)((char *)self[0x15C / 4] + 0x5F8) = func_00168A40((int)d);
    }
    if (func_0010A068(self, 0x40) != 0 || func_0010A068(self, 0x50) != 0) {
        if (func_0010D078(*(int *)(d + 0x80))
                < *(float *)((char *)self[0x15C / 4] + 0xA4) + 50.0f) {
            func_0013FF88(self, 0x26, (int)self);
        }
    }
    if (*(int *)(d + 0x94) != 0) {
        *(int *)((char *)self[0x15C / 4] + 0x5F8) = func_00168A60((int)d);
        if (func_0010A048(self, 0x40) != 0 || func_0010A048(self, 0x50) != 0) {
            if (func_0010D078(*(int *)(d + 0x8C))
                    < *(float *)((char *)self[0x15C / 4] + 0xA4) + 50.0f) {
                func_0013FF88(self, 0x26, (int)self);
            }
        }
    }
    return 0;
}
