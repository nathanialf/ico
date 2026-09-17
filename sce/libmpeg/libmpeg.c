/* Vendor SCE library run.  The archive attribution (libmpeg.a) comes from
 * MAIN.MAP's symbol table.  The January link carried a different revision of
 * this archive, so its member spans do not tile this run: the per-member
 * partition is NOT verified, and this file is the whole run. */
#include "common.h"
#include <libmpeg.h>
#include <libipu.h>

typedef struct {
    int unk0, unk4, unk8, unkC;
} P24D418;

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _type2id);
INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _id2type);
INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", sceMpegDemuxPssRing);

void sceMpegDemuxPss(void *a0, int a1, int a2)
{
    do {
        sceMpegDemuxPssRing(a0, a1, a2, 0, -1);
    } while (0);
}

/* the ten PSS stream descriptors: the id template of the stream and the mask
 * of the bits its stream number occupies */
typedef struct {
    long long id;
    unsigned long long mask;
} StrDesc;

extern StrDesc D_0054C018[];

/* one demux callback: the stream id it matches, the mask of the id bits that
 * take part in the match, and the handler with its user argument */
typedef struct {
    long long id;
    unsigned long long mask;
    int func;
    int arg;
} StrCb;

extern long long _type2id(int a0, long long a1);

int sceMpegAddStrCallback(int *a0, int a1, long long a2, int a3, int a4)
{
    int ret = 0;
    int *p = (int *)a0[0x40 / 4];
    StrCb *tbl = (StrCb *)p[0x44 / 4];
    long long id = _type2id(a1, a2);
    int n = p[0x48 / 4];
    int i;

    for (i = 0; i < n; i++) {
        if (id == tbl[i].id) {
            ret = tbl[i].func;
            break;
        }
    }
    if (i < 0x40) {
        p[0x48 / 4] = n + 1;
        tbl[i].id = id;
        tbl[i].arg = a4;
        tbl[i].func = a3;
        tbl[i].mask = D_0054C018[a1].mask;
    }
    return ret;
}

extern int _sysbitGet(int *bs, int nbits);
extern int _sysbitMarker(int *bs);
extern int _sysbitNext(void *a0, int a1);
extern int _system_header();

int _pack_header(int *bs, P24D418 *pkt)
{
    unsigned int i = 0;
    unsigned int a, b, c, n;
    int last;

    _sysbitGet(bs, 0x22);
    a = _sysbitGet(bs, 0x3);
    _sysbitMarker(bs);
    b = _sysbitGet(bs, 0xF);
    _sysbitMarker(bs);
    c = _sysbitGet(bs, 0xF);
    _sysbitMarker(bs);
    pkt->unk0 = _sysbitGet(bs, 0x9);
    _sysbitGet(bs, 0x1E);
    n = _sysbitGet(bs, 0x3);
    pkt->unk8 = (a >> 2) & 1;
    pkt->unk4 = (a << 30) | (b << 15) | c;
    for (i = 0; i < n; i++) {
        _sysbitGet(bs, 0x8);
    }
    last = _sysbitNext(bs, 0x20);
    if (last != 0x1BB)
        goto unset;
    pkt->unkC = 1;
    _system_header(bs, pkt);
    goto end;
unset:
    pkt->unkC = 0;
end:
    return 1;
}

