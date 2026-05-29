/* enemy_act.c -- typed sdata / lit4 definitions for this TU.
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

extern float D_00630AEC;
extern float D_00630CE0;
extern float D_00630CE4;
extern float D_00630CE8;
extern float D_00630CEC;
extern float D_00630CF0;
extern float D_00630CF4;
extern float D_00630CF8;
extern float D_00630CFC;
extern float D_00630D00;
extern float D_00630D04;
extern float D_00630D08;
extern float D_00630D0C;
extern float D_00630D10;
extern float D_00630D14;
extern float D_00630D18;
extern float D_00630D1C;
extern float D_00630D20;
extern float D_00630D24;
extern float D_00630D28;
extern float D_00630D2C;
extern float D_00630D30;
extern float D_00630D34;
extern float D_00630D38;
extern float D_00630D3C;
extern float D_00630D40;
extern float D_00630D44;
extern float D_00630D48;
extern float D_00630D4C;
extern float D_00630D50;
extern float D_00630D54;
extern float D_00630D58;
extern float D_00630D5C;
extern float D_00630D60;
extern float D_00630D64;
extern float D_00630D68;
extern float D_00630D6C;
extern float D_00630D70;
extern float D_00630D74;
extern float D_00630D78;
extern float D_00630D7C;
extern float D_00630D80;
extern float D_00630D84;
extern float D_00630D88;
extern float D_00630D8C;
extern float D_00630D90;
extern float D_00630D94;
extern int D_00631B10;
extern int D_00631B14;
extern char D_00631B18[8];
extern int D_00632390;
/* KEEP_DEF: D_00632398 must be declared as array (not scalar) so
 * ee-gcc's small-data gp_rel optimization stays off, matching original. */
extern int D_00632398[];
extern int D_006325B0;
extern char D_00632DC0[8];
extern int D_00632DC8;
extern int D_00632DCC;
extern const char D_00632DD0[8];
extern const char D_00632DD8[8];
extern const char D_00632DE0[8];
extern const char D_00632DE8[8];
extern const char D_00632DF0[8];
extern const char D_00632DF8[8];
extern const char D_00632E00[8];
extern const char D_00632E08[8];
extern const char D_00632E10[8];
extern const char D_00632E18[8];
extern const char D_00632E20[8];
extern const char D_00632E28[8];
extern const char D_00632E30[8];
extern const char D_00632E38[8];
extern const char D_00632E40[8];
extern const char D_00632E48[8];
extern const char D_00632E50[8];
extern const char D_00632E58[8];
extern const char D_00632E60[8];
extern unsigned int D_00632E68;
extern int D_00632E6C;
extern unsigned int D_00632E70;
extern int D_00632E74;
extern const char D_00632E78[8];
extern const char D_00632E80[8];
extern const char D_00632E88[8];
extern const char D_00632E90[8];
extern const char D_00632E98[8];
extern const char D_00632EA0[8];
extern const char D_00632EA8[8];
extern const char D_00632EB0[8];
extern const char D_00632EB8[8];
extern const char D_00632EC0[8];
extern unsigned int D_00632EC8;
extern int D_00632ECC;
extern int D_00632ED0;
extern float D_00632ED4;
extern float D_00632ED8;
extern unsigned int D_00632EDC;
extern unsigned int D_00632EE0;
extern unsigned int D_00632EE4;
extern int D_00632EE8;
extern short D_00632EEC;
extern char D_00632EEE;
extern char D_00632EEF;
extern int D_00632EF0;
extern int D_00632EF4;
extern int D_00632EF8;
extern int D_00632EFC;
extern const char D_00632F00[8];
extern const char D_00632F08[8];
extern const char D_00632F10[8];
extern const char D_00632F18[8];
extern const char D_00632F20[8];
extern int D_00632F28;
extern int D_00632F2C;
extern int D_00632F30;
extern int D_00632F34;
extern int D_00632F38;
extern int D_00632F3C;
extern int D_00632F40;
extern int D_00632F44;
extern int D_00632F48;
extern int D_00632F4C;
extern const char D_00632F58[12];
extern int D_00632F64;
extern int D_00632F68;
extern int D_00632F6C;
extern int D_00632F70;
extern int D_00632F74;
extern int D_00632F78;
extern int D_00632F7C;
extern char D_00632F80[8];

