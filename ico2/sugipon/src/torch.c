#include "sugiCommon.h"
#include "debug.h"
#include "memory.h"
#include "gobj.h"
#include "act-game.h"
#include "frameDependSequence.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "quaternion.h"

typedef struct TorchGeoWork { /* field names derived */
    /* 0x00 */ int flags;
    /* 0x04 */ int pad04[3];
    /* 0x10 */ float pos[4];
    /* 0x20 */ int lightOn;
    /* 0x24 */ int burnTime; /* frames the torch has been alight */
    /* 0x28 */ int life;
    /* 0x2C */ int fadeStart; /* the burn time the flame starts to fade at */
    /* 0x30 */ int chainFlag;
    /* 0x34 */ int effect[5]; /* the particle effects a lit torch runs, -1 when off */
    /* 0x48 */ int pad48[2];
} __attribute__((aligned(16))) TorchGeoWork; /* derived name */

#include "torch.h"
#include <libvu0.h>
#include "particleEffect.h"
#include "ios.h"
#include "main.h"
#include "sceneManager.h"
#include "include_asm.h"

/* the torch work record InitTorchGeo starts every torch from: 0x28 bytes,
   8-aligned, in this build */
INCLUDE_ASM(emptyTorchWork);

inline int IsTorchLightOn(GObj *torch);

INCLUDE_ASM(torchOffSE);

INCLUDE_ASM(LightTorchOn);

INCLUDE_ASM(LightTorchOff);

static void torchDrainControl(GObj *gobj, float level);

INCLUDE_ASM(moveTorch);

static void setPauseFlag(GObj *gobj, int flag);

INCLUDE_ASM(CheckTorchChainReactionReverse);

/* The chain-reaction functions are stubs, and PAL's inline check they share
   (chainReactionBlocked) is not carried: the demo's torch.o .rodata holds
   only the file name, none of that check's two messages. */

static void procChainReaction(GObj *gobj);

INCLUDE_ASM(TorchGeo);

INCLUDE_ASM(InitTorchGeo);

INCLUDE_ASM(TorchDL);

INCLUDE_ASM(IsTorchLightOn);

INCLUDE_ASM(CheckTorchChainReaction);

INCLUDE_ASM(SetTorchLife);

INCLUDE_ASM(SetTorchChainReactionFlag);

INCLUDE_ASM(UpdateRealTimeGeometryValue);
