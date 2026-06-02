/* boyact.c -- typed sdata / lit4 definitions for this TU.
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

extern float D_00630B2C;
extern float D_00630B30;
extern float D_00630B34;
extern float D_00630B38;
extern float D_00630B3C;
extern float D_00630B40;
extern float D_00630B44;
extern float D_00630B48;
extern float D_00630B4C;
extern float D_00630B50;
extern float D_00630B54;
extern float D_00630B58;
extern float D_00630B5C;
extern float D_00630B60;
extern float D_00630B64;
extern float D_00630B68;
extern float D_00630B6C;
extern float D_00630B70;
extern float D_00630B74;
extern float D_00630B78;
extern float D_00630B7C;
extern float D_00630B80;
extern float D_00630B84;
extern float D_00630B88;
extern float D_00630B8C;
extern float D_00630B90;
extern float D_00630B94;
extern float D_00630B98;
extern float D_00630B9C;
extern float D_00630BA0;
extern float D_00630BA4;
extern float D_00630BA8;
extern float D_00630BAC;
extern float D_00630BB0;
extern float D_00630BB4;
extern float D_00630BB8;
extern float D_00630BBC;
extern float D_00630BC0;
extern float D_00630BC4;
extern float D_00630BC8;
extern float D_00630BCC;
extern float D_00630BD0;
extern float D_00630BD4;
extern float D_00630BD8;
extern float D_00630BDC;
extern float D_00630BE0;
extern float D_00630BE4;
extern float D_00630BE8;
extern float D_00630BEC;
extern float D_00630BF0;
extern float D_00630BF4;
extern float D_00630BF8;
extern float D_00630BFC;
extern float D_00630C00;
extern float D_00630C04;
extern float D_00630C08;
extern float D_00630C0C;
extern float D_00630C10;
extern float D_00630C14;
extern float D_00630C18;
extern float D_00630C1C;
extern float D_00630C20;
extern float D_00630C48;
extern int D_00631AE4;
extern int D_00631AE8;
extern int D_00631AF0;
extern int D_00631B60;
extern int D_00631B64;
extern int D_006321DC;
extern const char D_00632290[8];
extern char D_00632298[8];
extern char D_006322A8[8];
extern int D_006322BC;
extern int D_006322C4;
extern int D_006322C8;
extern const char D_006322F0[8];
extern int D_006325B4;
extern float D_006325B8;
extern int D_006325BC;
extern char D_006325C0[8];
extern int D_006325C8;
extern int D_006325CC;
extern int D_006325D0;
extern int D_006325D4;
extern int D_006325D8;
extern int D_006325DC;
extern char D_006325E0[8];
extern char D_006325E8[8];
extern const char D_006325F0[8];
extern const char D_006325F8[8];
extern int D_00632600;
extern unsigned int D_00632604;
extern int D_00632608;
extern int D_0063260C;
extern unsigned int D_00632610;
extern int D_00632738;
extern int D_0063273C;
extern int D_00632740;
extern int D_00632744;
extern char D_00632748[16];
extern int D_00632D68;
extern int D_00632D8C;
extern int D_00633134;
extern char D_00633138[8];
extern unsigned char D_00633140;
extern unsigned char D_00633141;
extern unsigned char D_00633148;
extern unsigned char D_00633149;
extern unsigned short D_0063314A;
extern int D_0063314C;
extern unsigned int D_00633150;
extern unsigned int D_00633154;
extern int D_00633158;
extern int D_0063315C;
extern int D_00633160;
extern int D_00633164;
extern int D_00633168;
extern int D_0063316C;
extern int D_00633170;
extern int D_00633174;

unsigned int D_00281B90[24] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

unsigned char D_00281BF0[32] = { 0 };

unsigned int D_00281C10[84] = { 0x000001A0, 0x00000000, 0x40E00000, 0x01014601, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000001A1, 0x00000000, 0x00000000, 0x01004600, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000001A5, 0x00000000, 0x00000000, 0x00000000, 0xBF800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000001A6, 0xC1200000, 0x41B80000, 0x01014601, 0xBF800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

unsigned char D_00281D60[16] = { 0 };

unsigned int D_00281D70[392] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000069, 0x00000069, 0x00000037, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000000C4, 0x000000C5, 0x00000000, 0x00000000, 0x00000000, 0x0000004D, 0x0000004E, 0x00000000, 0x00000091, 0x0000006B, 0x00000095, 0x00000099, 0x00000001, 0x00000011, 0x00000013, 0x00000014, 0x00000000, 0x00000000, 0x00000000, 0x00000078, 0x00000000, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000083, 0x000000EE, 0xFFFFFFFF, 0x00000070, 0x0000006F, 0x00000092, 0x00000093, 0x00000000, 0x00000000, 0x00000000, 0x0000006D, 0x0000006C, 0x00000086, 0x00000087, 0x00000088, 0x000000EA, 0x000000EB, 0x00000004, 0x00000001, 0x00000004, 0x00000000, 0x00000000, 0x00000000, 0x00000039, 0x0000003A, 0x0000003B, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x00000000, 0x00000001, 0x00000000, 0x00000066, 0x0000000C, 0x00000007, 0x00000001, 0x0000005F, 0x00000001, 0x00000000, 0x00000067, 0x00000068, 0x0000000F, 0x0000000D, 0x00000001, 0x00000055, 0x0000005C, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x00000000, 0x00000000, 0x00000012, 0x00000078, 0x00000079, 0x0000007A, 0x00000000, 0x0000003E, 0x0000003F, 0x00000040, 0x00000001, 0x00000050, 0x00000051, 0x00000050, 0x00000094, 0x00000094, 0x00000041, 0x00000042, 0x00000043, 0x00000044, 0x00000046, 0x00000045, 0x00000047, 0x00000048, 0x00000048, 0x0000004A, 0x00000049, 0x00000071, 0x00000072, 0x00000073, 0x00000074, 0x00000070, 0x00000075, 0x00000069, 0x00000070, 0x00000089, 0x00000089, 0x0000004E, 0x000000B1, 0x000000B2, 0x000000B3, 0x000000B4, 0x000000B5, 0x0000008B, 0x00000073, 0x00000074, 0x000000B6, 0x000000B8, 0x000000B7, 0x000000BA, 0x000000B9, 0x000000B0, 0x00000091, 0x000000BB, 0x000000BC, 0x000000BD, 0x0000004C, 0x0000004B, 0x00000000, 0x00000000, 0x00000000, 0x0000004D, 0x000000BB, 0x000000B5, 0x000000BE, 0x00000000, 0x00000005, 0x00000006, 0x00000007, 0x00000008, 0x00000009, 0x0000000D, 0x0000000E, 0x0000000C, 0x0000000F, 0x00000010, 0x00000015, 0x00000016, 0x00000018, 0x00000018, 0x00000017, 0x00000019, 0x00000001, 0x00000001, 0x00000002, 0x00000023, 0x00000024, 0x0000000B, 0x00000001, 0x00000026, 0x00000026, 0x00000027, 0x0000002E, 0x0000002D, 0x0000002D, 0x0000002F, 0x0000002C, 0x0000002B, 0x0000006A, 0x00000083, 0x0000009B, 0x00000007, 0x00000000, 0x00000099, 0x00000001, 0x0000009A, 0x0000009B, 0x00000093, 0x00000034, 0x00000035, 0x0000006A, 0x000000AF, 0x00000052, 0x000000E5, 0x00000030, 0x000000C5, 0x000000C4, 0x000000C7, 0x000000C6, 0x000000C7, 0x000000C6, 0x000000C5, 0x000000C4, 0x0000000C, 0x00000007, 0x000000C8, 0x000000C5, 0x000000C4, 0x000000C8, 0x000000C8, 0x00000000, 0x0000003C, 0x0000003D, 0x00000001, 0x0000000C, 0x00000001, 0x00000000, 0x000000E6, 0x0000006A, 0x00000000, 0x00000000, 0x00000000, 0x000000EE, 0x000000EE, 0x000000E7, 0x0000001A, 0x000000EE, 0x0000000A, 0x0000000B, 0x0000000A, 0x00000001, 0x00000007, 0x00000001, 0x00000000, 0x000000C0, 0x000000C1, 0x000000C2, 0x000000C3, 0x0000001B, 0x0000001C, 0x0000001D, 0x0000001E, 0x0000001F, 0x00000020, 0x00000021, 0x00000022, 0x0000007B, 0x0000007B, 0x0000007C, 0x00000084, 0x00000085, 0x0000007D, 0x0000007E, 0x0000007F, 0x00000080, 0x00000082, 0x00000083, 0x00000000, 0x00000037, 0x00000036, 0x00000031, 0x00000032, 0x00000033, 0x00000038, 0x00000089, 0x0000008A, 0x00000075, 0x00000096, 0x00000097, 0x00000037, 0x00000037, 0x00000076, 0x00000077, 0x00000037, 0x00000069, 0x00000069, 0x0000006E, 0x0000006A, 0x00000055, 0x00000056, 0x00000057, 0x00000056, 0x00000058, 0x00000059, 0x0000005A, 0x00000053, 0x00000036, 0x00000054, 0x0000008B, 0x0000008C, 0x0000008D, 0x0000008E, 0x0000008F, 0x00000090, 0x00000091, 0x00000000, 0x00000000, 0x00000000, 0x000000EF, 0x000000F0, 0x000000AA, 0x000000AD, 0x000000AD, 0x000000AC, 0x000000AB, 0x000000AE, 0x000000C9, 0x000000D2, 0x000000D3, 0x000000CA, 0x000000CB, 0x000000CC, 0x000000CD, 0x000000CE, 0x000000CF, 0x000000CB, 0x000000D6, 0x00000007, 0x00000001, 0x000000D7, 0x000000D8, 0x000000D9, 0x000000D9, 0x000000DA, 0x000000DB, 0x000000DC, 0x000000DD, 0x000000DE, 0x000000E0, 0x000000E1, 0x0000009C, 0x0000009D, 0x0000009E, 0x0000009C, 0x0000009D, 0x0000009E, 0x0000009F, 0x000000A0, 0x000000A0, 0x000000A1, 0x000000A1, 0x00000000, 0x00000000, 0x000000A2, 0x000000A3, 0x000000A4, 0x0000005F, 0x000000A5, 0x00000001, 0x000000A6, 0x000000A7, 0x000000A8, 0x000000A9, 0x000000A7, 0x0000006A, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

unsigned int D_00282390[12] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000 };

unsigned int D_0028CE10[402] = { 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00160026, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00190027, 0x00040000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFF018C, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00180067, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00180022, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00680165, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00680166, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x000100F6, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x002C001A, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x002C00CB, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00050007, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00050128, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x0013010A, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x0013010B, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x0007002B, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x0015D488, 0x0016002C, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x001600CF, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00050018, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x0015D470, 0x0014010D, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x0014010F, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00140110, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00140111, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00140112, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00150113, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00160114, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x006F002E, 0x00050000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x0004002D, 0x00040000, 0x00000000, 0x00000000, 0x00165158, 0x00000000, 0x000000F0, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x006B00EF, 0x00050000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x004D004B, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x0057016E, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x000100F1, 0x00050000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x000100F2, 0x00050000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x000100F3, 0x00050000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x000100F4, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x000400F5, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00050133, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00080183, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00080182, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x000800A4, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00080075, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00080076, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x000E00B9, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x000E00BA, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x000D00BB, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x004A013C, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x006E0145, 0x00050000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x006A0141, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00620146, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x0064014A, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00610150, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x0055016B, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x002E006F, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x002F0070, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00300071, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x0036007C, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x007100FB, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x002D006B, 0x00040000, 0x0015E908, 0x0015EED0, 0x00000000, 0x00000000, 0x002A00D0, 0x00040000, 0x0015E908, 0x0015EED0, 0x00000000, 0x00000000, 0x002A00D1, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x005E0157, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x005E0159, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x005B0154, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x00290131, 0x00040000, 0x0015E6B0, 0x0015EED0, 0x00000000, 0x00000000, 0x000400B5, 0x00040000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000003A, 0x00040000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0xFFFF018C, 0x00040000 };

unsigned char D_004C49A8[2220] = { 0 };

float D_004C5AA0[4] = { -3.0f, 0.0f, -3.0f, 0.0f };

float D_004C5AB0[4] = { 3.0f, 0.0f, 3.0f, 0.0f };

float D_004C5AC0[4] = { -3.0f, 0.0f, 3.0f, 0.0f };

float D_004C5AD0[4] = { 3.0f, 0.0f, -3.0f, 0.0f };

const char D_005582C8[16] = "src/boyact.c";

const char D_005582D8[24] = "speed = %f (%f)\n";

const char D_005582F0[16] = "%f / %f\n";

const char D_005584E8[16] = "%d -> %d\n";

const char D_005584F8[24] = "\004\000\000\000.\000\000\000=\000\000\000\377\377\377\377";

const double D_00558620 = 0.2;

const float D_00558628[2] = { -107374184.0f, 1.8499999f };

const double D_00558630 = 0.2;

const double D_00558638 = 0.7;

const char D_00558640[24] = "enter actBoyFall\n";

const char D_00558658[24] = "attack sub id [%d]\n";

const char D_00558670[24] = "enter actBoyAttack\n";

const char D_00558688[24] = "enter actBoyCall\n";

const char D_005586A0[24] = "enter actBoyItemAfter\n";

const char D_005586B8[40] = "enemy error body slam[%s]\n";

const float D_005586E0[4] = { -1e+06f, 0.0f, 0.0f, 0.0f };

const char D_005586F0[16] = "actBoyStart:%p\n";

const float D_00558700[4] = { 0.0f, 0.0f, -5e+01f, 1.0f };

const float D_00558710[4] = { 0.0f, 0.0f, 5e+01f, 1.0f };

/* EUC-JP: "！！！ソファの壁を見付けることができません！！！\n" */
const char D_00558720[56] = "\241\252\241\252\241\252\245\275\245\325\245\241\244\316\312\311\244\362\270\253\311\325\244\261\244\353\244\263\244\310\244\254\244\307\244\255\244\336\244\273\244\363\241\252\241\252\241\252\n";

