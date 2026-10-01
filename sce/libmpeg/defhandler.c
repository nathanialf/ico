/* Vendor SCE library member: libmpeg.a(defhandler.o).  MAIN.MAP's member size
 * (0x1C) tiles the retail run, VMA 0x26CBA8..0x26CBC4, 2 functions, then 12
 * bytes of link fill to mpc.o's 16-aligned start: the default DMA stop and
 * restart handlers sceMpegCreate installs. */
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
