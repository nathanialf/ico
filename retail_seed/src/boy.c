/* src/boy.c — TU body. 3 INCLUDE_ASM funcs.
 *
 * .lit4 and .sdata defs are intentionally NOT here — co-locating them with
 * INCLUDE_ASM consumers in the same .o forces ee-as to emit %hi/%lo (2 insn)
 * instead of the original %gp_rel (1 insn), cascading +4 bytes per ref into
 * a SHA mismatch (memory: lit4_gp_rel_extern). They live in the gitignored
 * boy_data.c sidecar (separate .o → boy.o sees them as extern). Promote
 * back here as a .h pair if needed for a typed-data .h split later.
 */

const char D_00618838[16] = "src/boy.c";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/boy", func_001C1380);
INCLUDE_ASM("asm/nonmatchings/src/boy", func_001C16A8);
INCLUDE_ASM("asm/nonmatchings/src/boy", func_001C1A98);
