.global hashFun

.type hashFun, %function
.arch armv6     
.arm            
.fpu vfp        
.syntax unified 
.align 4
.data
.equ FP_OFFSET, 28 /*;(regs - 1) * 4*/

/* .equ for the hashFun */
.equ HASH_MASK, 0xFFFFFFFF /* ;2^32 - 1 */
.equ HASH_SHIFT, 6 /* ;2^6 = 64 */
.equ HASH_MULT, 0x632BE5FBC94F3B2D /* ;0x632BE5FBC94F3B2D = 0x632BE5FBC94F3B2D << 6 = 0x3B2D632BE5FBC94F */
.equ HASH_ADD, 0xB2D632BE5FBC94F3 /* ;0xB2D632BE5FBC94F3 = 0xB2D632BE5FBC94F3 << 16 = 0x3B2D632BE5FBC94F */
.equ HASH_INIT, 0x3B2D632BE5FBC94F /* ;0x3B2D632BE5FBC94F = 0x3B2D632BE5FBC94F << 6 = 0x3B2D632BE5FBC94F */



.text /*Tell the assembler that the following code is in the text section. */


/* ;The following code is the assembly code for hashFun. You will be implementing the following logic: */
/* ;hash = c + (hash << 6) + (hash << 16) - hash; */

hashFun:
    /* ;Use r4-r9 protected registers to store the input parameters.*/
    push    {r4-r9, fp, lr}     /* ; use r4-r9 protected regs */
    add     fp, sp, #FP_OFFSET /* ; fp = sp + 28 */
                                /*; Use temporary r0-r3 to preserve r4-r9. */
    mov     r0, r4              /*; r0 = r4 */
    mov     r1, r5              /*; r1 = r5 */
    mov     r2, r6             /*; r2 = r6 */
    mov     r3, r7             /* ; r3 = r7 */
    mov     r4, r8             /* ; r4 = r8 */
    mov     r5, r9             /*; r5 = r9 */

    /* ; Hash the input string. */
    mov     r6, r0             /*; r6 = r0 */
  
    mov     r8, #HASH_MASK     /*; r8 = HASH_MASK */
    mov     r9, #HASH_SHIFT    /*; r9 = HASH_SHIFT */
    /*; call hashLoop */
    bl      hashLoop
    
    hashLoop:
        mov     r0, r6           /*; r0 = r6 */
        mov     r3, r8           /*; r3 = r8 */
        mov     r4, r9           /*; r4 = r9 */
        lsl     r3, r3, r9       /*; r3 = r3 << r9 */
        lsl     r4, r4, r9       /*; r4 = r4 << r9 */
        add     r2, r2, r3       /*; r2 = r2 + r3 */
        add     r3, r2, r4       /*; r3 = r2 + r4 */
        sub     r2, r2, r3       /*; r2 = r2 - r3 */
        add     r1, r1, r2       /*; r1 = r1 + r2 */
        lsr     r1, r1, r9       /*; r1 = r1 >> r9 */
        add     r0, r0, r1       /*; r0 = r0 + r1 */
        lsr     r1, r1, r9       /*; r1 = r1 >> r9 */
        cmp     r6, #0           /*; r6 = r6 == 0 ? */
        bne     hashLoop         /* ; if not, goto hashLoop */
        mov     r0, r1           /*; r0 = r1 */
        pop     {r4-r9, fp, pc}  /*; restore r4-r9, fp, and return */
        /*; End of hashLoop */
        
        /*; End of hashFun */
.end hashFun
        



    



