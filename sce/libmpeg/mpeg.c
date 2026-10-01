/* libmpeg.a(mpeg.o): the sceMpeg entry points, the callback dispatch, the
 * arena allocator and the picture loop. */
#include <libmpeg.h>
#include <libmpeg_internal.h>
#include <eeregs.h>
#include <eekernel.h>
#include <libipu.h>

/* the library's build stamp, the member's first .data */
static char sceMpegVersion[16] = "PsIIlibmpeg 2200"; /* derived name */

/* The DMAC and IPU registers are hardware the DMAC itself updates, so every
   access is volatile, except the second write of the enable register at
   0x1000F590, whose address is already live from the first write. */
void sceMpegInit(void)
{
    DIntr();
    *D_ENABLEW = *D_ENABLER | 0x10000;
    *D3_CHCR &= 0xFFFFFEFF;
    *D4_CHCR &= 0xFFFFFEFF;
    *(unsigned int *)D_ENABLEW = *D_ENABLER & 0xFFFEFFFF;
    EIntr();
    *D3_QWC = 0;
    *D4_QWC = 0;
    sceIpuInit();
}

int sceMpegCreate(sceMpeg *mp, void *buf, int size)
{
    MpegSys *p = (MpegSys *)((((unsigned int)buf + 3) >> 2) << 2);
    unsigned int n = size - ((char *)p - (char *)buf);

    if (n < sizeof(MpegSys)) {
        _Error("The size of work area is too small");
        return 0;
    }
    mp->sys = p;
    _alalcInit(&p->heap, (int)(p + 1), n - sizeof(MpegSys));
    mp->width = 0;
    mp->height = 0;
    mp->frameCount = 0;
    mp->pts = -1;
    mp->dts = -1;
    mp->flags = 0;
    mp->pts2nd = -1;
    mp->dts2nd = -1;
    mp->flags2nd = 0;
    p->centerOffX[0] = 0;
    p->centerOffX[1] = 0;
    p->centerOffX[2] = 0;
    p->centerOffY[0] = 0;
    p->centerOffY[1] = 0;
    p->centerOffY[2] = 0;
    p->dispWidth = 0;
    p->dispHeight = 0;
    p->picStructure = 0;
    p->imageBuff = 0;
    p->buffWidth = 0;
    p->buffHeight = 0;
    p->buffSize = 0;
    p->brokenLink = 0;
    p->ptmState = 0;
    p->cb[0].func = 0;
    p->cb[1].func = 0;
    p->cb[4].func = 0;
    p->cb[5].func = 0;
    p->cb[6].func = 0;
    p->ptm = -1;
    p->cb[2].func = _defStopDMA;
    p->cb[3].func = _defRestartDMA;
    p->strCb = (struct StrCb *)_alalcAlloc(&p->heap, 0x600, 8);
    p->nStrCb = 0;
    p->frameBuff[0] = 0;
    p->frameBuff[1] = 0;
    p->frameBuff[2] = 0;
    p->usePtsGap = 0;
    p->ptsGap = 0;
    p->lastShow = 0;
    p->halfCount = 0;
    p->frameBase = 0;
    p->lastPts = -1;
    p->csc = 1;
    _theSceMpeg = mp;
    p->ni = -1;
    p->np = -1;
    p->nb = -1;
    _clearOnce();
    sceMpegReset(mp);
    sceMpegClearRefBuff(mp);
    _forwFrame = _refFrame0;
    _backFrame = _refFrame1;
    _zFrame = _refFrame2;
    _forwTop = _refTop0;
    _backTop = _refTop1;
    _zTop = _refTop2;
    _forwBot = _refBot0;
    _backBot = _refBot1;
    _zBot = _refBot2;
    _alalcSetDynamic(&p->heap);
}

int sceMpegDelete(sceMpeg *m)
{
    return 1;
}

void sceMpegAddBs(int a0, int data, int size)
{
    int rounded = (size + 0x13) / 16 * 16;
    _bsDatap = data;
    _bsDataSize = rounded;
    _sendDataToIPU(data, rounded);
}

int sceMpegGetPicture(sceMpeg *mp, unsigned int buf, int size)
{
    MpegSys *p = mp->sys;
    buf = (buf & 0x0FFFFFFF) | 0x20000000;
    p->csc = 1;
    p->imageBuff = buf;
    p->buffSize = size;
    p->buffHeight = 0;
    p->buffWidth = 0;
    return _getpic(mp);
}

int sceMpegGetPictureRAW8(sceMpeg *mp, unsigned int buf, int size, int a3)
{
    MpegSys *p = mp->sys;
    p->buffSize = size;
    p->imageBuff = (buf & 0x0FFFFFFF) | 0x20000000;
    p->csc = 0;
    p->buffHeight = 0;
    p->buffWidth = 0;
    return _getpic(mp);
}

