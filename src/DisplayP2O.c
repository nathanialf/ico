#include "common.h"

#include "vu0.h"
#include "ico/types.h"

/* header prototypes (order fixes the inline tail) */
void p2o_SetDefaultEnviroment(void);
extern void pac_MakePacket(void *a0);
extern void shadow_Render();
/* .rodata — carved VMA 0x54DB10..0x54DB30; string + ROM zero pad,
   bytes verified against baserom/pal/baseelf.rom */
const char D_0054DB10[32] = "display object = %d";
extern int D_00639F44;
extern int D_0063B160;
extern void debug_PrintFontWindow();
extern void reg_DispObj(void *req);
extern void p2o_DispVU1DObjMulti__pn() __asm__("p2o_DispVU1DObjMulti");
extern void p2o_DispVU1DObj__pn() __asm__("p2o_DispVU1DObj");
extern void p2o_DispVU1__pn() __asm__("p2o_DispVU1");
extern int D_00290B24[];
extern int dmaVif;
extern void sceDmaSend();
void p2o_MakePacket(char *a0) {
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
        debug_PrintFontWindow(0xCCCCCC00, D_0054DB10, a0);
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
void p2o_DispVU1Multi(GObj *self) {
    p2o_DispVU1DObjMulti__pn(GOBJ_SUB(self));
}
void p2o_DispVU1MultiDefault(GObj *self) {
    p2o_DispVU1Multi(self);
}
void p2o_DispVU1(GObj *self) {
    p2o_DispVU1DObj__pn(GOBJ_SUB(self));
}
void p2o_DispVU1Default(GObj *self) {
    p2o_DispVU1__pn(self);
}
void p2o_TransMicroProgram(void)
{
    sceDmaSend(dmaVif, D_00290B24[0]);
}
