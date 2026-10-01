; ico2/vusrc/scissorcommcut.h /* derived name */: SCISSOR_COMMON and the
; routines it calls, included by normal_c.vsm and normal_l.vsm after their
; own triangle loops. The two programs assemble these 359 instructions
; alike but for the two loads at SCISSOR_COMMON+6 and +7, which read the
; first two vertices of the triangle back from the input buffer: the
; including program defines VERTEX_QW, the quadwords of one input vertex
; (3 in normal_c, 4 in normal_l), before the #include.
;
; The name follows the VU sources around it: vusrc/, lower case, .h for a
; file cpp includes. dvp-as names the overlays it starts in here with the
; hash of the path cpp prints for it, fixed by the base at 483563468; of
; the label-word names under vusrc/ that hash allows, this is the one whose
; words all describe the file (scissor and comm from SCISSOR_COMMON, cut
; for clipping); the others name one plane (vusrc/scissor_xp_set.h ...).
;
; -----------------------------------------------------------------------
; SCISSOR_COMMON - runs the triangle in vf22..vf24 through six passes,
; ZMINUS, ZPLUS, XMINUS, XPLUS, YMINUS and YPLUS, each a loop over the
; polygon in one of the two buffers at mem[104] and mem[164] (vi08 and
; vi09 swap between them), then draws what is left with
; DrawScissorPolygon. The routines it calls:
;   CLIP_INTER - per vertex: blends vf31 into vf21..vf23, reads the clip
;            flags and stores the vertex, the edge point or both
;            (`bal vi02` from every pass).
;   SAVE_LAST_LOOP - copies the 3 quads at mem[vi08+0..2] to the vi09
;            stream (`bal vi02` at the end of each pass).
;   END_ALL - `jr vi15` early-out when a pass leaves nothing (vi11 == 0).
;   INTERPOLATE / LOOP_ROT_END - the edge point between two vertices
;            (`bal vi01` from CLIP_INTER).
;   SCISSOR_COMMON_PUSHREGISTER / SCISSOR_COMMON_POPREGISTER - save and
;            restore vf17..vf31 and vi02..vi15 on the vi14 stack around
;            the call.
;
; Setup: vi08 = 104, the three vertices to slots 0/9, 3 and 6 with the
; vf17.xy offset applied to their positions, and their colours from the
; vi07 stream converted with itof0 to slots 1/10, 4 and 7.
;
; Each pass: vi05 and vi06 select the plane, vi10 counts the polygon
; vertices; at the end vi08 swaps to the other buffer and the sign of
; vf30.x flips for the next plane. When the last pass leaves vertices,
; DrawScissorPolygon draws them (`bal vi01`).
; -----------------------------------------------------------------------
SCISSOR_COMMON:
	nop                              iaddiu vi08, vi00, 104                 ; vi08 = mem[104] (input vtx base)
	nop                              sq.xyzw vf22, 0(vi08)                  ; mem[104+0] = vf22
	nop                              sq.xyzw vf22, 9(vi08)                  ; mem[104+9] = vf22 (mirror)
	nop                              sq.xyzw vf23, 3(vi08)                  ; mem[104+3] = vf23
	nop                              iaddiu vi09, vi00, 164                 ; vi09 = mem[164] (output base)
	nop                              sq.xyzw vf24, 6(vi08)                  ; mem[104+6] = vf24
	nop                              lq.xyzw vf22, -2-2*VERTEX_QW(vi03)     ; first vertex of the triangle
	add.xy vf22, vf22, vf17          lq.xyzw vf23, -2-VERTEX_QW(vi03)       ; second vertex
	add.xy vf23, vf23, vf17          lq.xyzw vf24, -2(vi03)
	add.xy vf24, vf24, vf17          nop
	nop                              sq.xyzw vf22, 2(vi08)
	nop                              sq.xyzw vf22, 11(vi08)
	nop                              sq.xyzw vf23, 5(vi08)
	nop                              sq.xyzw vf24, 8(vi08)
	nop                              lq.xyzw vf22, -5(vi07)
	itof0.xyzw vf22, vf22            lq.xyzw vf23, -2(vi07)
	itof0.xyzw vf23, vf23            lq.xyzw vf24, 1(vi07)
	itof0.xyzw vf24, vf24            nop
	nop                              sq.xyzw vf22, 1(vi08)
	nop                              sq.xyzw vf22, 10(vi08)
	nop                              sq.xyzw vf23, 4(vi08)
	nop                              sq.xyzw vf24, 7(vi08)

