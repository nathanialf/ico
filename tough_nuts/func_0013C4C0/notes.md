# func_0013C4C0 (pad) — near-miss rc4, struct-init store-order / jr-delay occupant

Pure field-init, NO loop/call. 18 stores: f0=0x11(sb), f2=a3(sb), f3=a4(sb,5th EE arg t0),
f4=a1(sw), f14=a2(sw), rest zeros (f8/fA/fC/f10/f12/f18/f1A/f1C/f20/f22 = sh 0; f24/f26/f27 = sb 0).
BEST C (rc4) = stores written in the EXACT ROM output order:
  f3,f0,f4,f14,f2,f24,f8,f12,f10,fC,fA,f26,f18,f22,f20,f1C,f1A,f27.
ALL 18 stores correct; ONLY diff: gcc moves f27 (last sb) EARLY (groups it with the byte stores)
and fills the jr-delay with f1A (sh); ROM keeps f1A before jr and f27 in the jr-delay.
Tried: ascending field order (more scattered); ROM-output order (rc4); lever.py reorder 308:311
(lever metric misleads — its "winner" regressed match_loop rc 4->6).
NEXT: full store-order sweep (18! impractical by hand; offline reorder/permuter); or find the source
order where gcc leaves f27 as the dbr delay-slot fill (stop the byte-store grouping of f27).
