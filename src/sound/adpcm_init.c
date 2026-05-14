/* adpcm_init.c -- typed sdata / lit4 definitions for this TU.
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
 */

__attribute__((section(".sdata.0x006321E8"))) int D_006321E8 = 0x00000001;
__attribute__((section(".sdata.0x006321EC"))) int D_006321EC = 0x00000000;
__attribute__((section(".sdata.0x006321F0"))) const char D_006321F0[8] = "0";
__attribute__((section(".sdata.0x006321F8"))) const char D_006321F8[8] = "%s\n";

__attribute__((section(".rodata.0x00557B78"))) const char D_00557B78[24] = "sound/adpcm_init.c";

/* String rodata migrated from adpcm_init_data.c */
__attribute__((section(".rodata.0x00557B90"))) const char D_00557B90[32] = "AdpcmIopBuffAlloc not alloc\n";
__attribute__((section(".rodata.0x00557BF8"))) const char D_00557BF8[16] = "AdpcmPlay\n";
__attribute__((section(".rodata.0x00557C08"))) const char D_00557C08[24] = "AdpcmOpen id%d \n";
__attribute__((section(".rodata.0x00557C20"))) const char D_00557C20[16] = "AdpcmOpensync\n";
__attribute__((section(".rodata.0x00557C30"))) const char D_00557C30[32] = "AdpcmOpensync done\n";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "IOP領域が確保されているのにもかかわらず,使われていなので解放します
" */
__attribute__((section(".rodata.0x00557BB0"))) const char D_00557BB0[72] = "IOP\316\316\260\350\244\254\263\316\312\335\244\265\244\354\244\306\244\244\244\353\244\316\244\313\244\342\244\253\244\253\244\357\244\351\244\272,\273\310\244\357\244\354\244\306\244\244\244\312\244\316\244\307\262\362\312\374\244\267\244\336\244\271\n";