const char D_00558E10[16] = "src/enemy_act.c";

const char D_00558E20[32] = "*generator_gop!=NULL";

const char D_00558ED8[24] = "enter actEnemyStand\n";

const char D_00558EF0[24] = "enter motEnemyStand\n";

const char D_00558F08[24] = "enter actEnemyWalk\n";

const char D_00558F20[24] = "enter motEnemyWalk\n";

const char D_00558F38[24] = "enter actEnemyRun\n";

const char D_00558F50[24] = "enter motEnemyRun\n";

const char D_00558F68[24] = "enter actEnemyJump\n";

const char D_00558F80[32] = "enter actEnemyHang\n";

const float D_00558FA0[4] = { 0.0f, 0.0f, -1e+06f, 0.0f };

const char D_00558FB0[40] = "ASSERTMSG__GOP_IS_NOT_ENEMY(gop)";

const float D_00558FD8[2] = { 89128.96f, 1.035f };

const char D_00558FE0[32] = "undefined mode [%d]\n";

const char D_00559030[24] = "to generator way error!";

const float D_00559048[2] = { 4.172325e-08f, 1.9f };

const float D_00559050[2] = { 4.172325e-08f, 1.9f };

const float D_00559058[2] = { 4.172325e-08f, 1.9f };

const char D_00559060[16] = "not found";

const float D_00559070[2] = { 0.0f, 3.8515625f };

const float D_00559078[2] = { 0.0f, 3.7636719f };

const char D_00559080[40] = "**toboy function start :: count=[%d]\n";

const char D_005590A8[16] = "await start\n";

const char D_005590B8[24] = "!!! wwarning !!!\n";

const char D_005590D0[48] = "return value error :: [Battle_isCurrentStatus]\n";

const char D_00559100[16] = "await end\n";

const char D_00559110[24] = "toboy ra is [%d]\n";

const float D_00559128[2] = { 4.172325e-08f, 1.9f };

const char D_00559168[112] = "change to kidnap\000\000\000\000\000\000\000\000_ACTMotReqTimer wait\n\000\000\000_ACTMotReqTimer error loop\n\000\000\000\000\000\tmail[%d] can not accept\n\000\000\000\000\000\000";

const char D_005591D8[24] = "actEnemyStart:%p\n";

unsigned int D_0063239C = 0x00000000;

unsigned int D_006323A0 = 0x7F7FFFFF;

unsigned int D_006323A4 = 0x7F7FFFFF;

unsigned int D_006323A8 = 0x7F7FFFFF;

unsigned int D_006323AC = 0x7F7FFFFF;

unsigned char D_006323B0[12] = { 0 };

unsigned int D_006323BC = 0x00000000;

/* Inlined data (Phase 3e) — migrated from enemy_act_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* C-referenced data (extern kept, def supplies bytes) */
int D_00632398[1] = { 0x00000030 };

/* Inlined data (Phase 3e) — migrated from enemy_act_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* C-referenced data (extern kept, def supplies bytes) */
int D_00632390 = 0x00000000;
unsigned int D_00632394 = 0x00000000;

#include "include_asm.h"
#include "matching.h"
#include "regpin.h"

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_0015F6F0);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_0015F800);

/* Matched body inlined from src/cod/05F9B0.c during TU coalesce. */
extern void func_0015F800(int *self, int a1);
void func_0015F9B0(int *self, int a1)
{
    char *p;
    int i;
    p = (char *)((int *)self[0x59])[0x19C] + 0x360;
    i = 0;
    do {
        if (*(signed char *)(p + 0x1D) != 0) {
            if (*(int *)(p + 0x14) == a1) {
                return;
            }
        }
        i++;
        p += 0x20;
    } while (i < 5);
    func_0015F800(self, a1);
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_0015F9F4);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_0015F9F8);

