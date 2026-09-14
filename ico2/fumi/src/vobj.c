#include "common.h"
#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_TransMatrixV(int a0);
extern void sceVu0UnitMatrix(void *a0);
extern void gif_StartPacketPri(int a0);
extern void gif_EndPacket(void);
extern void DrawLine(float *from, float *to, int color, int flag);
/* one 4-float vertex per entry; [3] is the run flag: 0 = keep drawing,
 * 2 = break the run and skip a vertex, anything else = end of list. */
extern float *D_0054A290[];

void DrawVObj(int no, int color)
{
    float *from;
    float *to;

    gif_StartPacketPri(0xB);

    from = D_0054A290[no];
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
