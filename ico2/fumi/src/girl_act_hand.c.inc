/* girl_act_hand.c.inc -- the hand manager, #included as source into one girl_act.o.
 * The PAL listing (baserom/pal/SRCFILE.TXT) attributes these five bodies to
 * fumi/src/girl_act_hand.c.inc and links them into girl_act.o; the census in
 * docs/pal_source_tree.json records the include.  INCLUDE_ASM paths name the INCLUDER's
 * asm directory because splat splits by the translation unit, not by the included file. */

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/girl_act", HandMgr_GetDistHand);
INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/girl_act", HandMgr_Update);

extern GirlStand D_002A2F70;
extern int _RotyGV(void *buf, void *vec);

void HandMgr_Judge(void)
{
    /* CRUTCH: the `home = uninit` pair below is a stand-in, not source.  The
       census labels this body HandMgr_Judge.441 -- a GNU NESTED FUNCTION of
       actGirlHand -- and ROM homes the incoming static chain with
       `sw $2,0($sp)`.  Measured 2026-09-14: with the whole family written as
       nested functions inside actGirlHand this body is byte-identical (90/90
       words) and needs no stand-in; so are HandMgr_GetDistHand (68/68),
       HandMgr_Update (61/61), HandMgr_Print (66/66) and GetBoyMode (92/92).
       The unit is indivisible and actGirlHand itself does not yet match, so
       the stand-in stays.  Seed: seeds/girl_act.pass12_actGirlHandUnit.5of7_rc0.TU.c */
    volatile int home;
    int uninit;
    float one = 1.0f;
    home = uninit;
    if (D_002A2F70.f_20 < 2.0f) {
        D_002A2F70.f_58 = 1;
    }
    if ((_RotyGV(D_002A2F70.sub40, D_002A2F70.sub30) < 0
             ? -_RotyGV(D_002A2F70.sub40, D_002A2F70.sub30)
             : _RotyGV(D_002A2F70.sub40, D_002A2F70.sub30)) >= 0x3D) {
        D_002A2F70.f_59 = 1;
    }
    if (D_002A2F70.f_54 > 15.0f) {
        D_002A2F70.f_5E = 1;
    }
    if (one * 100.0f < D_002A2F70.f_50) {
        D_002A2F70.f_5A = 1;
    }
    if (one * 125.0f < D_002A2F70.f_50) {
        D_002A2F70.f_5B = 1;
    }
    if (one * 135.0f < D_002A2F70.f_50) {
        D_002A2F70.f_5C = 1;
    }
    if (D_002A2F70.f_50 < 90.0f) {
        D_002A2F70.f_5D = 1;
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/girl_act", HandMgr_Print);
INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/girl_act", HandMgr_Speed);