const char D_00558758[48] = "hand connect start\n\000\000\000\000\000WBP set [landing]\n\000\000\000\000\000";

const char D_00558788[24] = "critical hit to boss!!!";

const char D_005587A0[32] = "!!! unable guard flag get\n";

const char D_005587C0[16] = "guard mail\n";

const char D_005587D0[32] = "guard error=[%d][%d][%d][%d]\n";

const char D_005587F0[16] = "die!!!!!!!!!!!\n";

const char D_00558800[24] = "down!!!!!!!!!!!\n";

const char D_00558818[48] = "damage!!!!!!!!!!!  %d\n\000\000WBP set [with mail]\n\000\000\000";

const char D_006322B0[8] = "next";

unsigned int D_006322B8[2] = { 0x7F7FFFFF, 0x00000000 };

unsigned int D_006322C0[3] = { 0x65746661, 0x00000072, 0xFFFFFFFF };

unsigned int D_006322CC = 0x00000000;

const char D_006322D0[8] = "ignore";

const char D_006322D8[8] = "off!!\n";

const char D_006322E0[8] = "%d, %d\n";

unsigned int D_00632D90 = 0x00000000;

unsigned int D_00632D94 = 0x00000000;

unsigned int D_00632D98 = 0x00000000;

unsigned int D_00632D9C = 0x00000000;

