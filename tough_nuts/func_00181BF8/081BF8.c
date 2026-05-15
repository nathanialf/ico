/* Permuter seed for func_00181BF8 (attackhit.c, line 0x2ED). */

#include "matching.h"
#include "regpin.h"

extern char D_0055A518[];
extern char D_0055A528[];
extern unsigned int D_0055A3F0[];
extern void func_001AD768(const char *file, int line);
extern void func_00263FF0(const char *file, int line, const char *expr);
extern void func_00243AE8(float *dst, float *src, void *cb);
extern void func_00181960(int *buf);

typedef struct { long long w[14]; } AttackBuf;

void func_00181BF8(void *self, int p1, float *vec, void *cb, float scale)
{
    AttackBuf buf;
    register char *buf_base REG("$16");
    register float vx REG("$f2");
    register float vy REG("$f0");
    register float vz REG("$f1");
    float *vp = vec;
    if (self == 0) {
        func_001AD768(D_0055A518, 0x2ED);
        func_00263FF0(D_0055A518, 0x2ED, D_0055A528);
    }
    buf_base = (char *)&buf;
    KEEP_LIVE(buf_base);
    vx = vp[0]; vy = vp[1]; vz = vp[2];
    *(AttackBuf *)buf_base = *(AttackBuf *)D_0055A3F0;
    *(char *)(buf_base + 0x0) = 1;
    *(int *)(buf_base + 0xC) = p1;
    *(int *)(buf_base + 0x4) = (int)self;
    *(int *)(buf_base + 0x8) = p1;
    *(float *)(buf_base + 0x10) = vx;
    *(float *)(buf_base + 0x14) = vy;
    *(float *)(buf_base + 0x18) = vz;
    if (cb != 0) {
        func_00243AE8((float *)(buf_base + 0x20),
                      (float *)(buf_base + 0x10), cb);
        vx = vp[0]; vy = vp[1]; vz = vp[2];
    } else {
        *(float *)(buf_base + 0x20) = vx;
        *(float *)(buf_base + 0x24) = vy;
        *(float *)(buf_base + 0x28) = vz;
    }
    *(float *)(buf_base + 0x30) = vx;
    *(float *)(buf_base + 0x34) = vy;
    *(float *)(buf_base + 0x38) = vz;
    *(float *)(buf_base + 0x40) = scale;
    *(float *)(buf_base + 0x44) = scale;
    if (self != 0 && *(int *)((char *)self + 0xC) == 0x34) {
        *(float *)(buf_base + 0x48) = scale - 100.0f;
    } else {
        *(int *)(buf_base + 0x48) = 0;
    }
    *(float *)(buf_base + 0x4C) = 20.0f;
    func_00181960((int *)buf_base);
}
