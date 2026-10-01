/* Vendor SCE library member: libmpeg.a(var.o).  No code: the decoder state
 * every other member reads, MAIN.MAP .data 0x8C4 (122 globals, lines 6118 to
 * 6241), VMA 0x54C100..0x54C9C4.  The names are the map's; they follow the
 * public MPEG-2 reference decoder's globals (mpeg2decode's global.h), which
 * also gives frame_center_*_offset[3] and f_code[2][2].  Every object is
 * initialised, zero included, which keeps it in .data under ee-gcc 2.9.  The
 * default intra matrix is 64-byte aligned for its DMA to the IPU, which is
 * what starts the member 64-aligned after init.o's .data. */
#include <eeregs.h>
#include <libmpeg_internal.h>

int *_forwFrame = _refFrame0;

int *_backFrame = _refFrame1;

int *_zFrame = _refFrame2;

int *_forwTop = _refTop0;

int *_backTop = _refTop1;

int *_zTop = _refTop2;

int *_forwBot = _refBot0;

int *_backBot = _refBot1;

int *_zBot = _refBot2;

int _isTop32dirty = 1;

int _tmp_flag = 0;

volatile unsigned int *_ipucmd = (volatile unsigned int *)IPU_CMD;

volatile unsigned int *_ipuctrl = (volatile unsigned int *)IPU_CTRL;

volatile unsigned int *_ipubp = (volatile unsigned int *)IPU_BP;

volatile unsigned int *_iputop = (volatile unsigned int *)IPU_TOP;

volatile unsigned int *_d4tadr = (volatile unsigned int *)D4_TADR;

volatile unsigned int *_d4madr = (volatile unsigned int *)D4_MADR;

volatile unsigned int *_d4chcr = (volatile unsigned int *)D4_CHCR;

volatile unsigned int *_d4qwc = (volatile unsigned int *)D4_QWC;

volatile unsigned int *_d3madr = (volatile unsigned int *)D3_MADR;

volatile unsigned int *_d3chcr = (volatile unsigned int *)D3_CHCR;

volatile unsigned int *_d3qwc = (volatile unsigned int *)D3_QWC;

/* the default intra matrix, which _setDefaultQM sends to the IPU by DMA
   channel 4; on its own 64-byte line */
unsigned char _defIQM[64] __attribute__((aligned(64))) = {
    8,  16, 16, 19, 16, 19, 22, 22, 22, 22, 22, 22, 26, 24, 26, 27, 27, 27, 26, 26, 26, 26,
    27, 27, 27, 29, 29, 29, 34, 34, 34, 29, 29, 29, 27, 27, 29, 29, 32, 32, 34, 34, 37, 38,
    37, 35, 35, 34, 35, 38, 38, 40, 40, 40, 48, 48, 46, 46, 56, 56, 58, 69, 69, 83};

unsigned char _defNIQM[64] = {16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
                              16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
                              16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16,
                              16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16};

int _bsDataSize = 0;

int _totalFrames = 0;

int _isError = 0;

int _picWidth = 0;

int _picHeight = 0;

int _cWidth = 0;

int _cHeight = 0;

int _isSecondField = 0;

int _horizontal_size = 0;

int _vertical_size = 0;

int _widthMB = 0;

int _heightMB = 0;

int _aspect_ratio_information = 0;

int _frame_rate_code = 0;

int _bit_rate_value = 0;

int _vbv_buffer_size_value = 0;

int _constrained_parameters_flag = 0;

int _profile_and_level_indication = 0;

int _progressive_sequence = 0;

int _chroma_format = 0;

int _low_delay = 0;

int _frame_rate_extension_n = 0;

int _frame_rate_extension_d = 0;

int _video_format = 0;

int _color_description = 0;

int _color_primaries = 0;

int _transfer_characteristics = 0;

int _matrix_coefficients = 0;

int _display_horizontal_size = 0;

int _display_vertical_size = 0;

int _temporal_reference = 0;

int _picture_coding_type = 0;

int _vbv_delay = 0;

int _full_pel_forward_vector = 0;

int _forward_f_code = 0;

int _full_pel_backward_vector = 0;

int _backward_f_code = 0;

int _f_code[2][2] = {{0, 0}, {0, 0}};

int _intra_dc_precision = 0;

int _picture_structure = 0;

int _top_field_first = 0;

int _frame_pred_frame_dct = 0;

int _concealment_motion_vectors = 0;

int _intra_vlc_format = 0;

int _repeat_first_field = 0;

int _chroma_420_type = 0;

int _progressive_frame = 0;

int _composite_display_flag = 0;

int _v_axis = 0;

int _field_sequence = 0;

int _sub_carrier = 0;

int _burst_amplitude = 0;

int _sub_carrier_phase = 0;

int _frame_center_horizontal_offset[3] = {0, 0, 0};

int _frame_center_vertical_offset[3] = {0, 0, 0};

int _copyright_flag = 0;

int _copyright_identifier = 0;

int _original_or_copy = 0;

int _copyright_number_1 = 0;

int _copyright_number_2 = 0;

int _copyright_number_3 = 0;

int _drop_frame_flag = 0;

int _time_code_hours = 0;

int _time_code_minutes = 0;

int _time_code_seconds = 0;

int _time_code_pictures = 0;

int _closed_gop = 0;

int _broken_link = 0;

int _trFrameNumber = 0;

int _sp_dcr = 0;

int _qscqsc = 0;

int *_curFrame = 0;

int *_curTop = 0;

int *_curBot = 0;

int _refFrame0[26] = {0};

int _refFrame1[26] = {0};

int _refFrame2[26] = {0};

int _refTop0[26] = {0};

int _refTop1[26] = {0};

int _refTop2[26] = {0};

int _refBot0[26] = {0};

int _refBot1[26] = {0};

int _refBot2[26] = {0};

MCState _mbcont = {0};

int _isOutputPicture = 0;

long long _headerPts = 0;

long long _headerDts = 0;

int _top32 = 0;

int _top32len = 0;

int _load_intra_quantizer_matrix = 0;

int _load_non_intra_quantizer_matrix = 0;

int _load_chroma_intra_quantizer_matrix = 0;

int _load_chroma_non_intra_quantizer_matrix = 0;

int _isMpeg2 = 0;

int _q_scale_type = 0;

int _alternate_scan = 0;

int _priority_breakpoint = 0;

int _intra_slice = 0;
