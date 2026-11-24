.segment "CODE"

.proc main
    lda #5
    sec
    sbc #5 

    beq is_zero

    lda #10 
    jmp done

is_zero:
    lda #20 ; works

done:
    nop
.endproc