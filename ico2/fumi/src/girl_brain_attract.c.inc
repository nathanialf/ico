/* girl_brain_attract.c.inc -- the girl brain's "attract" state, #included as source into one
 * girl_act.o.  The PAL listing (baserom/pal/SRCFILE.TXT) attributes these bodies to
 * fumi/src/girl_brain_attract.c.inc and links them into girl_act.o; the census in
 * docs/pal_source_tree.json records the include.  Its includer in the 2002 tree is
 * girl_brain_main.c.inc, which is not split out yet (see docs/HEADERS.md), so the include
 * sits at the same point of girl_act.c that girl_brain_main.c.inc's text occupies today.
 * INCLUDE_ASM paths name the INCLUDER's asm directory because splat splits by the
 * translation unit, not by the included file. */

/* kept local: this TU's uses of GetSkeltonOrient do not fit the prototype in act-game.h */
extern void GetSkeltonOrient(float *out, void *obj, int node);
/* kept local: this TU's uses of _RotyGV do not fit the prototype in gv.h */
extern int _RotyGV(void *buf, void *vec);

int ATGoalTurnMail(void *actor, float *dir, int node)
{
    float o1[4];
    float v[4];
    float o2[4];
    int r1;
    int m;
    int r2;
    int d;
    int ret;

    ret = 0;
    v[0] = dir[0];
    v[1] = dir[1];
    v[2] = dir[2];
    GetSkeltonOrient(o1, actor, 0x2C);
    r1 = _RotyGV(o1, v);
    m = (r1 < 0) ? -r1 : r1;
    if (m >= 0x15) {
        GetSkeltonOrient(o2, actor, node);
        r2 = _RotyGV(o2, v);
        if (m >= 0x5A) {
            goto use_r2;
        }
        if (r1 * r2 < 0) {
            goto set_r1;
        }
    use_r2:
        d = r2;
        goto have_d;
    set_r1:
        d = r1;
    have_d:
        if (d > 0) {
            ATGoalTurnSet(actor, 2, 2, v);
        } else {
            ATGoalTurnSet(actor, 2, 1, v);
        }
        ret = 1;
    }
    return ret;
}

/* kept local: this TU's uses of test_CURRENTROOT do not fit the prototype in commonact.h */
extern void *test_CURRENTROOT(void *a0);

int checkWaterfallResult(float *out)
{
    union {
        float f[4];
        int i[4];
    } t;

    float pa[4];
    float pb[4];
    int r1;
    int r0;
    int ret;

    r1 = -1;
    r0 = -1;
    ret = 0;
    GetRootProjectionPosOfGObj(pa, D_00639EA4);
    GetRootProjectionPosOfGObj(pb, D_00639EA8);
    if (1600.0f < pb[1] && pb[1] < 2300.0f) {
        if (pb[2] < -150.0f) {
            r1 = 0;
        } else if (850.0f < pb[2]) {
            r1 = 2;
        } else {
            r1 = 1;
        }
    }
    if (1600.0f < pa[1] && pa[1] < 2300.0f) {
        if (pa[2] < -150.0f) {
            r0 = 0;
        } else if (850.0f < pa[2]) {
            r0 = 2;
        } else {
            r0 = 1;
        }
    }
    if (r0 == -1) {
        return 0;
    }
    if (r1 == -1) {
        return 0;
    }
    if (r1 == 1) {
        return 1;
    }
    if (r0 == 1) {
        if (*(void **)(*(char **)((char *)D_00639EA4 + 0x15C)) != 0 &&
            *(int *)((char *)*(void **)(*(char **)((char *)D_00639EA4 + 0x15C)) + 0xC) == 17) {
            t.f[0] =
                ((float *)test_CURRENTROOT(*(void **)(*(char **)((char *)D_00639EA4 + 0x15C))))[0];
            t.f[1] =
                ((float *)test_CURRENTROOT(*(void **)(*(char **)((char *)D_00639EA4 + 0x15C))))[1];
            t.f[2] =
                ((float *)test_CURRENTROOT(*(void **)(*(char **)((char *)D_00639EA4 + 0x15C))))[2];
        } else {
            return 1;
        }
    }
    if (r1 == 0 && r0 != 0) {
        ret = 1;
        if (r0 == 1 && t.f[2] < -50.0f) {
            out[0] = pa[0];
            out[1] = 1800.0f;
            out[2] = -170.0f;
            ret = 2;
        }
    }
    if (r1 == 2 && r0 != r1) {
        ret = 1;
        if (r0 == 1 && 750.0f < t.f[2] && 650.0f < t.f[0] && t.f[0] < 950.0f) {
            out[0] = pa[0];
            out[1] = 1900.0f;
            out[2] = 870.0f;
            ret = 2;
        }
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/girl_act", subGirlBrain_Attract);
