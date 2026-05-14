/* PObj.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".sdata.0x00633BA8"))) const char D_00633BA8[8] = "%s";
__attribute__((section(".sdata.0x00633BB0"))) const char D_00633BB0[8] = "\x1b[m";
__attribute__((section(".sdata.0x00633BB8"))) const char D_00633BB8[8] = "OBJH";
__attribute__((section(".sdata.0x00633BC0"))) const char D_00633BC0[] = "FALSE";

__attribute__((section(".rodata.0x0062E010"))) const char D_0062E010[16] = "src/PObj.c";

__attribute__((section(".rodata.0x0062E0D8"))) const char D_0062E0D8[16] = "D1_TADR=%08x:";
__attribute__((section(".rodata.0x0062E0E8"))) const char D_0062E0E8[16] = "D1_MADR=%08x:";
__attribute__((section(".rodata.0x0062E118"))) const char D_0062E118[16] = "D2_TADR=%08x:";
__attribute__((section(".rodata.0x0062E128"))) const char D_0062E128[16] = "D2_MADR=%08x:";
__attribute__((section(".rodata.0x0062E5A0"))) const char D_0062E5A0[24] = "TTY: receive error";
__attribute__((section(".rodata.0x0062E658"))) const char D_0062E658[8] = "....";
__attribute__((section(".rodata.0x0062E660"))) const char D_0062E660[8] = "....";
__attribute__((section(".rodata.0x0062E668"))) const char D_0062E668[8] = "all";
__attribute__((section(".rodata.0x0062E670"))) const char D_0062E670[16] = "rom0:UDNL ";

/* String rodata migrated from PObj_data.c */
__attribute__((section(".rodata.0x0062DF60"))) const char D_0062DF60[32] = "            : object name (%s)\n";
__attribute__((section(".rodata.0x0062DFD0"))) const char D_0062DFD0[32] = "Solve object address. %p\n";
__attribute__((section(".rodata.0x0062DFF0"))) const char D_0062DFF0[32] = "allocPObj:Invalid Object.\n";
__attribute__((section(".rodata.0x0062E020"))) const char D_0062E020[16] = "free object\n";
__attribute__((section(".rodata.0x0062E030"))) const char D_0062E030[56] = "sceGsDefDispEnv:Not support displaymode for %d!!\n";
__attribute__((section(".rodata.0x0062E068"))) const char D_0062E068[48] = "sceGsPutDrawEnv: DMA Ch.2 does not terminate\r\n";
__attribute__((section(".rodata.0x0062E098"))) const char D_0062E098[48] = "sceGsSyncPath: DMA Ch.1 does not terminate\r\n";
__attribute__((section(".rodata.0x0062E0C8"))) const char D_0062E0C8[16] = "\t<D1_CHCR=%08x:";
__attribute__((section(".rodata.0x0062E0F8"))) const char D_0062E0F8[16] = "D1_QWC=%08x>\r\n";
__attribute__((section(".rodata.0x0062E108"))) const char D_0062E108[16] = "\t<D2_CHCR=%08x:";
__attribute__((section(".rodata.0x0062E138"))) const char D_0062E138[16] = "D2_QWC=%08x>\r\n";
__attribute__((section(".rodata.0x0062E148"))) const char D_0062E148[24] = "\t<VIF1_STAT=%08x:";
__attribute__((section(".rodata.0x0062E160"))) const char D_0062E160[24] = "GIF_STAT=%08x>\r\n";
__attribute__((section(".rodata.0x0062E178"))) const char D_0062E178[48] = "sceGsSyncPath: DMA Ch.2 does not terminate\r\n";
__attribute__((section(".rodata.0x0062E1A8"))) const char D_0062E1A8[48] = "sceGsSyncPath: VIF1 does not terminate\r\n";
__attribute__((section(".rodata.0x0062E1D8"))) const char D_0062E1D8[40] = "sceGsSyncPath: VU1 does not terminate\r\n";
__attribute__((section(".rodata.0x0062E200"))) const char D_0062E200[48] = "sceGsSyncPath: GIF does not terminate\r\n";
__attribute__((section(".rodata.0x0062E230"))) const char D_0062E230[48] = "sceGsSetDefLoadImage: too big size\r\n";
__attribute__((section(".rodata.0x0062E350"))) const char D_0062E350[64] = "sceGsExecLoadImage: DMA Ch.2 does not terminate\r\n";
__attribute__((section(".rodata.0x0062E390"))) const char D_0062E390[56] = "sceGsExecStoreImage: DMA Ch.1 does not terminate\r\n";
__attribute__((section(".rodata.0x0062E3C8"))) const char D_0062E3C8[48] = "sceGsExecStoreImage: GS does not terminate\r\n";
__attribute__((section(".rodata.0x0062E3F8"))) const char D_0062E3F8[64] = "sceGsExecStoreImage: DMA Ch.1 (GS->MEM) does not terminate\r\n";
__attribute__((section(".rodata.0x0062E438"))) const char D_0062E438[56] = "sceGsExecStoreImage: Enough data does not reach VIF1\n";
__attribute__((section(".rodata.0x0062E560"))) const char D_0062E560[24] = "libdma: sync timeout\n";
__attribute__((section(".rodata.0x0062E578"))) const char D_0062E578[40] = "TTY: packet size larger than expect\n";
__attribute__((section(".rodata.0x0062E5B8"))) const char D_0062E5B8[24] = "TTY: send err %d\n";
__attribute__((section(".rodata.0x0062E5D0"))) const char D_0062E5D0[32] = "TTY: err ti->wlen=%08x\n";
__attribute__((section(".rodata.0x0062E680"))) const char D_0062E680[32] = "too long parameter '%s'\n";
__attribute__((section(".rodata.0x0062E6A0"))) const char D_0062E6A0[64] = "=========================<wired=%02d>=========================\n";
__attribute__((section(".rodata.0x0062E6E0"))) const char D_0062E6E0[48] = "idx=%02d: pm=%08x, hi=%08x, lo0=%08x, lo1=%08x\n";
__attribute__((section(".rodata.0x0062E710"))) const char D_0062E710[40] = "sceCdCbfunc= %d sceCdCbfunc_num= %d\n";
__attribute__((section(".rodata.0x0062E738"))) const char D_0062E738[32] = "Libcdvd bind err PowerOffCB\n";
__attribute__((section(".rodata.0x0062E758"))) const char D_0062E758[32] = "Libcdvd bind err CdSearchFile\n";
__attribute__((section(".rodata.0x0062E778"))) const char D_0062E778[24] = "ee call cmd search %s\n";
__attribute__((section(".rodata.0x0062E790"))) const char D_0062E790[16] = "search name %s\n";
__attribute__((section(".rodata.0x0062E7A0"))) const char D_0062E7A0[16] = "search size %d\n";
__attribute__((section(".rodata.0x0062E7B0"))) const char D_0062E7B0[24] = "search loc lbn %d\n";
__attribute__((section(".rodata.0x0062E7C8"))) const char D_0062E7C8[40] = "Ncmd fail sema cur_cmd:%d keep_cmd:%d\n";
__attribute__((section(".rodata.0x0062E7F0"))) const char D_0062E7F0[24] = "Libcdvd bind err N CMD\n";
__attribute__((section(".rodata.0x0062E808"))) const char D_0062E808[16] = "N cmd wait\n";
__attribute__((section(".rodata.0x0062E818"))) const char D_0062E818[16] = "S cmd wait\n";
__attribute__((section(".rodata.0x0062E828"))) const char D_0062E828[40] = "Scmd fail sema cur_cmd:%d keep_cmd:%d\n";
__attribute__((section(".rodata.0x0062E850"))) const char D_0062E850[24] = "Libcdvd bind err S cmd\n";
__attribute__((section(".rodata.0x0062E868"))) const char D_0062E868[32] = "Libcdvd bind err %d CD_Init %d\n";
__attribute__((section(".rodata.0x0062E888"))) const char D_0062E888[16] = "Libcdvd Exit\n";
__attribute__((section(".rodata.0x0062E898"))) const char D_0062E898[16] = "DiskReady 0\n";
__attribute__((section(".rodata.0x0062E8A8"))) const char D_0062E8A8[32] = "Libcdvd bind err CdDiskReady\n";
__attribute__((section(".rodata.0x0062E8C8"))) const char D_0062E8C8[24] = "DiskReady ended\n";
__attribute__((section(".rodata.0x0062E8E0"))) const char D_0062E8E0[24] = "call cdread cmd\n";
__attribute__((section(".rodata.0x0062E8F8"))) const char D_0062E8F8[16] = "cdread end\n";
__attribute__((section(".rodata.0x0062E908"))) const char D_0062E908[16] = "cdread end\n";
__attribute__((section(".rodata.0x0062E918"))) const char D_0062E918[16] = "status called\n";
__attribute__((section(".rodata.0x0062E928"))) const char D_0062E928[48] = "sceCdStRead call read size= %d mode= %d\n";
__attribute__((section(".rodata.0x0062E958"))) const char D_0062E958[72] = "sceCdStRead BLK Read cur_size= %d read_size= %d req_size= %d err 0x%x\n";
__attribute__((section(".rodata.0x0062E9A0"))) const char D_0062E9A0[32] = "sceCdStRead BLK Read Ended\n";
__attribute__((section(".rodata.0x0062E9C0"))) const char D_0062E9C0[24] = "sceCdStPause call\n";
__attribute__((section(".rodata.0x0062E9D8"))) const char D_0062E9D8[24] = "sceCdStResume call\n";
__attribute__((section(".rodata.0x0062E9F0"))) const char D_0062E9F0[24] = "sceCdStStat call\n";
__attribute__((section(".rodata.0x0062EA08"))) const char D_0062EA08[24] = "call cdreadstm call\n";
__attribute__((section(".rodata.0x0062EA20"))) const char D_0062EA20[24] = "call cdreadstm cmd\n";
__attribute__((section(".rodata.0x0062EA38"))) const char D_0062EA38[16] = "cdread end\n";
__attribute__((section(".rodata.0x0062EAB8"))) const char D_0062EAB8[40] = "[libpad.a = %d.%d, padman.irx = %d.%d]\n";
__attribute__((section(".rodata.0x0062EAE0"))) const char D_0062EAE0[48] = "libpad: buffer addr is not 64 byte align. %08x\n";
__attribute__((section(".rodata.0x0062EB10"))) const char D_0062EB10[48] = "libpad: pad port is already open [%d][%d]\n";
__attribute__((section(".rodata.0x0062EBA0"))) const char D_0062EBA0[24] = "bind error libmc \n";
__attribute__((section(".rodata.0x0062EBB8"))) const char D_0062EBB8[40] = "libmc: too old release of mcserv.irx\n";
__attribute__((section(".rodata.0x0062EBE0"))) const char D_0062EBE0[40] = "libmc: too old release of mcman.irx\n";
__attribute__((section(".rodata.0x0062EC08"))) const char D_0062EC08[56] = "pack_header_field_flag needs to be '0' in PS\n";
__attribute__((section(".rodata.0x0062ED08"))) const char D_0062ED08[16] = "[MPEG ERROR]%s\n";
__attribute__((section(".rodata.0x0062F098"))) const char D_0062F098[48] = "Too small buffer size for %dx%d picture\n";
__attribute__((section(".rodata.0x0062F0C8"))) const char D_0062F0C8[24] = "CSC handler error\n";
__attribute__((section(".rodata.0x0062FC48"))) const char D_0062FC48[49] = "assertion \"%s\" failed: file \"%s\", line %d\n";

/* Float rodata migrated from PObj_data.c */
__attribute__((section(".rodata.0x0062F7E0"))) const float D_0062F7E0[3] = { 0.4636476f, 0.7853981f, 0.9827937f };
__attribute__((section(".rodata.0x0062F7F0"))) const float D_0062F7F0[3] = { 5.0121582e-09f, 3.7748947e-08f, 3.4473217e-08f };

/* Single-float rodata migrated from PObj_data.c */
__attribute__((section(".rodata.0x0062F7EC"))) const float D_0062F7EC = 1.5707963f;
__attribute__((section(".rodata.0x0062F7FC"))) const float D_0062F7FC = 7.5497894e-08f;

/* String-pool rodata migrated from PObj_data.c */
__attribute__((section(".rodata.0x0062EA48"))) const char D_0062EA48[72] = "libpad: sceSifSetDma faild\n\000\000\000\000\000libpad: tPadDma Structure Invalid\n\000\000\000\000\000";