int _system_header(int *a0)
{
    _sysbitGet(a0, 0x38);
    _sysbitGet(a0, 0x28);
    while (_sysbitNext(a0, 1) == 1) {
        _sysbitGet(a0, 0x18);
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _PES_packet);
INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", sceMpegInit);
INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", sceMpegCreate);

int sceMpegDelete(void)
{
    return 1;
}

extern int D_0054C0E8[];
extern int _bsDataSize[];
extern void _sendDataToIPU(int a0, int a1);

void sceMpegAddBs(int a0, int a1, int a2)
{
    int rounded = (a2 + 0x13) / 16 * 16;
    D_0054C0E8[0] = a1;
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

extern int _forwFrame[];
extern int _backFrame[];
extern int _forwTop[];
extern int _backTop[];
extern int _forwBot[];
extern int _backBot[];

int sceMpegClearRefBuff(void)
{
    if (_forwFrame[0] != 0)
        *(int *)(_forwFrame[0] + 0x28) = 0;
    if (_forwTop[0] != 0)
        *(int *)(_forwTop[0] + 0x28) = 0;
    if (_forwBot[0] != 0)
        *(int *)(_forwBot[0] + 0x28) = 0;
    if (_backFrame[0] != 0)
        *(int *)(_backFrame[0] + 0x28) = 0;
    if (_backTop[0] != 0)
        *(int *)(_backTop[0] + 0x28) = 0;
    if (_backBot[0] != 0)
        *(int *)(_backBot[0] + 0x28) = 0;
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

extern void *D_0054C0E4[];

void sceMpegSetImageBuff(int a0)
{
    int *q = *(int **)((char *)D_0054C0E4[0] + 0x40);
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

extern int D_00636D58[];
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
    _Error(D_00636D58);
    return 0;
}

int _alalcRest(int *a0)
{
    return a0[0] + a0[1] - a0[2];
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _getpic);
INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _decodeOrSkipFrame);

extern int _picture_structure[];
extern int _decodeOrSkipField(int a0, int a1, int a2);
extern int _decodeOrSkipFrame(int a0, int a1, int a2);

int _decodeOrSkip(int a0, int a1, int a2)
{
    if (_picture_structure[0] != 3) {
        return _decodeOrSkipField(a0, a1, a2);
    }
    return _decodeOrSkipFrame(a0, a1, a2);
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _decodeOrSkipField);

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

extern int _isMpeg2[];
extern void _ipuSetMPEG1(int a0);

void _initSeqAgain(void)
{
    _isMpeg2[0] = 0;
    _ipuSetMPEG1(1);
}

extern int _isSecondField[];
extern char D_00636DD8[];
extern void _dispRefImage();
extern void _dispRefImageField();

void _lastFrame(int a0)
{
    int t;
    int d;
    int c;
    if (_isSecondField[0]) {
        _Error(D_00636DD8);
        _isSecondField[0] = 0;
        return;
    }
    t = _picture_structure[0];
    if (t == 3) {
        _dispRefImage(_backFrame[0], a0 - 1);
    } else {
        _dispRefImageField(_backTop[0], _backBot[0], a0 - 1);
    }
    _isSecondField[0] = 0;
}

extern int D_0054C0D8[];
extern int _mbcont[];

void _clearOnce(void)
{
    int v;
    _ipuSetMPEG1(1);
    v = D_0054C0D8[0];
    _mbcont[0] = v;
    _mbcont[1] = v + 0x1800;
    *(void **)&_mbcont[0x50] = (void *)(v + 0x1B00);
    *(void **)&_mbcont[0x51] = (void *)(v + 0x3300);
    *(float *)((char *)_mbcont + 0x280) = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _clearEach);

extern int D_00636DF8[];
extern void printf(void *a0, ...);

void _ErrMessage(int a0)
{
    printf(D_00636DF8, a0);
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
    char *p = D_0054C0E4[0];
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

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _sendDataToIPU);

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
extern int D_00636E08[];
extern void _setDefaultQM(int a0, int *a1);
extern void _sendIpuCommand(unsigned int a0);
extern void _waitIpuIdle(void);
extern void _extensionAndUserData(void);
extern void _initSeq(void *a0);

void _sequenceHeader(void)
{
    unsigned int v;

    *(int *)(*(int *)((char *)D_0054C0E4[0] + 0x40) + 0xD4) = 0;
    v = _nextBit(32);
    _frame_rate_code = v & 0xF;
    _aspect_ratio_information = (v >> 4) & 0xF;
    _vertical_size = (v >> 8) & 0xFFF;
    _horizontal_size = v >> 20;
    if (_vertical_size >= 0xAF1) {
        _Error(D_00636E08);
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
    _initSeq(D_0054C0E4[0]);
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _initSeq);
INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _initRefImages);
INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _setDefaultQM);

extern int _chroma_format;
extern int _progressive_sequence;
extern int _profile_and_level_indication;
extern int _low_delay;
extern int _frame_rate_extension_n;
extern int _frame_rate_extension_d;
extern int D_00636E20[];
extern int D_00636E48[];
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
        _Error(D_00636E20);
    }
    _progressive_sequence = (v >> 19) & 1;
    _profile_and_level_indication = v >> 20;
    v = _nextBit(16);
    _frame_rate_extension_d = v & 0x1F;
    _frame_rate_extension_n = (v >> 5) & 3;
    _low_delay = (v >> 7) & 1;
    vbv_ext = v >> 8;
    if (_profile_and_level_indication != 0x48 && _profile_and_level_indication != 0x58) {
        _Error(D_00636E48);
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

extern int D_00636E68[];

void _sequenceScalableExtension(void)
{
    _Error(D_00636E68);
}

extern int D_00636E98[];

void _unknown_extension(void)
{
    _Error(D_00636E98);
}

extern int D_00636EB0[];

void _pictureSpatialScalableExtension(void)
{
    _Error(D_00636EB0);
}

extern int D_00636EE8[];

void _pictureTemporalScalableExtension(void)
{
    _Error(D_00636EE8);
}

void _defStopDMA(int **a0)
{
    sceIpuStopDMA((char *)a0[0x10] + 0x4C);
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _defRestartDMA);
INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _motionComp0);
INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _getAllRefs);
INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _getRef0);
INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _doMC);

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        "    .global _rix_000\n"
        "    .type _rix_000, @function\n"
        "    .align 3\n"
        "_rix_000:\n"
        "    lw    $5, 0x14($4)\n"
        "    lw    $6, 0x18($4)\n"
        "    lw    $7, 0x8($4)\n"
        "    lw    $14, 0x0($4)\n"
        "    lw    $13, 0x4($4)\n"
        "    lw    $12, 0x10($4)\n"
        "    sll   $11, $12, 1\n"
        "    addiu $15, $0, -0x1\n"
        "    mtsab $13, 0x0\n"
        "1:\n"
        "    lq    $8, 0x0($5)\n"
        "    addi  $7, $7, -0x1\n"
        "    lq    $9, 0x0($6)\n"
        "    addu  $5, $5, $12\n"
        "    qfsrv $10, $9, $8\n"
        "    pextlb $8, $0, $10\n"
        "    pextub $9, $0, $10\n"
        "    sq    $8, 0x0($14)\n"
        "    addu  $6, $6, $12\n"
        "    sq    $9, 0x10($14)\n"
        "    bgtz  $7, 1b\n"
        "    addu  $14, $14, $11\n"
        "    addiu $5, $5, 0x80\n"
        "    addiu $6, $6, 0x80\n"
        "    lw    $7, 0xC($4)\n"
        "    and   $10, $15, $7\n"
        "    bnez  $10, 1b\n"
        "    daddu $15, $0, $0\n"
        "    jr    $31\n"
        "    nop\n"
        "    .size _rix_000, . - _rix_000\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global _ri0_000\n"
        ".type _ri0_000, @function\n"
        "    .align 3\n"
        "_ri0_000:\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $14, 0x0($4)\n"
        "    lw $13, 0x4($4)\n"
        "    lw $12, 0x10($4)\n"
        "    sll $11, $12, 1\n"
        "    mtsab $13, 0x0\n"
        "    addiu $24, $0, -0x1\n"
        ".L_ri0_00000250350:\n"
        "    lw $7, 0x8($4)\n"
        "    addiu $15, $0, -0x1\n"
        ".L_ri0_00000250358:\n"
        "    ld $8, 0x0($5)\n"
        "    ld $9, 0x0($6)\n"
        "    pcpyld $8, $9, $8\n"
        "    qfsrv $9, $8, $8\n"
        "    pextlb $8, $0, $9\n"
        "    sq $8, 0x0($14)\n"
        "    addi $7, $7, -0x1\n"
        "    addu $5, $5, $12\n"
        "    addu $14, $14, $11\n"
        "    bgtz $7, .L_ri0_00000250358\n"
        "    addu $6, $6, $12\n"
        "    addiu $5, $5, 0x140\n"
        "    addiu $6, $6, 0x140\n"
        "    lw $7, 0xC($4)\n"
        "    and $10, $15, $7\n"
        "    bnez $10, .L_ri0_00000250358\n"
        "    daddu $15, $0, $0\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $14, 0x0($4)\n"
        "    addiu $5, $5, 0x40\n"
        "    addiu $6, $6, 0x40\n"
        "    addiu $14, $14, 0x80\n"
        "    bnez $24, .L_ri0_00000250350\n"
        "    daddu $24, $0, $0\n"
        "    jr $31\n"
        "    nop\n"
        ".size _ri0_000, . - _ri0_000\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global _rix_001\n"
        ".type _rix_001, @function\n"
        "    .align 3\n"
        "_rix_001:\n"
        "    pnor $25, $0, $0\n"
        "    psrlh $25, $25, 15\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $7, 0x8($4)\n"
        "    lw $14, 0x0($4)\n"
        "    lw $13, 0x4($4)\n"
        "    lw $24, 0x10($4)\n"
        "    lq $8, 0x0($5)\n"
        "    sll $12, $24, 1\n"
        "    lq $9, 0x0($6)\n"
        "    mtsab $13, 0x0\n"
        "    qfsrv $10, $9, $8\n"
        "    pextlb $8, $0, $10\n"
        "    addiu $11, $0, -0x1\n"
        "    beqz $7, .L_rix_0010025045C\n"
        "    pextub $9, $0, $10\n"
        ".L_rix_0010025040C:\n"
        "    addu $5, $5, $24\n"
        "    addu $6, $6, $24\n"
        "    lq $10, 0x0($5)\n"
        "    lq $15, 0x0($6)\n"
        "    qfsrv $2, $15, $10\n"
        "    pextlb $10, $0, $2\n"
        "    addi $7, $7, -0x1\n"
        "    pextub $15, $0, $2\n"
        "    paddh $2, $8, $10\n"
        "    paddh $3, $9, $15\n"
        "    por $8, $10, $0\n"
        "    por $9, $15, $0\n"
        "    paddh $2, $2, $25\n"
        "    paddh $3, $3, $25\n"
        "    psrlh $2, $2, 1\n"
        "    psrlh $3, $3, 1\n"
        "    sq $2, 0x0($14)\n"
        "    sq $3, 0x10($14)\n"
        "    bgtz $7, .L_rix_0010025040C\n"
        "    addu $14, $14, $12\n"
        ".L_rix_0010025045C:\n"
        "    addiu $5, $5, 0x80\n"
        "    addiu $6, $6, 0x80\n"
        "    lw $7, 0xC($4)\n"
        "    and $10, $11, $7\n"
        "    bnez $10, .L_rix_0010025040C\n"
        "    daddu $11, $0, $0\n"
        "    jr $31\n"
        "    nop\n"
        ".size _rix_001, . - _rix_001\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global _ri0_001\n"
        ".type _ri0_001, @function\n"
        "    .align 3\n"
        "_ri0_001:\n"
        "    pnor $25, $0, $0\n"
        "    psrlh $25, $25, 15\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $14, 0x0($4)\n"
        "    lw $13, 0x4($4)\n"
        "    lw $12, 0x10($4)\n"
        "    addiu $11, $0, 0x1\n"
        "    sll $24, $12, 1\n"
        "    mtsab $13, 0x0\n"
        ".L_ri0_001002504A8:\n"
        "    lw $7, 0x8($4)\n"
        "    ld $8, 0x0($5)\n"
        "    ld $9, 0x0($6)\n"
        "    pcpyld $8, $9, $8\n"
        "    qfsrv $8, $8, $8\n"
        "    ori $11, $11, 0x8000\n"
        "    beqz $7, .L_ri0_00100250504\n"
        "    pextlb $15, $0, $8\n"
        ".L_ri0_001002504C8:\n"
        "    addu $5, $5, $12\n"
        "    addu $6, $6, $12\n"
        "    ld $8, 0x0($5)\n"
        "    ld $9, 0x0($6)\n"
        "    pcpyld $8, $9, $8\n"
        "    qfsrv $8, $8, $8\n"
        "    pextlb $10, $0, $8\n"
        "    addi $7, $7, -0x1\n"
        "    paddh $9, $10, $15\n"
        "    por $15, $10, $0\n"
        "    paddh $10, $9, $25\n"
        "    psrlh $10, $10, 1\n"
        "    sq $10, 0x0($14)\n"
        "    bgtz $7, .L_ri0_001002504C8\n"
        "    addu $14, $14, $24\n"
        ".L_ri0_00100250504:\n"
        "    psrah $10, $11, 15\n"
        "    addiu $5, $5, 0x140\n"
        "    lw $7, 0xC($4)\n"
        "    addiu $6, $6, 0x140\n"
        "    and $10, $10, $7\n"
        "    bnez $10, .L_ri0_001002504C8\n"
        "    andi $11, $11, 0x7FFF\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $14, 0x0($4)\n"
        "    addiu $5, $5, 0x40\n"
        "    addiu $6, $6, 0x40\n"
        "    addiu $14, $14, 0x80\n"
        "    andi $10, $11, 0x1\n"
        "    bnez $10, .L_ri0_001002504A8\n"
        "    andi $11, $11, 0xFFFE\n"
        "    jr $31\n"
        "    nop\n"
        ".size _ri0_001, . - _ri0_001\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global _rix_010\n"
        ".type _rix_010, @function\n"
        "    .align 3\n"
        "_rix_010:\n"
        "    pnor $25, $0, $0\n"
        "    psrlh $25, $25, 15\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $7, 0x8($4)\n"
        "    lw $14, 0x0($4)\n"
        "    lw $13, 0x4($4)\n"
        "    addiu $24, $0, 0x1\n"
        "    lw $9, 0x10($4)\n"
        "    sll $8, $9, 1\n"
        "    addiu $11, $0, -0x1\n"
        ".L_rix_0100025057C:\n"
        "    lq $10, 0x0($5)\n"
        "    lq $15, 0x0($6)\n"
        "    mtsab $13, 0x0\n"
        "    qfsrv $2, $15, $10\n"
        "    qfsrv $3, $10, $15\n"
        "    pextlb $10, $0, $2\n"
        "    addi $7, $7, -0x1\n"
        "    pextub $15, $0, $2\n"
        "    mtsab $24, 0x0\n"
        "    qfsrv $3, $3, $2\n"
        "    pextlb $2, $0, $3\n"
        "    pextub $3, $0, $3\n"
        "    paddh $10, $10, $2\n"
        "    paddh $15, $15, $3\n"
        "    paddh $2, $10, $25\n"
        "    paddh $3, $15, $25\n"
        "    psrlh $2, $2, 1\n"
        "    psrlh $3, $3, 1\n"
        "    sq $2, 0x0($14)\n"
        "    sq $3, 0x10($14)\n"
        "    addu $5, $5, $9\n"
        "    addu $6, $6, $9\n"
        "    bgtz $7, .L_rix_0100025057C\n"
        "    addu $14, $14, $8\n"
        "    addiu $5, $5, 0x80\n"
        "    addiu $6, $6, 0x80\n"
        "    lw $7, 0xC($4)\n"
        "    and $12, $11, $7\n"
        "    bnez $12, .L_rix_0100025057C\n"
        "    daddu $11, $0, $0\n"
        "    jr $31\n"
        "    nop\n"
        ".size _rix_010, . - _rix_010\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global _ri0_010\n"
        ".type _ri0_010, @function\n"
        "    .align 3\n"
        "_ri0_010:\n"
        "    pnor $25, $0, $0\n"
        "    psrlh $25, $25, 15\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $14, 0x0($4)\n"
        "    lw $13, 0x4($4)\n"
        "    addiu $24, $0, 0x1\n"
        "    addiu $12, $0, -0x1\n"
        "    lw $3, 0x10($4)\n"
        "    sll $2, $3, 1\n"
        ".L_ri0_01000250628:\n"
        "    lw $7, 0x8($4)\n"
        "    addiu $11, $0, -0x1\n"
        ".L_ri0_01000250630:\n"
        "    ld $8, 0x0($5)\n"
        "    ld $9, 0x0($6)\n"
        "    pcpyld $8, $9, $8\n"
        "    mtsab $13, 0x0\n"
        "    qfsrv $8, $8, $8\n"
        "    pextlb $9, $0, $8\n"
        "    addi $7, $7, -0x1\n"
        "    addu $5, $5, $3\n"
        "    addu $6, $6, $3\n"
        "    mtsab $24, 0x0\n"
        "    qfsrv $10, $0, $8\n"
        "    pextlb $8, $0, $10\n"
        "    paddh $10, $9, $8\n"
        "    paddh $10, $10, $25\n"
        "    psrlh $10, $10, 1\n"
        "    sq $10, 0x0($14)\n"
        "    bgtz $7, .L_ri0_01000250630\n"
        "    addu $14, $14, $2\n"
        "    addiu $5, $5, 0x140\n"
        "    addiu $6, $6, 0x140\n"
        "    lw $7, 0xC($4)\n"
        "    and $10, $11, $7\n"
        "    bnez $10, .L_ri0_01000250630\n"
        "    daddu $11, $0, $0\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $14, 0x0($4)\n"
        "    addiu $5, $5, 0x40\n"
        "    addiu $6, $6, 0x40\n"
        "    addiu $14, $14, 0x80\n"
        "    bnez $12, .L_ri0_01000250628\n"
        "    daddu $12, $0, $0\n"
        "    jr $31\n"
        "    nop\n"
        ".size _ri0_010, . - _ri0_010\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global _rix_011\n"
        ".type _rix_011, @function\n"
        "    .align 3\n"
        "_rix_011:\n"
        "    pnor $25, $0, $0\n"
        "    psrlh $25, $25, 15\n"
        "    psllh $25, $25, 1\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $7, 0x8($4)\n"
        "    lw $14, 0x0($4)\n"
        "    lw $13, 0x4($4)\n"
        "    lw $12, 0x10($4)\n"
        "    addiu $24, $0, 0x1\n"
        "    lq $8, 0x0($5)\n"
        "    lq $9, 0x0($6)\n"
        "    mtsab $13, 0x0\n"
        "    qfsrv $10, $9, $8\n"
        "    qfsrv $15, $8, $9\n"
        "    pextlb $8, $0, $10\n"
        "    pextub $9, $0, $10\n"
        "    addiu $11, $0, -0x1\n"
        "    mtsab $24, 0x0\n"
        "    qfsrv $15, $15, $10\n"
        "    pextlb $10, $0, $15\n"
        "    pextub $15, $0, $15\n"
        "    paddh $8, $8, $10\n"
        "    beqz $7, .L_rix_01100250790\n"
        "    paddh $9, $9, $15\n"
        ".L_rix_0110025071C:\n"
        "    addu $5, $5, $12\n"
        "    addu $6, $6, $12\n"
        "    lq $10, 0x0($5)\n"
        "    lq $15, 0x0($6)\n"
        "    mtsab $13, 0x0\n"
        "    qfsrv $2, $15, $10\n"
        "    qfsrv $3, $10, $15\n"
        "    pextlb $10, $0, $2\n"
        "    addi $7, $7, -0x1\n"
        "    pextub $15, $0, $2\n"
        "    mtsab $24, 0x0\n"
        "    qfsrv $3, $3, $2\n"
        "    pextlb $2, $0, $3\n"
        "    pextub $3, $0, $3\n"
        "    paddh $10, $10, $2\n"
        "    paddh $15, $15, $3\n"
        "    paddh $2, $8, $10\n"
        "    paddh $3, $9, $15\n"
        "    por $8, $10, $0\n"
        "    por $9, $15, $0\n"
        "    paddh $2, $2, $25\n"
        "    paddh $3, $3, $25\n"
        "    psrlh $2, $2, 2\n"
        "    psrlh $3, $3, 2\n"
        "    sq $2, 0x0($14)\n"
        "    sll $10, $12, 1\n"
        "    sq $3, 0x10($14)\n"
        "    bgtz $7, .L_rix_0110025071C\n"
        "    addu $14, $14, $10\n"
        ".L_rix_01100250790:\n"
        "    addiu $5, $5, 0x80\n"
        "    addiu $6, $6, 0x80\n"
        "    lw $7, 0xC($4)\n"
        "    and $10, $11, $7\n"
        "    bnez $10, .L_rix_0110025071C\n"
        "    daddu $11, $0, $0\n"
        "    jr $31\n"
        "    nop\n"
        ".size _rix_011, . - _rix_011\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global _ri0_011\n"
        ".type _ri0_011, @function\n"
        "    .align 3\n"
        "_ri0_011:\n"
        "    pnor $25, $0, $0\n"
        "    psrlh $25, $25, 15\n"
        "    psllh $25, $25, 1\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $14, 0x0($4)\n"
        "    lw $13, 0x4($4)\n"
        "    lw $12, 0x10($4)\n"
        "    addiu $24, $0, 0x1\n"
        "    addiu $11, $0, 0x1\n"
        ".L_ri0_011002507D8:\n"
        "    lw $7, 0x8($4)\n"
        "    ld $8, 0x0($5)\n"
        "    ld $9, 0x0($6)\n"
        "    pcpyld $8, $9, $8\n"
        "    mtsab $13, 0x0\n"
        "    qfsrv $8, $8, $8\n"
        "    pextlb $9, $0, $8\n"
        "    addu $5, $5, $12\n"
        "    ori $11, $11, 0x8000\n"
        "    mtsab $24, 0x0\n"
        "    qfsrv $10, $0, $8\n"
        "    pextlb $8, $0, $10\n"
        "    beqz $7, .L_ri0_01100250864\n"
        "    paddh $15, $9, $8\n"
        ".L_ri0_01100250810:\n"
        "    addu $6, $6, $12\n"
        "    ld $8, 0x0($5)\n"
        "    ld $9, 0x0($6)\n"
        "    pcpyld $8, $9, $8\n"
        "    mtsab $13, 0x0\n"
        "    qfsrv $8, $8, $8\n"
        "    pextlb $9, $0, $8\n"
        "    addi $7, $7, -0x1\n"
        "    addu $5, $5, $12\n"
        "    mtsab $24, 0x0\n"
        "    qfsrv $10, $0, $8\n"
        "    pextlb $8, $0, $10\n"
        "    paddh $10, $9, $8\n"
        "    paddh $9, $10, $15\n"
        "    por $15, $10, $0\n"
        "    paddh $10, $9, $25\n"
        "    sll $8, $12, 1\n"
        "    psrlh $10, $10, 2\n"
        "    sq $10, 0x0($14)\n"
        "    bgtz $7, .L_ri0_01100250810\n"
        "    addu $14, $14, $8\n"
        ".L_ri0_01100250864:\n"
        "    psrah $10, $11, 15\n"
        "    addiu $5, $5, 0x140\n"
        "    lw $7, 0xC($4)\n"
        "    addiu $6, $6, 0x140\n"
        "    and $10, $10, $7\n"
        "    bnez $10, .L_ri0_01100250810\n"
        "    andi $11, $11, 0x7FFF\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $14, 0x0($4)\n"
        "    addiu $5, $5, 0x40\n"
        "    addiu $6, $6, 0x40\n"
        "    addiu $14, $14, 0x80\n"
        "    andi $10, $11, 0x1\n"
        "    bnez $10, .L_ri0_011002507D8\n"
        "    andi $11, $11, 0xFFFE\n"
        "    jr $31\n"
        "    nop\n"
        ".size _ri0_011, . - _ri0_011\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _rix_100);

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global _ri0_100\n"
        ".type _ri0_100, @function\n"
        "    .align 3\n"
        "_ri0_100:\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $14, 0x0($4)\n"
        "    lw $13, 0x4($4)\n"
        "    addiu $12, $0, -0x1\n"
        "    lw $3, 0x10($4)\n"
        "    sll $2, $3, 1\n"
        "    mtsab $13, 0x0\n"
        ".L_ri0_10000250978:\n"
        "    lw $7, 0x8($4)\n"
        "    addiu $11, $0, -0x1\n"
        ".L_ri0_10000250980:\n"
        "    ld $8, 0x0($5)\n"
        "    ld $9, 0x0($6)\n"
        "    pcpyld $8, $9, $8\n"
        "    qfsrv $8, $8, $8\n"
        "    pextlb $9, $0, $8\n"
        "    addi $7, $7, -0x1\n"
        "    addu $5, $5, $3\n"
        "    addu $6, $6, $3\n"
        "    lq $8, 0x0($14)\n"
        "    paddh $10, $9, $8\n"
        "    pcgth $9, $10, $0\n"
        "    psrlh $9, $9, 15\n"
        "    paddh $10, $10, $9\n"
        "    psrlh $10, $10, 1\n"
        "    sq $10, 0x0($14)\n"
        "    bgtz $7, .L_ri0_10000250980\n"
        "    addu $14, $14, $2\n"
        "    addiu $5, $5, 0x140\n"
        "    addiu $6, $6, 0x140\n"
        "    lw $7, 0xC($4)\n"
        "    and $10, $11, $7\n"
        "    bnez $10, .L_ri0_10000250980\n"
        "    daddu $11, $0, $0\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $14, 0x0($4)\n"
        "    addiu $5, $5, 0x40\n"
        "    addiu $6, $6, 0x40\n"
        "    addiu $14, $14, 0x80\n"
        "    bnez $12, .L_ri0_10000250978\n"
        "    daddu $12, $0, $0\n"
        "    jr $31\n"
        "    nop\n"
        ".size _ri0_100, . - _ri0_100\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global _rix_101\n"
        ".type _rix_101, @function\n"
        "    .align 3\n"
        "_rix_101:\n"
        "    pnor $25, $0, $0\n"
        "    psrlh $25, $25, 15\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $7, 0x8($4)\n"
        "    lw $14, 0x0($4)\n"
        "    lw $13, 0x4($4)\n"
        "    lw $12, 0x10($4)\n"
        "    lq $8, 0x0($5)\n"
        "    lq $9, 0x0($6)\n"
        "    mtsab $13, 0x0\n"
        "    qfsrv $10, $9, $8\n"
        "    sll $24, $12, 1\n"
        "    pextlb $8, $0, $10\n"
        "    addiu $11, $0, -0x1\n"
        "    beqz $7, .L_rix_10100250ACC\n"
        "    pextub $9, $0, $10\n"
        ".L_rix_10100250A4C:\n"
        "    addu $5, $5, $12\n"
        "    addu $6, $6, $12\n"
        "    lq $10, 0x0($5)\n"
        "    lq $15, 0x0($6)\n"
        "    qfsrv $2, $15, $10\n"
        "    pextlb $10, $0, $2\n"
        "    addi $7, $7, -0x1\n"
        "    pextub $15, $0, $2\n"
        "    paddh $2, $8, $10\n"
        "    paddh $3, $9, $15\n"
        "    por $8, $10, $0\n"
        "    por $9, $15, $0\n"
        "    paddh $2, $2, $25\n"
        "    paddh $3, $3, $25\n"
        "    psrlh $2, $2, 1\n"
        "    psrlh $3, $3, 1\n"
        "    lq $10, 0x0($14)\n"
        "    lq $15, 0x10($14)\n"
        "    paddh $2, $2, $10\n"
        "    paddh $3, $3, $15\n"
        "    pcgth $10, $2, $0\n"
        "    psrlh $10, $10, 15\n"
        "    paddh $10, $2, $10\n"
        "    psrlh $2, $10, 1\n"
        "    pcgth $10, $3, $0\n"
        "    psrlh $10, $10, 15\n"
        "    paddh $10, $3, $10\n"
        "    psrlh $3, $10, 1\n"
        "    sq $2, 0x0($14)\n"
        "    sq $3, 0x10($14)\n"
        "    bgtz $7, .L_rix_10100250A4C\n"
        "    addu $14, $14, $24\n"
        ".L_rix_10100250ACC:\n"
        "    addiu $5, $5, 0x80\n"
        "    addiu $6, $6, 0x80\n"
        "    lw $7, 0xC($4)\n"
        "    and $10, $11, $7\n"
        "    bnez $10, .L_rix_10100250A4C\n"
        "    daddu $11, $0, $0\n"
        "    jr $31\n"
        "    nop\n"
        ".size _rix_101, . - _rix_101\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global _ri0_101\n"
        ".type _ri0_101, @function\n"
        "    .align 3\n"
        "_ri0_101:\n"
        "    pnor $25, $0, $0\n"
        "    psrlh $25, $25, 15\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $14, 0x0($4)\n"
        "    lw $13, 0x4($4)\n"
        "    lw $12, 0x10($4)\n"
        "    addiu $11, $0, 0x1\n"
        "    sll $24, $12, 1\n"
        "    mtsab $13, 0x0\n"
        ".L_ri0_10100250B18:\n"
        "    lw $7, 0x8($4)\n"
        "    ld $8, 0x0($5)\n"
        "    ld $9, 0x0($6)\n"
        "    pcpyld $8, $9, $8\n"
        "    qfsrv $8, $8, $8\n"
        "    ori $11, $11, 0x8000\n"
        "    beqz $7, .L_ri0_10100250B8C\n"
        "    pextlb $15, $0, $8\n"
        ".L_ri0_10100250B38:\n"
        "    addu $5, $5, $12\n"
        "    addu $6, $6, $12\n"
        "    ld $8, 0x0($5)\n"
        "    ld $9, 0x0($6)\n"
        "    pcpyld $8, $9, $8\n"
        "    qfsrv $8, $8, $8\n"
        "    pextlb $10, $0, $8\n"
        "    addi $7, $7, -0x1\n"
        "    paddh $9, $10, $15\n"
        "    por $15, $10, $0\n"
        "    paddh $10, $9, $25\n"
        "    psrlh $10, $10, 1\n"
        "    lq $8, 0x0($14)\n"
        "    paddh $10, $10, $8\n"
        "    pcgth $9, $10, $0\n"
        "    psrlh $9, $9, 15\n"
        "    paddh $10, $10, $9\n"
        "    psrlh $10, $10, 1\n"
        "    sq $10, 0x0($14)\n"
        "    bgtz $7, .L_ri0_10100250B38\n"
        "    addu $14, $14, $24\n"
        ".L_ri0_10100250B8C:\n"
        "    psrah $10, $11, 15\n"
        "    addiu $5, $5, 0x140\n"
        "    lw $7, 0xC($4)\n"
        "    addiu $6, $6, 0x140\n"
        "    and $10, $10, $7\n"
        "    bnez $10, .L_ri0_10100250B38\n"
        "    andi $11, $11, 0x7FFF\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $14, 0x0($4)\n"
        "    addiu $5, $5, 0x40\n"
        "    addiu $6, $6, 0x40\n"
        "    addiu $14, $14, 0x80\n"
        "    andi $10, $11, 0x1\n"
        "    bnez $10, .L_ri0_10100250B18\n"
        "    andi $11, $11, 0xFFFE\n"
        "    jr $31\n"
        "    nop\n"
        ".size _ri0_101, . - _ri0_101\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global _rix_110\n"
        ".type _rix_110, @function\n"
        "    .align 3\n"
        "_rix_110:\n"
        "    pnor $25, $0, $0\n"
        "    psrlh $25, $25, 15\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $7, 0x8($4)\n"
        "    lw $14, 0x0($4)\n"
        "    lw $13, 0x4($4)\n"
        "    addiu $24, $0, 0x1\n"
        "    lw $9, 0x10($4)\n"
        "    sll $8, $9, 1\n"
        "    addiu $11, $0, -0x1\n"
        ".L_rix_11000250C04:\n"
        "    lq $10, 0x0($5)\n"
        "    lq $15, 0x0($6)\n"
        "    mtsab $13, 0x0\n"
        "    qfsrv $2, $15, $10\n"
        "    qfsrv $3, $10, $15\n"
        "    pextlb $10, $0, $2\n"
        "    addi $7, $7, -0x1\n"
        "    pextub $15, $0, $2\n"
        "    mtsab $24, 0x0\n"
        "    qfsrv $3, $3, $2\n"
        "    pextlb $2, $0, $3\n"
        "    pextub $3, $0, $3\n"
        "    paddh $10, $10, $2\n"
        "    paddh $15, $15, $3\n"
        "    paddh $2, $10, $25\n"
        "    paddh $3, $15, $25\n"
        "    psrlh $2, $2, 1\n"
        "    psrlh $3, $3, 1\n"
        "    lq $10, 0x0($14)\n"
        "    lq $15, 0x10($14)\n"
        "    paddh $2, $2, $10\n"
        "    paddh $3, $3, $15\n"
        "    pcgth $10, $2, $0\n"
        "    psrlh $10, $10, 15\n"
        "    paddh $10, $2, $10\n"
        "    psrlh $2, $10, 1\n"
        "    pcgth $10, $3, $0\n"
        "    psrlh $10, $10, 15\n"
        "    paddh $10, $3, $10\n"
        "    psrlh $3, $10, 1\n"
        "    sq $2, 0x0($14)\n"
        "    sq $3, 0x10($14)\n"
        "    addu $5, $5, $9\n"
        "    addu $6, $6, $9\n"
        "    bgtz $7, .L_rix_11000250C04\n"
        "    addu $14, $14, $8\n"
        "    addiu $5, $5, 0x80\n"
        "    addiu $6, $6, 0x80\n"
        "    lw $7, 0xC($4)\n"
        "    and $12, $11, $7\n"
        "    bnez $12, .L_rix_11000250C04\n"
        "    daddu $11, $0, $0\n"
        "    jr $31\n"
        "    nop\n"
        ".size _rix_110, . - _rix_110\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global _ri0_110\n"
        ".type _ri0_110, @function\n"
        "    .align 3\n"
        "_ri0_110:\n"
        "    pnor $25, $0, $0\n"
        "    psrlh $25, $25, 15\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $14, 0x0($4)\n"
        "    lw $13, 0x4($4)\n"
        "    addiu $24, $0, 0x1\n"
        "    addiu $12, $0, -0x1\n"
        "    lw $3, 0x10($4)\n"
        "    sll $2, $3, 1\n"
        ".L_ri0_11000250CE0:\n"
        "    lw $7, 0x8($4)\n"
        "    addiu $11, $0, -0x1\n"
        ".L_ri0_11000250CE8:\n"
        "    ld $8, 0x0($5)\n"
        "    ld $9, 0x0($6)\n"
        "    pcpyld $8, $9, $8\n"
        "    mtsab $13, 0x0\n"
        "    qfsrv $8, $8, $8\n"
        "    pextlb $9, $0, $8\n"
        "    addi $7, $7, -0x1\n"
        "    addu $5, $5, $3\n"
        "    addu $6, $6, $3\n"
        "    mtsab $24, 0x0\n"
        "    qfsrv $10, $0, $8\n"
        "    pextlb $8, $0, $10\n"
        "    paddh $10, $9, $8\n"
        "    paddh $10, $10, $25\n"
        "    psrlh $10, $10, 1\n"
        "    lq $8, 0x0($14)\n"
        "    paddh $10, $10, $8\n"
        "    pcgth $9, $10, $0\n"
        "    psrlh $9, $9, 15\n"
        "    paddh $10, $10, $9\n"
        "    psrlh $10, $10, 1\n"
        "    sq $10, 0x0($14)\n"
        "    bgtz $7, .L_ri0_11000250CE8\n"
        "    addu $14, $14, $2\n"
        "    addiu $5, $5, 0x140\n"
        "    addiu $6, $6, 0x140\n"
        "    lw $7, 0xC($4)\n"
        "    and $10, $11, $7\n"
        "    bnez $10, .L_ri0_11000250CE8\n"
        "    daddu $11, $0, $0\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $14, 0x0($4)\n"
        "    addiu $5, $5, 0x40\n"
        "    addiu $6, $6, 0x40\n"
        "    addiu $14, $14, 0x80\n"
        "    bnez $12, .L_ri0_11000250CE0\n"
        "    daddu $12, $0, $0\n"
        "    jr $31\n"
        "    nop\n"
        ".size _ri0_110, . - _ri0_110\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global _rix_111\n"
        ".type _rix_111, @function\n"
        "    .align 3\n"
        "_rix_111:\n"
        "    pnor $25, $0, $0\n"
        "    psrlh $25, $25, 15\n"
        "    psllh $25, $25, 1\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $7, 0x8($4)\n"
        "    lw $14, 0x0($4)\n"
        "    lw $13, 0x4($4)\n"
        "    lw $24, 0x10($4)\n"
        "    addiu $12, $0, 0x1\n"
        "    lq $8, 0x0($5)\n"
        "    lq $9, 0x0($6)\n"
        "    mtsab $13, 0x0\n"
        "    qfsrv $10, $9, $8\n"
        "    qfsrv $15, $8, $9\n"
        "    pextlb $8, $0, $10\n"
        "    pextub $9, $0, $10\n"
        "    addiu $11, $0, -0x1\n"
        "    mtsab $12, 0x0\n"
        "    qfsrv $15, $15, $10\n"
        "    pextlb $10, $0, $15\n"
        "    pextub $15, $0, $15\n"
        "    paddh $8, $8, $10\n"
        "    beqz $7, .L_rix_11100250E90\n"
        "    paddh $9, $9, $15\n"
        ".L_rix_11100250DEC:\n"
        "    addu $5, $5, $24\n"
        "    addu $6, $6, $24\n"
        "    lq $10, 0x0($5)\n"
        "    lq $15, 0x0($6)\n"
        "    mtsab $13, 0x0\n"
        "    qfsrv $2, $15, $10\n"
        "    qfsrv $3, $10, $15\n"
        "    pextlb $10, $0, $2\n"
        "    addi $7, $7, -0x1\n"
        "    pextub $15, $0, $2\n"
        "    mtsab $12, 0x0\n"
        "    qfsrv $3, $3, $2\n"
        "    pextlb $2, $0, $3\n"
        "    pextub $3, $0, $3\n"
        "    paddh $10, $10, $2\n"
        "    paddh $15, $15, $3\n"
        "    paddh $2, $8, $10\n"
        "    paddh $3, $9, $15\n"
        "    por $8, $10, $0\n"
        "    por $9, $15, $0\n"
        "    paddh $2, $2, $25\n"
        "    paddh $3, $3, $25\n"
        "    psrlh $2, $2, 2\n"
        "    psrlh $3, $3, 2\n"
        "    lq $10, 0x0($14)\n"
        "    lq $15, 0x10($14)\n"
        "    paddh $2, $2, $10\n"
        "    paddh $3, $3, $15\n"
        "    pcgth $10, $2, $0\n"
        "    psrlh $10, $10, 15\n"
        "    paddh $10, $2, $10\n"
        "    psrlh $2, $10, 1\n"
        "    pcgth $10, $3, $0\n"
        "    psrlh $10, $10, 15\n"
        "    paddh $10, $3, $10\n"
        "    psrlh $3, $10, 1\n"
        "    sq $2, 0x0($14)\n"
        "    sll $10, $24, 1\n"
        "    sq $3, 0x10($14)\n"
        "    bgtz $7, .L_rix_11100250DEC\n"
        "    addu $14, $14, $10\n"
        ".L_rix_11100250E90:\n"
        "    addiu $5, $5, 0x80\n"
        "    addiu $6, $6, 0x80\n"
        "    lw $7, 0xC($4)\n"
        "    and $10, $11, $7\n"
        "    bnez $10, .L_rix_11100250DEC\n"
        "    daddu $11, $0, $0\n"
        "    jr $31\n"
        "    nop\n"
        ".size _rix_111, . - _rix_111\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global _ri0_111\n"
        ".type _ri0_111, @function\n"
        "    .align 3\n"
        "_ri0_111:\n"
        "    pnor $25, $0, $0\n"
        "    psrlh $25, $25, 15\n"
        "    psllh $25, $25, 1\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $14, 0x0($4)\n"
        "    lw $13, 0x4($4)\n"
        "    lw $12, 0x10($4)\n"
        "    addiu $24, $0, 0x1\n"
        "    addiu $11, $0, 0x1\n"
        ".L_ri0_11100250ED8:\n"
        "    lw $7, 0x8($4)\n"
        "    ld $8, 0x0($5)\n"
        "    ld $9, 0x0($6)\n"
        "    pcpyld $8, $9, $8\n"
        "    mtsab $13, 0x0\n"
        "    qfsrv $8, $8, $8\n"
        "    pextlb $9, $0, $8\n"
        "    addu $5, $5, $12\n"
        "    ori $11, $11, 0x8000\n"
        "    mtsab $24, 0x0\n"
        "    qfsrv $10, $0, $8\n"
        "    pextlb $8, $0, $10\n"
        "    beqz $7, .L_ri0_11100250F7C\n"
        "    paddh $15, $9, $8\n"
        ".L_ri0_11100250F10:\n"
        "    addu $6, $6, $12\n"
        "    ld $8, 0x0($5)\n"
        "    ld $9, 0x0($6)\n"
        "    pcpyld $8, $9, $8\n"
        "    mtsab $13, 0x0\n"
        "    qfsrv $8, $8, $8\n"
        "    pextlb $9, $0, $8\n"
        "    addi $7, $7, -0x1\n"
        "    addu $5, $5, $12\n"
        "    mtsab $24, 0x0\n"
        "    qfsrv $10, $0, $8\n"
        "    pextlb $8, $0, $10\n"
        "    paddh $10, $9, $8\n"
        "    paddh $9, $10, $15\n"
        "    por $15, $10, $0\n"
        "    paddh $10, $9, $25\n"
        "    psrlh $10, $10, 2\n"
        "    lq $8, 0x0($14)\n"
        "    paddh $10, $10, $8\n"
        "    pcgth $9, $10, $0\n"
        "    psrlh $9, $9, 15\n"
        "    paddh $10, $10, $9\n"
        "    sll $8, $12, 1\n"
        "    psrlh $10, $10, 1\n"
        "    sq $10, 0x0($14)\n"
        "    bgtz $7, .L_ri0_11100250F10\n"
        "    addu $14, $14, $8\n"
        ".L_ri0_11100250F7C:\n"
        "    psrah $10, $11, 15\n"
        "    addiu $5, $5, 0x140\n"
        "    lw $7, 0xC($4)\n"
        "    addiu $6, $6, 0x140\n"
        "    and $10, $10, $7\n"
        "    bnez $10, .L_ri0_11100250F10\n"
        "    andi $11, $11, 0x7FFF\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $14, 0x0($4)\n"
        "    addiu $5, $5, 0x40\n"
        "    addiu $6, $6, 0x40\n"
        "    addiu $14, $14, 0x80\n"
        "    andi $10, $11, 0x1\n"
        "    bnez $10, .L_ri0_11100250ED8\n"
        "    andi $11, $11, 0xFFFE\n"
        "    jr $31\n"
        "    nop\n"
        ".size _ri0_111, . - _ri0_111\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

