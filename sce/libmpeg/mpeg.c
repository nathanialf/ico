/* Vendor SCE library member: libmpeg.a(mpeg.o).  MAIN.MAP's member size (0xBD0)
 * tiles the retail run exactly, VMA 0x26B408..0x26BFD8, 35 functions: the
 * sceMpeg entry points, the callback dispatch, the arena allocator and the
 * picture loop. */
#include <libmpeg.h>
#include <eeregs.h>

/* the library's build stamp, the member's first .data */
static char sceMpegVersion[16] = "PsIIlibmpeg 2200"; /* derived name */

extern void DIntr();
extern int EIntr(void);
extern int sceIpuInit();

/* The DMAC and IPU registers are hardware the DMAC itself updates, so every
   access is volatile. The second write of the enable register at 0x1000F590 is
   plain: its address is already live in a register from the first write, and
   only a non-volatile store can be scheduled into the delay slot of jal EIntr. */
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

extern void _Error(void *a0);
extern void _alalcInit(int *a0, int a1, int a2);
extern int _alalcAlloc(unsigned int *a0, int a1, unsigned int a2);
extern void _alalcSetDynamic(int *a0);
extern void _clearOnce(void);
extern int sceMpegClearRefBuff();
extern void _defStopDMA();
extern void _defRestartDMA();
extern int _refFrame0[];
extern int _refFrame1[];
extern int _refFrame2[];
extern int _refTop0[];
extern int _refTop1[];
extern int _refTop2[];
extern int _refBot0[];
extern int _refBot1[];
extern int _refBot2[];
extern int *_forwFrame;
extern int *_backFrame;
extern int _zFrame[];
extern int *_forwTop;
extern int *_backTop;
extern int _zTop[];
extern int *_forwBot;
extern int *_backBot;
extern int _zBot[];

int sceMpegCreate(void *self, void *buf, int size)
{
    char *p = (char *)((((unsigned int)buf + 3) >> 2) << 2);
    unsigned int n = size - (p - (char *)buf);

    if (n < 0x118) {
        _Error("The size of work area is too small");
        return 0;
    }
    *(int *)((char *)self + 0x40) = (int)p;
    _alalcInit((int *)(p + 0x108), (int)(p + 0x118), n - 0x118);
    *(int *)((char *)self + 0x0) = 0;
    *(int *)((char *)self + 0x4) = 0;
    *(int *)((char *)self + 0x8) = 0;
    *(long long *)((char *)self + 0x10) = -1;
    *(long long *)((char *)self + 0x18) = -1;
    *(long long *)((char *)self + 0x20) = 0;
    *(long long *)((char *)self + 0x28) = -1;
    *(long long *)((char *)self + 0x30) = -1;
    *(long long *)((char *)self + 0x38) = 0;
    *(int *)(p + 0xB4) = 0;
    *(int *)(p + 0xB8) = 0;
    *(int *)(p + 0xBC) = 0;
    *(int *)(p + 0xC0) = 0;
    *(int *)(p + 0xC4) = 0;
    *(int *)(p + 0xC8) = 0;
    *(int *)(p + 0xCC) = 0;
    *(int *)(p + 0xD0) = 0;
    *(int *)(p + 0xD4) = 0;
    *(int *)(p + 0xD8) = 0;
    *(int *)(p + 0xDC) = 0;
    *(int *)(p + 0xE0) = 0;
    *(int *)(p + 0xE4) = 0;
    *(int *)(p + 0xE8) = 0;
    *(int *)(p + 0xF8) = 0;
    *(int *)(p + 0xC) = 0;
    *(int *)(p + 0x14) = 0;
    *(int *)(p + 0x2C) = 0;
    *(int *)(p + 0x34) = 0;
    *(int *)(p + 0x3C) = 0;
    *(long long *)(p + 0xF0) = -1;
    *(int *)(p + 0x1C) = (int)_defStopDMA;
    *(int *)(p + 0x24) = (int)_defRestartDMA;
    *(int *)(p + 0x44) = _alalcAlloc((unsigned int *)(p + 0x108), 0x600, 8);
    *(int *)(p + 0x48) = 0;
    *(int *)(p + 0xFC) = 0;
    *(int *)(p + 0x100) = 0;
    *(int *)(p + 0x104) = 0;
    *(int *)(p + 0x70) = 0;
    *(long long *)(p + 0x78) = 0;
    *(long long *)(p + 0x88) = 0;
    *(int *)(p + 0x90) = 0;
    *(int *)(p + 0xAC) = 0;
    *(int *)(p + 0x80) = -1;
    *(int *)(p + 0xB0) = 1;
    _theSceMpeg = self;
    *(int *)(p + 0x94) = -1;
    *(int *)(p + 0x98) = -1;
    *(int *)(p + 0x9C) = -1;
    _clearOnce();
    sceMpegReset(self);
    sceMpegClearRefBuff(self);
    _forwFrame = _refFrame0;
    _backFrame = _refFrame1;
    _zFrame[0] = (int)_refFrame2;
    _forwTop = _refTop0;
    _backTop = _refTop1;
    _zTop[0] = (int)_refTop2;
    _forwBot = _refBot0;
    _backBot = _refBot1;
    _zBot[0] = (int)_refBot2;
    _alalcSetDynamic((int *)(p + 0x108));
}

