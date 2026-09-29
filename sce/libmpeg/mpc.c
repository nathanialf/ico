/* Vendor SCE library member: libmpeg.a(mpc.o).  MAIN.MAP's member size (0x4D68)
 * tiles the retail run exactly, VMA 0x26CBD0..0x271938, 63 functions: motion
 * compensation, the macroblock and slice decoder, the IPU command and bit
 * reader layer, the picture-level header parsers and the output path.  The
 * member's .text is 16-aligned by _copyRefImage's `.align 4` before _maxval,
 * which is what places the 12 bytes of fill after defhandler.o. */
#include "common.h"
#include <libmpeg.h>

extern int _widthMB[];
extern int _isError[];
extern int _picture_structure;
extern int _curFrame[];
extern int _curTop[];
extern int _curBot[];
extern int D_0054C0DC[];
extern int D_00636F20[];
extern void _getAllRefs();

int _motionComp0(int a0, int a1, int a2, int a3, int *a4, int *a5, int *a6)
{
    int col = a0 % _widthMB[0];
    int row = a0 / _widthMB[0];
    int x = col * 16;
    int y = row * 16;
    int intra = a2 & 1;

    if (intra) {
        while (((*(volatile unsigned int *)0x1000D400) >> 8) & 1) {}
        *(int *)((char *)_mbcont + _mbcont[0x280 / 4] * 0x140 + 0x138) = 0;
    } else {
        long long *tag;
        int cnt;
        int i;

        if ((unsigned int)(a3 - 1) >= 3) {
            _Error1((int)D_00636F20, a3);
            _isError[0] = 1;
            return 0;
        }
        _getAllRefs(x, y, a2);
        while (((*(volatile unsigned int *)0x1000D400) >> 8) & 1) {}
        tag = (long long *)((D_0054C0DC[0] & 0x0FFFFFFF) | 0x20000000);
        cnt = *(int *)((char *)_mbcont + _mbcont[0x280 / 4] * 0x140 + 0x12C);
        for (i = 0; i < cnt; i++) {
            int id;
            tag[0] =
                ((long long)(((int *)((char *)_mbcont + i * 4 + _mbcont[0x280 / 4] * 0x140))[2] &
                             0x0FFFFFFF)
                 << 32) |
                (3 << 28) | 0x30;
            id = i == cnt - 1 ? 0 : 3;
            tag[2] =
                ((long long)(((int *)((char *)_mbcont + i * 4 + _mbcont[0x280 / 4] * 0x140))[6] &
                             0x0FFFFFFF)
                 << 32) |
                ((long long)id << 28) | 0x30;
            tag += 4;
        }
        __asm__ __volatile__("sync");
        *(volatile int *)0x1000D480 = *(int *)((char *)_mbcont + _mbcont[0x280 / 4] * 0x140);
        *(volatile int *)0x1000D430 = D_0054C0DC[0];
        *(volatile int *)0x1000D420 = 0;
        *(volatile int *)0x1000D400 = 0x105;
        *(int *)((char *)_mbcont + _mbcont[0x280 / 4] * 0x140 + 0x138) = 1;
    }
    if (a1 == 1 && (a2 & 2)) {
        *(int *)((char *)_mbcont + _mbcont[0x280 / 4] * 0x140 + 0x134) = a1;
    } else {
        *(int *)((char *)_mbcont + _mbcont[0x280 / 4] * 0x140 + 0x134) = 0;
    }
    ((int *)((char *)_mbcont + _mbcont[0x280 / 4] * 0x140))[0x130 / 4] = intra;
    if (_picture_structure == 3) {
        int *p = (int *)_curFrame[0];
        *(void **)((char *)_mbcont + _mbcont[0x280 / 4] * 0x140 + 0x128) =
            (void *)(p[0] + (col * p[4] + row) * 0x180);
    } else {
        int *p = (int *)(_picture_structure == 2 ? _curBot[0] : _curTop[0]);
        *(void **)((char *)_mbcont + _mbcont[0x280 / 4] * 0x140 + 0x128) =
            (void *)(p[0] + (col * p[4] + row) * 0x180);
    }
    return 1;
}

extern int _picture_coding_type[];
extern void _getRef0();
extern void _dualPrimeVector(int *DMV, int *dmvector, int mvx, int mvy);
extern int D_00636F48[];
extern int D_00636F68[];
extern int D_00636F88[];

