/* thread.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00632000"))) int D_00632000 = 0;
__attribute__((section(".sdata.0x006321B0"))) char D_006321B0[8] = { 0 };
__attribute__((section(".sdata.0x006321B8"))) const char D_006321B8[8] = "0";

__attribute__((section(".rodata.0x00557890"))) const char D_00557890[16] = "<THREAD_SP>....";
__attribute__((section(".rodata.0x005578A0"))) const char D_005578A0[16] = "<THREAD_SP_END>";
__attribute__((section(".rodata.0x005578D0"))) const char D_005578D0[16] = "ios/thread.c";

/* String rodata migrated from thread_data.c */
__attribute__((section(".rodata.0x005578B0"))) const char D_005578B0[32] = "thr:thread table over flow\n";
__attribute__((section(".rodata.0x005578E0"))) const char D_005578E0[32] = "thr:can't create thread\n";
__attribute__((section(".rodata.0x00557900"))) const char D_00557900[16] = "n_thread %d\n";
__attribute__((section(".rodata.0x00557910"))) const char D_00557910[24] = "thr:can't create stack\n";
__attribute__((section(".rodata.0x00557928"))) const char D_00557928[32] = "iosThreadDestroyMgr() in\n";
__attribute__((section(".rodata.0x00557948"))) const char D_00557948[16] = "1:n_thread %d\n";
__attribute__((section(".rodata.0x00557958"))) const char D_00557958[24] = "thr:id out of range\n";
__attribute__((section(".rodata.0x00557970"))) const char D_00557970[16] = "th:msg %d\n";
__attribute__((section(".rodata.0x00557980"))) const char D_00557980[24] = "th:thread joined\n";
__attribute__((section(".rodata.0x00557998"))) const char D_00557998[24] = "sem: can't create %d\n";
__attribute__((section(".rodata.0x005579B0"))) const char D_005579B0[24] = "sem: can't delete %d\n";
__attribute__((section(".rodata.0x005579C8"))) const char D_005579C8[24] = "sem: wait error? %d\n";
__attribute__((section(".rodata.0x005579E0"))) const char D_005579E0[24] = "sem: signal error? %d\n";
__attribute__((section(".rodata.0x005579F8"))) const char D_005579F8[24] = "sem: refer error? %d\n";
