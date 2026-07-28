#include "common.h"

struct BEl { int g; int f4; };
struct BStr { int cnt; int f4; int f8; struct BEl *arr; };




extern void playSEConditionID(int a0, int a1);
extern void _ACTWait();
extern int actInitialize();
extern void actInitialize_ext_charcter();
extern int AP1BeforeFunc();
extern int D_00633248[];
extern void *D_004BEF60[];

void *AttackCheckBoundaryBeforeFunc(void *a0) {
    void *p = *(void **)((char *)a0 + 0x164);
    unsigned int idx;
    if (p != 0) {
        idx = *(unsigned int *)((char *)p + 0x30);
        if (idx < 6) goto arr;
    }
    return D_00633248;
arr:
    return D_004BEF60[idx];
}

int InitAttackCheckBoundaryManagerGeo(int a0)
{
    return AP1BeforeFunc(a0, 0) ? 0 : -1;
}

int AttackCheckBoundaryManagerGeo(int a0)
{
    return AP1BeforeFunc(a0, 0) ? 0 : -1;
}

void AttackCheckBoundaryManagerDL(int x) {
    volatile int local = x;
}

extern int DebugDisp1CollisionWithColor(void *a0, int code);
extern void GetInverseQuaternion(void *a0, int a1);
extern void func_0010E0B8(void *a0, int a1);
extern void func_0010E1F8(void *a0, int a1);
extern void func_0012ABE0(void *a0, int a1);
extern void stage_SetParentOfGObj(void *a0, int a1, void *a2, float a3);

void InitAttackCheckBoundaryGeo(void *a0, int a1, int a2, void *a3) {
    char buf[0x10];
    int r1 = DebugDisp1CollisionWithColor(a0, a1);
    int r2 = DebugDisp1CollisionWithColor(a0, a2);
    func_0012ABE0(a3, 1);
    GetInverseQuaternion(buf, *(int *)(*(char **)((char *)a0 + 0x15C) + 0x10) + r1 * 0x10);
    func_0010E0B8(buf, 0x4000);
    func_0010E1F8(buf, 0x4000);
    stage_SetParentOfGObj(a3, *(int *)(*(char **)((char *)a0 + 0x15C) + 0xC) + r2 * 0x40 + 0x30, buf, 0.0f);
    func_0012ABE0(a3, 0);
}

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", AttackCheckBoundaryGeo);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", AttackCheckBoundaryDL);

void actAttackCheckBoundaryStart(int a0) {
    struct BStr *s = (struct BStr *)*(int *)(*(int *)(a0 + 0x15C) + 0x800);
    int i;
    for (i = 0; i < s->cnt; i++) {
        int g = s->arr[i].g;
        s->arr[i].f4 = *(int *)(*(int *)(*(int *)(g + 0x15C) + 0x800) + 4);
        *(int *)(*(int *)(*(int *)(g + 0x15C) + 0x800) + 4) = 0;
        *(int *)(g + 0x16C) = 1;
    }
    {
        int tmp = s->f4;
        s->f4 = 0;
        s->f8 = tmp;
    }
}

void GetAttackCheckBoundaryRadius(void) {}

extern char D_006185E8[];
extern int D_00632010;
extern int func_0013A0F8(int handle, int size, char *file, int line);

int CreateAttackCheckBoundary(int unused, void *obj)
{
  int buf = func_0013A0F8(D_00632010, 0xC, D_006185E8, 0x1B);
  int *p = *((int **) (((char *) obj) + 0x30));
  int new_var4;
  int *new_var2;
  int *new_var3;
  int new_var;
  new_var2 = p;
 do { new_var4 = (int) p; ; } while (0);
  *((int *) (buf + 4)) = 0;
  new_var3 = (int *) buf;
  *new_var2 = 0;
  *new_var3 = new_var4;
  *((int *) (buf + 8)) = 0;
  return buf;
}

void GetAttackCheckBoundaryManagerStatus(void *a0) {
    int *a = *(int **)((char *)a0 + 0x15C);
    int *b = *(int **)a;
    if (b == 0) return;
    if (*(int *)((char *)b + 0x16C) == 0) {
        *(int *)((char *)a0 + 0x16C) = 0;
    }
}

extern int D_00632CC8;
extern char D_004BEFC0[];
extern void gif_SpriteOffset(int a0);
extern void gsb_Reduction(int a0);
extern void gsb_SetFrame(int a0, int a1, int a2);
extern int func_00105278(void);
extern void func_00118678(int a0);
extern void MatrixDrive_TurnObjectMatrix(int a0, int a1);
extern float func_001BBFD0(void *a0);
extern void reg_dispBoxLine(void *a0, int a1, int a2, float a3);
extern int func_0010F630(void);

int switchOnSE(void *a0) {
    char *g = *(char **)(*(char **)((char *)a0 + 0x15C) + 0x800);
    int m;
    float f;
    if (D_00632CC8 == 0) goto end;
    if (*(int *)(g + 4) != 0) goto end;
    gif_SpriteOffset(0xB);
    gsb_Reduction(1);
    gsb_SetFrame(1, 5, 0x80);
    func_00118678(func_00105278());
    m = func_00105278();
    MatrixDrive_TurnObjectMatrix(m + 0x30,
        *(int *)(*(char **)((char *)a0 + 0x15C) + 0xC) + 0x30);
    f = func_001BBFD0(a0);
    reg_dispBoxLine(D_004BEFC0, 4, 4, f);
    return func_0010F630();
end:
    ;
}

void switchReleaseSE(int *self)
{
    int *p = actInitialize(self);
    long long v;
    actInitialize_ext_charcter(self);
    _ACTWait(1);
    v = *(long long *)((char *)p + 0x18);
    v |= 1LL << 32;
    *(long long *)((char *)p + 0x18) = v;
}

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BBFD0);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BBFE0);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC088);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC098);

void func_001BC0A8(int a0)
{
    playSEConditionID(a0, 0x3D);
}

void func_001BC0B0(int a0)
{
    playSEConditionID(a0, 0x3E);
}

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC0B8);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC130);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC1A8);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC438);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC4B8);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC530);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC7F0);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC870);

void func_001BC9A0(int a0)
{
    playSEConditionID(a0, 0x2);
}

void func_001BC9A8(int a0)
{
    playSEConditionID(a0, 0x24);
}

void func_001BC9B0(int a0)
{
    playSEConditionID(a0, 0x4);
}

void func_001BC9B8(int a0)
{
    playSEConditionID(a0, 0xD);
}

void func_001BC9C0(int a0)
{
    playSEConditionID(a0, 0x1E);
}

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BC9C8);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BCAF0);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BCC18);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BD138);

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", func_001BD278);

