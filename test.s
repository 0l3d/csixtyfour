.segment "CODE"

.proc main
    nop
    lda #5
    sec
    sbc #10
    sta 53280
    lda 53280
    adc 53280
    nop
.endproc
