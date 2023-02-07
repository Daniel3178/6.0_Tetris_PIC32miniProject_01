
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw \reg,0($sp)
.endm

.macro	POP reg
	lw	 \reg,0($sp)
	addi	$sp,$sp,4
.endm

.data
.align 2
.global enable_interrupts
.global delay
.global memcpy
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
memcpy:
# check if aligned
    andi $t0,$a0,3
    andi $t1,$a1,3
    or $t0,$t0,$t1
    bne $t0,$zero,byteloop
    nop
#copy word by word
    wordloop:
        slti $t0,$a2,4 # check if fewer than 4 bytes
        bne $t0,$zero,byteloop
        nop
        lw $t0,0($a0) # load word
        sw $t0,0($a1) # store word
        addi $a0,$a0,4 # increment src pointer
        addi $a1,$a1,4 # increment dst pointer
        addi $a2,$a2,-4 # decrement counter
        j wordloop
        nop
# standard, byte by byte of the rest
    byteloop:
        beq $a2,$zero,done # branch if done
        lb $t0,0($a0) # load byte
        sb $t0,0($a1) # store byte
        addi $a0,$a0,1 # increment src pointer
        addi $a1,$a1,1 # increment dst pointer
        addi $a2,$a2,-1 # decrement counter
        j byteloop
        nop
    done:
        jr $ra
        nop