/* Vendor SCE library member: libmpeg.a(pack.o).  MAIN.MAP's member size (0xDD8)
 * tiles the retail run exactly, VMA 0x26A630..0x26B408, 8 functions: the PSS
 * demultiplexer and its pack, system and PES header parsers. */
#include <libmpeg.h>
#include <libmpeg_internal.h>

typedef struct {
    int unk0, unk4, unk8, unkC;
} P24D418;

/* the ten PSS stream descriptors: the id template of the stream and the mask
 * of the bits its stream number occupies */
typedef struct {
    unsigned long long id;
    unsigned long long mask;
} StrDesc;

static StrDesc streamDesc[10] /* derived name */ = {
    {0xE000000000ULL, 0xFF00000000ULL}, {0xBDFFC00000ULL, 0xFFFFFFFFFFULL},
    {0xBDFFA00000ULL, 0xFFFFFFFFFFULL}, {0xBDFFA10000ULL, 0xFFFFFFFFFFULL},
    {0xBDFF900000ULL, 0xFFFFFFFFFFULL}, {0xC000000000ULL, 0xFF00000000ULL},
    {0xBD80000000ULL, 0xFFFF000000ULL}, {0xBDA0000000ULL, 0xFFFF000000ULL},
    {0xBD88000000ULL, 0xFFFF000000ULL}, {0xBD90000000ULL, 0xFFFF000000ULL},
};

long long _type2id(int a0, int a1)
{
    long long id = 0;
    int sh = 0;

    if ((unsigned int)a0 < 10) {
        switch (streamDesc[a0].mask) {
        case 0xFFFFFFFFFFULL:
            sh = 0;
            break;
        case 0xFFFF000000ULL:
            sh = 24;
            break;
        case 0xFF00000000ULL:
            sh = 32;
            break;
        }
        id = streamDesc[a0].id | ((long long)a1 << sh);
    }
    return id;
}

int _id2type(int *type, int *num, unsigned long long id)
{
    StrDesc *p = streamDesc;
    unsigned int i;
    int found = 0;

    for (i = 0; i < 10 && found == 0; i++) {
        unsigned long long m = p->mask;
        unsigned long long k;

        switch (m) {
        case 0xFFFFFFFFFFULL:
            m = id & 0xFFFFFF0000ULL;
            if (m == p->id) {
                *type = i;
                *num = id & 0xFFFF;
                found = 1;
            }
            break;
        case 0xFFFF000000ULL:
            switch (p->id) {
            case 0xBD20000000ULL:
                m = id & 0xFFE0000000ULL;
                k = 0x1F;
                break;
            case 0xBD80000000ULL:
            case 0xBD88000000ULL:
            case 0xBD90000000ULL:
            case 0xBDA0000000ULL:
                m = id & 0xFFF8000000ULL;
                k = 7;
                break;
            default:
                m = id & 0xFFFF000000ULL;
                k = 0;
                break;
            }
            if (m == p->id) {
                *type = i;
                *num = (id >> 24) & k;
                found = 1;
            }
            break;
        case 0xFF00000000ULL:
            if (p->id == 0xE000000000ULL) {
                m = id & 0xF000000000ULL;
                k = 0xF;
            } else if (p->id == 0xC000000000ULL) {
                m = id & 0xE000000000ULL;
                k = 0x1F;
            } else {
                m = id & m;
                k = 0;
            }
            if (m == p->id) {
                *type = i;
                *num = (id >> 32) & k;
                found = 1;
            }
            break;
        }
        p++;
    }
    return found;
}

/* one PES packet header: the 64-bit stream id the demux matches against, the
 * packet and payload lengths, the two timestamps and the bit positions the
 * ring buffer is rewound to */
typedef struct {
    long long id;
    int length;
    int scramble;
    long long pts;
    long long dts;
    int pos;
    int datalen;
    int startpos;
} PesPkt;

/* the packet the demuxer walks: the pack header _pack_header fills, then the
 * PES packet header _PES_packet fills */
typedef struct {
    P24D418 pack;
    int unk10;
    int unk14;
    PesPkt pes;
    int unk48;
    int unk4C;
} PssPkt;

/* the kinds of callback the decoder makes; a demuxed stream packet is the last */
typedef enum {
    MPEG_CB_ERROR,
    MPEG_CB_NODATA,
    MPEG_CB_STOPDMA,
    MPEG_CB_RESTARTDMA,
    MPEG_CB_BACKGROUND,
    MPEG_CB_TIMESTAMP,
    MPEG_CB_STR
} MpegCbType;

/* what a stream callback is handed (sceMpegCbDataStr): the callback type, the
 * ring addresses of the packet header and payload, the payload length and the
 * two time stamps */
typedef struct {
    MpegCbType type;
    unsigned char *header;
    unsigned char *data;
    unsigned int len;
    long long pts;
    long long dts;
} DemuxRec;

