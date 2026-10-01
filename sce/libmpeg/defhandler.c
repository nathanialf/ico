/* libmpeg.a(defhandler.o): the default DMA stop and restart handlers
 * sceMpegCreate installs, then 12 bytes of link fill to mpc.o's 16-aligned
 * start. */
#include <libmpeg.h>
#include <libmpeg_internal.h>
#include <libipu.h>

void _defStopDMA(int **a0)
{
    sceIpuStopDMA((char *)a0[0x10] + 0x4C);
}

void _defRestartDMA(int **a0)
{
    sceIpuRestartDMA((char *)a0[0x10] + 0x4C);
}