unsigned int D_00632DA0 = 0x00000000;

unsigned int D_00632DA4 = 0x00000000;

/* Inlined data (Phase 3e) — migrated from boyact_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
float D_00630C24 = 40000.0f;
float D_00630C28 = 3.1415927f;
float D_00630C2C = 3.1415927f;
float D_00630C30 = 3.1415927f;
float D_00630C34 = 3.1415927f;
float D_00630C38 = 3.1415927f;
float D_00630C3C = 0.7853982f;
float D_00630C40 = 3.1415927f;
float D_00630C44 = 0.2f;

/* Inlined data (Phase 3e) — migrated from boyact_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* misaligned arrays (scalar head + aligned tail) */
unsigned int D_004C5254 = 0x00000000;
unsigned char D_004C5258[2120] = { 0 };

#include "include_asm.h"
#include "ico/types.h"
#include "matching.h"
#include "regpin.h"

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_0014E5E8);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_0014E708);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_0014E840);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_0014EA30);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001501A0);
extern long long D_006AAAE0[];
extern void func_00107270(char *p, float a, float b, float c, float d, float e, float f);
extern void func_00102858(int obj);

void func_001502D8(void)
{
    char *base = (char *)D_006AAAE0;
    int *obj_ptr = *(int **)(base + 0x20);
    char *sub;
    if (obj_ptr == 0) return;
    sub = ((GObj *)((char *)obj_ptr))->p_15C;
    func_00107270(sub + 0xA0,
                  *(float *)(base + 0x30),
                  *(float *)(base + 0x34),
                  *(float *)(base + 0x38),
                  -*(float *)(base + 0x40),
                  -*(float *)(base + 0x44),
                  -*(float *)(base + 0x48));
    func_00102858(*(int *)(base + 0x20));
}
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00150348);
extern void func_0014E5E8(char *self, int code, char *p);