int sceMpegDelete(void)
{
    return 1;
}

extern int _bsDataSize[];
extern void _sendDataToIPU(int a0, int a1);

void sceMpegAddBs(int a0, int a1, int a2)
{
    int rounded = (a2 + 0x13) / 16 * 16;
    _bsDatap = a1;
    _bsDataSize[0] = rounded;
    _sendDataToIPU(a1, rounded);
}

extern int _getpic(int self);

int sceMpegGetPicture(int *a0, unsigned int a1, int a2)
{
    int *p = (int *)a0[0x40 / 4];
    a1 = (a1 & 0x0FFFFFFF) | 0x20000000;
    p[0xB0 / 4] = 1;
    p[0xD8 / 4] = a1;
    p[0xE4 / 4] = a2;
    p[0xE0 / 4] = 0;
    p[0xDC / 4] = 0;
    return _getpic((int)a0);
}

int sceMpegGetPictureRAW8(int *self, unsigned int a1, int a2, int a3)
{
    int *p = (int *)self[0x40 / 4];
    p[0xE4 / 4] = a2;
    p[0xD8 / 4] = (a1 & 0x0FFFFFFF) | 0x20000000;
    p[0xB0 / 4] = 0;
    p[0xE0 / 4] = 0;
    p[0xDC / 4] = 0;
    return _getpic((int)self);
}

int sceMpegGetPictureRAW8xy(int *self, unsigned int a1, int a2, int a3)
{
    int *p = (int *)self[0x40 / 4];
    int prod;
    p[0xE0 / 4] = a3 << 4;
    p[0xD8 / 4] = (a1 & 0x0FFFFFFF) | 0x20000000;
    prod = a2 * a3;
    p[0xE4 / 4] = prod;
    p[0xDC / 4] = a2 << 4;
    p[0xB0 / 4] = 0;
    return _getpic((int)self);
}

void sceMpegSetDecodeMode(void *a0, int a1, int a2, int a3)
{
    int *p = *(int **)((char *)a0 + 0x40);
    p[0x25] = a1;
    p[0x26] = a2;
    p[0x27] = a3;
}

void sceMpegGetDecodeMode(void *a0, int *a1, int *a2, int *a3)
{
    int *p = *(int **)((char *)a0 + 0x40);
    *a1 = *(int *)((char *)p + 0x94);
    *a2 = *(int *)((char *)p + 0x98);
    *a3 = *(int *)((char *)p + 0x9C);
}

int sceMpegIsEnd(int **a0)
{
    return a0[0x10][0];
}

int sceMpegIsRefBuffEmpty(void *a0)
{
    void *p = *(void **)((char *)a0 + 0x40);
    return *(int *)((char *)p + 0x4) == 0;
}

extern int _totalFrames[];
extern void _clearEach(void);
extern void _initSeqAgain(void);

void sceMpegReset(int *a0)
{
    int *p = (int *)a0[0x10];
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    a0[2] = 0;
    p[0x20] = -1;
    p[0x2B] = 0;
    _clearEach();
    _totalFrames[0] = 0;
    _initSeqAgain();
}

extern int *_forwFrame;
extern int *_backFrame;
extern int *_forwTop;
extern int *_backTop;
extern int *_forwBot;
extern int *_backBot;

int sceMpegClearRefBuff(void)
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

