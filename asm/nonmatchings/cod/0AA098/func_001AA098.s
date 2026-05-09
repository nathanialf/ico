/* Symbols accessed via $gp register */
.extern D_00632CA0, 1
.extern D_00632CA4, 1
.extern D_00633E58, 1
.extern D_00632C90, 1
.extern D_00632C94, 1
.extern D_00632C98, 1
.extern D_00632C9C, 1

.align 3
nonmatching func_001AA098, 0x28

glabel func_001AA098
    /* AA098 001AA098 0010023C */  lui        $2, (0x10000000 >> 16)
    /* AA09C 001AA09C B0A380AF */  sw         $0, (D_00632CA0) /* gp_rel: (D_00632CA0) */
    /* AA0A0 001AA0A0 000040AC */  sw         $0, (0x10000000 & 0xFFFF)($2)
    /* AA0A4 001AA0A4 ACA380AF */  sw         $0, (D_00632C9C) /* gp_rel: (D_00632C9C) */
    /* AA0A8 001AA0A8 A8A380AF */  sw         $0, (D_00632C98) /* gp_rel: (D_00632C98) */
    /* AA0AC 001AA0AC A4A380AF */  sw         $0, (D_00632C94) /* gp_rel: (D_00632C94) */
    /* AA0B0 001AA0B0 A0A380AF */  sw         $0, (D_00632C90) /* gp_rel: (D_00632C90) */
    /* AA0B4 001AA0B4 B4A380AF */  sw         $0, (D_00632CA4) /* gp_rel: (D_00632CA4) */
    /* AA0B8 001AA0B8 0800E003 */  jr         $31
    /* AA0BC 001AA0BC 68B580AF */   sw        $0, (D_00633E58) /* gp_rel: (D_00633E58) */
endlabel func_001AA098
