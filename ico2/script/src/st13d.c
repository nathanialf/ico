#include "common.h"

/* header prototypes (order fixes the inline tail) */
/* prototypes: their order is the inline tail's emission order */
void actSt13dInit(void);
void actSt13dInit(void);

inline void actSt13dInit(void) {}

typedef struct PosBox {
    long long lo; /* 0x00 */
    long long hi; /* 0x08 */
} PosBox;

typedef struct Act Act;

extern void *D_00639EA4;
extern Act *actInitialize(int a0);
extern void _ACTWait(int a0);
extern int gflagChk(int a0);
extern void ScpCallCameraOff(void);
extern void GetRootPosition(void *dst, void *obj);
extern int scpTriggerPosBox(float *p, float *pos, float *size);
extern int RequestStageChange(int a0, void *a1, int a2, float a3, float a4);
extern const PosBox D_00622F30;
extern const PosBox D_00622F20;

void actSt13dExit(volatile int a0)
{
    int x = a0;
    PosBox pos;
    PosBox size;
    PosBox p;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x12) == 0) {
        ScpCallCameraOff();
    }

    pos = D_00622F20;
    size = D_00622F30;

    GetRootPosition(&p, D_00639EA4);

    while (scpTriggerPosBox((float *)&p, (float *)&pos, (float *)&size) == 0) {
        _ACTWait(1);
    }

    RequestStageChange(2, D_00639EA4, 0, 16.0f, 16.0f);
}

extern const PosBox D_00622F40;

void actSt13dExitR(volatile int a0)
{
    int x = a0;
    PosBox pos;
    PosBox size;
    PosBox p;

    actInitialize(a0);
    _ACTWait(1);

    pos = D_00622F40;
    size = D_00622F30;

    GetRootPosition(&p, D_00639EA4);

    while (scpTriggerPosBox((float *)&p, (float *)&pos, (float *)&size) == 0) {
        _ACTWait(1);
    }

    RequestStageChange(7, D_00639EA4, 0, 16.0f, 16.0f);
}

extern const PosBox D_00622F50;

void actSt13dExitL(volatile int a0)
{
    int x = a0;
    PosBox pos;
    PosBox size;
    PosBox p;

    actInitialize(a0);
    _ACTWait(1);

    pos = D_00622F50;
    size = D_00622F30;

    GetRootPosition(&p, D_00639EA4);

    while (scpTriggerPosBox((float *)&p, (float *)&pos, (float *)&size) == 0) {
        _ACTWait(1);
    }

    RequestStageChange(8, D_00639EA4, 0, 16.0f, 16.0f);
}
