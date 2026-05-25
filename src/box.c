/* box.c -- typed sdata / lit4 definitions for this TU.
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


unsigned int D_004BD940[16] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

const char D_004BD980[16] = "\000\354\377\377\000\371\377\377\000(\000\000\000\016";

unsigned int D_004BEA80[20] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

const char D_004BEAD0[48] = ",\000\000\000\003\000\000\000\004\000\000\000\023\000\000\000\024\000\000\000-\000\000\000.\000\000\0001\000\000\0002";

unsigned int D_004BEB00[4] = { 0x00000000, 0xBF800000, 0x00000000, 0x00000000 };

unsigned int D_004BEB10[4] = { 0xBF800000, 0x00000000, 0x00000000, 0x00000000 };

unsigned int D_004BEB20[16] = { 0x00000000, 0xC2200000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x42200000, 0x3F800000, 0x00000000, 0x00000000, 0x42200000, 0x3F800000, 0x00000000, 0x42200000, 0x00000000, 0x3F800000 };

unsigned int D_004BEB60[16] = { 0x00000000, 0xC2200000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0xC2200000, 0x3F800000, 0x00000000, 0x00000000, 0xC2200000, 0x3F800000, 0x00000000, 0x42200000, 0x00000000, 0x3F800000 };

unsigned int D_004BEBA0[24] = { 0x41A00000, 0x00000000, 0x42A00000, 0x3F800000, 0xC1A00000, 0x00000000, 0x42A00000, 0x3F800000, 0x42480000, 0x00000000, 0xC1A00000, 0x3F800000, 0xC2480000, 0x00000000, 0xC1A00000, 0x3F800000, 0xC2480000, 0x00000000, 0x00000000, 0x3F800000, 0xC2480000, 0x00000000, 0x00000000, 0x3F800000 };

unsigned int D_004BEC00[4] = { 0x00000000, 0x00000000, 0x3F800000, 0x00000000 };

unsigned char D_004BEC10[32] = { 0 };

unsigned char D_004BEC30[160] = { 0 };

unsigned char D_004BECD0[32] = { 0 };

unsigned int D_004BECF0[40] = { 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x41A00000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

unsigned int D_004BED90[16] = { 0x40000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000 };

unsigned int D_004BEDD0[16] = { 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x42480000, 0x00000000, 0x00000000, 0x3F800000 };

unsigned int D_004BEE10[4] = { 0x00000000, 0x00000000, 0x00000000, 0x3F800000 };

unsigned int D_004BEE20[16] = { 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000 };

const char D_00618640[40] = "height: %f   dist: %f  ofs: %f %x \n";

const char D_00618668[56] = "\244\263\244\316\303\317\267\301\244\317\244\252\244\253\244\267\244\244\244\307\244\271(100cm\244\313\266\350\300\332\244\351\244\354\244\306\244\244\244\336\244\273\244\363)\n";

const char D_006186A0[16] = "src/box.c";

const char D_006186B0[24] = "front pos: %f, %f, %f\n";

const char D_006186C8[24] = "rear  pos: %f, %f, %f\n";

const char D_00618708[24] = "box die!!!\n";

const char D_00618740[32] = "near wall to %f, %f, %f\n";

const char D_00618760[16] = "BOXREINIT\n";

const char D_00618770[120] = "\033[36m\310\242\244\254\303\317\314\314\244\316\314\265\244\244\244\310\244\263\244\355\244\313\275\351\264\374\307\333\303\326\244\265\244\354\244\306\244\244\244\336\244\271\241\243\n\306\260\272\356\244\254\312\335\276\332\244\307\244\255\244\336\244\273\244\363(\245\263\245\352\245\270\245\347\245\363\304\352\265\301\244\350\244\352\301\260\244\313\310\242\244\254\244\242\244\352\244\336\244\273\244\363\244\253?)\033[m\n";

const char D_006187E8[16] = "\310\242\275\351\264\374\277\345\304\354\307\333\303\326\n";

const char D_006187F8[16] = "\310\242\275\351\264\374\304\314\276\357\307\333\303\326\n";

const char D_00618808[16] = "%f, %f, %f\n";

const char D_00618818[16] = "b_mantle";

const char D_00618828[16] = "tape_boro";

/* Inlined data (Phase 3e) — migrated from box_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* Inlined data (Phase 3e) — migrated from box_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
unsigned int D_00631140 = 0x3E4CCCCD;
unsigned int D_00631144 = 0x3E4CCCCD;
unsigned int D_00631148 = 0x3F34FDF4;
unsigned int D_0063114C = 0x3F34FDF4;
unsigned int D_00631150 = 0x3C23D70B;
unsigned int D_00631154 = 0x4622F983;
unsigned int D_00631158 = 0x3E4CCCCD;
unsigned int D_0063115C = 0x3EA2F983;
unsigned int D_00631160 = 0x3EA2F983;
unsigned int D_00631164 = 0x3D4CCCCD;
unsigned int D_0063116C = 0x428D6667;
unsigned int D_00631170 = 0xBDCCCCCD;
unsigned int D_00631174 = 0x3F666666;
unsigned int D_00631178 = 0x3C23D70B;
unsigned int D_0063117C = 0xBC23D70A;
unsigned int D_00631180 = 0x3F733333;
unsigned int D_00631184 = 0x41A3D70A;
unsigned int D_00631188 = 0x3DCCCCCD;
unsigned int D_00631190 = 0x3F59999A;
unsigned int D_00631194 = 0x3F7AE148;
unsigned int D_00631198 = 0x3F7AE148;
unsigned int D_0063119C = 0x3D4CCCCD;
unsigned int D_006311A0 = 0x47C35000;
unsigned int D_006311A4 = 0x3F7AE148;
unsigned int D_006311A8 = 0x3F59999A;
unsigned int D_006311AC = 0x3F7AE148;
unsigned int D_006311B0 = 0x3DCCCCCD;
unsigned int D_006311B4 = 0x3C23D70A;
unsigned int D_006311B8 = 0x3F666666;
unsigned int D_006311BC = 0x3D4CCCCD;
unsigned int D_006311C0 = 0x3ECCCCCD;
unsigned int D_006311C4 = 0x4197FFF6;
unsigned int D_006311C8 = 0x3D4CCCCD;
unsigned int D_006311CC = 0x3ECCCCCD;
unsigned int D_006311D0 = 0x3F666666;
unsigned int D_006311D4 = 0x3F333333;
unsigned int D_006311D8 = 0x3C23D70A;
unsigned int D_006311DC = 0x3A83126F;
unsigned int D_006311E0 = 0x3D75C28F;
unsigned int D_006311E4 = 0x3F7EB852;
unsigned int D_006311E8 = 0x4622F983;
unsigned int D_006311EC = 0x452AA000;
unsigned int D_006311F0 = 0x4622F983;
unsigned int D_006311F4 = 0x3C23D70A;
unsigned int D_006311F8 = 0x358637BD;
unsigned int D_006311FC = 0x3F4CCCCD;
unsigned int D_00631200 = 0x3F7AE148;
unsigned int D_00631204 = 0x3E4CCCCD;
unsigned int D_00631208 = 0x3E4CCCCD;

/* Inlined data (Phase 3e) — migrated from box_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* pointer / address tables */
void *D_004BD990[1072] = { (void *)0x00618528, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618510, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618500, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006184E8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006184D0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006184C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006184B0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618498, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618480, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618468, (void *)0x006331C0, (void *)0x00618458, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618440, (void *)0x006331C0, (void *)0x00618430, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618418, (void *)0x006331C0, (void *)0x00618400, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618500, (void *)0x006331C0, (void *)0x006183E8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006183D0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006183B8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006183A8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618398, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618380, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618370, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618358, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618340, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618330, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618320, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006184B0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618308, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618500, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006182F8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006182E0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618380, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006182C8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006182B0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618298, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618288, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618268, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618250, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618238, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618228, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618208, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006181F0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006181D8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618250, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006181C8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006181A8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618198, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618180, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006181F0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618170, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618158, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618140, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618130, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006184D0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618118, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618100, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006180E8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006180D0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006180E8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006180B8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006180A0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618088, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618078, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618060, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618050, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618040, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618050, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618020, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618008, (void *)0x006331C0, (void *)0x00617FE8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617FD0, (void *)0x006331C0, (void *)0x00617FA8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617F90, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617F80, (void *)0x006331C0, (void *)0x00617F68, (void *)0x006331C0, (void *)0x00617F58, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617F48, (void *)0x006331C0, (void *)0x00617F30, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617F10, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617F00, (void *)0x006331C0, (void *)0x00617EE8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617ED0, (void *)0x006331C0, (void *)0x00617EB8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617EA0, (void *)0x006331C0, (void *)0x00617E88, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617E70, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617E58, (void *)0x006331C0, (void *)0x00617E30, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617E18, (void *)0x006331C0, (void *)0x00617E30, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617E00, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617DE8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617DD0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617DC0, (void *)0x006331C0, (void *)0x00617DB0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617D90, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617D78, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617D68, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617D50, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617D40, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617D30, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617D18, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617D08, (void *)0x006331C0, (void *)0x00617CF8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617CE8, (void *)0x006331C0, (void *)0x00617CD0, (void *)0x006331C0, (void *)0x00617CC0, (void *)0x006331C0, (void *)0x00617CB0, (void *)0x006331C0, (void *)0x00617CA0, (void *)0x006331C0, (void *)0x00617C90, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617C80, (void *)0x006331C0, (void *)0x00617C70, (void *)0x006331C0, (void *)0x00617C60, (void *)0x006331C0, (void *)0x00617C50, (void *)0x006331C0, (void *)0x00617C38, (void *)0x006331C0, (void *)0x00617C28, (void *)0x006331C0, (void *)0x00617C18, (void *)0x006331C0, (void *)0x00617C00, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617BE8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617BD0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617BC0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617B98, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617B80, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617B60, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617B48, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617B38, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617B28, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617B18, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617AF8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617AE8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617AC0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617AB0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617AA0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617A90, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617A78, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617A68, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617A58, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617A40, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617A28, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617A10, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006179F8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006179E0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006179D0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006179B0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617998, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617978, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617968, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617950, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617940, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617920, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617910, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331B8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006178F8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006178E8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006178D0, (void *)0x006331C0, (void *)0x006178C0, (void *)0x006331C0, (void *)0x006178B0, (void *)0x006331C0, (void *)0x006178A0, (void *)0x006331C0, (void *)0x00617888, (void *)0x006331C0, (void *)0x00617878, (void *)0x006331C0, (void *)0x00617868, (void *)0x006331C0, (void *)0x00617858, (void *)0x006331C0, (void *)0x00617848, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617820, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617810, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006177F8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006177E0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006177C8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006177B8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617798, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617788, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617768, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617758, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617740, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617720, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617708, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006176F0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006176E0, (void *)0x006331C0, (void *)0x006176C8, (void *)0x006331C0, (void *)0x006176B8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006176A0, (void *)0x006331C0, (void *)0x00617688, (void *)0x006331C0, (void *)0x00617670, (void *)0x006331C0, (void *)0x00617660, (void *)0x006331C0, (void *)0x00617650, (void *)0x006331C0, (void *)0x00617638, (void *)0x006331C0, (void *)0x00617620, (void *)0x006331C0, (void *)0x00617608, (void *)0x006331C0, (void *)0x006175F0, (void *)0x006331C0, (void *)0x006175E0, (void *)0x006331C0, (void *)0x006175C8, (void *)0x006331C0, (void *)0x006175B8, (void *)0x006331C0, (void *)0x006175A0, (void *)0x006331C0, (void *)0x00617590, (void *)0x006331C0, (void *)0x00617578, (void *)0x006331C0, (void *)0x00617560, (void *)0x006331C0, (void *)0x00617550, (void *)0x006331C0, (void *)0x00617538, (void *)0x006331C0, (void *)0x00617520, (void *)0x006331C0, (void *)0x00617510, (void *)0x006331C0, (void *)0x006174F8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006174E0, (void *)0x006331C0, (void *)0x006174D0, (void *)0x006331C0, (void *)0x006174B8, (void *)0x006331C0, (void *)0x006174A8, (void *)0x006331C0, (void *)0x00617490, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617478, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617460, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00618500, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617448, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617438, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617418, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x00617400, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006173E8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006173D8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006173C8, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006173B0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0, (void *)0x006331C0 };
void *D_004BEA50[12] = { (void *)0x00633208, (void *)0x00633200, (void *)0x006331F8, (void *)0x006331F0, (void *)0x006331E8, (void *)0x006331E0, (void *)0x006331D8, (void *)0x006331D0, (void *)0x006331C8, (void *)0, (void *)0, (void *)0 };

