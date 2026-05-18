#include "matching.h"

extern float D_006309AC;
extern float D_006309B0;
extern float D_006309B4;

float func_0010D360(float x)
{
    float t;
    x += 50.0f;
    t = (float)(int)(x * D_006309AC) * 200.0f;
    x -= t;
    if (x < 100.0f) {
        return x * D_006309B0 - 0.5f;
    }
    return -(x - 100.0f) * D_006309B4 + 0.5f;
}
