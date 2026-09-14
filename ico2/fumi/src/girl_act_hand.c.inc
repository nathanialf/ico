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
ASM_LIT4_SLOT(D_00639038, 0.9f);
ASM_LIT4_SLOT(D_0063903C, 1.1f);
ASM_LIT4_SLOT(D_00639040, 1.4f);
ASM_LIT4_SLOT(D_00639044, 1.3f);
INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/girl_act", HandMgr_Speed);
