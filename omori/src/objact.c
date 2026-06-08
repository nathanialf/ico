#include "common.h"

typedef struct { float a0; float a4; float a8; } S;

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/objact", ObjectBeforeFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/objact", ObjAction_CorrectGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/objact", ObjAction_Mail);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/objact", ObjAction_MailCenter);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/objact", ObjAction_Init);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/objact", func_00237A20);

extern void actCreateSubThread(void *entry, int a1);
extern void func_00237AF8(void);

void func_00237AD0(volatile int a0) {
    actCreateSubThread(func_00237AF8, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/objact", func_00237AF8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/objact", func_00237BA8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/objact", func_00237E28);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/objact", func_00238020);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/objact", func_00238178);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/objact", func_002382C0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/objact", func_002384E0);

extern int func_00178DB0(int x);
extern float D_00629AC8;

int func_00238600(int *self)
{
  S *p;
  float new_var;
  p = (S *) self[0x34 / 4];
  p->a0 = D_00629AC8;
  p->a8 = 482.0f;
  new_var = 0.5f;
  *((float *) (((char *) self) + 0x1C)) = new_var;
  if (func_00178DB0(0x5F))
  {
    *((int *) (((char *) self) + 0x18)) = 0;
  }
  return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/objact", func_00238658);

extern int func_00188580(void);

int func_002386B8(void) {
    int r = func_00188580();
    if (r == 3 || r == 9) {
        return -1;
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/objact", func_002386F0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/objact", func_00238730);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/objact", func_00238800);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/objact", func_00238860);


/* recovered struct shapes */
typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
} S_00614EA0;

/* end struct shapes */
