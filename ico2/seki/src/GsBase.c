#include "common.h"
#include "debug.h"
#include "Basic.h"
#include "Packet.h"
#include "RegistPacket.h"
#include "Shadow.h"
#include "StageAnimation.h"
#include "Texture.h"
#include "staticBlur.h"
#include <libvu0.h>
#include <sifdev.h>
#include <stdio.h>
#include <string.h>
#include "typedef.h"

extern int D_0063A064;
extern int D_0063A068;
extern void sceGsSetDefDispEnv(int *env, int psm, short w, short h, short dx, short dy);

/* Point the double buffer's two display and two draw environments at the
 * frame this stage draws into: the low nine bits of each frame word carry the
 * buffer base in 64-word units and the second qword of each draw env carries
 * the zbuffer base, its psm nibble and the mask bit. */
void gsb_SetFrame(int *db, int a1, int a2, int psm, short zbp)
{
    int *disp1 = db + 0x28 / 4;
    long long zb = ((long long)zbp << 32) | 0xC0;
    short h = (short)(unsigned short)D_0063A068 / 2;
    short w = D_0063A064;

    *(int *)((char *)disp1 + 0x10) &= ~0x1FF;
    *(int *)((char *)db + 0x10) &= ~0x1FF;
    ((GifPkWord *)((char *)db + 0x150))->d =
        (((GifPkWord *)((char *)db + 0x150))->d & ~0x1FF) | 0x40;
    ((GifPkWord *)((char *)db + 0x60))->d = (((GifPkWord *)((char *)db + 0x60))->d & ~0x1FF) | 0x40;
    ((GifPkWord *)((char *)db + 0x160))->d = ((long long)(psm & 0xF) << 24) | zb;
    ((GifPkWord *)((char *)db + 0x70))->d = ((long long)(psm & 0xF) << 24) | zb;
    sceGsSetDefDispEnv(db, 0, w, h, 0, 0);
    sceGsSetDefDispEnv(disp1, 0, w, h, 0, 0);
}

extern int D_0028F4C0[];
extern int D_0063A058;
extern int D_0063A064;
extern int D_0063A068;
extern int D_00639F80;
extern float D_00639F88;
extern float D_00639F8C;
extern float D_00639F90;
extern int buffer_ID;
extern char D_0054E170[];
extern void sceGsSyncV(int a0);
extern void sceGsResetGraph(short mode, short inter, short omode, short ffmd);
extern void sceGsSetDefDBuff(void *db, short psm, short w, short h, short ztst, short zpsm,
                             short flag);
extern int sceGsSyncPath(int mode, int timeout);
extern void FlushCache(int mode);
extern void gsb_SetVSMatrix(int w, int h, float d);

/* Bring the GS up for the frame size the stage record asks for: 512 by 448
 * interlaced, 512 by 512 in the tall mode and 512 by 448 otherwise, then set
 * the double buffer up, hand the first frame over and put the view scale back
 * to one. */
void gsb_Init(void *db)
{
    int omode = 2;

    sceGsSyncV(0);
    D_0063A058 = 1;
    D_00639F80 = 0;
    switch (D_0028F4C0[0]) {
    case 0:
        D_0063A064 = 0x200;
        D_0063A068 = 0x1C0;
        break;
    case 1:
        D_0063A064 = 0x200;
        D_0063A068 = 0x200;
        omode = 3;
        break;
    }
    sceGsResetGraph(0, D_0028F4C0[1] == 1, omode, 1);
    sceGsSetDefDBuff(db, 0, D_0063A064, D_0063A068, 2, 0x30, D_0063A058);
    gsb_SetFrame(db, 0, 0, 0x30, 2);
    sceGsSyncV(0);
    buffer_ID = 0;
    FlushCache(0);
    sceGsSwapDBuff(db, buffer_ID);
    while (sceGsSyncPath(1, 0) != 0) {
        debug_StdPrintfDummy(D_0054E170);
    }
    gsb_SetVSMatrix(D_0063A064, D_0063A068, 512.0f);
    D_00639F88 = 1.0f;
    D_00639F90 = 1000.0f;
    D_00639F8C = 1.0f;
}

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/GsBase", gsb_Reduction);

extern unsigned char D_00639F98;
extern unsigned char D_00639F99;
extern unsigned char D_00639F9A;
extern unsigned char D_00639F9B;
/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket(void);
/* kept local: this TU's uses of gif_SetGsReg do not fit the prototype in GifPacket.h */
extern void gif_SetGsReg(int a0, long long a1);
/* kept local: this TU's uses of gif_StartPacketPriPath1 do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPriPath1(int a0);
extern GifDpk D_004EE6F0;

/* Reverted to asm 2026-09-17 (chain 3 pass 16): 163 of 163 instructions and
 * the first 77 word for word.  The body is derived: two rectangles built as
 * struct initialisers (ROM's ldl/ldr pair copies prove the 16-byte record),
 * the five register writes, and twelve 64-bit words into the display list
 * through an inline handle.  The residual is the register permutation of
 * the packet block (ROM has the context base in $6, the write pointer in $3
 * and the four colour bytes in $5 $4 $7 $2) and the scheduling that follows
 * it.  Derived body:
 * tails/seeds/GsBase.c3p16_gsb_KeepFrameBuffer_163of163_strict85_TU.c. */
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/GsBase", gsb_KeepFrameBuffer);

extern int fadeStatus;
extern float D_0063C124;
extern int D_0063B13C;
/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int pri);

