/*
 * sce/libmpeg/libmpeg_internal.h  (derived name: the file name is ours)
 *
 * libmpeg's declarations that are not public SDK API: the decoder's shared
 * state (var.o's and init.o's globals) and the helpers the members call
 * across files.  Each declaration is the definition's in sce/libmpeg.  A
 * reference image (_refFrame0 and the rest, 26 ints) is passed as the int
 * pointer var.o declares it.
 */
#ifndef SCE_LIBMPEG_LIBMPEG_INTERNAL_H
#define SCE_LIBMPEG_LIBMPEG_INTERNAL_H

/* one of the 8-byte time-stamp slots the decoder handle carries for each
 * field: _getPtsDtsFlags fills the pair as a 64-bit word and the display
 * record takes its low half back as an int */
typedef union {
    long long d;
    int w[2];
} MpegStamp;

/* the decoder handle sceMpegCreate registers: the picture size and count,
 * the two fields' time stamps and flags, and its internal record */
typedef struct {
    int width, height, frameCount, pad0C;
    MpegStamp pts, dts;       /* 0x10, 0x18 */
    long long flags;          /* 0x20 */
    MpegStamp pts2nd, dts2nd; /* 0x28, 0x30 */
    long long flags2nd;       /* 0x38 */
    struct MpegOut *sys;      /* 0x40 */
} MpegHandle;                 /* derived name */

void _ErrMessage(char *a0);
void _Error(char *a0);
void _Error1(int a0, int a1);
int _alalcAlloc(unsigned int *a0, int a1, unsigned int a2);
void _alalcFree(int *a0);
void _alalcInit(int *a0, int a1, int a2);
void _alalcSetDynamic(int *a0);
extern int _alternate_scan;
extern int _aspect_ratio_information;
extern int *_backBot;
extern int *_backFrame;
extern int *_backTop;
extern int _backward_f_code;
extern int _bit_rate_value;
extern int _broken_link;
extern int _bsDataSize;
extern int _bsDatap;
extern int _burst_amplitude;
extern int _cHeight;
extern int _cWidth;
extern int _chroma_420_type;
extern int _chroma_format;
void _clearEach(void);
void _clearOnce(void);
extern int _closed_gop;
extern int _color_description;
extern int _color_primaries;
extern int _composite_display_flag;
extern int _concealment_motion_vectors;
extern int _constrained_parameters_flag;
void _copyAddRefImage(void *a0, void *a1, void *a2);
void _copyRefImage(void *a0, void *a1);
extern int _copyright_flag;
extern int _copyright_identifier;
extern int _copyright_number_1;
extern int _copyright_number_2;
extern int _copyright_number_3;
void _cpr8(int *im);
void _csc_storeRefImage(int *p);
extern int *_curBot;
extern int *_curFrame;
extern int *_curTop;

int _decMB0(int *mb_type, int *motion_type, int *dct_type, int PMV[2][2][2], int mv_field_sel[2][2],
            int *dmvector);

int _decPicture(int a0, int a1);
int _decodeOrSkip(int a0, int a1, int a2);
int _decodeOrSkipField(int a0, int a1, int a2);
int _decodeOrSkipFrame(int a0, int a1, int a2);
void _decode_motion_vector(int *pred, int r_size, int motion_code, int motion_r, int full_pel);
void _defRestartDMA(int **a0);
void _defStopDMA(int **a0);
void *_dispatchMpegCallback(void *a0, void *a1);
void _dispatchMpegCbNodata(void *a0);
extern unsigned char _defIQM[64];
extern unsigned char _defNIQM[64];
extern int _display_horizontal_size;
extern int _display_vertical_size;
void _doCSC2(int a0, int a1);
void _doMC(int a0);
extern int _drop_frame_flag;
void _dispRefImage(int *img, int a1);
void _dispRefImageField(int *top, int *bot, int a2);
void _dualPrimeVector(int *DMV, int *dmvector, int mvx, int mvy);
void _extensionAndUserData(void);
void _extrainfo(void);
extern int _f_code[2][2];
extern int _field_sequence;
void _flushBuf(int a0);

void _getAllRefs(int x, int y, int mbflags, int motion_type, int *PMV, int *mv_field_sel,
                 int *dmvector);

extern int *_forwBot;
extern int *_forwFrame;
extern int *_forwTop;
extern int _forward_f_code;
extern int _frame_center_horizontal_offset[];
extern int _frame_center_vertical_offset[];
extern int _frame_pred_frame_dct;
extern int _frame_rate_code;
extern int _frame_rate_extension_d;
extern int _frame_rate_extension_n;
extern int _full_pel_backward_vector;
extern int _full_pel_forward_vector;
void _getPtsDtsFlags(int *img, void *a1, void *a2, void *a3);
int _getpic(int a0);

void _getRef0(int *img, int lineOff, int predIdx, int yoff, int h, int x, int y, int mvx, int mvy,
              int fld, int avg);

void _groupOfPicturesHeader(void);
extern long long _headerDts;
extern long long _headerPts;
extern int _heightMB;
extern int _horizontal_size;

void _initRefImages(int *frame0, int *frame1, int *frame2, int *top0, int *top1, int *top2,
                    int *bot0, int *bot1, int *bot2, int y, int cb, int cr);

void _initSeq(void *a0);
void _initSeqAgain(void);
extern int _isError;
extern int _isMpeg2;
extern int _isOutputPicture;
extern int _isSecondField;
extern int _isTop32dirty;
extern int _intra_dc_precision;
extern int _intra_slice;
extern int _intra_vlc_format;
void _ipuSetMPEG1(int a0);
int _ipuVdec(int tbl);
int _isOutSizeOK(int *p);
void _lastFrame(int a0);
extern int _load_intra_quantizer_matrix;
extern int _load_non_intra_quantizer_matrix;
extern int _low_delay;
int _markOutput(void);
extern int _matrix_coefficients;
extern int _maxval;
int _mbAddressIncrement(void);