ZMINUS:
	nop                              iaddiu vi05, vi00, 2048
	nop                              iaddiu vi06, vi00, 32
	nop                              iaddiu vi07, vi00, 2
	nop                              iaddiu vi10, vi00, 3
	nop                              iaddiu vi11, vi00, 0
	subw.x vf30, vf00, vf00w         lqi.xyzw vf21, (vi08++)
	nop                              lqi.xyzw vf22, (vi08++)
	nop                              lqi.xyzw vf23, (vi08++)
LOOP_ZM:
	nop                              bal vi02, CLIP_INTER
	nop                              nop
	nop                              isubiu vi10, vi10, 1
	nop                              nop
	nop                              ibne vi10, vi00, LOOP_ZM
	nop                              nop
	nop                              iaddiu vi08, vi00, 164
	nop                              bal vi02, SAVE_LAST_LOOP
	nop                              nop
	nop[d]                           nop                                    ; pad with M-bit flag (bit 28)
	nop                              ibeq vi11, vi00, END_ALL
	nop                              nop

ZPLUS:
	nop                              iaddiu vi05, vi00, 1024
	nop                              iaddiu vi06, vi00, 16
	nop                              iaddiu vi07, vi00, 2
	nop                              iaddiu vi08, vi00, 164
	nop                              iaddiu vi09, vi00, 104
	nop                              iadd vi10, vi00, vi11                  ; vi10 = previous tier vi11
	nop                              iaddiu vi11, vi00, 0
	addw.x vf30, vf00, vf00w         nop
	nop                              lqi.xyzw vf21, (vi08++)
	nop                              lqi.xyzw vf22, (vi08++)
	nop                              lqi.xyzw vf23, (vi08++)
LOOP_ZP:
	nop                              bal vi02, CLIP_INTER
	nop                              nop
	nop                              isubiu vi10, vi10, 1
	nop                              nop
	nop                              ibne vi10, vi00, LOOP_ZP
	nop                              nop
	nop                              iaddiu vi08, vi00, 104
	nop                              bal vi02, SAVE_LAST_LOOP
	nop                              nop
	nop                              ibeq vi11, vi00, END_ALL
	nop                              nop

XMINUS:
	nop                              iaddiu vi05, vi00, 128
	nop                              iaddiu vi06, vi00, 2
	nop                              iaddiu vi07, vi00, 0
	nop                              iaddiu vi08, vi00, 104
	nop                              iaddiu vi09, vi00, 164
	nop                              iadd vi10, vi00, vi11
	nop                              iaddiu vi11, vi00, 0
	subw.x vf30, vf00, vf00w         nop
	nop                              lqi.xyzw vf21, (vi08++)
	nop                              lqi.xyzw vf22, (vi08++)
	nop                              lqi.xyzw vf23, (vi08++)
LOOP_XM:
	nop                              bal vi02, CLIP_INTER
	nop                              nop
	nop                              isubiu vi10, vi10, 1
	nop                              nop
	nop                              ibne vi10, vi00, LOOP_XM
	nop                              nop
	nop                              iaddiu vi08, vi00, 164
	nop                              bal vi02, SAVE_LAST_LOOP
	nop                              nop
	nop                              ibeq vi11, vi00, END_ALL
	nop                              nop

XPLUS:
	nop                              iaddiu vi05, vi00, 64
	nop                              iaddiu vi06, vi00, 1
	nop                              iaddiu vi07, vi00, 0
	nop                              iaddiu vi08, vi00, 164
	nop                              iaddiu vi09, vi00, 104
	nop                              iadd vi10, vi00, vi11
	nop                              iaddiu vi11, vi00, 0
	addw.x vf30, vf00, vf00w         nop
	nop                              lqi.xyzw vf21, (vi08++)
	nop                              lqi.xyzw vf22, (vi08++)
	nop                              lqi.xyzw vf23, (vi08++)
LOOP_XP:
	nop                              bal vi02, CLIP_INTER
	nop                              nop
	nop                              isubiu vi10, vi10, 1
	nop                              nop
	nop                              ibne vi10, vi00, LOOP_XP
	nop                              nop
	nop                              iaddiu vi08, vi00, 104
	nop                              bal vi02, SAVE_LAST_LOOP
	nop                              nop
	nop                              ibeq vi11, vi00, END_ALL
	nop                              nop