extern int D_0026E920;

void _copyAddRefImage(void *a0, void *a1, void *a2)
{
    __asm__ __volatile__(".set noreorder\n"
                         "addiu $12, $0, 0x18\n"
                         "lui $10, %%hi(D_0026E920)\n"
                         "addiu $10, $10, %%lo(D_0026E920)\n"
                         "lq $11, 0x0($10)\n"
                         "1:\n"
                         "lq $8, 0x0($5)\n"
                         "addi $12, $12, -0x1\n"
                         "lq $13, 0x0($6)\n"
                         "addiu $4, $4, 0x10\n"
                         "lq $9, 0x10($5)\n"
                         "paddh $8, $8, $13\n"
                         "lq $2, 0x10($6)\n"
                         "pminh $8, $8, $11\n"
                         "paddh $9, $9, $2\n"
                         "pmaxh $8, $8, $0\n"
                         "pminh $9, $9, $11\n"
                         "addiu $5, $5, 0x20\n"
                         "pmaxh $9, $9, $0\n"
                         "addiu $6, $6, 0x20\n"
                         "ppacb $10, $9, $8\n"
                         "bnez $12, 1b\n"
                         "sq $10, -0x10($4)\n"
                         ".set reorder\n" ::
                             : "$2", "$8", "$9", "$10", "$11", "$12", "$13", "memory");
}

