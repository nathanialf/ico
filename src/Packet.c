/* Packet.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x00630A3C"))) float D_00630A3C = 0.99f;
__attribute__((section(".lit4.0x00630A40"))) float D_00630A40 = 16777215.0f;
__attribute__((section(".lit4.0x00630A44"))) float D_00630A44 = -16777215.0f;
__attribute__((section(".lit4.0x00630A48"))) float D_00630A48 = 0.5019608f;
__attribute__((section(".lit4.0x00630A4C"))) float D_00630A4C = 0.5019608f;
__attribute__((section(".lit4.0x00630A50"))) float D_00630A50 = 0.5019608f;
__attribute__((section(".sdata.0x00631CD0"))) char D_00631CD0[8] = { 0 };
__attribute__((section(".sdata.0x00631CD8"))) const char D_00631CD8[8] = "%02x";
__attribute__((section(".sdata.0x00631CE0"))) const char D_00631CE0[8] = " ";
__attribute__((section(".sdata.0x00631CE8"))) const char D_00631CE8[8] = "%12f ";
__attribute__((section(".sdata.0x00631CF0"))) const char D_00631CF0[8] = "\n";
__attribute__((section(".sdata.0x00631CF8"))) const char D_00631CF8[8] = "0";
__attribute__((section(".sdata.0x00631D00"))) const char D_00631D00[8] = " (%d)\n";
__attribute__((section(".sdata.0x00631D08"))) const char D_00631D08[8] = "e";
__attribute__((section(".sdata.0x00631D10"))) const char D_00631D10[8] = "%s";
__attribute__((section(".sdata.0x00631D18"))) const char D_00631D18[8] = "%s_l";
__attribute__((section(".sdata.0x00631D20"))) const char D_00631D20[8] = "%s_ref";
__attribute__((section(".sdata.0x00632D28"))) int D_00632D28 = 0;

__attribute__((section(".rodata.0x00554FD0"))) const char D_00554FD0[16] = "src/Packet.c";

__attribute__((section(".rodata.0x00555038"))) const char D_00555038[24] = "pac_makeNormalStrip";
__attribute__((section(".rodata.0x00555050"))) const char D_00555050[24] = "pac_getWeight(0)";
__attribute__((section(".rodata.0x00555068"))) const char D_00555068[24] = "pac_getWeight(1)";
__attribute__((section(".rodata.0x00555080"))) const char D_00555080[24] = "pac_getWeight(2)";
__attribute__((section(".rodata.0x00555138"))) const char D_00555138[24] = "pac_makeClusterStrip";
__attribute__((section(".rodata.0x005551E0"))) const char D_005551E0[16] = "GIFTAG    :";
__attribute__((section(".rodata.0x00555308"))) const char D_00555308[32] = "pac_countOneVertexPacketSize";

/* String rodata migrated from Packet_data.c */
__attribute__((section(".rodata.0x00554EE0"))) const char D_00554EE0[48] = "IN %s\n%s:NoTexture Polygon(s) exist(s).\n";
__attribute__((section(".rodata.0x00554F10"))) const char D_00554F10[48] = "IN %s\n%s:NoNormal Cluster Model exists.\n";
__attribute__((section(".rodata.0x00554F40"))) const char D_00554F40[48] = "IN %s\n%s:Abnormal Weight Data exist(s).\n";
__attribute__((section(".rodata.0x00554F70"))) const char D_00554F70[56] = "IN %s\n%s:Too Much Weight (>=4) Vertex exist(s).\n";
__attribute__((section(".rodata.0x00554FA8"))) const char D_00554FA8[40] = "IN %s\n%s:No Weight Vertex exist(s).\n";
__attribute__((section(".rodata.0x00555098"))) const char D_00555098[56] = "vertex has 3 cluster-weights %d(%f) %d(%f) %d(%f)\n";
__attribute__((section(".rodata.0x005550D0"))) const char D_005550D0[40] = "warning:weight total %f VtxIdx:%d\n";
__attribute__((section(".rodata.0x00555150"))) const char D_00555150[32] = "over 60 skeltons exist.\n";
__attribute__((section(".rodata.0x00555170"))) const char D_00555170[32] = "color table not exists.\n";
__attribute__((section(".rodata.0x00555190"))) const char D_00555190[16] = "DMAOPEN   :%p\n";
__attribute__((section(".rodata.0x005551A0"))) const char D_005551A0[32] = "VIFUNPACK :%08x %08x (%p:%d)\n";
__attribute__((section(".rodata.0x005551F0"))) const char D_005551F0[40] = "pac_continueTag:Packet too small. %d\n";
__attribute__((section(".rodata.0x00555218"))) const char D_00555218[40] = "Original Strip Too Long. Size %d\n";
__attribute__((section(".rodata.0x00555240"))) const char D_00555240[24] = "size(0x%x) strips(%d)\n";
__attribute__((section(".rodata.0x00555258"))) const char D_00555258[16] = "--- cut ---\n\n";
__attribute__((section(".rodata.0x00555268"))) const char D_00555268[56] = "gif over! cut! %d/%d polys:%d/%d fchain:%d vif+gif:%d\n";
__attribute__((section(".rodata.0x005552A0"))) const char D_005552A0[24] = "chain too long! cut!\n";
__attribute__((section(".rodata.0x005552B8"))) const char D_005552B8[48] = "pac_copyStrip:No Enough Memory for Packet.\n";
__attribute__((section(".rodata.0x005552E8"))) const char D_005552E8[32] = "ALL:src:%p => dst:%p (size:%x)\n";
__attribute__((section(".rodata.0x00555328"))) const char D_00555328[40] = "pac_makeStrip:No Memory To Convert.\n";
__attribute__((section(".rodata.0x00555350"))) const char D_00555350[40] = "pac_makeStrip:No Tex Poly Exists.%s\n";
__attribute__((section(".rodata.0x00555398"))) const char D_00555398[88] = "IN OBJECT \"%s\"\nHUGE PACKET (SIZE:0x%x) APPEARED\nMAYBE INFLATE MEMORY AREA WAS BROKEN.\n";
__attribute__((section(".rodata.0x005553F0"))) const char D_005553F0[48] = "pac_makeTextureTable:\n\tTexture not Found. %s\n";
__attribute__((section(".rodata.0x00555420"))) const char D_00555420[56] = "pac_makePacket:Material Table Not Found. (%s:%s)\n";
__attribute__((section(".rodata.0x00555458"))) const char D_00555458[24] = "illegal size = %d\n";
__attribute__((section(".rodata.0x00555470"))) const char D_00555470[32] = "illegal vertex num %d\n";
