#include "common.h"

extern void MatrixDrive_TurnObjectMatrix(int p, int q);
extern void playSEConditionID(int p, int q);
extern int D_00629DE8;
extern int D_0062B5CC;
extern int D_0062B5D0;
extern int D_0062B5D4;
extern int D_0062B5D8;
extern float D_0062B5DC;
extern char D_004BBC80[];

void _dispParam(int a0, float t)
{
  int new_var;
  if (D_00629DE8 != 0)
  {
    playSEConditionID(D_00629DE8, 0x75);
    playSEConditionID(D_00629DE8, 0x76);
    playSEConditionID(D_00629DE8, 0x77);
    playSEConditionID(D_00629DE8, 0x78);
    playSEConditionID(D_00629DE8, 0x79);
  }
  D_0062B5CC = (new_var = 1);
  new_var = (D_0062B5D4 = new_var);
  D_0062B5D8 = (D_0062B5D0 = 0);
  MatrixDrive_TurnObjectMatrix((int) D_004BBC80, a0);
  D_0062B5DC = t;
}

void editParam(int a0, float t)
{
    D_0062B5CC = 1;
    D_0062B5D4 = 1;
    D_0062B5D0 = 0;
    D_0062B5D8 = 0;
    MatrixDrive_TurnObjectMatrix((int) D_004BBC80, a0);
    D_0062B5DC = t;
    D_0062B5D8 = 1;
    D_0062B5D4 = 0;
}


void dispXZYZCircle(void) {
    D_0062B5CC = 0;
    D_0062B5D4 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", dispCircle2);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", setQ);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", dispEffectToolField);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", EditTarget);

extern unsigned short D_0062B658;
extern unsigned short D_0062B65A;
extern void GetMatrixFromQuaternion(int *self);
extern void func_0010E4E8(int *self, short y);
extern void func_0010E448(int *self, short y);

void saveEffectData(int *self)
{
    GetMatrixFromQuaternion(self);
    func_0010E4E8(self, -D_0062B658);
    func_0010E448(self, -D_0062B65A);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", moveEffectToolGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", execEffectTool);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_C;  /* 0x0C */
} S_004BBCB8;  /* stride 0x1C */

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
} S_004BC040;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00702E60;  /* stride 0x4 */

/* end struct shapes */