/* The saturating pack _copyAddRefImage does without the add: 24 rounds of two
 * quadwords of signed halfword samples clamped into 0..255 and packed down to
 * bytes. Whole-function assembly under the MMI exception, and the 16 byte
 * clamp mask its sibling reads as D_0026E920 lives in this function's own
 * text, aligned to a quadword, with the two pad instructions the alignment
 * leaves behind. */
void _copyRefImage(void *a0, void *a1)
{
    __asm__ __volatile__(".set noreorder\n"
                         "addiu $12, $0, 0x18\n"
                         "lui $10, %%hi(D_0026E920)\n"
                         "addiu $10, $10, %%lo(D_0026E920)\n"
                         "lq $11, 0x0($10)\n"
                         "1:\n"
                         "lq $8, 0x0($5)\n"
                         "addi $12, $12, -0x1\n"
                         "pminh $8, $8, $11\n"
                         "lq $9, 0x10($5)\n"
                         "pmaxh $8, $8, $0\n"
                         "pminh $9, $9, $11\n"
                         "addiu $5, $5, 0x20\n"
                         "pmaxh $9, $9, $0\n"
                         "addiu $4, $4, 0x10\n"
                         "ppacb $10, $9, $8\n"
                         "bnez $12, 1b\n"
                         "sq $10, -0x10($4)\n"
                         ".align 4\n"
                         "D_0026E920:\n"
                         ".word 0x00FF00FF\n"
                         ".word 0x00FF00FF\n"
                         ".word 0x00FF00FF\n"
                         ".word 0x00FF00FF\n"
                         ".set reorder\n" ::
                             : "$8", "$9", "$10", "$11", "$12", "memory");
}