void _getAllRefs(int x, int y, int mbflags, int motion_type, int *PMV, int *mv_field_sel,
                 int *dmvector)
{
    int DMV[4];
    int fields[2][2];
    int fld = 1;
    int avg = 0;

    *(int *)((char *)_mbcont + _mbcont[0x280 / 4] * 0x140 + 0x12C) = 0;
    if ((mbflags & 8) || _picture_coding_type[0] == 2) {
        if (_picture_structure == 3) {
            if (motion_type == 2 || (mbflags & 8) == 0) {
                _getRef0(_forwFrame[0], 0, 0, 0, 16, x, y, PMV[0], PMV[1], 0, 0);
            } else if (motion_type == 1) {
                _getRef0(_forwFrame[0], mv_field_sel[0], 0, 0, 8, x, y, PMV[0], PMV[1] >> 1, fld,
                         0);
                _getRef0(_forwFrame[0], mv_field_sel[2], 1, 0, 8, x, y, PMV[4], PMV[5] >> 1, fld,
                         0);
            } else if (motion_type == 3) {
                _dualPrimeVector(DMV, dmvector, PMV[0], PMV[1] >> 1);
                _getRef0(_forwFrame[0], 0, 0, 0, 8, x, y, PMV[0], PMV[1] >> 1, fld, 0);
                _getRef0(_forwFrame[0], 1, 0, 0, 8, x, y, DMV[0], DMV[1], fld, 1);
                _getRef0(_forwFrame[0], 1, 1, 0, 8, x, y, PMV[0], PMV[1] >> 1, fld, 0);
                _getRef0(_forwFrame[0], 0, 1, 0, 8, x, y, DMV[2], DMV[3], fld, 1);
            } else {
                _Error1((int)D_00636F48, motion_type);
            }
        } else {
            int sel;

            fields[0][0] = _forwTop[0];
            fields[0][1] = _forwBot[0];
            fields[1][0] = _backTop[0];
            fields[1][1] = _backBot[0];
            /* On a field picture the frame flag is reused for the current
               field's parity (1 = bottom): the ROM keeps both in $23, and
               this set is what stops cse carrying the entry 1 into the
               selection below, whose conditional move combine then folds to
               the ROM's xor/sltu. */
            fld = _picture_structure == 2;
            /* The else arm's set is hoisted by jump in front of the first
               test, after its li 2, which is where the ROM schedules it. */
            if (_picture_coding_type[0] == 2 && _isSecondField[0] != 0 && fld != mv_field_sel[0]) {
                sel = 1;
            } else {
                sel = 0;
            }
            if (motion_type == 1 || (mbflags & 8) == 0) {
                _getRef0(fields[sel][mv_field_sel[0]], 0, 0, 0, 16, x, y, PMV[0], PMV[1], 0, 0);
            } else if (motion_type == 2) {
                _getRef0(fields[sel][mv_field_sel[0]], 0, 0, 0, 8, x, y, PMV[0], PMV[1], 0, 0);
                sel = 0;
                if (_picture_coding_type[0] == motion_type && _isSecondField[0] != 0 &&
                    fld != mv_field_sel[2]) {
                    sel = 1;
                }
                _getRef0(fields[sel][mv_field_sel[2]], 0, 0, 8, 8, x, y, PMV[4], PMV[5], 0, 0);
            } else if (motion_type == 3) {
                sel = 0;
                if (_isSecondField[0] != 0) {
                    sel = 1;
                }
                _dualPrimeVector(DMV, dmvector, PMV[0], PMV[1]);
                _getRef0(fields[0][fld], 0, 0, 0, 16, x, y, PMV[0], PMV[1], 0, 0);
                _getRef0(fields[sel][fld ? 0 : 1], 0, 0, 0, 16, x, y, DMV[0], DMV[1], 0, 1);
            } else {
                _Error1((int)D_00636F68, motion_type);
            }
        }
        avg = 1;
    }
    if (mbflags & 4) {
        if (_picture_structure == 3) {
            /* The backward frame's own field flag (ROM `addiu $23,$0,1`
               before the motion_type test): fld may hold the field parity
               here, and as one variable with fld the allocation would rank
               it above mv_field_sel, where the ROM has the reverse. */
            int bfld = 1;

            if (motion_type == 2) {
                _getRef0(_backFrame[0], 0, 0, 0, 16, x, y, PMV[2], PMV[3], 0, avg);
            } else {
                _getRef0(_backFrame[0], mv_field_sel[1], 0, 0, 8, x, y, PMV[2], PMV[3] >> 1, bfld,
                         avg);
                _getRef0(_backFrame[0], mv_field_sel[3], 1, 0, 8, x, y, PMV[6], PMV[7] >> 1, bfld,
                         avg);
            }
        } else if (motion_type == 1) {
            _getRef0(mv_field_sel[1] ? _backBot[0] : _backTop[0], 0, 0, 0, 16, x, y, PMV[2], PMV[3],
                     0, avg);
        } else if (motion_type == 2) {
            _getRef0(mv_field_sel[1] ? _backBot[0] : _backTop[0], 0, 0, 0, 8, x, y, PMV[2], PMV[3],
                     0, avg);
            _getRef0(mv_field_sel[3] ? _backBot[0] : _backTop[0], 0, 0, 8, 8, x, y, PMV[6], PMV[7],
                     0, avg);
        } else {
            _Error1((int)D_00636F88, motion_type);
        }
    }
}

/* the prediction buffer the IPU reads the two reference blocks out of */
extern int D_0054C0E0;
/* the eight luma (_rix_*) and the eight chroma (_ri0_*) prediction copy
 * routines, picked by the half-pel bits of the vector and by whether this
 * reference is averaged; _doMC calls them with the descriptor */
extern void (*D_0054C9C8[])();
extern void (*D_0054C9E8[])();

/* Append one reference block to the current macroblock record: the luma
 * descriptor at +0x48 and the chroma descriptor at +0xB8 (seven ints each,
 * one per reference), then the two source addresses and the two copy
 * routines in the record's four parallel arrays at +8, +0x18, +0x28 and +0x38.
 * fld is 1 when the reference is read field-organised out of a frame buffer,
 * which doubles every vertical step and halves every vertical extent. The
 * chroma half reuses the luma half's position, fraction and half-pel
 * variables. */
