#include "common.h"

typedef struct { float a0; float a4; float a8; } S;

extern void actInitialize(void *a0);
extern void _ACTWait(int a0);
extern void scpSetCageVelocityFriction(int a0, int a1, int a2, int a3);

void ObjectBeforeFunc(void *a0) {
    void *volatile p = a0;
    (void)p;
    actInitialize(p);
    _ACTWait(1);
    scpSetCageVelocityFriction(0xC8C, 0, 0x1E2, 0);
}

void ObjAction_CorrectGeo(void *a0) {
    void *volatile p = a0;
    (void)p;
    actInitialize(p);
    _ACTWait(1);
    scpSetCageVelocityFriction(0xC8B, 0, 0x1E3, 0);
}

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

int func_002386F0(void) {
    int r = func_00188580();
    int flag;
    if (r == 3 || r == 9) {
        flag = -1;
    } else {
        flag = 0;
    }
    return flag ? 0 : -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/objact", func_00238730);

extern int D_0062BE54;
extern int D_00629C60;
extern float D_0062BE50;
extern void *UpdateRootPosition(void);
extern float DispWireLetter(void *a0);

int func_00238800(void *a0) {
    float f;
    if (D_0062BE54 == D_00629C60) {
        f = D_0062BE50;
    } else {
        D_0062BE54 = D_00629C60;
        f = DispWireLetter(UpdateRootPosition());
        f = f * 0.5f + 0.5f;
        D_0062BE50 = f;
    }
    *(float *)((char *)a0 + 0x18) = f;
    return -1;
}

extern float D_00629AE0, D_00629AE4, D_00629AE8;

int func_00238860(void *a0) {
    float x = *(float *)((char *)UpdateRootPosition() + 8);
    float f;
    if (x < D_00629AE0) {
        f = 0.0f;
    } else if (x > *(volatile float *)&D_00629AE4) {
        f = 1.0f;
    } else {
        f = (x - D_00629AE0) / D_00629AE8;
    }
    *(float *)((char *)a0 + 0x18) = 1.0f - f;
    return -1;
}


/* recovered struct shapes */
typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
} S_00614EA0;

/* end struct shapes */