void _ipuSetMPEG1(int a0)
{
    int *reg = (int *)0x10002010;
    *reg = (*reg & 0xFF7FFFFF) | (a0 << 23);
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _waitBdecOut);

extern int _ipuVdec(int a0);

int _dmVector(void)
{
    return _ipuVdec(3);
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _dualPrimeVector);

extern int _isError[];
extern int D_00636FE0[];
extern void _flushBuf(int a0);
extern int _peepBit(int a0);

int _mbAddressIncrement(void)
{
    int cont;
    int sum;
    unsigned int v;

    sum = 0;
    do {
        v = _ipuVdec(0);
        switch (v) {
        case 0x22:
            cont = 1;
            break;
        case 0x23:
            cont = 1;
            sum += 0x21;
            break;
        case 0: {
            int r = _peepBit(0xB);
            if ((_isMpeg2[0] != 0) && (r == 0xF)) {
                _flushBuf(0xB);
                cont = 1;
            } else {
                _Error1((int)D_00636FE0, v);
                _isError[0] = 1;
                return 1;
            }
        } break;
        default:
            sum += v;
            cont = 0;
            break;
        }
    } while (cont);
    return sum;
}

extern int _widthMB[];
extern int _heightMB[];
extern void _waitIpuIdle(void);
extern int _slice0(int a0, int a1);
extern int _waitBdecOut(void);
extern void _doMC(int a0);
extern int D_00637018[];

