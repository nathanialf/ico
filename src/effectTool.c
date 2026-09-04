#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/effectTool", _dispParam);
INCLUDE_ASM("asm/nonmatchings/src/effectTool", editParam);
INCLUDE_ASM("asm/nonmatchings/src/effectTool", dispXZYZCircle);
INCLUDE_ASM("asm/nonmatchings/src/effectTool", dispCircle2);
extern unsigned short D_0063B858;
extern unsigned short D_0063B85A;
extern void RotQuaternionX(int *self, short y);
extern void RotQuaternionY(int *self, short y);
extern void SetIdentityQuaternion(int *self);

void setQ(int *self)
{
    SetIdentityQuaternion(self);
    RotQuaternionY(self, -D_0063B858);
    RotQuaternionX(self, -D_0063B85A);
}
INCLUDE_ASM("asm/nonmatchings/src/effectTool", dispEffectToolField);
INCLUDE_ASM("asm/nonmatchings/src/effectTool", EditTarget);
INCLUDE_ASM("asm/nonmatchings/src/effectTool", saveEffectData);
INCLUDE_ASM("asm/nonmatchings/src/effectTool", moveEffectToolGeometry);
INCLUDE_ASM("asm/nonmatchings/src/effectTool", execEffectTool);
extern void Camctrl_SetTarget(int x, int y, int z);
extern int D_0063AA08;
extern int D_0063B854;
extern int D_0063B86C;
extern char D_0063B878[];
extern void DeleteParticleEffect(int x);
extern void debug_StdPrintfDummy(char *p);

void exitEffectTool(void)
{
    DeleteParticleEffect(D_0063B854);
    D_0063B854 = -1;
    Camctrl_SetTarget(D_0063B86C, 0, 3);
    D_0063AA08 = 0;
    debug_StdPrintfDummy(D_0063B878);
}
INCLUDE_ASM("asm/nonmatchings/src/effectTool", EffectTool);