#include "include_asm.h"
#include "matching.h"

INCLUDE_ASM("asm/nonmatchings/src/box", func_001BCAF0);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BCC18);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BD138);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BD278);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BD408);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BD668);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BD770);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BDA70);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BDC58);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BE120);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BE250);
extern float D_00631168;
void func_00104508(void *buf, void *self);
void func_00105F00(void *dst, void *src);
int func_001684C8(void *struct_arg);
void func_00103C48(void *arg, void *self, int flag, float v, float maxv, float scale, float zero);
void func_00102858(void *arg);

void func_001BE558(int arg, int *self) {
    int local[50];
    int rc;
    float v;
    int *p_15C = (int *)self[0x15C/4];
    float val_3D8 = *(float *)&p_15C[0x3D8/4];
    float clamped = val_3D8;
    if (!(30.0f < val_3D8)) clamped = 30.0f;

    *(float *)((char *)local + 0x70) = clamped;
    func_00104508((char *)local + 0xC0, self);

    {
        float val_270 = *(float *)&((int *)self[0x15C/4])[0x270/4];
        float val_C4 = *(float *)((char *)local + 0xC4);
        val_270 += 10.0f;
        val_C4 += val_270;
        *(float *)((char *)local + 0xC4) = val_C4;
        func_00105F00((char *)local, (char *)local + 0xC0);
    }
    func_00105F00((char *)local + 0x10, (char *)local + 0xC0);

    *(int *)((char *)local + 0x74) = arg;
    *(int *)((char *)local + 0x78) = -1;
    *(int *)((char *)local + 0x7C) = 0;
    func_001684C8((char *)local);
    {
        register int chk __asm__("$2") = *(int *)((char *)local + 0x88);
        if (chk == 0) return;
    }

    {
        int *p2 = (int *)self[0x15C/4];
        int state = p2[0x4D8/4];
        if ((unsigned)(state - 7) >= 10) goto def;
        switch (state) {
        case 7: case 8: case 10: case 15: case 16:
            rc = (p2[0x180/4] == arg);
            goto done;
        default: ;
        }
    def:
        rc = 1;
    done:
        if (rc == 0) return;
    }

    v = *(float *)((char *)local + 0x70);
    v += 50.0f;
    v *= D_00631168;
    func_00103C48((void *)arg, self, 1, v, 100.0f, 0.5f, 0.0f);
    func_00102858((void *)arg);
}
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BE6A8);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BEC30);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BED00);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BEE60);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BEF58);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BF148);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BF2C8);
#if 0
int func_001BF148(void *self, int code);
void func_001BD138(void *self);
void func_001BEF58(void *self);
int func_001BE120(void *self);
void func_001BE6A8(void *self);
void func_001A6E28(const char *fmt, ...);
void func_002641D8(int p, int q, int r);
void func_00118648(void *a, int b, void *c);
void func_0010D838(void *self, void *p);
void func_00102870(void *self, void *p);
extern float D_0063118C;

