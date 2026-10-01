/* libscf.a.  The archive name is inferred: neither the member nor its source
 * path is named for these 21 functions.  The sceScf family is the public SDK's
 * libscf, GetRomName and IsT10K feed sceScfSetT10kConfig, and the BCD date
 * helpers feed the RTC readers, so the run is one library.
 *
 * The file name is the run's own __assert string "libscf.c", and the asserts
 * carry __LINE__ (tobcd's is 281), so the line layout above them is fixed:
 * a line added or removed anywhere above an assert moves its line constant;
 * a comment that changes is rewritten in place, keeping its line count.
 */
#include <stdio.h>
#include <libscf.h>
#include <sifdev.h>

/* The member's .data: the build stamp, the T10K (DTL-T10000 kit) OSD
 * config shadow (timezone 540 minutes, JST) and the rom0:ROMVER cache GetRomName fills. */
typedef struct {
    short timezone;
    unsigned char aspect;
    unsigned char dateNotation;
    unsigned char language;
    unsigned char spdif;
    unsigned char summerTime;
    unsigned char timeNotation;
} sceScfT10KConfig;

static char sceScfVersion[16] = "PsIIlibscf  2200"; /* derived name */

static sceScfT10KConfig t10kConfig = {540, 0, 0, 0, 0, 0, 0}; /* derived name */

static char romName[16] = {0}; /* derived name */

/* The OSD configuration word the kernel's GetOsdConfigParam syscall returns.
 * Every bit position below is the shift/mask pair this file's getters use;
 * the field names follow the public sceScfGet* entry points that read
 * them. */
typedef struct {
    unsigned int spdif : 1;        /* bit 0     sceScfGetSpdif */
    unsigned int aspect : 2;       /* bits 1-2  sceScfGetAspect */
    unsigned int videoOutput : 1;  /* bit 3 */
    unsigned int japanese : 1;     /* bit 4     sceScfGetLanguage, version 0 */
    unsigned int ps1drvConfig : 8; /* bits 5-12 */
    unsigned int version : 3;      /* bits 13-15 */
    unsigned int language : 5;     /* bits 16-20 */
    int timezone : 11;             /* bits 21-31, signed */
} ConfigParam;

/* The second configuration record, read by GetOsdConfigParam2 with count 1 and
 * offset 1.  Only its first byte is touched here, read as one unsigned byte,
 * so the three flags below sit in one storage unit. */
typedef struct {
    unsigned char reserved : 4;     /* bits 0-3 */
    unsigned char summerTime : 1;   /* bit 4    sceScfGetSummerTime */
    unsigned char timeNotation : 1; /* bit 5    sceScfGetTimeNotation */
    unsigned char dateNotation : 2; /* bits 6-7 sceScfGetDateNotation */
} ConfigParam2;

/* The strings this member emits.  The developer wrote them as literals at the
 * use sites; the compiler interns each one on first use, which fixes the
 * .rodata order (the month-length template lands between the two assert
 * groups because adddate precedes AdjustTime).  In .rodata order:
 *   rom0:ROMVER                     GetRomName
 *   Can't open rom0:ROMVER          GetRomName
 *   Can't read rom error            GetRomName
 *   Timezone=%d                     sceScfGetTimeZone
 *   DateNotation=%d                 sceScfGetDateNotation
 *   SummerTime=%d                   sceScfGetSummerTime
 *   TimeNotation=%d                 sceScfGetTimeNotation
 *   libscf.c                        __FILE__, first used by tobcd
 *   c <=99                          tobcd
 *   c <= 0x99                       frombcd
 *   prtc != NULL                    convertfrombcd
 *   the twelve month lengths        adddate, shared with subdate
 *   -60*24<=diff && diff <= 60*24   AdjustTime
 * (the five printf strings and the two rom0 diagnostics each end in a newline
 * escape, dropped from the table above so the table stays one line per entry).
 * libscf.c is __FILE__, so the member is compiled from inside its own
 * directory by its bare name, and every assert string is the stringified
 * expression, so the three-argument calls are the newlib assert macro and
 * their line arguments (0x119 for the first, 0x1C7 for the last) fix this
 * file's line layout. */

