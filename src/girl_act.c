/* girl_act.c -- typed sdata / lit4 definitions for this TU.
 *
 * Generated initially by tools/decode_sdata_lit4_typed.py
 * from baserom/baseelf.elf. Each line is a developer
 * reconstruction of one game variable or constant; the
 * file is tracked because the typed forms (named float
 * constants, string literals, single hex-word declarations)
 * are clean-room rather than raw byte arrays.
 *
 * As the TU gets fully decompiled, function definitions
 * land in this same file (per-TU layout); typed
 * data declarations stay here next to their references.
 */

/* __FILE__ anchor + neighboring debug strings — migrated out of
 * src/girl_brain_attract.c's D_00559770[96] packed blob. */
const char D_00559780[16] = "src/girl_act.c";
const char D_00559790[16] = "NOTARGET";
const char D_005597A0[24] = "[%s] %4d %4d %4d";
const char D_005597B8[24] = "delete wg 2\n";

/* Inlined data (Phase 3e) — migrated from girl_act_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* numeric word tables */
unsigned int D_00632520[2] = { 0x80808080, 0x00000000 };
unsigned int D_00632528[8] = { 0x00000030, 0x00000000, 0x0064253E, 0x00000000, 0x00642520, 0x00000000, 0x0000000A, 0x00000000 };

#include "include_asm.h"
#include "matching.h"

extern void func_0014A3A8(unsigned int a0);
extern void func_001A6E28(char *a0);
extern void func_0013B8F0(int a0);
extern void func_00201DC8(unsigned int a0);
extern void func_00203AA0(int a0);
extern void func_00132B90(int a0, int a1, int a2);
extern int  func_00133500(int a0, int a1);
extern char D_005598F0[];
extern char D_00559AE8[];

INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00175DC0);

int func_00175F60(int a0, int a1)
{
    float diff = *(float *)(a0 + 0x20) - *(float *)(a1 + 0x20);
    return (int)diff;
}

/* func_00175F7C is a 4-byte nop pad absorbed into func_00175F80's .s. */
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00175F80);

void func_001760F0(unsigned int a0)
{
  volatile unsigned int local = a0;
 do { func_0014A3A8(a0); func_001A6E28(D_005598F0); func_0013B8F0(7); func_00201DC8(local); } while (0);
}

void func_00176130(char *p) {
    int local;
    char *q;
    char *sub;
    *(volatile int *)&local = (int)p;
    q = (char *)*(volatile int *)&local;
    sub = *(char **)(q + 0x15C);
    *(int *)(sub + 0x634) = 0;
}

/* func_0017614C is a 4-byte nop pad absorbed into func_00176130's matching .s. */

void func_00176150(volatile unsigned int a0)
{
  volatile int local;
  int *new_var;
  int *s0;
  new_var = *((int **) (a0 + 0x164));
  func_001A6E28(D_00559AE8);
  s0 = new_var;
  s0[0x30 / 4] = 0x4;
  func_00203AA0(0);
}

/* func_00176194 is a 4-byte nop pad absorbed into func_00176198's .s. */
void func_00176198(int a0)
{
    int s;
    DEFEAT_TCO();
    s = a0;
    __asm__ volatile("" : : "r"(&s), "r"(s) : "memory");
    NOP();
    func_0014A3A8(a0);
    DEFEAT_TCO();
}
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001761B8);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00176200);

void func_00176398(int self, int a1, int size)
{
    int large = size + 0x7FE;
    int v1 = size - 1;
    int neg_one = -1;
    if (neg_one < v1) large = v1;
    large = ((large >> 11) + 1) << 11;
    func_00132B90(self, a1, large);
    func_00133500(self, *(int *)((char *)self + 0x110) + size);
}

/* func_001763F4 is a 4-byte nop pad absorbed into func_001763F8's .s. */
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_001763F8);
INCLUDE_ASM("asm/nonmatchings/src/girl_act", func_00176600);
