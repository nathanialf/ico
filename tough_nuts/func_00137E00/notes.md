# func_00137E00 (fumi/ios/mcdata) — parked rc3 (b), twin of func_00137DB8 (writes 9)
Same -2 register-coalescing floor (a3 arg reg reused for AND mask in ROM; gcc
materializes -2 twice). union+int-return -> rc3; ~30 forms incl long-long arg all
rc3. See func_00137DB8 notes. Twins: func_00137ED8, func_00137F20.
