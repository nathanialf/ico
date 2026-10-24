#include "typedef.h"
#include "generator.h"

void actSt13b2Generator(GObj *volatile self)
{
    Generator_Mask(self);
#ifndef VERSION_JUN26
    Generator_ResetCount(self);
#endif
}
