#include "typedef.h"
#include "debug.h"
#include "camera-root.h"
#include "debug_menu.h"

/* kept local: agrees with GobjProc.h, which this TU does not include (GetGObjP differ) */
extern int GetMaxGObj(void);
/* kept local: agrees with GobjProc.h, which this TU does not include */
extern int GetGObjP(); /* unprototyped: C89 default int return, a GObj handle */
/* kept local: agrees with GobjProc.h, which this TU does not include (GetGObjP differ) */
extern int GetGObjId(int gobj);
extern int D_0063B404;
extern int *D_0063B408;
extern int D_0063B40C;
extern int D_0063B410;
/* kept local: int here, GObj * in main.h */
extern int CurrentTargetGObj;

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
    CurrentTargetGObj = (int)D_0063B408;
    Camctrl_SetTarget((int)D_0063B408, 0, 3);
    debug_PrintfDummy(16, 16, 0xFFFFFFFF, "GObj address:%p", CurrentTargetGObj);
    if ((D_0063B410++ & 7) == 0) {
        D_0063B408[0x14] = ~D_0063B408[0x14];
    }
    if (ret != 0) {
        D_0063B408[0x14] = D_0063B40C;
        if (ret < 0) {
            Camctrl_SetTarget(D_0063B404, 0, 3);
            CurrentTargetGObj = D_0063B404;
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
/* kept local: agrees with GobjProc.h, which this TU does not include */
extern int GetGObjP();

char *debug_TargetGObj_Func(void)
{
    int idx = ((PObjGObj *)GetGObjP())->kind;
    return ((ObjKindEnt *)((char *)objKindData + idx * 0x64))->name;
}