void _getRef0(int *img, int lineOff, int predIdx, int yoff, int h, int x, int y, int mvx, int mvy,
              int fld, int avg)
{
    int n = *(int *)((char *)_mbcont + _mbcont[0x280 / 4] * 0x140 + 0x12C);
    int *luma = (int *)((char *)_mbcont + 0x48 + _mbcont[0x280 / 4] * 0x140 + n * 0x1C);
    int *chroma = (int *)((char *)_mbcont + 0xB8 + _mbcont[0x280 / 4] * 0x140 + n * 0x1C);
    int dst;
    int lumaCmd, chromaCmd;
    int ix, rx, ry, px, py, fy, blk, t, xh, yh;
    int cmvx, cmvy, cpx, cpy, cyoff, ch;
    int base, idx, lrow, lrow2, cbase, crow, crow2;

    ix = mvx >> 1;
    dst = D_0054C0E0;
    rx = ix + x;
    if (fld) {
        ry = (mvy >> 1) * 2 + lineOff + yoff + y;
    } else {
        ry = (mvy >> 1) + lineOff + yoff + y;
    }
    px = rx >> 4;
    py = ry >> 4;
    blk = px * img[0x10 / 4] + py;
    fy = ry - py * 16;
    xh = mvx & 1;
    yh = mvy & 1;
    luma[1] = rx - px * 16;
    ((void **)luma)[0] = (void *)(dst + (predIdx + yoff) * 32);
    if (yh) {
        if (fy + (h << fld) >= 16) {
            t = (16 >> fld) - (fy >> fld) - 1;
            luma[2] = t;
            luma[3] = h - t;
        } else {
            luma[2] = h;
            luma[3] = 0;
        }
    } else {
        if (fy + (h << fld) >= 17) {
            t = (16 >> fld) - (fy >> fld);
            luma[2] = t;
            luma[3] = h - t;
        } else {
            luma[2] = h;
            luma[3] = 0;
        }
    }
    base = *(int *)((char *)_mbcont + _mbcont[0x280 / 4] * 0x140) + n * 0x600;
    lrow = fy * 16;
    ((void **)luma)[5] = (void *)(base + lrow);
    lrow2 = lrow + 0x300;
    ((void **)luma)[6] = (void *)(base + lrow2);
    luma[4] = 16 << fld;
    lumaCmd = (avg << 2) | (xh << 1) | yh;

    cmvx = mvx / 2;
    cmvy = mvy / 2;
    rx = (cmvx >> 1) + (x >> 1);
    cyoff = yoff >> 1;
    ch = h >> 1;
    if (fld) {
        ry = (cmvy >> 1) * 2 + lineOff + cyoff + (y >> 1);
    } else {
        ry = (cmvy >> 1) + lineOff + cyoff + (y >> 1);
    }
    cpx = rx >> 3;
    cpy = ry >> 3;
    fy = ry - cpy * 8;
    xh = cmvx & 1;
    yh = cmvy & 1;
    chroma[1] = rx - cpx * 8;
    ((void **)chroma)[0] = (void *)(dst + 0x200 + (predIdx + cyoff) * 16);
    if (yh) {
        if (fy + (ch << fld) >= 8) {
            t = (8 >> fld) - (fy >> fld) - 1;
            chroma[2] = t;
            chroma[3] = ch - t;
        } else {
            chroma[2] = ch;
            chroma[3] = 0;
        }
    } else {
        if (fy + (ch << fld) >= 9) {
            t = (8 >> fld) - (fy >> fld);
            chroma[2] = t;
            chroma[3] = ch - t;
        } else {
            chroma[2] = ch;
            chroma[3] = 0;
        }
    }
    cbase = ((cpx - px) * 2 + (cpy - py)) * 0x180 + base;
    crow = fy * 8 + 0x100;
    crow2 = fy * 8 + 0x400;
    ((void **)chroma)[5] = (void *)(cbase + crow);
    ((void **)chroma)[6] = (void *)(cbase + crow2);
    chroma[4] = 8 << fld;
    chromaCmd = (avg << 2) | (xh << 1) | yh;

    idx = _mbcont[0x280 / 4];
    ((void **)((char *)_mbcont + n * 4 + idx * 0x140))[2] = (void *)(img[0] + blk * 0x180);
    ((void **)((char *)_mbcont + n * 4 + idx * 0x140))[6] =
        (void *)(img[0] + (blk + img[0x10 / 4]) * 0x180);
    ((void (**)())((char *)_mbcont + n * 4 + idx * 0x140))[10] = D_0054C9C8[lumaCmd];
    ((void (**)())((char *)_mbcont + n * 4 + idx * 0x140))[14] = D_0054C9E8[chromaCmd];
    *(int *)((char *)_mbcont + idx * 0x140 + 0x12C) += 1;
}

extern void _copyRefImage(void *a0, void *a1);
extern void _copyAddRefImage(void *a0, void *a1, void *a2);
extern int D_00636FA8[]; /* "intra && skip MB" */

/* One macroblock's motion-compensation record, 0x140 bytes, as the members of
 * this file fill it: _motionComp0 sets the IPU output base, the destination and
 * the flags, _getRef0 appends one reference per call (source addresses, copy
 * routines, a seven-int luma and a seven-int chroma descriptor). */
typedef struct {
    void *ipuOut;
    void *src;
    void *refAddr[2][4];
    void (*lumaFn[4])();
    void (*chromaFn[4])();
    int luma[4][7];
    int chroma[4][7];
    void *dst;
    int count;
    int intra;
    int _134;
    int busy;
    int skip;
} MCRecord;

/* _mbcont: two records, double-buffered, and the index of the current one
 * (the `_mbcont[0x280 / 4]` the other members read). */
typedef struct {
    MCRecord rec[2];
    int cur;
} MCState;

/* Finish record a0: run each reference's luma and chroma copy routines into
 * the prediction buffer, then copy the intra block, the prediction (skipped
 * macroblock) or the prediction plus the residual to the destination. */
