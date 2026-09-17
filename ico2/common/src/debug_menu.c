#include "common.h"
#include "debug.h"
#include "camera-root.h"

/* kept local: this TU's uses of GetMaxGObj do not fit the prototype in GobjProc.h */
extern int GetMaxGObj(void);
/* kept local: this TU's uses of GetGObjP do not fit the prototype in GobjProc.h */
extern int GetGObjP(); /* unprototyped: C89 default int return, a GObj handle */
/* kept local: this TU's uses of GetGObjId do not fit the prototype in GobjProc.h */
extern int GetGObjId(int gobj);
extern int debug_SelectCsvWindowVal(int a0, int a1, int a2, int a3, int count, int a5,
                                    int (*fn)(int, int), int a7);
extern int D_0063B404;
extern int *D_0063B408;
extern int D_0063B40C;
extern int D_0063B410;
extern int D_00639EC0;

/* .sbss, owned by debug_menu.o and reached only from this file (MAIN.MAP names
   no symbol in the run), in the ROM's run order.  init_debug_menu writes the
   first two and nothing in the ROM ever reads them (checked over every
   gp-relative access in .text), so those two names are positional, ours; the
   third is the index the "object target" menu edits. */
static int debugMenuFlag0;

static int debugMenuFlag1;

static int targetGObjIdx;

char *debug_TargetGObj_Func(void);

int debug_TargetGObj(int reset)
{
    int n;
    int ret;

    n = GetMaxGObj();
    if (reset != 0) {
        int t = CameraGetTarget();
        D_0063B408 = 0;
        D_0063B404 = t;
        targetGObjIdx = GetGObjId(t);
    }
    ret = debug_SelectCsvWindowVal((int)"object target", 0xA, 0x3C, 0xA, n, (int)&targetGObjIdx,
                                   (int (*)(int, int))debug_TargetGObj_Func, 0);
    if (D_0063B408 != (int *)GetGObjP(targetGObjIdx)) {
        CameraSetMode(2);
        CameraChangeTargetParallel((int)D_0063B408, GetGObjP(targetGObjIdx));
        if (D_0063B408 != 0) {
            D_0063B408[0x14] = D_0063B40C;
        }
        D_0063B408 = (int *)GetGObjP(targetGObjIdx);
        D_0063B40C = D_0063B408[0x14];
    }
    D_0063B408 = (int *)GetGObjP(targetGObjIdx);
    D_00639EC0 = (int)D_0063B408;
    Camctrl_SetTarget((int)D_0063B408, 0, 3);
    debug_PrintfDummy(16, 16, 0xFFFFFFFF, "GObj address:%p", D_00639EC0);
    if ((D_0063B410++ & 7) == 0) {
        D_0063B408[0x14] = ~D_0063B408[0x14];
    }
    if (ret != 0) {
        D_0063B408[0x14] = D_0063B40C;
        if (ret < 0) {
            Camctrl_SetTarget(D_0063B404, 0, 3);
            D_00639EC0 = D_0063B404;
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

extern int D_002C1270[];
/* kept local: this TU's uses of GetGObjP do not fit the prototype in GobjProc.h */
extern int GetGObjP();

char *debug_TargetGObj_Func(void)
{
    int idx = *(int *)((char *)GetGObjP() + 0xC);
    return (char *)D_002C1270 + idx * 0x64;
}