/* Reverted to asm 2026-09-17 (chain 3 pass 16): 223 of 224 instructions, the
 * first 65 word for word and the whole tail aligned one instruction on.
 * The shape is derived: a switch on fadeStatus whose default arm is a goto
 * to a clear block placed after the debug print (ROM puts it between the
 * main path and the epilogue), the level step and the two end tests, the
 * clamp into fadeColor[3], and the packet, whose last six words are the
 * inlined A+D writes of an untextured sprite.  The residual is one FPU
 * constant reload: ROM shares $f0 between the 0.0 and 128.0 compares and
 * reloads 0.0 on the join, the built code keeps the level in $f3 instead.
 * Derived body: tails/seeds/GsBase.c3p16_gsb_fade_223of224_strict145_TU.c. */
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/GsBase", gsb_fade);

extern int CurrentTargetGObjSub;
extern StageSetting D_0028F720;

void gsb_SetMotionBlur(void)
{
    int i = CurrentTargetGObjSub;

    if (i == 0) {
        SetMotionBlur(D_0028F720.motionBlur);
    } else {
        SetMotionBlur(D_0028F720.subMotionBlur[i - 1]);
    }
}

extern int D_0063B60C;
extern int D_00639FA4;
extern float D_00639FA8;
extern float D_00639FAC;
extern char D_00639FB0[];
extern int D_0028F814;
extern void SetMotionBlur(int on);
extern void gif_EndPacketPath1(void);

/* Reverted to asm 2026-09-17 (chain 3 pass 16): 223 of 226 instructions with
 * the first 82 word for word and the tail aligned one instruction on.  The
 * shape is derived: the two letterbox bars as one `GsbRect r[2]` array
 * initialiser (ROM's four ldl/ldr pairs copy the 32 bytes), the alpha ease
 * towards 128 or 0 on the demo state, the two clamps, and a two-iteration
 * loop whose body is an inlined untextured sprite.  MEASURED RESIDUAL: ROM
 * carries two extra lui (one is %hi(D_0028F814) computed in both
 * predecessors of the SetMotionBlur call, the other still unattributed),
 * one extra hazard nop before the first bc1f (the built code spends that
 * slot on the branch delay instead) and spells one sp-relative address with
 * ori where the built code uses addiu.  Derived body:
 * tails/seeds/GsBase.c3p16_gsb_scissorOnDemo_223of226_strict141_TU.c. */
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/GsBase", gsb_scissorOnDemo);

extern int D_0028F4C0[];
extern char D_00639FB8[];
/* kept local: this TU's uses of gif_SetGsReg do not fit the prototype in GifPacket.h */
extern void gif_SetGsReg(int a0, long long a1);
/* kept local: this TU's uses of gif_EndPacketPath1 do not fit the prototype in GifPacket.h */
extern void gif_EndPacketPath1(void);
/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int pri);
/* kept local: this TU's uses of gif_SetAlpha do not fit the prototype in GifPacket.h */
extern void gif_SetAlpha(int a0, int a1, int a2);
/* kept local: this TU's uses of gif_MakeSpriteNoTexture do not fit the prototype in GifPacket.h */
extern void gif_MakeSpriteNoTexture(int x, int y, int w, int h, unsigned int z, unsigned char *col,
                                    int prim);

/* Darken the whole frame by the stage record's brightness step: a full screen
 * white sprite in destination-alpha blend whose alpha is the step, clamped to
 * 0 to 15 and skipped at 0. */
void gsb_controlBrightness(void)
{
    int v = D_0028F4C0[0x2C / 4];

    if (v < 0) {
        v = D_0028F4C0[0x2C / 4] = 0;
    }
    if (v >= 0x10) {
        v = D_0028F4C0[0x2C / 4] = 0xF;
    }
    if (v != 0) {
        if (D_0063B13C & 1) {
            debug_Printf(0x212, D_0063A068 / 2 - 8, 0xCCCCCC00, D_00639FB8);
        }
        gif_StartPacketPri(0xB);
        {
            unsigned char col[4] = {0xFF, 0xFF, 0xFF, D_0028F4C0[0x2C / 4]};

            gif_SetGsReg(0x47, 0x30000);
            gif_SetGsReg(0x4E, 0x1300000C0LL);
            gif_SetAlpha(1, 7, 0);
            gif_MakeSpriteNoTexture((0x800 - D_0063A064 / 2) << 4, (0x800 - D_0063A068 / 2) << 4,
                                    D_0063A064 << 4, D_0063A068 << 4, 0xFFFFFFFE, col, 1);
            gif_EndPacketPath1();
        }
    }
}

/* Reverted to asm 2026-09-17 (chain 3 pass 16): 233 of 233 instructions with
 * the derived shape and the exact .rodata.  The body is six 16-byte source
 * and destination rectangles as local initialisers, the 0x80808080 colour
 * copied out of D_00639FC0 (declared as an incomplete array so the address
 * is absolute, not gp-relative), the stage record's two anti-alias levels
 * read into an `int lv[2]` (an array, which is what keeps them on the
 * frame the way ROM re-reads them), and up to four sensitive-sprite blends
 * whose TEX0 is written as two groups so the 0x400000000 TCC bit stays a
 * separate hoisted constant.  DATA the landing would emit: .rodata 96
 * bytes, byte-identical to D_0054E310..D_0054E36F (VMA 0x0054E310, ROM
 * offset 0x0044E310), six records {4,4,0x2000,0x2000} {4,4,0x1000,0x1000}
 * {4,4,0x800,0x800} {-0x1004,-0x1004,0x2000,0x2000} {-0x804,-0x804,0x1000,
 * 0x1000} {-0x404,-0x404,0x800,0x800}.  RESIDUAL: the callee-saved count
 * (ROM holds the first tex_GetTWTH result and the TCC constant in $16 and
 * $17, frame 0xB0; the built code keeps one and spills, frame 0xA0) and the
 * scheduling that follows.  Derived body:
 * tails/seeds/GsBase.c3p16_gsb_antiAlias_233of233_strict212_TU.c. */
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/GsBase", gsb_antiAlias);

