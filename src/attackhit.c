/* src/attackhit.c — __FILE__ anchor at .rodata 0x0055A518
 *
 * TU range: [0x00181960, 0x00181F38)  (next subseg: src/cod/081F38 at 0x00181F38)
 *
 * Six funcs:
 *   - func_00181960 (anchor; complex linked-list scan with debug logs)
 *   - func_00181BB8 (jr ra + nop — empty stub)
 *   - func_00181BC0 (jr ra + nop — empty stub)
 *   - func_00181BC8 (small wrapper: forward to func_00180F40 + func_00181960)
 *   - func_00181BF8 (anchor; long initializer using D_0055A3F0 template)
 *   - func_00181D88 (anchor; same shape as func_00181BF8 at line 0x300)
 */

#include "attackhit.h"

INCLUDE_ASM("asm/nonmatchings/src/attackhit", func_00181960);

void func_00181BB8(void) {}

void func_00181BC0(void) {}

void func_00181BC8(int a0)
{
    int buf[28];
    int *v0 = *(int **)((char *)a0 + 0x164);
    func_00180F40(buf, a0, v0[0x140 / 4]);
    func_00181960(buf);
}

typedef struct {
    long long w[14];
} AttackBuf_181BF8;

void func_00181BF8(void *self, int p1, float *vec, void *cb, float scale)
{
    AttackBuf_181BF8 buf;
    register char *buf_base REG("$16");
    register float vx REG("$f2");
    register float vy REG("$f0");
    register float vz REG("$f1");
    float *vp = vec;
    if (self == 0) {
        func_001AD768(D_0055A518, 0x2ED);
        func_00263FF0(D_0055A518, 0x2ED, D_0055A528);
    }
    buf_base = (char *)(&buf);
    vx = vp[0];
    vy = vp[1];
    vz = vp[2];
    *((AttackBuf_181BF8 *)buf_base) = *((AttackBuf_181BF8 *)D_0055A3F0);
    *((char *)(buf_base + 0x0)) = 1;
    *((int *)(buf_base + 0xC)) = p1;
    *((int *)(buf_base + 0x4)) = (int)self;
    KEEP_LIVE(buf_base);
    *((int *)(buf_base + 0x8)) = p1;
    *((float *)(buf_base + 0x10)) = vx;
    *((float *)(buf_base + 0x14)) = vy;
    *((float *)(buf_base + 0x18)) = vz;
    if (cb != 0) {
        func_00243AE8((float *)(buf_base + 0x20), (float *)(buf_base + 0x10), cb);
        vx = vp[0];
        vy = vp[1];
        vz = vp[2];
    } else {
        *((float *)(buf_base + 0x20)) = vx;
        *((float *)(buf_base + 0x24)) = vy;
        *((float *)(buf_base + 0x28)) = vz;
    }
    *((float *)(buf_base + 0x30)) = vx;
    *((float *)(buf_base + 0x34)) = vy;
    *((float *)(buf_base + 0x38)) = vz;
    *((float *)(buf_base + 0x40)) = scale;
    *((float *)(buf_base + 0x44)) = scale;
    if ((self != 0) && ((*((int *)(((char *)self) + 0xC))) == 0x34)) {
        *((float *)(buf_base + 0x48)) = scale - 100.0f;
    } else {
        *((int *)(buf_base + 0x48)) = 0;
    }
    *((float *)(buf_base + 0x4C)) = 20.0f;
    func_00181960((int *)((char *)(&buf)));
}

INCLUDE_ASM("asm/nonmatchings/src/attackhit", func_00181D88);
