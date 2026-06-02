/* rotObject.c -- typed sdata / lit4 definitions for this TU.
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

extern unsigned char D_006335C8;
extern int D_006335CC;
extern int D_006335D0;
extern int D_006335D4;
extern int D_006335D8;
extern int D_006335DC;
extern const char D_006335E8[8];
extern unsigned int D_006335F0;
extern int D_006335F4;
extern int D_006335F8;

extern unsigned int D_00275890[20];
extern int          D_00275860[4];
extern int          D_00632010;
extern float        D_006313C8;

extern int  *func_0013A0F8(int handle, int size, char *file, int line);
extern int   func_00105278(void);
extern void  func_00104140(int v, int *self);
extern void  func_00104FC0(int x);
extern void  func_00105F00(int *out, int *src);
extern void  func_00118648(int *out, int v, unsigned int *src);
extern void  func_001182F0(int *out, int *in);
extern void  func_00105FA8(int v);
extern float func_0025E5D8(float a, float b);
extern void  func_00105F20(int a, int b);
extern void  func_0010ECB8(int *self);

/* String-pool rodata migrated from rotObject_data.c */
const char D_00619FC8[120] = "src/rotObject.c\000GetRotObjectHoldPoint\000\000\000\t%f, %f, %f\n\000\000\000\000MoveRotObjectWithHoldPoint\000\000\000\000\000\000GetRotObjectGlobalHoldGeometry\000";

#include "include_asm.h"
#include "ico/types.h"
#include "matching.h"
#include "regpin.h"

INCLUDE_ASM("asm/nonmatchings/src/rotObject", func_001E9F08);

INCLUDE_ASM("asm/nonmatchings/src/rotObject", func_001EA030);
