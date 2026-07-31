#include "common.h"



extern float D_006317E4;
extern float D_006317E8;
typedef struct 
{
  float a0;
  float a4;
  float a8;
} S;
extern float D_006317E0;
extern int func_0017B230(int a0);
extern void actCreateSubThread(void *f, int a1);
extern void func_0023B518(volatile int a0);

void func_0023B4F0(volatile int a0) {
    actCreateSubThread(func_0023B518, 0x15);
}

extern int actInitialize(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int *D_00631AE4;

void func_0023B518(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    for (;;) {
        stage_KillPlayBgAnimation(0x1C0, 1, 0);
        _ACTWait(0xB3);
        stage_KillPlayBgAnimation(0x1C1, 1, 0);
        _ACTWait(0xB3);
        stage_KillPlayBgAnimation(0x1C2, 1, 0);
        _ACTWait(0xB3);
        stage_KillPlayBgAnimation(0x1C3, 1, 0);
        _ACTWait(0xB3);
    }
}

extern void actCreateSubThread(void *f, int a1);
extern void func_0023B5C8(volatile int a0);

void func_0023B5A0(volatile int a0) {
    actCreateSubThread(func_0023B5C8, 0x15);
}


void func_0023B5C8(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    for (;;) {
        stage_KillPlayBgAnimation(0xAD, 1, 0);
        _ACTWait(0xC8);
        stage_KillPlayBgAnimation(0xAE, 1, 0);
        _ACTWait(0xC8);
        stage_KillPlayBgAnimation(0xAF, 1, 0);
        _ACTWait(0xC8);
        stage_KillPlayBgAnimation(0xB0, 1, 0);
        _ACTWait(0xC8);
    }
}

extern void _ACTWait(int a0);

extern void func_0017E660(int a0, float a1, float a2, float a3, float a4);

void func_0023B650(volatile int a0) {
    for (;;) {
        while ((((int *)D_00631AE4[0x164 / 4])[0x2D4 / 4] & 0x400) == 0) {
            _ACTWait(1);
        }
        func_0017E660(2, 0.0f, -500.0f, 0.0f, 500.0f);
        _ACTWait(1);
    }
}

extern int D_00275250[];
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_0023B6B8(volatile int a0) {
    for (;;) {
        while ((D_00275250[0x5C / 4] & 0x20) == 0) {
            _ACTWait(1);
        }
        stage_KillPlayBgAnimation(0x47, 1, 0);
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/objact", func_0023B728);

INCLUDE_ASM("asm/nonmatchings/src/objact", func_0023B8B8);

INCLUDE_ASM("asm/nonmatchings/src/objact", func_0023BAB0);

INCLUDE_ASM("asm/nonmatchings/src/objact", func_0023BC08);

INCLUDE_ASM("asm/nonmatchings/src/objact", func_0023BD50);

INCLUDE_ASM("asm/nonmatchings/src/objact", func_0023BF70);

int func_0023C090(int *self)
{
  S *p;
  float new_var;
  p = (S *) self[0x34 / 4];
  p->a0 = D_006317E0;
  p->a8 = 482.0f;
  new_var = 0.5f;
  *((float *) (((char *) self) + 0x1C)) = new_var;
  if (func_0017B230(0x5F))
  {
    *((int *) (((char *) self) + 0x18)) = 0;
  }
  return 1;
}

int func_0023C0E8(int *self)
{
  int new_var3;
  float new_var2;
  float *p;
  int *new_var4;
  float new_var;
  int new_var5;
  p = (float *) self[0x34 / 4];
  new_var3 = 0;
  new_var = 482.0f;
  p[new_var3] = D_006317E4;
  new_var2 = D_006317E8;
  p[1] = new_var2;
  p[2] = new_var;
  *((float *) (((char *) self) + 0x1C)) = 0.5f;
  new_var5 = func_0017B230(0x5F);
  if (new_var5)
  {
    new_var4 = self;
    *((int *) (((char *) new_var4) + 0x18)) = 0;
  }
  return 1;
}

extern int func_0018B0A0(void);

int func_0023C148(void) {
    int r = func_0018B0A0();
    if (r == 3 || r == 9) {
        return -1;
    }
    return 0;
}

int func_0023C180(void) {
    int r = func_0018B0A0();
    int busy = (r == 3 || r == 9) ? -1 : 0;
    if (busy != 0) {
        return 0;
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/src/objact", func_0023C1C0);

extern int D_00633B4C;
extern int D_00631960;
extern float D_00633B48;
extern void *UpdateRootPosition(void);
extern float DispWireLetter(void *a0);

int func_0023C290(void *a0) {
    float v;
    if (D_00633B4C == D_00631960) {
        v = D_00633B48;
    } else {
        D_00633B4C = D_00631960;
        v = DispWireLetter(UpdateRootPosition()) * 0.5f + 0.5f;
        D_00633B48 = v;
    }
    *(float *)((char *)a0 + 0x18) = v;
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/src/objact", func_0023C2F0);

