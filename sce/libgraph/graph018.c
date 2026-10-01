/* libgraph.a member graph018.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include <eeregs.h>

typedef unsigned int u_long128 __attribute__((mode(TI)));
/* The member's .data (MAIN.MAP graph018.o .data 0x10, no map symbol, so a
   static of Sony's): one VIF1 quadword, MSKPATH3 0 then three NOPs, written
   to the VIF1 FIFO to unmask PATH3 again.  Read-only: its load is hoisted
   above the 0x12001000 store at the end, which alias.c's true_dependence
   allows only for an unchanging MEM.
   kept local: the member's own object, still bytes of the cod/44A2E0 blob;
   it becomes this file's static when its .data row is carved. */
/* kept local: the member's own object, still bytes of the cod/44A2E0 blob; it becomes this
   file's static when its .data row is carved */
extern const u_long128 sceGsUnmaskPath3Packet; /* derived name */
/* kept local: sce/libc/stdio.h declares printf void */
extern int printf(const char *fmt, ...);
/* kept local: eekernel.h declares it as `int GsGetIMR(void)` */
extern unsigned long GsGetIMR(void);
/* kept local: eekernel.h declares it as `int GsPutIMR(int a0)` */
extern unsigned long GsPutIMR(unsigned long a0);

/* RECONSTRUCTION.  What the bytes pin: the allocator's order i, n1, n8, rem,
   pkt, img, extra for $16..$22 (global.c allocno_compare), which needs n8 and
   n1 referenced in every arm, extra kept to seven references (one shared
   `pad` tail for the four shift arms, the 24-bit arm its own) and n1 numbered
   before n8; the counter zeroes after the three declared initialisers, so
   sched2 leaves nh = 0 last for the range check's slot; a separate `rest`
   holding each arm's shift; the rem path re-reading the TRXREG word from the
   packet; every GIF FIFO access volatile (reorg never takes one into a slot).
   What they cannot pin: the names, and whether the arms were written with a
   macro. */
