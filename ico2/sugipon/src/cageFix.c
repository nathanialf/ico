#include "typedef.h"
#include "cageFix.h"
#include "cage.h"
#include "gobj.h"
#include "DisplayP2O.h"
#include "matrixDrive.h"
#include "include_asm.h"

inline int InitCageFixGeo(void)
{
    return 0;
}

INCLUDE_ASM(CageFixGeo);

void CageFixDL(GObj *self)
{
    Sub15C *d = self->dobj;
    if (d->disp != 0) {
        p2o_SetDefaultEnviroment();
        p2o_DispVU1DObjMulti(d);
    }
}
