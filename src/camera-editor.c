/* camera-editor.c -- typed sdata / lit4 definitions for this TU.
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

extern int D_00632028;
extern unsigned int D_00632614;
extern const char D_00632618[8];
extern const char D_00632620[8];
extern int D_00632628;
extern int D_0063262C;
extern int D_00632630;
extern int D_00632634;
extern float D_00632638[2];
extern float D_00632640[2];
extern const char D_00632648[8];
extern float D_00632650[2];
extern const char D_00632658[8];
extern const char D_00632660[8];
extern float D_00632668[2];
extern const char D_00632670[8];
extern const char D_00632678[8];
extern const char D_00632680[8];
extern const char D_00632688[];
extern const char D_00632690[];
extern const char D_00632698[];
extern const char D_006326A0[];
extern const char D_006326A8[8];
extern const char D_006326B0[8];
extern const char D_006326B8[];
extern const char D_006326C0[8];
extern const char D_006326C8[8];
extern int D_006326D0;
extern int D_006326D4;
extern char D_006326D8[8];

const char D_0055A5C0[24] = "src/camera-editor.c";

const char D_0055A5D8[56] = "==== Save camera data start ========================\n";

const char D_0055A610[16] = "\tfilename[%s]\n";

const char D_0055A620[16] = "\t    size[%d]\n";

const char D_0055A630[16] = "ico2Data/%s";

const char D_0055A640[48] = "Save Camera Data: host file open error.\n";

const char D_0055A670[56] = "==== Save camera data end ==========================\n";

const char D_0055A6A8[40] = "error---cannot open save camera data";

const char D_0055A6D0[40] = "group[%s]\n%d\t\t%d\t%d\t%d\t\t\t%d\t%d\t%d\n";

const char D_0055A6F8[24] = "group[%s]'s pin\n";

const char D_0055A710[64] = "%s\t%d\t\t%d\t%d\t%d\t\t\t%d\t%d\t%d\n\000\000\000\000\000illegal message %d\n\000\000\000\000\000\000\000\000\000\000\000\000";

/* RGBA color: white at 50% alpha — used for the camera-editor's
 * translucent overlay quads. Each channel is a 32-bit value (not a
 * packed 32-bit pixel) so the GS register write goes lane-by-lane. */
const int D_0055A750[4] = { 255, 255, 255, 128 };

/* Cube face list: 6 faces × 4 vertices each. Vertex indices reference
 * the cube's 8 corners (binary-coded: bit0=X, bit1=Y, bit2=Z). */
const int D_0055A760[6][4] = {
    { 0, 1, 2, 3 },  /* -Z */
    { 1, 3, 5, 7 },  /* +X */
    { 2, 3, 6, 7 },  /* +Y */
    { 0, 2, 4, 6 },  /* -X */
    { 5, 4, 7, 6 },  /* +Z */
    { 1, 0, 5, 4 },  /* -Y */
};

/* Cube edge list: 12 edges × 2 vertex indices (start, end). */
const int D_0055A7C0[12][2] = {
    { 0, 1 }, { 1, 3 }, { 3, 2 }, { 2, 0 },  /* bottom face */
    { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 },  /* vertical edges */
    { 4, 5 }, { 5, 7 }, { 7, 6 }, { 6, 4 },  /* top face */
};

/* RGBA color: opaque white — outline / non-translucent overlay. */
const int D_0055A820[4] = { 255, 255, 255, 255 };

const char D_0055A830[16] = "center-x";

const char D_0055A840[16] = "center-y";

const char D_0055A850[16] = "center-z";

const char D_0055A860[16] = ">>%8s = %d\n";

const char D_0055A870[16] = "  %8s = %d\n";

const char D_0055A880[16] = "camera-x";

const char D_0055A890[16] = "camera-y";

const char D_0055A8A0[16] = "camera-z";

const char D_0055A8B0[16] = "target-x";

const char D_0055A8C0[16] = "target-y";

const char D_0055A8D0[16] = "target-z";

const char D_0055A8E0[16] = "menu_2, arg=%d\n";

const char D_0055A8F0[16] = "menu_1, arg=%d\n";

const char D_0055A900[24] = "\244\263\244\354\260\312\276\345\304\311\262\303\244\307\244\255\244\336\244\273\244\363";

const char D_0055A918[24] = "\244\263\244\354\260\312\276\345\272\357\275\374\244\307\244\255\244\336\244\273\244\363";

const float D_0055A930[4] = { 0.0f, 2e+02f, 5e+02f, 0.0f };

#include "include_asm.h"

INCLUDE_ASM("asm/nonmatchings/src/camera-editor", func_00182D20);
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", func_00182DD8);
INCLUDE_ASM("asm/nonmatchings/src/camera-editor", func_00182F20);
