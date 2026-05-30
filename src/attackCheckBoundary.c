/* attackCheckBoundary.c -- typed sdata / lit4 definitions for this TU.
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
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */


float D_004BEF80[4] = { 0.0f, -20.0f, 2.0f, 0.0f };

/* Float rodata migrated from attackCheckBoundary_data.c */
const char D_006185E8[32] = "src/attackCheckBoundary.c";

/* Float rodata migrated from attackCheckBoundary_data.c */
/* EUC-JP: " - 剣で切られた\n" */
const char D_00618608[24] = " - \267\365\244\307\300\332\244\351\244\354\244\277\n";

/* Float rodata migrated from attackCheckBoundary_data.c */
/* EUC-JP: " - きれない\n" */
const char D_00618620[16] = " - \244\255\244\354\244\312\244\244\n";

/* Float rodata migrated from attackCheckBoundary_data.c */
const float D_0061E730[6] = { 0.0f, -8e+01f, 15.0f, 0.0f, 1.8e+02f, 0.0f };

/* Inlined data (Phase 3e) — migrated from attackCheckBoundary_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
float D_00631134 = 0.05f;
float D_00631138 = 10000.0f;
float D_0063113C = 10000.0f;

#include "include_asm.h"
#include "ico/types.h"
#include "regpin.h"

extern int func_001BA6B0(int a0, int a1);

int func_001BB860(int a0)
{
    return func_001BA6B0(a0, 0) ? 0 : -1;
}

int func_001BB888(int a0)
{
    return func_001BA6B0(a0, 0) ? 0 : -1;
}

void func_001BB8B0(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BB8C0);
INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BB988);
INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BBB20);

typedef struct { void *sub; int field4; } BBDD8Entry;

int func_001BBDD8(void *obj)
{
    register void *temp1 REG("$3");
    register int *t1 REG("$9");
    register int count REG("$2");
    register int i REG("$8");
    register BBDD8Entry *entries REG("$10");
    register int const_one REG("$7");
    register BBDD8Entry *e REG("$5");
    register void *sub REG("$6");
    int saved;
    int *inner;
    int *inner2;
    temp1 = ((GObj *)((char *)obj))->p_15C;
    t1 = ((Sub15C *)((char *)temp1))->p_800;
    count = *t1;
    if (count > 0) {
        i = 0;
        entries = *(BBDD8Entry **)((char *)t1 + 0xC);
        do {
            e = (BBDD8Entry *)(i << 3);
            const_one = 1;
            e = (BBDD8Entry *)((long)e + (long)entries);
            i += 1;
            sub = e->sub;
            inner = (int *)((volatile Sub15C *)((volatile GObj *)sub)->p_15C)->p_800;
            e->field4 = inner[1];
            __asm__ __volatile__("" ::: "memory");
            inner2 = (int *)((volatile Sub15C *)((volatile GObj *)sub)->p_15C)->p_800;
            inner2[1] = 0;
            ((GObj *)sub)->f_16C = const_one;
            count = *t1;
        } while (i < count);
    }
    saved = t1[1];
    t1[1] = 0;
    t1[2] = saved;
    return saved;
}

void func_001BBE48(void) {}


extern int D_00632010;
extern int func_0013A0F8(int handle, int size, char *file, int line);
int func_001BBE50(int unused, void *obj)
{
  int buf = func_0013A0F8(D_00632010, 0xC, D_006185E8, 0x1B);
  int *p = *((int **) (((char *) obj) + 0x30));
  int new_var4;
  int *new_var2;
  int *new_var3;
  int new_var;
  new_var2 = p;
 do { new_var4 = (int) p; ; } while (0);
  *((int *) (buf + 4)) = 0;
  new_var3 = (int *) buf;
  *new_var2 = 0;
  *new_var3 = new_var4;
  *((int *) (buf + 8)) = 0;
  return buf;
}

void func_001BBEA0(int *a0)
{
    int *p = (int *)((GObj *)(a0))->p_15C;
    int *q = (int *)p[0];
    if (q == 0) {
        return;
    }
    if (q[0x16C / 4] == 0) {
        a0[0x16C / 4] = 0;
    }
}
