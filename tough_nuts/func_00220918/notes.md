# func_00220918 (script/src/st08a) — parked at rc4

Door-open setup: GObj sub at +0x164; sets sub->field_B4=&D_004CCAA0,
D_004CCAA0[1]=&actSt05eSolar, D_0062A894=1, sub->field_B0=0;
BoxBarSoundOn(obj,0x189); _ACTWait(0).

## Best seed (rc4) — capture form from permuter output-125
- struct DoorSub for `s` (deref result -> a2, not a3)
- int[] D_004CCAA0; new_var2 = (D_004CCAA0[1] = (int)solar, (void*)solar);
  + new_var = new_var2 copy => keeps solar (v1) live -> FIXES prologue %hi grouping.
- store order brute-forced (all 120 perms of the 5 stores): current order is the floor.

## CORRECT at rc4: prologue %hi grouping, a2/a3 (const->a3, deref s->a2),
## v0/v1 (D_004CCAA0->v0, solar->v1), const placement, reads, frame.

## RESIDUAL (4 diffs): store SCHEDULE only.
- [1] store (sw v1,4(v0)) hoisted to right after the deref (should be 3rd store).
- gp store (sw a3,0(gp)) pushed after 0xB4 (should be 1st store).
- Built order: [1], 0xB4, gp ; Expected: gp, 0xB4, [1].
- The [1] hoist is intrinsic to the capture form (capture must be early for the
  prologue fix); store-order reordering can't move it (brute-forced). Need a
  permuter perturbation that defers the [1] store while keeping solar live early.

## Coupling history: rc9 (struct s + void*[] D, a2/a3 swap) -> permuter new_var
## (rc8) -> hand rc6 -> permuter output-125 capture (rc4). Re-seed permuter from rc4.