/* kept local: this TU's uses of dl_GetPri do not fit the prototype in DisplayList.h */
extern int dl_GetPri(void);
/* kept local: this TU's uses of dl_SetDLPriority do not fit the prototype in DisplayList.h */
extern void dl_SetDLPriority();
/* kept local: this TU's uses of gif_EndPacketPath1 do not fit the prototype in GifPacket.h */
extern void gif_EndPacketPath1(void);
/* kept local: this TU's uses of gif_SetGsReg do not fit the prototype in GifPacket.h */
extern void gif_SetGsReg(int a0, long long a1);
/* kept local: this TU's uses of gif_StartPacketPriPath1 do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPriPath1(int a0);

void gsb_setNormalReg(int ctx)
{
    dl_SetDLPriority();
    gif_StartPacketPriPath1(dl_GetPri());
    gif_SetGsReg(0x47, 0x50000);
    gif_SetGsReg(0x4E, 0x300000C0);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x8000000080LL);
    gif_EndPacketPath1();
}

void gsb_setSemitransReg(int ctx)
{
    dl_SetDLPriority();
    gif_StartPacketPriPath1(dl_GetPri());
    gif_SetGsReg(0x47, 0x5140D);
    gif_SetGsReg(0x4E, 0x300000C0);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x810000807FLL);
    gif_EndPacketPath1();
}

void gsb_setSpecularReg(int ctx)
{
    dl_SetDLPriority();
    gif_StartPacketPriPath1(dl_GetPri());
    gif_SetGsReg(0x47, 0x5C000);
    gif_SetGsReg(0x4E, 0x1300000C0LL);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x8000000080LL);
    gif_EndPacketPath1();
}

void gsb_setParticleReg(int ctx)
{
    dl_SetDLPriority();
    gif_StartPacketPriPath1(dl_GetPri());
    gif_SetGsReg(0x47, 0x50000);
    gif_SetGsReg(0x4E, 0x1300000C0LL);
    gif_SetGsReg(0x4A, 0);
    gif_SetGsReg(0x3B, 0x8000000080LL);
    gif_EndPacketPath1();
}

extern int game_pause;
extern char *matrixptr;
extern char D_0054E370[];
extern void _MulMatrix(void *d, void *a, void *b);
extern void _InversMatrix(void *d, void *s);
extern void _CopyMatrix(void *d, void *s);
/* kept local: this TU's uses of dl_OpenDma do not fit the prototype in DisplayList.h */
extern void dl_OpenDma(int a0, char *a1, int a2);
/* kept local: this TU's uses of dl_CloseDma do not fit the prototype in DisplayList.h */
extern void dl_CloseDma(void);

/* Build the frame's common matrix packet: the three view matrices the stage
 * needs, the inverse of the view, and the display list that uploads them to
 * VU memory, opened once for each of the thirteen list priorities. */
void gsb_MakeCommonMatrix(void)
{
    GifPkWord *p;
    GifPkWord *q;
    int i;

    if (game_pause == 0) {
        return;
    }
    i = 0;
    _MulMatrix(matrixptr + 0x100, matrixptr + 0xC0, matrixptr + 0x80);
    _MulMatrix(matrixptr + 0x200, matrixptr + 0x1C0, matrixptr + 0x80);
    _MulMatrix(matrixptr + 0x280, matrixptr + 0x240, matrixptr + 0x80);
    _InversMatrix(matrixptr + 0x380, matrixptr + 0x80);
    p = (GifPkWord *)D_004EE6F0.ptr;
    D_004EE6F0.gif = 0;
    D_004EE6F0.dma = (char *)p;
    D_004EE6F0.end = 0;
    D_004EE6F0.tail = (char *)p;
    p[0].d = 0x10000011;
    D_004EE6F0.ptr = (unsigned long long *)((char *)p + 8);
    p[1].w[0] = 0x13000000;
    D_004EE6F0.ptr = (unsigned long long *)((char *)p + 0xC);
    D_004EE6F0.gif = (char *)p + 0xC;
    p[1].w[1] = 0x6C100000;
    D_004EE6F0.ptr = (unsigned long long *)((char *)p + 0x10);
    _CopyMatrix((char *)p + 0x10, D_0054E370);
    D_004EE6F0.ptr = (unsigned long long *)((char *)D_004EE6F0.ptr + 0x40);
    _CopyMatrix(D_004EE6F0.ptr, matrixptr + 0x100);
    D_004EE6F0.ptr = (unsigned long long *)((char *)D_004EE6F0.ptr + 0x40);
    _CopyMatrix(D_004EE6F0.ptr, matrixptr + 0x340);
    D_004EE6F0.ptr = (unsigned long long *)((char *)D_004EE6F0.ptr + 0x40);
    _CopyMatrix(D_004EE6F0.ptr, matrixptr + 0x380);
    q = (GifPkWord *)D_004EE6F0.ptr;
    D_004EE6F0.ptr = (unsigned long long *)((char *)q + 0x40);
    q[8].w[0] = 0x13000000;
    D_004EE6F0.ptr = (unsigned long long *)((char *)q + 0x44);
    q[8].w[1] = 0;
    D_004EE6F0.ptr = (unsigned long long *)((char *)q + 0x48);
    q[9].w[0] = 0;
    D_004EE6F0.ptr = (unsigned long long *)((char *)q + 0x4C);
    q[9].w[1] = 0;
    D_004EE6F0.ptr = (unsigned long long *)((char *)q + 0x50);
    D_004EE6F0.tail = (char *)q + 0x50;
    q[10].d = 0x60000000;
    D_004EE6F0.ptr = (unsigned long long *)((char *)q + 0x58);
    q[11].w[0] = 0;
    D_004EE6F0.ptr = (unsigned long long *)((char *)q + 0x5C);
    q[11].w[1] = 0;
    D_004EE6F0.ptr = (unsigned long long *)((char *)q + 0x60);
    do {
        dl_SetDLPriority(i);
        i++;
        dl_OpenDma(5, D_004EE6F0.dma, 0);
        dl_CloseDma();
    } while (i < 0xD);
}

