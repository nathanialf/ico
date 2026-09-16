#include "common.h"
#include "generator.h"

void actSt13b2Generator(volatile int a0)
{
    Generator_Mask(a0);
    Generator_ResetCount(a0);
}
