#include "common.h"

extern int D_0062D388[];
extern void *D_004BA260[];

void *AttackCheckBoundaryBeforeFunc(void *a0) {
    void *p = *(void **)((char *)a0 + 0x164);
    unsigned int idx;
    if (p != 0) {
        idx = *(unsigned int *)((char *)p + 0x30);
        if (idx < 6) goto arr;
    }
    return D_0062D388;
arr:
    return D_004BA260[idx];
}

extern int AP1BeforeFunc(void *a0, int a1);

int InitAttackCheckBoundaryManagerGeo(void *a0) {
    return AP1BeforeFunc(a0, 0) ? 0 : -1;
}

int AttackCheckBoundaryManagerGeo(void *a0) {
    return AP1BeforeFunc(a0, 0) ? 0 : -1;
}

void AttackCheckBoundaryManagerDL(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern int DebugDisp1CollisionWithColor(void *a0, int code);
extern void func_0012AAB8(void *a0, int a1);
extern void GetInverseQuaternion(void *a0, int a1);
extern void func_0010E448(void *a0, int a1);
extern void func_0010E588(void *a0, int a1);
extern void stage_SetParentOfGObj(void *a0, int a1, void *a2, float a3);

void InitAttackCheckBoundaryGeo(void *a0, int a1, int a2, void *a3) {
    char buf[0x10];
    int r1 = DebugDisp1CollisionWithColor(a0, a1);
    int r2 = DebugDisp1CollisionWithColor(a0, a2);
    func_0012AAB8(a3, 1);
    GetInverseQuaternion(buf, *(int *)(*(char **)((char *)a0 + 0x15C) + 0x10) + r1 * 0x10);
    func_0010E448(buf, 0x4000);
    func_0010E588(buf, 0x4000);
    stage_SetParentOfGObj(a3, *(int *)(*(char **)((char *)a0 + 0x15C) + 0xC) + r2 * 0x40 + 0x30, buf, 0.0f);
    func_0012AAB8(a3, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", AttackCheckBoundaryGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", AttackCheckBoundaryDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", actAttackCheckBoundaryStart);

void GetAttackCheckBoundaryRadius(void) {
}

extern int D_0062A310;
extern int iosFree(int handle, int size, char *file, int line);

extern char D_00610EF8[];

int CreateAttackCheckBoundary(int unused, void *obj)
{
  int buf = iosFree(D_0062A310, 0xC, D_00610EF8, 0x1B);
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


/* recovered struct shapes */
typedef struct {
    unsigned int       f_38;  /* 0x38 */
    unsigned int       f_40;  /* 0x40 */
    unsigned int       f_44;  /* 0x44 */
} S_00617FA0;  /* stride 0x50 */

/* end struct shapes */
