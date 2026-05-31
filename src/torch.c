/* src/torch.c — __FILE__ anchor at .rodata 0x0061A6E8 */

const char D_0061A6E8[16] = "src/torch.c";

/* Float rodata migrated from torch_data.c */
/* EUC-JP: "点火の例外処理発生\n" */
const char D_0061A6F8[24] = "\305\300\262\320\244\316\316\343\263\260\275\350\315\375\310\257\300\270\n";

/* Float rodata migrated from torch_data.c */
/* EUC-JP: "    第%dポイントの第%d候補は箱と重なっています。次の候補をチェックします\n" */
const char D_0061A710[80] = "    \302\350%d\245\335\245\244\245\363\245\310\244\316\302\350%d\270\365\312\344\244\317\310\242\244\310\275\305\244\312\244\303\244\306\244\244\244\336\244\271\241\243\274\241\244\316\270\365\312\344\244\362\245\301\245\247\245\303\245\257\244\267\244\336\244\271\n";

/* Float rodata migrated from torch_data.c */
/* EUC-JP: "決定: 第%dポイント 第%d候補 %f, %f, %f\n" */
const char D_0061A760[48] = "\267\350\304\352: \302\350%d\245\335\245\244\245\363\245\310 \302\350%d\270\365\312\344 %f, %f, %f\n";

/* Float rodata migrated from torch_data.c */
const float D_0061A790[48] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1e+01f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

#include "matching.h"
/* Inlined data (Phase 3e) — migrated from torch_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
unsigned int D_0061A870[4] = { 0x00000080, 0x00000080, 0x00000080, 0x00000080 };

/* strings */
const char D_0061AB50[56] = "\000@\001\000\0008\000\000\000x\000\000\000\020\000\000\000@\000\000\000\300\000\000\000\240\000\000\0000\000\000\000h\000\000\0008\000\000\000\020\000\000\000\200\000\000\000\200\001";

/* strings */
unsigned int D_00632024 = 0x00000000;

#include "include_asm.h"
#include "ico/types.h"
#include "regpin.h"

extern void func_00104508(int *buf, int *p);
extern void func_00243AE8(int *p, int *buf, int *q);
extern void func_00105F00(int *dst, int *src);
extern int func_00240EA0(int a, int b, int c, int d, int e, int f, int g);
extern void func_001F2370(void);
extern int D_00633748;
extern void func_001F2320(void);
extern int *func_00203B40(void (*fn)(void), int x);

INCLUDE_ASM("asm/nonmatchings/src/torch", func_001F1868);
INCLUDE_ASM("asm/nonmatchings/src/torch", func_001F19F0);
INCLUDE_ASM("asm/nonmatchings/src/torch", func_001F1AD8);
INCLUDE_ASM("asm/nonmatchings/src/torch", func_001F1B98);
INCLUDE_ASM("asm/nonmatchings/src/torch", func_001F1CF0);
INCLUDE_ASM("asm/nonmatchings/src/torch", func_001F2048);

void func_001F2140(void) {}

int func_001F2148(char *self_) {
    GObj *self = (GObj *)self_;
    Sub15C *sub = self->p_15C;
    Obj800 *p = sub->p_800;
    return p->f_4;
}

INCLUDE_ASM("asm/nonmatchings/src/torch", func_001F2158);

void func_001F2230(char *self_, int val) {
    GObj *self = (GObj *)self_;
    Sub15C *sub = self->p_15C;
    Obj800 *p = sub->p_800;
    p->f_C = val;
}

void func_001F2240(char *self_, int val) {
    GObj *self = (GObj *)self_;
    Sub15C *sub = self->p_15C;
    Obj800 *p = sub->p_800;
    p->f_10 = val;
}

void func_001F2250(int *self)
{
    int buf[4];
    Sub15C *p;
    func_00104508(buf, self);
    p = ((GObj *)self)->p_15C;
    func_00243AE8((int *)((char *)p + 0x130), buf, (int *)((char *)p + 0x1F0));
    p = ((GObj *)self)->p_15C;
    func_00105F00((int *)((char *)p + 0x1F0), buf);
}

int func_001F22A0(void) {
    int v = func_00240EA0(0, 0, 0, 0, (int)&func_001F2370, 0, 0);
    D_00633748 = v;
    return v;
}

INCLUDE_ASM("asm/nonmatchings/src/torch", func_001F22E0);
