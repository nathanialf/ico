/* libkernl.a(intr.o) */
#include <eekernel.h>
#include <eeregs.h>
#include <libkernl_internal.h>

/* R5900 opcodes with no C spelling.  Defined in this member. */
#define SYNC() __asm__ __volatile__("sync" : : : "memory")
/* COP0 Status ($12), bit 16 = interrupts enabled.  Taken as an lvalue: the
   wrappers mask the word in place. */
#define MFC0_STATUS(dst) __asm__ __volatile__("mfc0 %0, $12" : "=r"(dst))
#define COP0_STATUS_EIE 0x10000

int DisableIntc(int cause)
{
    int eie;
    int rv;
    MFC0_STATUS(eie);
    eie &= COP0_STATUS_EIE;
    if (eie) {
        DIntr();
    }
    rv = _DisableIntc(cause);
    SYNC();
    if (eie) {
        EIntr();
    }
    return rv;
}

int EnableIntc(int cause)
{
    int eie;
    int rv;
    MFC0_STATUS(eie);
    eie &= COP0_STATUS_EIE;
    if (eie) {
        DIntr();
    }
    rv = _EnableIntc(cause);
    SYNC();
    if (eie) {
        EIntr();
    }
    return rv;
}

int DisableDmac(int channel)
{
    int eie;
    int rv;
    MFC0_STATUS(eie);
    eie &= COP0_STATUS_EIE;
    if (eie) {
        DIntr();
    }
    rv = _DisableDmac(channel);
    SYNC();
    if (eie) {
        EIntr();
    }
    return rv;
}

int EnableDmac(int channel)
{
    int eie;
    int rv;
    MFC0_STATUS(eie);
    eie &= COP0_STATUS_EIE;
    if (eie) {
        DIntr();
    }
    rv = _EnableDmac(channel);
    SYNC();
    if (eie) {
        EIntr();
    }
    return rv;
}

int iEnableIntc(int cause)
{
    int r = _iEnableIntc(cause);
    SYNC();
    return r;
}

int iDisableIntc(int cause)
{
    int r = _iDisableIntc(cause);
    SYNC();
    return r;
}

int iEnableDmac(int channel)
{
    int r = _iEnableDmac(channel);
    SYNC();
    return r;
}

int iDisableDmac(int channel)
{
    int r = _iDisableDmac(channel);
    SYNC();
    return r;
}

/* intr.o's own file static setup (initsys.o holds the global of the same
   name); InitAlarm calls it. */
static void setup(int num, int addr)
{
    __asm__ __volatile__("addiu $3, $0, 116\n\tsyscall 0" : : : "$3", "memory");
}

/* syscall 90 is Copy(dst, src, len); the leaf ignores its arguments, the
   kernel reads them out of $a0..$a2. */
void Copy(char *dst, char *src, int len)
{
    __asm__ __volatile__("addiu $3, $0, 90\n\tsyscall 0" : : : "$3", "memory");
}

int kCopy(int *dst, int *src, unsigned int n)
{
    unsigned int i;
    n >>= 2;
    for (i = 0; i < n; i++) {
        *dst++ = *src++;
    }
    return 0;
}

/* An EE syscall leaf (`addiu $3,$zero,NUM; syscall 0`, the `jr $31; nop`
   from gcc's epilogue) that takes an argument and returns the kernel's $v0:
   syscall 91 is GetEntryAddress(num). */
int GetEntryAddress(int num)
{
    __asm__ __volatile__("addiu $3, $0, 91\n\tsyscall 0" : : : "$3", "memory");
}

/* The member's .data: the kernel-mode alarm handler InitAlarm copies to
   0x80076000 (0x740 B of R5900 code and its tables, linked at that address,
   so the words carry no relocation), the 0x20-byte entry code it copies to
   0x82000, and the syscall table it installs: {number, handler} pairs, the
   first two handlers given, the other six looked up with GetEntryAddress. */
