#include "sugiCommon.h"
#include "main.h"

/* SetWindManager and InitWindManager are inline and expand into
 * ReinitWindManager; ExecWindManager is the file's only plain function. */

/* the wind kind, the base speed and its variance with their reciprocals, and
   the gust state */
static int windKind = -1; /* derived name */

static float windSpeed = 0; /* derived name */

static float windSpeedInv = 0; /* derived name */

static float windVariance = 0; /* derived name */

static float windVarianceInv = 0; /* derived name */

static float gustAim = 0; /* derived name */

static float gustSpeed = 0; /* derived name */

static int gustTimer = 0; /* derived name */

#include "windField.h"
#include "windManager.h"
#include "include_asm.h"

void ExecWindManager(void)
{
    gustTimer++;
    if (gustTimer >= 51) {
        float r = random_unit();
        gustTimer = 0;
        gustAim = windSpeed * ((r + r - 1.0f) * windVariance + 1.0f);
    }
    gustSpeed = gustSpeed + (gustAim - gustSpeed) * 0.1f;
    ExecWindField(gustSpeed);
}

inline float GetRegularizedWindSpeed(void *pos)
{
    float s;

    if (windSpeed == 0.0f || windVariance == 0.0f) {
        return 1.0f;
    }
    GetWindVector(&s, pos);
    return (s / (60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1])) * windSpeedInv -
            (1.0f - windVariance)) *
           0.5f * windVarianceInv;
}

INCLUDE_ASM(ReinitWindManager);

INCLUDE_ASM(SetWindManager);

INCLUDE_ASM(InitWindManager);
