#include "typedef.h"
#include "debug.h"
#include "camera-root.h"
#include "debug_menu.h"
#include "main.h"
#include "GobjProc.h"
#include "gamesys.h"

/* .sdata, the "object target" menu's state: a word nothing reads, the camera target
   to restore on cancel, the object being targeted, the display word saved from
   it, and the blink counter. */
static int debugMenuUnusedWord = 0; /* derived name */

static int savedCameraTarget = 0; /* derived name */

static int *targetGObj = 0; /* derived name */

static int savedDispWord = 0; /* derived name */

static int targetBlinkCount = 0; /* derived name */

/* .sbss: init_debug_menu writes the first two and nothing reads them; the
   third is the index the "object target" menu edits. */
static int debugMenuFlag0; /* derived name */

static int debugMenuFlag1; /* derived name */

static int targetGObjIdx; /* derived name */

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

char *debug_TargetGObj_Func(int idx)
{
    int kind = ((GObj *)GetGObjP(idx))->kind;
    return objKindData[kind].name;
}
