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
extern int D_0063C390;
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
        D_0063C390 = GetGObjId(t);
    }
    ret = debug_SelectCsvWindowVal((int)"object target", 0xA, 0x3C, 0xA, n, (int)&D_0063C390,
                                   (int (*)(int, int))debug_TargetGObj_Func, 0);
    if (D_0063B408 != (int *)GetGObjP(D_0063C390)) {
        CameraSetMode(2);
        CameraChangeTargetParallel((int)D_0063B408, GetGObjP(D_0063C390));
        if (D_0063B408 != 0) {
            D_0063B408[0x14] = D_0063B40C;
        }
        D_0063B408 = (int *)GetGObjP(D_0063C390);
        D_0063B40C = D_0063B408[0x14];
    }
    D_0063B408 = (int *)GetGObjP(D_0063C390);
    D_00639EC0 = (int)D_0063B408;
    Camctrl_SetTarget((int)D_0063B408, 0, 3);
    debug_PrintfDummy(0x10, 0x10, 0xFFFFFFFF, "GObj address:%p", D_00639EC0);
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

extern int D_0063C388;
extern int D_0063C38C;

void init_debug_menu(void)
{
    D_0063C388 = 0;
    D_0063C38C = 1;
    D_0063C390 = 0;
}

extern int D_002C1270[];
/* kept local: this TU's uses of GetGObjP do not fit the prototype in GobjProc.h */
extern int GetGObjP();

char *debug_TargetGObj_Func(void)
{
    int idx = *(int *)((char *)GetGObjP() + 0xC);
    return (char *)D_002C1270 + idx * 0x64;
}
