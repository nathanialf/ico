#include "flag.h"
#include "ios.h"
#include "attackCheckBoundary.h"
#include "memory.h"
#include "DisplayP2O.h"
#include "Light.h"
#include "Matrix.h"
#include "Primitive.h"
#include "clothAnimation.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "quaternion.h"
#include <string.h>
#include "include_asm.h"

/* InitFlagGeo builds a cloth from the laid-out object's row of layoutClothDef
   (attackCheckBoundary.h): its corners, the cloth type in the low four bits,
   the rows and columns, the length shared out over the columns and the fall. */

/* the flag's cloth template, copied into every new config; InitFlagGeo
   passes __LINE__, so its lines below are kept out of clang-format */
static ClothCfg flagCfg = {8, 50.0f, 10, 0, 0, 0, 5.0f}; /* derived name */

/* clang-format off */
INCLUDE_ASM(InitFlagGeo);

/* clang-format on */

INCLUDE_ASM(FlagGeo);

INCLUDE_ASM(FlagDL);
