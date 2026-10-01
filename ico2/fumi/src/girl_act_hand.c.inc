/* the hand manager, included inside actGirlHand's body, on the listing's .inc lines */ /* clang-format off */
void HandMgr_GetDistHand(float *dist, float *height)
{
    union GAIF g[4], b[4];
    int n, m;
    n = GetSkeltonFocusNode(girlGObj, 0x12);

    g[0].f = *(float *)((n << 6) + GOBJ_SUB(girlGObj)->nodeMtx + 0x30); g[1].f = *(float *)((n << 6) + GOBJ_SUB(girlGObj)->nodeMtx + 0x34); g[2].f = *(float *)((n << 6) + GOBJ_SUB(girlGObj)->nodeMtx + 0x38);
    m = GetSkeltonFocusNode(boyGObj, 2);

    b[0].f = *(float *)((m << 6) + GOBJ_SUB(boyGObj)->nodeMtx + 0x30); b[1].f = *(float *)((m << 6) + GOBJ_SUB(boyGObj)->nodeMtx + 0x34); b[2].f = *(float *)((m << 6) + GOBJ_SUB(boyGObj)->nodeMtx + 0x38);


    *dist = _DistGV(g, b);
    *height = g[1].f - (b[1].f - 40.0f) < 0.0f ? -(g[1].f - (b[1].f - 40.0f))
                                               : g[1].f - (b[1].f - 40.0f);
}

__inline void HandMgr_Init(void) { GetRootPosition(handmgr.prev, girlGObj); }

void HandMgr_Update(void)
{
    GetRootPosition(handmgr.cur, girlGObj);
    handmgr.f_20 = _DistGV(handmgr.cur, handmgr.prev);
    handmgr.sub30[0] = test_CURRENTORIENT(girlGObj)[0]; handmgr.sub30[1] = test_CURRENTORIENT(girlGObj)[1]; handmgr.sub30[2] = test_CURRENTORIENT(girlGObj)[2];
    _OrientXZGV(handmgr.sub40, test_CURRENTROOT(boyGObj), handmgr.cur);
    HandMgr_GetDistHand(&handmgr.f_50, &handmgr.f_54);

    handmgr.f_58 = 0;
    handmgr.f_59 = 0;
    handmgr.f_5A = 0;
    handmgr.f_5B = 0;
    handmgr.f_5C = 0;
    handmgr.f_5D = 0;
    handmgr.f_5E = 0;


    handmgr.prev[0] = handmgr.cur[0]; handmgr.prev[1] = handmgr.cur[1]; handmgr.prev[2] = handmgr.cur[2];
}

void HandMgr_Judge(void)
{
    float one = 1.0f;
    if (handmgr.f_20 < 2.0f) {
        handmgr.f_58 = 1;
    }
    if ((_RotyGV(handmgr.sub40, handmgr.sub30) < 0
             ? -_RotyGV(handmgr.sub40, handmgr.sub30)
             : _RotyGV(handmgr.sub40, handmgr.sub30)) >= 0x3D) {
        handmgr.f_59 = 1;
    }
    if (handmgr.f_54 > 15.0f) {
        handmgr.f_5E = 1;
    }
    if (one * 100.0f < handmgr.f_50) {
        handmgr.f_5A = 1;
    }
    if (one * 125.0f < handmgr.f_50) {
        handmgr.f_5B = 1;
    }
    if (one * 135.0f < handmgr.f_50) {
        handmgr.f_5C = 1;
    }
    if (handmgr.f_50 < 90.0f) {
        handmgr.f_5D = 1;
    }
}

void HandMgr_Print(void)
{
    if (debug_font_flag & 1) {
        debug_Printf(10, 60, 0xFFFFFFF, "[%d] [%d]", (int)handmgr.f_50,
                     (int)handmgr.f_54);
        if (debug_font_flag & 1) {
            debug_Printf(10, 70, 0xFFFFFFF, "gv[%d] mo[%d] hd[%d] hd2[%d]\n", handmgr.f_58,
                         handmgr.f_59, handmgr.f_5B, handmgr.f_5D);
            if (debug_font_flag & 1) {
                debug_Printf(10, 80, 0xFFFFFFF, "\tgv[%d] mo[%d] hd[%d]\n", (int)handmgr.f_20,
                             _RotyGV(handmgr.sub40, handmgr.sub30),
                             (int)handmgr.f_50);
            }
        }
    }
}

void HandMgr_Speed(float f)
{
    float lim = 1.5f;
    int m;
    if (handmgr.f_5E) {
        f = f + f;
        lim = 2.0f;
    }
    f = f < 1.0f ? 1.0f : (lim < f ? lim : f);
    f = f < 1.0f ? 1.0f : (_ACTGame_GetParamF(8) < f ? _ACTGame_GetParamF(8) : f);
    ACTGame_SetMotionPlaySpeedRatio_Reserve((void *)a0, f, 2);
    m = GOBJ_ACT(boyGObj)->actMode;
    if ((unsigned int)m < 4) {
        if (m != 0) {
            float one = 1.0f;
            float r;
            if (one < f) {
                f = one - (f - one);
            }
            r = f < _ACTGame_GetParamF(7) ? _ACTGame_GetParamF(7) : (one < f ? one : f);
            ACTGame_SetMotionPlaySpeedRatio_Reserve((void *)a0, r, 2);
        }
    }
    if (handmgr.f_50 < 60.0f) {
        ACTGame_SetMotionPlaySpeedRatio_Reserve((void *)a0, 0.9f, 3);
    }
    if (90.0f < handmgr.f_50) {
        float r;
        if ((int)GOBJ_ACT(boyGObj)->curItem != 0) {
            r = 2.0f;
        } else if (systemStatus[0] == 1) {
            r = (handmgr.f_50 - 90.0f) / 120.0f + 1.1f;
            r = r < 1.0f ? 1.0f : (r > 1.4 ? 1.4f : r);
        } else {
            r = 1.3f;
        }
        ACTGame_SetMotionPlaySpeedRatio_Reserve((void *)a0, r, 3);
    }
}