YMINUS:
	nop                              iaddiu vi05, vi00, 512
	nop                              iaddiu vi06, vi00, 8
	nop                              iaddiu vi07, vi00, 1
	nop                              iaddiu vi08, vi00, 104
	nop                              iaddiu vi09, vi00, 164
	nop                              iadd vi10, vi00, vi11
	nop                              iaddiu vi11, vi00, 0
	subw.x vf30, vf00, vf00w         nop
	nop                              lqi.xyzw vf21, (vi08++)
	nop                              lqi.xyzw vf22, (vi08++)
	nop                              lqi.xyzw vf23, (vi08++)
LOOP_YM:
	nop                              bal vi02, CLIP_INTER
	nop                              nop
	nop                              isubiu vi10, vi10, 1
	nop                              nop
	nop                              ibne vi10, vi00, LOOP_YM
	nop                              nop
	nop                              iaddiu vi08, vi00, 164
	nop                              bal vi02, SAVE_LAST_LOOP
	nop                              nop
	nop                              ibeq vi11, vi00, END_ALL
	nop                              nop

YPLUS:
	nop                              iaddiu vi05, vi00, 256
	nop                              iaddiu vi06, vi00, 4
	nop                              iaddiu vi07, vi00, 1
	nop                              iaddiu vi08, vi00, 164
	nop                              iaddiu vi09, vi00, 104
	nop                              iadd vi10, vi00, vi11
	nop                              iaddiu vi11, vi00, 0
	addw.x vf30, vf00, vf00w         nop
	nop                              lqi.xyzw vf21, (vi08++)
	nop                              lqi.xyzw vf22, (vi08++)
	nop                              lqi.xyzw vf23, (vi08++)
LOOP_YP:
	nop                              bal vi02, CLIP_INTER
	nop                              nop
	nop                              isubiu vi10, vi10, 1
	nop                              nop
	nop                              ibne vi10, vi00, LOOP_YP
	nop                              nop
	nop                              iaddiu vi08, vi00, 104
	nop                              bal vi02, SAVE_LAST_LOOP
	nop                              nop
	nop                              ibeq vi11, vi00, END_ALL
	nop                              nop

	nop                              iaddiu vi08, vi00, 104
	nop                              iaddiu vi09, vi00, 164
	nop                              iadd vi10, vi00, vi11
	nop                              iaddiu vi11, vi00, 0
	nop                              bal vi01, DrawScissorPolygon                     ; call save-context routine
	nop                              nop

; END_ALL - `jr vi15` back to the caller when a pass leaves no vertex.
END_ALL:
	nop                              jr vi15
	nop                              nop

; SAVE_LAST_LOOP - copies 3 quads from mem[vi08+0..2] to the vi09 stream
; and returns via `jr vi02`.
SAVE_LAST_LOOP:
	nop                              lq.xyzw vf21, 0(vi08)
	nop                              lq.xyzw vf22, 1(vi08)
	nop                              lq.xyzw vf23, 2(vi08)
	nop                              sqi.xyzw vf21, (vi09++)
	nop                              sqi.xyzw vf22, (vi09++)
	nop                              sqi.xyzw vf23, (vi09++)
	nop                              jr vi02
	nop                              nop

; CLIP_INTER - adds vf31 to vf21..vf23 into vf17..vf19, reads the clip
; flags with fcget and stores through one of three paths (CO_NEXT_IN,
; CUR_IN, CI_NEXT_IN) to CLIP_INTER_END, which returns via `jr vi02`.
; -----------------------------------------------------------------------
CLIP_INTER:
	add.xyzw vf17, vf31, vf21        lqi.xyzw vf21, (vi08++)
	add.xyzw vf18, vf31, vf22        lqi.xyzw vf22, (vi08++)
	add.xyzw vf19, vf31, vf23        lqi.xyzw vf23, (vi08++)
	clipw.xyz vf17, vf17w            nop                                    ; upper op6=0x3F .xyz fd=7 fs=17 ft=17 (FD-dispatch)
	clipw.xyz vf21, vf21w            nop                                    ; upper op6=0x3F .xyz fd=7 fs=21 ft=21 (FD-dispatch)
	nop                              nop
	nop                              nop
	nop                              nop
	nop                              fcget vi01                             ; vi01 = clip flag bits
	nop                              iand vi04, vi01, vi05                  ; vi04 = vi01 & tier-mask
	nop                              nop
	nop                              ibeq vi04, vi00, CUR_IN
	nop                              nop
