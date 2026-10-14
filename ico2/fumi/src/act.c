#include "debug.h"
#include "memory.h"
#include "obj_manager.h"
#include "act-game.h"
#include "commonact.h"
#include "mail-add-data.h"
#include "motionOrientManager.h"
#include "GifPacket.h"
#include "matrixDrive.h"
#include "motionManager2.h"
#include "isys.h"
#include "geometryManager.h"
#include "thread.h"
#include "lineManager.h"
#include "pad.h"
#include "gobj_process.h"
#include "main.h"

/* one zero word that nothing reads */
static int actUnusedWord = 0; /* derived name */

#include "act.h"
#include "enemy_act.h"
#include <libvu0.h>
#include <string.h>
#include "typedef.h"
#include "ios.h"
#include "fieldCollision.h"
#include "gamesys.h"
#include "include_asm.h"

void actChangeActBrain(GObj *self, void (*func)(), GProc **proc)
{
    GProc *old = *proc;
    GProc *n = actCreateSubThread(func, 20);
    *proc = n;
    if (old != 0) {
        debug_StdPrintfDummy("--b-- %p:act brain del %p\n", self, n);
        isysGObjProcRemove(old);
    } else {
        debug_StdPrintfDummy("--b-- %p:act brain NULL %p\n", self, n);
    }
}

void actChangeActMain(GObj *self, void (*func)(), GProc **proc)
{
    unsigned short fld = objLayout[self->labelId].procPri;
    GProc *old = *proc;
    GProc *ret;
    if (((long long)fld << 10) == 0) {
        ret = isysGObjProcAdd(self, func, 0, 0x13);
    } else {
        ret = isysGObjProcAddS(self, func, 0, 0x13, (long long)fld << 10);
    }
    *proc = ret;
    if (old != 0) {
        debug_StdPrintfDummy("--m-- %p:act main del %p\n", self, ret);
        isysGObjProcRemove(old);
    } else {
        debug_StdPrintfDummy("--m-- %p:act main NULL %p\n", self, ret);
    }
}

void actCreateMotionThread(void (*func)(), int pri, GProc **proc)
{
    GProc *old = *proc;
    GProc *ret = isysGObjProcAdd(isysCurrentGObj, func, 0, pri);
    *proc = ret;
    if (old != 0) {
        debug_StdPrintfDummy("--t-- %p:act mot del %p\n", *(int *)((char *)old + 4), ret);
        isysGObjProcRemove(old);
    } else {
        debug_StdPrintfDummy("--t-- %p:act mot NULL %p\n", ret, ret);
    }
}

INCLUDE_ASM_LIT(actCreateSubThread);

INCLUDE_ASM(after_func_exec);

INCLUDE_ASM(actInitialize_ext_charcter);

INCLUDE_ASM(actInitialize);

INCLUDE_ASM(act_check_intr_list);

INCLUDE_ASM(act_check_mail);

INCLUDE_ASM(BeforeFunc);

INCLUDE_ASM(ACTDebugMove);

INCLUDE_ASM(actInitialize_geo);

INCLUDE_ASM(actInitialize_only_charcter);

INCLUDE_ASM(ACTReserveTarget);

INCLUDE_ASM(_ACTRun);

INCLUDE_ASM(_ACTWait);

INCLUDE_ASM(actCreateSubThreadGOppArg);

INCLUDE_ASM(actCreateSubThread);

INCLUDE_ASM(actSetInterrupt);

INCLUDE_ASM(ConvertStickToAbsCoord);

INCLUDE_ASM(ActSetStartBrainStatus);

inline void actWaitCondition(int value, int mask)
{
    int t = value & mask;
    if (t == 0) {
        do {
            int count = (60 - systemStatus[0] * 10) / systemStatus[1] / 60;
            int n = 1;
            if (count != 0) {
                n = count;
            }
            if (n == 0) {
                for (;;) {
                    iosThreadSleep();
                }
            }
            if (n > 0) {
                int i = n;
                do {
                    iosThreadSleep();
                    i--;
                } while (i != 0);
            }
        } while (t == 0);
    }
}

/* The actor object: only the work pointer at +0x164 matters here. */
typedef struct { /* field names derived */
    char pad0[356];
    int work;
} ActSelf; /* derived name */

typedef union { /* field names derived */
    float f;
    int i;
} ActFWord; /* derived name */

/* The extended work block hung off the work block at +0x688; the three
   ten-entry histories at 0x900, 0x928 and 0x950 are read back in BeforeFunc. */
typedef struct { /* field names derived */
    char pad0[2304];
    int a900[10];
    int a928[10];
    int a950[10];
} ActExt; /* derived name */

/* The interrupt list lives at self+0x54: a count at +4 and 8-byte entries
   from +8. */
typedef struct { /* field names derived */
    int id;
    void *f4;
} IntrEnt; /* derived name */

typedef struct { /* field names derived */
    int f0;
    int n;
    IntrEnt ent[1];
} IntrList; /* derived name */

typedef union { /* field names derived */
    float f;
    int i;
} ActFloat; /* derived name */

/* motionOrientManager.h declares none of the motion tables */
extern MotionDef motionKind[];

/* one flag per mail list: a list whose flag is set is not checked for an
   interrupt while the status record's b11 is set */
typedef struct { /* field names derived */
    unsigned int w[4];
} IntrSkip; /* derived name */

/* this TU passes the packet priority that the prototype in
   seki/include/GifPacket.h leaves out */
