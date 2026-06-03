#include "common.h"

extern void playSEConditionID(int a0, int a1);

void bombSparkStartSE(int a0) {
    playSEConditionID(a0, 0x31);
}

void bombSparkSE(int a0) {
    playSEConditionID(a0, 0x32);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/item", bombExplodeSE);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/item", HoldItem);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/item", avoidInsideOfWall);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/item", ReleaseItem);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/item", ThrowItem);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/item", InitItemGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/item", carriedItemGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/item", uncarriedItemGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/item", execBombGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/item", ItemGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/item", ItemDL);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
} S_004CECE0;  /* stride 0x14 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_006118E0;  /* stride 0x4 */

/* end struct shapes */
