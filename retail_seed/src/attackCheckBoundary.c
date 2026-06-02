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

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BBDD8);

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


/* === BEGIN recovered struct shapes (tools/place_struct_shapes.py) === */
/* Field layouts mined from load/store access patterns; SPARSE
 * (only touched offsets, no padding). Unused typedefs — they add
 * no symbol and cannot affect codegen. Cast as ((S_<VMA> *)D_<VMA>).
 */

typedef struct {
    unsigned int     f_0;  /* 0x0  x2 */
} S_bl_006186E0;  /* stride 0x4, 2 accesses */

typedef struct {
    unsigned int     f_0;  /* 0x0  x2 */
} S_bl_00618720;  /* stride 0x4, 2 accesses */

/* === END recovered struct shapes === */