int sceMpegAddCallback(void *a0, int a1, int a2, int a3)
{
    char *p = *(char **)((char *)a0 + 0x40);
    char *q0 = p + 0xC;
    int *q = (int *)(q0 + a1 * 8);
    int old;
    p += a1 * 8;
    ((int *)p)[4] = a3;
    old = *q;
    *q = a2;
    return old;
}

void *_dispatchMpegCallback(void *a0, void *a1)
{
    void *rv = 0;
    if (a0 != 0) {
        char *p = *(char **)((char *)a0 + 0x40);
        if (p != 0) {
            char *q0 = p + 0xC;
            int off = *(int *)a1 * 8;
            void *(*fn)(void *, void *, int) = *(void *(**)(void *, void *, int))(q0 + off);
            if (fn != 0) {
                char *e2 = p + off;
                rv = fn(a0, a1, *(int *)(e2 + 0x10));
            }
        }
    }
    return rv;
}

void _dispatchMpegCbNodata(void *a0)
{
    int buf[8];
    buf[0] = 1;
    _dispatchMpegCallback(a0, buf);
}

void sceMpegSetDefaultPtsGap(void *a0, long long a1)
{
    int *p = *(int **)((char *)a0 + 0x40);
    p[0x1C] = 1;
    *(long long *)((char *)p + 0x78) = a1;
}

void sceMpegResetDefaultPtsGap(void *a0)
{
    void *p = *(void **)((char *)a0 + 0x40);
    *(int *)((char *)p + 0x70) = 0;
    *(long long *)((char *)p + 0x78) = 0;
}

void sceMpegSetImageBuff(int a0)
{
    int *q = *(int **)((char *)_theSceMpeg + 0x40);
    q[0x36] = a0;
}

int sceMpegDispWidth(int **a0)
{
    return a0[0x10][0x33];
}

int sceMpegDispHeight(int **a0)
{
    return a0[0x10][0x34];
}

void *sceMpegDispCenterOffX(int **a0)
{
    return (char *)a0[0x10] + 0xB4;
}

void *sceMpegDispCenterOffY(int **a0)
{
    return (char *)a0[0x10] + 0xB4;
}

int sceSetBrokenLink(void *a0, int a1)
{
    void *p = *(void **)((char *)a0 + 0x40);
    int old = *(int *)((char *)p + 0xE8);
    *(int *)((char *)p + 0xE8) = a1;
    return old;
}

void sceSetPtm(void *a0, long long a1)
{
    int *p = *(int **)((char *)a0 + 0x40);
    *(long long *)((char *)p + 0xF0) = a1;
    p[0x3E] = 1;
}

void _alalcInit(int *a0, int a1, int a2)
{
    a0[0] = a1;
    a0[1] = a2;
    a0[2] = a1;
    a0[3] = a1;
}

void _alalcSetDynamic(int *a0)
{
    a0[3] = a0[2];
}

void _alalcFree(int *a0)
{
    a0[2] = a0[3];
}

extern void _Error(void *a0);

int _alalcAlloc(unsigned int *a0, int a1, unsigned int a2)
{
    unsigned int rounded;
    unsigned int total;
    rounded = ((a0[2] + a2 - 1) / a2) * a2;
    total = rounded + a1;
    if (a0[0] + a0[1] >= total) {
        a0[2] = total;
        return rounded;
    }
    _Error("work area size is too small");
    return 0;
}

int _alalcRest(int *a0)
{
    return a0[0] + a0[1] - a0[2];
}

extern int _isOutputPicture[];
extern int _picture_structure;
extern int _isMpeg2[];
extern void _Error1(int a0, int a1);
extern int _decodeOrSkip(int a0, int a1, int a2);
extern int _nextHeader(void);
extern int _sceMpegFlush(int *self);

int _getpic(int a0)
{
    int code = 1;
    int ret = 0;
    int *self = (int *)a0;
    int *p = (int *)self[0x40 / 4];
    int v = p[0xD8 / 4];

    p[0] = 0;
    if ((v & 0x3F) != 0) {
        _Error1((int)"image buffer needs to be aligned to 64byte boundary(0x%08x)", v);
        return -1;
    }
    _isOutputPicture[0] = 0;
    do {
        if (ret != -1) {
            do {
                code = _nextHeader();
            } while (code != 0 && _picture_structure != p[0xD4 / 4] && _isMpeg2[0] != 0);
        }
        switch (code) {
        case 0:
            _sceMpegFlush(self);
            p[0] = 1;
            break;
        case 1:
            p[0xA8 / 4] = 0;
            p[0xA4 / 4] = 0;
            p[0xA0 / 4] = 0;
            ret = _decodeOrSkip(a0, 0, p[0x94 / 4]);
            p[0xA0 / 4] = p[0xA0 / 4] + 1;
            break;
        case 2:
            ret = _decodeOrSkip(a0, p[0xA4 / 4], p[0x98 / 4]);
            p[0xA4 / 4] = p[0xA4 / 4] + 1;
            break;
        case 3:
        case 4:
            ret = _decodeOrSkip(a0, p[0xA8 / 4], p[0x9C / 4]);
            p[0xA8 / 4] = p[0xA8 / 4] + 1;
            break;
        }
    } while (_isOutputPicture[0] == 0);
    return 1;
}

