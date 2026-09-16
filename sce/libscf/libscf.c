/* Vendor SCE library run, attribution INFERRED: libscf.a.  Neither disc map names an
 * archive for these 21 functions (MAIN.MAP is an older link whose .text ends before
 * them; SRCFILE.TXT carries them with symbols but no source paths).  The sceScf
 * family is the public SDK's libscf, GetRomName and IsT10K feed
 * sceScfSetT10kConfig, and the BCD date helpers feed sceScfGetGMTfromRTC and
 * sceScfGetLocalTimefromRTC, so the run is treated as one library.  VMA
 * 0x272878..0x273228.  The FILE name is no longer inferred: the run's own
 * __assert file string is "libscf.c" at 0x637260 (evidence rung: ROM bytes);
 * only the archive it was linked from stays an inference. */
#include "common.h"

/* The T10K (DTL-T10000 development kit) OSD configuration shadow the
 * sceScfSet/Get pair reads.  In the 2001 source this is the file's own static;
 * here the record is still blob .data at VMA 0x54CB60..0x54CB68, so the TU
 * declares it extern with the size left open (the repo's spelling for a blob
 * symbol, as in sce/libgraph/graph001.c).  Field offsets are read off the ROM:
 * +0 short (lh), +2..+7 unsigned char (lbu).  Evidence rung: ROM bytes. */
typedef struct {
    short timezone;
    unsigned char aspect;
    unsigned char dateNotation;
    unsigned char language;
    unsigned char spdif;
    unsigned char summerTime;
    unsigned char timeNotation;
} sceScfT10KConfig;

extern sceScfT10KConfig D_0054CB60[];
/* The 16-byte rom0:ROMVER record GetRomName reads once and caches; blob .data
 * at VMA 0x54CB68.  Byte 4 is the region letter (T = DTL-T10000). */
extern char D_0054CB68[];

/* The OSD configuration word the kernel's GetOsdConfigParam syscall returns.
 * Every bit position below is read straight off the ROM's shift/mask pairs in
 * this file (evidence rung: ROM bytes); the field names follow the public
 * sceScfGet* entry points that read them. */
typedef struct {
    unsigned int spdif : 1;        /* bit 0     sceScfGetSpdif */
    unsigned int aspect : 2;       /* bits 1-2  sceScfGetAspect */
    unsigned int videoOutput : 1;  /* bit 3 */
    unsigned int japanese : 1;     /* bit 4     sceScfGetLanguage, version 0 */
    unsigned int ps1drvConfig : 8; /* bits 5-12 */
    unsigned int version : 3;      /* bits 13-15 */
    unsigned int language : 5;     /* bits 16-20 */
    int timezone : 11;             /* bits 21-31, signed: ROM reads it with sra */
} ConfigParam;

/* The second configuration record, read by GetOsdConfigParam2 with count 1 and
 * offset 1.  Only its first byte is touched here, and the ROM reads that byte
 * with lbu, so the three flags below sit in one storage unit. */
typedef struct {
    unsigned char reserved : 4;     /* bits 0-3 */
    unsigned char summerTime : 1;   /* bit 4    sceScfGetSummerTime */
    unsigned char timeNotation : 1; /* bit 5    sceScfGetTimeNotation */
    unsigned char dateNotation : 2; /* bits 6-7 sceScfGetDateNotation */
} ConfigParam2;

/* The rom0:ROMVER record and the assert strings this member keeps in the blob
 * .rodata run at 0x637260..0x6372C5; the TU reaches them by their splat names,
 * as sce/libgraph/graph008.c does for its own format string.
 *   0x6371D0  rom0:ROMVER
 *   0x6371E0  Can't open rom0:ROMVER\n
 *   0x6371F8  Can't read rom error\n
 *   0x637210  Timezone=%d\n
 *   0x637220  DateNotation=%d\n
 *   0x637238  SummerTime=%d\n
 *   0x637248  TimeNotation=%d\n
 *   0x637260  libscf.c
 *   0x637270  c <=99
 *   0x637278  c <= 0x99
 *   0x637288  prtc != NULL
 *   0x637298  the twelve month lengths adddate and subdate copy to the stack
 *   0x6372A8  -60*24<=diff && diff <= 60*24
 */
extern char D_006371D0[];
extern char D_006371E0[];
extern char D_006371F8[];
extern char D_00637210[];
extern char D_00637220[];
extern char D_00637238[];
extern char D_00637248[];
extern char D_00637260[];
extern char D_00637270[];
extern char D_00637278[];
extern char D_00637288[];
extern char D_006372A8[];

