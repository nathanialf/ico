#include "girl.h"
#include "DObj.h"
#include "debug.h"
#include "memory.h"
#include "obj_manager.h"
#include "act-game.h"
#include "girl_act.h"
#include "script.h"
#include "Matrix.h"
#include "RegistPacket.h"
#include "actressLight.h"
#include "clothAnimation.h"
#include "geometryManager.h"
#include "handManager.h"
#include "lodManager.h"
#include "matrixDrive.h"
#include "motionManager2.h"
#include "motionOrientManager.h"
#include "quaternion.h"
#include "wireLetter.h"
#include <libvu0.h>
#include "ios.h"
#include "main.h"
#include "DisplayP2O.h"
#include "sceneManager.h"
#include "include_asm.h"

static void setGirlClothSetting(int lv);

/* The girl's work record: her kind, the four cloths and the hair she wears
   with the switches SetGirlClothDispSwitch sets (case 0 for cloth0, 1 for
   cloth1, cloth2 and the hair, 2 for cloth3), the crown and the two
   ornaments, and the two hint voices' ready and played flags.  The cloth and
   model pointers are held as words: InitGirlGeo's zero stores to them keep
   their order against the record's other int stores only as int stores. */
typedef struct GirlWork { /* field names derived */
    int kind;             /* 0x00, the layout's 0x30 word */
    int cloth0Disp;       /* 0x04 */
    int cloth0;           /* 0x08, a Cloth4D */
    int cloth12Disp;      /* 0x0C */
    int cloth1;           /* 0x10, a Cloth4D */
    int cloth2;           /* 0x14, a Cloth4D */
    int hair;             /* 0x18, the Cloth4D the debug hair settings drive */
    int cloth3Disp;       /* 0x1C */
    int cloth3;           /* 0x20, a Cloth4D */
    int crown;            /* 0x24, a display object */
    int ornamentDisp;     /* 0x28 */
    int ornament0;        /* 0x2C, a display object */
    int ornament1;        /* 0x30, a display object */
    int hint1Ready;       /* 0x34 */
    int hint2Ready;       /* 0x38 */
    int hint1Played;      /* 0x3C */
    int hint2Played;      /* 0x40 */
} GirlWork;               /* derived name */

/* file-static: boy.c has a global function of the same name */
INCLUDE_ASM(execClothes_girl);

/* file-static: boy.c has a global function of the same name */
static void dispCrown(GObj *gobj, Sub15C *acc);
/* file-static: boy.c has a global function of the same name */
static void dispClothes(GObj *gobj);

INCLUDE_ASM(dispClothes_girl);

/* The girl's cloth meshes, their hang tables and parameters, as InitGirlGeo
   builds them: this build's run (0x4500 bytes) differs from PAL's in its
   meshes and has no cloth parameter sets. */
INCLUDE_ASM(D_004E0620);

INCLUDE_ASM(D_0065FC00);

INCLUDE_ASM(D_0067ADF8);

INCLUDE_ASM(InitGirlGeo);

INCLUDE_ASM(GirlGeo);

/* the name the cloth debug display prints for each girl kind */
static char *girlClothName[4] = {"", "DEVIL", "STONE", 0}; /* derived name */

/* the girl's cloth work */
static inline GirlWork *getGirlCloth(GObj *gobj) /* derived name */
{
    return GOBJ_SUB(gobj)->work;
}

static void debugWireStringGirl(GObj *gobj);

INCLUDE_ASM(debugWireStringGirl);

void GirlDL(GObj *gobj)
{
    p2o_SetDefaultEnviroment();
    p2o_DispVU1(gobj);
    dispClothes(gobj);
    debugWireStringGirl(gobj);
}

INCLUDE_ASM(GirlAI);