/* Open the frame's first display list: one DMA tag, the two VIF words that
 * hand path 1 to the GS, a second tag for the register run, and then the
 * default register set for each of the thirteen contexts. */
void gsb_SetGsDefault(void)
{
    GifDpk *d = &D_004EE6F0;
    GifPkWord *p = (GifPkWord *)d->ptr;

    d->gif = 0;
    d->tail = (char *)p;
    d->dma = (char *)p;
    d->end = 0;
    p[0].d = 0x10000000;
    d->ptr = (unsigned long long *)((char *)p + 8);
    p[1].w[0] = 0x3000100;
    d->ptr = (unsigned long long *)((char *)p + 0xC);
    p[1].w[1] = 0x2000180;
    d->ptr = (unsigned long long *)((char *)p + 0x10);
    d->tail = (char *)p + 0x10;
    p[2].d = 0x60000000;
    d->ptr = (unsigned long long *)((char *)p + 0x18);
    p[3].w[0] = 0;
    d->ptr = (unsigned long long *)((char *)p + 0x1C);
    p[3].w[1] = 0;
    d->ptr = (unsigned long long *)((char *)p + 0x20);
    dl_SetDLPriority(0);
    dl_OpenDma(5, d->dma, 0);
    dl_CloseDma();
    gsb_MakeCommonMatrix();
    gsb_setNormalReg(0);
    gsb_setSemitransReg(1);
    gsb_setSemitransReg(2);
    gsb_setParticleReg(6);
    gsb_setSpecularReg(4);
    gsb_setNormalReg(7);
    gsb_setNormalReg(8);
    gsb_setNormalReg(9);
    gsb_setNormalReg(0xA);
    gsb_setNormalReg(0xB);
    gsb_setNormalReg(0xC);
}

extern char D_0054E3B0[];

/* Lay the film grain texture over the frame: the noise texture at texture
 * slot 10, drawn as one full screen sprite whose colour comes from the
 * stage record's grain tint for this target and whose UV step is the
 * record's grain scale, passed as raw bits in both halves of the register. */
void gsb_filmNoise(void)
{
    int n = tex_GetTextureNo(D_0054E3B0);
    char *st;
    float scale;

    if (n < 0) {
        return;
    }
    st = (char *)&D_0028F720;
    scale = *(float *)(st + 0x170);
    tex_TransTexture(n, 0xA);
    gif_StartPacketPriPath1(dl_GetPri());
    gif_SetGsReg(8, 0);
    gif_SetGsReg(0x4E, 0x1300000C0LL);
    gif_SetGsReg(0x47, 0x30000);
    gif_SetGsReg(0x49, 0);
    gif_SetGsReg(0x42, 0x44);
    gif_SetGsReg(0, 0x56);
    gif_SetGsReg(1, ((long long)*(int *)(st + ((CurrentTargetGObjSub - 1) << 4) + 0x13C) << 24) |
                        0x3F80000000808080LL);
    gif_SetGsReg(2, 0);
    gif_SetGsReg(5, 0xFFFFFFFF70007000LL);
    gif_SetGsReg(2, ((long long)*(unsigned int *)&scale << 32) | *(unsigned int *)&scale);
    gif_SetGsReg(5, 0xFFFFFFFF90009000LL);
    gif_EndPacketPath1();
}

extern char D_0054E408[];
extern char D_00639FC8[];
extern char D_00639FD0[];
extern char D_00639FD8[];
extern int D_0063B60C;
extern int fadeStatus;
extern float D_0063C124;
extern unsigned char D_0063BCB3;
extern int D_00639FC4;
extern int D_0063AA00;
extern int D_0063A054;
extern int staffRollStartFlag;
extern void FullScreenEffectAfter(void);
extern void shadow_Draw(void);
extern void fog_DrawFog(void);
extern void MotionBlur(void);
extern void gsb_antiAlias(void);
extern void gsb_KeepFrameBuffer(void);
extern void staffRollMain(void);
extern void gsb_fade(void);
extern void gsb_scissorOnDemo(void);

/* Everything the frame still owes after the scene is drawn: the debug read
 * outs, the full screen effect, the shadow and fog passes, the motion blur,
 * the anti alias pass, the film grain and the brightness step, the kept frame
 * buffer, the staff roll and last the fade and the demo scissor. */
