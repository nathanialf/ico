#include "common.h"

extern void playSEConditionID(int a0, int a1);

void WallLeverDL(int a0) {
    playSEConditionID(a0, 0x2);
}

void CheckReadyAllSwitches(int a0) {
    playSEConditionID(a0, 0x24);
}

void InitBoxGeo(int a0) {
    playSEConditionID(a0, 0x4);
}
