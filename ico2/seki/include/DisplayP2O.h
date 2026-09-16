/*
 * ico2/seki/include/DisplayP2O.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what DisplayP2O.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef DISPLAYP2O_H
#define DISPLAYP2O_H

#include "typedef.h"

extern void p2o_DispVU1(GObj *self);
extern void p2o_DispVU1DObj(void *req);
extern void p2o_DispVU1DObjMulti(void *req);
extern void p2o_DispVU1Default(GObj *self);
extern void p2o_DispVU1Multi(GObj *self);
extern void p2o_MakePacket(char *a0);
extern void p2o_SetDefaultEnviroment(void);
extern void p2o_TransMicroProgram(void);

#endif /* DISPLAYP2O_H */