/* a stream callback: the decoder, the packet record and the user argument */
typedef int (*MpegStrCallback)(int *dec, DemuxRec *cbdata, void *arg);

/* one demux callback: the stream id it matches, the mask of the id bits that
 * take part in the match, and the handler with its user argument */
typedef struct {
    long long id;
    unsigned long long mask;
    MpegStrCallback func;
    void *arg;
} StrCb;

/* kept local: its record type is this member's own */
extern int _pack_header(int *bs, P24D418 *pkt);
extern int _PES_packet(int *bs, PesPkt *pkt);

int sceMpegDemuxPssRing(int *dec, void *p4, int size, int a3, int a4)
{
    int bsbuf[12];
    PssPkt pktbuf;
    int *bs;
    PssPkt *pkt = &pktbuf;
    DemuxRec rec;
    int *p = (int *)dec[0x40 / 4];
    MpegStrCallback func = 0;
    void *arg = 0;
    StrCb *tbl = (StrCb *)p[0x44 / 4];
    int ret = 0;
    int i;
    int cont = 1;

    _sysbitInit(bsbuf, (int)p4, a3, a4);
    bs = bsbuf;
    i = 0;
    if (p[0x48 / 4] > 0) {
        do {
            if (tbl[i].id == 0xBDFF000000LL) {
                func = tbl[i].func;
                arg = tbl[i].arg;
            }
            if (func != 0) {
                break;
            }
            i++;
        } while (i < p[0x48 / 4]);
    }
    do {
        if (_sysbitNext(bs, 32) == 0x1BA) {
            _pack_header(bs, &pkt->pack);
        }
        while (_sysbitNext(bs, 24) == 1 && _sysbitNext(bs, 32) != 0x1BA &&
               _sysbitNext(bs, 32) != 0x1B9 && *(unsigned long long *)(bs + 6) < size * 8 &&
               cont != 0) {
            _PES_packet(bs, &pkt->pes);
            if (*(unsigned long long *)(bs + 6) > size * 8) {
                continue;
            }
            for (i = 0; i < p[0x48 / 4]; i++) {
                if (tbl[i].id == (pkt->pes.id & tbl[i].mask)) {
                    rec.type = MPEG_CB_STR;
                    rec.header = (unsigned char *)_sysbitPtr(bs, pkt->pes.startpos);
                    rec.data = (unsigned char *)_sysbitPtr(bs, pkt->pes.pos);
                    rec.len = pkt->pes.datalen;
                    rec.pts = pkt->pes.pts;
                    rec.dts = pkt->pes.dts;
                    cont = tbl[i].func(dec, &rec, tbl[i].arg);
                    break;
                }
            }
            if (i == p[0x48 / 4] && func != 0) {
                rec.type = MPEG_CB_STR;
                rec.header = (unsigned char *)_sysbitPtr(bs, pkt->pes.startpos);
                rec.data = (unsigned char *)_sysbitPtr(bs, pkt->pes.pos);
                rec.len = pkt->pes.datalen;
                rec.pts = pkt->pes.pts;
                rec.dts = pkt->pes.dts;
                cont = func(dec, &rec, arg);
            }
            if (cont != 0) {
                ret = (int)(*(unsigned long long *)(bs + 6) >> 3);
            }
        }
        if (size * 8 < *(unsigned long long *)(bs + 6)) {
            break;
        }
    } while (_sysbitNext(bs, 32) == 0x1BA);
    return ret;
}

int sceMpegDemuxPss(void *a0, int a1, int a2)
{
    return sceMpegDemuxPssRing(a0, a1, a2, 0, -1);
}

int sceMpegAddStrCallback(int *a0, int a1, int a2, MpegStrCallback a3, void *a4)
{
    int ret = 0;
    int *p = (int *)a0[0x40 / 4];
    StrCb *tbl = (StrCb *)p[0x44 / 4];
    long long id = _type2id(a1, a2);
    int n = p[0x48 / 4];
    int i;

    for (i = 0; i < n; i++) {
        if (id == tbl[i].id) {
            ret = (int)tbl[i].func;
            break;
        }
    }
    if (i < 0x40) {
        p[0x48 / 4] = n + 1;
        tbl[i].id = id;
        tbl[i].arg = a4;
        tbl[i].func = a3;
        tbl[i].mask = streamDesc[a1].mask;
    }
    return ret;
}

/* kept local: libmpeg_internal.h leaves it out: its callers' arguments do not fit the
   definition's prototype */
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

/* the bit count each combination of the four header flags adds */
static unsigned char headerBits[16] /* derived name */ = {
    0, 16, 8, 24, 8, 24, 16, 32, 24, 40, 32, 48, 32, 48, 40, 56,
};