/* Matched body inlined from src/cod/05FB60.c during TU coalesce. */
extern int D_00631AE4;
extern char D_00565060[];
extern void func_0014B228(int *self, int x);
extern void func_00165B80(int *self, int a1, int a2);
void func_0015FB60(int *self) {
    int *p, *entry;
    int idx;
    unsigned int v;
    if (D_00631AE4 != 0) {
        func_0014B228(self, 0x1B);
        p = (int *)self[0x15C / 4];
        idx = p[0x4A0 / 4] * 0x190;
        entry = (int *)(D_00565060 + idx);
        v = entry[0x188 / 4];
        if (((v >> 1) & 1) != 0) {
            func_00165B80(self, D_00631AE4, 5);
        }
    }
}

/* Matched body inlined from src/cod/05FBD8.c during TU coalesce. */
extern int D_00631AE8;
void func_0015FBD8(int *self) {
    int *p, *entry;
    int idx;
    unsigned int v;
    if (D_00631AE8 != 0) {
        func_0014B228(self, 0x1B);
        p = (int *)self[0x15C / 4];
        idx = p[0x4A0 / 4] * 0x190;
        entry = (int *)(D_00565060 + idx);
        v = entry[0x188 / 4];
        if (((v >> 1) & 1) != 0) {
            func_00165B80(self, D_00631AE8, 5);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_0015FC50);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_0015FD58);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_001609A0);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00160AF8);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00160C08);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_001613B0);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00161598);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00161AC8);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00161C38);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00161F10);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_001626D0);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00162AC8);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00162DB8);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00163068);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_001631B8);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00163890);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00163950);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00163D60);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00163EB8);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164440);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_001648A0);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164D30);

/* Matched body inlined from src/cod/064EB0.c during TU coalesce.
 * D_00558ED8/F08/F38/F80 are typed rodata defs above (const char[N]);
 * cast at call site to satisfy func_001A6E28's `char *` signature. */
extern void func_001A6E28(char *p);
extern unsigned int func_00203AA0(int a0);
void func_00164EB0(volatile unsigned int a0)
{
    volatile int local;
    int *new_var;
    int *s0;
    new_var = *((int **) (a0 + 0x164));
    func_001A6E28((char *)D_00558ED8);
    s0 = new_var;
    s0[0x30 / 4] = 0x1;
    func_00203AA0(0);
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164EF4);

/* Matched body inlined from src/cod/064EF8.c during TU coalesce. */
void func_00164EF8(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    func_001A6E28((char *)D_00558F08);
    s0[0x30 / 4] = 0x2;
    func_00203AA0(0);
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164F3C);

/* Matched body inlined from src/cod/064F40.c during TU coalesce. */
void func_00164F40(volatile unsigned int a0)
{
    volatile int local;
    int *s0;
    s0 = *((int **) (a0 + 0x164));
    func_001A6E28((char *)D_00558F38);
    s0[0x30 / 4] = 0x3;
    func_00203AA0(0);
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164F84);

/* Matched body inlined from src/cod/064F88.c during TU coalesce. */
void func_00164F88(volatile unsigned int a0)
{
    int *new_var;
    volatile int local;
    int *s0;
    new_var = *((int **) (a0 + 0x164));
    func_001A6E28((char *)D_00558F80);
    s0 = new_var;
    s0[0x30 / 4] = 0x1C;
    func_00203AA0(0);
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00164FCC);

/* Matched body inlined from src/cod/064FD0.c during TU coalesce. */
extern void func_001AD768(char *buf, int sz);
extern void func_00263FF0(char *buf, int sz, int *list);
void func_00164FD0(volatile unsigned int a0)
{
    volatile int local;
    func_001AD768((char *)D_00558E10, 0xAF3);
    func_00263FF0((char *)D_00558E10, 0xAF3, D_00632398);
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00165018);

/* Matched body inlined from src/cod/065158.c during TU coalesce. */
void func_00165158(char *self) {
    char *sub = *(char **)(self + 0x164);
    *(long long *)(sub + 0x150) |= 0x100000000LL;
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00165174);

