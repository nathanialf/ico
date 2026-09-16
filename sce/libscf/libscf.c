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

/* The strings this member emits.  The developer wrote them as literals at the
 * use sites; the compiler interns each one on first use, which is what fixes
 * the ROM's .rodata order (the month-length template lands between the two
 * assert groups because adddate precedes AdjustTime).  ROM VMA 0x6371D0:
 *   0x6371D0  rom0:ROMVER                     GetRomName
 *   0x6371E0  Can't open rom0:ROMVER          GetRomName
 *   0x6371F8  Can't read rom error            GetRomName
 *   0x637210  Timezone=%d                     sceScfGetTimeZone
 *   0x637220  DateNotation=%d                 sceScfGetDateNotation
 *   0x637238  SummerTime=%d                   sceScfGetSummerTime
 *   0x637248  TimeNotation=%d                 sceScfGetTimeNotation
 *   0x637260  libscf.c                        __FILE__, first used by tobcd
 *   0x637270  c <=99                          tobcd
 *   0x637278  c <= 0x99                       frombcd
 *   0x637288  prtc != NULL                    convertfrombcd
 *   0x637298  the twelve month lengths        adddate, shared with subdate
 *   0x6372A8  -60*24<=diff && diff <= 60*24   AdjustTime
 * (the five printf strings and the two rom0 diagnostics each end in a newline
 * escape, dropped from the table above so the table stays one line per entry).
 * libscf.c is __FILE__, so the member is compiled from inside its own
 * directory by its bare name, and every assert string is the stringified
 * expression, so the three-argument calls are the newlib assert macro and
 * their line arguments (0x119 for the first, 0x1C7 for the last) fix this
 * file's line layout.  Evidence rung: ROM bytes. */

/* newlib <assert.h> and <stddef.h>, reconstructed here because the repo's
 * include/ carries stub scaffolding only.  NDEBUG is not defined in this
 * archive: the calls are in the shipped code.  The layout pass keeps the
 * two defines together. */
#define assert(e) ((e) ? (void)0 : __assert(__FILE__, __LINE__, #e))
/* <stddef.h> */
#define NULL 0

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
        fd = sceOpen("rom0:ROMVER", 1);
        if (fd == -1) {
            printf("Can't open rom0:ROMVER\n");
        }
        if (sceRead(fd, D_0054CB68, 14) == -1) {
            printf("Can't read rom error\n");
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
            printf("Timezone=%d\n", tz);
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
            printf("DateNotation=%d\n", v);
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
            printf("SummerTime=%d\n", v);
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
            printf("TimeNotation=%d\n", v);
        }
    }
    return v;
}

/* #e stringifies the expression exactly as it is spelled, so the spacing of
 * this file's first assert and of AdjustTime's range assert is load-bearing
 * (assert is a whitespace-sensitive macro for the formatter), and the ROM's
 * __LINE__ arguments pin every assert to its line the comment blocks keep. */

unsigned char tobcd(unsigned char c)
{
    assert(c <=99);
    return (c / 10) * 6 + c;
}

/* frombcd, the inverse, lands on the ROM's next assert line. */
/* The correction term is its own byte-wide local: with the product written
 * straight into the subtraction the r5900 three-operand mult3 takes it, and
 * the ROM has the two-operand mult with a separate mflo (tobcd takes mult3,
 * its product feeding an addu).  Evidence rung: ROM bytes. */
unsigned char frombcd(unsigned char c)
{
    unsigned char t;

    assert(c <= 0x99);
    t = (c >> 4) * 6;
    return c - t;
}

/* The six packed-BCD fields libcdvd fills in a sceCdCLOCK record, widened to
 * plain binary in place.  The stat and pad bytes are left alone.  The order
 * of the six is the ROM's, year first and second last (evidence rung: ROM
 * bytes); the walk is written out rather than looped because the members are
 * named, which is what the ROM's six calls show. */