void _doMC(int a0)
{
    int i;

    if (((MCState *)_mbcont)->rec[a0].busy != 0) {
        for (i = 0; i < ((MCState *)_mbcont)->rec[a0].count; i++) {
            ((MCState *)_mbcont)->rec[a0].lumaFn[i](((MCState *)_mbcont)->rec[a0].luma[i]);
            ((MCState *)_mbcont)->rec[a0].chromaFn[i](((MCState *)_mbcont)->rec[a0].chroma[i]);
        }
    }
    if (((MCState *)_mbcont)->rec[a0].intra != 0 && ((MCState *)_mbcont)->rec[a0].skip != 0) {
        _Error(D_00636FA8);
    }
    if (((MCState *)_mbcont)->rec[a0].intra != 0) {
        _copyRefImage(((MCState *)_mbcont)->rec[a0].dst, ((MCState *)_mbcont)->rec[a0].src);
    } else if (((MCState *)_mbcont)->rec[a0].skip != 0) {
        _copyRefImage(((MCState *)_mbcont)->rec[a0].dst, (void *)D_0054C0E0);
    } else {
        _copyAddRefImage(((MCState *)_mbcont)->rec[a0].dst, (void *)D_0054C0E0,
                         ((MCState *)_mbcont)->rec[a0].src);
    }
}

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

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        ".global _rix_100\n"
        ".type _rix_100, @function\n"
        "    .align 3\n"
        "_rix_100:\n"
        "    lw $5, 0x14($4)\n"
        "    lw $6, 0x18($4)\n"
        "    lw $7, 0x8($4)\n"
        "    lw $14, 0x0($4)\n"
        "    lw $13, 0x4($4)\n"
        "    lw $9, 0x10($4)\n"
        "    sll $8, $9, 1\n"
        "    addiu $11, $0, -0x1\n"
        "    mtsab $13, 0x0\n"
        ".L_rix_100_row:\n"
        "    lq $10, 0x0($5)\n"
        "    lq $15, 0x0($6)\n"
        "    qfsrv $2, $15, $10\n"
        "    pextlb $10, $0, $2\n"
        "    pextub $15, $0, $2\n"
        "    lq $2, 0x0($14)\n"
        "    lq $3, 0x10($14)\n"
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
        "    addi $7, $7, -0x1\n"
        "    addu $5, $5, $9\n"
        "    addu $14, $14, $8\n"
        "    bgtz $7, .L_rix_100_row\n"
        "    addu $6, $6, $9\n"
        "    addiu $5, $5, 0x80\n"
        "    addiu $6, $6, 0x80\n"
        "    lw $7, 0xC($4)\n"
        "    and $12, $11, $7\n"
        "    bnez $12, .L_rix_100_row\n"
        "    daddu $11, $0, $0\n"
        "    jr $31\n"
        "    nop\n"
        ".size _rix_100, . - _rix_100\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

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

extern int _maxval; /* the clamp mask at the end of _copyRefImage, named as the listing names it */

