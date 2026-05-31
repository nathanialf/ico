/* isys/gobj_process.c — __FILE__ anchor at .rodata 0x00557AD0
 *
 * TU range: [0x0013F700, 0x0013F778)  (next subseg: src/cod/03F778 at 0x0013F778)
 *
 * Single func:
 *   - func_0013F700: alloc count*0x94 GObjProcess pool, zero first int per slot.
 *     ptr pinned to $5 (a1) and stride pinned to $2 (v0) so gcc emits the
 *     original `mult3` per-iter index instead of strength-reducing to a
 *     pointer increment. Compiled with -fno-strength-reduce.
 */

#include "include_asm.h"
#include "matching.h"
#include "regpin.h"

const char D_00557AD0[24] = "isys/gobj_process.c";

const char D_00557AE8[40] = "isys:not enough memory for GObj\n";
const char D_00557B10[16] = "id %d %x %x \n";
const char D_00557B20[40] = "isys:not enough memory for GObjProcess\n";
const char D_00557B48[24] = "isys:null GObjProcess\n";

extern int   D_00632008;
extern int   D_00633CA8;
extern int   D_00633CAC;
extern int   func_0013A0F8(int a0, int a1, char *file, int line);
extern void  func_0013F3F0(int, int, int, unsigned char, int, int);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_process", func_0013F700);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_process", func_0013F778);
