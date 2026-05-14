/* DmaPacket.c -- typed sdata / lit4 definitions for this TU.
 *
 * Generated initially by tools/decode_sdata_lit4_typed.py
 * from baserom/baseelf.elf. Each line is a developer
 * reconstruction of one game variable or constant; the
 * file is tracked because the typed forms (named float
 * constants, string literals, single hex-word declarations)
 * are clean-room rather than raw byte arrays.
 *
 * As the TU gets fully decompiled, function definitions
 * land in this same file (parappa2-style layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 *
 * REVISIT: this TU's sole function (func_001FBB48) is matched but
 * NOT coalesced into this file. Coalescing fails the SHA-1 gate
 * because the function references D_00632014 (sdata) — and ee-gcc
 * 2.9's small-data heuristic only emits %gp_rel when the function's
 * TU sees the symbol as `extern`. Putting the typed `.sdata.0xVMA`
 * def in the same TU as the function flips ee-gcc to %hi/%lo, which
 * doesn't match the original ELF.
 *
 * Workaround paths to consider next time:
 *   (A) Sibling tracked .c file holding only the sdata def (separate .o,
 *       function's TU sees only `extern` -> %gp_rel preserved).
 *   (B) Migrate to per-TU `.sdata` subsegments in config/ico.us.yaml
 *       (parappa2 style). Requires linker-script and rewriter changes
 *       to drop SORT_BY_NAME(.sdata.0x*) in favor of YAML-ordered
 *       concatenation — coordinated refactor across all sdata TUs.
 *
 * For now: function lives at src/cod/0FBB48.c and references
 * D_00632014 / D_0061AC60 via local externs; this file remains
 * data-only.
 */

__attribute__((section(".sdata.0x00632014"))) int D_00632014 = 0;

__attribute__((section(".rodata.0x0061AC60"))) const char D_0061AC60[16] = "src/DmaPacket.c";