void func_001BF2C8(int *self) {
    int local[4];
    int *sub = (int *)((int *)self[0x15C/4])[0x800/4];
    register int state __asm__("$5");
    state = sub[0x20/4];
    if ((unsigned)(state + 1) >= 8) goto default_case;
    switch (state + 1) {
    case 0: goto default_case;
    case 1: {
        register int *q __asm__("$4");
        register int *p15c __asm__("$2");
        if (sub[0x58/4] == 0) goto end_no_reload;
        func_001BF148(self, 6);
        p15c = (int *)self[0x15C/4];
        q = (int *)p15c[0x800/4];
        if (q[0x11C/4] == 0) goto skip_body;
        {
            float v = *(float *)((char *)q + 0x48) * D_0063118C / *(float *)((char *)q + 0x124);
            *(short *)((char *)q + 0x120) = (short)(int)((float)*(short *)((char *)q + 0x120) - v);
        }
    skip_body:
        q = local;
        func_002641D8((int)q, 0, 0x10);
        *(float *)((char *)local + 0x8) = 1.0f;
        {
            int *p15c = (int *)self[0x15C/4];
            func_00118648((char *)p15c + 0x520, p15c[0xC/4], local);
        }
        goto end_reload;
    }
    case 2:
    case 7:
        func_001BD138(self);
        goto end_reload;
    case 3:
    case 4:
        func_001BEF58(self);
        goto end_reload;
    case 5:
        if (func_001BE120(self) != 0) {
            ((int *)((int *)self[0x15C/4])[0x800/4])[0x20/4] = 0;
            func_0010D838(self, (char *)(int *)self[0x15C/4] + 0x60);
            func_00102870(self, local);
            ((int *)self[0x15C/4])[0x78/4] = 1;
        }
        goto end_reload;
    case 6:
        func_001BE6A8(self);
        goto end_reload;
    }
default_case:
    func_001A6E28(D_00618708);
end_reload:
    state = sub[0x20/4];
end_no_reload:
    if (state != 6) {
        int *p180 = (int *)sub[0x180/4];
        if (p180[0x16C/4] != 0) p180[0x16C/4] = 0;
    }
}
#endif
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BF460);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BF6A0);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BF7F8);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BF918);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BFFE8);
INCLUDE_ASM("asm/nonmatchings/src/box", func_001C00C0);
