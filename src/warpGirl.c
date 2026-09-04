#include "common.h"

/* header prototypes (order fixes the inline tail) */
void warpGirlInit(void);
extern int warpGirlId;
inline void warpGirlInit(void) {
    warpGirlId = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/warpGirl", warpGirlOutStage);
INCLUDE_ASM("asm/nonmatchings/src/warpGirl", warpGirlInStage);
