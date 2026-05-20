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
extern float D_00630C24;
extern float D_00630C28;
extern float D_00630C2C;
extern float D_00630C30;
extern float D_00630C34;
extern float D_00630C38;
extern float D_00630C3C;
extern float D_00630C40;
extern float D_00630C44;
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
extern const char D_006322B0[8];
extern int D_006322B8;
extern int D_006322BC;
extern int D_006322C0;
extern int D_006322C4;
extern int D_006322C8;
extern int D_006322CC;
extern const char D_006322D0[8];
extern const char D_006322D8[8];
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

__attribute__((section(".rodata.0x005582C8"))) const char D_005582C8[16] = "src/boyact.c";

__attribute__((section(".rodata.0x00558788"))) const char D_00558788[24] = "critical hit to boss!!!";

/* D_005581F0 .. D_005582B0 (10 "boy{act,mot}Hand{50,100,200}" + sync
 * strings, plus "boy after func", "boy error flg get", "boy error",
 * "%s sync error") moved to src/act-parallel-control.c — they sit
 * in apc's rodata range (between apc and boyact anchors). */

/* String rodata migrated from boyact_data.c */
__attribute__((section(".rodata.0x005582D8"))) const char D_005582D8[24] = "speed = %f (%f)\n";
__attribute__((section(".rodata.0x005582F0"))) const char D_005582F0[16] = "%f / %f\n";
__attribute__((section(".rodata.0x005584E8"))) const char D_005584E8[16] = "%d -> %d\n";
__attribute__((section(".rodata.0x00558640"))) const char D_00558640[24] = "enter actBoyFall\n";
__attribute__((section(".rodata.0x00558658"))) const char D_00558658[24] = "attack sub id [%d]\n";
__attribute__((section(".rodata.0x00558670"))) const char D_00558670[24] = "enter actBoyAttack\n";
__attribute__((section(".rodata.0x00558688"))) const char D_00558688[24] = "enter actBoyCall\n";
__attribute__((section(".rodata.0x005586A0"))) const char D_005586A0[24] = "enter actBoyItemAfter\n";
__attribute__((section(".rodata.0x005586B8"))) const char D_005586B8[40] = "enemy error body slam[%s]\n";
__attribute__((section(".rodata.0x005586F0"))) const char D_005586F0[16] = "actBoyStart:%p\n";
__attribute__((section(".rodata.0x005587A0"))) const char D_005587A0[32] = "!!! unable guard flag get\n";
__attribute__((section(".rodata.0x005587C0"))) const char D_005587C0[16] = "guard mail\n";
__attribute__((section(".rodata.0x005587D0"))) const char D_005587D0[32] = "guard error=[%d][%d][%d][%d]\n";
__attribute__((section(".rodata.0x005587F0"))) const char D_005587F0[16] = "die!!!!!!!!!!!\n";
__attribute__((section(".rodata.0x00558800"))) const char D_00558800[24] = "down!!!!!!!!!!!\n";

/* Float rodata migrated from boyact_data.c */
__attribute__((section(".rodata.0x00558628"))) const float D_00558628[2] = { -107374184.0f, 1.8499999f };
__attribute__((section(".rodata.0x005586E0"))) const float D_005586E0[4] = { -1e+06f, 0.0f, 0.0f, 0.0f };
__attribute__((section(".rodata.0x00558700"))) const float D_00558700[4] = { 0.0f, 0.0f, -5e+01f, 1.0f };
__attribute__((section(".rodata.0x00558710"))) const float D_00558710[4] = { 0.0f, 0.0f, 5e+01f, 1.0f };

/* Single-float rodata migrated from boyact_data.c */

/* String-pool rodata migrated from boyact_data.c */
__attribute__((section(".rodata.0x00558758"))) const char D_00558758[48] = "hand connect start\n\000\000\000\000\000WBP set [landing]\n\000\000\000\000\000";
__attribute__((section(".rodata.0x00558818"))) const char D_00558818[48] = "damage!!!!!!!!!!!  %d\n\000\000WBP set [with mail]\n\000\000\000";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "！！！ソファの壁を見付けることができません！！！
" */
__attribute__((section(".rodata.0x00558720"))) const char D_00558720[56] = "\241\252\241\252\241\252\245\275\245\325\245\241\244\316\312\311\244\362\270\253\311\325\244\261\244\353\244\263\244\310\244\254\244\307\244\255\244\336\244\273\244\363\241\252\241\252\241\252\n";

#include "include_asm.h"
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
    sub = *(char **)((char *)obj_ptr + 0x15C);
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
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_001504D8);
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
    KEEP_LIVE(buf);
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
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00154390);

/* Matched body inlined from src/cod/054420.c during TU coalesce. */
int func_00154420(void)
{
    int *v0 = (int *)D_00631AE4;
    int *v1 = (int *)v0[0x164 / 4];
    unsigned int a = v1[0x30 / 4];
    register int ret REG("$2");
    ret = 1;
    if (a >= 0x5D) goto end;
    ret = a < 0x5B;
end:
    return ret;
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
INCLUDE_ASM("asm/nonmatchings/src/boyact", func_00154B20);