void func_001504D8(char *self)
{
    func_0014E5E8(self, 0x1A0, *(char **)(*(char * volatile *)(self + 0x164) + 0x670) + 0x2A0);
    func_0014E5E8(self, 0x1A1, *(char **)(*(char * volatile *)(self + 0x164) + 0x670) + 0x2A4);
    func_0014E5E8(self, 0x1A5, *(char **)(*(char * volatile *)(self + 0x164) + 0x670) + 0x2B0);
    func_0014E5E8(self, 0x1A5, *(char **)(*(char * volatile *)(self + 0x164) + 0x670) + 0x2AC);
    func_0014E5E8(self, 0x1A6, *(char **)(*(char * volatile *)(self + 0x164) + 0x670) + 0x2A8);
}
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00150568);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001520E8);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001521F0);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001522E0);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00153478);

/* Matched body inlined from src/cod/0538C0.c during TU coalesce. */
extern void func_00203C40(int *a0);
extern void func_00194508(int *a0, int a1);
void func_001538C0(int a0)
{
    int buf[4];
    func_00203C40(buf);
    func_00194508(buf, a0);

}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001538F4);

/* Matched body inlined from src/cod/0538F8.c during TU coalesce. */
extern int D_00631AE4;
int func_001538F8(void)
{
    if (D_00631AE4 != 0) {
        return *(int *)(*(int *)(D_00631AE4 + 0x164) + 0x140);
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00153918);

/* Matched body inlined from src/cod/0539B8.c during TU coalesce. */
extern void func_0015D348(unsigned int a0, int a1);
extern void func_00203AA0(int a0);
void func_001539B8(volatile unsigned int a0)
{
    volatile int local;
    int *v1 = *(int **)(a0 + 0x164);
    int a1 = v1[0x678 / 4];
    func_0015D348(a0, a1 + 0x7E0);
    func_00203AA0(0);
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001539F0);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00153FF0);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001540A8);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00154160);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00154218);
extern int D_00631990;
extern int D_006AAB48[];
extern void func_001F4098(int a0);
extern void func_002641D8(int *dst, int val, int size);
extern void func_00104360(int a0, int *buf);
extern int func_001AE420(int a0, int a1, int a2, int a3);

