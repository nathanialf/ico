/* Vendor SCE library member: libmpeg.a(init.o).  MAIN.MAP's member size (0xBCC)
 * tiles the retail run, VMA 0x26BFD8..0x26CBA4, 19 functions, then 4 bytes of
 * link fill to defhandler.o's 8-aligned start: the decoder state resets, the
 * error reporting, the bitstream DMA and the sequence-level header parsers. */
#include <libmpeg.h>

extern void DIntr();
extern int EIntr(void);
extern int _isMpeg2[];
extern void _ipuSetMPEG1(int a0);

void _initSeqAgain(void)
{
    _isMpeg2[0] = 0;
    _ipuSetMPEG1(1);
}

extern int _isSecondField[];
extern void _dispRefImage();
extern void _dispRefImageField();

void _lastFrame(int a0)
{
    int t;
    if (_isSecondField[0]) {
        _Error("the second field is missing");
        _isSecondField[0] = 0;
        return;
    }
    t = _picture_structure;
    if (t == 3) {
        _dispRefImage(_backFrame, a0 - 1);
    } else {
        _dispRefImageField(_backTop, _backBot, a0 - 1);
    }
    _isSecondField[0] = 0;
}

/* the member's .bss: the scratchpad tag buffer _sprtag points at and the
   DMA tags _sendDataToIPU builds the bitstream chain in */
static long long sprTagBuf[64]; /* derived name */

static long long ipuTags[258]; /* derived name */

/* the member's .data: the scratchpad base the macroblock state lives at, then
   the four globals MAIN.MAP lists */
static int sprBase = 0x70000000; /* derived name */

int _sprtag = (int)sprTagBuf;

int _refBlockp = 0x70003600;

MpegHandle *_theSceMpeg = 0;

int _bsDatap = 0;

extern int _mbcont[];

void _clearOnce(void)
{
    int v;
    _ipuSetMPEG1(1);
    v = sprBase;
    _mbcont[0] = v;
    _mbcont[1] = v + 0x1800;
    *(void **)&_mbcont[0x50] = (void *)(v + 0x1B00);
    *(void **)&_mbcont[0x51] = (void *)(v + 0x3300);
    *(float *)((char *)_mbcont + 0x280) = 0.0f;
}

extern int _sp_dcr[];
extern int _isTop32dirty[];
extern int sceIpuSync();

/* Same hardware-register rule as sceMpegInit: volatile everywhere, and the
   second write of the enable register at 0x1000F590 plain so it can be
   scheduled into the delay slot of jal EIntr. */
void _clearEach(void)
{
    _sp_dcr[0] = 0;
    _isTop32dirty[0] = 1;
    DIntr();
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 | 0x10000;
    *(volatile int *)0x1000B000 = 0;
    *(volatile int *)0x1000B400 = 0;
    *(volatile int *)0x1000D400 = 0;
    *(int *)0x1000F590 = *(volatile int *)0x1000F520 & 0xFFFEFFFF;
    EIntr();
    *(volatile int *)0x1000B020 = 0;
    *(volatile int *)0x1000B420 = 0;
    *(volatile int *)0x1000D420 = 0;
    *(volatile int *)0x10002010 = 0x40000000;
    sceIpuSync(0, 0);
}

extern void printf(void *a0, ...);

void _ErrMessage(int a0)
{
    printf("[MPEG ERROR]%s\n", a0);
}

extern void sprintf(void *a0, int a1, ...);

void _Error1(int a0, int a1)
{
    char buf[0x100];
    sprintf(buf, a0, a1);
    _Error(buf);
}

extern void _ErrMessage(int a0);

void _Error(void *a0)
{
    char *p = (char *)_theSceMpeg;
    if (p != 0) {
        register int q = *(int *)(p + 0x40);
        if (q != 0) {
            register int r = *(int *)(q + 0xC);
            if (r != 0) {
                int local[2];
                local[0] = 0;
                local[1] = (int)a0;
                _dispatchMpegCallback((int)p, local);
                return;
            }
        }
    }
    _ErrMessage(a0);
}

void _sendDataToIPU(int a0, int a1)
{
    long long *tag = (long long *)((((unsigned int)ipuTags) & 0x0FFFFFFF) | 0x20000000);
    int p = a0;
    int n = a1;

    while (n > 0) {
        int len = n > 0xFFF40 ? 0xFFF40 : n;
        int addr = p & 0x0FFFFFFF;
        int id;
        int qwc;

        n -= len;
        id = n != 0 ? 3 : 0;
        qwc = (len + 15) / 16;
        *tag = ((long long)addr << 32) | ((long long)id << 28) | (unsigned int)qwc;
        p += len;
        tag += 2;
    }
    *(volatile int *)0x1000B430 = (int)ipuTags & 0x0FFFFFFF;
    *(volatile int *)0x1000B420 = 0;
    *(volatile int *)0x1000B400 = 0x105;
}

int _RefImageInit(int *a0, int a1, int a2)
{
    a0[0x4 / 4] = a1;
    a0[0x8 / 4] = a2;
    a0[0xC / 4] = a1 >> 4;
    a0[0x10 / 4] = a2 >> 4;
    return 1;
}

