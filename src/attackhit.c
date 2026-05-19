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

#include "matching.h"
#include "regpin.h"
#include "include_asm.h"

/* sdata */
extern int D_00632DBC;

/* ASCII rodata */
__attribute__((section(".rodata.0x0055A4B0"))) const char D_0055A4B0[16] = "flag ok\n";
__attribute__((section(".rodata.0x0055A4C0"))) const char D_0055A4C0[16] = "group ok\n";
__attribute__((section(".rodata.0x0055A4D0"))) const char D_0055A4D0[16] = "invincible ok\n";
__attribute__((section(".rodata.0x0055A4E0"))) const char D_0055A4E0[16] = "geometry ok\n";
__attribute__((section(".rodata.0x0055A4F0"))) const char D_0055A4F0[16] = "id equal error\n";
__attribute__((section(".rodata.0x0055A500"))) const char D_0055A500[24] = "mail send ok [%d]\n";
__attribute__((section(".rodata.0x0055A518"))) const char D_0055A518[16] = "src/attackhit.c";
__attribute__((section(".rodata.0x0055A528"))) const char D_0055A528[16] = "gop!=NULL";
__attribute__((section(".rodata.0x0055A538"))) const char D_0055A538[48] = "brainStatusDefaultSet: brain target area over\n";

/* EUC-JP: "ブレインレベルのオーバーライドに失敗しました\n" */
__attribute__((section(".rodata.0x0055A568"))) const char D_0055A568[48] = "\245\326\245\354\245\244\245\363\245\354\245\331\245\353\244\316\245\252\241\274\245\320\241\274\245\351\245\244\245\311\244\313\274\272\307\324\244\267\244\336\244\267\244\277\n";

/* Int / float / double rodata */
__attribute__((section(".rodata.0x0055A3F0"))) unsigned int D_0055A3F0[28] = {
    0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000,
};
__attribute__((section(".rodata.0x0055A460"))) unsigned int D_0055A460[20] = {
    0x00000001, 0x00000000, 0x00000004, 0x00000001,
    0x0000002E, 0x00000001, 0x00000035, 0x00000001,
    0x00000034, 0x00000001, 0x00000034, 0x00000001,
    0x0000003D, 0x00000001, 0x00000002, 0x00000003,
    0x0000003E, 0x00000001, 0xFFFFFFFF, 0x00000000,
};
__attribute__((section(".rodata.0x0055A598"))) const double D_0055A598 = 1.9;
__attribute__((section(".rodata.0x0055A5A0"))) const double D_0055A5A0 = 0.002;
__attribute__((section(".rodata.0x0055A5A8"))) const float D_0055A5A8[2] = { 89128.96f, 0.955f };
__attribute__((section(".rodata.0x0055A5B0"))) const double D_0055A5B0[2] = { 1.9, 0.0 };

/* Cross-TU symbols referenced from this TU */
extern void func_00180F40(int *buf, int self, int arg);
extern void func_001A6E28(const char *msg);
extern void func_001AD768(const char *file, int line);
extern void func_00263FF0(const char *file, int line, const char *expr);
extern void func_00243AE8(float *dst, float *src, void *cb);

/* Intra-TU forward decls (defined via INCLUDE_ASM or below) */
void func_00181960(int *buf);
void func_00181BB8(void);
void func_00181BC0(void);
void func_00181BC8(int a0);

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

void func_00181D88(void *self, int p1, float *vec, void *cb, float scale)
{
    AttackBuf_181BF8 buf;
    register char *buf_base REG("$16");
    register float vx REG("$f2");
    register float vy REG("$f0");
    register float vz REG("$f1");
    float *vp = vec;
    if (self == 0) {
        func_001AD768(D_0055A518, 0x300);
        func_00263FF0(D_0055A518, 0x300, D_0055A528);
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
    if (cb != 0) {
        volatile float *cp = (volatile float *)cb;
        vx = cp[2];
        vy = cp[0];
        vz = cp[1];
        *((char *)(&buf) + 0x50) = 1;
        *((float *)((char *)(&buf) + 0x60)) = vy;
        *((float *)((char *)(&buf) + 0x64)) = vz;
        *((float *)((char *)(&buf) + 0x68)) = vx;
    }
    func_00181960((int *)((char *)(&buf)));
}
