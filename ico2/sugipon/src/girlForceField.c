#include "typedef.h"
#include "sugiCommon.h"
#include "memory.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "gamesys.h"

/* Per-object force-field state: InitGirlForceFieldGeo returns it, the object
   creator hangs it at the display object's work and GirlForceFieldDL reads it. */
typedef struct GirlForceFieldWork { /* field names derived */
    float radius;
    float invRadius;
    int frame;
} GirlForceFieldWork; /* derived name */

#include "girlForceField.h"
#include "ios.h"
#include "main.h"
#include "StageAnimation.h"
#include "sceneManager.h"
#include "include_asm.h"

/* the girl's blue, the colour boy.c's position-sync marker draws her sphere
   in; nothing reads it */
static int forceFieldColor[4] = {64, 96, 128, 128}; /* derived name */

inline void GirlForceFieldGeo(void) {}

/* the action table the layout rows select into */
extern OaRecB objAction[];

INCLUDE_ASM(GirlForceFieldDL);

INCLUDE_ASM(InitGirlForceFieldGeo);