extern unsigned int _nextBit(int n);
extern int _frame_rate_code;
extern int _aspect_ratio_information;
extern int _horizontal_size;
extern int _vertical_size;
extern int _constrained_parameters_flag;
extern int _vbv_buffer_size_value;
extern int _bit_rate_value;
extern int _load_intra_quantizer_matrix;
extern int _load_non_intra_quantizer_matrix;
extern int _defIQM[];
extern int _defNIQM[];
extern void _setDefaultQM(int a0, int *a1);
extern void _sendIpuCommand(unsigned int a0);
extern void _waitIpuIdle(void);
extern void _extensionAndUserData(void);
extern void _initSeq(void *a0);

void _sequenceHeader(void)
{
    unsigned int v;

    *(int *)(*(int *)((char *)_theSceMpeg + 0x40) + 0xD4) = 0;
    v = _nextBit(32);
    _frame_rate_code = v & 0xF;
    _aspect_ratio_information = (v >> 4) & 0xF;
    _vertical_size = (v >> 8) & 0xFFF;
    _horizontal_size = v >> 20;
    if (_vertical_size >= 0xAF1) {
        _Error("vertical size > 2800");
    }
    v = _nextBit(30);
    _constrained_parameters_flag = v & 1;
    _vbv_buffer_size_value = (v >> 1) & 0x3FF;
    _bit_rate_value = v >> 12;
    if ((_load_intra_quantizer_matrix = _nextBit(1)) != 0) {
        _waitIpuIdle();
        _sendIpuCommand(0x50000000);
        _waitIpuIdle();
    } else {
        _setDefaultQM(0x50000000, _defIQM);
    }
    if ((_load_non_intra_quantizer_matrix = _nextBit(1)) != 0) {
        _waitIpuIdle();
        _sendIpuCommand(0x58000000);
        _waitIpuIdle();
    } else {
        _setDefaultQM(0x58000000, _defNIQM);
    }
    _extensionAndUserData();
    _initSeq(_theSceMpeg);
}

extern int _isMpeg2[];
extern int _picture_structure;
extern int _frame_pred_frame_dct;
extern int _matrix_coefficients;
extern int _progressive_sequence;
extern int _chroma_format;
extern int _progressive_frame;
extern int _widthMB[];
extern int _heightMB[];
extern int _picWidth;
extern int _picHeight;
extern int _cWidth;
extern int _cHeight;
extern void _initRefImages(int *frame0, int *frame1, int *frame2, int *top0, int *top1, int *top2,
                           int *bot0, int *bot1, int *bot2, int y, int cb, int cr);

/* the stream record _initSeq re-sizes: the picture size the decoder was last
 * set up for, and at 0x40 the decoder the three frame buffers are allocated
 * out of */
typedef struct {
    int width;
    int height;
    int _8[14];
    int *dec;
} MpegSeq;

void _initSeq(void *a0)
{
    MpegSeq *p = (MpegSeq *)a0;
    int *r = p->dec;
    int *heap;
    unsigned int size;

    if (_isMpeg2[0] == 0) {
        _progressive_sequence = 1;
        _chroma_format = 1;
        _progressive_frame = 1;
        _picture_structure = 3;
        _frame_pred_frame_dct = 1;
        _matrix_coefficients = 5;
    }
    _widthMB[0] = (_horizontal_size + 15) >> 4;
    _heightMB[0] = (_isMpeg2[0] != 0 && _progressive_sequence == 0)
                       ? ((_vertical_size + 31) >> 5) * 2
                       : (_vertical_size + 15) >> 4;
    _picWidth = _widthMB[0] * 16;
    _picHeight = _heightMB[0] * 16;
    if (_picWidth != p->width || _picHeight != p->height) {
        p->width = _picWidth;
        p->height = _picHeight;
        _cWidth = _picWidth >> 1;
        _cHeight = _picHeight >> 1;
        heap = (int *)((char *)r + 0x108);
        size = (unsigned int)(_picWidth * 0x180 * _picHeight) >> 8;
        _alalcFree(heap);
        r[0xFC / 4] = _alalcAlloc((unsigned int *)heap, size, 0x40);
        r[0x100 / 4] = _alalcAlloc((unsigned int *)heap, size, 0x40);
        r[0x104 / 4] = _alalcAlloc((unsigned int *)heap, size, 0x40);
        _initRefImages(_refFrame0, _refFrame1, _refFrame2, _refTop0, _refTop1, _refTop2, _refBot0,
                       _refBot1, _refBot2, r[0xFC / 4], r[0x100 / 4], r[0x104 / 4]);
        _RefImageInit(_refFrame0, _picWidth, _picHeight);
        _RefImageInit(_refFrame1, _picWidth, _picHeight);
        _RefImageInit(_refFrame2, _picWidth, _picHeight);
        _RefImageInit(_refTop0, _picWidth, _picHeight / 2);
        _RefImageInit(_refTop1, _picWidth, _picHeight / 2);
        _RefImageInit(_refTop2, _picWidth, _picHeight / 2);
        _RefImageInit(_refBot0, _picWidth, _picHeight / 2);
        _RefImageInit(_refBot1, _picWidth, _picHeight / 2);
        _RefImageInit(_refBot2, _picWidth, _picHeight / 2);
    }
}