/* Matched body inlined from src/cod/065178.c during TU coalesce. */
extern void func_00104360(int *self, char *spill);
extern void func_001CEC88(int *self);
extern void func_001651C8(int *self);
void func_00165178(int *self)
{
    char spill[16];
    *(long long *)(spill + 0) = *(long long *)((char *)D_00558FA0 + 0);
    *(long long *)(spill + 8) = *(long long *)((char *)D_00558FA0 + 8);
    func_00104360(self, spill);
    func_001CEC88(self);
    func_001651C8(self);
}

/* Matched body inlined from src/cod/0651C8.c during TU coalesce. */
extern char D_002A4C48[];
void func_001651C8(int *a0)
{
    char *base = D_002A4C48 + a0[2] * 0x4C;
    *(int *)(base + 0x48) &= ~0x200000;
}

/* Matched body inlined from src/cod/0651F8.c during TU coalesce. */
extern void func_0013FF88(int *p, int a, int b);
extern void func_00149EA8(int *p);
extern void func_0017B288(int a);
extern void func_001919A0(int *self, int a);
void func_001651F8(volatile int self_arg)
{
    register int *D asm("$3") = (int *)D_00631AE8;
    int new_var2;
    int *sub = (int *) ((int *) self_arg)[0x59];
    int *new_var;
    sub[0x4E] = (int) D;
    new_var2 = 0x4E;
    new_var = &sub[new_var2];
    func_0013FF88((int *)D_00631AE8, 0x30, self_arg);
    new_var2 = *new_var;
    ((int *) ((int *) sub[0x4E])[0x57])[0x1D] = 1;
    func_00149EA8((int *) new_var2);
    func_0017B288(0x168);
    sub[0x4E] = 0;
    if (sub[0xC] == 5)
    {
        func_001919A0((int *) self_arg, 4);
    }
    asm __volatile__("" : : : "memory");
}

/* Matched body inlined from src/cod/065270.c during TU coalesce. */
void func_00165270(int *a0)
{
    char *base = D_002A4C48 + a0[2] * 0x4C;
    *(int *)(base + 0x48) |= 0x40000;
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_0016529C);

/* Matched body inlined from src/cod/0652A0.c during TU coalesce. */
int func_001652A0(char *self) {
    char *sub = *(char **)(self + 0x164);
    return *(int *)(sub + 0x430) == 2;
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_001652B4);

/* Matched body inlined from src/cod/0652B8.c during TU coalesce. */
int func_001652B8(char *self) {
    char *sub = *(char **)(self + 0x164);
    return *(int *)(sub + 0x430) == 1;
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_001652CC);

/* Matched body inlined from src/cod/0652D0.c during TU coalesce. */
int func_001652D0(int *a0)
{
    int *p = (int *)(D_002A4C48 + a0[2] * 0x4C);
    return ((unsigned int)p[0x48 / 4] >> 18) & 1;
}

/* Matched body inlined from src/cod/0652F8.c during TU coalesce. */
int func_001652F8(int *a0)
{
    unsigned int *p = (unsigned int *)(D_002A4C48 + a0[2] * 0x4C);
    unsigned int field = p[0x48 / 4];
    unsigned int v0 = (field >> 18) & 1;
    if (v0 != 0) goto zero;
    v0 = (field >> 21) & 1;
    v0 = v0 ^ 1;
    if (v0 == 0) goto one;
zero:
    return 0;
one:
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00165344);

/* Matched body inlined from src/cod/065348.c during TU coalesce. */
extern int func_00160AF8(int *self);
extern void func_00165B50(char *self, int a1, int *a2);
extern void func_0015BCC8(int *self, int a);
int func_00165348(int *self)
{
    int r = func_00160AF8(self);
    if (r != 0) {
        func_00165B50(self, 0, 0);
    }
    func_0015BCC8(self, 0xF4);
    return r;
}

/* Matched body inlined from src/cod/0653A0.c during TU coalesce. */
int func_001653A0(int *self) {
    int *p = (int *)self[0x164/4];
    int *q = (int *)p[0x670/4];
    if (q[0x1E0/4] == 0 && p[0x30/4] == 0x10) {
        return q[0x218/4];
    }
    return 0;
}

/* Matched body inlined from src/cod/0653D0.c during TU coalesce. */
int func_001653D0(char *self) {
    char *sub = *(char **)(self + 0x164);
    char *p = *(char **)(sub + 0x670);
    return *(int *)(p + 0x1E0) == 1;
}

