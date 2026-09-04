/* func_001F3A28 — weapon.c — rc3 seed (debug circle: 16 segs, radius 30, sin/cos
 * via GetTableCos/func_0010E950). rc71->8 (frame/struct-align/FP-const/layout +
 * permuter do{}while(0) barrier), then 8->3 via `int angB=(int)angA+0x1000` (no
 * (short) re-trunc, angA-sourced). Residual 2 sites: angB addiu sources from
 * angA(s0) not i(s2)+i-fusion — gcc shares a shifted IV for any i-sourced
 * (short)(i+K); only angA-sourced avoids it. 78-stall hand loop (stall-limit 75)
 * + 1 permuter shot. ROM uses 2 independent sll/sra (cost-model divergence). */
#include "include_asm.h"
#include "ico/types.h"
#include "matching.h"
#include "regpin.h"

extern unsigned int D_004C6340[];
extern float D_004C6350[];
extern float D_004C6360[];
extern int func_00105278(void);
extern void func_00105F20(int a, int b);
extern void func_001118B8(int a);
extern void func_00112148(int a);
extern void func_00112188(int a);
extern void func_00111FA8(int a, int b, int c);
extern void func_001D4A58(void *a, void *b, void *c, void *d, int e);
extern float GetTableCos(short angle);
extern float func_0010E950(short angle);
extern void func_0010F630(void);

typedef struct { float x; int pad; float y; float w; } __attribute__((aligned(8))) DbgVtx;

void func_001F3A28(int *self)
{
    DbgVtx buf[3];
    int r;
    int i;
    r = func_00105278();
    func_00105F20(r, ((Sub15C *)((GObj *)self)->p_15C)->f_C);
    func_001118B8(0xB);
    func_00112148(1);
    func_00112188(1);
    func_00111FA8(1, 7, 0x80);
    func_001D4A58(D_004C6350, D_004C6340, D_004C6360, D_004C6340, 0);
    i = 0;
    do {
        short angA = (short)i;
        int angB = (int)angA + 0x1000;
        i += 0x1000;
        do { } while (0);
        buf[1].x = GetTableCos(angA) * 30.0f;
        buf[1].pad = 0;
        buf[1].y = func_0010E950(angA) * 30.0f + 130.0f;
        buf[1].w = 1.0f;
        buf[0] = buf[1];
        buf[2].x = GetTableCos(angB) * 30.0f;
        buf[2].pad = 0;
        buf[2].y = func_0010E950(angB) * 30.0f + 130.0f;
        buf[2].w = 1.0f;
        buf[1] = buf[2];
        func_001D4A58(&buf[0], D_004C6340, &buf[1], D_004C6340, 0);
    } while (i <= 0xFFFF);
    func_0010F630();
}
