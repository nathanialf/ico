/* func_001F34C8 (src/weapon.c) — NEAR-MATCH seed, real_count 24 (match_diff).
 *
 * APPLY INTO src/weapon.c:
 *   - replace the INCLUDE_ASM line with this function;
 *   - the TU already declares struct E36, D_006124F8, D_004C6330, D_0061A850
 *     ABOVE this function -> DROP those externs from the seed;
 *   - add forward externs for D_00632010 / func_0013A0F8 / func_001B7FE8 /
 *     func_0019F4E8 / func_00105F00 (weapon.c declares some AFTER this func);
 *   - CHANGE the 3rd param to `WBody *arg1` (NOT int) — this is load-bearing
 *     (see notes.md: alias analysis); also change the later
 *     `extern void func_001F34C8(int*,int,int)` to `WBody*` and cast the call
 *     site `func_001F34C8(self, i, (WBody*)arg1)` in func_001F43D0.
 *     (func_001F43D0 still byte-matches at 0 after the cast — verified.)
 */
#include "matching.h"
#include "regpin.h"

extern volatile unsigned int D_00632010;   /* permuter-found: volatile pins gp load (16->15); apply to ALL D_00632010 decls in the TU */
extern int func_0013A0F8(int handle, int size, const char *file, int line);
extern int func_001B7FE8(int a, int b, int c, int d, int e, int f, int g, int h);
extern void func_0019F4E8(int *a0, int *a1);
extern void func_00105F00(int *arg, int b);
extern const char D_0061A850[16];
extern float D_004C6330[4];
struct E36 { char pad[0xC]; int field; char pad2[0x14]; };
extern struct E36 D_006124F8[];

typedef struct { long long d[8]; } WBody;
typedef struct __attribute__((packed)) { long long w; } WUB8;

void func_001F34C8(int *self, int i, WBody *arg1)
{
    struct {
        int *self;
        int i;
        int pad[2];
        WBody body;
    } req;
    WBody body2;
    WBody *src = arg1;
    int n;
    register int flag REG("$8");
    register int five REG("$6") = 5;
    register int ii REG("$15") = i;
    int *buf = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    long long new_var;   /* permuter-found: dead ll slot fixes self->$a0 coalescing (24->16) */
    int new_var2;        /* permuter-found: '1' tied live across loop (15->13) */
    float scale = 0.0f;

    flag = (((int *)src)[0x30 / 4] & 0xFF00) ? five : 4;

    req.self = self;
    req.i = ii;
    req.body = *src;
    *(volatile int *)&((int *)&req.body)[0x30 / 4] = flag;

    new_var2 = 1;
    buf[new_var = 0x50 / 4] = new_var2;
    buf[0x54 / 4] = func_0013A0F8(D_00632010, 4, D_0061A850, 0x2C7);

    for (n = 0; n < 1; n++) {
        int idx = buf[0];
        int *obj;
        D_004C6330[2] = ((float *)&D_006124F8[idx])[0] * (float)n / scale;
        obj = (int *)func_001B7FE8(0xA, 0x45, -1, n == 0, (int)&req.body, -new_var2, 7, 0);
        func_0019F4E8(obj, (int *)&req);
        func_00105F00((int *)(obj[0x15C / 4] + 0xA0), (int)D_004C6330);
        ((int *)buf[0x54 / 4])[n] = (int)obj;
    }

    body2 = *src;
    ((int *)&body2)[0x30 / 4] = 0xD;
    {
        int *obj2 = (int *)func_001B7FE8(0x2D, 9, -1, 0, (int)&body2, -1, 7, 0);
        *(WUB8 *)(obj2[0x15C / 4]) = *(WUB8 *)&req;
        buf[0x5C / 4] = (int)obj2;
    }
}