static unsigned int alarm_handler[464] /* derived name */ = {
    0x3C028007, 0x0000282D, 0x24436710, 0x00000000, 0x8C620000, 0x14820003, 0x24A50001, 0x03E00008,
    0x8C620004, 0x2CA20006, 0x1440FFF9, 0x24630008, 0x03E00008, 0x0000102D, 0x00A4202A, 0x10800003,
    0x3C020001, 0x03E00008, 0x00A21025, 0x03E00008, 0x00A0102D, 0x00000000, 0x27BDFF80, 0xFFB30030,
    0x3C138007, 0xFFB60060, 0xFFB50050, 0x0080B02D, 0xFFB00000, 0x00A0A82D, 0x8E626700, 0x0000802D,
    0xFFBF0070, 0xFFB40040, 0xFFB20020, 0x18400028, 0xFFB10010, 0x3C148007, 0x24120014, 0x00000000,
    0x26916740, 0x02121018, 0x02C0202D, 0x00511021, 0x0C01D80E, 0x94450000, 0x02A2102A, 0x10400018,
    0x8E626700, 0x2444FFFF, 0x0090182A, 0x14600018, 0x00921018, 0x00511821, 0x68650007, 0x6C650000,
    0x6866000F, 0x6C660008, 0x8C670010, 0xB065001B, 0xB4650014, 0xB0660023, 0xB466001C, 0xAC670024,
    0x2484FFFF, 0x2463FFEC, 0x0090102A, 0x00000000, 0x1040FFF1, 0x00000000, 0x10000006, 0x0200102D,
    0x26100001, 0x0202102A, 0x1440FFDD, 0x24120014, 0x0200102D, 0xDFBF0070, 0xDFB60060, 0xDFB50050,
    0xDFB40040, 0xDFB30030, 0xDFB20020, 0xDFB10010, 0xDFB00000, 0x03E00008, 0x27BD0080, 0x00000000,
    0x27BDFF70, 0x3C02B000, 0xFFB70070, 0x34421800, 0xFFB60060, 0x00C0B82D, 0xFFB50050, 0x00A0B02D,
    0xFFB30030, 0x3C158007, 0xFFBF0080, 0x3093FFFF, 0xFFB20020, 0xFFB10010, 0xFFB00000, 0xFFB40040,
    0x8EA36700, 0x8C540000, 0x28630040, 0x14600008, 0x02749821, 0x1000002E, 0x2402FFFF, 0x0060902D,
    0x00621014, 0x00821025, 0x1000000D, 0xFCA26708, 0x3C058007, 0x0000182D, 0xDCA46708, 0x00641016,
    0x30420001, 0x1040FFF5, 0x24020001, 0x24630001, 0x28620040, 0x1440FFFA, 0x00641016, 0x2412FFFF,
    0x0640001B, 0x0240102D, 0x0380882D, 0x0260282D, 0x0C01D816, 0x0280202D, 0x24040014, 0x3C088007,
    0x00441018, 0x25036740, 0x8EA56700, 0x24700004, 0x24A50001, 0x00432021, 0x00623821, 0x00508021,
    0xA4940002, 0xA4930000, 0x00E0302D, 0xAE120000, 0x00C0182D, 0xACF10010, 0x95046740, 0xACD60008,
    0xAC77000C, 0x0C01D918, 0xAEA56700, 0x8E020000, 0xDFBF0080, 0xDFB70070, 0xDFB60060, 0xDFB50050,
    0xDFB40040, 0xDFB30030, 0xDFB20020, 0xDFB10010, 0xDFB00000, 0x03E00008, 0x27BD0090, 0x00000000,
    0x27BDFFD0, 0x3C0C8007, 0xFFB10010, 0x0080682D, 0x8D826700, 0x0180882D, 0xFFBF0020, 0x2406FFFF,
    0x18400058, 0xFFB00000, 0x18400056, 0x0000402D, 0x3C0B8007, 0x24030014, 0x25656740, 0x01032018,
    0x00A41021, 0x8C430004, 0x15A3004A, 0x8D826700, 0x3C03B000, 0x00852021, 0x34631820, 0x94850000,
    0x8C620000, 0x14A20008, 0x24030014, 0x3C021000, 0x3442F000, 0x8C430000, 0x30631000, 0x14600043,
    0x2402FFFF, 0x24030014, 0x8D896700, 0x01031818, 0x25646740, 0x2522FFFF, 0x0100382D, 0x0102102A,
    0x00641821, 0x10400019, 0x94700002, 0x3C0A8007, 0x24E30001, 0x24050014, 0x00651018, 0x00E52018,
    0x25666740, 0x0060382D, 0x00462821, 0x00862021, 0x2522FFFF, 0x68A30007, 0x6CA30000, 0x68A6000F,
    0x6CA60008, 0x8CAE0010, 0xB0830007, 0xB4830000, 0xB086000F, 0xB4860008, 0x00E2102A, 0x1440FFEC,
    0xAC8E0010, 0x10000003, 0x24020001, 0x3C0A8007, 0x24020001, 0x8D846700, 0xDD436708, 0x01A21014,
    0x00021027, 0x2484FFFF, 0x00621824, 0xAD846700, 0x15000003, 0xFD436708, 0x0C01D918, 0x95646740,
    0x8E226700, 0x14400004, 0x24030083, 0x3C02B000, 0x34421810, 0xAC430000, 0x3C02B000, 0x0200202D,
    0x34421800, 0x0C01D80E, 0x8C450000, 0x10000005, 0x00503023, 0x25080001, 0x0102102A, 0x1440FFAE,
    0x24030014, 0x0000000F, 0x00C0102D, 0xDFBF0020, 0xDFB10010, 0xDFB00000, 0x03E00008, 0x27BD0030,
    0x27BDFFF0, 0xFFBF0000, 0x0C01D858, 0x3084FFFF, 0x0000000F, 0xDFBF0000, 0x03E00008, 0x27BD0010,
    0x3C02B000, 0x34421820, 0xAC440000, 0x0000000F, 0x3C02B000, 0x24030583, 0x34421810, 0x03E00008,
    0xAC430000, 0x00000000, 0x27BDFF50, 0x0000402D, 0xFFBF00A0, 0xFFB70090, 0xFFB60080, 0xFFB50070,
    0xFFB40060, 0xFFB30050, 0xFFB20040, 0xFFB10030, 0xFFB00020, 0x3C118007, 0x3C128007, 0x00000000,
    0x8E226700, 0x0102102A, 0x1040000A, 0x24030014, 0x26446740, 0x01031818, 0x96456740, 0x00641821,
    0x94620000, 0x10A2FFF6, 0x25080001, 0x0C01D918, 0x0040202D, 0x3C028007, 0x0220B02D, 0x24546740,
    0x24130014, 0x3C158007, 0x10000004, 0x24170001, 0x96426740, 0x1462003E, 0x8E226700, 0x8EC26700,
    0x0000402D, 0x26466740, 0x68C30007, 0x6CC30000, 0x68C4000F, 0x6CC40008, 0x8CC50010, 0xB3A30007,
    0xB7A30000, 0xB3A4000F, 0xB7A40008, 0xAFA50010, 0x2442FFFF, 0x1840001A, 0xAEC26700, 0x8E296700,
    0x8FAA0010, 0x8FA60004, 0x97A70000, 0x00000000, 0x01131818, 0x25020001, 0x0040402D, 0x00742821,
    0x00531818, 0x00742021, 0x688B0007, 0x6C8B0000, 0x688C000F, 0x6C8C0008, 0x8C8D0010, 0xB0AB0007,
    0xB4AB0000, 0xB0AC000F, 0xB4AC0008, 0x0109182A, 0x1460FFEF, 0xACAD0010, 0x10000004, 0x00000000,
    0x8FAA0010, 0x8FA60004, 0x97A70000, 0x0380802D, 0x0140E02D, 0xDEA36708, 0x00D71014, 0x00021027,
    0x3C040008, 0x00621824, 0x8FA50008, 0x8FA8000C, 0x34842000, 0x0C01D9A0, 0xFEA36708, 0x0200E02D,
    0x8E226700, 0x1C40FFC2, 0x97A30000, 0x8E226700, 0x18400005, 0x24030483, 0x0C01D918, 0x96446740,
    0x10000004, 0x00000000, 0x3C02B000, 0x34421810, 0xAC430000, 0x0000000F, 0x42000038, 0xDFBF00A0,
    0xDFB70090, 0xDFB60080, 0xDFB50070, 0xDFB40060, 0xDFB30050, 0xDFB20040, 0xDFB10030, 0xDFB00020,
    0x03E00008, 0x27BD00B0, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x3C1A8007, 0xAF5F6C40, 0x3C1A8007, 0xAF5D6C50, 0x40847000, 0x0000040F, 0x00A0182D, 0x00C0202D,
    0x00E0282D, 0x0100302D, 0x401A6000, 0x375A0012, 0x409A6000, 0x0000040F, 0x42000018, 0x00000000,
    0x40016000, 0x241AFFE4, 0x003A0824, 0x40816000, 0x0000040F, 0x3C1A8007, 0x8F5F6C40, 0x3C1A8007,
    0x03E00008, 0x8F5D6C50, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x000000FC, 0x80076440, 0x000000FE, 0x80076440,
    0x000000FD, 0x800762A0, 0x000000FF, 0x800762A0, 0x0000012C, 0x80076488, 0x00000008, 0x800766C0,
};

static unsigned int alarm_entry[8] /* derived name */ = {
    0x3C1D0008, 0x0060F809, 0x27BD1FC0, 0x2403FFF8, 0x0000000C, 0x00000000, 0x00000000, 0x00000000,
};

static int alarm_syscalls[16] /* derived name */ = {
    90, (int)kCopy, 91, 0x80076000, 252, 0, 254, 0, 253, 0, 255, 0, 300, 0, 8, 0,
};

void InitAlarm(void)
{
    unsigned int i;

    if (*T3_MODE & 0x100)
        return;
    setup(alarm_syscalls[0], alarm_syscalls[1]);
    Copy((char *)0x80076000, (char *)alarm_handler, 0x740);
    Copy((char *)0x82000, (char *)alarm_entry, 0x20);
    FlushCache(0);
    FlushCache(2);
    setup(alarm_syscalls[2], alarm_syscalls[3]);
    for (i = 2; i < 8; i++) {
        setup(alarm_syscalls[i * 2], GetEntryAddress(alarm_syscalls[i * 2]));
    }
}
