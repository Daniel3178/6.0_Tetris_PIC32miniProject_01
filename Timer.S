
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw \reg,0($sp)
.endm

.macro	POP reg
	lw	 \reg,0($sp)
	addi	$sp,$sp,4
.endm

.data
.global enable_interrupts
.global delay
.text

enable_interrupts:
	ei

	jr $ra
	nop

delay: 
    move $t0, $a0   # t0 = arg
    li $t1, 0x00    # i = 0;
    lui $t2, 0x1b   # length = 0x1b7740
    ori $t2, $t2, 0x7740
    j while
    nop

    while:
        slti $t3, $t0, 0x00     #set true if i < 0;
        bne $t3, $0, breakLoop  #if true, break
        nop
        sub $t0, $t1, 0x1
    
        for:
            beq $t1, $t2, end   #if i == length, end
            nop
            addi $t1, $t1, 0x1
            j for
            nop
        end:
            j while
            nop
    breakLoop:
        jr $ra
        nop