void func_00154390(void)
{
    if (D_00631AE4 != 0) {
        int s0 = *(int *)(D_00631AE4 + 0x164);
        if (*(int *)(s0 + 0x140) != 0) {
            union { int i[4]; float f[4]; } buf;
            func_001F4098(*(int *)(s0 + 0x140));
            func_002641D8(buf.i, 0, 0x10);
            buf.f[0] = D_00630C20;
            func_00104360(*(int *)(s0 + 0x140), buf.i);
            func_001AE420(*(int *)(s0 + 0x140), 0, 0, D_00631990);
            *(int *)(*(int *)(s0 + 0x140) + 0x16C) = 0;
        }
        D_006AAB48[0] = 0;
        *(int *)D_006AAAE0 = 0;
        *(int *)(s0 + 0x140) = 0;
    }
}

/* Matched body inlined from src/cod/054420.c during TU coalesce. */
int func_00154420(void)
{
    unsigned int a = *(unsigned int *)(*(int *)(D_00631AE4 + 0x164) + 0x30);
    if (a >= 0x5D) return 1;
    if (a < 0x5B) return 1;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00154444);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00154448);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00154520);

/* Matched body inlined from src/cod/0545D8.c during TU coalesce. */
extern long long D_006AAAE8[];
int func_001545D8(void) {
    return (int)((unsigned char)((unsigned long long)D_006AAAE8[0] >> 35)) & 1;
}

/* Matched body inlined from src/cod/0545F0.c during TU coalesce. */
extern unsigned char D_00633CEC;
unsigned char func_001545F0(void) {
    return D_00633CEC;
}

/* Matched body inlined from src/cod/0545F8.c during TU coalesce. */
extern int D_00631AE8;
int func_001545F8(void)
{
    int *a = (int *)D_00631AE4;
    int *b = (int *)D_00631AE8;
    int *pa, *pb, *r;
    int v;
    if (a == 0) goto err;
    if (b == 0) goto err;
    pa = (int *)a[0x164/4];
    v = pa[0x30/4];
    if (v != 0x2D) goto err;
    pb = (int *)b[0x164/4];
    if (pb[0x30/4] != v) goto err;
    r = (int *)pa[0x150/4];
    return r[2];
err:
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00154644);

