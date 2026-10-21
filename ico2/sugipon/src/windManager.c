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

inline void SetWindManager(float a, float b, float c, float d, float e, float f, float g, float h)
{
    float buf1[4] = {a, b, c, 1.0f};
    float buf2[4] = {d, e, f, 0.0f};

    windSpeed = g;
    windSpeedInv = 1.0f / g;
    windVariance = h;
    windVarianceInv = 1.0f / h;
    gustAim = g;
    gustSpeed = g;
    InitWindField(1, g, buf1, buf2);
}

inline void InitWindManager(int no)
{
    const float *pos = stageData[no].windPos;
    const float *dir = stageData[no].windDir;

    SetWindManager(pos[0], pos[1], pos[2], dir[0], dir[1], dir[2], stageData[no].windSpeed,
                   stageData[no].windAmp);
    windKind = no;
}

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

inline void ReinitWindManager(void)
{
    InitWindManager(windKind);
}