int gsb_PostEffect(void)
{
    if (D_0063B13C & 1) {
        debug_Printf(0xA, D_0063A068 / 2 - 8, 0xCCCCCC00, D_0054E408, D_0063B60C, fadeStatus,
                     D_0063C124, D_0063BCB3);
    }
    if (D_0028F4C0[0x18 / 4] != 0 && (D_0063B13C & 1)) {
        debug_Printf(0x230, D_0063A068 / 2 - 8, 0xCCCCCC00, D_00639FC8);
    }
    if (D_0028F4C0[0x14 / 4] != 0 && (D_0063B13C & 1)) {
        debug_Printf(0x23A, D_0063A068 / 2 - 8, 0xCCCCCC00, D_00639FD0);
    }
    FullScreenEffectAfter();
    if (D_00639FC4 != 0) {
        shadow_Draw();
    }
    fog_DrawFog();
    MotionBlur();
    gsb_antiAlias();
    if (D_0063AA00 > 0 && CurrentTargetGObjSub != 0) {
        gsb_filmNoise();
    }
    gsb_controlBrightness();
    if (D_0063A054 != 0) {
        gsb_KeepFrameBuffer();
        if (D_0063B13C & 1) {
            debug_Printf(0x226, D_0063A068 / 2 - 8, 0xCCCCCC00, D_00639FD8);
        }
    }
    if (staffRollStartFlag != 0) {
        staffRollMain();
    }
    gsb_fade();
    gsb_scissorOnDemo();
    return D_0063A054;
}

extern int D_00639FDC;
extern int fall_death_active;
extern int screen_offset_y;
extern int D_0063A074;
extern int D_0063A078;
extern int D_00639F84;
extern char D_0054E428[];
extern char D_0054E438[];
extern char D_0054E448[];
extern char D_0054E458[];
extern char D_0028F4F0[];
extern void sceGsResetPath(void);
extern void sceGsSyncV(int a0);
/* kept local: the declaration in GsBase.h changes this TU codegen */
extern void gsb_Init(void *p);
/* kept local: this TU's uses of dl_Init do not fit the prototype in DisplayList.h */
extern void dl_Init(void);

void gsb_InitGSSystem(void)
{
    fall_death_active = 0;
    screen_offset_y = 0;
    if (D_00639FDC != 0) {
        sceGsResetPath();
        sceVpu0Reset();
        debug_StdPrintfDummy(D_0054E428);
        dma_init();
        debug_StdPrintfDummy(D_0054E438);
        matrix_init();
        debug_StdPrintfDummy(D_0054E448);
        tex_Init();
        debug_StdPrintfDummy(D_0054E458);
        sceGsSyncV(0);
        gsb_Init(D_0028F4F0);
        sceGsSyncV(0);
        dl_Init();
        D_00639FDC = 0;
    } else {
        debug_StdPrintfDummy(D_0054E428);
        dma_init();
        debug_StdPrintfDummy(D_0054E448);
        tex_Init();
    }
    resetmallocseki();
    pac_Init();
    reg_Init();
    shadow_Init();
    D_00639F84 = 1;
    D_0063A074 = D_0063A078 = 0;
}

extern int frame_count;
extern int buffer_ID;
extern int odd_even;
extern int D_00639FC4;
extern int D_0063A06C;
extern int GlobalTimer;
extern void sceGsSetHalfOffset(void *env, short x, short y, int field);
extern void gsb_Reduction(void);
extern void debug_FlushFont(void);
extern void FlushCache(int mode);
extern void shadow_Reset(void);
extern void FullScreenEffectBefore(void);
extern void light_ResetLight(void);
extern void tex_ResetVram(void);

/* One frame boundary: take the field parity from the GS CSR, run the
 * reduction pass, flip the double buffer and hand the display list back
 * either swapped or cleared, then reopen the frame's register set. */
void gsb_UpdateGSSystem(int keep)
{
    char *draw;

    odd_even = (*(volatile unsigned long long *)0x12001000 >> 13) & 1;
    gsb_Reduction();
    if (D_00639F84 == 0) {
        dl_Clear();
        return;
    }
    debug_FlushFont();
    frame_count++;
    buffer_ID = frame_count & 1;
    FlushCache(0);
    sceGsSwapDBuff(D_0028F4F0, buffer_ID);
    if (buffer_ID != 0) {
        draw = D_0028F4F0 + 0x150;
    } else {
        draw = D_0028F4F0 + 0x60;
    }
    sceGsSetHalfOffset(draw, (short)((float)screen_offset_y + 2048.0f),
                       (short)((float)fall_death_active + 2048.0f), odd_even == 0);
    tex_ResetVram();
    if (keep == 0) {
        dl_Swap();
    } else {
        dl_Clear();
    }
    gsb_SetGsDefault();
    D_00639FC4 = 0;
    shadow_Reset();
    D_00639FC4 = 1;
    FullScreenEffectBefore();
    D_0063A06C = GlobalTimer;
    light_ResetLight();
}

extern int D_0028F4C0[];
/* kept local: this TU passes every argument of sceGsResetGraph as a short */
extern void sceGsResetGraph(short mode, short inter, short omode, short ffmd);
extern void sceGsSetHalfOffset(void *env, short x, short y, int field);

/* Reset the GS between stages: reopen the paths, reset the VU0 and the DMA,
 * put the graphics mode back, take the field parity out of the GS CSR and
 * flip the double buffer, then re-open the frame's display list. */