/* The uncached-accelerated alias of a frame buffer address. RECONSTRUCTION:
 * the ROM computes `size / 512 * 384` three times (three `mult` into fresh
 * scratch registers), which is an inline call per store: gcc expands each
 * inline argument with EXPAND_SUM and computes its product into the argument
 * copy, so cse can not share it; the helper's name stands in for Sony's. */
static inline int _uncachedAddr(int addr)
{
    return (addr & 0x0FFFFFFF) | 0x20000000;
}

void _initRefImages(int *frame0, int *frame1, int *frame2, int *top0, int *top1, int *top2,
                    int *bot0, int *bot1, int *bot2, int y, int cb, int cr)
{
    int size = _picWidth * _picHeight;

    *frame0 = _uncachedAddr(y);
    *frame1 = _uncachedAddr(cb);
    *frame2 = _uncachedAddr(cr);
    *top0 = _uncachedAddr(y);
    *top1 = _uncachedAddr(cb);
    *top2 = _uncachedAddr(cr);
    *bot0 = _uncachedAddr(y + size / 512 * 384);
    *bot1 = _uncachedAddr(cb + size / 512 * 384);
    *bot2 = _uncachedAddr(cr + size / 512 * 384);
}

void _setDefaultQM(int a0, int *a1)
{
    int buf[8];

    buf[0] = 2;
    _dispatchMpegCallback(_theSceMpeg, buf);
    _waitIpuIdle();
    *(volatile int *)0x10002000 = 0;
    _waitIpuIdle();
    /* channel 4 (to IPU) sends the four quadwords of the matrix */
    *(volatile int *)0x1000B410 = (int)a1 & 0x0FFFFFFF;
    *(volatile int *)0x1000B420 = 4;
    *(volatile int *)0x1000B400 = 0x101;
    _sendIpuCommand(a0);
    _waitIpuIdle();
    buf[0] = 3;
    _dispatchMpegCallback(_theSceMpeg, buf);
}

extern int _chroma_format;
extern int _progressive_sequence;
extern int _profile_and_level_indication;
extern int _low_delay;
extern int _frame_rate_extension_n;
extern int _frame_rate_extension_d;
extern void _ipuSetMPEG1(int a0);

void _sequenceExtension(void)
{
    unsigned int v;
    int horiz_ext;
    int vert_ext;
    int bit_rate_ext;
    int vbv_ext;

    _isMpeg2[0] = 1;
    _ipuSetMPEG1(0);
    v = _nextBit(28);
    bit_rate_ext = (v >> 1) & 0xFFF;
    _chroma_format = (v >> 17) & 3;
    vert_ext = (v >> 13) & 3;
    horiz_ext = (v >> 15) & 3;
    if (_chroma_format != 1) {
        _Error("_chroma_format needs to be 1: 420");
    }
    _progressive_sequence = (v >> 19) & 1;
    _profile_and_level_indication = v >> 20;
    v = _nextBit(16);
    _frame_rate_extension_d = v & 0x1F;
    _frame_rate_extension_n = (v >> 5) & 3;
    _low_delay = (v >> 7) & 1;
    vbv_ext = v >> 8;
    if (_profile_and_level_indication != 0x48 && _profile_and_level_indication != 0x58) {
        _Error("Unsupported profile/level");
    }
    _horizontal_size = (horiz_ext << 12) | (_horizontal_size & 0xFFF);
    _vertical_size = (vert_ext << 12) | (_vertical_size & 0xFFF);
    _bit_rate_value = _bit_rate_value + (bit_rate_ext << 18);
    _vbv_buffer_size_value = _vbv_buffer_size_value + (vbv_ext << 10);
}

extern unsigned int _nextBit(int n);
/* the sequence_display_extension fields, all of them in the vendor's own
 * variable object */
extern int _video_format;
extern int _color_description;
extern int _color_primaries;
extern int _transfer_characteristics;
extern int _matrix_coefficients;
extern int _display_horizontal_size;
extern int _display_vertical_size;

void _sequenceDisplayExtension(void)
{
    _video_format = _nextBit(3);
    if ((_color_description = _nextBit(1)) != 0) {
        _color_primaries = _nextBit(8);
        _transfer_characteristics = _nextBit(8);
        _matrix_coefficients = _nextBit(8);
    }
    _display_horizontal_size = _nextBit(14);
    _nextBit(1);
    _display_vertical_size = _nextBit(14);
}

void _sequenceScalableExtension(void)
{
    _Error("_sequenceScalableExtension() is not implemented");
}

void _unknown_extension(void)
{
    _Error("Unknown Extension");
}

void _pictureSpatialScalableExtension(void)
{
    _Error("_pictureSpatialScalableExtension is not supported");
}

void _pictureTemporalScalableExtension(void)
{
    _Error("_pictureTemporalScalableExtension is not supported");
}