/* The RTC record libcdvd hands out: eight packed BCD bytes. */
typedef struct {
    unsigned char stat;
    unsigned char second;
    unsigned char minute;
    unsigned char hour;
    unsigned char pad;
    unsigned char day;
    unsigned char month;
    unsigned char year;
} sceCdCLOCK;

extern void __assert(char *file, int line, char *expr);
extern void printf(char *fmt, ...);
extern void AdjustTime(sceCdCLOCK *prtc, int diff);
extern void convertfrombcd(sceCdCLOCK *prtc);
extern void converttobcd(sceCdCLOCK *prtc);
extern void adddate(sceCdCLOCK *prtc);
extern void subdate(sceCdCLOCK *prtc);
extern void addhour(sceCdCLOCK *prtc);
extern void subhour(sceCdCLOCK *prtc);
extern unsigned char tobcd(unsigned char c);
extern unsigned char frombcd(unsigned char c);
extern int sceScfGetTimeZone(void);
extern int sceScfGetSummerTime(void);
extern int sceOpen(char *name, int flags);
extern int sceRead(int fd, void *buf, int size);
extern int sceClose(int fd);
extern char *GetRomName(void);
extern int IsT10K(void);
extern void GetOsdConfigParam(ConfigParam *param);
extern int GetOsdConfigParam2(ConfigParam2 *param, int count, int offset);

char *GetRomName(void)
{
    int fd;

    if (D_0054CB68[0] == 0) {
        fd = sceOpen(D_006371D0, 1);
        if (fd == -1) {
            printf(D_006371E0);
        }
        if (sceRead(fd, D_0054CB68, 14) == -1) {
            printf(D_006371F8);
        }
        sceClose(fd);
    }
    return D_0054CB68;
}

int IsT10K(void)
{
    if (D_0054CB68[0] == 0) {
        GetRomName();
    }
    return D_0054CB68[4] == 'T';
}

int sceScfGetLanguage(void)
{
    ConfigParam param;

    int lang;

    GetOsdConfigParam(&param);
    if (IsT10K()) {
        lang = D_0054CB60[0].language;
    } else {
        GetOsdConfigParam(&param);
        if (param.version == 0) {
            lang = param.japanese;
        } else {
            lang = param.language;
        }
    }
    return lang;
}

INCLUDE_ASM("asm/nonmatchings/sce/libscf/libscf", sceScfSetT10kConfig);

int sceScfGetAspect(void)
{
    ConfigParam param;

    if (IsT10K()) {
        return D_0054CB60[0].aspect;
    }
    GetOsdConfigParam(&param);
    return param.aspect;
}

int sceScfGetSpdif(void)
{
    ConfigParam param;

    if (IsT10K()) {
        return D_0054CB60[0].spdif;
    }
    GetOsdConfigParam(&param);
    return param.spdif;
}

int sceScfGetTimeZone(void)
{
    ConfigParam param;
    int tz;

    if (IsT10K()) {
        tz = D_0054CB60[0].timezone;
    } else {
        tz = 540;
        GetOsdConfigParam(&param);
        if (param.version != 0) {
            tz = param.timezone;
            printf(D_00637210, tz);
        }
    }
    return tz;
}

int sceScfGetDateNotation(void)
{
    ConfigParam param;
    ConfigParam2 param2;
    int v;

    if (IsT10K()) {
        v = D_0054CB60[0].dateNotation;
    } else {
        GetOsdConfigParam(&param);
        if (param.version == 0) {
            v = 0;
        } else {
            GetOsdConfigParam2(&param2, 1, 1);
            v = param2.dateNotation;
            printf(D_00637220, v);
        }
    }
    return v;
}

int sceScfGetSummerTime(void)
{
    ConfigParam param;
    ConfigParam2 param2;
    int v;

    if (IsT10K()) {
        v = D_0054CB60[0].summerTime;
    } else {
        GetOsdConfigParam(&param);
        if (param.version == 0) {
            v = 0;
        } else {
            GetOsdConfigParam2(&param2, 1, 1);
            v = param2.summerTime;
            printf(D_00637238, v);
        }
    }
    return v;
}

int sceScfGetTimeNotation(void)
{
    ConfigParam param;
    ConfigParam2 param2;
    int v;

    if (IsT10K()) {
        v = D_0054CB60[0].timeNotation;
    } else {
        GetOsdConfigParam(&param);
        if (param.version == 0) {
            v = 0;
        } else {
            GetOsdConfigParam2(&param2, 1, 1);
            v = param2.timeNotation;
            printf(D_00637248, v);
        }
    }
    return v;
}

unsigned char tobcd(unsigned char c)
{
    if (!(c <= 99)) {
        __assert(D_00637260, 0x119, D_00637270);
    }
    return (c / 10) * 6 + c;
}