int _pictureData0(int a0)
{
    int n = _widthMB[0] * _heightMB[0];
    int r;

    _mbcont[0x280 / 4] = 0;
    _mbcont[0x284 / 4] = 0;
    if (_picture_structure[0] != 3) {
        n = n >> 1;
    }
    do {
        r = _slice0(a0, n);
    } while (r == 1 || r == 3);
    _waitIpuIdle();
    if (_waitBdecOut() == 0) {
        r = 2;
    }
    while (((*(volatile unsigned int *)0x1000D400) >> 8) & 1) {}
    if (r == 0) {
        _doMC(_mbcont[0x280 / 4] == 0);
    }
    if (r == 1 || r == 2) {
        _Error(D_00637018);
    }
    return r == 0;
}

extern int _widthMB[];
extern int _sp_dcr[];
extern int D_00637038[];
extern int D_00637060[];
extern void _nextStartCode(void);
extern int _sliceB(void);

int _sliceA0(int a0, int *a1, int *a2, int *a3)
{
    int id;
    int m;
    int n;

    _isError[0] = 0;
    _nextStartCode();
    id = _peepBit(0x20);
    if ((unsigned int)(id - 0x101) >= 0xAF) {
        _Error1((int)D_00637038, id);
        return 2;
    }
    _flushBuf(0x20);
    m = _sliceB();
    n = _mbAddressIncrement();
    *a2 = n;
    if (_isError[0] != 0) {
        _Error(D_00637060);
        return 1;
    }
    *a1 = ((((m << 7) + (id & 0xFF)) - 1) * _widthMB[0] + n) - 1;
    *a2 = 1;
    _sp_dcr[0] = 1;
    a3[5] = 0;
    a3[4] = 0;
    a3[1] = 0;
    a3[0] = 0;
    a3[7] = 0;
    a3[6] = 0;
    a3[3] = 0;
    a3[2] = 0;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _slice0);

extern int D_006370A0[];
extern int _picture_coding_type[];

int _skipMB0(int *a0, int *a1, int *a2, int *a3)
{
    int ret = 1;
    char *p;

    _sp_dcr[0] = 1;
    p = (char *)_mbcont + _mbcont[0xA0] * 0x140;
    *(int *)(p + 0x13C) = 1;
    if (_picture_coding_type[0] == 2) {
        a0[0] = a0[1] = a0[4] = a0[5] = 0;
    }
    if (_picture_structure[0] == 3) {
        a1[0] = 2;
    } else {
        a1[0] = 1;
        a2[0] = a2[1] = _picture_structure[0] == 2;
    }
    if (_picture_coding_type[0] == 1) {
        _Error(D_006370A0);
        ret = 0;
    }
    a3[0] = a3[0] & ~1;
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _decMB0);

void _decode_motion_vector(int *pred, int r_size, int motion_code, int motion_r, int full_pel)
{
    int lim = 16 << r_size;
    int vec = full_pel ? (*pred >> 1) : *pred;

    if (motion_code > 0) {
        vec += ((motion_code - 1) << r_size) + motion_r + 1;
        if (vec >= lim) {
            vec -= lim + lim;
        }
    } else if (motion_code < 0) {
        vec -= ((-motion_code - 1) << r_size) + motion_r + 1;
        if (vec < -lim) {
            vec += lim + lim;
        }
    }
    *pred = full_pel ? vec * 2 : vec;
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _motionVectors);

