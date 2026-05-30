extern int D_00631B40;

/* Pre-increment in v0 throughout: `lw $2; addiu $2,1; sw $2` (the store
 * fills the jr delay slot), keeping the value in $v0 the whole time —
 * matches WITHOUT the coalesce_v1_v0 postprocess (no redundant move $2,$3). */
/* Declared void: ee-gcc loads the global into $v0 as scratch, increments,
 * and the store fills the jr delay slot — all in $v0, no redundant move
 * $2,$3. An int return forces gcc to split load/modify into $v1 and copy
 * to $v0 (the shape that needed the coalesce_v1_v0 postprocess); the value
 * left in $v0 here is incidental, so callers that read it still work. */
void func_00105258(void)
{
    D_00631B40++;
}