CUR_OUT:
	nop                              iand vi04, vi01, vi06                  ; vi04 = vi01 & mip-mask
	nop                              nop
	nop                              ibeq vi04, vi00, CO_NEXT_IN
	nop                              nop
CO_NEXT_OUT:
	nop                              b CLIP_INTER_END
	nop                              nop
CO_NEXT_IN:
	nop                              bal vi01, INTERPOLATE                  ; refine via subroutine
	nop                              nop                                    ; (delay slot)
	nop                              sqi.xyzw vf25, (vi09++)                ; store refined vf25/26/27
	nop                              sqi.xyzw vf26, (vi09++)
	nop                              sqi.xyzw vf27, (vi09++)
	nop                              iaddiu vi11, vi11, 1
	nop                              b CLIP_INTER_END
	nop                              nop
CUR_IN:
	nop                              iand vi04, vi01, vi06
	nop                              nop
	nop                              ibeq vi04, vi00, CI_NEXT_IN
	nop                              nop
CI_NEXT_OUT:
	nop                              bal vi01, INTERPOLATE                  ; refine (both-path variant)
	nop                              nop                                    ; (delay slot)
	nop                              sqi.xyzw vf17, (vi09++)                ; store base vf17/18/19
	nop                              sqi.xyzw vf18, (vi09++)
	nop                              sqi.xyzw vf19, (vi09++)
	nop                              sqi.xyzw vf25, (vi09++)                ; + refined vf25/26/27
	nop                              sqi.xyzw vf26, (vi09++)
	nop                              sqi.xyzw vf27, (vi09++)
	nop                              iaddiu vi11, vi11, 2
	nop                              b CLIP_INTER_END
	nop                              nop
CI_NEXT_IN:
	nop                              sqi.xyzw vf17, (vi09++)                ; store base vf17/18/19 only
	nop                              sqi.xyzw vf18, (vi09++)
	nop                              sqi.xyzw vf19, (vi09++)
	nop                              iaddiu vi11, vi11, 1
CLIP_INTER_END:
	nop                              jr vi02                                ; return
	nop                              nop

; -----------------------------------------------------------------------
; INTERPOLATE - the vf30-weighted differences of vf17/vf21, rotated with
; mr32 vi12 times, then LOOP_ROT_END.
INTERPOLATE:
	mulx.w vf25, vf17, vf30x         iadd vi12, vi00, vi07
	mulx.w vf26, vf21, vf30x         nop
	subw.xyzw vf25, vf17, vf25w      nop
	subw.xyzw vf26, vf21, vf26w      nop
	nop                              nop
LOOP_ROT:
	nop                              ibeq vi12, vi00, LOOP_ROT_END
	nop                              nop
	nop                              mr32.xyzw vf25, vf25
	nop                              mr32.xyzw vf26, vf26
	nop                              isubiu vi12, vi12, 1
	nop                              b LOOP_ROT
	nop                              nop

; -----------------------------------------------------------------------
; LOOP_ROT_END - Q = vf25.x / vf27.x; vf25..vf27 = vf17..vf19 plus |Q|
; times the differences (vf21..vf23 - vf17..vf19).
LOOP_ROT_END:
	sub.xyz vf27, vf26, vf25         nop
	nop                              div q, vf25x, vf27x
	addq.x vf29, vf00, q             waitq
	abs.x vf29, vf29                 nop
	sub.xyzw vf25, vf21, vf17        nop
	sub.xyzw vf26, vf22, vf18        nop
	sub.xyzw vf27, vf23, vf19        nop
	mulx.xyzw vf25, vf25, vf29x      nop
	mulx.xyzw vf26, vf26, vf29x      nop
	mulx.xyzw vf27, vf27, vf29x      nop
	add.xyzw vf25, vf25, vf17        nop
	add.xyzw vf26, vf26, vf18        nop
	add.xyzw vf27, vf27, vf19        nop
	nop                              jr vi01                                ; return to INTERPOLATE-call-site

; -----------------------------------------------------------------------
; DrawScissorPolygon - transforms the clipped vertices, builds the GIF
; packet at mem[vi02] and kicks it.
; -----------------------------------------------------------------------
	nop                              nop                                    ; (entry - also delay slot from sub_2818 caller)
