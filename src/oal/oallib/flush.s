    INCLUDE kxarm.h
    TEXTAREA

    EXPORT _flush
    LEAF_ENTRY _flush

	mov     r0, #0
	mcr     p15, 0, r0, c8, c7, 0           ; invalidate TLB's
	dsb

    bx lr
    
    ENTRY_END

    END
