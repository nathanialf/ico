/* pool.c -- typed sdata / lit4 definitions for this TU.
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


/* World bounding box: { min_x, min_y, max_x, max_y } in fixed-point
 * stage coordinates (-2048..+4096 covers the stage extent). */
float D_00276040[16] = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f };

float D_00276080[16] = { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

float D_002760C0[16] = { 0.707f, 0.707f, 0.0f, 0.0f, 0.707f, 0.707f, 0.0f, 0.0f, 0.707f, 0.707f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

float D_00276100[16] = { 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };

const int D_00553DD0[4] = { -2048, -2048, 4096, 4096 };

const char D_00553DE0[16] = "src/pool.c";

const float D_00553DF0[4] = { 2048.0f, 2048.0f, 0.0f, 0.0f };

const char D_00553E00[40] = "Quaternion stack not initialized.\n";

const char D_00553E28[32] = "Quaternion stack overflow!!\n";

const char D_00553E48[40] = "Quaternion stack underflow!!\n";

const char D_00553E90[32] = "display object = %d";

const char D_00553EB0[48] = "-------------------------------- read from CD\n";

const char D_00553EE0[24] = "initialize CD device.\n";

const char D_00553EF8[24] = "load default module.\n";

const char D_00553F10[24] = "cdrom0:\\IOPRP224.IMG;1";

const char D_00553F28[24] = "loading iop modules.\n";

const char D_00553F40[24] = "cdrom0:\\SIO2MAN.IRX;1";

const char D_00553F58[24] = "cdrom0:\\PADMAN.IRX;1";

const char D_00553F70[24] = "cdrom0:\\MCMAN.IRX;1";

const char D_00553F88[24] = "cdrom0:\\MCSERV.IRX;1";

const char D_00553FA0[24] = "cdrom0:\\LIBSD.IRX;1";

const char D_00553FB8[24] = "cdrom0:\\SNDN2DRV.IRX;1";

unsigned int D_00631B68 = 0x00000000;

unsigned int D_00631B6C = 0x00000000;

unsigned int D_00631B70[2] = { 0x80808080, 0x00000000 };

unsigned int D_00631B78 = 0x80FFFFFF;

unsigned int D_00631B7C = 0xFFFFFFFF;

/* Inlined data (Phase 3e) — migrated from pool_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
float D_00630998 = 0.1f;
float D_0063099C = 0.8f;
float D_006309A0 = 1.15f;
float D_006309A4 = 0.8f;
float D_006309A8 = 0.3f;
float D_006309AC = 0.005f;
float D_006309B0 = 0.01f;
float D_006309B4 = 0.01f;
float D_006309B8 = 0.05f;

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/pool", func_0010B2D0);
INCLUDE_ASM("asm/nonmatchings/src/pool", func_0010B770);
INCLUDE_ASM("asm/nonmatchings/src/pool", func_0010C0F0);
INCLUDE_ASM("asm/nonmatchings/src/pool", func_0010C5C0);
INCLUDE_ASM("asm/nonmatchings/src/pool", func_0010C6C0);