/* Matched body inlined from src/cod/0653E8.c during TU coalesce. */
int func_001653E8(char *self) {
    char *sub = *(char **)(self + 0x164);
    char *p = *(char **)(sub + 0x670);
    return *(int *)(p + 0x1E0) == 2;
}

/* Matched body inlined from src/cod/065400.c during TU coalesce. */
int func_00165400(char *self) {
    char *sub = *(char **)(self + 0x164);
    char *p = *(char **)(sub + 0x670);
    return *(int *)(p + 0x1E0) == 0;
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00165414);
int func_00165418(char *self, int *out)
{
    char *sub = *(char **)(self + 0x164);
    char *p = *(char **)(sub + 0x670);
    if (*(int *)(p + 0x1FC) != 5)
        return 0;
    {
        int v = *(int *)(*(char **)(sub + 0x678) + 0x420);
        *out = v;
        if (v == 0) {
            func_001AD768((char *)D_00558E10, 0x2FA);
            func_00263FF0((char *)D_00558E10, 0x2FA, (int *)D_00558E20);
        }
    }
    return 1;
}
int func_00165488(char *self)
{
    char *sub;
    char *sub2;
    if (D_00631AE8 != 0) {
        char *sub_d = *(char **)((char *)D_00631AE8 + 0x164);
        if (*(int *)(sub_d + 0x30) != 0x6B) return 0;
    }
    sub = *(char **)((char *)self + 0x164);
    sub2 = *(char **)(sub + 0x670);
    return *(int *)(sub2 + 0x1FC) == 3;
}

/* Matched body inlined from src/cod/0654C8.c during TU coalesce. */
int func_001654C8(char *self) {
    char *sub = *(char **)(self + 0x164);
    char *p = *(char **)(sub + 0x670);
    return *(int *)(p + 0x1DC);
}

/* Matched body inlined from src/cod/0654D8.c during TU coalesce. */
int func_001654D8(void) {
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_001654E0);
int func_00165540(int *a0)
{
    if (a0 == 0 || a0[3] != 4) {
        func_001AD768((char *)D_00558E10, 0x7D2);
        func_00263FF0((char *)D_00558E10, 0x7D2, (int *)D_00558FB0);
    }
    return func_001652F8(a0);
}
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_001655B0);
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00165918);

extern int func_00163D60(int a0);

void func_00165B50(char *self, int a1, int *a2)
{
    char *first;
    register char *second REG("$3");
    register int new_a0 REG("$4");
    first = *(char * volatile *)(self + 0x164);
    second = *(char **)(first + 0x670);
    *(int *)(second + 0x200) = a1;
    if (a2 != 0) {
        first = *(char * volatile *)(self + 0x164);
        new_a0 = *a2;
    } else {
        first = *(char * volatile *)(self + 0x164);
        new_a0 = D_00632390;
    }
    second = *(char **)(first + 0x670);
    *(int *)(second + 0x20C) = new_a0;
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00165B80);

int func_00165CE8(int a0)
{
    int v = *(int *)(*(int *)(a0 + 0x164) + 0x10);
    if (v < 0xC) return -1;
    return func_00163D60(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00165D18);
extern char *func_001E29E8(unsigned int a0, int v, void *p);

void func_00165DC0(volatile unsigned int arg)
{
    int *obj = *(int **)(arg + 0x164);
    func_001A6E28((char *)D_00558EF0);
    *(int *)((char *)obj + 0x120) = (int)func_001E29E8(arg, 1, (char *)obj + 0x610);
    for (;;) {
        func_00203AA0(1);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/enemy_act", func_00165E08);

void func_00165E60(volatile unsigned int a0)
{
    volatile int local;
    int *sub;
    char *r;
    sub = *((int **)(a0 + 0x164));
    func_001A6E28((char *)D_00558F50);
    r = func_001E29E8(a0, 0xC, (char *)sub + 0x610);
    sub[0x120 / 4] = (int)r;
    *(int *)(r + 0x114) = 0;
    func_00203AA0(0);
}
