xbsywt: lodd 4095       ; get xmtr status
        subd mask:
        jneg xbsywt:    ; loop if busy
        retn
