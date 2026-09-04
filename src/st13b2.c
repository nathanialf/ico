#include "common.h"

extern void Generator_Mask(int a0);
extern void Generator_ResetCount(int a0);
void actSt13b2Generator(volatile int a0) {
    Generator_Mask(a0);
    Generator_ResetCount(a0);
}