unsigned char frombcd(unsigned char c)
{
    /* The correction term is its own byte-wide local: with the product written
     * straight into the subtraction the r5900 three-operand mult3 takes it, and
     * the ROM has the two-operand mult with a separate mflo (evidence rung: ROM
     * bytes; tobcd, whose product feeds an addu, does take mult3). */
    unsigned char t;

    if (!(c <= 0x99)) {
        __assert(D_00637260, 0x126, D_00637278);
    }
    t = (c >> 4) * 6;
    return c - t;
}

void convertfrombcd(sceCdCLOCK *prtc)
{
    if (prtc == 0) {
        __assert(D_00637260, 0x132, D_00637288);
    }
    prtc->year = frombcd(prtc->year);
    prtc->month = frombcd(prtc->month);
    prtc->day = frombcd(prtc->day);
    prtc->hour = frombcd(prtc->hour);
    prtc->minute = frombcd(prtc->minute);
    prtc->second = frombcd(prtc->second);
}

void converttobcd(sceCdCLOCK *prtc)
{
    if (prtc == 0) {
        __assert(D_00637260, 0x141, D_00637288);
    }
    prtc->year = tobcd(prtc->year);
    prtc->month = tobcd(prtc->month);
    prtc->day = tobcd(prtc->day);
    prtc->hour = tobcd(prtc->hour);
    prtc->minute = tobcd(prtc->minute);
    prtc->second = tobcd(prtc->second);
}

/* adddate and subdate each copy the month-length template onto the stack so the
 * February entry can be patched for a leap year.  The template is the TU's only
 * emitted data: 12 bytes of .rodata, ROM VMA 0x637298..0x6372A4. */
void adddate(sceCdCLOCK *prtc)
{
    char mtab[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (prtc == 0) {
        __assert(D_00637260, 0x150, D_00637288);
    }
    prtc->day++;
    if ((prtc->year % 4) == 0) {
        mtab[1] = 29;
    }
    if (mtab[prtc->month - 1] < prtc->day) {
        prtc->day = 1;
        if (++prtc->month == 13) {
            if (prtc->year == 99) {
                prtc->year = 0;
            } else {
                prtc->year++;
            }
            prtc->month = 1;
        }
    }
}

void subdate(sceCdCLOCK *prtc)
{
    char mtab[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (prtc == 0) {
        __assert(D_00637260, 0x168, D_00637288);
    }
    prtc->day--;
    if ((prtc->year % 4) == 0) {
        mtab[1] = 29;
    }
    if (prtc->day == 0) {
        if (--prtc->month == 0) {
            if (prtc->year == 0) {
                prtc->year = 99;
            } else {
                prtc->year--;
            }
            prtc->month = 12;
        }
        prtc->day = mtab[prtc->month - 1];
    }
}

void addhour(sceCdCLOCK *prtc)
{
    if (prtc == 0) {
        __assert(D_00637260, 0x181, D_00637288);
    }
    if (++prtc->hour == 24) {
        prtc->hour = 0;
        adddate(prtc);
    }
}

void subhour(sceCdCLOCK *prtc)
{
    if (prtc == 0) {
        __assert(D_00637260, 0x18E, D_00637288);
    }
    if (prtc->hour == 0) {
        prtc->hour = 23;
        subdate(prtc);
    } else {
        prtc->hour--;
    }
}

void AdjustTime(sceCdCLOCK *prtc, int diff)
{
    int min;

    if (prtc == 0) {
        __assert(D_00637260, 0x1A0, D_00637288);
    }
    if (!(-60 * 24 <= diff && diff <= 60 * 24)) {
        __assert(D_00637260, 0x1A1, D_006372A8);
    }
    convertfrombcd(prtc);
    min = prtc->minute + diff;
    if (min >= 0) {
        while (min > 60) {
            min -= 60;
            addhour(prtc);
        }
    } else {
        do {
            min += 60;
            subhour(prtc);
        } while (min < 0);
    }
    prtc->minute = min;
    converttobcd(prtc);
}

void sceScfGetGMTfromRTC(sceCdCLOCK *prtc)
{
    if (prtc == 0) {
        __assert(D_00637260, 0x1BC, D_00637288);
    }
    AdjustTime(prtc, -540);
}

void sceScfGetLocalTimefromRTC(sceCdCLOCK *prtc)
{
    int diff;
    int adj;

    diff = sceScfGetTimeZone();
    adj = sceScfGetSummerTime() * 60 - 540;
    diff += adj;
    if (prtc == 0) {
        __assert(D_00637260, 0x1C7, D_00637288);
    }
    AdjustTime(prtc, diff);
}