/* newlib <assert.h> and <stddef.h>, written out here: this tree has no
 * libc include directory for the SDK archives.  NDEBUG is not defined in
 * this archive: the calls are in the shipped code.  The two defines stay
 * together. */
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

/* newlib's <assert.h> declaration, written out with the macro above (no
   assert.h on this archive's include path); assert.c defines it */
extern void __assert(const char *file, int line, const char *failedexpr);
void AdjustTime(sceCdCLOCK *prtc, int diff);
void convertfrombcd(sceCdCLOCK *prtc);
void converttobcd(sceCdCLOCK *prtc);
void adddate(sceCdCLOCK *prtc);
void subdate(sceCdCLOCK *prtc);
void addhour(sceCdCLOCK *prtc);
void subhour(sceCdCLOCK *prtc);
unsigned char tobcd(unsigned char c);
unsigned char frombcd(unsigned char c);
char *GetRomName(void);
int IsT10K(void);
/* The kernel's records are typed in this member (asserts pin its line count) */
extern void GetOsdConfigParam(ConfigParam *param);
extern int GetOsdConfigParam2(ConfigParam2 *param, int count, int offset);

char *GetRomName(void)
{
    int fd;

    if (romName[0] == 0) {
        fd = sceOpen("rom0:ROMVER", 1);
        if (fd == -1) {
            printf("Can't open rom0:ROMVER\n");
        }
        if (sceRead(fd, romName, 14) == -1) {
            printf("Can't read rom error\n");
        }
        sceClose(fd);
    }
    return romName;
}

int IsT10K(void)
{
    if (romName[0] == 0) {
        GetRomName();
    }
    return romName[4] == 'T';
}

int sceScfGetLanguage(void)
{
    ConfigParam param;

    int lang;

    GetOsdConfigParam(&param);
    if (IsT10K()) {
        lang = t10kConfig.language;
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

void sceScfSetT10kConfig(sceScfT10KConfig *param)
{
    t10kConfig = *param;
}

int sceScfGetAspect(void)
{
    ConfigParam param;

    if (IsT10K()) {
        return t10kConfig.aspect;
    }
    GetOsdConfigParam(&param);
    return param.aspect;
}

int sceScfGetSpdif(void)
{
    ConfigParam param;

    if (IsT10K()) {
        return t10kConfig.spdif;
    }
    GetOsdConfigParam(&param);
    return param.spdif;
}

int sceScfGetTimeZone(void)
{
    ConfigParam param;
    int tz;

    if (IsT10K()) {
        tz = t10kConfig.timezone;
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
        v = t10kConfig.dateNotation;
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
        v = t10kConfig.summerTime;
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
        v = t10kConfig.timeNotation;
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
 * this file's first assert and of AdjustTime's range assert is part of the
 * strings (assert is a whitespace-sensitive macro for the formatter), and the
 * __LINE__ arguments pin every assert to its line. */

unsigned char tobcd(unsigned char c)
{
    assert(c <=99);
    return (c / 10) * 6 + c;
}

/* frombcd, the inverse, lands on the next assert line. */
/* The correction term is its own byte-wide local, multiplied with a
 * separate mult and mflo rather than the r5900 three-operand mult3 (tobcd
 * takes mult3, its product feeding an addu).
 */
unsigned char frombcd(unsigned char c)
{
    unsigned char t;

    assert(c <= 0x99);
    t = (c >> 4) * 6;
    return c - t;
}

/* The six packed-BCD fields libcdvd fills in a sceCdCLOCK record, widened to
 * plain binary in place.  The stat and pad bytes are left alone.  The order
 * of the six is year first and second last; the walk is written out rather
 * than looped because the members are named, one call per field.
 */
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
/* AdjustTime's range assert sits on line 0x1A1. */
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
 * rather than shared; the local entry reaches the OSD by this file's
 * getters. */
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