extern void _decode_motion_vector();
extern unsigned int _nextBit(int a0);

void _motionVector(char *a0, char *a1, void *a2, void *a3, int a4, int a5, int a6)
{
    void *r;
    int r2;

    r = (void *)_ipuVdec(2);
    if (a2 == 0)
        goto c1z;
    if (r == 0) {
        r2 = 0;
        goto c1c;
    }
    r2 = _nextBit(a2);
    goto c1c;
c1z:
    r2 = 0;
c1c:
    _decode_motion_vector(a0, a2, r, r2, a6);
    if (a4 != 0) {
        *(int *)a1 = _dmVector();
    }
    r = (void *)_ipuVdec(2);
    if (a3 == 0)
        goto c2z;
    if (r == 0) {
        r2 = 0;
        goto c2c;
    }
    r2 = _nextBit(a3);
    goto c2c;
c2z:
    r2 = 0;
c2c:
    if (a5 != 0) {
        *(int *)(a0 + 4) = *(int *)(a0 + 4) >> 1;
    }
    _decode_motion_vector(a0 + 4, a3, r, r2, a6);
    if (a5 != 0) {
        *(int *)(a0 + 4) = *(int *)(a0 + 4) * 2;
    }
    if (a4 != 0) {
        *(int *)(a1 + 4) = _dmVector();
    }
}

extern int _isTop32dirty[];
extern int D_0054CA08[];
extern int D_0054CA08[];

void _sendIpuCommand(unsigned int a0)
{
    *(volatile unsigned int *)0x10002000 = a0;
    _isTop32dirty[0] = D_0054CA08[a0 >> 28];
}

void _waitIpuIdle(void)
{
    int n = 0;

    /* the IPU control register the hardware clears when the decode retires */
    while ((*(volatile int *)0x10002010 & 0x80004000) == 0x80000000) {
        if (n++ >= 5001) {
            _dispatchMpegCbNodata(D_0054C0E4[0]);
            n = 0;
        }
    }
}

long long _waitIpuIdle64(void)
{
    long long v;
    int n = 0;

    /* the 64 bit IPU command register: the top bit stays set while the
     * command is running, and 0x4000 of the control register at 0x10002010
     * is the error the decoder gives up on */
    while ((v = *(volatile long long *)0x10002000) < 0 &&
           (*(volatile int *)0x10002010 & 0x4000) == 0) {
        if (n++ >= 5001) {
            _dispatchMpegCbNodata(D_0054C0E4[0]);
            n = 0;
        }
    }
    return v;
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _ipuVdec);

extern int _top32;
extern int _top32len;
extern long long _waitIpuIdle64(void);

int _peepBit(int a0)
{
    if (_isTop32dirty[0] != 0 || _top32len < a0) {
        int n = 0;

        while ((*(volatile int *)0x10002010 & 0x80004000) == 0x80000000) {
            if (n++ >= 5001) {
                _dispatchMpegCbNodata(D_0054C0E4[0]);
                n = 0;
            }
        }
        *(volatile unsigned int *)0x10002000 = 0x40000000;
        _isTop32dirty[0] = D_0054CA08[4];
        _top32 = _waitIpuIdle64();
        _top32len = 32;
    }
    return (unsigned int)_top32 >> (32 - a0);
}

extern int _top32;
extern int _top32len;
extern long long _waitIpuIdle64(void);

void _flushBuf(int a0)
{
    int n = 0;
    int cmd;

    while ((*(volatile int *)0x10002010 & 0x80004000) == 0x80000000) {
        if (n++ >= 5001) {
            _dispatchMpegCbNodata(D_0054C0E4[0]);
            n = 0;
        }
    }
    cmd = a0 | 0x40000000;
    *(volatile unsigned int *)0x10002000 = cmd;
    _isTop32dirty[0] = D_0054CA08[(unsigned int)cmd >> 28];
    _top32 = _waitIpuIdle64();
    _top32len = 32;
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _nextBit);

extern void _waitIpuIdle(void);

void _nextStartCode(void)
{
    int v;
    _waitIpuIdle();
    v = (-(*(volatile int *)0x10002020 & 7)) & 7;
    if (v)
        _flushBuf(v);
    while (_peepBit(0x18) != 1) {
        _flushBuf(8);
    }
}

extern void _extrainfo(void);
extern int _qscqsc;
extern int _intra_slice;
extern void _extrainfo(void);

int _sliceB(void)
{
    _qscqsc = _nextBit(5);
    if (_nextBit(1) != 0) {
        _intra_slice = _nextBit(1);
        _flushBuf(7);
        _extrainfo();
    } else {
        _intra_slice = 0;
    }
    return 0;
}

extern void _groupOfPicturesHeader(void);
extern void _pictureHeader(void);
extern void _sequenceHeader(void);
extern long long _headerPts;
extern long long _headerDts;
extern void _sequenceHeader(void);
extern void _groupOfPicturesHeader(void);
extern void _pictureHeader(void);

int _nextHeader(void)
{
    int buf[8];
    unsigned int code;

    for (;;) {
        _nextStartCode();
        code = _nextBit(32);
        switch (code) {
        case 0x1B3:
            _sequenceHeader();
            break;
        case 0x1B8:
            _groupOfPicturesHeader();
            break;
        case 0x100:
            _pictureHeader();
            buf[0] = 5;
            *(long long *)&buf[2] = -1;
            *(long long *)&buf[4] = -1;
            _dispatchMpegCallback(D_0054C0E4[0], buf);
            _headerPts = *(long long *)&buf[2];
            _headerDts = *(long long *)&buf[4];
            return _picture_coding_type[0];
        case 0x1B7:
            return 0;
        }
    }
}

extern int _temporal_reference;
extern int _vbv_delay;
extern int _full_pel_forward_vector;
extern int _forward_f_code;
extern int _full_pel_backward_vector;
extern int _backward_f_code;
extern void _extensionAndUserData(void);
extern void _updateTempTackData(void);

void _pictureHeader(void)
{
    _temporal_reference = _nextBit(10);
    _picture_coding_type[0] = _nextBit(3);
    _vbv_delay = _nextBit(16);
    if (_picture_coding_type[0] == 2 || _picture_coding_type[0] == 3) {
        _full_pel_forward_vector = _nextBit(1);
        _forward_f_code = _nextBit(3);
    }
    if (_picture_coding_type[0] == 3) {
        _full_pel_backward_vector = _nextBit(1);
        _backward_f_code = _nextBit(3);
    }
    _extrainfo();
    _extensionAndUserData();
    _updateTempTackData();
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _extensionAndUserData);
INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _pictureCodingExtension);

void _extrainfo(void)
{
    while (_nextBit(1) != 0) {
        _flushBuf(8);
    }
}

extern int D_0054CA6C;
extern int D_0054CA70;
extern int _tmpRefBase;
extern int _tmpRefGOPreset;
extern int _trFrameNumber;
extern int _trFrameNumberA;

void _updateTempTackData(void)
{
    if (_picture_coding_type[0] != 3 && _temporal_reference != D_0054CA70) {
        if (D_0054CA6C != 0) {
            D_0054CA6C = 0;
            _tmpRefBase += 0x400;
        }
        if (_temporal_reference < D_0054CA70 && _tmpRefGOPreset == 0) {
            D_0054CA6C = 1;
        }
        _tmpRefGOPreset = 0;
        D_0054CA70 = _temporal_reference;
    }
    _trFrameNumber = _tmpRefBase + _temporal_reference;
    if (D_0054CA6C != 0 && D_0054CA70 >= _temporal_reference) {
        _trFrameNumber = _tmpRefBase + _temporal_reference + 0x400;
    }
    _trFrameNumberA = _trFrameNumberA < _trFrameNumber ? _trFrameNumber : _trFrameNumberA;
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _groupOfPicturesHeader);

extern int _load_intra_quantizer_matrix;
extern int _load_non_intra_quantizer_matrix;
extern int D_006370F0[];
extern int D_00637118[];

void _quantMatrixExtension(void)
{
    if ((_load_intra_quantizer_matrix = _nextBit(1)) != 0) {
        _waitIpuIdle();
        _sendIpuCommand(0x50000000);
        _waitIpuIdle();
    }
    if ((_load_non_intra_quantizer_matrix = _nextBit(1)) != 0) {
        _waitIpuIdle();
        _sendIpuCommand(0x58000000);
        _waitIpuIdle();
    }
    if (_nextBit(1) != 0) {
        _Error(D_006370F0);
    }
    if (_nextBit(1) != 0) {
        _Error(D_00637118);
    }
}

extern int _progressive_sequence;
extern int _repeat_first_field;
extern int _top_field_first;
extern int _frame_center_horizontal_offset[];
extern int _frame_center_vertical_offset[];

void _pictureDisplayExtension(void)
{
    int n;
    int i;

    if (_progressive_sequence != 0) {
        if (_repeat_first_field != 0) {
            n = _top_field_first != 0 ? 3 : 2;
        } else {
            n = 1;
        }
    } else {
        if (_picture_structure[0] != 3) {
            n = 1;
        } else {
            n = _repeat_first_field != 0 ? 3 : 2;
        }
    }
    for (i = 0; i < n; i++) {
        _frame_center_horizontal_offset[i] = _nextBit(16);
        _nextBit(1);
        _frame_center_vertical_offset[i] = _nextBit(16);
        _nextBit(1);
    }
}

