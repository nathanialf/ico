; -----------------------------------------------------------------------
; ParticleMicroProgram — VU1 microprogram (ico2000.a particle.o), seki/GS renderer.
;
; One of the 5 per-primitive VU1 microprograms in ICO's .vutext section
; (cluster/mesh/normal_c/normal_l/particle), managed by MicroCode.o
; (mc_TransMicroCode).  Split by the MAIN.MAP .vutext .o boundaries.
;
; Clean-room: bytes re-derived from published VU0/VU1 documentation
; (EE User's Manual, PCSX2 microVU GPL-3.0 opcode dispatch, ps2sdk) via
; tools/assemble_vu0.py — never from extracted disc data.  Byte-identical
; to aug6 .vutext 0x2704A0..0x270A50 (1456 bytes); labels are
; program-relative (VU micromem is loaded at 0).
; -----------------------------------------------------------------------
.vu0
.org 0x0000
nop ; .word 0x60000059                  ; 0x4B30 — FCSET imm24=0x59
.word 0x4AB20000 ; nop                  ; 0x4B38 — upper FMAC-family (`add.yw vf00, vf00, vf18`+flags)

; Program-5 entry dispatch.
pad ; b L_0110                          ; 0x4B40
pad ; nop_swap
pad ; b L_0198                          ; 0x4B50
pad ; nop_swap
pad ; nop_swap                          ; 0x4B60 — reserved
pad ; nop_swap                          ; 0x4B68 — reserved
pad ; nop_swap                          ; 0x4B70 — reserved
pad ; nop_swap                          ; 0x4B78 — reserved
pad ; b L_01D0                          ; 0x4B80
pad ; nop_swap
pad ; b L_0240                          ; 0x4B90
pad ; nop_swap
pad ; b L_0318                          ; 0x4BA0
pad ; nop_swap
pad ; nop_swap                          ; 0x4BB0 — reserved
pad ; nop_swap                          ; 0x4BB8 — reserved
pad ; b L_0330                          ; 0x4BC0
pad ; nop_swap
pad ; b L_0378                          ; 0x4BD0
pad ; nop_swap
pad ; b L_0390                          ; 0x4BE0
pad ; nop_swap
pad ; nop_swap                          ; 0x4BF0 — reserved
pad ; nop_swap                          ; 0x4BF8 — reserved

; Program-5 entry dispatch tail (8 reserved nop_swap fillers).
pad ; nop_swap                          ; 0x4C00 — reserved
pad ; nop_swap                          ; 0x4C08 — reserved
pad ; nop_swap                          ; 0x4C10 — reserved
pad ; nop_swap                          ; 0x4C18 — reserved
pad ; nop_swap                          ; 0x4C20 — reserved
pad ; nop_swap                          ; 0x4C28 — reserved
pad ; nop_swap                          ; 0x4C30 — reserved
pad ; nop_swap                          ; 0x4C38 — reserved

; -----------------------------------------------------------------------
; sub_4C40 — copy-with-count + xgkick + END (program-5 clone of sub_0EA0).
; -----------------------------------------------------------------------
sub_4C40:
pad ; xtop vi12
pad ; ilwr.x vi10, vi12
pad ; iaddiu vi07, vi12, 191
pad ; iaddiu vi09, vi07, 0
pad ; lqi.xyzw vf29, vi12
pad ; iaddiu vi13, vi00, 32767
pad ; iand vi10, vi13, vi10
pad ; sqi.xyzw vf29, vi09
sub_4C40_loop:
pad ; lqi.xyzw vf28, vi12
pad ; iaddi vi10, vi10, -1
pad ; nop_swap
pad ; ibne vi10, vi00, sub_4C40_loop
pad ; sqi.xyzw vf28, vi09                ; (delay slot)
pad ; nop_swap
pad ; xgkick vi07
epad ; nop_swap                          ; END
pad ; nop_swap

; -----------------------------------------------------------------------
; sub_4CC8 — mem[2].xy patch (program-5 clone of sub_0F28).
; -----------------------------------------------------------------------
sub_4CC8:
pad ; xtop vi01
pad ; lq.xyzw vf30, 2(vi00)
pad ; lqi.xyzw vf31, vi01
pad ; move.xy vf30, vf31
pad ; sq.xyzw vf30, 2(vi00)
epad ; nop_swap                          ; END
pad ; nop_swap

; -----------------------------------------------------------------------
; sub_4D00 — 4-quad matrix upload to mem[256] (program-5 clone of sub_0F60).
; -----------------------------------------------------------------------
sub_4D00:
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
epad ; nop_swap                          ; END
pad ; nop_swap

; -----------------------------------------------------------------------
; exit_4D60 — shared E-bit stub (program-5 clone of exit_0FC0).
; -----------------------------------------------------------------------
exit_4D60:
epad ; nop_swap                          ; END
pad ; nop_swap

; -----------------------------------------------------------------------
; sub_4D70 — palette-indexed vertex transform (clone of sub_0FD0);
; falls through into sub_4E48 for terminator.
; -----------------------------------------------------------------------
sub_4D70:
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

sub_4D70_loop:
add.xy vf09, vf09, vf16 ; lq.xyzw vf20, 256(vi15)
pad ; move.w vf09, vf00
pad ; iaddiu vi11, vi11, 1
pad ; ilwr.w vi14, vi11
pad ; iaddi vi10, vi10, -1
ftoi4.xyzw vf10, vf09 ; sqi.xyzw vf20, vi09
pad ; lq.xyzw vf09, 0(vi11)
pad ; iand vi15, vi13, vi14
pad ; ibne vi10, vi00, sub_4D70_loop
pad ; sqi.xyzw vf10, vi09                ; (delay slot)

pad ; nop_swap
pad ; xgkick vi07
pad ; nop_swap                           ; falls through into sub_4E48

; -----------------------------------------------------------------------
; sub_4E48 — final palette-step + `b exit_4D60` (clone of sub_10A8).
; -----------------------------------------------------------------------
sub_4E48:
add.xy vf16, vf16, vf17 ; nop_swap
pad ; b exit_4D60
pad ; nop_swap                           ; (delay slot)

; -----------------------------------------------------------------------
; sub_4E60 — 8-quad load into vf01..vf08 (variant of sub_03B8).
; -----------------------------------------------------------------------
sub_4E60:
pad ; xtop vi10
pad ; lqi.xyzw vf01, vi10
pad ; lqi.xyzw vf02, vi10
pad ; lqi.xyzw vf03, vi10
pad ; lqi.xyzw vf04, vi10
pad ; lqi.xyzw vf05, vi10
pad ; lqi.xyzw vf06, vi10
pad ; lqi.xyzw vf07, vi10
pad ; lqi.xyzw vf08, vi10

; -----------------------------------------------------------------------
; sub_4EA8 — 3-bundle shared terminator.  Also reachable from
; sub_4EC0's loop tail via `ibeq vi05, vi00, L_0378` or `b L_0378`.
; -----------------------------------------------------------------------
sub_4EA8:
pad ; nop_swap                           ; entry / delay slot of sub_4E60's lqi chain
epad ; nop_swap                          ; END
pad ; nop_swap                           ; E-bit delay slot

; -----------------------------------------------------------------------
; sub_4EC0 — particle / clip-test routine.  Loads input quads
; vf23/vf24/vf26/vf27/vf29, sets up output cursors vi02 = vi11,
; vi01 = mem[544], vi03 = vi01, vi05 = 0.  Per-particle loop:
;   - Load vf30/vf31 (position + direction).
;   - Build vf10 = vf30.xyz with .w=0; vf28 = (vf30 + vf30.w into .xy)
;     plus .zw masked.
;   - Run two FMAC chains producing vf09 and vf12 (transformed pos
;     and tangent).
;   - Compute vf13/vf14 = particle motion vectors using add+sub
;     micro-patches (lane-by-lane).
;   - addz/addx into vf20 for sprite axis.
;   - Two clip tests (sub.xyw + fmand chain) against vf26/vf27/vf10/vf11.
;   - On clip-pass: store vf09/vf12 to (vi03+3)/(vi03+5); advance.
;   - Loop count via vi07, then post-process and `b L_0378`.
; -----------------------------------------------------------------------
sub_4EC0:
pad ; xtop vi10
pad ; ilwr.x vi07, vi10
pad ; iaddiu vi11, vi10, 1
pad ; lqi.xyzw vf23, vi11
pad ; lqi.xyzw vf24, vi11
pad ; lqi.xyzw vf26, vi11
pad ; lqi.xyzw vf27, vi11
pad ; lqi.xyzw vf29, vi11
pad ; iaddiu vi02, vi11, 0
pad ; iaddiu vi01, vi00, 544
pad ; iaddiu vi03, vi01, 0
pad ; iaddiu vi05, vi00, 0

L_03F0:
pad ; lqi.xyzw vf30, vi02
pad ; lqi.xyzw vf31, vi02
pad ; iaddi vi07, vi07, -1
pad ; move.xyz vf10, vf30
pad ; move.w vf10, vf00
addw.xy vf28, vf00, vf30 ; iaddiu vi10, vi00, 1
subx.w vf00, vf31, vf00 ; move.zw vf28, vf00
mulax.xyzw vf01, vf10 ; sq.xyzw vf23, 0(vi03)
madday.xyzw vf02, vf10 ; nop_swap
maddaz.xyzw vf03, vf10 ; nop_swap
maddw.xyzw vf09, vf04, vf00 ; fmand vi11, vi10
mulx.xy vf28, vf28, vf29 ; ibeq vi11, vi10, L_0560
add.xy vf13, vf00, vf31 ; nop_swap
addw.z vf13, vf00, vf00 ; nop_swap
sub.w vf13, vf00, vf00 ; div Q, vf00.w, vf09.w
mulax.xyzw vf05, vf28 ; nop_swap
madday.xyzw vf06, vf28 ; move.xyzw vf10, vf09
maddaz.xyzw vf07, vf28 ; move.xyzw vf11, vf09
maddw.xyzw vf12, vf08, vf28 ; sq.xyzw vf13, 2(vi03)
add.xy vf14, vf00, vf31 ; iaddiu vi10, vi00, 208
addw.z vf14, vf00, vf00 ; nop_swap
sub.w vf14, vf00, vf00 ; nop_swap
sub.xy vf10, vf10, vf12 ; nop_swap
add.xy vf11, vf11, vf12 ; nop_swap
addz.xyz vf20, vf00, vf31 ; nop_swap
addx.w vf20, vf31, vf00 ; nop_swap
mulq.xyz vf10, vf10 ; nop_swap
mulq.xyz vf11, vf11 ; nop_swap
addy.x vf14, vf14, vf29 ; nop_swap
addz.y vf14, vf14, vf29 ; nop_swap
ftoi0.xyzw vf20, vf20 ; nop_swap
sub.xyw vf28, vf26, vf10 ; mfir.w vf09, vi00
sub.xyw vf28, vf10, vf27 ; mfir.w vf12, vi00
sub.xyw vf28, vf26, vf11 ; sq.xyzw vf14, 4(vi03)
sub.xyw vf28, vf11, vf27 ; sq.xyzw vf20, 1(vi03)
ftoi4.xyz vf09, vf10 ; fmand vi11, vi10
ftoi4.xyz vf12, vf11 ; fmand vi11, vi11
pad ; fmand vi11, vi11
pad ; fmand vi11, vi11
pad ; ibne vi11, vi10, L_0560
pad ; nop_swap                           ; (delay slot)
pad ; sq.xyzw vf09, 3(vi03)
pad ; sq.xyzw vf12, 5(vi03)
pad ; iaddiu vi05, vi05, 1
pad ; iaddiu vi04, vi03, 0
pad ; iaddiu vi03, vi03, 6

L_0560:
pad ; ibne vi07, vi00, L_03F0
pad ; nop_swap                           ; (delay slot)
pad ; ibeq vi05, vi00, L_0378
pad ; sq.xyzw vf24, 0(vi04)              ; (delay slot)
pad ; xgkick vi01
pad ; nop_swap
pad ; b L_0378                           ; → END
pad ; nop_swap                           ; (delay slot)

; =======================================================================
; SIXTH VU0 PROGRAM begins here (truncated — only the first 2 bundles
; of the header are within .vutext's 0x50E0 byte limit).  The rest of
; program 6 lives beyond the section in `.data` / non-VU memory.
; =======================================================================
nop ; .word 0x70000000                  ; 0x50D0 — lower op7=0x38
nop ; nop                               ; 0x50D8 — true-zero filler

; Trailing alignment padding — 0x40 bytes of zero between .vutext's
; logical end (0x50E0) and the next section's start (0x5120).  The
; original textbin .bin file extends to 0x5120 (file size 20768),
; and the linker uses those bytes for alignment between .vutext and
; .data.  Reproducing the same 0x40 zero bytes keeps the LD's
; section-end alignment at the original VMA.

.assert_pc 0x5B0
.assert_pc 0x5B0
