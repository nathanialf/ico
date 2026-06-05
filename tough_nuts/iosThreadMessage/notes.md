# iosThreadMessage — parked (rc5, fumi/ios/thread)
Struct of function pointers. rc12 (ternary) -> rc9 (stop-temp) -> rc8 (f8-store-early)
-> rc5 (if/else + stop-temp + f8-early; registers start=v0/stop=v1 now match).
Residual: lui order (built luis stop first, ROM start first) + f8 store position
(built early before branch, ROM late after f4). ~30 distinct hand shapes. Permuter-class.