extern int _copyright_flag;
extern int _copyright_identifier;
extern int _original_or_copy;
extern int _copyright_number_1;
extern int _copyright_number_2;
extern int _copyright_number_3;

void _copyrightExtension(void)
{
    _copyright_flag = _nextBit(1);
    _copyright_identifier = _nextBit(8);
    _original_or_copy = _nextBit(1);
    /* seven reserved bits, then the marker bit before each field */
    _nextBit(7);
    _nextBit(1);
    _copyright_number_1 = _nextBit(20);
    _nextBit(1);
    _copyright_number_2 = _nextBit(22);
    _nextBit(1);
    _copyright_number_3 = _nextBit(22);
}

extern int _curFrame[];
extern int _curTop[];
extern int _curBot[];
extern int D_00637148[];
extern int D_00637168[];
extern int _pictureData0(int a0);

int _decPicture(int a0, int a1)
{
    int p;
    int r;

    if (_picture_structure[0] == 3 && _isSecondField[0] != 0) {
        _Error(D_00637148);
        _isSecondField[0] = 0;
    }
    switch (_picture_structure[0]) {
    case 3:
        p = _curFrame[0];
        break;
    case 1:
        p = _curTop[0];
        break;
    case 2:
        p = _curBot[0];
        break;
    default:
        p = _curFrame[0];
        _Error(D_00637168);
        break;
    }
    r = _pictureData0(a0);
    if (r != 0) {
        *(int *)(p + 0x28) = 1;
    }
    return r;
}

extern int _picture_coding_type[];
extern int _zFrame[];
extern int _zTop[];
extern int _zBot[];

void _outputFrame(int a0, int a1)
{
    int *p = *(int **)((char *)D_0054C0E4[0] + 0x40);

    if (a1 != 0) {
        int top;
        int bot;

        if (_picture_structure[0] == 3) {
            if (_picture_coding_type[0] == 3) {
                top = _zFrame[0];
            } else {
                top = _forwFrame[0];
            }
            _dispRefImage(top, a0 - 1);
        } else {
            if (_picture_coding_type[0] == 3) {
                top = _zTop[0];
                bot = _zBot[0];
            } else {
                top = _forwTop[0];
                bot = _forwBot[0];
            }
            _dispRefImageField(top, bot, a0 - 1);
        }
    }
    if (p[0xF8 / 4] == 1) {
        p[0xF8 / 4] = 2;
    }
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _updateRefImage);

extern char D_00637188[];
extern void sprintf();

int _isOutSizeOK(char *p)
{
    char *c = *(char **)((char *)D_0054C0E4[0] + 0x40);
    int e0 = *(int *)(c + 0xE0);
    int flag;
    if (e0 != 0) {
        flag = *(int *)(c + 0xDC) >= *(int *)(p + 0x4) && e0 >= *(int *)(p + 0x8);
    } else {
        flag = *(int *)(c + 0xE4) >= *(int *)(p + 0xC) * *(int *)(p + 0x10);
    }
    if (flag == 0) {
        char buf[0x100];
        sprintf(buf, (int)D_00637188, *(int *)(p + 0x4), *(int *)(p + 0x8));
        _Error(buf);
    }
    return flag;
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _cpr8);

extern int _isOutputPicture[];

int _markOutput(void)
{
    int *q = *(int **)((char *)D_0054C0E4[0] + 0x40);
    if (q[2] != 2) {
        int v = _totalFrames[0];
        q[2] = 2;
        q[0x2B] = v;
    }
    _isOutputPicture[0] = 1;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _getPtsDtsFlags);

extern unsigned int _showCount[];
extern void _getPtsDtsFlags(char *a0, void *a1, void *a2, void *a3);
extern int _isOutSizeOK(char *p);
extern void _csc_storeRefImage(char *p);
extern void _cpr8(char *p);
extern int _markOutput(void);

void _dispRefImage(char *a0, int a1)
{
    char *q = D_0054C0E4[0];
    char *r = *(char **)(q + 0x40);

    _getPtsDtsFlags(a0, q + 0x10, q + 0x18, q + 0x20);
    q = D_0054C0E4[0];
    *(int *)(r + 0x80) = *(int *)(q + 0x10);
    *(long long *)(r + 0x88) = _showCount[(int)(*(long long *)(q + 0x20) >> 5) & 0xF];
    *(int *)(r + 0xCC) = *(int *)(a0 + 0x5C);
    *(int *)(r + 0xD0) = *(int *)(a0 + 0x60);
    *(int *)(r + 0xB4) = *(int *)(a0 + 0x44);
    *(int *)(r + 0xB8) = *(int *)(a0 + 0x48);
    *(int *)(r + 0xBC) = *(int *)(a0 + 0x4C);
    *(int *)(r + 0xC0) = *(int *)(a0 + 0x50);
    *(int *)(r + 0xC4) = *(int *)(a0 + 0x54);
    *(int *)(r + 0xC8) = *(int *)(a0 + 0x58);
    if (_isOutSizeOK(a0) != 0 && *(int *)(a0 + 0x28) == 1) {
        if (*(int *)(r + 0xB0) != 0) {
            _csc_storeRefImage(a0);
        } else {
            _cpr8(a0);
        }
        _markOutput();
    }
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _dispRefImageField);

void _doCSC(int a0, int a1)
{
    int buf[8];

    while (*(volatile int *)0x10002010 < 0) {}
    *(volatile int *)0x1000B010 = a0 & 0x0FFFFFFF;
    *(volatile int *)0x1000B020 = a1 << 6;
    *(volatile int *)0x1000B000 = 0x100;
    _sendIpuCommand(a1 | 0x70000000);
    buf[0] = 4;
    _dispatchMpegCallback(D_0054C0E4[0], buf);
    while (((*(volatile unsigned int *)0x1000B000) >> 8) & 1) {}
    while (*(volatile int *)0x10002010 < 0) {}
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _ch3dmaCSC);
INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _doCSC2);

extern int D_007315DC[];
extern int D_007315E0[];
extern int D_007315E4[];
extern int D_007315DC[];
extern int D_007315E0[];
extern int D_007315E4[];

int _ch4dma(void)
{
    *(volatile unsigned int *)0x1000E010 = 0x10;
    D_007315DC[0]++;
    if (D_007315E0[0] == 0)
        return 1;
    if ((unsigned int)D_007315E0[0] > 0xFFFF) {
        *(volatile unsigned int *)0x1000B410 = D_007315E4[0];
        *(volatile unsigned int *)0x1000B420 = 0xFFFF;
        *(volatile unsigned int *)0x1000B400 = 0x101;
        D_007315E4[0] = (D_007315E4[0] + 0xFFFF0) & 0xFFFFFFF;
        D_007315E0[0] -= 0xFFFF;
    } else {
        *(volatile unsigned int *)0x1000B410 = D_007315E4[0];
        *(volatile unsigned int *)0x1000B420 = D_007315E0[0];
        *(volatile unsigned int *)0x1000B400 = 0x101;
        D_007315E0[0] = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _csc_storeRefImage);

extern void _sysbitFlush(int *a0, int a1);

void _sysbitInit(int *a0, int a1, int a2, int a3)
{
    a0[2] = a1;
    a0[3] = a1;
    *(long long *)a0 = 0;
    a0[4] = 0;
    *(long long *)(a0 + 6) = 0;
    a0[8] = a2;
    a0[9] = a2 + a3;
    a0[0xA] = a3;
    _sysbitFlush(a0, 0);
}

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _sysbitNext);
INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/libmpeg", _sysbitFlush);

int _sysbitGet(int *self, int a1)
{
    int ret = _sysbitNext(self, a1);
    _sysbitFlush(self, a1);
    return ret;
}

int _sysbitMarker(int *self)
{
    int ret = _sysbitNext(self, 1);
    _sysbitFlush(self, 1);
    return ret;
}

void _sysbitJump(int *a0, int a1)
{
    long long x = *(long long *)(a0 + 6) + (a1 << 3);
    int v;
    *(long long *)a0 = 0;
    a0[4] = 0;
    *(long long *)(a0 + 6) = x;
    v = a0[2] + (int)(x >> 3);
    a0[3] = v;
    if ((unsigned int)v >= (unsigned int)a0[9]) {
        a0[3] = v - a0[10];
    }
    _sysbitFlush(a0, 0);
}

int _sysbitPtr(int *a0, int a1)
{
    int v = a0[2] + (a1 >> 3);
    if ((unsigned int)v >= (unsigned int)a0[9]) {
        v -= a0[10];
    }
    return v;
}

extern void DIntr(int *self);
extern void EIntr(void);

void setD3_CHCR(int *a0)
{
    DIntr(a0);
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 | 0x10000;
    *(volatile int *)0x1000B000 = (int)a0;
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 & 0xFFFEFFFF;
    EIntr();
}

void setD4_CHCR(int *a0)
{
    DIntr(a0);
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 | 0x10000;
    *(volatile int *)0x1000B400 = (int)a0;
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 & 0xFFFEFFFF;
    EIntr();
}