void _copyAddRefImage(void *a0, void *a1, void *a2)
{
    __asm__ __volatile__(".set noreorder\n"
                         "addiu $12, $0, 0x18\n"
                         "lui $10, %%hi(_maxval)\n"
                         "addiu $10, $10, %%lo(_maxval)\n"
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
 * clamp mask its sibling reads as _maxval lives in this function's own
 * text, aligned to a quadword, with the two pad instructions the alignment
 * leaves behind. */
void _copyRefImage(void *a0, void *a1)
{
    __asm__ __volatile__(".set noreorder\n"
                         "addiu $12, $0, 0x18\n"
                         "lui $10, %%hi(_maxval)\n"
                         "addiu $10, $10, %%lo(_maxval)\n"
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
                         "_maxval:\n"
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

extern int _top32;
extern int _top32len;
extern char D_00636FC0[];
extern void DIntr();
extern int EIntr(void);

int _waitBdecOut(void)
{
    int a[8];
    int b[8];
    int ret = 1;
    int bp;
    long long top;

    _waitIpuIdle();
    while (*(volatile int *)0x1000B020 != 0 && (*(volatile int *)0x10002010 & 0x4000) == 0) {
        if (*(volatile int *)0x1000B420 == 0 && (*(volatile int *)0x1000B400 & 0x100) == 0) {
            a[0] = 1;
            _dispatchMpegCallback(_theSceMpeg[0], a);
        }
    }
    bp = *(volatile int *)0x10002020;
    top = *(long long *)0x10002030;
    _top32 = top;
    if (top < 0) {
        _top32len = (bp & 0x1F) != 0 ? 32 - (bp & 0x1F) : 0;
    } else {
        _top32len = 32;
    }
    if ((*(volatile int *)0x10002010 & 0x4000) != 0) {
        ret = 0;
        _Error(D_00636FC0);
        b[0] = 2;
        _dispatchMpegCallback(_theSceMpeg[0], b);
        *(int *)0x10002010 = 0x40000000;
        b[0] = 3;
        _dispatchMpegCallback(_theSceMpeg[0], b);
        DIntr();
        *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 | 0x10000;
        *(volatile int *)0x1000B000 = 0;
        *(int *)0x1000F590 = *(volatile int *)0x1000F520 & 0xFFFEFFFF;
        EIntr();
        *(volatile int *)0x1000B020 = 0;
    }
    return ret;
}

extern int _ipuVdec(int a0);

int _dmVector(void)
{
    return _ipuVdec(3);
}

extern int _top_field_first;

void _dualPrimeVector(int *DMV, int *dmvector, int mvx, int mvy)
{
    int vec;
    int ps;

    if (_picture_structure == 3) {
        if (_top_field_first != 0) {
            DMV[0] = ((mvx + (mvx > 0)) >> 1) + dmvector[0];
            DMV[1] = ((mvy + (mvy > 0)) >> 1) + dmvector[1] - 1;
            DMV[2] = ((3 * mvx + (mvx > 0)) >> 1) + dmvector[0];
            DMV[3] = ((3 * mvy + (mvy > 0)) >> 1) + dmvector[1] + 1;
        } else {
            DMV[0] = ((3 * mvx + (mvx > 0)) >> 1) + dmvector[0];
            DMV[1] = ((3 * mvy + (mvy > 0)) >> 1) + dmvector[1] - 1;
            DMV[2] = ((mvx + (mvx > 0)) >> 1) + dmvector[0];
            DMV[3] = ((mvy + (mvy > 0)) >> 1) + dmvector[1] + 1;
        }
    } else {
        DMV[0] = ((mvx + (mvx > 0)) >> 1) + dmvector[0];
        vec = ((mvy + (mvy > 0)) >> 1) + dmvector[1];
        ps = _picture_structure;
        DMV[1] = vec;
        if (ps == 1) {
            DMV[1] = vec - 1;
        } else {
            DMV[1] = vec + 1;
        }
    }
}

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
    if (_picture_structure != 3) {
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

extern int _sliceA0(int a0, int *a1, int *a2, int *a3);
extern int _mbAddressIncrement(void);
extern int _decMB0(int *a0, int *a1, int *a2, int a3[2][2][2], int *a4, int *a5);
extern int _skipMB0(int *a0, int *a1, int *a2, int *a3);
extern int _motionComp0(int a0, int a1, int a2, int a3, int *a4, int *a5, int *a6);
extern char D_00637080[];

int _slice0(int a0, int a1)
{
    int PMV[8];
    int dmvector[4];
    int mv_field_sel[4];
    int mba;
    int n;
    int mb_type;
    int motion_type;
    int dct_type;
    int r;

    mba = 0;
    n = 0;
    r = _sliceA0(a1, &mba, &n, PMV);
    if (r != 0) {
        return r;
    }
    _isError[0] = 0;
    for (;;) {
        if (mba >= a1) {
            return 0;
        }
        *(int *)((char *)_mbcont + _mbcont[0x280 / 4] * 0x140 + 0x13C) = 0;
        if (_waitBdecOut() == 0) {
            return 2;
        }
        if (n == 0) {
            if (_peepBit(0x17) == 0 || _isError[0] != 0) {
                _isError[0] = 0;
                return 3;
            }
            n = _mbAddressIncrement();
            if (_isError[0] != 0) {
                _isError[0] = 0;
                return 1;
            }
        }
        if (mba >= a1) {
            _Error(D_00637080);
            return 2;
        }
        if (n == 1) {
            if (_decMB0(&mb_type, &motion_type, &dct_type, PMV, dmvector, mv_field_sel) == 0) {
                _isError[0] = 0;
                return 1;
            }
        } else {
            if (_skipMB0(PMV, &motion_type, dmvector, &mb_type) == 0) {
                _isError[0] = 0;
                return 2;
            }
        }
        if (_motionComp0(mba, n, mb_type, motion_type, PMV, dmvector, mv_field_sel) == 0) {
            _isError[0] = 0;
            return 2;
        }
        if (mba != 0) {
            _doMC(_mbcont[0x280 / 4] ^ 1);
        }
        mba = mba + 1;
        n = n - 1;
        _mbcont[0x280 / 4] = _mbcont[0x280 / 4] ^ 1;
    }
}

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
    if (_picture_structure == 3) {
        a1[0] = 2;
    } else {
        a1[0] = 1;
        a2[0] = a2[1] = _picture_structure == 2;
    }
    if (_picture_coding_type[0] == 1) {
        _Error(D_006370A0);
        ret = 0;
    }
    a3[0] = a3[0] & ~1;
    return ret;
}

extern int _frame_pred_frame_dct;
extern int _concealment_motion_vectors;
extern int _f_code[];
extern int _forward_f_code;
extern int _backward_f_code;
extern int _full_pel_forward_vector;
extern int _full_pel_backward_vector;
extern int _qscqsc;
extern unsigned int _nextBit(int a0);
extern void _motionVectors();
extern void _motionVector();
extern char D_006370D0[];

/* Decode one macroblock's header: the macroblock type, the motion and DCT
 * types, the quantiser scale and the motion vectors, then either start the
 * IPU block decode (the fromIPU channel writing into the current record) or
 * mark the record skipped, and reset the motion vector predictors. PMV is the
 * [r][s][t] predictor array _motionVectors takes. */
int _decMB0(int *mb_type, int *motion_type, int *dct_type, int PMV[2][2][2], int *mv_field_sel,
            int *dmvector)
{
    int mv_count;
    int mv_format;
    int dmv;
    int mvscale;
    int *p;
    int cmd;
    int cmd2;

    *(volatile int *)0x10002010 =
        (*(volatile int *)0x10002010 & 0xF8FFFFFF) | (_picture_coding_type[0] << 24);
    mb_type[0] = _ipuVdec(1);
    if (mb_type[0] == 0) {
        _Error(D_006370D0);
        _isError[0] = 1;
        return 0;
    }
    if (mb_type[0] & 0xC) {
        if (_picture_structure == 3 && _frame_pred_frame_dct != 0) {
            motion_type[0] = 2;
        } else {
            motion_type[0] = _nextBit(2);
        }
    } else if ((mb_type[0] & 1) && _concealment_motion_vectors != 0) {
        motion_type[0] = _picture_structure == 3 ? 2 : 1;
    }
    if (_picture_structure == 3) {
        mv_count = motion_type[0] == 1 ? 2 : 1;
        mv_format = motion_type[0] == 2;
    } else {
        mv_count = motion_type[0] == 2 ? 2 : 1;
        mv_format = 0;
    }
    dmv = motion_type[0] == 3;
    mvscale = 0;
    if (mv_format == 0) {
        mvscale = _picture_structure == 3;
    }
    dct_type[0] = _picture_structure == 3 && _frame_pred_frame_dct == 0 && (mb_type[0] & 3) != 0
                      ? _nextBit(1)
                      : 0;
    if (mb_type[0] & 0x10) {
        _qscqsc = _nextBit(5);
    }
    if ((mb_type[0] & 8) || ((mb_type[0] & 1) && _concealment_motion_vectors != 0)) {
        if (_isMpeg2[0]) {
            _motionVectors(PMV, dmvector, mv_field_sel, 0, mv_count, mv_format, _f_code[0] - 1,
                           _f_code[1] - 1, dmv, mvscale);
        } else {
            _motionVector(PMV[0][0], dmvector, _forward_f_code - 1, _forward_f_code - 1, 0, 0,
                          _full_pel_forward_vector);
        }
    }
    if (_isError[0]) {
        return 0;
    }
    if (mb_type[0] & 4) {
        if (_isMpeg2[0]) {
            _motionVectors(PMV, dmvector, mv_field_sel, 1, mv_count, mv_format, _f_code[2] - 1,
                           _f_code[3] - 1, 0, mvscale);
        } else {
            _motionVector(PMV[0][1], dmvector, _backward_f_code - 1, _backward_f_code - 1, 0, 0,
                          _full_pel_backward_vector);
        }
    }
    if (_isError[0]) {
        return 0;
    }
    if ((mb_type[0] & 1) && _concealment_motion_vectors != 0) {
        _flushBuf(1);
    }
    if (mb_type[0] & 3) {
        p = (int *)((char *)_mbcont + _mbcont[0x280 / 4] * 0x140);
        *(volatile int *)0x1000B010 = (p[1] & 0x0FFFFFFF) | 0x80000000;
        *(volatile int *)0x1000B020 = 0x30;
        *(volatile int *)0x1000B000 = 0x100;
        _waitIpuIdle();
        cmd = ((mb_type[0] & 1) << 27) | (_qscqsc << 16);
        cmd2 = (_sp_dcr[0] << 26) | 0x20000000;
        _sendIpuCommand(cmd | cmd2 | (dct_type[0] << 25));
    } else {
        *(int *)((char *)_mbcont + _mbcont[0x280 / 4] * 0x140 + 0x13C) = 1;
    }
    _sp_dcr[0] = 0;
    if (_isError[0]) {
        return 0;
    }
    if ((mb_type[0] & 1) == 0) {
        _sp_dcr[0] = 1;
    }
    if ((mb_type[0] & 1) && _concealment_motion_vectors == 0) {
        PMV[0][0][0] = PMV[0][0][1] = PMV[1][0][0] = PMV[1][0][1] = 0;
        PMV[0][1][0] = PMV[0][1][1] = PMV[1][1][0] = PMV[1][1][1] = 0;
    }
    if (_picture_coding_type[0] == 2 && (mb_type[0] & 9) == 0) {
        PMV[0][0][0] = PMV[0][0][1] = PMV[1][0][0] = PMV[1][0][1] = 0;
        if (_picture_structure == 3) {
            motion_type[0] = 2;
        } else {
            motion_type[0] = 1;
            mv_field_sel[0] = _picture_structure == 2;
        }
    }
    return 1;
}

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

extern unsigned int _nextBit(int a0);
extern void _motionVector();

void _motionVectors(int PMV[2][2][2], int *dmvector, int mv_field_sel[2][2], int s, int mv_count,
                    int mv_format, int h_r_size, int v_r_size, int dmv, int mvscale)
{
    if (mv_count == 1) {
        if (mv_format == 0 && dmv == 0) {
            mv_field_sel[1][s] = mv_field_sel[0][s] = _nextBit(1);
        }
        _motionVector(PMV[0][s], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
        PMV[1][s][0] = PMV[0][s][0];
        PMV[1][s][1] = PMV[0][s][1];
    } else {
        mv_field_sel[0][s] = _nextBit(1);
        _motionVector(PMV[0][s], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
        mv_field_sel[1][s] = _nextBit(1);
        _motionVector(PMV[1][s], dmvector, h_r_size, v_r_size, dmv, mvscale, 0);
    }
}

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
            _dispatchMpegCbNodata(_theSceMpeg[0]);
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
            _dispatchMpegCbNodata(_theSceMpeg[0]);
            n = 0;
        }
    }
    return v;
}

extern int _top32;
extern int _top32len;
extern int _isError[];

int _ipuVdec(int tbl)
{
    long long v;
    int cmd;
    int bp;
    long long top;
    int m = 0;
    int n = 0;

    while ((*(volatile int *)0x10002010 & 0x80004000) == 0x80000000) {
        if (n++ >= 5001) {
            _dispatchMpegCbNodata(_theSceMpeg[0]);
            n = 0;
        }
    }
    cmd = (tbl << 26) | 0x30000000;
    *(volatile unsigned int *)0x10002000 = cmd;
    _isTop32dirty[0] = D_0054CA08[cmd >> 28];
    while ((v = *(volatile long long *)0x10002000) < 0) {
        if (m++ >= 5001) {
            _dispatchMpegCbNodata(_theSceMpeg[0]);
            m = 0;
        }
    }
    bp = *(volatile int *)0x10002020;
    /* the IPU TOP register is read once, after the command above has retired,
     * so this read is not qualified: the two busy-waits above are what needs
     * the qualifier, and the plain read is what lets the address stay a
     * constant in the load */
    top = *(long long *)0x10002030;
    _top32 = top;
    if (top < 0) {
        _top32len = (-(bp & 0x1F)) & 0x1F;
    } else {
        _top32len = 32;
    }
    _isError[0] = ((int)v == 0);
    return (short)v;
}

extern int _top32;
extern int _top32len;
extern long long _waitIpuIdle64(void);

int _peepBit(int a0)
{
    if (_isTop32dirty[0] != 0 || _top32len < a0) {
        int n = 0;

        while ((*(volatile int *)0x10002010 & 0x80004000) == 0x80000000) {
            if (n++ >= 5001) {
                _dispatchMpegCbNodata(_theSceMpeg[0]);
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
            _dispatchMpegCbNodata(_theSceMpeg[0]);
            n = 0;
        }
    }
    cmd = a0 | 0x40000000;
    *(volatile unsigned int *)0x10002000 = cmd;
    _isTop32dirty[0] = D_0054CA08[(unsigned int)cmd >> 28];
    _top32 = _waitIpuIdle64();
    _top32len = 32;
}

unsigned int _nextBit(int a0)
{
    int n = 0;
    int cmd;
    unsigned int r;

    while ((*(volatile int *)0x10002010 & 0x80004000) == 0x80000000) {
        if (n++ >= 5001) {
            _dispatchMpegCbNodata(_theSceMpeg[0]);
            n = 0;
        }
    }
    if (_isTop32dirty[0] != 0 || _top32len < a0) {
        *(volatile unsigned int *)0x10002000 = 0x40000000;
        _isTop32dirty[0] = D_0054CA08[4];
        _top32 = _waitIpuIdle64();
    }
    _top32len = 32;
    r = (unsigned int)_top32 >> (32 - a0);
    cmd = a0 | 0x40000000;
    *(volatile unsigned int *)0x10002000 = cmd;
    _isTop32dirty[0] = D_0054CA08[(unsigned int)cmd >> 28];
    _top32 = _waitIpuIdle64();
    return r;
}

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
            _dispatchMpegCallback(_theSceMpeg[0], buf);
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

/* the extension dispatch table, one entry per extension id, entry 0 is the
 * unknown-extension handler every id past the last known one falls back to */
extern void (*D_0054CA40[])(void);

void _extensionAndUserData(void)
{
    int code;

    _nextStartCode();
    while ((code = _peepBit(32)) == 0x1B5 || code == 0x1B2) {
        if (code == 0x1B5) {
            unsigned int id;

            _flushBuf(32);
            id = _nextBit(4);
            id = id > 10 ? 0 : id;
            D_0054CA40[id]();
            _nextStartCode();
        } else {
            _flushBuf(32);
            _nextStartCode();
        }
    }
}

extern int _f_code[];
extern int _intra_dc_precision;
extern int _top_field_first;
extern int _frame_pred_frame_dct;
extern int _concealment_motion_vectors;
extern int _q_scale_type;
extern int _intra_vlc_format;
extern int _alternate_scan;
extern int _repeat_first_field;
extern int _chroma_420_type;
extern int _progressive_frame;
extern int _composite_display_flag;
extern int _v_axis;
extern int _field_sequence;
extern int _sub_carrier;
extern int _burst_amplitude;
extern int _sub_carrier_phase;

void _pictureCodingExtension(void)
{
    int *p = *(int **)((char *)_theSceMpeg[0] + 0x40);

    _f_code[0] = _nextBit(4);
    _f_code[1] = _nextBit(4);
    _f_code[2] = _nextBit(4);
    _f_code[3] = _nextBit(4);
    _intra_dc_precision = _nextBit(2);
    *(int *)0x10002010 = (*(int *)0x10002010 & 0xFFFCFFFF) | (_intra_dc_precision << 16);
    _picture_structure = _nextBit(2);
    if (p[0xD4 / 4] == 0) {
        p[0xD4 / 4] = _picture_structure;
    }
    _top_field_first = _nextBit(1);
    _frame_pred_frame_dct = _nextBit(1);
    _concealment_motion_vectors = _nextBit(1);
    _q_scale_type = _nextBit(1);
    *(int *)0x10002010 = (*(int *)0x10002010 & 0xFFBFFFFF) | (_q_scale_type << 22);
    _intra_vlc_format = _nextBit(1);
    *(int *)0x10002010 = (*(int *)0x10002010 & 0xFFDFFFFF) | (_intra_vlc_format << 21);
    _alternate_scan = _nextBit(1);
    *(int *)0x10002010 = (*(int *)0x10002010 & 0xFFEFFFFF) | (_alternate_scan << 20);
    _repeat_first_field = _nextBit(1);
    _chroma_420_type = _nextBit(1);
    _progressive_frame = _nextBit(1);
    _composite_display_flag = _nextBit(1);
    if (_composite_display_flag != 0) {
        _v_axis = _nextBit(1);
        _field_sequence = _nextBit(3);
        _sub_carrier = _nextBit(1);
        _burst_amplitude = _nextBit(7);
        _sub_carrier_phase = _nextBit(8);
    }
}

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

extern int _drop_frame_flag;
extern int _time_code_hours;
extern int _time_code_minutes;
extern int _time_code_seconds;
extern int _time_code_pictures;
extern int _closed_gop;
extern int _broken_link;

/* The handle is read as an int here: the ROM issues its load ahead of the
 * register saves, which sched2 does only when that load shares int's alias
 * set with the +0xE8 store (the store's anti dependence breaks the tie). */
void _groupOfPicturesHeader(void)
{
    int *p = *(int **)(*(int *)_theSceMpeg + 0x40);

    p[0xE8 / 4] = 0;
    _tmpRefBase = _trFrameNumberA + 1;
    _tmpRefGOPreset = 1;
    _drop_frame_flag = _nextBit(1);
    _time_code_hours = _nextBit(5);
    _time_code_minutes = _nextBit(6);
    _nextBit(1);
    _time_code_seconds = _nextBit(6);
    _time_code_pictures = _nextBit(6);
    _closed_gop = _nextBit(1);
    _broken_link = _nextBit(1);
    _extensionAndUserData();
}

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
        if (_picture_structure != 3) {
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

    if (_picture_structure == 3 && _isSecondField[0] != 0) {
        _Error(D_00637148);
        _isSecondField[0] = 0;
    }
    switch (_picture_structure) {
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
    int *p = *(int **)((char *)_theSceMpeg[0] + 0x40);

    if (a1 != 0) {
        int top;
        int bot;

        if (_picture_structure == 3) {
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

INCLUDE_ASM("asm/nonmatchings/sce/libmpeg/mpc", _updateRefImage);

extern char D_00637188[];
extern void sprintf();

int _isOutSizeOK(char *p)
{
    char *c = *(char **)((char *)_theSceMpeg[0] + 0x40);
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

extern int _picture_structure;

void _cpr8(char *im)
{
    int *r = *(int **)((char *)_theSceMpeg[0] + 0x40);
    int src = *(int *)im & 0x0FFFFFFF;
    int dst = r[0xD8 / 4] & 0x0FFFFFFF;
    int e;
    int sstride;
    int dstride;
    int qwc;
    int n;
    int i;
    int j;

    if (_picture_structure == 3 || r[0xE0 / 4] == 0) {
        e = r[0xE0 / 4];
        sstride = *(int *)(im + 0x10) * 0x180;
        qwc = sstride >> 4;
        if (e != 0) {
            dstride = (e >> 4) * 0x180;
        } else {
            dstride = sstride;
        }
        n = 1;
    } else {
        e = r[0xE0 / 4];
        sstride = (*(int *)(im + 0x10) >> 1) * 0x180;
        qwc = sstride >> 4;
        dstride = (e >> 4) * 0xC0;
        n = 2;
    }
    for (j = 0; j < n; j++) {
        int d = dst;

        for (i = 0; i < *(int *)(im + 0xC); i++) {
            *(volatile int *)0x1000D480 = 0;
            *(volatile int *)0x1000D410 = src;
            *(volatile int *)0x1000D420 = qwc;
            *(volatile int *)0x1000D400 = 0x101;
            while (*(volatile int *)0x1000D400 & 0x100) {}
            *(volatile int *)0x1000D080 = 0;
            *(volatile int *)0x1000D010 = d;
            *(volatile int *)0x1000D020 = qwc;
            *(volatile int *)0x1000D000 = 0x100;
            while (*(volatile int *)0x1000D000 & 0x100) {}
            while (*(volatile int *)0x1000D020 != 0) {}
            d += dstride;
            src += sstride;
        }
        dst += r[0xE4 / 4] * 0xC0;
    }
}

extern int _isOutputPicture[];

int _markOutput(void)
{
    int *q = *(int **)((char *)_theSceMpeg[0] + 0x40);
    if (q[2] != 2) {
        int v = _totalFrames[0];
        q[2] = 2;
        q[0x2B] = v;
    }
    _isOutputPicture[0] = 1;
    return 1;
}

void _getPtsDtsFlags(char *a0, void *a1, void *a2, void *a3)
{
    char *s = *(char **)((char *)_theSceMpeg[0] + 0x40);
    long long t;
    int v88;
    int b80;
    int carry;

    if (*(int *)(s + 0x70) != 0) {
        t = *(long long *)(a0 + 0x18);
        if (t < 0 && (b80 = *(int *)(s + 0x80)) >= 0) {
            v88 = (int)*(long long *)(s + 0x88);
            carry = (int)((long long)(v88 & 1) * (*(long long *)(s + 0x78) & 1) *
                          (*(int *)(s + 0x90) & 1));
            *(long long *)a1 = b80 + ((int)((*(long long *)(s + 0x78) * v88) >> 1) + carry);
            if ((long long)(v88 & 1) * (*(long long *)(s + 0x78) & 1) != 0) {
                *(int *)(s + 0x90) = *(int *)(s + 0x90) + 1;
            }
        } else {
            *(long long *)a1 = t;
        }
    } else {
        *(long long *)a1 = *(long long *)(a0 + 0x18);
    }
    if (*(int *)(s + 0xF8) == 2) {
        long long v = *(long long *)(s + 0xF0);

        if (v >= 0) {
            *(long long *)a1 = v;
            *(int *)(s + 0xF8) = 0;
            *(long long *)(s + 0xF0) = -1;
        }
    }
    *(long long *)a2 = *(long long *)(a0 + 0x20);
    *(long long *)a3 =
        ((long long)*(int *)(a0 + 0x34) << 8) | ((long long)*(int *)(a0 + 0x38) << 7) |
        ((long long)*(int *)(a0 + 0x3C) << 6) | ((long long)*(int *)(a0 + 0x40) << 5) |
        ((long long)*(int *)(a0 + 0x30) << 3) | *(int *)(a0 + 0x2C);
}

extern unsigned int _showCount[];
extern void _getPtsDtsFlags(char *a0, void *a1, void *a2, void *a3);
extern int _isOutSizeOK(char *p);
extern void _csc_storeRefImage(char *p);
extern void _cpr8(char *p);
extern int _markOutput(void);

void _dispRefImage(char *a0, int a1)
{
    char *q = _theSceMpeg[0];
    char *r = *(char **)(q + 0x40);

    _getPtsDtsFlags(a0, q + 0x10, q + 0x18, q + 0x20);
    q = _theSceMpeg[0];
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

/* one of the three 8-byte time-stamp slots the decoder record carries for
 * each field: _getPtsDtsFlags fills the pair as a 64-bit word and the
 * display record takes its low half back as an int */
typedef union {
    long long d;
    int w[2];
} MpegStamp;

extern int _picture_structure;
extern void _getPtsDtsFlags(char *a0, void *a1, void *a2, void *a3);
extern int _isOutSizeOK(char *p);
extern void _csc_storeRefImage(char *p);
extern void _cpr8(char *p);
extern int _markOutput(void);

void _dispRefImageField(char *a0, char *a1, int a2)
{
    char *r = *(char **)((char *)_theSceMpeg[0] + 0x40);
    char *f;
    char *s;
    int m = 0;

    if (_picture_structure == 2) {
        f = a0;
        s = a1;
        m = 0x40;
    } else {
        f = a1;
        s = a0;
    }
    _getPtsDtsFlags(f, (char *)_theSceMpeg[0] + 0x10, (char *)_theSceMpeg[0] + 0x18,
                    (char *)_theSceMpeg[0] + 0x20);
    *(int *)(r + 0x80) = ((MpegStamp *)((char *)_theSceMpeg[0] + 0x10))->w[0];
    *(long long *)(r + 0x88) = 1;
    _getPtsDtsFlags(s, (char *)_theSceMpeg[0] + 0x28, (char *)_theSceMpeg[0] + 0x30,
                    (char *)_theSceMpeg[0] + 0x38);
    *(int *)(r + 0x80) = ((MpegStamp *)((char *)_theSceMpeg[0] + 0x28))->w[0];
    *(long long *)(r + 0x88) = 1;
    *(long long *)((char *)_theSceMpeg[0] + 0x20) |= m;
    *(long long *)((char *)_theSceMpeg[0] + 0x38) |= m;
    *(int *)(r + 0xCC) = *(int *)(f + 0x5C);
    *(int *)(r + 0xD0) = *(int *)(f + 0x60);
    *(int *)(r + 0xB4) = *(int *)(f + 0x44);
    *(int *)(r + 0xB8) = *(int *)(s + 0x48);
    *(int *)(r + 0xC0) = *(int *)(f + 0x50);
    *(int *)(r + 0xC4) = *(int *)(s + 0x54);
    if (_isOutSizeOK(a0) != 0 && *(int *)(a0 + 0x28) == 1 && *(int *)(a1 + 0x28) == 1) {
        *(int *)(a0 + 0x10) = *(int *)(a0 + 0x10) * 2;
        if (*(int *)(r + 0xB0) != 0) {
            _csc_storeRefImage(a0);
        } else {
            _cpr8(a0);
        }
        *(int *)(a0 + 0x10) = *(int *)(a0 + 0x10) >> 1;
        _markOutput();
    }
}
