#include "camera-set-manager.h"

void *TopCameraSetDataOfCurrentStage;

int NumOfGroup;

void *TopOfCameraGroup;

void *TopOfCameraPin;

void InitCameraSetManager(void)
{
    TopCameraSetDataOfCurrentStage = 0;
}