/* Matched body inlined from src/cod/054648.c during TU coalesce. */
/* D_006AAAE0 is `long long[]` to match func_00154648's original. */
extern long long D_006AAAE0[];
void func_00154648(void) {
    D_006AAAE0[1] |= 0x800000000LL;
}

/* Matched body inlined from src/cod/054668.c during TU coalesce. */
extern void func_001F3F58(int *self, int *d, int r);
void func_00154668(int *self)
{
    int new_var;
    int *d;
    int *p;
    d = (int *) D_00631AE4;
    if (0 == d) return;
    if (self == 0) return;
    new_var = 0x164;
    p = (int *) d[new_var / 4];
    func_001F3F58(self, d, 0x16);
    new_var = self[0x8 / 4];
    p[0x140 / 4] = (int) self;
    *(int *)D_006AAAE0 = new_var;
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001546BC);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001546C0);

/* Matched body inlined from src/cod/054770.c during TU coalesce. */
extern unsigned char D_006AAB30[];
int func_00154770(void)
{
    if (D_006AAB30[0]) {
        return *(int *)(D_006AAB30 + 4);
    }
    return 0;
}

/* Matched body inlined from src/cod/054790.c during TU coalesce. */
unsigned char func_00154790(void) {
    return D_006AAB30[0];
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_0015479C);

/* Matched body inlined from src/cod/0547A0.c during TU coalesce. */
extern int D_006AAB40[];
int *func_001547A0(void) {
    return D_006AAB40;
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001547AC);

/* Matched body inlined from src/cod/0547B0.c during TU coalesce. */
int func_001547B0(void) {
    return 24;
}

INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001547B8);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001548F0);
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001549B8);
extern void func_00149D60(int a0, int a1, int a2, int a3, int a4, int a5, int a6);
extern void func_001A6E28(const char *fmt, ...);
extern unsigned int D_00282660[];
struct Blob12 { long long ll __attribute__((packed)); int w; };
void func_00154B20(volatile int a0)
{
    int sub;
    func_00149D60(a0, 0, 3, 0, 0, 0, 0);
    sub = (int)((GObj *)(a0))->p_15C;
    *(struct Blob12 *)(sub + 0x1C0) = *(struct Blob12 *)D_00282660;
    func_001A6E28((const char *)D_006322C0);
}


/* === BEGIN recovered struct shapes (tools/place_struct_shapes.py) === */
/* Field layouts mined from load/store access patterns; SPARSE
 * (only touched offsets, no padding). Unused typedefs — they add
 * no symbol and cannot affect codegen. Cast as ((S_<VMA> *)D_<VMA>).
 */

typedef struct {
    unsigned int     f_4;  /* 0x4  x1 */
    unsigned long long f_8;  /* 0x8  x16  mixed-width */
    unsigned int     f_10;  /* 0x10  x1 */
    unsigned int     f_20;  /* 0x20  x5 */
    unsigned int     f_24;  /* 0x24  x3 */
} S_006AAAE0;  /* 26 accesses */

typedef struct {
    unsigned int     f_0;  /* 0x0  x19 */
} S_004C49A8;  /* stride 0x4, 19 accesses */

typedef struct {
    unsigned int     f_8;  /* 0x8  x2 */
    unsigned int     f_C;  /* 0xC  x1 */
    unsigned int     f_10;  /* 0x10  x1 */
    unsigned char    f_14;  /* 0x14  x1 */
    unsigned char    f_15;  /* 0x15  x1 */
    unsigned short   f_16;  /* 0x16  x1 */
} S_006AAB40;  /* 7 accesses */

typedef struct {
    unsigned int     f_0;  /* 0x0  x1 */
} S_bl_00558300;  /* stride 0x4, 1 accesses */

typedef struct {
    unsigned int     f_0;  /* 0x0  x1 */
} S_bl_005584D0;  /* stride 0x4, 1 accesses */

typedef struct {
    unsigned int     f_0;  /* 0x0  x1 */
} S_bl_00558510;  /* stride 0x4, 1 accesses */

/* === END recovered struct shapes === */
