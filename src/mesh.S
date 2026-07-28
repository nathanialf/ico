; -----------------------------------------------------------------------
; MeshMicroProgram — VU1 microprogram (ico2000.a mesh.o), seki/GS renderer.
;
; One of the 5 per-primitive VU1 microprograms in ICO's .vutext section
; (cluster/mesh/normal_c/normal_l/particle), managed by MicroCode.o
; (mc_TransMicroCode).  Split by the MAIN.MAP .vutext .o boundaries.
;
; Clean-room: bytes re-derived from published VU0/VU1 documentation
; (EE User's Manual, PCSX2 microVU GPL-3.0 opcode dispatch, ps2sdk) via
; tools/assemble_vu0.py — never from extracted disc data.  Byte-identical
; to aug6 .vutext 0x26C730..0x26D120 (2544 bytes); labels are
; program-relative (VU micromem is loaded at 0).
; -----------------------------------------------------------------------
.vu0
.org 0x0000
nop ; .word 0x6000009D                  ; lower op7=0x30 (FCSET imm24=0x9D)
.word 0x4A000000 ; nop                  ; upper op6=0x00 unknown-family + lower true-zero

; Program-2 entry-stub dispatch table (parallels 0x0010..0x00D8 in program 1).
pad ; b L_00E0                          ; 0x0DD0 — entry → L_00E0
pad ; nop_swap                          ;        delay slot
pad ; b L_0168                          ; 0x0DE0 — entry → L_0168
pad ; nop_swap                          ;        delay slot
pad ; nop_swap                          ; 0x0DF0 — reserved slot
pad ; nop_swap                          ; 0x0DF8 — reserved slot
pad ; nop_swap                          ; 0x0E00 — reserved slot
pad ; nop_swap                          ; 0x0E08 — reserved slot
pad ; b L_01A0                          ; 0x0E10 — entry → L_01A0
pad ; nop_swap                          ;        delay slot
pad ; b L_0210                          ; 0x0E20 — entry → L_0210
pad ; nop_swap                          ;        delay slot
pad ; b L_02E8                          ; 0x0E30 — entry → L_02E8
pad ; nop_swap                          ;        delay slot
pad ; nop_swap                          ; 0x0E40 — reserved slot
pad ; nop_swap                          ; 0x0E48 — reserved slot
pad ; b L_0300                          ; 0x0E50 — entry → L_0300
pad ; nop_swap                          ;        delay slot
pad ; b L_0358                          ; 0x0E60 — entry → L_0358
pad ; nop_swap                          ;        delay slot
pad ; b L_0818                          ; 0x0E70 — entry → L_0818  (far-target)
pad ; nop_swap                          ;        delay slot
pad ; b L_03B0                          ; 0x0E80 — entry → L_03B0
pad ; nop_swap                          ;        delay slot
pad ; b L_05D8                          ; 0x0E90 — entry → L_05D8
pad ; nop_swap                          ;        delay slot

; =======================================================================
; PROGRAM 2 SUBROUTINE BODIES — mostly direct clones of program 1's
; routines (sub_0110 / sub_0198 / sub_01D0 / sub_0240 / sub_0318 /
; sub_03B8), at fresh VRAM offsets in this concatenated blob.
; =======================================================================

; -----------------------------------------------------------------------
; sub_0EA0 — quad-copy loop with count header + xgkick + END.
;
; Same algorithm as sub_0110 (program 1) but self-contained: it ends
; with `xgkick vi07` and an E-bit terminator instead of falling
; through to a sibling routine.
; -----------------------------------------------------------------------
sub_0EA0:
pad ; xtop vi12
pad ; ilwr.x vi10, vi12
pad ; iaddiu vi07, vi12, 191
pad ; iaddiu vi09, vi07, 0
pad ; lqi.xyzw vf29, vi12
pad ; iaddiu vi13, vi00, 32767
pad ; iand vi10, vi13, vi10
pad ; sqi.xyzw vf29, vi09
sub_0EA0_loop:
pad ; lqi.xyzw vf28, vi12
pad ; iaddi vi10, vi10, -1
pad ; nop_swap
pad ; ibne vi10, vi00, sub_0EA0_loop
pad ; sqi.xyzw vf28, vi09                ; (branch delay slot)
pad ; nop_swap
pad ; xgkick vi07
epad ; nop_swap                          ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_0F28 — patch .xy lanes of mem[2] from VIF input.  Direct clone
; of sub_0198 in program 1.
; -----------------------------------------------------------------------
sub_0F28:
pad ; xtop vi01
pad ; lq.xyzw vf30, 2(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; move.xy vf30, vf31
pad ; sq.xyzw vf30, 2(vi00)
epad ; nop_swap                          ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_0F60 — bulk 4-quad upload to mem[256..259].  Direct clone of
; sub_01D0 in program 1 (same vf18/19/16/17 destination order).
; -----------------------------------------------------------------------
sub_0F60:
pad ; xtop vi12
pad ; iaddiu vi13, vi00, 256
pad ; lqi.xyzw vf18, vi12
pad ; lqi.xyzw vf19, vi12
pad ; lqi.xyzw vf16, vi12
pad ; lqi.xyzw vf17, vi12
pad ; sqi.xyzw vf18, vi13
pad ; sqi.xyzw vf19, vi13
pad ; sqi.xyzw vf16, vi13
pad ; sqi.xyzw vf17, vi13
epad ; nop_swap                          ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; exit_0FC0 — shared "end immediately" stub for program 2.  Direct
; clone of exit_0230 in program 1.
; -----------------------------------------------------------------------
exit_0FC0:
epad ; nop_swap                          ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_0FD0 — palette-indexed vertex transform with GS kick.  Direct
; clone of sub_0240 in program 1; same algorithm, fall-through into
; sub_10A8 for its terminator.
; -----------------------------------------------------------------------
sub_0FD0:
pad ; xtop vi12
pad ; iaddiu vi11, vi12, 1
pad ; ilwr.x vi10, vi12
pad ; lq.xyzw vf29, 0(vi12)
pad ; iaddiu vi13, vi00, 32767
pad ; iaddiu vi07, vi12, 191
pad ; iaddiu vi09, vi07, 0
pad ; sqi.xyzw vf29, vi09
pad ; iand vi10, vi13, vi10
pad ; iaddiu vi13, vi00, 1
pad ; lq.xyzw vf09, 0(vi11)
pad ; ilwr.w vi14, vi11
pad ; nop_swap
pad ; iand vi15, vi13, vi14

sub_0FD0_loop:
add.xy vf09, vf09, vf16 ; lq.xyzw vf20, 256(vi15)
pad ; move.w vf09, vf00
pad ; iaddiu vi11, vi11, 1
pad ; ilwr.w vi14, vi11
pad ; iaddi vi10, vi10, -1
ftoi4.xyzw vf10, vf09 ; sqi.xyzw vf20, vi09
pad ; lq.xyzw vf09, 0(vi11)
pad ; iand vi15, vi13, vi14
pad ; ibne vi10, vi00, sub_0FD0_loop
pad ; sqi.xyzw vf10, vi09                ; (branch delay slot)

pad ; nop_swap
pad ; xgkick vi07
pad ; nop_swap                           ; falls through into sub_10A8

; -----------------------------------------------------------------------
; sub_10A8 — final palette-step + exit.  Direct clone of sub_0318;
; reachable as own entry OR fall-through from sub_0FD0.
; -----------------------------------------------------------------------
sub_10A8:
add.xy vf16, vf16, vf17 ; nop_swap
pad ; b exit_0FC0                        ; → exit_0FC0 (END)
pad ; nop_swap                           ; (branch delay slot)

; -----------------------------------------------------------------------
; sub_10C0 — I-register setup + 4-quad load.
;
; Loads two I-immediates into the VU0 I-register via the I-bit on a
; `pad`-upper bundle:
;   - 0x10C8: pad[I] + imm 0x4B7FFFFE (= IEEE-754 ~16777214.0;
;     used by `addi.w vf14, vf00` at 0x10D0 to set vf14.w).
;   - 0x10D8: pad[I] + imm 0x457FF000 (= IEEE-754 4094.0;
;     used by `addi.xy vf14, vf00` at 0x10E0 to set vf14.xy).
; Then loads vf01..vf04 from the vi13 stream.
;
; assemble_vu0.py has no I-bit `pad` suffix yet, so both I-bundles
; are emitted as two raw `.word`s.  disasm renders the lowers as
; `jalr vi31, vi31` (0x4B7FFFFE) and an op7=0x22 ".word" (0x457FF000)
; — both are immediate misreads.
; -----------------------------------------------------------------------
sub_10C0:
pad ; xtop vi13
.word 0x800002FF ; .word 0x4B7FFFFE      ; pad[I] + I = 0x4B7FFFFE (~16777214.0f)
addi.w vf14, vf00 ; move.xyzw vf13, vf00 ; vf14.w = vf00.w + I (= 16777214.0); vf13 = 0
.word 0x800002FF ; .word 0x457FF000      ; pad[I] + I = 0x457FF000 (= 4094.0f)
addi.xy vf14, vf00 ; nop_swap            ; vf14.xy = vf00.xy + I (= 4094.0)
pad ; lqi.xyzw vf01, vi13
pad ; lqi.xyzw vf02, vi13
pad ; lqi.xyzw vf03, vi13
pad ; lqi.xyzw vf04, vi13
epad ; nop_swap                          ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_1118 — bulk 8-quad load into vf05..vf12.  Variant of sub_03B8
; (program 1) at a different destination-register block.
; -----------------------------------------------------------------------
sub_1118:
pad ; xtop vi13
pad ; lqi.xyzw vf05, vi13
pad ; lqi.xyzw vf06, vi13
pad ; lqi.xyzw vf07, vi13
pad ; lqi.xyzw vf08, vi13
pad ; lqi.xyzw vf09, vi13
pad ; lqi.xyzw vf10, vi13
pad ; lqi.xyzw vf11, vi13
pad ; lqi.xyzw vf12, vi13
epad ; nop_swap                          ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_1170 — 4-bundle shared terminator (TPC=0xE0 in program 2's
; dispatch).  Same shape as sub_0A30: an extra `nop_swap` slot before
; the E-bit so the sub_1188 loop tail's `b L_03B0` lands one bundle
; ahead of the END.
; -----------------------------------------------------------------------
sub_1170:
pad ; nop_swap                           ; do nothing (entry / branch delay slot)
epad ; nop_swap                          ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_1188 — program-2 skinned vertex transform (variant 4).
;
; Same overall algorithm as sub_0428 (see that routine for full docs)
; with the following differences:
;   * Uses vi04 as the count register (not vi06) and vi05 as a 3-slot
;     decimator (not vi07).
;   * Output-base offset is +252 quads (not +192): `iaddiu vi01, vi13,
;     252`.  vi01 = vi13 + 252; output cursor vi03 = vi01 + 1.
;   * Lighting/color registers shuffled: front-face marker vf19
;     (not vf26), back-face marker vf20 (not vf27).
;   * Bone-weight register vf16 (not vf21/22); per-vertex matrix
;     selection via vf15/vf16/vf17/vf18.
;   * Loop start label is sub_1188_loop (= L_04D0), reached after a
;     full pre-loop matrix-mul prologue.
;   * `iaddiu vi07, vi00, 208` sets the clip-mask in vi07 (not vi09).
;   * Bundle 0x12C8 is the I-bit 255.0f trick (upper `mul.xyz vf22,
;     vf18, vf29` + I-bit; lower 0x437F0000 → I); disasm reads the
;     lower as `bal vi31, L_0510`, which is a misread.
;   * Loop tail: `b L_03B0` (into the 1-bundle pre-END at sub_1170).
; -----------------------------------------------------------------------
sub_1188:
pad ; xtop vi13
pad ; iaddiu vi14, vi00, 32767
pad ; iaddiu vi02, vi13, 1
pad ; ilwr.x vi04, vi13                 ; vi04 = count
pad ; lq.xyzw vf29, 0(vi13)
pad ; iand vi04, vi14, vi04
pad ; iaddiu vi01, vi13, 252            ; output base = vi13 + 252
pad ; sq.xyzw vf29, 0(vi01)
pad ; iaddiu vi14, vi14, 1
pad ; iaddiu vi03, vi01, 1
pad ; mfir.w vf19, vi00                  ; vf19.w = 0 (front-face marker)
pad ; mfir.w vf20, vi14                  ; vf20.w = 0x8000 (back-face marker)
pad ; iaddiu vi07, vi00, 208             ; vi07 = clip mask 0xD0
pad ; lqi.xyzw vf18, vi02
pad ; lq.xyzw vf23, 2(vi00)
sub.w       vf21, vf21, vf21 ; lq.xyzw vf16, 1(vi02)    ; vf21.w = 0; load weight quad
pad ; lq.xyzw vf15, 0(vi02)
pad ; lq.xyzw vf17, 2(vi02)
pad ; iaddiu vi02, vi02, 3

mulax.xyzw  vf05, vf16 ; nop_swap
madday.xyzw vf06, vf16 ; nop_swap
maddaz.xyzw vf07, vf16 ; nop_swap
maddw.xyzw  vf29, vf08, vf16 ; nop_swap
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maddaz.xyzw vf03, vf15 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; nop_swap
maxx.xyzw   vf29, vf29, vf00 ; nop_swap
add.xy      vf17, vf17, vf23 ; nop_swap
pad ; nop_swap
pad ; div Q, vf00.w, vf28.w
pad ; nop_swap
pad ; nop_swap

sub_1188_loop:
mulax.xyzw  vf09, vf29 ; lqi.xyzw vf15, vi02
madday.xyzw vf10, vf29 ; lqi.xyzw vf16, vi02
maddaz.xyzw vf11, vf29 ; nop_swap
maddw.xyzw  vf29, vf12, vf29 ; iaddi vi04, vi04, -1
mulq.xyz    vf28, vf28 ; waitq
mulq.xyz    vf21, vf17 ; nop_swap
mulax.xyzw  vf01, vf15 ; move.w vf22, vf18
; I-bit bundle: upper mul.xyz vf22,vf18,vf29 + I-bit; lower = 255.0f → I
.word 0x81DD95AA ; .word 0x437F0000
madday.xyzw vf02, vf15 ; lqi.xyzw vf17, vi02
ftoi4.xyz   vf19, vf28 ; sq.xyzw vf21, 0(vi03)
ftoi4.xyz   vf20, vf28 ; nop_swap
minii.xyzw  vf22, vf22 ; nop_swap
sub.xyw     vf00, vf13, vf28 ; nop_swap
sub.xyw     vf00, vf28, vf14 ; nop_swap
maddaz.xyzw vf03, vf15 ; nop_swap
ftoi0.xyzw  vf22, vf22 ; iaddi vi05, vi05, -1
maddw.xyzw  vf28, vf04, vf00 ; fmand vi14, vi07
mulax.xyzw  vf05, vf16 ; fmand vi14, vi14
madday.xyzw vf06, vf16 ; nop_swap
maddaz.xyzw vf07, vf16 ; ibne vi14, vi07, L_0598
maddw.xyzw  vf29, vf08, vf16 ; sq.xyzw vf22, 1(vi03)
pad ; ibgtz vi05, L_05A0
pad ; sq.xyzw vf19, 2(vi03)
pad ; b L_05A8
pad ; nop_swap
L_0598:
pad ; iaddiu vi05, vi00, 3
L_05A0:
pad ; sq.xyzw vf20, 2(vi03)
L_05A8:
pad ; div Q, vf00.w, vf28.w
maxx.xyzw   vf29, vf29, vf00 ; ibne vi04, vi00, sub_1188_loop
pad ; iaddiu vi03, vi03, 3
pad ; xgkick vi01
pad ; b L_03B0
pad ; nop_swap                           ; (branch delay slot)

; -----------------------------------------------------------------------
; sub_1398 — 3-bundle shared terminator (TPC=0xE0 dispatch via 0x0E90;
; also `b L_05D8` from sub_13B0).  Same shape as sub_0410.
; -----------------------------------------------------------------------
sub_1398:
pad ; nop_swap                           ; do nothing (entry)
epad ; nop_swap                          ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_13B0 — program-2 skinned vertex transform (variant 5).
;
; Near-clone of sub_1188 with restructured loop body and a different
; placement of the I-bit immediate bundle (now at 0x1510 with the
; same `0x437F0000` = 255.0f I-immediate, upper `mul.xyz vf22, vf18,
; vf29` with I-bit).  Loop tail: `b L_05D8`.
; -----------------------------------------------------------------------
sub_13B0:
pad ; xtop vi13
pad ; iaddiu vi14, vi00, 32767
pad ; iaddiu vi02, vi13, 1
pad ; ilwr.x vi04, vi13
pad ; lq.xyzw vf29, 0(vi13)
pad ; iand vi04, vi14, vi04
pad ; iaddiu vi01, vi13, 252
pad ; sq.xyzw vf29, 0(vi01)
pad ; iaddiu vi14, vi14, 1
pad ; iaddiu vi03, vi01, 1
pad ; mfir.w vf19, vi00
pad ; mfir.w vf20, vi14
pad ; iaddiu vi07, vi00, 208
pad ; lqi.xyzw vf18, vi02
pad ; lq.xyzw vf23, 2(vi00)
sub.w       vf21, vf21, vf21 ; lq.xyzw vf16, 1(vi02)
pad ; lq.xyzw vf15, 0(vi02)
pad ; lq.xyzw vf17, 2(vi02)
pad ; iaddiu vi02, vi02, 3

mulax.xyzw  vf05, vf16 ; nop_swap
madday.xyzw vf06, vf16 ; nop_swap
maddaz.xyzw vf07, vf16 ; nop_swap
maddw.xyzw  vf29, vf08, vf16 ; nop_swap
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maddaz.xyzw vf03, vf15 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; nop_swap
maxx.xyzw   vf29, vf29, vf00 ; nop_swap
add.xy      vf17, vf17, vf23 ; nop_swap
pad ; nop_swap
pad ; div Q, vf00.w, vf28.w
pad ; nop_swap
pad ; nop_swap

sub_13B0_loop:
mulax.xyzw  vf09, vf29 ; iaddi vi04, vi04, -1
madday.xyzw vf10, vf29 ; lqi.xyzw vf15, vi02
maddaz.xyzw vf11, vf29 ; lqi.xyzw vf16, vi02
maddw.xyzw  vf29, vf12, vf29 ; nop_swap
mulq.xyz    vf28, vf28 ; waitq
mulq.xyz    vf21, vf17 ; nop_swap
mulax.xyzw  vf01, vf15 ; lqi.xyzw vf17, vi02
mul.xyz     vf29, vf29, vf29 ; nop_swap             ; vf29²
ftoi4.xyz   vf19, vf28 ; move.w vf22, vf18
ftoi4.xyz   vf20, vf28 ; sq.xyzw vf21, 0(vi03)
sub.xyw     vf00, vf13, vf28 ; nop_swap
; I-bit bundle: upper mul.xyz vf22,vf18,vf29 + I-bit; lower = 255.0f → I
.word 0x81DD95AA ; .word 0x437F0000
sub.xyw     vf00, vf28, vf14 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maddaz.xyzw vf03, vf15 ; fmand vi14, vi07
minii.xyzw  vf22, vf22 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; fmand vi14, vi14
mulax.xyzw  vf05, vf16 ; nop_swap
madday.xyzw vf06, vf16 ; nop_swap
ftoi0.xyzw  vf22, vf22 ; iaddi vi05, vi05, -1
maddaz.xyzw vf07, vf16 ; div Q, vf00.w, vf28.w
maddw.xyzw  vf29, vf08, vf16 ; nop_swap
add.xy      vf17, vf17, vf23 ; ibne vi14, vi07, L_07D8
pad ; sq.xyzw vf22, 1(vi03)
pad ; ibgtz vi05, L_07E0
pad ; sq.xyzw vf19, 2(vi03)
pad ; b L_07E8
pad ; nop_swap
L_07D8:
pad ; iaddiu vi05, vi00, 3
L_07E0:
pad ; sq.xyzw vf20, 2(vi03)
L_07E8:
maxx.xyzw   vf29, vf29, vf00 ; iaddiu vi03, vi03, 3
pad ; ibne vi04, vi00, sub_13B0_loop
pad ; nop_swap                           ; (branch delay slot)
pad ; xgkick vi01
pad ; b L_05D8
.word 0x4A380100 ; nop                   ; upper: `add.w vf04,vf00,vf24` + flag bits (E/T/25-ish)

; -----------------------------------------------------------------------
; sub_15D8 — 4-bundle shared terminator with extra `nop_swap` at
; L_0820 (so sub_15F8 can `b L_0820` and hit the E-bit one bundle
; later).  Same shape as sub_0A30 / sub_1170.
; -----------------------------------------------------------------------
sub_15D8:
pad ; nop_swap                           ; do nothing (entry / branch delay slot)
L_0820:
pad ; nop_swap                           ; sub_15F8's `b L_0820` lands here
epad ; nop_swap                          ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_15F8 — program-2 skinned vertex transform (variant 6).
;
; Near-clone of sub_13B0 with one additional `move.w vf29, vf28` /
; `ftoi0.xyzw vf22, vf18` bundle at L_0910, and a different loop-exit
; pattern that branches to L_0820 (one bundle past sub_15D8 entry)
; for the END.
; -----------------------------------------------------------------------
sub_15F8:
pad ; xtop vi13
pad ; iaddiu vi14, vi00, 32767
pad ; iaddiu vi02, vi13, 1
pad ; ilwr.x vi04, vi13
pad ; lq.xyzw vf29, 0(vi13)
pad ; iand vi04, vi14, vi04
pad ; iaddiu vi01, vi13, 252
pad ; sq.xyzw vf29, 0(vi01)
pad ; iaddiu vi14, vi14, 1
pad ; iaddiu vi03, vi01, 1
pad ; mfir.w vf19, vi00
pad ; mfir.w vf20, vi14
pad ; iaddiu vi07, vi00, 208
pad ; lqi.xyzw vf18, vi02
pad ; lq.xyzw vf23, 2(vi00)
sub.w       vf21, vf21, vf21 ; lqi.xyzw vf15, vi02
pad ; lqi.xyzw vf17, vi02
pad ; nop_swap
pad ; nop_swap

mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maddaz.xyzw vf03, vf15 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; nop_swap
pad ; lqi.xyzw vf15, vi02
pad ; nop_swap
pad ; nop_swap
add.xy      vf17, vf17, vf23 ; div Q, vf00.w, vf28.w

sub_15F8_loop:
ftoi0.xyzw  vf22, vf18 ; move.w vf29, vf28
mulq.xyz    vf29, vf28 ; waitq
mulq.xyz    vf21, vf17 ; iaddi vi05, vi05, -1
mulax.xyzw  vf01, vf15 ; lqi.xyzw vf17, vi02
madday.xyzw vf02, vf15 ; sq.xyzw vf22, 1(vi03)
sub.xyw     vf00, vf13, vf29 ; iaddi vi04, vi04, -1
sub.xyw     vf00, vf29, vf14 ; sq.xyzw vf21, 0(vi03)
maddaz.xyzw vf03, vf15 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; lqi.xyzw vf15, vi02
ftoi4.xyz   vf19, vf29 ; fmand vi14, vi07
ftoi4.xyz   vf20, vf29 ; fmand vi14, vi14
add.xy      vf17, vf17, vf23 ; ibne vi14, vi07, L_0998
pad ; div Q, vf00.w, vf28.w
pad ; ibgtz vi05, L_09A0
pad ; sq.xyzw vf19, 2(vi03)
pad ; b L_09A8
pad ; nop_swap
L_0998:
pad ; iaddiu vi05, vi00, 3
L_09A0:
pad ; sq.xyzw vf20, 2(vi03)
L_09A8:
pad ; iaddiu vi03, vi03, 3
pad ; ibne vi04, vi00, sub_15F8_loop
pad ; nop_swap                           ; (branch delay slot)
pad ; xgkick vi01
pad ; b L_0820
pad ; nop_swap                           ; (branch delay slot)

; =======================================================================
; THIRD VU0 PROGRAM begins here.  Same multi-program concatenation as
; the program-1 → program-2 transition at 0x0DB0.
; =======================================================================

; Program-3 pre-header filler (one bundle of true-zero halves) +
; control-flag prologue (parallels program 2's 0x0DB0..0x0DC8 with a
; different FCSET immediate).
nop ; nop                                ; 0x1798 — true-zero filler
nop ; .word 0x70000000                   ; 0x17A0 — lower op7=0x38
nop ; nop                                ; 0x17A8 — true-zero filler
.assert_pc 0x9F0
