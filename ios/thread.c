/* thread.c -- typed sdata / lit4 definitions for this TU.
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


__attribute__((section(".rodata.0x00557890"))) const char D_00557890[16] = "<THREAD_SP>....";
__attribute__((section(".rodata.0x005578A0"))) const char D_005578A0[16] = "<THREAD_SP_END>";
__attribute__((section(".rodata.0x005578D0"))) const char D_005578D0[16] = "ios/thread.c";

/* String rodata migrated from thread_data.c */
__attribute__((section(".rodata.0x005578B0"))) const char D_005578B0[32] = "thr:thread table over flow\n";
__attribute__((section(".rodata.0x005578E0"))) const char D_005578E0[32] = "thr:can't create thread\n";
__attribute__((section(".rodata.0x00557900"))) const char D_00557900[16] = "n_thread %d\n";
__attribute__((section(".rodata.0x00557910"))) const char D_00557910[24] = "thr:can't create stack\n";
__attribute__((section(".rodata.0x00557928"))) const char D_00557928[32] = "iosThreadDestroyMgr() in\n";
__attribute__((section(".rodata.0x00557948"))) const char D_00557948[16] = "1:n_thread %d\n";
__attribute__((section(".rodata.0x00557958"))) const char D_00557958[24] = "thr:id out of range\n";
__attribute__((section(".rodata.0x00557970"))) const char D_00557970[16] = "th:msg %d\n";
__attribute__((section(".rodata.0x00557980"))) const char D_00557980[24] = "th:thread joined\n";
__attribute__((section(".rodata.0x00557998"))) const char D_00557998[24] = "sem: can't create %d\n";
__attribute__((section(".rodata.0x005579B0"))) const char D_005579B0[24] = "sem: can't delete %d\n";
__attribute__((section(".rodata.0x005579C8"))) const char D_005579C8[24] = "sem: wait error? %d\n";
__attribute__((section(".rodata.0x005579E0"))) const char D_005579E0[24] = "sem: signal error? %d\n";
__attribute__((section(".rodata.0x005579F8"))) const char D_005579F8[24] = "sem: refer error? %d\n";


#include "include_asm.h"
#include "regpin.h"
#include "matching.h"

INCLUDE_ASM("asm/nonmatchings/ios/thread", func_0013D1B0);


extern void func_00100340(int a0, int a1);

void func_0013D3C8(int a0)
{
    func_00100340(*(int *)(a0 + 0x30), *(int *)(a0 + 0x34));
}


INCLUDE_ASM_NOP_PAD(func_0013D3D4);


extern void func_00100350(void);
extern void func_00100370(int a0);

void func_0013D3D8(int a0)
{
    if (a0 == 0) {
        func_00100350();
    } else {
        func_00100370(*(int *)(a0 + 0x30));
    }
}



extern void func_00100440(int a0, int a1, int a2, int a3);

void func_0013D3F0(int a0, int a1, int a2, int a3)
{
    func_00100440(a0, a1, a2, a3);
}



extern int D_006A6F30[];
extern char D_006A7330[];
extern int func_00100410(void);
extern void func_0013A5B8(char *a, int b, int c);

void func_0013D3F8(int a0)
{
    int a1 = a0;
    if (a0 == 0) {
        a1 = D_006A6F30[func_00100410()];
    }
    func_0013A5B8(D_006A7330, a1, 0);
}




extern void func_001003B0(int a, int b);
void func_0013D440(int *a0, int a1)
{
  int *v;
  v = a0;
  if (v == 0)
  {
    v = (int *) D_006A6F30[func_00100410()];
  }
  else
  {
    v = a0;
  }
  v[0x18 / 4] = a1;
  func_001003B0(v[0x30 / 4], a1);
}


INCLUDE_ASM_NOP_PAD(func_0013D494);

INCLUDE_ASM("asm/nonmatchings/ios/thread", func_0013D498);


extern void func_00265168(int a0);
void func_0013D538(int a0)
{
    func_00265168(a0 + 0x50);
}



