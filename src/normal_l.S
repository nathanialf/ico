; -----------------------------------------------------------------------
; NormalLMicroProgram — VU1 microprogram (ico2000.a normal_l.o), seki/GS renderer.
;
; One of the 5 per-primitive VU1 microprograms in ICO's .vutext section
; (cluster/mesh/normal_c/normal_l/particle), managed by MicroCode.o
; (mc_TransMicroCode).  Split by the MAIN.MAP .vutext .o boundaries.
;
; Clean-room: bytes re-derived from published VU0/VU1 documentation
; (EE User's Manual, PCSX2 microVU GPL-3.0 opcode dispatch, ps2sdk) via
; tools/assemble_vu0.py — never from extracted disc data.  Byte-identical
; to aug6 .vutext 0x26E800..0x2704A0 (7328 bytes); labels are
; program-relative (VU micromem is loaded at 0).
; -----------------------------------------------------------------------
.vu0
.org 0x0000
nop ; .word 0x600001C8                  ; 0x2E90 — FCSET imm24=0x1C8
.word 0x4A000000 ; nop                  ; 0x2E98 — upper FMAC-family + true-zero

; Program-4 entry-stub dispatch.
pad ; b L_0150                          ; 0x2EA0 — entry → L_0150
pad ; nop_swap
pad ; b L_01D8                          ; 0x2EB0 — entry → L_01D8
pad ; nop_swap
pad ; nop_swap                          ; 0x2EC0 — reserved
pad ; nop_swap                          ; 0x2EC8 — reserved
pad ; nop_swap                          ; 0x2ED0 — reserved
pad ; nop_swap                          ; 0x2ED8 — reserved
pad ; b L_0210                          ; 0x2EE0 — entry → L_0210
pad ; nop_swap
pad ; b L_0280                          ; 0x2EF0 — entry → L_0280
pad ; nop_swap
pad ; b L_0358                          ; 0x2F00 — entry → L_0358
pad ; nop_swap
pad ; nop_swap                          ; 0x2F10 — reserved
pad ; nop_swap                          ; 0x2F18 — reserved
pad ; b L_0370                          ; 0x2F20 — entry → L_0370
pad ; nop_swap
pad ; b L_0458                          ; 0x2F30 — entry → L_0458
pad ; nop_swap
pad ; nop_swap                          ; 0x2F40 — reserved
pad ; nop_swap                          ; 0x2F48 — reserved
pad ; nop_swap                          ; 0x2F50 — reserved
pad ; nop_swap                          ; 0x2F58 — reserved
pad ; nop_swap                          ; 0x2F60 — reserved
pad ; nop_swap                          ; 0x2F68 — reserved
pad ; nop_swap                          ; 0x2F70 — reserved
pad ; nop_swap                          ; 0x2F78 — reserved
pad ; nop_swap                          ; 0x2F80 — reserved
pad ; nop_swap                          ; 0x2F88 — reserved
pad ; nop_swap                          ; 0x2F90 — reserved
pad ; nop_swap                          ; 0x2F98 — reserved
pad ; b L_04F0                          ; 0x2FA0 — entry → L_04F0
pad ; nop_swap
pad ; b L_0790                          ; 0x2FB0 — entry → L_0790  (far target)
pad ; nop_swap
pad ; b L_18E0                          ; 0x2FC0 — entry → L_18E0  (far target)
pad ; nop_swap
pad ; b L_0A30                          ; 0x2FD0 — entry → L_0A30  (far target)
pad ; nop_swap

; =======================================================================
; PROGRAM 4 SUBROUTINE BODIES.  Direct clones of program-1/2/3 routines
; at fresh VRAM offsets.
; =======================================================================

; sub_2FE0 — copy-with-count + xgkick + END (clone of sub_0EA0).
sub_2FE0:
pad ; xtop vi12
pad ; ilwr.x vi10, vi12
pad ; iaddiu vi07, vi12, 191
pad ; iaddiu vi09, vi07, 0
pad ; lqi.xyzw vf29, vi12
pad ; iaddiu vi13, vi00, 32767
pad ; iand vi10, vi13, vi10
pad ; sqi.xyzw vf29, vi09
sub_2FE0_loop:
pad ; lqi.xyzw vf28, vi12
pad ; iaddi vi10, vi10, -1
pad ; nop_swap
pad ; ibne vi10, vi00, sub_2FE0_loop
pad ; sqi.xyzw vf28, vi09                ; (branch delay slot)
pad ; nop_swap
pad ; xgkick vi07
epad ; nop_swap                          ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; sub_3068 — mem[2].xy patch (clone of sub_0F28).
sub_3068:
pad ; xtop vi01
pad ; lq.xyzw vf30, 2(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; move.xy vf30, vf31
pad ; sq.xyzw vf30, 2(vi00)
epad ; nop_swap                          ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; sub_30A0 — 4-quad matrix upload to mem[256] (clone of sub_0F60).
sub_30A0:
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

; exit_3100 — shared E-bit stub (clone of exit_0FC0).
exit_3100:
epad ; nop_swap                          ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; sub_3110 — palette-indexed vertex transform (clone of sub_0FD0);
; falls through into sub_31E8 for terminator.
sub_3110:
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

sub_3110_loop:
add.xy vf09, vf09, vf16 ; lq.xyzw vf20, 256(vi15)
pad ; move.w vf09, vf00
pad ; iaddiu vi11, vi11, 1
pad ; ilwr.w vi14, vi11
pad ; iaddi vi10, vi10, -1
ftoi4.xyzw vf10, vf09 ; sqi.xyzw vf20, vi09
pad ; lq.xyzw vf09, 0(vi11)
pad ; iand vi15, vi13, vi14
pad ; ibne vi10, vi00, sub_3110_loop
pad ; sqi.xyzw vf10, vi09                ; (branch delay slot)

pad ; nop_swap
pad ; xgkick vi07
pad ; nop_swap                           ; falls through into sub_31E8

; sub_31E8 — final palette-step + `b exit_3100` (clone of sub_10A8).
sub_31E8:
add.xy vf16, vf16, vf17 ; nop_swap
pad ; b exit_3100
pad ; nop_swap                           ; (branch delay slot)

; sub_3200 — bulk 13-quad upload to mem[16..27] + mem[3]→mem[37]
; (clone of sub_1B10).
sub_3200:
pad ; xtop vi01
pad ; lqi.xyzw vf01, vi01
pad ; sq.xyzw vf01, 16(vi00)
pad ; lqi.xyzw vf02, vi01
pad ; sq.xyzw vf02, 17(vi00)
pad ; lqi.xyzw vf03, vi01
pad ; sq.xyzw vf03, 18(vi00)
pad ; lqi.xyzw vf04, vi01
pad ; sq.xyzw vf04, 19(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 20(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 21(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 22(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 23(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 24(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 25(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 26(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 27(vi00)
pad ; lq.xyzw vf31, 3(vi00)
pad ; sq.xyzw vf31, 37(vi00)
epad ; nop_swap                          ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; sub_32E8 — bulk 8-quad upload via vf31 to mem[28..35] (clone of sub_1BF8).
sub_32E8:
pad ; xtop vi01
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 28(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 29(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 30(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 31(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 32(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 33(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 34(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; sq.xyzw vf31, 35(vi00)
epad ; nop_swap                          ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; sub_3380 — I-register setup with extended bulk load (variant of sub_1C90
; with 8 additional lq from mem[28..35] into vf05..vf12).
sub_3380:
.word 0x800002FF ; .word 0x4B7FFFFE      ; pad[I] + I = 0x4B7FFFFE
addi.w vf14, vf00 ; move.xyzw vf13, vf00
.word 0x800002FF ; .word 0x457FF000      ; pad[I] + I = 0x457FF000
addi.xy vf14, vf00 ; nop_swap
pad ; lq.xyzw vf23, 2(vi00)
pad ; lq.xyzw vf05, 28(vi00)
pad ; lq.xyzw vf06, 29(vi00)
pad ; lq.xyzw vf07, 30(vi00)
pad ; lq.xyzw vf08, 31(vi00)
pad ; lq.xyzw vf09, 32(vi00)
pad ; lq.xyzw vf10, 33(vi00)
pad ; lq.xyzw vf11, 34(vi00)
pad ; lq.xyzw vf12, 35(vi00)
epad ; nop_swap                          ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot
pad ; xtop vi13

; --- sub_3380 transform body (0x3400..0x3618) ---
; Reached directly when EE sets VU0_TPC=0x3400.  Loop tail branches
; `b L_04F0` to re-enter sub_3380's I-imm setup tail, which then hits
; the E-bit at 0x33E8 to terminate.  Same exit-via-branch-into-tail
; pattern as sub_1EA0 / sub_1C90 in program 3.
pad ; iaddiu vi14, vi00, 32767
pad ; iaddiu vi02, vi13, 1
pad ; ilwr.x vi04, vi13
pad ; lq.xyzw vf29, 0(vi13)
pad ; iand vi04, vi14, vi04
pad ; iaddiu vi01, vi13, 192
pad ; sq.xyzw vf29, 0(vi01)
pad ; iaddiu vi14, vi14, 1
pad ; iaddi vi03, vi01, -2               ; vi03 = vi01 - 2 (note: -2, not +1)
pad ; mfir.w vf19, vi00
pad ; mfir.w vf20, vi14
pad ; iaddiu vi07, vi00, 208
sub.w       vf21, vf21, vf21 ; lq.xyzw vf16, 1(vi02)
pad ; lq.xyzw vf15, 0(vi02)
pad ; lq.xyzw vf17, 2(vi02)
pad ; lq.xyzw vf18, 3(vi02)
mulax.xyzw  vf05, vf16 ; nop_swap
madday.xyzw vf06, vf16 ; nop_swap
maddaz.xyzw vf07, vf16 ; nop_swap
maddw.xyzw  vf29, vf08, vf16 ; nop_swap
sub.w       vf00, vf17, vf00 ; nop_swap
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maxx.xyzw   vf29, vf29, vf00 ; nop_swap
maddaz.xyzw vf03, vf15 ; fsand vi15, 0x2
maddw.xyzw  vf28, vf04, vf00 ; nop_swap
add.xy      vf17, vf17, vf23 ; nop_swap
pad ; nop_swap
mulax.xyzw  vf09, vf29 ; nop_swap
madday.xyzw vf10, vf29 ; div Q, vf00.w, vf28.w

L_0660:
maddaz.xyzw vf11, vf29 ; iaddiu vi02, vi02, 4
maddw.xyzw  vf29, vf12, vf29 ; ibeq vi15, vi00, L_0680
pad ; lq.xyzw vf16, 1(vi02)
pad ; iaddiu vi05, vi00, 3
L_0680:
mulq.xyz    vf28, vf28 ; waitq
mulq.xyz    vf21, vf17 ; lq.xyzw vf15, 0(vi02)
maxx.xyzw   vf29, vf29, vf00 ; lq.xyzw vf17, 2(vi02)
mulax.xyzw  vf05, vf16 ; iaddi vi04, vi04, -1
sub.xyw     vf00, vf13, vf28 ; iaddiu vi03, vi03, 3
sub.xyw     vf00, vf28, vf14 ; sq.xyzw vf21, 0(vi03)
; I-bit bundle: upper mul.xyz vf18,vf18,vf29 + I-bit; lower = 255.0f → I
.word 0x81DD94AA ; .word 0x437F0000
madday.xyzw vf06, vf16 ; move.xyzw vf30, vf28
maddaz.xyzw vf07, vf16 ; fmand vi14, vi07
maddw.xyzw  vf29, vf08, vf16 ; fmand vi14, vi14
minii.xyzw  vf22, vf18 ; iaddi vi05, vi05, -1
mulax.xyzw  vf01, vf15 ; lq.xyzw vf18, 3(vi02)
sub.w       vf00, vf17, vf00 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
ftoi0.xyzw  vf22, vf22 ; nop_swap
maddaz.xyzw vf03, vf15 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; fsand vi15, 0x2
maxx.xyzw   vf29, vf29, vf00 ; nop_swap
ftoi4.xyz   vf20, vf30 ; sq.xyzw vf22, 1(vi03)
ftoi4.xyz   vf19, vf30 ; ibne vi14, vi07, L_0760
add.xy      vf17, vf17, vf23 ; div Q, vf00.w, vf28.w
pad ; ibgtz vi05, L_0768
pad ; nop_swap
mulax.xyzw  vf09, vf29 ; ibne vi04, vi00, L_0660
madday.xyzw vf10, vf29 ; sq.xyzw vf19, 2(vi03)
pad ; xgkick vi01
pad ; b L_04F0                           ; → sub_3380's E-bit
pad ; nop_swap                           ; (branch delay slot)
L_0760:
pad ; iaddiu vi05, vi00, 3
L_0768:
mulax.xyzw  vf09, vf29 ; ibne vi04, vi00, L_0660
madday.xyzw vf10, vf29 ; sq.xyzw vf20, 2(vi03)
pad ; xgkick vi01
pad ; b L_04F0                           ; → sub_3380's E-bit
pad ; nop_swap                           ; (branch delay slot)

; -----------------------------------------------------------------------
; sub_3620 — I-register setup (clone of sub_3380's I-imm prologue).
; Transform body extends past 0x3690 (deferred to next batch).
; -----------------------------------------------------------------------
sub_3620:
.word 0x800002FF ; .word 0x4B7FFFFE      ; pad[I] + I = 0x4B7FFFFE
L_0798:
addi.w vf14, vf00 ; move.xyzw vf13, vf00
.word 0x800002FF ; .word 0x457FF000      ; pad[I] + I = 0x457FF000
addi.xy vf14, vf00 ; nop_swap
pad ; lq.xyzw vf23, 2(vi00)
pad ; lq.xyzw vf05, 28(vi00)
pad ; lq.xyzw vf06, 29(vi00)
pad ; lq.xyzw vf07, 30(vi00)
pad ; lq.xyzw vf08, 31(vi00)
pad ; lq.xyzw vf09, 32(vi00)
pad ; lq.xyzw vf10, 33(vi00)
pad ; lq.xyzw vf11, 34(vi00)
pad ; lq.xyzw vf12, 35(vi00)
epad ; nop_swap                          ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; --- sub_3620 transform body (0x3698..0x38B8) ---
; Reached directly when EE sets VU0_TPC=0x3698.  Loop tail `b L_0798`
; re-enters sub_3620's I-setup-tail at 0x3628 (the addi.w bundle),
; which then falls through to the E-bit at 0x3688 and terminates.
; This routine adds a specular-power chain (mul.xyz vf30 squared
; twice) before quantizing, and has the I-bit 255.0f trick at 0x3810.
pad ; xtop vi13
.word 0x4A000100 ; nop                   ; upper: `add vf04, vf00, vf00` + flag bits (E/T/25-ish)
pad ; iaddiu vi14, vi00, 32767
pad ; iaddiu vi02, vi13, 1
pad ; ilwr.x vi04, vi13
pad ; lq.xyzw vf29, 0(vi13)
pad ; iand vi04, vi14, vi04
pad ; iaddiu vi01, vi13, 192
pad ; sq.xyzw vf29, 0(vi01)
pad ; iaddiu vi14, vi14, 1
pad ; iaddiu vi03, vi01, 1
pad ; mfir.w vf19, vi00
pad ; mfir.w vf20, vi14
pad ; iaddiu vi07, vi00, 208
sub.w       vf21, vf21, vf21 ; lq.xyzw vf16, 1(vi02)
pad ; lq.xyzw vf15, 0(vi02)
pad ; lq.xyzw vf17, 2(vi02)
pad ; lq.xyzw vf18, 3(vi02)
mulax.xyzw  vf05, vf16 ; nop_swap
madday.xyzw vf06, vf16 ; nop_swap
maddaz.xyzw vf07, vf16 ; nop_swap
maddw.xyzw  vf29, vf08, vf16 ; nop_swap
sub.w       vf00, vf17, vf00 ; nop_swap
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maddaz.xyzw vf03, vf15 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; fsand vi15, 0x2
maxx.xyzw   vf29, vf29, vf00 ; nop_swap
add.xy      vf17, vf17, vf23 ; nop_swap
pad ; nop_swap

L_08F8:
mulax.xyzw  vf09, vf29 ; div Q, vf00.w, vf28.w
madday.xyzw vf10, vf29 ; iaddiu vi02, vi02, 4
maddaz.xyzw vf11, vf29 ; ibeq vi15, vi00, L_0920
maddw.xyzw  vf29, vf00, vf29 ; lq.xyzw vf16, 1(vi02)
pad ; iaddiu vi05, vi00, 3
L_0920:
maxx.xyzw   vf29, vf29, vf00 ; waitq
mulq.xyz    vf28, vf28 ; nop_swap
mulq.xyz    vf21, vf17 ; lq.xyzw vf15, 0(vi02)
mulax.xyzw  vf05, vf16 ; lq.xyzw vf17, 2(vi02)
mul.xyz     vf30, vf29, vf29 ; iaddi vi04, vi04, -1
sub.xyw     vf00, vf13, vf28 ; nop_swap
sub.xyw     vf00, vf28, vf14 ; sq.xyzw vf21, 0(vi03)
madday.xyzw vf06, vf16 ; nop_swap
mul.xyz     vf30, vf30, vf30 ; nop_swap
maddaz.xyzw vf07, vf16 ; fmand vi14, vi07
maddw.xyzw  vf29, vf08, vf16 ; fmand vi14, vi14
sub.w       vf00, vf17, vf00 ; nop_swap
; I-bit bundle: upper mul.xyz vf18,vf18,vf30 + I-bit; lower = 255.0f → I
.word 0x81DE94AA ; .word 0x437F0000
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maddaz.xyzw vf03, vf15 ; fsand vi15, 0x2
minii.xyzw  vf22, vf18 ; nop_swap
ftoi4.xyz   vf19, vf28 ; iaddi vi05, vi05, -1
ftoi4.xyz   vf20, vf28 ; lq.xyzw vf18, 3(vi02)
maddw.xyzw  vf28, vf04, vf00 ; nop_swap
ftoi0.xyzw  vf22, vf22 ; nop_swap
maxx.xyzw   vf29, vf29, vf00 ; ibne vi14, vi07, L_0A00
add.xy      vf17, vf17, vf23 ; iaddiu vi03, vi03, 3
pad ; ibgtz vi05, L_0A08
pad ; nop_swap
pad ; sq.xyzw vf19, -1(vi03)
pad ; b L_0A10
pad ; nop_swap
L_0A00:
pad ; iaddiu vi05, vi00, 3
L_0A08:
pad ; sq.xyzw vf20, -1(vi03)
L_0A10:
pad ; ibne vi04, vi00, L_08F8
pad ; sq.xyzw vf22, -2(vi03)
pad ; xgkick vi01
pad ; b L_0798                           ; → sub_3620's E-bit

; -----------------------------------------------------------------------
; sub_38C0 — 1-bundle no-op entry (also delay slot of `b L_0798` above).
; Falls through into sub_38C8's I-register setup.
; -----------------------------------------------------------------------
sub_38C0:
pad ; nop_swap                           ; do nothing (entry / branch delay slot)
L_0A38:
.word 0x800002FF ; .word 0x4B7FFFFE      ; pad[I] + I = 0x4B7FFFFE
addi.w vf14, vf00 ; move.xyzw vf13, vf00
.word 0x800002FF ; .word 0x457FF000      ; pad[I] + I = 0x457FF000
addi.xy vf14, vf00 ; nop_swap
pad ; lq.xyzw vf23, 2(vi00)
pad ; lq.xyzw vf05, 24(vi00)
pad ; lq.xyzw vf06, 25(vi00)
pad ; lq.xyzw vf07, 26(vi00)
pad ; lq.xyzw vf08, 27(vi00)
pad ; lq.xyzw vf09, 12(vi00)
pad ; lq.xyzw vf10, 13(vi00)
pad ; lq.xyzw vf11, 14(vi00)
pad ; lq.xyzw vf12, 15(vi00)
epad ; nop_swap                          ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_3940 — full skinned vertex transform with rsqrt + per-vertex
; rotational refinement.  Largest single routine in the blob so far.
;
; Reached via VU0_TPC=0x3940 (entry from sub_38C0 path) OR directly.
; Loop tail `b L_0A38` returns to the I-imm setup tail, which then
; falls through to E-bit at 0x3930 to terminate.
;
; Distinctive features vs earlier transform routines:
;   - rsqrt Q computation for unit-vector normalization at 0x3A60.
;   - mulax.w/madday.w/maddz.w accumulator-form chains feeding a
;     squared-distance computation (vf27 = |vf29|²).
;   - mulaw.xyz/maddaw.xyz/maddw.xyz vf30 chain — a tri-add producing
;     a refined position vf30 from vf27 scaled by vf29.
;   - rinit R / rget.xyzw vf25 — captures the VU0 R-register state
;     (a hardware random-number lane).
;   - Two LOI immediate bundles at 0x3BA8 (= 0.125f) and 0x3BB0
;     (= 0.25f) carrying float constants in the lower-half opcode
;     position; the upper FMAC of those bundles is unaffected (no
;     I-bit) but the next-iter `mulai.xy` / `maddi.xy` consume the
;     last-loaded I value.
;   - Front-face / back-face / refined-position 3-way output store
;     (sq vf19 / vf20 / vf21 at -1(vi03), -1(vi03), -3(vi03)).
; -----------------------------------------------------------------------
sub_3940:
pad ; xtop vi13
pad ; iaddiu vi14, vi00, 32767
pad ; iaddiu vi02, vi13, 1
pad ; ilwr.x vi04, vi13
pad ; lq.xyzw vf29, 0(vi13)
pad ; iand vi04, vi14, vi04
pad ; iaddiu vi01, vi13, 192
pad ; sq.xyzw vf29, 0(vi01)
pad ; iaddi vi14, vi14, 1
pad ; iaddiu vi03, vi01, 1
pad ; mfir.w vf19, vi00
pad ; mfir.w vf20, vi14
sub.w       vf21, vf21, vf21 ; iaddiu vi07, vi00, 208
pad ; lq.xyzw vf15, 0(vi02)
pad ; lq.xyzw vf16, 1(vi02)
pad ; lq.xyzw vf17, 2(vi02)
pad ; lq.xyzw vf18, 3(vi02)

mulax.xyzw  vf05, vf15 ; nop_swap
madday.xyzw vf06, vf15 ; nop_swap
maddaz.xyzw vf07, vf15 ; nop_swap
maddw.xyzw  vf29, vf08, vf00 ; nop_swap
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maddaz.xyzw vf03, vf15 ; nop_swap
maddw.xyzw  vf28, vf04, vf00 ; nop_swap
mul.xyz     vf27, vf29, vf29 ; nop_swap                 ; vf27 = vf29² (squared lights)
mulax.xyzw  vf05, vf16 ; nop_swap
madday.xyzw vf06, vf16 ; nop_swap
maddaz.xyzw vf07, vf16 ; nop_swap
maddw.xyzw  vf30, vf00, vf16 ; nop_swap

L_0BA0:
mulax.w     vf00, vf27 ; div Q, vf00.w, vf28.w          ; sum-of-squares init
madday.w    vf00, vf27 ; iaddiu vi02, vi02, 4
maddz.w     vf27, vf00, vf27 ; iaddi vi04, vi04, -1     ; vf27.w = sum-of-squared-lanes
ftoi0.xyzw  vf22, vf18 ; nop_swap
sub.w       vf00, vf17, vf00 ; nop_swap
addq.x      vf31, vf00 ; waitq                          ; vf31.x = vf00.x + Q
pad ; rsqrt Q, vf00.w, vf27.w                            ; Q = 1/sqrt(|vf29|²)
pad ; sq.xyzw vf22, 1(vi03)
pad ; fsand vi15, 0x2
pad ; ibeq vi15, vi00, L_0C00
pad ; nop_swap
pad ; iaddiu vi05, vi00, 3
L_0C00:
mulq.xyz    vf29, vf29 ; waitq                          ; vf29 = vf29 * Q (unit-length normalize)
mulx.xyz    vf28, vf28, vf31 ; nop_swap                 ; vf28.xyz *= vf31.x
pad ; lq.xyzw vf15, 0(vi02)
pad ; lq.xyzw vf16, 1(vi02)
mul.xyz     vf27, vf29, vf30 ; lq.xyzw vf18, 3(vi02)
sub.xyw     vf00, vf28, vf14 ; lq.xyzw vf17, 2(vi02)
sub.xyw     vf00, vf13, vf28 ; iaddi vi05, vi05, -1
ftoi4.xyz   vf19, vf28 ; nop_swap
mulax.w     vf00, vf27 ; nop_swap
madday.w    vf00, vf27 ; fmand vi14, vi07
maddz.w     vf27, vf00, vf27 ; fmand vi14, vi14
ftoi4.xyz   vf20, vf28 ; nop_swap
pad ; nop_swap
pad ; nop_swap
mulaw.xyz   vf30, vf27 ; nop_swap                       ; ACC = vf30 + ?
maddaw.xyz  vf30, vf27 ; nop_swap
maddw.xyz   vf30, vf29, vf27 ; nop_swap                 ; vf30 += vf29*vf27.w
mulax.xyzw  vf05, vf15 ; nop_swap
madday.xyzw vf06, vf15 ; nop_swap
maddaz.xyzw vf07, vf15 ; nop_swap
maddw.xyzw  vf29, vf08, vf00 ; nop_swap
mulax.xyzw  vf09, vf30 ; nop_swap
madday.xyzw vf10, vf30 ; nop_swap
maddaz.xyzw vf11, vf30 ; nop_swap
maddw.xyzw  vf26, vf00, vf00 ; nop_swap                 ; vf26 = ?
mulax.xyzw  vf01, vf15 ; nop_swap
madday.xyzw vf02, vf15 ; nop_swap
maddaz.xyzw vf03, vf15 ; nop_swap
add.z       vf26, vf26, vf26 ; rinit R, vf00.w          ; R = vf00.w (sequence reset)
maddw.xyzw  vf28, vf04, vf00 ; rget.xyzw vf25           ; vf25 = R (sequence sample)
mul.xyz     vf27, vf29, vf29 ; nop_swap
mulax.xyzw  vf05, vf16 ; nop_swap
addz.xy     vf26, vf26, vf26 ; nop_swap
madday.xyzw vf06, vf16 ; mr32.z vf26, vf00              ; vf26.z = ?
maddaz.xyzw vf07, vf16 ; nop_swap
; LOI bundles: upper has I-bit set (bit 31); lower is the 32-bit
; float immediate loaded into the VU0 I-register.  The upper FMAC
; still executes normally; the I-load happens in parallel.
.word 0x81F0078B ; .word 0x3E000000        ; maddw.xyzw vf30,vf00,vf16 [I-bit]; I = 0.125f
.word 0x8180D1FE ; .word 0x3E800000        ; mulai.xy vf26 [I-bit];           I = 0.25f
maddi.xy    vf26, vf25 ; nop_swap                       ; vf26.xy += vf25 * I
pad ; nop_swap
pad ; nop_swap
pad ; ibne vi14, vi07, L_0D78
mulx.xyz    vf21, vf26, vf31 ; iaddiu vi03, vi03, 3     ; vf21.xyz = vf26 * vf31.x
pad ; ibgtz vi05, L_0D80
pad ; nop_swap
pad ; sq.xyzw vf19, -1(vi03)
pad ; b L_0D88
pad ; nop_swap
L_0D78:
pad ; iaddiu vi05, vi00, 3
L_0D80:
pad ; sq.xyzw vf20, -1(vi03)
L_0D88:
pad ; ibne vi04, vi00, L_0BA0
pad ; sq.xyzw vf21, -3(vi03)                            ; (delay slot — also stores refined vf21)
pad ; xgkick vi01
pad ; b L_0A38                           ; → sub_38C8's I-setup tail/E-bit
pad ; nop_swap                           ; (branch delay slot)

; -----------------------------------------------------------------------
; sub_3C40 — hierarchical LOD mesh subdivision driver (program-4 clone
; of sub_2080).  Same 6-tier dispatch structure as program-1's
; sub_2080, with refreshed targets:
;   L_12F8 / L_12B8 / L_12A8 (jr vi15) / L_1478 (refinement) /
;   L_14D8 (perspective-divide cont) / L_1550 (save-context output).
; Two extra "landing slot" labels L_12A0/4140/4180 sit one bundle
; before their respective subroutine entries (L_12A8 / L_12B8 /
; L_12F8) so some callers can branch into the same routine one
; bundle later (skipping a leading nop_swap).
;
; sub_3C40's setup phase loads vf22/vf23/vf24 from mem[8/9/3/6]
; offsets and from vi03-relative stream, applies vf17 .xy fixups,
; itof0-casts integer fields to float, then runs the 6 LOD tiers.
; -----------------------------------------------------------------------
sub_3C40:
pad ; iaddiu vi08, vi00, 104
pad ; sq.xyzw vf22, 0(vi08)
L_0DC0:
pad ; sq.xyzw vf22, 9(vi08)
pad ; sq.xyzw vf23, 3(vi08)
pad ; iaddiu vi09, vi00, 164
pad ; sq.xyzw vf24, 6(vi08)
pad ; lq.xyzw vf22, -10(vi03)
add.xy vf22, vf22, vf17 ; lq.xyzw vf23, -6(vi03)
add.xy vf23, vf23, vf17 ; lq.xyzw vf24, -2(vi03)
add.xy vf24, vf24, vf17 ; nop_swap
pad ; sq.xyzw vf22, 2(vi08)
pad ; sq.xyzw vf22, 11(vi08)
pad ; sq.xyzw vf23, 5(vi08)
pad ; sq.xyzw vf24, 8(vi08)
pad ; lq.xyzw vf22, -5(vi07)
itof0.xyzw vf22, vf22 ; lq.xyzw vf23, -2(vi07)
itof0.xyzw vf23, vf23 ; lq.xyzw vf24, 1(vi07)
itof0.xyzw vf24, vf24 ; nop_swap
pad ; sq.xyzw vf22, 1(vi08)
pad ; sq.xyzw vf22, 10(vi08)
pad ; sq.xyzw vf23, 4(vi08)
pad ; sq.xyzw vf24, 7(vi08)

; --- LOD tier 1 ---
pad ; iaddiu vi05, vi00, 2048
pad ; iaddiu vi06, vi00, 32
pad ; iaddiu vi07, vi00, 2
pad ; iaddiu vi10, vi00, 3
pad ; iaddiu vi11, vi00, 0
subw.x vf30, vf00, vf00 ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
L_0EA0:
pad ; bal vi02, L_12F0
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, L_0EA0
pad ; nop_swap
pad ; iaddiu vi08, vi00, 164
pad ; bal vi02, L_12B0
pad ; nop_swap
.word 0x100002FF ; nop_swap              ; pad with M-bit flag
pad ; ibeq vi11, vi00, L_12A0
pad ; nop_swap

; --- LOD tier 2 ---
pad ; iaddiu vi05, vi00, 1024
pad ; iaddiu vi06, vi00, 16
pad ; iaddiu vi07, vi00, 2
pad ; iaddiu vi08, vi00, 164
pad ; iaddiu vi09, vi00, 104
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
addw.x vf30, vf00, vf00 ; nop_swap
pad ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
L_0F58:
pad ; bal vi02, L_12F0
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, L_0F58
pad ; nop_swap
pad ; iaddiu vi08, vi00, 104
pad ; bal vi02, L_12B0
pad ; nop_swap
pad ; ibeq vi11, vi00, L_12A0
pad ; nop_swap

; --- LOD tier 3 ---
pad ; iaddiu vi05, vi00, 128
pad ; iaddiu vi06, vi00, 2
pad ; iaddiu vi07, vi00, 0
pad ; iaddiu vi08, vi00, 104
pad ; iaddiu vi09, vi00, 164
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
subw.x vf30, vf00, vf00 ; nop_swap
pad ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
pad ; bal vi02, L_12F0
L_1010:
pad ; nop_swap
.word 0x4A000200 ; nop                   ; upper: `add vf08, vf00, vf00` + flag bits
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, L_1010
pad ; nop_swap
pad ; iaddiu vi08, vi00, 164
pad ; bal vi02, L_12B8
pad ; nop_swap
pad ; ibeq vi11, vi00, L_12A8
pad ; nop_swap

; --- LOD tier 4 ---
pad ; iaddiu vi05, vi00, 64
pad ; iaddiu vi06, vi00, 1
pad ; iaddiu vi07, vi00, 0
pad ; iaddiu vi08, vi00, 164
pad ; iaddiu vi09, vi00, 104
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
addw.x vf30, vf00, vf00 ; nop_swap
pad ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
L_10C0:
pad ; bal vi02, L_12F8
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, L_10C0
pad ; nop_swap
pad ; iaddiu vi08, vi00, 104
pad ; bal vi02, L_12B8
pad ; nop_swap
pad ; ibeq vi11, vi00, L_12A8
pad ; nop_swap

; --- LOD tier 5 ---
pad ; iaddiu vi05, vi00, 512
pad ; iaddiu vi06, vi00, 8
pad ; iaddiu vi07, vi00, 1
pad ; iaddiu vi08, vi00, 104
pad ; iaddiu vi09, vi00, 164
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
subw.x vf30, vf00, vf00 ; nop_swap
pad ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
L_1170:
pad ; bal vi02, L_12F8
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, L_1170
pad ; nop_swap
pad ; iaddiu vi08, vi00, 164
pad ; bal vi02, L_12B8
pad ; nop_swap
pad ; ibeq vi11, vi00, L_12A8
pad ; nop_swap

; --- LOD tier 6 ---
pad ; iaddiu vi05, vi00, 256
pad ; iaddiu vi06, vi00, 4
pad ; iaddiu vi07, vi00, 1
pad ; iaddiu vi08, vi00, 164
pad ; iaddiu vi09, vi00, 104
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
addw.x vf30, vf00, vf00 ; nop_swap
pad ; lqi.xyzw vf21, vi08
pad ; lqi.xyzw vf22, vi08
pad ; lqi.xyzw vf23, vi08
L_1220:
pad ; bal vi02, L_12F8
pad ; nop_swap
pad ; isubiu vi10, vi10, 1
pad ; nop_swap
pad ; ibne vi10, vi00, L_1220
pad ; nop_swap
pad ; iaddiu vi08, vi00, 104
pad ; bal vi02, L_12B8
pad ; nop_swap
pad ; ibeq vi11, vi00, L_12A8
pad ; nop_swap

; --- Final consolidation block: call save-context output at L_1550 ---
pad ; iaddiu vi08, vi00, 104
pad ; iaddiu vi09, vi00, 164
pad ; iadd vi10, vi00, vi11
pad ; iaddiu vi11, vi00, 0
pad ; bal vi01, L_1550
L_12A0:
pad ; nop_swap                           ; branch-landing slot before L_12A8
L_12A8:
pad ; jr vi15                            ; shared early-out return
L_12B0:
pad ; nop_swap                           ; branch-landing slot before L_12B8
L_12B8:
pad ; lq.xyzw vf21, 0(vi08)
pad ; lq.xyzw vf22, 1(vi08)
pad ; lq.xyzw vf23, 2(vi08)
pad ; sqi.xyzw vf21, vi09
pad ; sqi.xyzw vf22, vi09
pad ; sqi.xyzw vf23, vi09
pad ; jr vi02
L_12F0:
pad ; nop_swap                           ; branch-landing slot before L_12F8
L_12F8:
add.xyzw vf17, vf31, vf21 ; lqi.xyzw vf21, vi08
add.xyzw vf18, vf31, vf22 ; lqi.xyzw vf22, vi08
add.xyzw vf19, vf31, vf23 ; lqi.xyzw vf23, vi08
.word 0x01D189FF ; nop_swap              ; FD-dispatch FMAC variant
.word 0x01D5A9FF ; nop_swap
pad ; nop_swap
pad ; nop_swap
pad ; nop_swap
pad ; fcget vi01
pad ; iand vi04, vi01, vi05
pad ; nop_swap
pad ; ibeq vi04, vi00, L_13D0
pad ; nop_swap
pad ; iand vi04, vi01, vi06
pad ; nop_swap
pad ; ibeq vi04, vi00, L_1390
pad ; nop_swap
pad ; b L_1468
pad ; nop_swap
L_1390:
pad ; bal vi01, L_1478
pad ; nop_swap
pad ; sqi.xyzw vf25, vi09
pad ; sqi.xyzw vf26, vi09
pad ; sqi.xyzw vf27, vi09
pad ; iaddiu vi11, vi11, 1
pad ; b L_1468
pad ; nop_swap
L_13D0:
pad ; iand vi04, vi01, vi06
pad ; nop_swap
pad ; ibeq vi04, vi00, L_1448
pad ; nop_swap
pad ; bal vi01, L_1478
pad ; nop_swap
pad ; sqi.xyzw vf17, vi09
pad ; sqi.xyzw vf18, vi09
pad ; sqi.xyzw vf19, vi09
pad ; sqi.xyzw vf25, vi09
pad ; sqi.xyzw vf26, vi09
pad ; sqi.xyzw vf27, vi09
pad ; iaddiu vi11, vi11, 2
pad ; b L_1468
pad ; nop_swap
L_1448:
pad ; sqi.xyzw vf17, vi09
pad ; sqi.xyzw vf18, vi09
pad ; sqi.xyzw vf19, vi09
pad ; iaddiu vi11, vi11, 1
L_1468:
pad ; jr vi02
pad ; nop_swap
L_1478:
mulx.w vf25, vf17, vf30 ; iadd vi12, vi00, vi07
mulx.w vf26, vf21, vf30 ; nop_swap
subw.xyzw vf25, vf17, vf25 ; nop_swap
subw.xyzw vf26, vf21, vf26 ; nop_swap
pad ; nop_swap
L_14A0:
pad ; ibeq vi12, vi00, L_14D8
pad ; nop_swap
pad ; mr32.xyzw vf25, vf25
pad ; mr32.xyzw vf26, vf26
pad ; isubiu vi12, vi12, 1
pad ; b L_14A0
pad ; nop_swap
L_14D8:
sub.xyz vf27, vf26, vf25 ; nop_swap
pad ; div Q, vf25.x, vf27.x
addq.x vf29, vf00 ; waitq
abs.x vf29, vf29 ; nop_swap
sub.xyzw vf25, vf21, vf17 ; nop_swap
sub.xyzw vf26, vf22, vf18 ; nop_swap
sub.xyzw vf27, vf23, vf19 ; nop_swap
mulx.xyzw vf25, vf25, vf29 ; nop_swap
mulx.xyzw vf26, vf26, vf29 ; nop_swap
mulx.xyzw vf27, vf27, vf29 ; nop_swap
add.xyzw vf25, vf25, vf17 ; nop_swap
add.xyzw vf26, vf26, vf18 ; nop_swap
add.xyzw vf27, vf27, vf19 ; nop_swap
pad ; jr vi01
pad ; nop_swap

; -----------------------------------------------------------------------
; sub_43E0 — program-4 clone of sub_2818 (save-context vertex output).
; Two-stage GIF kick with matrix reload from mem[16..19].
; -----------------------------------------------------------------------
sub_43E0:
pad ; iaddiu vi02, vi00, 37
pad ; iadd vi03, vi00, vi08
pad ; iaddiu vi07, vi02, 2
pad ; iaddiu vi11, vi00, 32767
pad ; iaddiu vi11, vi11, 1
pad ; isw.x vi11, 0(vi02)
pad ; lq.xyzw vf01, 8(vi00)
pad ; lq.xyzw vf02, 9(vi00)
pad ; lq.xyzw vf03, 10(vi00)
pad ; lq.xyzw vf04, 11(vi00)
pad ; xgkick vi02
pad ; iaddiu vi11, vi10, 32767
pad ; iaddiu vi11, vi11, 1
pad ; isw.x vi11, 0(vi02)

sub_43E0_loop:
pad ; lq.xyzw vf20, 0(vi03)
mulax.xyzw  vf01, vf20 ; nop_swap
madday.xyzw vf02, vf20 ; nop_swap
maddaz.xyzw vf03, vf20 ; nop_swap
maddw.xyzw  vf25, vf04, vf20 ; nop_swap
pad ; div Q, vf00.w, vf25.w
mulq.xyzw   vf25, vf25 ; waitq
ftoi4.xyzw  vf26, vf25 ; nop_swap
pad ; sq.xyzw vf26, 1(vi07)
pad ; lq.xyzw vf20, 2(vi03)
mulq.xyz    vf28, vf20 ; nop_swap
pad ; sq.xyzw vf28, -1(vi07)
pad ; lq.xyzw vf27, 1(vi03)
ftoi0.xyzw  vf29, vf27 ; nop_swap
pad ; sq.xyzw vf29, 0(vi07)
pad ; iaddiu vi07, vi07, 3
pad ; iaddiu vi03, vi03, 3
pad ; iaddi vi10, vi10, -1
pad ; nop_swap
pad ; ibne vi10, vi00, sub_43E0_loop
pad ; nop_swap
pad ; xgkick vi02
pad ; lq.xyzw vf01, 16(vi00)
pad ; lq.xyzw vf02, 17(vi00)
pad ; lq.xyzw vf03, 18(vi00)
pad ; lq.xyzw vf04, 19(vi00)
pad ; nop_swap
pad ; jr vi01
pad ; nop_swap
pad ; sqd.xyzw vf17, vi14                ; entry of L_16A8/L_16B0 save-context

; -----------------------------------------------------------------------
; L_16B0 — VU0 register-bank save (program-4 clone of L_2978).
; sqd 15 floats + iswr 14 ints; `jr vi15` returns.
; -----------------------------------------------------------------------
L_16B0:
pad ; sqd.xyzw vf18, vi14
pad ; sqd.xyzw vf19, vi14
pad ; sqd.xyzw vf20, vi14
pad ; sqd.xyzw vf21, vi14
pad ; sqd.xyzw vf22, vi14
pad ; sqd.xyzw vf23, vi14
pad ; sqd.xyzw vf24, vi14
pad ; sqd.xyzw vf25, vi14
pad ; sqd.xyzw vf26, vi14
pad ; sqd.xyzw vf27, vi14
pad ; sqd.xyzw vf28, vi14
pad ; sqd.xyzw vf29, vi14
pad ; sqd.xyzw vf30, vi14
pad ; sqd.xyzw vf31, vi14
pad ; isubiu vi14, vi14, 1
pad ; iswr.x vi02, vi14
pad ; iswr.y vi03, vi14
pad ; iswr.z vi04, vi14
pad ; iswr.w vi05, vi14
pad ; isubiu vi14, vi14, 1
pad ; iswr.x vi06, vi14
pad ; iswr.y vi07, vi14
pad ; iswr.z vi08, vi14
pad ; iswr.w vi09, vi14
pad ; isubiu vi14, vi14, 1
pad ; iswr.x vi10, vi14
pad ; iswr.y vi11, vi14
pad ; iswr.z vi12, vi14
pad ; iswr.w vi13, vi14
pad ; isubiu vi14, vi14, 1
pad ; iswr.x vi14, vi14
pad ; iswr.y vi15, vi14
pad ; nop_swap
pad ; jr vi15
pad ; nop_swap

; -----------------------------------------------------------------------
; L_17D0 — VU0 register-bank restore (program-4 clone of L_2A98).
; Flag-bits-set FMAC at 0x46B0 (`.word 0x4A8D0300`) — `add.y vf12,
; vf00, vf13` with E/T/extra flag bits, emitted as `.word`.
; -----------------------------------------------------------------------
pad ; iadd vi01, vi00, vi15                ; (0x4658 — pre-L_17D0 setup bundle)
L_17D0:
pad ; iswr.x vi14, vi14
pad ; iswr.y vi15, vi14
pad ; iaddiu vi14, vi14, 1
pad ; ilwr.x vi10, vi14
pad ; ilwr.y vi11, vi14
pad ; ilwr.z vi12, vi14
pad ; ilwr.w vi13, vi14
pad ; iaddiu vi14, vi14, 1
pad ; ilwr.x vi06, vi14
pad ; ilwr.y vi07, vi14
.word 0x4A8D0300 ; nop                   ; upper: `add.y vf12, vf00, vf13` + flag bits
pad ; ilwr.z vi08, vi14
pad ; ilwr.w vi09, vi14
pad ; iaddiu vi14, vi14, 1
pad ; ilwr.x vi02, vi14
pad ; ilwr.y vi03, vi14
pad ; ilwr.z vi04, vi14
pad ; ilwr.w vi05, vi14
pad ; iaddiu vi14, vi14, 1
pad ; lqi.xyzw vf31, vi14
pad ; lqi.xyzw vf30, vi14
pad ; lqi.xyzw vf29, vi14
pad ; lqi.xyzw vf28, vi14
pad ; lqi.xyzw vf27, vi14
pad ; lqi.xyzw vf26, vi14
pad ; lqi.xyzw vf25, vi14
pad ; lqi.xyzw vf24, vi14
pad ; lqi.xyzw vf23, vi14
pad ; lqi.xyzw vf22, vi14
pad ; lqi.xyzw vf21, vi14
pad ; lqi.xyzw vf20, vi14
pad ; lqi.xyzw vf19, vi14
pad ; lqi.xyzw vf18, vi14
pad ; lqi.xyzw vf17, vi14
L_18E0:
pad ; nop_swap                           ; `jr vi01` return stub
pad ; jr vi01
pad ; nop_swap

; -----------------------------------------------------------------------
; L_18F8 — vertex-buffer init (program-4 clone of L_2BC0).
; Loads scratch matrix vf13..vf16 from mem[20..23], extended bulk
; load vf05..vf12 from mem[28..35] / mem[32..35].  Sets vi14 = 256.
; -----------------------------------------------------------------------
L_18F8:
sub.xyzw vf31, vf00, vf00 ; lq.xyzw vf17, 2(vi00)
pad ; lq.xyzw vf13, 20(vi00)
pad ; lq.xyzw vf14, 21(vi00)
pad ; lq.xyzw vf15, 22(vi00)
pad ; lq.xyzw vf16, 23(vi00)
pad ; lq.xyzw vf05, 28(vi00)
pad ; lq.xyzw vf06, 29(vi00)
pad ; lq.xyzw vf07, 30(vi00)
pad ; lq.xyzw vf08, 31(vi00)
pad ; lq.xyzw vf09, 32(vi00)
pad ; lq.xyzw vf10, 33(vi00)
pad ; lq.xyzw vf11, 34(vi00)
pad ; lq.xyzw vf12, 35(vi00)
mulw.w vf17, vf00, vf00 ; iaddiu vi14, vi00, 256
pad ; move.z vf17, vf00
epad ; nop_swap                          ; upper: E-bit pad (END)
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_4810 — bone-blended vertex transform with clip-flag culling
; (program-4 clone of sub_2C00, but with subtle vf-register
; reshuffling: vf18/vf19/vf20/vf21 instead of vf18/vf21/vf20).
; -----------------------------------------------------------------------
sub_4810:
pad ; xtop vi01
pad ; ilwr.x vi10, vi01
pad ; iaddiu vi11, vi00, 32767
pad ; iand vi10, vi10, vi11
pad ; iaddi vi11, vi11, 1
pad ; lq.xyzw vf25, 0(vi01)
pad ; iaddiu vi03, vi01, 1
pad ; iaddiu vi02, vi01, 192
pad ; sq.xyzw vf25, 0(vi02)
pad ; iaddiu vi07, vi02, 1
mulw.xyzw   vf22, vf00, vf00 ; iaddi vi04, vi00, -2
mulw.xyzw   vf23, vf00, vf00 ; iaddi vi05, vi00, -2
mulw.xyzw   vf24, vf00, vf00 ; iaddi vi06, vi00, -2
pad ; lq.xyzw vf19, 1(vi03)              ; (different load order vs sub_2C00)
pad ; lq.xyzw vf18, 0(vi03)
pad ; lq.xyzw vf21, 2(vi03)
pad ; lq.xyzw vf20, 3(vi03)

L_1A08:
mulax.xyzw  vf05, vf19 ; iaddiu vi03, vi03, 4
madday.xyzw vf06, vf19 ; iaddi vi10, vi10, -1
maddaz.xyzw vf07, vf19 ; iadd vi04, vi00, vi05
maddw.xyzw  vf26, vf08, vf19 ; iadd vi05, vi00, vi06
mulax.xyzw  vf01, vf18 ; move.xyzw vf22, vf23
madday.xyzw vf02, vf18 ; move.xyzw vf23, vf24
maddaz.xyzw vf03, vf18 ; lq.xyzw vf19, 1(vi03)
maxx.xyzw   vf26, vf26, vf00 ; nop_swap
pad ; nop_swap
pad ; nop_swap
maddw.xyzw  vf25, vf04, vf18 ; nop_swap
mulax.xyzw  vf09, vf26 ; nop_swap
madday.xyzw vf10, vf26 ; nop_swap
maddaz.xyzw vf11, vf26 ; nop_swap
maddw.xyzw  vf26, vf12, vf26 ; div Q, vf00.w, vf25.w
mulax.xyzw  vf13, vf18 ; nop_swap
madday.xyzw vf14, vf18 ; nop_swap
maddaz.xyzw vf15, vf18 ; nop_swap
maddw.xyzw  vf24, vf16, vf18 ; nop_swap
maxx.xyzw   vf26, vf26, vf00 ; lq.xyzw vf18, 0(vi03)
add.xy      vf21, vf21, vf17 ; nop_swap
mulq.xyzw   vf27, vf25 ; waitq
mulq.xyz    vf28, vf21 ; nop_swap
mul.xyz     vf20, vf20, vf26 ; nop_swap
; I-bit immediate bundle: upper sub.w vf00,vf21,vf00 + I-bit; lower = 255.0f → I.
; (disasm reads lower as `bal vi31, L_1AD0` — a misread; the next bundle is sequential.)
.word 0x8020A82C ; .word 0x437F0000

ftoi4.xyzw  vf27, vf27 ; lq.xyzw vf21, 2(vi03)
pad ; sq.xyzw vf28, 0(vi07)
minii.xyzw  vf20, vf20 ; nop_swap
.word 0x01D6B1FF ; fsand vi08, 0x2       ; flag-bit FD-dispatch FMAC
.word 0x01D7B9FF ; sq.xyzw vf27, 2(vi07)
.word 0x01D8C1FF ; nop_swap
pad ; nop_swap
pad ; nop_swap
pad ; nop_swap
ftoi0.xyzw  vf29, vf20 ; fcand vi01, 0x3F
pad ; lq.xyzw vf20, 3(vi03)
pad ; iadd vi06, vi00, vi01
pad ; ibeq vi08, vi00, L_1B58
pad ; sq.xyzw vf29, 1(vi07)               ; (delay slot)
pad ; iaddi vi04, vi00, 1
pad ; iaddi vi05, vi00, 1
pad ; iaddi vi09, vi00, 2
L_1B58:
pad ; iadd vi01, vi04, vi05
pad ; iadd vi01, vi01, vi06
pad ; nop_swap
pad ; ibgtz vi01, L_1BB0
pad ; nop_swap                           ; (delay slot)
L_1B80:
pad ; ibne vi10, vi00, L_1A08
pad ; iaddiu vi07, vi07, 3                ; (delay slot)
pad ; xgkick vi02
pad ; nop_swap
pad ; b L_18F8
pad ; nop_swap
L_1BB0:
pad ; iaddi vi09, vi09, -1
pad ; ibgtz vi09, L_1C80
pad ; fcor vi01, 0xFDF7DF
pad ; ibne vi01, vi00, L_1C80
pad ; nop_swap
pad ; fcor vi01, 0xFEFBEF
pad ; ibne vi01, vi00, L_1C80
pad ; nop_swap
pad ; fcor vi01, 0xFF7DF7
pad ; ibne vi01, vi00, L_1C80
pad ; nop_swap
pad ; fcor vi01, 0xFFBEFB
pad ; ibne vi01, vi00, L_1C80
pad ; nop_swap
pad ; fcor vi01, 0xFFDF7D
pad ; ibne vi01, vi00, L_1C80
pad ; nop_swap
pad ; fcor vi01, 0xFFEFBE
pad ; ibne vi01, vi00, L_1C80
pad ; nop_swap
pad ; bal vi15, L_16B0
pad ; nop_swap
pad ; bal vi15, L_0DC0
pad ; nop_swap
pad ; bal vi15, L_17D0
pad ; nop_swap
L_1C80:
pad ; b L_1B80
pad ; isw.w vi11, 2(vi07)                ; (delay slot)

; =======================================================================
; FIFTH VU0 PROGRAM begins here.  FCSET imm = 0x59 this time.
; Entry table at 0x4B40..0x4BE8 with targets L_1DB0 / L_1E38 /
; L_1E70 / L_1EE0 / L_1FB8 / L_1FD0 / L_2018 / L_2030.
; =======================================================================

nop ; .word 0x70000000                  ; 0x4B20 — op7=0x38
nop ; nop                               ; 0x4B28 — true-zero filler
.assert_pc 0x1CA0
