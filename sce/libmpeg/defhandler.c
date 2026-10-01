/* libmpeg.a(defhandler.o): the default DMA stop and restart handlers
 * sceMpegCreate installs, then 12 bytes of link fill to mpc.o's 16-aligned
 * start. */
#include <libmpeg.h>
#include <libmpeg_internal.h>
#include <libipu.h>

int _defStopDMA(sceMpeg *mp, void *cbdata, void *data)
{
    sceIpuStopDMA(mp->sys->dmaEnv);
}

int _defRestartDMA(sceMpeg *mp, void *cbdata, void *data)
{
    sceIpuRestartDMA(mp->sys->dmaEnv);
}