extern int _isSecondField[];
extern int _updateRefImage(int a0);
extern int _decPicture(int a0, int a1);
extern void _outputFrame(int a0, int a1);

int _decodeOrSkipFrame(int a0, int a1, int a2)
{
    int skip = 0;
    int ret;
    int t;
    int second;
    int *self = (int *)a0;
    int *p = (int *)self[0x40 / 4];

    if (a2 == -1 || a1 < a2) {
        int ok;
        int decoded;

        if (p[2] == 0) {
            self[2] = 0;
            p[2] = 1;
        }
        ok = _updateRefImage(0);
        decoded = 0;
        if (ok != 0) {
            decoded = _decPicture(_totalFrames[0], p[1]) != 0;
        }
        ret = decoded;
    } else {
        ret = _updateRefImage(0);
        _dispatchMpegCbNodata(self);
        skip = 1;
    }
    _outputFrame(_totalFrames[0], p[1]);
    if (_picture_structure != 3 && skip == 0) {
        _isSecondField[0] = _isSecondField[0] == 0;
    }
    t = _totalFrames[0];
    second = _isSecondField[0];
    self[2] = t - p[0xAC / 4];
    if (second == 0) {
        int f = p[1];

        _totalFrames[0] = t + 1;
        p[1] = f + 1;
    }
    return ret;
}

extern int _picture_structure;
extern int _decodeOrSkipField(int a0, int a1, int a2);
extern int _decodeOrSkipFrame(int a0, int a1, int a2);

int _decodeOrSkip(int a0, int a1, int a2)
{
    if (_picture_structure != 3) {
        return _decodeOrSkipField(a0, a1, a2);
    }
    return _decodeOrSkipFrame(a0, a1, a2);
}

extern int _isSecondField[];
extern int _updateRefImage(int a0);
extern int _decPicture(int a0, int a1);
extern int _nextHeader(void);
extern int _sceMpegFlush(int *self);
extern void _outputFrame(int a0, int a1);

int _decodeOrSkipField(int a0, int a1, int a2)
{
    int dec = 0;
    int ret;
    int t;
    int want;
    int ok;
    int base;
    int *self = (int *)a0;
    int *p = (int *)self[0x40 / 4];

    _isSecondField[0] = 0;
    if (a2 == -1 || a1 < a2) {
        dec = 1;
    }
    if (p[2] == 0) {
        self[2] = 0;
        p[2] = 1;
    }
    if (_updateRefImage(0) != 0 && dec != 0) {
        _decPicture(_totalFrames[0], p[1]);
    }
    _isSecondField[0] = 1;
    if (_nextHeader() == 0) {
        _sceMpegFlush(self);
        p[0] = 1;
        return 0;
    }
    want = 2;
    if (p[0xD4 / 4] != 1) {
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
        if (_decPicture(_totalFrames[0], p[1]) != 0) {
            ret = 1;
        }
    }
    _outputFrame(_totalFrames[0], p[1]);
    t = _totalFrames[0];
    base = p[0xAC / 4];
    _isSecondField[0] = 0;
    self[2] = t - base;
    _totalFrames[0] = t + 1;
    p[1] = p[1] + 1;
    if (dec == 0) {
        _dispatchMpegCbNodata(self);
    }
    return ret;
}

extern void _lastFrame(int a0);

int _sceMpegFlush(int *self)
{
    int *p = (int *)self[0x40 / 4];
    int ret = 0;
    if (p[1] != 0 && p[2] != 0) {
        _lastFrame(_totalFrames[0]);
        self[2] = _totalFrames[0] - p[0xAC / 4];
        p[1] = 0;
        ret = 1;
    }
    return ret;
}
