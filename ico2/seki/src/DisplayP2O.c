#include "common.h"
#include "typedef.h"
#include "DisplayP2O.h"
#include "debug.h"
#include "Packet.h"
#include "RegistPacket.h"
#include "MicroCode.h"
#include <libdma.h>

/* kept local: this TU's uses of shadow_Render do not fit the prototype in Shadow.h */
extern void shadow_Render();

/* The TU's whole .rodata run, VMA 0x54DB10..0x54DB30: debug_PrintFontWindow's
   format for the display-object counter.  The explicit 32 is the ROM's own
   object size, so its zero tail belongs to the array rather than to link pad. */
static const char dispObjFormat[32] = "display object = %d";

extern int D_00639F44;
extern int D_0063B160;
extern int dmaVif;

void p2o_MakePacket(char *a0)
{
    *(char **)(*(char **)(a0 + 0x854) + 0x28) = a0;
    pac_MakePacket(a0);
}

inline void p2o_SetDefaultEnviroment(void) {}

void p2o_DispShadowVolume(int a0)
{
    shadow_Render((int)((GObj *)(a0))->p_15C);
}

void p2o_HideDispVU1(int a0)
{
    D_00639F44 = a0;
    if (D_0063B160 != 0) {
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
