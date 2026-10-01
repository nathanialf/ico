#include "typedef.h"
#include "DisplayP2O.h"
#include "debug.h"
#include "Packet.h"
#include "RegistPacket.h"
#include "MicroCode.h"
#include <libdma.h>
#include "Shadow.h"

/* The TU's whole .rodata run, VMA 0x54DB10..0x54DB30: debug_PrintFontWindow's
   format for the display-object counter.  The explicit 32 is the ROM's own
   object size, so its zero tail belongs to the array rather than to link pad. */
static const char dispObjFormat[32] = "display object = %d";

/* .sdata, DisplayP2O.o's one word (MAIN.MAP 0x4): the display-object count
   p2o_HideDispVU1 records and reports, none yet. */
static int dispObjCount = -1; /* derived name */

/* kept local: int here, int * in Basic.h */
extern int dmaVif;

void p2o_MakePacket(Sub15C *a0)
{
    a0->model->dobj = a0;
    pac_MakePacket(a0);
}

inline void p2o_SetDefaultEnviroment(void) {}

void p2o_DispShadowVolume(int a0)
{
    shadow_Render(((GObj *)a0)->p_15C);
}

void p2o_HideDispVU1(int a0)
{
    dispObjCount = a0;
    if (debug_window_flag != 0) {
        debug_PrintFontWindow(0xCCCCCC00, dispObjFormat, a0);
    }
}

void p2o_DispVU1DObj(void *req)
{
    reg_DispObj(req);
}

void p2o_DispVU1DObjMulti(void *req)
{
    reg_DispObj(req);
}

void p2o_DispVU1Multi(GObj *self)
{
    p2o_DispVU1DObjMulti(GOBJ_SUB(self));
}

void p2o_DispVU1MultiDefault(GObj *self)
{
    p2o_DispVU1Multi(self);
}

void p2o_DispVU1(GObj *self)
{
    p2o_DispVU1DObj(GOBJ_SUB(self));
}

void p2o_DispVU1Default(GObj *self)
{
    p2o_DispVU1(self);
}

void p2o_TransMicroProgram(void)
{
    sceDmaSend(dmaVif, MicroCodeAddress[1]);
}
