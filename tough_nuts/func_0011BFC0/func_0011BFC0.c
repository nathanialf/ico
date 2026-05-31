/* src/Primitive.c — __FILE__ anchor at .rodata 0x00555490 */

#include "include_asm.h"

const char D_00555490[16] = "src/Primitive.c";
const char D_005554B0[32] = "too large mesh packet. %d\n";
const float D_005554E0[4] = { 1024.0f, 1024.0f, 0.0f, 1.0f };
const float D_005554F0[4] = { 3071.0f, 3071.0f, 0.0f, 16777215.0f };
const char D_00555500[72] = "Particle Object too big (%d particles). (must be under %d particles)\n";
const char D_00555548[48] = "prim_InitParticle:illegal texture no. %s:%d\n";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "prim_DispParticle:指定したテクスチャ番号が異常です. %s:%d\n" */
const char D_00555578[64] = "prim_DispParticle:\273\330\304\352\244\267\244\277\245\306\245\257\245\271\245\301\245\343\310\326\271\346\244\254\260\333\276\357\244\307\244\271. %s:%d\n";

extern int D_00633C50;
extern void func_00102558(int a0);

void func_0011BFB8(void) {
    D_00633C50 = 0;
}

extern void func_00118FD8(unsigned char *arg, int slot_size);
void func_0011BFC0(int a0, int count, int a2)
{
    unsigned char *p = (unsigned char *)(a0 * 16 + 0x1100C000);
    int i;
    if (count <= 0) {
        return;
    }
    i = count;
loop:
    {
        unsigned char *arg = p;
        p += 16;
        func_00118FD8(arg, a2);
    }
    if (--i != 0) goto loop;
}
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011C028);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011C2B8);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011C500);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011C868);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011CBF8);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011CE90);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011D2E8);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011D590);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011D658);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011D730);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011D800);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011D9A0);
INCLUDE_ASM("asm/nonmatchings/src/Primitive", func_0011DD08);

void func_0011DEE0(int a0)
{
    func_00102558(*(int *)(a0 + 0x18C));
    func_00102558(*(int *)(a0 + 0x188));
    func_00102558(a0);
}