/* one reference's copy descriptor, the argument a lumaCopy or chromaCopy
 * routine takes: where the prediction goes, the horizontal fraction, the rows
 * read from the first and the second source block, the source row step and
 * the two source blocks (the second is the next block down) */
typedef struct { /* derived name */
    void *dst;   /* 0x00 */
    int xoff;    /* 0x04 */
    int rows0;   /* 0x08 */
    int rows1;   /* 0x0C */
    int stride;  /* 0x10 */
    void *src0;  /* 0x14 */
    void *src1;  /* 0x18 */
} MCRefDesc;

/* one macroblock's motion-compensation record, 0x140 bytes: _motionComp0 sets
 * the flags and the destination, _getRef0 appends one reference per call
 * (the two source addresses DMA'd into refBuf, the copy routines and their
 * descriptors), _decMB0 has the IPU write its output (the intra block or the
 * residual) into ipuBuf and _doMC finishes it.  Every field name is ours. */
typedef struct {           /* derived name */
    int refBuf;            /* 0x000 scratchpad area the references land in */
    int ipuBuf;            /* 0x004 scratchpad area the IPU writes into */
    void *srcAddr[2][4];   /* 0x008 */
    void (*lumaFn[4])();   /* 0x028 */
    void (*chromaFn[4])(); /* 0x038 */
    MCRefDesc luma[4];     /* 0x048 */
    MCRefDesc chroma[4];   /* 0x0B8 */
    void *dst;             /* 0x128 */
    int count;             /* 0x12C */
    int intra;             /* 0x130 */
    int coded;             /* 0x134 */
    int busy;              /* 0x138 the reference DMA is under way */
    int skip;              /* 0x13C no residual: the prediction is the block */
} MCRecord;

/* var.o's _mbcont, as var.c defines it and mpc.c declares it: two records,
 * double-buffered (one is filled while the other is finished), and the
 * index of the current one.  init.c declares its own view. */
typedef struct {     /* derived name */
    MCRecord rec[2]; /* 0x000 */
    int cur;         /* 0x280 */
    int aux;         /* 0x284 zeroed beside cur, read by no member */
} MCState;

int _motionComp0(int a0, int a1, int a2, int a3, int *PMV, int *mv_field_sel, int *dmvector);

void _motionVector(int *PMV, int *dmvector, int h_r_size, int v_r_size, int dmv, int mvscale,
                   int full_pel);

void _motionVectors(int PMV[2][2][2], int *dmvector, int mv_field_sel[2][2], int s, int mv_count,
                    int mv_format, int h_r_size, int v_r_size, int dmv, int mvscale);

unsigned int _nextBit(int a0);
int _nextHeader(void);
void _nextStartCode(void);
extern int _original_or_copy;
void _outputFrame(int a0, int a1);
int _peepBit(int a0);
extern int _picHeight;
extern int _picWidth;
int _pictureData0(int a0);
void _pictureHeader(void);
void _pictureSpatialScalableExtension(void);
void _pictureTemporalScalableExtension(void);
extern int _picture_coding_type;
extern int _picture_structure;
extern int _profile_and_level_indication;
extern int _progressive_frame;
extern int _progressive_sequence;
extern int _q_scale_type;
extern int _qscqsc;
extern int _refBlockp;
extern int _refBot0[];
extern int _refBot1[];
extern int _refBot2[];
extern int _refFrame0[];
extern int _refFrame1[];
extern int _refFrame2[];
extern int _refTop0[];
extern int _refTop1[];
extern int _refTop2[];
extern int _repeat_first_field;
int _sceMpegFlush(int *self);
void _sendDataToIPU(int a0, int a1);
void _sendIpuCommand(unsigned int a0);
void _sequenceDisplayExtension(void);
void _sequenceExtension(void);
void _sequenceHeader(void);
void _sequenceScalableExtension(void);
void _setDefaultQM(int cmd, unsigned char *qm);
int _skipMB0(int *PMV, int *motion_type, int *mv_field_sel, int *mb_type);
int _slice0(int a0, int a1);
int _sliceA0(int a0, int *a1, int *a2, int *a3);
int _sliceB(void);
extern int _sp_dcr;
extern int _sprtag;
extern int _sub_carrier;
extern int _sub_carrier_phase;
int _sysbitGet(int *self, int a1);
void _sysbitInit(int *a0, int a1, int a2, int a3);
void _sysbitJump(int *a0, int a1);
int _sysbitMarker(int *self);
int _sysbitNext(void *a0, int a1);
int _sysbitPtr(int *a0, int a1);
extern int _temporal_reference;
extern MpegHandle *_theSceMpeg;
extern int _time_code_hours;
extern int _time_code_minutes;
extern int _time_code_pictures;
extern int _time_code_seconds;
extern int _top32;
extern int _top32len;
extern int _top_field_first;
extern int _totalFrames;
extern int _trFrameNumber;
extern int _transfer_characteristics;
long long _type2id(int a0, int a1);
void _unknown_extension(void);
int _updateRefImage(int a0);
void _updateTempTackData(void);
extern int _v_axis;
extern int _vbv_buffer_size_value;
extern int _vbv_delay;
extern int _vertical_size;
extern int _video_format;
extern int _widthMB;
int _waitBdecOut(void);
void _waitIpuIdle(void);
long long _waitIpuIdle64(void);
extern int *_zBot;
extern int *_zFrame;
extern int *_zTop;

#endif /* SCE_LIBMPEG_LIBMPEG_INTERNAL_H */