int _PES_packet(int *bs, PesPkt *pkt)
{
    int ptsdts;
    int escr;
    int flags;
    int ext;
    int hdrlen;
    int base;
    int n;
    int len;

    pkt->startpos = bs[6];
    _sysbitGet(bs, 0x18);
    pkt->id = (long long)_sysbitGet(bs, 8) << 32;
    pkt->length = _sysbitGet(bs, 0x10);
    pkt->pts = pkt->dts = -1;
    if (pkt->id != 0xBC00000000 && pkt->id != 0xBE00000000 && pkt->id != 0xBF00000000 &&
        pkt->id != 0xF000000000 && pkt->id != 0xF100000000 && pkt->id != 0xFF00000000 &&
        pkt->id != 0xF200000000 && pkt->id != 0xF800000000) {
        _sysbitGet(bs, 2);
        pkt->scramble = _sysbitGet(bs, 2);
        _sysbitGet(bs, 4);
        ptsdts = _sysbitGet(bs, 2);
        escr = _sysbitGet(bs, 1);
        flags = _sysbitGet(bs, 4);
        ext = _sysbitGet(bs, 1);
        hdrlen = _sysbitGet(bs, 8);
        base = (int)*(long long *)(bs + 6);
        if (ptsdts & 2) {
            unsigned int a;
            int b;
            int c;
            unsigned int low;

            _sysbitGet(bs, 4);
            a = _sysbitGet(bs, 3);
            _sysbitMarker(bs);
            b = _sysbitGet(bs, 0xF);
            _sysbitMarker(bs);
            c = _sysbitGet(bs, 0xF);
            _sysbitMarker(bs);
            low = (a << 30) | (b << 15) | c;
            pkt->pts = ((long long)((a >> 2) & 1) << 32) | low;
        }
        if (ptsdts == 3) {
            unsigned int a;
            int b;
            int c;
            unsigned int low;

            _sysbitGet(bs, 4);
            a = _sysbitGet(bs, 3);
            _sysbitMarker(bs);
            b = _sysbitGet(bs, 0xF);
            _sysbitMarker(bs);
            c = _sysbitGet(bs, 0xF);
            _sysbitMarker(bs);
            low = (a << 30) | (b << 15) | c;
            pkt->dts = ((long long)((a >> 2) & 1) << 32) | low;
        }
        if (escr == 1) {
            _sysbitGet(bs, 0x30);
        }
        if (flags != 0) {
            _sysbitGet(bs, headerBits[flags]);
        }
        if (ext == 1) {
            int priv;
            int pack;
            int seq;
            int pstd;
            int ext2;
            unsigned int i;
            unsigned int cnt;

            priv = _sysbitGet(bs, 1);
            pack = _sysbitGet(bs, 1);
            seq = _sysbitGet(bs, 1);
            pstd = _sysbitGet(bs, 1);
            _sysbitGet(bs, 3);
            ext2 = _sysbitGet(bs, 1);
            if (priv == 1) {
                _sysbitGet(bs, 0x30);
                _sysbitGet(bs, 0x30);
                _sysbitGet(bs, 0x20);
            }
            if (pack == 1) {
                _Error("pack_header_field_flag needs to be '0' in PS\n");
                return 0;
            }
            if (seq == 1) {
                _sysbitGet(bs, 0x10);
            }
            if (pstd == 1) {
                _sysbitGet(bs, 0x10);
            }
            if (ext2 == 1) {
                _sysbitMarker(bs);
                cnt = _sysbitGet(bs, 7);
                for (i = 0; i < cnt; i++) {
                    _sysbitGet(bs, 8);
                }
            }
        }
        n = hdrlen - (int)((*(long long *)(bs + 6) - base) >> 3);
        if (n != 0) {
            _sysbitJump(bs, n);
        }
        len = pkt->length - hdrlen;
        n = len - 3;
        pkt->datalen = n;
        pkt->pos = bs[6];
        if (pkt->id == 0xBD00000000) {
            pkt->id = pkt->id | (unsigned int)_sysbitGet(bs, 0x20);
            n = len - 7;
        }
        if (n != 0) {
            _sysbitJump(bs, n);
        }
    } else if (pkt->id == 0xBC00000000 || pkt->id == 0xBF00000000 || pkt->id == 0xF000000000 ||
               pkt->id == 0xF100000000 || pkt->id == 0xFF00000000 || pkt->id == 0xF200000000 ||
               pkt->id == 0xF800000000) {
        len = pkt->length;
        if (pkt->id == 0xBF00000000) {
            len = len - 4;
            pkt->id = pkt->id | (unsigned int)_sysbitGet(bs, 0x20);
        }
        if (len != 0) {
            _sysbitJump(bs, len);
        }
    } else if (pkt->id == 0xBE00000000) {
        n = pkt->length;
        if (n != 0) {
            _sysbitJump(bs, n);
        }
    }
    return 1;
}
