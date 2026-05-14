/* s_init.c -- typed sdata / lit4 definitions for this TU.
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

__attribute__((section(".lit4.0x00630A9C"))) float D_00630A9C = 0.1f;
__attribute__((section(".lit4.0x00630AA0"))) float D_00630AA0 = 0.05f;
__attribute__((section(".lit4.0x00630AA4"))) float D_00630AA4 = -0.00277777785f;
__attribute__((section(".lit4.0x00630AA8"))) float D_00630AA8 = 3000.0f;
__attribute__((section(".lit4.0x00630AAC"))) float D_00630AAC = 0.1f;
__attribute__((section(".lit4.0x00630AB0"))) float D_00630AB0 = 10000.0f;
__attribute__((section(".lit4.0x00630AB4"))) float D_00630AB4 = 3000.0f;
__attribute__((section(".lit4.0x00630AB8"))) float D_00630AB8 = 0.1f;
__attribute__((section(".lit4.0x00630ABC"))) float D_00630ABC = 3000.0f;
__attribute__((section(".lit4.0x00630AC0"))) float D_00630AC0 = 0.1f;
__attribute__((section(".lit4.0x00630AC4"))) float D_00630AC4 = 0.0174532924f;
__attribute__((section(".lit4.0x00630AC8"))) float D_00630AC8 = 0.8f;
__attribute__((section(".lit4.0x00630ACC"))) float D_00630ACC = 0.8f;
__attribute__((section(".lit4.0x00630AD0"))) float D_00630AD0 = 5000.0f;
__attribute__((section(".lit4.0x00630AD4"))) float D_00630AD4 = -1.57079637f;
__attribute__((section(".lit4.0x00630AD8"))) float D_00630AD8 = 1.57079637f;
__attribute__((section(".lit4.0x00630ADC"))) float D_00630ADC = 12100.0f;
__attribute__((section(".lit4.0x00630AE0"))) float D_00630AE0 = 160000.0f;
__attribute__((section(".lit4.0x00630AE4"))) float D_00630AE4 = 0.3f;
__attribute__((section(".lit4.0x00630AE8"))) float D_00630AE8 = 0.2f;
__attribute__((section(".sdata.0x00631AEC"))) int D_00631AEC = 0;
__attribute__((section(".sdata.0x00632200"))) unsigned int D_00632200 = 0x00005010;
__attribute__((section(".sdata.0x00632204"))) unsigned int D_00632204 = 0x001D9020;
__attribute__((section(".sdata.0x00632208"))) unsigned int D_00632208 = 0x0000000A;
__attribute__((section(".sdata.0x0063220C"))) float D_0063220C = 1.0f;
__attribute__((section(".sdata.0x00632210"))) int D_00632210 = 0;
__attribute__((section(".sdata.0x00632214"))) int D_00632214 = 0;
__attribute__((section(".sdata.0x00632218"))) char D_00632218[8] = { 0 };
__attribute__((section(".sdata.0x00632220"))) unsigned int D_00632220 = 0x00000030;
__attribute__((section(".sdata.0x00632224"))) int D_00632224 = 0;
__attribute__((section(".sdata.0x00632228"))) int D_00632228 = 0x00000001;
__attribute__((section(".sdata.0x0063222C"))) int D_0063222C = 0x00000000;
__attribute__((section(".sdata.0x00632230"))) const char D_00632230[8] = ">";
__attribute__((section(".sdata.0x00632238"))) unsigned int D_00632238 = 0x00000020;
__attribute__((section(".sdata.0x0063223C"))) int D_0063223C = 0;
__attribute__((section(".sdata.0x00632240"))) int D_00632240 = 0;

__attribute__((section(".rodata.0x00557CC8"))) const char D_00557CC8[16] = "sound/s_init.c";
__attribute__((section(".rodata.0x00557D80"))) const char D_00557D80[16] = "center x";
__attribute__((section(".rodata.0x00557D90"))) const char D_00557D90[16] = "center y";
__attribute__((section(".rodata.0x00557DA0"))) const char D_00557DA0[16] = "volumeRate";
__attribute__((section(".rodata.0x00557DB0"))) const char D_00557DB0[24] = "max volume range";
__attribute__((section(".rodata.0x00557DC8"))) const char D_00557DC8[16] = "attenuator";
__attribute__((section(".rodata.0x00557DD8"))) const char D_00557DD8[16] = "volume length";
__attribute__((section(".rodata.0x00557DE8"))) const char D_00557DE8[16] = "max volume type";
__attribute__((section(".rodata.0x00557DF8"))) const char D_00557DF8[16] = "stereo rate";

/* String rodata migrated from s_init_data.c */
__attribute__((section(".rodata.0x00557C50"))) const char D_00557C50[24] = "Spu2DmaWriteEe2Iop\n";
__attribute__((section(".rodata.0x00557C68"))) const char D_00557C68[24] = "ee %x iop %x size %x\n";
__attribute__((section(".rodata.0x00557C80"))) const char D_00557C80[32] = "send SpuStEnv completed \n";
__attribute__((section(".rodata.0x00557CA0"))) const char D_00557CA0[16] = "SgInit()\n";
__attribute__((section(".rodata.0x00557CB0"))) const char D_00557CB0[24] = "SgSetTickMode()\n";
__attribute__((section(".rodata.0x00557CD8"))) const char D_00557CD8[24] = "\nCan't alloc heap \n";
__attribute__((section(".rodata.0x00557CF0"))) const char D_00557CF0[40] = "iop sound alloced 0x%x  size %d\n";
__attribute__((section(".rodata.0x00557D18"))) const char D_00557D18[16] = "se open\n";
__attribute__((section(".rodata.0x00557D28"))) const char D_00557D28[24] = "bgm request buff over\n";
__attribute__((section(".rodata.0x00557D40"))) const char D_00557D40[16] = "bgm not open\n";
__attribute__((section(".rodata.0x00557D50"))) const char D_00557D50[16] = "bgm play\n";
__attribute__((section(".rodata.0x00557D60"))) const char D_00557D60[32] = "soundBufAdpcmChAlloc over\n";
__attribute__((section(".rodata.0x00557E08"))) const char D_00557E08[24] = "req no %d %s %f\n";
__attribute__((section(".rodata.0x00557E20"))) const char D_00557E20[16] = "%s%8s = %d\n";
__attribute__((section(".rodata.0x00557E30"))) const char D_00557E30[16] = "%s%8s = %f\n";
__attribute__((section(".rodata.0x00557E50"))) const char D_00557E50[24] = "se request buff over\n";
__attribute__((section(".rodata.0x00557E68"))) const char D_00557E68[16] = "se not open\n";
__attribute__((section(".rodata.0x00557E78"))) const char D_00557E78[16] = "num %d %d\n";
__attribute__((section(".rodata.0x00557E88"))) const char D_00557E88[24] = "sound manager in\n";
__attribute__((section(".rodata.0x00557EA0"))) const char D_00557EA0[16] = "IosSndLock %d\n";
__attribute__((section(".rodata.0x00557EB0"))) const char D_00557EB0[32] = "SOUND MANAGER START\n";
__attribute__((section(".rodata.0x00557ED0"))) const char D_00557ED0[16] = "with mail\n";