void gsb_ResetGSSystem(void)
{
    char *draw;

    sceGsResetPath();
    sceVpu0Reset();
    dma_init();
    sceGsResetGraph(0, D_0028F4C0[1] == 1, (unsigned short)D_0028F4C0[0] + 2, 1);
    frame_count++;
    buffer_ID = frame_count & 1;
    odd_even = (*(volatile unsigned long long *)0x12001000 >> 13) & 1;
    FlushCache(0);
    sceGsSwapDBuff(D_0028F4F0, buffer_ID);
    if (buffer_ID != 0) {
        draw = D_0028F4F0 + 0x150;
    } else {
        draw = D_0028F4F0 + 0x60;
    }
    sceGsSetHalfOffset(draw, (short)((float)screen_offset_y + 2048.0f),
                       (short)((float)fall_death_active + 2048.0f), odd_even == 0);
    tex_ResetVram();
    dl_Swap();
    gsb_SetGsDefault();
}

/* Reverted to asm 2026-09-17 (chain 3 pass 16): 313 of 313 instructions with
 * the whole body derived.  It builds the four view matrices from the view
 * record gsb_SetVSMatrix fills: the screen scale (vs[0] down the diagonal
 * with the w row swapped in), the perspective projection for the main view,
 * the half scale projection for the reduction buffer, and the 1500 unit
 * orthographic pair for the reflection, multiplying two of them into
 * matrixptr+0x640 and +0x680.  LEVERS ALREADY MEASURED: the two range
 * terms are written `-vs[5] + vs[6]` and `-vs[7] + vs[8]` (ROM's neg.s plus
 * add.s, not sub.s), which took the function from 311 of 313 and 263
 * differing words to 313 of 313 and 129; the screen half size pair is a
 * `union { float f[4]; long long d[2]; }` initialiser, which is what makes
 * ROM copy it with ld/sd rather than lwl/lwr; 1500.0f twice is a static
 * const float[4] in .rodata (VMA 0x0054E478, ROM offset 0x0044E478, bytes
 * 1500.0 1500.0 0.0 0.0) that a landing would emit and that needs a carve
 * row.  RESIDUAL: the floating point register assignment (ROM holds the far
 * and near terms in $f26 and $f25, the four scale terms in $f21 $f22 $f23
 * $f20 and the three constants in $f24 $f27 $f28) and the load order that
 * follows from it; the instruction count and every mnemonic class match.
 * Derived body:
 * tails/seeds/GsBase.c3p16_gsb_SetVSMatrixSub_313of313_strict129_TU.c. */
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/GsBase", gsb_SetVSMatrixSub);
/* Reverted to asm 2026-09-17 (chain 3 pass 16): 156 of 159 instructions, the
 * whole body derived and the tail word for word; the residual is three
 * `addiu $2, $6, %lo(D_0028F720)` that ROM keeps as a separate address
 * value (0xE0 stays the load displacement) where the built code folds the
 * lo_sum and the offset into each load.  Derived body and mechanism:
 * tails/seeds/GsBase.c3p16_gsb_SetVSMatrix_156of159_strict112_TU.c. */
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/GsBase", gsb_SetVSMatrix);

/* Clip a box against the current matrix: transform its eight corners with the
 * matrix in $vf4 to $vf7 and read the clip flags out of $vi18.  All eight
 * corners outside one plane gives 0, no corner clipped at all gives -1, and
 * the second pass re-clips against a 0.99 w so a corner that only just crosses
 * the near plane still counts as visible: 2 when it does, 1 when it does not. */
int gsb_ClipBox(float *p)
{
    int all = 0x3F;
    int any = 0;
    int c = 0;
    float *q = p;
    int i;

    for (i = 0; i < 8; q += 4, i++) {
        int cf;

        __asm__ __volatile__(".set noreorder\n\t"
                             "lqc2 $vf8, 0x0(%1)\n\t"
                             "vmulax.xyzw ACC, $vf4, $vf8x\n\t"
                             "vmadday.xyzw ACC, $vf5, $vf8y\n\t"
                             "vmaddaz.xyzw ACC, $vf6, $vf8z\n\t"
                             "vmaddw.xyzw $vf10, $vf7, $vf0w\n\t"
                             "vclipw.xyz $vf10, $vf10w\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "cfc2.ni %0, $vi18\n\t"
                             ".set reorder"
                             : "=r"(cf)
                             : "r"(q)
                             : "memory");
        all &= cf;
        any |= cf;
    }
    if (all & 0x2F) {
        return 0;
    }
    if ((any & 0x2F) == 0) {
        return -1;
    }
    for (i = 0; i < 8; p += 4, i++) {
        int cf;

        __asm__ __volatile__(".set noreorder\n\t"
                             "mfc1 $8, %1\n\t"
                             "lqc2 $vf8, 0x0(%2)\n\t"
                             "qmtc2.ni $8, $vf1\n\t"
                             "vmulx.w $vf1, $vf0, $vf1x\n\t"
                             "vmulax.xyzw ACC, $vf4, $vf8x\n\t"
                             "vmadday.xyzw ACC, $vf5, $vf8y\n\t"
                             "vmaddaz.xyzw ACC, $vf6, $vf8z\n\t"
                             "vmaddw.xyzw $vf10, $vf7, $vf0w\n\t"
                             "vclipw.xyz $vf10, $vf1w\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "cfc2.ni %0, $vi18\n\t"
                             ".set reorder"
                             : "=r"(cf)
                             : "f"(0.99f), "r"(p)
                             : "memory");
        c |= cf;
    }
    return (c & 0x20) ? 2 : 1;
}