int sceMpegGetPictureRAW8xy(sceMpeg *mp, unsigned int buf, int mbw, int mbh)
{
    MpegSys *p = mp->sys;
    int prod;
    p->buffHeight = mbh << 4;
    p->imageBuff = (buf & 0x0FFFFFFF) | 0x20000000;
    prod = mbw * mbh;
    p->buffSize = prod;
    p->buffWidth = mbw << 4;
    p->csc = 0;
    return _getpic(mp);
}

void sceMpegSetDecodeMode(sceMpeg *mp, int ni, int np, int nb)
{
    MpegSys *p = mp->sys;
    p->ni = ni;
    p->np = np;
    p->nb = nb;
}

void sceMpegGetDecodeMode(sceMpeg *mp, int *ni, int *np, int *nb)
{
    MpegSys *p = mp->sys;
    *ni = p->ni;
    *np = p->np;
    *nb = p->nb;
}

int sceMpegIsEnd(sceMpeg *mp)
{
    return mp->sys->isEnd;
}

int sceMpegIsRefBuffEmpty(sceMpeg *mp)
{
    MpegSys *p = mp->sys;
    return p->refCount == 0;
}

void sceMpegReset(sceMpeg *mp)
{
    MpegSys *p = mp->sys;
    p->isEnd = 0;
    p->refCount = 0;
    p->outState = 0;
    mp->frameCount = 0;
    p->lastPts = -1;
    p->frameBase = 0;
    _clearEach();
    _totalFrames = 0;
    _initSeqAgain();
}

int sceMpegClearRefBuff(sceMpeg *mp)
{
    if (_forwFrame != 0)
        *(int *)((char *)_forwFrame + 0x28) = 0;
    if (_forwTop != 0)
        *(int *)((char *)_forwTop + 0x28) = 0;
    if (_forwBot != 0)
        *(int *)((char *)_forwBot + 0x28) = 0;
    if (_backFrame != 0)
        *(int *)((char *)_backFrame + 0x28) = 0;
    if (_backTop != 0)
        *(int *)((char *)_backTop + 0x28) = 0;
    if (_backBot != 0)
        *(int *)((char *)_backBot + 0x28) = 0;
    return 1;
}

sceMpegCallback sceMpegAddCallback(sceMpeg *mp, int type, sceMpegCallback func, void *data)
{
    MpegSys *p = mp->sys;
    sceMpegCallback old;
    p->cb[type].data = data;
    old = p->cb[type].func;
    p->cb[type].func = func;
    return old;
}

int _dispatchMpegCallback(sceMpeg *mp, int *cbdata)
{
    int rv = 0;
    if (mp != 0) {
        MpegSys *p = mp->sys;
        if (p != 0) {
            int type = *cbdata;
            sceMpegCallback fn = p->cb[type].func;
            if (fn != 0) {
                rv = fn(mp, cbdata, p->cb[type].data);
            }
        }
    }
    return rv;
}

void _dispatchMpegCbNodata(sceMpeg *mp)
{
    int buf[8];
    buf[0] = 1;
    _dispatchMpegCallback(mp, buf);
}

void sceMpegSetDefaultPtsGap(sceMpeg *mp, long long gap)
{
    MpegSys *p = mp->sys;
    p->usePtsGap = 1;
    p->ptsGap = gap;
}

void sceMpegResetDefaultPtsGap(sceMpeg *mp)
{
    MpegSys *p = mp->sys;
    p->usePtsGap = 0;
    p->ptsGap = 0;
}

void sceMpegSetImageBuff(int buff)
{
    MpegSys *q = _theSceMpeg->sys;
    q->imageBuff = buff;
}

int sceMpegDispWidth(sceMpeg *mp)
{
    return mp->sys->dispWidth;
}

int sceMpegDispHeight(sceMpeg *mp)
{
    return mp->sys->dispHeight;
}

int *sceMpegDispCenterOffX(sceMpeg *mp)
{
    return mp->sys->centerOffX;
}

/* returns the horizontal offsets too, as the ROM's code does */
int *sceMpegDispCenterOffY(sceMpeg *mp)
{
    return mp->sys->centerOffX;
}

int sceSetBrokenLink(sceMpeg *mp, int pending)
{
    MpegSys *p = mp->sys;
    int old = p->brokenLink;
    p->brokenLink = pending;
    return old;
}

void sceSetPtm(sceMpeg *mp, long long ptm)
{
    MpegSys *p = mp->sys;
    p->ptm = ptm;
    p->ptmState = 1;
}

void _alalcInit(MpegHeap *heap, int base, int size)
{
    heap->base = base;
    heap->size = size;
    heap->cur = base;
    heap->dynamic = base;
}

void _alalcSetDynamic(MpegHeap *heap)
{
    heap->dynamic = heap->cur;
}

void _alalcFree(MpegHeap *heap)
{
    heap->cur = heap->dynamic;
}