int sceGsExecStoreImage(void *pkt, void *img)
{
    union {
        u_long128 q;
        char c[16];
    } buf;

    unsigned int i = 0;
    int rem = 0;
    int n1;
    int n8;
    unsigned long imr;
    int psm;
    int w;
    int h;
    int nh;
    int len;
    int rest;
    int j;
    int extra = 0;
    unsigned long trxreg;

    n8 = 0;
    n1 = 0;
    nh = 0;
    trxreg = ((unsigned long *)pkt)[8];
    w = (int)(trxreg & 0xFFF);
    h = (int)((trxreg >> 32) & 0xFFF);
    psm = (int)((((unsigned long *)pkt)[4] >> 24) & 0x3F);

    switch (psm) {
    case 0x00:
    case 0x30:
        len = (w * h) << 2;
        rem = len & 0xF;
        n1 = (len >> 4) & 7;
        n8 = (len >> 4) & 0xFFFFFFF8;
        if (rem == 0) {
            goto same_height;
        }
        nh = (h + 3) & 0x1FFC;
        rest = (w * nh) >> 2;
        rest = rest - n8 - n1;
        goto pad;
    case 0x01:
    case 0x31:
        len = (w * h) * 3;
        rem = len & 0xF;
        n1 = (len >> 4) & 7;
        n8 = (len >> 4) & 0xFFFFFFF8;
        if (rem == 0) {
            goto same_height;
        }
        nh = (h + 15) & 0x1FF0;
        rest = ((w * nh) * 3) >> 4;
        extra = rest - n8 - n1 - 1;
        break;
    case 0x02:
    case 0x0A:
    case 0x32:
    case 0x3A:
        len = (w * h) << 1;
        rem = len & 0xF;
        n1 = (len >> 4) & 7;
        n8 = (len >> 4) & 0xFFFFFFF8;
        if (rem == 0) {
            goto same_height;
        }
        nh = (h + 7) & 0xFFFFFFF8;
        rest = (w * nh) >> 3;
        rest = rest - n8 - n1;
        goto pad;
    case 0x13:
    case 0x1B:
        len = w * h;
        rem = len & 0xF;
        n1 = (len >> 4) & 7;
        n8 = (len >> 4) & 0xFFFFFFF8;
        if (rem == 0) {
            goto same_height;
        }
        nh = (h + 7) & 0xFFFFFFF8;
        rest = (w * nh) >> 4;
        rest = rest - n8 - n1;
        goto pad;
    case 0x14:
    case 0x24:
    case 0x2C:
        len = (w * h) >> 1;
        rem = len & 0xF;
        n1 = (len >> 4) & 7;
        n8 = (len >> 4) & 0xFFFFFFF8;
        if (rem == 0) {
        same_height:
            nh = h;
            extra = 0;
            break;
        }
        nh = (h + 7) & 0xFFFFFFF8;
        rest = (w * nh) >> 5;
        rest = rest - n8 - n1;
    pad:
        extra = rest - 1;
        break;
    default:
        break;
    }

    if (rem != 0) {
        *(volatile unsigned long *)(((unsigned int)pkt + 0x40) | 0x20000000) =
            (unsigned long)(int)(((unsigned long *)pkt)[8] & 0xFFF) | ((unsigned long)nh << 32);
    }

    while (*D1_CHCR & 0x100) {
        if (i++ > 0x1000000) {
            printf("sceGsExecStoreImage: DMA Ch.1 does not terminate\r\n");
            return -1;
        }
    }

    imr = GsPutIMR(GsGetIMR() | 0x200);

    *GS_CSR = 2;
    *D1_QWC = 7;
    if (((unsigned int)pkt & 0x70000000) == 0x70000000) {
        *D1_MADR = ((unsigned int)pkt & 0x0FFFFFFF) | 0x80000000;
    } else {
        *D1_MADR = (unsigned int)pkt & 0x0FFFFFFF;
    }
    *D1_CHCR = 0x101;
    while (*D1_CHCR & 0x100) {
        if (i++ > 0x1000000) {
            printf("sceGsExecStoreImage: DMA Ch.1 does not terminate\r\n");
            return -1;
        }
    }

    while ((*GS_CSR & 2) == 0) {
        if (i++ > 0x1000000) {
            printf("sceGsExecStoreImage: GS does not terminate\r\n");
            *(volatile u_long128 *)VIF1_FIFO = sceGsUnmaskPath3Packet;
            return -1;
        }
    }

    *VIF1_STAT = 0x800000;
    *GS_BUSDIR = 1;

    if (n8 != 0) {
        *D1_QWC = n8;
        if (((unsigned int)img & 0x70000000) == 0x70000000) {
            *D1_MADR = ((unsigned int)img & 0x0FFFFFFF) | 0x80000000;
        } else {
            *D1_MADR = (unsigned int)img & 0x0FFFFFFF;
        }
        *D1_CHCR = 0x100;
        while (*D1_CHCR & 0x100) {
            if (i++ > 0x1000000) {
                printf("sceGsExecStoreImage: DMA Ch.1 (GS->MEM) does not terminate\r\n");
                *GS_CSR = 0x100;
                *GS_BUSDIR = 0;
                *GIF_CTRL = 1;
                *VIF1_FBRST = 1;
                return -1;
            }
        }
    }

    for (j = 0; j < n1; j++) {
        while ((*VIF1_STAT & 0x1F000000) == 0) {
            if (i++ > 0x1000000) {
                printf("sceGsExecStoreImage: Enough data does not reach VIF1\n");
                *GS_CSR = 0x100;
                *GS_BUSDIR = 0;
                *GIF_CTRL = 1;
                *VIF1_FBRST = 1;
                return -1;
            }
        }
        ((u_long128 *)img)[n8 + j] = *(volatile u_long128 *)VIF1_FIFO;
    }

    if (rem != 0) {
        while ((*VIF1_STAT & 0x1F000000) == 0) {
            if (i++ > 0x1000000) {
                printf("sceGsExecStoreImage: Enough data does not reach VIF1\n");
                *GS_CSR = 0x100;
                *GS_BUSDIR = 0;
                *GIF_CTRL = 1;
                *VIF1_FBRST = 1;
                return -1;
            }
        }
        buf.q = *(volatile u_long128 *)VIF1_FIFO;
        for (j = 0; j < rem; j++) {
            *((char *)img + (n8 + n1) * 16 + j) = buf.c[j];
        }
        for (j = 0; j < extra; j++) {
            while ((*VIF1_STAT & 0x1F000000) == 0) {
                if (i++ > 0x1000000) {
                    printf("sceGsExecStoreImage: Enough data does not reach VIF1\n");
                    *GS_CSR = 0x100;
                    *GS_BUSDIR = 0;
                    *GIF_CTRL = 1;
                    *VIF1_FBRST = 1;
                    return -1;
                }
            }
            buf.q = *(volatile u_long128 *)VIF1_FIFO;
        }
    }

    *VIF1_STAT = 0;
    *GS_BUSDIR = 0;
    GsPutIMR(imr);
    *GS_CSR = 2;
    *(volatile u_long128 *)VIF1_FIFO = sceGsUnmaskPath3Packet;
    return 0;
}