typedef struct sceCdCLOCK {
    unsigned char stat;
    unsigned char second;
    unsigned char minute;
    unsigned char hour;
    unsigned char pad;
    unsigned char day;
    unsigned char month;
    unsigned char year;
} sceCdCLOCK;

extern int stage_no;
extern char D_005F5D90[];
extern char D_0063A000[];
extern char D_0054E4F8[];
extern char D_0054E518[];
extern char D_0054E530[];
extern char D_0067BA88[];
extern int sceCdReadClock(sceCdCLOCK *c);

void appendLogFile(void)
{
    sceCdCLOCK clock;
    int fd;

    sceCdReadClock(&clock);
    sprintf(D_0067BA88, D_0054E4F8);
    fd = debugSceOpen(D_0067BA88, 0x302);
    if (fd < 0) {
        debug_StdPrintfDummy(D_0054E518);
        return;
    }
    sprintf(D_0067BA88, D_0054E530, clock.year | 0x2000, clock.month, clock.day, clock.hour,
            clock.minute, clock.second, D_005F5D90 + stage_no * 0x194, D_0063A000);
    sceLseek(fd, 0, 2);
    sceWrite(fd, D_0067BA88, strlen(D_0067BA88));
    debugSceClose(fd);
    debug_StdPrintfDummy(D_0067BA88);
}

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/GsBase", gsb_FilmNoiseTool);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/GsBase", gsb_StageSettingTool);

extern int D_00639F78;
extern char D_0054EF00[];
extern char D_0054EF20[];
extern char D_0054EF30[];
extern char D_0063A038[];
extern char D_0063A040[];
extern char D_0067BB88[];
extern char D_0067BC88[];
extern int D_00639F7C;

void updateOtherEditingLockFlag(void)
{
    char buf[0x100];
    int fd;

    sprintf(D_0067BB88, D_0054EF00, D_005F5D90 + stage_no * 0x194);
    D_00639F78 = 0;
    fd = debugSceOpen(D_0067BB88, 1);
    if (fd >= 0) {
        sceRead(fd, buf, 0x100);
        debugSceClose(fd);
        sscanf(buf, D_0063A038, D_0067BC88);
    }
    if (fd < 0 || strcmp(D_0063A040, D_0067BC88) == 0) {
        debug_StdPrintfDummy(D_0054EF20);
        D_00639F7C = 0;
    } else if (strcmp(D_0063A000, D_0067BC88) != 0) {
        debug_StdPrintfDummy(D_0054EF30, D_0067BC88);
        D_00639F78 = 1;
    } else {
        D_00639F7C = 1;
    }
}

extern char D_0054EF40[];
extern char D_0054EF58[];

/* the line-2873 helper the PAL listing shows inlined at the head of
   updateOtherEditingLockFlag, createLockFile and removeLockFile */
/* static helper the listing places at GsBase.c line 2873, inlined at the head of
 * updateOtherEditingLockFlag, createLockFile and removeLockFile; never emitted
 * out of line, so it has no MAIN.MAP symbol and this name is ours. */
static inline char *makeLockFileName(void)
{
    sprintf(D_0067BB88, D_0054EF00, D_005F5D90 + stage_no * 0x194);
    return D_0067BB88;
}

int createLockFile(void)
{
    char buf[0x100];
    char *name = makeLockFileName();
    int fd = debugSceOpen(name, 0x602);
    if (fd < 0) {
        debug_StdPrintfDummy(D_0054EF40);
        return 0;
    }
    sprintf(buf, D_0063A038, D_0063A000);
    sceWrite(fd, buf, strlen(buf) + 1);
    debugSceClose(fd);
    debug_StdPrintfDummy(D_0054EF58, name, buf);
    D_00639F7C = 1;
    return 1;
}

extern char D_0054EF78[];
extern char D_0054EF90[];

int removeLockFile(void)
{
    char buf[0x100];
    char *name = makeLockFileName();
    int fd = debugSceOpen(name, 0x602);
    if (fd < 0) {
        debug_StdPrintfDummy(D_0054EF78);
        return 0;
    }
    sprintf(buf, D_0063A038, D_0063A040);
    sceWrite(fd, buf, strlen(buf) + 1);
    debugSceClose(fd);
    debug_StdPrintfDummy(D_0054EF90, name, D_0063A000);
    D_00639F7C = 0;
    return 1;
}

typedef struct {
    char *name;  /* 0x0 */
    int (*fn)(); /* 0x4 */
    int arg;     /* 0x8 */
} GsbMenuItem;

extern GsbPad D_0028F8F0[];
extern GsbMenuItem D_00290820[];
extern GsbMenuItem D_00290830[];
extern int D_0054F078[];
extern int D_0054F07C[];
extern char D_0054F080[];
extern char D_0063A050[];
extern int D_0063A048;
extern int D_0063A04C;