void convertfrombcd(sceCdCLOCK *prtc)
{
    assert(prtc != NULL);
    prtc->year = frombcd(prtc->year);
    prtc->month = frombcd(prtc->month);
    prtc->day = frombcd(prtc->day);
    prtc->hour = frombcd(prtc->hour);
    prtc->minute = frombcd(prtc->minute);
    prtc->second = frombcd(prtc->second);
}

/* The inverse, over the same six fields in the same order: the record goes
 * back to the packed form the RTC hardware and libcdvd use, which is the
 * form AdjustTime hands out and the form sceScfGetGMTfromRTC's caller was
 * given it in. */
void converttobcd(sceCdCLOCK *prtc)
{
    assert(prtc != NULL);
    prtc->year = tobcd(prtc->year);
    prtc->month = tobcd(prtc->month);
    prtc->day = tobcd(prtc->day);
    prtc->hour = tobcd(prtc->hour);
    prtc->minute = tobcd(prtc->minute);
    prtc->second = tobcd(prtc->second);
}

/* adddate and subdate each copy the month-length template onto the stack so
 * the February entry can be patched for a leap year. */
void adddate(sceCdCLOCK *prtc)
{
    char mtab[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    assert(prtc != NULL);
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

/* The two-digit year wraps at 99 in both directions: the record carries no
 * century field. */
void subdate(sceCdCLOCK *prtc)
{
    char mtab[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    assert(prtc != NULL);
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

/* The hour carry.  addhour and subhour are the only callers of adddate and
 * subdate, and AdjustTime is the only caller of these two: the minute offset
 * a time zone or a summer-time shift asks for is applied by repeated
 * one-hour steps rather than by a calendar computation, which is why that
 * function asserts its argument range. */
void addhour(sceCdCLOCK *prtc)
{
    assert(prtc != NULL);
    if (++prtc->hour == 24) {
        prtc->hour = 0;
        adddate(prtc);
    }
}

/* The hour borrow.  The zero test comes first so the decrement never runs
 * on an hour of zero, which would wrap the unsigned field to 255 before
 * subdate could pull the day back; the else arm is therefore the ordinary
 * case and the day walk the exception. */
void subhour(sceCdCLOCK *prtc)
{
    assert(prtc != NULL);
    if (prtc->hour == 0) {
        prtc->hour = 23;
        subdate(prtc);
    } else {
        prtc->hour--;
    }
}

/* Shift a packed-BCD RTC record by diff minutes: widen it to binary, give
 * the minute field the whole offset, carry the overflow out an hour at a
 * time, pack it again.  The bound asserted is the sixty hours either side a
 * time zone plus a summer-time hour can reach. */
/* AdjustTime's range assert sits on line 0x1A1, the ROM's argument. */
void AdjustTime(sceCdCLOCK *prtc, int diff)
{
    int min;

    assert(prtc != NULL);
    assert(-60*24<=diff && diff <= 60*24);
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

/* The two public entry points follow. */
/* The two public entry points.  The RTC the CD-ROM drive keeps runs on Japan
 * Standard Time whatever the console's region, so GMT is nine hours behind it
 * and the local time is the OSD's time zone plus its summer-time flag away
 * from GMT.  540 is those nine hours in minutes, spelled out at both sites
 * rather than shared, which is what the ROM's two immediates show (evidence
 * rung: ROM bytes); the local entry reaches the OSD by this file's getters. */
void sceScfGetGMTfromRTC(sceCdCLOCK *prtc)
{
    assert(prtc != NULL);
    AdjustTime(prtc, -540);
}

void sceScfGetLocalTimefromRTC(sceCdCLOCK *prtc)
{
    int diff, adj;

    diff = sceScfGetTimeZone();
    adj = sceScfGetSummerTime() * 60 - 540;
    diff += adj;
    assert(prtc != NULL);
    AdjustTime(prtc, diff);
}
