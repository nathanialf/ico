/* queen.c -- typed sdata / lit4 definitions for this TU.
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


float D_0028C990[24] = { 1200.0f, -1000.0f, 300.0f, 0.0f, 1200.0f, -1000.0f, -100.0f, 0.0f, 1100.0f, -1000.0f, 100.0f, 0.0f, 800.0f, -920.0f, 200.0f, 0.0f, 600.0f, -900.0f, -200.0f, 0.0f, 400.0f, -900.0f, 100.0f, 0.0f };

unsigned int D_0028C9F0[8] = { 0x00000000, 0x00000001, 0x00000002, 0x00000003, 0x00000004, 0x00000008, 0x00000009, 0x00000000 };

unsigned int D_0028CA10[8] = { 0x00000000, 0x00000001, 0x00000002, 0x00000004, 0x00000005, 0x00000006, 0x00000007, 0x00000000 };

unsigned char D_0028CA30[24] = { 0 };

unsigned char D_0028CA48[64] = { 0 };

unsigned int D_0028CA88[210] = { 0x00000009, 0x0000000A, 0x00000015, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x000005EB, 0x00000015, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000008E, 0x00000091, 0x00000015, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000008F, 0x00000092, 0x00000015, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000090, 0x00000093, 0x00000015, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000267, 0x00000091, 0x00000015, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000081, 0x00000082, 0x00000015, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000085, 0x00000088, 0x00000015, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000086, 0x00000089, 0x00000015, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000087, 0x0000008A, 0x00000015, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000083, 0x00000084, 0x00000015, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000008B, 0x0000008C, 0x00000015, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000007E, 0x0000038E, 0x00000015, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000007E, 0x000005EB, 0x00000015, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000004B, 0x000005EB, 0x00000015, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000269, 0x000005EB, 0x00000005, 0x420C0000, 0x42480000, 0xC2480000, 0xC23E0000, 0xC28C0000, 0x42F00000, 0x42B40000, 0x00000354, 0x000005EB, 0x00000015, 0x42200000, 0x41C80000, 0xC2960000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000037B, 0x000005EB, 0x00000015, 0x420C0000, 0x42340000, 0xC2340000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000002AE, 0x000005EB, 0x00000015, 0x42180000, 0x41E00000, 0xC2140000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x0000027D, 0x000005EB, 0x00000015, 0xC4C1C000, 0xC5098000, 0x43E10000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000005FF, 0x000005EB, 0x00000015, 0xC4C1C000, 0xC5098000, 0x43E10000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

const float D_0055C2C0[12] = { 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.0f };

const float D_0055C2F0[66] = { 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f };

const float D_0055C3F8[12] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f };

const float D_0055C428[12] = { 3.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f };

const float D_0055C458[12] = { 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 0.0f };

const float D_0055C488[12] = { 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.0f };

const float D_0055C4B8[66] = { 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f };

const char D_0055C5C0[16] = "queen attacked\n";

const char D_0055C5D0[16] = "enemy dead %p\n";

unsigned int D_0055C5E0[6] = { 0x000007B1, 0x000007B2, 0x000007B3, 0x000007B4, 0x000007B5, 0x000007B6 };

unsigned int D_0055C5F8[6] = { 0x00000CC0, 0x00000CC1, 0x00000CC2, 0x00000CC3, 0x00000CC4, 0x00000CC5 };

const char D_0055C610[16] = "\006\000\000\000\340\305U\000\006\000\000\000\370\305U";

const char D_0055C620[40] = "n_enemy_max:%d n_enemy:%d counter:%d";

const char D_0055C648[16] = "queen dead\n";

const char D_0055C658[24] = "queen_ball_scr";

const char D_0055C690[16] = "src/queen.c";

const char D_0055C6A0[24] = "queen barrier attacked\n";

unsigned int D_0055C6B8[2] = { 0x000007AF, 0x00000000 };

unsigned int D_0055C6C0[2] = { 0x00000CB8, 0x00000000 };

const char D_0055C6C8[16] = "damage:%d";

const char D_0055C6D8[16] = "mail %d\n";

const char D_0055C6E8[24] = "queen ball attacked\n";

const float D_0055C700[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

const char D_0055C710[16] = "\000\360\377\377\000\370\377\377\000 \000\000\000\020";

const char D_0055C720[32] = "queen barrier damaged\n";

const float D_0055C740[4] = { 2.5e+02f, 1.5e+02f, 2e+02f, 0.0f };

const float D_0055C750[4] = { 1e+02f, 1.2e+02f, 115.0f, 0.0f };

unsigned int D_0055C760[398] = { 0x37347473, 0x00000061, 0x00000000, 0x00000000, 0x00000000, 0x43480000, 0xC3AF0000, 0xC46D8000, 0x00000000, 0xC4DAC000, 0x00000000, 0x38317473, 0x00000061, 0x00000000, 0x00000000, 0xC0490FD0, 0xC5979000, 0xC4CE4000, 0x45403000, 0xC5228000, 0xC46D8000, 0x44ABE000, 0x31307473, 0x00000062, 0x00000000, 0x00000000, 0xBFC90FF9, 0xC5976800, 0xC507F000, 0x45BFE000, 0xC59AB000, 0xC4F0A000, 0x45C28800, 0x39307473, 0x00000061, 0x00000000, 0x00000000, 0x40490FD0, 0xC58A4800, 0xC4D48000, 0x46115000, 0xC58A4800, 0xC4D48000, 0x46115000, 0x33307473, 0x00000074, 0x00000000, 0x00000000, 0x3FC90FF9, 0xC53EA000, 0xC4674000, 0x459F6000, 0xC5435000, 0xC4A8C000, 0x45B3B000, 0x30317473, 0x0000006C, 0x00000000, 0x00000000, 0x40490FD0, 0xC485C000, 0x43ED8000, 0x45B0E000, 0xC4898000, 0x43ED8000, 0x45947000, 0x34307473, 0x00000061, 0x00000000, 0x00000000, 0x3FC90FF9, 0x45960000, 0xC4DAC000, 0xA9EA64F4, 0x45CB2000, 0xC4DAC000, 0x00000000, 0x34307473, 0x00000062, 0x00000000, 0x00000000, 0x3FC90FF9, 0x45B2E800, 0x434D0000, 0x45467000, 0x45CCB000, 0xC4C80000, 0x43480000, 0x34307473, 0x00000063, 0x00000000, 0x00000000, 0x40490FD0, 0x45CCD800, 0x44520000, 0x463CFC00, 0x45CCB000, 0x43AF0000, 0x46160000, 0x34307473, 0x00000064, 0x00000000, 0x00000000, 0xC0490FD0, 0x45CCB000, 0x44816000, 0x465D5400, 0x45CCB000, 0x43AF0000, 0x46179000, 0x34307473, 0x00000065, 0x00000000, 0x00000000, 0x40490FD0, 0x45BD3800, 0x449A6000, 0x467CF800, 0x45CCB000, 0x43AF0000, 0x4619E800, 0x35307473, 0x00000062, 0x00000000, 0x00000000, 0x3FC90FF9, 0x45A0C800, 0x43340000, 0xC522D000, 0x45CCB000, 0xC4C80000, 0xC2480000, 0x35307473, 0x00000063, 0x00000000, 0x00000000, 0x00000000, 0x45CCB000, 0x44A0A000, 0xC639B400, 0x45CCB000, 0x442F0000, 0xC613A800, 0x35307473, 0x00000064, 0x00000000, 0x00000000, 0x00000000, 0x45CCB000, 0x44E6A000, 0xC65A0C00, 0x45CCB000, 0x442F0000, 0xC613A800, 0x35307473, 0x00000065, 0x00000000, 0x00000000, 0x00000000, 0x45B6A800, 0x44C80000, 0xC6770800, 0x45CCB000, 0x442F0000, 0xC6153800, 0x32307473, 0x00000061, 0x00000000, 0x00000000, 0xBFC90FF9, 0xC57C3000, 0xC43F4000, 0xC546C000, 0xC570A000, 0xC3E10000, 0xC53B8000, 0x36307473, 0x00000061, 0x00000000, 0x00000000, 0xBFC90FF9, 0xC5DC5000, 0x43910000, 0xC5386000, 0xC5DC5000, 0xC3E10000, 0xC5386000, 0x32327473, 0x00000061, 0x00000000, 0x00000000, 0x00000000, 0x45EEC000, 0xC5B13000, 0xC5039000, 0x46228000, 0xC5B6D000, 0x44B54000, 0x39317473, 0x00000061, 0x00000000, 0x00000000, 0x00000000, 0xC5C96800, 0xC50CA000, 0xC5958800, 0xC5A5A000, 0xC50CA000, 0xC50CA000, 0x30327473, 0x00000061, 0x00000000, 0x00000000, 0x00000000, 0xC588E000, 0xC55B1000, 0xC617F400, 0xC59DD000, 0xC5228000, 0xC5FA0000, 0x30317473, 0x00000072, 0x00000000, 0x00000000, 0x00000000, 0xC42B4000, 0x40A00000, 0xC5AD7000, 0xC4B54000, 0x44098000, 0xC5FB9000, 0x39317473, 0x00000062, 0x00000000, 0x00000000, 0x00000000, 0xC59DF800, 0xC5A16800, 0xC5980800, 0xC5A5A000, 0xC50CA000, 0xC50CA000, 0x37317473, 0x00000062, 0x00000000, 0x00000000, 0x00000000, 0xC64A8000, 0xC5BDD800, 0xC55C0000, 0xC59AB000, 0xC5EBF000, 0xC5B09000, 0x37317473, 0x00000061, 0x00000000, 0x00000000, 0x00000000, 0xC65E5800, 0xC2200000, 0x43E38000, 0xC68E9400, 0xC5066000, 0xC4228000, 0x38307473, 0x00000061, 0x00000000, 0x00000000, 0x00000000, 0xC6144800, 0x442A0000, 0x4539A000, 0xC6027800, 0xC51F6000, 0x43E10000, 0x37307473, 0x00000061, 0x00000000, 0x00000000, 0x40490FD0, 0xC5866000, 0xC3ED8000, 0x2A6A600D, 0xC5BB8000, 0x00000000, 0xC46D8000, 0x30307473, 0x00000061, 0x00000000, 0x00000000, 0xBFC90FF9, 0xC6250000, 0xC3160000, 0x42480000, 0xC6160000, 0xC3960000, 0x42480000, 0x33317473, 0x00000063, 0x00000000, 0x00000000, 0xC0490FD0, 0xC691B400, 0xC3660000, 0x43E10000, 0xC691B400, 0xC3FA0000, 0x43E10000, 0x33317473, 0x00000064, 0x00000000, 0x00000000, 0x40490FD0, 0xC6917800, 0x451C9000, 0x43E10000, 0xC691B400, 0xC3FA0000, 0x43E10000, 0x33317473, 0x00000062, 0x00000000, 0x00000000, 0x40490FD0, 0xC6C22400, 0xC3D70000, 0x43E10000, 0xC6C22400, 0xC4610000, 0x43E10000, 0x33317473, 0x00000061, 0x00000000, 0x00000000, 0x00000000, 0xC6BB8A00, 0xC5EE2000, 0x43F28000, 0xC6966400, 0xC5C67000, 0xC5002000, 0x34327473, 0x00000061, 0x00000000, 0x00000000, 0xBFC90FF9, 0xC6A6A400, 0xC6234800, 0x43C30000, 0xC6A08C00, 0xC6234800, 0xC42F0000, 0x35327473, 0x00000061, 0x00000000, 0x00000000, 0x00000000, 0xC6C35000, 0x45910000, 0x43E10000, 0xC6C35000, 0x45A8C000, 0x43E10000, 0x34327473, 0x00000062, 0x00000000, 0x00000000, 0xBFC90FF9, 0xC6A02800, 0xC6234800, 0xC4160000, 0xC6A02800, 0xC6234800, 0xC4160000, 0x37327473, 0x00000061, 0x00000000, 0x00000000, 0x3FC90FF9, 0x46D57A00, 0xC6405800, 0x47971D00, 0x46E42000, 0xC641C000, 0x47975E00, 0x00000000, 0x692F2E2E, 0x692F6F74, 0x756C636E, 0x6D2F6564, 0x65645F76, 0x682E7366, 0x00000000, 0x00000000, 0x3D212070, 0x4C554E20, 0x0000004C, 0x00000000 };

const char D_0055CD98[16] = "movie pause\n";

const char D_0055CDA8[16] = "D_CTRL %x\n";

const char D_0055CDB8[24] = "open movie file %s\n";

const char D_0055CDD0[32] = "create video decode thread\n";

const char D_0055CDF0[16] = "start thread\n";

const char D_0055CE00[16] = "add intc\n";

const char D_0055CE10[24] = "add intc failed\n";

const char D_0055CE28[16] = "add dmac\n";

const char D_0055CE38[24] = "add dmac failed\n";

const char D_0055CE50[24] = "sceGsGetIMR() %lx\n";

const char D_0055CE68[16] = "dmac %d %d\n";

const char D_0055CE78[16] = "intc %d %d\n";

const char D_0055CE88[24] = "movie init failed\n";

const char D_0055CEA0[16] = "movie end\n";

const char D_0055CEB0[32] = "../ito/include/mv_defs.h";

const char D_0055CED0[64] = "p != NULL\000\000\000\000\000\000\000../ito/include/mv_defs.h\000\000\000\000\000\000\000\000p != NULL\000\000\000\000\000\000";

const char D_0055CF10[32] = "../ito/include/mv_defs.h";

const char D_0055CF30[16] = "p != NULL";

const char D_0055CF40[24] = "pts buffer overflow\n";

const char D_0055CF58[24] = "decode thread: aborted\n";

const char D_0055CF70[40] = "sceMpegGetPicture() decode error";

const char D_0055CF98[16] = "movie %d x %d\n";

const char D_0055CFA8[32] = "../ito/include/mv_defs.h";

const char D_0055CFC8[16] = "p != NULL";

const char D_006327F0[8] = "barr %d";

unsigned int D_006327F8 = 0x80808080;

unsigned int D_006327FC = 0x00000000;

const char D_00632800[8] = "%s";

unsigned int D_00632808 = 0x00000001;

unsigned int D_0063280C = 0x00000000;

unsigned char D_00632810[8] = { 0 };

const char D_00632818[8] = "= %d =\n";

const char D_00632820[8] = "%s\n";

float D_00632828[2] = { -7.688999e-06f, 0.0f };

/* Inlined data (Phase 3e) — migrated from queen_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
float D_00631068 = 0.001f;
float D_00631078 = 0.05235988f;
float D_0063107C = 0.08726647f;
float D_00631080 = 0.122173056f;
float D_00631084 = 0.02f;
float D_00631088 = 0.05f;
float D_0063108C = 6.2831855f;
float D_00631090 = 3.1415927f;
float D_00631094 = 6.2831855f;
float D_00631098 = -3.1415927f;
float D_0063109C = 6.2831855f;
float D_006310A0 = 6.2831855f;
float D_006310A4 = 3.1415927f;
float D_006310A8 = 6.2831855f;
float D_006310AC = -3.1415927f;
float D_006310B0 = 6.2831855f;
float D_006310B4 = 6.2831855f;
float D_006310B8 = 3.1415927f;
float D_006310BC = 6.2831855f;
float D_006310C0 = -3.1415927f;
float D_006310C4 = 6.2831855f;
float D_006310C8 = 5000.0f;
float D_006310CC = 2340.5715f;
float D_006310D0 = 10430.378f;
float D_006310D4 = 0.333f;
float D_006310D8 = 3.1415927f;

#include "include_asm.h"
#include "ico/types.h"
#include "regpin.h"
#include "matching.h"

extern int *func_0013EB50(int a0);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019A7E8);
extern char D_00274ED4[];
extern int D_00633DD8;
extern float D_0063106C;
extern float D_00631070;
extern float D_00631074;
extern void func_001E3FC8(int *self);
extern void func_001BB8C0(int *self, int a, int b, int c);
extern void func_001C8218(int x, float a, float b);
extern void func_00103D50(int *self, int a, float b, float c, float d);
INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019A8F0);
extern int *D_00631AE4;
extern void func_001504D8(int *p);
extern void func_0010ECD8(void);
extern void func_0010ECB8(int *self);
extern void func_001C62D0(int a, char *b, char *c);

void func_0019A9A0(int *self)
{
    if (D_00631AE4 != 0) {
        func_001504D8(D_00631AE4);
    }
    func_0010ECD8();
    func_0010ECB8(self);
    {
        Sub15C *sub = ((GObj *)((char *)self))->p_15C;
        Obj800 *inner = ((Sub15C *)(sub))->p_800;
        if (*(int *)((char *)inner + 0xC) != 0) {
            char *q = *(char **)((char *)sub + 0x844);
            func_001C62D0(*(int *)((char *)inner + 0x10), q + 0x40, q);
            sub = ((GObj *)((char *)self))->p_15C;
        }
        {
            char *q = *(char **)((char *)sub + 0x844);
            func_001C62D0(*(int *)((char *)inner + 0x14), q + 0x40, q);
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019AA20);
extern void func_0019C280(float x);
void func_0019AE50(int *self)
{
    Sub15C *p = ((int *)((GObj *)(self))->p_15C)[0x800 / 4];
    if (*(signed char *)((char *)p + 0x12) == 0) return;
    {
        float f = (float)p->f_18;
        func_0019C280(1.0f - f / 5.0f);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019AE98);
INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019B660);
extern int *func_00202208(int *self);
extern void func_00203AA0(int x);
extern void func_00203B78(void *func, int id);
extern int func_001E29E8(int *self, int x, int *arg);
extern char D_00199F80[];
extern int func_0019BCE0(void);
extern int func_00199C30(void);
void func_0019B7F8(int *self)
{
    int *p = func_00202208(self);
    func_00202148(self);
    func_00203AA0(1);
    func_00203B78((void *)D_00199F80, 0x14);
    func_00203B78((void *)func_0019BCE0, 0x15);
    func_00203B78((void *)func_00199C30, 0x15);
    p[0x120 / 4] = func_001E29E8(self, 0xEE, p + 0x610 / 4);
    ((int *)self[0x15C / 4])[0x7C / 4] = 1;
}
extern int func_0013EBE0(int iter);
void func_0019B888(void)
{
    int *obj1 = func_0013EB50(0x2E);
    int *iter;
    *((char *)((int *)((GObj *)(obj1))->p_15C)[0x800 / 4] + 1) = 1;
    iter = func_0013EB50(0x35);
    while (iter != 0) {
        *((char *)((int *)((GObj *)(iter))->p_15C)[0x800 / 4] + 0x12) = 1;
        iter = (int *)func_0013EBE0((int)iter);
    }
}

int func_0019B8E8(void)
{
    int v0 = (int)func_0013EB50(0x2E);
    int v1 = (int)((GObj *)(v0))->p_15C;
    int a0 = (int)((Sub15C *)(v1))->p_800;
    return *(signed char *)(a0 + 0x3);
}

int func_0019B910(void)
{
    int v0 = (int)func_0013EB50(0x2E);
    int v1 = (int)((GObj *)(v0))->p_15C;
    int a0 = (int)((Sub15C *)(v1))->p_800;
    return *(int *)(a0 + 0x4);
}

float func_0019B938(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = ((Sub15C *)(sub))->p_800;
    return *(float *)(p + 0x14);
}

int func_0019B948(void)
{
    int *p;
    int ret = 0;
    p = (int *)((int *)func_0013EB50(0x2E)[0x15C / 4])[0x800 / 4];
    if (p[0x4 / 4] > 0 || p[0x8 / 4] > 0) {
        ret = 1;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019B998);

int func_0019BA60(void)
{
    int ret = 0;
    int *p;
    int *q;
    int *r;
    p = func_0013EB50(0x35);
    if (p != 0) {
        q = (int *)((GObj *)(p))->p_15C;
        r = (int *)((Sub15C *)(q))->p_800;
        ret = r[0x18 / 4] < 5;
    }
    return ret;
}

INCLUDE_ASM_NOP_PAD(func_0019BAA4);
extern void func_0019C558(void);
extern int D_00632010;
extern int func_0013A0F8(int handle, int size, const char *file, int line);
extern void func_002641D8(int *buf, int val, int size);
extern void func_00104508(int *buf, int *self);
int *func_0019BAA8(int *self)
{
    register int *p;
    int *buf;
    p = (int *)((GObj *)(self))->p_15C;
    buf = (int *)func_0013A0F8(D_00632010, 0x30, D_0055C690, 0x3DA);
    func_002641D8(buf, 0, 0x30);
    (int)((Sub15C *)(p))->p_800 = (int)buf;
    *((float *)((char *)buf + 0x14)) = 300.0f;
    func_00104508(buf, self);
    func_00202208(self);
    func_00202148(self);
    func_0019C558();
    return buf;
}

float func_0019BB40(int a0)
{
    return *(float *)(*(int *)((int)((GObj *)(a0))->p_15C + 0x800) + 0x14) * 100.0f;
}

INCLUDE_ASM_NOP_PAD(func_0019BB5C);
INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019BB60);
int *func_0019BC58(int *self)
{
    register int *p;
    register int *s = self;
    int *buf;
    p = (int *)((GObj *)(s))->p_15C;
    buf = (int *)func_0013A0F8(D_00632010, 0x20, D_0055C690, 0x4F4);
    (int)((Sub15C *)(p))->p_800 = (int)buf;
    func_002641D8(buf, 0, 0x20);
    *((int *)((char *)buf + 0x14)) = 0;
    func_00104508(buf, s);
    func_00202208(s);
    func_00202148(s);
    return buf;
}
INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019BCE0);


/* === BEGIN recovered struct shapes (tools/place_struct_shapes.py) === */
/* Field layouts mined from load/store access patterns; SPARSE
 * (only touched offsets, no padding). Unused typedefs — they add
 * no symbol and cannot affect codegen. Cast as ((S_<VMA> *)D_<VMA>).
 */

typedef struct {
    short            f_0;  /* 0x0  x8 */
} S_006D43B0;  /* stride 0x2, 8 accesses */

typedef struct {
    unsigned int     f_0;  /* 0x0  x2 */
    unsigned int     f_8;  /* 0x8  x1 */
} S_0028CA88;  /* stride 0x28, 3 accesses */

/* === END recovered struct shapes === */
