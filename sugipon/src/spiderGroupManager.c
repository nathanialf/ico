#include "common.h"

int EntrySpiderGroupManager(void) {
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", tryToRevive);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", ExecSpiderGroupManager);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", InitSpiderGroupManager);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", EntryRevivedSpiderGroupManager);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", DispAllSpiderGroups);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", EntryToSpiderGroupManagerForReviveMaster);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", getReviveEnemyGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", func_001E8638);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", func_001E86B0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", func_001E87F0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", func_001E89E8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", func_001E8C18);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", func_001E8C40);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", func_001E8C68);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", func_001E8D10);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", func_001E8D38);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", func_001E8D98);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/spiderGroupManager", func_001E8E38);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00706D00;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00705F98;  /* stride 0x4 */

typedef struct {
    unsigned int       f_4;  /* 0x04 */
} S_00706098;  /* stride 0x8 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00706298;  /* stride 0x4 */

/* end struct shapes */
