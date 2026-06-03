#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjKindTableInit);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjInit);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", cut_gobj_link);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjRemoveAll);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", add_gobj_to_tail);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", add_gobj_to_head);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjMove);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjMoveHead);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjAddAfterGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjAddBeforeGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGetNbAllocedGObjs);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjAlloc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjRemove);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjKindTableAdd);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjKindTableRemove);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjMoveAfterGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjMoveBeforeGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjAdd);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjAddHead);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjSearchFromObjLayoutID);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj", isysGObjSearchFromObjKindID_begin);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_006A2F50;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0027DE10;  /* stride 0x4 */

/* end struct shapes */
