#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", AttackCheckBoundaryBeforeFunc);

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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", InitAttackCheckBoundaryGeo);

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
