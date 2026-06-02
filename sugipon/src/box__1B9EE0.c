#include "common.h"

extern void playSEConditionID(int a0, int a1);

void execAutoMove(int a0) {
    playSEConditionID(a0, 0xD);
}

void initWheels(int a0) {
    playSEConditionID(a0, 0x1E);
}