extern void func_00100490(int a0);
void func_0013D540(int a0)
{
    func_00100490(*(int *)(a0 + 0x30));
}



extern void func_001004B0(int a0);
void func_0013D548(int a0)
{
    func_001004B0(*(int *)(a0 + 0x30));
}


INCLUDE_ASM("asm/nonmatchings/ios/thread", func_0013D550);

INCLUDE_ASM("asm/nonmatchings/ios/thread", func_0013D700);



int func_0013D8A0(int *a0)
{
    register int **base REG("$16");  /* s0 */
    if (a0 == 0) {
        int idx;
        base = D_006A6F30;
        idx = func_00100410();
        a0 = base[idx];
    }
    return a0[0x18 / 4];
}


INCLUDE_ASM_NOP_PAD(func_0013D8DC);


extern void func_001A6E28();

int func_0013D8E0(unsigned int a0)
{
    int ret;
    if (a0 < 0x101) goto valid;
    func_001A6E28(D_00557958);
    ret = 0;
    goto out;
valid:
    ret = D_006A6F30[a0];
out:
    return ret;
}


INCLUDE_ASM_NOP_PAD(func_0013D924);



extern void func_00100450(int);

void func_0013D928(int *self) {
    func_00100450(self[12]);  // 0x30/4 = 12
    DEFEAT_TCO();
}


INCLUDE_ASM_NOP_PAD(func_0013D944);

INCLUDE_ASM("asm/nonmatchings/ios/thread", func_0013D948);



extern int func_00100470(int a0);

int func_0013D9C8(int *self)
{
    int v;
    if (self == 0) {
        v = func_00100410();
    } else {
        v = self[0x30/4];
    }
    return func_00100470(v);
}

TRAILING_PAD_NOP();


extern int func_00100520(int *self);
extern char D_006321B8[];
int func_0013DA00(int *self, int a1, int a2, int a3)
{
    int rv;
    self[0x8 / 4] = a1;
    self[0x4 / 4] = a2;
    self[0x14 / 4] = a3;
    rv = func_00100520(self);
    self[0x30 / 4] = rv;
    if (rv < 0) {
        func_001A6E28(D_00557998, rv);
        func_001AD768(D_005578D0, 0x25C);
        func_00263FF0(D_005578D0, 0x25C, D_006321B8);
        return self[0x30 / 4];
    }
    return 0;
}

extern int func_00100530(int sem);
extern void func_001AD768(const char *file, int line);
extern void func_00263FF0(const char *file, int line, const char *expr);
int func_0013DA88(int *self)
{
    int rv = func_00100530(self[0x30 / 4]);
    if (rv < 0) {
        func_001A6E28(D_005579B0, self[0x30 / 4]);
        func_001AD768(D_005578D0, 0x270);
        func_00263FF0(D_005578D0, 0x270, D_006321B8);
        return rv;
    }
    return 0;
}

extern int func_00100590(int sem, int *self);
extern int func_00100560(int sem);
extern void func_001A6E28(const char *fmt, int arg);
int func_0013DB00(int *self)
{
    int rv = func_00100590(self[0x30 / 4], self);
    if (rv < 0) {
        func_001A6E28(D_005579C8, self[0x30 / 4]);
        return rv;
    }
    func_00100560(self[0x30 / 4]);
    return 0;
}


extern int func_00100540(int x);

int func_0013DB60(int *self)
{
    int v;
    int rv = 0;
    v = func_00100540(self[0x30/4]);
    if (v >= 0) {
        return rv;
    }
    func_001A6E28(D_005579E0, self[0x30/4]);
    return v;
}


int func_0013DBB0(int *self)
{
    int rv = func_00100590(self[0x30 / 4], self + 0x18 / 4);
    if (rv < 0) {
        func_001A6E28(D_005579F8, self[0x30 / 4]);
        func_001AD768(D_005578D0, 0x2B0);
        func_00263FF0(D_005578D0, 0x2B0, D_006321B8);
        return rv;
    }
    return 0;
}
