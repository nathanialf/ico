#include "typedef.h"
#include "debug.h"
#include "camera-root.h"
#include "debug_menu.h"
#include "main.h"
#include "GobjProc.h"

/* .sdata, owned by debug_menu.o (VMA 0x63B400..0x63B414, 0x14 B; MAIN.MAP's
   January run is 0x10 and names no symbol in it), the "object target" menu's
   state in the ROM's order: a word nothing in the ROM reads, the camera target
   to restore on cancel, the object being targeted, the display word saved from
   it, and the blink counter. */
static int debugMenuUnusedWord = 0; /* derived name */

static int savedCameraTarget = 0; /* derived name */

static int *targetGObj = 0; /* derived name */

static int savedDispWord = 0; /* derived name */

static int targetBlinkCount = 0; /* derived name */

/* .sbss, owned by debug_menu.o and reached only from this file (MAIN.MAP names
   no symbol in the run), in the ROM's run order.  init_debug_menu writes the
   first two and nothing in the ROM ever reads them (checked over every
   gp-relative access in .text), so those two names are positional, ours; the
   third is the index the "object target" menu edits. */
static int debugMenuFlag0;

static int debugMenuFlag1;

static int targetGObjIdx;

char *debug_TargetGObj_Func(int idx);

int debug_TargetGObj(int reset)
{
    int n;
    int ret;

    n = GetMaxGObj();
    if (reset != 0) {
        int t = CameraGetTarget();
        targetGObj = 0;
        savedCameraTarget = t;
        targetGObjIdx = GetGObjId(t);
    }
    ret = debug_SelectCsvWindowVal((int)"object target", 0xA, 0x3C, 0xA, n, (int)&targetGObjIdx,
                                   (int (*)(int, int))debug_TargetGObj_Func, 0);
    if (targetGObj != (int *)GetGObjP(targetGObjIdx)) {
        CameraSetMode(2);
        CameraChangeTargetParallel((int)targetGObj, GetGObjP(targetGObjIdx));
        if (targetGObj != 0) {
            targetGObj[0x14] = savedDispWord;
        }
        targetGObj = (int *)GetGObjP(targetGObjIdx);
        savedDispWord = targetGObj[0x14];
    }
    targetGObj = (int *)GetGObjP(targetGObjIdx);
    CurrentTargetGObj = (int)targetGObj;
    Camctrl_SetTarget((int)targetGObj, 0, 3);
    debug_PrintfDummy(16, 16, 0xFFFFFFFF, "GObj address:%p", CurrentTargetGObj);
    if ((targetBlinkCount++ & 7) == 0) {
        targetGObj[0x14] = ~targetGObj[0x14];
    }
    if (ret != 0) {
        targetGObj[0x14] = savedDispWord;
        if (ret < 0) {
            Camctrl_SetTarget(savedCameraTarget, 0, 3);
            CurrentTargetGObj = savedCameraTarget;
        }
    }
    return ret;
}

void init_debug_menu(void)
{
    debugMenuFlag0 = 0;
    debugMenuFlag1 = 1;
    targetGObjIdx = 0;
}

extern ObjKindEnt objKindData[];

char *debug_TargetGObj_Func(int idx)
{
    int kind = ((GObj *)GetGObjP(idx))->kind;
    return objKindData[kind].name;
}
