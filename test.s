.segment "CODE"

.proc main
    nop
    lda #5
    sec
    sbc #10
    sta $FA
    lda $FA
    adc $FA
    nop
.endproc
