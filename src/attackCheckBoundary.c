#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", AttackCheckBoundaryBeforeFunc);
INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", InitAttackCheckBoundaryManagerGeo);
INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", AttackCheckBoundaryManagerGeo);
void AttackCheckBoundaryManagerDL(void) {}
extern char D_0061EEC8[];
extern int D_0063A438;
extern int iosMallocDebug(int handle, int size, char *file, int line);

int InitAttackCheckBoundaryGeo(int unused, void *obj)
{
  int buf = iosMallocDebug(D_0063A438, 0xC, D_0061EEC8, 0x1B);
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
void AttackCheckBoundaryGeo(void *a0) {
    int *a = *(int **)((char *)a0 + 0x15C);
    int *b = *(int **)a;
    if (b == 0) return;
    if (*(int *)((char *)b + 0x16C) == 0) {
        *(int *)((char *)a0 + 0x16C) = 0;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", AttackCheckBoundaryDL);
extern void _ACTWait();
extern int actInitialize();
extern void actInitialize_ext_charcter();

void actAttackCheckBoundaryStart(int *self)
{
    int *p = actInitialize(self);
    long long v;
    actInitialize_ext_charcter(self);
    _ACTWait(1);
    v = *(long long *)((char *)p + 0x18);
    v |= 1LL << 32;
    *(long long *)((char *)p + 0x18) = v;
}
float GetAttackCheckBoundaryRadius(char *a0) {
    return *(float *)(*(char **)(*(char **)(a0 + 0x15C) + 0x870) + 0x20);
}
INCLUDE_ASM("asm/nonmatchings/src/attackCheckBoundary", CreateAttackCheckBoundary);
int GetAttackCheckBoundaryManagerStatus(char *a0) {
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8);
}
void SetAttackCheckBoundaryAttribute(char *a0, int a1) {
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 8) = a1;
}
