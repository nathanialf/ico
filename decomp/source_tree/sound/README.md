# `sound/` — recovered ICO source

EE-side sound init / ADPCM. IOP-side audio lives in another ELF.

**2 file(s)** recovered from `__FILE__` literals in `baserom/baseelf.elf` `.rodata`. Each placeholder records its anchor vma — the address of the literal that lets us tie a `.text` function back to this TU.

See `../source_tree.md` for the full recovery method.

## Files

- `adpcm_init.c` — anchor 0x00557b78
- `s_init.c` — anchor 0x00557cc8
