#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", _dispParam);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", editParam);

extern int D_0062B5CC;
extern int D_0062B5D4;

void dispXZYZCircle(void) {
    D_0062B5CC = 0;
    D_0062B5D4 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", dispCircle2);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", setQ);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", dispEffectToolField);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", EditTarget);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/effectTool", saveEffectData);

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