DrawScissorPolygon:
	nop                              iaddiu vi02, vi00, 37                  ; vi02 = mem[37] (GIF tag slot)
	nop                              iadd vi03, vi00, vi08                  ; vi03 = vi08 (input cursor)
	nop                              iaddiu vi07, vi02, 2                   ; vi07 = vi02 + 2 (output cursor)
	nop                              iaddiu vi11, vi00, 32767               ; vi11 = 0x7FFF
	nop                              iaddiu vi11, vi11, 1                   ; vi11 = 0x8000
	nop                              isw.x vi11, 0(vi02)                    ; mem[vi02].x = 0x8000 (count word)
	nop                              lq.xyzw vf01, 8(vi00)                  ; load matrix M0
	nop                              lq.xyzw vf02, 9(vi00)                  ; M1
	nop                              lq.xyzw vf03, 10(vi00)                 ; M2
	nop                              lq.xyzw vf04, 11(vi00)                 ; M3
	nop                              xgkick vi02                            ; kick initial GIF packet
	nop                              iaddiu vi11, vi10, 32767               ; vi11 = vi10 + 0x7FFF
	nop                              iaddiu vi11, vi11, 1                   ; vi11 = vi10 + 0x8000
	nop                              isw.x vi11, 0(vi02)                    ; mem[vi02].x = vi11 (count)

LOOP2:
	nop                              lq.xyzw vf20, 0(vi03)                  ; vf20 = *vi03 (input vertex)
	mulax.xyzw acc, vf01, vf20x      nop                                    ; ACC = vf01 * vf20.x
	madday.xyzw acc, vf02, vf20y     nop
	maddaz.xyzw acc, vf03, vf20z     nop
	maddw.xyzw vf25, vf04, vf20w     nop                                    ; vf25 = ACC + vf04*vf20.w
	nop                              div q, vf00w, vf25w                    ; Q = 1/vf25.w
	mulq.xyzw vf25, vf25, q          waitq                                  ; vf25 *= Q (perspective)
	ftoi4.xyzw  vf26, vf25           nop                                    ; vf26 = ftoi4(vf25)
	nop                              sq.xyzw vf26, 1(vi07)
	nop                              lq.xyzw vf20, 2(vi03)                  ; vf20 = mem[vi03+2]
	mulq.xyz vf28, vf20, q           nop                                    ; vf28 = vf20 * Q
	nop                              sq.xyzw vf28, -1(vi07)
	nop                              lq.xyzw vf27, 1(vi03)                  ; vf27 = mem[vi03+1]
	ftoi0.xyzw  vf29, vf27           nop                                    ; vf29 = ftoi0(vf27)
	nop                              sq.xyzw vf29, 0(vi07)
	nop                              iaddiu vi07, vi07, 3
	nop                              iaddiu vi03, vi03, 3
	nop                              iaddi vi10, vi10, -1
	nop                              nop
	nop                              ibne vi10, vi00, LOOP2
	nop                              nop                                    ; (branch delay slot)
	nop                              xgkick vi02                            ; kick transformed GIF packet
	nop                              lq.xyzw vf01, 16(vi00)                 ; reload matrix M0 from mem[16..19]
	nop                              lq.xyzw vf02, 17(vi00)
	nop                              lq.xyzw vf03, 18(vi00)
	nop                              lq.xyzw vf04, 19(vi00)
	nop                              nop
	nop                              jr vi01                                ; return to SCISSOR_COMMON caller
	nop                              nop                                    ; (delay slot)

