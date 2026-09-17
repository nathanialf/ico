#include "common.h"
#include "lineManager.h"
#include "matrixDrive.h"
#include <libvu0.h>

/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int a0);
/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket(void);

/* one 4-float vertex per entry; [3] is the run flag: 0 = keep drawing,
 * 2 = break the run and skip a vertex, anything else = end of list. */
static float vobjArrow[5][4] = {
    {-10.0f, -75.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 0.0f}, {10.0f, -75.0f, 0.0f, 0.0f},
    {-10.0f, -75.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f, 1.0f},
};

static float *vobjList[] = {&vobjArrow[0][0]};

void DrawVObj(int no, int color)
{
    float *from;
    float *to;

    gif_StartPacketPri(0xB);

    from = vobjList[no];
    to = from + 4;

    for (;;) {
        while (to[3] == 0.0f) {
            DrawLine(from, to, color, 0x800000);
            from = to;
            to += 4;
        }
        if (to[3] == 2.0f) {
            from = to + 4;
            to += 8;
        } else {
            break;
        }
    }

    gif_EndPacket();
}

void SetVObjRT(int a0, void *a1)
{
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    *(float *)((char *)a1 + 0xC) = 1.0f;
    MatrixDrive_TransMatrixV((int)a1);
}
