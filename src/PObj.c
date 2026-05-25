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

/* KEEP_DEF: auto-gen sidecar truncates the trailing 'E' (emits
 * "FALS\0\0" instead of "FALSE\0"); keep the typed def so the .o
 * owns the correct bytes. The KEEP_DEF marker tells
 * tools/extern_sdata_lit4.py to skip this line on subsequent sweeps. */
unsigned int D_0027470C = 0x30343232;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00274710[464] = { 0x3C028007, 0x0000282D, 0x24436710, 0x00000000, 0x8C620000, 0x14820003, 0x24A50001, 0x03E00008, 0x8C620004, 0x2CA20006, 0x1440FFF9, 0x24630008, 0x03E00008, 0x0000102D, 0x00A4202A, 0x10800003, 0x3C020001, 0x03E00008, 0x00A21025, 0x03E00008, 0x00A0102D, 0x00000000, 0x27BDFF80, 0xFFB30030, 0x3C138007, 0xFFB60060, 0xFFB50050, 0x0080B02D, 0xFFB00000, 0x00A0A82D, 0x8E626700, 0x0000802D, 0xFFBF0070, 0xFFB40040, 0xFFB20020, 0x18400028, 0xFFB10010, 0x3C148007, 0x24120014, 0x00000000, 0x26916740, 0x02121018, 0x02C0202D, 0x00511021, 0x0C01D80E, 0x94450000, 0x02A2102A, 0x10400018, 0x8E626700, 0x2444FFFF, 0x0090182A, 0x14600018, 0x00921018, 0x00511821, 0x68650007, 0x6C650000, 0x6866000F, 0x6C660008, 0x8C670010, 0xB065001B, 0xB4650014, 0xB0660023, 0xB466001C, 0xAC670024, 0x2484FFFF, 0x2463FFEC, 0x0090102A, 0x00000000, 0x1040FFF1, 0x00000000, 0x10000006, 0x0200102D, 0x26100001, 0x0202102A, 0x1440FFDD, 0x24120014, 0x0200102D, 0xDFBF0070, 0xDFB60060, 0xDFB50050, 0xDFB40040, 0xDFB30030, 0xDFB20020, 0xDFB10010, 0xDFB00000, 0x03E00008, 0x27BD0080, 0x00000000, 0x27BDFF70, 0x3C02B000, 0xFFB70070, 0x34421800, 0xFFB60060, 0x00C0B82D, 0xFFB50050, 0x00A0B02D, 0xFFB30030, 0x3C158007, 0xFFBF0080, 0x3093FFFF, 0xFFB20020, 0xFFB10010, 0xFFB00000, 0xFFB40040, 0x8EA36700, 0x8C540000, 0x28630040, 0x14600008, 0x02749821, 0x1000002E, 0x2402FFFF, 0x0060902D, 0x00621014, 0x00821025, 0x1000000D, 0xFCA26708, 0x3C058007, 0x0000182D, 0xDCA46708, 0x00641016, 0x30420001, 0x1040FFF5, 0x24020001, 0x24630001, 0x28620040, 0x1440FFFA, 0x00641016, 0x2412FFFF, 0x0640001B, 0x0240102D, 0x0380882D, 0x0260282D, 0x0C01D816, 0x0280202D, 0x24040014, 0x3C088007, 0x00441018, 0x25036740, 0x8EA56700, 0x24700004, 0x24A50001, 0x00432021, 0x00623821, 0x00508021, 0xA4940002, 0xA4930000, 0x00E0302D, 0xAE120000, 0x00C0182D, 0xACF10010, 0x95046740, 0xACD60008, 0xAC77000C, 0x0C01D918, 0xAEA56700, 0x8E020000, 0xDFBF0080, 0xDFB70070, 0xDFB60060, 0xDFB50050, 0xDFB40040, 0xDFB30030, 0xDFB20020, 0xDFB10010, 0xDFB00000, 0x03E00008, 0x27BD0090, 0x00000000, 0x27BDFFD0, 0x3C0C8007, 0xFFB10010, 0x0080682D, 0x8D826700, 0x0180882D, 0xFFBF0020, 0x2406FFFF, 0x18400058, 0xFFB00000, 0x18400056, 0x0000402D, 0x3C0B8007, 0x24030014, 0x25656740, 0x01032018, 0x00A41021, 0x8C430004, 0x15A3004A, 0x8D826700, 0x3C03B000, 0x00852021, 0x34631820, 0x94850000, 0x8C620000, 0x14A20008, 0x24030014, 0x3C021000, 0x3442F000, 0x8C430000, 0x30631000, 0x14600043, 0x2402FFFF, 0x24030014, 0x8D896700, 0x01031818, 0x25646740, 0x2522FFFF, 0x0100382D, 0x0102102A, 0x00641821, 0x10400019, 0x94700002, 0x3C0A8007, 0x24E30001, 0x24050014, 0x00651018, 0x00E52018, 0x25666740, 0x0060382D, 0x00462821, 0x00862021, 0x2522FFFF, 0x68A30007, 0x6CA30000, 0x68A6000F, 0x6CA60008, 0x8CAE0010, 0xB0830007, 0xB4830000, 0xB086000F, 0xB4860008, 0x00E2102A, 0x1440FFEC, 0xAC8E0010, 0x10000003, 0x24020001, 0x3C0A8007, 0x24020001, 0x8D846700, 0xDD436708, 0x01A21014, 0x00021027, 0x2484FFFF, 0x00621824, 0xAD846700, 0x15000003, 0xFD436708, 0x0C01D918, 0x95646740, 0x8E226700, 0x14400004, 0x24030083, 0x3C02B000, 0x34421810, 0xAC430000, 0x3C02B000, 0x0200202D, 0x34421800, 0x0C01D80E, 0x8C450000, 0x10000005, 0x00503023, 0x25080001, 0x0102102A, 0x1440FFAE, 0x24030014, 0x0000000F, 0x00C0102D, 0xDFBF0020, 0xDFB10010, 0xDFB00000, 0x03E00008, 0x27BD0030, 0x27BDFFF0, 0xFFBF0000, 0x0C01D858, 0x3084FFFF, 0x0000000F, 0xDFBF0000, 0x03E00008, 0x27BD0010, 0x3C02B000, 0x34421820, 0xAC440000, 0x0000000F, 0x3C02B000, 0x24030583, 0x34421810, 0x03E00008, 0xAC430000, 0x00000000, 0x27BDFF50, 0x0000402D, 0xFFBF00A0, 0xFFB70090, 0xFFB60080, 0xFFB50070, 0xFFB40060, 0xFFB30050, 0xFFB20040, 0xFFB10030, 0xFFB00020, 0x3C118007, 0x3C128007, 0x00000000, 0x8E226700, 0x0102102A, 0x1040000A, 0x24030014, 0x26446740, 0x01031818, 0x96456740, 0x00641821, 0x94620000, 0x10A2FFF6, 0x25080001, 0x0C01D918, 0x0040202D, 0x3C028007, 0x0220B02D, 0x24546740, 0x24130014, 0x3C158007, 0x10000004, 0x24170001, 0x96426740, 0x1462003E, 0x8E226700, 0x8EC26700, 0x0000402D, 0x26466740, 0x68C30007, 0x6CC30000, 0x68C4000F, 0x6CC40008, 0x8CC50010, 0xB3A30007, 0xB7A30000, 0xB3A4000F, 0xB7A40008, 0xAFA50010, 0x2442FFFF, 0x1840001A, 0xAEC26700, 0x8E296700, 0x8FAA0010, 0x8FA60004, 0x97A70000, 0x00000000, 0x01131818, 0x25020001, 0x0040402D, 0x00742821, 0x00531818, 0x00742021, 0x688B0007, 0x6C8B0000, 0x688C000F, 0x6C8C0008, 0x8C8D0010, 0xB0AB0007, 0xB4AB0000, 0xB0AC000F, 0xB4AC0008, 0x0109182A, 0x1460FFEF, 0xACAD0010, 0x10000004, 0x00000000, 0x8FAA0010, 0x8FA60004, 0x97A70000, 0x0380802D, 0x0140E02D, 0xDEA36708, 0x00D71014, 0x00021027, 0x3C040008, 0x00621824, 0x8FA50008, 0x8FA8000C, 0x34842000, 0x0C01D9A0, 0xFEA36708, 0x0200E02D, 0x8E226700, 0x1C40FFC2, 0x97A30000, 0x8E226700, 0x18400005, 0x24030483, 0x0C01D918, 0x96446740, 0x10000004, 0x00000000, 0x3C02B000, 0x34421810, 0xAC430000, 0x0000000F, 0x42000038, 0xDFBF00A0, 0xDFB70090, 0xDFB60080, 0xDFB50070, 0xDFB40060, 0xDFB30050, 0xDFB20040, 0xDFB10030, 0xDFB00020, 0x03E00008, 0x27BD00B0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3C1A8007, 0xAF5F6C40, 0x3C1A8007, 0xAF5D6C50, 0x40847000, 0x0000040F, 0x00A0182D, 0x00C0202D, 0x00E0282D, 0x0100302D, 0x401A6000, 0x375A0012, 0x409A6000, 0x0000040F, 0x42000018, 0x00000000, 0x40016000, 0x241AFFE4, 0x003A0824, 0x40816000, 0x0000040F, 0x3C1A8007, 0x8F5F6C40, 0x3C1A8007, 0x03E00008, 0x8F5D6C50, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000000FC, 0x80076440, 0x000000FE, 0x80076440, 0x000000FD, 0x800762A0, 0x000000FF, 0x800762A0, 0x0000012C, 0x80076488, 0x00000008, 0x800766C0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_00274E50[32] = "\010\000\035<\t\370`\000\300\037\275'\370\377\003$\014";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00274E70[16] = { 0x0000005A, 0x00100C48, 0x0000005B, 0x80076000, 0x000000FC, 0x00000000, 0x000000FE, 0x00000000, 0x000000FD, 0x00000000, 0x000000FF, 0x00000000, 0x0000012C, 0x00000000, 0x00000008, 0x00000000 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00274EB0 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00274EB4 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_004D4230[32] = { 0x656A626F, 0x732F7463, 0x622F6664, 0x6D2F796F, 0x6C65646F, 0x796F622F, 0x65646F6D, 0x32702E6C, 0x00000063, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x656A626F, 0x732F7463, 0x622F6664, 0x6D2F796F, 0x6C65646F, 0x6468732F, 0x646F6D77, 0x702E6C65, 0x00007332, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0053BA58[370] = { 0x00000001, 0x00000000, 0x00000036, 0x00020089, 0x00000000, 0xFFFFFFFF, 0x00020089, 0x00000000, 0x00000036, 0x00020089, 0x00000000, 0xFFFFFFFF, 0x000004CD, 0x00000000, 0x00000036, 0x000004F6, 0x00010412, 0x00000268, 0x0000052E, 0x00000000, 0x00000353, 0x000004F3, 0x00000000, 0x0000037A, 0x000004F3, 0x00000000, 0x000002AD, 0x00000533, 0x00000000, 0x00000137, 0x00000533, 0x00000000, 0x00000138, 0x00000489, 0x00000000, 0x00000511, 0x000004CD, 0x00000000, 0xFFFFFFFF, 0x000004CE, 0x000103F6, 0x00000036, 0x000004F9, 0x00010412, 0x00000268, 0x0000052E, 0x00000000, 0x00000353, 0x000004F3, 0x00000000, 0x0000037A, 0x000004F3, 0x00000000, 0x000002AD, 0x00000533, 0x00000000, 0x00000137, 0x00000533, 0x00000000, 0x00000138, 0x0000048A, 0x000103EF, 0x00000511, 0x000004CE, 0x000103F6, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000036, 0x000004F7, 0x00000000, 0x00000268, 0x0000052F, 0x00000000, 0x00000353, 0x000004F4, 0x00000000, 0x0000037A, 0x000004F4, 0x00000000, 0x000002AD, 0x00000000, 0x00000000, 0x00000511, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000506, 0x00000000, 0xFFFFFFFF, 0x000004CF, 0x00000000, 0x00000036, 0x00000508, 0x00000000, 0x00000268, 0x0000048B, 0x00000000, 0x00000511, 0x000004F5, 0x00000000, 0x0000037A, 0x000004F5, 0x00000000, 0x000002AD, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x000004D0, 0x00000000, 0xFFFFFFFF, 0x000200AB, 0x00000000, 0xFFFFFFFF, 0x00020093, 0x00000000, 0xFFFFFFFF, 0x0001043D, 0x00000000, 0x0000005C, 0x000004EA, 0x00000000, 0x00000079, 0x000200AB, 0x00000000, 0xFFFFFFFF, 0x0001043D, 0x00000000, 0x0000005C, 0x000004EA, 0x00000000, 0x00000079, 0x000004EA, 0x00000000, 0x00000248, 0x00020093, 0x00000000, 0xFFFFFFFF, 0x0000018D, 0x00000000, 0x0000005C, 0x0002009F, 0x00000000, 0xFFFFFFFF, 0x000001A4, 0x00000000, 0xFFFFFFFF, 0x000004ED, 0x00000000, 0xFFFFFFFF, 0x000004EA, 0x00000000, 0xFFFFFFFF, 0x00000523, 0x00000000, 0x000001C3, 0x00000520, 0x00000000, 0x0000037D, 0x0000051E, 0x00000000, 0x00000241, 0x00000531, 0x00000000, 0x00000245, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x000001C3, 0x00000521, 0x00000000, 0x0000037D, 0x00000000, 0x00000000, 0x00000241, 0x00000000, 0x00000000, 0x00000245, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x000004AF, 0x00000000, 0xFFFFFFFF, 0x000004B0, 0x00000000, 0xFFFFFFFF, 0x000001A4, 0x00000000, 0xFFFFFFFF, 0x00010441, 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x000200AD, 0x00000000, 0x00000045, 0x000200B7, 0x00000000, 0x00000047, 0x000200B7, 0x00000000, 0x00000049, 0x000200B7, 0x00000000, 0x00000048, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x000004EE, 0x00000000, 0x00000045, 0x0000050B, 0x00000000, 0x00000047, 0x0000050B, 0x00000000, 0x00000049, 0x0000050B, 0x00000000, 0x00000048, 0x000004EE, 0x00000000, 0xFFFFFFFF, 0x000101E7, 0x00000000, 0x00000045, 0x000101EB, 0x00000000, 0x00000047, 0x000101EB, 0x00000000, 0x00000049, 0x000101EB, 0x00000000, 0x00000048, 0x000101EB, 0x00000000, 0xFFFFFFFF, 0x000001F8, 0x00000000, 0x00000000, 0x00000395, 0x00000000, 0x00000002, 0x0000051F, 0x00000000, 0x00000036, 0x000001F8, 0x00000000, 0xFFFFFFFF, 0x0000047B, 0x00000000, 0xFFFFFFFF, 0x0000047D, 0x00000000, 0xFFFFFFFF, 0x00000477, 0x00000000, 0xFFFFFFFF, 0x00000478, 0x00000000, 0xFFFFFFFF, 0x0000047B, 0x00000000, 0xFFFFFFFF, 0x0000047B, 0x00000000, 0xFFFFFFFF, 0x0000047B, 0x00000000, 0xFFFFFFFF, 0x0000047A, 0x00000000, 0xFFFFFFFF, 0x0000047C, 0x00000000, 0xFFFFFFFF, 0x000103CD, 0x00000000, 0xFFFFFFFF, 0x0000053B, 0x00000000, 0xFFFFFFFF, 0x0000053C, 0x00000000, 0xFFFFFFFF, 0x00010104, 0x00000000, 0xFFFFFFFF, 0x000103C0, 0x00000000, 0xFFFFFFFF, 0x000101F6, 0x00000000, 0xFFFFFFFF, 0x000101F9, 0x00000000, 0xFFFFFFFF, 0x0000016B, 0x00000000, 0xFFFFFFFF, 0x0000016F, 0x00000000, 0xFFFFFFFF, 0x0000018E, 0x00000000, 0xFFFFFFFF, 0x0000018F, 0x00000000, 0xFFFFFFFF, 0x00000190, 0x00000000, 0xFFFFFFFF, 0x00000191, 0x00000000, 0xFFFFFFFF, 0x00000190, 0x00000000, 0xFFFFFFFF, 0x00000191, 0x00000000, 0xFFFFFFFF, 0x00000346, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000347, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000347, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000348, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000194, 0x00000199, 0xFFFFFFFF, 0x00000195, 0x0000019A, 0xFFFFFFFF, 0x00000196, 0x0000019B, 0xFFFFFFFF, 0x00000197, 0x0000019C, 0xFFFFFFFF, 0x00000198, 0x0000019D, 0xFFFFFFFF, 0x00000135, 0x00000000, 0xFFFFFFFF, 0x00000000 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550680[8] = { 0x00550630, 0x00000000, 0x00000000, 0x00000000, 0x49497350, 0x6762696C, 0x68706172, 0x30303232 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005506A0[4] = { 0x00020001, 0x00030001, 0x00000000, 0x00000000 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005506B0[8] = { 0x01000404, 0x20000000, 0x00000000, 0x05000000, 0x06000000, 0x03000000, 0x02000000, 0x04000000 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005506D0[4] = { 0x06000000, 0x00000000, 0x00000000, 0x00000000 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005506E0[4] = { 0x362E9C14, 0xB94FB21F, 0x3C08873E, 0xBE2AAAA4 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005506F0[8] = { 0x01000404, 0x20000000, 0x00000000, 0x05000000, 0x04000000, 0x00000000, 0x00000000, 0x00000000 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550710[10] = { 0x10008000, 0x10009000, 0x1000A000, 0x1000B000, 0x1000B400, 0x1000C000, 0x1000C400, 0x1000C800, 0x1000D000, 0x1000D400 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550738[6] = { 0x00000000, 0x00000000, 0x49497350, 0x6462696C, 0x2020616D, 0x30303232 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550750[10] = { 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x00000001 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550778[4] = { 0x03000000, 0x00000100, 0x00000002, 0x00000000 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550788[4] = { 0x00020100, 0x00030000, 0x00000000, 0x00000000 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550798[4] = { 0x00030200, 0x00000000, 0x00000000, 0x00000000 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005507A8[10] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x49497350, 0x7062696C, 0x2020746B, 0x30303232 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005507D0 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005507D4 = 0x0071EB98;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_005507D8[8] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005507E0[32] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550860 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550864 = 0xFFFFFFFF;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550868 = 0xFFFFFFFF;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0055086C = 0xFFFFFFFF;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550870 = 0x0062E658;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550874 = 0xFFFFFFFF;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550878 = 0xFFFFFFFF;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0055087C = 0x0062E660;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00550880[8] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00550888[64] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_005508C8[48] = "T\000\000\000@\266$\000U\000\000\000(\260$\000V\000\000\000\350\260$\000W\000\000\0000\261$\000X\000\000\000\200\261$\000Y\000\000\000\320\261$";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005508F8[6] = { 0x00000000, 0x00000000, 0x49497350, 0x6362696C, 0x20647664, 0x30343232 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550910 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550914 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550918 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0055091C = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550920 = 0xFFFFFFFF;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550924 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550928 = 0xFFFFFFFF;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0055092C = 0xFFFFFFFF;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550930 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550934 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550938 = 0xFFFFFFFF;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0055093C = 0xFFFFFFFF;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550940 = 0xFFFFFFFF;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550944 = 0xFFFFFFFF;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550948 = 0xFFFFFFFF;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0055094C = 0xFFFFFFFF;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550950 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00550954 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00550958[40] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00550980[128] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00550A00[4096] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00551A00[192] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00551AC0[16] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00551AD0[48] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00551B00[1088] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00551F40[1032] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00552348[40] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552370[6] = { 0x00000000, 0x00000000, 0x49497350, 0x7062696C, 0x20206461, 0x30303232 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552388 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0055238C = 0x00000001;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005523B0[8] = { 0x0062EB90, 0x0062EB88, 0x0062EB80, 0x00000000, 0x49497350, 0x6D62696C, 0x20202063, 0x30343232 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005523D0 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005523D4 = 0xFFFFFFFF;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005523D8[40] = { 0x00000000, 0x000000E0, 0x00000000, 0x000000FF, 0xFFC00000, 0x000000BD, 0xFFFFFFFF, 0x000000FF, 0xFFA00000, 0x000000BD, 0xFFFFFFFF, 0x000000FF, 0xFFA10000, 0x000000BD, 0xFFFFFFFF, 0x000000FF, 0xFF900000, 0x000000BD, 0xFFFFFFFF, 0x000000FF, 0x00000000, 0x000000C0, 0x00000000, 0x000000FF, 0x80000000, 0x000000BD, 0xFF000000, 0x000000FF, 0xA0000000, 0x000000BD, 0xFF000000, 0x000000FF, 0x88000000, 0x000000BD, 0xFF000000, 0x000000FF, 0x90000000, 0x000000BD, 0xFF000000, 0x000000FF };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552478[8] = { 0x18081000, 0x20101808, 0x30202818, 0x38283020, 0x49497350, 0x6D62696C, 0x20676570, 0x30303232 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552498 = 0x70000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0055249C = 0x007195C0;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005524A0 = 0x70003600;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005524A4 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_005524A8[24] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005524C0 = 0x00552710;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005524C4 = 0x00552778;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005524C8 = 0x005527E0;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005524CC = 0x00552848;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005524D0 = 0x005528B0;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005524D4 = 0x00552918;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005524D8 = 0x00552980;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005524DC = 0x005529E8;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552540[16] = { 0x13101008, 0x16161310, 0x16161616, 0x1B1A181A, 0x1A1A1B1B, 0x1B1B1A1A, 0x1D1D1D1B, 0x1D222222, 0x1B1B1D1D, 0x20201D1D, 0x26252222, 0x22232325, 0x28262623, 0x30302828, 0x38382E2E, 0x5345453A };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552580[16] = { 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010, 0x10101010 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005525C0 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005525C4 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005525C8 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005525CC = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005525D0 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005525D4 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005525D8 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005525DC = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005525E0 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005525E4 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005525E8 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005525EC = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005525F0 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005525F4 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005525F8 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005525FC = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552600 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552604 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552608 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0055260C = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552610 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552614 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552618 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0055261C = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552620 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552624 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552628 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0055262C = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552630 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552634 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552638 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0055263C = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552640 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552644 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552648 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0055264C = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00552650[8] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00552658[16] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552668 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0055266C = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552670 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552674 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552678 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0055267C = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552680 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552684 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552688 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0055268C = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552690 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552694 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552698 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0055269C = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_005526A0[8] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_005526A8[16] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_005526B8[12] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005526C4 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005526C8 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005526CC = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005526D0 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005526D4 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005526D8 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005526DC = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005526E0 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005526E4 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005526E8 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005526EC = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005526F0 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005526F4 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005526F8 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_005526FC = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552700 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552704 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552708 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0055270C = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00552710[104] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00552778[104] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_005527E0[104] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00552848[104] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_005528B0[104] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00552918[104] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00552980[104] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_005529E8[104] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00552A50[104] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00552AB8[648] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00552D40[8] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00552D48[8] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00552D50[8] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552D58 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552D5C = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552D60 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552D70 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552D74 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00552D78[8] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00552D80[8] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552DC8[10] = { 0x00000001, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x00000001, 0x00000001, 0x00000001, 0x00000001 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552DF0 = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552DF4 = 0xFFFFFFFF;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00552DF8[8] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552E2C = 0x00000000;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00552E30[8] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552E38[16] = { 0x00000002, 0x00000000, 0x00000002, 0x00000000, 0x00000002, 0x00000003, 0x00000002, 0x00000003, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000002, 0x00000004, 0x00000000, 0x00000006 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00552E78[8] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552E80[8] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x49497350, 0x6962696C, 0x20207570, 0x30303232 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552EA0[20] = { 0x13101008, 0x16161310, 0x16161616, 0x1B1A181A, 0x1A1A1B1B, 0x1B1B1A1A, 0x1D1D1D1B, 0x1D222222, 0x1B1B1D1D, 0x20201D1D, 0x26252222, 0x22232325, 0x28262623, 0x30302828, 0x38382E2E, 0x5345453A, 0x10101010, 0x10101010, 0x10101010, 0x10101010 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552EF0[8] = { 0x04210000, 0x03E00842, 0x14A51084, 0x1CE718C6, 0x2529001F, 0x7C00294A, 0x35AD318C, 0x39CE7FFF };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_00552F10[64] = "\000\177\010\177\020\177\030\177 \177(\1770\1778\177@\177H\177P\177X\177`\177h\177p\177xxxx\177p\177h\177`\177X\177P\177H\177@\1778\1770\177(\177 \177\030\177\020\177\010\177";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_00552F50[8] = "\354?c";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00552F58[121] = { 0x00000000, 0x0055313C, 0x00553194, 0x005531EC, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0062FD80, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00553244 = 0x00552F58;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00553248[6] = { 0x00000001, 0x00000000, 0x00000043, 0x00000000, 0x00000043, 0x00000000 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00553260[8] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00553668[2] = { 0x00020000, 0x00000000 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00553670[8] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00553678[2] = { 0xFFFFFFFF, 0x00000000 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00553680[8] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00553688[8] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const double D_00553748 = 0.1;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const double D_00553750 = 0.1;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062DF60[32] = "            : object name (%s)\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062DFD0[32] = "Solve object address. %p\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062DFF0[32] = "allocPObj:Invalid Object.\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E010[16] = "src/PObj.c";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E020[16] = "free object\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E030[56] = "sceGsDefDispEnv:Not support displaymode for %d!!\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E068[48] = "sceGsPutDrawEnv: DMA Ch.2 does not terminate\r\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E098[48] = "sceGsSyncPath: DMA Ch.1 does not terminate\r\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E0C8[16] = "\t<D1_CHCR=%08x:";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E0D8[16] = "D1_TADR=%08x:";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E0E8[16] = "D1_MADR=%08x:";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E0F8[16] = "D1_QWC=%08x>\r\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E108[16] = "\t<D2_CHCR=%08x:";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E118[16] = "D2_TADR=%08x:";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E128[16] = "D2_MADR=%08x:";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E138[16] = "D2_QWC=%08x>\r\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E148[24] = "\t<VIF1_STAT=%08x:";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E160[24] = "GIF_STAT=%08x>\r\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E178[48] = "sceGsSyncPath: DMA Ch.2 does not terminate\r\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E1A8[48] = "sceGsSyncPath: VIF1 does not terminate\r\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E1D8[40] = "sceGsSyncPath: VU1 does not terminate\r\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E200[48] = "sceGsSyncPath: GIF does not terminate\r\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E230[48] = "sceGsSetDefLoadImage: too big size\r\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E350[64] = "sceGsExecLoadImage: DMA Ch.2 does not terminate\r\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E390[56] = "sceGsExecStoreImage: DMA Ch.1 does not terminate\r\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E3C8[48] = "sceGsExecStoreImage: GS does not terminate\r\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E3F8[64] = "sceGsExecStoreImage: DMA Ch.1 (GS->MEM) does not terminate\r\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E438[56] = "sceGsExecStoreImage: Enough data does not reach VIF1\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E560[24] = "libdma: sync timeout\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E578[40] = "TTY: packet size larger than expect\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E5A0[24] = "TTY: receive error";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E5B8[24] = "TTY: send err %d\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E5D0[32] = "TTY: err ti->wlen=%08x\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E658[8] = "....";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E660[8] = "....";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E668[8] = "all";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E670[16] = "rom0:UDNL ";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E680[32] = "too long parameter '%s'\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E6A0[64] = "=========================<wired=%02d>=========================\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E6E0[48] = "idx=%02d: pm=%08x, hi=%08x, lo0=%08x, lo1=%08x\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E710[40] = "sceCdCbfunc= %d sceCdCbfunc_num= %d\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E738[32] = "Libcdvd bind err PowerOffCB\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E758[32] = "Libcdvd bind err CdSearchFile\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E778[24] = "ee call cmd search %s\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E790[16] = "search name %s\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E7A0[16] = "search size %d\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E7B0[24] = "search loc lbn %d\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E7C8[40] = "Ncmd fail sema cur_cmd:%d keep_cmd:%d\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E7F0[24] = "Libcdvd bind err N CMD\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E808[16] = "N cmd wait\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E818[16] = "S cmd wait\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E828[40] = "Scmd fail sema cur_cmd:%d keep_cmd:%d\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E850[24] = "Libcdvd bind err S cmd\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E868[32] = "Libcdvd bind err %d CD_Init %d\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E888[16] = "Libcdvd Exit\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E898[16] = "DiskReady 0\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E8A8[32] = "Libcdvd bind err CdDiskReady\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E8C8[24] = "DiskReady ended\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E8E0[24] = "call cdread cmd\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E8F8[16] = "cdread end\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E908[16] = "cdread end\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E918[16] = "status called\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E928[48] = "sceCdStRead call read size= %d mode= %d\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E958[72] = "sceCdStRead BLK Read cur_size= %d read_size= %d req_size= %d err 0x%x\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E9A0[32] = "sceCdStRead BLK Read Ended\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E9C0[24] = "sceCdStPause call\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E9D8[24] = "sceCdStResume call\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062E9F0[24] = "sceCdStStat call\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062EA08[24] = "call cdreadstm call\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062EA20[24] = "call cdreadstm cmd\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062EA38[16] = "cdread end\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062EA48[72] = "libpad: sceSifSetDma faild\n\000\000\000\000\000libpad: tPadDma Structure Invalid\n\000\000\000\000\000";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062EAB8[40] = "[libpad.a = %d.%d, padman.irx = %d.%d]\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062EAE0[48] = "libpad: buffer addr is not 64 byte align. %08x\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062EB10[48] = "libpad: pad port is already open [%d][%d]\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_0062EB68[8] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062EBA0[24] = "bind error libmc \n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062EBB8[40] = "libmc: too old release of mcserv.irx\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062EBE0[40] = "libmc: too old release of mcman.irx\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062EC08[56] = "pack_header_field_flag needs to be '0' in PS\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062ED08[16] = "[MPEG ERROR]%s\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062F098[48] = "Too small buffer size for %dx%d picture\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062F0C8[24] = "CSC handler error\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0062F2E0[37] = { 0x00000000, 0x7FF80000, 0x3F800000, 0x40490FDA, 0x3FC90FDA, 0x33A22168, 0x3E2AAAAB, 0xBEA6B090, 0x3E4E0AA8, 0xBD241146, 0x3A4F7F04, 0x3811EF08, 0xC019D139, 0x4001572D, 0xBF303361, 0x3D9DC62E, 0x3F800000, 0x7149F2CA, 0x3FC90FDA, 0x33A22168, 0x3F490FDB, 0x3E2AAAAB, 0xBEA6B090, 0x3E4E0AA8, 0xBD241146, 0x3A4F7F04, 0x3811EF08, 0xC019D139, 0x4001572D, 0xBF303361, 0x3D9DC62E, 0x0DA24260, 0x00000000, 0x3F490FDB, 0x3FC90FDB, 0x40490FDA, 0x34222168 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0062F380[2] = { 0x00000000, 0x80000000 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062F388[792] = "\242\000\000\000\371\000\000\000\203\000\000\000n\000\000\000N\000\000\000D\000\000\000\025\000\000\000)\000\000\000\374\000\000\000'\000\000\000W\000\000\000\321\000\000\000\365\000\000\0004\000\000\000\335\000\000\000\300\000\000\000\333\000\000\000b\000\000\000\225\000\000\000\231\000\000\000<\000\000\000C\000\000\000\220\000\000\000A\000\000\000\376\000\000\000Q\000\000\000c\000\000\000\253\000\000\000\336\000\000\000\273\000\000\000\305\000\000\000a\000\000\000\267\000\000\000$\000\000\000n\000\000\000:\000\000\000B\000\000\000M\000\000\000\322\000\000\000\340\000\000\000\006\000\000\000I\000\000\000.\000\000\000\352\000\000\000\t\000\000\000\321\000\000\000\222\000\000\000\034\000\000\000\376\000\000\000\035\000\000\000\353\000\000\000\034\000\000\000\261\000\000\000)\000\000\000\247\000\000\000>\000\000\000\350\000\000\000\202\000\000\0005\000\000\000\365\000\000\000.\000\000\000\273\000\000\000D\000\000\000\204\000\000\000\351\000\000\000\234\000\000\000p\000\000\000&\000\000\000\264\000\000\000_\000\000\000~\000\000\000A\000\000\0009\000\000\000\221\000\000\000\326\000\000\0009\000\000\000\203\000\000\000S\000\000\0009\000\000\000\364\000\000\000\234\000\000\000\204\000\000\000_\000\000\000\213\000\000\000\275\000\000\000\371\000\000\000(\000\000\000;\000\000\000\037\000\000\000\370\000\000\000\227\000\000\000\377\000\000\000\336\000\000\000\005\000\000\000\230\000\000\000\017\000\000\000\357\000\000\000/\000\000\000\021\000\000\000\213\000\000\000Z\000\000\000\n\000\000\000m\000\000\000\037\000\000\000m\000\000\0006\000\000\000~\000\000\000\317\000\000\000'\000\000\000\313\000\000\000\t\000\000\000\267\000\000\000O\000\000\000F\000\000\000?\000\000\000f\000\000\000\236\000\000\000_\000\000\000\352\000\000\000-\000\000\000u\000\000\000'\000\000\000\272\000\000\000\307\000\000\000\353\000\000\000\345\000\000\000\361\000\000\000{\000\000\000=\000\000\000\007\000\000\0009\000\000\000\367\000\000\000\212\000\000\000R\000\000\000\222\000\000\000\352\000\000\000k\000\000\000\373\000\000\000_\000\000\000\261\000\000\000\037\000\000\000\215\000\000\000]\000\000\000\010\000\000\000V\000\000\000\003\000\000\0000\000\000\000F\000\000\000\374\000\000\000{\000\000\000k\000\000\000\253\000\000\000\360\000\000\000\317\000\000\000\274\000\000\000 \000\000\000\232\000\000\000\364\000\000\0006\000\000\000\035\000\000\000\251\000\000\000\343\000\000\000\221\000\000\000a\000\000\000^\000\000\000\346\000\000\000\033\000\000\000\010\000\000\000e\000\000\000\231\000\000\000\205\000\000\000_\000\000\000\024\000\000\000\240\000\000\000h\000\000\000@\000\000\000\215\000\000\000\377\000\000\000\330\000\000\000\200\000\000\000M\000\000\000s\000\000\000'\000\000\0001\000\000\000\006\000\000\000\006\000\000\000\025\000\000\000V\000\000\000\312\000\000\000s\000\000\000\250\000\000\000\311\000\000\000`\000\000\000\342\000\000\000{\000\000\000\300\000\000\000\214\000\000\000k";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0062F6A0[52] = { 0x3FC90F00, 0x40490F00, 0x4096CB00, 0x40C90F00, 0x40FB5300, 0x4116CB00, 0x412FED00, 0x41490F00, 0x41623100, 0x417B5300, 0x418A3A00, 0x4196CB00, 0x41A35C00, 0x41AFED00, 0x41BC7E00, 0x41C90F00, 0x41D5A000, 0x41E23100, 0x41EEC200, 0x41FB5300, 0x4203F200, 0x420A3A00, 0x42108300, 0x4216CB00, 0x421D1400, 0x42235C00, 0x4229A500, 0x422FED00, 0x42363600, 0x423C7E00, 0x4242C700, 0x42490F00, 0x00000000, 0x3F000000, 0x43800000, 0x3F22F984, 0x3FC90F80, 0x37354443, 0x37354400, 0x2E85A308, 0x2E85A300, 0x248D3132, 0x3F800000, 0x0DA24260, 0x3F800000, 0x3D2AAAAB, 0xBAB60B61, 0x37D00D01, 0xB493F27C, 0x310F74F6, 0xAD47D74E, 0x00000000 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0062F770[4] = { 0x00000004, 0x00000007, 0x00000009, 0x00000000 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0062F780[22] = { 0x3FC90000, 0x39F00000, 0x37DA0000, 0x33A20000, 0x2E840000, 0x2B500000, 0x27C20000, 0x22D00000, 0x1FC40000, 0x1BC60000, 0x17440000, 0x00000000, 0x3F800000, 0x43800000, 0x3B800000, 0x3F000000, 0xBE2AAAAB, 0x3C088889, 0xB9500D01, 0x3638EF1B, 0xB2D72F34, 0x2F2EC9D3 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0062F7D8[2] = { 0x00000001, 0x00000000 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const float D_0062F7E0[3] = { 0.4636476f, 0.7853981f, 0.9827937f };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const float D_0062F7EC = 1.5707963f;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const float D_0062F7F0[3] = { 5.0121582e-09f, 3.7748947e-08f, 3.4473217e-08f };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const float D_0062F7FC = 7.5497894e-08f;

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0062F800[18] = { 0x3EAAAAAB, 0xBE4CCCCD, 0x3E124925, 0xBDE38E38, 0x3DBA2E6E, 0xBD9D8795, 0x3D886B35, 0xBD6EF16B, 0x3D4BDA59, 0xBD15A221, 0x3C8569D7, 0x3F800000, 0x7149F2CA, 0x7149F2CA, 0x4C000000, 0x33000000, 0x7149F2CA, 0x0DA24260 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0062F848[64] = { 0x02020100, 0x03030303, 0x04040404, 0x04040404, 0x05050505, 0x05050505, 0x05050505, 0x05050505, 0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0062F948[64] = { 0x02020100, 0x03030303, 0x04040404, 0x04040404, 0x05050505, 0x05050505, 0x05050505, 0x05050505, 0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0062FA48[64] = { 0x02020100, 0x03030303, 0x04040404, 0x04040404, 0x05050505, 0x05050505, 0x05050505, 0x05050505, 0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_0062FB48[64] = { 0x02020100, 0x03030303, 0x04040404, 0x04040404, 0x05050505, 0x05050505, 0x05050505, 0x05050505, 0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x06060606, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x07070707, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808, 0x08080808 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_0062FC48[49] = "assertion \"%s\" failed: file \"%s\", line %d\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00630190[12] = { 0x0001000A, 0x00030002, 0x00050004, 0x00070006, 0x00090008, 0x000B000A, 0x000D000C, 0x000F000E, 0x00000010, 0x00000000, 0x00000000, 0x00000000 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00630620[2] = { 0x636F4361, 0x3FD287A7 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00630628[2] = { 0x8B60C8B3, 0x3FC68A28 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_00630630[16] = "\373y\237P\023D\323?";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00630658[12] = { 0x00630690, 0x00630688, 0x00630688, 0x00630688, 0x00630688, 0x00630688, 0x00630688, 0x00630688, 0x00630688, 0x00630688, 0x7F7F7F7F, 0x7F7F7F7F };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00630688[8] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_006306A0[16] = "\005\000\000\000\031\000\000\000}";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_006306B0[50] = { 0x00000000, 0x3FF00000, 0x00000000, 0x40240000, 0x00000000, 0x40590000, 0x00000000, 0x408F4000, 0x00000000, 0x40C38800, 0x00000000, 0x40F86A00, 0x00000000, 0x412E8480, 0x00000000, 0x416312D0, 0x00000000, 0x4197D784, 0x00000000, 0x41CDCD65, 0x20000000, 0x4202A05F, 0xE8000000, 0x42374876, 0xA2000000, 0x426D1A94, 0xE5400000, 0x42A2309C, 0x1E900000, 0x42D6BCC4, 0x26340000, 0x430C6BF5, 0x37E08000, 0x4341C379, 0x85D8A000, 0x43763457, 0x674EC800, 0x43ABC16D, 0x60913D00, 0x43E158E4, 0x78B58C40, 0x4415AF1D, 0xD6E2EF50, 0x444B1AE4, 0x064DD592, 0x4480F0CF, 0xC7E14AF6, 0x44B52D02, 0x79D99DB4, 0x44EA7843 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00630778[8] = { 0x37E08000, 0x4341C379, 0xB5056E17, 0x4693B8B5, 0xE93FF9F5, 0x4D384F03, 0xF9301D32, 0x5A827748 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00630798[2] = { 0x7F73BF3C, 0x75154FDD };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_006307A0[48] = "\274\211\330\227\262\322\234<3\247\250\325#\366I9=\247\364D\375\017\2452\235\227\214\317\010\272[%Co\254d(\006\310\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00630888[2] = { 0x94A03595, 0x3FDFFFFF };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned int D_00630898[2] = { 0x94A03595, 0x3FCFFFFF };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
unsigned char D_00633B98[8] = { 0 };

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_00633BA0[8] = "%d\n";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_00633BA8[8] = "%s";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_00633BB0[8] = "\033[m";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_00633BB8[8] = "OBJH";

/* 8-byte double constants. -G 8 would put doubles in `.sdata`
 * without the placement attribute; the VMA-pinned attr forces
 * `.rodata` placement. */
const char D_00633BC0[] = "FALSE";

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/PObj", func_002413F0);
INCLUDE_ASM("asm/nonmatchings/src/PObj", func_002418A0);

/* ASCII debug strings — re-derived from EE rodata bytes. */
/* ASCII preview: "<ESC>[33mobject info : adrs(%p) objnum(%d) clstnum(%d)<LF>" */
const char D_0062DF28[56] = "\033[33mobject info : adrs(%p) objnum(%d) clstnum(%d)\n";
/* ASCII preview: "            : object table (%p)<ESC><LF>" */
const char D_0062DF80[40] = "            : object table (%p)\033\n";
/* ASCII preview: "            : texture table (%p)<ESC>[m<LF>" */
const char D_0062DFA8[40] = "            : texture table (%p)\033[m\n";
/* ASCII preview: "                " */
const char D_0062FD90[16] = "                ";
/* ASCII preview: "0000000000000000" */
const char D_0062FDA0[16] = "0000000000000000";
/* ASCII preview: "                " */
const char D_0062FF80[16] = "                ";
/* ASCII preview: "0000000000000000" */
const char D_0062FF90[16] = "0000000000000000";
/* ASCII preview: "bug in vfprintf: bad bas" */
const char D_0062FFE8[24] = "bug in vfprintf: bad bas";