; -----------------------------------------------------------------------
; SCISSOR_COMMON_PUSHREGISTER - VU0 register-bank save routine.
;
; Stores all 15 float registers vf17..vf31 (via sqd post-decrement
; into the vi14 stack), then packs all 14 int registers vi02..vi15
; into 4 quads via iswr (one lane per int).  Used as an interrupt
; save / context-switch primitive. The caller sets vi14 to the stack top; this routine returns via `jr vi15`.
; -----------------------------------------------------------------------
SCISSOR_COMMON_PUSHREGISTER:
	nop                              sqd.xyzw vf17, (--vi14)
	nop                              sqd.xyzw vf18, (--vi14)
	nop                              sqd.xyzw vf19, (--vi14)
	nop                              sqd.xyzw vf20, (--vi14)
	nop                              sqd.xyzw vf21, (--vi14)
	nop                              sqd.xyzw vf22, (--vi14)
	nop                              sqd.xyzw vf23, (--vi14)
	nop                              sqd.xyzw vf24, (--vi14)
	nop                              sqd.xyzw vf25, (--vi14)
	nop                              sqd.xyzw vf26, (--vi14)
	nop                              sqd.xyzw vf27, (--vi14)
	nop                              sqd.xyzw vf28, (--vi14)
	nop                              sqd.xyzw vf29, (--vi14)
	nop                              sqd.xyzw vf30, (--vi14)
	nop                              sqd.xyzw vf31, (--vi14)
	nop                              isubiu vi14, vi14, 1                   ; vi14--
	nop                              iswr.x vi02, (vi14)                    ; pack vi02..vi05 -> quad
	nop                              iswr.y vi03, (vi14)
	nop                              iswr.z vi04, (vi14)
	nop                              iswr.w vi05, (vi14)
	nop                              isubiu vi14, vi14, 1
	nop                              iswr.x vi06, (vi14)                    ; vi06..vi09 -> quad
	nop                              iswr.y vi07, (vi14)
	nop                              iswr.z vi08, (vi14)
	nop                              iswr.w vi09, (vi14)
	nop                              isubiu vi14, vi14, 1
	nop                              iswr.x vi10, (vi14)                    ; vi10..vi13 -> quad
	nop                              iswr.y vi11, (vi14)
	nop                              iswr.z vi12, (vi14)
	nop                              iswr.w vi13, (vi14)
	nop                              isubiu vi14, vi14, 1
	nop                              iswr.x vi14, (vi14)                    ; vi14, vi15 -> quad (vi00/vi01 omitted)
	nop                              iswr.y vi15, (vi14)
	nop                              nop
	nop                              jr vi15
	nop                              nop

; -----------------------------------------------------------------------
; SCISSOR_COMMON_POPREGISTER - VU0 register-bank restore routine.
;
; Reverses SCISSOR_COMMON_PUSHREGISTER: unpacks 4 int-saving quads via ilwr (one lane per
; int), then lqi 15 floats back into vf17..vf31 (in reverse order:
; vf31 first since save order is reverse).  Caller pre-loads vi14
; to the bottom-of-stack slot; routine returns via `jr vi01`.
; -----------------------------------------------------------------------
SCISSOR_COMMON_POPREGISTER:
	nop                              iadd vi01, vi00, vi15                  ; vi01 = vi15 (save return target)
	nop                              iswr.x vi14, (vi14)                    ; ?? (write-back vi14/vi15 first)
	nop                              iswr.y vi15, (vi14)
	nop                              iaddiu vi14, vi14, 1                   ; vi14++
	nop                              ilwr.x vi10, (vi14)                    ; unpack vi10..vi13 from quad
	nop                              ilwr.y vi11, (vi14)
	nop                              ilwr.z vi12, (vi14)
	nop                              ilwr.w vi13, (vi14)
	nop                              iaddiu vi14, vi14, 1
	nop                              ilwr.x vi06, (vi14)                    ; vi06..vi09
	nop                              ilwr.y vi07, (vi14)
	nop                              ilwr.z vi08, (vi14)
	nop                              ilwr.w vi09, (vi14)
	nop                              iaddiu vi14, vi14, 1
	nop                              ilwr.x vi02, (vi14)                    ; vi02..vi05
	nop                              ilwr.y vi03, (vi14)
	nop                              ilwr.z vi04, (vi14)
	nop                              ilwr.w vi05, (vi14)
	nop                              iaddiu vi14, vi14, 1
	nop                              lqi.xyzw vf31, (vi14++)                ; restore vf17..vf31 (reverse)
	nop                              lqi.xyzw vf30, (vi14++)
	nop                              lqi.xyzw vf29, (vi14++)
	nop                              lqi.xyzw vf28, (vi14++)
	nop                              lqi.xyzw vf27, (vi14++)
	nop                              lqi.xyzw vf26, (vi14++)
	nop                              lqi.xyzw vf25, (vi14++)
	nop                              lqi.xyzw vf24, (vi14++)
	nop                              lqi.xyzw vf23, (vi14++)
	nop                              lqi.xyzw vf22, (vi14++)
	nop                              lqi.xyzw vf21, (vi14++)
	nop                              lqi.xyzw vf20, (vi14++)
	nop                              lqi.xyzw vf19, (vi14++)
	nop                              lqi.xyzw vf18, (vi14++)
	nop                              lqi.xyzw vf17, (vi14++)
	nop                              nop

; -----------------------------------------------------------------------
; The `jr vi01` return of SCISSOR_COMMON_POPREGISTER.
; -----------------------------------------------------------------------
	nop                              jr vi01
	nop                              nop