int gsb_StageSetting(void)
{
    int i;
    D_00639F7C = 1;
    if (D_0063A04C >= 0) {
        if (D_00290830[D_0063A04C].fn != 0) {
            int r = D_00290830[D_0063A04C].fn(D_00290830[D_0063A04C].arg);
            if (r == -1) {
                D_0063A04C = r;
            }
            return 0;
        }
    }
    if (D_00639F7C) {
        for (i = 0; i < 11; i++) {
            debug_PrintfDummy(18, (i + 1) * 8 + 0x1E, D_0054F078[(D_0063A048 == i) ? 1 : 0],
                              D_0063A050, D_00290830[i].name);
        }
        if (D_0028F8F0[0].rep & 0x4000) {
            D_0063A048++;
            if (D_0063A048 >= 11)
                D_0063A048 = 0;
        }
        if (D_0028F8F0[0].rep & 0x1000) {
            D_0063A048--;
            if (D_0063A048 < 0)
                D_0063A048 = 10;
        }
        if (D_0028F8F0[0].trg & 0x20) {
            D_0063A04C = D_0063A048;
        }
    } else {
        debug_PrintfDummy(26, 22, 0xFFFFFFFF, D_0054F080);
        debug_PrintfDummy(18, 38, D_0054F07C[0], D_0063A050, D_00290820[0].name);
        if (D_0028F8F0[0].trg & 0x20) {
            D_00290820[0].fn(1);
        }
    }
    return (D_0028F8F0[0].trg & 0x40) ? -1 : 0;
}

extern unsigned char D_0067BCD0[];

inline void gsb_SetBGColor(void *a0, int r, int g, int b)
{
    unsigned long long bg = ((long long)b << 16) | ((long long)g << 8);
    unsigned long long v = r | 0x3F80000000000000ULL;
    v |= bg;
    *(int *)&D_0067BCD0[0] = r;
    v |= 0x80000000;
    *(int *)&D_0067BCD0[4] = g;
    *(int *)&D_0067BCD0[8] = b;
    *(int *)&D_0067BCD0[0xC] = 0x80;
    *(unsigned long long *)((char *)a0 + 0x1F0) = v;
    *(unsigned long long *)((char *)a0 + 0x100) = v;
}

inline void gsb_GetBGColor(unsigned char *a0)
{
    a0[0] = D_0067BCD0[0];
    a0[1] = D_0067BCD0[4];
    a0[2] = D_0067BCD0[8];
    a0[3] = D_0067BCD0[0xC];
}

extern int D_0054E3C0[];
extern char D_0054E3D8[];
extern char D_0054E3F0[];

inline void gsb_ResetFilmNoise(void)
{
    int i;
    for (i = 0; i < 5; i++) {
        if (D_0054E3C0[i] != -1) {
            if (i == CurrentTargetGObjSub) {
                stage_SetLoopFlag(D_0054E3C0[i], 1);
                debug_StdPrintfDummy(D_0054E3D8, CurrentTargetGObjSub);
            } else {
                stage_SetLoopFlag(D_0054E3C0[i], 0);
                debug_StdPrintfDummy(D_0054E3F0, CurrentTargetGObjSub);
            }
        }
    }
}

extern float D_00639F88;
extern float D_00639F90;

inline void gsb_SetZoom(float a, float b)
{
    D_00639F88 = a;
    D_00639F90 = b;
}

extern int sceGsSyncPath(int mode, int timeout);
/* kept local: the declaration in GsBase.h changes this TU codegen */
extern void gsb_ResetGSSystem(void);
extern char D_0054E468[];
extern int D_00639FF8;

inline int gsb_SyncGSSystem(void)
{
    if (sceGsSyncPath(1, 0)) {
        D_00639FF8++;
        if (D_00639FF8 >= 11) {
            debug_StdPrintfDummy(D_0054E468);
            gsb_ResetGSSystem();
            D_00639FF8 = 0;
        }
        return 1;
    }
    D_00639FF8 = 0;
    gsb_PostEffect();
    return 0;
}

extern char D_0054E488[];
extern char D_0054E4A8[];
extern char D_0054E4D8[];

inline int gsb_LoadStageSettings(void)
{
    char buf[0x100];
    int fd;
    sprintf(buf, D_0054E488, D_005F5D90 + stage_no * 0x194);
    fd = debugSceOpen(buf, 1);
    if (fd < 0) {
        debug_StdPrintfDummy(D_0054E4A8);
    } else {
        debug_StdPrintfDummy(D_0054E4D8, buf);
        sceRead(fd, &D_0028F720, 0x1D0);
        debugSceClose(fd);
    }
    return -1;
}

extern char D_0054E568[];
extern char D_0054E598[];
/* kept local: the declaration in GsBase.h changes this TU codegen */
extern void appendLogFile(void);

inline int gsb_SaveStageSettings(void)
{
    char buf[0x100];
    int fd;
    if (D_00639F78 == 0) {
        sprintf(buf, D_0054E488, D_005F5D90 + stage_no * 0x194);
        fd = debugSceOpen(buf, 0x602);
        if (fd < 0) {
            debug_StdPrintfDummy(D_0054E568);
            return -1;
        }
        sceWrite(fd, &D_0028F720, 0x1D0);
        debug_StdPrintfDummy(D_0054E598, buf);
        debugSceClose(fd);
        appendLogFile();
    }
    return -1;
}

inline void gsb_ClearFrameBuffer(void)
{
    volatile int local[96];
}

inline void gsb_ResetSnap(void) {}

inline void gsb_TakeSnap(void) {}

/* kept local: the declaration in GsBase.h changes this TU codegen */
extern void updateOtherEditingLockFlag(void);

inline int lockOtherEditing(void)
{
    updateOtherEditingLockFlag();
    if (D_00639F78 != 0) {
        return -1;
    }
    createLockFile();
    gsb_LoadStageSettings();
    return -1;
}

inline int unlockOtherEditing(void)
{
    updateOtherEditingLockFlag();
    if (D_00639F78 != 0) {
        return -1;
    }
    gsb_LoadStageSettings();
    removeLockFile();
    return -1;
}