int _alalcAlloc(MpegHeap *heap, int size, unsigned int align)
{
    unsigned int rounded;
    unsigned int total;
    rounded = ((heap->cur + align - 1) / align) * align;
    total = rounded + size;
    if (heap->base + heap->size >= total) {
        heap->cur = total;
        return rounded;
    }
    _Error("work area size is too small");
    return 0;
}

int _alalcRest(MpegHeap *heap)
{
    return heap->base + heap->size - heap->cur;
}

int _getpic(sceMpeg *mp)
{
    int code = 1;
    int ret = 0;
    MpegSys *p = mp->sys;
    int v = p->imageBuff;

    p->isEnd = 0;
    if ((v & 0x3F) != 0) {
        _Error1("image buffer needs to be aligned to 64byte boundary(0x%08x)", v);
        return -1;
    }
    _isOutputPicture = 0;
    do {
        if (ret != -1) {
            do {
                code = _nextHeader();
            } while (code != 0 && _picture_structure != p->picStructure && _isMpeg2 != 0);
        }
        switch (code) {
        case 0:
            _sceMpegFlush(mp);
            p->isEnd = 1;
            break;
        case 1:
            p->bCount = 0;
            p->pCount = 0;
            p->iCount = 0;
            ret = _decodeOrSkip(mp, 0, p->ni);
            p->iCount = p->iCount + 1;
            break;
        case 2:
            ret = _decodeOrSkip(mp, p->pCount, p->np);
            p->pCount = p->pCount + 1;
            break;
        case 3:
        case 4:
            ret = _decodeOrSkip(mp, p->bCount, p->nb);
            p->bCount = p->bCount + 1;
            break;
        }
    } while (_isOutputPicture == 0);
    return 1;
}

int _decodeOrSkipFrame(sceMpeg *mp, int count, int limit)
{
    int skip = 0;
    int ret;
    int t;
    int second;
    MpegSys *p = mp->sys;

    if (limit == -1 || count < limit) {
        int ok;
        int decoded;

        if (p->outState == 0) {
            mp->frameCount = 0;
            p->outState = 1;
        }
        ok = _updateRefImage(0);
        decoded = 0;
        if (ok != 0) {
            decoded = _decPicture(_totalFrames, p->refCount) != 0;
        }
        ret = decoded;
    } else {
        ret = _updateRefImage(0);
        _dispatchMpegCbNodata(mp);
        skip = 1;
    }
    _outputFrame(_totalFrames, p->refCount);
    if (_picture_structure != 3 && skip == 0) {
        _isSecondField = _isSecondField == 0;
    }
    t = _totalFrames;
    second = _isSecondField;
    mp->frameCount = t - p->frameBase;
    if (second == 0) {
        int f = p->refCount;

        _totalFrames = t + 1;
        p->refCount = f + 1;
    }
    return ret;
}

int _decodeOrSkip(sceMpeg *mp, int count, int limit)
{
    if (_picture_structure != 3) {
        return _decodeOrSkipField(mp, count, limit);
    }
    return _decodeOrSkipFrame(mp, count, limit);
}

int _decodeOrSkipField(sceMpeg *mp, int count, int limit)
{
    int dec = 0;
    int ret;
    int t;
    int want;
    int ok;
    int base;
    MpegSys *p = mp->sys;

    _isSecondField = 0;
    if (limit == -1 || count < limit) {
        dec = 1;
    }
    if (p->outState == 0) {
        mp->frameCount = 0;
        p->outState = 1;
    }
    if (_updateRefImage(0) != 0 && dec != 0) {
        _decPicture(_totalFrames, p->refCount);
    }
    _isSecondField = 1;
    if (_nextHeader() == 0) {
        _sceMpegFlush(mp);
        p->isEnd = 1;
        return 0;
    }
    want = 2;
    if (p->picStructure != 1) {
        want = 1;
    }
    if (_picture_structure != want) {
        return -1;
    }
    ret = 0;
    ok = 0;
    if (_updateRefImage(1) != 0) {
        ok = 1;
    }
    if (ok != 0 && dec != 0) {
        if (_decPicture(_totalFrames, p->refCount) != 0) {
            ret = 1;
        }
    }
    _outputFrame(_totalFrames, p->refCount);
    t = _totalFrames;
    base = p->frameBase;
    _isSecondField = 0;
    mp->frameCount = t - base;
    _totalFrames = t + 1;
    p->refCount = p->refCount + 1;
    if (dec == 0) {
        _dispatchMpegCbNodata(mp);
    }
    return ret;
}

int _sceMpegFlush(sceMpeg *mp)
{
    MpegSys *p = mp->sys;
    int ret = 0;
    if (p->refCount != 0 && p->outState != 0) {
        _lastFrame(_totalFrames);
        mp->frameCount = _totalFrames - p->frameBase;
        p->refCount = 0;
        ret = 1;
    }
    return ret;
}
